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


static GSnmpEnum const dot1dBaseType[] = {
    { BRIDGE_MIB_DOT1DBASETYPE_UNKNOWN,	"unknown" },
    { BRIDGE_MIB_DOT1DBASETYPE_TRANSPARENT_ONLY,	"transparent (TP)" },
    { BRIDGE_MIB_DOT1DBASETYPE_SOURCEROUTE_ONLY,	"source route (SR)" },
    { BRIDGE_MIB_DOT1DBASETYPE_SRT,	"source route transparent (SRT)" },
    { 0, NULL }
};



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


static guint32 const oid_fs_other[]
    = { HOST_RESOURCES_TYPES_HRFSOTHER };
static guint32 const oid_fs_unknown[]
    = { HOST_RESOURCES_TYPES_HRFSUNKNOWN };
static guint32 const oid_fs_bffs[]
    = { HOST_RESOURCES_TYPES_HRFSBERKELEYFFS };
static guint32 const oid_fs_sys5[]
    = { HOST_RESOURCES_TYPES_HRFSSYS5FS };
static guint32 const oid_fs_fat[]
    = { HOST_RESOURCES_TYPES_HRFSFAT };
static guint32 const oid_fs_hpfs[]
    = { HOST_RESOURCES_TYPES_HRFSHPFS };
static guint32 const oid_fs_hfs[]
    = { HOST_RESOURCES_TYPES_HRFSHFS };
static guint32 const oid_fs_mfs[]
    = { HOST_RESOURCES_TYPES_HRFSMFS };
static guint32 const oid_fs_ntfs[]
    = { HOST_RESOURCES_TYPES_HRFSNTFS };
static guint32 const oid_fs_vnode[]
    = { HOST_RESOURCES_TYPES_HRFSVNODE };
static guint32 const oid_fs_journal[]
    = { HOST_RESOURCES_TYPES_HRFSJOURNALED };
static guint32 const oid_fs_iso9660[]
    = { HOST_RESOURCES_TYPES_HRFSISO9660 };
static guint32 const oid_fs_rockridge[]
    = { HOST_RESOURCES_TYPES_HRFSROCKRIDGE };
static guint32 const oid_fs_nfs[]
    = { HOST_RESOURCES_TYPES_HRFSNFS };

static guint32 const oid_fs_netware[]
    = { HOST_RESOURCES_TYPES_HRFSNETWARE };
static guint32 const oid_fs_afs[]
    = { HOST_RESOURCES_TYPES_HRFSAFS };
static guint32 const oid_fs_dfs[]
    = { HOST_RESOURCES_TYPES_HRFSDFS };
static guint32 const oid_fs_apple[]
    = { HOST_RESOURCES_TYPES_HRFSAPPLESHARE };
static guint32 const oid_fs_rfs[]
    = { HOST_RESOURCES_TYPES_HRFSRFS };
static guint32 const oid_fs_dgcfs[]
    = { HOST_RESOURCES_TYPES_HRFSDGCFS };
static guint32 const oid_fs_bfs[]
    = { HOST_RESOURCES_TYPES_HRFSBFS };
static guint32 const oid_fs_fat32[]
    = { HOST_RESOURCES_TYPES_HRFSFAT32 };
static guint32 const oid_fs_ext2[]
    = { HOST_RESOURCES_TYPES_HRFSLINUXEXT2 };

static GSnmpIdentity const filesystem_types[] = {
    { oid_fs_other,
      sizeof(oid_fs_other)/sizeof(guint32),
      "other" },
    { oid_fs_unknown,
      sizeof(oid_fs_unknown)/sizeof(guint32),
      "unknown" },
    { oid_fs_bffs,
      sizeof(oid_fs_bffs)/sizeof(guint32),
      "bffs" },
    { oid_fs_sys5,
      sizeof(oid_fs_sys5)/sizeof(guint32),
      "sys5" },
    { oid_fs_fat,
      sizeof(oid_fs_fat)/sizeof(guint32),
      "fat" },
    { oid_fs_hpfs,
      sizeof(oid_fs_hpfs)/sizeof(guint32),
      "hpfs" },
    { oid_fs_hfs,
      sizeof(oid_fs_hfs)/sizeof(guint32),
      "hfs" },
    { oid_fs_mfs,
      sizeof(oid_fs_mfs)/sizeof(guint32),
      "mfs" },
    { oid_fs_ntfs,
      sizeof(oid_fs_ntfs)/sizeof(guint32),
      "ntfs" },
    { oid_fs_vnode,
      sizeof(oid_fs_vnode)/sizeof(guint32),
      "vnode" },
    { oid_fs_journal,
      sizeof(oid_fs_journal)/sizeof(guint32),
      "journal" },
    { oid_fs_iso9660,
      sizeof(oid_fs_iso9660)/sizeof(guint32),
      "iso9660" },
    { oid_fs_rockridge,
      sizeof(oid_fs_rockridge)/sizeof(guint32),
      "rockridge" },
    { oid_fs_nfs,
      sizeof(oid_fs_nfs)/sizeof(guint32),
      "nfs" },
    { oid_fs_netware,
      sizeof(oid_fs_netware)/sizeof(guint32),
      "netware" },
    { oid_fs_afs,
      sizeof(oid_fs_afs)/sizeof(guint32),
      "afs" },
    { oid_fs_dfs,
      sizeof(oid_fs_dfs)/sizeof(guint32),
      "dfs" },
    { oid_fs_apple,
      sizeof(oid_fs_apple)/sizeof(guint32),
      "apple" },
    { oid_fs_rfs,
      sizeof(oid_fs_rfs)/sizeof(guint32),
      "rfs" },
    { oid_fs_dgcfs,
      sizeof(oid_fs_dgcfs)/sizeof(guint32),
      "dgcfs" },
    { oid_fs_bfs,
      sizeof(oid_fs_bfs)/sizeof(guint32),
      "bfs" },
    { oid_fs_fat32,
      sizeof(oid_fs_fat32)/sizeof(guint32),
      "fat32" },
    { oid_fs_ext2,
      sizeof(oid_fs_ext2)/sizeof(guint32),
      "ext2" },
    { NULL, 0, NULL }
};


static GSnmpEnum const hrSWRunStatus[] = {
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_RUNNING,		"C" },
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_RUNNABLE,	"R" },
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_NOTRUNNABLE,	"S" },
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_INVALID,		"Z" },
    { 0, NULL }
};

static GSnmpEnum const hrSWInstalledType[] = {
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_UNKNOWN,		"?" },
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_OPERATINGSYSTEM,	"O" },
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_DEVICEDRIVER,	"D" },
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_APPLICATION,		"A" },
    { 0, NULL }
};

GSnmpEnum const hrFSAccess[] = {
    { HOST_RESOURCES_MIB_HRFSACCESS_READWRITE,	"rw" },
    { HOST_RESOURCES_MIB_HRFSACCESS_READONLY,	"ro" },
    { 0, NULL }
};



static void
strip_white(guchar *s, gsize *len)
{
    while (*len && isspace(s[(*len)-1])) {
	(*len)--;
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
fmt_kbytes(GString *s, guint32 bytes)
{
    if (bytes > 9999999) {
	g_string_sprintfa(s, "%uG", bytes / 1024 / 1024);
    } else if (bytes > 9999) {
	g_string_sprintfa(s, "%uM", bytes / 1024);
    } else {
	g_string_sprintfa(s, "%uK", bytes);
    }
}



static host_resources_mib_hrSWRunPerfEntry_t*
get_hrSWRunPerfEntry(host_resources_mib_hrSWRunPerfEntry_t **hrSWRunPerfTable,
		     gint32 hrSWRunIndex)
{
    int i;

    for (i = 0; hrSWRunPerfTable[i]; i++) {
	if (hrSWRunPerfTable[i]->hrSWRunIndex == hrSWRunIndex) {
	    return hrSWRunPerfTable[i];
	}
    }
    return NULL;
}



static void
xml_system_device(xmlNodePtr root,
		  host_resources_mib_hrDeviceEntry_t *hrDeviceEntry)
{
    xmlNodePtr tree;
    char const *type;
    
    tree = xmlNewChild(root, NULL, "device", NULL);
    xml_set_prop(tree, "index", "%d", hrDeviceEntry->hrDeviceIndex);

    if (hrDeviceEntry->hrDeviceStatus) {
	(void) xmlNewChild(tree, NULL, "status",
			   fmt_enum(host_resources_mib_enums_hrDeviceStatus,
				    hrDeviceEntry->hrDeviceStatus));
    }

    type = gsnmp_identity_get_label(host_resources_types_identities,
				    hrDeviceEntry->hrDeviceType,
				    hrDeviceEntry->_hrDeviceDescrLength);
    if (type) {
	(void) xmlNewChild(tree, NULL, "type", type);
    }
	
    if (hrDeviceEntry->hrDeviceDescr && hrDeviceEntry->_hrDeviceDescrLength) {
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
    
    g_string_sprintfa(s, "%5u ", hrDeviceEntry->hrDeviceIndex);

    status = fmt_enum(host_resources_mib_enums_hrDeviceStatus,
		      hrDeviceEntry->hrDeviceStatus);
    g_string_sprintfa(s, "%-8s", status ? status : "");

    type = gsnmp_identity_get_label(host_resources_types_identities,
				    hrDeviceEntry->hrDeviceType,
				    hrDeviceEntry->_hrDeviceDescrLength);
    g_string_sprintfa(s, "%8s", type ? type : "");
	
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
	return SCLI_SYNTAX_NUMARGS;
    }

    host_resources_mib_get_hrDeviceTable(interp->peer, &hrDeviceTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (hrDeviceTable) {
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "INDEX STATUS  TYPE    DESCRIPTION");
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
	xml_set_prop(node, "unit", "kilobyte");
    }
    if (hrSWRunPerfEntry && hrSWRunPerfEntry->hrSWRunPerfCPU) {
	node = xml_new_child(tree, NULL, "cpu", "%u",
			     *hrSWRunPerfEntry->hrSWRunPerfCPU/100);
	xml_set_prop(node, "unit", "seconds");
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
    const char *e;
    
    g_string_sprintfa(s, "%5d ", hrSWRunEntry->hrSWRunIndex);

    e = fmt_enum(hrSWRunStatus, hrSWRunEntry->hrSWRunStatus);
    g_string_sprintfa(s, "%s ", e ? e : " ");
    
    e = fmt_enum(hrSWInstalledType, hrSWRunEntry->hrSWRunType);
    g_string_sprintfa(s, "%s ", e ? e : " ");

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
	return SCLI_SYNTAX_NUMARGS;
    }

    host_resources_mib_get_hrSWRunTable(interp->peer, &hrSWRunTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (hrSWRunTable) {
	host_resources_mib_get_hrSWRunPerfTable(interp->peer,
						&hrSWRunPerfTable, 0);
	if (! scli_interp_xml(interp)) {
	    g_string_append(interp->header,
			    "  PID S T MEMORY     TIME COMMAND");
	}
	for (i = 0; hrSWRunTable[i]; i++) {
	    host_resources_mib_hrSWRunPerfEntry_t *hrSWRunPerfEntry;
	    hrSWRunPerfEntry = get_hrSWRunPerfEntry(hrSWRunPerfTable,
					    hrSWRunTable[i]->hrSWRunIndex);
	    if (scli_interp_xml(interp)) {
		xml_system_process(interp->xml_node, hrSWRunTable[i],
				   hrSWRunPerfEntry);
	    } else {
		fmt_system_process(interp->result, hrSWRunTable[i],
				   hrSWRunPerfEntry);
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
		 host_resources_mib_hrFSEntry_t *fsEntry)
{
    const char *e;
    const char *type;
    xmlNodePtr tree;
    
    tree = xmlNewChild(root, NULL, "filesystem", NULL);
    xml_set_prop(tree, "index", "%d", fsEntry->hrFSIndex);

    if (fsEntry->hrFSMountPoint
	&& fsEntry->_hrFSMountPointLength) {
	(void) xml_new_child(tree, NULL, "local", "%.*s", 
			     (int) fsEntry->_hrFSMountPointLength,
			     fsEntry->hrFSMountPoint);
    }

    if (fsEntry->hrFSRemoteMountPoint
	&& fsEntry->_hrFSRemoteMountPointLength) {
	(void) xml_new_child(tree, NULL, "remote", "%.*s", 
			     (int) fsEntry->_hrFSRemoteMountPointLength,
			     fsEntry->hrFSRemoteMountPoint);
    }

    type = gsnmp_identity_get_label(filesystem_types,
				    fsEntry->hrFSType,
				    fsEntry->_hrFSTypeLength);
    if (type) {
	(void) xml_new_child(tree, NULL, "type", "%s", type);
    }

    e = fmt_enum(host_resources_mib_enums_hrFSAccess,
		 fsEntry->hrFSAccess);
    if (e) {
	(void) xml_new_child(tree, NULL, "access", "%s", e);
    }

    if (fsEntry->hrFSBootable
	&& *(fsEntry->hrFSBootable) == HOST_RESOURCES_MIB_HRFSBOOTABLE_TRUE) {
	(void) xmlNewChild(tree, NULL, "boot", NULL);
    }
}



static void
fmt_system_mount(GString *s,
		 host_resources_mib_hrFSEntry_t *fsEntry,
		 int loc_len, int rem_len, int type_len)
{
    const char *e;
    const char *type;

    g_string_sprintfa(s, "%5d ", fsEntry->hrFSIndex);

    if (fsEntry->hrFSMountPoint) {
	g_string_sprintfa(s, "%-*.*s", loc_len,
			  (int) fsEntry->_hrFSMountPointLength,
			  fsEntry->hrFSMountPoint);
    } else {
	g_string_sprintfa(s, "%*s", loc_len, "");
    }
    if (fsEntry->hrFSRemoteMountPoint) {
	g_string_sprintfa(s, "%-*.*s", rem_len,
			  (int) fsEntry->_hrFSRemoteMountPointLength,
			  fsEntry->hrFSRemoteMountPoint);
    } else {
	g_string_sprintfa(s, "%*s", rem_len, "");
    }

    type = gsnmp_identity_get_label(filesystem_types,
				    fsEntry->hrFSType,
				    fsEntry->_hrFSTypeLength);
    g_string_sprintfa(s, "%-*s", type_len, type ? type : "");

    e = fmt_enum(hrFSAccess, fsEntry->hrFSAccess);
    g_string_sprintfa(s, "%s", e ? e : "");

    if (fsEntry->hrFSBootable
	&& *(fsEntry->hrFSBootable) == HOST_RESOURCES_MIB_HRFSBOOTABLE_TRUE) {
	g_string_append(s, ",boot");
    }

    g_string_append(s, "\n");
}



static int
show_system_mounts(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrFSEntry_t **hrFSTable = NULL;
    int i, loc_len = 8, rem_len = 8, type_len = 4;
    const char *type;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    host_resources_mib_get_hrFSTable(interp->peer, &hrFSTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
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
	    type = gsnmp_identity_get_label(filesystem_types,
					    hrFSTable[i]->hrFSType,
					    hrFSTable[i]->_hrFSTypeLength);
	    if (type) {
		type_len = MAX(type_len, strlen(type));
	    }
	}
	loc_len++, rem_len++, type_len++,
	g_string_sprintfa(interp->header, "INDEX %-*s%-*s%-*sOPTIONS",
			  loc_len, "LOCAL",
			  rem_len, "REMOTE",
			  type_len, "TYPE");
	for (i = 0; hrFSTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_system_mount(interp->xml_node, hrFSTable[i]);
	    } else {
		fmt_system_mount(interp->result, hrFSTable[i],
				 loc_len, rem_len, type_len);
	    }
	}
    }

    if (hrFSTable) host_resources_mib_free_hrFSTable(hrFSTable);

    return SCLI_OK;
}



static void
xml_system_storage(xmlNodePtr root,
		   host_resources_mib_hrStorageEntry_t *hrStorageEntry)
{
    xmlNodePtr node, tree;
    gchar const *type = NULL;

    tree = xmlNewChild(root, NULL, "area", NULL);
    xml_set_prop(tree, "index", "%d", hrStorageEntry->hrStorageIndex);
    
    if (hrStorageEntry->hrStorageDescr
	&& hrStorageEntry->_hrStorageDescrLength) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			     (int) hrStorageEntry->_hrStorageDescrLength,
			     hrStorageEntry->hrStorageDescr);
    }

    type = gsnmp_identity_get_label(storage_types,
				    hrStorageEntry->hrStorageType,
				    hrStorageEntry->_hrStorageTypeLength);
    if (type) {
	(void) xmlNewChild(tree, NULL, "type", type);
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

	node = xml_new_child(tree, NULL, "size", "%llu", storage_size);
	xml_set_prop(node, "unit", "kilobyte");

	node = xml_new_child(tree, NULL, "used", "%llu", storage_used);
	xml_set_prop(node, "unit", "kilobyte");
    }
}



static void
fmt_system_storage(GString *s,
		   host_resources_mib_hrStorageEntry_t *hrStorageEntry,
		   int descr_width, int type_width)
{
    gchar const *type = NULL;

    g_string_sprintfa(s, "%5d ", hrStorageEntry->hrStorageIndex);

    if (hrStorageEntry->hrStorageDescr
	&& hrStorageEntry->_hrStorageDescrLength) {
	g_string_sprintfa(s, "%-*.*s",
			  descr_width,
			  (int) MIN(25, hrStorageEntry->_hrStorageDescrLength),
			  hrStorageEntry->hrStorageDescr);
    } else {
	g_string_sprintfa(s, "%*s", descr_width, "");
    }

    type = gsnmp_identity_get_label(storage_types,
				    hrStorageEntry->hrStorageType,
				    hrStorageEntry->_hrStorageTypeLength);
    g_string_sprintfa(s, "%-*s", type_width, type ? type : "");

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

	fmt_x_kbytes(s, storage_size);
	fmt_x_kbytes(s, storage_used);
	fmt_x_kbytes(s, storage_size - storage_used);
	g_string_sprintfa(s, " %3u",
			  (guint32) (storage_size
				     ? storage_used * 100 / storage_size : 0));
    }
    g_string_append(s, "\n");
}



static int
show_system_storage(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrStorageEntry_t **hrStorageTable = NULL;
    int descr_width = 14, type_width = 4;
    const char *type;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    host_resources_mib_get_hrStorageTable(interp->peer,
					  &hrStorageTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (hrStorageTable) {
	for (i = 0; hrStorageTable[i]; i++) {
	    if (hrStorageTable[i]->hrStorageDescr
		&& hrStorageTable[i]->_hrStorageDescrLength > descr_width) {
		descr_width = hrStorageTable[i]->_hrStorageDescrLength;
	    }
	    type = gsnmp_identity_get_label(storage_types,
				    hrStorageTable[i]->hrStorageType,
				    hrStorageTable[i]->_hrStorageTypeLength);
	    if (type) {
		type_width = MAX(type_width, strlen(type));
	    }
	}
	descr_width++, type_width++;
	g_string_sprintfa(interp->header,
			  "INDEX %-*s%-*s  SIZE  USED  FREE USE%%",
			  descr_width, "DESCRIPTION",
			  type_width, "TYPE");
	for (i = 0; hrStorageTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_system_storage(interp->xml_node, hrStorageTable[i]);
	    } else {
		fmt_system_storage(interp->result, hrStorageTable[i],
				   descr_width, type_width);
	    }
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
	    if (vendor && vendor->url) {
		(void) xml_new_child(root, NULL, "url", "%s", vendor->url);
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
	    g_string_sprintfa(s, "%-*s", indent, "Address:");
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
		g_string_sprintfa(s, "%-*s", indent, "Vendor:");
		if (vendor->id) {
		    g_string_append(s, vendor->name);
		    if (vendor->url) {
			g_string_sprintfa(s, " <%s>", vendor->url);
		    }
		} else {
		    g_string_sprintfa(s, "unknown (%s)", vendor->name);
		}
		g_string_append_c(s, '\n');
	    }
	}
	if (system->sysServices) {
	    char const *serv_names[] = {
		"physical", "datalink", "network", "transport", "session",
		"representation", "application", NULL
	    };

	    g_string_sprintfa(s, "%-*s", indent, "Services:");
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
    const char *e;
    GString *s;
    int i;
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    snmpv2_mib_get_system(interp->peer, &system, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    host_resources_mib_get_hrSystem(interp->peer, &hrSystem, 0);
    host_resources_mib_get_hrStorage(interp->peer, &hrStorage, 0);
    if_mib_get_interfaces(interp->peer, &interfaces, 0);
    bridge_mib_get_dot1dBase(interp->peer, &dot1dBase, 0);
    disman_script_mib_get_smLangTable(interp->peer, &smLangTable,
				      DISMAN_SCRIPT_MIB_SMLANGDESCR);

    if (scli_interp_xml(interp)) {
	xml_system_info(interp->xml_node, interp, system);
    } else {
	fmt_system_info(interp->result, interp, system);
    }

    s = interp->result;
    if (hrSystem) {
	if (hrSystem->hrSystemDate && hrSystem->_hrSystemDateLength) {
	    g_string_sprintfa(s, "%-*s", indent, "Current Time:");
	    g_string_append(s, fmt_date_and_time(hrSystem->hrSystemDate,
					 hrSystem->_hrSystemDateLength));
	    g_string_append_c(s, '\n');
	}
    }

    if (system) {
	if (system->sysUpTime) {
	    g_string_sprintfa(s, "%-*s", indent, "Agent Boot Time:");
	    g_string_append(s, fmt_timeticks(*(system->sysUpTime)));
	    g_string_append_c(s, '\n');
	}
    }
    
    if (hrSystem) {
	if (hrSystem->hrSystemUptime) {
	    g_string_sprintfa(s, "%-*s", indent, "System Boot Time:");
	    g_string_append(s, fmt_timeticks(*(hrSystem->hrSystemUptime)));
	    g_string_append_c(s, '\n');
	}
	if (hrSystem->hrSystemInitialLoadDevice) {
	    host_resources_mib_hrDeviceEntry_t *dev;
	    host_resources_mib_get_hrDeviceEntry(interp->peer, &dev, *hrSystem->hrSystemInitialLoadDevice, 0);
	    if (dev->hrDeviceDescr) {
		g_string_sprintfa(s, "%-*s%.*s\n", indent, "System Boot Dev:",
				  (int) dev->_hrDeviceDescrLength,
				  dev->hrDeviceDescr);
	    }
	    host_resources_mib_free_hrDeviceEntry(dev);
	}
	if (hrSystem->hrSystemInitialLoadParameters) {
	    g_string_sprintfa(s, "%-*s%.*s\n", indent, "System Boot Args:",
		      (int) hrSystem->_hrSystemInitialLoadParametersLength,
			      hrSystem->hrSystemInitialLoadParameters);
	}
	if (hrSystem->hrSystemNumUsers) {
	    g_string_sprintfa(s, "%-*s%u", indent, "Users:", 
			      *(hrSystem->hrSystemNumUsers));
	    g_string_append_c(s, '\n');
	}
	if (hrSystem->hrSystemProcesses) {
	    g_string_sprintfa(s, "%-*s%u", indent, "Processes:",
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
	    g_string_sprintfa(s, "%-*s", indent, "Memory:");
	    fmt_kbytes(s, *(hrStorage->hrMemorySize));
	    g_string_append_c(s, '\n');
	}
    }

    if (interfaces) {
	if (interfaces->ifNumber) {
	    g_string_sprintfa(s, "%-*s%d\n", indent, "Interfaces:",
			      *(interfaces->ifNumber));
	}
    }

    if (dot1dBase) {
	if (dot1dBase->dot1dBaseNumPorts && *dot1dBase->dot1dBaseNumPorts) {
	    g_string_sprintfa(s, "%-*s%d\n", indent, "Bridge Ports:",
			      *(dot1dBase->dot1dBaseNumPorts));
	}
	if (dot1dBase->dot1dBaseType) {
	    e = fmt_enum(dot1dBaseType, dot1dBase->dot1dBaseType);
	    if (e) {
		g_string_sprintfa(s, "%-*s%s\n", indent, "Bridge Type:", e);
	    }
	}
    }

    if (smLangTable) {
	for (i = 0; smLangTable[i]; i++) ;
	g_string_sprintfa(s, "%-*s%u\n", indent, "Script Languages:", i);
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

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    system = snmpv2_mib_new_system();
    system->sysContact = argv[1];
    system->_sysContactLength = strlen(system->sysContact);
    snmpv2_mib_set_system(interp->peer, system, SNMPV2_MIB_SYSCONTACT);
    snmpv2_mib_free_system(system);

    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
set_system_name(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    system = snmpv2_mib_new_system();
    system->sysName = argv[1];
    system->_sysNameLength = strlen(system->sysName);
    snmpv2_mib_set_system(interp->peer, system, SNMPV2_MIB_SYSNAME);
    snmpv2_mib_free_system(system);
    
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
set_system_location(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    system = snmpv2_mib_new_system();
    system->sysLocation = argv[1];
    system->_sysLocationLength = strlen(system->sysLocation);
    snmpv2_mib_set_system(interp->peer, system, SNMPV2_MIB_SYSLOCATION);
    snmpv2_mib_free_system(system);

    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
dump_system(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    snmpv2_mib_get_system(interp->peer, &system, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (system) {
	if (system->sysName) {
	    g_string_sprintfa(interp->result,
			     "set system name \"%.*s\"\n",
			      (int) system->_sysNameLength,
			      system->sysName);
	}
	if (system->sysContact) {
	    g_string_sprintfa(interp->result,
			     "set system contact \"%.*s\"\n",
			      (int) system->_sysContactLength,
			      system->sysContact);
	}
	if (system->sysLocation) {
	    g_string_sprintfa(interp->result,
			     "set system location \"%.*s\"\n",
			      (int) system->_sysLocationLength,
			      system->sysLocation);
	}
    }

    if (system) snmpv2_mib_free_system(system);

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
	return SCLI_SYNTAX_NUMARGS;
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

	{ "set system contact", "<string>",
	  "The set system contact command configures the system's contact\n"
	  "information. The <string> argument should include information\n"
	  "on how to contact a person who is responsible for this system.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_system_contact },

	{ "set system name", "<string>",
	  "The set system name command configures the systems's name. By\n"
	  "convention, this is the system's fully-qualified domain name.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_system_name },

	{ "set system location", "<string>",
	  "The set system location command configures the system's physical\n"
	  "location.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_system_location },

	{ "show system info", NULL,
	  "The show system info command shows general information about the\n"
	  "system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "system info", NULL,
	  show_system_info },

	{ "show system devices", NULL,
	  "The show system devices command shows a list of system devices.\n"
	  "The command generates a table with the following columns:\n"
	  "\n"
	  "  INDEX       device number\n"
	  "  STATUS      current status of the device\n"
	  "  DESCRIPTION description of the device",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "system devices", NULL,
	  show_system_devices },

	{ "show system storage", NULL,
	  "The show system storage command displays information about the\n"
	  "logical areas attached in the system. The command generates a\n"
	  "table with the following columns:\n"
	  "\n"
	  "  INDEX       logical storage area number\n"
	  "  DESCRIPTION description of the storage area\n"
	  "  TYPE        logical storage area type\n"
	  "  SIZE        total size of the storage area\n"
	  "  USED        amount of storage in use\n"
	  "  FREE        amount of storage available\n"
	  "  USE%        used storage in percent",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "system storage", NULL,
	  show_system_storage },

	{ "show system mounts", NULL,
	  "The show system mounts command shows the list of filesystems\n"
	  "mounted on the system. The command generates a table with the\n"
	  "following columns:\n"
	  "\n"
	  "  INDEX   filesystem identification number\n"
	  "  LOCAL   local root path name of the filesystem\n"
	  "  REMOTE  remote server and root path name (if any)\n"
	  "  TYPE    filesytem type (if known)\n"
	  "  OPTIONS access mode (ro/rw) and boot flag",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "system mounts", NULL,
	  show_system_mounts },

	{ "show system processes", NULL,
	  "The show system processes command display information about the\n"
	  "processes currently running on the system. The command generates\n"
	  "a table with the following columns:\n"
	  "\n"
	  "  PID     process identification number\n"
	  "  S       status of the process (see below)\n"
	  "  T       type of the process (see below)\n"
	  "  MEMORY  memory used by the process\n"
	  "  TIME    CPU time used by the process\n"
	  "  COMMAND command executed by the process\n"
	  "\n"
	  "The process status values are C=running, R=runnable,\n"
	  "S=not runnable, and Z=invalid. The process types values are\n"
	  "?=unknown, O=operating system, D=device driver, and A=application.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "system processes", NULL,
	  show_system_processes },

	{ "monitor system storage", NULL,
	  "The monitor system storage command shows the same\n"
	  "information as the show system storage command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  show_system_storage },
#if 0
	{ "loop system storage", NULL,
	  "The monitor system storage command shows the same\n"
	  "information as the show system storage command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_LOOP | SCLI_CMD_FLAG_XML,
	  NULL, NULL,
	  show_system_storage },
#endif
	{ "monitor system processes", NULL,
	  "The monitor system processes command show the same\n"
	  "information as the show system processes command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  show_system_processes },

#ifdef MEM_DEBUG
	{ "xxx", "<repetitions>",
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_xxx },
#endif
	{ "dump system", NULL,
	  "The dump system command generates a sequence of scli commands\n"
	  "which can be used to restore the system configuration.\n",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  dump_system },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
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
