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

#include "stools.h"
#include "scli.h"


static int
cmd_interfaces(scli_interp_t *interp, int argc, char **argv)
{
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    system_t *system = NULL;
    ipAddrEntry_t **ipAddrTable = NULL;
    GString *s;
    int i, j;
    int const width = 20;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    (void) snmpv2_mib_get_system(interp->peer, &system);
    (void) ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable);

    s = interp->result;
    if (ifTable) {

	for (i = 0; ifTable[i]; i++) {

	    if (i) {
		g_string_append(s, "\n");
	    }

	    g_string_sprintfa(s, "Index:       %-*d", width,
			      ifTable[i]->ifIndex);
	    if (ifXTable && ifXTable[i]
		&& ifXTable[i]->ifName && ifXTable[i]->_ifNameLength) {
		g_string_sprintfa(s, " Name:    %.*s\n",
			    (int) ifXTable[i]->_ifNameLength,
				  ifXTable[i]->ifName);
	    } else if (ifTable[i]->ifDescr && ifTable[i]->_ifDescrLength
		&& ifTable[i]->_ifDescrLength < width) {
		g_string_sprintfa(s, " Name:    %.*s\n",
			    (int) ifTable[i]->_ifDescrLength,
				  ifTable[i]->ifDescr);
	    } else {
		g_string_sprintfa(s, " Name:    if#%-17d\n",
				  ifTable[i]->ifIndex);
	    }

	    g_string_append(s, "OperStatus:  ");
	    fmt_enum(s, width, if_mib_enums_ifOperStatus,
		     ifTable[i]->ifOperStatus);
	    if (ifTable[i]->ifPhysAddress
		&& ifTable[i]->_ifPhysAddressLength) {
		g_string_append(s, " Address: ");
		for (j = 0; j < ifTable[i]->_ifPhysAddressLength; j++) {
		    g_string_sprintfa(s, "%s%02X",
				      (j == 0) ? "" : ":",
				      ifTable[i]->ifPhysAddress[j]);
		}
		g_string_append(s, "\n");
	    } else {
		g_string_append(s, " Address:\n");
	    }

	    g_string_append(s, "AdminStatus: ");
	    fmt_enum(s, width, if_mib_enums_ifAdminStatus,
		     ifTable[i]->ifAdminStatus);
	    g_string_append(s, " Type:    ");
	    fmt_enum(s, width, if_mib_enums_ifType,
		     ifTable[i]->ifType);
	    g_string_append(s, "\n");

	    g_string_append(s, "Traps:       ");
	    fmt_enum(s, width, if_mib_enums_ifLinkUpDownTrapEnable,
		     (ifXTable && ifXTable[i]) ?
		     ifXTable[i]->ifLinkUpDownTrapEnable : NULL);
	    if (ifTable[i]->ifMtu) {
		g_string_sprintfa(s, " MTU:     %d byte\n",
				  *(ifTable[i]->ifMtu));
	    } else {
		g_string_append(s, " MTU:\n");
	    }

	    g_string_append(s, "Connector:   ");
	    fmt_enum(s, width, if_mib_enums_ifConnectorPresent,
		     (ifXTable && ifXTable[i]) ?
		     ifXTable[i]->ifConnectorPresent : NULL);
	    if (ifTable[i]->ifSpeed) {
		if (*(ifTable[i]->ifSpeed) == 0xffffffff
		    && ifXTable && ifXTable[i]->ifHighSpeed) {
		    g_string_sprintfa(s, " Speed:   %s bps\n",
				      fmt_gtp(*(ifXTable[i]->ifHighSpeed)));
		} else {
		    g_string_sprintfa(s, " Speed:   %s bps\n",
				      fmt_kmg(*(ifTable[i]->ifSpeed)));
		}
	    } else {
		g_string_append(s, " Speed:\n");
	    }
	    
	    g_string_append(s, "Promiscuous: ");
	    fmt_enum(s, width, if_mib_enums_ifPromiscuousMode,
		     (ifXTable && ifXTable[i]) ?
		     ifXTable[i]->ifPromiscuousMode : NULL);
	    if (ifTable[i]->ifLastChange && system && system->sysUpTime) {
		guint32 dsecs =
		    *(system->sysUpTime) - *(ifTable[i]->ifLastChange);
		g_string_sprintfa(s, " Change:  ");
		fmt_time_ticks(s, dsecs);
		g_string_append(s, "\n");
	    } else {
		g_string_append(s, " Change:\n");
	    }
	    
	    for (j = 0; ipAddrTable[j]; j++) {
		if (ipAddrTable[j]->ipAdEntIfIndex
		    && (ifTable[i]->ifIndex
			== *(ipAddrTable[j]->ipAdEntIfIndex))) {
		    g_string_sprintfa(s, "IP Address:  %-*s", width,
				      fmt_ipv4_address(
					  ipAddrTable[j]->ipAdEntAddr, 0));
		    g_string_sprintfa(s, " Prefix:  %s\n",
				      fmt_ipv4_mask(
					  ipAddrTable[j]->ipAdEntNetMask));
		}
	    }
	    	    
	    if (ifTable[i]->ifDescr && ifTable[i]->_ifDescrLength) {
		g_string_sprintfa(s, "Description: %.*s\n",
			    (int) ifTable[i]->_ifDescrLength,
				  ifTable[i]->ifDescr);
	    }

	    if (ifXTable && ifXTable[i]
		&& ifXTable[i]->ifAlias && ifXTable[i]->_ifAliasLength) {
		g_string_sprintfa(s, "Alias:       %.*s\n",
			    (int) ifXTable[i]->_ifAliasLength,
				  ifXTable[i]->ifAlias);
	    }
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (system) snmpv2_mib_free_system(system);
    if (ipAddrTable) ip_mib_free_ipAddrTable(ipAddrTable);

    interp->result = s;
    return SCLI_OK;
}



void
scli_init_interface_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "interface", NULL, NULL },
	{ "show interface", "info",
	  "show information about the network interfaces",
	  cmd_interfaces },
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
