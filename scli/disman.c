/* 
 * system.c -- scli disman mode implementation
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



static int
cmd_languages(scli_interp_t *interp, int argc, char **argv)
{
    smLangEntry_t **smLangEntry = NULL;
    smExtsnEntry_t **smExtsnEntry = NULL;
    GString *s;
    int i;
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (disman_script_mib_get_smLangEntry(interp->peer, &smLangEntry) == 0) {
	(void) disman_script_mib_get_smExtsnEntry(interp->peer, &smExtsnEntry);
    }

    s = interp->result;
    if (smLangEntry) {
	for (i = 0; smLangEntry[i]; i++) {
	    if (smLangEntry[i]->smLangIndex) {
		g_string_sprintfa(s, "%-*s ", indent, "Index:"),
		g_string_sprintfa(s, " %-5u\n", *(smLangEntry[i]->smLangIndex));
	    }
	    if (smLangEntry[i]->smLangVersion) {
		g_string_sprintfa(s, "%-*s ", indent, "Version:"),
		g_string_sprintfa(s, " %.*s\n",
			    (int) smLangEntry[i]->_smLangVersionLength,
				  smLangEntry[i]->smLangVersion);
	    }
	    if (smLangEntry[i]->smLangRevision) {
		g_string_sprintfa(s, "%-*s ", indent, "Revision:"),
		g_string_sprintfa(s, " %.*s\n",
			    (int) smLangEntry[i]->_smLangRevisionLength,
				  smLangEntry[i]->smLangRevision);
	    }
	    if (smLangEntry[i]->smLangDescr) {
		g_string_sprintfa(s, "%-*s ", indent, "Descr:"),
		g_string_sprintfa(s, " %.*s\n",
			    (int) smLangEntry[i]->_smLangDescrLength,
				  smLangEntry[i]->smLangDescr);
	    }

	    if (smLangEntry[i+1]) {
		g_string_append(s, "\n");
	    }
	}
    }

    if (smLangEntry) disman_script_mib_free_smLangEntry(smLangEntry);
    if (smExtsnEntry) disman_script_mib_free_smExtsnEntry(smExtsnEntry);
    
    interp->result = s;
    return SCLI_OK;
}



void
scli_init_disman_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "disman", NULL, NULL },
	{ "show disman", "languages",
	  "show the languages supported by the disman", cmd_languages },
	{ NULL, NULL, NULL, NULL }
    };
    
    static scli_mode_t disman_mode = {
	"system",
	"scli mode to display and configure distributed managers",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &disman_mode);
}
