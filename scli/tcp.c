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


typedef struct {
    char *address;
    char *port;
    char *service;
    int process;
} tcp_listener_t;



static void
tcp_listener_free(tcp_listener_t *l)
{
    g_free(l->address);
    g_free(l->port);
    g_free(l->service);
    g_free(l);
}



static tcp_listener_t*
tcp_listener_new_tcpListenerEntry(tcp_mib_tcpListenerEntry_t *tcpListenerEntry)
{
    tcp_listener_t *l;

    l = g_new0(tcp_listener_t, 1);
    l->address = g_strdup(fmt_inet_address(&tcpListenerEntry->tcpListenerLocalAddressType,
					   tcpListenerEntry->tcpListenerLocalAddress,
					   tcpListenerEntry->_tcpListenerLocalAddressLength));
    l->port = g_strdup(fmt_tcp_port(tcpListenerEntry->tcpListenerLocalPort,
				    SCLI_FMT_ADDR));
    l->service = g_strdup(fmt_tcp_port(tcpListenerEntry->tcpListenerLocalPort,
				       SCLI_FMT_NAME));
    if (tcpListenerEntry->tcpListenerProcess) {
	l->process = *tcpListenerEntry->tcpListenerProcess;
    }

    return l;
}



static tcp_listener_t*
tcp_listener_new_tcpConnEntry(tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    tcp_listener_t *l;

    l = g_new0(tcp_listener_t, 1);
    l->address = g_strdup(fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
					   SCLI_FMT_ADDR));
    l->port = g_strdup(fmt_tcp_port(tcpConnEntry->tcpConnLocalPort,
				    SCLI_FMT_ADDR));
    return l;
}



static void
xml_tcp_listener(xmlNodePtr root, tcp_listener_t *l)
{
    xmlNodePtr node;

    node = xml_new_child(root, NULL, BAD_CAST("listener"), NULL);
    xml_new_child(node, NULL, BAD_CAST("address"), "%s", l->address);
    xml_new_child(node, NULL, BAD_CAST("port"), "%s", l->port);
    if (l->process) {
	xml_new_child(node, NULL, BAD_CAST("process"), "%s", l->process);
    }
}



static void
fmt_tcp_listener(GString *s, tcp_listener_t *l,
		 int address_width, int port_width, int service_width)
{
    g_string_sprintfa(s, "%-*s %-*s %-*s ",
		      address_width, l->address,
		      port_width, l->port,
		      service_width, l->service ? l->service : "-");
    if (l->process) {
	g_string_sprintfa(s, "%u\n", l->process);
    } else {
	g_string_sprintfa(s, "-\n");
    }
}



static int
show_tcp_listener(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    tcp_mib_tcpListenerEntry_t **tcpListenerTable = NULL;
    int width = 20;
    const char *addr, *port;
    int i, len, cnt;
    GError *error = NULL;
    GPtrArray *tab = NULL;
    tcp_listener_t *l;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    tcp_mib_get_tcpListenerTable(interp->peer, &tcpListenerTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    if (tcpListenerTable) {
	tab = g_ptr_array_new();
	for (i = 0; tcpListenerTable[i]; i++) {
	    l = tcp_listener_new_tcpListenerEntry(tcpListenerTable[i]);
	    g_ptr_array_add(tab, l);
	}
    }

    if (! tcpListenerTable) {
	tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable, 0, &error);
	if (scli_interp_set_error_snmp(interp, &error)) {
	    return SCLI_SNMP;
	}
	
	if (tcpConnTable) {
	    tab = g_ptr_array_new();
	    for (i = 0; tcpConnTable[i]; i++) {
		if (tcpConnTable[i]->tcpConnState
		    && (*tcpConnTable[i]->tcpConnState
			== TCP_MIB_TCPCONNSTATE_LISTEN)) {
		    l = tcp_listener_new_tcpConnEntry(tcpConnTable[i]);
		    g_ptr_array_add(tab, l);
		}
	    }
	}
    }

    if (tab) {
	int address_width = 7, port_width = 4, service_width = 7;
	for (i = 0; i < tab->len; i++) {
	    l = g_ptr_array_index(tab, i);
	    if (l->address) address_width = MAX(address_width, strlen(l->address));
	    if (l->port) port_width = MAX(port_width, strlen(l->port));
	    if (l->service) service_width = MAX(service_width, strlen(l->service));
	}

	if (tab->len && ! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "%-*s %-*s %-*s PROCESS",
			      address_width, "ADDRESS",
			      port_width, "PORT",
			      service_width, "SERVICE");
	}

	for (i = 0; i < tab->len; i++) {
	    l = g_ptr_array_index(tab, i);
	    if (scli_interp_xml(interp)) {
		xml_tcp_listener(interp->xml_node, l);
	    } else {
		fmt_tcp_listener(interp->result, l, address_width,
				 port_width, service_width);
	    }
	    tcp_listener_free(l);
	}
	g_ptr_array_free(tab, TRUE);
    }

    
    if (tcpListenerTable) tcp_mib_free_tcpListenerTable(tcpListenerTable);
    if (tcpConnTable) tcp_mib_free_tcpConnTable(tcpConnTable);
    return SCLI_OK;
}



typedef struct {
    char *local_address;
    char *local_port;
    char *remote_address;
    char *remote_port;
    char *state;
    int process;
} tcp_connection_t;



static void
tcp_connection_free(tcp_connection_t *c)
{
    g_free(c->local_address);
    g_free(c->local_port);
    g_free(c->remote_address);
    g_free(c->remote_port);
    g_free(c->state);
}



static tcp_connection_t*
tcp_connection_new_tcpConnectionEntry(tcp_mib_tcpConnectionEntry_t *tcpConnectionEntry)
{
    tcp_connection_t *c;

    c = g_new0(tcp_connection_t, 1);

    c->local_address = g_strdup(fmt_inet_address(&tcpConnectionEntry->tcpConnectionLocalAddressType,
						 tcpConnectionEntry->tcpConnectionLocalAddress,
						 tcpConnectionEntry->_tcpConnectionLocalAddressLength));
    c->local_port = g_strdup(fmt_tcp_port(tcpConnectionEntry->tcpConnectionLocalPort,
					  SCLI_FMT_ADDR));
    c->remote_address = g_strdup(fmt_inet_address(&tcpConnectionEntry->tcpConnectionRemAddressType,
						 tcpConnectionEntry->tcpConnectionRemAddress,
						 tcpConnectionEntry->_tcpConnectionRemAddressLength));
    c->remote_port = g_strdup(fmt_tcp_port(tcpConnectionEntry->tcpConnectionRemPort,
					  SCLI_FMT_ADDR));
    if (tcpConnectionEntry->tcpConnectionState) {
	c->state = g_strdup(fmt_enum(tcp_mib_enums_tcpConnectionState,
				     tcpConnectionEntry->tcpConnectionState));
    }
    if (tcpConnectionEntry->tcpConnectionProcess) {
	c->process = *tcpConnectionEntry->tcpConnectionProcess;
    }

    return c;
}



static tcp_connection_t*
tcp_connection_new_tcpConnEntry(tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    tcp_connection_t *c;

    c = g_new0(tcp_connection_t, 1);
    c->local_address = g_strdup(fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress,
						 SCLI_FMT_ADDR));
    c->local_port = g_strdup(fmt_tcp_port(tcpConnEntry->tcpConnLocalPort,
					   SCLI_FMT_ADDR));
    c->remote_address = g_strdup(fmt_ipv4_address(tcpConnEntry->tcpConnRemAddress,
						  SCLI_FMT_ADDR));
    c->remote_port = g_strdup(fmt_tcp_port(tcpConnEntry->tcpConnRemPort,
					   SCLI_FMT_ADDR));
    if (tcpConnEntry->tcpConnState) {
	c->state = g_strdup(fmt_enum(tcp_mib_enums_tcpConnState,
				     tcpConnEntry->tcpConnState));
    }

    return c;
}



static void
xml_tcp_connection(xmlNodePtr root, tcp_connection_t *c)
{
    xmlNodePtr node;

    node = xml_new_child(root, NULL, BAD_CAST("connection"), NULL);
    xml_new_child(node, NULL, BAD_CAST("local-address"),
		  "%s", c->local_address);
    xml_new_child(node, NULL, BAD_CAST("local-port"),
		  "%s", c->local_port);
    xml_new_child(node, NULL, BAD_CAST("remote-address"),
		  "%s", c->remote_address);
    xml_new_child(node, NULL, BAD_CAST("remote-port"),
		  "%s", c->remote_port);
    xml_new_child(node, NULL, BAD_CAST("state"),
		  "%s", c->state);
    if (c->process) {
	xml_new_child(node, NULL, BAD_CAST("process"), "%s", c->process);
    }
}



static void
fmt_tcp_connection(GString *s, tcp_connection_t *c,
		   int local_address_width, int local_port_width,
		   int remote_address_width, int remote_port_width,
		   int state_width)
{
    g_string_sprintfa(s, "%-*s %-*s %-*s %-*s %-*s ",
		      local_address_width, c->local_address,
		      local_port_width, c->local_port,
		      remote_address_width, c->remote_address,
		      remote_port_width, c->remote_port,
		      state_width, c->state);
    if (c->process) {
	g_string_sprintfa(s, "%u\n", c->process);
    } else {
	g_string_sprintfa(s, "-\n");
    }
}



static int
show_tcp_connections(scli_interp_t *interp, int argc, char **argv)
{
    tcp_mib_tcpConnectionEntry_t **tcpConnectionTable = NULL;
    tcp_mib_tcpConnEntry_t **tcpConnTable = NULL;
    int local_width = 20;
    int remote_width = 20;
    char *addr, *port;
    int i, len, cnt;
    GError *error = NULL;
    GPtrArray *tab = NULL;
    tcp_connection_t *c;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

#if 1
    tcp_mib_get_tcpConnectionTable(interp->peer, &tcpConnectionTable,
				   0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (tcpConnectionTable) {
	tab = g_ptr_array_new();
	for (i = 0; tcpConnectionTable[i]; i++) {
	    if (tcpConnectionTable[i]->tcpConnectionState &&
		*tcpConnectionTable[i]->tcpConnectionState
		!= TCP_MIB_TCPCONNECTIONSTATE_LISTEN) {
		c = tcp_connection_new_tcpConnectionEntry(tcpConnectionTable[i]);
		g_ptr_array_add(tab, c);
	    }
	}
    }
#endif

    if (! tcpConnectionTable) {

	tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable, 0, &error);
	if (scli_interp_set_error_snmp(interp, &error)) {
	    return SCLI_SNMP;
	}
	
	if (tcpConnTable) {
	    tab = g_ptr_array_new();
	    for (i = 0; tcpConnTable[i]; i++) {
		if (tcpConnTable[i]->tcpConnState &&
		    *tcpConnTable[i]->tcpConnState
		    != TCP_MIB_TCPCONNSTATE_LISTEN) {
		    c = tcp_connection_new_tcpConnEntry(tcpConnTable[i]);
		    g_ptr_array_add(tab, c);
		}
	    }
	}
    }

    if (tab) {
	int local_address_width = 13, local_port_width = 4,
	    remote_address_width = 14, remote_port_width = 4,
	    state_width = 5;
	for (i = 0; i < tab->len; i++) {
	    c = g_ptr_array_index(tab, i);
	    if (c->local_address) local_address_width = MAX(local_address_width, strlen(c->local_address));
	    if (c->local_port) local_port_width = MAX(local_port_width, strlen(c->local_port));
	    if (c->remote_address) remote_address_width = MAX(remote_address_width, strlen(c->remote_address));
	    if (c->remote_port) remote_port_width = MAX(remote_port_width, strlen(c->remote_port));
	    if (c->state) state_width = MAX(state_width, strlen(c->state));
	}

	if (tab->len && ! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "%-*s %-*s %-*s %-*s %-*s PROCESS",
			      local_address_width, "LOCAL-ADDRESS",
			      local_port_width, "PORT",
			      remote_address_width, "REMOTE-ADDRESS",
			      remote_port_width, "PORT",
			      state_width, "STATE");
	}

	for (i = 0; i < tab->len; i++) {
	    c = g_ptr_array_index(tab, i);
	    if (scli_interp_xml(interp)) {
		xml_tcp_connection(interp->xml_node, c);
	    } else {
		fmt_tcp_connection(interp->result, c,
				   local_address_width, local_port_width,
				   remote_address_width, remote_port_width,
				   state_width);
	    }
	    tcp_connection_free(c);
	}
	g_ptr_array_free(tab, TRUE);
    }

    if (tcpConnectionTable) tcp_mib_free_tcpConnectionTable(tcpConnectionTable);
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
		 
    tree = xml_new_child(root, NULL, BAD_CAST("state"), NULL);
    xml_set_prop(tree, BAD_CAST("name"), "%s", e);

    for (elem = ports; elem; elem = g_slist_next(elem)) {
	tcp_state_t *t = (tcp_state_t *) elem->data;
	node = xml_new_child(tree, NULL, BAD_CAST("service"), "%u", t->count);
	xml_set_prop(node, BAD_CAST("port"), "%d", t->port);
	xml_set_prop(node, BAD_CAST("name"), "%s", t->name);
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
    GError *error = NULL;

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

    tcp_mib_get_tcpConnTable(interp->peer, &tcpConnTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
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

    tree = xml_new_child(root, NULL, BAD_CAST("rto"), NULL);
    e = fmt_enum(tcp_mib_enums_tcpRtoAlgorithm, tcp->tcpRtoAlgorithm);
    if (e) {
	(void) xml_new_child(tree, NULL, BAD_CAST("algorithm"), "%s", e);
    }
    if (tcp->tcpRtoMin) {
	node = xml_new_child(tree, NULL, BAD_CAST("minimum"), "%d", *tcp->tcpRtoMin);
	xml_set_prop(node, BAD_CAST("unit"), "milliseconds");
    }
    if (tcp->tcpRtoMax) {
	node = xml_new_child(tree, NULL, BAD_CAST("maximum"), "%d", *tcp->tcpRtoMax);
	xml_set_prop(node, BAD_CAST("unit"), "milliseconds");
    }
    if (tcp->tcpCurrEstab) {
	(void) xml_new_child(root, NULL, BAD_CAST("established"), "%u", *tcp->tcpCurrEstab);
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
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    tcp_mib_get_tcp(interp->peer, &tcp, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
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
	  "  ADDRESS IP address of the listening TCP endpoint\n"
	  "  PORT    port number of the listening TCP endpoint\n"
	  "  SERVICE service name of the listening TCP endpoint\n"
	  "  PROCESS process number",
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
