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

#include "stools.h"
#include "scli.h"


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
    hrDeviceEntry_t **hrDeviceEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrDeviceEntry(interp->peer, &hrDeviceEntry)) {
	return SCLI_ERROR;
    }
    
    if (hrDeviceEntry) {
	for (i = 0; hrDeviceEntry[i]; i++) {
	    show_device(interp->result, hrDeviceEntry[i]);
	}
	host_resources_mib_free_hrDeviceEntry(hrDeviceEntry);
    }

    return SCLI_OK;
}



static int
cmd_processes(scli_interp_t *interp, int argc, char **argv)
{
    hrSWRunEntry_t **hrSWRunEntry = NULL;
    hrSWRunPerfEntry_t **hrSWRunPerfEntry = NULL;
    GString *s;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrSWRunEntry(interp->peer,
					    &hrSWRunEntry) == 0) {
	(void) host_resources_mib_get_hrSWRunPerfEntry(interp->peer,
						       &hrSWRunPerfEntry);
    }

    s = interp->result;
    if (hrSWRunEntry) {
	g_string_append(s, "  PID S T MEMORY    TIME COMMAND\n");
	for (i = 0; hrSWRunEntry[i]; i++) {
	    g_string_sprintfa(s, "%5d ", hrSWRunEntry[i]->hrSWRunIndex);
	    fmt_run_state_and_type(s,
				   hrSWRunEntry[i]->hrSWRunStatus,
				   hrSWRunEntry[i]->hrSWRunType);
	    if (hrSWRunPerfEntry && hrSWRunPerfEntry[i]
		&& hrSWRunPerfEntry[i]->hrSWRunPerfMem) {
		fmt_x_kbytes(s, *(hrSWRunPerfEntry[i]->hrSWRunPerfMem));
	    } else {
		g_string_sprintfa(s, " %5s", "-----");
	    }
	    if (hrSWRunPerfEntry && hrSWRunPerfEntry[i]
		&& hrSWRunPerfEntry[i]->hrSWRunPerfCPU) {
		g_string_append(s, " ");
		fmt_hsec32(s, *(hrSWRunPerfEntry[i]->hrSWRunPerfCPU));
	    } else {
		g_string_sprintfa(s, " %5s", "--:--");
	    }
	    if (hrSWRunEntry[i]->hrSWRunPath
		&& hrSWRunEntry[i]->_hrSWRunPathLength) {
		g_string_sprintfa(s, " %.*s",
			    (int) hrSWRunEntry[i]->_hrSWRunPathLength,
				  hrSWRunEntry[i]->hrSWRunPath);
	    }
	    if (hrSWRunEntry[i]->hrSWRunParameters
		&& hrSWRunEntry[i]->_hrSWRunParametersLength) {
		g_string_sprintfa(s, " %.*s",
			    (int) hrSWRunEntry[i]->_hrSWRunParametersLength,
				  hrSWRunEntry[i]->hrSWRunParameters);
	    }
	    g_string_append(s, "\n");
	}
    }
	
    if (hrSWRunEntry)
	host_resources_mib_free_hrSWRunEntry(hrSWRunEntry);
    if (hrSWRunPerfEntry)
	host_resources_mib_free_hrSWRunPerfEntry(hrSWRunPerfEntry);
    
    interp->result = s;
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
    hrFSEntry_t **hrFSEntry = NULL;
    int i, loc_len = 20, rem_len = 20;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrFSEntry(interp->peer, &hrFSEntry)) {
	return SCLI_ERROR;
    }

    if (hrFSEntry) {
	for (i = 0; hrFSEntry[i]; i++) {
	    if (hrFSEntry[i]->hrFSMountPoint) {
		loc_len = MAX(loc_len,
			      hrFSEntry[i]->_hrFSMountPointLength);
	    }
	    if (hrFSEntry[i]->hrFSRemoteMountPoint) {
		rem_len = MAX(rem_len,
			      hrFSEntry[i]->_hrFSRemoteMountPointLength);
	    }
	}
	loc_len++, rem_len++;
	g_string_sprintfa(interp->result, "%-*s%-*sAccess\n",
			  loc_len, "Mount Point",
			  rem_len, "Remote Mount Point");
	for (i = 0; hrFSEntry[i]; i++) {
	    show_mount(interp->result, hrFSEntry[i], loc_len, rem_len);
	}
	host_resources_mib_free_hrFSEntry(hrFSEntry);
    }

    return SCLI_OK;
}



static void
show_storage(GString *s, hrStorageEntry_t *hrStorageEntry)
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
	g_string_sprintfa(s, "%-20.*s",
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
    hrStorageEntry_t **hrStorageEntry = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (host_resources_mib_get_hrStorageEntry(interp->peer,
					      &hrStorageEntry)) {
	return SCLI_ERROR;
    }

    if (hrStorageEntry) {
	g_string_append(interp->result, "Storage Area          "
	       "Size [K]   Used [K]   Free [K] Use%\n");
	for (i = 0; hrStorageEntry[i]; i++) {
	    show_storage(interp->result, hrStorageEntry[i]);
	}
	host_resources_mib_free_hrStorageEntry(hrStorageEntry);
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
    smLangEntry_t **smLangEntry = NULL;
    GString *s;
    int i;
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    s = interp->result;
    if (snmpv2_mib_get_system(interp->peer, &system) == 0 && system) {
	if (system->sysDescr && system->_sysDescrLength) {
	    g_string_sprintfa(s, "%.*s\n",
			      (int) system->_sysDescrLength,
			      system->sysDescr);
	}
	if (system->sysName) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Name:");
	    g_string_sprintfa(s, "%.*s", (int) system->_sysNameLength,
			      system->sysName);
	}
	if (interp->peer->name) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Address:");
	    g_string_sprintfa(s, "%s:%d", interp->peer->name,
			      interp->peer->port);
	}
	if (system->sysContact) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Contact:");
	    g_string_sprintfa(s, "%.*s", (int) system->_sysContactLength,
			      system->sysContact);
	}
	if (system->sysLocation) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Location:");
	    g_string_sprintfa(s, "%.*s", (int) system->_sysLocationLength,
			      system->sysLocation);
	}
	if (system->sysObjectID) {
	    scli_vendor_t *vendor;
	    vendor = scli_get_vendor(system->sysObjectID,
				     system->_sysObjectIDLength);
	    if (vendor) {
		g_string_sprintfa(s, "\n%-*s ", indent, "Vendor:");
		if (vendor->name) {
		    g_string_append(s, vendor->name);
		    if (vendor->url) {
			g_string_sprintfa(s, " <%s>", vendor->url);
		    }
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
	if (system->sysUpTime) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Agent Boot Time:");
	    fmt_time_ticks(s, *(system->sysUpTime));
	}
	snmpv2_mib_free_system(system);
    }

    if (host_resources_mib_get_hrSystem(interp->peer, &hrSystem) == 0
	&& hrSystem) {
	if (hrSystem->hrSystemUptime) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "System Boot Time:");
	    fmt_time_ticks(s, *(hrSystem->hrSystemUptime));
	}
	if (hrSystem->hrSystemDate && hrSystem->_hrSystemDateLength) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Current Time:");
	    fmt_date_and_time(s, hrSystem->hrSystemDate,
			      hrSystem->_hrSystemDateLength);
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
	host_resources_mib_free_hrSystem(hrSystem);
    }

    if (host_resources_mib_get_hrStorage(interp->peer, &hrStorage) == 0
	&& hrStorage) {
	if (hrStorage->hrMemorySize) {
	    g_string_sprintfa(s, "\n%-*s ", indent, "Memory:");
	    fmt_kbytes(s, *(hrStorage->hrMemorySize));	
}
	host_resources_mib_free_hrStorage(hrStorage);
    }

    if (if_mib_get_interfaces(interp->peer, &interfaces) == 0
	&& interfaces) {
	if (interfaces->ifNumber) {
	    g_string_sprintfa(s, "\n%-*s %d", indent, "Interfaces:",
			      *(interfaces->ifNumber));
	}
	if_mib_free_interfaces(interfaces);
    }

    if (bridge_mib_get_dot1dBase(interp->peer, &dot1dBase) == 0
	&& dot1dBase) {
	if (dot1dBase->dot1dBaseNumPorts) {
	    g_string_sprintfa(s, "\n%-*s %d ", indent, "Bridge Ports:",
			      *(dot1dBase->dot1dBaseNumPorts));
	    if (dot1dBase->dot1dBaseType) {
		fmt_enum(s, 60, bridge_mib_enums_dot1dBaseType,
			 dot1dBase->dot1dBaseType);
	    }
	}
	bridge_mib_free_dot1dBase(dot1dBase);
    }

    if (disman_script_mib_get_smLangEntry(interp->peer, &smLangEntry) == 0
	&& smLangEntry) {
	for (i = 0; smLangEntry[i]; i++) ;
	g_string_sprintfa(s, "\n%-*s %u", indent, "Script Languages:", i);
	disman_script_mib_free_smLangEntry(smLangEntry);
    }

    g_string_append(s, "\n");
    interp->result = s;
    return SCLI_OK;
}



void
scli_init_system_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "system", NULL, NULL },
	{ "show system", "info",
	  "show system summary information",
	  cmd_system },
	{ "show system", "devices",
	  "show list of system devices",
	  cmd_devices },
	{ "show system", "storage",
	  "show storage areas attached to the system",
	  cmd_storage },
	{ "show system", "mounts",
	  "show file systems mounted on the system",
	  cmd_mounts },
	{ "show system", "processes",
	  "show processes running on the system",
	  cmd_processes },
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
