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
xml_tcp_listener(GString *s, tcp_mib_tcpConnEntry_t *tcpConnEntry, int width)
{
    g_string_sprintfa(s, "  <listener address=\"%s\" port=\"%s\"/>\n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
				       SCLI_FMT_ADDR),
		      fmt_udp_port(tcpConnEntry->tcpConnLocalPort,
				   SCLI_FMT_ADDR));
}



static void
show_tcp_listener(GString *s, tcp_mib_tcpConnEntry_t *tcpConnEntry, int width)
{
    int pos;
    
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
				       SCLI_FMT_NAME_OR_ADDR),
		      fmt_tcp_port(tcpConnEntry->tcpConnLocalPort,
				   SCLI_FMT_NAME_OR_ADDR),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(width-pos+1, 1), "");
    if (tcpConnEntry->tcpConnState) {
	fmt_enum(s, 1, tcp_mib_enums_tcpConnState,
		 tcpConnEntry->tcpConnState);
    }
    g_string_append(s, "\n");
}



static int
cmd_tcp_listener(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    int width = 20;
    char *addr, *port;
    int i, len, cnt;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable)) {
	return SCLI_ERROR;
    }

    if (tcpConnTable) {
	for (i = 0, cnt = 0; tcpConnTable[i]; i++) {
	    if (tcpConnTable[i]->tcpConnState
		&& (*tcpConnTable[i]->tcpConnState
		    != TCP_MIB_TCPCONNSTATE_LISTEN)) {
		continue;
	    }
	    cnt++;
	    addr = fmt_ipv4_address(tcpConnTable[i]->tcpConnLocalAddress,
				    SCLI_FMT_NAME_OR_ADDR);
	    port = fmt_tcp_port(tcpConnTable[i]->tcpConnLocalPort,
				SCLI_FMT_NAME_OR_ADDR);
	    len = strlen(addr) + strlen(port) + 1;
	    if (len > width) {
		width = len;
	    }
	}
	if (cnt) {
	    if (scli_interp_xml(interp)) {
		g_string_append(interp->result, "<tcp>\n");
	    } else {
		g_string_sprintfa(interp->result, "%-*s %s\n",
				  width, "Local Address", "State");
	    }
	    for (i = 0; tcpConnTable[i]; i++) {
		if (tcpConnTable[i]->tcpConnState
		    && (*tcpConnTable[i]->tcpConnState
			== TCP_MIB_TCPCONNSTATE_LISTEN)) {
		    if (scli_interp_xml(interp)) {
			xml_tcp_listener(interp->result,
					 tcpConnTable[i], width);
		    } else {
			show_tcp_listener(interp->result,
					  tcpConnTable[i], width);
		    }
		}
	    }
	    if (scli_interp_xml(interp)) {
		g_string_append(interp->result, "</tcp>\n");
	    }
	}
    }

    if (tcpConnTable) tcp_mib_free_tcpConnTable(tcpConnTable);
    return SCLI_OK;
}



static void
xml_tcp_connection(GString *s, tcp_mib_tcpConnEntry_t *tcpConnEntry,
		   int local_width, int remote_width)
{
    g_string_sprintfa(s, "  <connection src=\"%s:%s\"",
		      fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
				       SCLI_FMT_ADDR),
		      fmt_tcp_port(tcpConnEntry->tcpConnLocalPort,
				   SCLI_FMT_ADDR));
    g_string_sprintfa(s, " dst=\"%s:%s:\" state=\"",
		      fmt_ipv4_address(tcpConnEntry->tcpConnRemAddress,
				       SCLI_FMT_ADDR),
		      fmt_tcp_port(tcpConnEntry->tcpConnRemPort,
				   SCLI_FMT_ADDR));
    fmt_enum(s, 1, tcp_mib_enums_tcpConnState,
	     tcpConnEntry->tcpConnState);
    g_string_append(s, "\"/>\n");
}



static void
show_tcp_connection(GString *s, tcp_mib_tcpConnEntry_t *tcpConnEntry,
		    int local_width, int remote_width)
{
    int pos;
    
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
				       SCLI_FMT_NAME_OR_ADDR),
		      fmt_tcp_port(tcpConnEntry->tcpConnLocalPort,
				   SCLI_FMT_NAME_OR_ADDR),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(local_width-pos+1, 1), "");
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnRemAddress,
				       SCLI_FMT_NAME_OR_ADDR),
		      fmt_tcp_port(tcpConnEntry->tcpConnRemPort,
				   SCLI_FMT_NAME_OR_ADDR),
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
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    int local_width = 20;
    int remote_width = 20;
    char *addr, *port;
    int i, len, cnt;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable)) {
	return SCLI_ERROR;
    }

    if (tcpConnTable) {
	for (i = 0, cnt = 0; tcpConnTable[i]; i++) {
	    if (tcpConnTable[i]->tcpConnState
		&& (*tcpConnTable[i]->tcpConnState
		    == TCP_MIB_TCPCONNSTATE_LISTEN)) {
		continue;
	    }
	    cnt++;
	    addr = fmt_ipv4_address(tcpConnTable[i]->tcpConnLocalAddress,
				    SCLI_FMT_NAME_OR_ADDR);
	    port = fmt_tcp_port(tcpConnTable[i]->tcpConnLocalPort,
				SCLI_FMT_NAME_OR_ADDR);
	    len = strlen(addr) + strlen(port) + 1;
	    if (len > local_width) {
		local_width = len;
	    }
	    addr = fmt_ipv4_address(tcpConnTable[i]->tcpConnRemAddress,
				    SCLI_FMT_NAME_OR_ADDR);
	    port = fmt_tcp_port(tcpConnTable[i]->tcpConnRemPort,
				SCLI_FMT_NAME_OR_ADDR);
	    len = strlen(addr) + strlen(port) + 1;
	    if (len > remote_width) {
		remote_width = len;
	    }
	}
	if (cnt) {
	    if (scli_interp_xml(interp)) {
		g_string_append(interp->result, "<tcp>\n");
	    } else {
		g_string_sprintfa(interp->result, "%-*s %-*s %s\n",
				  local_width, "Local Address",
				  remote_width, "Remote Address", "State");
	    }
	    for (i = 0; tcpConnTable[i]; i++) {
		if (tcpConnTable[i]->tcpConnState
		    && (*tcpConnTable[i]->tcpConnState
			!= TCP_MIB_TCPCONNSTATE_LISTEN)) {
		    if (scli_interp_xml(interp)) {
			xml_tcp_connection(interp->result, tcpConnTable[i],
					   local_width, remote_width);
		    } else {
			show_tcp_connection(interp->result, tcpConnTable[i],
					    local_width, remote_width);
		    }
		}
	    }
	    if (scli_interp_xml(interp)) {
		g_string_append(interp->result, "</tcp>\n");
	    }
	}
    }

    if (tcpConnTable) tcp_mib_free_tcpConnTable(tcpConnTable);
    return SCLI_OK;
}



void
scli_init_tcp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show tcp listener",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "existing tcp listener",
	  cmd_tcp_listener },
	{ "show tcp connections",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "existing tcp connections",
	  cmd_tcp_connections },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t tcp_mode = {
	"tcp",
	"scli mode to display and configure TCP parameters",
	cmds
    };
    
    scli_register_mode(interp, &tcp_mode);
}
