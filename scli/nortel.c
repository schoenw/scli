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



static int
match_vlan(regex_t *regex_vlan,
	   rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry)
{
    int status;
    
    if (! regex_vlan) {
	return 1;
    }

    /*
     * Does it really make sense to filter only on the description?
     * This way, we do not need to read the ifXTable at all...
     */

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
		if (first == i-1) {
		    g_string_sprintfa(s, "%s%d", n ? ", " : "", first);
		} else {
		    g_string_sprintfa(s, "%s%d-%d", n ? ", " : "", first, i-1);
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
	    g_string_append(s, "\nPorts:       ");
	    fmt_ports(s, vlanEntry->rcVlanPortMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
    }

    if (vlanEntry->rcVlanType
	&& *vlanEntry->rcVlanType == RAPIDCITY_VLAN_MIB_RCVLANTYPE_BYPROTOCOLID) {
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
		if (c) {
		    g_string_append(interp->result, "\n");
		}
		fmt_nortel_baystack_vlan_details(interp->result, vlanTable[i]);
		c++;
	    }
	}
    }

    if (vlanTable) rapidcity_vlan_mib_free_rcVlanTable(vlanTable);

    if (regex_vlan) regfree(regex_vlan);

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
    if (interp->peer->error_status) {
	g_string_sprintfa(interp->result, "%d: ",
			  vlanEntry->rcVlanId);
	scli_snmp_error(interp);
	g_string_append(interp->result, "\n");
    }

    rapidcity_vlan_mib_free_rcVlanEntry(xx);

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
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_ERROR;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		delete_vlan(interp, vlanTable[i]);
	    }
	}
    }

    if (vlanTable) rapidcity_vlan_mib_free_rcVlanTable(vlanTable);

    if (regex_vlan) regfree(regex_vlan);
    
    return SCLI_OK;
}



static int
create_nortel_baystack_vlan(scli_interp_t *interp, int argc, char **argv)
{
    rapidcity_vlan_mib_rcVlanEntry_t *vlanEntry;
    int i, vlanId;
    gint32 status, type;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    vlanId = atoi(argv[1]);

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
    rapidcity_vlan_mib_set_rcVlanEntry(interp->peer, vlanEntry);
    if (interp->peer->error_status) {
	g_string_sprintfa(interp->result, "%d: ",
			  vlanEntry->rcVlanId);
	scli_snmp_error(interp);
	g_string_append(interp->result, "\n");
    }

    (void) rapidcity_vlan_mib_free_rcVlanEntry(vlanEntry);

    return SCLI_OK;
}



void
scli_init_nortel_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show nortel bridge vlan info", "[<regexp>]",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "nortel (baystack) vlan summary",
	  show_nortel_baystack_vlan_info },
	{ "show nortel bridge vlan details", "[<regexp>]",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "nortel (baystack) vlan details",
	  show_nortel_baystack_vlan_details },
	{ "delete nortel bridge vlan", "<regexp>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "delete vlans on nortel (baystack) bridges",
	  delete_nortel_baystack_vlan },
	{ "create nortel bridge vlan", "<vlanid> <name>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "create a vlan on nortel (baystack) bridges",
	  create_nortel_baystack_vlan },
	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t nortel_mode = {
	"nortel",
	"scli mode to display and configure nortel parameters",
	cmds
    };

    scli_register_mode(interp, &nortel_mode);
}
