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

#include "stools.h"
#include "scli.h"


static void
show_tcp_connection(GString *s, tcpConnEntry_t *tcpConnEntry)
{
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
    g_string_append(s, "\n");
}



static int
cmd_tcp_connections(scli_interp_t *interp, int argc, char **argv)
{
    tcpConnEntry_t **tcpConnEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (tcp_mib_get_tcpConnEntry(interp->peer, &tcpConnEntry)) {
	return SCLI_ERROR;
    }

    if (tcpConnEntry) {
	g_string_sprintfa(interp->result, "%-32s%-32s%s\n",
			  "Local Address", "Remote Address", "State");
	for (i = 0; tcpConnEntry[i]; i++) {
	    show_tcp_connection(interp->result, tcpConnEntry[i]);
	}
	tcp_mib_free_tcpConnEntry(tcpConnEntry);
    }
    return SCLI_OK;
}



void
scli_init_tcp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "tcp", NULL, NULL },
	{ "show tcp", "connections",
	  "show existing tcp connections",
	  cmd_tcp_connections },
	{ NULL, NULL, NULL, NULL }
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
