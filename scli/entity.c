/* 
 * entity.c -- scli entity mode implementation
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

#include "stools.h"
#include "scli.h"


static void
fmt_string(GString *s, char *label, int width, guchar *string, gsize len)
{
    if (string) {
	g_string_sprintfa(s, "%-*s %.*s", width, label, (int) len, string);
    }
}


static int
cmd_entities(scli_interp_t *interp, int argc, char **argv)
{
    entPhysicalEntry_t **entPhysicalEntry = NULL;
    GString *s;
    int i;
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (entity_mib_get_entPhysicalEntry(interp->peer, &entPhysicalEntry)) {
	return SCLI_ERROR;
    }

    /*
     * We should build up the containment tree in order to produce
     * really useful output.
     */
    
    s = interp->result;
    if (entPhysicalEntry) {
	for (i = 0; entPhysicalEntry[i]; i++) {
	    fmt_string(s, "\nName:", indent,
		       entPhysicalEntry[i]->entPhysicalName,
		       entPhysicalEntry[i]->_entPhysicalNameLength);
	    fmt_string(s, "\nDescription:", indent,
		       entPhysicalEntry[i]->entPhysicalDescr,
		       entPhysicalEntry[i]->_entPhysicalDescrLength);
	    fmt_string(s, "\nHardware Revision:", indent,
		       entPhysicalEntry[i]->entPhysicalHardwareRev,
		       entPhysicalEntry[i]->_entPhysicalHardwareRevLength);
	    fmt_string(s, "Firmware Revision:", indent,
		       entPhysicalEntry[i]->entPhysicalFirmwareRev,
		       entPhysicalEntry[i]->_entPhysicalFirmwareRevLength);
	    fmt_string(s, "Software Revision:", indent,
		       entPhysicalEntry[i]->entPhysicalSoftwareRev,
		       entPhysicalEntry[i]->_entPhysicalSoftwareRevLength);
	    fmt_string(s, "Serial Number:", indent,
		       entPhysicalEntry[i]->entPhysicalSerialNum,
		       entPhysicalEntry[i]->_entPhysicalSerialNumLength);
	    fmt_string(s, "Manufacturer:", indent,
		       entPhysicalEntry[i]->entPhysicalMfgName,
		       entPhysicalEntry[i]->_entPhysicalMfgNameLength);

	    /* xxx entPhysicalModelName entPhysicalAlias
	       entPhysicalAssetID entPhysicalIsFRU */

	    g_string_append(s, "\n");
	}
	entity_mib_free_entPhysicalEntry(entPhysicalEntry);
    }
    
    return SCLI_OK;
}



void
scli_init_entity_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show system", "entities",
	  "show the entities that make up the system", cmd_entities },
	{ NULL, NULL, NULL, NULL }
    };
    
    static scli_mode_t entity_mode = {
	"entity",
	"scli mode to display the entities that make up a system",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &entity_mode);
}
