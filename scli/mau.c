/* 
 * mau.c -- scli mau mode implementation
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

#include "mau-mib.h"



static void
show_mau_info(GString *s, ifMauEntry_t *ifMauEntry)
{
    g_string_sprintfa(s, "%7u ", ifMauEntry->ifMauIfIndex);
    
    fmt_enum(s, 1, mau_mib_enums_ifMauStatus,
	     ifMauEntry->ifMauStatus);
    g_string_sprintfa(s, " ");

    fmt_enum(s, 1, mau_mib_enums_ifMauMediaAvailable,
	     ifMauEntry->ifMauMediaAvailable);

    g_string_append(s, "\n");
}



static int
cmd_mau_info(scli_interp_t *interp, int argc, char **argv)
{
    ifMauEntry_t **ifMauTable = NULL;
    int width = 20;
    int i, len;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (mau_mib_get_ifMauTable(interp->peer, &ifMauTable)) {
	return SCLI_ERROR;
    }

    if (ifMauTable) {
	g_string_sprintfa(interp->result,
			  "Interface Status Media Jabber Type\n");
	for (i = 0; ifMauTable[i]; i++) {
	    show_mau_info(interp->result, ifMauTable[i]);
	}
    }

    if (ifMauTable) mau_mib_free_ifMauTable(ifMauTable);
    
    return SCLI_OK;
}



void
scli_init_mau_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show mau",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "display media attachment unit parameters",
	  cmd_mau_info },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t mau_mode = {
	"mau",
	"scli mode to display and media attachment unit parameters",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &mau_mode);
}
