/* 
 * atm.c -- scli atm mode implementation
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

#include "atm-mib.h"
#include "if-mib.h"


static void
show_atm_interface(GString *s, atmInterfaceConfEntry_t *atmInterfaceConfEntry,
		   ifEntry_t *ifEntry, ifXEntry_t *ifXEntry)
{
    if (atmInterfaceConfEntry->atmInterfaceMaxVpcs) {
	g_string_sprintfa(s, "%5d   ",
			  *atmInterfaceConfEntry->atmInterfaceMaxVpcs);
    }

    if (atmInterfaceConfEntry->atmInterfaceMaxVpcs) {
	g_string_sprintfa(s, "%5d ",
			  *atmInterfaceConfEntry->atmInterfaceMaxVpcs);
    }

    g_string_append(s, "\n");
}



static int
cmd_atm_interface(scli_interp_t *interp, int argc, char **argv)
{
    atmInterfaceConfEntry_t **atmInterfaceConfTable = NULL;
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (atm_mib_get_atmInterfaceConfTable(interp->peer, &atmInterfaceConfTable)) {
	return SCLI_ERROR;
    }

    (void) if_mib_get_ifTable(interp->peer, &ifTable);
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    
    if (atmInterfaceConfTable) {
	g_string_append(interp->result, "MaxVpcs MaxVccs\n");
	for (i = 0; atmInterfaceConfTable[i]; i++) {
	    show_atm_interface(interp->result, atmInterfaceConfTable[i],
			       NULL, NULL);
	}
    }

    if (atmInterfaceConfTable)
	atm_mib_free_atmInterfaceConfTable(atmInterfaceConfTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    return SCLI_OK;
}



void
scli_init_atm_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show atm interface",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "atm interfaces",
	  cmd_atm_interface },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t atm_mode = {
	"atm",
	"scli mode to display and configure ATM parameters",
	cmds
    };
    
    scli_register_mode(interp, &atm_mode);
}
