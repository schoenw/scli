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
#include "if-mib-proc.h"
#if 1
#include "ip-mib.h"
#endif
#include "ianaiftype-mib.h"


static GNetSnmpEnum const dot1dBaseType[] = {
    { BRIDGE_MIB_DOT1DBASETYPE_UNKNOWN,	"unknown" },
    { BRIDGE_MIB_DOT1DBASETYPE_TRANSPARENT_ONLY,	"transparent (TP)" },
    { BRIDGE_MIB_DOT1DBASETYPE_SOURCEROUTE_ONLY,	"source route (SR)" },
    { BRIDGE_MIB_DOT1DBASETYPE_SRT,	"source route transparent (SRT)" },
    { 0, NULL }
};


static GNetSnmpEnum const dot1dStpProtocolSpecification[] = {
    { BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_UNKNOWN,	"unknown" },
    { BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_DECLB100,	"DEC LANbridge 100 Spanning Tree Protocol" },
    { BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_IEEE8021D,	"IEEE 802.1d Spanning Tree Protocol" },
    { 0, NULL }
};


static char*
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
fmt_stpStatus(GString *s, gint32 *enable, gint32 *state)
{
    const char *e;

    GNetSnmpEnum const port_state[] = {
	{ BRIDGE_MIB_DOT1DSTPPORTSTATE_DISABLED,	"D" },
	{ BRIDGE_MIB_DOT1DSTPPORTSTATE_BLOCKING,	"B" },
	{ BRIDGE_MIB_DOT1DSTPPORTSTATE_LISTENING,	"I" },
	{ BRIDGE_MIB_DOT1DSTPPORTSTATE_LEARNING,	"L" },
	{ BRIDGE_MIB_DOT1DSTPPORTSTATE_FORWARDING,	"F" },
	{ BRIDGE_MIB_DOT1DSTPPORTSTATE_BROKEN,		"X" },
	{ 0, NULL }
    };
    
    GNetSnmpEnum const port_enable[] = {
	{ BRIDGE_MIB_DOT1DSTPPORTENABLE_ENABLED,	"E" },
	{ BRIDGE_MIB_DOT1DSTPPORTENABLE_DISABLED,	"D" },
	{ 0, NULL }
    };

    e = fmt_enum(port_enable, enable);
    g_string_sprintfa(s, "%s", e ? e : "-");
    e = fmt_enum(port_state, state);
    g_string_sprintfa(s, "%s", e ? e : "-");
}



static void
fmt_bridge_stp_info(GString *s,
		    bridge_mib_dot1dBase_t *dot1dBase,
		    bridge_mib_dot1dStp_t *dot1dStp)
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
	g_string_sprintfa(s, "%-*s%d (0x%04x)\n", indent,
			      "Stp Priority:",
			  *dot1dStp->dot1dStpPriority,
			  *dot1dStp->dot1dStpPriority);
    }

    if (dot1dStp->dot1dStpPriority && dot1dBase->dot1dBaseBridgeAddress) {
	g_string_sprintfa(s, "%-*s%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n", indent,
			  "Stp Bridge ID:",
			  (*dot1dStp->dot1dStpPriority >> 8) & 0xff,
			  (*dot1dStp->dot1dStpPriority) & 0xff,
			  dot1dBase->dot1dBaseBridgeAddress[0],
			  dot1dBase->dot1dBaseBridgeAddress[1],
			  dot1dBase->dot1dBaseBridgeAddress[2],
			  dot1dBase->dot1dBaseBridgeAddress[3],
			  dot1dBase->dot1dBaseBridgeAddress[4],
			  dot1dBase->dot1dBaseBridgeAddress[5]);
	
    }
    
    if (dot1dStp->dot1dStpDesignatedRoot) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Stp Root ID:",
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
	g_string_sprintfa(s, "%-*s%d milliseconds\n", indent,
			  "Stp Aging Time:", *dot1dStp->dot1dStpMaxAge * 10);
    }

    if (dot1dStp->dot1dStpHelloTime) {
	g_string_sprintfa(s, "%-*s%d milliseconds\n", indent,
			  "Stp Hello Time:", *dot1dStp->dot1dStpHelloTime * 10);
    }

    if (dot1dStp->dot1dStpHoldTime) {
	g_string_sprintfa(s, "%-*s%d milliseconds\n", indent,
			  "Stp Hold  Time:", *dot1dStp->dot1dStpHoldTime * 10);
    }

    if (dot1dStp->dot1dStpForwardDelay) {
	g_string_sprintfa(s, "%-*s%d milliseconds\n", indent,
			  "Stp Fwd Delay:", *dot1dStp->dot1dStpForwardDelay * 10);
    }

    if (dot1dStp->dot1dStpTimeSinceTopologyChange) {
	g_string_sprintfa(s, "%-*s", indent, "Stp Topo Change:");
	g_string_append(s, fmt_timeticks(*(dot1dStp->dot1dStpTimeSinceTopologyChange)));
	g_string_append_c(s, '\n');
    }
    
    if (dot1dStp->dot1dStpTopChanges) {
	g_string_sprintfa(s, "%-*s%u (estimated)\n", indent,
			  "Stp Topo Changes:", *dot1dStp->dot1dStpTopChanges);
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
		|| *dot1dBase->dot1dBaseType == BRIDGE_MIB_DOT1DBASETYPE_SRT)) {
	    if (dot1dTp && dot1dTp->dot1dTpAgingTime) {
		g_string_sprintfa(s, "%-*s%d seconds\n", indent, "Tp Aging Time:",
				  *dot1dTp->dot1dTpAgingTime);
	    }
	}
    }

    if (dot1dStp) {
	fmt_bridge_stp_info(s, dot1dBase, dot1dStp);
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
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    bridge_mib_get_dot1dBase(interp->peer, &dot1dBase, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (dot1dBase
	&& dot1dBase->dot1dBaseNumPorts
	&& *dot1dBase->dot1dBaseNumPorts) {
	bridge_mib_get_dot1dTp(interp->peer, &dot1dTp, 0);
	bridge_mib_get_dot1dStp(interp->peer, &dot1dStp, 0);
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
	type = fmt_enum(ianaiftype_mib_enums_IANAifType, ifEntry->ifType);
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
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    bridge_mib_get_dot1dBasePortTable(interp->peer, &dot1dBasePortTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    if_mib_proc_get_ifTable(interp->peer, &ifTable,
			    IF_MIB_IFTYPE | IF_MIB_IFSPEED | IF_MIB_IFDESCR, interp->epoch);
    if_mib_get_ifXTable(interp->peer, &ifXTable,
			IF_MIB_IFNAME | IF_MIB_IFHIGHSPEED);
    
    if (dot1dBasePortTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (ifXTable && ifXTable[i]) {
		if (ifXTable[i]->_ifNameLength > name_width) {
		    name_width = ifXTable[i]->_ifNameLength;
		}
	    }
	    if (ifTable[i]->ifType) {
		char const *label;
		label = gnet_snmp_enum_get_label(ianaiftype_mib_enums_IANAifType,
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
    if (ifTable) if_mib_proc_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    return SCLI_OK;
}



static void
fmt_bridge_stp_port(GString *s,
		    bridge_mib_dot1dStpPortEntry_t *dot1dStpPortEntry)
{
    g_string_sprintfa(s, "%5u ", dot1dStpPortEntry->dot1dStpPort);

    if (dot1dStpPortEntry->dot1dStpPortPriority) {
	g_string_sprintfa(s, "%5u   ", *dot1dStpPortEntry->dot1dStpPortPriority);
    }

    fmt_stpStatus(s, dot1dStpPortEntry->dot1dStpPortEnable,
		  dot1dStpPortEntry->dot1dStpPortState);

    if (dot1dStpPortEntry->dot1dStpPortPathCost) {
	g_string_sprintfa(s, "%6u  ", *dot1dStpPortEntry->dot1dStpPortPathCost);
    } else {
	g_string_sprintfa(s, "%6s  ", "");
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
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    bridge_mib_get_dot1dStpPortTable(interp->peer, &dot1dStpPortTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (dot1dStpPortTable) {
	g_string_sprintfa(interp->header,
			  " PORT  PRIO STATE P-COST D-ROOT D-COST D-BRIDGE D-PORT");
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
		      ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry,
		      int name_width)
{
    const scli_vendor_t *vendor;
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
	if (ipNetToMediaEntry) {
	    g_string_sprintfa(s, " %-15s",
			      fmt_ipv4_address(ipNetToMediaEntry->ipNetToMediaNetAddress, SCLI_FMT_ADDR));
	} else {
	    g_string_sprintfa(s, " %-15s", "");
	}
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
#if 1
    ip_mib_ipNetToMediaEntry_t **ipNetToMediaTable = NULL;
#endif
    char *name;
    int i, p, max = 0;
    int name_width = 8;
    int k = 0;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    bridge_mib_get_dot1dTpFdbTable(interp->peer, &dot1dTpFdbTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

#if 1
    ip_mib_get_ipNetToMediaTable(interp->peer, &ipNetToMediaTable,
				 IP_MIB_IPNETTOMEDIAPHYSADDRESS);
#endif

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
			  " PORT STATUS   ADDRESS           %-*s IP ADDRESS      VENDOR",
			  name_width, "NAME");
	for (p = 0; p < max+1; p++) {
	    for (i = 0; dot1dTpFdbTable[i]; i++) {
		if (dot1dTpFdbTable[i]->dot1dTpFdbPort
		    && *dot1dTpFdbTable[i]->dot1dTpFdbPort == p) {

		    /* do not follow the mapping port number ->
		     * interface number -> ipNetToMedia entry since
		     * this won't work on some bridges (e.g. 3com)
		     */

		    if (ipNetToMediaTable) {
			for (k = 0; ipNetToMediaTable[k]; k++) {
			    if (ipNetToMediaTable[k]->_ipNetToMediaPhysAddressLength == 6
				&& ipNetToMediaTable[k]->ipNetToMediaPhysAddress
				&& memcmp(ipNetToMediaTable[k]->ipNetToMediaPhysAddress, dot1dTpFdbTable[i]->dot1dTpFdbAddress, 6) == 0) {
				break;
			    }
			}
		    }
		    
		    fmt_bridge_forwarding(interp->result, dot1dTpFdbTable[i],
					  (ipNetToMediaTable && ipNetToMediaTable[k]) ? ipNetToMediaTable[k] : NULL,
					  name_width);
		}
	    }
	}
    }

#if 1
    if (ipNetToMediaTable) ip_mib_free_ipNetToMediaTable(ipNetToMediaTable);
#endif
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
	g_string_sprintfa(s, "%5s ", "*");
    }

    status = fmt_enum(bridge_mib_enums_dot1dStaticStatus,
		      dot1dStaticEntry->dot1dStaticStatus);
    if (status) {
	g_string_sprintfa(s, "%-15s ", status);
    }
    
    if (dot1dStaticEntry->dot1dStaticAddress) {
	char *addr = fmt_ether_address(dot1dStaticEntry->dot1dStaticAddress,
				       SCLI_FMT_ADDR);
	g_string_sprintfa(s, "%s ", addr);
    } else {
	g_string_sprintfa(s, "--:--:--:--:--:-- ");
    }

    if (dot1dStaticEntry->dot1dStaticAllowedToGoTo) {
	fmt_port_set(s, dot1dStaticEntry->dot1dStaticAllowedToGoTo,
		     dot1dStaticEntry->_dot1dStaticAllowedToGoToLength);
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
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    bridge_mib_get_dot1dStaticTable(interp->peer, &dot1dStaticTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (dot1dStaticTable) {
	g_string_sprintfa(interp->header,
			  " PORT STATUS          ADDRESS           ALLOWED-PORTS");
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
    char    *descr;
} bridge_stats_t;


static char*
get_port_description(scli_interp_t *interp, gint32 dot1dTpPort)
{
    bridge_mib_dot1dBasePortEntry_t *dot1dBasePortEntry = NULL;
    if_mib_ifEntry_t *ifEntry = NULL;
    char *descr = NULL;

    bridge_mib_get_dot1dBasePortEntry(interp->peer, &dot1dBasePortEntry,
				      dot1dTpPort,
				      BRIDGE_MIB_DOT1DBASEPORTIFINDEX);
    if (interp->peer->error_status) {
	return NULL;
    }

    if (dot1dBasePortEntry && dot1dBasePortEntry->dot1dBasePortIfIndex) {
	if_mib_get_ifEntry(interp->peer, &ifEntry,
			   *dot1dBasePortEntry->dot1dBasePortIfIndex,
			   IF_MIB_IFDESCR);
	if (! interp->peer->error_status && ifEntry) {
	    descr = g_strdup_printf("%.*s", ifEntry->_ifDescrLength,
				    ifEntry->ifDescr);
	}
    }

    if (ifEntry) if_mib_free_ifEntry(ifEntry);
    if (dot1dBasePortEntry)
	bridge_mib_free_dot1dBasePortEntry(dot1dBasePortEntry);
    
    return descr;
}


static int
show_bridge_stats(scli_interp_t *interp, int argc, char **argv)
{
    bridge_mib_dot1dTpPortEntry_t **portTable = NULL;
    static struct timeval last, now;
    double delta;
    static bridge_stats_t *stats = NULL;
    static int stats_size = 0;
    static time_t epoch = 0;
    int i;
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    bridge_mib_get_dot1dTpPortTable(interp->peer, &portTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (epoch < interp->epoch) {
	if (stats) {
	    for (i = 0; i < stats_size; i++) {
		if (stats[i].descr) g_free(stats[i].descr);
	    }
	    g_free(stats);
	}
	stats = NULL;
	stats_size = 0;
	last.tv_sec = last.tv_usec = 0;
    }

    if (! stats && portTable) {
	for (i = 0; portTable[i]; i++) ;
	stats_size = i;
	stats = g_new0(bridge_stats_t, i);
	for (i = 0; portTable[i]; i++) {
	    stats[i].descr = get_port_description(interp,
						  portTable[i]->dot1dTpPort);
	}
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

	    g_string_sprintfa(interp->result, " %s\n",
			      stats[i].descr ? stats[i].descr : "");
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
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_bridge_info },

	{ "show bridge ports", NULL,
	  "The show bridge ports command displays information about the\n"
	  "bridge ports.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_bridge_ports },

	{ "show bridge stp ports", NULL,
	  "The show bridge stp ports command displays information about the\n"
	  "bridge ports which participate in the spanning tree protocol. The\n"
	  "command generates a table with the following columns:\n"
	  "\n"
	  "  PORT     port number\n"
	  "  PRIO     spanning tree priority of the port\n"
	  "  STATE    spanning tree status of the port\n"
	  "  P-COST   path costs for this port\n"
	  "  D-ROOT   designated root port\n"
	  "  D-COST   designated costs\n"
	  "  D-BRIDGE designated bridge\n"
	  "  D-PORT   designated port\n"
	  "\n"
	  "The status is encoded in two characters. The first character\n"
	  "indicates whether STP on the port is enabled (E) or disabled\n"
	  "(D). The second character indicates the current status\n"
	  "(D=disabled, B=blocking, I=listening, L=learning, F=forwarding,\n"
	  "X=broken).",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
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
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_bridge_forwarding },

	{ "show bridge filter", NULL,
	  "The show bridge filter command shows filtering information.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
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
	  "  DESCRIPTION description of the port",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_bridge_stats },

	{ "monitor bridge stats", NULL,
	  "The monitor bridge stats command shows the same\n"
	  "information as the show bridge stats command. The"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
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
