/* 
 * isdn.c -- scli isdn mode implementation
 *
 * Copyright (C) 2001-2002 Oliver Wellnitz, Juergen Schoenwaelder
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

#include "isdn-mib.h"


static void
fmt_isdn_bearer(GString *s, isdn_mib_isdnBearerEntry_t *bearerEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Interface:",
		      bearerEntry->ifIndex);

    e = fmt_enum(isdn_mib_enums_isdnBearerChannelType,
		 bearerEntry->isdnBearerChannelType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Channel Type:", e);
    }
}



static int
show_isdn_bearer(scli_interp_t * interp, int argc, char **argv)
{
    isdn_mib_isdnBearerEntry_t **bearerTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    isdn_mib_get_isdnBearerTable(interp->peer, &bearerTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (bearerTable) {
	for (i = 0; bearerTable[i]; i++) {
	    fmt_isdn_bearer(interp->result, bearerTable[i]);
	}
    }
    
    if (bearerTable)
	isdn_mib_free_isdnBearerTable(bearerTable);

    return SCLI_OK;
}



void
scli_init_isdn_mode(scli_interp_t * interp)
{
    static scli_cmd_t cmds[] = {

	{ "show isdn bearer", NULL,
	  "The `show isdn bearer' command shows information about\n"
	  "the ISDN B (bearer) channels.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_isdn_bearer },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };

    static scli_mode_t isdn_mode = {
	"printer",
	"The scli isdn mode is based on the ISDN-MIB as published\n"
	"in RFC 2127.",
	cmds
    };

    scli_register_mode(interp, &isdn_mode);
}
