/* 
 * process.c -- stop process mode implementation
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

#include "host-resources-mib.h"



static char*
fmt_kbytes(guint32 bytes)
{
    static char buffer[80];
    
    if (bytes > 9999999) {
	g_snprintf(buffer, sizeof(buffer), "%uG", bytes / 1024 / 1024);
    } else if (bytes > 9999) {
	g_snprintf(buffer, sizeof(buffer), "%uM", bytes / 1024);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%uK", bytes);
    }
    return buffer;
}



static void
fmt_run_state_and_type(GString *s, gint32 *state, gint32 *type)
{
    if (state) {
	switch (*state) {
	case 1:  g_string_append(s, "C "); break;
	case 2:  g_string_append(s, "R "); break;
	case 3:  g_string_append(s, "S "); break;
	case 4:  g_string_append(s, "Z "); break;
	default: g_string_append(s, "- "); break;
	}
    } else {
	g_string_append(s, "- ");
    }

    if (type) {
	switch (*type) {
	case 1:  g_string_append(s, "? "); break;
	case 2:  g_string_append(s, "O "); break;
	case 3:  g_string_append(s, "D "); break;
	case 4:  g_string_append(s, "A "); break;
	default: g_string_append(s, "- "); break;
	}
    } else {
	g_string_append(s, "- ");
    }
}


typedef struct {
    gint32  idx;
    guint32 cpu;
} hr_sort_t;

static int 
hr_sort (const void *arg1, const void *arg2)
{
    hr_sort_t *p = (hr_sort_t *) arg1;
    hr_sort_t *q = (hr_sort_t *) arg2;
    
    if (p->cpu > q->cpu) {
	return -1;
    } else if (p->cpu == q->cpu) {
	return 0;
    } else {
	return 1;
    }
}



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



static void
show_processes(WINDOW *win, host_snmp *peer, int flags)
{
    hrSWRunEntry_t **hrSWRunTable = NULL;
    hrSWRunPerfEntry_t **hrSWRunPerfTable = NULL;
    int j, i;
    int n_idx;
    hr_sort_t *s_arr;

    if (flags & STOP_FLAG_RESTART) {
	show_process_summary(peer);
	wattron(win, A_REVERSE);
	mvwprintw(win, 0, 0, "%-*s", COLS, 
		  "  PID S T    MEM     TIME COMMAND");
	wattroff(win, A_REVERSE);
	wrefresh(win);
    }

    if (host_resources_mib_get_hrSWRunTable(peer, &hrSWRunTable) != 0 
	|| hrSWRunTable == NULL
	|| host_resources_mib_get_hrSWRunPerfTable(peer, 
						   &hrSWRunPerfTable) != 0
	|| hrSWRunPerfTable == NULL) {
	return;
    }

    /* count number of elements: */
    for (n_idx = 0; hrSWRunTable[n_idx] && hrSWRunPerfTable[n_idx]; n_idx++) {
	continue;
    }
    /* allocate array to sort: */
    s_arr = g_malloc (n_idx * sizeof(hr_sort_t));
    for (i = 0; i < n_idx; i++) {
	s_arr [i].idx = i;
	s_arr [i].cpu = *hrSWRunPerfTable [i]->hrSWRunPerfCPU;
    }

    qsort ((void *) s_arr, n_idx, sizeof(hr_sort_t), hr_sort);

    for (j = 0; j < n_idx; j++) {
	GString *s;
        i = s_arr [j].idx;
	s = g_string_new(NULL);
	g_string_sprintfa(s, "%5d ", hrSWRunTable[i]->hrSWRunIndex);
	fmt_run_state_and_type(s,
			       hrSWRunTable[i]->hrSWRunStatus,
			       hrSWRunTable[i]->hrSWRunType);
	g_string_sprintfa(s, " %5s", 
			  fmt_kbytes(*hrSWRunPerfTable[i]->hrSWRunPerfMem));
	g_string_sprintfa(s, " %7s", 
			  fmt_seconds(*hrSWRunPerfTable[i]->hrSWRunPerfCPU/100));
	if (hrSWRunTable[i]->hrSWRunPath) {
	    g_string_sprintfa(s, " %.*s",
			(int) hrSWRunTable[i]->_hrSWRunPathLength,
			      hrSWRunTable[i]->hrSWRunPath);
	}
	if (hrSWRunTable[i]->hrSWRunParameters) {
	    g_string_sprintfa(s, " %.*s",
 		        (int) hrSWRunTable[i]->_hrSWRunParametersLength,
			      hrSWRunTable[i]->hrSWRunParameters);
	}
	if (s->len > COLS) {
	  g_string_truncate(s, COLS);
	}
	mvwprintw(win, j + 1, 0, s->str);
	wclrtoeol(win);
	g_string_free(s, 1);
    }
    wclrtobot(win);

    host_resources_mib_free_hrSWRunTable(hrSWRunTable);
    host_resources_mib_free_hrSWRunPerfTable(hrSWRunPerfTable);
}



void
stop_init_process_mode()
{
    static stop_mode_t process_mode = {
	"process",
	"Display list of running processes",
	&show_processes
    };
    
    stop_register_mode(&process_mode);
}
