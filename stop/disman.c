/* 
 * disman.c -- stop disman mode implementation
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

#include "stop.h"

#include "disman-script-mib.h"



static void
fmt_run_state(GString *s, gint32 *state)
{
    char *name;

    static stls_table_t const run_states[] = {
	{ 1, "I" },	/* initializing */
	{ 2, "R" },	/* executing */
	{ 3, "U" },	/* suspending */
	{ 4, "S" },	/* suspended */
	{ 5, "R" },	/* resuming */
	{ 6, "A" },	/* aborting */
	{ 7, "T" },	/* terminated */
	{ 0, NULL }
    };
    
    if (! state) {
	g_string_append(s, "-");
	return;
    }
    
    name = stls_table_get_value(run_states, *state);
    if (name) {
	g_string_append(s, name);
    } else {
	g_string_append(s, "?");
    }
}


static void
fmt_exit_code(GString *s, gint32 *code)
{
    char *name;

    static stls_table_t const exit_codes[] = {
	{ 1, "N" },	/* noError */
	{ 2, "H" },	/* halted */
	{ 3, "T" },	/* lifeTimeExceeded */
	{ 4, "O" },	/* noResourcesLeft */
	{ 5, "L" },	/* languageError */
	{ 6, "R" },	/* runtimeError */
	{ 7, "A" },	/* invalidArgument */
	{ 8, "S" },	/* securityViolation */
	{ 9, "G" },	/* genericError */
	{ 0, NULL }
    };
    
    if (! code) {
	g_string_append(s, "-");
	return;
    }
    
    name = stls_table_get_value(exit_codes, *code);
    if (name) {
	g_string_append(s, name);
    } else {
	g_string_append(s, "?");
    }
}



static char const *
trim_string8(guchar *s, gsize len)
{
    static char buffer[9];

    memset(buffer, 0, sizeof(buffer));

    if (s && len) {
	if (len < sizeof(buffer)-1) {
	    strncpy(buffer, s, len);
	} else {
	    strncpy(buffer, s, 3);
	    strcat(buffer, "..");
	    strncpy(buffer+5, s+len-3, 3);
	}
    }

    return buffer;
}



static void
show_runs(WINDOW *win, host_snmp *peer, int flags)
{
    smLaunchEntry_t **smLaunchTable = NULL;
    smRunEntry_t **smRunTable = NULL;
    int i;

    if (flags & STOP_FLAG_RESTART) {
	/* show_disman_summary(peer); */
	wattron(win, A_REVERSE);
	mvwprintw(win, 0, 0, "%-*s", COLS, 
		  "L-OWNER  L-NAME   RUNID STAT    LIFE   EXPIRE S-OWNER  S-NAME   ARGUMENT");
	wattroff(win, A_REVERSE);
	wrefresh(win);
    }

    if (disman_script_mib_get_smRunTable(peer, &smRunTable) != 0 
	|| smRunTable == NULL) {
	return;
    }

    (void) disman_script_mib_get_smLaunchTable(peer, &smLaunchTable);

    for (i = 0; smRunTable[i]; i++) {
	GString *s;
	s = g_string_new(NULL);
	g_string_sprintfa(s, "%-8s ",
			  trim_string8(smRunTable[i]->smLaunchOwner,
				      smRunTable[i]->_smLaunchOwnerLength));
	g_string_sprintfa(s, "%-8s ",
			  trim_string8(smRunTable[i]->smLaunchName,
				       smRunTable[i]->_smLaunchNameLength));
	g_string_sprintfa(s, "%5d ", smRunTable[i]->smRunIndex);

	g_string_append(s, " ");
	fmt_run_state(s, smRunTable[i]->smRunState);
	fmt_exit_code(s, smRunTable[i]->smRunExitCode);
	g_string_append(s, " ");

	if (smRunTable[i]->smRunLifeTime) {
	    g_string_sprintfa(s, "%7s ",
			      fmt_seconds(*smRunTable[i]->smRunLifeTime/100));
	} else {
	    g_string_sprintfa(s, "%7s ", "");
	}
	if (smRunTable[i]->smRunExpireTime) {
	    g_string_sprintfa(s, "%7s ", 
			      fmt_seconds(*smRunTable[i]->smRunExpireTime/100));
	} else {
	    g_string_sprintfa(s, "%7s ", "");
	}

	if (smLaunchTable) {
	    int l;
	    for (l = 0; smLaunchTable[l]; l++) {
		if (smLaunchTable[l]->_smLaunchOwnerLength == smRunTable[i]->_smLaunchOwnerLength
		    && memcmp(smLaunchTable[l]->smLaunchOwner, smRunTable[i]->smLaunchOwner, smRunTable[i]->_smLaunchOwnerLength) == 0
		    && smLaunchTable[l]->_smLaunchNameLength == smRunTable[i]->_smLaunchNameLength
		    && memcmp(smLaunchTable[l]->smLaunchName, smRunTable[i]->smLaunchName, smRunTable[i]->_smLaunchNameLength) == 0
		    ) {
		    break;
		}
	    }
	    if (smLaunchTable[l]) {
		g_string_sprintfa(s, "%-8s ",
				  trim_string8(smLaunchTable[l]->smLaunchScriptOwner,
					       smLaunchTable[l]->_smLaunchScriptOwnerLength));
		g_string_sprintfa(s, "%-8s ",
				  trim_string8(smLaunchTable[l]->smLaunchScriptName,
					       smLaunchTable[l]->_smLaunchScriptNameLength));
	    } else {
		g_string_sprintfa(s, "%.*s ",
				  (int) smRunTable[i]->_smLaunchNameLength,
				  smRunTable[i]->smLaunchName);
	    }
	}

	if (smRunTable[i]->smRunArgument) {
	    g_string_sprintfa(s, "%.*s ",
			      (int) smRunTable[i]->_smRunArgumentLength,
			      smRunTable[i]->smRunArgument);
	}
	
	g_string_truncate(s, COLS);
	mvwprintw(win, i + 1, 0, s->str);
	wclrtoeol(win);
	g_string_free(s, 1);
    }
    wclrtobot(win);

    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);
    if (smRunTable) disman_script_mib_free_smRunTable(smRunTable);
}



void
stop_init_disman_mode()
{
    static stop_mode_t disman_mode = {
	"disman",
	"Display list of management scripts",
	&show_runs
    };
    
    stop_register_mode(&disman_mode);
}
