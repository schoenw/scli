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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "scli.h"

#include "snmpv2-mib.h"
#include "if-mib.h"
#include "ip-mib.h"



static void
fmt_ifStatus(GString *s, gint32 *admin, gint32 *oper,
	     gint32 *conn, gint32 *prom)
{
    static stls_enum_t const admin_states[] = {
	{ IF_MIB_IFADMINSTATUS_UP,	"U" },
	{ IF_MIB_IFADMINSTATUS_DOWN,	"D" },
	{ IF_MIB_IFADMINSTATUS_TESTING,	"T" },
	{ 0, NULL }
    };

    static stls_enum_t const oper_states[] = {
	{ IF_MIB_IFOPERSTATUS_UP,		"U" },
	{ IF_MIB_IFOPERSTATUS_DOWN,		"D" },
	{ IF_MIB_IFOPERSTATUS_TESTING,		"T" },
	{ IF_MIB_IFOPERSTATUS_UNKNOWN,		"?" },
	{ IF_MIB_IFOPERSTATUS_DORMANT,		"O" },
	{ IF_MIB_IFOPERSTATUS_NOTPRESENT,	"N" },
	{ IF_MIB_IFOPERSTATUS_LOWERLAYERDOWN,	"L" },
	{ 0, NULL }
    };

    static stls_enum_t const conn_states[] = {
	{ IF_MIB_IFCONNECTORPRESENT_TRUE,	"C" },
	{ IF_MIB_IFCONNECTORPRESENT_FALSE,	"N" },
	{ 0, NULL }
    };

    static stls_enum_t const prom_states[] = {
	{ IF_MIB_IFPROMISCUOUSMODE_TRUE,	"P" },
	{ IF_MIB_IFPROMISCUOUSMODE_FALSE,	"N" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, admin_states, admin);
    fmt_enum(s, 1, oper_states, oper);
    fmt_enum(s, 1, conn_states, conn);
    fmt_enum(s, 1, prom_states, prom);
}
    


static void
show_if_details(GString *s, ifEntry_t *ifEntry, ifXEntry_t *ifXEntry,
		system_t *system, ipAddrEntry_t **ipAddrTable)
{
    int j;
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
    fmt_enum(s, width, if_mib_enums_ifOperStatus, ifEntry->ifOperStatus);
    if (ifEntry->ifPhysAddress && ifEntry->_ifPhysAddressLength) {
	g_string_append(s, " Address: ");
	for (j = 0; j < ifEntry->_ifPhysAddressLength; j++) {
	    g_string_sprintfa(s, "%s%02X", (j == 0) ? "" : ":",
			      ifEntry->ifPhysAddress[j]);
	}
	g_string_append(s, "\n");
    } else {
	g_string_append(s, " Address:\n");
    }
    
    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, width, if_mib_enums_ifAdminStatus, ifEntry->ifAdminStatus);
    g_string_append(s, " Type:    ");
    fmt_enum(s, width, if_mib_enums_ifType, ifEntry->ifType);
    g_string_append(s, "\n");
    
    g_string_append(s, "Traps:       ");
    fmt_enum(s, width, if_mib_enums_ifLinkUpDownTrapEnable,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifLinkUpDownTrapEnable : NULL);
    if (ifEntry->ifMtu) {
	g_string_sprintfa(s, " MTU:     %d byte\n", *(ifEntry->ifMtu));
    } else {
	g_string_append(s, " MTU:\n");
    }
    
    g_string_append(s, "Connector:   ");
    fmt_enum(s, width, if_mib_enums_ifConnectorPresent,
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
    fmt_enum(s, width, if_mib_enums_ifPromiscuousMode,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifPromiscuousMode : NULL);
    if (ifEntry->ifLastChange && system && system->sysUpTime) {
	guint32 dsecs = *(system->sysUpTime) - *(ifEntry->ifLastChange);
	g_string_sprintfa(s, " Change:  ");
	fmt_time_ticks(s, dsecs);
	g_string_append(s, "\n");
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
		      fmt_ipv4_address(ipAddrTable[j]->ipAdEntAddr, 0));
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



static int
cmd_if_details(scli_interp_t *interp, int argc, char **argv)
{
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    system_t *system = NULL;
    ipAddrEntry_t **ipAddrTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    (void) snmpv2_mib_get_system(interp->peer, &system);
    (void) ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable);

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_if_details(interp->result, ifTable[i],
			    ifXTable ? ifXTable[i] : NULL,
			    system, ipAddrTable);
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (system) snmpv2_mib_free_system(system);
    if (ipAddrTable) ip_mib_free_ipAddrTable(ipAddrTable);

    return SCLI_OK;
}



static void
show_if_info(GString *s, ifEntry_t *ifEntry, ifXEntry_t *ifXEntry,
	     int type_width, int name_width)
{
    g_string_sprintfa(s, "%6u     ", ifEntry->ifIndex);

    fmt_ifStatus(s,
		 ifEntry->ifAdminStatus, ifEntry->ifOperStatus,
		 ifXEntry ? ifXEntry->ifConnectorPresent : NULL,
		 ifXEntry ? ifXEntry->ifPromiscuousMode : NULL);

    g_string_append(s, "  ");
    fmt_enum(s, type_width, if_mib_enums_ifType, ifEntry->ifType);
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
cmd_if_info(scli_interp_t *interp, int argc, char **argv)
{
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    int name_width = 6;
    int type_width = 6;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (ifXTable && ifXTable[i]) {
		if (ifXTable[i]->_ifNameLength > name_width) {
		    name_width = ifXTable[i]->_ifNameLength;
		}
	    }
	    if (ifTable[i]->ifType) {
		char const *label;
		label = stls_enum_get_label(if_mib_enums_ifType,
					*ifTable[i]->ifType);
		if (label && strlen(label) > type_width) {
		    type_width = strlen(label);
		}
	    }
	}
	g_string_sprintfa(interp->result,
			  "Interface Status %-*s  Speed %-*s Description\n",
			  type_width, "Type",
			  name_width, "Name");
	for (i = 0; ifTable[i]; i++) {
	    show_if_info(interp->result, ifTable[i],
			 ifXTable ? ifXTable[i] : NULL,
			 type_width, name_width);
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    return SCLI_OK;
}


#if 0
static int
cmd_if_stack(scli_interp_t *interp, int argc, char **argv)
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
    
    return SCLI_OK;
}
#endif


void
scli_init_interface_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show interface info",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "network interface summary",
	  cmd_if_info },
	{ "show interface details",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "network interface details",
	  cmd_if_details },
#if 0
	{ "show interface stack",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "network interface stacking",
	  cmd_if_stack },
#endif
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t if_mib_mode = {
	"interface",
	"scli mode to display and configure interface parameters",
	cmds
    };
    
    scli_register_mode(interp, &if_mib_mode);
}
