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

#include "scli.h"

#include "snmpv2-tm.h"


#include <ctype.h>
#include <time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <net/if.h>
#ifdef HAVE_NETINET_IF_ETHER_H
#include <netinet/if_ether.h>
#endif
#ifdef HAVE_NETINET_ETHER_H
#include <netinet/ether.h>
#endif



static guint32 const snmpUDPDomain[]
	= { SNMPV2_TM_SNMPUDPDOMAIN };
static guint32 const snmpCLNSDomain[]
	= { SNMPV2_TM_SNMPCLNSDOMAIN };
static guint32 const snmpCONSDomain[]
	= { SNMPV2_TM_SNMPCONSDOMAIN };
static guint32 const snmpDDPDomain[]
	= { SNMPV2_TM_SNMPDDPDOMAIN };
static guint32 const snmpIPXDomain[]
	= { SNMPV2_TM_SNMPIPXDOMAIN };
static guint32 const rfc1157Domain[]
	= { SNMPV2_TM_RFC1157DOMAIN };

static GSnmpIdentity const tdomain_identities[] = {
    { snmpUDPDomain,
      sizeof(snmpUDPDomain)/sizeof(guint32),
      "udp" },
    { snmpCLNSDomain,
      sizeof(snmpCLNSDomain)/sizeof(guint32),
      "clns" },
    { snmpCONSDomain,
      sizeof(snmpCONSDomain)/sizeof(guint32),
      "cons" },
    { snmpDDPDomain,
      sizeof(snmpDDPDomain)/sizeof(guint32),
      "ddp" },
    { snmpIPXDomain,
      sizeof(snmpIPXDomain)/sizeof(guint32),
      "ipx" },
    { rfc1157Domain,
      sizeof(rfc1157Domain)/sizeof(guint32),
      "rfc1157" },
    { 0, 0, NULL }
};



char const *
fmt_timeticks(guint32 timeticks)
{
    static char buffer[80];
    time_t now, gmt;
    struct tm *tm, now_tm;
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
    now_tm = *tm;	/* make a copy since mktime() below can modify tm */
    tm->tm_isdst = 0;
    gmt_offset = mktime(tm) - gmt;

    g_snprintf(buffer, sizeof(buffer),
	       "%04d-%02d-%02d %02d:%02d:%02d %c%02d:%02d",
	       now_tm.tm_year + 1900, now_tm.tm_mon + 1, now_tm.tm_mday,
	       now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec,
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
fmt_date_and_time(guchar *data, gsize len)
{
    static char buffer[80];
    int i;

    buffer[0] = 0;
    if (! data) {
	return buffer;
    }
    
    /*
     * Check if it is a null value consisting of all 0x00 bytes or if
     * it has a length of 0 (not really legal, but people sometimes
     * do it this way).
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

    g_snprintf(buffer, sizeof(buffer), "%3d:%02d:%02d", hour, min, sec);

    return buffer;
}



void
xxx_enum(GString *s, int width, GSnmpEnum const *table, gint32 *number)
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
fmt_enum(GSnmpEnum const *table, gint32 *number)
{
    static char buffer[80];
    gchar const *name;

    if (! number) {
	return NULL;
    }

    name = gsnmp_enum_get_label(table, *number);
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
fmt_udp_port(unsigned short int port, int flags)
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
fmt_tcp_port(unsigned short int port, int flags)
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
    g_snprintf(buffer, sizeof(buffer), "%u", prefix);
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



void
fmt_indent_string(GString *s, int indent, char *label, int len, char *string)
{
    int i;
    
    g_string_sprintfa(s, "%-*s", indent, label);

    for (i = 0; i < len; i++) {
	if (string[i] == '\r') continue;
	if (string[i] == '\n') {
	    g_string_sprintfa(s, "\n%*s", indent, "");
	} else {
	    if (isprint(string[i])) {
		g_string_append_c(s, string[i]);
	    } else {
		g_string_sprintfa(s, "\\%o", string[i]);
	    }
	}
    }
    g_string_append_c(s, '\n');
}


void
fmt_display_string(GString *s, int indent, char *label, int len, char *string)
{
    int i, pos;
    
    g_string_sprintfa(s, "%-*s", indent, label);
    pos = indent;

    /* Remove leading and trailing white-space characters first. */

    while (len && isspace(string[0])) {
	string++, len--;
    }
    while (len && isspace(string[len-1])) {
	len--;
    }

    /* Split long strings into chunks so that the text fits on
       a 80 column display. Display non-printable characters as
       special sequences such as \245. */
    
    for (i = 0; i < len; i++) {
	if (string[i] == '\r') continue;
	if (isspace(string[i])) {
	    int j, p;
	    for (j = i+1, p = pos; p < 80 && j < len; p++, j++) {
		if (string[j] != '\r' && isspace(string[j])) break;
	    }
	    if (p == 80) {
		g_string_sprintfa(s, "\n%*s", indent, "");
		pos = indent;
		continue;
	    }
	}
	if (string[i] != '\n') {
	    if (isprint(string[i])) {
		g_string_append_c(s, string[i]);
		pos++;
	    } else {
		g_string_sprintfa(s, "\\%o", string[i]);
		pos += 4;
	    }
	}
    }
    g_string_append_c(s, '\n');
}



const char *
fmt_tdomain(guint32 *tdomain, gsize tdomain_len)
{
    const char *e;

    e = gsnmp_identity_get_label(tdomain_identities, tdomain, tdomain_len);

    return e;
}



const char *
fmt_taddress(guint32 *tdomain, gsize tdomain_len,
	     guchar *taddress, gsize taddress_len)
{
    static char *e = NULL;
    int i;

    if (e) {
	g_free(e);
	e = NULL;
    }

    if (! tdomain && taddress) {
	return NULL;
    }

    for (i = 0; tdomain_identities[i].label; i++) {
	if (tdomain_identities[i].oidlen == tdomain_len
	    && memcmp(tdomain_identities[i].oid, tdomain, tdomain_len * sizeof(guint32)) == 0) {
	    break;
	}
    }
    
    if (tdomain_identities[i].label) {
	switch (i) {
	case 0:
	    if (taddress_len == 6) {
		e = g_strdup_printf("%d.%d.%d.%d:%d",
				    taddress[0], taddress[1], taddress[2], taddress[3],
				    (taddress[4] << 8) + taddress[5]);
	    } else {
		g_warning("invalid taddress value");
	    }
	    break;
	default:
	    break;
	}
    }

    if (! e) {
	e = g_malloc0(3 + taddress_len * 2);
	strcpy(e, "0x");
	for (i = 0; i < taddress_len; i++) {
	    sprintf(e + strlen(e), "%02x", taddress[i]);
	}
    }

    return e;
}



void
fmt_row_status(GString *s, gint32 *status)
{
    static GSnmpEnum const row_states[] = {
	{ 1, "A" },	/* active */
	{ 2, "S" },	/* notInService */
	{ 3, "R" },	/* notReady */
	{ 0, NULL }
    };

    const char *label;

    if (! status) {
	g_string_append(s, " ");
	return;
    }

    label = gsnmp_enum_get_label(row_states, *status);
    if (label) {
	g_string_append(s, label);
    } else {
	g_string_append(s, "-");
    }
}



void
fmt_storage_type(GString *s, gint32 *storage)
{
    static GSnmpEnum const storage_types[] = {
	{ 1, "O" },	/* other */
	{ 2, "V" },	/* volatile */
	{ 3, "N" },	/* nonVolatile */
	{ 4, "P" },	/* permanent */
	{ 5, "R" },	/* readOnly */
	{ 0, NULL }
    };
    
    const char *label;
    
    if (! storage) {
	g_string_append(s, " ");
	return;
    }
    
    label = gsnmp_enum_get_label(storage_types, *storage);
    if (label) {
	g_string_append(s, label);
    } else {
	g_string_append(s, "-");
    }
}



void
fmt_port_set(GString *s, guchar *bits, gsize bits_len)
{
    int bit, i;
    int first = -1;
    int n = 0;

    for (i = 0; i < bits_len * 8; i++) {
	bit = bits[i/8] & 1 << (7-(i%8));
	if (bit) {
	    if (first < 0) {
		first = i;
	    }
	} else {
	    if (first >= 0) {
		if (n) {
		    g_string_append_c(s, ',');
		}
		if (first == i-1) {
		    g_string_sprintfa(s, "%d", first);
		} else {
		    g_string_sprintfa(s, "%d-%d", first, i-1);
		}
		n++;
	    }
	    first = -1;
	}
    }
    if (first >= 0) {
	g_string_sprintfa(s, "%s%d-%d", n ? ", " : "", first, i-1);
    }
}



int
scan_port_set(guchar *bits, gsize bits_len, char *string)
{
    char *p = string;
    int i, from, to, off;

    memset(bits, 0, bits_len);
    while (*p) {
	if (sscanf(p, "%d-%d%n", &from, &to, &off) == 2) {
	    p += off;
	} else if (sscanf(p, "%d%n", &from, &off) == 1) {
	    p += off;
	    to = from;
	} else {
	    memset(bits, 0, bits_len);
	    return SCLI_ERROR;
	}
	if (from < 0 || to >= bits_len*8) {
	    memset(bits, 0, bits_len);
	    return SCLI_ERROR;
	}
	for (i = from; i < to+1; i++) {
	    bits[i/8] |= (1 <<(7-(i%8)));
	}
	if (*p == ',') p++;
    }

    return SCLI_OK;
}



