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

#include "scli.h"

#include "entity-mib.h"


static void
show_containment(GString *s, char *prefix,
		 entPhysicalEntry_t **entPhysicalEntry, gint32 parent)
{
    int i, j, len;

    if (! entPhysicalEntry) {
	return;
    }

    len = strlen(prefix);
    for (i = 0; entPhysicalEntry[i]; i++) {
	if (entPhysicalEntry[i]->entPhysicalContainedIn
	    && *(entPhysicalEntry[i]->entPhysicalContainedIn) == parent) {
	    int next = 0;
	    for (j = i+1; entPhysicalEntry[j]; j++) {
		if (entPhysicalEntry[j]->entPhysicalContainedIn
		    && entPhysicalEntry[i]->entPhysicalIndex
		    && *(entPhysicalEntry[j]->entPhysicalContainedIn)
		    == parent) {
		    next = 1;
		    break;
		}
	    }
	    
	    g_string_sprintfa(s, "%5d:",
			      entPhysicalEntry[i]->entPhysicalIndex);
	    if (len) {
		g_string_sprintfa(s, "%s  %c- ", prefix, next ? '|' : '`');
	    } else {
		g_string_append(s, "   ");
	    }
	    g_string_sprintfa(s, "%.*s\n", 
			   (int) entPhysicalEntry[i]->_entPhysicalDescrLength,
			         entPhysicalEntry[i]->entPhysicalDescr);

	    if (entPhysicalEntry[i]->entPhysicalIndex) {
		char *new_prefix = NULL;
		new_prefix = g_malloc(len + 3);
		strcpy(new_prefix, prefix);
		if (next) {
		    strcat(new_prefix, len ? "  |" : "`");
		} else {
		    strcat(new_prefix, len ? "   " : " ");
		}
		show_containment(s, new_prefix, entPhysicalEntry,
				 entPhysicalEntry[i]->entPhysicalIndex);
		g_free(new_prefix);
	    }
	}
    }
}



static int
cmd_containment(scli_interp_t *interp, int argc, char **argv)
{
    entPhysicalEntry_t **entPhysicalTable = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (entity_mib_get_entPhysicalTable(interp->peer, &entPhysicalTable)) {
	return SCLI_ERROR;
    }

    if (entPhysicalTable) {
	show_containment(interp->result, "", entPhysicalTable, 0);
	entity_mib_free_entPhysicalTable(entPhysicalTable);
    }
    
    return SCLI_OK;
}



static void
show_component(GString *s, entPhysicalEntry_t *entPhysicalEntry)
{
    if (entPhysicalEntry->entPhysicalDescr) {
	g_string_sprintfa(s, "%.*s\n",
		    (int) entPhysicalEntry->_entPhysicalDescrLength,
			  entPhysicalEntry->entPhysicalDescr);
    }
    
    if (entPhysicalEntry->entPhysicalName) {
	g_string_sprintfa(s, "Name:   %-30.*s",
		    (int) entPhysicalEntry->_entPhysicalNameLength,
			  entPhysicalEntry->entPhysicalName);
    } else {
	g_string_sprintfa(s, "Name:   %-30s", "");
    }
    g_string_sprintfa(s, "Class:  ");
    fmt_enum(s, 1, entity_mib_enums_entPhysicalClass,
	     entPhysicalEntry->entPhysicalClass);
    if (entPhysicalEntry->entPhysicalIsFRU) {
	if (*entPhysicalEntry->entPhysicalIsFRU == 2) {
	    g_string_append(s, " (replaceable)");
	}
    }
    g_string_append(s, "\n");
    
    if (entPhysicalEntry->entPhysicalMfgName) {
	g_string_sprintfa(s, "Vendor: %-30.*s",
		    (int) entPhysicalEntry->_entPhysicalMfgNameLength,
			  entPhysicalEntry->entPhysicalMfgName);
    } else {
	g_string_sprintfa(s, "Vendor: %-30s", "");
    }
    if (entPhysicalEntry->entPhysicalHardwareRev) {
	g_string_sprintfa(s, "HW Rev: %-30.*s\n",
		    (int) entPhysicalEntry->_entPhysicalHardwareRevLength,
			  entPhysicalEntry->entPhysicalHardwareRev);
    } else {
	g_string_sprintfa(s, "HW Rev:\n");
    }
    
    if (entPhysicalEntry->entPhysicalModelName) {
	g_string_sprintfa(s, "Model:  %-30.*s",
		    (int) entPhysicalEntry->_entPhysicalModelNameLength,
			  entPhysicalEntry->entPhysicalModelName);
    } else {
	g_string_sprintfa(s, "Model:  %-30s", "");
    }
    if (entPhysicalEntry->entPhysicalFirmwareRev) {
	g_string_sprintfa(s, "FW Rev: %-30.*s\n",
		    (int) entPhysicalEntry->_entPhysicalFirmwareRevLength,
			  entPhysicalEntry->entPhysicalFirmwareRev);
    } else {
	g_string_sprintfa(s, "FW Rev:\n");
    }
    
    if (entPhysicalEntry->entPhysicalSerialNum) {
	g_string_sprintfa(s, "Serial: %-30.*s",
		    (int) entPhysicalEntry->_entPhysicalSerialNumLength,
			  entPhysicalEntry->entPhysicalSerialNum);
    } else {
	g_string_sprintfa(s, "Serial: %-30s", "");
    }
    if (entPhysicalEntry->entPhysicalSoftwareRev) {
	g_string_sprintfa(s, "SW Rev: %-30.*s\n",
		    (int) entPhysicalEntry->_entPhysicalSoftwareRevLength,
			  entPhysicalEntry->entPhysicalSoftwareRev);
    } else {
	g_string_sprintfa(s, "SW Rev:\n");
    }
    
    if (entPhysicalEntry->entPhysicalAlias) {
	g_string_sprintfa(s, "Alias:  %-30.*s",
		    (int) entPhysicalEntry->_entPhysicalAliasLength,
			  entPhysicalEntry->entPhysicalAlias);
    } else {
	g_string_sprintfa(s, "Alias:  %-30s", "");
    }
    if (entPhysicalEntry->entPhysicalAssetID) {
	g_string_sprintfa(s, "Asset:  %.*s\n",
		    (int) entPhysicalEntry->_entPhysicalAssetIDLength,
			  entPhysicalEntry->entPhysicalAssetID);
    } else {
	g_string_append(s, "Asset:\n");
    }
}



static int
cmd_components(scli_interp_t *interp, int argc, char **argv)
{
    entPhysicalEntry_t **entPhysicalTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (entity_mib_get_entPhysicalTable(interp->peer, &entPhysicalTable)) {
	return SCLI_ERROR;
    }

    if (entPhysicalTable) {
	for (i = 0; entPhysicalTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_component(interp->result, entPhysicalTable[i]);
	}
	entity_mib_free_entPhysicalTable(entPhysicalTable);
    }
    
    return SCLI_OK;
}



void
scli_init_entity_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show system components",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "physical components of the system",
	  cmd_components },
	{ "show system containment",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "physical component's containment hierarchy",
	  cmd_containment },
	{ NULL, 0, NULL, NULL }
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
