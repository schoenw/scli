/* 
 * udp.c -- scli udp mode implementation
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

#include "udp-mib.h"



static void
xml_udp_listener(xmlNodePtr root, udp_mib_udpEntry_t *udpEntry, int width)
{
    xmlNodePtr node;

    node = xmlNewChild(root, NULL, "listener", NULL);
    xmlSetProp(node, "address",
	       fmt_ipv4_address(udpEntry->udpLocalAddress, SCLI_FMT_ADDR));
    xmlSetProp(node, "port",
	       fmt_udp_port(udpEntry->udpLocalPort, SCLI_FMT_ADDR));
}



static void
fmt_udp_listener(GString *s, udp_mib_udpEntry_t *udpEntry, int width)
{
    int pos;
    
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(udpEntry->udpLocalAddress,
				       SCLI_FMT_NAME_OR_ADDR),
		      fmt_udp_port(udpEntry->udpLocalPort,
				   SCLI_FMT_NAME_OR_ADDR),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(width-pos+1, 1), "");
    g_string_append(s, "listen\n");
}



static int
show_udp_listener(scli_interp_t *interp, int argc, char **argv)
{
    udp_mib_udpEntry_t **udpTable = NULL;
    int width = 20;
    char *addr, *port;
    int i, len;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (udp_mib_get_udpTable(interp->peer, &udpTable)) {
	return SCLI_ERROR;
    }

    if (udpTable) {
	for (i = 0; udpTable[i]; i++) {
	    addr = fmt_ipv4_address(udpTable[i]->udpLocalAddress,
				    SCLI_FMT_NAME_OR_ADDR);
	    port = fmt_udp_port(udpTable[i]->udpLocalPort,
				SCLI_FMT_NAME_OR_ADDR);
	    len = strlen(addr) + strlen(port) + 1;
	    if (len > width) {
		width = len;
	    }
	}
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "%-*s %s",
			      width, "LOCAL ADDRESS", "STATE");
	}
	for (i = 0; udpTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_udp_listener(interp->xml_node, udpTable[i], width);
	    } else {
		fmt_udp_listener(interp->result, udpTable[i], width);
	    }
	}
    }

    if (udpTable) udp_mib_free_udpTable(udpTable);
    
    return SCLI_OK;
}



void
scli_init_udp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show udp listener", NULL,
	  "The show udp listener command displays the listening UDP\n"
	  "endpoints.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "udp", NULL,
	  show_udp_listener },
	
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t udp_mode = {
	"udp",
	"The scli udp mode is based on the UDP-MIB as published in\n"
	"RFC 2013. It provides commands to browse information specific\n"
	"to the UDP transport protocol.",
	cmds
    };
    
    scli_register_mode(interp, &udp_mode);
}
