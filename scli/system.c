/* 
 * system.c -- scli system mode implementation
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

#include "host-resources-mib.h"
#include "snmpv2-mib.h"
#include "if-mib.h"
#include "bridge-mib.h"
#include "disman-script-mib.h"

#include <ctype.h>


static void
strip_white(guchar *s, gsize *len)
{
    while (*len && isspace(s[(*len)-1])) {
	(*len)--;
    }
}



static void
fmt_hsec32(GString *s, guint32 number)
{
    guint32 min, hour;

    min  = (number / 100 / 60) % 60;
    hour = (number / 100 / 60 / 60);

    g_string_sprintfa(s, "%4.02d:%02d", hour, min);
}



static void
fmt_run_state_and_type(GString *s, gint32 *state, gint32 *type)
{
    if (state) {
	switch (*state) {
	case 1:  g_string_append(s, "C "); break;
	case 2:  g_string_append(s, "R "); break;
	case 3:  g_string_append(s, "S "); break;
	case 4:  g_string_append(s, "Z "); break;
	default: g_string_append(s, "- "); break;
	}
    } else {
	g_string_append(s, "- ");
    }

    if (type) {
	switch (*type) {
	case 1:  g_string_append(s, "? "); break;
	case 2:  g_string_append(s, "O "); break;
	case 3:  g_string_append(s, "D "); break;
	case 4:  g_string_append(s, "A "); break;
	default: g_string_append(s, "- "); break;
	}
    } else {
	g_string_append(s, "- ");
    }
}



static void
fmt_x_kbytes(GString *s, guint32 bytes)
{
    if (bytes > 9999999) {
	g_string_sprintfa(s, "%5uG", bytes / 1024 / 1024);
    } else if (bytes > 9999) {
	g_string_sprintfa(s, "%5uM", bytes / 1024);
    } else {
	g_string_sprintfa(s, "%5uK", bytes);
    }
}



static void
show_device(GString *s, hrDeviceEntry_t *hrDeviceEntry)
{
    g_return_if_fail(hrDeviceEntry);

    g_string_sprintfa(s, "%5d: ", hrDeviceEntry->hrDeviceIndex);
    
    if (hrDeviceEntry->hrDeviceDescr) {
	g_string_sprintfa(s, "%.*s\n",
			  (int) hrDeviceEntry->_hrDeviceDescrLength,
			  hrDeviceEntry->hrDeviceDescr);
    }
}



static int
cmd_devices(scli_interp_t *interp, int argc, char **argv)
{
    hrDeviceEntry_t **hrDeviceTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrDeviceTable(interp->peer, &hrDeviceTable)) {
	return SCLI_ERROR;
    }
    
    if (hrDeviceTable) {
	for (i = 0; hrDeviceTable[i]; i++) {
	    show_device(interp->result, hrDeviceTable[i]);
	}
	host_resources_mib_free_hrDeviceTable(hrDeviceTable);
    }

    return SCLI_OK;
}



static void
show_process(GString *s, hrSWRunEntry_t *hrSWRunEntry,
	     hrSWRunPerfEntry_t *hrSWRunPerfEntry)
{
    g_string_sprintfa(s, "%5d ", hrSWRunEntry->hrSWRunIndex);
    fmt_run_state_and_type(s,
			   hrSWRunEntry->hrSWRunStatus,
			   hrSWRunEntry->hrSWRunType);
    if (hrSWRunPerfEntry && hrSWRunPerfEntry
	&& hrSWRunPerfEntry->hrSWRunPerfMem) {
	fmt_x_kbytes(s, *(hrSWRunPerfEntry->hrSWRunPerfMem));
    } else {
	g_string_sprintfa(s, " %5s", "-----");
    }
    if (hrSWRunPerfEntry && hrSWRunPerfEntry
	&& hrSWRunPerfEntry->hrSWRunPerfCPU) {
	g_string_append(s, " ");
	fmt_hsec32(s, *(hrSWRunPerfEntry->hrSWRunPerfCPU));
    } else {
	g_string_sprintfa(s, " %5s", "--:--");
    }
    if (hrSWRunEntry->hrSWRunPath
	&& hrSWRunEntry->_hrSWRunPathLength) {
	strip_white(hrSWRunEntry->hrSWRunPath,
		    &hrSWRunEntry->_hrSWRunPathLength);
	g_string_sprintfa(s, " %.*s",
			  (int) hrSWRunEntry->_hrSWRunPathLength,
			  hrSWRunEntry->hrSWRunPath);
    }
    if (hrSWRunEntry->hrSWRunParameters
	&& hrSWRunEntry->_hrSWRunParametersLength) {
	strip_white(hrSWRunEntry->hrSWRunParameters,
		    &hrSWRunEntry->_hrSWRunParametersLength);
	g_string_sprintfa(s, " %.*s",
			  (int) hrSWRunEntry->_hrSWRunParametersLength,
			  hrSWRunEntry->hrSWRunParameters);
    }
    g_string_append(s, "\n");
}



static int
cmd_processes(scli_interp_t *interp, int argc, char **argv)
{
    hrSWRunEntry_t **hrSWRunTable = NULL;
    hrSWRunPerfEntry_t **hrSWRunPerfTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrSWRunTable(interp->peer, &hrSWRunTable)) {
	return SCLI_ERROR;
    }
    (void) host_resources_mib_get_hrSWRunPerfTable(interp->peer,
						   &hrSWRunPerfTable);

    if (hrSWRunTable) {
	g_string_append(interp->result, "  PID S T MEMORY    TIME COMMAND\n");
	for (i = 0; hrSWRunTable[i]; i++) {
	    show_process(interp->result, hrSWRunTable[i],
			 hrSWRunPerfTable ? hrSWRunPerfTable[i] : NULL);
	}
    }
	
    if (hrSWRunTable)
	host_resources_mib_free_hrSWRunTable(hrSWRunTable);
    if (hrSWRunPerfTable)
	host_resources_mib_free_hrSWRunPerfTable(hrSWRunPerfTable);
    
    return SCLI_OK;
}



static void
show_mount(GString *s, hrFSEntry_t *hrFSEntry, int loc_len, int rem_len)
{
    g_return_if_fail(hrFSEntry);

    if (hrFSEntry->hrFSMountPoint) {
	g_string_sprintfa(s, "%-*.*s", loc_len,
			  (int) hrFSEntry->_hrFSMountPointLength,
			  hrFSEntry->hrFSMountPoint);
    } else {
	g_string_sprintfa(s, "%*s", loc_len, "");
    }
    if (hrFSEntry->hrFSRemoteMountPoint) {
	g_string_sprintfa(s, "%-*.*s", rem_len,
			  (int) hrFSEntry->_hrFSRemoteMountPointLength,
			  hrFSEntry->hrFSRemoteMountPoint);
    } else {
	g_string_sprintfa(s, "%*s", rem_len, "");
    }
    if (hrFSEntry->hrFSAccess) {
	fmt_enum(s, 0, host_resources_mib_enums_hrFSAccess,
		 hrFSEntry->hrFSAccess);
    }
    if (hrFSEntry->hrFSBootable
	&& *(hrFSEntry->hrFSBootable) == 1) {
	g_string_append(s, ", bootable");
    }
    g_string_append(s, "\n");
}



static int
cmd_mounts(scli_interp_t *interp, int argc, char **argv)
{
    hrFSEntry_t **hrFSTable = NULL;
    int i, loc_len = 20, rem_len = 20;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrFSTable(interp->peer, &hrFSTable)) {
	return SCLI_ERROR;
    }

    if (hrFSTable) {
	for (i = 0; hrFSTable[i]; i++) {
	    if (hrFSTable[i]->hrFSMountPoint) {
		loc_len = MAX(loc_len,
			      hrFSTable[i]->_hrFSMountPointLength);
	    }
	    if (hrFSTable[i]->hrFSRemoteMountPoint) {
		rem_len = MAX(rem_len,
			      hrFSTable[i]->_hrFSRemoteMountPointLength);
	    }
	}
	loc_len++, rem_len++;
	g_string_sprintfa(interp->result, "%-*s%-*sAccess\n",
			  loc_len, "Local Mount Point",
			  rem_len, "Remote Mount Point");
	for (i = 0; hrFSTable[i]; i++) {
	    show_mount(interp->result, hrFSTable[i], loc_len, rem_len);
	}
	host_resources_mib_free_hrFSTable(hrFSTable);
    }

    return SCLI_OK;
}



static void
show_storage(GString *s, hrStorageEntry_t *hrStorageEntry, int descr_width)
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
	g_string_sprintfa(s, "%-*.*s",
			  descr_width,
			  (int) MIN(25, hrStorageEntry->_hrStorageDescrLength),
			  hrStorageEntry->hrStorageDescr);
    } else {
	g_string_sprintfa(s, "%20s", "");
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

        g_string_sprintfa(s, "%10llu %10llu %10llu %3u",
	       storage_size, storage_used, storage_size - storage_used,
	       (guint32) (storage_size
			  ? storage_used * 100 / storage_size : 0));

	if (type) {
	    g_string_sprintfa(s, " (%s)", type);
	}
    }
    g_string_append(s, "\n");
}



static int
cmd_storage(scli_interp_t *interp, int argc, char **argv)
{
    hrStorageEntry_t **hrStorageTable = NULL;
    int descr_width = 14;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrStorageTable(interp->peer,
					      &hrStorageTable)) {
	return SCLI_ERROR;
    }

    if (hrStorageTable) {
	for (i = 0; hrStorageTable[i]; i++) {
	    if (hrStorageTable[i]->hrStorageDescr
		&& hrStorageTable[i]->_hrStorageDescrLength > descr_width) {
		descr_width = hrStorageTable[i]->_hrStorageDescrLength;
	    }
	}
	g_string_sprintfa(interp->result,
			  "%-*s  Size [K]   Used [K]   Free [K] Use%\n",
			  descr_width, "Storage Area");
	for (i = 0; hrStorageTable[i]; i++) {
	    show_storage(interp->result, hrStorageTable[i],
			 descr_width);
	}
	host_resources_mib_free_hrStorageTable(hrStorageTable);
    }

    return SCLI_OK;
}



static int
cmd_system(scli_interp_t *interp, int argc, char **argv)
{
    system_t *system = NULL;
    hrSystem_t *hrSystem = NULL;
    hrStorage_t *hrStorage = NULL;
    interfaces_t *interfaces = NULL;
    dot1dBase_t *dot1dBase = NULL;
    smLangEntry_t **smLangTable = NULL;
    GString *s;
    int i;
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmpv2_mib_get_system(interp->peer, &system)) {
	return SCLI_ERROR;
    }
    (void) host_resources_mib_get_hrSystem(interp->peer, &hrSystem);
    (void) host_resources_mib_get_hrStorage(interp->peer, &hrStorage);
    (void) if_mib_get_interfaces(interp->peer, &interfaces);
    (void) bridge_mib_get_dot1dBase(interp->peer, &dot1dBase);
    (void) disman_script_mib_get_smLangTable(interp->peer, &smLangTable);
    
    s = interp->result;
    if (system) {
	if (system->sysDescr && system->_sysDescrLength) {
	    g_string_sprintfa(s, "%.*s\n",
			      (int) system->_sysDescrLength,
			      system->sysDescr);
	}
	if (system->sysName) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Name:");
	    g_string_sprintfa(s, "%.*s",
			      (int) system->_sysNameLength,
			      system->sysName);
	}
	if (interp->peer->name) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Address:");
	    g_string_sprintfa(s, "%s:%d", interp->peer->name,
			      interp->peer->port);
	}
	if (system->sysContact) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Contact:");
	    g_string_sprintfa(s, "%.*s",
			      (int) system->_sysContactLength,
			      system->sysContact);
	}
	if (system->sysLocation) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Location:");
	    g_string_sprintfa(s, "%.*s",
			      (int) system->_sysLocationLength,
			      system->sysLocation);
	}
	if (system->sysObjectID) {
	    scli_vendor_t *vendor;
	    vendor = scli_get_iana_vendor(system->sysObjectID,
					  system->_sysObjectIDLength);
	    if (vendor && vendor->name) {
		g_string_sprintfa(s, "\n%-*s ", indent, "Vendor:");
		if (vendor->id) {
		    g_string_append(s, vendor->name);
		    if (vendor->url) {
			g_string_sprintfa(s, " <%s>", vendor->url);
		    }
		} else {
		    g_string_sprintfa(s, "unknown (%s)", vendor->name);
		}
	    }
	}
	if (system->sysServices) {
	    char const *serv_names[] = {
		"physical", "datalink", "network", "transport", "session",
		"representation", "application", NULL
	    };

	    g_string_sprintfa(s, "\n%-*s ", indent, "Services:");
	    for (i = 0; serv_names[i]; i++) {
		if (*(system->sysServices) & (1 << i)) {
		    g_string_sprintfa(s, "%s ", serv_names[i]);
		}
	    }
	}
    }

    if (hrSystem) {
	if (hrSystem->hrSystemDate && hrSystem->_hrSystemDateLength) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Current Time:");
	    fmt_date_and_time(s, hrSystem->hrSystemDate,
			      hrSystem->_hrSystemDateLength);
	}
    }

    if (system) {
	if (system->sysUpTime) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Agent Boot Time:");
	    fmt_time_ticks(s, *(system->sysUpTime));
	}
    }
    
    if (hrSystem) {
	if (hrSystem->hrSystemUptime) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "System Boot Time:");
	    fmt_time_ticks(s, *(hrSystem->hrSystemUptime));
	}
	if (hrSystem->hrSystemNumUsers) {
	    g_string_sprintfa(s, "\n%-*s %u", indent, "Users:", 
			      *(hrSystem->hrSystemNumUsers));
	}
	if (hrSystem->hrSystemProcesses) {
	    g_string_sprintfa(s, "\n%-*s %u", indent, "Processes:",
			      *(hrSystem->hrSystemProcesses));
	}
	if (hrSystem->hrSystemMaxProcesses
	    && *(hrSystem->hrSystemMaxProcesses)) {
	    g_string_sprintfa(s, " (%u maximum)",
			      *(hrSystem->hrSystemMaxProcesses));
	}
    }

    if (hrStorage) {
	if (hrStorage->hrMemorySize) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Memory:");
	    fmt_kbytes(s, *(hrStorage->hrMemorySize));	
	}
    }

    if (interfaces) {
	if (interfaces->ifNumber) {
	    g_string_sprintfa(s, "\n%-*s %d", indent, "Interfaces:",
			      *(interfaces->ifNumber));
	}
    }

    if (dot1dBase) {
	if (dot1dBase->dot1dBaseNumPorts && *dot1dBase->dot1dBaseNumPorts) {
	    g_string_sprintfa(s, "\n%-*s %d ", indent, "Bridge Ports:",
			      *(dot1dBase->dot1dBaseNumPorts));
	    if (dot1dBase->dot1dBaseType) {
		fmt_enum(s, 60, bridge_mib_enums_dot1dBaseType,
			 dot1dBase->dot1dBaseType);
           }
	}
    }

    if (smLangTable) {
	for (i = 0; smLangTable[i]; i++) ;
	g_string_sprintfa(s, "\n%-*s %u", indent, "Script Languages:", i);
    }

    g_string_append(s, "\n");

    if (system)
	snmpv2_mib_free_system(system);
    if (hrSystem)
	host_resources_mib_free_hrSystem(hrSystem);
    if (hrStorage)
	host_resources_mib_free_hrStorage(hrStorage);
    if (interfaces)
	if_mib_free_interfaces(interfaces);
    if (dot1dBase)
	bridge_mib_free_dot1dBase(dot1dBase);
    if (smLangTable)
	disman_script_mib_free_smLangTable(smLangTable);

    return SCLI_OK;
}



void
scli_init_system_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "system", 0, NULL, NULL },
	{ "show system", "info", SCLI_CMD_FLAG_NEED_PEER,
	  "system summary information",
	  cmd_system },
	{ "show system", "devices", SCLI_CMD_FLAG_NEED_PEER,
	  "list of system devices",
	  cmd_devices },
	{ "show system", "storage", SCLI_CMD_FLAG_NEED_PEER,
	  "storage areas attached to the system",
	  cmd_storage },
	{ "show system", "mounts", SCLI_CMD_FLAG_NEED_PEER,
	  "file systems mounted on the system",
	  cmd_mounts },
	{ "show system", "processes", SCLI_CMD_FLAG_NEED_PEER,
	  "processes running on the system",
	  cmd_processes },
	{ NULL, NULL, 0, NULL, NULL }
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
