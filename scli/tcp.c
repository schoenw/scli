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
				  width, "LOCAL", "STATE");
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
				  local_width, "LOCAL",
				  remote_width, "REMOTE", "STATE");
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
    gchar  *name;
    guint16 port;
    guint32 count;
} tcp_state_t;



static tcp_state_t *
tcp_state_new(const gchar *name, const guint16 port)
{
    tcp_state_t *t;
    
    t = g_new0(tcp_state_t, 1);
    t->name = name ? g_strdup(name) : NULL;
    t->port = port;

    return t;
}



static void
tcp_state_free(gpointer data, gpointer user_data)
{
    tcp_state_t *t = (tcp_state_t *) data;

    if (t->name) g_free(t->name);
    g_free(t);
}



static gint
tcp_state_cmp(gconstpointer a, gconstpointer b)
{
    tcp_state_t *state_a = (tcp_state_t *) a;
    tcp_state_t *state_b = (tcp_state_t *) b;

    if (state_a->port < state_b->port) {
	return -1;
    }
    if (state_a->port > state_b->port) {
	return 1;
    }
    return 0;
}



static tcp_state_t *
tcp_state_lookup(GSList **list, const gchar *name, const guint16 port)
{
    GSList *elem;
    tcp_state_t *t = NULL;

    for (elem = *list; elem; elem = g_slist_next(elem)) {
	t = (tcp_state_t *) elem->data;
	if (strcmp(t->name, name) == 0) break;
    }
    
    if (! elem) {
	t = tcp_state_new(name, port);
	*list = g_slist_insert_sorted(*list, t, tcp_state_cmp);
    }
    return t;
}



static void
xml_tcp_state(xmlNodePtr root, gint32 state, guint32 count, GSList *ports)
{
    const char *e;
    GSList *elem;
    xmlNodePtr tree, node;

    e = fmt_enum(tcp_mib_enums_tcpConnState, &state);
    if (! e) return;
		 
    tree = xmlNewChild(root, NULL, "state", NULL);
    xmlSetProp(tree, "name", e);

    for (elem = ports; elem; elem = g_slist_next(elem)) {
	tcp_state_t *t = (tcp_state_t *) elem->data;
	node = xml_new_child(tree, NULL, "service", "%u", t->count);
	xml_set_prop(node, "port", "%d", t->port);
	xml_set_prop(node, "name", "%s", t->name);
    }
}



static void
fmt_tcp_state(GString *s, gint32 state, guint32 count, GSList *ports)
{
    const char *e;
    GSList *elem;
    gint len;

    e = fmt_enum(tcp_mib_enums_tcpConnState, &state);
    if (! e) return;
    
    g_string_sprintfa(s, "%5u %-11s ", count, e);
    len = 12 + 5 + 1;
    for (elem = ports; elem; elem = g_slist_next(elem)) {
	tcp_state_t *t = (tcp_state_t *) elem->data;
	if (t->count > 1) {
	    g_string_sprintfa(s, "%s/%u", t->name, t->count);
	    len += strlen(t->name) + 2 + 4;
	} else {
	    g_string_sprintfa(s, "%s", t->name);
	    len += strlen(t->name) + 1;
	}
	if (elem->next) {
	    if (len > 70) {
		g_string_sprintfa(s, "\n%17s ", "");
		len = 12 + 5 + 1;
	    } else {
		g_string_sprintfa(s, " ");
	    }
	}
    }
    g_string_sprintfa(s, "\n");
}



static int
show_tcp_states(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    int i, j, t;

    const gint32 tcp_states[] = { TCP_MIB_TCPCONNSTATE_LISTEN,
				  TCP_MIB_TCPCONNSTATE_SYNSENT,
				  TCP_MIB_TCPCONNSTATE_SYNRECEIVED,
				  TCP_MIB_TCPCONNSTATE_ESTABLISHED,
				  TCP_MIB_TCPCONNSTATE_FINWAIT1,
				  TCP_MIB_TCPCONNSTATE_FINWAIT2,
				  TCP_MIB_TCPCONNSTATE_CLOSEWAIT,
				  TCP_MIB_TCPCONNSTATE_LASTACK,
				  TCP_MIB_TCPCONNSTATE_CLOSING,
				  TCP_MIB_TCPCONNSTATE_TIMEWAIT,
				  TCP_MIB_TCPCONNSTATE_CLOSED };
    
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
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "COUNT STATE       PORTS");
	}

	for (t = 0; t < sizeof(tcp_states) / sizeof(gint32); t++) {

	    gint32 s = tcp_states[t];
	    gint32 c = 0;
	    const char *name;
	    guint16 port;
	    GSList *list = NULL;
	    tcp_state_t *t;
		
	    for (i = 0; tcpConnTable[i]; i++) {
		if (! tcpConnTable[i]->tcpConnState
		    || *tcpConnTable[i]->tcpConnState != s) {
		    continue;
		}
		c++;
		port = tcpConnTable[i]->tcpConnLocalPort;

		/*
		 * Check if the port is one of the ports we are listening
		 * to. If yes, we assume that it is useful to identify a
		 * certain protocol.
		 */

		for (j = 0; tcpConnTable[j]; j++) {
		    if (tcpConnTable[j]->tcpConnState
			&& (*tcpConnTable[j]->tcpConnState
			    == TCP_MIB_TCPCONNSTATE_LISTEN)
			&& tcpConnTable[j]->tcpConnLocalPort == port) {
			break;
		    }
		}
		if (tcpConnTable[j]) {
		    name = fmt_tcp_port(port, SCLI_FMT_NAME_OR_ADDR);
		} else {
		    name = fmt_tcp_port(port, SCLI_FMT_NAME);
		}
		if (! name && s != TCP_MIB_TCPCONNSTATE_LISTEN) {
		    port = tcpConnTable[i]->tcpConnRemPort;
		    name = fmt_tcp_port(port, SCLI_FMT_NAME);
		}
		if (! name) {
		    name = "-?-";
		    port = 0xffff;
		}

		t = tcp_state_lookup(&list, name, port);
		t->count++;
	    }

	    if (scli_interp_xml(interp)) {
		xml_tcp_state(interp->xml_node, s, c, list);
	    } else {
		fmt_tcp_state(interp->result, s, c, list);
	    }
	    g_slist_foreach(list, tcp_state_free, NULL);
	    g_slist_free(list);
	}
    }

    if (tcpConnTable) tcp_mib_free_tcpConnTable(tcpConnTable);
    return SCLI_OK;
}



static void
xml_tcp_info(xmlNodePtr root, tcp_mib_tcp_t *tcp)
{
    xmlNodePtr tree, node;
    const char *e;

    tree = xmlNewChild(root, NULL, "rto", NULL);
    e = fmt_enum(tcp_mib_enums_tcpRtoAlgorithm, tcp->tcpRtoAlgorithm);
    if (e) {
	(void) xml_new_child(tree, NULL, "algorithm", "%s", e);
    }
    if (tcp->tcpRtoMin) {
	node = xml_new_child(tree, NULL, "minimum", "%d", *tcp->tcpRtoMin);
	xml_set_prop(node, "unit", "milliseconds");
    }
    if (tcp->tcpRtoMax) {
	node = xml_new_child(tree, NULL, "maximum", "%d", *tcp->tcpRtoMax);
	xml_set_prop(node, "unit", "milliseconds");
    }
    if (tcp->tcpCurrEstab) {
	(void) xml_new_child(root, NULL, "established", "%u", *tcp->tcpCurrEstab);
    }
}



static void
fmt_tcp_info(GString *s, tcp_mib_tcp_t *tcp)
{
    int const indent = 16;
    const char *e;

    e = fmt_enum(tcp_mib_enums_tcpRtoAlgorithm, tcp->tcpRtoAlgorithm);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "RTO-Algorithm:", e);
    }
    if (tcp->tcpRtoMin) {
	g_string_sprintfa(s, "%-*s%d milliseconds\n",
			  indent, "RTO-Minimum:", *tcp->tcpRtoMin);
    }
    if (tcp->tcpRtoMax) {
	g_string_sprintfa(s, "%-*s%d milliseconds\n",
			  indent, "RTO-Maximum:", *tcp->tcpRtoMax);
    }
    if (tcp->tcpMaxConn && *tcp->tcpMaxConn) {
	if (*tcp->tcpMaxConn < 0) {
	    g_string_sprintfa(s, "%-*sdynamic\n", indent, "TCB-Limit:");
	} else {
	    g_string_sprintfa(s, "%-*s%d connections\n",
			      indent, "TCB-Limit:", *tcp->tcpMaxConn);
	}
    }
    if (tcp->tcpCurrEstab) {
	g_string_sprintfa(s, "%-*s%u\n",
			  indent, "Established:", *tcp->tcpCurrEstab);
    }
}



static int
show_tcp_info(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcp_t *tcp;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    tcp_mib_get_tcp(interp->peer, &tcp, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (tcp) {
	if (scli_interp_xml(interp)) {
	    xml_tcp_info(interp->xml_node, tcp);
	} else {
	    fmt_tcp_info(interp->result, tcp);
	}
    }

    if (tcp) tcp_mib_free_tcp(tcp);

    return SCLI_OK;
}



void
scli_init_tcp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show tcp info", NULL,
	  "The `show tcp info' command displays parameters of the TCP\n"
	  "protocol engine.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "tcp", NULL,
	  show_tcp_info },

	{ "show tcp listener", NULL,
	  "The `show tcp listener' command displays the listening TCP\n"
	  "endpoints. The command generates a table with the following\n"
	  "columns:\n"
	  "\n"
	  "  LOCAL  local TCP endpoint\n"
	  "  STATE  transmission control block state (listen)",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "tcp listeners", NULL,
	  show_tcp_listener },

	{ "show tcp connections", NULL,
	  "The `show tcp connections' command displays the connected TCP\n"
	  "endpoints including the current state of the connection as seen\n"
	  "by the remote SNMP agent. The command generates a table with\n"
	  "the following columns:\n"
	  "\n"
	  "  LOCAL  local  TCP endpoint\n"
	  "  REMOTE remote TCP endpoint\n"
	  "  STATE  transmission control block state\n"
	  "\n"
	  "The transmission control block state is either closed, synSent,\n"
	  "synReceived, established, finWait1, finWait2, closeWait, lastAck,\n"
	  "closing, or timeWait.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "tcp connections", NULL,
	  show_tcp_connections },

	{ "show tcp states", NULL,
	  "The `show tcp states' command displays the distribution of TCP\n"
	  "transmission control block states together with a list of known\n"
	  "port names in each state. The command generates a table with\n"
	  "the following columns:\n"
	  "\n"
	  "  COUNT number of transmission control blocks per state\n"
	  "  STATE transmission control block state\n"
	  "  PORTS well-known ports associated with the state\n"
	  "\n"
	  "The command uses some heuristics to identify the interesting\n"
	  "port numbers. First, all local port numbers are considered\n"
	  "where the local port number matches one of the listening port\n"
	  "numbers. From the remaining connections, all local port numbers\n"
	  "are considered with a well known name. From the remaining\n"
	  "connections, all remote port numbers are considered with a\n"
	  "well known name. All remaining connections are aggregated\n"
	  "under the pseudo name - (hyphen). Unspecified port numbers\n"
	  "are show using the pseudo name * (star).",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "tcp states", NULL,
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
