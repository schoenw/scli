/* 
 * bridge.c -- scli bridge mode implementation
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

#include "bridge-mib.h"
#include "if-mib.h"


static GSnmpEnum const dot1dBaseType[] = {
    { BRIDGE_MIB_DOT1DBASETYPE_UNKNOWN,	"unknown" },
    { BRIDGE_MIB_DOT1DBASETYPE_TRANSPARENT_ONLY,	"transparent (TP)" },
    { BRIDGE_MIB_DOT1DBASETYPE_SOURCEROUTE_ONLY,	"source route (SR)" },
    { BRIDGE_MIB_DOT1DBASETYPE_SRT,	"source route transparent (SRT)" },
    { 0, NULL }
};


GSnmpEnum const dot1dStpProtocolSpecification[] = {
    { BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_UNKNOWN,	"unknown" },
    { BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_DECLB100,	"DEC LANbridge 100 Spanning Tree Protocol" },
    { BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_IEEE8021D,	"IEEE 802.1d Spanning Tree Protocol" },
    { 0, NULL }
};


char *
fmt_bridgeid(guchar *addr)
{
    static char buffer[256];

    g_snprintf(buffer, sizeof(buffer),
	       "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
	       addr[0], addr[1], addr[2], addr[3],
	       addr[4], addr[5], addr[6], addr[7]);
    return buffer;
}



static void
fmt_bridge_stp_info(GString *s, bridge_mib_dot1dStp_t *dot1dStp)
{
    int const indent = 18;
    const char *e;

    if (dot1dStp->dot1dStpProtocolSpecification) {
	e = fmt_enum(dot1dStpProtocolSpecification,
		     dot1dStp->dot1dStpProtocolSpecification);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Stp Type:", e);
	}
    }
    
    if (dot1dStp->dot1dStpPriority) {
	g_string_sprintfa(s, "%-*s%d (%02x:%02x)\n", indent,
			      "Stp Priority:",
			  *dot1dStp->dot1dStpPriority,
			  (*dot1dStp->dot1dStpPriority >> 8) & 0xff,
			  (*dot1dStp->dot1dStpPriority) & 0xff);
    }
    
    if (dot1dStp->dot1dStpDesignatedRoot) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Stp Root:",
			  fmt_bridgeid(dot1dStp->dot1dStpDesignatedRoot));
    }

    if (dot1dStp->dot1dStpRootCost) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Stp Root Cost:",
			  *dot1dStp->dot1dStpRootCost);
    }

    if (dot1dStp->dot1dStpRootPort) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Stp Root Port:",
			  *dot1dStp->dot1dStpRootPort);
    }

    if (dot1dStp->dot1dStpMaxAge) {
	g_string_sprintfa(s, "%-*s%d seconds\n", indent, "Stp Aging Time:",
			  *dot1dStp->dot1dStpMaxAge);
    }
    
}



static void
fmt_bridge_info(GString *s,
		bridge_mib_dot1dBase_t *dot1dBase,
		bridge_mib_dot1dTp_t *dot1dTp,
		bridge_mib_dot1dStp_t *dot1dStp)
{
    int const indent = 18;
    const char *e;

    if (dot1dBase->dot1dBaseBridgeAddress) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Address:",
			  fmt_ether_address(dot1dBase->dot1dBaseBridgeAddress,
					    SCLI_FMT_ADDR));
	e = fmt_ether_address(dot1dBase->dot1dBaseBridgeAddress,
			      SCLI_FMT_NAME);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Name:", e);
	}
    }

    if (dot1dBase->dot1dBaseNumPorts) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Ports:",
			  *(dot1dBase->dot1dBaseNumPorts));
    }
	
    if (dot1dBase->dot1dBaseType) {
	e = fmt_enum(dot1dBaseType, dot1dBase->dot1dBaseType);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Type:", e);
	}
	if (dot1dBase->dot1dBaseType
	    && (*dot1dBase->dot1dBaseType == BRIDGE_MIB_DOT1DBASETYPE_TRANSPARENT_ONLY
		|| *dot1dBase->dot1dBaseType == BRIDGE_MIB_DOT1DBASETYPE_SRT)
	    && dot1dTp
		&& dot1dTp->dot1dTpAgingTime) {
		g_string_sprintfa(s, "%-*s%d seconds\n", indent, "Tp Aging Time:",
				  *dot1dTp->dot1dTpAgingTime);
	    }
	    if (dot1dStp && dot1dStp->dot1dStpMaxAge) {
		g_string_sprintfa(s, "%-*s %d seconds\n", indent, "Stp Aging Time:",
				  *dot1dStp->dot1dStpMaxAge);
	    }
	}
    }

    if (dot1dStp) {
	fmt_bridge_stp_info(s, dot1dStp);
    }
}



static int
show_bridge_info(scli_interp_t *interp, int argc, char **argv)
{
    bridge_mib_dot1dBase_t *dot1dBase = NULL;
    bridge_mib_dot1dTp_t *dot1dTp = NULL;
    bridge_mib_dot1dStp_t *dot1dStp = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    bridge_mib_get_dot1dBase(interp->peer, &dot1dBase, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    bridge_mib_get_dot1dTp(interp->peer, &dot1dTp, 0);
    bridge_mib_get_dot1dStp(interp->peer, &dot1dStp, 0);
    
    if (dot1dBase
	&& dot1dBase->dot1dBaseNumPorts
	&& *dot1dBase->dot1dBaseNumPorts) {
	fmt_bridge_info(interp->result, dot1dBase, dot1dTp, dot1dStp);
    }

    if (dot1dBase)
	bridge_mib_free_dot1dBase(dot1dBase);
    if (dot1dTp)
	bridge_mib_free_dot1dTp(dot1dTp);
    if (dot1dStp)
	bridge_mib_free_dot1dStp(dot1dStp);
    
    return SCLI_OK;
}



static void
fmt_bridge_port(GString *s,
		bridge_mib_dot1dBasePortEntry_t *dot1dBasePortEntry,
		if_mib_ifEntry_t *ifEntry,
		if_mib_ifXEntry_t *ifXEntry,
		int type_width, int name_width)
{
    g_string_sprintfa(s, "%5u ", dot1dBasePortEntry->dot1dBasePort);
    if (dot1dBasePortEntry->dot1dBasePortIfIndex) {
	g_string_sprintfa(s, "%9u ",
			  *dot1dBasePortEntry->dot1dBasePortIfIndex);
    } else {
	g_string_sprintfa(s, "%9s ", "");
    }
    if (ifEntry) {
	const char *type;
	type = fmt_enum(if_mib_enums_ifType, ifEntry->ifType);
	g_string_sprintfa(s, "%-*s", type_width, type ? type : "");
	if (ifEntry->ifSpeed) {
	    if (*(ifEntry->ifSpeed) == 0xffffffff
		&& ifXEntry && ifXEntry->ifHighSpeed) {
		g_string_sprintfa(s, "  %4s ",
				  fmt_gtp(*(ifXEntry->ifHighSpeed)));
	    } else {
		g_string_sprintfa(s, "  %4s ",
				  fmt_kmg(*(ifEntry->ifSpeed)));
	    }
	} else {
	    g_string_append(s, "       ");
	}
	
	if (ifXEntry && ifXEntry->ifName) {
	    g_string_sprintfa(s, "%-*.*s ", name_width,
			      (int) ifXEntry->_ifNameLength,
			      ifXEntry->ifName);
	} else {
	    g_string_sprintfa(s, "%*s ", name_width, "");
	}
	
	if (ifEntry->ifDescr) {
	    g_string_sprintfa(s, "%.*s",
			      (int) ifEntry->_ifDescrLength,
			      ifEntry->ifDescr);
	}
    }
    g_string_append(s, "\n");
}



static int
show_bridge_ports(scli_interp_t *interp, int argc, char **argv)
{
    bridge_mib_dot1dBasePortEntry_t **dot1dBasePortTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int type_width = 6;
    int name_width = 6;
    int i, j = -1;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    bridge_mib_get_dot1dBasePortTable(interp->peer, &dot1dBasePortTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    if_mib_get_ifTable(interp->peer, &ifTable, 0);
    if_mib_get_ifXTable(interp->peer, &ifXTable, 0);
    
    if (dot1dBasePortTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (ifXTable && ifXTable[i]) {
		if (ifXTable[i]->_ifNameLength > name_width) {
		    name_width = ifXTable[i]->_ifNameLength;
		}
	    }
	    if (ifTable[i]->ifType) {
		char const *label;
		label = gsnmp_enum_get_label(if_mib_enums_ifType,
					     *ifTable[i]->ifType);
		if (label && strlen(label) > type_width) {
		    type_width = strlen(label);
		}
	    }
	}
	g_string_sprintfa(interp->header,
			  " PORT INTERFACE %-*s SPEED %-*s DESCRIPTION",
			  type_width, "TYPE",
			  name_width, "NAME");
	for (i = 0; dot1dBasePortTable[i]; i++) {
	    if (ifTable && dot1dBasePortTable[i]->dot1dBasePortIfIndex) {
		for (j = 0; ifTable[j]; j++) {
		    if (ifTable[j]->ifIndex ==
			*dot1dBasePortTable[i]->dot1dBasePortIfIndex) {
			break;
		    }
		}
	    }
	    fmt_bridge_port(interp->result, dot1dBasePortTable[i],
			    (ifTable && ifTable[j]) ? ifTable[j] : NULL,
			    (ifXTable && ifXTable[j]) ? ifXTable[j] : NULL,
			    type_width, name_width);
	}
    }

    if (dot1dBasePortTable)
	bridge_mib_free_dot1dBasePortTable(dot1dBasePortTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    return SCLI_OK;
}



static void
fmt_bridge_stp_port(GString *s,
		    bridge_mib_dot1dStpPortEntry_t *dot1dStpPortEntry)
{
    const char *e;
    
    g_string_sprintfa(s, "%5u ", dot1dStpPortEntry->dot1dStpPort);

    if (dot1dStpPortEntry->dot1dStpPortPriority) {
	g_string_sprintfa(s, "%5u ", *dot1dStpPortEntry->dot1dStpPortPriority);
    }

    e = fmt_enum(bridge_mib_enums_dot1dStpPortState,
		 dot1dStpPortEntry->dot1dStpPortState);
    g_string_sprintfa(s, " %s ", e ? e : "");

    e = fmt_enum(bridge_mib_enums_dot1dStpPortEnable,
		 dot1dStpPortEntry->dot1dStpPortEnable);
    g_string_sprintfa(s, " %s ", e ? e : "");

    if (dot1dStpPortEntry->dot1dStpPortPathCost) {
	g_string_sprintfa(s, "%5u ", *dot1dStpPortEntry->dot1dStpPortPathCost);
    }

    if (dot1dStpPortEntry->dot1dStpPortDesignatedRoot) {
	g_string_sprintfa(s, " %s ",
		  fmt_bridgeid(dot1dStpPortEntry->dot1dStpPortDesignatedRoot));
    }

    if (dot1dStpPortEntry->dot1dStpPortDesignatedCost) {
	g_string_sprintfa(s, "%5u ", *dot1dStpPortEntry->dot1dStpPortDesignatedCost);
    }
    
    if (dot1dStpPortEntry->dot1dStpPortDesignatedBridge) {
	g_string_sprintfa(s, " %s ",
		  fmt_bridgeid(dot1dStpPortEntry->dot1dStpPortDesignatedBridge));
    }

    if (dot1dStpPortEntry->dot1dStpPortDesignatedPort) {
	g_string_sprintfa(s, "%5u ", *dot1dStpPortEntry->dot1dStpPortDesignatedPort);
    }

    g_string_append(s, "\n");
}



static int
show_bridge_stp_ports(scli_interp_t *interp, int argc, char **argv)
{
    bridge_mib_dot1dStpPortEntry_t **dot1dStpPortTable = NULL;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (bridge_mib_get_dot1dStpPortTable(interp->peer, &dot1dStpPortTable)) {
	return SCLI_ERROR;
    }

    if (dot1dStpPortTable) {
	g_string_sprintfa(interp->header,
			  " PORT PRIO STATE STATUS P-COST D-ROOT D-COST D-BRIDGE D-PORT");
	for (i = 0; dot1dStpPortTable[i]; i++) {
	    fmt_bridge_stp_port(interp->result, dot1dStpPortTable[i]);
	}
    }

    if (dot1dStpPortTable)
	bridge_mib_free_dot1dStpPortTable(dot1dStpPortTable);

    return SCLI_OK;
}



static void
fmt_bridge_forwarding(GString *s,
		      bridge_mib_dot1dTpFdbEntry_t *dot1dTpFdbEntry,
		      int name_width)
{
    scli_vendor_t *vendor;
    guint32 prefix;
    char *name;
    const char *status;

    if (dot1dTpFdbEntry->dot1dTpFdbPort) {
	g_string_sprintfa(s, "%5u ", *dot1dTpFdbEntry->dot1dTpFdbPort);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }
    status = fmt_enum(bridge_mib_enums_dot1dTpFdbStatus,
	     dot1dTpFdbEntry->dot1dTpFdbStatus);
    g_string_sprintfa(s, "%-*s ", 8, status ? status : "");
    if (dot1dTpFdbEntry->dot1dTpFdbAddress) {
	g_string_sprintfa(s, "%s",
		  fmt_ether_address(dot1dTpFdbEntry->dot1dTpFdbAddress,
				    SCLI_FMT_ADDR));
	name = fmt_ether_address(dot1dTpFdbEntry->dot1dTpFdbAddress,
				 SCLI_FMT_NAME);
	g_string_sprintfa(s, " %-*s", name_width, name ? name : "");
	prefix = dot1dTpFdbEntry->dot1dTpFdbAddress[0] * 65536
	    + dot1dTpFdbEntry->dot1dTpFdbAddress[1] * 256
	    + dot1dTpFdbEntry->dot1dTpFdbAddress[2];
	vendor = scli_get_ieee_vendor(prefix);
	if (vendor && vendor->name) {
	    g_string_sprintfa(s, " %s", vendor->name);
	}
    }
    g_string_append(s, "\n");
}



static int
show_bridge_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    bridge_mib_dot1dTpFdbEntry_t **dot1dTpFdbTable = NULL;
    char *name;
    int i, p, max = 0;
    int name_width = 8;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    bridge_mib_get_dot1dTpFdbTable(interp->peer, &dot1dTpFdbTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (dot1dTpFdbTable) {
	for (i = 0; dot1dTpFdbTable[i]; i++) {
	    if (dot1dTpFdbTable[i]->dot1dTpFdbPort
		&& *dot1dTpFdbTable[i]->dot1dTpFdbPort > max) {
		max = *dot1dTpFdbTable[i]->dot1dTpFdbPort;
	    }
	    if (dot1dTpFdbTable[i]->dot1dTpFdbAddress) {
		name = fmt_ether_address(dot1dTpFdbTable[i]->dot1dTpFdbAddress,
					 SCLI_FMT_NAME);
		if (name && strlen(name) > name_width) {
		    name_width = strlen(name);
		}
	    }
	};
	g_string_sprintfa(interp->header,
			  " PORT STATUS   ADDRESS           %-*s VENDOR",
			  name_width, "NAME");
	for (p = 0; p < max+1; p++) {
	    for (i = 0; dot1dTpFdbTable[i]; i++) {
		if (dot1dTpFdbTable[i]->dot1dTpFdbPort
		    && *dot1dTpFdbTable[i]->dot1dTpFdbPort == p) {
		    fmt_bridge_forwarding(interp->result, dot1dTpFdbTable[i],
					  name_width);
		}
	    }
	}
    }

    if (dot1dTpFdbTable) bridge_mib_free_dot1dTpFdbTable(dot1dTpFdbTable);

    return SCLI_OK;
}



static void
fmt_bridge_filter(GString *s,
		   bridge_mib_dot1dStaticEntry_t *dot1dStaticEntry)
{
    const char *status;
    
    if (dot1dStaticEntry->dot1dStaticReceivePort) {
	g_string_sprintfa(s, "%5d ",
			  dot1dStaticEntry->dot1dStaticReceivePort);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }

    if (dot1dStaticEntry->dot1dStaticAddress) {
	char *addr = fmt_ether_address(dot1dStaticEntry->dot1dStaticAddress,
				       SCLI_FMT_ADDR);
	g_string_append(s, addr);
    } else {
	g_string_sprintfa(s, "--:--:--:--:--:--");
    }

    if (dot1dStaticEntry->dot1dStaticAllowedToGoTo) {
	/* xxx */
    }

    status = fmt_enum(bridge_mib_enums_dot1dStaticStatus,
		      dot1dStaticEntry->dot1dStaticStatus);
    if (status) {
	g_string_sprintfa(s, " %s", status);
    }
    
    g_string_append(s, "\n");
}



static int
show_bridge_filter(scli_interp_t *interp, int argc, char **argv)
{
    bridge_mib_dot1dStaticEntry_t **dot1dStaticTable = NULL;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    bridge_mib_get_dot1dStaticTable(interp->peer, &dot1dStaticTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (dot1dStaticTable) {
	for (i = 0; dot1dStaticTable[i]; i++) {
	    fmt_bridge_filter(interp->result, dot1dStaticTable[i]);
	}
    }

    if (dot1dStaticTable)
	bridge_mib_free_dot1dStaticTable(dot1dStaticTable);

    return SCLI_OK;
}



typedef struct {
    guint32 inFrames;
    guint32 outFrames;
    guint32 inDiscards;
} bridge_stats_t;



static int
show_bridge_stats(scli_interp_t *interp, int argc, char **argv)
{
    bridge_mib_dot1dTpPortEntry_t **portTable = NULL;
    static struct timeval last, now;
    double delta;
    static bridge_stats_t *stats = NULL;
    static time_t epoch = 0;
    int i;
    
    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    bridge_mib_get_dot1dTpPortTable(interp->peer, &portTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (epoch < interp->epoch) {
	if (stats) g_free(stats);
	stats = NULL;
	last.tv_sec = last.tv_usec = 0;
    }

    if (! stats && portTable) {
	for (i = 0; portTable[i]; i++) ;
	stats = (bridge_stats_t *) g_malloc0(i * sizeof(bridge_stats_t));
    }

    epoch = time(NULL);
    gettimeofday(&now, NULL);
    delta = TV_DIFF(last, now);

    if (portTable) {
	g_string_append(interp->header, " PORT  I-FPS O-FPS D-FPS DESCRIPTION");
	for (i = 0; portTable[i]; i++) {

	    g_string_sprintfa(interp->result, "%5u ",
			      portTable[i]->dot1dTpPort);
	    
	    fmt_counter_dt(interp->result, portTable[i]->dot1dTpPortInFrames,
			   &(stats[i].inFrames),
			   &last, delta);

	    fmt_counter_dt(interp->result, portTable[i]->dot1dTpPortOutFrames,
			   &(stats[i].outFrames),
			   &last, delta);

	    fmt_counter_dt(interp->result, portTable[i]->dot1dTpPortInDiscards,
			   &(stats[i].inDiscards),
			   &last, delta);

	    g_string_append(interp->result, "\n");
	}
    }

    last = now;
    if (portTable) bridge_mib_free_dot1dTpPortTable(portTable);

    return SCLI_OK;
}



void
scli_init_bridge_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show bridge info", NULL,
	  "The show bridge info command displays summary information about\n"
	  "a bridge, such as the number of ports and the supported bridging\n"
	  "functions and associated parameters.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_bridge_info },

	{ "show bridge ports", NULL,
	  "The show bridge ports command displays information about the\n"
	  "bridge ports.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_bridge_ports },

	{ "show bridge stp ports", NULL,
	  "The show bridge stp ports command displays information about the\n"
	  "bridge ports which participate in the spanning tree protocol.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_bridge_stp_ports },

	{ "show bridge forwarding", NULL,
	  "The show bridge forwarding command displays the forwarding\n"
	  "data base used by transparent bridges. The command generates\n"
	  "a table with the following columns:\n"
	  "\n"
	  "  PORT    port number\n"
	  "  STATUS  status of the forwarding entry\n"
	  "  ADDRESS address associated with the port\n"
	  "  NAME    name of the address (where known)\n"
	  "  VENDOR  vendor info derived from the address",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_bridge_forwarding },

	{ "show bridge filter", NULL,
	  "The show bridge filte command shows filtering information.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_bridge_filter },

	{ "show bridge stats", NULL,
	  "The show bridge stats command displays per port statistics for\n"
	  "transparent bridges. The command generates a table with the\n"
	  "following columns:\n"
	  "\n"
	  "  PORT        port number\n"
	  "  I-FPS       input frames per second\n"
	  "  O-FPS       output frames per second\n"
	  "  D-FPS       discarded frames per second\n"
	  "  DESCRIPTION",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_bridge_stats },

	{ "monitor bridge stats", NULL,
	  "The monitor bridge stats command shows the same\n"
	  "information as the show bridge stats command. The"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  show_bridge_stats },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t bridge_mode = {
	"bridge",
	"The scli bridge mode is based on the BRIDGE-MIB as published in\n"
	"RFC 1493. It provides commands to browse information specific\n"
	"to LAN bridges (also known as layer two switches).",
	cmds
    };
    
    scli_register_mode(interp, &bridge_mode);
}
