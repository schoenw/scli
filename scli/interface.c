/* 
 * interface.c -- scli interface mode implementation
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

#include "snmpv2-mib.h"
#include "if-mib.h"
#include "ip-mib.h"
#include "entity-mib.h"

#include <regex.h>



static void
interface_error(scli_interp_t *interp,
		if_mib_ifEntry_t *ifEntry)
{
    g_string_sprintfa(interp->result, "interface %d: ", ifEntry->ifIndex);
    if (ifEntry->ifDescr && ifEntry->_ifDescrLength) {
	g_string_sprintfa(interp->result, "%.*s: ",
			  (int) ifEntry->_ifDescrLength, ifEntry->ifDescr);
    }
}



static void
interface_snmp_error(scli_interp_t *interp,
		     if_mib_ifEntry_t *ifEntry)
{
    interface_error(interp, ifEntry);
    scli_snmp_error(interp);
    g_string_append(interp->result, "\n");
}



static void
fmt_ifStatus(GString *s, gint32 *admin, gint32 *oper,
	     gint32 *conn, gint32 *prom)
{
    static GSnmpEnum const admin_states[] = {
	{ IF_MIB_IFADMINSTATUS_UP,	"U" },
	{ IF_MIB_IFADMINSTATUS_DOWN,	"D" },
	{ IF_MIB_IFADMINSTATUS_TESTING,	"T" },
	{ 0, NULL }
    };

    static GSnmpEnum const oper_states[] = {
	{ IF_MIB_IFOPERSTATUS_UP,		"U" },
	{ IF_MIB_IFOPERSTATUS_DOWN,		"D" },
	{ IF_MIB_IFOPERSTATUS_TESTING,		"T" },
	{ IF_MIB_IFOPERSTATUS_UNKNOWN,		"?" },
	{ IF_MIB_IFOPERSTATUS_DORMANT,		"O" },
	{ IF_MIB_IFOPERSTATUS_NOTPRESENT,	"N" },
	{ IF_MIB_IFOPERSTATUS_LOWERLAYERDOWN,	"L" },
	{ 0, NULL }
    };

    static GSnmpEnum const conn_states[] = {
	{ IF_MIB_IFCONNECTORPRESENT_TRUE,	"C" },
	{ IF_MIB_IFCONNECTORPRESENT_FALSE,	"N" },
	{ 0, NULL }
    };

    static GSnmpEnum const prom_states[] = {
	{ IF_MIB_IFPROMISCUOUSMODE_TRUE,	"P" },
	{ IF_MIB_IFPROMISCUOUSMODE_FALSE,	"N" },
	{ 0, NULL }
    };

    xxx_enum(s, 1, admin_states, admin);
    xxx_enum(s, 1, oper_states, oper);
    xxx_enum(s, 1, conn_states, conn);
    xxx_enum(s, 1, prom_states, prom);
}



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



static if_mib_ifEntry_t *
get_if_entry(if_mib_ifEntry_t **ifTable, gint32 ifIndex)
{
    int i;
    
    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (ifTable[i]->ifIndex == ifIndex) {
		return ifTable[i];
	    }
	}
    }
    return NULL;
}
    


static int
get_if_type_width(if_mib_ifEntry_t **ifTable)
{
    int i, type_width = 6;

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (ifTable[i]->ifType) {
		char const *label;
		label = gsnmp_enum_get_label(if_mib_enums_ifType,
					     *ifTable[i]->ifType);
		if (label && strlen(label) > type_width) {
		    type_width = strlen(label);
		}
	    }
	}
    }
    return type_width;
}



static int
get_if_name_width(if_mib_ifXEntry_t **ifXTable)
{
    int i, name_width = 6;
    
    if (ifXTable) {
	for (i = 0; ifXTable[i]; i++) {
	    if (ifXTable[i]->_ifNameLength > name_width) {
		name_width = ifXTable[i]->_ifNameLength;
	    }
	}
    }
    return name_width;
}



static void
fmt_interface_details(GString *s,
		      if_mib_ifEntry_t *ifEntry,
		      if_mib_ifXEntry_t *ifXEntry,
		      snmpv2_mib_system_t *system,
		      ip_mib_ipAddrEntry_t **ipAddrTable)
{
    int j;
    char *name;
    int const width = 20;

    g_string_sprintfa(s, "Interface:   %-*d", width,
		      ifEntry->ifIndex);
    if (ifXEntry && ifXEntry->ifName) {
	g_string_sprintfa(s, " Name:    %.*s\n",
			  (int) ifXEntry->_ifNameLength,
			  ifXEntry->ifName);
    } else {
	g_string_append(s, " Name:\n");
    }
	
    g_string_append(s, "OperStatus:  ");
    xxx_enum(s, width, if_mib_enums_ifOperStatus, ifEntry->ifOperStatus);
    if (ifEntry->ifPhysAddress && ifEntry->_ifPhysAddressLength) {
	g_string_append(s, " Address: ");
	for (j = 0; j < ifEntry->_ifPhysAddressLength; j++) {
	    g_string_sprintfa(s, "%s%02X", (j == 0) ? "" : ":",
			      ifEntry->ifPhysAddress[j]);
	}
	/* See RFC 2665 section 3.2.6. why the test below is so ugly... */
	if (ifEntry->ifType && ifEntry->_ifPhysAddressLength == 6
	    && (*ifEntry->ifType == IF_MIB_IFTYPE_ETHERNETCSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_ISO88023CSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_STARLAN
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHER
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHERFX
		|| *ifEntry->ifType == IF_MIB_IFTYPE_GIGABITETHERNET)) {
	    name = fmt_ether_address(ifEntry->ifPhysAddress, SCLI_FMT_NAME);
	    if (name) {
		g_string_sprintfa(s, " (%s)", name);
	    }
	}
	g_string_append(s, "\n");
    } else {
	g_string_append(s, " Address:\n");
    }
    
    g_string_append(s, "AdminStatus: ");
    xxx_enum(s, width, if_mib_enums_ifAdminStatus, ifEntry->ifAdminStatus);
    g_string_append(s, " Type:    ");
    xxx_enum(s, width, if_mib_enums_ifType, ifEntry->ifType);
    g_string_append(s, "\n");
    
    g_string_append(s, "Traps:       ");
    xxx_enum(s, width, if_mib_enums_ifLinkUpDownTrapEnable,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifLinkUpDownTrapEnable : NULL);
    if (ifEntry->ifMtu) {
	g_string_sprintfa(s, " MTU:     %d byte\n", *(ifEntry->ifMtu));
    } else {
	g_string_append(s, " MTU:\n");
    }
    
    g_string_append(s, "Connector:   ");
    xxx_enum(s, width, if_mib_enums_ifConnectorPresent,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifConnectorPresent : NULL);
    if (ifEntry->ifSpeed) {
	if (*(ifEntry->ifSpeed) == 0xffffffff
	    && ifXEntry && ifXEntry->ifHighSpeed) {
	    g_string_sprintfa(s, " Speed:   %s bps\n",
			      fmt_gtp(*(ifXEntry->ifHighSpeed)));
	} else {
	    g_string_sprintfa(s, " Speed:   %s bps\n",
			      fmt_kmg(*(ifEntry->ifSpeed)));
	}
    } else {
	g_string_append(s, " Speed:\n");
    }
    
    g_string_append(s, "Promiscuous: ");
    xxx_enum(s, width, if_mib_enums_ifPromiscuousMode,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifPromiscuousMode : NULL);
    if (ifEntry->ifLastChange && system && system->sysUpTime) {
	guint32 dsecs = *(system->sysUpTime) - *(ifEntry->ifLastChange);
	g_string_sprintfa(s, " Change:  %s\n", fmt_timeticks(dsecs));
    } else {
	g_string_append(s, " Change:\n");
    }

    if (ipAddrTable) {
	for (j = 0; ipAddrTable[j]; j++) {
	    if (ipAddrTable[j]->ipAdEntIfIndex
		&& (ifEntry->ifIndex == *(ipAddrTable[j]->ipAdEntIfIndex))) {
		if (ipAddrTable[j]->ipAdEntAddr
		    && ipAddrTable[j]->ipAdEntNetMask) {
		    g_string_sprintfa(s, "IP Address:  %-*s", width,
		      fmt_ipv4_address(ipAddrTable[j]->ipAdEntAddr,
				       SCLI_FMT_ADDR));
		    g_string_sprintfa(s, " Prefix:  %s\n",
		      fmt_ipv4_mask(ipAddrTable[j]->ipAdEntNetMask));
		}
	    }
	}
    }
    
    if (ifEntry->ifDescr && ifEntry->_ifDescrLength) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) ifEntry->_ifDescrLength,
			  ifEntry->ifDescr);
    }
    
    if (ifXEntry && ifXEntry
	&& ifXEntry->ifAlias && ifXEntry->_ifAliasLength) {
	g_string_sprintfa(s, "Alias:       %.*s\n",
			  (int) ifXEntry->_ifAliasLength,
			  ifXEntry->ifAlias);
    }
}



static void
xml_interface_details(xmlNodePtr root,
		      if_mib_ifEntry_t *ifEntry,
		      if_mib_ifXEntry_t *ifXEntry,
		      snmpv2_mib_system_t *system,
		      ip_mib_ipAddrEntry_t **ipAddrTable)
{
    int j;
    xmlNodePtr tree;
    const char *s;

    tree = xmlNewChild(root, NULL, "interface", NULL);
    xml_set_prop(tree, "index", "%d", ifEntry->ifIndex);

    if (ifXEntry && ifXEntry->ifName) {
	(void) xml_new_child(tree, NULL, "name", "%.*s",
			     (int) ifXEntry->_ifNameLength,
			     ifXEntry->ifName);
    }

    s = fmt_enum(if_mib_enums_ifOperStatus, ifEntry->ifOperStatus);
    if (s) {
	(void) xml_new_child(tree, NULL, "operational", "%s", s);
    }
    
#if 0
    
    if (ifEntry->ifPhysAddress && ifEntry->_ifPhysAddressLength) {
	g_string_append(s, " Address: ");
	for (j = 0; j < ifEntry->_ifPhysAddressLength; j++) {
	    g_string_sprintfa(s, "%s%02X", (j == 0) ? "" : ":",
			      ifEntry->ifPhysAddress[j]);
	}
	/* See RFC 2665 section 3.2.6. why the test below is so ugly... */
	if (ifEntry->ifType && ifEntry->_ifPhysAddressLength == 6
	    && (*ifEntry->ifType == IF_MIB_IFTYPE_ETHERNETCSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_ISO88023CSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_STARLAN
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHER
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHERFX
		|| *ifEntry->ifType == IF_MIB_IFTYPE_GIGABITETHERNET)) {
	    name = fmt_ether_address(ifEntry->ifPhysAddress, SCLI_FMT_NAME);
	    if (name) {
		g_string_sprintfa(s, " (%s)", name);
	    }
	}
	g_string_append(s, "\n");
    } else {
	g_string_append(s, " Address:\n");
    }
#endif

    s = fmt_enum(if_mib_enums_ifAdminStatus, ifEntry->ifAdminStatus);
    if (s) {
	(void) xml_new_child(tree, NULL, "administrative", "%s", s);
    }

    s = fmt_enum(if_mib_enums_ifType, ifEntry->ifType);
    if (s) {
	(void) xml_new_child(tree, NULL, "type", "%s", s);
    }

#if 0
    g_string_append(s, "Traps:       ");
    xxx_enum(s, width, if_mib_enums_ifLinkUpDownTrapEnable,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifLinkUpDownTrapEnable : NULL);
    if (ifEntry->ifMtu) {
	g_string_sprintfa(s, " MTU:     %d byte\n", *(ifEntry->ifMtu));
    } else {
	g_string_append(s, " MTU:\n");
    }
    
    g_string_append(s, "Connector:   ");
    xxx_enum(s, width, if_mib_enums_ifConnectorPresent,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifConnectorPresent : NULL);
    if (ifEntry->ifSpeed) {
	if (*(ifEntry->ifSpeed) == 0xffffffff
	    && ifXEntry && ifXEntry->ifHighSpeed) {
	    g_string_sprintfa(s, " Speed:   %s bps\n",
			      fmt_gtp(*(ifXEntry->ifHighSpeed)));
	} else {
	    g_string_sprintfa(s, " Speed:   %s bps\n",
			      fmt_kmg(*(ifEntry->ifSpeed)));
	}
    } else {
	g_string_append(s, " Speed:\n");
    }
    
    g_string_append(s, "Promiscuous: ");
    xxx_enum(s, width, if_mib_enums_ifPromiscuousMode,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifPromiscuousMode : NULL);
    if (ifEntry->ifLastChange && system && system->sysUpTime) {
	guint32 dsecs = *(system->sysUpTime) - *(ifEntry->ifLastChange);
	g_string_sprintfa(s, " Change:  %s\n", fmt_timeticks(dsecs));
    } else {
	g_string_append(s, " Change:\n");
    }

    if (ipAddrTable) {
	for (j = 0; ipAddrTable[j]; j++) {
	    if (ipAddrTable[j]->ipAdEntIfIndex
		&& (ifEntry->ifIndex == *(ipAddrTable[j]->ipAdEntIfIndex))) {
		if (ipAddrTable[j]->ipAdEntAddr
		    && ipAddrTable[j]->ipAdEntNetMask) {
		    g_string_sprintfa(s, "IP Address:  %-*s", width,
		      fmt_ipv4_address(ipAddrTable[j]->ipAdEntAddr,
				       SCLI_FMT_ADDR));
		    g_string_sprintfa(s, " Prefix:  %s\n",
		      fmt_ipv4_mask(ipAddrTable[j]->ipAdEntNetMask));
		}
	    }
	}
    }
#endif
    
    if (ifEntry->ifDescr && ifEntry->_ifDescrLength) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			     (int) ifEntry->_ifDescrLength,
			     ifEntry->ifDescr);
    }
    
    if (ifXEntry && ifXEntry
	&& ifXEntry->ifAlias && ifXEntry->_ifAliasLength) {
	(void) xml_new_child(tree, NULL, "alias", "%.*s", 
			     (int) ifXEntry->_ifAliasLength,
			     ifXEntry->ifAlias);
    }
}



static gint32
get_entity_index(gint32 ifIndex,
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

    if (! entPhysicalIndex) {
	return 0;
    }

    for (i = 0; entPhysicalTable[i]; i++) {
	if (entPhysicalTable[i]->entPhysicalIndex == entPhysicalIndex) {
	    /*
	    g_printerr("%.*s\n",
		       (int) entPhysicalTable[i]->_entPhysicalDescrLength,
		       entPhysicalTable[i]->entPhysicalDescr);
	    */
	}
    }
    return entPhysicalIndex;
}



static int
show_interface_details(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    snmpv2_mib_system_t *system = NULL;
    ip_mib_ipAddrEntry_t **ipAddrTable = NULL;
    entity_mib_entAliasMappingEntry_t **entAliasMappingTable = NULL;
    entity_mib_entPhysicalEntry_t **entPhysicalTable = NULL;
    regex_t _regex_iface, *regex_iface = NULL;
    int i, c;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    (void) snmpv2_mib_get_system(interp->peer, &system);
    (void) ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable);

    if (entity_mib_get_entAliasMappingTable(interp->peer,
					    &entAliasMappingTable) == 0) {
	(void) entity_mib_get_entPhysicalTable(interp->peer, &entPhysicalTable);
	
    }

    if (ifTable) {
	for (i = 0, c = 0; ifTable[i]; i++) {
	    if (match_interface(regex_iface, ifTable[i])) {
		if (scli_interp_xml(interp)) {
		    xml_interface_details(interp->xml_node, ifTable[i],
					  ifXTable ? ifXTable[i] : NULL,
					  system, ipAddrTable);
		} else {
		    if (c) {
			g_string_append(interp->result, "\n");
		    }
		    (void) get_entity_index(ifTable[i]->ifIndex,
					    entAliasMappingTable, entPhysicalTable);
		    fmt_interface_details(interp->result, ifTable[i],
					  ifXTable ? ifXTable[i] : NULL,
					  system, ipAddrTable);
		}
		c++;
	    }
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (system) snmpv2_mib_free_system(system);
    if (ipAddrTable) ip_mib_free_ipAddrTable(ipAddrTable);
    if (entAliasMappingTable)
	entity_mib_free_entAliasMappingTable(entAliasMappingTable);
    if (entPhysicalTable)
	entity_mib_free_entPhysicalTable(entPhysicalTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



static void
fmt_interface_info(GString *s,
	     if_mib_ifEntry_t *ifEntry,
	     if_mib_ifXEntry_t *ifXEntry,
	     int type_width, int name_width)
{
    g_string_sprintfa(s, "%9u  ", ifEntry->ifIndex);

    fmt_ifStatus(s,
		 ifEntry->ifAdminStatus, ifEntry->ifOperStatus,
		 ifXEntry ? ifXEntry->ifConnectorPresent : NULL,
		 ifXEntry ? ifXEntry->ifPromiscuousMode : NULL);

    if (ifEntry->ifMtu) {
	g_string_sprintfa(s, " %5d", *(ifEntry->ifMtu));
    } else {
	g_string_sprintfa(s, "      ");
    }

    g_string_append(s, " ");
    xxx_enum(s, type_width, if_mib_enums_ifType, ifEntry->ifType);
    g_string_append(s, " ");

    if (ifEntry->ifSpeed) {
	if (*(ifEntry->ifSpeed) == 0xffffffff
	    && ifXEntry && ifXEntry->ifHighSpeed) {
	    g_string_sprintfa(s, "  %4s ",
			      fmt_gtp(*(ifXEntry->ifHighSpeed)));
	} else {
	    g_string_sprintfa(s, "  %4s ",
			      fmt_kmg(*(ifEntry->ifSpeed)));
	}
    } else {
	g_string_append(s, "       ");
    }

    if (ifXEntry && ifXEntry->ifName) {
	g_string_sprintfa(s, "%-*.*s ", name_width,
			  (int) ifXEntry->_ifNameLength,
			  ifXEntry->ifName);
    } else {
	g_string_sprintfa(s, "%*s ", name_width, "");
    }

    if (ifEntry->ifDescr) {
	g_string_sprintfa(s, "%.*s",
			  (int) ifEntry->_ifDescrLength,
			  ifEntry->ifDescr);
    }

    g_string_append(s, "\n");
}



static int
show_interface_info(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int name_width, type_width;
    regex_t _regex_iface, *regex_iface = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    type_width = get_if_type_width(ifTable);
    name_width = get_if_name_width(ifXTable);

    if (ifTable) {
	g_string_sprintfa(interp->header,
		  "INTERFACE STATUS  MTU %-*s  SPEED %-*s DESCRIPTION",
			  type_width, "TYPE",
			  name_width, "NAME");
	for (i = 0; ifTable[i]; i++) {
	    if (match_interface(regex_iface, ifTable[i])) {
		fmt_interface_info(interp->result, ifTable[i],
				   ifXTable ? ifXTable[i] : NULL,
				   type_width, name_width);
	    }
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



static void
fmt_interface_stack(GString *s,
		    if_mib_ifStackEntry_t *ifStackEntry,
		    if_mib_ifStackEntry_t **ifStackTable,
		    if_mib_ifEntry_t **ifTable,
		    int level, int type_width)
{
    /*
     *      ,-- if2 
     * if1 -+-- if3
     *      `-- if4
     *
     * if5 -,
     * if6 -+-- if8
     * if7 -'
     */

    int i = 0;
    char *ifDescr = NULL;
    int ifDescrLength = 0;
    if_mib_ifEntry_t *ifEntry = NULL;

    if (! ifStackEntry->ifStackStatus
	|| *ifStackEntry->ifStackStatus != IF_MIB_IFSTACKSTATUS_ACTIVE) {
	return;
    }
    
    ifEntry = get_if_entry(ifTable, ifStackEntry->ifStackHigherLayer);

    if (ifEntry->ifDescr) {
	ifDescr = ifEntry->ifDescr;
	ifDescrLength = ifEntry->_ifDescrLength;
    }

    g_string_sprintfa(s, "%9d ", ifStackEntry->ifStackHigherLayer);
    xxx_enum(s, type_width, if_mib_enums_ifType, ifEntry->ifType);
    g_string_sprintfa(s, " %*s%s %.*s\n",
		      level*4, "", level ? "`-" : " -",
		      ifDescrLength, ifDescr ? ifDescr : "");

    for (i = 0; ifStackTable[i]; i++) {
	if ((ifStackTable[i]->ifStackLowerLayer
	     == ifStackEntry->ifStackHigherLayer)
	    && ifStackTable[i]->ifStackHigherLayer) {
	    fmt_interface_stack(s, ifStackTable[i], ifStackTable, ifTable,
				level+1, type_width);
	    if (ifStackTable[i]->ifStackStatus) {
		*ifStackTable[i]->ifStackStatus = 0;
	    }
	}
    }
}



static int
show_interface_stack(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifStackEntry_t **ifStackTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifEntry_t *ifEntry = NULL;
    regex_t _regex_iface, *regex_iface = NULL;
    int i, type_width;

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (if_mib_get_ifStackTable(interp->peer, &ifStackTable)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifTable(interp->peer, &ifTable);

    type_width = get_if_type_width(ifTable);

    if (ifStackTable) {
	g_string_sprintfa(interp->header, "INTERFACE %-*s    STACKING ORDER",
			  type_width, "TYPE");
	for (i = 0; ifStackTable[i]; i++) {
	    if (ifStackTable[i]->ifStackLowerLayer == 0) {
		ifEntry = get_if_entry(ifTable,
				       ifStackTable[i]->ifStackHigherLayer);
		if (! ifEntry) {
		    g_warning("stacked interface %d does not exist "
			      "in the ifTable",
			      ifStackTable[i]->ifStackHigherLayer);
		    continue;
		}
		if (match_interface(regex_iface, ifEntry)) {
		    fmt_interface_stack(interp->result, ifStackTable[i],
					ifStackTable, ifTable, 0, type_width);
		}
	    }
	}
    }

    if (ifStackTable) if_mib_free_ifStackTable(ifStackTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    
    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



typedef struct {
    guint32 inOctets;
    guint32 outOctets;
    guint32 inPkts;
    guint32 outPkts;
    guint32 inErrors;
    guint32 outErrors;
} if_stats_t;



static int
show_interface_stats(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    static struct timeval last, now;
    double delta;
    static if_stats_t *stats = NULL;
    static time_t epoch = 0;
    regex_t _regex_iface, *regex_iface = NULL;
    int i;

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    if (epoch < interp->epoch) {
	if (stats) g_free(stats);
	stats = NULL;
	last.tv_sec = last.tv_usec = 0;
    }

    if (! stats && ifTable) {
	for (i = 0; ifTable[i]; i++) ;
	stats = (if_stats_t *) g_malloc0(i * sizeof(if_stats_t));
    }

    epoch = time(NULL);
    gettimeofday(&now, NULL);
    delta = TV_DIFF(last, now);

    if (ifTable) {
	g_string_append(interp->header, "INTERFACE STATUS "
			"I-BPS O-BPS I-PPS O-PPS I-ERR O-ERR  DESCRIPTION");
	for (i = 0; ifTable[i]; i++) {
	    GString *s;
	    if (! match_interface(regex_iface, ifTable[i])) {
		continue;
	    }
	    s = interp->result;
	    g_string_sprintfa(s, "%9u  ", ifTable[i]->ifIndex);
	    fmt_ifStatus(s,
			 ifTable[i]->ifAdminStatus, ifTable[i]->ifOperStatus,
	 (ifXTable && ifXTable[i]) ? ifXTable[i]->ifConnectorPresent : NULL,
	 (ifXTable && ifXTable[i]) ? ifXTable[i]->ifPromiscuousMode : NULL);

	    g_string_sprintfa(s, " ");

	    fmt_counter_dt(s, ifTable[i]->ifInOctets, &(stats[i].inOctets),
			   &last, delta);

	    fmt_counter_dt(s, ifTable[i]->ifOutOctets, &(stats[i].outOctets),
			   &last, delta);
	    
	    if (ifTable[i]->ifInUcastPkts && delta > TV_DELTA) {
		guint32 pkts;
		pkts = *(ifTable[i]->ifInUcastPkts);
		if (ifXTable && ifXTable[i]->ifInMulticastPkts
		    && ifXTable[i]->ifInBroadcastPkts) {
		    pkts += *(ifXTable[i]->ifInMulticastPkts);
		    pkts += *(ifXTable[i]->ifInBroadcastPkts);
		} else if (ifTable[i]->ifInNUcastPkts) {
		    pkts += *(ifTable[i]->ifInNUcastPkts);
		} else {
		    /* might be fixed length ??? */
		}
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (pkts - stats[i].inPkts) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].inPkts = pkts;
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    if (ifTable[i]->ifOutUcastPkts && delta > TV_DELTA) {
		guint32 pkts;
		pkts = *(ifTable[i]->ifOutUcastPkts);
		if (ifXTable && ifXTable[i]->ifOutMulticastPkts
		    && ifXTable[i]->ifOutBroadcastPkts) {
		    pkts += *(ifXTable[i]->ifOutMulticastPkts);
		    pkts += *(ifXTable[i]->ifOutBroadcastPkts);
		} else if (ifTable[i]->ifOutNUcastPkts) {
		    pkts += *(ifTable[i]->ifOutNUcastPkts);
		} else {
		    /* might be fixed length ??? */
		}
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (pkts - stats[i].outPkts) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].outPkts = pkts;
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    fmt_counter_dt(s, ifTable[i]->ifInErrors, &(stats[i].inErrors),
			   &last, delta);

	    fmt_counter_dt(s, ifTable[i]->ifOutErrors, &(stats[i].outErrors),
			   &last, delta);
	    
	    if (ifTable[i]->ifDescr && ifTable[i]->_ifDescrLength) {
		g_string_sprintfa(s, "  %.*s",
				  (int) ifTable[i]->_ifDescrLength,
				  ifTable[i]->ifDescr);
	    }
	    g_string_append(s, "\n");
	}
    }
    
    last = now;
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



typedef void (*InterfaceForeachFunc)	(scli_interp_t    *interp,
					 if_mib_ifEntry_t *ifEntry,
					 gpointer	  user_data);

static int
foreach_interface(scli_interp_t *interp, char *regex,
		  InterfaceForeachFunc func, gpointer user_data)
{
    if_mib_ifEntry_t **ifTable = NULL;
    regex_t _regex_iface, *regex_iface = &_regex_iface;
    int i;

    if (regcomp(regex_iface, regex, REG_EXTENDED|REG_NOSUB) != 0) {
	return SCLI_SYNTAX_REGEXP;
    }

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	regfree(regex_iface);
	return SCLI_ERROR;
    }

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (match_interface(regex_iface, ifTable[i])) {
		g_printerr("** interface %d **\n", ifTable[i]->ifIndex);
		(func) (interp, ifTable[i], user_data);
		/* call function here */
	    }
	}
    }
    
    if (ifTable) if_mib_free_ifTable(ifTable);
    regfree(regex_iface);

    return SCLI_OK;
}



static void
set_status(scli_interp_t *interp, if_mib_ifEntry_t *ifEntry,
	   gpointer user_data)
{
    if_mib_ifEntry_t *ifXEntry;
    gint32 *value = (gint32 *) user_data;

    ifXEntry = if_mib_new_ifEntry();
    ifXEntry->ifIndex = ifEntry->ifIndex;
    ifXEntry->ifAdminStatus = value;
    (void) if_mib_set_ifEntry(interp->peer, ifXEntry);
    if (interp->peer->error_status) {
	interface_snmp_error(interp, ifEntry);
    }
    if_mib_free_ifEntry(ifXEntry);
}



static int
set_interface_status(scli_interp_t *interp, int argc, char **argv)
{
    gint32 value;
    int status;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    if (! gsnmp_enum_get_number(if_mib_enums_ifAdminStatus, argv[2], &value)) {
	return SCLI_SYNTAX;
    }

    status = foreach_interface(interp, argv[1], set_status, &value);
    return status;
}



static void
set_alias(scli_interp_t *interp, if_mib_ifEntry_t *ifEntry,
	  gpointer user_data)
{
    if_mib_ifXEntry_t *ifXEntry;
    char *value = (char *) user_data;

    ifXEntry = if_mib_new_ifXEntry();
    ifXEntry->ifIndex = ifEntry->ifIndex;
    ifXEntry->ifAlias = value;
    ifXEntry->_ifAliasLength = strlen(value);
    (void) if_mib_set_ifXEntry(interp->peer, ifXEntry);
    if (interp->peer->error_status) {
	interface_snmp_error(interp, ifEntry);
    }
    if_mib_free_ifXEntry(ifXEntry);
}



static int
set_interface_alias(scli_interp_t *interp, int argc, char **argv)
{
    int status;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    status = foreach_interface(interp, argv[1], set_alias, argv[2]);
    return status;
}



static void
set_promiscuous(scli_interp_t *interp, if_mib_ifEntry_t *ifEntry,
		gpointer user_data)
{
    if_mib_ifXEntry_t *ifXEntry;
    gint32 *value = (gint32 *) user_data;

    ifXEntry = if_mib_new_ifXEntry();
    ifXEntry->ifIndex = ifEntry->ifIndex;
    ifXEntry->ifPromiscuousMode = value;
    (void) if_mib_set_ifXEntry(interp->peer, ifXEntry);
    if (interp->peer->error_status) {
	interface_snmp_error(interp, ifEntry);
    }
    if_mib_free_ifXEntry(ifXEntry);
}



static int
set_interface_promiscuous(scli_interp_t *interp, int argc, char **argv)
{
    gint32 value;
    int status;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    if (! gsnmp_enum_get_number(if_mib_enums_ifPromiscuousMode,
				argv[2], &value)) {
	return SCLI_SYNTAX;
    }

    status = foreach_interface(interp, argv[1], set_promiscuous, &value);
    return status;
}



static void
set_notifications(scli_interp_t *interp, if_mib_ifEntry_t *ifEntry,
		  gpointer user_data)
{
    if_mib_ifXEntry_t *ifXEntry;
    gint32 *value = (gint32 *) user_data;

    ifXEntry = if_mib_new_ifXEntry();
    ifXEntry->ifIndex = ifEntry->ifIndex;
    ifXEntry->ifLinkUpDownTrapEnable = value;
    (void) if_mib_set_ifXEntry(interp->peer, ifXEntry);
    if (interp->peer->error_status) {
	interface_snmp_error(interp, ifEntry);
    }
    if_mib_free_ifXEntry(ifXEntry);
}



static int
set_interface_notifications(scli_interp_t *interp, int argc, char **argv)
{
    gint32 value;
    int status;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX;
    }

    if (! gsnmp_enum_get_number(if_mib_enums_ifLinkUpDownTrapEnable,
				argv[2], &value)) {
	return SCLI_SYNTAX;
    }

    status = foreach_interface(interp, argv[1], set_notifications, &value);
    return status;
}



void
scli_init_interface_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "set interface status", "<regexp> <status>",
	  "The set interface status command modifies the administrative\n"
	  "status of all selected interfaces. The regular expression\n"
	  "<regexp> is matched against the interface descriptions to\n"
	  "select the interfaces of interest. The <value> parameter must\n"
	  "be one of the strings \"up\", \"down\", or \"testing\".",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_interface_status },

	{ "set interface alias", "<regexp> <string>",
	  "The set interface alias command assigns the alias name\n"
	  "<string> to the selected interfaces. The alias name provies\n"
	  "a non-volatile 'handle' which can be used by management\n"
	  "applications to better identify interfaces. The regular\n"
	  "expression <regexp> is matched against the interface\n"
	  "descriptions to select the interfaces.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_interface_alias },

	{ "set interface notifications", "<regexp> <value>",
	  "The set interface notifications command controls whether the\n"
	  "selected interfaces generate linkUp and linkDown notifications.\n"
	  "The regular expression <regexp> is matched against the interface\n"
	  "descriptions to select the interfaces. The <value> parameter\n"
	  "must be one of the strings \"enabled\" or \"disabled\".",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_interface_notifications },

	{ "set interface promiscuous", "<regexp> <bool>",
	  "The set interface promiscuous command controls whether the\n"
	  "selected interfaces operate in promiscuous mode or not. The\n"
	  "regular expression <regexp> is matched against the interface\n"
	  "descriptions to select the interfaces. The <bool> parameter\n"
	  "must be one of the strings \"true\" or \"false\".",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_interface_promiscuous },

	{ "show interface info", "[<regexp>]",
	  "The show interface info command displays summary information\n"
	  "for all selected interfaces. The optional regular expression\n"
	  "<regexp> is matched against the interface descriptions to\n"
	  "select the interfaces of interest. The command generates a\n"
	  "table with the following columns:\n"
	  "\n"
	  "  INTERFACE   network interface number\n"
	  "  STATUS      interface status (see below)\n"
	  "  MTU         maximum transfer unit\n"
	  "  TYPE        type of the network interface\n"
	  "  SPEED       speed in bits per second\n"
	  "  NAME        name of the network interface\n"
	  "  DESCRIPTION description of the network interface\n"
	  "\n"
	  "The status is encoded in four characters. The first character\n"
	  "indicates the administrative status (U=up, D=down, T=testing).\n"
	  "The second character indicates the operational status (U=up,\n"
	  "D=down, T=testing, ?=unknown, O=dormant, N=not-present,\n"
	  "L=lower-layer-down). The third character indicates whether a\n"
	  "connector is present (C=connector, N=none) and the fourth\n"
	  "character indicates whether the interface is in promiscuous\n"
	  "mode (P=promiscuous, N=normal).",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_interface_info },
	
	{ "show interface details", "[<regexp>]",
	  "The show interface details command describes the selected\n"
	  "interfaces in more detail. The optional regular expression\n"
	  "<regexp> is matched against the interface descriptions to\n"
	  "select the interfaces of interest.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "interfaces", NULL,
	  show_interface_details },
	
	{ "show interface stack", "[<regexp>]",
	  "The show interface stack command shows the stacking order\n"
	  "of the interfaces. <xxx>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_interface_stack },
	
	{ "show interface stats", "[<regexp>]",
	  "The show interface stats command displays network\n"
	  "interface statistics for all selected interfaces.\n"
	  "The optional regular expression <regexp> is matched\n"
	  "against the interface description to select the\n"
	  "interfaces. The command outputs a table which has\n"
	  "the following columns:\n"
	  "\n"
	  "  INTERFACE   network interface number\n"
	  "  STATUS      interface status (see above)\n"
	  "  I-BPS       input bytes per second\n"
	  "  O-BPS       output bytes per second\n"
	  "  I-PPS       input packets per second\n"
	  "  O-PPS       output packets per second\n"
	  "  I-ERR       input errors per second\n"
	  "  O-ERR       output errors per second\n"
	  "  DESCRIPTION description of the network interface",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_interface_stats },
	
	{ "monitor interface stats", "[<regexp>]",
	  "The monitor interface stats command shows the same\n"
	  "information as the show interface stats command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  show_interface_stats },
	
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t if_mib_mode = {
	"interface",
	"The scli interface mode is based on the IF-MIB as published in\n"
	"RFC 2863. It provides commands to browse, monitor and configure\n"
	"arbitrary network interfaces.",
	cmds
    };

    scli_register_mode(interp, &if_mib_mode);
}
