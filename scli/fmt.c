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
#include <net/if.h>
#ifdef HAVE_NETINET_IF_ETHER_H
#include <netinet/if_ether.h>
#endif
#ifdef HAVE_NETINET_ETHER_H
#include <netinet/ether.h>
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



char const *
fmt_date_and_time(guchar *data, gsize len)
{
    static char buffer[80];
    int i;

    if (! data) {
	buffer[0] = 0;
	return buffer;
    }
    
    /*
     * Check if it is a null value consisting of all 0x00 bytes or if
     * it has a length of 0 (not really legal, but people sometimes
     * do it this way.
     */

    for (i = 0; i < len; i++) {
	if (data[i]) break;
    }

    if (len == 0 || i == len) {
	strcpy(buffer, "-");
	return buffer;
    }

    /*
     * The two normal cases for DateAndTime are handled below.
     */
    
    if (len == 8) {
	g_snprintf(buffer, sizeof(buffer),
		   "%04u-%02u-%02u %02u:%02u:%02u",
		   (data[0] << 8) + data[1], data[2], data[3],
		   data[4], data[5], data[6]);
    } else if (len == 11) {
	g_snprintf(buffer, sizeof(buffer),
		   "%04u-%02u-%02u %02u:%02u:%02u %c%02u:%02u",
		   (data[0] << 8) + data[1], data[2], data[3],
		   data[4], data[5], data[6],
		   data[8], data[9], data[10]);
    }
    return buffer;
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
fmt_seconds(guint32 seconds)
{
    static char buffer[80];
    guint32 sec, min, hour;

    sec  = (seconds) % 60;
    min  = (seconds / 60) % 60;
    hour = (seconds / 60 / 60);

    g_snprintf(buffer, sizeof(buffer), "%2d:%02d:%02d", hour, min, sec);

    return buffer;
}



char const *
fmt_kbytes(guint32 kbytes)
{
    static char buffer[80];
    
    if (kbytes > 9999999) {
	g_snprintf(buffer, sizeof(buffer), "%u GByte", kbytes / 1024 / 1024);
    } else if (kbytes > 9999) {
	g_snprintf(buffer, sizeof(buffer), "%u MByte", kbytes / 1024);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%u KByte", kbytes);
    }
    return buffer;
}



void
xxx_enum(GString *s, int width, stls_enum_t const *table, gint32 *number)
{
    gchar const *name;

    name = fmt_enum(table, number);
    if (name) {
	g_string_sprintfa(s, "%-*s", width, name);
    } else {
	g_string_sprintfa(s, "%*s", width, "");
    }
}



char const *
fmt_enum(stls_enum_t const *table, gint32 *number)
{
    static char buffer[80];
    gchar const *name;

    if (! number) {
	return NULL;
    }

    name = stls_enum_get_label(table, *number);
    if (! name) {
	g_snprintf(buffer, sizeof(buffer), "%d", *number);
	return buffer;
    } else {
	return name;
    }
}



char const *
fmt_kmg(guint32 number)
{
    static char buffer[80];

    if (number > 999999999) {
	g_snprintf(buffer, sizeof(buffer), "%3ug", number / 1000000000);
    } else if (number > 999999) {
	g_snprintf(buffer, sizeof(buffer), "%3um", number / 1000000);
    } else if (number > 9999) {
	g_snprintf(buffer, sizeof(buffer), "%3uk", number / 1000);
    } else {
	g_snprintf(buffer, sizeof(buffer), "%4u", number);
    }
    return buffer;
}



char const *
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
fmt_udp_port(int port, int flags)
{
    struct servent *s;
    static char buffer[12];

    if (flags & SCLI_FMT_NAME) {
	if (! port) {
	    return "*";
	}
	s = getservbyport(htons(port), "udp");
	if (s) {
	    return s->s_name;
	}
    }
    if (flags & SCLI_FMT_ADDR) {
	sprintf(buffer, "%d", port);
	return buffer;
    }
    return NULL;
}



char*
fmt_tcp_port(int port, int flags)
{
    struct servent *s;
    static char buffer[12];

    if (flags & SCLI_FMT_NAME) {
	if (! port) {
	    return "*";
	}
	s = getservbyport(htons(port), "tcp");
	if (s) {
	    return s->s_name;
	}
    }
    if (flags & SCLI_FMT_ADDR) {
	g_snprintf(buffer, sizeof(buffer), "%d", port);
	return buffer;
    }
    return NULL;
}



char*
fmt_ipv4_address(guchar *addr, int flags)
{
    static char buffer[16];
    struct hostent *h;

    if (flags & SCLI_FMT_NAME) {
	if (! addr[0] && ! addr[1] && ! addr[2] && ! addr[3]) {
	    return "*";
	}
	h = gethostbyaddr((char *) addr, 4, AF_INET);
	if (h) {
	    return h->h_name;
	}
    }
    if (flags & SCLI_FMT_ADDR) {
	g_snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d",
		   addr[0], addr[1], addr[2], addr[3]);
	return buffer;
    }
    return NULL;
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
    g_snprintf(buffer, sizeof(buffer), "/%u", prefix);
    return buffer;
}


char *
fmt_ether_address(guchar *addr, int flags)
{
    static char buffer[256]; /* xxx */

    if (flags & SCLI_FMT_NAME) {
#ifdef HAVE_ETHER_NTOHOST
	if (ether_ntohost(buffer, (struct ether_addr *) addr) == 0) {
	    return buffer;
	}
#endif
    }
    if (flags & SCLI_FMT_ADDR) {
	g_snprintf(buffer, sizeof(buffer), "%02x:%02x:%02x:%02x:%02x:%02x",
		   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
	return buffer;
    }
    return NULL;
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

