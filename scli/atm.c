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

#include "scli.h"

#include "atm-mib.h"
#include "if-mib.h"



static int
match_interface(regex_t *regex_iface,
		if_mib_ifEntry_t *ifEntry)
{
    int status;

    if (! regex_iface) {
	return 1;
    }

    /*
     * Does it really make sense to filter only on the description?
     * This way, we do not need to read the ifXTable at all...
     */

    if (ifEntry->ifDescr) {
	char *s = g_strdup_printf("%.*s",
				  (int) ifEntry->_ifDescrLength,
				  ifEntry->ifDescr);
	status = regexec(regex_iface, s, (size_t) 0, NULL, 0);
	g_free(s);
	if (status == 0) {
	    return 1;
	}
    }

    return 0;
}



static void
fmt_atm_interface_info(GString *s,
		       atm_mib_atmInterfaceConfEntry_t *atmIfaceConfEntry,
		       if_mib_ifEntry_t *ifEntry)
{
    g_string_sprintfa(s, "%9u  ", atmIfaceConfEntry->ifIndex);

    if (atmIfaceConfEntry->atmInterfaceMaxVpcs) {
	g_string_sprintfa(s, "%6d   ",
			  *atmIfaceConfEntry->atmInterfaceMaxVpcs);
    }

    if (atmIfaceConfEntry->atmInterfaceMaxVccs) {
	g_string_sprintfa(s, "%6d  ",
			  *atmIfaceConfEntry->atmInterfaceMaxVccs);
    }

    if (ifEntry && ifEntry->ifDescr && ifEntry->_ifDescrLength) {
	g_string_sprintfa(s, "%.*s",
			  (int) ifEntry->_ifDescrLength, ifEntry->ifDescr);
    }

    g_string_append(s, "\n");
}



static int
show_atm_interface_info(scli_interp_t *interp, int argc, char **argv)
{
    atm_mib_atmInterfaceConfEntry_t **atmInterfaceConfTable = NULL;
    if_mib_ifEntry_t *ifEntry = NULL;
    regex_t _regex_iface, *regex_iface = NULL;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_OK;
    }

    atm_mib_get_atmInterfaceConfTable(interp->peer,
				      &atmInterfaceConfTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (atmInterfaceConfTable) {
	g_string_append(interp->header,
			"INTERFACE MAX-VPCS MAX-VCCS DESCRIPTION");
	for (i = 0; atmInterfaceConfTable[i]; i++) {
	    if_mib_get_ifEntry(interp->peer, &ifEntry,
			       atmInterfaceConfTable[i]->ifIndex,
			       IF_MIB_IFDESCR);
	    if (! ifEntry) continue;
	    if (match_interface(regex_iface, ifEntry)) {
		fmt_atm_interface_info(interp->result,
				       atmInterfaceConfTable[i], ifEntry);
	    }
	    if_mib_free_ifEntry(ifEntry);
	}
    }

    if (atmInterfaceConfTable)
	atm_mib_free_atmInterfaceConfTable(atmInterfaceConfTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



static void
xml_atm_interface_details(xmlNodePtr root,
			  atm_mib_atmInterfaceConfEntry_t *atmIfaceConfEntry,
			  if_mib_ifEntry_t *ifEntry)
{
    xmlNodePtr tree;

    tree = xmlNewChild(root, NULL, "interface", NULL);
    xml_set_prop(tree, "index", "%d", atmIfaceConfEntry->ifIndex);
    
    if (atmIfaceConfEntry->atmInterfaceMaxVpcs) {
	(void) xml_new_child(tree, NULL, "max-vpcs", "%d",
			     *atmIfaceConfEntry->atmInterfaceMaxVpcs);
    }

    if (atmIfaceConfEntry->atmInterfaceMaxVccs) {
	(void) xml_new_child(tree, NULL, "max-vccs", "%d",
			     *atmIfaceConfEntry->atmInterfaceMaxVccs);
    }

    if (atmIfaceConfEntry->atmInterfaceConfVpcs) {
	(void) xml_new_child(tree, NULL, "conf-vpcs", "%d",
			     *atmIfaceConfEntry->atmInterfaceConfVpcs);
    }

    if (atmIfaceConfEntry->atmInterfaceConfVccs) {
	(void) xml_new_child(tree, NULL, "conf-vccs", "%d",
			     *atmIfaceConfEntry->atmInterfaceConfVccs);
    }
}



static void
fmt_atm_interface_details(GString *s,
			  atm_mib_atmInterfaceConfEntry_t *atmIfaceConfEntry,
			  if_mib_ifEntry_t *ifEntry)
{
    const int indent = 18;
    
    g_string_sprintfa(s, "%-*s%u\n", indent, "Interface:",
		      atmIfaceConfEntry->ifIndex);

    if (atmIfaceConfEntry->atmInterfaceMaxVpcs) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Maximum VPCs:",
			  *atmIfaceConfEntry->atmInterfaceMaxVpcs);
    }

    if (atmIfaceConfEntry->atmInterfaceMaxVccs) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Maximum VCCs:",
			  *atmIfaceConfEntry->atmInterfaceMaxVccs);
    }

    if (atmIfaceConfEntry->atmInterfaceConfVpcs) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Configured VPCs:",
			  *atmIfaceConfEntry->atmInterfaceConfVpcs);
    }

    if (atmIfaceConfEntry->atmInterfaceConfVccs) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Configured VCCs:",
			  *atmIfaceConfEntry->atmInterfaceConfVccs);
    }

    if (atmIfaceConfEntry->atmInterfaceMaxActiveVpiBits) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Active VPI Bits:",
			  *atmIfaceConfEntry->atmInterfaceMaxActiveVpiBits);
    }

    if (atmIfaceConfEntry->atmInterfaceMaxActiveVciBits) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Active VCI Bits:",
			  *atmIfaceConfEntry->atmInterfaceMaxActiveVciBits);
    }

    if (atmIfaceConfEntry->atmInterfaceIlmiVpi
	&& atmIfaceConfEntry->atmInterfaceIlmiVci) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Active ILMI VPI:",
			  *atmIfaceConfEntry->atmInterfaceIlmiVpi);
	g_string_sprintfa(s, "%-*s%d\n", indent, "Active ILMI VCI:",
			  *atmIfaceConfEntry->atmInterfaceIlmiVci);
    }

    if (ifEntry->ifDescr && ifEntry->_ifDescrLength) {
	g_string_sprintfa(s, "%-*s%.*s\n", indent, "Description:",
			  (int) ifEntry->_ifDescrLength,
			  ifEntry->ifDescr);
    }
}



static int
show_atm_interface_details(scli_interp_t *interp, int argc, char **argv)
{
    atm_mib_atmInterfaceConfEntry_t **atmInterfaceConfTable = NULL;
    if_mib_ifEntry_t *ifEntry = NULL;
    regex_t _regex_iface, *regex_iface = NULL;
    int i, c;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_OK;
    }

    atm_mib_get_atmInterfaceConfTable(interp->peer,
				      &atmInterfaceConfTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (atmInterfaceConfTable) {
	for (i = 0, c= 0; atmInterfaceConfTable[i]; i++) {
	    if_mib_get_ifEntry(interp->peer, &ifEntry,
			       atmInterfaceConfTable[i]->ifIndex,
			       IF_MIB_IFDESCR);
	    if (! ifEntry) continue;
	    if (match_interface(regex_iface, ifEntry)) {
		if (scli_interp_xml(interp)) {
		    xml_atm_interface_details(interp->xml_node,
					      atmInterfaceConfTable[i],
					      ifEntry);
		} else {
		    if (c) {
			g_string_append(interp->result, "\n");
		    }
		    fmt_atm_interface_details(interp->result,
					      atmInterfaceConfTable[i],
					      ifEntry);
		}
		c++;
	    }
	    if_mib_free_ifEntry(ifEntry);
	}
    }

    if (atmInterfaceConfTable)
	atm_mib_free_atmInterfaceConfTable(atmInterfaceConfTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



void
scli_init_atm_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show atm interface info", "<regexp>",
	  "The show atm interface info command displays summary\n"
	  "information for all selected ATM interfaces. The optional\n"
	  "regular expression <regexp> is matched against the interface\n"
	  "descriptions to select the interfaces of interest. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  INTERFACE network interface number",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_atm_interface_info },
	
	{ "show atm interface details", "<regexp>",
	  "The show atm interface details command describes the selected\n"
	  "ATM interfaces in more detail. The optional regular expression\n"
	  "<regexp> is matched against the interface descriptions to\n"
	  "select the interfaces of interest.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "atm interfaces", NULL,
	  show_atm_interface_details },
	
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t atm_mode = {
	"atm",
	"The atm scli mode is based on the ATM-MIB as published in RFC 2515.\n"
	"This mode is intended to display and configure ATM parameters.",
	cmds
    };
    
    scli_register_mode(interp, &atm_mode);
}
