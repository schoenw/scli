/* 
 * interface.c -- scli interface mode command implementation
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


static char*
fmt_time_ticks(guint32 timeticks)
{
    static char buffer[80];
    time_t now;
    struct tm *tm;
    
    now = time(NULL);
    now -= timeticks/100;
    tm = gmtime(&now);

    g_snprintf(buffer, sizeof(buffer),
	       "%04d-%02d-%02d %02d:%02d:%02d %c%02d:%02d",
	       tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
	       tm->tm_hour, tm->tm_min, tm->tm_sec,
	       timezone < 0 ? '+' : '-',
	       (int) ABS(timezone) / 60 / 60, (int) (ABS(timezone) / 60) % 60);
    
    return buffer;
}



static char *
fmt_enum(stls_table_t *table, gint32 *number)
{
    static char buffer[20];
    char *s = "";

    if (number) {
        s = stls_table_get_value(table, *number);
	if (! s) {
	    g_snprintf(buffer, sizeof(buffer), "%d", *number);
	    s = buffer;
	}
    }
    return s;
}



static char*
fmt_string(guchar *s, gsize len)
{
    static char *d = NULL;

    if (s) {
	if (! d) {
	    d = g_malloc(len+1);
	} else {
	    d = g_realloc(d, len+1);
	}
	memcpy(d, s, len);
	d[len] = 0;
    } else {
	if (d) {
	    g_free(d);
	}
	d = strdup("?");
    }

    return d;
}


static char*
fmt_kmg(guint32 number)
{
    static char buffer[80];

    if (number > 999999999) {
	g_snprintf(buffer, sizeof(buffer), "%3ug", number / 1000000);
    } else if (number > 999999) {
	g_snprintf(buffer, sizeof(buffer), "%3um", number / 1000000);
    } else if (number > 9999) {
	g_snprintf(buffer, sizeof(buffer), "%3uk", number / 1000);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%4u", number);
    }
    return buffer;
}


static char*
fmt_gtp(guint32 number)
{
    static char buffer[80];

    if (number > 999999999) {
	g_snprintf(buffer, sizeof(buffer), "%3up", number / 1000000000);
    } else if (number > 999999) {
	g_snprintf(buffer, sizeof(buffer), "%3ut", number / 1000000);
    } else if (number > 999) {
	g_snprintf(buffer, sizeof(buffer), "%3ug", number / 1000);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%3um", number);
    }
    return buffer;
}


static int
cmd_show(scli_interp_t *interp, int argc, char **argv)
{
    ifEntry_t **ifEntry = NULL;
    ifXEntry_t **ifXEntry = NULL;
    system_t *system = NULL;
    int i, j;

    g_return_val_if_fail(interp, SCLI_ERROR);

    /*
     * TODO:
     *
     * - Show IPv4 addresses based on the IP-MIB::ipAddrTable.
     */

    if (if_mib_get_ifEntry(interp->peer, &ifEntry) == 0) {
	(void) if_mib_get_ifXEntry(interp->peer, &ifXEntry);
	(void) snmpv2_mib_get_system(interp->peer, &system);
    }

    if (ifEntry) {

	for (i = 0; ifEntry[i]; i++) {

	    if (ifEntry[i]->ifIndex) {
		printf("Index:       %20d ", *(ifEntry[i]->ifIndex));
	    } else {
		printf("Index:       %20s ", "");
	    }

	    if (ifXEntry && ifXEntry[i]
		&& ifXEntry[i]->ifName && ifXEntry[i]->_ifNameLength) {
		printf("Name:    %s\n",
		       fmt_string(ifXEntry[i]->ifName,
				  ifXEntry[i]->_ifNameLength));
	    } else if (ifEntry[i]->ifDescr && ifEntry[i]->_ifDescrLength
		&& ifEntry[i]->_ifDescrLength < 20) {
		printf("Name:    %.*s\n",
		       (int) ifEntry[i]->_ifDescrLength,
		       ifEntry[i]->ifDescr);
	    } else {
		printf("Name:    if#%-17d\n", i);
	    }

	    printf("OperStatus:  %-20s ",
		   fmt_enum(if_mib_enums_ifOperStatus,
			    ifEntry[i]->ifOperStatus));
	    if (ifEntry[i]->ifPhysAddress
		&& ifEntry[i]->_ifPhysAddressLength) {
		printf("Address: ");
		for (j = 0; j < ifEntry[i]->_ifPhysAddressLength; j++) {
		    printf("%s%02X", (j == 0) ? "" : ":",
			   ifEntry[i]->ifPhysAddress[j]);
		}
		printf("\n");
	    } else {
		printf("Address:\n");
	    }
	    
	    printf("AdminStatus: %-20s ",
		   fmt_enum(if_mib_enums_ifAdminStatus,
			    ifEntry[i]->ifAdminStatus));
	    printf("Type:    %s\n",
		   fmt_enum(if_mib_enums_ifType,
			    ifEntry[i]->ifType));
	    
	    printf("Traps:       %-20s ",
		   fmt_enum(if_mib_enums_ifLinkUpDownTrapEnable,
			    (ifXEntry && ifXEntry[i]) ?
			    ifXEntry[i]->ifLinkUpDownTrapEnable : NULL));
	    if (ifEntry[i]->ifMtu) {
		printf("MTU:     %d byte\n", *(ifEntry[i]->ifMtu));
	    } else {
		printf("MTU:     ? byte\n");
	    }
	    
	    printf("Connector:   %-20s ",
		   fmt_enum(if_mib_enums_ifConnectorPresent,
			    (ifXEntry && ifXEntry[i]) ?
			    ifXEntry[i]->ifConnectorPresent : NULL));
	    if (ifEntry[i]->ifSpeed) {
		if (*(ifEntry[i]->ifSpeed) == 0xffffffff
		    && ifXEntry && ifXEntry[i]->ifHighSpeed) {
		    printf("Speed:   %s bps\n",
			   fmt_gtp(*(ifXEntry[i]->ifHighSpeed)));
		} else {
		    printf("Speed:   %s bps\n",
			   fmt_kmg(*(ifEntry[i]->ifSpeed)));
		}
	    } else {
		printf("Speed:   ? bps\n");
	    }
	    printf("Promiscuous: %-20s ",
		   fmt_enum(if_mib_enums_ifPromiscuousMode,
			    (ifXEntry && ifXEntry[i]) ?
			    ifXEntry[i]->ifPromiscuousMode : NULL));
	    if (ifEntry[i]->ifLastChange && system && system->sysUpTime) {
		guint32 dsecs =
		    *(system->sysUpTime) - *(ifEntry[i]->ifLastChange);
		printf("Change:  %s\n", fmt_time_ticks(dsecs));
	    } else {
		printf("Change:\n");
	    }
	    	    
	    if (ifEntry[i]->ifDescr && ifEntry[i]->_ifDescrLength) {
		printf("Description: %.*s\n",
		       (int) ifEntry[i]->_ifDescrLength,
		       ifEntry[i]->ifDescr);
	    }

	    if (ifXEntry && ifXEntry[i]
		&& ifXEntry[i]->ifAlias && ifXEntry[i]->_ifAliasLength) {
		printf("Info:        %.*s\n",
		       (int) ifXEntry[i]->_ifAliasLength,
		       ifXEntry[i]->ifAlias);
	    }
	    
	    if (ifEntry[i+1]) {
		printf("\n");
	    }
	}
    }

    if (ifEntry) if_mib_free_ifEntry(ifEntry);
    if (ifXEntry) if_mib_free_ifXEntry(ifXEntry);
    if (system) snmpv2_mib_free_system(system);

    return SCLI_OK;
}



void
scli_init_interface_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "interface",
	  "display interface information", cmd_show },
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
