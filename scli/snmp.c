/* 
 * entity.c -- scli snmp mode implementation
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

#include "snmpv2-mib.h"
#include "snmp-framework-mib.h"
#include "snmp-view-based-acm-mib.h"


static stls_enum_t const security_model[] = {
    { 0,	"any" },
    { 1,	"v1" },
    { 2,	"v2c" },
    { 3,	"usm" },    
    { 0, NULL }
};



static stls_enum_t const security_level[] = {
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_NOAUTHNOPRIV,	"--" },
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_AUTHNOPRIV,	"a-" },
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_AUTHPRIV,		"ap" },
    { 0, NULL }
};



static void
fmt_storage_type(GString *s, gint32 *storage)
{
    static stls_enum_t const storage_types[] = {
	{ 1, "o" },	/* other */
	{ 2, "v" },	/* volatile */
	{ 3, "n" },	/* nonVolatile */
	{ 4, "p" },	/* permanent */
	{ 5, "r" },	/* readOnly */
	{ 0, NULL }
    };

    fmt_enum(s, 1, storage_types, storage);
}



static void
fmt_row_status(GString *s, gint32 *status)
{
    static stls_enum_t const row_states[] = {
	{ 1, "a" },	/* active */
	{ 2, "s" },	/* notInService */
	{ 3, "r" },	/* notReady */
	{ 0, NULL }
    };

    fmt_enum(s, 1, row_states, status);
}



static int
cmd_snmp_engine(scli_interp_t *interp, int argc, char **argv)
{
    snmp_framework_mib_snmpEngine_t *snmpEngine;
    GString *s;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmp_framework_mib_get_snmpEngine(interp->peer, &snmpEngine)) {
	return SCLI_ERROR;
    }

    s = interp->result;
    if (snmpEngine) {
	if (snmpEngine->snmpEngineBoots) {
	    g_string_sprintfa(s, "Boots: %u times\n",
			      *(snmpEngine->snmpEngineBoots));
	}
	if (snmpEngine->snmpEngineTime) {
	    g_string_sprintfa(s, "Time: %u seconds since last change of boots\n",
			      *(snmpEngine->snmpEngineTime));
	}
	if (snmpEngine->snmpEngineMaxMessageSize) {
	    g_string_sprintfa(s, "MMSZ: %u byte\n",
			      *(snmpEngine->snmpEngineMaxMessageSize));
	}
	snmp_framework_mib_free_snmpEngine(snmpEngine);
    }
    
    return SCLI_OK;
}



static void
show_snmp_resource(GString *s, sysOREntry_t *sysOREntry)
{
    g_string_sprintfa(s, "%3d: %.*s\n",
		      sysOREntry->sysORIndex,
		      (int) sysOREntry->_sysORDescrLength,
		      sysOREntry->sysORDescr);
}



static int
cmd_snmp_resources(scli_interp_t *interp, int argc, char **argv)
{
    sysOREntry_t **sysORTable;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmpv2_mib_get_sysORTable(interp->peer, &sysORTable)) {
	return SCLI_ERROR;
    }

    if (sysORTable) {
	for (i = 0; sysORTable[i]; i++) {
	    show_snmp_resource(interp->result, sysORTable[i]);
	}
    }

    if (sysORTable) snmpv2_mib_free_sysORTable(sysORTable);

    return SCLI_OK;
}



static void
show_snmp_vacm_group(GString *s,
     snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmGroupEntry,
		     int sec_name_width, int sec_group_width)
{
    char const *model;
    
    /*
	group
	|- name (usm) (pa)
	|- foo  (usm)
	`- bar  (usm)
	asdf
	`- base (snmpc)
    */

    fmt_storage_type(s, vacmGroupEntry->vacmSecurityToGroupStorageType);
    fmt_row_status(s, vacmGroupEntry->vacmSecurityToGroupStatus);

    model = stls_enum_get_label(security_model,
				vacmGroupEntry->vacmSecurityModel);
    g_string_sprintfa(s, " %-3s %-*.*s",
		      model ? model : "", sec_name_width,
		      (int) vacmGroupEntry->_vacmSecurityNameLength,
		      vacmGroupEntry->vacmSecurityName);
    g_string_sprintfa(s, " -> %-*.*s\n", sec_group_width,
		      (int) vacmGroupEntry->_vacmGroupNameLength,
		      vacmGroupEntry->vacmGroupName);
}



static int
cmd_snmp_vacm_groups(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmGroupTable;
    int sec_name_width = 8;
    int sec_group_width = 8;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmp_view_based_acm_mib_get_vacmSecurityToGroupTable(interp->peer,
						     &vacmGroupTable)) {
	return SCLI_ERROR;
    }

    if (vacmGroupTable) {
	for (i = 0; vacmGroupTable[i]; i++) {
	    if (vacmGroupTable[i]->_vacmSecurityNameLength > sec_name_width)
		sec_name_width = vacmGroupTable[i]->_vacmSecurityNameLength;
	    if (vacmGroupTable[i]->_vacmGroupNameLength > sec_group_width)
		sec_group_width = vacmGroupTable[i]->_vacmGroupNameLength;
	}
	g_string_sprintfa(interp->result,
			  "XX Mod %-*s -> Group\n",
			  sec_name_width, "Name");
	for (i = 0; vacmGroupTable[i]; i++) {
	    show_snmp_vacm_group(interp->result, vacmGroupTable[i],
				 sec_name_width, sec_group_width);
	}
    }

    if (vacmGroupTable)
	snmp_view_based_acm_mib_free_vacmSecurityToGroupTable(vacmGroupTable);
    
    return SCLI_OK;
}



static void
show_snmp_vacm_access(GString *s,
	      snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry,
		      int group_width, int cntxt_width,
		      int read_width, int  write_width, int notify_width)
{
    char const *model = NULL, *level = NULL, *match = NULL;
    
    fmt_storage_type(s, vacmAccessEntry->vacmAccessStorageType);
    fmt_row_status(s, vacmAccessEntry->vacmAccessStatus);

    model = stls_enum_get_label(security_model,
				vacmAccessEntry->vacmAccessSecurityModel);
    level = stls_enum_get_label(security_level,
				vacmAccessEntry->vacmAccessSecurityLevel);
    if (vacmAccessEntry->vacmAccessContextMatch) {
	match = stls_enum_get_label(snmp_view_based_acm_mib_enums_vacmAccessContextMatch,
				    *vacmAccessEntry->vacmAccessContextMatch);
    }
        
    g_string_sprintfa(s, " %-*.*s", group_width,
		      (int) vacmAccessEntry->_vacmGroupNameLength,
		      vacmAccessEntry->vacmGroupName);

    g_string_sprintfa(s, " %-3s %-2s",
		      model ? model : "", level ? level : "");
    
    g_string_sprintfa(s, " %-*.*s", cntxt_width,
		      (int) vacmAccessEntry->_vacmAccessContextPrefixLength,
		      vacmAccessEntry->vacmAccessContextPrefix);

    g_string_sprintfa(s, " %-8s", match ? match : "");

    g_string_sprintfa(s, " %-*.*s", read_width,
		      (int) vacmAccessEntry->_vacmAccessReadViewNameLength,
		      vacmAccessEntry->vacmAccessReadViewName);
    
    g_string_sprintfa(s, " %-*.*s", write_width,
		      (int) vacmAccessEntry->_vacmAccessWriteViewNameLength,
		      vacmAccessEntry->vacmAccessWriteViewName);
    
    g_string_sprintfa(s, " %-*.*s", notify_width,
		      (int) vacmAccessEntry->_vacmAccessNotifyViewNameLength,
		      vacmAccessEntry->vacmAccessNotifyViewName);
    
    g_string_append(s, "\n");
}



static int
cmd_snmp_vacm_access(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessTable;
    int group_width = 5;
    int cntxt_width = 3;
    int read_width = 5;
    int write_width = 5;
    int notify_width = 5;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmp_view_based_acm_mib_get_vacmAccessTable(interp->peer,
						    &vacmAccessTable)) {
	return SCLI_ERROR;
    }

    if (vacmAccessTable) {
	for (i = 0; vacmAccessTable[i]; i++) {
	    if (vacmAccessTable[i]->_vacmGroupNameLength > group_width)
		group_width = vacmAccessTable[i]->_vacmGroupNameLength;
	    if (vacmAccessTable[i]->_vacmAccessContextPrefixLength)
		cntxt_width = vacmAccessTable[i]->_vacmAccessContextPrefixLength;
	    if (vacmAccessTable[i]->_vacmAccessReadViewNameLength
		> read_width)
		read_width = vacmAccessTable[i]->_vacmAccessReadViewNameLength;
	    if (vacmAccessTable[i]->_vacmAccessWriteViewNameLength
		> write_width)
		write_width = vacmAccessTable[i]->_vacmAccessWriteViewNameLength;
	    if (vacmAccessTable[i]->_vacmAccessNotifyViewNameLength
		> notify_width)
		notify_width = vacmAccessTable[i]->_vacmAccessNotifyViewNameLength;
	}
	g_string_sprintfa(interp->result,
			  "XX %-*s Mod Le %-*s %-8s %-*s %-*s %-*s\n",
			  group_width, "Group",
			  cntxt_width, "Ctx",
			  "Match",
			  read_width, "Read",
			  write_width, "Write",
			  notify_width, "Notify");
	for (i = 0; vacmAccessTable[i]; i++) {
	    show_snmp_vacm_access(interp->result, vacmAccessTable[i],
				  group_width, cntxt_width,
				  read_width, write_width, notify_width);
	}
    }

    if (vacmAccessTable)
	snmp_view_based_acm_mib_free_vacmAccessTable(vacmAccessTable);
    
    return SCLI_OK;
}



static void
show_snmp_vacm_view(GString *s,
	      snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewEntry,
		      int view_width)
{
    char const *type = NULL;
    
    fmt_storage_type(s, vacmViewEntry->vacmViewTreeFamilyStorageType);
    fmt_row_status(s, vacmViewEntry->vacmViewTreeFamilyStatus);

    g_string_sprintfa(s, " %-*.*s", view_width,
		      (int) vacmViewEntry->_vacmViewTreeFamilyViewNameLength,
		      vacmViewEntry->vacmViewTreeFamilyViewName);

    if (vacmViewEntry->vacmViewTreeFamilyType) {
	type = stls_enum_get_label(snmp_view_based_acm_mib_enums_vacmViewTreeFamilyType,
				   *vacmViewEntry->vacmViewTreeFamilyType);
    }

    g_string_sprintfa(s, " %-8s ", type ? type : "");

    /* XXX display the OID pattern string */
    
    g_string_append(s, "\n");
}



static int
cmd_snmp_vacm_views(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTable;
    int view_width = 5;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmp_view_based_acm_mib_get_vacmViewTreeFamilyTable(interp->peer,
						    &vacmViewTable)) {
	return SCLI_ERROR;
    }

    if (vacmViewTable) {
	for (i = 0; vacmViewTable[i]; i++) {
	    if (vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength
		> view_width)
		view_width
		    = vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength;
	}
	g_string_sprintfa(interp->result,
			  "XX %-*s Type     Tree Family\n",
			  view_width, "View");
	for (i = 0; vacmViewTable[i]; i++) {
	    show_snmp_vacm_view(interp->result, vacmViewTable[i], view_width);
	}
    }

    if (vacmViewTable)
	snmp_view_based_acm_mib_free_vacmViewTreeFamilyTable(vacmViewTable);
    
    return SCLI_OK;
}



void
scli_init_snmp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show snmp engine",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "information about the snmp engine",
	  cmd_snmp_engine },
	{ "show snmp resources",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "information about the SNMP resources",
	  cmd_snmp_resources },
	{ "show snmp vacm groups",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "information about the VACM groups",
	  cmd_snmp_vacm_groups },
	{ "show snmp vacm access",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "information about the VACM access rules",
	  cmd_snmp_vacm_access },
	{ "show snmp vacm views",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "information about the VACM views",
	  cmd_snmp_vacm_views },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t snmp_mode = {
	"snmp",
	"scli mode to display and configure snmp specific information",
	cmds
    };
    
    scli_register_mode(interp, &snmp_mode);
}
