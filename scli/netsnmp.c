/* 
 * netsnmp.c -- scli ucdsnmp/netsnmp mode implementation
 *
 * Copyright (C) 2002 Juergen Schoenwaelder
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

#include "ucd-snmp-mib.h"


static void
fmt_info(GString *s, ucd_snmp_mib_version_t *version)
{
    int const indent = 18;
    const char *e;

    if (version->versionTag) {
	fmt_display_string(s, indent, "Version:",
			   (int) version->_versionTagLength,
			   version->versionTag);
    }
    if (version->versionConfigureOptions) {
	fmt_display_string(s, indent, "Configuration:",
			   (int) version->_versionConfigureOptionsLength,
			   version->versionConfigureOptions);
    }

    e = fmt_enum(ucd_snmp_mib_enums_versionDoDebugging,
		 version->versionDoDebugging);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Debugging:", e);
    }
}



static void
fmt_load(GString *s, ucd_snmp_mib_laEntry_t *laEntry)
{
    int const indent = 18;
    
    if (laEntry->laNames && laEntry->laLoad) {
	g_string_sprintfa(s, "%-*.*s: %.*s\n", indent-1,
			  laEntry->_laNamesLength, laEntry->laNames,
			  laEntry->_laLoadLength, laEntry->laLoad);
    }
}



static int
show_netsnmp_info(scli_interp_t *interp, int argc, char **argv)
{
    ucd_snmp_mib_version_t *version = NULL;
    ucd_snmp_mib_laEntry_t **laTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ucd_snmp_mib_get_version(interp->peer, &version,
			     UCD_SNMP_MIB_VERSIONTAG
			     | UCD_SNMP_MIB_VERSIONCONFIGUREOPTIONS
			     | UCD_SNMP_MIB_VERSIONDODEBUGGING);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    ucd_snmp_mib_get_laTable(interp->peer, &laTable,
			     UCD_SNMP_MIB_LANAMES
			     | UCD_SNMP_MIB_LALOAD);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (version) {
	fmt_info(interp->result, version);
    }

    if (laTable) {
	for (i = 0; laTable[i]; i++) {
	    fmt_load(interp->result, laTable[i]);
	}
    }
    
    if (version) ucd_snmp_mib_free_version(version);
    if (laTable) ucd_snmp_mib_free_laTable(laTable);

    return SCLI_OK;
}



static int
set_netsnmp_debugging(scli_interp_t *interp, int argc, char **argv)
{
    ucd_snmp_mib_version_t *version = NULL;
    gint32 value = 1;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    if (! gsnmp_enum_get_number(ucd_snmp_mib_enums_versionDoDebugging,
				argv[1], &value)) {
	return SCLI_SYNTAX_VALUE;
    }

    version = ucd_snmp_mib_new_version();
    version->versionDoDebugging = &value;
    ucd_snmp_mib_set_version(interp->peer, version,
			     UCD_SNMP_MIB_VERSIONDODEBUGGING);
    ucd_snmp_mib_free_version(version);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



void
scli_init_netsnmp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "set netsnmp debugging", "<value>",
	  "The set netsnmp debugging command controls whether the agent\n"
	  "generates debug messages or not. The <value> parameter must\n"
	  "be one of the strings \"enabled\" or \"disabled\".",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  set_netsnmp_debugging },
	
	{ "show netsnmp info", NULL,
	  "The show netsnmp info command show general information about\n"
	  "the netsnmp/ucdsnmp agent such as the version number and the\n"
	  "software configuration.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_netsnmp_info },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t netsnmp_mode = {
	"netsnmp",
	"The netsnmp scli mode is used to display and configure netsnmp\n"
	"specific parameters. It is based on the UCD-SNMP-MIB.",
	cmds
    };

    scli_register_mode(interp, &netsnmp_mode);
}

