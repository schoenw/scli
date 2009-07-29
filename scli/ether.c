/* 
 * ether.c -- scli ether mode implementation
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

#include "snmpv2-tc.h"
#include "iana-mau-mib.h"
#include "mau-mib.h"
#include "etherlike-mib.h"
#include "rmon-mib.h" 



static guint32 const dot3MauTypeAUI[]
	= { IANA_MAU_MIB_DOT3MAUTYPEAUI };
static guint32 const dot3MauType10Base5[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASE5 };
static guint32 const dot3MauTypeFoirl[]
	= { IANA_MAU_MIB_DOT3MAUTYPEFOIRL };
static guint32 const dot3MauType10Base2[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASE2 };
static guint32 const dot3MauType10BaseT[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASET };
static guint32 const dot3MauType10BaseFP[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASEFP };
static guint32 const dot3MauType10BaseFB[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASEFB };
static guint32 const dot3MauType10BaseFL[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASEFL };
static guint32 const dot3MauType10Broad36[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BROAD36 };
static guint32 const dot3MauType10BaseTHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASETHD };
static guint32 const dot3MauType10BaseTFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASETFD };
static guint32 const dot3MauType10BaseFLHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASEFLHD };
static guint32 const dot3MauType10BaseFLFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE10BASEFLFD };
static guint32 const dot3MauType100BaseT4[]
	= { IANA_MAU_MIB_DOT3MAUTYPE100BASET4 };
static guint32 const dot3MauType100BaseTXHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE100BASETXHD };
static guint32 const dot3MauType100BaseTXFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE100BASETXFD };
static guint32 const dot3MauType100BaseFXHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE100BASEFXHD };
static guint32 const dot3MauType100BaseFXFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE100BASEFXFD };
static guint32 const dot3MauType100BaseT2HD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE100BASET2HD };
static guint32 const dot3MauType100BaseT2FD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE100BASET2FD };
static guint32 const dot3MauType1000BaseXHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASEXHD };
static guint32 const dot3MauType1000BaseXFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASEXFD };
static guint32 const dot3MauType1000BaseLXHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASELXHD };
static guint32 const dot3MauType1000BaseLXFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASELXFD };
static guint32 const dot3MauType1000BaseSXHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASESXHD };
static guint32 const dot3MauType1000BaseSXFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASESXFD };
static guint32 const dot3MauType1000BaseCXHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASECXHD };
static guint32 const dot3MauType1000BaseCXFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASECXFD };
static guint32 const dot3MauType1000BaseTHD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASETHD };
static guint32 const dot3MauType1000BaseTFD[]
	= { IANA_MAU_MIB_DOT3MAUTYPE1000BASETFD };

GNetSnmpIdentity const mau_type_identities[] = {
    { dot3MauTypeAUI,
      sizeof(dot3MauTypeAUI)/sizeof(guint32),
      "AUI" },
    { dot3MauType10Base5,
      sizeof(dot3MauType10Base5)/sizeof(guint32),
      "10Base5" },
    { dot3MauTypeFoirl,
      sizeof(dot3MauTypeFoirl)/sizeof(guint32),
      "Foirl" },
    { dot3MauType10Base2,
      sizeof(dot3MauType10Base2)/sizeof(guint32),
      "10Base2" },
    { dot3MauType10BaseT,
      sizeof(dot3MauType10BaseT)/sizeof(guint32),
      "10BaseT" },
    { dot3MauType10BaseFP,
      sizeof(dot3MauType10BaseFP)/sizeof(guint32),
      "10BaseFP" },
    { dot3MauType10BaseFB,
      sizeof(dot3MauType10BaseFB)/sizeof(guint32),
      "10BaseFB" },
    { dot3MauType10BaseFL,
      sizeof(dot3MauType10BaseFL)/sizeof(guint32),
      "10BaseFL" },
    { dot3MauType10Broad36,
      sizeof(dot3MauType10Broad36)/sizeof(guint32),
      "10Broad36" },
    { dot3MauType10BaseTHD,
      sizeof(dot3MauType10BaseTHD)/sizeof(guint32),
      "10BaseTHD" },
    { dot3MauType10BaseTFD,
      sizeof(dot3MauType10BaseTFD)/sizeof(guint32),
      "10BaseTFD" },
    { dot3MauType10BaseFLHD,
      sizeof(dot3MauType10BaseFLHD)/sizeof(guint32),
      "10BaseFLHD" },
    { dot3MauType10BaseFLFD,
      sizeof(dot3MauType10BaseFLFD)/sizeof(guint32),
      "10BaseFLFD" },
    { dot3MauType100BaseT4,
      sizeof(dot3MauType100BaseT4)/sizeof(guint32),
      "100BaseT4" },
    { dot3MauType100BaseTXHD,
      sizeof(dot3MauType100BaseTXHD)/sizeof(guint32),
      "100BaseTXHD" },
    { dot3MauType100BaseTXFD,
      sizeof(dot3MauType100BaseTXFD)/sizeof(guint32),
      "100BaseTXFD" },
    { dot3MauType100BaseFXHD,
      sizeof(dot3MauType100BaseFXHD)/sizeof(guint32),
      "100BaseFXHD" },
    { dot3MauType100BaseFXFD,
      sizeof(dot3MauType100BaseFXFD)/sizeof(guint32),
      "100BaseFXFD" },
    { dot3MauType100BaseT2HD,
      sizeof(dot3MauType100BaseT2HD)/sizeof(guint32),
      "100BaseT2HD" },
    { dot3MauType100BaseT2FD,
      sizeof(dot3MauType100BaseT2FD)/sizeof(guint32),
      "100BaseT2FD" },
    { dot3MauType1000BaseXHD,
      sizeof(dot3MauType1000BaseXHD)/sizeof(guint32),
      "1000BaseXHD" },
    { dot3MauType1000BaseXFD,
      sizeof(dot3MauType1000BaseXFD)/sizeof(guint32),
      "1000BaseXFD" },
    { dot3MauType1000BaseLXHD,
      sizeof(dot3MauType1000BaseLXHD)/sizeof(guint32),
      "1000BaseLXHD" },
    { dot3MauType1000BaseLXFD,
      sizeof(dot3MauType1000BaseLXFD)/sizeof(guint32),
      "1000BaseLXFD" },
    { dot3MauType1000BaseSXHD,
      sizeof(dot3MauType1000BaseSXHD)/sizeof(guint32),
      "1000BaseSXHD" },
    { dot3MauType1000BaseSXFD,
      sizeof(dot3MauType1000BaseSXFD)/sizeof(guint32),
      "1000BaseSXFD" },
    { dot3MauType1000BaseCXHD,
      sizeof(dot3MauType1000BaseCXHD)/sizeof(guint32),
      "1000BaseCXHD" },
    { dot3MauType1000BaseCXFD,
      sizeof(dot3MauType1000BaseCXFD)/sizeof(guint32),
      "1000BaseCXFD" },
    { dot3MauType1000BaseTHD,
      sizeof(dot3MauType1000BaseTHD)/sizeof(guint32),
      "1000BaseTHD" },
    { dot3MauType1000BaseTFD,
      sizeof(dot3MauType1000BaseTFD)/sizeof(guint32),
      "1000BaseTFD" },
    { 0, 0, NULL }
};


static void
fmt_ether_mau_info(GString *s, mau_mib_ifMauEntry_t *ifMauEntry)
{
    const char *e;
    
    g_string_sprintfa(s, "%7u ", ifMauEntry->ifMauIfIndex);
    g_string_sprintfa(s, "%7u ", ifMauEntry->ifMauIndex);

    e = fmt_enum(mau_mib_enums_ifMauStatus,
		 ifMauEntry->ifMauStatus);
    g_string_sprintfa(s, "%-12s", e ? e : "");

    e = fmt_enum(iana_mau_mib_enums_IANAifMauMediaAvailable,
		 ifMauEntry->ifMauMediaAvailable);
    g_string_sprintfa(s, "%-14s", e ? e : "");

    e = fmt_enum(mau_mib_enums_ifMauJabberState,
		 ifMauEntry->ifMauJabberState);
    g_string_sprintfa(s, "%-9s", e ? e : "");

    e = fmt_enum(snmpv2_tc_enums_TruthValue,
		 ifMauEntry->ifMauAutoNegSupported);
    g_string_sprintfa(s, "%-7s", e ? e : "");

    e = fmt_identity(mau_type_identities,
		     ifMauEntry->ifMauType, ifMauEntry->_ifMauTypeLength);
    if (e) {
	g_string_sprintfa(s, " %s", e);
    }

    /* ifMauEntry->ifMauTypeListBits */

    /* foreach jack on this mau:
       ifJackEntry->ifJackType */

    /* auto negotiation information:
       ifMauAutoNegEntry->ifMauAutoNegAdminStatus
       ifMauAutoNegEntry->ifMauAutoNegRemoteSignaling
       ifMauAutoNegEntry->ifMauAutoNegConfig
       ifMauAutoNegEntry->ifMauAutoNegCapabilityBits
       ifMauAutoNegEntry->ifMauAutoNegCapAdvertisedBits
       ifMauAutoNegEntry->ifMauAutoNegCapReceivedBits
       ifMauAutoNegEntry->ifMauAutoNegRemoteFaultAdvertised
       ifMauAutoNegEntry->ifMauAutoNegRemoteFaultReceived
     */

    g_string_append(s, "\n");
}



static int
show_ether_mau_info(scli_interp_t *interp, int argc, char **argv)
{
    mau_mib_ifMauEntry_t **ifMauTable = NULL;
    mau_mib_ifJackEntry_t **ifJackTable = NULL;
    int i;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    mau_mib_get_ifMauTable(interp->peer, &ifMauTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (ifMauTable) {
	mau_mib_get_ifJackTable(interp->peer, &ifJackTable, 0, NULL);
	g_string_sprintfa(interp->header,
		  "INTERFACE   MAU STATUS      MEDIA         JABBER   AUTONEG TYPE");
	for (i = 0; ifMauTable[i]; i++) {
	    fmt_ether_mau_info(interp->result, ifMauTable[i]);
	}
    }

    if (ifJackTable) mau_mib_free_ifJackTable(ifJackTable);
    if (ifMauTable) mau_mib_free_ifMauTable(ifMauTable);
    
    return SCLI_OK;
}



typedef struct {
    /* input errors */
    guint32 alignmentErrors;
    guint32 fcsErrors;
    guint32 macRecvErrors;
    guint32 frameTooLongs;
    /* output errors */
    guint32 deferredTransmissions;
    guint32 singleCollisionFrames;
    guint32 multipleCollisionFrames;
    guint32 excessiveCollisions;
    guint32 lateCollisions;
    guint32 macSendErrors;
    guint32 carrierSenseErrors;
} ether_stats_t;


static int
show_ether_stats(scli_interp_t *interp, int argc, char **argv)
{
    etherlike_mib_dot3StatsEntry_t **dot3StatsTable = NULL;
    static struct timeval last, now;
    double delta;
    int i;
    static ether_stats_t *stats = NULL;
    static time_t epoch = 0;
    GError *error = NULL;

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    etherlike_mib_get_dot3StatsTable(interp->peer, &dot3StatsTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (epoch < interp->epoch) {
	if (stats) g_free(stats);
	stats = NULL;
	last.tv_sec = last.tv_usec = 0;
    }

    if (! stats && dot3StatsTable) {
	for (i = 0; dot3StatsTable[i]; i++) ;
	stats = g_new0(ether_stats_t, i);
    }

    epoch = time(NULL);
    gettimeofday(&now, NULL);
    delta = TV_DIFF(last, now);

    if (dot3StatsTable) {
	g_string_append(interp->header,
			"INTERFACE | ALIGN   FCS   RCV  LONG | "
			"DEFER  SCOL  MCOL  XCOL  LCOL  XMIT  CARR");
	for (i = 0; dot3StatsTable[i]; i++) {
	    GString *s = interp->result;

	    g_string_sprintfa(s, "%9u |",
			      dot3StatsTable[i]->dot3StatsIndex);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsAlignmentErrors,
			   &(stats[i].alignmentErrors), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsFCSErrors,
			   &(stats[i].fcsErrors), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsInternalMacReceiveErrors,
			   &(stats[i].macRecvErrors), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsFrameTooLongs,
			   &(stats[i].frameTooLongs), &last, delta);
	    
	    g_string_append(s, " |");
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsDeferredTransmissions,
			   &(stats[i].deferredTransmissions), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsSingleCollisionFrames,
			   &(stats[i].singleCollisionFrames), &last, delta);

	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsMultipleCollisionFrames,
			   &(stats[i].multipleCollisionFrames), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsExcessiveCollisions,
			   &(stats[i].excessiveCollisions), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsLateCollisions,
			   &(stats[i].lateCollisions), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsInternalMacTransmitErrors,
			   &(stats[i].macSendErrors), &last, delta);
	    
	    fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsCarrierSenseErrors,
			   &(stats[i].carrierSenseErrors), &last, delta);
	    
	    g_string_append(s, "\n");
	}
    }

    last = now;
    if (dot3StatsTable) etherlike_mib_free_dot3StatsTable(dot3StatsTable);

    return SCLI_OK;
}



static void
fmt_ether_history(GString *s, rmon_mib_historyControlEntry_t *ctrlEntry)
{
    g_string_sprintfa(s, "%9u |",
		      ctrlEntry->historyControlIndex);
    
    g_string_sprintfa(s, " (%.*s)",
		      ctrlEntry->_historyControlOwnerLength,
		      ctrlEntry->historyControlOwner);
    
    g_string_append(s, "\n");
}



static int
show_ether_history(scli_interp_t *interp, int argc, char **argv)
{
    rmon_mib_historyControlEntry_t **ctrlTable = NULL;
    int i;
    GError *error = NULL;

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rmon_mib_get_historyControlTable(interp->peer, &ctrlTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (ctrlTable) {
	g_string_append(interp->header,
			"INTERFACE | ALIGN   FCS   RCV  LONG | "
			"DEFER  SCOL  MCOL  XCOL  LCOL  XMIT  CARR");
	for (i = 0; ctrlTable[i]; i++) {
	    fmt_ether_history(interp->result, ctrlTable[i]);
	}
    }

    if (ctrlTable) rmon_mib_free_historyControlTable(ctrlTable);

    return SCLI_OK;
}



void
scli_init_ether_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show ethernet mau", NULL,
	  "The `show ethernet mau' command displays information about the\n"
	  "medium attachment units (MAUs) for each ethernet port. The\n"
	  "command generates a table which has the following columns:\n"
	  "\n"
	  "  INTERFACE network interface number\n"
	  "  MAU       medium attachment unit number per interface\n"
	  "  STATUS    status of the medium attachment unit\n"
	  "  MEDIA     media availability\n"
	  "  JABBER    jabber state of the medium attachment unit\n"
	  "  AUTONEG   autonegation capabilities\n"
	  "  TYPE      type of the medium attachment unit",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_ether_mau_info },

	{ "show ethernet stats", NULL,
	  "The `show ethernet stats' command displays ethernet specific\n"
	  "statistics for each ethernet interface. The command outputs\n"
	  "a table which has the following columns:\n"
	  "\n"
          "  INTERFACE network interface number\n"
          "  ALIGN     alignement errors per second\n"
          "  FCS       frame check sequence errors per second\n"
          "  RCV       MAC receive errors per second\n"
          "  LONG      frames exceeding maximum frame size per second\n"
          "  DEFER     deferred transmission per second\n"
          "  SCOL      single collisions per second\n"
          "  MCOLR     multiple collisions per second\n"
          "  XCOL      excessive collisions per second\n"
          "  LCOL      late collisions per second\n"
          "  XMIT      MAC transmit errors per second\n"
          "  CARR      carrier sense errors per second",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_ether_stats },

	{ "show ethernet history", NULL,
	  "...",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_ether_history },

	{ "monitor ethernet stats", NULL,
	  "The `monitor ethernet stats' command shows the same information\n"
	  "as the show ethernet stats command. The information is updated\n"
	  "periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_ether_stats },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t ether_mode = {
	"ethernet",
	"The ethernet scli mode is based on the EtherLike-MIB as published\n"
	"in RFC 2665 and the MAU-MIB as published in RFC 2668.",
	cmds
    };
    
    scli_register_mode(interp, &ether_mode);
}
