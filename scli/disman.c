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

#include "stools.h"
#include "scli.h"



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
show_script(GString *s, smScriptEntry_t *smScriptEntry)
{
    int const width = 20;
    
    g_string_append(s, "Owner:       ");
    g_string_sprintfa(s, "%-*.*s", width,
		      (int) smScriptEntry->_smScriptOwnerLength,
		      smScriptEntry->smScriptOwner);
    g_string_append(s, "Name:     ");
    g_string_sprintfa(s, "%-*.*s\n", width,
		      (int) smScriptEntry->_smScriptNameLength,
		      smScriptEntry->smScriptName);

    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptAdminStatus,
	     smScriptEntry->smScriptAdminStatus);
    g_string_append(s, "Language: ");
    if (smScriptEntry->smScriptLanguage) {
	g_string_sprintfa(s, "%d (xxx)\n",
			  *(smScriptEntry->smScriptLanguage));
    } else {
	g_string_append(s, "\n");
    }

    g_string_append(s, "OperStatus:  ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptOperStatus,
	     smScriptEntry->smScriptOperStatus);
    g_string_append(s, "Storage:  ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptStorageType,
	     smScriptEntry->smScriptStorageType);
    g_string_append(s, "\n");
    
    if (smScriptEntry->smScriptSource) {
	g_string_sprintfa(s, "Source:      %.*s\n",
			  (int) smScriptEntry->_smScriptSourceLength,
			  smScriptEntry->smScriptSource);
    }

    if (smScriptEntry->smScriptDescr) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) smScriptEntry->_smScriptDescrLength,
			  smScriptEntry->smScriptDescr);
    }
}



static int
cmd_scripts(scli_interp_t *interp, int argc, char **argv)
{
    smScriptEntry_t **smScriptTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable)) {
	return SCLI_ERROR;
    }

    if (smScriptTable) {
	for (i = 0; smScriptTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_script(interp->result, smScriptTable[i]);
	}
	disman_script_mib_free_smScriptTable(smScriptTable);
    }

    return SCLI_OK;
}



void
scli_init_disman_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "disman", NULL, NULL },
	{ "show disman", "languages",
	  "show languages supported by the distributed manager",
	  cmd_languages },
	{ "show disman", "scripts",
	  "show scripts installed at the distributed manager",
	  cmd_scripts },
	{ NULL, NULL, NULL, NULL }
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
