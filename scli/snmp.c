/* 
 * snmp.c -- scli snmp mode implementation
 *
 * Copyright (C) 2001-2002 Juergen Schoenwaelder
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
#include "snmp-user-based-sm-mib.h"
#include "snmp-target-mib.h"
#include "snmp-notification-mib.h"

#include "snmp-view-based-acm-mib-proc.h"


static GSnmpEnum const mp_model[] = {
    { 0,	"SNMPv1" },
    { 1,	"SNMPv2c" },
    { 2,	"SNMPv2u/*" },
    { 3,	"SNMPv3" },
    { 0, NULL }
};



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



static guint32 const usmNoAuthProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMNOAUTHPROTOCOL };
static guint32 const usmHMACMD5AuthProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMHMACMD5AUTHPROTOCOL };
static guint32 const usmHMACSHAAuthProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMHMACSHAAUTHPROTOCOL };
static guint32 const usmNoPrivProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMNOPRIVPROTOCOL };
static guint32 const usmDESPrivProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMDESPRIVPROTOCOL };

GSnmpIdentity const sec_proto_identities[] = {
    { usmNoAuthProtocol,
      sizeof(usmNoAuthProtocol)/sizeof(guint32),
      "none" },
    { usmHMACMD5AuthProtocol,
      sizeof(usmHMACMD5AuthProtocol)/sizeof(guint32),
      "HMAC-MD5" },
    { usmHMACSHAAuthProtocol,
      sizeof(usmHMACSHAAuthProtocol)/sizeof(guint32),
      "HMAC-SHA" },
    { usmNoPrivProtocol,
      sizeof(usmNoPrivProtocol)/sizeof(guint32),
      "none" },
    { usmDESPrivProtocol,
      sizeof(usmDESPrivProtocol)/sizeof(guint32),
      "DES" },
    { 0, 0, NULL }
};



static int
creatable(gint32 *storage)
{
    /* check whether a row is actually creatable */
    return (storage && (*storage != 4) && (*storage != 5));
}



static int
create_snmp_vacm_member(scli_interp_t *interp, int argc, char **argv)
{
    gint32 model = 0;	/* "any" */

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc < 3 || argc > 4) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (strlen(argv[1]) < 1 || strlen(argv[1]) > 32) {
	return SCLI_SYNTAX_VALUE;
    }

    if (strlen(argv[2]) < 1 || strlen(argv[2]) > 32) {
	return SCLI_SYNTAX_VALUE;
    }

    if (argc == 4) {
	if (! gsnmp_enum_get_number(security_model, argv[3], &model)) {
	    return SCLI_SYNTAX_VALUE;
	}
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }
    
    snmp_view_based_acm_mib_proc_create_member(interp->peer,
					       argv[1], argv[2], model);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    return SCLI_OK;
}



static int
delete_snmp_vacm_member(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmGroupTable;
    regex_t _regex_group, *regex_group = NULL;
    regex_t _regex_name, *regex_name = NULL;
    gint32 model = 0;	/* "any" */
    int i, status;
    char *s;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc < 3 || argc > 4) {
	return SCLI_SYNTAX_NUMARGS;
    }

    regex_name = &_regex_name;
    if (regcomp(regex_name, argv[1], interp->regex_flags) != 0) {
	return SCLI_SYNTAX_REGEXP;
    }

    regex_group = &_regex_group;
    if (regcomp(regex_group, argv[2], interp->regex_flags) != 0) {
	if (regex_name) regfree(regex_name);
	return SCLI_SYNTAX_REGEXP;
    }

    if (argc == 4) {
	if (! gsnmp_enum_get_number(security_model, argv[3], &model)) {
	    if (regex_name) regfree(regex_name);
	    if (regex_group) regfree(regex_group);
	    return SCLI_SYNTAX_VALUE;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_name) regfree(regex_name);
	if (regex_group) regfree(regex_group);
	return SCLI_OK;
    }

    snmp_view_based_acm_mib_get_vacmSecurityToGroupTable(interp->peer,
							 &vacmGroupTable, 0);
    if (interp->peer->error_status) {
	if (regex_name) regfree(regex_name);
	if (regex_group) regfree(regex_group);
	return SCLI_SNMP;
    }

    if (vacmGroupTable) {
	for (i = 0; vacmGroupTable[i]; i++) {
	    if (! vacmGroupTable[i]->vacmGroupName) {
		continue;
	    }
	    if (model && (vacmGroupTable[i]->vacmSecurityModel != model)) {
		continue;
	    }
	    s = g_strdup_printf("%.*s",
				vacmGroupTable[i]->_vacmSecurityNameLength,
				vacmGroupTable[i]->vacmSecurityName);
	    status = regexec(regex_name, s, (size_t) 0, NULL, 0);
	    g_free(s);
	    if (status != 0) continue;
	    s = g_strdup_printf("%.*s",
				vacmGroupTable[i]->_vacmGroupNameLength,
				vacmGroupTable[i]->vacmGroupName);
	    status = regexec(regex_group, s, (size_t) 0, NULL, 0);
	    g_free(s);
	    if (status != 0) continue;
	    snmp_view_based_acm_mib_proc_delete_member(interp->peer,
			       vacmGroupTable[i]->vacmSecurityName,
			       vacmGroupTable[i]->_vacmSecurityNameLength,
			       vacmGroupTable[i]->vacmGroupName,
			       vacmGroupTable[i]->_vacmGroupNameLength, model);
	}
    }
    
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (vacmGroupTable)
	snmp_view_based_acm_mib_free_vacmSecurityToGroupTable(vacmGroupTable);
    
    if (regex_name) regfree(regex_name);
    if (regex_group) regfree(regex_group);
    
    return SCLI_OK;
}



static void
fmt_snmp_engine(GString *s,
		snmp_framework_mib_snmpEngine_t *snmpEngine,
		snmpv2_mib_snmp_t *snmp)
{
    int const indent = 22;
    int i;
    const char *e;
    
    if (snmpEngine) {
	if (snmpEngine->snmpEngineID) {
	    guint32 enterp = 0;
	    const scli_vendor_t *vendor;
	    g_string_sprintfa(s, "%-*s", indent, "Engine Identifier:");
	    for (i = 0; i < snmpEngine->_snmpEngineIDLength; i++) {
		g_string_sprintfa(s, "%02x", snmpEngine->snmpEngineID[i]);
	    }
	    g_string_append(s, "\n");
	    enterp = (enterp << 8) + (snmpEngine->snmpEngineID[0] & 0x7F);
	    enterp = (enterp << 8) + snmpEngine->snmpEngineID[1];
	    enterp = (enterp << 8) + snmpEngine->snmpEngineID[2];
	    enterp = (enterp << 8) + snmpEngine->snmpEngineID[3];
	    vendor = scli_get_vendor(enterp);
	    if (vendor && vendor->name) {
		g_string_sprintfa(s, "%-*s%s", indent, "Engine Vendor:",
				  vendor->name);
		if (vendor->url) {
		    g_string_sprintfa(s, " <%s>", vendor->url);
		}
		g_string_append(s, "\n");
	    }
	}
	if (snmpEngine->snmpEngineTime) {
	    g_string_sprintfa(s, "%-*s%u seconds\n",
			      indent, "Engine Uptime:",
			      *(snmpEngine->snmpEngineTime));
	}
	if (snmpEngine->snmpEngineBoots) {
	    g_string_sprintfa(s, "%-*s%u\n",
			      indent, "Number of Boots:",
			      *(snmpEngine->snmpEngineBoots));
	}
	if (snmpEngine->snmpEngineMaxMessageSize) {
	    g_string_sprintfa(s, "%-*s%u byte\n",
			      indent, "Maximum Message Size:",
			      *(snmpEngine->snmpEngineMaxMessageSize));
	}
    }
    if (snmp) {
	e = fmt_enum(snmpv2_mib_enums_snmpEnableAuthenTraps,
		     snmp->snmpEnableAuthenTraps);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n",
			      indent, "Authentication Traps:", e);
	}
    }
}



static int
show_snmp_engine(scli_interp_t *interp, int argc, char **argv)
{
    snmp_framework_mib_snmpEngine_t *snmpEngine;
    snmpv2_mib_snmp_t *snmp;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_framework_mib_get_snmpEngine(interp->peer, &snmpEngine, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    snmpv2_mib_get_snmp(interp->peer, &snmp, SNMPV2_MIB_SNMPENABLEAUTHENTRAPS);

    fmt_snmp_engine(interp->result, snmpEngine, snmp);
    
    if (snmpEngine) snmp_framework_mib_free_snmpEngine(snmpEngine);
    if (snmp) snmpv2_mib_free_snmp(snmp);
    
    return SCLI_OK;
}



static void
fmt_snmp_resource(GString *s,
		  snmpv2_mib_sysOREntry_t *sysOREntry,
		  snmpv2_mib_system_t *system)
{
    int i;
    int const indent = 14;
    
    g_string_sprintfa(s, "%-*s%d\n", indent, "MIB Resource:",
		      sysOREntry->sysORIndex);
    if (sysOREntry->sysORUpTime && system && system->sysUpTime) {
	guint32 dsecs = *system->sysUpTime - *sysOREntry->sysORUpTime;
	g_string_sprintfa(s, "%-*s%s\n", indent, "Last Change:",
			  fmt_timeticks(dsecs));
    }
    
    if (sysOREntry->sysORDescr) {
	fmt_display_string(s, indent, "Description:",
			   (int) sysOREntry->_sysORDescrLength,
			   sysOREntry->sysORDescr);
    }
    if (sysOREntry->sysORID && sysOREntry->_sysORIDLength) {
	g_string_sprintfa(s, "%-*s", indent, "Capabilities:");
	for (i = 0; i < sysOREntry->_sysORIDLength; i++) {
	    g_string_sprintfa(s, "%s%u", i ? "." : "",
			      sysOREntry->sysORID[i]);
	}
	g_string_append(s, "\n");
    }
}



static int
show_snmp_resources(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_sysOREntry_t **sysORTable;
    snmpv2_mib_system_t *system;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmpv2_mib_get_sysORTable(interp->peer, &sysORTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    snmpv2_mib_get_system(interp->peer, &system, SNMPV2_MIB_SYSUPTIME);
        
    if (sysORTable) {
	for (i = 0; sysORTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_snmp_resource(interp->result, sysORTable[i], system);
	}
    }
    
    if (sysORTable) snmpv2_mib_free_sysORTable(sysORTable);
    if (system) snmpv2_mib_free_system(system);
    
    return SCLI_OK;
}



static void
fmt_snmp_vacm_member(GString *s,
     snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmGroupEntry,
		    int sec_name_width, int sec_group_width)
{
    char const *model;
    
    fmt_storage_type(s, vacmGroupEntry->vacmSecurityToGroupStorageType);
    fmt_row_status(s, vacmGroupEntry->vacmSecurityToGroupStatus);
    
    model = gsnmp_enum_get_label(security_model,
				 vacmGroupEntry->vacmSecurityModel);
    g_string_sprintfa(s, "  %-3s %-*.*s",
		      model ? model : "", sec_name_width,
		      (int) vacmGroupEntry->_vacmSecurityNameLength,
		      vacmGroupEntry->vacmSecurityName);
    g_string_sprintfa(s, " %-*.*s\n", sec_group_width,
		      (int) vacmGroupEntry->_vacmGroupNameLength,
		      vacmGroupEntry->vacmGroupName);
}



static int
show_snmp_vacm_member(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmGroupTable;
    int sec_name_width = 8;
    int sec_group_width = 8;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_view_based_acm_mib_get_vacmSecurityToGroupTable(interp->peer,
							 &vacmGroupTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vacmGroupTable) {
	for (i = 0; vacmGroupTable[i]; i++) {
	    if (vacmGroupTable[i]->_vacmSecurityNameLength > sec_name_width)
		sec_name_width = vacmGroupTable[i]->_vacmSecurityNameLength;
	    if (vacmGroupTable[i]->_vacmGroupNameLength > sec_group_width)
		sec_group_width = vacmGroupTable[i]->_vacmGroupNameLength;
	}
	g_string_sprintfa(interp->header, "ROW MOD %-*s GROUP",
			  sec_name_width, "NAME");
	for (i = 0; vacmGroupTable[i]; i++) {
	    fmt_snmp_vacm_member(interp->result, vacmGroupTable[i],
				 sec_name_width, sec_group_width);
	}
    }

    if (vacmGroupTable)
	snmp_view_based_acm_mib_free_vacmSecurityToGroupTable(vacmGroupTable);
    
    return SCLI_OK;
}



static void
fmt_snmp_vacm_access(GString *s,
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
show_snmp_vacm_access(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessTable;
    int group_width = 5;
    int cntxt_width = 3;
    int read_width = 5;
    int write_width = 5;
    int notify_width = 5;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_view_based_acm_mib_get_vacmAccessTable(interp->peer,
						&vacmAccessTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
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
	g_string_sprintfa(interp->header,
			  "ROW %-*s MOD LVL %-*s %-8s %-*s %-*s %-*s",
			  group_width, "GROUP",
			  cntxt_width, "CTX",
			  "MATCH",
			  read_width, "READ",
			  write_width, "WRITE",
			  notify_width, "NOTIFY");
	for (i = 0; vacmAccessTable[i]; i++) {
	    fmt_snmp_vacm_access(interp->result, vacmAccessTable[i],
				 group_width, cntxt_width,
				 read_width, write_width, notify_width);
	}
    }

    if (vacmAccessTable)
	snmp_view_based_acm_mib_free_vacmAccessTable(vacmAccessTable);
    
    return SCLI_OK;
}



static void
fmt_snmp_vacm_view(GString *s,
	   snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewEntry,
		   int view_width)
{
    char const *type = NULL;
    int i;

    if (vacmViewEntry->vacmViewTreeFamilySubtree
	&& vacmViewEntry->vacmViewTreeFamilyMask
	&& vacmViewEntry->vacmViewTreeFamilyType) {

	fmt_storage_type(s, vacmViewEntry->vacmViewTreeFamilyStorageType);
	fmt_row_status(s, vacmViewEntry->vacmViewTreeFamilyStatus);

	g_string_sprintfa(s, "  %-*.*s", view_width,
			  (int) vacmViewEntry->_vacmViewTreeFamilyViewNameLength,
			  vacmViewEntry->vacmViewTreeFamilyViewName);

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
show_snmp_vacm_views(scli_interp_t *interp, int argc, char **argv)
{
    snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTable;
    int view_width = 8;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_view_based_acm_mib_get_vacmViewTreeFamilyTable(interp->peer,
							&vacmViewTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vacmViewTable) {
	for (i = 0; vacmViewTable[i]; i++) {
	    if (vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength > view_width) {
		view_width = vacmViewTable[i]->_vacmViewTreeFamilyViewNameLength;
	    }
	}
	g_string_sprintfa(interp->header, "ROW %-*s TYPE PREFIX",
			  view_width, "VIEW");
	for (i = 0; vacmViewTable[i]; i++) {
	    fmt_snmp_vacm_view(interp->result, vacmViewTable[i], view_width);
	}
    }

    if (vacmViewTable)
	snmp_view_based_acm_mib_free_vacmViewTreeFamilyTable(vacmViewTable);
    
    return SCLI_OK;
}



static void
fmt_snmp_usm_user(GString *s, snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry,
		  int user_width, int sec_width)
{
    const char *label;
    
    fmt_storage_type(s, usmUserEntry->usmUserStorageType);
    fmt_row_status(s, usmUserEntry->usmUserStatus);

    g_string_sprintfa(s, "  %-*.*s", user_width,
		      (int) usmUserEntry->_usmUserNameLength,
		      usmUserEntry->usmUserName);

    if (usmUserEntry->usmUserSecurityName) {
	g_string_sprintfa(s, " %-*.*s", sec_width,
			  (int) usmUserEntry->_usmUserSecurityNameLength,
			  usmUserEntry->usmUserSecurityName);
    } else {
	g_string_sprintfa(s, " %*s", sec_width, "");
    }

    label = gsnmp_identity_get_label(sec_proto_identities,
				    usmUserEntry->usmUserAuthProtocol,
				    usmUserEntry->_usmUserAuthProtocolLength);
    if (label) {
	g_string_sprintfa(s, " %-8s", label ? label : "");
    }

    label = gsnmp_identity_get_label(sec_proto_identities,
				    usmUserEntry->usmUserPrivProtocol,
				    usmUserEntry->_usmUserPrivProtocolLength);
    if (label) {
	g_string_sprintfa(s, " %-8s", label ? label : "");
    }

    g_string_append(s, "\n");
}



static int
show_snmp_usm_users(scli_interp_t *interp, int argc, char **argv)
{
    snmp_user_based_sm_mib_usmUserEntry_t **usmUserTable = NULL;
    int i, user_width = 8, sec_width = 8;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_user_based_sm_mib_get_usmUserTable(interp->peer, &usmUserTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (usmUserTable) {
	for (i = 0; usmUserTable[i]; i++) {
	    if (usmUserTable[i]->_usmUserNameLength > user_width) {
		user_width = usmUserTable[i]->_usmUserNameLength;
	    }
	    if (usmUserTable[i]->_usmUserSecurityNameLength > sec_width) {
		sec_width = usmUserTable[i]->_usmUserSecurityNameLength;
	    }
	}
	g_string_sprintfa(interp->header, "ROW %-*s %-*s AUTH     PRIV",
			  user_width, "USER", sec_width, "NAME");
	for (i = 0; usmUserTable[i]; i++) {
	    fmt_snmp_usm_user(interp->result, usmUserTable[i],
			      user_width, sec_width);
	}
    }

    if (usmUserTable) {
	snmp_user_based_sm_mib_free_usmUserTable(usmUserTable);
    }

    return SCLI_OK;
}



static void
fmt_snmp_target_address(GString *s,
			snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetEntry,
		int name_width, int tag_width, int addr_width, int para_width)
{
    const char *e;
    
    fmt_storage_type(s, snmpTargetEntry->snmpTargetAddrStorageType);
    fmt_row_status(s, snmpTargetEntry->snmpTargetAddrRowStatus);

    g_string_sprintfa(s, "  %-*.*s", name_width,
		      (int) snmpTargetEntry->_snmpTargetAddrNameLength,
		      snmpTargetEntry->snmpTargetAddrName);

    e = fmt_tdomain(snmpTargetEntry->snmpTargetAddrTDomain,
		    snmpTargetEntry->_snmpTargetAddrTDomainLength);
    g_string_sprintfa(s, " %-6s", e ? e : "?");

    e = fmt_taddress(snmpTargetEntry->snmpTargetAddrTDomain,
		     snmpTargetEntry->_snmpTargetAddrTDomainLength,
		     snmpTargetEntry->snmpTargetAddrTAddress,
		     snmpTargetEntry->_snmpTargetAddrTAddressLength);
    g_string_sprintfa(s, " %-*s", addr_width, e ? e : "?");

    if (snmpTargetEntry->snmpTargetAddrTimeout) {
	g_string_sprintfa(s, "%6d",
			  *snmpTargetEntry->snmpTargetAddrTimeout * 10);
    } else {
	g_string_sprintfa(s, "%6s", "");
    }

    if (snmpTargetEntry->snmpTargetAddrRetryCount) {
	g_string_sprintfa(s, "%6d",
			  *snmpTargetEntry->snmpTargetAddrRetryCount);
    } else {
	g_string_sprintfa(s, "%6s", "");
    }
    
    if (snmpTargetEntry->snmpTargetAddrParams) {
	g_string_sprintfa(s, " %-*.*s", para_width,
			  (int) snmpTargetEntry->_snmpTargetAddrParamsLength,
			  snmpTargetEntry->snmpTargetAddrParams);
    } else {
	g_string_sprintfa(s, " %*s", para_width, "");
    }

    if (snmpTargetEntry->snmpTargetAddrTagList) {
	g_string_sprintfa(s, " %-*.*s", tag_width,
			  (int) snmpTargetEntry->_snmpTargetAddrTagListLength,
			  snmpTargetEntry->snmpTargetAddrTagList);
    } else {
	g_string_sprintfa(s, " %*s", tag_width, "");
    }

    g_string_append(s, "\n");
}



static int
show_snmp_target_addresses(scli_interp_t *interp, int argc, char **argv)
{
    snmp_target_mib_snmpTargetAddrEntry_t **snmpTargetTable = NULL;
    int name_width = 8, tag_width = 8, addr_width = 8, para_width = 8;
    const char *e;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_target_mib_get_snmpTargetAddrTable(interp->peer, &snmpTargetTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (snmpTargetTable) {
	for (i = 0; snmpTargetTable[i]; i++) {
	    if (snmpTargetTable[i]->_snmpTargetAddrNameLength > name_width) {
		name_width = snmpTargetTable[i]->_snmpTargetAddrNameLength;
	    }
	    if (snmpTargetTable[i]->_snmpTargetAddrTagListLength > tag_width) {
		tag_width = snmpTargetTable[i]->_snmpTargetAddrTagListLength;
	    }
	    if (snmpTargetTable[i]->_snmpTargetAddrParamsLength > para_width) {
		para_width = snmpTargetTable[i]->_snmpTargetAddrParamsLength;
	    }
	    e = fmt_taddress(snmpTargetTable[i]->snmpTargetAddrTDomain,
			     snmpTargetTable[i]->_snmpTargetAddrTDomainLength,
			     snmpTargetTable[i]->snmpTargetAddrTAddress,
			     snmpTargetTable[i]->_snmpTargetAddrTAddressLength);
	    if (e && strlen(e) > addr_width) {
		addr_width = strlen(e);
	    }
	}
	g_string_sprintfa(interp->header,
			  "ROW %-*s DOMAIN %-*s TMOUT RETRY %-*s %-*s",
			  name_width, "TARGET",
			  addr_width, "ADDRESS",
			  para_width, "PARAMS",
			  tag_width, "TAGS");
	for (i = 0; snmpTargetTable[i]; i++) {
	    fmt_snmp_target_address(interp->result, snmpTargetTable[i],
			    name_width, tag_width, addr_width, para_width);
	}
    }

    if (snmpTargetTable) {
	snmp_target_mib_free_snmpTargetAddrTable(snmpTargetTable);
    }

    return SCLI_OK;
}



static void
fmt_snmp_target_parameter(GString *s,
			  snmp_target_mib_snmpTargetParamsEntry_t *snmpParamsEntry,
			  int para_width, int name_width)
{
    const char *e;
    
    fmt_storage_type(s, snmpParamsEntry->snmpTargetParamsStorageType);
    fmt_row_status(s, snmpParamsEntry->snmpTargetParamsRowStatus);

    g_string_sprintfa(s, "  %-*.*s", para_width,
		      (int) snmpParamsEntry->_snmpTargetParamsNameLength,
		      snmpParamsEntry->snmpTargetParamsName);

    if (snmpParamsEntry->snmpTargetParamsSecurityName) {
	g_string_sprintfa(s, " %-*.*s", name_width,
			  (int) snmpParamsEntry->_snmpTargetParamsSecurityNameLength,
			  snmpParamsEntry->snmpTargetParamsSecurityName);
    } else {
	g_string_sprintfa(s, " %*s", name_width, "");
    }

    e = fmt_enum(security_model, snmpParamsEntry->snmpTargetParamsSecurityModel);
    g_string_sprintfa(s, " %-3s", e ? e : "");

    e = fmt_enum(security_level, snmpParamsEntry->snmpTargetParamsSecurityLevel);
    g_string_sprintfa(s, " %-3s", e ? e : "");

    e = fmt_enum(mp_model, snmpParamsEntry->snmpTargetParamsMPModel);
    g_string_sprintfa(s, " %s", e ? e : "");

    g_string_append(s, "\n");
}



static int
show_snmp_target_parameters(scli_interp_t *interp, int argc, char **argv)
{
    snmp_target_mib_snmpTargetParamsEntry_t **snmpParamsTable = NULL;
    int name_width = 8, para_width = 8;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_target_mib_get_snmpTargetParamsTable(interp->peer, &snmpParamsTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (snmpParamsTable) {
	for (i = 0; snmpParamsTable[i]; i++) {
	    if (snmpParamsTable[i]->_snmpTargetParamsNameLength > para_width) {
		para_width = snmpParamsTable[i]->_snmpTargetParamsNameLength;
	    }
	    if (snmpParamsTable[i]->_snmpTargetParamsSecurityNameLength > name_width) {
		name_width = snmpParamsTable[i]->_snmpTargetParamsSecurityNameLength;
	    }
	}
	g_string_sprintfa(interp->header,
			  "ROW %-*s %-*s MOD LVL MP",
			  para_width, "PARAMS",
			  name_width, "NAME");
	for (i = 0; snmpParamsTable[i]; i++) {
	    fmt_snmp_target_parameter(interp->result, snmpParamsTable[i],
				      para_width, name_width);
	}
    }

    if (snmpParamsTable) {
	snmp_target_mib_free_snmpTargetParamsTable(snmpParamsTable);
    }

    return SCLI_OK;
}



static void
fmt_snmp_notification_target(GString *s,
		       snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry,
		       int name_width)
{
    const char *e;
    
    fmt_storage_type(s, snmpNotifyEntry->snmpNotifyStorageType);
    fmt_row_status(s, snmpNotifyEntry->snmpNotifyRowStatus);

    g_string_sprintfa(s, "  %-*.*s", name_width,
		      (int) snmpNotifyEntry->_snmpNotifyNameLength,
		      snmpNotifyEntry->snmpNotifyName);

    e = fmt_enum(snmp_notification_mib_enums_snmpNotifyType, snmpNotifyEntry->snmpNotifyType);
    g_string_sprintfa(s, " %-6s", e ? e : "");

    if (snmpNotifyEntry->snmpNotifyTag) {
	g_string_sprintfa(s, " %.*s",
			  snmpNotifyEntry->_snmpNotifyTagLength,
			  snmpNotifyEntry->snmpNotifyTag);
    }

    g_string_append(s, "\n");
}



static int
show_snmp_notification_targets(scli_interp_t *interp, int argc, char **argv)
{
    snmp_notification_mib_snmpNotifyEntry_t **snmpNotifyTable = NULL;
    int name_width = 8;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp_notification_mib_get_snmpNotifyTable(interp->peer, &snmpNotifyTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (snmpNotifyTable) {
	for (i = 0; snmpNotifyTable[i]; i++) {
	    if (snmpNotifyTable[i]->_snmpNotifyNameLength > name_width) {
		name_width = snmpNotifyTable[i]->_snmpNotifyNameLength;
	    }
	}
	g_string_sprintfa(interp->header,
			  "ROW %-*s TYPE   TAG",
			  name_width, "NAME");
	for (i = 0; snmpNotifyTable[i]; i++) {
	    fmt_snmp_notification_target(interp->result, snmpNotifyTable[i],
					 name_width);
	}
    }

    if (snmpNotifyTable) {
	snmp_notification_mib_free_snmpNotifyTable(snmpNotifyTable);
    }

    return SCLI_OK;
}



static int
set_snmp_authentication_traps(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_snmp_t *snmp = NULL;
    gint32 value;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (! gsnmp_enum_get_number(snmpv2_mib_enums_snmpEnableAuthenTraps,
				argv[1], &value)) {
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmp = snmpv2_mib_new_snmp();
    snmp->snmpEnableAuthenTraps = &value;
    snmpv2_mib_set_snmp(interp->peer, snmp, SNMPV2_MIB_SNMPENABLEAUTHENTRAPS);
    snmpv2_mib_free_snmp(snmp);

    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
dump_snmp(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_snmp_t *snmp;
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmGroupTable;
    const char *e;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    snmpv2_mib_get_snmp(interp->peer, &snmp, SNMPV2_MIB_SNMPENABLEAUTHENTRAPS);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (snmp) {
	e = fmt_enum(snmpv2_mib_enums_snmpEnableAuthenTraps,
		     snmp->snmpEnableAuthenTraps);
	if (e) {
	    g_string_sprintfa(interp->result,
			      "set snmp authentication traps %s\n", e);
	}
    }

    snmp_view_based_acm_mib_get_vacmSecurityToGroupTable(interp->peer,
							 &vacmGroupTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vacmGroupTable) {
	g_string_sprintfa(interp->result, "delete snmp vacm member . .\n");
	for (i = 0; vacmGroupTable[i]; i++) {
	    if (! creatable(vacmGroupTable[i]->vacmSecurityToGroupStorageType)) {
		continue;
	    }
	    e  = gsnmp_enum_get_label(security_model,
				      vacmGroupTable[i]->vacmSecurityModel);
	    g_string_sprintfa(interp->result,
		      "create snmp vacm member \"%.*s\" \"%.*s\" \"%s\"\n",
			      vacmGroupTable[i]->_vacmSecurityNameLength,
			      vacmGroupTable[i]->vacmSecurityName,
			      vacmGroupTable[i]->_vacmSecurityNameLength,
			      vacmGroupTable[i]->vacmSecurityName,
			      e ? e : "");
	}
    }

    if (snmp) snmpv2_mib_free_snmp(snmp);

    if (vacmGroupTable)
	snmp_view_based_acm_mib_free_vacmSecurityToGroupTable(vacmGroupTable);
    
    return SCLI_OK;
}



void
scli_init_snmp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "create snmp vacm member", "<name> <group> [<model>]",
	  "The create snmp vacm member commands can be used to assign\n"
	  "new members (security names) to vacm groups. New groups are\n"
	  "created if they do not exist.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  create_snmp_vacm_member },

	{ "delete snmp vacm member", "<regex-name> <regex-group> [<model>]",
	  "The delete snmp vacm member commands can be used to delete\n"
	  "members (security names) from vacm groups. Groups are deleted\n"
	  "if the last member is deleted.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  delete_snmp_vacm_member },

	{ "set snmp authentication traps", "<status>",
	  "The set snmp authentication traps command controls whether the\n"
	  "SNMP engine generates authentication failure notifications.\n"
	  "The <value> parameter must be one of the strings \"enabled\"\n"
	  "or \"disabled\".",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  set_snmp_authentication_traps },

	{ "show snmp engine", NULL,
	  "The show snmp engine command displays information about the\n"
	  "SNMP protocol engine such as the number of boots, the current\n"
	  "time relative to the last boot and the maximum message size.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_engine },

	{ "show snmp resources", NULL,
	  "The show snmp resources command displays information about the\n"
	  "MIB resources supported by the SNMP agent.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_resources },

	{ "show snmp vacm member", NULL,
	  "The show snmp vacm member command displays the mapping of\n"
	  "security names to group names. The command generates a table\n"
	  "with the following columns:\n"
	  "\n"
	  "  ROW    row storage type and status\n"
	  "  MOD    security model\n"
	  "  NAME   member name (security name)\n"
	  "  GROUP  name of the vacm group",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_vacm_member },

	{ "show snmp vacm access", NULL,
	  "The show snmp vacm access command display the access control\n"
	  "rules for the security groups. The command generates a table\n"
	  "with the following columns:\n"
	  "\n"
	  "  ROW    row storage type and status\n"
	  "  GROUP  security group name\n"
	  "  MOD    security model\n"
	  "  LVL    security level (--, a-, ap)\n"
	  "  CTX    context name\n"
	  "  MATCH  match (exact or prefix)\n"
	  "  READ   view name for read access\n"
	  "  WRITE  view name for write access\n"
	  "  NOTIFY view name for notification",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_vacm_access },

	{ "show snmp vacm views", NULL,
	  "The show snmp vacm views command displays MIB view definitions.\n"
	  "The command generates a table with the following columns:\n"
	  "\n"
	  "  ROW    row storage type and status\n"
	  "  VIEW   view name\n"
	  "  TYPE   access to the view subtree (incl/excl)\n"
	  "  PREFIX object identifier wildcard prefix",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_vacm_views },

	{ "show snmp usm users", NULL,
	  "The show snmp usm users command displays the configured users.\n"
	  "The command generates a table with the following columns:\n"
	  "\n"
	  "  ROW    row storage type and status\n"
	  "  USER   USM user name\n"
	  "  NAME   security name of the USM user\n"
	  "  AUTH   authentication protocol\n"
	  "  PRIV   privacy protocol",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_usm_users },

	{ "show snmp target addresses", NULL,
	  "The show snmp target addresses command displays information\n"
	  "about the configured SNMP target addresses. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  ROW      row storage type and status\n"
	  "  TARGET   target name\n"
	  "  DOMAIN   transport domain\n"
	  "  ADDRESS  transport address\n"
	  "  TMOUT    timeout value in ms\n"
	  "  RETRY    number of retries\n"
	  "  PARAMS   associated parameters\n"
	  "  TAGS     tag list",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_target_addresses },

	{ "show snmp target parameters", NULL,
	  "The show snmp target parameters command displays information\n"
	  "about the configured SNMP target parameters. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  ROW      row storage type and status\n"
	  "  PARAMS   parameter name\n"
	  "  NAME     security name",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_target_parameters },

	{ "show snmp notification targets", NULL,
	  "The show snmp notification targets command displays information\n"
	  "about the configured SNMP notification targets. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  ROW      row storage type and status\n"
	  "  NAME     notification target name\n"
	  "  TYPE     notification type\n"
	  "  TAG      tag reference to targets",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_snmp_notification_targets },

	{ "dump snmp", NULL,
	  "The dump snmp command generates a sequence of scli commands\n"
	  "which can be used to restore the engine configuration.\n",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  dump_snmp },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t snmp_mode = {
	"snmp",
	
	"The snmp scli mode is based on the SNMPv2-MIB as published\n"
	"in RFC 1907, the SNMP-FRAMEWORK-MIB as published in RFC 2571,\n"
	"the SNMP-USER-BASED-SM-MIB as published in RFC 2574, the\n"
	"SNMP-VIEW-BASED-ACM-MIB as published in RFC 2575, the\n"
	"SNMP-TARGET-MIB as published in RFC 2573, and the\n"
	"SNMP-NOTIFICATION-MIB as published in RFC 2573.",
	cmds
    };
    
    scli_register_mode(interp, &snmp_mode);
}
