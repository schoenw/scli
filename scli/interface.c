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



static char*
get_if_name(ifEntry_t *ifEntry, ifXEntry_t *ifXEntry, int width)
{
    static char buffer[80];

    buffer[0] = 0;
    if (ifXEntry && ifXEntry->ifName && ifXEntry->_ifNameLength) {
	g_snprintf(buffer, sizeof(buffer), "%.*s",
		   (int) ifXEntry->_ifNameLength, ifXEntry->ifName);
    } else if (ifEntry->ifDescr && ifEntry->_ifDescrLength
	       && ifEntry->_ifDescrLength < width) {
	g_snprintf(buffer, sizeof(buffer), "%.*s",
		   (int) ifEntry->_ifDescrLength, ifEntry->ifDescr);
#if 0
    } else {
	g_snprintf(buffer, sizeof(buffer), "if#%-*d", width - 3,
		   ifEntry->ifIndex);
#endif
    }

    return buffer;
}



static void
fmt_ifStatus(GString *s, gint32 *admin, gint32 *oper)
{
    stls_table_t const admin_states[] = {
	{ 1, "u" },	/* up */
	{ 2, "d" },	/* down */
	{ 3, "t" },	/* testing */
	{ 0, NULL }
    };

    stls_table_t const oper_states[] = {
	{ 1, "u" },	/* up */
	{ 2, "d" },	/* down */
	{ 3, "t" },	/* testing */
	{ 4, "?" },	/* unknown */
	{ 5, "o" },	/* dormant */
	{ 6, "n" },	/* notPresent */
	{ 7, "l" },	/* lowerLayerDown */
	{ 0, NULL }
    };
    
    g_string_append(s, " ");
    fmt_enum(s, 1, admin_states, admin);
    g_string_append(s, "/");
    fmt_enum(s, 1, oper_states, oper);
}
    


static void
show_details(GString *s, ifEntry_t *ifEntry, ifXEntry_t *ifXEntry,
	     system_t *system, ipAddrEntry_t **ipAddrTable)
{
    int j;
    int const width = 20;

    g_string_sprintfa(s, "Index:       %-*d", width,
		      ifEntry->ifIndex);
    g_string_sprintfa(s, " Name:    %-*s\n", width,
		      get_if_name(ifEntry, ifXEntry, width));
    
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
	    
    for (j = 0; ipAddrTable[j]; j++) {
	if (ipAddrTable[j]->ipAdEntIfIndex
	    && (ifEntry->ifIndex == *(ipAddrTable[j]->ipAdEntIfIndex))) {
	    g_string_sprintfa(s, "IP Address:  %-*s", width,
		      fmt_ipv4_address(ipAddrTable[j]->ipAdEntAddr, 0));
	    g_string_sprintfa(s, " Prefix:  %s\n",
		      fmt_ipv4_mask(ipAddrTable[j]->ipAdEntNetMask));
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
cmd_details(scli_interp_t *interp, int argc, char **argv)
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
	    show_details(interp->result, ifTable[i],
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
show_info(GString *s, ifEntry_t *ifEntry, ifXEntry_t *ifXEntry,
	  int name_width)
{
    int j;

    g_string_sprintfa(s, "%5u ", ifEntry->ifIndex);
    g_string_sprintfa(s, "%-*s ", name_width,
		      get_if_name(ifEntry, ifXEntry, 12));
    fmt_ifStatus(s, ifEntry->ifAdminStatus, ifEntry->ifOperStatus);

    if (ifEntry->ifMtu) {
	g_string_sprintfa(s, " %6d", *(ifEntry->ifMtu));
    } else {
	g_string_append(s, "       ");
    }

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

    fmt_enum(s, 20, if_mib_enums_ifType, ifEntry->ifType);
    g_string_append(s, " ");

    if (ifEntry->ifPhysAddress && ifEntry->_ifPhysAddressLength) {
	for (j = 0; j < ifEntry->_ifPhysAddressLength; j++) {
	    g_string_sprintfa(s, "%s%02X", (j == 0) ? "" : ":",
			      ifEntry->ifPhysAddress[j]);
	}
    }

    g_string_append(s, "\n");
}



static int
cmd_info(scli_interp_t *interp, int argc, char **argv)
{
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    int i;
    int name_width = 12;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    char *x = get_if_name(ifTable[i], ifXTable ? ifXTable[i] : NULL, 12);
	    if (x && strlen(x) > name_width) {
		name_width = strlen(x);
	    }
	}
	g_string_sprintfa(interp->result,
			  "Index %-*s Status  MTU Speed Type"
			  "                 Address\n",
			  name_width, "Name");
	for (i = 0; ifTable[i]; i++) {
	    show_info(interp->result, ifTable[i],
		      ifXTable ? ifXTable[i] : NULL,
		      name_width);
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    return SCLI_OK;
}



static int
cmd_stack(scli_interp_t *interp, int argc, char **argv)
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



void
scli_init_interface_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "interface", NULL, NULL },
	{ "show interface", "details",
	  "show detailed information about the network interfaces",
	  cmd_details },
	{ "show interface", "info",
	  "show network interface summary information",
	  cmd_info },
	{ "show interface", "stack",
	  "show interface stacking information",
	  cmd_stack },
	{ NULL, NULL, NULL, NULL }
    };
    
    static scli_mode_t if_mib_mode = {
	"interface",
	"scli mode to display and configure interface parameters",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &if_mib_mode);
}
