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
    int j;
    
    for (j = 0; j < 4; j++) {
	g_string_sprintfa(s, "%s%d", j ? "." : "",
			  tcpConnEntry->tcpConnLocalAddress[j]);
    }
    g_string_sprintfa(s, ":%d",
		      tcpConnEntry->tcpConnLocalPort);
    g_string_append(s, "\t\t");
    for (j = 0; j < 4; j++) {
	g_string_sprintfa(s, "%s%d", j ? "." : "",
			  tcpConnEntry->tcpConnRemAddress[j]);
    }
    g_string_sprintfa(s, ":%d\t\t",
		      tcpConnEntry->tcpConnRemPort);
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
	g_string_append(interp->result,
			"Local Address\t\tRemote Address\t\tState\n");
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
	"interface",
	"scli mode to display and configure tcp parameters",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &tcp_mode);
}
