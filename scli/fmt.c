/* 
 * fmt.c -- scli formatting utilities used by many scli modes
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

#include "scli.h"

#include <netdb.h>
#include <netinet/in.h>

#ifndef HAVE_TM_ZONE
extern time_t timezone;
#endif


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



void
fmt_time_ticks(GString *s, guint32 timeticks)
{
    time_t now;
    struct tm *tm;
    long gmt_offset;
    
    now = time(NULL);
    now -= timeticks/100;
    tm = localtime(&now);

#ifdef HAVE_TM_ZONE
    gmt_offset = tm->tm_gmtoff;
#else
    gmt_offset = timezone;
#endif

    /*
     * This code assumes that daylight savings time is always 1 hour,
     * which is probably not true everywhere on the world. I have no
     * clue how you get the real daylight savings time offset in a
     * portable way.
     */
    
    g_string_sprintfa(s, "%04d-%02d-%02d %02d:%02d:%02d %c%02d:%02d",
		      tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		      tm->tm_hour, tm->tm_min, tm->tm_sec,
		      gmt_offset <= 0 ? '+' : '-',
		      (int) ABS(gmt_offset) / 3600
		      + ((tm->tm_isdst > 0) ? 1 : 0),
		      (int) (ABS(gmt_offset) / 60) % 60);
}



void
fmt_date_and_time(GString *s, guchar *data, gsize len)
{
    int i;
    
    /*
     * Check if it is a NULL value consisting of all 0x00 bytes or if
     * it has a length of 0 (not really legal, but people sometimes
     * do it this way.
     */

    for (i = 0; i < len; i++) {
	if (data[i]) break;
    }

    if (len == 0 || i == len) {
	g_string_sprintfa(s, "-");
	return;
    }

    /*
     * The two normal cases for DateAndTime are handled below.
     */
    
    if (len == 8) {
	g_string_sprintfa(s, "%04u-%02u-%02u %02u:%02u:%02u",
			  (data[0] << 8) + data[1], data[2], data[3],
			  data[4], data[5], data[6]);
    }
    if (len == 11) {
	g_string_sprintfa(s, "%04u-%02u-%02u %02u:%02u:%02u %c%02u:%02u",
			  (data[0] << 8) + data[1], data[2], data[3],
			  data[4], data[5], data[6],
			  data[8], data[9], data[10]);
    }
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



void
fmt_kbytes(GString *s, guint32 kbytes)
{
    if (kbytes > 9999999) {
	g_string_sprintfa(s, "%u GByte", kbytes / 1024 / 1024);
    } else if (kbytes > 9999) {
	g_string_sprintfa(s, "%u MByte", kbytes / 1024);
    } else {
	g_string_sprintfa(s, "%u KByte", kbytes);
    }
}



void
fmt_enum(GString *s, int width, stls_enum_t const *table, gint32 *number)
{
    gchar const *name;

    if (! number) {
	g_string_sprintfa(s, "%*s", width, "");
	return;
    }
    
    name = stls_enum_get_label(table, *number);
    if (! name) {
	g_string_sprintfa(s, "%-*d", width, *number);
    } else {
	g_string_sprintfa(s, "%-*s", width, name);
    }
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



char*
fmt_gtp(guint32 number)
{
    static char buffer[80];

    if (number > 999999999) {
	g_snprintf(buffer, sizeof(buffer), "%3up", number / 1000000000);
    } else if (number > 999999) {
	g_snprintf(buffer, sizeof(buffer), "%3ut", number / 1000000);
    } else if (number > 999) {
	g_snprintf(buffer, sizeof(buffer), "%3ug", number / 1000);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%3um", number);
    }
    return buffer;
}



char*
fmt_udp_port(int port, int name)
{
    struct servent *s;
    static char buffer[12];

    if (name) {
	if (! port) {
	    return "*";
	}
	s = getservbyport(htons(port), "udp");
	if (s) {
	    return s->s_name;
	}
    }
    sprintf(buffer, "%d", port);
    return buffer;
}



char*
fmt_tcp_port(int port, int name)
{
    struct servent *s;
    static char buffer[12];

    if (name) {
	if (! port) {
	    return "*";
	}
	s = getservbyport(htons(port), "tcp");
	if (s) {
	    return s->s_name;
	}
    }
    sprintf(buffer, "%d", port);
    return buffer;
}



char*
fmt_ipv4_address(guchar *addr, int name)
{
    static char buffer[16];
    struct hostent *h;

    if (name) {
	if (! addr[0] && ! addr[1] && ! addr[2] && ! addr[3]) {
	    return "*";
	}
	h = gethostbyaddr((char *) addr, 4, AF_INET);
	if (h) {
	    return h->h_name;
	}
    }
    sprintf(buffer, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
    return buffer;
}



char *
fmt_ipv4_mask(guchar *addr)
{
    static char buffer[4];
    unsigned prefix = 0;
    int i, j;

    for (i = 0; i < 4; i++) {
	for (j = 0; j < 8; j++) {
	    if ((1 << (7-j)) & addr[i]) {
		prefix++;
	    } else {
		i = 4;
		break;
	    }
	}
    }
    sprintf(buffer, "/%u", prefix);
    return buffer;
}
