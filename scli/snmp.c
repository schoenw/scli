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

#include "scli.h"

#include "snmpv2-mib.h"
#include "snmp-framework-mib.h"
#include "snmp-view-based-acm-mib.h"


static GSnmpEnum const security_model[] = {
    { 0,	"any" },
    { 1,	"v1" },
    { 2,	"v2c" },
    { 3,	"usm" },    
    { 0, NULL }
};



static GSnmpEnum const security_level[] = {
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_NOAUTHNOPRIV,	"--" },
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_AUTHNOPRIV,	"a-" },
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_AUTHPRIV,		"ap" },
    { 0, NULL }
};



static GSnmpEnum const view_tree_family_type[] = {
    { SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_INCLUDED,	"incl" },
    { SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_EXCLUDED,	"excl" },
    { 0, NULL }
};



static void
fmt_storage_type(GString *s, gint32 *storage)
{
    static GSnmpEnum const storage_types[] = {
	{ 1, "o" },	/* other */
	{ 2, "v" },	/* volatile */
	{ 3, "n" },	/* nonVolatile */
	{ 4, "p" },	/* permanent */
	{ 5, "r" },	/* readOnly */
	{ 0, NULL }
    };
    
    const char *label;
    
    if (! storage) {
	g_string_append(s, " ");
	return;
    }
    
    label = gsnmp_enum_get_label(storage_types, *storage);
    if (label) {
	g_string_append(s, label);
    } else {
	g_string_append(s, "-");
    }
}



static void
fmt_row_status(GString *s, gint32 *status)
{
    static GSnmpEnum const row_states[] = {
	{ 1, "a" },	/* active */
	{ 2, "s" },	/* notInService */
	{ 3, "r" },	/* notReady */
	{ 0, NULL }
    };
    
    const char *label;
    
    if (! status) {
	g_string_append(s, " ");
	return;
    }
    
    label = gsnmp_enum_get_label(row_states, *status);
    if (label) {
	g_string_append(s, label);
    } else {
	g_string_append(s, "-");
    }
}



static int
cmd_snmp_engine(scli_interp_t *interp, int argc, char **argv)
{
    snmp_framework_mib_snmpEngine_t *snmpEngine;
    int const indent = 18;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (snmp_framework_mib_get_snmpEngine(interp->peer, &snmpEngine)) {
	return SCLI_ERROR;
    }
    
    if (snmpEngine) {
	if (snmpEngine->snmpEngineBoots) {
	    g_string_sprintfa(interp->result,
			      "%-*s %u times\n",
			      indent, "Boots:",
			      *(snmpEngine->snmpEngineBoots));
	}
	if (snmpEngine->snmpEngineTime) {
	    g_string_sprintfa(interp->result,
			      "%-*s %u seconds since last boot\n",
			      indent, "Time:",
			      *(snmpEngine->snmpEngineTime));
	}
	if (snmpEngine->snmpEngineMaxMessageSize) {
	    g_string_sprintfa(interp->result,
			      "%-*s %u byte\n",
			      indent, "MMSZ:",
			      *(snmpEngine->snmpEngineMaxMessageSize));
	}
    }
    
    if (snmpEngine) snmp_framework_mib_free_snmpEngine(snmpEngine);
    
    return SCLI_OK;
}



static void
show_snmp_resource(GString *s, snmpv2_mib_sysOREntry_t *sysOREntry)
{
    g_string_sprintfa(s, "%3d: %.*s\n",
		      sysOREntry->sysORIndex,
		      (int) sysOREntry->_sysORDescrLength,
		      sysOREntry->sysORDescr);
}



static int
cmd_snmp_resources(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_sysOREntry_t **sysORTable;
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
    
    model = gsnmp_enum_get_label(security_model,
				 vacmGroupEntry->vacmSecurityModel);
    g_string_sprintfa(s, "  %-3s %-*.*s",
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
			  "Row Mod %-*s -> Group\n",
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

    model = gsnmp_enum_get_label(security_model,
				vacmAccessEntry->vacmAccessSecurityModel);
    level = gsnmp_enum_get_label(security_level,
				vacmAccessEntry->vacmAccessSecurityLevel);
    if (vacmAccessEntry->vacmAccessContextMatch) {
	match = gsnmp_enum_get_label(snmp_view_based_acm_mib_enums_vacmAccessContextMatch,
				    *vacmAccessEntry->vacmAccessContextMatch);
    }
        
    g_string_sprintfa(s, "  %-*.*s", group_width,
		      (int) vacmAccessEntry->_vacmGroupNameLength,
		      vacmAccessEntry->vacmGroupName);

    g_string_sprintfa(s, " %-3s %-3s",
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
			  "Row %-*s Mod Sec %-*s %-8s %-*s %-*s %-*s\n",
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
		    int new, int last)
{
    char const *type = NULL;
    int i;

    if (vacmViewEntry->vacmViewTreeFamilySubtree
	&& vacmViewEntry->vacmViewTreeFamilyMask
	&& vacmViewEntry->vacmViewTreeFamilyType) {

	if (new) {
	    g_string_sprintfa(s, "%*s\n",
			      (int) vacmViewEntry->_vacmViewTreeFamilyViewNameLength,
			      vacmViewEntry->vacmViewTreeFamilyViewName);
	}

	g_string_sprintfa(s, "%c- ", last ? '`' : '|');
	fmt_storage_type(s, vacmViewEntry->vacmViewTreeFamilyStorageType);
	fmt_row_status(s, vacmViewEntry->vacmViewTreeFamilyStatus);
	type = gsnmp_enum_get_label(view_tree_family_type,
				   *vacmViewEntry->vacmViewTreeFamilyType);
	g_string_sprintfa(s, " %-4s ", type ? type : "");

	if (vacmViewEntry->vacmViewTreeFamilySubtree && vacmViewEntry->vacmViewTreeFamilyMask) {
	    for (i = 0; i < vacmViewEntry->_vacmViewTreeFamilySubtreeLength; i++) {
		int w = 0;
		if (i/8 < vacmViewEntry->_vacmViewTreeFamilyMaskLength) {
		    w = (vacmViewEntry->vacmViewTreeFamilyMask[i/8] & 1<<(7-(i%8))) ? 0 : 1;
		}
		if (w) {
		    g_string_sprintfa(s, "%s*", i ? "." : "");
		} else {
		    g_string_sprintfa(s, "%s%u", i ? "." : "",
				      vacmViewEntry->vacmViewTreeFamilySubtree[i]);
		}
	    }
	}   
	g_string_append(s, "\n");
    }
}



static int
cmd_snmp_vacm_views(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTable;
    int new;
    int last;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmp_view_based_acm_mib_get_vacmViewTreeFamilyTable(interp->peer,
						    &vacmViewTable)) {
	return SCLI_ERROR;
    }

    if (vacmViewTable) {
	for (i = 0; vacmViewTable[i]; i++) {
	    new = 1;
	    last = !vacmViewTable[i+1];
	    if (i > 0) {
		new = (vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength
		       != vacmViewTable[i-1]->_vacmViewTreeFamilyViewNameLength)
		    || (memcmp(vacmViewTable[i]->vacmViewTreeFamilyViewName,
			       vacmViewTable[i-1]->vacmViewTreeFamilyViewName,
			       vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength) != 0);
	    }
	    if (vacmViewTable[i+1]) {
		last = (vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength
			!= vacmViewTable[i+1]->_vacmViewTreeFamilyViewNameLength)
		    || (memcmp(vacmViewTable[i]->vacmViewTreeFamilyViewName,
			       vacmViewTable[i+1]->vacmViewTreeFamilyViewName,
			       vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength) != 0);
	    }
	    show_snmp_vacm_view(interp->result, vacmViewTable[i], new, last);
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

	{ "show snmp engine", NULL,
	  "information about the SNMP engine",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_snmp_engine },

	{ "show snmp resources", NULL,
	  "information about the SNMP resources",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_snmp_resources },

	{ "show snmp vacm groups", NULL,
	  "information about the VACM groups",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_snmp_vacm_groups },

	{ "show snmp vacm access", NULL,
	  "information about the VACM access rules",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_snmp_vacm_access },

	{ "show snmp vacm views", NULL,
	  "information about the VACM views",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_snmp_vacm_views },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t snmp_mode = {
	"snmp",
	"scli mode to display and configure snmp specific information",
	cmds
    };
    
    scli_register_mode(interp, &snmp_mode);
}
