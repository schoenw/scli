/* 
 * cisco.c -- scli cisco mode implementation
 *
 * Copyright (C) 2001 Juergen Schoenwaelder
 *           (C) 2005 Frank Strauss
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
#include "cisco-dot11-association-mib.h"
#include "inet-address-mib.h"
#include "if-mib.h"


#define IF_MIB_IFENTRY_PARAMS \
	( IF_MIB_IFDESCR | IF_MIB_IFSPEED | IF_MIB_IFPHYSADDRESS \
	  | IF_MIB_IFADMINSTATUS | IF_MIB_IFOPERSTATUS )

#define IF_MIB_IFXENTRY_PARAMS \
	( IF_MIB_IFNAME | IF_MIB_IFLINKUPDOWNTRAPENABLE | IF_MIB_IFHIGHSPEED \
	  | IF_MIB_IFPROMISCUOUSMODE | IF_MIB_IFCONNECTORPRESENT | IF_MIB_IFALIAS)


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



static if_mib_ifEntry_t *
get_ifEntry(if_mib_ifEntry_t **ifTable, gint32 ifIndex)
{
    int i;
    
    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (ifTable[i]->ifIndex == ifIndex) {
		return ifTable[i];
	    }
	}
    }
    return NULL;
}
    


static if_mib_ifXEntry_t *
get_ifXEntry(if_mib_ifXEntry_t **ifXTable, gint32 ifIndex)
{
    int i;

    if (ifXTable) {
	for (i = 0; ifXTable[i]; i++) {
	    if (ifXTable[i]->ifIndex == ifIndex) {
		return ifXTable[i];
	    }
	}
    }
    return NULL;
}



static cisco_dot11_association_mib_cDot11AssociationStatsEntry_t *
get_assStatsEntry(cisco_dot11_association_mib_cDot11AssociationStatsEntry_t **assStatsTable, gint32 ifIndex)
{
    int i;

    if (assStatsTable) {
	for (i = 0; assStatsTable[i]; i++) {
	    if (assStatsTable[i]->ifIndex == ifIndex) {
		return assStatsTable[i];
	    }
	}
    }
    return NULL;
}



static cisco_dot11_association_mib_cDot11ClientStatisticEntry_t *
get_client_statsEntry(cisco_dot11_association_mib_cDot11ClientStatisticEntry_t **statsTable, gint32 ifIndex, guint16 ssidLength, guchar *ssid, guchar *address)
{
    int i;

    if (statsTable) {
	for (i = 0; statsTable[i]; i++) {
	    if ((statsTable[i]->ifIndex == ifIndex) &&
		(statsTable[i]->_cd11IfAuxSsidLength == ssidLength) &&
		(!memcmp(statsTable[i]->cd11IfAuxSsid, ssid, ssidLength)) &&
		(!memcmp(statsTable[i]->cDot11ClientAddress, address, 6))) {
		return statsTable[i];
	    }
	}
    }
    return NULL;
}



static int
get_if_name_width(if_mib_ifXEntry_t **ifXTable)
{
    int i, name_width = 4;
    
    if (ifXTable) {
	for (i = 0; ifXTable[i]; i++) {
	    if (ifXTable[i]->_ifNameLength > name_width) {
		name_width = ifXTable[i]->_ifNameLength;
	    }
	}
    }
    return name_width;
}



static void
fmt_interface_info(GString *s,
	     cisco_dot11_association_mib_cDot11ActiveDevicesEntry_t *deviceEntry,
	     cisco_dot11_association_mib_cDot11AssociationStatsEntry_t *assStatsEntry,
	     if_mib_ifEntry_t *ifEntry,
	     if_mib_ifXEntry_t *ifXEntry,
	     int name_width)
{
    const char *e;
    
    g_string_sprintfa(s, "%5u ", deviceEntry->ifIndex);

    if (ifEntry->ifSpeed) {
	if (*(ifEntry->ifSpeed) == 0xffffffff
	    && ifXEntry && ifXEntry->ifHighSpeed) {
	    g_string_sprintfa(s, "%5s ",
			      fmt_gtp(*(ifXEntry->ifHighSpeed)));
	} else {
	    g_string_sprintfa(s, "%5s ",
			      fmt_kmg(*(ifEntry->ifSpeed)));
	}
    } else {
	g_string_append(s, "      ");
    }

    if (ifXEntry && ifXEntry->ifName) {
	g_string_sprintfa(s, "%-*.*s ", name_width,
			  (int) ifXEntry->_ifNameLength,
			  ifXEntry->ifName);
    } else {
	g_string_sprintfa(s, "%*s ", name_width, "");
    }

    if (deviceEntry->cDot11ActiveWirelessClients)
	g_string_sprintfa(s, "%4d ", *deviceEntry->cDot11ActiveWirelessClients);
    else
	g_string_append(s, "     ");
	
    if (deviceEntry->cDot11ActiveBridges)
	g_string_sprintfa(s, "%4d ", *deviceEntry->cDot11ActiveBridges);
    else
	g_string_append(s, "     ");
	
    if (deviceEntry->cDot11ActiveRepeaters)
	g_string_sprintfa(s, "%4d ", *deviceEntry->cDot11ActiveRepeaters);
    else
	g_string_append(s, "     ");
	
    if (assStatsEntry->cDot11AssStatsAssociated)
	g_string_sprintfa(s, "%5d ", *assStatsEntry->cDot11AssStatsAssociated);
    else
	g_string_append(s, "      ");
	
    if (assStatsEntry->cDot11AssStatsDisassociated)
	g_string_sprintfa(s, "%5d ", *assStatsEntry->cDot11AssStatsDisassociated);
    else
	g_string_append(s, "      ");
	
    if (assStatsEntry->cDot11AssStatsRoamedIn)
	g_string_sprintfa(s, "%5d ", *assStatsEntry->cDot11AssStatsRoamedIn);
    else
	g_string_append(s, "      ");
	
    if (assStatsEntry->cDot11AssStatsRoamedAway)
	g_string_sprintfa(s, "%5d ", *assStatsEntry->cDot11AssStatsRoamedAway);
    else
	g_string_append(s, "      ");
	
    if (assStatsEntry->cDot11AssStatsAuthenticated)
	g_string_sprintfa(s, "%5d ", *assStatsEntry->cDot11AssStatsAuthenticated);
    else
	g_string_append(s, "      ");
	
    if (assStatsEntry->cDot11AssStatsDeauthenticated)
	g_string_sprintfa(s, "%5d ", *assStatsEntry->cDot11AssStatsDeauthenticated);
    else
	g_string_append(s, "      ");
	
    g_string_append(s, "\n");
}



static int
show_cisco_dot11_interface_info(scli_interp_t *interp, int argc, char **argv)
{
    cisco_dot11_association_mib_cDot11ActiveDevicesEntry_t **deviceTable = NULL;
    cisco_dot11_association_mib_cDot11AssociationStatsEntry_t **assStatsTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int name_width;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    cisco_dot11_association_mib_get_cDot11ActiveDevicesTable(interp->peer,
					  &deviceTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (deviceTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, IF_MIB_IFENTRY_PARAMS);
	if_mib_get_ifXTable(interp->peer, &ifXTable, IF_MIB_IFXENTRY_PARAMS);
	cisco_dot11_association_mib_get_cDot11AssociationStatsTable(interp->peer, &assStatsTable, 0);
	name_width = get_if_name_width(ifXTable);
	g_string_sprintfa(interp->header,
			  "IFACE SPEED %-*s CLNT BRDG RPTR ASSCI ASSCO ROAMI ROAMO AUTHI AUTHO",
			  name_width, "NAME");
	for (i = 0; deviceTable[i]; i++) {
	    if_mib_ifEntry_t *ifEntry;
	    if_mib_ifXEntry_t *ifXEntry;
	    cisco_dot11_association_mib_cDot11AssociationStatsEntry_t *assStatsEntry;
	    ifEntry = get_ifEntry(ifTable, deviceTable[i]->ifIndex);
	    ifXEntry = get_ifXEntry(ifXTable, deviceTable[i]->ifIndex);
	    assStatsEntry = get_assStatsEntry(assStatsTable, deviceTable[i]->ifIndex);
	    fmt_interface_info(interp->result, deviceTable[i], assStatsEntry,
			       ifEntry, ifXEntry, name_width);
	}
	
    }

    if (deviceTable) cisco_dot11_association_mib_free_cDot11ActiveDevicesTable(deviceTable);
    if (assStatsTable) cisco_dot11_association_mib_free_cDot11AssociationStatsTable(assStatsTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
	
    return SCLI_OK;
}



static int
get_client_ssid_width(cisco_dot11_association_mib_cDot11ClientConfigInfoEntry_t **configTable)
{
    int i, width = 4;
    
    if (configTable) {
	for (i = 0; configTable[i]; i++) {
	    if (configTable[i]->_cd11IfAuxSsidLength > width) {
		width = configTable[i]->_cd11IfAuxSsidLength;
	    }
	}
    }
    return width;
}



static void
fmt_client_info(GString *s,
		cisco_dot11_association_mib_cDot11ClientConfigInfoEntry_t *configEntry,
		cisco_dot11_association_mib_cDot11ClientStatisticEntry_t *statsEntry,
		int ssid_width)
{
    const char *e;
    
    g_string_sprintfa(s, "%2u ", configEntry->ifIndex);

    if (configEntry && configEntry->cd11IfAuxSsid) {
	g_string_sprintfa(s, "%-*.*s ", ssid_width,
			  (int) configEntry->_cd11IfAuxSsidLength,
			  configEntry->cd11IfAuxSsid);
    } else {
	g_string_sprintfa(s, "%*s ", ssid_width, "");
    }

    if (configEntry && configEntry->cDot11ClientAddress) {
	g_string_sprintfa(s, "%s ",
			  fmt_ether_address(configEntry->cDot11ClientAddress,
					    SCLI_FMT_ADDR));
    } else {
	g_string_append(s, "                  ");
    }
	
    if (configEntry && configEntry->cDot11ClientIpAddressType &&
	configEntry->cDot11ClientIpAddress &&
	(*configEntry->cDot11ClientIpAddressType == INET_ADDRESS_MIB_INETADDRESSTYPE_IPV4)) {
	// XXX: support other inet address types
	g_string_sprintfa(s, "%-15s ",
			  fmt_ipv4_address(configEntry->cDot11ClientIpAddress,
					   SCLI_FMT_ADDR));
    } else {
	g_string_append(s, "                ");
    }
	
    if (statsEntry && statsEntry->cDot11ClientSignalStrength) {
	g_string_sprintfa(s, "%4d ", *statsEntry->cDot11ClientSignalStrength);
    } else {
	g_string_append(s, "     ");
    }
	
    if (statsEntry && statsEntry->cDot11ClientUpTime) {
	g_string_sprintfa(s, "%s",
			  fmt_seconds(*statsEntry->cDot11ClientUpTime));
    } else {
	g_string_append(s, "          ");
    }
}



typedef struct {
    guint32 inOctets;
    guint32 outOctets;
    guint32 errors;
} client_stats_t;



static int
show_cisco_dot11_clients_stats(scli_interp_t *interp, int argc, char **argv)
{
    cisco_dot11_association_mib_cDot11ClientConfigInfoEntry_t **configTable = NULL;
    cisco_dot11_association_mib_cDot11ClientStatisticEntry_t **statsTable = NULL;
    int ssid_width;
    int i;
    static struct timeval last, now;
    double delta;
    static client_stats_t *stats = NULL;
    static time_t epoch = 0;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    cisco_dot11_association_mib_get_cDot11ClientConfigInfoTable(interp->peer,
					  &configTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (epoch < interp->epoch) {
	if (stats) g_free(stats);
	stats = NULL;
	last.tv_sec = last.tv_usec = 0;
    }

    if (! stats && configTable) {
	for (i = 0; configTable[i]; i++) ;
	stats = g_new0(client_stats_t, i);
    }

    epoch = time(NULL);
    gettimeofday(&now, NULL);
    delta = TV_DIFF(last, now);

    if (configTable) {
	cisco_dot11_association_mib_get_cDot11ClientStatisticTable(interp->peer, &statsTable, 0);
	ssid_width = get_client_ssid_width(configTable);
	g_string_sprintfa(interp->header,
			  "IF %-*s ADDRESS           IPv4-ADDRESS    SGNL     UPTIME I-BPS O-BPS   ERR",
			  ssid_width, "SSID");
	for (i = 0; configTable[i]; i++) {
	    cisco_dot11_association_mib_cDot11ClientStatisticEntry_t *statsEntry;
	    statsEntry = get_client_statsEntry(statsTable,
					       configTable[i]->ifIndex,
					       configTable[i]->_cd11IfAuxSsidLength,
					       configTable[i]->cd11IfAuxSsid,
					       configTable[i]->cDot11ClientAddress);
	    fmt_client_info(interp->result, configTable[i], statsEntry,
			    ssid_width);

	    fmt_counter_dt(interp->result,
			   statsEntry->cDot11ClientBytesReceived,
			   &(stats[i].inOctets), &last, delta);

	    fmt_counter_dt(interp->result,
			   statsEntry->cDot11ClientBytesSent,
			   &(stats[i].outOctets), &last, delta);

	    if (statsEntry->cDot11ClientDuplicates &&
		statsEntry->cDot11ClientMsduRetries &&
		statsEntry->cDot11ClientMsduFails &&
		statsEntry->cDot11ClientWepErrors &&
		statsEntry->cDot11ClientMicErrors &&
		statsEntry->cDot11ClientMicMissingFrames &&
		delta > TV_DELTA) {
		guint32 err = *statsEntry->cDot11ClientDuplicates +
		    *statsEntry->cDot11ClientMsduRetries +
		    *statsEntry->cDot11ClientMsduFails +
		    *statsEntry->cDot11ClientWepErrors +
		    *statsEntry->cDot11ClientMicErrors +
		    *statsEntry->cDot11ClientMicMissingFrames;
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (err - stats[i].errors) / delta;
		    g_string_sprintfa(interp->result, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(interp->result, "  ----");
		}
		stats[i].errors = err;
	    } else {
		g_string_sprintfa(interp->result, "  ----");
	    }
		    
	    g_string_append(interp->result, "\n");
	}
	
    }

    last = now;
    if (configTable) cisco_dot11_association_mib_free_cDot11ClientConfigInfoTable(configTable);
    if (statsTable) cisco_dot11_association_mib_free_cDot11ClientStatisticTable(statsTable);
	
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

	{ "show cisco dot11 interface info", NULL,
	  "The `show cisco dot11 interface info' command displays information\n"
	  "about all IEEE 802.11 interfaces on a CISCO device. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  IFACE  network interface number\n"
	  "  SPEED  speed in bits per second\n"
	  "  NAME   name of the network interface\n"
	  "  CLNT   number of associated clients\n"
	  "  BRDG   number of assiciated bridges\n"
	  "  RPRT   number of assiciated repeaters\n"
	  "  ASSCI  total number of associated stations\n"
	  "  ASSCO  total number of deassociated stations\n"
	  "  ROAMI  total number of roamed-in stations\n"
	  "  ROAMO  total number of roamed-away stations\n"
	  "  AUTHI  total number of authenticated stations\n"
	  "  AUTHO  total number of deauthenticated stations",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_dot11_interface_info },

	{ "show cisco dot11 clients stats", NULL,
	  "The `show cisco dot11 clients stats' command displays information\n"
	  "about all IEEE 802.11 clients associated with a CISCO device. The\n"
	  "command generates a table with the following columns:\n"
	  "\n"
	  "  IF      	   network interface number\n"
	  "  SSID    	   SSID to which client is associated\n"
	  "  ADDRESS 	   client MAC address\n"
	  "  IPv4-ADDRESS  client's IPv4 address (if supplied)\n"
	  "  SGNL          client's signal strength\n"
	  "  UPTIME        lifetime of client's association\n"
	  "  I-BPS         input bytes per second\n"
	  "  O-BPS         output bytes per second\n"
	  "  ERR           errors per second",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_dot11_clients_stats },

	{ "monitor cisco dot11 clients stats", NULL,
	  "The `monitor cisco dot11 clients stats' command shows the same\n"
	  "information as the show cisco dot11 clients stats command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_cisco_dot11_clients_stats },

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
