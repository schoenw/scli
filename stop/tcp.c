/* 
 * tcp.c -- stop tcp mode implementation
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

#include "stop.h"

#include "tcp-mib.h"

#include <netdb.h>
#include <netinet/in.h>


static char*
fmt_tcp_port(int port, int name)
{
    struct servent *s;
    static char buffer[12];

    if (name) {
	if (! port) {
	    return "*";
	}
	s = getservbyport(htons(port), "tcp");
	if (s) {
	    return s->s_name;
	}
    }
    sprintf(buffer, "%d", port);
    return buffer;
}



static char*
fmt_ipv4_address(guchar *addr, int name)
{
    static char buffer[16];
    struct hostent *h;

    if (name) {
	if (! addr[0] && ! addr[1] && ! addr[2] && ! addr[3]) {
	    return "*";
	}
	h = gethostbyaddr((char *) addr, 4, AF_INET);
	if (h) {
	    return h->h_name;
	}
    }
    sprintf(buffer, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
    return buffer;
}



static void
show_tcp_summary(host_snmp *peer)
{
    GString *s;
    
    g_return_if_fail(peer);
    
    s = g_string_new("Tcp:   ");

    stop_show_mode_summary_line(s->str);
    g_string_free(s, 1);
}



static void
show_tcp_connection(GString *s, tcpConnEntry_t *tcpConnEntry)
{
    int pos;
    
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnLocalAddress, 0),
		      fmt_tcp_port(tcpConnEntry->tcpConnLocalPort, 0),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(24-pos+1, 1), "");
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(tcpConnEntry->tcpConnRemAddress, 0),
		      fmt_tcp_port(tcpConnEntry->tcpConnRemPort, 0),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(24-pos+1, 1), "");
    
    if (tcpConnEntry->tcpConnState) {
	char *name;
	name = stls_table_get_value(tcp_mib_enums_tcpConnState,
				    *tcpConnEntry->tcpConnState);
	if (name) {
	    g_string_sprintfa(s, "%s", name);
	} else {
	    g_string_sprintfa(s, "%d", *tcpConnEntry->tcpConnState);
	}
    }
}



static void
show_tcp_connections(WINDOW *win, host_snmp *peer, int flags)
{
    tcpConnEntry_t **tcpConnTable = NULL;
    GString *s;
    int i, p;

    if (flags & STOP_FLAG_RESTART) {
	show_tcp_summary(peer);
	wattron(win, A_REVERSE);
	mvwprintw(win, 0, 0, "%-*s", COLS, 
		  "Local Address            Remote Address           Status");
	wattroff(win, A_REVERSE);
	wrefresh(win);
    }

    if (tcp_mib_get_tcpConnTable(peer, &tcpConnTable) != 0 
	|| tcpConnTable == NULL) {
	return;
    }

    for (i = 0, p = 0; tcpConnTable[i]; i++) {
	if (tcpConnTable[i]->tcpConnState &&
	    *tcpConnTable[i]->tcpConnState == 2) {
	    continue;
	}
	p++;
	s = g_string_new(NULL);
	show_tcp_connection(s, tcpConnTable[i]);
	g_string_truncate(s, COLS);
	mvwprintw(win, p, 0, s->str);
	wclrtoeol(win);
	g_string_free(s, 1);
    }
    wclrtobot(win);

    tcp_mib_free_tcpConnTable(tcpConnTable);
}



void
stop_init_tcp_mode()
{
    static stop_mode_t tcp_mode = {
	"tcp",
	"Display list of existing TCP connections",
	&show_tcp_connections
    };
    
    stop_register_mode(&tcp_mode);
}
