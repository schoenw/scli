/* 
 * cisco.c -- scli cisco mode implementation
 *
 * Copyright (C) 2001 Juergen Schoenwaelder
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 * @(#) $Id$
 */

/*
 * TODO:
 *
 * - document the commands
 * - show the serial number in the checkpoints
 * - add some xml support
 * - add raw data support for the current accounting table
 * - finalize the show cisco processes command
 */

#include "scli.h"

#include "snmpv2-mib.h"

#include "old-cisco-ip-mib.h"
#include "cisco-process-mib.h"


typedef struct {
    guchar  src[4];
    guchar  dst[4];
    guint32 inPkts;
    guint32 inByts;
    guint32 outPkts;
    guint32 outByts;
} act_stats_t;


static int 
stats_sort(const void *arg1, const void *arg2)
{
    act_stats_t *p = (act_stats_t *) arg1;
    act_stats_t *q = (act_stats_t *) arg2;

    guint32 psum = p->inByts + p->outByts;
    guint32 qsum = q->inByts + q->outByts;
    
    if (psum > qsum) {
	return -1;
    } else if (psum == qsum) {
	return 0;
    } else {
	return 1;
    }
}



static void
fmt_cisco_ip_accounting(GString *s, act_stats_t *statEntry)
{
    guint32 total_byts = 0;
    guint32 total_pkts = 0;
    
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(statEntry->src, SCLI_FMT_ADDR));
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(statEntry->dst, SCLI_FMT_ADDR));

    g_string_sprintfa(s, "%6s ", fmt_kmg(statEntry->inPkts));
    total_pkts += statEntry->inPkts;

    g_string_sprintfa(s, "%6s ", fmt_kmg(statEntry->inByts));
    total_byts += statEntry->inByts;

    g_string_sprintfa(s, "%6s ", fmt_kmg(statEntry->outPkts));
    total_pkts += statEntry->outPkts;
	
    g_string_sprintfa(s, "%6s ", fmt_kmg(statEntry->outByts));
    total_byts += statEntry->outByts;

    g_string_sprintfa(s, "%7s ", fmt_kmg(total_pkts));
    g_string_sprintfa(s, "%6s ", fmt_kmg(total_byts));
    
    g_string_append(s, "\n");
}



static void
fmt_cisco_ip_accounting_current(GString *s,
			old_cisco_ip_mib_lipAccountEntry_t *srcActEntry,
			old_cisco_ip_mib_lipAccountEntry_t *dstActEntry)
{
    guint32 total_byts = 0;
    guint32 total_pkts = 0;
    
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(srcActEntry->actSrc, SCLI_FMT_ADDR));
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(srcActEntry->actDst, SCLI_FMT_ADDR));

    if (srcActEntry->actPkts) {
	g_string_sprintfa(s, "%6s ", fmt_kmg(*srcActEntry->actPkts));
	total_pkts += *srcActEntry->actPkts;
    } else {
	g_string_sprintfa(s, "%6s ", "");
    }

    if (srcActEntry->actByts) {
	g_string_sprintfa(s, "%6s ", fmt_kmg(*srcActEntry->actByts));
	total_byts += *srcActEntry->actByts;
    } else {
	g_string_sprintfa(s, "%6s ", "");
    }

    if (dstActEntry && dstActEntry->actPkts) {
	g_string_sprintfa(s, "%6s ", fmt_kmg(*dstActEntry->actPkts));
	total_pkts += *dstActEntry->actPkts;
    } else {
	g_string_sprintfa(s, "%6s ", "");
    }
	
    if (dstActEntry && dstActEntry->actByts) {
	g_string_sprintfa(s, "%6s ", fmt_kmg(*dstActEntry->actByts));
	total_byts += *dstActEntry->actByts;
    } else {
	g_string_sprintfa(s, "%6s ", "");
    }

    if (srcActEntry->actPkts || (dstActEntry && dstActEntry->actPkts)) {
	g_string_sprintfa(s, "%7s ", fmt_kmg(total_pkts));
    } else {
	g_string_sprintfa(s, "%7s ", "");
    }

    if (srcActEntry->actByts || (dstActEntry && dstActEntry->actByts)) {
	g_string_sprintfa(s, "%6s ", fmt_kmg(total_byts));
    } else {
	g_string_sprintfa(s, "%6s ", "");
    }
    
    g_string_append(s, "\n");
}


static void
fmt_cisco_ip_accounting_current_raw(GString *s,
			    old_cisco_ip_mib_lipAccountEntry_t *ActEntry)
{
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(ActEntry->actSrc, SCLI_FMT_ADDR));
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(ActEntry->actDst, SCLI_FMT_ADDR));

    if (ActEntry->actPkts) {
	g_string_sprintfa(s, "%12u ", *ActEntry->actPkts);
    } else {
	g_string_sprintfa(s, "%12u ", 0);
    }

    if (ActEntry->actByts) {
	g_string_sprintfa(s, "%12u ", *ActEntry->actByts);
    } else {
	g_string_sprintfa(s, "%12u ", 0);
    }

    g_string_append(s, "\n");
}


static int
show_cisco_ip_accounting_current_sorted(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lipAccountEntry_t **lipAccountTable = NULL;
    int i, j, n;
    act_stats_t *stats;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    old_cisco_ip_mib_get_lipAccountingTable(interp->peer,
					    &lipAccountTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lipAccountTable) {
	g_string_sprintfa(interp->header,
			  "SOURCE           DESTINATION       "
			  " PKTS > BYTS   PKTS < BYTS   TPKTS  TBYTS");

	for (n = 0; lipAccountTable[n]; n++) ;
	stats = g_new0(act_stats_t, n);
	
	for (i = 0; lipAccountTable[i]; i++) {
	    for (j = 0; lipAccountTable[j]; j++) {
		if ((memcmp(lipAccountTable[i]->actSrc,
			    lipAccountTable[j]->actDst, 4) == 0)
		    && (memcmp(lipAccountTable[i]->actDst,
			       lipAccountTable[j]->actSrc, 4) == 0)) {
		    break;
		}
	    }
	    memcpy(stats[i].src, lipAccountTable[i]->actSrc, 4);
	    memcpy(stats[i].dst, lipAccountTable[i]->actDst, 4);
	    stats[i].inByts = lipAccountTable[i]->actByts ?
		*lipAccountTable[i]->actByts : 0;
	    stats[i].inPkts = lipAccountTable[i]->actPkts ?
		*lipAccountTable[i]->actPkts : 0;
	    if (lipAccountTable[j]) {
		stats[i].outByts = lipAccountTable[j]->actByts ?
		    *lipAccountTable[j]->actByts : 0;
		stats[i].outPkts = lipAccountTable[j]->actPkts ?
		    *lipAccountTable[j]->actPkts : 0;
	    }
	}

	qsort((void *) stats, (size_t) n, sizeof(act_stats_t), stats_sort);

	for (i = 0; i < n; i++) {
	    fmt_cisco_ip_accounting(interp->result, stats+i);
	}
	g_free(stats);
    }

    if (lipAccountTable)
	old_cisco_ip_mib_free_lipAccountingTable(lipAccountTable);

    return SCLI_OK;
}



static int
show_cisco_ip_accounting_current_raw(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lipAccountEntry_t **lipAccountTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    old_cisco_ip_mib_get_lipAccountingTable(interp->peer,
					    &lipAccountTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lipAccountTable) {
	g_string_sprintfa(interp->header,
			  "SOURCE           DESTINATION           PACKETS        BYTES");
	for (i = 0; lipAccountTable[i]; i++) {
	    fmt_cisco_ip_accounting_current_raw(interp->result,
						lipAccountTable[i]);
	}
    }

    if (lipAccountTable)
	old_cisco_ip_mib_free_lipAccountingTable(lipAccountTable);

    return SCLI_OK;
}



static int
show_cisco_ip_accounting_snapshot_sorted(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lipCkAccountEntry_t **lipCkAccountTable = NULL;
    int i, j;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    old_cisco_ip_mib_get_lipCkAccountingTable(interp->peer,
					      &lipCkAccountTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lipCkAccountTable) {
	g_string_sprintfa(interp->header,
			  "SOURCE           DESTINATION       "
			  " PKTS > BYTS   PKTS < BYTS   TPKTS  TBYTS");
	for (i = 0; lipCkAccountTable[i]; i++) {
	    for (j = 0; lipCkAccountTable[j]; j++) {
		if ((memcmp(lipCkAccountTable[i]->ckactSrc,
			    lipCkAccountTable[j]->ckactDst, 4) == 0)
		    && (memcmp(lipCkAccountTable[i]->ckactDst,
			    lipCkAccountTable[j]->ckactSrc, 4) == 0)) {
		    break;
		}
	    }
	    fmt_cisco_ip_accounting_current(interp->result,
	     (old_cisco_ip_mib_lipAccountEntry_t *) lipCkAccountTable[i],
	     (old_cisco_ip_mib_lipAccountEntry_t *) (lipCkAccountTable[j] ?
				     lipCkAccountTable[j] : NULL));
	}
    }

    if (lipCkAccountTable)
	old_cisco_ip_mib_free_lipCkAccountingTable(lipCkAccountTable);

    return SCLI_OK;
}


static int
show_cisco_ip_accounting_snapshot_raw(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lipCkAccountEntry_t **lipCkAccountTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    old_cisco_ip_mib_get_lipCkAccountingTable(interp->peer,
					      &lipCkAccountTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lipCkAccountTable) {
	g_string_sprintfa(interp->header,
			  "SOURCE           DESTINATION           PACKETS        BYTES");
	for (i = 0; lipCkAccountTable[i]; i++) {
	    fmt_cisco_ip_accounting_current_raw(interp->result,
						(old_cisco_ip_mib_lipAccountEntry_t *) lipCkAccountTable[i]);
	}
    }

    if (lipCkAccountTable)
	old_cisco_ip_mib_free_lipCkAccountingTable(lipCkAccountTable);

    return SCLI_OK;
}



static void
fmt_cisco_ip_accounting_info(GString *s,
			     old_cisco_ip_mib_lip_t *lip)
{
    if (lip->actThresh) {
	g_string_sprintfa(s, "Max. Records: %10d", *lip->actThresh);
    }

    if (lip->ckactAge) {
	g_string_sprintfa(s, "        Checkpoint  Start: %s\n",
			  fmt_timeticks(*lip->ckactAge));
    }

    if (lip->actLostPkts) {
	g_string_sprintfa(s, "Lost Packets: %10d", *lip->actLostPkts);
    }

    if (lip->actAge) {
	g_string_sprintfa(s, "        Current     Start: %s\n",
			  fmt_timeticks(*lip->actAge));
    }

    if (lip->actLostByts) {
	g_string_sprintfa(s, "Lost Bytes:   %10d", *lip->actLostByts);
    }

    if (lip->actCheckPoint) {
	g_string_sprintfa(s, "        Checkpoint Serial: %d\n",
			  *lip->actCheckPoint);
    }

    /* ipNoaccess ? */   
}



static int
show_cisco_ip_accounting_info(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lip_t *lip;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    old_cisco_ip_mib_get_lip(interp->peer, &lip, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lip) {
	fmt_cisco_ip_accounting_info(interp->result, lip);
    }

    if (lip) old_cisco_ip_mib_free_lip(lip);

    return SCLI_OK;
}



static void
fmt_x_kbytes(GString *s, guint32 bytes)
{
    if (bytes > 9999999) {
	g_string_sprintfa(s, "%5uG", bytes / 1024 / 1024);
    } else if (bytes > 9999) {
	g_string_sprintfa(s, "%5uM", bytes / 1024);
    } else {
	g_string_sprintfa(s, "%5uK", bytes);
    }
}



static void
fmt_cisco_processes(GString *s,
		    cisco_process_mib_cpmProcessEntry_t *procEntry,
		    cisco_process_mib_cpmProcessExtEntry_t *extEntry,
		    cisco_process_mib_cpmProcessExtRevEntry_t *extRevEntry)
{
    guint32 usecs = 0;
    
    g_string_sprintfa(s, "%5u ", procEntry->cpmCPUTotalIndex);

    g_string_sprintfa(s, "%5u ", procEntry->cpmProcessPID);

    if (extEntry && extEntry->cpmProcExtPriority) {
	g_string_sprintfa(s, "%d ", *extEntry->cpmProcExtPriority);
    }

    if (extEntry
	&& extEntry->cpmProcExtMemAllocated
	&& extEntry->cpmProcExtMemFreed) {
	guint32 bytes = *extEntry->cpmProcExtMemAllocated
	    - *extEntry->cpmProcExtMemFreed;
	fmt_x_kbytes(s, bytes/1024);
    }

    /*
     * xxx This seems to be broken. I think we have to look at
     * extRevEntry->cpmProcExtRuntimeRev to get useful data on boxes
     * that support this or extEntry->cpmProcExtRuntime.
     */

#if 1
    if (extRevEntry && extRevEntry->cpmProcExtRuntimeRev) {
	usecs = *extRevEntry->cpmProcExtRuntimeRev;
    } else if (extEntry && extEntry->cpmProcExtRuntime) {
        usecs = *extEntry->cpmProcExtRuntime;
    } else {
	usecs = 0;
    }
#else
    if (procEntry->cpmProcessAverageUSecs) {
	usecs = *procEntry->cpmProcessAverageUSecs;
    } else if (procEntry->cpmProcessuSecs) {
	usecs = *procEntry->cpmProcessuSecs;
    }
#endif
    g_string_sprintfa(s, " %s ",
		      fmt_seconds(usecs/1000));

    if (procEntry->cpmProcessName && procEntry->_cpmProcessNameLength) {
	g_string_sprintfa(s, "%.*s", procEntry->_cpmProcessNameLength,
			  procEntry->cpmProcessName);
    }
    g_string_append(s, "\n");
}



static int
show_cisco_processes(scli_interp_t *interp, int argc, char **argv)
{
    cisco_process_mib_cpmProcessEntry_t **procTable = NULL;
    cisco_process_mib_cpmProcessExtEntry_t **extTable = NULL;
    cisco_process_mib_cpmProcessExtRevEntry_t **extRevTable = NULL;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    cisco_process_mib_get_cpmProcessTable(interp->peer,
					  &procTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (procTable) {
	cisco_process_mib_get_cpmProcessExtTable(interp->peer,
						 &extTable, 0);
	cisco_process_mib_get_cpmProcessExtRevTable(interp->peer,
						    &extRevTable, 0);
	g_string_sprintfa(interp->header,
			  "  CPU   PID P MEMORY      TIME COMMAND");
	for (i = 0; procTable[i]; i++) {
	    fmt_cisco_processes(interp->result, procTable[i],
				extTable ? extTable[i] : NULL,
				extRevTable ? extRevTable[i] : NULL);
	}
    }

    if (procTable)
	cisco_process_mib_free_cpmProcessTable(procTable);
    if (extTable)
	cisco_process_mib_free_cpmProcessExtTable(extTable);
    if (extRevTable)
	cisco_process_mib_free_cpmProcessExtRevTable(extRevTable);
    
    return SCLI_OK;
}


static int
set_cisco_ip_accounting_checkpoint(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lip_t *lip;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    old_cisco_ip_mib_get_lip(interp->peer, &lip, OLD_CISCO_IP_MIB_ACTCHECKPOINT);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lip) {
        old_cisco_ip_mib_set_lip(interp->peer, lip, OLD_CISCO_IP_MIB_ACTCHECKPOINT);
        if (interp->peer->error_status) {
	    return SCLI_SNMP;
        }
    }

    if (lip->actCheckPoint) {
        g_string_sprintfa(interp->result, "%d\n", *lip->actCheckPoint);
    }

    if (lip) old_cisco_ip_mib_free_lip(lip);

    return SCLI_OK;
}


void
scli_init_cisco_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	
	{ "show cisco processes", NULL,
	  "The `show cisco processes' command displays information about\n"
	  "all processes running on a CISCO device. The command generates\n"
	  "a table with the following columns:\n"
	  "\n"
	  "  CPU     processor executing a given process\n"
	  "  PID     process indentification number on a CPU\n"
	  "  P       priority of the process\n"
	  "  MEMORY  memory used by the process\n"
	  "  TIME    CPU time used by the process\n"
	  "  COMMAND command executed by the process",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_processes },

	{ "show cisco ip accounting info", NULL,
	  "The `show cisco ip accounting info' command displays general\n"
	  "status information concerning the simple cisco IPv4 accounting\n"
	  "mechanism supported by many older cisco devices. In particular,\n"
	  "it displays the starting point of the current and snapshot data\n"
	  "tables, information about the available accounting capacity,\n"
	  "and statistics about lost bytes and packets.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_ip_accounting_info },

	{ "show cisco ip accounting current sorted", NULL,
	  "cisco IP current accounting data",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_ip_accounting_current_sorted },

	{ "show cisco ip accounting current raw", NULL,
	  "The `show cisco ip accounting current raw' command displays\n"
	  "the raw accounting data retrieved from the current table. The\n"
	  "command generates a table with the following columns:\n"
	  "\n"
	  "  SOURCE      source IPv4 address in dotted notation \n"
	  "  DESTINATION destination IPv4 address in dotted notation\n"
	  "  PACKETS     packets sent from source to destination\n"
	  "  BYTES       bytes sent from source to destination",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_ip_accounting_current_raw },

	{ "show cisco ip accounting snapshot sorted", NULL,
	  "cisco IP snapshot accounting data",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_ip_accounting_snapshot_sorted },

	{ "show cisco ip accounting snapshot raw", NULL,
	  "The `show cisco ip accounting snapshot raw' command displays\n"
	  "the raw accounting data retrieved from the snapshot table. The\n"
	  "command generates a table with the following columns:\n"
	  "\n"
	  "  SOURCE      source IPv4 address in dotted notation \n"
	  "  DESTINATION destination IPv4 address in dotted notation\n"
	  "  PACKETS     packets sent from source to destination\n"
	  "  BYTES       bytes sent from source to destination",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_ip_accounting_snapshot_raw },

	{ "monitor cisco ip accounting current", NULL,
	  "cisco IP current accounting data",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_ip_accounting_current_sorted },

	{ "monitor cisco ip accounting snapshot sorted", NULL,
	  "cisco IP snapshot accounting data",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_ip_accounting_snapshot_sorted },

	{ "set cisco ip accounting checkpoint", NULL,
	  "The `set cisco ip accounting checkpoint' command takes a\n"
	  "snapshot of the current accounting table by copying it to\n"
	  "the snapshot accounting table. The current accounting table\n"
	  "is reinitialized before it is updated again. The command\n"
	  "returns the serial number of the snapshot.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  set_cisco_ip_accounting_checkpoint },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t cisco_mode = {
	"cisco",
	"The cisco scli mode is used to display and configure cisco\n"
	"parameters. It also supports retrieval of accounting data\n"
	"from devices that support the old cisco accounting mib. This\n"
	"mode is based on the OLD-CISCO-IP-MIB published in May 1994.",
	cmds
    };

    scli_register_mode(interp, &cisco_mode);
}
