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

#include "scli.h"

#include "tcp-mib.h"



static void
xml_tcp_listener(xmlNodePtr root, tcp_mib_tcpConnEntry_t *tcpConnEntry, int width)
{
    xmlNodePtr node;

    node = xmlNewChild(root, NULL, "listener", NULL);
    xmlSetProp(node, "address",
	       fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
				SCLI_FMT_ADDR));
    xmlSetProp(node, "port",
	       fmt_tcp_port(tcpConnEntry->tcpConnLocalPort,
			    SCLI_FMT_ADDR));
}



static void
fmt_tcp_listener(GString *s, tcp_mib_tcpConnEntry_t *tcpConnEntry, int width)
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
	g_string_append(s, fmt_enum(tcp_mib_enums_tcpConnState,
				    tcpConnEntry->tcpConnState));
    }
    g_string_append(s, "\n");
}



static int
show_tcp_listener(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    int width = 20;
    char *addr, *port;
    int i, len, cnt;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
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
	    if (! scli_interp_xml(interp)) {
		g_string_sprintfa(interp->header, "%-*s %s",
				  width, "LOCAL ADDRESS", "STATE");
	    }
	    for (i = 0; tcpConnTable[i]; i++) {
		if (tcpConnTable[i]->tcpConnState
		    && (*tcpConnTable[i]->tcpConnState
			== TCP_MIB_TCPCONNSTATE_LISTEN)) {
		    if (scli_interp_xml(interp)) {
			xml_tcp_listener(interp->xml_node,
					 tcpConnTable[i], width);
		    } else {
			fmt_tcp_listener(interp->result,
					 tcpConnTable[i], width);
		    }
		}
	    }
	}
    }

    if (tcpConnTable) tcp_mib_free_tcpConnTable(tcpConnTable);
    return SCLI_OK;
}



static void
xml_tcp_connection(xmlNodePtr root, tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    xmlNodePtr node;

    node = xmlNewChild(root, NULL, "connection", NULL);
    xmlSetProp(node, "local-address",
	       fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
				SCLI_FMT_ADDR));
    xmlSetProp(node, "local-port",
	       fmt_tcp_port(tcpConnEntry->tcpConnLocalPort,
			    SCLI_FMT_ADDR));
    xmlSetProp(node, "remote-address",
	       fmt_ipv4_address(tcpConnEntry->tcpConnRemAddress,
				SCLI_FMT_ADDR));
    xmlSetProp(node, "remote-port",
	       fmt_tcp_port(tcpConnEntry->tcpConnRemPort,
			    SCLI_FMT_ADDR));

    node = xmlNewChild(node, NULL, "state",
		       fmt_enum(tcp_mib_enums_tcpConnState,
				tcpConnEntry->tcpConnState));
}



static void
fmt_tcp_connection(GString *s, tcp_mib_tcpConnEntry_t *tcpConnEntry,
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
	g_string_append(s, fmt_enum(tcp_mib_enums_tcpConnState,
				    tcpConnEntry->tcpConnState));
    }
    g_string_append(s, "\n");
}



static int
show_tcp_connections(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    int local_width = 20;
    int remote_width = 20;
    char *addr, *port;
    int i, len, cnt;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
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
	    if (! scli_interp_xml(interp)) {
		g_string_sprintfa(interp->header, "%-*s %-*s %s",
				  local_width, "LOCAL ADDRESS",
				  remote_width, "REMOTE ADDRESS", "STATE");
	    }
	    for (i = 0; tcpConnTable[i]; i++) {
		if (tcpConnTable[i]->tcpConnState
		    && (*tcpConnTable[i]->tcpConnState
			!= TCP_MIB_TCPCONNSTATE_LISTEN)) {
		    if (scli_interp_xml(interp)) {
			xml_tcp_connection(interp->xml_node, tcpConnTable[i]);
		    } else {
			fmt_tcp_connection(interp->result, tcpConnTable[i],
					   local_width, remote_width);
		    }
		}
	    }
	}
    }

    if (tcpConnTable) tcp_mib_free_tcpConnTable(tcpConnTable);
    return SCLI_OK;
}



typedef struct tcp_state {
    guint16 port;
    gchar  *name;
    guint32 count;
} tcp_state_t;



static void
fmt_tcp_state(GString *s, gint32 state , guint32 count, GSList *ports)
{
    const char *e;
    GSList *elem;
    gint len;

    e = fmt_enum(tcp_mib_enums_tcpConnState, &state);
    if (e) {
	g_string_sprintfa(s, "%-12s%5u ", e, count);
	len = 12 + 5 + 1;
	for (elem = ports; elem; elem = g_slist_next(elem)) {
	    tcp_state_t *t = (tcp_state_t *) elem->data;
	    if (t->count > 1) {
		g_string_sprintfa(s, "%s/%u ", t->name, t->count);
		len += strlen(t->name) + 2 + 4;
	    } else {
		g_string_sprintfa(s, "%s ", t->name);
		len += strlen(t->name) + 1;
	    }
	    if (len > 70) {
		g_string_sprintfa(s, "\n%17s ", "");
		len = 12 + 5 + 1;
	    }
	}
	g_string_sprintfa(s, "\n");
    }
}



static int
show_tcp_states(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    int i, t;

    const gint32 tcp_states[] = { TCP_MIB_TCPCONNSTATE_CLOSED,
				  TCP_MIB_TCPCONNSTATE_LISTEN,
				  TCP_MIB_TCPCONNSTATE_SYNSENT,
				  TCP_MIB_TCPCONNSTATE_SYNRECEIVED,
				  TCP_MIB_TCPCONNSTATE_ESTABLISHED,
				  TCP_MIB_TCPCONNSTATE_FINWAIT1,
				  TCP_MIB_TCPCONNSTATE_FINWAIT2,
				  TCP_MIB_TCPCONNSTATE_CLOSEWAIT,
				  TCP_MIB_TCPCONNSTATE_LASTACK,
				  TCP_MIB_TCPCONNSTATE_CLOSING,
				  TCP_MIB_TCPCONNSTATE_TIMEWAIT };
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (tcpConnTable) {
	g_string_sprintfa(interp->header, "STATE       COUNT PORTS");

	for (t = 0; t < sizeof(tcp_states) / sizeof(gint32); t++) {

	    gint32 s = tcp_states[t];
	    gint32 c = 0;
	    const char *name;
	    guint16 port;
	    GSList *list = NULL, *elem;
	    tcp_state_t *p;
		
	    for (i = 0; tcpConnTable[i]; i++) {
		if (! tcpConnTable[i]->tcpConnState
		    || *tcpConnTable[i]->tcpConnState != s) {
		    continue;
		}
		c++;
		port = tcpConnTable[i]->tcpConnLocalPort;
		name = fmt_tcp_port(port, SCLI_FMT_NAME);
		if (! name && *tcpConnTable[i]->tcpConnState
		    != TCP_MIB_TCPCONNSTATE_LISTEN) {
		    port = tcpConnTable[i]->tcpConnRemPort;
		    name = fmt_tcp_port(port, SCLI_FMT_NAME);
		}
		if (! name) {
		    name = "other";
		}

		for (elem = list; elem; elem = g_slist_next(elem)) {
		    tcp_state_t *t = (tcp_state_t *) elem->data;
		    if (strcmp(t->name, name) == 0) {
			break;
		    }
		}
		if (! elem) {
		    p = g_new0(tcp_state_t, 1);
		    p->name = g_strdup(name);
		    p->port = port;
		    list = g_slist_append(list, p);
		} else {
		    p = (tcp_state_t *) elem->data;
		}
		p->count++;
	    }
	    fmt_tcp_state(interp->result, s, c, list);
	    for (elem = list; elem; elem = g_slist_next(elem)) {
		tcp_state_t *t = (tcp_state_t *) elem->data;
		g_free(t->name);
		g_free(t);
	    }
	    g_slist_free_1(list);
	}
    }

    if (tcpConnTable) tcp_mib_free_tcpConnTable(tcpConnTable);
    return SCLI_OK;
}



void
scli_init_tcp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show tcp listener", NULL,
	  "The `show tcp listener' command displays the listening TCP\n"
	  "endpoints.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "tcp", NULL,
	  show_tcp_listener },

	{ "show tcp connections", NULL,
	  "The `show tcp connections' command displays the connected TCP\n"
	  "endpoints including the current state of the connection as seen\n"
	  "by the remote SNMP agent.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "tcp", NULL,
	  show_tcp_connections },

	{ "show tcp states", NULL,
	  "The `show tcp states' command displays the distribution of TCP\n"
	  "connection states together with a list of known port names in\n"
           "each state.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "tcp", NULL,
	  show_tcp_states },

	{ "monitor tcp connections", NULL,
	  "The `monitor tcp connections' command displays the connected TCP\n"
	  "endpoints including the current state of the connection as seen\n"
	  "by the remote SNMP agent. The information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_tcp_connections },

	{ "monitor tcp states", NULL,
	  "The `monitor tcp states' command displays the distribution of TCP\n"
	  "connection states. The information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_tcp_states },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t tcp_mode = {
	"tcp",
	"The scli tcp mode is based on the TCP-MIB as published in\n"
	"RFC 2012. It provides commands to browse information specific\n"
	"to the TCP transport protocol.",
	cmds
    };
    
    scli_register_mode(interp, &tcp_mode);
}
