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

#include "scli.h"

#include "entity-mib.h"


static void
fmt_containment(GString *s, char *prefix,
		entity_mib_entPhysicalEntry_t **entPhysicalEntry,
		gint32 parent, int class_width)
{
    int i, j;
    size_t len;
    const char *class;

    if (! entPhysicalEntry) {
	return;
    }

    len = strlen(prefix);
    for (i = 0; entPhysicalEntry[i]; i++) {
	if (entPhysicalEntry[i]->entPhysicalContainedIn
	    && *(entPhysicalEntry[i]->entPhysicalContainedIn) == parent) {
	    int next = 0;
	    if (parent) {
		for (j = i+1; entPhysicalEntry[j]; j++) {
		    if (entPhysicalEntry[j]->entPhysicalContainedIn
			&& entPhysicalEntry[i]->entPhysicalIndex
			&& *(entPhysicalEntry[j]->entPhysicalContainedIn)
			== parent) {
			next = 1;
			break;
		    }
		}
	    }
	    
	    g_string_sprintfa(s, "%6d",
			      entPhysicalEntry[i]->entPhysicalIndex);

	    class = fmt_enum(entity_mib_enums_entPhysicalClass,
			     entPhysicalEntry[i]->entPhysicalClass);
	    g_string_sprintfa(s, " %-*s", class_width, class ? class : "");

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
		fmt_containment(s, new_prefix, entPhysicalEntry,
				entPhysicalEntry[i]->entPhysicalIndex,
				class_width);
		g_free(new_prefix);
	    }
	}
    }
}



static int
show_entity_containment(scli_interp_t *interp, int argc, char **argv)
{
    entity_mib_entPhysicalEntry_t **entPhysicalTable = NULL;
    int class_width = 6;
    int i;
    const char *class;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    entity_mib_get_entPhysicalTable(interp->peer, &entPhysicalTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (entPhysicalTable) {
	for (i = 0; entPhysicalTable[i]; i++) {
	    class = fmt_enum(entity_mib_enums_entPhysicalClass,
			     entPhysicalTable[i]->entPhysicalClass);
	    if (strlen(class) > class_width) {
		class_width = strlen(class);
	    }
	}
	g_string_sprintfa(interp->header, "ENTITY %-*s CONTAINMENT",
			  class_width, "CLASS");
	fmt_containment(interp->result, "", entPhysicalTable, 0, class_width);
    }

    if (entPhysicalTable) entity_mib_free_entPhysicalTable(entPhysicalTable);
    
    return SCLI_OK;
}



static void
fmt_entity_details(GString *s, entity_mib_entPhysicalEntry_t *entPhysicalEntry)
{
    const char *class;
    
    g_string_sprintfa(s, "Entity: %-*d", 30,
		      entPhysicalEntry->entPhysicalIndex);
    
    if (entPhysicalEntry->entPhysicalName) {
	g_string_sprintfa(s, "Name:   %.*s\n",
		    (int) entPhysicalEntry->_entPhysicalNameLength,
			  entPhysicalEntry->entPhysicalName);
    } else {
	g_string_sprintfa(s, "Name:\n");
    }
    
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
    
    if (entPhysicalEntry->entPhysicalAssetID) {
	g_string_sprintfa(s, "Asset:  %-30.*s",
		    (int) entPhysicalEntry->_entPhysicalAssetIDLength,
			  entPhysicalEntry->entPhysicalAssetID);
    } else {
	g_string_sprintfa(s, "Asset:  %-30s", "");
    }

    class = fmt_enum(entity_mib_enums_entPhysicalClass,
		     entPhysicalEntry->entPhysicalClass);
    if (class) {
	g_string_sprintfa(s, "Class:  %s", class);
	if (entPhysicalEntry->entPhysicalIsFRU) {
	    if (*entPhysicalEntry->entPhysicalIsFRU == 2) {
		g_string_append(s, " (replaceable)");
	    }
	}
	g_string_append(s, "\n");
    }
    
    fmt_display_string(s, 8, "Alias:",
		       (int) entPhysicalEntry->_entPhysicalAliasLength,
		       entPhysicalEntry->entPhysicalAlias);
    fmt_display_string(s, 8, "Descr:",
		       (int) entPhysicalEntry->_entPhysicalDescrLength,
		       entPhysicalEntry->entPhysicalDescr);
}



static void
xml_entity_details(xmlNodePtr root,
		   entity_mib_entPhysicalEntry_t *entPhysicalEntry)
{
    xmlNodePtr tree;
    const char *e;

    tree = xmlNewChild(root, NULL, "entity", NULL);
    xml_set_prop(tree, "index", "%d", entPhysicalEntry->entPhysicalIndex);
    
    if (entPhysicalEntry->entPhysicalDescr) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			     (int) entPhysicalEntry->_entPhysicalDescrLength,
			     entPhysicalEntry->entPhysicalDescr);
    }

    if (entPhysicalEntry->entPhysicalName) {
	(void) xml_new_child(tree, NULL, "name", "%.*s",
			     (int) entPhysicalEntry->_entPhysicalNameLength,
			     entPhysicalEntry->entPhysicalName);
    }

    e = fmt_enum(entity_mib_enums_entPhysicalClass,
		 entPhysicalEntry->entPhysicalClass);
    if (e) {
	(void) xml_new_child(tree, NULL, "class", "%s", e);
    }

    if (entPhysicalEntry->entPhysicalContainedIn) {
	(void) xml_new_child(tree, NULL, "contained-in", "%d",
			     *entPhysicalEntry->entPhysicalContainedIn);
    }

    if (entPhysicalEntry->entPhysicalIsFRU
	&& (*entPhysicalEntry->entPhysicalIsFRU
	    == ENTITY_MIB_ENTPHYSICALISFRU_TRUE)) {
	(void) xmlNewChild(tree, NULL, "replaceable", NULL);
    } 
 
    if (entPhysicalEntry->entPhysicalMfgName) {
	(void) xml_new_child(tree, NULL, "manufacturer", "%.*s",
			     (int) entPhysicalEntry->_entPhysicalMfgNameLength,
			     entPhysicalEntry->entPhysicalMfgName);
    }

    if (entPhysicalEntry->entPhysicalModelName) {
	(void) xml_new_child(tree, NULL, "model", "%.*s",
		       (int) entPhysicalEntry->_entPhysicalModelNameLength,
			     entPhysicalEntry->entPhysicalModelName);
    }
    
    if (entPhysicalEntry->entPhysicalSerialNum) {
	(void) xml_new_child(tree, NULL, "serial", "%.*s",
		       (int) entPhysicalEntry->_entPhysicalSerialNumLength,
			     entPhysicalEntry->entPhysicalSerialNum);
    }
    
    if (entPhysicalEntry->entPhysicalHardwareRev) {
	(void) xml_new_child(tree, NULL, "hardware-revision", "%.*s",
		       (int) entPhysicalEntry->_entPhysicalHardwareRevLength,
			     entPhysicalEntry->entPhysicalHardwareRev);
    }
    
    if (entPhysicalEntry->entPhysicalFirmwareRev) {
	(void) xml_new_child(tree, NULL, "firmware-revision", "%.*s",
		       (int) entPhysicalEntry->_entPhysicalFirmwareRevLength,
			     entPhysicalEntry->entPhysicalFirmwareRev);
    }
    
    if (entPhysicalEntry->entPhysicalSoftwareRev) {
	(void) xml_new_child(tree, NULL, "software-revision", "%.*s",
		       (int) entPhysicalEntry->_entPhysicalSoftwareRevLength,
			     entPhysicalEntry->entPhysicalSoftwareRev);
    }
    
    if (entPhysicalEntry->entPhysicalAlias) {
	(void) xml_new_child(tree, NULL, "alias", "%.*s",
			     (int) entPhysicalEntry->_entPhysicalAliasLength,
			     entPhysicalEntry->entPhysicalAlias);
    }
    if (entPhysicalEntry->entPhysicalAssetID) {
	(void) xml_new_child(tree, NULL, "asset","%.*s",
			     (int) entPhysicalEntry->_entPhysicalAssetIDLength,
			     entPhysicalEntry->entPhysicalAssetID);
    }
}



static int
show_entity_details(scli_interp_t *interp, int argc, char **argv)
{
    entity_mib_entPhysicalEntry_t **entPhysicalTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    entity_mib_get_entPhysicalTable(interp->peer, &entPhysicalTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (entPhysicalTable) {
	for (i = 0; entPhysicalTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_entity_details(interp->xml_node, entPhysicalTable[i]);
	    } else {
		if (i) {
		    g_string_append(interp->result, "\n");
		}
		fmt_entity_details(interp->result, entPhysicalTable[i]);
	    }
	}
    }

    if (entPhysicalTable) entity_mib_free_entPhysicalTable(entPhysicalTable);
    
    return SCLI_OK;
}



static void
fmt_entity_info(GString *s, entity_mib_entPhysicalEntry_t *entPhysicalEntry,
		int class_width, int name_width)
{
    const char *class;

    g_string_sprintfa(s, "%6d", entPhysicalEntry->entPhysicalIndex);
    
    class = fmt_enum(entity_mib_enums_entPhysicalClass,
		     entPhysicalEntry->entPhysicalClass);
    if (class) {
	g_string_sprintfa(s, " %-*s", class_width, class);
    } else {
	g_string_sprintfa(s, " %-*s", class_width, "");
    }
    
    if (entPhysicalEntry->entPhysicalName) {
	g_string_sprintfa(s, " %-*.*s", name_width,
		    (int) entPhysicalEntry->_entPhysicalNameLength,
			  entPhysicalEntry->entPhysicalName);
    } else {
	g_string_sprintfa(s, " %-*s", name_width, "");
    }

    if (entPhysicalEntry->entPhysicalDescr) {
	g_string_sprintfa(s, " %.*s",
		    (int) entPhysicalEntry->_entPhysicalDescrLength,
			  entPhysicalEntry->entPhysicalDescr);
    }
    g_string_append(s, "\n");
}



static int
show_entity_info(scli_interp_t *interp, int argc, char **argv)
{
    entity_mib_entPhysicalEntry_t **entPhysicalTable = NULL;
    int class_width = 6, name_width = 6;
    int i;
    const char *class;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    entity_mib_get_entPhysicalTable(interp->peer, &entPhysicalTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (entPhysicalTable) {
	for (i = 0; entPhysicalTable[i]; i++) {
	    class = fmt_enum(entity_mib_enums_entPhysicalClass,
			     entPhysicalTable[i]->entPhysicalClass);
	    if (strlen(class) > class_width) {
		class_width = strlen(class);
	    }
	    if (entPhysicalTable[i]->entPhysicalName
		&& entPhysicalTable[i]->_entPhysicalNameLength > name_width) {
		name_width = entPhysicalTable[i]->_entPhysicalNameLength;
	    }
	}
	g_string_sprintfa(interp->header,
			  "ENTITY %-*s %-*s DESCRIPTION",
			  class_width, "CLASS",
			  name_width, "NAME");
	for (i = 0; entPhysicalTable[i]; i++) {
	    fmt_entity_info(interp->result, entPhysicalTable[i],
			    class_width, name_width);
	}
    }

    if (entPhysicalTable) entity_mib_free_entPhysicalTable(entPhysicalTable);
    
    return SCLI_OK;
}



void
scli_init_entity_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show entity info", NULL,
	  "The show entity info command displays summary information about\n"
	  "the physical entities that compose the system. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  ENTITY      entity number\n"
	  "  CLASS       class of the entity (see below)\n"
	  "  NAME        name of the entity\n"
	  "  DESCRIPTION description of the entity",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_entity_info },
	
	{ "show entity details ", NULL,
	  "The show entity details command describes the physical entities\n"
	  "in more detail.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "entities physical", NULL,
	  show_entity_details },
	
	{ "show entity containment", NULL,
	  "The show entity containment command displays the physical entity\n"
	  "containment hierarchy.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_entity_containment },

#if 0
	{ "set entity serial", NULL,
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_entity_serial },

	{ "set entity alias", NULL,
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_entity_alias },

	{ "set entity asset", NULL,
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_entity_serial },

	{ "dump entity", NULL,
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_entity_serial },
#endif
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t entity_mode = {
	"entity",
	"The entity scli mode is based on the ENTITY-MIB as published in\n"
	"RFC 2737. It provides commands to browse the physical entities\n"
	"or physical components what make up a managed system.",
	cmds
    };
    
    scli_register_mode(interp, &entity_mode);
}
