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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "scli.h"

#include "ip-mib.h"
#include "ip-forward-mib.h"
#include "tunnel-mib.h"
#include "if-mib.h"
#include "rfc1213-mib.h"



static void
show_ip_forward(GString *s, ipCidrRouteEntry_t *ipCidrRouteEntry)
{
#if 0    
    int pos;
    
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress, 1),
		      fmt_port(tcpConnEntry->tcpConnLocalPort, 1),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(32-pos, 1), "");
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnRemAddress, 1),
		      fmt_port(tcpConnEntry->tcpConnRemPort, 1),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(32-pos, 1), "");
    if (tcpConnEntry->tcpConnState) {
	fmt_enum(s, 1, tcp_mib_enums_tcpConnState,
		 tcpConnEntry->tcpConnState);
    }
#endif
    g_string_append(s, "\n");
}



static void
show_ip_route(GString *s, rfc1213_mib_ipRouteEntry_t *ipRouteEntry,
	      ifXEntry_t **ifXTable, ifEntry_t **ifTable)
{
    int i, pos;
    
    if (ipRouteEntry->ipRouteDest
	&& ipRouteEntry->ipRouteNextHop
	&& ipRouteEntry->ipRouteMask
	&& ipRouteEntry->ipRouteIfIndex) {
	g_string_sprintfa(s, "%s%s%n",
			  fmt_ipv4_address(ipRouteEntry->ipRouteDest, 0),
			  fmt_ipv4_mask(ipRouteEntry->ipRouteMask), &pos);
	g_string_sprintfa(s, "%*s", MAX(20-pos, 1), "");
	
	g_string_sprintfa(s, "%-20s",
			  fmt_ipv4_address(ipRouteEntry->ipRouteNextHop, 0));

	g_string_sprintfa(s, "%d", *ipRouteEntry->ipRouteIfIndex);

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
    ipCidrRouteEntry_t **ipCidrRouteTable = NULL;
    rfc1213_mib_ipRouteEntry_t **ipRouteTable = NULL;
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

#if 0
    if (ip_forward_mib_get_ipCidrRouteTable(interp->peer, &ipCidrRouteTable)) {
	return SCLI_ERROR;
    }
#endif

    if (!ipCidrRouteTable) {
	if (rfc1213_mib_get_ipRouteTable(interp->peer, &ipRouteTable)) {
	    return SCLI_ERROR;
	}
    }

    (void) if_mib_get_ifTable(interp->peer, &ifTable);
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    if (ipCidrRouteTable || ipRouteTable) {
	g_string_sprintfa(interp->result, "%-20s%-20s%s\n",
			  "Destination", "Next Hop", "Interface");
	if (ipCidrRouteTable) {
	    for (i = 0; ipCidrRouteTable[i]; i++) {
		show_ip_forward(interp->result, ipCidrRouteTable[i]);
	    }
	}
	if (ipRouteTable) {
	    for (i = 0; ipRouteTable[i]; i++) {
		show_ip_route(interp->result, ipRouteTable[i],
			      ifXTable, ifTable);
	    }
	}
    }

    if (ipCidrRouteTable)
	ip_forward_mib_free_ipCidrRouteTable(ipCidrRouteTable);
    if (ipRouteTable)
	rfc1213_mib_free_ipRouteTable(ipRouteTable);

    return SCLI_OK;
}



static void
show_ip_address(GString *s, ipAddrEntry_t *ipAddrEntry)
{
    unsigned prefix = 0;
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
		      fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, 0));
    if (ipAddrEntry->ipAdEntNetMask) {
	g_string_sprintfa(s, "%-6s",
			  fmt_ipv4_mask(ipAddrEntry->ipAdEntNetMask));;
    } else {
	g_string_sprintfa(s, "%-6s", "");
    }
    g_string_sprintfa(s, "%s",
		      fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, 1));
    g_string_append(s, "\n");
}



static int
cmd_ip_addresses(scli_interp_t *interp, int argc, char **argv)
{
    ipAddrEntry_t **ipAddrTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable)) {
	return SCLI_ERROR;
    }

    if (ipAddrTable) {
	g_string_sprintfa(interp->result,
			  "Interface IP Address     Prefix  Name\n");
	for (i = 0; ipAddrTable[i]; i++) {
	    show_ip_address(interp->result, ipAddrTable[i]);
	}
	ip_mib_free_ipAddrTable(ipAddrTable);
    }
    return SCLI_OK;
}



static void
show_ip_tunnel(GString *s, tunnelIfEntry_t *tunnelIfEntry,
	       ifXEntry_t **ifXTable, ifEntry_t **ifTable)
{
    int i;

    g_return_if_fail(tunnelIfEntry);

    if (tunnelIfEntry->tunnelIfLocalAddress) {
	g_string_sprintfa(s, "%-15s  ",
		  fmt_ipv4_address(tunnelIfEntry->tunnelIfLocalAddress, 0));
    } else {
	g_string_sprintfa(s, "%-15s  ", "-");
    }

    if (tunnelIfEntry->tunnelIfRemoteAddress) {
	g_string_sprintfa(s, "%-15s  ",
		  fmt_ipv4_address(tunnelIfEntry->tunnelIfRemoteAddress, 0));
    } else {
	g_string_sprintfa(s, "%-15s  ", "-");
    }

    if (tunnelIfEntry->tunnelIfEncapsMethod) {
	fmt_enum(s, 8, tunnel_mib_enums_tunnelIfEncapsMethod,
		 tunnelIfEntry->tunnelIfEncapsMethod);
    } else {
	g_string_sprintfa(s, "%-6s  ", "-");
    }

    if (tunnelIfEntry->tunnelIfSecurity) {
	fmt_enum(s, 6, tunnel_mib_enums_tunnelIfSecurity,
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
    tunnelIfEntry_t **tunnelIfTable = NULL;
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (tunnel_mib_get_tunnelIfTable(interp->peer, &tunnelIfTable)) {
	return SCLI_ERROR;
    }

    (void) if_mib_get_ifTable(interp->peer, &ifTable);
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    
    if (tunnelIfTable) {

	g_string_append(interp->result,
	"Local Address    Remote Address   Type    Sec.  TTL TOS Interface\n");
	for (i = 0; tunnelIfTable[i]; i++) {
	    show_ip_tunnel(interp->result, tunnelIfTable[i], ifXTable, ifTable);
	}
    }

    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (tunnelIfTable) tunnel_mib_free_tunnelIfTable(tunnelIfTable);

    return SCLI_OK;
}



static void
show_ip_arp(GString *s, ipNetToMediaEntry_t *ipNetToMediaEntry)
{
    int i;

    g_string_sprintfa(s, "%6u    ",
		      ipNetToMediaEntry->ipNetToMediaIfIndex);
    
    fmt_enum(s, 8, ip_mib_enums_ipNetToMediaType,
	     ipNetToMediaEntry->ipNetToMediaType);
    
    g_string_sprintfa(s, " %-16s ",
	      fmt_ipv4_address(ipNetToMediaEntry->ipNetToMediaNetAddress, 0));

    if (ipNetToMediaEntry->ipNetToMediaPhysAddress) {
	for (i = 0;
	     i < ipNetToMediaEntry->_ipNetToMediaPhysAddressLength; i++) {
	    g_string_sprintfa(s, "%s%02x", i ? ":" : "",
			      ipNetToMediaEntry->ipNetToMediaPhysAddress[i]);
	}
    }
    
    g_string_append(s, "\n");
}



static int
cmd_ip_media_mapping(scli_interp_t *interp, int argc, char **argv)
{
    ipNetToMediaEntry_t **ipNetToMediaTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (ip_mib_get_ipNetToMediaTable(interp->peer, &ipNetToMediaTable)) {
	return SCLI_ERROR;
    }

    if (ipNetToMediaTable) {
	g_string_append(interp->result,
	"Interface Type     IP Address       Physical Address\n");
	for (i = 0; ipNetToMediaTable[i]; i++) {
	    show_ip_arp(interp->result, ipNetToMediaTable[i]);
	}
    }


    if (ipNetToMediaTable) ip_mib_free_ipNetToMediaTable(ipNetToMediaTable);
    
    return SCLI_OK;
}



void
scli_init_ip_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show ip forwarding",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "IP forwarding table",
	  cmd_ip_forwarding },
	{ "show ip addresses",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "list of assigned IP addresses",
	  cmd_ip_addresses },
	{ "show ip tunnel",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "list of IP tunnels",
	  cmd_ip_tunnel },
	{ "show ip mapping",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "list of IP to media mappings",
	  cmd_ip_media_mapping },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t ip_mode = {
	"ip",
	"scli mode to display and configure IP parameters",
	cmds
    };
    
    scli_register_mode(interp, &ip_mode);
}
