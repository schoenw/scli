/* 
 * nortel.c -- scli nortel mode implementation
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

#include "rapidcity-vlan-mib.h"

#include <regex.h>


static GSnmpEnum const vlan_priority[] = {
    { RAPIDCITY_VLAN_MIB_RCVLANHIGHPRIORITY_TRUE,	"high" },
    { RAPIDCITY_VLAN_MIB_RCVLANHIGHPRIORITY_FALSE,	"normal" },
    { 0, NULL }
};



static void
vlan_error(scli_interp_t *interp,
	   rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry)
{
    g_string_sprintfa(interp->result, "vlan %d: ", vlanEntry->rcVlanId);
    if (vlanEntry->rcVlanName) {
	g_string_sprintfa(interp->result, "%.*s: ",
			  (int) vlanEntry->_rcVlanNameLength,
			  vlanEntry->rcVlanName);
    }
}



static void
vlan_snmp_error(scli_interp_t *interp,
		rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry)
{
    vlan_error(interp, vlanEntry);
    scli_snmp_error(interp);
    g_string_append(interp->result, "\n");
}



static int
match_vlan(regex_t *regex_vlan,
	   rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry)
{
    int status;
    
    if (! regex_vlan) {
	return 1;
    }

    if (vlanEntry->rcVlanName) {
	char *string = g_malloc0(vlanEntry->_rcVlanNameLength + 1);
	memcpy(string, vlanEntry->rcVlanName, vlanEntry->_rcVlanNameLength);
	status = regexec(regex_vlan, string, (size_t) 0, NULL, 0);
	g_free(string);
	if (status == 0) {
	    return 1;
	}
    }

    return 0;
}



static void
fmt_ports(GString *s, guchar *bits, gsize bits_len)
{
    int bit, i;
    int first = -1;
    int n = 0;

    for (i = 0; i < bits_len * 8; i++) {
	bit = bits[i/8] & 1 << (7-(i%8));
	if (bit) {
	    if (first < 0) {
		first = i;
	    }
	} else {
	    if (first >= 0) {
		if (n) {
		    g_string_append_c(s, ',');
		}
		if (first == i-1) {
		    g_string_sprintfa(s, "%d", first);
		} else {
		    g_string_sprintfa(s, "%d-%d", first, i-1);
		}
		n++;
	    }
	    first = -1;
	}
    }
    if (first >= 0) {
	g_string_sprintfa(s, "%s%d-%d", n ? ", " : "", first, i-1);
    }
}



static int
scan_ports(guchar *bits, gsize bits_len, char *string)
{
    char *p = string;
    int i, from, to, off;

    memset(bits, 0, bits_len);
    while (*p) {
	if (sscanf(p, "%d-%d%n", &from, &to, &off) == 2) {
	    p += off;
	} else if (sscanf(p, "%d%n", &from, &off) == 1) {
	    p += off;
	    to = from;
	} else {
	    memset(bits, 0, bits_len);
	    return SCLI_ERROR;
	}
	if (from < 0 || to >= bits_len*8) {
	    memset(bits, 0, bits_len);
	    return SCLI_ERROR;
	}
	for (i = from; i < to+1; i++) {
	    bits[i/8] |= (1 <<(7-(i%8)));
	}
	if (*p == ',') p++;
    }

    return SCLI_OK;
}



static int
get_vlan_name_width(rapidcity_vlan_mib_rcVlanEntry_t **vlanTable)
{
    int i, name_width = 6;
    
    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (vlanTable[i]->_rcVlanNameLength > name_width) {
		name_width = vlanTable[i]->_rcVlanNameLength;
	    }
	}
    }
    return name_width;
}



static int
get_vlan_type_width(rapidcity_vlan_mib_rcVlanEntry_t **vlanTable)
{
    int i, type_width = 6;
    
    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (vlanTable[i]->rcVlanType) {
		char const *label;
		label = gsnmp_enum_get_label(rapidcity_vlan_mib_enums_rcVlanType,
					     *vlanTable[i]->rcVlanType);
		if (label && strlen(label) > type_width) {
		    type_width = strlen(label);
		}
	    }
	}
    }
    return type_width;
}



static void
xml_nortel_baystack_vlan_details(xmlNodePtr root,
				 rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry)
{
    xmlNodePtr tree, node;
    const char *s;

    tree = xmlNewChild(root, NULL, "vlan", NULL);
    xml_set_prop(tree, "vlanid", "%d", vlanEntry->rcVlanId);

    if (vlanEntry->rcVlanName) {
	node = xmlNewChild(tree, NULL, "name", NULL);
	xml_set_content(node, "%.*s",
			(int) vlanEntry->_rcVlanNameLength,
			vlanEntry->rcVlanName);
    }

    s = fmt_enum(rapidcity_vlan_mib_enums_rcVlanType, vlanEntry->rcVlanType);
    if (s) {
	node = xmlNewChild(tree, NULL, "type", s);
    }

    if (vlanEntry->rcVlanColor) {
	node = xmlNewChild(tree, NULL, "color", NULL);
	xml_set_content(node, "%d", *vlanEntry->rcVlanColor);
    }

    s = fmt_enum(vlan_priority, vlanEntry->rcVlanHighPriority);
    if (s) {
	node = xmlNewChild(tree, NULL, "priority", s);
    }

    s = fmt_enum(rapidcity_vlan_mib_enums_rcVlanRoutingEnable,
		 vlanEntry->rcVlanRoutingEnable);
    if (s) {
	node = xmlNewChild(tree, NULL, "routing", s);
    }

    s = fmt_enum(rapidcity_vlan_mib_enums_rcVlanRowStatus,
		 vlanEntry->rcVlanRowStatus);
    if (s) {
	node = xmlNewChild(tree, NULL, "status", s);
    }
}



static void
fmt_nortel_baystack_vlan_details(GString *s,
				 rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry)
{
    const int width = 20;

    g_string_sprintfa(s, "VLan:        %-*d", width, vlanEntry->rcVlanId);
    if (vlanEntry->rcVlanName && vlanEntry->_rcVlanNameLength) {
	g_string_sprintfa(s, " Name:     %.*s\n",
			  (int) vlanEntry->_rcVlanNameLength,
			  vlanEntry->rcVlanName);
    } else {
	g_string_append(s, " Name:\n");
    }

    g_string_append(s, "Type:        ");
    xxx_enum(s, width, rapidcity_vlan_mib_enums_rcVlanType,
	     vlanEntry->rcVlanType);

    if (vlanEntry->rcVlanType
	&& *vlanEntry->rcVlanType == RAPIDCITY_VLAN_MIB_RCVLANTYPE_BYPORT) {
	if (vlanEntry->rcVlanPortMembers) {
	    g_string_append(s, "\nMember:      ");
	    fmt_ports(s, vlanEntry->rcVlanPortMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
	if (vlanEntry->rcVlanStaticMembers) {
	    g_string_append(s, "Static:      ");
	    fmt_ports(s, vlanEntry->rcVlanStaticMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
	if (vlanEntry->rcVlanPotentialMembers) {
	    g_string_append(s, "Allowed:     ");
	    fmt_ports(s, vlanEntry->rcVlanPotentialMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
	if (vlanEntry->rcVlanNotAllowToJoin) {
	    g_string_append(s, "Disallowed:  ");
	    fmt_ports(s, vlanEntry->rcVlanNotAllowToJoin, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
    }

    if (vlanEntry->rcVlanType
	&& (*vlanEntry->rcVlanType
	    == RAPIDCITY_VLAN_MIB_RCVLANTYPE_BYPROTOCOLID)) {
	if (vlanEntry->rcVlanProtocolId) {
	    g_string_append(s, " Protocol: ");
	    xxx_enum(s, width, rapidcity_vlan_mib_enums_rcVlanProtocolId,
		     vlanEntry->rcVlanProtocolId);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
    }
}



static int
show_nortel_baystack_vlan_details(scli_interp_t *interp, int argc, char **argv)
{
    rapidcity_vlan_mib_rcVlanEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i, c;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_vlan = &_regex_vlan;
	if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX;
	}
    }

    if (rapidcity_vlan_mib_get_rcVlanTable(interp->peer, &vlanTable)) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_ERROR;
    }

    if (vlanTable) {	
	for (i = 0, c = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		if (scli_interp_xml(interp)) {
		    xml_nortel_baystack_vlan_details(interp->xml_node,
						     vlanTable[i]);
		} else {
		    if (c) {
			g_string_append(interp->result, "\n");
		    }
		    fmt_nortel_baystack_vlan_details(interp->result,
						     vlanTable[i]);
		    c++;
		}
	    }
	}
    }

    if (vlanTable) rapidcity_vlan_mib_free_rcVlanTable(vlanTable);
    if (regex_vlan) regfree(regex_vlan);
    
    return SCLI_OK;
}



static void
fmt_nortel_baystack_vlan_info(GString *s,
			      rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry,
			      int name_width, int type_width)
{
    g_string_sprintfa(s, "%4d ", vlanEntry->rcVlanId);

    if (vlanEntry->rcVlanName && vlanEntry->_rcVlanNameLength) {
	g_string_sprintfa(s, "%-*.*s ", name_width,
			  (int) vlanEntry->_rcVlanNameLength,
			  vlanEntry->rcVlanName);
    } else {
	g_string_sprintfa(s, "%*s ", name_width, "");
    }

    xxx_enum(s, type_width, rapidcity_vlan_mib_enums_rcVlanType,
	     vlanEntry->rcVlanType);

    if (vlanEntry->rcVlanColor) {
	g_string_sprintfa(s, " %4d   ", *vlanEntry->rcVlanColor);
    } else {
	g_string_append(s, "        ");
    }

    xxx_enum(s, 9, vlan_priority,
	     vlanEntry->rcVlanHighPriority);

    xxx_enum(s, 7, rapidcity_vlan_mib_enums_rcVlanRoutingEnable,
	     vlanEntry->rcVlanRoutingEnable);
    
    xxx_enum(s, 8, rapidcity_vlan_mib_enums_rcVlanRowStatus,
	     vlanEntry->rcVlanRowStatus);

    g_string_append(s, "\n");
}



static int
show_nortel_baystack_vlan_info(scli_interp_t *interp, int argc, char **argv)
{
    rapidcity_vlan_mib_rcVlanEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i, name_width, type_width;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_vlan = &_regex_vlan;
	if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX;
	}
    }

    if (rapidcity_vlan_mib_get_rcVlanTable(interp->peer, &vlanTable)) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_ERROR;
    }

    name_width = get_vlan_name_width(vlanTable);
    type_width = get_vlan_type_width(vlanTable);

    if (vlanTable) {
	g_string_sprintfa(interp->header,
			  "VLAN %-*s %-*s COLOR PRIORITY ROUTING STATUS",
			  name_width, "NAME", type_width, "TYPE");
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		fmt_nortel_baystack_vlan_info(interp->result, vlanTable[i],
					      name_width, type_width);
	    }
	}
    }

    if (vlanTable) rapidcity_vlan_mib_free_rcVlanTable(vlanTable);
    if (regex_vlan) regfree(regex_vlan);
    
    return SCLI_OK;
}



static int
delete_vlan(scli_interp_t *interp,
	    rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry)
{
    rapidcity_vlan_mib_rcVlanEntry_t *xx;
    gint32 row_status = RAPIDCITY_VLAN_MIB_RCVLANROWSTATUS_DESTROY;

    xx = rapidcity_vlan_mib_new_rcVlanEntry();
    if (! xx) {
	return SCLI_ERROR;
    }

    xx->rcVlanId = vlanEntry->rcVlanId;
    xx->rcVlanRowStatus = &row_status;

    (void) rapidcity_vlan_mib_set_rcVlanEntry(interp->peer, xx);
    rapidcity_vlan_mib_free_rcVlanEntry(xx);
    
    if (interp->peer->error_status) {
	vlan_snmp_error(interp, vlanEntry);
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
delete_nortel_baystack_vlan(scli_interp_t *interp, int argc, char **argv)
{
    rapidcity_vlan_mib_rcVlanEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX;
    }

    regex_vlan = &_regex_vlan;
    if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	return SCLI_SYNTAX;
    }

    if (rapidcity_vlan_mib_get_rcVlanTable(interp->peer, &vlanTable)) {
	regfree(regex_vlan);
	return SCLI_ERROR;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		(void) delete_vlan(interp, vlanTable[i]);
	    }
	}
    }

    if (vlanTable) rapidcity_vlan_mib_free_rcVlanTable(vlanTable);
    regfree(regex_vlan);
    
    return SCLI_OK;
}



static int
create_nortel_baystack_vlan(scli_interp_t *interp, int argc, char **argv)
{
    rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry;
    gint32 vlanId, status, type;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    if (sscanf(argv[1], "%d", &vlanId) != 1) {
	return SCLI_SYNTAX;
    }

    vlanEntry = rapidcity_vlan_mib_new_rcVlanEntry();
    if (! vlanEntry) {
	return SCLI_ERROR;
    }

    vlanEntry->rcVlanId = vlanId;
    vlanEntry->rcVlanName = argv[2];
    type = RAPIDCITY_VLAN_MIB_RCVLANTYPE_BYPORT;
    vlanEntry->rcVlanType = &type;
    vlanEntry->_rcVlanNameLength = strlen(argv[2]);
    status = RAPIDCITY_VLAN_MIB_RCVLANROWSTATUS_CREATEANDGO;
    vlanEntry->rcVlanRowStatus = &status;

    (void) rapidcity_vlan_mib_set_rcVlanEntry(interp->peer, vlanEntry);
    rapidcity_vlan_mib_free_rcVlanEntry(vlanEntry);

    if (interp->peer->error_status) {
	vlan_snmp_error(interp, vlanEntry);
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
set_vlan_ports(scli_interp_t *interp,
	       rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry,
	       guchar *ports)
{
    rapidcity_vlan_mib_rcVlanEntry_t *xx;
    
    xx = rapidcity_vlan_mib_new_rcVlanEntry();
    if (! xx) {
	return SCLI_ERROR;
    }

    xx->rcVlanId = vlanEntry->rcVlanId;
    xx->rcVlanPortMembers = ports;

#if 0
    /* At least the baystack switches return notWritable. */
    xx->rcVlanPotentialMembers = ports;
    xx->rcVlanStaticMembers = ports;
#endif

    (void) rapidcity_vlan_mib_set_rcVlanEntry(interp->peer, xx);
    rapidcity_vlan_mib_free_rcVlanEntry(xx);

    if (interp->peer->error_status) {
	vlan_snmp_error(interp, vlanEntry);
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
set_nortel_baystack_vlan_ports(scli_interp_t *interp, int argc, char **argv)
{
    rapidcity_vlan_mib_rcVlanEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    guchar ports[32];
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    regex_vlan = &_regex_vlan;
    if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	return SCLI_SYNTAX;
    }

    if (scan_ports(ports, sizeof(ports), argv[2]) != SCLI_OK) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SYNTAX;
    }

    if (rapidcity_vlan_mib_get_rcVlanTable(interp->peer, &vlanTable)) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_ERROR;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		(void) set_vlan_ports(interp, vlanTable[i], ports);
	    }
	}
    }

    if (vlanTable) rapidcity_vlan_mib_free_rcVlanTable(vlanTable);

    if (regex_vlan) regfree(regex_vlan);
        
    return SCLI_OK;
}



void
scli_init_nortel_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "create nortel bridge vlan", "<vlanid> <name>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "The create nortel bridge vlan command is used to create a\n"
	  "new vlan with the given <vlanid> and <name>.",
	  create_nortel_baystack_vlan },

	{ "delete nortel bridge vlan", "<regexp>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "The delete nortel bridge vlan command deletes all selected\n"
	  "vlans. The regular expression <regexp> is matched against the\n"
	  "vlan names to select the vlans that should be deleted.",
	  delete_nortel_baystack_vlan },

	{ "set nortel bridge vlan ports", "<regexp> <ports>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "The set nortel bridge vlan ports command allows to assign\n"
	  "ports to port-based vlans. The regular expression <regexp>\n"
	  "is matched against the vlan names to select the vlans that\n"
	  "should be modified. The <ports> argument contains a comma\n"
	  "separated list of port numbers or port number ranges, e.g.\n"
	  "1,5,7-8.",
	  set_nortel_baystack_vlan_ports },

	{ "show nortel bridge vlan info", "[<regexp>]",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "The show nortel bridge vlan info command shows summary\n"
	  "information about all selected vlans. The optional regular\n"
	  "expression <regexp> is matched against the vlan names to\n"
	  "select the vlans of interest. The command generates a table\n"
	  "which displays the vlan number, the vlan name, the vlan type,\n"
	  "the assigned vlan color, the vlan priority, whether routing\n"
	  "is enabled and the status of the vlan.",
	  show_nortel_baystack_vlan_info },

	{ "show nortel bridge vlan details", "[<regexp>]",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "The  show nortel bridge vlan details command describes the\n"
	  "selected vlans in more detail. The optional regular expression\n"
	  "<regexp> is matched against the vlan names to select the vlans\n"
	  "of interest. <xxx>",
	  show_nortel_baystack_vlan_details },

	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t nortel_mode = {
	"nortel",
	"The nortel scli mode allows to manipulate virtual lans (vlans)\n"
	"on nortel bridges. It is based on the RAPIDCITY-VLAN-MIB which\n"
	"is implemented at least on the baystack bridges.",
	cmds
    };

    scli_register_mode(interp, &nortel_mode);
}
