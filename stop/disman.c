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
	{ 1, "i" },	/* initializing */
	{ 2, "e" },	/* executing */
	{ 3, "S" },	/* suspending */
	{ 4, "s" },	/* suspended */
	{ 5, "R" },	/* resuming */
	{ 6, "A" },	/* aborting */
	{ 7, "t" },	/* terminated */
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


#if 0
static void
show_process_summary(host_snmp *peer)
{
    hrSystem_t *hrSystem = NULL;
    hrStorage_t *hrStorage = NULL;
    GString *s;
    
    g_return_if_fail(peer);
    
    s = g_string_new("Process:   ");
    
    if (host_resources_mib_get_hrSystem(peer, &hrSystem) == 0 && hrSystem) {

    	if (hrSystem->hrSystemNumUsers) {
	    g_string_sprintfa(s, " %u %s",
			      *(hrSystem->hrSystemNumUsers),
			      (*(hrSystem->hrSystemNumUsers) == 1)
			      ? "user" : "users");
	}
	if (hrSystem->hrSystemProcesses) {
	    g_string_sprintfa(s, " %u processes",
			      *(hrSystem->hrSystemProcesses));
	}
	if (hrSystem->hrSystemMaxProcesses
	    && *(hrSystem->hrSystemMaxProcesses)) {
	    g_string_sprintfa(s, " (%u maximum)",
			      *(hrSystem->hrSystemMaxProcesses));
	}
	host_resources_mib_free_hrSystem(hrSystem);
    }

    if (host_resources_mib_get_hrStorage(peer, &hrStorage) == 0 && hrStorage) {
	if (hrStorage->hrMemorySize) {
	    g_string_sprintfa(s, " %s memory",
			      fmt_kbytes(*(hrStorage->hrMemorySize)));
	}
	host_resources_mib_free_hrStorage(hrStorage);
    }

    stop_show_mode_summary_line(s->str);
    g_string_free(s, 1);
}
#endif


static void
show_runs(WINDOW *win, host_snmp *peer, int flags)
{
    smRunEntry_t **smRunTable = NULL;
    int i;

    if (flags & STOP_FLAG_RESTART) {
	/* show_disman_summary(peer); */
	wattron(win, A_REVERSE);
	mvwprintw(win, 0, 0, "%-*s", COLS, 
		  "  PID OWNER   STAT START END  EXPIRE SCRIPT ARGUMENTS");
	wattroff(win, A_REVERSE);
	wrefresh(win);
	sleep(1);
    }

    if (disman_script_mib_get_smRunTable(peer, &smRunTable) != 0 
	|| smRunTable == NULL) {
	return;
    }

    for (i = 0; smRunTable[i]; i++) {
	GString *s;
	s = g_string_new(NULL);
	g_string_sprintfa(s, "%5d ", smRunTable[i]->smRunIndex);
	g_string_sprintfa(s, "%.*s ",
			  (int) smRunTable[i]->_smLaunchOwnerLength,
			  smRunTable[i]->smLaunchOwner);
	fmt_run_state(s, smRunTable[i]->smRunState);
	g_string_sprintfa(s, " ? ");
	g_string_append(s, "--- -- ----- ");
	g_string_append(s, "--- -- ----- ");
	g_string_sprintfa(s, "%.*s ",
			  (int) smRunTable[i]->_smLaunchNameLength,
			  smRunTable[i]->smLaunchName);
	g_string_sprintfa(s, "%.*s ",
			  (int) smRunTable[i]->_smRunArgumentLength,
			  smRunTable[i]->smRunArgument);
	g_string_truncate(s, COLS);
	mvwprintw(win, i + 1, 0, s->str);
	clrtoeol();
	g_string_free(s, 1);
    }

    disman_script_mib_free_smRunTable(smRunTable);
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
