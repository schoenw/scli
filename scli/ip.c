/* 
 * ip.c -- scli ip mode implementation
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

#include "ip-mib.h"
#include "ip-forward-mib.h"
#include "tunnel-mib.h"
#include "if-mib.h"
#include "rfc1213-mib.h"



static void
show_ip_forward(GString *s,
		ip_forward_mib_ipCidrRouteEntry_t *ipCidrRouteEntry)
{
    g_string_append(s, "\n");
}



static void
show_ip_route(GString *s,
	      rfc1213_mib_ipRouteEntry_t *ipRouteEntry,
	      if_mib_ifXEntry_t **ifXTable,
	      if_mib_ifEntry_t **ifTable)
{
    const char *label;
    int i, pos;
    
    if (ipRouteEntry->ipRouteDest
	&& ipRouteEntry->ipRouteNextHop
	&& ipRouteEntry->ipRouteMask
	&& ipRouteEntry->ipRouteIfIndex) {
	g_string_sprintfa(s, "%s%s%n",
			  fmt_ipv4_address(ipRouteEntry->ipRouteDest,
					   SCLI_FMT_ADDR),
			  fmt_ipv4_mask(ipRouteEntry->ipRouteMask), &pos);
	g_string_sprintfa(s, "%*s", MAX(20-pos, 1), "");
	
	g_string_sprintfa(s, "%-16s",
			  fmt_ipv4_address(ipRouteEntry->ipRouteNextHop,
					   SCLI_FMT_ADDR));

	label = NULL;
	if (ipRouteEntry->ipRouteType) {
	    label = gsnmp_enum_get_label(rfc1213_mib_enums_ipRouteType,
					 *ipRouteEntry->ipRouteType);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	label = NULL;
	if (ipRouteEntry->ipRouteProto) {
	    label = gsnmp_enum_get_label(rfc1213_mib_enums_ipRouteProto,
					*ipRouteEntry->ipRouteProto);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	g_string_sprintfa(s, "%2d", *ipRouteEntry->ipRouteIfIndex);

	if (ifXTable) {
	    for (i = 0; ifXTable[i]; i++) {
		if(ifXTable[i]->ifIndex == *ipRouteEntry->ipRouteIfIndex) {
		    g_string_sprintfa(s, " (%.*s)",
				      (int) ifXTable[i]->_ifNameLength,
				      ifXTable[i]->ifName);
		    break;
		}
	    }
	} else if (ifTable) {
	    for (i = 0; ifTable[i]; i++) {
		if(ifTable[i]->ifIndex == *ipRouteEntry->ipRouteIfIndex) {
		    g_string_sprintfa(s, " (%.*s)",
				      (int) ifTable[i]->_ifDescrLength,
				      ifTable[i]->ifDescr);
		    break;
		}
	    }
	}
	g_string_append(s, "\n");
    }
}



static int
cmd_ip_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    ip_forward_mib_ipCidrRouteEntry_t **ipCidrRouteTable = NULL;
    rfc1213_mib_ipRouteEntry_t **ipRouteTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (ip_forward_mib_get_ipCidrRouteTable(interp->peer, &ipCidrRouteTable)) {
	if (rfc1213_mib_get_ipRouteTable(interp->peer, &ipRouteTable)) {
	    return SCLI_ERROR;
	}
    }

    (void) if_mib_get_ifTable(interp->peer, &ifTable);
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    if (ipCidrRouteTable || ipRouteTable) {
	g_string_sprintfa(interp->header, "%-20s%-16s%-10s%-10s%s",
		  "DESTINATION", "NEXT HOP", "TYPE", "PROTO", "INTERFACE");
	if (ipCidrRouteTable) {
	    for (i = 0; ipCidrRouteTable[i]; i++) {
		show_ip_forward(interp->result, ipCidrRouteTable[i]);
	    }
	}
	if (! ipCidrRouteTable && ipRouteTable) {
	    for (i = 0; ipRouteTable[i]; i++) {
		show_ip_route(interp->result, ipRouteTable[i],
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
show_ip_address(GString *s, ip_mib_ipAddrEntry_t *ipAddrEntry)
{
    unsigned prefix = 0;
    char *name;
    int i, j;

    if (ipAddrEntry->ipAdEntNetMask) {
	for (i = 0; i < 4; i++) {
	    for (j = 0; j < 8; j++) {
		if ((1 << (7-j)) & (ipAddrEntry->ipAdEntNetMask)[i]) {
		    prefix++;
		} else {
		    i = 4;
		    break;
		}
	    }
	}
    }
	      
    if (ipAddrEntry->ipAdEntIfIndex) {
	g_string_sprintfa(s, "%6u    ", *(ipAddrEntry->ipAdEntIfIndex));
    } else {
	g_string_sprintfa(s, "%6s    ", "");
    }
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_ADDR));
    if (ipAddrEntry->ipAdEntNetMask) {
	g_string_sprintfa(s, "%-6s",
			  fmt_ipv4_mask(ipAddrEntry->ipAdEntNetMask));;
    } else {
	g_string_sprintfa(s, "%-6s", "");
    }
    name = fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_NAME);
    if (name) {
	g_string_append(s, name);
    }
    g_string_append(s, "\n");
}



static int
cmd_ip_addresses(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ipAddrEntry_t **ipAddrTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable)) {
	return SCLI_ERROR;
    }

    if (ipAddrTable) {
	g_string_sprintfa(interp->header,
			  "INTERFACE IP-ADDRESS     PREFIX  NAME");
	for (i = 0; ipAddrTable[i]; i++) {
	    show_ip_address(interp->result, ipAddrTable[i]);
	}
	ip_mib_free_ipAddrTable(ipAddrTable);
    }
    return SCLI_OK;
}



static void
show_ip_tunnel(GString *s,
	       tunnel_mib_tunnelIfEntry_t *tunnelIfEntry,
	       if_mib_ifXEntry_t **ifXTable,
	       if_mib_ifEntry_t **ifTable)
{
    int i;

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

    if (tunnelIfEntry->tunnelIfEncapsMethod) {
	xxx_enum(s, 8, tunnel_mib_enums_tunnelIfEncapsMethod,
		 tunnelIfEntry->tunnelIfEncapsMethod);
    } else {
	g_string_sprintfa(s, "%-6s  ", "-");
    }

    if (tunnelIfEntry->tunnelIfSecurity) {
	xxx_enum(s, 6, tunnel_mib_enums_tunnelIfSecurity,
		 tunnelIfEntry->tunnelIfSecurity);
    } else {
	g_string_sprintfa(s, "%-4s  ", "-");
    }

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
cmd_ip_tunnel(scli_interp_t *interp, int argc, char **argv)
{
    tunnel_mib_tunnelIfEntry_t **tunnelIfTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (tunnel_mib_get_tunnelIfTable(interp->peer, &tunnelIfTable)) {
	return SCLI_ERROR;
    }

    (void) if_mib_get_ifTable(interp->peer, &ifTable);
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    
    if (tunnelIfTable) {
	g_string_append(interp->header,
	"LOCAL ADDRESS    REMOTE ADDRESS   TYPE    SEC.  TTL TOS INTERFACE");
	for (i = 0; tunnelIfTable[i]; i++) {
	    show_ip_tunnel(interp->result, tunnelIfTable[i],
			   ifXTable, ifTable);
	}
    }

    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (tunnelIfTable) tunnel_mib_free_tunnelIfTable(tunnelIfTable);

    return SCLI_OK;
}



static void
show_ip_arp(GString *s,
	    ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry,
	    if_mib_ifEntry_t *ifEntry)
{
    char *name;
    int i;

    g_string_sprintfa(s, "%6u    ",
		      ipNetToMediaEntry->ipNetToMediaIfIndex);
    
    xxx_enum(s, 8, ip_mib_enums_ipNetToMediaType,
	     ipNetToMediaEntry->ipNetToMediaType);
    
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
	    && (*ifEntry->ifType == IF_MIB_IFTYPE_ETHERNETCSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_ISO88023CSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_STARLAN
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHER
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHERFX
		|| *ifEntry->ifType == IF_MIB_IFTYPE_GIGABITETHERNET)) {
	    name = fmt_ether_address(ipNetToMediaEntry->ipNetToMediaPhysAddress, SCLI_FMT_NAME);
	    if (name) {
		g_string_sprintfa(s, " (%s)", name);
	    }
	}
    }
    
    g_string_append(s, "\n");
}



static int
cmd_ip_media_mapping(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ipNetToMediaEntry_t **ipNetToMediaTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL, *ifEntry = NULL;
    int i, j;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (ip_mib_get_ipNetToMediaTable(interp->peer, &ipNetToMediaTable)) {
	return SCLI_ERROR;
    }

    (void) if_mib_get_ifTable(interp->peer, &ifTable);

    if (ipNetToMediaTable) {
	g_string_append(interp->header,
		"INTERFACE TYPE     IP-ADDRESS       LOWER LAYER ADDRESS");
	for (i = 0; ipNetToMediaTable[i]; i++) {
	    if (ifTable) {
		for (j = 0; ifTable[j]; j++) {
		    if (ipNetToMediaTable[i]->ipNetToMediaIfIndex
			== ifTable[j]->ifIndex) break;
		}
		ifEntry = ifTable[j];
	    }
	    show_ip_arp(interp->result, ipNetToMediaTable[i], ifEntry);
	}
    }


    if (ipNetToMediaTable) ip_mib_free_ipNetToMediaTable(ipNetToMediaTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    
    return SCLI_OK;
}



void
scli_init_ip_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	
	{ "show ip forwarding", NULL,
	  "IP forwarding data base",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_ip_forwarding },
	
	{ "show ip addresses", NULL,
	  "IP addresses assigned to interfaces",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_ip_addresses },
	
	{ "show ip tunnel", NULL,
	  "IP tunnels",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_ip_tunnel },
	
	{ "show ip mapping", NULL,
	  "IP address to lower layer address mappings",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_ip_media_mapping },
	
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t ip_mode = {
	"ip",
	"scli mode to display and configure IP parameters",
	cmds
    };
    
    scli_register_mode(interp, &ip_mode);
}
