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

#include "stools.h"
#include "scli.h"


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



static int
cmd_ip_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    ipCidrRouteEntry_t **ipCidrRouteEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (ip_forward_mib_get_ipCidrRouteEntry(interp->peer, &ipCidrRouteEntry)) {
	return SCLI_ERROR;
    }

    if (ipCidrRouteEntry) {
	g_string_sprintfa(interp->result, "%-32s%-32s%s\n",
			  "Destination", "Next Hop", "Interface");
	for (i = 0; ipCidrRouteEntry[i]; i++) {
	    show_ip_forward(interp->result, ipCidrRouteEntry[i]);
	}
	ip_forward_mib_free_ipCidrRouteEntry(ipCidrRouteEntry);
    }
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
	      
    g_string_sprintfa(s, "%-16s ",
		      fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, 0));
    if (ipAddrEntry->ipAdEntNetMask) {
	g_string_sprintfa(s, "%-6s",
			  fmt_ipv4_mask(ipAddrEntry->ipAdEntNetMask));;
    } else {
	g_string_sprintfa(s, "%-6s", "");
    }
    if (ipAddrEntry->ipAdEntIfIndex) {
	g_string_sprintfa(s, "%6u      ", *(ipAddrEntry->ipAdEntIfIndex));
    } else {
	g_string_sprintfa(s, "%6s      ", "");
    }
    g_string_sprintfa(s, "%s",
		      fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, 1));
    g_string_append(s, "\n");
}



static int
cmd_ip_addresses(scli_interp_t *interp, int argc, char **argv)
{
    ipAddrEntry_t **ipAddrEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (ip_mib_get_ipAddrEntry(interp->peer, &ipAddrEntry)) {
	return SCLI_ERROR;
    }

    if (ipAddrEntry) {
	g_string_sprintfa(interp->result,
			  "Address        Prefix  Interface   Name\n");
	for (i = 0; ipAddrEntry[i]; i++) {
	    show_ip_address(interp->result, ipAddrEntry[i]);
	}
	ip_mib_free_ipAddrEntry(ipAddrEntry);
    }
    return SCLI_OK;
}



void
scli_init_ip_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "ip", NULL, NULL },
	{ "show ip", "forwarding",
	  "show current IP forwarding table",
	  cmd_ip_forwarding },
	{ "show ip", "addresses",
	  "show list of assigned IP addresses",
	  cmd_ip_addresses },
	{ NULL, NULL, NULL, NULL }
    };
    
    static scli_mode_t ip_mode = {
	"ip",
	"scli mode to display and configure IP parameters",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &ip_mode);
}
