/* 
 * udp-mib-proc.c -- UDP-MIB procedures
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

#include <stdio.h>
#include <time.h>

#include "udp-mib-proc.h"

#define TV_DIFF(t1, t2) (1.0 * (t2.tv_sec - t1.tv_sec) + \
                         (t2.tv_usec - t1.tv_usec) / 1000000.0)
#define TV_DELTA	0.1

struct state {
    GTimeVal		last_poll_time;
    udp_mib_udp_t	*udp;
};

extern void
udp_mib_proc_get_stats(GSnmpSession *s,
		       udp_mib_proc_stats_t **udpStatsEntry)
{
    udp_mib_udp_t *udp;
    static struct state state = { {0,0}, NULL};
    GTimeVal now;
    double delta;
    
    udp_mib_get_udp(s, &udp, 0);
    if (s->error_status || !udp) return;

#if 0
    if (state.last_poll_time.tv_sec < interp->epoch) {
	if (state.udp) udp_mib_free_udp(state.udp);
	state.udp = NULL;
	state.last_poll_time = {0,0};
    }
#endif

    g_get_current_time(&now);
    delta = TV_DIFF(state.last_poll_time, now);

    if (udp && state.udp && state.last_poll_time.tv_sec && state.last_poll_time.tv_usec) {
	if (state.udp->udpInDatagrams && udp->udpInDatagrams) {
	    (*udpStatsEntry)->inDatagrams = (*udp->udpInDatagrams - *state.udp->udpInDatagrams);
	    g_printerr("** old: %u new: %u delta: %u\n", *state.udp->udpInDatagrams, *udp->udpInDatagrams, (*udpStatsEntry)->inDatagrams);
	}
    }

    state.last_poll_time = now;
    if (state.udp) udp_mib_free_udp(state.udp);
    state.udp = udp;
}

