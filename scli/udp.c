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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "scli.h"

#include "udp-mib.h"



static void
show_udp_listener(GString *s, udpEntry_t *udpEntry, int width)
{
    int pos;
    
    g_string_sprintfa(s, "%s:%s%n",
		      fmt_ipv4_address(udpEntry->udpLocalAddress, 1),
		      fmt_udp_port(udpEntry->udpLocalPort, 1),
		      &pos);
    g_string_sprintfa(s, "%*s", MAX(width-pos+1, 1), "");
    g_string_append(s, "listen\n");
}



static int
cmd_udp_listener(scli_interp_t *interp, int argc, char **argv)
{
    udpEntry_t **udpTable = NULL;
    int width = 20;
    char *addr, *port;
    int i, len;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (udp_mib_get_udpTable(interp->peer, &udpTable)) {
	return SCLI_ERROR;
    }

    if (udpTable) {
	for (i = 0; udpTable[i]; i++) {
	    addr = fmt_ipv4_address(udpTable[i]->udpLocalAddress, 1);
	    port = fmt_udp_port(udpTable[i]->udpLocalPort, 1);
	    len = strlen(addr) + strlen(port) + 1;
	    if (len > width) {
		width = len;
	    }
	}
	g_string_sprintfa(interp->result, "%-*s %s\n",
			  width, "Local Address",
			  "State");
	for (i = 0; udpTable[i]; i++) {
	    show_udp_listener(interp->result, udpTable[i], width);
	}
    }

    if (udpTable) udp_mib_free_udpTable(udpTable);
    
    return SCLI_OK;
}



void
scli_init_udp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show udp listener",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "existing udp listener",
	  cmd_udp_listener },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t udp_mode = {
	"udp",
	"scli mode to display and configure UDP parameters",
	cmds
    };
    
    scli_register_mode(interp, &udp_mode);
}
