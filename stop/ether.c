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


typedef struct {
    /* input errors */
    guint32 alignmentErrors;
    guint32 fcsErrors;
    guint32 macRecvErrors;
    guint32 frameTooLongs;
    /* output errors */
    guint32 deferredTransmissions;
    guint32 singleCollisionFrames;
    guint32 multipleCollisionFrames;
    guint32 excessiveCollisions;
    guint32 lateCollisions;
    guint32 macSendErrors;
    guint32 carrierSenseErrors;
} ether_stats_t;


static void
show_ether_summary(host_snmp *peer)
{
    GString *s;
    
    g_return_if_fail(peer);
    
    s = g_string_new("Ether: ");

    stop_show_mode_summary_line(s->str);
    g_string_free(s, 1);
}



static void
show_ethers(WINDOW *win, host_snmp *peer, int flags)
{
    dot3StatsEntry_t **dot3StatsTable = NULL;
    static struct timeval last, now;
    double delta;
    int i;
    static ether_stats_t *stats = NULL;

    if (flags & STOP_FLAG_RESTART) {
	show_ether_summary(peer);
	wattron(win, A_REVERSE);
	mvwprintw(win, 0, 0, "%-*s", COLS, 
		  "INDEX | ALIGN   FCS   MAC  LONG | DEFER  SCOL  MCOL  XCOL  LCOL   MAC  CARR");
	wattroff(win, A_REVERSE);
	wrefresh(win);
	if (stats) {
	    g_free(stats);
	    stats = NULL;
	}
    }
    
    if (etherlike_mib_get_dot3StatsTable(peer, &dot3StatsTable)
	|| !dot3StatsTable) {
	return;
    }

    if (! stats && dot3StatsTable) {
	for (i = 0; dot3StatsTable[i]; i++) ;
	stats = (ether_stats_t *) g_malloc0(i * sizeof(ether_stats_t));
    }

    gettimeofday(&now, NULL);
    delta = TV_DIFF(last, now);
    
    wmove(win, 1, 0);
    for (i = 0; dot3StatsTable[i]; i++) {
	GString *s;
	s = g_string_new(NULL);

	g_string_sprintfa(s, "%5u |",
			  dot3StatsTable[i]->dot3StatsIndex);

	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsAlignmentErrors,
		       &(stats[i].alignmentErrors), &last, delta);

	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsFCSErrors,
		       &(stats[i].fcsErrors), &last, delta);

	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsInternalMacReceiveErrors,
		       &(stats[i].macRecvErrors), &last, delta);

	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsFrameTooLongs,
		       &(stats[i].frameTooLongs), &last, delta);

	g_string_append(s, " |");

	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsDeferredTransmissions,
		       &(stats[i].deferredTransmissions), &last, delta);

	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsSingleCollisionFrames,
		       &(stats[i].singleCollisionFrames), &last, delta);

	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsMultipleCollisionFrames,
		       &(stats[i].multipleCollisionFrames), &last, delta);
	
	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsExcessiveCollisions,
		       &(stats[i].excessiveCollisions), &last, delta);
	
	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsLateCollisions,
		       &(stats[i].lateCollisions), &last, delta);
	
	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsInternalMacTransmitErrors,
		       &(stats[i].macSendErrors), &last, delta);
	
	fmt_counter_dt(s, dot3StatsTable[i]->dot3StatsCarrierSenseErrors,
		       &(stats[i].carrierSenseErrors), &last, delta);
	
	if (s->len > COLS) {
	  g_string_truncate(s, COLS);
	}
	mvwprintw(win, i + 1, 0, s->str);
	wclrtoeol(win);
	g_string_free(s, 1);
    }
    wclrtobot(win);

    last = now;
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
