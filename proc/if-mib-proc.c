/* 
 * if-mib-proc.c -- IF-MIB procedures
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

#include "if-mib-proc.h"

#include <time.h>

#define CACHE_TIME	10

typedef struct {
    gpointer data;
    time_t time;
    time_t epoch;
} ifEntry_t;


void
if_mib_proc_get_ifTable(GNetSnmp *s,
			if_mib_ifEntry_t ***ifEntry,
			gint mask,
			time_t epoch)
{
    static ifEntry_t cache = {NULL, 0};
    time_t now = time(NULL);

    if (cache.data) {
	if (cache.epoch == epoch && (now - cache.time) < CACHE_TIME) {
	    *ifEntry = cache.data;
	    return;
	}
	if_mib_free_ifTable(cache.data);
	cache.data = NULL;
    }

    if_mib_get_ifTable(s, ifEntry, 0);
    if (! s->error_status) {
	cache.data = *ifEntry;
	cache.time = now;
	cache.epoch = epoch;
    }
}



void
if_mib_proc_free_ifTable(if_mib_ifEntry_t **ifEntry)
{
}
