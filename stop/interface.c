/* 
 * interface.c -- stop interface mode implementation
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

#include "snmpv2-mib.h"
#include "if-mib.h"


extern time_t timezone;


typedef struct {
    guint32 inOctets;
    guint32 outOctets;
    guint32 inPkts;
    guint32 outPkts;
} if_stats_t;



static char*
fmt_time_ticks(guint32 timeticks)
{
    static char buffer[80];
    time_t now;
    struct tm *tm;
    
    now = time(NULL);
    now -= timeticks/100;
    tm = gmtime(&now);

    g_snprintf(buffer, sizeof(buffer),
	       "%04d-%02d-%02d %02d:%02d:%02d %c%02d:%02d",
	       tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
	       tm->tm_hour, tm->tm_min, tm->tm_sec,
	       timezone < 0 ? '+' : '-',
	       (int) ABS(timezone) / 60 / 60, (int) (ABS(timezone) / 60) % 60);
    
    return buffer;
}



static char *
fmt_ifStatus(gint32 *admin, gint32 *oper)
{
    static char buffer[5];
    
    if (admin) {
	switch (*admin) {
	case 1: strcpy(buffer, "U"); break;
	case 2: strcpy(buffer, "D"); break;
	case 3: strcpy(buffer, "T"); break;
	default: strcpy(buffer, "?"); break;
	}
    } else {
	strcpy(buffer, "-");
    }
    strcat(buffer, "/");
    if (oper) {
	switch (*oper) {
	case 1: strcat(buffer, "U"); break;
	case 2: strcat(buffer, "D"); break;
	case 3: strcat(buffer, "T"); break;
	case 4: strcat(buffer, "?"); break;
	case 5: strcat(buffer, "M"); break;
	case 6: strcat(buffer, "N"); break;
	case 7: strcat(buffer, "L"); break;
	default: strcat(buffer, "?"); break;
	}
    } else {
	strcat(buffer,"-");
    }

    return buffer;
}



static char*
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



static char*
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



static void
show_interface_summary(host_snmp *peer)
{
    system_t *system = NULL;
    interfaces_t *interfaces = NULL;
    ifMIBObjects_t *ifMIBObjects = NULL;
    GString *s;

    g_return_if_fail(peer);

    s = g_string_new("Interface: ");
    
    if (if_mib_get_interfaces(peer, &interfaces) == 0 && interfaces) {
	if (interfaces->ifNumber) {
	    g_string_sprintfa(s, "%d interfaces",
			      *(interfaces->ifNumber));
	}
	if_mib_free_interfaces(interfaces);
    }

    if (if_mib_get_ifMIBObjects(peer, &ifMIBObjects) == 0
	&& ifMIBObjects) {
	if (snmpv2_mib_get_system(peer, &system) == 0 && system) {
    
	    if (ifMIBObjects->ifTableLastChange && system->sysUpTime) {
		guint32 dsecs = *(system->sysUpTime)
		    - *(ifMIBObjects->ifTableLastChange);
		g_string_sprintfa(s, ", last create/delete %s",
				  fmt_time_ticks(dsecs));
	    }
	    snmpv2_mib_free_system(system);
	}
	if_mib_free_ifMIBObjects(ifMIBObjects);
    }
    
    stop_show_mode_summary_line(s->str);
    g_string_free(s, 1);
}



static void
show_interfaces(WINDOW *win, host_snmp *peer, int flags)
{
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    static struct timeval last, now;
    double delta;
    int i;
    static if_stats_t *stats = NULL;

    if (flags & STOP_FLAG_RESTART) {
	show_interface_summary(peer);
	wattron(win, A_REVERSE);
	mvwprintw(win, 0, 0, "%-*s",
		  COLS, "INDEX STAT   MTU SPEED I-BPS O-BPS I-PPS O-PPS  DESCR ...");
	wattroff(win, A_REVERSE);
	wrefresh(win);
	sleep(1);
	if (stats) {
	    g_free(stats);
	    stats = NULL;
	}
    }

    if (if_mib_get_ifTable(peer, &ifTable) == 0) {
	(void) if_mib_get_ifXTable(peer, &ifXTable);
    }

    if (! stats && ifTable) {
	for (i = 0; ifTable[i]; i++) ;
	stats = (if_stats_t *) g_malloc0(i * sizeof(if_stats_t));
    }

    gettimeofday (&now, NULL);
    delta = TV_DIFF(last, now);

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    GString *s;
	    s = g_string_new(NULL);
	    g_string_sprintfa(s, "%5u", ifTable[i]->ifIndex);
	    g_string_sprintfa(s, " %4s",
			      fmt_ifStatus(ifTable[i]->ifAdminStatus,
					   ifTable[i]->ifOperStatus));
	    if (ifTable[i]->ifMtu) {
		g_string_sprintfa(s, " %5d", *(ifTable[i]->ifMtu));
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    if (ifTable[i]->ifSpeed) {
		if (*(ifTable[i]->ifSpeed) == 0xffffffff
		    && ifXTable && ifXTable[i]->ifHighSpeed) {
		    g_string_sprintfa(s, " %5s",
				      fmt_gtp(*(ifXTable[i]->ifHighSpeed)));
		} else {
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg(*(ifTable[i]->ifSpeed)));
		}
	    } else {
		g_string_sprintfa(s, "  ----");
	    }

	    if (ifTable[i]->ifInOctets && delta > TV_DELTA) {
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (*(ifTable[i]->ifInOctets) - stats[i].inOctets) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].inOctets = *(ifTable[i]->ifInOctets);
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    if (ifTable[i]->ifOutOctets && delta > TV_DELTA) {
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (*(ifTable[i]->ifOutOctets) - stats[i].outOctets) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].outOctets = *(ifTable[i]->ifOutOctets);
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    if (ifTable[i]->ifInUcastPkts && delta > TV_DELTA) {
		guint32 pkts;
		pkts = *(ifTable[i]->ifInUcastPkts);
		if (ifXTable && ifXTable[i]->ifInMulticastPkts
		    && ifXTable[i]->ifInBroadcastPkts) {
		    pkts += *(ifXTable[i]->ifInMulticastPkts);
		    pkts += *(ifXTable[i]->ifInBroadcastPkts);
		} else if (ifTable[i]->ifInNUcastPkts) {
		    pkts += *(ifTable[i]->ifInNUcastPkts);
		} else {
		    /* might be fixed length ??? */
		}
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (pkts - stats[i].inPkts) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].inPkts = pkts;
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    if (ifTable[i]->ifOutUcastPkts && delta > TV_DELTA) {
		guint32 pkts;
		pkts = *(ifTable[i]->ifOutUcastPkts);
		if (ifXTable && ifXTable[i]->ifOutMulticastPkts
		    && ifXTable[i]->ifOutBroadcastPkts) {
		    pkts += *(ifXTable[i]->ifOutMulticastPkts);
		    pkts += *(ifXTable[i]->ifOutBroadcastPkts);
		} else if (ifTable[i]->ifOutNUcastPkts) {
		    pkts += *(ifTable[i]->ifOutNUcastPkts);
		} else {
		    /* might be fixed length ??? */
		}
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (pkts - stats[i].outPkts) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].outPkts = pkts;
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    if (ifTable[i]->ifDescr && ifTable[i]->_ifDescrLength) {
		g_string_sprintfa(s, "  %.*s",
				  (int) ifTable[i]->_ifDescrLength,
				  ifTable[i]->ifDescr);
	    }
	    g_string_truncate(s, COLS);
	    mvwprintw(win, i+1, 0, s->str);
	    g_string_free(s, 1);
	}
    }
    
    last = now;
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);
}



void
stop_init_interface_mode()
{
    static stop_mode_t interface_mode = {
	"interface",
	"Display information about the network interfaces",
	&show_interfaces
    };
    
    stop_register_mode(&interface_mode);
}
