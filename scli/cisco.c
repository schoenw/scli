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

#include "scli.h"

#include "old-cisco-ip-mib.h"
#include "snmpv2-mib.h"


typedef struct {
    guchar  src[4];
    guchar  dst[4];
    guint32 inPkts;
    guint32 inByts;
    guint32 outPkts;
    guint32 outByts;
} act_stats_t;


static int 
stats_sort (const void *arg1, const void *arg2)
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
show_cisco_ip_accounting(GString *s, act_stats_t *statEntry)
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
show_cisco_ip_accounting_current(GString *s,
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



static int
cmd_cisco_ip_accounting_current(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lipAccountEntry_t **lipAccountTable = NULL;
    int i, j, n;
    act_stats_t *stats;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
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
	stats = g_malloc0(n * sizeof(act_stats_t));
	
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
	    stats[i].inByts = *lipAccountTable[i]->actByts;
	    stats[i].inPkts = *lipAccountTable[i]->actPkts;
	    if (lipAccountTable[j]) {
		stats[i].outByts = *lipAccountTable[j]->actByts;
		stats[i].outPkts = *lipAccountTable[j]->actPkts;
	    }
	}

	qsort((void *) stats, (size_t) n, sizeof(act_stats_t), stats_sort);

	for (i = 0; i < n; i++) {
	    show_cisco_ip_accounting(interp->result, stats+i);
	}
	g_free(stats);
    }

    if (lipAccountTable)
	old_cisco_ip_mib_free_lipAccountingTable(lipAccountTable);

    return SCLI_OK;
}



static int
cmd_cisco_ip_accounting_snapshot(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lipCkAccountEntry_t **lipCkAccountTable = NULL;
    int i, j;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
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
	    show_cisco_ip_accounting_current(interp->result,
	     (old_cisco_ip_mib_lipAccountEntry_t *) lipCkAccountTable[i],
	     (old_cisco_ip_mib_lipAccountEntry_t *) (lipCkAccountTable[j] ?
				     lipCkAccountTable[j] : NULL));
	}
    }

    if (lipCkAccountTable)
	old_cisco_ip_mib_free_lipCkAccountingTable(lipCkAccountTable);

    return SCLI_OK;
}



static void
show_cisco_ip_accounting_info(GString *s,
			      old_cisco_ip_mib_lip_t *lip)
{
    if (lip->actThresh) {
	g_string_sprintfa(s, "Threshold:    %10d", *lip->actThresh);
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
cmd_cisco_ip_accounting_info(scli_interp_t *interp, int argc, char **argv)
{
    old_cisco_ip_mib_lip_t *lip;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    old_cisco_ip_mib_get_lip(interp->peer, &lip, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lip) {
	show_cisco_ip_accounting_info(interp->result, lip);
    }

    if (lip) old_cisco_ip_mib_free_lip(lip);

    return SCLI_OK;
}



void
scli_init_cisco_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	
	{ "show cisco ip accounting info", NULL,
	  "cisco IP accounting info",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_cisco_ip_accounting_info },

	{ "show cisco ip accounting current", NULL,
	  "cisco IP current accounting data",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_cisco_ip_accounting_current },

	{ "show cisco ip accounting snapshot", NULL,
	  "cisco IP snapshot accounting data",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_cisco_ip_accounting_snapshot },

	{ "monitor cisco ip accounting current", NULL,
	  "cisco IP current accounting data",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  cmd_cisco_ip_accounting_current },

	{ "monitor cisco ip accounting snapshot", NULL,
	  "cisco IP snapshot accounting data",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  cmd_cisco_ip_accounting_snapshot },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t cisco_mode = {
	"cisco",
	"scli mode to display and configure cisco parameters",
	cmds
    };

    scli_register_mode(interp, &cisco_mode);
}
