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

#include "scli.h"

#include "host-resources-mib.h"
#include "host-resources-types.h"
#include "snmpv2-mib.h"
#include "if-mib.h"
#include "bridge-mib.h"
#include "disman-script-mib.h"

#include <ctype.h>


static guint32 const oid_other[]
    = { HOST_RESOURCES_TYPES_HRSTORAGEOTHER };
static guint32 const oid_ram[]
    = { HOST_RESOURCES_TYPES_HRSTORAGERAM };
static guint32 const oid_virtual_memory[]
    = { HOST_RESOURCES_TYPES_HRSTORAGEVIRTUALMEMORY };
static guint32 const oid_fixed_disk[]
    = { HOST_RESOURCES_TYPES_HRSTORAGEFIXEDDISK };
static guint32 const oid_removable_disk[]
    = { HOST_RESOURCES_TYPES_HRSTORAGEREMOVABLEDISK };
static guint32 const oid_floppy_disk[]
    = { HOST_RESOURCES_TYPES_HRSTORAGEFLOPPYDISK };
static guint32 const oid_compact_disk[]
    = { HOST_RESOURCES_TYPES_HRSTORAGECOMPACTDISC };
static guint32 const oid_ram_disk[]
    = { HOST_RESOURCES_TYPES_HRSTORAGERAMDISK };
static guint32 const oid_flash_memory[]
    = { HOST_RESOURCES_TYPES_HRSTORAGEFLASHMEMORY };
static guint32 const oid_network_disk[]
    = { HOST_RESOURCES_TYPES_HRSTORAGENETWORKDISK };

static GSnmpIdentity const storage_types[] = {
    { oid_ram,
      sizeof(oid_ram)/sizeof(guint32),
      "ram" },
    { oid_virtual_memory,
      sizeof(oid_virtual_memory)/sizeof(guint32),
      "virtual memory" },
    { oid_fixed_disk,
      sizeof(oid_fixed_disk)/sizeof(guint32),
      "fixed disk" },
    { oid_removable_disk,
      sizeof(oid_removable_disk)/sizeof(guint32),
      "removable disk" },
    { oid_floppy_disk,
      sizeof(oid_floppy_disk)/sizeof(guint32),
      "floppy disk" },
    { oid_compact_disk,
      sizeof(oid_compact_disk)/sizeof(guint32),
      "compact disk" },
    { oid_ram_disk,
      sizeof(oid_ram_disk)/sizeof(guint32),
      "ram disk" },
    { oid_flash_memory,
      sizeof(oid_flash_memory)/sizeof(guint32),
      "flash memory" },
    { oid_network_disk,
      sizeof(oid_network_disk)/sizeof(guint32),
      "network disk" },
    { NULL, 0, NULL }
};



static void
strip_white(guchar *s, gsize *len)
{
    while (*len && isspace(s[(*len)-1])) {
	(*len)--;
    }
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
xml_system_device(xmlNodePtr root,
		  host_resources_mib_hrDeviceEntry_t *hrDeviceEntry)
{
    xmlNodePtr tree;
    char const *type;
    
    g_return_if_fail(hrDeviceEntry);

    tree = xmlNewChild(root, NULL, "device", NULL);
    xml_set_prop(tree, "index", "%d", hrDeviceEntry->hrDeviceIndex);

    if (hrDeviceEntry->hrDeviceStatus) {
	(void) xmlNewChild(tree, NULL, "status",
			   fmt_enum(host_resources_mib_enums_hrDeviceStatus,
				    hrDeviceEntry->hrDeviceStatus));
    }

    if (hrDeviceEntry->hrDeviceType) {
	type = gsnmp_identity_get_label(host_resources_types_identities,
					hrDeviceEntry->hrDeviceType,
					hrDeviceEntry->_hrDeviceDescrLength);
	if (type) {
	    (void) xmlNewChild(tree, NULL, "type", type);
	}
    }
	
    if (hrDeviceEntry->hrDeviceDescr) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			     (int) hrDeviceEntry->_hrDeviceDescrLength,
			     hrDeviceEntry->hrDeviceDescr);
    }
}



static void
fmt_system_device(GString *s,
		  host_resources_mib_hrDeviceEntry_t *hrDeviceEntry)
{
    char const *status;
    char const *type;
    
    g_return_if_fail(hrDeviceEntry);

    g_string_sprintfa(s, "%5u ", hrDeviceEntry->hrDeviceIndex);

    status = fmt_enum(host_resources_mib_enums_hrDeviceStatus,
		      hrDeviceEntry->hrDeviceStatus);
    g_string_sprintfa(s, "%-8s", status ? status : "");

    if (hrDeviceEntry->hrDeviceType) {
	type = gsnmp_identity_get_label(host_resources_types_identities,
					hrDeviceEntry->hrDeviceType,
					hrDeviceEntry->_hrDeviceDescrLength);
	if (type) {
	    g_string_sprintfa(s, " (%s) ", type);
	}
    }
	
    if (hrDeviceEntry->hrDeviceDescr) {
	g_string_sprintfa(s, "%.*s\n",
			  (int) hrDeviceEntry->_hrDeviceDescrLength,
			  hrDeviceEntry->hrDeviceDescr);
    }
}



static int
show_system_devices(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrDeviceEntry_t **hrDeviceTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (host_resources_mib_get_hrDeviceTable(interp->peer, &hrDeviceTable)) {
	return SCLI_ERROR;
    }
    
    if (hrDeviceTable) {
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "INDEX STATUS  DESCRIPTION");
	}
	for (i = 0; hrDeviceTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_system_device(interp->xml_node, hrDeviceTable[i]);
	    } else {
		fmt_system_device(interp->result, hrDeviceTable[i]);
	    }
	}
    }

    if (hrDeviceTable) host_resources_mib_free_hrDeviceTable(hrDeviceTable);

    return SCLI_OK;
}



static void
xml_system_process(xmlNodePtr root,
		   host_resources_mib_hrSWRunEntry_t *hrSWRunEntry,
		   host_resources_mib_hrSWRunPerfEntry_t *hrSWRunPerfEntry)
{
    xmlNodePtr tree, node;

    tree = xmlNewChild(root, NULL, "process", NULL);
    xml_set_prop(tree, "index", "%d", hrSWRunEntry->hrSWRunIndex);
    
    if (hrSWRunEntry->hrSWRunStatus) {
	(void) xmlNewChild(tree, NULL, "status",
			   fmt_enum(host_resources_mib_enums_hrSWRunStatus,
				    hrSWRunEntry->hrSWRunStatus));
    }

    if (hrSWRunEntry->hrSWRunType) {
	(void) xmlNewChild(tree, NULL, "type",
			   fmt_enum(host_resources_mib_enums_hrSWRunType,
				    hrSWRunEntry->hrSWRunType));
    }

    if (hrSWRunPerfEntry && hrSWRunPerfEntry->hrSWRunPerfMem) {
	node = xml_new_child(tree, NULL, "memory", "%u",
			     *hrSWRunPerfEntry->hrSWRunPerfMem);
	xml_set_prop(node, "unit", "KByte");
    }
    if (hrSWRunPerfEntry && hrSWRunPerfEntry->hrSWRunPerfCPU) {
	node = xml_new_child(tree, NULL, "cpu", "%u",
			     *hrSWRunPerfEntry->hrSWRunPerfCPU/100);
	xml_set_prop(node, "unit", "secs");
    }

    if (hrSWRunEntry->hrSWRunPath
	&& hrSWRunEntry->_hrSWRunPathLength) {
	strip_white(hrSWRunEntry->hrSWRunPath,
		    &hrSWRunEntry->_hrSWRunPathLength);
	(void) xml_new_child(tree, NULL, "path", "%.*s",
			     (int) hrSWRunEntry->_hrSWRunPathLength,
			     hrSWRunEntry->hrSWRunPath);
    }
    if (hrSWRunEntry->hrSWRunParameters
	&& hrSWRunEntry->_hrSWRunParametersLength) {
	strip_white(hrSWRunEntry->hrSWRunParameters,
		    &hrSWRunEntry->_hrSWRunParametersLength);
	(void) xml_new_child(tree, NULL, "parameter", "%.*s",
			     (int) hrSWRunEntry->_hrSWRunParametersLength,
			     hrSWRunEntry->hrSWRunParameters);
    }
}



static void
fmt_system_process(GString *s,
		    host_resources_mib_hrSWRunEntry_t *hrSWRunEntry,
		    host_resources_mib_hrSWRunPerfEntry_t *hrSWRunPerfEntry)
{
    g_string_sprintfa(s, "%5d ", hrSWRunEntry->hrSWRunIndex);
    fmt_run_state_and_type(s,
			   hrSWRunEntry->hrSWRunStatus,
			   hrSWRunEntry->hrSWRunType);
    if (hrSWRunPerfEntry
	&& hrSWRunPerfEntry->hrSWRunPerfMem) {
	fmt_x_kbytes(s, *(hrSWRunPerfEntry->hrSWRunPerfMem));
    } else {
	g_string_sprintfa(s, " %5s", "-----");
    }
    if (hrSWRunPerfEntry
	&& hrSWRunPerfEntry->hrSWRunPerfCPU) {
	g_string_sprintfa(s, " %s",
		  fmt_seconds(*(hrSWRunPerfEntry->hrSWRunPerfCPU)/100));
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
show_system_processes(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrSWRunEntry_t **hrSWRunTable = NULL;
    host_resources_mib_hrSWRunPerfEntry_t **hrSWRunPerfTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (host_resources_mib_get_hrSWRunTable(interp->peer, &hrSWRunTable)) {
	return SCLI_ERROR;
    }
    (void) host_resources_mib_get_hrSWRunPerfTable(interp->peer,
						   &hrSWRunPerfTable);

    if (hrSWRunTable) {
	if (! scli_interp_xml(interp)) {
	    g_string_append(interp->header,
			    "  PID S T MEMORY     TIME COMMAND");
	}
	for (i = 0; hrSWRunTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_system_process(interp->xml_node, hrSWRunTable[i],
			   hrSWRunPerfTable ? hrSWRunPerfTable[i] : NULL);
	    } else {
		fmt_system_process(interp->result, hrSWRunTable[i],
			    hrSWRunPerfTable ? hrSWRunPerfTable[i] : NULL);
	    }
	}
    }
	
    if (hrSWRunTable)
	host_resources_mib_free_hrSWRunTable(hrSWRunTable);
    if (hrSWRunPerfTable)
	host_resources_mib_free_hrSWRunPerfTable(hrSWRunPerfTable);
    
    return SCLI_OK;
}



static void
xml_system_mount(xmlNodePtr root,
		 host_resources_mib_hrFSEntry_t *hrFSEntry)
{
    const char *e;
    xmlNodePtr tree;
    
    g_return_if_fail(hrFSEntry);

    tree = xmlNewChild(root, NULL, "filesystem", NULL);
    xml_set_prop(tree, "index", "%d", hrFSEntry->hrFSIndex);

    if (hrFSEntry->hrFSMountPoint
	&& hrFSEntry->_hrFSMountPointLength) {
	(void) xml_new_child(tree, NULL, "local", "%.*s", 
			     (int) hrFSEntry->_hrFSMountPointLength,
			     hrFSEntry->hrFSMountPoint);
    }

    if (hrFSEntry->hrFSRemoteMountPoint
	&& hrFSEntry->_hrFSRemoteMountPointLength) {
	(void) xml_new_child(tree, NULL, "remote", "%.*s", 
			     (int) hrFSEntry->_hrFSRemoteMountPointLength,
			     hrFSEntry->hrFSRemoteMountPoint);
    }

    e = fmt_enum(host_resources_mib_enums_hrFSAccess,
		 hrFSEntry->hrFSAccess);
    if (e) {
	(void) xml_new_child(tree, NULL, "access", "%s", e);
    }

    if (hrFSEntry->hrFSBootable && *(hrFSEntry->hrFSBootable) == 1) {
	(void) xmlNewChild(tree, NULL, "bootable", NULL);
    }
}



static void
fmt_system_mount(GString *s,
		 host_resources_mib_hrFSEntry_t *hrFSEntry,
		 int loc_len, int rem_len)
{
    const char *e;
    
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

    e = fmt_enum(host_resources_mib_enums_hrFSAccess,
		 hrFSEntry->hrFSAccess);
    g_string_sprintfa(s, "%s", e ? e : "");

    if (hrFSEntry->hrFSBootable
	&& *(hrFSEntry->hrFSBootable) == 1) {
	g_string_append(s, ", bootable");
    }

    g_string_append(s, "\n");
}



static int
show_system_mounts(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrFSEntry_t **hrFSTable = NULL;
    int i, loc_len = 20, rem_len = 20;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

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
	g_string_sprintfa(interp->header, "%-*s%-*sACCESS",
			  loc_len, "LOCAL MOUNT POINT",
			  rem_len, "REMOTE MOUNT POINT");
	for (i = 0; hrFSTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_system_mount(interp->xml_node, hrFSTable[i]);
	    } else {
		fmt_system_mount(interp->result, hrFSTable[i],
				 loc_len, rem_len);
	    }
	}
    }

    if (hrFSTable) host_resources_mib_free_hrFSTable(hrFSTable);

    return SCLI_OK;
}



static void
fmt_system_storage(GString *s,
		   host_resources_mib_hrStorageEntry_t *hrStorageEntry,
		   int descr_width)
{
    gchar const *type = NULL;

    g_return_if_fail(hrStorageEntry);

    if (hrStorageEntry->hrStorageType) {
	type = gsnmp_identity_get_label(storage_types,
					hrStorageEntry->hrStorageType,
					hrStorageEntry->_hrStorageTypeLength);
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
show_system_storage(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrStorageEntry_t **hrStorageTable = NULL;
    int descr_width = 14;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

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
	g_string_sprintfa(interp->header,
			  "%-*s  SIZE [K]   USED [K]   FREE [K] USE%%",
			  descr_width, "STORAGE AREA");
	for (i = 0; hrStorageTable[i]; i++) {
	    fmt_system_storage(interp->result, hrStorageTable[i],
			       descr_width);
	}
    }

    if (hrStorageTable) host_resources_mib_free_hrStorageTable(hrStorageTable);

    return SCLI_OK;
}



static void
xml_system_info(xmlNodePtr root, scli_interp_t *interp,
		snmpv2_mib_system_t *system)
{
    if (system) {
	if (system->sysName && system->_sysNameLength) {
	    (void) xml_new_child(root, NULL, "name", "%.*s",
				 (int) system->_sysNameLength,
				 system->sysName);
	}
	if (interp->peer->name) {
	    (void) xml_new_child(root, NULL, "address", "%s:%d",
				 interp->peer->name,
				 interp->peer->port);
	}
	if (system->sysDescr && system->_sysDescrLength) {
	    (void) xml_new_child(root, NULL, "description", "%.*s",
				 (int) system->_sysDescrLength,
				 system->sysDescr);
	}
	if (system->sysContact && system->_sysContactLength) {
	    (void) xml_new_child(root, NULL, "contact", "%.*s",
				 (int) system->_sysContactLength,
				 system->sysContact);
	}
	if (system->sysLocation && system->_sysLocationLength) {
	    (void) xml_new_child(root, NULL, "location", "%.*s",
				 (int) system->_sysLocationLength,
				 system->sysLocation);
	}

	if (system->sysObjectID) {
	    scli_vendor_t *vendor;
	    vendor = scli_get_iana_vendor(system->sysObjectID,
					  system->_sysObjectIDLength);
	    if (vendor && vendor->name) {
		(void) xml_new_child(root, NULL, "vendor", "%s", vendor->name);
	    }
	}

	if (system->sysServices) {
	    char const *serv_names[] = {
		"physical", "datalink", "network", "transport", "session",
		"representation", "application", NULL
	    };
	    int i;

	    for (i = 0; serv_names[i]; i++) {
		if (*(system->sysServices) & (1 << i)) {
		    (void) xml_new_child(root, NULL, "service", "%s",
					 serv_names[i]);
		}
	    }
	}
    }
}



static void
fmt_system_info(GString *s, scli_interp_t *interp,
		snmpv2_mib_system_t *system)
{
    int i;
    int const indent = 18;

    if (system) {
	if (system->sysName) {
	    fmt_display_string(s, indent, "Name:",
			       (int) system->_sysNameLength,
			       system->sysName);
	}
	if (interp->peer->name) {
	    g_string_sprintfa(s, "%-*s ", indent, "Address:");
	    g_string_sprintfa(s, "%s:%d\n", interp->peer->name,
			      interp->peer->port);
	}
	if (system->sysDescr && system->_sysDescrLength) {
	    fmt_display_string(s, indent, "Description:",
			       (int) system->_sysDescrLength,
			       system->sysDescr);
	}
	if (system->sysContact) {
	    fmt_display_string(s, indent, "Contact:",
			       (int) system->_sysContactLength,
			       system->sysContact);
	}
	if (system->sysLocation) {
	    fmt_display_string(s, indent, "Location:",
			       (int) system->_sysLocationLength,
			       system->sysLocation);
	}
	if (system->sysObjectID) {
	    scli_vendor_t *vendor;
	    vendor = scli_get_iana_vendor(system->sysObjectID,
					  system->_sysObjectIDLength);
	    if (vendor && vendor->name) {
		g_string_sprintfa(s, "%-*s ", indent, "Vendor:");
		if (vendor->id) {
		    g_string_append(s, vendor->name);
		    if (vendor->url) {
			g_string_sprintfa(s, " <%s>\n", vendor->url);
		    }
		} else {
		    g_string_sprintfa(s, "unknown (%s)\n", vendor->name);
		}
	    }
	}
	if (system->sysServices) {
	    char const *serv_names[] = {
		"physical", "datalink", "network", "transport", "session",
		"representation", "application", NULL
	    };

	    g_string_sprintfa(s, "%-*s ", indent, "Services:");
	    for (i = 0; serv_names[i]; i++) {
		if (*(system->sysServices) & (1 << i)) {
		    g_string_sprintfa(s, "%s ", serv_names[i]);
		}
	    }
	    g_string_append_c(s, '\n');
	}
    }
}



static int
show_system_info(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;
    host_resources_mib_hrSystem_t *hrSystem = NULL;
    host_resources_mib_hrStorage_t *hrStorage = NULL;
    if_mib_interfaces_t *interfaces = NULL;
    bridge_mib_dot1dBase_t *dot1dBase = NULL;
    disman_script_mib_smLangEntry_t **smLangTable = NULL;
    GString *s;
    int i;
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (snmpv2_mib_get_system(interp->peer, &system)) {
	return SCLI_ERROR;
    }
    (void) host_resources_mib_get_hrSystem(interp->peer, &hrSystem);
    (void) host_resources_mib_get_hrStorage(interp->peer, &hrStorage);
    (void) if_mib_get_interfaces(interp->peer, &interfaces);
    (void) bridge_mib_get_dot1dBase(interp->peer, &dot1dBase);
    (void) disman_script_mib_get_smLangTable(interp->peer, &smLangTable);

    if (scli_interp_xml(interp)) {
	xml_system_info(interp->xml_node, interp, system);
    } else {
	fmt_system_info(interp->result, interp, system);
    }

    s = interp->result;
    if (hrSystem) {
	if (hrSystem->hrSystemDate && hrSystem->_hrSystemDateLength) {
	    g_string_sprintfa(s, "%-*s ", indent, "Current Time:");
	    g_string_append(s, fmt_date_and_time(hrSystem->hrSystemDate,
					 hrSystem->_hrSystemDateLength));
	    g_string_append_c(s, '\n');
	}
    }

    if (system) {
	if (system->sysUpTime) {
	    g_string_sprintfa(s, "%-*s ", indent, "Agent Boot Time:");
	    g_string_append(s, fmt_timeticks(*(system->sysUpTime)));
	    g_string_append_c(s, '\n');
	}
    }
    
    if (hrSystem) {
	if (hrSystem->hrSystemUptime) {
	    g_string_sprintfa(s, "%-*s ", indent, "System Boot Time:");
	    g_string_append(s, fmt_timeticks(*(hrSystem->hrSystemUptime)));
	    g_string_append_c(s, '\n');
	}
	if (hrSystem->hrSystemNumUsers) {
	    g_string_sprintfa(s, "%-*s %u", indent, "Users:", 
			      *(hrSystem->hrSystemNumUsers));
	    g_string_append_c(s, '\n');
	}
	if (hrSystem->hrSystemProcesses) {
	    g_string_sprintfa(s, "%-*s %u", indent, "Processes:",
			      *(hrSystem->hrSystemProcesses));
	    if (hrSystem->hrSystemMaxProcesses
		&& *(hrSystem->hrSystemMaxProcesses)) {
		g_string_sprintfa(s, " (%u maximum)",
				  *(hrSystem->hrSystemMaxProcesses));
	    }
	    g_string_append_c(s, '\n');
	}
    }

    if (hrStorage) {
	if (hrStorage->hrMemorySize) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Memory:",
			      fmt_kbytes(*(hrStorage->hrMemorySize)));
	}
    }

    if (interfaces) {
	if (interfaces->ifNumber) {
	    g_string_sprintfa(s, "%-*s %d\n", indent, "Interfaces:",
			      *(interfaces->ifNumber));
	}
    }

    if (dot1dBase) {
	if (dot1dBase->dot1dBaseNumPorts && *dot1dBase->dot1dBaseNumPorts) {
	    g_string_sprintfa(s, "%-*s %d ", indent, "Bridge Ports:",
			      *(dot1dBase->dot1dBaseNumPorts));
	    if (dot1dBase->dot1dBaseType) {
		xxx_enum(s, 20, bridge_mib_enums_dot1dBaseType,
			 dot1dBase->dot1dBaseType);
	    }
	    g_string_append_c(s, '\n');
	}
    }

    if (smLangTable) {
	for (i = 0; smLangTable[i]; i++) ;
	g_string_sprintfa(s, "%-*s %u\n", indent, "Script Languages:", i);
    }

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



static int
set_system_contact(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;
    int code;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX;
    }

    system = snmpv2_mib_new_system();
    system->sysContact = argv[1];
    system->_sysContactLength = strlen(system->sysContact);
    code = snmpv2_mib_set_system(interp->peer, system);
    snmpv2_mib_free_system(system);

    if (interp->peer->error_status) {
	scli_snmp_error(interp);
	g_string_append(interp->result, "\n");
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
set_system_name(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;
    int code;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX;
    }

    system = snmpv2_mib_new_system();
    system->sysName = argv[1];
    system->_sysNameLength = strlen(system->sysName);
    code = snmpv2_mib_set_system(interp->peer, system);
    snmpv2_mib_free_system(system);
    
    if (interp->peer->error_status) {
	scli_snmp_error(interp);
	g_string_append(interp->result, "\n");
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
set_system_location(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;
    int code;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX;
    }

    system = snmpv2_mib_new_system();
    system->sysLocation = argv[1];
    system->_sysLocationLength = strlen(system->sysLocation);
    code = snmpv2_mib_set_system(interp->peer, system);
    snmpv2_mib_free_system(system);

    if (interp->peer->error_status) {
	scli_snmp_error(interp);
	g_string_append(interp->result, "\n");
	return SCLI_ERROR;
    }

    return SCLI_OK;
}


#ifdef MEM_DEBUG
static int
cmd_xxx(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_interfaces_t *interfaces = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    int i, n;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX;
    }
    n = atoi(argv[1]);

    for (i = 0; i < n; i++) {
	(void) getuid();
#if 1
	if (if_mib_get_interfaces(interp->peer, &interfaces)) {
	    return SCLI_ERROR;
	}
#endif
#if 0
	if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	    return SCLI_ERROR;
	}
#endif
	if (interfaces) if_mib_free_interfaces(interfaces);
	if (ifTable) if_mib_free_ifTable(ifTable);
    }
    
    
    return SCLI_OK;
}
#endif


void
scli_init_system_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "set system contact", "<contact>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "The set system contact command configures the system's contact\n"
	  "information. The <contact> string should include information\n"
	  "on how to contact a person who is responsible for this system.",
	  set_system_contact },

	{ "set system name", "<name>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "The set system name command configures the systems's name. By\n"
	  "convention, this is the system's fully-qualified domain name.",
	  set_system_name },

	{ "set system location", "<location>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "The set system location command configures the system's physical\n"
	  "location.",
	  set_system_location },

	{ "show system info", NULL,
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "The show system info command shows general information about the\n"
	  "system.",
	  show_system_info },

	{ "show system devices", NULL,
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "list of system devices",
	  show_system_devices },

	{ "show system storage", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "storage areas attached to the system",
	  show_system_storage },

	{ "show system mounts", NULL,
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "file systems mounted on the system",
	  show_system_mounts },

	{ "show system processes", NULL,
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "processes running on the system",
	  show_system_processes },

	{ "monitor system storage", NULL,
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  "storage areas attached to the system",
	  show_system_storage },

	{ "monitor system processes", NULL,
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  "processes running on the system",
	  show_system_processes },

#ifdef MEM_DEBUG
	{ "xxx", "<repetitions>",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "xxx",
	  cmd_xxx },
#endif

	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t system_mode = {
	"system",
	"The system scli mode is primarily based on the SNMPv2-MIB as\n"
	"published in RFC 1907 and the HOST-RESOURCES-MIB as publisched\n"
	"in RFC 2790. It can be used to browse and configure system\n"
	"parameters and characteristics.",
	cmds
    };
    
    scli_register_mode(interp, &system_mode);
}
