/* 
 * graph.c -- scli graph mode implementation
 *
 * Copyright (C) 2010 Juergen Schoenwaelder
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
 * @(#) $Id: entity.c 3180 2009-07-29 22:36:13Z schoenw $
 */

#include "scli.h"

#include "snmpv2-tc.h"
#include "entity-mib.h"
#include "if-mib.h"
#include "ianaiftype-mib.h"

#include "if-mib-proc.h"
#include "ianaiftype-mib-proc.h"

#define IF_MIB_IFENTRY_PARAMS \
	( IF_MIB_IFDESCR | IF_MIB_IFTYPE | IF_MIB_IFMTU | IF_MIB_IFSPEED \
	  | IF_MIB_IFPHYSADDRESS | IF_MIB_IFADMINSTATUS | IF_MIB_IFOPERSTATUS \
	  | IF_MIB_IFLASTCHANGE )

#define ENTITY_MIB_ENTPHYSICAL_MASK \
	( ENTITY_MIB_ENTPHYSICALDESCR | ENTITY_MIB_ENTPHYSICALCLASS \
	  | ENTITY_MIB_ENTPHYSICALCONTAINEDIN )


static entity_mib_entPhysicalEntry_t*
get_entity(gint32 ifIndex,
	   entity_mib_entAliasMappingEntry_t **entAliasMappingTable,
	   entity_mib_entPhysicalEntry_t **entPhysicalTable)
{
    int i;
    static const gint32 ifIndex_base[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 1};
    static const int ifIndex_base_len = sizeof(ifIndex_base)/sizeof(guint32);
    gint32 entPhysicalIndex = 0;

    if (! entAliasMappingTable || ! entPhysicalTable) {
	return 0;
    }

    /*
     * This piece of code does not really handle logical entities other
     * than the zero default logical entity.
     */

    for (i = 0; entAliasMappingTable[i]; i++) {
	if (entAliasMappingTable[i]->entAliasLogicalIndexOrZero) {
	    continue;
	}
	if (entAliasMappingTable[i]->_entAliasMappingIdentifierLength
	    == ifIndex_base_len + 1) {
	    if (memcmp(entAliasMappingTable[i]->entAliasMappingIdentifier,
		       ifIndex_base, sizeof(ifIndex_base)) == 0) {
		if (entAliasMappingTable[i]->entAliasMappingIdentifier[ifIndex_base_len] == ifIndex) {
		    entPhysicalIndex = entAliasMappingTable[i]->entPhysicalIndex;
		    break;
		}
	    }
	}
    }

    if (entPhysicalIndex) {
	for (i = 0; entPhysicalTable[i]; i++) {
	    if (entPhysicalTable[i]->entPhysicalIndex == entPhysicalIndex) {
		return entPhysicalTable[i];
	    }
	}
    }

    return NULL;
}



static int
show_graph(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifStackEntry_t **ifStackTable = NULL;
    entity_mib_entPhysicalEntry_t **entPhysicalTable = NULL;
    entity_mib_entAliasMappingEntry_t **entAliasMappingTable = NULL;
    int i;
    GError *error = NULL;

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    if_mib_get_ifStackTable(interp->peer, &ifStackTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if_mib_proc_get_ifTable(interp->peer, &ifTable,
			    IF_MIB_IFENTRY_PARAMS, interp->epoch, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    entity_mib_get_entAliasMappingTable(interp->peer,
					&entAliasMappingTable, 0, NULL);
    if (!interp->peer->error_status && entAliasMappingTable) {
	entity_mib_get_entPhysicalTable(interp->peer, &entPhysicalTable,
					ENTITY_MIB_ENTPHYSICAL_MASK, NULL);
    }
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    g_string_sprintfa(interp->result, "digraph entityinterfaces {\n\n");
    g_string_sprintfa(interp->result, "  splines=true;\n");
    g_string_sprintfa(interp->result, "  nodesep=0.5;\n");
    g_string_sprintfa(interp->result, "  label=\"[%s] physical entity and interfaces graph\";\n\n",
	      gnet_snmp_taddress_get_short_name(interp->peer->taddress));
	
    if (entPhysicalTable) {
	
	for (i = 0; entPhysicalTable[i]; i++) {
	    const char *class;
	    class = fmt_enum(entity_mib_enums_PhysicalClass,
			     entPhysicalTable[i]->entPhysicalClass);
	    g_string_sprintfa(interp->result,
			      "  \"e%d\" [label=\"%.*s\\n(#%d - %s)\",color=black,shape=box];\n",
	      entPhysicalTable[i]->entPhysicalIndex,
	      entPhysicalTable[i]->entPhysicalDescr ? (int) entPhysicalTable[i]->_entPhysicalDescrLength : 0,
	      entPhysicalTable[i]->entPhysicalDescr,
	      entPhysicalTable[i]->entPhysicalIndex,
	      class ? class : "");
	}

	for (i = 0; entPhysicalTable[i]; i++) {
	    if (entPhysicalTable[i]->entPhysicalContainedIn &&
		*(entPhysicalTable[i]->entPhysicalContainedIn)) {
		g_string_sprintfa(interp->result,
			  "  \"e%d\" -> \"e%d\";\n",
			  *(entPhysicalTable[i]->entPhysicalContainedIn),
			  entPhysicalTable[i]->entPhysicalIndex);
	    }
	}
    }

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    char const *label = NULL;
	    if (ifTable[i]->ifType) {
		label = gnet_snmp_enum_get_label(ianaiftype_mib_enums_IANAifType,
						 *ifTable[i]->ifType);
	    }
	    g_string_sprintfa(interp->result,
	      "  \"i%d\" [label=\"%.*s\\n(#%d - %s)\",color=blue];\n",
	      ifTable[i]->ifIndex,
	      ifTable[i]->ifDescr ? (int) ifTable[i]->_ifDescrLength : 0,
	      ifTable[i]->ifDescr,
	      ifTable[i]->ifIndex,
	      label ? label : "");
	}
    }

    if (ifStackTable) {

	for (i = 0; ifStackTable[i]; i++) {
	    entity_mib_entPhysicalEntry_t *entPhysicalEntry = NULL;
	    
	    if (ifStackTable[i]->ifStackLowerLayer == 0) {
		entPhysicalEntry = get_entity(ifStackTable[i]->ifStackHigherLayer,
					      entAliasMappingTable, entPhysicalTable);
		if (entPhysicalEntry) {
		    g_string_sprintfa(interp->result, "  \"e%d\" -> \"i%d\";\n",
				      entPhysicalEntry->entPhysicalIndex,
				      ifStackTable[i]->ifStackHigherLayer);
		}
		continue;
	    }
	    if (ifStackTable[i]->ifStackHigherLayer == 0) {
		continue;
	    }
	    
	    g_string_sprintfa(interp->result, "  \"i%d\" -> \"i%d\";\n", 
		    ifStackTable[i]->ifStackLowerLayer,
		    ifStackTable[i]->ifStackHigherLayer);
	}

    }
    
    g_string_sprintfa(interp->result, "\n}\n");
    
    if (ifStackTable) if_mib_free_ifStackTable(ifStackTable);
    if (ifTable) if_mib_proc_free_ifTable(ifTable);
    
    if (entAliasMappingTable)
	entity_mib_free_entAliasMappingTable(entAliasMappingTable);
    if (entPhysicalTable)
	entity_mib_free_entPhysicalTable(entPhysicalTable);

    return SCLI_OK;
}



void
scli_init_graph_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show graph", NULL,
	  "The `show graph' command displays the physical entity and\n"
	  "interface hierarchy.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_graph },
	
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t entity_mode = {
	"graph",
	"The graph scli mode is based on the ENTITY-MIB as published in\n"
	"RFC 2737. It provides commands to browse the physical entities\n"
	"or physical components that make up a managed system.",
	cmds
    };
    
    scli_register_mode(interp, &entity_mode);
}
