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

#include <regex.h>


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
    g_string_sprintfa(interp->result, "vlan %d: ", vlanEntry->rcVlanId);
    if (vlanEntry->rcVlanName && vlanEntry->_rcVlanNameLength) {
	g_string_sprintfa(interp->result, "%.*s: ",
			  (int) vlanEntry->_rcVlanNameLength,
			  vlanEntry->rcVlanName);
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
xml_ports(xmlNodePtr root, guchar *bits, gsize bits_len)
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
			       rapid_city_rcVlanEntry_t *vlanEntry)
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
	    xml_ports(node, vlanEntry->rcVlanPortMembers, 32);
	}
	if (vlanEntry->rcVlanActiveMembers) {
	    node = xmlNewChild(tree, NULL, "active", NULL);
	    xml_ports(node, vlanEntry->rcVlanActiveMembers, 32);
	}
	if (vlanEntry->rcVlanStaticMembers) {
	    node = xmlNewChild(tree, NULL, "static", NULL);
	    xml_ports(node, vlanEntry->rcVlanStaticMembers, 32);
	}
	if (vlanEntry->rcVlanNotAllowToJoin) {
	    node = xmlNewChild(tree, NULL, "disallowed", NULL);
	    xml_ports(node, vlanEntry->rcVlanNotAllowToJoin, 32);
	}
    }
}



static void
fmt_nortel_bridge_vlan_details(GString *s,
			       rapid_city_rcVlanEntry_t *vlanEntry)
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
	    fmt_ports(s, vlanEntry->rcVlanPortMembers, 32);
	    g_string_append(s, "\n");
	} else {
	    g_string_append(s, "\n");
	}
	if (vlanEntry->rcVlanActiveMembers) {
	    g_string_append(s, "Allowed:     ");
	    fmt_ports(s, vlanEntry->rcVlanActiveMembers, 32);
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
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_vlan = &_regex_vlan;
	if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, mask);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if (vlanTable) {	
	for (i = 0, c = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		if (scli_interp_xml(interp)) {
		    xml_nortel_bridge_vlan_details(interp->xml_node,
						   vlanTable[i]);
		} else {
		    if (c) {
			g_string_append(interp->result, "\n");
		    }
		    fmt_nortel_bridge_vlan_details(interp->result,
						   vlanTable[i]);
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
	fmt_ports(s, vlanEntry->rcVlanPortMembers, 32);
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
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_vlan = &_regex_vlan;
	if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX_REGEXP;
	}
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
    int i;
    
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
	for (i = 0; i < *vlanPortEntry->rcVlanPortNumVlanIds; i += 2) {
	    gint32 port;
	    port = vlanPortEntry->rcVlanPortVlanIds[i*2] * 256
		+ vlanPortEntry->rcVlanPortVlanIds[i*2+1];
	    g_string_sprintfa(s, "%s%d", i ? "," : "", port);
	}
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
	return SCLI_SYNTAX;
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
delete_vlan(scli_interp_t *interp,
	    rapid_city_rcVlanEntry_t *vlanEntry)
{
    rapid_city_rcVlanEntry_t *xx;
    gint32 row_status = RAPID_CITY_RCVLANROWSTATUS_DESTROY;

    xx = rapid_city_new_rcVlanEntry();
    if (! xx) {
	return SCLI_ERROR;
    }

    xx->rcVlanId = vlanEntry->rcVlanId;
    xx->rcVlanRowStatus = &row_status;

    rapid_city_set_rcVlanEntry(interp->peer, xx, RAPID_CITY_RCVLANROWSTATUS);
    rapid_city_free_rcVlanEntry(xx);
    
    if (interp->peer->error_status) {
	vlan_snmp_error(interp, vlanEntry);
	return SCLI_ERROR;
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
	return SCLI_SYNTAX;
    }

    regex_vlan = &_regex_vlan;
    if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	return SCLI_SYNTAX_REGEXP;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, RAPID_CITY_RCVLANNAME);
    if (interp->peer->error_status) {
	regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		(void) delete_vlan(interp, vlanTable[i]);
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);
    regfree(regex_vlan);
    
    return SCLI_OK;
}



static int
create_nortel_bridge_vlan(scli_interp_t *interp, int argc, char **argv)
{
    rapid_city_rcVlanEntry_t *vlanEntry;
    gint32 vlanId, status, type;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    if (sscanf(argv[1], "%d", &vlanId) != 1) {
	return SCLI_SYNTAX;
    }

    vlanEntry = rapid_city_new_rcVlanEntry();
    if (! vlanEntry) {
	return SCLI_ERROR;
    }

    vlanEntry->rcVlanId = vlanId;
    vlanEntry->rcVlanName = argv[2];
    type = RAPID_CITY_RCVLANTYPE_BYPORT;
    vlanEntry->rcVlanType = &type;
    vlanEntry->_rcVlanNameLength = strlen(argv[2]);
    status = RAPID_CITY_RCVLANROWSTATUS_CREATEANDGO;
    vlanEntry->rcVlanRowStatus = &status;

    rapid_city_set_rcVlanEntry(interp->peer, vlanEntry,
			       RAPID_CITY_RCVLANNAME
			       | RAPID_CITY_RCVLANTYPE
			       | RAPID_CITY_RCVLANROWSTATUS);
    rapid_city_free_rcVlanEntry(vlanEntry);

    if (interp->peer->error_status) {
	vlan_snmp_error(interp, vlanEntry);
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
set_vlan_ports(scli_interp_t *interp,
	       rapid_city_rcVlanEntry_t *vlanEntry,
	       guchar *ports)
{
    rapid_city_rcVlanEntry_t *xx;
    
    xx = rapid_city_new_rcVlanEntry();
    if (! xx) {
	return SCLI_ERROR;
    }

    xx->rcVlanId = vlanEntry->rcVlanId;
    xx->rcVlanPortMembers = ports;

    rapid_city_set_rcVlanEntry(interp->peer, xx, RAPID_CITY_RCVLANPORTMEMBERS);
    rapid_city_free_rcVlanEntry(xx);

    if (interp->peer->error_status) {
	vlan_snmp_error(interp, vlanEntry);
	return SCLI_ERROR;
    }

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
	return SCLI_SYNTAX;
    }

    regex_vlan = &_regex_vlan;
    if (regcomp(regex_vlan, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	return SCLI_SYNTAX_REGEXP;
    }

    if (scan_ports(ports, sizeof(ports), argv[2]) != SCLI_OK) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SYNTAX;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, RAPID_CITY_RCVLANNAME);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
		(void) set_vlan_ports(interp, vlanTable[i], ports);
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);

    if (regex_vlan) regfree(regex_vlan);
        
    return SCLI_OK;
}



void
scli_init_nortel_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "create nortel bridge vlan", "<vlanid> <name>",
	  "The create nortel bridge vlan command is used to create a\n"
	  "new vlan with the given <vlanid> and <name>.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  create_nortel_bridge_vlan },

	{ "delete nortel bridge vlan", "<regexp>",
	  "The delete nortel bridge vlan command deletes all selected\n"
	  "vlans. The regular expression <regexp> is matched against the\n"
	  "vlan names to select the vlans that should be deleted.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  delete_nortel_bridge_vlan },

	{ "set nortel bridge vlan ports", "<regexp> <ports>",
	  "The set nortel bridge vlan ports command allows to assign\n"
	  "ports to port-based vlans. The regular expression <regexp>\n"
	  "is matched against the vlan names to select the vlans that\n"
	  "should be modified. The <ports> argument contains a comma\n"
	  "separated list of port numbers or port number ranges, e.g.\n"
	  "1,5,7-8.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_nortel_bridge_vlan_ports },

	{ "show nortel bridge vlan info", "[<regexp>]",
	  "The show nortel bridge vlan info command shows summary\n"
	  "information about all selected vlans. The optional regular\n"
	  "expression <regexp> is matched against the vlan names to\n"
	  "select the vlans of interest. The command generates a table\n"
	  "with the following columns:\n"
	  "\n"
	  "  VLAN   vlan number\n"
	  "  STATUS status of the vlan (see below)\n"
	  "  NAME   vlan name\n"
	  "  PORTS  ports assigned to the vlan\n"
	  "\n"
	  "The status is encoded in four characters. The first character\n"
	  "indicates the status of the row (A=active, S=not in service,\n"
	  "R=not ready). The second character indicates  vlan type (P=B\n"
	  "port, I=IP-subnet, O=protocol, S=src address, D=dst address).\n"
	  "The third character indicates the priority of the vlan (H=high,\n"
	  "N=normal) and the fourth character indicates whether routing\n"
	  "is enabled (R=routing, N=no routing).",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_nortel_bridge_vlan_info },

	{ "show nortel bridge vlan details", "[<regexp>]",
	  "The show nortel bridge vlan details command describes the\n"
	  "selected vlans in more detail. The optional regular expression\n"
	  "<regexp> is matched against the vlan names to select the vlans\n"
	  "of interest.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "nortel bridge vlans", NULL,
	  show_nortel_bridge_vlan_details },

	{ "show nortel bridge vlan ports", NULL,
	  "The show nortel bridge vlan ports command shows information\n"
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
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_nortel_bridge_vlan_ports },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t nortel_mode = {
	"nortel",
	"The nortel scli mode allows to manipulate virtual lans (vlans)\n"
	"on nortel bridges. It is based on the RAPID-CITY MIB which\n"
	"is implemented at least on the baystack bridges.",
	cmds
    };

    scli_register_mode(interp, &nortel_mode);
}
