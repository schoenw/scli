/* 
 * ip.c -- scli ip mode implementation
 *
 * Copyright (C) 2001-2002 Juergen Schoenwaelder
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

#include "ip-mib.h"
#include "ip-forward-mib.h"
#include "ianaiftype-mib.h"
#include "tunnel-mib.h"
#include "if-mib.h"
#include "rfc1213-mib.h"
#include "ianaiftype-mib.h"
#include "inet-address-mib.h"

#include "ianaiftype-mib-proc.h"

#define RFC1213_MIB_IPROUTE_MASK \
	( RFC1213_MIB_IPROUTEDEST | RFC1213_MIB_IPROUTEIFINDEX \
	  | RFC1213_MIB_IPROUTENEXTHOP | RFC1213_MIB_IPROUTETYPE \
	  | RFC1213_MIB_IPROUTEPROTO | RFC1213_MIB_IPROUTEMASK )


GNetSnmpEnum const forwarding[] = {
    { IP_MIB_IPFORWARDING_FORWARDING,	"enabled" },
    { IP_MIB_IPFORWARDING_NOTFORWARDING,	"disabled" },
    { 0, NULL }
};



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
fmt_route_if(GString *s, gint32 *ifIndex,
	     if_mib_ifXEntry_t **ifXTable,
	     if_mib_ifEntry_t **ifTable)
{
    int i;
    
    if (ifIndex) {
	g_string_sprintfa(s, "%2d", *ifIndex);
	if (ifXTable) {
	    for (i = 0; ifXTable[i]; i++) {
		if (ifXTable[i]->ifIndex == *ifIndex
		    && ifXTable[i]->ifName) {
		    g_string_sprintfa(s, " (%.*s)",
				      (int) ifXTable[i]->_ifNameLength,
				      ifXTable[i]->ifName);
		    break;
		}
	    }
	} else if (ifTable) {
	    for (i = 0; ifTable[i]; i++) {
		if (ifTable[i]->ifIndex == *ifIndex
		    && ifTable[i]->ifDescr) {
		    g_string_sprintfa(s, " (%.*s)",
				      (int) ifTable[i]->_ifDescrLength,
				      ifTable[i]->ifDescr);
		    break;
		}
	    }
	}
    }
    g_string_append(s, "\n");
}



static void
fmt_inet_route(GString *s,
	       ip_forward_mib_inetCidrRouteEntry_t *inetCidrRouteEntry,
	       if_mib_ifXEntry_t **ifXTable,
	       if_mib_ifEntry_t **ifTable)
{
    const char *label;
    int pos;

    label = fmt_inet_address(&inetCidrRouteEntry->inetCidrRouteDestType,
			     inetCidrRouteEntry->inetCidrRouteDest,
			     inetCidrRouteEntry->_inetCidrRouteDestLength);
    g_string_sprintfa(s, "%s/%u%n", label ? label : "?",
		      inetCidrRouteEntry->inetCidrRoutePfxLen, &pos);
    g_string_sprintfa(s, "%*s", MAX(20-pos, 1), "");

    label = fmt_inet_address(&inetCidrRouteEntry->inetCidrRouteNextHopType,
			     inetCidrRouteEntry->inetCidrRouteNextHop,
			     inetCidrRouteEntry->_inetCidrRouteNextHopLength);
    g_string_sprintfa(s, "%s%n", label ? label : "?", &pos);
    g_string_sprintfa(s, "%*s", MAX(20-pos, 1), "");
    
    label = NULL;
    if (inetCidrRouteEntry->inetCidrRouteType) {
	label = gnet_snmp_enum_get_label(ip_forward_mib_enums_inetCidrRouteType,
					 *inetCidrRouteEntry->inetCidrRouteType);
    }
    g_string_sprintfa(s, "%-10s", label ? label : "");
    
    label = NULL;
    if (inetCidrRouteEntry->inetCidrRouteProto) {
	label = gnet_snmp_enum_get_label(ip_forward_mib_enums_ipCidrRouteProto,
					 *inetCidrRouteEntry->inetCidrRouteProto);
    }
    g_string_sprintfa(s, "%-10s", label ? label : "");

    fmt_route_if(s, inetCidrRouteEntry->inetCidrRouteIfIndex,
		 ifXTable, ifTable);
}



static void
fmt_ip_forward(GString *s,
	       ip_forward_mib_ipCidrRouteEntry_t *ipCidrRouteEntry,
	       if_mib_ifXEntry_t **ifXTable,
	       if_mib_ifEntry_t **ifTable)
{
    const char *label;
    int pos;
    
    if (ipCidrRouteEntry->ipCidrRouteIfIndex) {
	g_string_sprintfa(s, "%s/%s%n",
			  fmt_ipv4_address(ipCidrRouteEntry->ipCidrRouteDest,
					   SCLI_FMT_ADDR),
			  fmt_ipv4_mask(ipCidrRouteEntry->ipCidrRouteMask), &pos);
	g_string_sprintfa(s, "%*s", MAX(20-pos, 1), "");
	
	g_string_sprintfa(s, "  %2d ", ipCidrRouteEntry->ipCidrRouteTos);
	
	g_string_sprintfa(s, "%-16s",
			  fmt_ipv4_address(ipCidrRouteEntry->ipCidrRouteNextHop,
					   SCLI_FMT_ADDR));

	label = NULL;
	if (ipCidrRouteEntry->ipCidrRouteType) {
	    label = gnet_snmp_enum_get_label(ip_forward_mib_enums_ipCidrRouteType,
					     *ipCidrRouteEntry->ipCidrRouteType);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	label = NULL;
	if (ipCidrRouteEntry->ipCidrRouteProto) {
	    label = gnet_snmp_enum_get_label(ip_forward_mib_enums_ipCidrRouteProto,
					     *ipCidrRouteEntry->ipCidrRouteProto);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	fmt_route_if(s, ipCidrRouteEntry->ipCidrRouteIfIndex,
		     ifXTable, ifTable);
    }
}



static void
fmt_ip_route(GString *s,
	     rfc1213_mib_ipRouteEntry_t *ipRouteEntry,
	     if_mib_ifXEntry_t **ifXTable,
	     if_mib_ifEntry_t **ifTable)
{
    const char *label;
    int pos;
    
    if (ipRouteEntry->ipRouteDest
	&& ipRouteEntry->ipRouteNextHop
	&& ipRouteEntry->ipRouteMask
	&& ipRouteEntry->ipRouteIfIndex) {
	g_string_sprintfa(s, "%s/%s%n",
			  fmt_ipv4_address(ipRouteEntry->ipRouteDest,
					   SCLI_FMT_ADDR),
			  fmt_ipv4_mask(ipRouteEntry->ipRouteMask), &pos);
	g_string_sprintfa(s, "%*s", MAX(20-pos, 1), "");

	g_string_sprintfa(s, "   - ");
	
	g_string_sprintfa(s, "%-16s",
			  fmt_ipv4_address(ipRouteEntry->ipRouteNextHop,
					   SCLI_FMT_ADDR));

	label = NULL;
	if (ipRouteEntry->ipRouteType) {
	    label = gnet_snmp_enum_get_label(rfc1213_mib_enums_ipRouteType,
					     *ipRouteEntry->ipRouteType);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	label = NULL;
	if (ipRouteEntry->ipRouteProto) {
	    label = gnet_snmp_enum_get_label(rfc1213_mib_enums_ipRouteProto,
					     *ipRouteEntry->ipRouteProto);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	fmt_route_if(s, ipRouteEntry->ipRouteIfIndex,
		     ifXTable, ifTable);
    }
}



static int
show_ip_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    ip_forward_mib_inetCidrRouteEntry_t **inetCidrRouteTable = NULL;
    ip_forward_mib_ipCidrRouteEntry_t **ipCidrRouteTable = NULL;
    rfc1213_mib_ipRouteEntry_t **ipRouteTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int i;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ip_forward_mib_get_inetCidrRouteTable(interp->peer, &inetCidrRouteTable, 0, &error);
    if (error || interp->peer->error_status || !inetCidrRouteTable) {
	ip_forward_mib_get_ipCidrRouteTable(interp->peer, &ipCidrRouteTable, 0, &error);
	if (error || interp->peer->error_status || !ipCidrRouteTable) {
	    rfc1213_mib_get_ipRouteTable(interp->peer, &ipRouteTable, RFC1213_MIB_IPROUTE_MASK, &error);
	    if (scli_interp_set_error_snmp(interp, &error)) {
		return SCLI_SNMP;
	    }
	}
    }

    if (inetCidrRouteTable || ipCidrRouteTable || ipRouteTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, IF_MIB_IFDESCR, NULL);
	if_mib_get_ifXTable(interp->peer, &ifXTable, IF_MIB_IFNAME, NULL);
	g_string_sprintfa(interp->header, "%-20s TOS %-16s%-10s%-10s%s",
		  "DESTINATION", "NEXT-HOP", "TYPE", "PROTO", "INTERFACE");
	if (inetCidrRouteTable) {
	    for (i = 0; inetCidrRouteTable[i]; i++) {
		fmt_inet_route(interp->result, inetCidrRouteTable[i],
			       ifXTable, ifTable);
	    }
	} else if (ipCidrRouteTable) {
	    for (i = 0; ipCidrRouteTable[i]; i++) {
		fmt_ip_forward(interp->result, ipCidrRouteTable[i],
			       ifXTable, ifTable);
	    }
	} else if (ipRouteTable) {
	    for (i = 0; ipRouteTable[i]; i++) {
		fmt_ip_route(interp->result, ipRouteTable[i],
			     ifXTable, ifTable);
	    }
	}
    }

    if (ifTable)
	if_mib_free_ifTable(ifTable);
    if (ifXTable)
	if_mib_free_ifXTable(ifXTable);
    if (ipRouteTable)
	rfc1213_mib_free_ipRouteTable(ipRouteTable);
    if (ipCidrRouteTable)
	ip_forward_mib_free_ipCidrRouteTable(ipCidrRouteTable);

    return SCLI_OK;
}



static void
xml_ip_address(xmlNodePtr root, ip_mib_ipAddrEntry_t *ipAddrEntry)
{
    xmlNodePtr tree;
    char *name;

    tree = xml_new_child(root, NULL, BAD_CAST("address"), NULL);
    xml_set_prop(tree, BAD_CAST("address"), "%s",
		 fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_ADDR));
    xml_set_prop(tree, BAD_CAST("type"), "ipv4");

    if (ipAddrEntry->ipAdEntNetMask) {
	xml_set_prop(tree, BAD_CAST("prefix"), "%s",
		     fmt_ipv4_mask(ipAddrEntry->ipAdEntNetMask));
    }

    if (ipAddrEntry->ipAdEntIfIndex) {
	xml_set_prop(tree, BAD_CAST("interface"),
		     "%d", *ipAddrEntry->ipAdEntIfIndex);
    }

    name = fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_NAME);
    if (name) {
	(void) xml_new_child(tree, NULL, BAD_CAST("name"), "%s", name);
    }
}



static void
fmt_ip_address(GString *s,
	       ip_mib_ipAddrEntry_t *ipAddrEntry,
	       int name_width,
	       if_mib_ifXEntry_t **ifXTable,
	       if_mib_ifEntry_t **ifTable,
	       int ifName_width)
{
    char *name;
    int i;

    g_string_sprintfa(s, "%-17s ",
	      fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_ADDR));
    if (ipAddrEntry->ipAdEntNetMask) {
	g_string_sprintfa(s, "/%-4s",
			  fmt_ipv4_mask(ipAddrEntry->ipAdEntNetMask));;
    } else {
	g_string_sprintfa(s, "%-5s", "");
    }
    name = fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_NAME);
    g_string_sprintfa(s, "%-*s ", name_width, name ? name : "");
    
    if (ipAddrEntry->ipAdEntIfIndex) {
	g_string_sprintfa(s, "%9u", *(ipAddrEntry->ipAdEntIfIndex));
	for (i = 0; ifXTable && ifXTable[i]; i++) {
	    if (ifXTable[i]->ifIndex == *ipAddrEntry->ipAdEntIfIndex
		&& ifXTable[i]->ifName) {
		g_string_sprintfa(s, " %-*.*s", ifName_width,
				  (int) ifXTable[i]->_ifNameLength,
				  ifXTable[i]->ifName);
		break;
	    }
	}
	if (!ifXTable || !ifXTable[i]) {
	    g_string_sprintfa(s, " %*s", ifName_width, "");
	}
	if (ifTable) {
	    for (i = 0; ifTable[i]; i++) {
		if (ifTable[i]->ifIndex == *ipAddrEntry->ipAdEntIfIndex
		    && ifTable[i]->ifDescr) {
		    g_string_sprintfa(s, " %.*s",
				      (int) ifTable[i]->_ifDescrLength,
				      ifTable[i]->ifDescr);
		    break;
		}
	    }
	}
    }
    g_string_append(s, "\n");
}



static int
show_ip_addresses(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ipAddrEntry_t **ipAddrTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int i, name_width = 4, ifName_width;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (ipAddrTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, IF_MIB_IFDESCR, NULL);
	if_mib_get_ifXTable(interp->peer, &ifXTable, IF_MIB_IFNAME, NULL);
	ifName_width = get_if_name_width(ifXTable);
	if (! scli_interp_xml(interp)) {
	    for (i = 0; ipAddrTable[i]; i++) {
		char *name;
		name = fmt_ipv4_address(ipAddrTable[i]->ipAdEntAddr, SCLI_FMT_NAME);
		if (name && strlen(name) > name_width) {
		    name_width = strlen(name);
		}
	    }
	    g_string_sprintfa(interp->header,
		      "ADDRESS         PREFIX %-*s INTERFACE %-*s DESCRIPTION",
			      name_width, "NAME", ifName_width, "NAME");
	}
	for (i = 0; ipAddrTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_ip_address(interp->xml_node, ipAddrTable[i]);
	    } else {
		fmt_ip_address(interp->result, ipAddrTable[i],
			       name_width, ifXTable, ifTable, ifName_width);
	    }
	}
    }

    if (ifTable)
	if_mib_free_ifTable(ifTable);
    if (ifXTable)
	if_mib_free_ifXTable(ifXTable);
    if (ipAddrTable)
	ip_mib_free_ipAddrTable(ipAddrTable);

    return SCLI_OK;
}



static void
fmt_ip_tunnel(GString *s,
	      tunnel_mib_tunnelIfEntry_t *tunnelIfEntry,
	      if_mib_ifXEntry_t **ifXTable,
	      if_mib_ifEntry_t **ifTable)
{
    int i;
    const char *e;

    g_return_if_fail(tunnelIfEntry);

    if (tunnelIfEntry->tunnelIfLocalAddress) {
	g_string_sprintfa(s, "%-15s  ",
		  fmt_ipv4_address(tunnelIfEntry->tunnelIfLocalAddress,
				   SCLI_FMT_ADDR));
    } else {
	g_string_sprintfa(s, "%-15s  ", "-");
    }

    if (tunnelIfEntry->tunnelIfRemoteAddress) {
	g_string_sprintfa(s, "%-15s  ",
		  fmt_ipv4_address(tunnelIfEntry->tunnelIfRemoteAddress,
				   SCLI_FMT_ADDR));
    } else {
	g_string_sprintfa(s, "%-15s  ", "-");
    }

    e = fmt_enum(ianaiftype_mib_enums_IANAtunnelType,
		 tunnelIfEntry->tunnelIfEncapsMethod);
    g_string_sprintfa(s, "%-8s", e ? e : "-");

    e = fmt_enum(tunnel_mib_enums_tunnelIfSecurity,
		 tunnelIfEntry->tunnelIfSecurity);
    g_string_sprintfa(s, "%-6s", e ? e : "-");

    if (tunnelIfEntry->tunnelIfHopLimit) {
	g_string_sprintfa(s, "%3d  ", *tunnelIfEntry->tunnelIfHopLimit);
    } else {
	g_string_sprintfa(s, "%3s  ", "---");
    }
    
    if (tunnelIfEntry->tunnelIfTOS) {
	switch (*tunnelIfEntry->tunnelIfTOS) {
	case -1:
	    /* A value of -1 indicates that the bits are copied from the
	     * payload's header. */
	    g_string_append(s, "CP");
	    break;
	case -2:
	    /* A value of -2 indicates that a traffic conditioner is
	     * invoked and more information may be available in a traffic
	     * conditioner MIB. */
	    g_string_append(s, "TC");
	    break;
        default:
	    g_string_sprintfa(s, "%2d", *tunnelIfEntry->tunnelIfTOS);
	    break;
	}
    } else {
	g_string_append(s, "--");
    }

    if (tunnelIfEntry->ifIndex) {
	g_string_sprintfa(s, " %2u", tunnelIfEntry->ifIndex);
        if (ifXTable) {
	    for (i = 0; ifXTable[i]; i++) {
	        if(ifXTable[i]->ifIndex == tunnelIfEntry->ifIndex) {
		   g_string_sprintfa(s, " (%.*s)",
                         (int) ifXTable[i]->_ifNameLength,
			 ifXTable[i]->ifName);
		   break;
		}
	    }
	} else if (ifTable) {
            for (i = 0; ifTable[i]; i++) {
		if(ifTable[i]->ifIndex == tunnelIfEntry->ifIndex) {
		  g_string_sprintfa(s, " (%.*s)",
	                (int) ifTable[i]->_ifDescrLength,
			ifTable[i]->ifDescr);
		  break;
		}
	    }
	}
    }
    g_string_append(s, "\n");
}



static int
show_ip_tunnel(scli_interp_t *interp, int argc, char **argv)
{
    tunnel_mib_tunnelIfEntry_t **tunnelIfTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int i;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    tunnel_mib_get_tunnelIfTable(interp->peer, &tunnelIfTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (tunnelIfTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, IF_MIB_IFDESCR, NULL);
	if_mib_get_ifXTable(interp->peer, &ifXTable, IF_MIB_IFNAME, NULL);
	g_string_append(interp->header,
	"LOCAL ADDRESS    REMOTE ADDRESS   TYPE    SEC.  TTL TOS INTERFACE");
	for (i = 0; tunnelIfTable[i]; i++) {
	    fmt_ip_tunnel(interp->result, tunnelIfTable[i],
			  ifXTable, ifTable);
	}
    }

    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (tunnelIfTable) tunnel_mib_free_tunnelIfTable(tunnelIfTable);

    return SCLI_OK;
}



static void
fmt_ip_mapping(GString *s,
	       ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry,
	       if_mib_ifEntry_t *ifEntry)
{
    char *name;
    const char *e;
    int i;

    g_string_sprintfa(s, "%9u ",
		      ipNetToMediaEntry->ipNetToMediaIfIndex);

    e = fmt_enum(ip_mib_enums_ipNetToMediaType,
		 ipNetToMediaEntry->ipNetToMediaType);
    g_string_sprintfa(s, "%-8s", e ? e : "");
    
    g_string_sprintfa(s, " %-16s ",
	      fmt_ipv4_address(ipNetToMediaEntry->ipNetToMediaNetAddress,
			       SCLI_FMT_ADDR));

    if (ipNetToMediaEntry->ipNetToMediaPhysAddress) {
	for (i = 0;
	     i < ipNetToMediaEntry->_ipNetToMediaPhysAddressLength; i++) {
	    g_string_sprintfa(s, "%s%02x", i ? ":" : "",
			      ipNetToMediaEntry->ipNetToMediaPhysAddress[i]);
	}
	/* See RFC 2665 section 3.2.6. why the test below is so ugly... */
	if (ifEntry && ifEntry->ifType
	    && ipNetToMediaEntry->_ipNetToMediaPhysAddressLength == 6
	    && ianaiftype_mib_proc_isether(*ifEntry->ifType)) {
	    name = fmt_ether_address(ipNetToMediaEntry->ipNetToMediaPhysAddress, SCLI_FMT_NAME);
	    if (name) {
		g_string_sprintfa(s, " (%s)", name);
	    }
	}
    }
    
    g_string_append(s, "\n");
}



static int
show_ip_mapping(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ipNetToMediaEntry_t **ipNetToMediaTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL, *ifEntry = NULL;
    int i, j;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ip_mib_get_ipNetToMediaTable(interp->peer, &ipNetToMediaTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (ipNetToMediaTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, IF_MIB_IFTYPE, NULL);
	g_string_append(interp->header,
		"INTERFACE STATUS   ADDRESS          LOWER LAYER ADDRESS");
	for (i = 0; ipNetToMediaTable[i]; i++) {
	    if (ifTable) {
		for (j = 0; ifTable[j]; j++) {
		    if (ipNetToMediaTable[i]->ipNetToMediaIfIndex
			== ifTable[j]->ifIndex) break;
		}
		if (ifTable[j]) {
		    ifEntry = ifTable[j];
		}
	    }
	    fmt_ip_mapping(interp->result, ipNetToMediaTable[i], ifEntry);
	}
    }


    if (ipNetToMediaTable) ip_mib_free_ipNetToMediaTable(ipNetToMediaTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    
    return SCLI_OK;
}



static int
create_ip_mapping(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry = NULL;
    gint32 type = IP_MIB_IPNETTOMEDIATYPE_STATIC;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 4) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ipNetToMediaEntry = ip_mib_new_ipNetToMediaEntry();
    if (! ipNetToMediaEntry) {
	return SCLI_ERROR;
    }

    ipNetToMediaEntry->ipNetToMediaIfIndex = 42;
    memcpy(ipNetToMediaEntry->ipNetToMediaNetAddress, "gaga",
	   IP_MIB_IPNETTOMEDIANETADDRESSLENGTH);
    ipNetToMediaEntry->ipNetToMediaPhysAddress = "deadbeef";
    ipNetToMediaEntry->_ipNetToMediaPhysAddressLength = 8;
    ipNetToMediaEntry->ipNetToMediaType = &type;

    ip_mib_set_ipNetToMediaEntry(interp->peer, ipNetToMediaEntry, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (ipNetToMediaEntry) ip_mib_free_ipNetToMediaEntry(ipNetToMediaEntry);
    
    return SCLI_OK;
}



static void
fmt_ip_info(GString *s, ip_mib_ip_t *ip)
{
    int const indent = 18;
    const char *e;

    e = fmt_enum(forwarding, ip->ipForwarding);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Forwarding:", e);
    }

    if (ip->ipDefaultTTL) {
	g_string_sprintfa(s, "%-*s%d hops\n", indent, "Default-TTL:",
			  *ip->ipDefaultTTL);
    }

    if (ip->ipReasmTimeout) {
	g_string_sprintfa(s, "%-*s%d seconds\n", indent, "Reasm-Timeout:",
			  *ip->ipReasmTimeout);
    }
}



static void
xml_ip_info(xmlNodePtr tree, ip_mib_ip_t *ip)
{
    xmlNodePtr node;
    const char *e;

    e = fmt_enum(forwarding, ip->ipForwarding);
    if (e) {
	(void) xml_new_child(tree, NULL, BAD_CAST("forwarding"), "%s", e);
    }

    if (ip->ipDefaultTTL) {
	node = xml_new_child(tree, NULL, BAD_CAST("default-ttl"), "%d",
			     *ip->ipDefaultTTL);
	xml_set_prop(node, BAD_CAST("unit"), "hops");
    }

    if (ip->ipReasmTimeout) {
	node = xml_new_child(tree, NULL, BAD_CAST("reassemble-timeout"), "%d",
			     *ip->ipDefaultTTL);
	xml_set_prop(node, BAD_CAST("unit"), "seconds");
    }
}



static void
xxx_ip_info(GString *s, xmlNodePtr tree)
{
    int const indent = 18;
    xmlNodePtr node;

    for (node = tree->children; node; node = node->next) {
	g_printerr("%s\n", xmlGetNodePath(node));
	if (xmlStrcmp(node->name, (const xmlChar *) "forwarding") == 0) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Forwarding:", 
			      node->content);
	}
    }
}



static int
show_ip_info(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ip_mib_get_ip(interp->peer, &ip, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (ip) {
	if (scli_interp_xml(interp)) {
	    xml_ip_info(interp->xml_node, ip);
	} else {
	    fmt_ip_info(interp->result, ip);
	}
    }

    if (scli_interp_xml(interp)) {
	xxx_ip_info(interp->result, interp->xml_node);
	g_printerr("%s", interp->result->str);
    }

    if (ip) ip_mib_free_ip(ip);

    return SCLI_OK;
}



static int
set_ip_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;
    gint32 value;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (! gnet_snmp_enum_get_number(forwarding, argv[1], &value)) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ip = ip_mib_new_ip();
    ip->ipForwarding = &value;
    ip_mib_set_ip(interp->peer, ip, IP_MIB_IPFORWARDING, &error);
    ip_mib_free_ip(ip);

    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
set_ip_ttl(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;
    gint32 value;
    char *end;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    value = strtol(argv[1], &end, 0);
    if (*end || value < 1 || value > 255) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_NUMBER;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ip = ip_mib_new_ip();
    ip->ipDefaultTTL = &value;
    ip_mib_set_ip(interp->peer, ip, IP_MIB_IPDEFAULTTTL, &error);
    ip_mib_free_ip(ip);

    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
dump_ip(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;
    const char *e;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ip_mib_get_ip(interp->peer, &ip,
		  IP_MIB_IPFORWARDING | IP_MIB_IPDEFAULTTTL, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (ip) {
	e = fmt_enum(forwarding, ip->ipForwarding);
	if (e) {
	    g_string_sprintfa(interp->result,
			      "set ip forwarding \"%s\"\n", e);
	}
	if (ip->ipDefaultTTL) {
	    g_string_sprintfa(interp->result,
			      "set ip ttl \"%d\"\n",
			      *ip->ipDefaultTTL);
	}
    }

    if (ip) ip_mib_free_ip(ip);

    return SCLI_OK;
}



void
scli_init_ip_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "set ip forwarding", "<value>",
	  "The `set ip forwarding' command controls whether the IP protocol\n"
	  "engine forwards IP datagrams or not. The <value> parameter must\n"
	  "be one of the strings \"enabled\" or \"disabled\".",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_ip_forwarding },
	
	{ "set ip ttl", "<number>",
	  "The `set ip ttl' command can be used to change the default\n"
	  "time to live (TTL) value used by the IP protocol engine. The\n"
	  "<number> parameter must be a number between 1 and 255 inclusive.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_ip_ttl },
	
	{ "show ip info", NULL,
	  "The `show ip info' command displays parameters of the IP\n"
	  "protocol engine, such as the default TTL or whether the\n"
	  "node is forwarding IP packets.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "ip info", NULL,
	  show_ip_info },
	
	{ "show ip forwarding", NULL,
	  "The `show ip forwarding' command displays the IP forwarding data\n"
	  "base. The command generates a table with the following columns:\n"
	  "\n"
	  "  DESTINATION destination address and prefix\n"
	  "  NEXT-HOP    next hop towards the destination\n"
	  "  TOS         type of service selector\n"
	  "  TYPE        type (direct/indirect) of the entry\n"
	  "  PROTO       protocol which created the entry\n"
	  "  INTERFACE   interface used for forwarding",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_ip_forwarding },
	
	{ "show ip addresses", NULL,
	  "The `show ip addresses' command displays the IP addresses\n"
	  "assigned to network interfaces. The command generates a table\n"
	  "with the following columns:\n"
	  "\n"
	  "  ADDRESS     IP address\n"
	  "  PREFIX      IP address prefix length\n"
	  "  NAME        name of the IP address\n"
	  "  INTERFACE   network interface number\n"
	  "  DESCRIPTION description of the network interface",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "ip", NULL,
	  show_ip_addresses },
	
	{ "show ip tunnel", NULL,
	  "The `show ip tunnel' command displays information about existing\n"
	  "IP tunnels.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_ip_tunnel },
	
	{ "show ip mapping", NULL,
	  "The `show ip mapping' command displays the mapping of IP address\n"
	  "to lower layer address (e.g., IEEE 802 addresses). The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  INTERFACE network interface number\n"
	  "  STATUS    status of the mapping entry\n"
	  "  ADDRESS   IP address\n"
	  "  ADDRESS   lower layer address",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_ip_mapping },

	{ "create ip mapping", "<interface> <ip> <mac>",
	  "The `create ip mapping' command creates a mapping of an IP\n"
	  "address to a lower layer address (e.g., IEEE 802 addresses).",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  create_ip_mapping },
	
	{ "dump ip", NULL,
	  "The `dump ip' command generates a sequence of scli commands\n"
	  "which can be used to restore the IP configuration.\n",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  dump_ip },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t ip_mode = {
	"ip",
	"The ip scli mode is based on the IP-MIB as published in\n"
	"RFC 2011, the IP-FORWARD-MIB as published in RFC 2096, the\n"
	"IP-TUNNEL-MIB as published in RFC 2667 and the RFC1213-MIB\n"
	"as published in RFC 1213. It provides commands to browse,\n"
	"monitor and configure IP protocol engines.",
	cmds
    };
    
    scli_register_mode(interp, &ip_mode);
}
