/* 
 * fmt.c -- stop formatting utilities used by many stop modes
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



char const *
fmt_timeticks(guint32 timeticks)
{
    static char buffer[80];
    time_t now, gmt;
    struct tm *tm;
    int gmt_offset;
    
    now = time(NULL);
    now -= timeticks/100;

    /*
     * Get the UTC time (which is basically identically with GMT)
     * and the local time so that we can compute the UTC offset.
     * Some C libraries give you the GMT offset in tm_gmtoff but
     * you can't rely on it.
     */

    tm = gmtime(&now);
    tm->tm_isdst = 0;
    gmt = mktime(tm);

    tm = localtime(&now);
    tm->tm_isdst = 0;
    gmt_offset = mktime(tm) - gmt;

    g_snprintf(buffer, sizeof(buffer),
	       "%04d-%02d-%02d %02d:%02d:%02d %c%02d:%02d",
	       tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
	       tm->tm_hour, tm->tm_min, tm->tm_sec,
	       gmt_offset >= 0 ? '+' : '-',
	       (int) ABS(gmt_offset) / 3600,
	       (int) (ABS(gmt_offset) / 60) % 60);
    
    return buffer;
}



static time_t
date_to_time(guchar *date, gsize len)
{
    struct tm tm;
    time_t t = 0;
    
    if (len == 8 || len == 11) {
	memset(&tm, 0, sizeof(struct tm));
	tm.tm_year = ((date[0] << 8) + date[1]) - 1900;
	tm.tm_mon  = date[2];
	tm.tm_mday = date[3];
	tm.tm_hour = date[4];
	tm.tm_min  = date[5];
	tm.tm_sec  = date[6];
	t = mktime(&tm);
    }

    return t;
}



char const *
fmt_date_and_time_delta(guchar *date1, gsize len1,
			guchar *date2, gsize len2)
{
    time_t a, b;
    
    a = date_to_time(date1, len1);
    b = date_to_time(date2, len2);

    return fmt_seconds((a && b && b > a) ? b-a : 0);
}



char const *
fmt_seconds(guint32 number)
{
    static char buffer[80];
    guint32 sec, min, hour;

    sec  = (number) % 60;
    min  = (number / 60) % 60;
    hour = (number / 60 / 60);

    g_snprintf(buffer, sizeof(buffer), "%2d:%02d:%02d", hour, min, sec);

    return buffer;
}



char*
fmt_kmg(guint32 number)
{
    static char buffer[80];

    if (number > 999999999) {
	g_snprintf(buffer, sizeof(buffer), "%3ug", number / 1000000);
    } else if (number > 999999) {
	g_snprintf(buffer, sizeof(buffer), "%3um", number / 1000000);
    } else if (number > 9999) {
	g_snprintf(buffer, sizeof(buffer), "%3uk", number / 1000);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%4u", number);
    }
    return buffer;
}



void
fmt_counter_dt(GString *s, guint32 *new_counter, guint32 *old_counter,
	       struct timeval *last, double delta)
{
    if (new_counter && delta > TV_DELTA) {
	if (last->tv_sec && last->tv_usec) {
	    double f_val = (*new_counter - *old_counter) / delta;
	    g_string_sprintfa(s, " %5s", fmt_kmg((guint32) f_val));
	} else {
	    g_string_sprintfa(s, "  ----");
	}
	*old_counter = *new_counter;
    } else {
	g_string_sprintfa(s, "  ----");
    }
}



