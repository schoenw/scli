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

#define UCD_SNMP_MIB_VERSIONDODEBUGGING_DISABLED 0
#define UCD_SNMP_MIB_VERSIONDODEBUGGING_ENABLED  1

static GNetSnmpEnum const ucd_snmp_mib_enums_versionDoDebugging[] = {
    { UCD_SNMP_MIB_VERSIONDODEBUGGING_DISABLED, "disabled" },
    { UCD_SNMP_MIB_VERSIONDODEBUGGING_ENABLED,  "enabled" },
    { 0, NULL }
};


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



static int
show_netsnmp_info(scli_interp_t *interp, int argc, char **argv)
{
    ucd_snmp_mib_version_t *version = NULL;

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

    if (version) {
	fmt_info(interp->result, version);
    }

    if (version) ucd_snmp_mib_free_version(version);

    return SCLI_OK;
}



static void
fmt_load(GString *s, ucd_snmp_mib_laEntry_t *laEntry)
{
    const char *names[] = {
	"Load-1", "Load-5", "Load-15", NULL
    };
    const char *labels[] = {
	"Load (1 min):", "Load (5 min):", "Load (15 min):", NULL
    };
    int const indent = 18; 
    int i;

    for (i = 0; names[i]; i++) {
	if (strncmp(laEntry->laNames, names[i],
		    laEntry->_laNamesLength) == 0) {
	    break;
	}
    }
    if (! names[i]) {
	return;
    }

    g_string_sprintfa(s, "%-*s%.2f\n", indent, labels[i],
		      *laEntry->laLoadInt / 100.0);

    if (laEntry->_laErrMessageLength) {
	fmt_display_string(s, indent, "Error:",
			   (int) laEntry->_laErrMessageLength,
			   laEntry->laErrMessage);
    }
}



static int
show_netsnmp_load(scli_interp_t *interp, int argc, char **argv)
{
    ucd_snmp_mib_laEntry_t **laTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ucd_snmp_mib_get_laTable(interp->peer, &laTable,
			     UCD_SNMP_MIB_LANAMES
			     | UCD_SNMP_MIB_LALOADINT
			     | UCD_SNMP_MIB_LAERRMESSAGE);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (laTable) {
	for (i = 0; laTable[i]; i++) {
	    fmt_load(interp->result, laTable[i]);
	}
    }
    
    if (laTable) ucd_snmp_mib_free_laTable(laTable);

    return SCLI_OK;
}



static void
fmt_ext(GString *s, ucd_snmp_mib_extEntry_t *extEntry)
{
    int const indent = 18;

    g_string_sprintfa(s, "%-*s%d\n", indent, "Index:",
		      extEntry->extIndex);
    fmt_display_string(s, indent, "Name:",
		       (int) extEntry->_extNamesLength,
		       extEntry->extNames);
    fmt_display_string(s, indent, "Command:",
		       (int) extEntry->_extCommandLength,
		       extEntry->extCommand);
    fmt_display_string(s, indent, "Output:",
		       (int) extEntry->_extOutputLength,
		       extEntry->extOutput);
    if (extEntry->extResult) {
	g_string_sprintfa(s, "%-*s%d\n", indent, "Code:",
			  *extEntry->extResult);
    }
}



static int
show_netsnmp_exec(scli_interp_t *interp, int argc, char **argv)
{
    ucd_snmp_mib_extEntry_t **extTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ucd_snmp_mib_get_extTable(interp->peer, &extTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (extTable) {
	for (i = 0; extTable[i]; i++) {
	    fmt_ext(interp->result, extTable[i]);
	}
    }

    if (extTable) ucd_snmp_mib_free_extTable(extTable);

    return SCLI_OK;
}



static void
fmt_proc(GString *s, ucd_snmp_mib_prEntry_t *prEntry)
{
    int const indent = 18;

    g_string_sprintfa(s, "%-*s%d\n", indent, "Index:",
		      prEntry->prIndex);
    fmt_display_string(s, indent, "Process:",
		       (int) prEntry->_prNamesLength,
		       prEntry->prNames);
    g_string_sprintfa(s, "%-*s%d\n", indent, "Minimum:",
		      *prEntry->prMin);
    g_string_sprintfa(s, "%-*s%d\n", indent, "Maximum:",
		      *prEntry->prMax);
    g_string_sprintfa(s, "%-*s%d\n", indent, "Current:",
		      *prEntry->prCount);
    if (prEntry->_prErrMessageLength) {
	fmt_display_string(s, indent, "Error:",
			   (int) prEntry->_prErrMessageLength,
			   prEntry->prErrMessage);
    }
}



static int
show_netsnmp_proc(scli_interp_t *interp, int argc, char **argv)
{
    ucd_snmp_mib_prEntry_t **prTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ucd_snmp_mib_get_prTable(interp->peer, &prTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prTable) {
	for (i = 0; prTable[i]; i++) {
	    if (i) g_string_append(interp->result, "\n");
	    fmt_proc(interp->result, prTable[i]);
	}
    }

    if (prTable) ucd_snmp_mib_free_prTable(prTable);

    return SCLI_OK;
}



static int
set_netsnmp_debugging(scli_interp_t *interp, int argc, char **argv)
{
    gint32 value = 1;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (! gnet_snmp_enum_get_number(ucd_snmp_mib_enums_versionDoDebugging,
				    argv[1], &value)) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ucd_snmp_mib_set_versionDoDebugging(interp->peer, value);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
set_netsnmp_restart(scli_interp_t *interp, int argc, char **argv)
{
    gint32 value = 1;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ucd_snmp_mib_set_versionRestartAgent(interp->peer, value);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
dump_netsnmp(scli_interp_t *interp, int argc, char **argv)
{
    ucd_snmp_mib_version_t *version = NULL;
    const char *e;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    ucd_snmp_mib_get_version(interp->peer, &version,
			     UCD_SNMP_MIB_VERSIONDODEBUGGING);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (version) {
	e = fmt_enum(ucd_snmp_mib_enums_versionDoDebugging,
		     version->versionDoDebugging);
	if (e) {
	    g_string_sprintfa(interp->result, "set netsnmp debugging %s\n", e);
	}
    }

    if (version) ucd_snmp_mib_free_version(version);
    
    return SCLI_OK;
}



void
scli_init_netsnmp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "set netsnmp debugging", "<value>",
	  "The `set netsnmp debugging' command controls whether the agent\n"
	  "generates debug messages or not. The <value> parameter must\n"
	  "be one of the strings \"enabled\" or \"disabled\".",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_netsnmp_debugging },
	
	{ "set netsnmp restart", NULL,
	  "The `set netsnmp restart' command restarts the agent.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_netsnmp_restart },
	
	{ "show netsnmp info", NULL,
	  "The `show netsnmp info' command shows general information about\n"
	  "the netsnmp/ucdsnmp agent such as the version number and the\n"
	  "software configuration.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_netsnmp_info },

	{ "show netsnmp load", NULL,
	  "The `show netsnmp load' command shows the load indices of the\n"
	  "system. This is usually the length of the queue in front of\n"
	  "the processor(s) averaged over some time interval.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_netsnmp_load },

	{ "show netsnmp exec", NULL,
	  "The `show netsnmp exec' command shows information about\n"
	  "pre-configured commands that can be invoked.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_netsnmp_exec },

	{ "show netsnmp proc", NULL,
	  "The `show netsnmp proc' command shows information about\n"
	  "which processes netsnmp watches.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_netsnmp_proc },

	{ "dump netsnmp", NULL,
	  "The `dump netsnmp' command generates a sequence of scli commands\n"
	  "which can be used to restore the netsnmp specific configuration.\n",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  dump_netsnmp },

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

