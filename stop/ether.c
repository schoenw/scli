/* 
 * ether.c -- stop ether mode implementation
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

#include "etherlike-mib.h"


static void
show_ethers(WINDOW *win, host_snmp *peer, int flags)
{
    dot3StatsEntry_t **dot3StatsTable = NULL;
    int i;

    if (flags & STOP_FLAG_RESTART) {
	/* show_ether_summary(peer); */
	wattron(win, A_REVERSE);
	mvwprintw(win, 0, 0, "%-*s", COLS, 
		  "FOO BAR");
	wattroff(win, A_REVERSE);
	wrefresh(win);
    }
    
    if (etherlike_mib_get_dot3StatsTable(peer, &dot3StatsTable)
	|| !dot3StatsTable) {
	return;
    }

    wmove(win, 1, 0);
    for (i = 0; dot3StatsTable[i]; i++) {
	GString *s;
	s = g_string_new(NULL);

	g_string_sprintfa(s, "%6u %6u %6u %6u %6u",
			  dot3StatsTable[i]->dot3StatsIndex,
			  *dot3StatsTable[i]->dot3StatsAlignmentErrors,
			  *dot3StatsTable[i]->dot3StatsFCSErrors,
			  *dot3StatsTable[i]->dot3StatsSingleCollisionFrames,
			  *dot3StatsTable[i]->dot3StatsMultipleCollisionFrames);
	
	g_string_truncate(s, COLS);
	mvwprintw(win, i + 1, 0, s->str);
	wclrtoeol(win);
	g_string_free(s, 1);
    }
    wclrtobot(win);

    if (dot3StatsTable) etherlike_mib_free_dot3StatsTable(dot3StatsTable);
}



void
stop_init_ether_mode()
{
    static stop_mode_t ether_mode = {
	"ether",
	"Display ethernet like interface statistics",
	&show_ethers
    };
    
    stop_register_mode(&ether_mode);
}
