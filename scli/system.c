/* 
 * system.c -- scli system mode command implementation
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
    unsigned days, hours, minutes, seconds;
    guint32 secs = timeticks/100;
    
    days = secs / (24 * 60 * 60);
    hours = (secs / (60 * 60)) % 24;
    minutes = (secs / 60) % 60;
    seconds = secs % 60;

    g_snprintf(buffer, sizeof(buffer), "%d %s %02d:%02d:%02d",
	       days, (days == 1) ? "day" : "days",
	       hours, minutes, seconds);
    return buffer;
}



static char*
fmt_date_and_time(unsigned char *data, size_t len)
{
    static char buffer[80];

    if (len == 8) {
	g_snprintf(buffer, sizeof(buffer),
		   "%04u-%02u-%02u %02u:%02u:%02u",
		   (data[0] << 8) + data[1], data[2], data[3],
		   data[4], data[5], data[6]);
	return buffer;
    }

    if (len == 11) {
	g_snprintf(buffer, sizeof(buffer),
		   "%04u-%02u-%02u %02u:%02u:%02u %c%02u:%02u",
		   (data[0] << 8) + data[1], data[2], data[3],
		   data[4], data[5], data[6],
		   data[8], data[9], data[10]);
	return buffer;
    }
    
    return NULL;
}



static char*
fmt_kbytes(guint32 bytes)
{
    static char buffer[80];
    
    if (bytes > 9999999) {
	g_snprintf(buffer, sizeof(buffer), "%u GByte", bytes / 1024 / 1024);
    } else if (bytes > 9999) {
	g_snprintf(buffer, sizeof(buffer), "%u MByte", bytes / 1024);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%u KByte", bytes);
    }
    return buffer;
}



static void
print_string(char *label, gchar *string, gsize len)
{
    if (len < 0) {
	len = strlen(string);
    }
    if (string && len) {
	if (label) {
	    printf("%-10s %.*s\n", label, (int) len, string);
	} else {
	    printf("%.*s\n", (int) len, string);
	}
    }
}



static void
show_entity_summary(scli_interp_t *interp)
{
    entPhysicalEntry_t **entPhysicalEntry = NULL;
    int i;

    if (entity_mib_get_entPhysicalEntry(interp->peer, &entPhysicalEntry) == 0 && entPhysicalEntry) {
	for (i = 0; entPhysicalEntry[i]; i++) {
	    print_string(NULL,
			 entPhysicalEntry[i]->entPhysicalDescr,
			 entPhysicalEntry[i]->_entPhysicalDescrLength);
	    printf("\n");
	}
	entity_mib_free_entPhysicalEntry(entPhysicalEntry);
    }
}



static void
show_system_summary(scli_interp_t *interp)
{
    system_t *system = NULL;
    hrSystem_t *hrSystem = NULL;
    hrStorage_t *hrStorage = NULL;

    g_return_if_fail(interp);

    if (snmpv2_mib_get_system(interp->peer, &system) == 0 && system) {
	print_string(NULL,
		    system->sysDescr, system->_sysDescrLength);
	printf("\n");
	print_string("Name:",
		    system->sysName, system->_sysNameLength);
	printf("Address:   %s:%u\n", interp->peer->name, interp->peer->port);
	print_string("Contact:",
		    system->sysContact, system->_sysContactLength);
	print_string("Location:",
		    system->sysLocation, system->_sysLocationLength);
	if (system->sysUpTime) {
	    print_string("Agent:",
			fmt_time_ticks(*(system->sysUpTime)), -1);
	}
	if (system->sysObjectID) {
	    scli_vendor_t *vendor;
	    vendor = scli_get_vendor(system->sysObjectID,
				     system->_sysObjectIDLength);
	    if (vendor) {
		printf("Vendor:    ");
		if (vendor->name) {
		    printf("%s", vendor->name);
		    if (vendor->url) {
			printf(" <%s>", vendor->url);
		    }
		}
		printf("\n");
	    }
	}
	if (system->sysServices) {
	    guint32 services = *(system->sysServices);
	    printf("Services:  ");
	    if (services & 0x01) printf("physical ");
	    if (services & 0x02) printf("datalink ");
	    if (services & 0x04) printf("network ");
	    if (services & 0x08) printf("transport ");
	    if (services & 0x10) printf("session ");
	    if (services & 0x20) printf("representation ");
	    if (services & 0x40) printf("application ");
	    printf("\n");
	}
	snmpv2_mib_free_system(system);
    }

    if (host_resources_mib_get_hrSystem(interp->peer, &hrSystem) == 0 && hrSystem) {
	if (hrSystem->hrSystemUptime) {
	    print_string("Uptime:",
			fmt_time_ticks(*(hrSystem->hrSystemUptime)), -1);
	}
	if (hrSystem->hrSystemDate && hrSystem->_hrSystemDateLength) {
	    char *date = fmt_date_and_time(hrSystem->hrSystemDate,
					   hrSystem->_hrSystemDateLength);
	    if (date) {
		print_string("Date:", date, -1);
	    }
	}
	if (hrSystem->hrSystemNumUsers) {
	    printf("Users:     %u\n",
		   *(hrSystem->hrSystemNumUsers));
	}
	if (hrSystem->hrSystemProcesses) {
	    printf("Processes: %u\n",
		   *(hrSystem->hrSystemProcesses));
	}
	host_resources_mib_free_hrSystem(hrSystem);
    }

    if (host_resources_mib_get_hrStorage(interp->peer, &hrStorage) == 0 && hrStorage) {
	if (hrStorage->hrMemorySize) {
	    print_string("Memory:", fmt_kbytes(*(hrStorage->hrMemorySize)), -1);
	}
	host_resources_mib_free_hrStorage(hrStorage);
    }
}



static int
cmd_entities(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc == 1) {
	show_entity_summary(interp);
    }
    
    return SCLI_OK;
}



static int
cmd_show(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 1) {
	printf("wrong # args: should be \"show system\"\n");
	return SCLI_ERROR;
    }
    
    show_system_summary(interp);

    return SCLI_OK;
}



void
scli_init_system_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "system",
	  "display system information", cmd_show },
	{ "show system", "entities",
	  "display system entities", cmd_entities },
	{ NULL, NULL, NULL, NULL }
    };
    
    static scli_mode_t system_mode = {
	"system",
	"scli mode to display and configure system parameters",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &system_mode);
}
