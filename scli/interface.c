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
    ifEntry_t **ifEntry = NULL;
    ifXEntry_t **ifXEntry = NULL;
    system_t *system = NULL;
    ipAddrEntry_t **ipAddrEntry = NULL;
    GString *s;
    int i, j;
    int const width = 20;

    g_return_val_if_fail(interp, SCLI_ERROR);

    /*
     * TODO:
     *
     * - Show IPv4 addresses based on the IP-MIB::ipAddrTable.
     */

    if (if_mib_get_ifEntry(interp->peer, &ifEntry)) {
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXEntry(interp->peer, &ifXEntry);
    (void) snmpv2_mib_get_system(interp->peer, &system);
    (void) ip_mib_get_ipAddrEntry(interp->peer, &ipAddrEntry);

    s = interp->result;
    if (ifEntry) {

	for (i = 0; ifEntry[i]; i++) {

	    if (i) {
		g_string_append(s, "\n");
	    }

	    g_string_sprintfa(s, "Index:       %-*d", width,
			      ifEntry[i]->ifIndex);
	    if (ifXEntry && ifXEntry[i]
		&& ifXEntry[i]->ifName && ifXEntry[i]->_ifNameLength) {
		g_string_sprintfa(s, " Name:    %.*s\n",
			    (int) ifXEntry[i]->_ifNameLength,
				  ifXEntry[i]->ifName);
	    } else if (ifEntry[i]->ifDescr && ifEntry[i]->_ifDescrLength
		&& ifEntry[i]->_ifDescrLength < width) {
		g_string_sprintfa(s, " Name:    %.*s\n",
			    (int) ifEntry[i]->_ifDescrLength,
				  ifEntry[i]->ifDescr);
	    } else {
		g_string_sprintfa(s, " Name:    if#%-17d\n",
				  ifEntry[i]->ifIndex);
	    }

	    g_string_append(s, "OperStatus:  ");
	    fmt_enum(s, width, if_mib_enums_ifOperStatus,
		     ifEntry[i]->ifOperStatus);
	    if (ifEntry[i]->ifPhysAddress
		&& ifEntry[i]->_ifPhysAddressLength) {
		g_string_append(s, " Address: ");
		for (j = 0; j < ifEntry[i]->_ifPhysAddressLength; j++) {
		    g_string_sprintfa(s, "%s%02X",
				      (j == 0) ? "" : ":",
				      ifEntry[i]->ifPhysAddress[j]);
		}
		g_string_append(s, "\n");
	    } else {
		g_string_append(s, " Address:\n");
	    }

	    g_string_append(s, "AdminStatus: ");
	    fmt_enum(s, width, if_mib_enums_ifAdminStatus,
		     ifEntry[i]->ifAdminStatus);
	    g_string_append(s, " Type:    ");
	    fmt_enum(s, width, if_mib_enums_ifType,
		     ifEntry[i]->ifType);
	    g_string_append(s, "\n");

	    g_string_append(s, "Traps:       ");
	    fmt_enum(s, width, if_mib_enums_ifLinkUpDownTrapEnable,
		     (ifXEntry && ifXEntry[i]) ?
		     ifXEntry[i]->ifLinkUpDownTrapEnable : NULL);
	    if (ifEntry[i]->ifMtu) {
		g_string_sprintfa(s, " MTU:     %d byte\n",
				  *(ifEntry[i]->ifMtu));
	    } else {
		g_string_append(s, " MTU:\n");
	    }

	    g_string_append(s, "Connector:   ");
	    fmt_enum(s, width, if_mib_enums_ifConnectorPresent,
		     (ifXEntry && ifXEntry[i]) ?
		     ifXEntry[i]->ifConnectorPresent : NULL);
	    if (ifEntry[i]->ifSpeed) {
		if (*(ifEntry[i]->ifSpeed) == 0xffffffff
		    && ifXEntry && ifXEntry[i]->ifHighSpeed) {
		    g_string_sprintfa(s, " Speed:   %s bps\n",
				      fmt_gtp(*(ifXEntry[i]->ifHighSpeed)));
		} else {
		    g_string_sprintfa(s, " Speed:   %s bps\n",
				      fmt_kmg(*(ifEntry[i]->ifSpeed)));
		}
	    } else {
		g_string_append(s, " Speed:\n");
	    }
	    
	    g_string_append(s, "Promiscuous: ");
	    fmt_enum(s, width, if_mib_enums_ifPromiscuousMode,
		     (ifXEntry && ifXEntry[i]) ?
		     ifXEntry[i]->ifPromiscuousMode : NULL);
	    if (ifEntry[i]->ifLastChange && system && system->sysUpTime) {
		guint32 dsecs =
		    *(system->sysUpTime) - *(ifEntry[i]->ifLastChange);
		g_string_sprintfa(s, " Change:  ");
		fmt_time_ticks(s, dsecs);
		g_string_append(s, "\n");
	    } else {
		g_string_append(s, " Change:\n");
	    }
	    
	    for (j = 0; ipAddrEntry[j]; j++) {
		if (ipAddrEntry[j]->ipAdEntIfIndex
		    && (ifEntry[i]->ifIndex
			== *(ipAddrEntry[j]->ipAdEntIfIndex))) {
		    g_string_sprintfa(s, "IP Address:  %-*s", width,
				      fmt_ipv4_address(
					  ipAddrEntry[j]->ipAdEntAddr, 0));
		    g_string_sprintfa(s, " Host:    %s\n",
				      fmt_ipv4_address(
					  ipAddrEntry[j]->ipAdEntAddr, 1));
		}
	    }
	    	    
	    if (ifEntry[i]->ifDescr && ifEntry[i]->_ifDescrLength) {
		g_string_sprintfa(s, "Description: %.*s\n",
			    (int) ifEntry[i]->_ifDescrLength,
				  ifEntry[i]->ifDescr);
	    }

	    if (ifXEntry && ifXEntry[i]
		&& ifXEntry[i]->ifAlias && ifXEntry[i]->_ifAliasLength) {
		g_string_sprintfa(s, "Alias:       %.*s\n",
			    (int) ifXEntry[i]->_ifAliasLength,
				  ifXEntry[i]->ifAlias);
	    }
	}
    }

    if (ifEntry) if_mib_free_ifEntry(ifEntry);
    if (ifXEntry) if_mib_free_ifXEntry(ifXEntry);
    if (system) snmpv2_mib_free_system(system);
    if (ipAddrEntry) ip_mib_free_ipAddrEntry(ipAddrEntry);

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
