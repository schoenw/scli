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

#include "snmpv2-tc.h"
#include "host-resources-mib.h"
#include "host-resources-types.h"
#include "snmpv2-mib.h"
#include "if-mib.h"
#include "entity-mib.h"
#include "bridge-mib.h"
#include "disman-script-mib.h"
#include "rs-232-mib.h"

#include <ctype.h>



static GNetSnmpEnum const dot1dBaseType[] = {
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

static GNetSnmpIdentity const storage_types[] = {
    { oid_other,
      sizeof(oid_other)/sizeof(guint32),
      "other" },
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

static GNetSnmpIdentity const filesystem_types[] = {
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


static GNetSnmpEnum const hrSWRunStatus[] = {
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_RUNNING,		"C" },
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_RUNNABLE,	"R" },
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_NOTRUNNABLE,	"S" },
    { HOST_RESOURCES_MIB_HRSWRUNSTATUS_INVALID,		"Z" },
    { 0, NULL }
};

static GNetSnmpEnum const hrSWRunType[] = {
    { HOST_RESOURCES_MIB_HRSWRUNTYPE_UNKNOWN,		"?" },
    { HOST_RESOURCES_MIB_HRSWRUNTYPE_OPERATINGSYSTEM,	"O" },
    { HOST_RESOURCES_MIB_HRSWRUNTYPE_DEVICEDRIVER,	"D" },
    { HOST_RESOURCES_MIB_HRSWRUNTYPE_APPLICATION,	"A" },
    { 0, NULL }
};

static GNetSnmpEnum const hrSWInstalledType[] = {
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_UNKNOWN,		"?" },
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_OPERATINGSYSTEM,	"O" },
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_DEVICEDRIVER,	"D" },
    { HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_APPLICATION,		"A" },
    { 0, NULL }
};

static GNetSnmpEnum const hrFSAccess[] = {
    { HOST_RESOURCES_MIB_HRFSACCESS_READWRITE,	"rw" },
    { HOST_RESOURCES_MIB_HRFSACCESS_READONLY,	"ro" },
    { 0, NULL }
};



static void
strip_white(guchar *s, guint16 *len)
{
    while (*len && isspace(s[(*len)-1])) {
	(*len)--;
    }
}


static char*
get_command(host_resources_mib_hrSWRunEntry_t *hrSWRunEntry)
{
    char *s = NULL;
    
    strip_white(hrSWRunEntry->hrSWRunPath,
		&hrSWRunEntry->_hrSWRunPathLength);
    strip_white(hrSWRunEntry->hrSWRunName,
		&hrSWRunEntry->_hrSWRunNameLength);
    if (hrSWRunEntry->hrSWRunPath) {
	s = g_strdup_printf("%.*s",
			    (int) hrSWRunEntry->_hrSWRunPathLength,
			    hrSWRunEntry->hrSWRunPath);
    } else if (hrSWRunEntry->hrSWRunName) {
	s = g_strdup_printf("%.*s",
			    (int) hrSWRunEntry->_hrSWRunNameLength,
			    hrSWRunEntry->hrSWRunName);
    }
    return s;
}



static int
match_process(regex_t *regex_path,
	      host_resources_mib_hrSWRunEntry_t *hrSWRunEntry)
{
    int match = 0;
    char *s;
    
    if (! regex_path) {
	return 1;
    }

    s = get_command(hrSWRunEntry);
    if (s) {
	match = (regexec(regex_path, s, (size_t) 0, NULL, 0) == 0);
	g_free(s);
    }

    return match;
}



static int
match_software(regex_t *regex_path,
	       host_resources_mib_hrSWInstalledEntry_t *hrSWEntry)
{
    int status;
    
    if (! regex_path) {
	return 1;
    }

    /*
     * Does it really make sense to filter this way?
     */

    if (hrSWEntry->hrSWInstalledName) {
	char *s;
	s = g_strdup_printf("%.*s",
			    (int) hrSWEntry->_hrSWInstalledNameLength,
			    hrSWEntry->hrSWInstalledName);
	status = regexec(regex_path, s, (size_t) 0, NULL, 0);
	g_free(s);
	if (status == 0) {
	    return 1;
	}
    }

    return 0;
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
    char const *e;
    
    tree = xml_new_child(root, NULL, BAD_CAST("device"), NULL);
    xml_set_prop(tree, BAD_CAST("index"), "%d", hrDeviceEntry->hrDeviceIndex);

    if (hrDeviceEntry->hrDeviceStatus) {
	(void) xml_new_child(tree, NULL, BAD_CAST("status"), "%s",
			     fmt_enum(host_resources_mib_enums_hrDeviceStatus,
				      hrDeviceEntry->hrDeviceStatus));
    }

    e = fmt_identity(host_resources_types_identities,
		     hrDeviceEntry->hrDeviceType,
		     hrDeviceEntry->_hrDeviceDescrLength);
    if (e) {
	(void) xml_new_child(tree, NULL, BAD_CAST("type"), e);
    }
	
    if (hrDeviceEntry->hrDeviceDescr && hrDeviceEntry->_hrDeviceDescrLength) {
	(void) xml_new_child(tree, NULL, BAD_CAST("description"), "%.*s",
			     (int) hrDeviceEntry->_hrDeviceDescrLength,
			     hrDeviceEntry->hrDeviceDescr);
    }
}



static void
fmt_system_device(GString *s,
		  host_resources_mib_hrDeviceEntry_t *hrDeviceEntry,
		  int type_width)
{
    char const *e;
    
    g_string_sprintfa(s, "%5u ", hrDeviceEntry->hrDeviceIndex);

    e = fmt_enum(host_resources_mib_enums_hrDeviceStatus,
		 hrDeviceEntry->hrDeviceStatus);
    g_string_sprintfa(s, "%-8s", e ? e : "");

    e = fmt_identity(host_resources_types_identities,
		     hrDeviceEntry->hrDeviceType,
		     hrDeviceEntry->_hrDeviceDescrLength);
    g_string_sprintfa(s, "%*s ", type_width, e ? e : "");
	
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
    int type_width = 8;
    char const *type;
    int i;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    host_resources_mib_get_hrDeviceTable(interp->peer, &hrDeviceTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (hrDeviceTable) {
	if (! scli_interp_xml(interp)) {
	    for (i = 0; hrDeviceTable[i]; i++) {
		type = fmt_identity(host_resources_types_identities,
				    hrDeviceTable[i]->hrDeviceType,
				    hrDeviceTable[i]->_hrDeviceDescrLength);
		if (type) {
		    type_width = MAX(type_width, strlen(type));
		}
	    }
	    g_string_sprintfa(interp->header, "INDEX STATUS  %-*s DESCRIPTION",
			      type_width, "TYPE");
	}
	for (i = 0; hrDeviceTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_system_device(interp->xml_node, hrDeviceTable[i]);
	    } else {
		fmt_system_device(interp->result, hrDeviceTable[i],
				  type_width);
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
    char *c;

    tree = xml_new_child(root, NULL, BAD_CAST("process"), NULL);
    xml_set_prop(tree, BAD_CAST("index"), "%d", hrSWRunEntry->hrSWRunIndex);
    
    if (hrSWRunEntry->hrSWRunStatus) {
	(void) xml_new_child(tree, NULL, BAD_CAST("status"), "%s",
			     fmt_enum(host_resources_mib_enums_hrSWRunStatus,
				      hrSWRunEntry->hrSWRunStatus));
    }

    if (hrSWRunEntry->hrSWRunType) {
	(void) xml_new_child(tree, NULL, BAD_CAST("type"), "%s",
			     fmt_enum(host_resources_mib_enums_hrSWRunType,
				      hrSWRunEntry->hrSWRunType));
    }

    if (hrSWRunPerfEntry && hrSWRunPerfEntry->hrSWRunPerfMem) {
	node = xml_new_child(tree, NULL, BAD_CAST("memory"), "%llu",
			     (guint64)1024 * *hrSWRunPerfEntry->hrSWRunPerfMem);
	xml_set_prop(node, BAD_CAST("unit"), "bytes");
    }
    if (hrSWRunPerfEntry && hrSWRunPerfEntry->hrSWRunPerfCPU) {
	node = xml_new_child(tree, NULL, BAD_CAST("cpu"), "%u",
			     *hrSWRunPerfEntry->hrSWRunPerfCPU/100);
	xml_set_prop(node, BAD_CAST("unit"), "seconds");
    }

    c = get_command(hrSWRunEntry);
    if (c) {
	(void) xml_new_child(tree, NULL, BAD_CAST("path"), "%s", c);
	g_free(c);
    }
    if (hrSWRunEntry->hrSWRunParameters
	&& hrSWRunEntry->_hrSWRunParametersLength) {
	strip_white(hrSWRunEntry->hrSWRunParameters,
		    &hrSWRunEntry->_hrSWRunParametersLength);
	(void) xml_new_child(tree, NULL, BAD_CAST("parameter"), "%.*s",
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
    char *c;
    
    g_string_sprintfa(s, "%7d ", hrSWRunEntry->hrSWRunIndex);

    e = fmt_enum(hrSWRunStatus, hrSWRunEntry->hrSWRunStatus);
    g_string_sprintfa(s, "%s ", e ? e : " ");
    
    e = fmt_enum(hrSWRunType, hrSWRunEntry->hrSWRunType);
    g_string_sprintfa(s, "%s ", e ? e : " ");

    if (hrSWRunPerfEntry
	&& hrSWRunPerfEntry->hrSWRunPerfMem) {
	fmt_x_kbytes(s, (guint32) *(hrSWRunPerfEntry->hrSWRunPerfMem));
    } else {
	g_string_sprintfa(s, " -----");
    }
    if (hrSWRunPerfEntry
	&& hrSWRunPerfEntry->hrSWRunPerfCPU) {
	g_string_sprintfa(s, " %s",
		  fmt_seconds((guint32) *(hrSWRunPerfEntry->hrSWRunPerfCPU)/100));
    } else {
	g_string_sprintfa(s, "    -:--:--");
    }
    c = get_command(hrSWRunEntry);
    if (c) {
	g_string_sprintfa(s, " %s", c);
	g_free(c);
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
    regex_t _regex_path, *regex_path = NULL;
    int i;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_path = &_regex_path;
	if (regcomp(regex_path, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_path) regfree(regex_path);
	return SCLI_OK;
    }

    host_resources_mib_get_hrSWRunTable(interp->peer, &hrSWRunTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (hrSWRunTable) {
	host_resources_mib_get_hrSWRunPerfTable(interp->peer,
						&hrSWRunPerfTable, 0, NULL);
	if (! scli_interp_xml(interp)) {
	    g_string_append(interp->header,
			    "    PID S T MEMORY       TIME COMMAND");
	}
	for (i = 0; hrSWRunTable[i]; i++) {
	    if (match_process(regex_path, hrSWRunTable[i])) {
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
    }
	
    if (hrSWRunTable)
	host_resources_mib_free_hrSWRunTable(hrSWRunTable);
    if (hrSWRunPerfTable)
	host_resources_mib_free_hrSWRunPerfTable(hrSWRunPerfTable);

    if (regex_path) regfree(regex_path);
    
    return SCLI_OK;
}



static void
fmt_system_software(GString *s,
		    host_resources_mib_hrSWInstalledEntry_t *hrSWEntry)
{
    const char *e;

    g_string_sprintfa(s, "%7d ", hrSWEntry->hrSWInstalledIndex);

    e = fmt_enum(hrSWInstalledType, hrSWEntry->hrSWInstalledType);
    g_string_sprintfa(s, "%s ", e ? e : " ");

    g_string_sprintfa(s, "%19s", fmt_date_and_time(hrSWEntry->hrSWInstalledDate,
						   hrSWEntry->_hrSWInstalledDateLength));

    if (hrSWEntry->hrSWInstalledName) {
	strip_white(hrSWEntry->hrSWInstalledName,
		    &hrSWEntry->_hrSWInstalledNameLength);
        g_string_sprintfa(s, " %.*s",
			  (int) hrSWEntry->_hrSWInstalledNameLength,
			  hrSWEntry->hrSWInstalledName);
    }
    g_string_append(s, "\n");
}



static int
show_system_software(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrSWInstalledEntry_t **hrSWTable = NULL;
    regex_t _regex_path, *regex_path = NULL;
    int i;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_path = &_regex_path;
	if (regcomp(regex_path, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_path) regfree(regex_path);
	return SCLI_OK;
    }

    host_resources_mib_get_hrSWInstalledTable(interp->peer, &hrSWTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (hrSWTable) {
	if (! scli_interp_xml(interp)) {
	    g_string_append(interp->header,
			    "    SID T DATE                SOFTWARE");
	}
	for (i = 0; hrSWTable[i]; i++) {
	    if (match_software(regex_path, hrSWTable[i])) {
		if (scli_interp_xml(interp)) {
//		    xml_system_software(interp->xml_node, hrSWTable[i]);
		} else {
		    fmt_system_software(interp->result, hrSWTable[i]);
		}
	    }
	}
    }
	
    if (hrSWTable)
	host_resources_mib_free_hrSWInstalledTable(hrSWTable);

    if (regex_path) regfree(regex_path);
    
    return SCLI_OK;
}



static void
xml_system_mount(xmlNodePtr root,
		 host_resources_mib_hrFSEntry_t *fsEntry)
{
    const char *e;
    xmlNodePtr tree;
    
    tree = xml_new_child(root, NULL, BAD_CAST("filesystem"), NULL);
    xml_set_prop(tree, BAD_CAST("index"), "%d", fsEntry->hrFSIndex);

    if (fsEntry->hrFSMountPoint
	&& fsEntry->_hrFSMountPointLength) {
	(void) xml_new_child(tree, NULL, BAD_CAST("local"), "%.*s", 
			     (int) fsEntry->_hrFSMountPointLength,
			     fsEntry->hrFSMountPoint);
    }

    if (fsEntry->hrFSRemoteMountPoint
	&& fsEntry->_hrFSRemoteMountPointLength) {
	(void) xml_new_child(tree, NULL, BAD_CAST("remote"), "%.*s", 
			     (int) fsEntry->_hrFSRemoteMountPointLength,
			     fsEntry->hrFSRemoteMountPoint);
    }

    e = fmt_identity(filesystem_types,
		     fsEntry->hrFSType, fsEntry->_hrFSTypeLength);
    if (e) {
	(void) xml_new_child(tree, NULL, BAD_CAST("type"), "%s", e);
    }

    e = fmt_enum(host_resources_mib_enums_hrFSAccess,
		 fsEntry->hrFSAccess);
    if (e) {
	(void) xml_new_child(tree, NULL, BAD_CAST("access"), "%s", e);
    }

    if (fsEntry->hrFSBootable
	&& *(fsEntry->hrFSBootable) == SNMPV2_TC_TRUTHVALUE_TRUE) {
	(void) xml_new_child(tree, NULL, BAD_CAST("boot"), NULL);
    }
}



static void
fmt_system_mount(GString *s,
		 host_resources_mib_hrFSEntry_t *fsEntry,
		 int loc_len, int rem_len, int type_len)
{
    const char *e;

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

    e = fmt_identity(filesystem_types,
		     fsEntry->hrFSType,
		     fsEntry->_hrFSTypeLength);
    g_string_sprintfa(s, "%-*s", type_len, e ? e : "");

    e = fmt_enum(hrFSAccess, fsEntry->hrFSAccess);
    g_string_sprintfa(s, "%s", e ? e : "");

    if (fsEntry->hrFSBootable
	&& *(fsEntry->hrFSBootable) == SNMPV2_TC_TRUTHVALUE_TRUE) {
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
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    host_resources_mib_get_hrFSTable(interp->peer, &hrFSTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
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
	    type = fmt_identity(filesystem_types,
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
    gchar const *e;

    tree = xml_new_child(root, NULL, BAD_CAST("area"), NULL);
    xml_set_prop(tree, BAD_CAST("index"), "%d", hrStorageEntry->hrStorageIndex);
    
    if (hrStorageEntry->hrStorageDescr
	&& hrStorageEntry->_hrStorageDescrLength) {
	(void) xml_new_child(tree, NULL, BAD_CAST("description"), "%.*s",
			     (int) hrStorageEntry->_hrStorageDescrLength,
			     hrStorageEntry->hrStorageDescr);
    }

    e = fmt_identity(storage_types,
		     hrStorageEntry->hrStorageType,
		     hrStorageEntry->_hrStorageTypeLength);
    if (e) {
	(void) xml_new_child(tree, NULL, BAD_CAST("type"), "%s", e);
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

	node = xml_new_child(tree, NULL, BAD_CAST("size"), "%llu", (guint64)1024 * storage_size);
	xml_set_prop(node, BAD_CAST("unit"), "bytes");

	node = xml_new_child(tree, NULL, BAD_CAST("used"), "%llu", (guint64)1024 * storage_used);
	xml_set_prop(node, BAD_CAST("unit"), "bytes");
    }
}



static void
fmt_system_storage(GString *s,
		   host_resources_mib_hrStorageEntry_t *hrStorageEntry,
		   int descr_width, int type_width)
{
    gchar const *e = NULL;

    g_string_sprintfa(s, "%5d ", hrStorageEntry->hrStorageIndex);

    if (hrStorageEntry->hrStorageDescr
	&& hrStorageEntry->_hrStorageDescrLength) {
	g_string_sprintfa(s, "%-*.*s",
			  descr_width,
			  (int) MIN(descr_width, hrStorageEntry->_hrStorageDescrLength),
			  hrStorageEntry->hrStorageDescr);
    } else {
	g_string_sprintfa(s, "%*s", descr_width, "");
    }

    e = fmt_identity(storage_types,
		     hrStorageEntry->hrStorageType,
		     hrStorageEntry->_hrStorageTypeLength);
    g_string_sprintfa(s, "%-*s", type_width, e ? e : "");

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

	fmt_x_kbytes(s, (guint32) storage_size);
	fmt_x_kbytes(s, (guint32) storage_used);
	if (storage_size > storage_used) {
	    fmt_x_kbytes(s, (guint32) (storage_size - storage_used));
	} else {
	    g_string_sprintfa(s, " %5s", "-----");
	}
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
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    host_resources_mib_get_hrStorageTable(interp->peer,
					  &hrStorageTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (hrStorageTable) {
	for (i = 0; hrStorageTable[i]; i++) {
	    if (hrStorageTable[i]->hrStorageDescr
		&& hrStorageTable[i]->_hrStorageDescrLength > descr_width) {
		descr_width = hrStorageTable[i]->_hrStorageDescrLength;
	    }
	    type = fmt_identity(storage_types,
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
    gchar *name;

    if (system) {
	(void) xml_new_child(root, NULL, BAD_CAST("name"), "%.*s",
			     (int) system->_sysNameLength,
			     system->sysName);
	name = gnet_snmp_get_uri_string(interp->peer);
	if (name) {
	    (void) xml_new_child(root, NULL, BAD_CAST("uri"), "%s", name);
	    g_free(name);
	}
	
	(void) xml_new_child(root, NULL, BAD_CAST("description"), "%.*s",
			     (int) system->_sysDescrLength,
			     system->sysDescr);
	(void) xml_new_child(root, NULL, BAD_CAST("contact"), "%.*s",
			     (int) system->_sysContactLength,
			     system->sysContact);
	(void) xml_new_child(root, NULL, BAD_CAST("location"), "%.*s",
			     (int) system->_sysLocationLength,
			     system->sysLocation);

	if (system->sysObjectID) {
	    scli_vendor_t const *vendor;
	    vendor = scli_get_vendor_oid(system->sysObjectID,
					 system->_sysObjectIDLength);
	    if (vendor && vendor->name) {
		(void) xml_new_child(root, NULL, BAD_CAST("vendor"), "%s", vendor->name);
	    }
	    if (vendor && vendor->url) {
		(void) xml_new_child(root, NULL, BAD_CAST("vendor-url"), "%s", vendor->url);
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
		    (void) xml_new_child(root, NULL, BAD_CAST("service"), "%s",
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
    gchar *name;
    int i;
    int const indent = 18;

    if (system) {
	if (system->sysName) {
	    fmt_display_string(s, indent, "Name:",
			       (int) system->_sysNameLength,
			       (gchar *) system->sysName);
	}
	name = gnet_snmp_get_uri_string(interp->peer);
	if (name) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Agent:", name);
	    g_free(name);
	}
	if (system->sysDescr && system->_sysDescrLength) {
	    fmt_display_string(s, indent, "Description:",
			       (int) system->_sysDescrLength,
			       (gchar *) system->sysDescr);
	}
	if (system->sysContact) {
	    fmt_display_string(s, indent, "Contact:",
			       (int) system->_sysContactLength,
			       (gchar *) system->sysContact);
	}
	if (system->sysLocation) {
	    fmt_display_string(s, indent, "Location:",
			       (int) system->_sysLocationLength,
			       (gchar *) system->sysLocation);
	}
	if (system->sysObjectID) {
	    scli_vendor_t const *vendor;
	    vendor = scli_get_vendor_oid(system->sysObjectID,
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
    if_mib_ifMIBObjects_t *ifMibObjects = NULL;
    entity_mib_entityGeneral_t *entityGeneral = NULL;
    bridge_mib_dot1dBase_t *dot1dBase = NULL;
    rs_232_mib_rs232_t *rs232 = NULL;
    disman_script_mib_smLangEntry_t **smLangTable = NULL;
    const char *e;
    GString *s;
    int i;
    int const indent = 18;
    xmlNodePtr node;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmpv2_mib_get_system(interp->peer, &system, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    host_resources_mib_get_hrSystem(interp->peer, &hrSystem, 0, NULL);
    host_resources_mib_get_hrStorage(interp->peer, &hrStorage, 0, NULL);
    if_mib_get_interfaces(interp->peer, &interfaces, 0, NULL);
    if_mib_get_ifMIBObjects(interp->peer, &ifMibObjects, 0, NULL);
    entity_mib_get_entityGeneral(interp->peer, &entityGeneral, 0, NULL);
    bridge_mib_get_dot1dBase(interp->peer, &dot1dBase, 0, NULL);
    rs_232_mib_get_rs232(interp->peer, &rs232, 0, NULL);
    disman_script_mib_get_smLangTable(interp->peer, &smLangTable,
				      DISMAN_SCRIPT_MIB_SMLANGDESCR, NULL);

    if (scli_interp_xml(interp)) {
	xml_system_info(interp->xml_node, interp, system);
    } else {
	fmt_system_info(interp->result, interp, system);
    }

    s = interp->result;
    if (hrSystem) {
	if (hrSystem->hrSystemDate && hrSystem->_hrSystemDateLength) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("current-time"), "%s",
			     xml_date_and_time(hrSystem->hrSystemDate,
					       hrSystem->_hrSystemDateLength));
	    } else {
		g_string_sprintfa(s, "%-*s", indent, "Current-Time:");
		g_string_append(s, fmt_date_and_time(hrSystem->hrSystemDate,
						     hrSystem->_hrSystemDateLength));
		g_string_append_c(s, '\n');
	    }
	}
    }

    if (system) {
	if (system->sysUpTime) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("agent-boot-time"), "%s",
				     xml_timeticks(*(system->sysUpTime)));
	    } else {
		g_string_sprintfa(s, "%-*s", indent, "Agent-Boot-Time:");
		g_string_append(s, fmt_timeticks(*(system->sysUpTime)));
		g_string_append_c(s, '\n');
	    }
	}
    }
    
    if (hrSystem) {
	if (hrSystem->hrSystemUptime) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("system-boot-time"), "%s",
				     xml_timeticks(*(hrSystem->hrSystemUptime)));
	    } else {
	    g_string_sprintfa(s, "%-*s", indent, "System-Boot-Time:");
	    g_string_append(s, fmt_timeticks(*(hrSystem->hrSystemUptime)));
	    g_string_append_c(s, '\n');
	}
	}
	if (hrSystem->hrSystemInitialLoadDevice) {
	    host_resources_mib_hrDeviceEntry_t *dev;
	    host_resources_mib_get_hrDeviceEntry(interp->peer, &dev,
						 *hrSystem->hrSystemInitialLoadDevice, 0, NULL);
	    if (dev && dev->hrDeviceDescr) {
		if (scli_interp_xml(interp)) {
		    (void) xml_new_child(interp->xml_node, NULL,
					 BAD_CAST("system-boot-dev"), "%.*s",
					 (int) dev->_hrDeviceDescrLength,
					 dev->hrDeviceDescr);
		} else {
		fmt_display_string(s, indent, "System-Boot-Dev:",
				   (int) dev->_hrDeviceDescrLength,
				   (gchar *) dev->hrDeviceDescr);
	    }
	    }
	    host_resources_mib_free_hrDeviceEntry(dev);
	}
	if (hrSystem->hrSystemInitialLoadParameters) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("system-boot-args"), "%s",
				     xml_display_string((int) hrSystem->_hrSystemInitialLoadParametersLength,
							(gchar *) hrSystem->hrSystemInitialLoadParameters));
	    } else {
	    fmt_display_string(s, indent, "System-Boot-Args:",
			       (int) hrSystem->_hrSystemInitialLoadParametersLength,
			       (gchar *) hrSystem->hrSystemInitialLoadParameters);
	}
	}
	if (hrSystem->hrSystemNumUsers) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("users"), "%u",
				     *(hrSystem->hrSystemNumUsers));
	    } else {
	    g_string_sprintfa(s, "%-*s%u", indent, "Users:", 
			      *(hrSystem->hrSystemNumUsers));
	    g_string_append_c(s, '\n');
	}
	}
	if (hrSystem->hrSystemProcesses) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("processes"), "%u",
				     *(hrSystem->hrSystemProcesses));
	    } else {
	    g_string_sprintfa(s, "%-*s%u", indent, "Processes:",
			      *(hrSystem->hrSystemProcesses));
	    }
	    if (hrSystem->hrSystemMaxProcesses
		&& *(hrSystem->hrSystemMaxProcesses)) {
		if (scli_interp_xml(interp)) {
		    (void) xml_new_child(interp->xml_node, NULL,
					 BAD_CAST("max-processes"), "%u",
					 *(hrSystem->hrSystemMaxProcesses));
		} else {
		g_string_sprintfa(s, " (%u maximum)",
				  *(hrSystem->hrSystemMaxProcesses));
	    }
	    }
	    if (!scli_interp_xml(interp)) {
	    g_string_append_c(s, '\n');
	}
    }
    }

    if (hrStorage) {
	if (hrStorage->hrMemorySize) {
	    if (scli_interp_xml(interp)) {
		node = xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("memory"), "%llu",
				     (guint64)1024 * *(hrStorage->hrMemorySize));
		xml_set_prop(node, BAD_CAST("unit"), "bytes");
	    } else {
	    g_string_sprintfa(s, "%-*s", indent, "Memory:");
	    fmt_kbytes(s, (guint32) *(hrStorage->hrMemorySize));
	    g_string_append_c(s, '\n');
	}
    }
    }

    if (interfaces) {
	if (interfaces->ifNumber) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("interfaces"), "%d",
				     *(interfaces->ifNumber));
	    } else {
		g_string_sprintfa(s, "%-*s%d\n", indent, "Interfaces:",
				  *(interfaces->ifNumber));
	    }
	}
	if (ifMibObjects && system && system->sysUpTime) {
	    if (ifMibObjects->ifTableLastChange) {
		guint32 dsecs = *(system->sysUpTime)
		    - *(ifMibObjects->ifTableLastChange);
		g_string_sprintfa(s, "%-*s%s\n", indent, "Interface Swap:",
				  fmt_timeticks(dsecs));
	    }
	}
    }

    if (entityGeneral && entityGeneral->entLastChangeTime
	&& system && system->sysUpTime) {
	guint32 dsecs = *(system->sysUpTime)
	    - *(entityGeneral->entLastChangeTime);
	g_string_sprintfa(s, "%-*s%s\n", indent, "Entity Swap:",
			  fmt_timeticks(dsecs));
    }

    if (dot1dBase) {
	if (dot1dBase->dot1dBaseNumPorts && *dot1dBase->dot1dBaseNumPorts) {
	    if (scli_interp_xml(interp)) {
		(void) xml_new_child(interp->xml_node, NULL,
				     BAD_CAST("bridge-ports"), "%d",
				     *(dot1dBase->dot1dBaseNumPorts));
	    } else {
	    g_string_sprintfa(s, "%-*s%d\n", indent, "Bridge Ports:",
			      *(dot1dBase->dot1dBaseNumPorts));
	}
	}
	if (dot1dBase->dot1dBaseType) {
	    e = fmt_enum(bridge_mib_enums_dot1dBaseType, dot1dBase->dot1dBaseType);
	    if (e) {
		if (scli_interp_xml(interp)) {
		    (void) xml_new_child(interp->xml_node, NULL,
					 BAD_CAST("bridge-type"), "%s", e);
		} else {
		    g_string_sprintfa(s, "%-*s%s\n", indent,
				      "Bridge Type:", e);
		}
	    }
	}
    }

    if (rs232 && rs232->rs232Number && rs232->rs232Number > 0) {
	if (scli_interp_xml(interp)) {
	    (void) xml_new_child(interp->xml_node, NULL,
				 BAD_CAST("rs232-ports"), "%d", *(rs232->rs232Number));
	} else {
	g_string_sprintfa(s, "%-*s%d\n", indent, "RS 232 Ports:",
			  *(rs232->rs232Number));
    }
    }

    if (smLangTable) {
	for (i = 0; smLangTable[i]; i++) ;
	if (scli_interp_xml(interp)) {
	    (void) xml_new_child(interp->xml_node, NULL,
				 BAD_CAST("script-languages"), "%d", i);
	} else {
	g_string_sprintfa(s, "%-*s%u\n", indent, "Script Languages:", i);
    }
    }

    if (system)
	snmpv2_mib_free_system(system);
    if (hrSystem)
	host_resources_mib_free_hrSystem(hrSystem);
    if (hrStorage)
	host_resources_mib_free_hrStorage(hrStorage);
    if (interfaces)
	if_mib_free_interfaces(interfaces);
    if (ifMibObjects)
	if_mib_free_ifMIBObjects(ifMibObjects);
    if (entityGeneral)
	entity_mib_free_entityGeneral(entityGeneral);
    if (dot1dBase)
	bridge_mib_free_dot1dBase(dot1dBase);
    if (rs232)
	rs_232_mib_free_rs232(rs232);
    if (smLangTable)
	disman_script_mib_free_smLangTable(smLangTable);

    return SCLI_OK;
}



static int
set_system_contact(scli_interp_t *interp, int argc, char **argv)
{
    gchar *contact;
    gsize contact_len;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    contact = argv[1];
    contact_len = strlen(contact);
    if (contact_len < SNMPV2_MIB_SYSCONTACTMINLENGTH
	|| contact_len > SNMPV2_MIB_SYSCONTACTMAXLENGTH) {
	g_string_assign(interp->result, contact);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmpv2_mib_set_sysContact(interp->peer, (guchar *) contact, contact_len, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
set_system_name(scli_interp_t *interp, int argc, char **argv)
{
    gchar *name;
    gsize name_len;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    name = argv[1];
    name_len = strlen(name);
    if (name_len < SNMPV2_MIB_SYSNAMEMINLENGTH
	|| name_len > SNMPV2_MIB_SYSNAMEMAXLENGTH) {
	g_string_assign(interp->result, name);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmpv2_mib_set_sysName(interp->peer, (guchar *) name, name_len, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
set_system_location(scli_interp_t *interp, int argc, char **argv)
{
    gchar *location;
    gsize location_len;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    location = argv[1];
    location_len = strlen(location);
    if (location_len < SNMPV2_MIB_SYSLOCATIONMINLENGTH
	|| location_len > SNMPV2_MIB_SYSLOCATIONMAXLENGTH) {
	g_string_assign(interp->result, location);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmpv2_mib_set_sysLocation(interp->peer, (guchar *) location, location_len, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
dump_system(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmpv2_mib_get_system(interp->peer, &system, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
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



static int
check_system_contact(scli_interp_t *interp, int argc, char **argv)
{
    regex_t _regex_contact, *regex_contact = NULL;
    snmpv2_mib_system_t *system;
    int status = 1;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_contact = &_regex_contact;
	if (regcomp(regex_contact, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }
    
    if (scli_interp_dry(interp)) {
        if (regex_contact) regfree(regex_contact);
	return SCLI_OK;
    }

    snmpv2_mib_get_system(interp->peer, &system, SNMPV2_MIB_SYSCONTACT, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
        if (regex_contact) regfree(regex_contact);
	return SCLI_SNMP;
    }

    if (system) {
	if (system->_sysContactLength == 0) {
	    g_string_sprintfa(interp->result,
			      "System contact is a zero-length string and "
			      "should be configured to include at least an "
			      "email address.\n");
	}
	if (regex_contact) {
	    char *s = g_strdup_printf("%.*s",
				      (int) system->_sysContactLength,
				      system->sysContact);
	    status = regexec(regex_contact, s, (size_t) 0, NULL, 0);
	    g_free(s);
	    if (status != 0) {
		g_string_sprintfa(interp->result,
				  "System contact `%.*s' does not match the "
				  "regular expression `%s'.\n",
				  (int) system->_sysContactLength,
				  system->sysContact, argv[1]);
	    }
	}
    }

    if (system) snmpv2_mib_free_system(system);

    if (regex_contact) regfree(regex_contact);
    
    return SCLI_OK;
}



static int
check_system_storage(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrStorageEntry_t **hrStorageTable = NULL;
    int i;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    host_resources_mib_get_hrStorageTable(interp->peer,
					  &hrStorageTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (hrStorageTable) {
	for (i = 0; hrStorageTable[i]; i++) {
	    if (hrStorageTable[i]->hrStorageAllocationUnits
		&& hrStorageTable[i]->hrStorageSize
		&& hrStorageTable[i]->hrStorageUsed) {
		
		guint64 storage_size = 0;
		guint64 storage_used = 0;
		guint32 const scale = 1024;
		double percentage;
		
		storage_size = *(hrStorageTable[i]->hrStorageSize);
		storage_size *= *(hrStorageTable[i]->hrStorageAllocationUnits);
		storage_size /= scale;

		storage_used = *(hrStorageTable[i]->hrStorageUsed);
		storage_used *= *(hrStorageTable[i]->hrStorageAllocationUnits);
		storage_used /= scale;

		percentage = storage_size ? storage_used * 100 / storage_size : 0;
		if (percentage > 90) {
		    g_string_sprintfa(interp->result,
			      "Storage #%d (%.*s) is %3.1f%% (> 90%%) filled\n",
			      hrStorageTable[i]->hrStorageIndex,
			      hrStorageTable[i]->_hrStorageDescrLength,
			      hrStorageTable[i]->hrStorageDescr,
				      percentage);
		}
	    }
	}
    }

    if (hrStorageTable) host_resources_mib_free_hrStorageTable(hrStorageTable);

    return SCLI_OK;
}



static int
check_system_process(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrSWRunEntry_t **hrSWRunTable = NULL;
    regex_t _regex_path, *regex_path = NULL;
    int i;
    guint min = 0, max = 0xffffffff, cnt = 0;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    regex_path = &_regex_path;
    if (regcomp(regex_path, (argc > 1) ? argv[1] : ".",
		interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }

    if (argc == 3) {
	/* xxx scan this by hand to make sure it does what we want */
	if (2 == sscanf(argv[2], "%u*%u", &min, &max)) {
	} else if (1 == sscanf(argv[2], "%u", &min)) {
	    max = min;
	} else {
	    if (regex_path) regfree(regex_path);
	    return SCLI_SYNTAX_VALUE;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_path) regfree(regex_path);
	return SCLI_OK;
    }

    host_resources_mib_get_hrSWRunTable(interp->peer, &hrSWRunTable,
					HOST_RESOURCES_MIB_HRSWRUNPATH,
					&error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (hrSWRunTable) {
	for (i = 0, cnt = 0; hrSWRunTable[i]; i++) {
	    if (match_process(regex_path, hrSWRunTable[i])) {
		cnt++;
	    }
	}
	if (cnt < min || cnt > max) {
	    g_string_sprintfa(interp->result,
		  "Number of processes (%d) matching the regular "
	          "expression `%s' does not match the bound %u*%u.\n",
			      cnt, argv[1], min, max);
	}
    }
	
    if (hrSWRunTable)
	host_resources_mib_free_hrSWRunTable(hrSWRunTable);

    if (regex_path) regfree(regex_path);
    
    return SCLI_OK;
}



#ifdef MEM_DEBUG
static int
cmd_xxx(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_interfaces_t *interfaces = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    int i, n;
    char *end;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    n = strtol(argv[1], &end, 0);
    if (*end) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_NUMBER;
    }

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
	  "The `set system contact' command configures the system contact\n"
	  "information. The <string> argument should include information\n"
	  "on how to contact a person who is responsible for this system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_system_contact },

	{ "set system name", "<string>",
	  "The `set system name' command configures the name of the system.\n"
	  "By convention, this is the fully-qualified domain name.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_system_name },

	{ "set system location", "<string>",
	  "The `set system location' command configures the physical\n"
	  "location of the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_system_location },

	{ "show system info", NULL,
	  "The `show system info' command shows general information about the\n"
	  "system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "system info", NULL,
	  show_system_info },

	{ "show system devices", NULL,
	  "The `show system devices' command shows a list of system devices.\n"
	  "The command generates a table with the following columns:\n"
	  "\n"
	  "  INDEX       device number\n"
	  "  STATUS      current status of the device\n"
	  "  DESCRIPTION description of the device",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "system devices", NULL,
	  show_system_devices },

	{ "show system storage", NULL,
	  "The `show system storage' command displays information about the\n"
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
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "system storage", NULL,
	  show_system_storage },

	{ "show system mounts", NULL,
	  "The `show system mounts' command shows the list of filesystems\n"
	  "mounted on the system. The command generates a table with the\n"
	  "following columns:\n"
	  "\n"
	  "  INDEX   filesystem identification number\n"
	  "  LOCAL   local root path name of the filesystem\n"
	  "  REMOTE  remote server and root path name (if any)\n"
	  "  TYPE    filesytem type (if known)\n"
	  "  OPTIONS access mode (ro/rw) and boot flag",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "system mounts", NULL,
	  show_system_mounts },

	{ "show system processes", "[<regexp>]",
	  "The `show system processes' command display information about the\n"
	  "processes currently running on the system. The regular expression\n"
	  "<regexp> is matched against the command executed by the process\n"
	  "to select the processes of interest. The command generates a table\n"
	  "with the following columns:\n"
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
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "system processes", NULL,
	  show_system_processes },

	{ "show system software", "[<regexp>]",
	  "The `show system software' command display information about the\n"
	  "software installed on the system. The regular expression <regexp>\n"
	  "is matched against the software name to select the software of\n"
	  "interest. The command generates a table with the following columns:\n"
	  "\n"
	  "  SID     software identification number\n"
	  "  T       type of the software (see below)\n"
	  "  DATE    software installation date\n"
	  "  NAME    software name\n"
	  "\n"
	  "The software type values are ?=unknown, O=operating system, \n"
	  "D=device driver, and A=application.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  "system software", NULL,
	  show_system_software },

	{ "monitor system storage", NULL,
	  "The `monitor system storage' command shows the same\n"
	  "information as the show system storage command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_system_storage },

	{ "loop system storage", NULL,
	  "The `loop system storage' command shows the same\n"
	  "information as the show system storage command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_LOOP | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_system_storage },

	{ "monitor system processes", "[<regexp>]",
	  "The `monitor system processes' command show the same\n"
	  "information as the show system processes command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_system_processes },

	{ "check system contact", NULL,
	  "The `check system contact' command xxx.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  check_system_contact },

	{ "check system storage", NULL,
	  "The `check system storage' command checks xxx.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  check_system_storage },

	{ "check system process", "[<regexp>] [<n>*<m>]",
	  "The `check system process' command checks xxx.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  check_system_process },

#ifdef MEM_DEBUG
	{ "xxx", "<repetitions>",
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_xxx },
#endif
	{ "dump system", NULL,
	  "The `dump system' command generates a sequence of scli commands\n"
	  "which can be used to restore the system configuration.\n",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
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
