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


void
fmt_time_ticks(GString *s, guint32 timeticks)
{
    time_t now;
    struct tm *tm;
    long gmt_offset;
    
    now = time(NULL);
    now -= timeticks/100;
    tm = gmtime(&now);

#ifdef HAVE_TM_ZONE
    gmt_offset = tm->tm_gmtoff;
#else
    gmt_offset = timezone;
#endif
    g_string_sprintfa(s, "%04d-%02d-%02d %02d:%02d:%02d %c%02d:%02d",
		      tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		      tm->tm_hour, tm->tm_min, tm->tm_sec,
		      gmt_offset <= 0 ? '+' : '-',
		      (int) ABS(gmt_offset) / 3600,
		      (int) (ABS(gmt_offset) / 60) % 60);
}



void
fmt_date_and_time(GString *s, guchar *data, gsize len)
{
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
fmt_enum(GString *s, int width, stls_table_t const *table, gint32 *number)
{
    gchar *name;

    if (! number) {
	g_string_sprintfa(s, "%*s", width, "");
	return;
    }
    
    name = stls_table_get_value(table, *number);
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
fmt_port(int port, int name)
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
