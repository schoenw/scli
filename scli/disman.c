/* 
 * disman.c -- scli disman mode implementation
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

#include "disman-script-mib.h"


static guint32 const oid_javabc[] = { 1, 3, 6, 1, 2, 1, 73, 1 };
static guint32 const oid_tcl[] = { 1, 3, 6, 1, 2, 1, 73, 2 };
static guint32 const oid_perl[] = { 1, 3, 6, 1, 2, 1, 73, 3 };
static guint32 const oid_scheme[] = { 1, 3, 6, 1, 2, 1, 73, 4 };
static guint32 const oid_srsl[] = { 1, 3, 6, 1, 2, 1, 73, 5 };
static guint32 const oid_psl[] = { 1, 3, 6, 1, 2, 1, 73, 6 };
static guint32 const oid_smsl[] = { 1, 3, 6, 1, 2, 1, 73, 7 };

typedef struct lang {
    guint32 const *oid;
    gsize const oidlen;
    char const *name;
} lang_t;

static lang_t const languages[] = {
    { oid_javabc,	sizeof(oid_javabc) / sizeof(guint32),	"Java" },
    { oid_tcl,		sizeof(oid_tcl) / sizeof(guint32),	"Tcl" },
    { oid_perl,		sizeof(oid_perl) / sizeof(guint32),	"Perl" },
    { oid_scheme,	sizeof(oid_scheme) / sizeof(guint32),	"Scheme" },
    { oid_srsl,		sizeof(oid_srsl) / sizeof(guint32),	"SRSL" },
    { oid_psl,		sizeof(oid_psl) / sizeof(guint32),	"PSL" },
    { oid_smsl,		sizeof(oid_smsl) / sizeof(guint32),	"SMSL" },
    { NULL, 0, NULL }
};



static char const *
get_lang_name(smLangEntry_t *smLangEntry)
{
    int l;
    
    for (l = 0; languages[l].oidlen; l++) {
	if (languages[l].oidlen == smLangEntry->_smLangLanguageLength) {
	    if (memcmp(languages[l].oid, smLangEntry->smLangLanguage,
		       languages[l].oidlen) == 0) {
		return languages[l].name;
	    }
	}
    }

    return NULL;
}



static void
fmt_script_admin_status(GString *s, gint32 *status)
{
    static stls_table_t const script_admin_states[] = {
	{ 1, "e" },	/* enabled */
	{ 2, "d" },	/* disabled */
	{ 3, "t" },	/* editing */
	{ 0, NULL }
    };

    fmt_enum(s, 1, script_admin_states, status);
}



static void
fmt_script_oper_status(GString *s, gint32 *status)
{
    static stls_table_t const script_oper_states[] = {
	{ 1, "e" },	/* enabled */
	{ 2, "d" },	/* disabled */
	{ 3, "t" },	/* editing */
	{ 4, "r" },	/* retrieving */
	{ 5, "c" },	/* compiling */
	{ 6, "n" },	/* noSuchScript */
	{ 7, "a" },	/* accessDenied */
	{ 8, "w" },	/* wrongLanguage */
	{ 9, "v" },	/* wrongVersion */
	{ 10, "f" },	/* compilationFailed */
	{ 11, "o" },	/* noResourcesLeft */
	{ 12, "u" },	/* unknownProtocol */
	{ 13, "p" },	/* protocolFailure */
	{ 14, "g" },	/* genericError */
	{ 0, NULL }
    };

    fmt_enum(s, 1, script_oper_states, status);
}



static void
fmt_storage_type(GString *s, gint32 *storage)
{
    static stls_table_t const storage_types[] = {
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
    static stls_table_t const row_states[] = {
	{ 1, "a" },	/* active */
	{ 2, "s" },	/* notInService */
	{ 3, "r" },	/* notReady */
	{ 0, NULL }
    };

    fmt_enum(s, 1, row_states, status);
}



static void
fmt_last_change(GString *s, guchar *data, gsize len)
{
    static char const *months[] = {
	"---",
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    int year;
    
    if (! data || (len != 8 && len != 11)) {
	g_string_sprintfa(s, "--- -- ----- ");
	return;
    }

    year = (data[0] << 8) + data[1];

    g_string_sprintfa(s, "%3s %2u  %4u ",
		      months[data[2] < 13 ? data[2] : 0], data[3], year);
}



static void
show_extension(GString *s, smExtsnEntry_t *smExtsnEntry)
{
    int const indent = 12;
    if (smExtsnEntry->smExtsnDescr) {
	g_string_sprintfa(s, "%-*s ", indent, "  Extension:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smExtsnEntry->_smExtsnDescrLength,
			  smExtsnEntry->smExtsnDescr);
	
    }
    if (smExtsnEntry->smExtsnVersion) {
	g_string_sprintfa(s, "%-*s ", indent, "  Version:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smExtsnEntry->_smExtsnVersionLength,
			  smExtsnEntry->smExtsnVersion);
    }
    if (smExtsnEntry->smExtsnRevision && smExtsnEntry->_smExtsnRevisionLength) {
	g_string_sprintfa(s, "%-*s ", indent, "  Revision:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smExtsnEntry->_smExtsnRevisionLength,
			  smExtsnEntry->smExtsnRevision);
    }
}



static char const *
get_script_lang_name(smScriptEntry_t *smScriptEntry,
		     smLangEntry_t **smLangTable)
{
    int i;

    if (! smScriptEntry->smScriptLanguage) {
	return NULL;
    }
    
    for (i = 0; smLangTable[i]; i++) {
	if (smLangTable[i]->smLangIndex == *smScriptEntry->smScriptLanguage) {
	    return get_lang_name(smLangTable[i]);
	}
    }
    return NULL;
}



static void
show_langauge(GString *s, smLangEntry_t *smLangEntry,
	      smExtsnEntry_t **smExtsnEntry)
{
    int i;
    int const indent = 12;

    if (smLangEntry->smLangDescr) {
	g_string_sprintfa(s, "%-*s ", indent, "Descr:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smLangEntry->_smLangDescrLength,
			  smLangEntry->smLangDescr);
    }
    if (smLangEntry->smLangVersion) {
	g_string_sprintfa(s, "%-*s ", indent, "Version:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smLangEntry->_smLangVersionLength,
			  smLangEntry->smLangVersion);
    }
    if (smLangEntry->smLangRevision && smLangEntry->_smLangRevisionLength) {
	g_string_sprintfa(s, "%-*s ", indent, "Revision:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smLangEntry->_smLangRevisionLength,
			  smLangEntry->smLangRevision);
    }

    if (smExtsnEntry) {
	for (i = 0; smExtsnEntry[i]; i++) {
	    if (smExtsnEntry[i]->smLangIndex != smLangEntry->smLangIndex) {
		continue;
	    }
	    show_extension(s, smExtsnEntry[i]);
	}
    }
}



static int
cmd_languages(scli_interp_t *interp, int argc, char **argv)
{
    smLangEntry_t **smLangTable = NULL;
    smExtsnEntry_t **smExtsnTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smLangTable(interp->peer, &smLangTable)) {
	return SCLI_ERROR;
    }
    (void) disman_script_mib_get_smExtsnTable(interp->peer, &smExtsnTable);

    if (smLangTable) {
	for (i = 0; smLangTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_langauge(interp->result, smLangTable[i], smExtsnTable);
	}
    }

    if (smLangTable) disman_script_mib_free_smLangTable(smLangTable);
    if (smExtsnTable) disman_script_mib_free_smExtsnTable(smExtsnTable);
    
    return SCLI_OK;
}



static void
show_script_details(GString *s, smScriptEntry_t *smScriptEntry,
		    char const *language)
{
    int const width = 20;
    
    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptAdminStatus,
	     smScriptEntry->smScriptAdminStatus);
    g_string_append(s, "Owner:    ");
    g_string_sprintfa(s, "%-*.*s\n", width,
		      (int) smScriptEntry->_smScriptOwnerLength,
		      smScriptEntry->smScriptOwner);

    g_string_append(s, "OperStatus:  ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptOperStatus,
	     smScriptEntry->smScriptOperStatus);
    g_string_append(s, "Name:     ");
    g_string_sprintfa(s, "%-*.*s\n", width,
		      (int) smScriptEntry->_smScriptNameLength,
		      smScriptEntry->smScriptName);
    
    g_string_append(s, "RowStatus:   ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptRowStatus,
	     smScriptEntry->smScriptRowStatus);
    g_string_append(s, "Language: ");
    if (smScriptEntry->smScriptLanguage) {
	if (language) {
	    g_string_sprintfa(s, "%s", language);
	} else {
	    g_string_sprintfa(s, "%d",
			      *(smScriptEntry->smScriptLanguage));
	}
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Storage:     ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptStorageType,
	     smScriptEntry->smScriptStorageType);
    g_string_append(s, "Change:   ");
#if 0
    if (smScriptEntry->smScriptLastChange) {
	fmt_date_and_time(s, smScriptEntry->smScriptLastChange,
			  smScriptEntry->_smScriptLastChangeLength);
    }
#endif
    g_string_append(s, "\n");
    
    if (smScriptEntry->smScriptSource) {
	g_string_sprintfa(s, "Source:      %.*s\n",
			  (int) smScriptEntry->_smScriptSourceLength,
			  smScriptEntry->smScriptSource);
    }

#if 0
    if (smScriptEntry->smScriptError) {
	g_string_sprintfa(s, "Error:       %.*s\n",
			  (int) smScriptEntry->_smScriptErrorLength,
			  smScriptEntry->smScriptError);
    }
#endif

    if (smScriptEntry->smScriptDescr) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) smScriptEntry->_smScriptDescrLength,
			  smScriptEntry->smScriptDescr);
    }
}



static int
cmd_script_details(scli_interp_t *interp, int argc, char **argv)
{
    smLangEntry_t **smLangTable = NULL;
    smScriptEntry_t **smScriptTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smLangTable(interp->peer, &smLangTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable);

    if (smScriptTable) {
	for (i = 0; smScriptTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_script_details(interp->result, smScriptTable[i],
			get_script_lang_name(smScriptTable[i], smLangTable));
	}
    }

    if (smScriptTable) disman_script_mib_free_smScriptTable(smScriptTable);
    if (smLangTable) disman_script_mib_free_smLangTable(smLangTable);

    return SCLI_OK;
}



static void
show_script_info(GString *s, smScriptEntry_t *smScriptEntry, 
		 char const *language, int launches,
		 int owner_width, int lang_width)
{
    fmt_script_admin_status(s, smScriptEntry->smScriptAdminStatus);
    fmt_script_oper_status(s, smScriptEntry->smScriptOperStatus);
    fmt_storage_type(s, smScriptEntry->smScriptStorageType);
    fmt_row_status(s, smScriptEntry->smScriptRowStatus);

    g_string_sprintfa(s, " %3u ", launches);
    
    g_string_sprintfa(s, "%-*.*s ", owner_width,
		      (int) smScriptEntry->_smScriptOwnerLength,
		      smScriptEntry->smScriptOwner);

    g_string_sprintfa(s, "%-*s ", lang_width, language ? language : "");

    fmt_last_change(s, NULL, 0);
    
    g_string_sprintfa(s, "%.*s",
		      (int) smScriptEntry->_smScriptNameLength,
		      smScriptEntry->smScriptName);
    g_string_append(s, "\n");
}



static int
count_launches(smScriptEntry_t *smScriptEntry, smLaunchEntry_t **smLaunchTable)
{
    int i;
    int launches = 0;

    if (! smLaunchTable) {
	return 0;
    }

    for (i = 0; smLaunchTable[i]; i++) {
	if (smLaunchTable[i]->smLaunchScriptOwner
	    && smLaunchTable[i]->smLaunchScriptName
	    && (smLaunchTable[i]->_smLaunchScriptOwnerLength ==
		smScriptEntry->_smScriptOwnerLength)
	    && (smLaunchTable[i]->_smLaunchScriptNameLength ==
		smScriptEntry->_smScriptNameLength)
	    && memcmp(smLaunchTable[i]->smLaunchScriptOwner,
		      smScriptEntry->smScriptOwner,
		      smScriptEntry->_smScriptOwnerLength) == 0
	    && memcmp(smLaunchTable[i]->smLaunchScriptName,
		      smScriptEntry->smScriptName,
		      smScriptEntry->_smScriptNameLength) == 0)
	    {
	    launches++;
	}
    }
    
    return launches;
}



static int
cmd_script_info(scli_interp_t *interp, int argc, char **argv)
{
    smLangEntry_t **smLangTable = NULL;
    smScriptEntry_t **smScriptTable = NULL;
    smLaunchEntry_t **smLaunchTable = NULL;
    int i;
    int owner_width = 8, lang_width = 8;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smLangTable(interp->peer, &smLangTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable);
    (void) disman_script_mib_get_smLaunchTable(interp->peer, &smLaunchTable);

    if (smScriptTable) {
	for (i = 0; smScriptTable[i]; i++) {
	    if (smScriptTable[i]->_smScriptOwnerLength > owner_width) {
		owner_width = smScriptTable[i]->_smScriptOwnerLength;
	    }
	}
	g_string_sprintfa(interp->result,
			  "State  L %-*s %-*s Last Change  Name\n",
			  owner_width, "Owner", lang_width, "Language");
	for (i = 0; smScriptTable[i]; i++) {
	    show_script_info(interp->result, smScriptTable[i],
		     get_script_lang_name(smScriptTable[i], smLangTable),
			     count_launches(smScriptTable[i], smLaunchTable),
			     owner_width, lang_width);
	}
    }

    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);
    if (smScriptTable) disman_script_mib_free_smScriptTable(smScriptTable);
    if (smLangTable) disman_script_mib_free_smLangTable(smLangTable);

    return SCLI_OK;
}



static void
show_launch_info(GString *s, smLaunchEntry_t *smLaunchEntry,
		 int owner_width)
{
#if 0
    fmt_script_admin_status(s, smScriptEntry->smScriptAdminStatus);
    fmt_script_oper_status(s, smScriptEntry->smScriptOperStatus);
    fmt_storage_type(s, smScriptEntry->smScriptStorageType);
    fmt_row_status(s, smScriptEntry->smScriptRowStatus);

    g_string_sprintfa(s, " %3u ", launches);
#endif
    
    g_string_sprintfa(s, "%-*.*s ", owner_width,
		      (int) smLaunchEntry->_smLaunchOwnerLength,
		      smLaunchEntry->smLaunchOwner);

#if 0
    g_string_sprintfa(s, "%-*s ", lang_width, language ? language : "");
#endif

    fmt_last_change(s, NULL, 0);
    
    g_string_sprintfa(s, "%.*s",
		      (int) smLaunchEntry->_smLaunchNameLength,
		      smLaunchEntry->smLaunchName);
    g_string_append(s, "\n");
}



static int
cmd_launch_info(scli_interp_t *interp, int argc, char **argv)
{
    smScriptEntry_t **smScriptTable = NULL;
    smLaunchEntry_t **smLaunchTable = NULL;
    smRunEntry_t **smRunTable = NULL;
    int i;
    int owner_width = 8, lang_width = 8;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smLaunchTable(interp->peer, &smLaunchTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable);
    (void) disman_script_mib_get_smRunTable(interp->peer, &smRunTable);

    if (smLaunchTable) {
	for (i = 0; smLaunchTable[i]; i++) {
	    if (smLaunchTable[i]->_smLaunchOwnerLength > owner_width) {
		owner_width = smLaunchTable[i]->_smLaunchOwnerLength;
	    }
	}
	g_string_sprintfa(interp->result,
			  "State  L %-*s %-*s Last Change  Name\n",
			  owner_width, "Owner", lang_width, "Language");
	for (i = 0; smLaunchTable[i]; i++) {
	    show_launch_info(interp->result, smLaunchTable[i],
			     owner_width);
	}
    }

    if (smRunTable) disman_script_mib_free_smRunTable(smRunTable);
    if (smScriptTable) disman_script_mib_free_smScriptTable(smScriptTable);
    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);

    return SCLI_OK;
}



static int
cmd_launch_details(scli_interp_t *interp, int argc, char **argv)
{
#if 0
    smScriptEntry_t **smScriptTable = NULL;
    smLaunchEntry_t **smLaunchTable = NULL;
    smRunEntry_t **smRunTable = NULL;
    int i;
    int owner_width = 8, lang_width = 8;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smLaunchTable(interp->peer, &smLaunchTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable);
    (void) disman_script_mib_get_smRunTable(interp->peer, &smRunTable);

    if (smLaunchTable) {
	for (i = 0; smLaunchTable[i]; i++) {
	    if (smLaunchTable[i]->_smLaunchOwnerLength > owner_width) {
		owner_width = smLaunchTable[i]->_smLaunchOwnerLength;
	    }
	}
	g_string_sprintfa(interp->result,
			  "State  L %-*s %-*s Last Change  Name\n",
			  owner_width, "Owner", lang_width, "Language");
	for (i = 0; smLaunchTable[i]; i++) {
	    show_launch_info(interp->result, smLaunchTable[i],
			     owner_width);
	}
    }

    if (smRunTable) disman_script_mib_free_smRunTable(smRunTable);
    if (smScriptTable) disman_script_mib_free_smScriptTable(smScriptTable);
    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);
#endif
    return SCLI_OK;
}



static int
cmd_run_info(scli_interp_t *interp, int argc, char **argv)
{
    smRunEntry_t **smRunTable = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smRunTable(interp->peer, &smRunTable)) {
	return SCLI_ERROR;
    }

    if (smRunTable) disman_script_mib_free_smRunTable(smRunTable);
	
    return SCLI_OK;
}



static int
cmd_run_details(scli_interp_t *interp, int argc, char **argv)
{
    return SCLI_OK;
}



void
scli_init_disman_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show disman languages",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "languages supported by the distributed manager",
	  cmd_languages },
	{ "show disman script info",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "script summary information",
	  cmd_script_info },
	{ "show disman script details",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "scripts installed at the distributed manager",
	  cmd_script_details },
	{ "show disman launch info",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "launch summary information",
	  cmd_launch_info },
	{ "show disman launch details",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "launch buttons installed on the distributed manager",
	  cmd_launch_details },
	{ "show disman run info",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "summary information about running scripts",
	  cmd_run_info },
	{ "show disman run details",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "running scripts on the distributed manager",
	  cmd_run_details },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t disman_mode = {
	"disman",
	"scli mode to display and configure distributed managers",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &disman_mode);
}
