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

#include "rapid-city.h"
#include "rapid-city-proc.h"



static GSnmpEnum const vlan_priority[] = {
    { RAPID_CITY_RCVLANHIGHPRIORITY_TRUE,	"high" },
    { RAPID_CITY_RCVLANHIGHPRIORITY_FALSE,	"normal" },
    { 0, NULL }
};



static void
fmt_vlanStatus(GString *s, rapid_city_rcVlanEntry_t *vlanEntry)
{
    static GSnmpEnum const rcVlanType[] = {
	{ RAPID_CITY_RCVLANTYPE_BYPORT,	"P" },
	{ RAPID_CITY_RCVLANTYPE_BYIPSUBNET,	"I" },
	{ RAPID_CITY_RCVLANTYPE_BYPROTOCOLID,	"O" },
	{ RAPID_CITY_RCVLANTYPE_BYSRCMAC,	"S" },
	{ RAPID_CITY_RCVLANTYPE_BYDSTMCAST,	"D" },
	{ 0, NULL }
    };
    
    static GSnmpEnum const rcVlanHighPriority[] = {
	{ RAPID_CITY_RCVLANHIGHPRIORITY_TRUE,	"H" },
	{ RAPID_CITY_RCVLANHIGHPRIORITY_FALSE,	"N" },
	{ 0, NULL }
    };

    static GSnmpEnum const rcVlanRoutingEnable[] = {
	{ RAPID_CITY_RCVLANROUTINGENABLE_TRUE,	"R" },
	{ RAPID_CITY_RCVLANROUTINGENABLE_FALSE,	"N" },
	{ 0, NULL }
    };

    static GSnmpEnum const rcVlanRowStatus[] = {
	{ RAPID_CITY_RCVLANROWSTATUS_ACTIVE,	"A" },
	{ RAPID_CITY_RCVLANROWSTATUS_NOTINSERVICE,	"S" },
	{ RAPID_CITY_RCVLANROWSTATUS_NOTREADY,	"R" },
	{ RAPID_CITY_RCVLANROWSTATUS_CREATEANDGO,	"G" },
	{ RAPID_CITY_RCVLANROWSTATUS_CREATEANDWAIT,	"W" },
	{ RAPID_CITY_RCVLANROWSTATUS_DESTROY,	"D" },
	{ 0, NULL }
    };

    const char *e;
    
    e = fmt_enum(rcVlanRowStatus, vlanEntry->rcVlanRowStatus);
    g_string_sprintfa(s, "%s", e ? e : "-");

    e = fmt_enum(rcVlanType, vlanEntry->rcVlanType);
    g_string_sprintfa(s, "%s", e ? e : "-");

    e = fmt_enum(rcVlanHighPriority, vlanEntry->rcVlanHighPriority);
    g_string_sprintfa(s, "%s", e ? e : "-");

    e = fmt_enum(rcVlanRoutingEnable, vlanEntry->rcVlanRoutingEnable);
    g_string_sprintfa(s, "%s", e ? e : "-");
}



static void
vlan_error(scli_interp_t *interp,
	   rapid_city_rcVlanEntry_t *vlanEntry)
{
    if (vlanEntry) {
	g_string_sprintfa(interp->result, "vlan %d: ", vlanEntry->rcVlanId);
	if (vlanEntry->rcVlanName && vlanEntry->_rcVlanNameLength) {
	    g_string_sprintfa(interp->result, "%.*s: ",
			      (int) vlanEntry->_rcVlanNameLength,
			      vlanEntry->rcVlanName);
	}
    }
}



static void
vlan_snmp_error(scli_interp_t *interp,
		rapid_city_rcVlanEntry_t *vlanEntry)
{
    vlan_error(interp, vlanEntry);
    scli_snmp_error(interp);
    g_string_append(interp->result, "\n");
}



static int
match_vlan(regex_t *regex_vlan,
	   rapid_city_rcVlanEntry_t *vlanEntry)
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
get_default_port_set(guchar *bits, gsize bits_len,
		     rapid_city_rcVlanPortEntry_t **vlanPortTable,
		     guint32 vlanid)
{
    int i; 
    
    for (i = 0; vlanPortTable[i]; i++) {
	if (vlanPortTable[i]->rcVlanPortDefaultVlanId
	    && *vlanPortTable[i]->rcVlanPortDefaultVlanId == vlanid) {
	    int p = vlanPortTable[i]->rcVlanPortIndex;
	    if (p/8 < bits_len) {
		bits[p/8] |= 1 << (7-(p%8));
	    }
	}
    }
}



static void
xml_port_set(xmlNodePtr root, guchar *bits, gsize bits_len)
{
    int bit, i;
    xmlNodePtr node;

    for (i = 0; i < bits_len * 8; i++) {
	bit = bits[i/8] & 1 << (7-(i%8));
	if (bit) {
	    node = xmlNewChild(root, NULL, "port", NULL);
	    xml_set_prop(node, "number", "%d", i);
	}
    }
}



static void
fmt_id_list(GString *s, guchar *ids, gint32 numids)
{
    int i, cnt;
    int first = -1;
    int last = -1;
    int port;

    for (i = 0, cnt = 0; i < numids; i++) {
	port = ids[i*2] * 256 + ids[i*2+1];
	if (first < 0) {
	    first = port;
	} else {
	    if (last+1 != port) {
		if (first == last) {
		    g_string_sprintfa(s, "%s%d", cnt ? "," : "", first);
		} else {
		    g_string_sprintfa(s, "%s%d-%d", cnt ? "," : "", first, last);
		}
		first = port;
		cnt++;
	    }
	}
	last = port;
    }

    if (first == last) {
	g_string_sprintfa(s, "%s%d", cnt ? "," : "", first);
    } else {
	g_string_sprintfa(s, "%s%d-%d", cnt ? "," : "", first, last);
    }
}



static int
get_vlan_name_width(rapid_city_rcVlanEntry_t **vlanTable)
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



static void
xml_nortel_bridge_vlan_details(xmlNodePtr root,
			       rapid_city_rcVlanEntry_t *vlanEntry,
			       rapid_city_rcVlanPortEntry_t **vlanPortTable)
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

    s = fmt_enum(rapid_city_enums_rcVlanType, vlanEntry->rcVlanType);
    if (s) {
	node = xmlNewChild(tree, NULL, "type", s);
    }

    s = fmt_enum(vlan_priority, vlanEntry->rcVlanHighPriority);
    if (s) {
	node = xmlNewChild(tree, NULL, "priority", s);
    }

    s = fmt_enum(rapid_city_enums_rcVlanRoutingEnable,
		 vlanEntry->rcVlanRoutingEnable);
    if (s) {
	node = xmlNewChild(tree, NULL, "routing", s);
    }

    s = fmt_enum(rapid_city_enums_rcVlanRowStatus,
		 vlanEntry->rcVlanRowStatus);
    if (s) {
	node = xmlNewChild(tree, NULL, "status", s);
    }

    if (vlanEntry->rcVlanType
	&& *vlanEntry->rcVlanType == RAPID_CITY_RCVLANTYPE_BYPORT) {
	if (vlanEntry->rcVlanPortMembers) {
	    node = xmlNewChild(tree, NULL, "member", NULL);
	    xml_port_set(node, vlanEntry->rcVlanPortMembers, 32);
	}
	if (vlanEntry->rcVlanActiveMembers) {
	    node = xmlNewChild(tree, NULL, "active", NULL);
	    xml_port_set(node, vlanEntry->rcVlanActiveMembers, 32);
	}
	if (vlanEntry->rcVlanStaticMembers) {
	    node = xmlNewChild(tree, NULL, "static", NULL);
	    xml_port_set(node, vlanEntry->rcVlanStaticMembers, 32);
	}
	if (vlanEntry->rcVlanNotAllowToJoin) {
	    node = xmlNewChild(tree, NULL, "disallowed", NULL);
	    xml_port_set(node, vlanEntry->rcVlanNotAllowToJoin, 32);
	}
    }

    if (vlanPortTable) {
	guchar bits[32];
	memset(bits, 0, sizeof(bits));
	get_default_port_set(bits, sizeof(bits),
			     vlanPortTable, (guint32) vlanEntry->rcVlanId);
	node = xmlNewChild(tree, NULL, "default", NULL);
	xml_port_set(node, bits, sizeof(bits));
    }
}



static void
fmt_nortel_bridge_vlan_details(GString *s,
			       rapid_city_rcVlanEntry_t *vlanEntry,
			       rapid_city_rcVlanPortEntry_t **vlanPortTable)
{
    const int width = 20;
    const char *e;

    g_string_sprintfa(s, "VLan:        %-*d", width, vlanEntry->rcVlanId);
    if (vlanEntry->rcVlanName && vlanEntry->_rcVlanNameLength) {
	g_string_sprintfa(s, " Name:     %.*s\n",
			  (int) vlanEntry->_rcVlanNameLength,
			  vlanEntry->rcVlanName);
    } else {
	g_string_append(s, " Name:\n");
    }

    e = fmt_enum(vlan_priority, vlanEntry->rcVlanHighPriority);
    g_string_sprintfa(s, "Priority:    %-*s", width, e ? e : "");

    e = fmt_enum(rapid_city_enums_rcVlanRowStatus,
		 vlanEntry->rcVlanRowStatus);
    g_string_sprintfa(s, " Status:   %-*s\n", width, e ? e : "");

    e = fmt_enum(rapid_city_enums_rcVlanRoutingEnable,
		 vlanEntry->rcVlanRoutingEnable);
    g_string_sprintfa(s, "Routing:     %-*s", width, e ? e : "");

    e = fmt_enum(rapid_city_enums_rcVlanType,
		 vlanEntry->rcVlanType);
    g_string_sprintfa(s, " Type:     %-*s", width, e ? e : "");

    if (vlanEntry->rcVlanType
	&& *vlanEntry->rcVlanType == RAPID_CITY_RCVLANTYPE_BYPORT) {
	if (vlanEntry->rcVlanPortMembers) {
	    g_string_append(s, "\nMember:      ");
	    fmt_port_set(s, vlanEntry->rcVlanPortMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
	if (vlanEntry->rcVlanActiveMembers) {
	    g_string_append(s, "Allowed:     ");
	    fmt_port_set(s, vlanEntry->rcVlanActiveMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
	if (vlanEntry->rcVlanStaticMembers) {
	    g_string_append(s, "Static:      ");
	    fmt_port_set(s, vlanEntry->rcVlanStaticMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
	if (vlanEntry->rcVlanNotAllowToJoin) {
	    g_string_append(s, "Disallowed:  ");
	    fmt_port_set(s, vlanEntry->rcVlanNotAllowToJoin, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
    }

    if (vlanPortTable) {
	guchar bits[32];
	memset(bits, 0, sizeof(bits));
	get_default_port_set(bits, sizeof(bits),
			     vlanPortTable, (guint32) vlanEntry->rcVlanId);
	g_string_append(s, "Default:     ");
	fmt_port_set(s, bits, sizeof(bits));
	g_string_append(s, "\n");
    }

    if (vlanEntry->rcVlanType
	&& (*vlanEntry->rcVlanType
	    == RAPID_CITY_RCVLANTYPE_BYPROTOCOLID)) {
	if (vlanEntry->rcVlanProtocolId) {
	    e = fmt_enum(rapid_city_enums_rcVlanProtocolId,
			 vlanEntry->rcVlanProtocolId);
	    g_string_sprintfa(s, " Protocol: %s\n", e ? e : "");
	} else {
	    g_string_append(s, "\n");
	}
    }
}



static int
show_nortel_bridge_vlan_details(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t **vlanTable = NULL;
    rapid_city_rcVlanPortEntry_t **vlanPortTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i, c;
    const int mask = (RAPID_CITY_RCVLANNAME
		      | RAPID_CITY_RCVLANTYPE
		      | RAPID_CITY_RCVLANHIGHPRIORITY
		      | RAPID_CITY_RCVLANROUTINGENABLE
		      | RAPID_CITY_RCVLANROWSTATUS
		      | RAPID_CITY_RCVLANPORTMEMBERS
		      | RAPID_CITY_RCVLANACTIVEMEMBERS
		      | RAPID_CITY_RCVLANSTATICMEMBERS
		      | RAPID_CITY_RCVLANNOTALLOWTOJOIN
		      | RAPID_CITY_RCVLANPROTOCOLID);

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_vlan = &_regex_vlan;
	if (regcomp(regex_vlan, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_OK;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, mask);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if (vlanTable) {
	rapid_city_get_rcVlanPortTable(interp->peer, &vlanPortTable,
				       RAPID_CITY_RCVLANPORTDEFAULTVLANID);
	for (i = 0, c = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		if (scli_interp_xml(interp)) {
		    xml_nortel_bridge_vlan_details(interp->xml_node,
						   vlanTable[i],
						   vlanPortTable);
		} else {
		    if (c) {
			g_string_append(interp->result, "\n");
		    }
		    fmt_nortel_bridge_vlan_details(interp->result,
						   vlanTable[i],
						   vlanPortTable);
		    c++;
		}
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);
    if (regex_vlan) regfree(regex_vlan);
    
    return SCLI_OK;
}



static void
fmt_nortel_bridge_vlan_info(GString *s,
			    rapid_city_rcVlanEntry_t *vlanEntry,
			    int name_width)
{
    g_string_sprintfa(s, "%4d  ", vlanEntry->rcVlanId);

    fmt_vlanStatus(s, vlanEntry);

    if (vlanEntry->rcVlanName && vlanEntry->_rcVlanNameLength) {
	g_string_sprintfa(s, "  %-*.*s ", name_width,
			  (int) vlanEntry->_rcVlanNameLength,
			  vlanEntry->rcVlanName);
    } else {
	g_string_sprintfa(s, "  %*s ", name_width, "");
    }

    if (vlanEntry->rcVlanPortMembers) {
	fmt_port_set(s, vlanEntry->rcVlanPortMembers, 32);
    }

    g_string_append(s, "\n");
}



static int
show_nortel_bridge_vlan_info(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i, name_width;
    const int mask = (RAPID_CITY_RCVLANNAME
		      | RAPID_CITY_RCVLANTYPE
		      | RAPID_CITY_RCVLANHIGHPRIORITY
		      | RAPID_CITY_RCVLANROUTINGENABLE
		      | RAPID_CITY_RCVLANROWSTATUS
		      | RAPID_CITY_RCVLANPORTMEMBERS);

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_vlan = &_regex_vlan;
	if (regcomp(regex_vlan, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_OK;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, mask);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    name_width = get_vlan_name_width(vlanTable);

    if (vlanTable) {
	g_string_sprintfa(interp->header,
			  "VLAN STATUS %-*s PORTS", name_width, "NAME");
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		fmt_nortel_bridge_vlan_info(interp->result, vlanTable[i],
					    name_width);
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);
    if (regex_vlan) regfree(regex_vlan);
    
    return SCLI_OK;
}



static void
fmt_nortel_bridge_vlan_port(GString *s,
			    rapid_city_rcVlanPortEntry_t *vlanPortEntry)
{
    static GSnmpEnum const rapid_city_enums_rcVlanPortType[] = {
	{ RAPID_CITY_RCVLANPORTTYPE_ACCESS,	"A" },
	{ RAPID_CITY_RCVLANPORTTYPE_TRUNK,	"T" },
	{ 0, NULL }
    };

    static GSnmpEnum const rcVlanPortPerformTagging[] = {
	{ RAPID_CITY_RCVLANPORTPERFORMTAGGING_TRUE,	"T" },
	{ RAPID_CITY_RCVLANPORTPERFORMTAGGING_FALSE,	"N" },
	{ 0, NULL }
    };
    
    static GSnmpEnum const rcVlanPortDiscardTaggedFrames[] = {
	{ RAPID_CITY_RCVLANPORTDISCARDTAGGEDFRAMES_TRUE,	"D" },
	{ RAPID_CITY_RCVLANPORTDISCARDTAGGEDFRAMES_FALSE,	"N" },
	{ 0, NULL }
    };

    static GSnmpEnum const rcVlanPortDiscardUntaggedFrames[] = {
	{ RAPID_CITY_RCVLANPORTDISCARDUNTAGGEDFRAMES_TRUE,	"D" },
	{ RAPID_CITY_RCVLANPORTDISCARDUNTAGGEDFRAMES_FALSE,	"N" },
	{ 0, NULL }
    };

    const char *e;
    
    g_string_sprintfa(s, "%5u ", vlanPortEntry->rcVlanPortIndex);

    e = fmt_enum(rapid_city_enums_rcVlanPortType,
		 vlanPortEntry->rcVlanPortType);
    g_string_sprintfa(s, "%s", e ? e : "-");

    e = fmt_enum(rcVlanPortPerformTagging,
		 vlanPortEntry->rcVlanPortPerformTagging);
    g_string_sprintfa(s, "%s", e ? e : "-");

    e = fmt_enum(rcVlanPortDiscardTaggedFrames,
		 vlanPortEntry->rcVlanPortDiscardTaggedFrames);
    g_string_sprintfa(s, "%s", e ? e : "-");

    e = fmt_enum(rcVlanPortDiscardUntaggedFrames,
		 vlanPortEntry->rcVlanPortDiscardUntaggedFrames);
    g_string_sprintfa(s, "%s", e ? e : "-");

    if (vlanPortEntry->rcVlanPortDefaultVlanId) {
	g_string_sprintfa(s, "  %5u   ",
			  *vlanPortEntry->rcVlanPortDefaultVlanId);
    }

    if (vlanPortEntry->rcVlanPortNumVlanIds
	&& vlanPortEntry->rcVlanPortVlanIds) {
	fmt_id_list(s, vlanPortEntry->rcVlanPortVlanIds,
		    *vlanPortEntry->rcVlanPortNumVlanIds);
    }

    g_string_sprintfa(s, "\n");
}


    
static int
show_nortel_bridge_vlan_ports(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanPortEntry_t **vlanPortTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rapid_city_get_rcVlanPortTable(interp->peer, &vlanPortTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vlanPortTable) {
	g_string_sprintfa(interp->header, " PORT FLAGS DEFAULT VLANS");
	for (i = 0; vlanPortTable[i]; i++) {
	    fmt_nortel_bridge_vlan_port(interp->result, vlanPortTable[i]);
	}
    }

    if (vlanPortTable) rapid_city_free_rcVlanPortTable(vlanPortTable);
    
    return SCLI_OK;
}



static int
create_nortel_bridge_vlan(scli_interp_t *interp, int argc, char **argv)
{
    gint32 vlanId;
    char *end, *name;
    size_t name_len;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    vlanId = strtol(argv[1], &end, 0);
    if (*end || vlanId < 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_NUMBER;
    }

    name = argv[2];
    name_len = strlen(name);
    if (name_len < RAPID_CITY_RCVLANNAMEMINLENGTH
	|| name_len > RAPID_CITY_RCVLANNAMEMAXLENGTH) {
	g_string_assign(interp->result, name);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rapid_city_proc_create_vlan(interp->peer, vlanId, name, name_len,
				RAPID_CITY_RCVLANTYPE_BYPORT);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
delete_nortel_bridge_vlan(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    regex_vlan = &_regex_vlan;
    if (regcomp(regex_vlan, argv[1], interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }

    if (scli_interp_dry(interp)) {
	regfree(regex_vlan);
	return SCLI_OK;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable,
			       RAPID_CITY_RCVLANNAME);
    if (interp->peer->error_status) {
	regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		rapid_city_proc_delete_vlan(interp->peer,
					    vlanTable[i]->rcVlanId);
		if (interp->peer->error_status) {
		    vlan_snmp_error(interp, vlanTable[i]);
		}
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);
    regfree(regex_vlan);
    
    return SCLI_OK;
}



static int
set_nortel_bridge_vlan_name(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t *vlanEntry = NULL;
    gint32 vlanId;
    char *end, *name;
    size_t name_len;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    vlanId = strtol(argv[1], &end, 0);
    if (*end || vlanId < 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_NUMBER;
    }

    name = argv[2];
    name_len = strlen(name);
    if (name_len < RAPID_CITY_RCVLANNAMEMINLENGTH
	|| name_len > RAPID_CITY_RCVLANNAMEMAXLENGTH) {
	g_string_assign(interp->result, name);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rapid_city_get_rcVlanEntry(interp->peer, &vlanEntry, vlanId,
			       RAPID_CITY_RCVLANNAME);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vlanEntry) {
	vlanEntry->rcVlanName = name;
	vlanEntry->_rcVlanNameLength = name_len;
	rapid_city_set_rcVlanEntry(interp->peer, vlanEntry,
				   RAPID_CITY_RCVLANNAME);
	if (interp->peer->error_status) {
	    rapid_city_free_rcVlanEntry(vlanEntry);
	    return SCLI_SNMP;
	}
    }

    if (vlanEntry) rapid_city_free_rcVlanEntry(vlanEntry);

    return SCLI_OK;
}



static int
set_nortel_bridge_vlan_ports(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    guchar ports[32];
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    regex_vlan = &_regex_vlan;
    if (regcomp(regex_vlan, argv[1], interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }

    if (scan_port_set(ports, sizeof(ports), argv[2]) != SCLI_OK) {
	if (regex_vlan) regfree(regex_vlan);
	g_string_assign(interp->result, argv[2]);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_OK;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, RAPID_CITY_RCVLANNAME);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		rapid_city_proc_set_vlan_port_member(interp->peer,
						     vlanTable[i]->rcVlanId,
						     ports);
		if (interp->peer->error_status) {
		    vlan_snmp_error(interp, vlanTable[i]);
		}
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);

    if (regex_vlan) regfree(regex_vlan);
        
    return SCLI_OK;
}



static int
set_nortel_bridge_vlan_default(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t **vlanTable = NULL;
    guchar ports[32];
    int i, port, bit;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scan_port_set(ports, sizeof(ports), argv[2]) != SCLI_OK) {
	g_string_assign(interp->result, argv[2]);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, RAPID_CITY_RCVLANNAME);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vlanTable) {
	size_t len = strlen(argv[1]);
	for (i = 0; vlanTable[i]; i++) {
	    if (vlanTable[i]->rcVlanName
		&& vlanTable[i]->_rcVlanNameLength == len
		&& memcmp(vlanTable[i]->rcVlanName, argv[1], len) == 0) {
		break;
	    }
	}
	if (! vlanTable[i]) {
	    g_string_sprintfa(interp->result, "no vlan with this name");
	    rapid_city_free_rcVlanTable(vlanTable);
	    return SCLI_ERROR;
	}
	for (port = 0; port < 32 * 8; port++) {
	    bit = ports[port/8] & 1 << (7-(port%8));
	    if (bit) {
		rapid_city_proc_set_vlan_port_default(interp->peer, port,
						      vlanTable[i]->rcVlanId);
		if (interp->peer->error_status) {
		    vlan_snmp_error(interp, vlanTable[i]);
		}
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);

    return SCLI_OK;
}



static int
dump_nortel_bridge_vlan(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t **vlanTable = NULL;
    int i;
    const int mask = (RAPID_CITY_RCVLANNAME
		      | RAPID_CITY_RCVLANTYPE
		      | RAPID_CITY_RCVLANPORTMEMBERS);
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, mask);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (! vlanTable[i]->rcVlanName) {
		continue;
	    }
	    g_string_sprintfa(interp->result,
			      "create nortel bridge vlan \"%u\" \"%.*s\"\n",
			      vlanTable[i]->rcVlanId,
			      (int) vlanTable[i]->_rcVlanNameLength,
			      vlanTable[i]->rcVlanName);
	}
	g_string_append(interp->result, "\n");
	for (i = 0; vlanTable[i]; i++) {
	    if (! vlanTable[i]->rcVlanName) {
		continue;
	    }
	    if (vlanTable[i]->rcVlanPortMembers) {
		g_string_sprintfa(interp->result,
				  "set nortel bridge vlan ports \"%.*s\" \"",
				  (int) vlanTable[i]->_rcVlanNameLength,
				  vlanTable[i]->rcVlanName);
		fmt_port_set(interp->result, vlanTable[i]->rcVlanPortMembers, 32);
		g_string_sprintfa(interp->result, "\"\n");
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);

    return SCLI_OK;
}



void
scli_init_nortel_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "create nortel bridge vlan", "<vlanid> <name>",
	  "The `create nortel bridge vlan' command is used to create a\n"
	  "new virtual LAN with the given <vlanid> and <name>.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  create_nortel_bridge_vlan },

	{ "delete nortel bridge vlan", "<regexp>",
	  "The `delete nortel bridge vlan' command deletes all selected\n"
	  "virtual LANs. The regular expression <regexp> is matched\n"
	  "against the virtual LAN names to select the vlans that should\n"
	  "be deleted.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  delete_nortel_bridge_vlan },

	{ "set nortel bridge vlan name", "<vlanid> <name>",
	  "The `set nortel bridge vlan name' command changes the name of\n"
	  "a virtual LAN.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_nortel_bridge_vlan_name },

	{ "set nortel bridge vlan ports", "<regexp> <ports>",
	  "The `set nortel bridge vlan ports' command allows to assign\n"
	  "ports to port-based vlans. The regular expression <regexp>\n"
	  "is matched against the vlan names to select the vlans that\n"
	  "should be modified. The <ports> argument contains a comma\n"
	  "separated list of port numbers or port number ranges, e.g.\n"
	  "1,5,7-8.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_nortel_bridge_vlan_ports },

	{ "set nortel bridge vlan default", "<string> <ports>",
	  "The `set nortel bridge vlan default' command allows to assign\n"
	  "ports to a default vlan. The <string> argument is matched\n"
	  "against the vlan names to select the vlan. The <ports> argument\n"
	  "contains a comma separated list of port numbers or port number\n"
	  "ranges, e.g. 1,5,7-8.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_nortel_bridge_vlan_default },

	{ "show nortel bridge vlan info", "[<regexp>]",
	  "The `show nortel bridge vlan info' command shows summary\n"
	  "information about all selected virtual LANs. The optional\n"
	  "regular expression <regexp> is matched against the virtual\n"
	  "LAN names to select the virtual LANs of interest. The\n"
	  "command generates a table with the following columns:\n"
	  "\n"
	  "  VLAN   number of the virtual LAN\n"
	  "  STATUS status of the virtual LAN (see below)\n"
	  "  NAME   name of the virtual LAN\n"
	  "  PORTS  ports assigned to the virtual LAN\n"
	  "\n"
	  "The status is encoded in four characters. The first character\n"
	  "indicates the status of the row (A=active, S=not in service,\n"
	  "R=not ready). The second character indicates virtual LAN type\n"
	  "(P=port, I=IP-subnet, O=protocol, S=src address, D=dst address).\n"
	  "The third character indicates the priority of the virtual LAN\n"
	  "(H=high, N=normal) and the fourth character indicates whether\n"
	  "routing is enabled (R=routing, N=no routing).",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_nortel_bridge_vlan_info },

	{ "show nortel bridge vlan details", "[<regexp>]",
	  "The `show nortel bridge vlan details' command describes the\n"
	  "selected vlans in more detail. The optional regular expression\n"
	  "<regexp> is matched against the vlan names to select the vlans\n"
	  "of interest.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "nortel bridge vlans", NULL,
	  show_nortel_bridge_vlan_details },

	{ "show nortel bridge vlan ports", NULL,
	  "The `show nortel bridge vlan ports' command shows information\n"
	  "for each vlan port. The command generates a table with the\n"
	  "following columns:\n"
	  "\n"
	  "  PORT    port number\n"
	  "  FLAGS   port vlan flags (see below)\n"
	  "  DEFAULT default vlan number\n"
	  "  VLANS   vlan numbers the port is member of\n"
	  "\n"
	  "The flags are encoded in four characters. The first character\n"
	  "indicates the port type (A=access, T=trunk). The second character\n"
	  "indicates whether the port tags frames (T=tagging, N=none). The\n"
	  "third character indicates whether the port discards tagged frames\n"
	  "(D=discard, N=none) and the fourth character indicates whether\n"
	  "the port discards untagged frames (D=discard, N=none).",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_nortel_bridge_vlan_ports },

	{ "dump nortel bridge vlan", NULL,
	  "The `dump nortel bridge vlan' command generates a sequence of scli\n"
	  "commands which can be used to restore the virtual LAN configuration.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  dump_nortel_bridge_vlan },
	
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t nortel_mode = {
	"nortel",
	"The nortel scli mode allows to manipulate virtual LANs (vlans)\n"
	"on nortel bridges. It is based on the RAPID-CITY MIB which\n"
	"is implemented at least on the baystack bridges.",
	cmds
    };

    scli_register_mode(interp, &nortel_mode);
}
