/* 
 * rpl.c -- scli rpl mode implementation
 *
 * Copyright (C) 2011 Juergen Schoenwaelder
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
 * @(#) $Id: rpl.c 3180 2009-07-29 22:36:13Z schoenw $
 */

#include "scli.h"

#include "snmpv2-tc.h"
#include "ip-mib.h"
#include "if-mib.h"
#include "jacobs-rpl-mib.h"



static void
fmt_rpl_instances(GString *s, jacobs_rpl_mib_rplRPLInstanceEntry_t *rplInstancEntry)
{
    return;
}



static int
show_rpl_instances(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_rpl_mib_rplRPLInstanceEntry_t **rplInstanceTable = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplRPLInstanceTable(interp->peer, &rplInstanceTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplInstanceTable) {
	for (i = 0; rplInstanceTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_rpl_instances(interp->result, rplInstanceTable[i]);
	}
    }
    
    if (rplInstanceTable) jacobs_rpl_mib_free_rplRPLInstanceTable(rplInstanceTable);
    
    return SCLI_OK;
}



void
scli_init_rpl_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show rpl instances", NULL,
	  "The `show rpl instances' command displays information about\n"
	  "RPL instances known by the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_instances },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
	
    static scli_mode_t rpl_mode = {
	"rpl",
	"The scli rpl mode is used to display and configure RPL\n"
	"parameters.",
	cmds
    };
    
    scli_register_mode(interp, &rpl_mode);
}
