/* 
 * rs232.c -- scli rs232 mode implementation
 *
 * Copyright (C) 2002 Juergen Schoenwaelder
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

#include "rs-232-mib.h"


static void
fmt_rs232_detail(GString *s, rs_232_mib_rs232PortEntry_t *portEntry)
{
    const char *e;

    g_string_sprintfa(s, "Interface: %d\n", portEntry->rs232PortIndex);

    e = fmt_enum(rs_232_mib_enums_rs232PortType, portEntry->rs232PortType);
    if (e) {
	g_string_sprintfa(s, "Port Type: %s\n", e);
    }

    if (portEntry->rs232PortInSpeed) {
	g_string_sprintfa(s, "In  Speed: %d\n", *portEntry->rs232PortInSpeed);
    }

    if (portEntry->rs232PortOutSpeed) {
	g_string_sprintfa(s, "Out Speed: %d\n", *portEntry->rs232PortOutSpeed);
    }

    e = fmt_enum(rs_232_mib_enums_rs232PortInFlowType, portEntry->rs232PortInFlowType);
    if (e) {
	g_string_sprintfa(s, "In  Flow Type: %s\n", e);
    }

    e = fmt_enum(rs_232_mib_enums_rs232PortOutFlowType, portEntry->rs232PortOutFlowType);
    if (e) {
	g_string_sprintfa(s, "Out Flow Type: %s\n", e);
    }

    g_string_append(s, "\n");
}



static int
show_rs232_details(scli_interp_t *interp, int argc, char **argv)
{
    rs_232_mib_rs232PortEntry_t **portTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rs_232_mib_get_rs232PortTable(interp->peer, &portTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (portTable) {
	for (i = 0; portTable[i]; i++) {
	    fmt_rs232_detail(interp->result, portTable[i]);
	}
    }

    if (portTable) rs_232_mib_free_rs232PortTable(portTable);
    
    return SCLI_OK;
}



void
scli_init_rs232_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show rs232 details", NULL,
	  "",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rs232_details },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t rs232_mode = {
	"rs232",
	"The rs232 scli mode is based on the RS-232-MIB as published\n"
	"in RFC 1659.",
	cmds
    };
    
    scli_register_mode(interp, &rs232_mode);
}
