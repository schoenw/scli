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

    if (ifEntry && ifEntry->ifDescr) {
	g_string_sprintfa(s, "%.*s",
			  (int) ifEntry->_ifDescrLength, ifEntry->ifDescr);
    }

    g_string_append(s, "\n");
}



static int
show_atm_interface_info(scli_interp_t *interp, int argc, char **argv)
{
    atm_mib_atmInterfaceConfEntry_t **atmInterfaceConfTable = NULL;
    regex_t _regex_iface, *regex_iface = NULL;
    int i;
    GError *error = NULL;
    
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
				      &atmInterfaceConfTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (atmInterfaceConfTable) {
	g_string_append(interp->header,
			"INTERFACE MAX-VPCS MAX-VCCS DESCRIPTION");
	for (i = 0; atmInterfaceConfTable[i]; i++) {
	    if_mib_ifEntry_t *ifEntry = NULL;
	    if_mib_get_ifEntry(interp->peer, &ifEntry,
			       atmInterfaceConfTable[i]->ifIndex,
			       IF_MIB_IFDESCR, NULL);
	    if (! ifEntry) continue;
	    if (interface_match(regex_iface, ifEntry)) {
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

    tree = xml_new_child(root, NULL, BAD_CAST("interface"), NULL);
    xml_set_prop(tree, BAD_CAST("index"), "%d", atmIfaceConfEntry->ifIndex);
    
    if (atmIfaceConfEntry->atmInterfaceMaxVpcs) {
	(void) xml_new_child(tree, NULL, BAD_CAST("max-vpcs"), "%d",
			     *atmIfaceConfEntry->atmInterfaceMaxVpcs);
    }

    if (atmIfaceConfEntry->atmInterfaceMaxVccs) {
	(void) xml_new_child(tree, NULL, BAD_CAST("max-vccs"), "%d",
			     *atmIfaceConfEntry->atmInterfaceMaxVccs);
    }

    if (atmIfaceConfEntry->atmInterfaceConfVpcs) {
	(void) xml_new_child(tree, NULL, BAD_CAST("conf-vpcs"), "%d",
			     *atmIfaceConfEntry->atmInterfaceConfVpcs);
    }

    if (atmIfaceConfEntry->atmInterfaceConfVccs) {
	(void) xml_new_child(tree, NULL, BAD_CAST("conf-vccs"), "%d",
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
    regex_t _regex_iface, *regex_iface = NULL;
    int i, c;
    GError *error = NULL;
    
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
				      &atmInterfaceConfTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (atmInterfaceConfTable) {
	for (i = 0, c= 0; atmInterfaceConfTable[i]; i++) {
	    if_mib_ifEntry_t *ifEntry = NULL;
	    if_mib_get_ifEntry(interp->peer, &ifEntry,
			       atmInterfaceConfTable[i]->ifIndex,
			       IF_MIB_IFDESCR, NULL);
	    if (interface_match(regex_iface, ifEntry)) {
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
	  "The `show atm interface info' command displays summary\n"
	  "information for all selected ATM interfaces. The optional\n"
	  "regular expression <regexp> is matched against the interface\n"
	  "descriptions to select the interfaces of interest. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  INTERFACE   network interface number\n"
          "  DESCRIPTION description of the network interface",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_atm_interface_info },
	
	{ "show atm interface details", "<regexp>",
	  "The `show atm interface details' command describes the selected\n"
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
