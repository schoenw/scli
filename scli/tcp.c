/* 
 * tcp.c -- scli tcp mode implementation
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

#include "tcp-mib.h"


static void
show_tcp_connection(GString *s, tcpConnEntry_t *tcpConnEntry,
		    int local_width, int remote_width)
{
    int pos;
    
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress, 1),
		      fmt_port(tcpConnEntry->tcpConnLocalPort, 1),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(local_width-pos+1, 1), "");
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnRemAddress, 1),
		      fmt_port(tcpConnEntry->tcpConnRemPort, 1),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(remote_width-pos+1, 1), "");
    if (tcpConnEntry->tcpConnState) {
	fmt_enum(s, 1, tcp_mib_enums_tcpConnState,
		 tcpConnEntry->tcpConnState);
    }
    g_string_append(s, "\n");
}



static int
cmd_tcp_connections(scli_interp_t *interp, int argc, char **argv)
{
    tcpConnEntry_t **tcpConnTable = NULL;
    int local_width = 20;
    int remote_width = 20;
    char *addr, *port;
    int i, len;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable)) {
	return SCLI_ERROR;
    }

    if (tcpConnTable) {
	for (i = 0; tcpConnTable[i]; i++) {
	    addr = fmt_ipv4_address(tcpConnTable[i]->tcpConnLocalAddress, 1);
	    port = fmt_port(tcpConnTable[i]->tcpConnLocalPort, 1);
	    len = strlen(addr) + strlen(port) + 1;
	    if (len > local_width) {
		local_width = len;
	    }
	    addr = fmt_ipv4_address(tcpConnTable[i]->tcpConnRemAddress, 1);
	    port = fmt_port(tcpConnTable[i]->tcpConnRemPort, 1);
	    len = strlen(addr) + strlen(port) + 1;
	    if (len > remote_width) {
		remote_width = len;
	    }
	}
	g_string_sprintfa(interp->result, "%-*s %-*s %s\n",
			  local_width, "Local Address",
			  remote_width, "Remote Address",
			  "State");
	for (i = 0; tcpConnTable[i]; i++) {
	    show_tcp_connection(interp->result, tcpConnTable[i],
				local_width, remote_width);
	}
	tcp_mib_free_tcpConnTable(tcpConnTable);
    }
    return SCLI_OK;
}



void
scli_init_tcp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "tcp", 0, NULL, NULL },
	{ "show tcp", "connections", SCLI_CMD_FLAG_NEED_PEER,
	  "show existing tcp connections",
	  cmd_tcp_connections },
	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t tcp_mode = {
	"tcp",
	"scli mode to display and configure TCP parameters",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &tcp_mode);
}
