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
print_string(char *label, guchar *string, gsize len)
{
    if (len < 0) {
	len = strlen((char *) string);
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
stls_string_append_string(GString *s, gint width, guchar *str, gsize len)
{
    /* XXX add code here to make sure the characters are displayable */
     
    if (str && len) {
	g_string_sprintfa(s, width < 0 ? "%-*.*s" : "%*.*s",
			  ABS(width), (int) MIN(len, ABS(width)), str);
    } else {
	g_string_sprintfa(s, "%*s", ABS(width), "");
    }
}



static int
cmd_mounts(scli_interp_t *interp, int argc, char **argv)
{
    hrFSEntry_t **hrFSEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrFSEntry(interp->peer, &hrFSEntry)) {
	return SCLI_OK;
    }

    if (hrFSEntry) {
	GString *s;
	s = g_string_new("Mount Point              Remote Mount Point\n");
	for (i = 0; hrFSEntry[i]; i++) {
	    stls_string_append_string(s, -25,
			      hrFSEntry[i]->hrFSMountPoint,
			      hrFSEntry[i]->_hrFSMountPointLength);
	    stls_string_append_string(s, -50,
			      hrFSEntry[i]->hrFSRemoteMountPoint,
			      hrFSEntry[i]->_hrFSRemoteMountPointLength);
	    s = g_string_append(s, "\n");
	}
	puts(s->str);
	g_string_free(s, 1);
	host_resources_mib_free_hrFSEntry(hrFSEntry);
    }

    return SCLI_OK;
}



static void
storage(hrStorageEntry_t *hrStorageEntry)
{
    static guint32 const hrStorageTypes[] = {1, 3, 6, 1, 2, 1, 25, 2, 1};
    guint const idx = sizeof(hrStorageTypes)/sizeof(guint32);
    gchar *type = NULL;

    static stls_table_t const storage_types[] = {
	{ 2, "ram" },
	{ 3, "virtual memory" },
	{ 4, "fixed disk" },
	{ 5, "removable disk" },
	{ 6, "floppy disk" },
	{ 7, "compact disk" },
	{ 8, "ram disk" },
	{ 9, "flash memory" },
	{ 10, "network disk" },
	{ 0, NULL }
    };
    
    g_return_if_fail(hrStorageEntry);

    if (hrStorageEntry->hrStorageType
	&& hrStorageEntry->_hrStorageTypeLength == idx + 1
	&& memcmp(hrStorageEntry->hrStorageType,
		  hrStorageTypes, sizeof(hrStorageTypes)) == 0) {
	type = stls_table_get_value(storage_types,
				    hrStorageEntry->hrStorageType[idx]);
    }

    if (hrStorageEntry->hrStorageDescr
	&& hrStorageEntry->_hrStorageDescrLength) {
	printf("%-20.*s", (int) MIN(25, hrStorageEntry->_hrStorageDescrLength),
	       hrStorageEntry->hrStorageDescr);
    } else {
	printf("%20s", "");
    }

    if (hrStorageEntry->hrStorageAllocationUnits
	&& hrStorageEntry->hrStorageSize
	&& hrStorageEntry->hrStorageUsed) {
	
	guint64 storage_size = 0;
	guint64 storage_used = 0;
	guint32 const scale = 1024;
	
	storage_size = *(hrStorageEntry->hrStorageSize);
	storage_size *= *(hrStorageEntry->hrStorageAllocationUnits);
	storage_size /= scale;

    	storage_used = *(hrStorageEntry->hrStorageUsed);
	storage_used *= *(hrStorageEntry->hrStorageAllocationUnits);
	storage_used /= scale;

        printf("%10llu %10llu %10llu %3u%%",
	       storage_size, storage_used, storage_size - storage_used,
	       (guint32) (storage_size
			  ? storage_used / storage_size * 100 : 0));

	if (type) {
	    printf(" (%s)\n", type);
	} else {
	    printf("\n");
	}
    } else {
	printf("\n");
    }
}



static int
cmd_storage(scli_interp_t *interp, int argc, char **argv)
{
    hrStorageEntry_t **hrStorageEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrStorageEntry(interp->peer,
					      &hrStorageEntry)) {
	return SCLI_OK;
    }

    if (hrStorageEntry) {
	printf("Storage Area          "
	       "Size [K]   Used [K]   Free [K] Use%%\n");
	for (i = 0; hrStorageEntry[i]; i++) {
	    storage(hrStorageEntry[i]);
	}
	host_resources_mib_free_hrStorageEntry(hrStorageEntry);
    }

    return SCLI_OK;
}



static int
cmd_entities(scli_interp_t *interp, int argc, char **argv)
{
    entPhysicalEntry_t **entPhysicalEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (entity_mib_get_entPhysicalEntry(interp->peer, &entPhysicalEntry) == 0 && entPhysicalEntry) {
	for (i = 0; entPhysicalEntry[i]; i++) {
	    print_string(NULL,
			 entPhysicalEntry[i]->entPhysicalDescr,
			 entPhysicalEntry[i]->_entPhysicalDescrLength);
	    printf("\n");
	}
	entity_mib_free_entPhysicalEntry(entPhysicalEntry);
    }
    
    return SCLI_OK;
}



static int
cmd_show(scli_interp_t *interp, int argc, char **argv)
{
    system_t *system = NULL;
    hrSystem_t *hrSystem = NULL;
    hrStorage_t *hrStorage = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

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
			(guchar *) fmt_time_ticks(*(system->sysUpTime)), -1);
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
			(guchar *) fmt_time_ticks(*(hrSystem->hrSystemUptime)), -1);
	}
	if (hrSystem->hrSystemDate && hrSystem->_hrSystemDateLength) {
	    char *date = fmt_date_and_time(hrSystem->hrSystemDate,
					   hrSystem->_hrSystemDateLength);
	    if (date) {
		print_string("Date:", (guchar *) date, -1);
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
	    print_string("Memory:", (guchar *) fmt_kbytes(*(hrStorage->hrMemorySize)), -1);
	}
	host_resources_mib_free_hrStorage(hrStorage);
    }

    return SCLI_OK;
}



void
scli_init_system_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "system",
	  "show generic system information", cmd_show },
	{ "show system", "entities",
	  "show the entities that make up the system", cmd_entities },
	{ "show system", "storage",
	  "show storage areas attached to the system", cmd_storage },
	{ "show system", "mounts",
	  "show file systems mounted on the system", cmd_mounts },
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
