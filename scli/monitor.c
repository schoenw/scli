/* 
 * monitor.c -- basic monitor functions for the scli command interpreter
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

#include "snmpv2-mib.h"
#include "ip-mib.h"
#include "udp-mib.h"
#include "tcp-mib.h"

#include <ctype.h>
#include <errno.h>
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_NCURSES_H
#include <ncurses.h>
#else
#include <curses.h>
#endif


/*
 * Flags that are passed to the mode driver in order to give him a
 * chance to redraw the screen or to recover from a discontinuity.
 */

#define STOP_FLAG_RESTART       0x01	/* restart everything */
#define STOP_FLAG_DONE          0x02	/* stop is quitting */
#define STOP_FLAG_NODELAY	0x04	/* sometimes we have no delay */
#define STOP_FLAG_SNMP_FAILURE	0x08	/* indicates a previous SNMP
					   failure in this poll */
static int sys_des_line = 0;
static int sys_con_line = 0;
static int sys_loc_line = 0;
static int ipv4_line = 0;
#ifdef IPV6
static int ipv6_line = 0;
#endif
static int udp_line = 0;
static int tcp_line = 0;
static int status_line = 0;
static int mode_line = 0;

static int do_contact_summary = 0;
static int do_network_summary = 1;
static int do_transport_summary = 1;
static int do_mode_summary = 1;

static WINDOW *mode_win = NULL;


static void
fix_string(guchar *s, guint16 *len)
{
    int i;

    for (i = 0; i < *len; i++) {
        if (s[i] == '\r' || s[i] == '\n') s[i] = ' ';
    }
}



static void
snmp_decode_hook(GList *list)
{
    static char x[] = { '-', '/', '-', '\\', '|' };
    static int i = 0;
    char buffer[80];

    if (! list) {
	i = 0;
	return;
    }

    i = (i+1) % 5;
    g_snprintf(buffer, sizeof(buffer), "%c", x[i]);
    
    move(status_line, 0);
    clrtoeol();
    attron(A_BOLD);
    addstr(buffer);
    attroff(A_BOLD);
    move(status_line, 0);
    refresh();
}



static void
page(WINDOW *win, scli_interp_t *interp)
{
    char *s, *e;
    int y = 0;

    wattron(win, A_REVERSE);
    mvwprintw(win, y++, 0, "%-*s", COLS,
	      interp->header->len ? interp->header->str : " ");
    wattroff(win, A_REVERSE);
    wclrtobot(win);
    if (interp->result->len) {
	for (s = interp->result->str; s; s = e ? ++e : NULL) {
	    e = strchr(s, '\n');
	    if (e) *e = 0;
	    mvwprintw(win, y++, 0, "%s", s);
	}
    }
    wclrtobot(win);
    wrefresh(win);
}



static void
show_message(const char *message)
{
    move(status_line, 0);
    clrtoeol();
    attron(A_BOLD);
    addstr(message);
    attroff(A_BOLD);
    refresh();
    sleep(1);
}



static void
show_mode_summary(char *string)
{
    move(mode_line, 0);
    mvprintw(mode_line, 0, "Command:  %.*s",
	     MIN(strlen(string), COLS-10), string);
    clrtoeol();
}



static char*
prompt(char *message)
{
    static char buffer[80];

    move(status_line, 0);
    clrtoeol();
    addstr(message);
    timeout(-1);
    (void) echo();
    if (wgetnstr(stdscr, buffer, sizeof(buffer)) == ERR) {
        strcpy(buffer, "");
    }
    (void) noecho();
    move(status_line, 0);
    clrtoeol();
    return buffer;
}



static int
show_system(GNetSnmp *peer, int flags)
{
    snmpv2_mib_system_t *system = NULL;
    static struct timeval last, now;
    static guint32 sysUpTime = 0;
    char timestr[10];
    struct tm *now_tm;
    int mask = (SNMPV2_MIB_SYSDESCR | SNMPV2_MIB_SYSUPTIME);

    if (flags & STOP_FLAG_RESTART) {
        last.tv_sec = last.tv_usec = 0;
    }

    gettimeofday (&now, NULL);
    now_tm = localtime(&now.tv_sec);
    if (now_tm) {
        strftime(timestr, sizeof(timestr), "%T", now_tm);
    } else {
        strcpy(timestr, "--:--:--");
    }

    if (do_contact_summary) {
	mask |= SNMPV2_MIB_SYSCONTACT;
	mask |= SNMPV2_MIB_SYSLOCATION;
    }
    snmpv2_mib_get_system(peer, &system, mask);
    if (peer->error_status) {
	GURI *uri;
	gchar *name = NULL;
	uri = gnet_snmp_get_uri(peer);
	if (uri) {
	    name = gnet_uri_get_string(uri);
	}
        move(0, 10);
        clrtoeol();
        mvprintw(0, 10, "%s", name ? name : "?");
        mvaddstr(0, (int) (COLS-strlen(timestr)-1), timestr);
	if (name) g_free(name);
        return STOP_FLAG_SNMP_FAILURE;
    }

    if (system) {
    
	if (system->sysUpTime) {
	    unsigned days, hours, minutes, seconds;
	    guint32 secs;
	    gchar *name = NULL;
	    GURI *uri;
	    if (last.tv_sec && last.tv_usec) {
		if (sysUpTime > *(system->sysUpTime)) {
		    return STOP_FLAG_RESTART;
		}
	    }
	    secs = *(system->sysUpTime)/100;
	    days = secs / (24 * 60 * 60);
	    hours = (secs / (60 * 60)) % 24;
	    minutes = (secs / 60) % 60;
	    seconds = secs % 60;
	    move(0, 10);
	    clrtoeol();
	    uri = gnet_snmp_get_uri(peer);
	    if (uri) {
		name = gnet_uri_get_string(uri);
	    }
	    mvprintw(0, 10, "%s up %d %s %02d:%02d:%02d",
		     name ? name : "?",
		     days, (days == 1) ? "day" : "days",
		     hours, minutes, seconds);
	    sysUpTime = *(system->sysUpTime);
	    if (name) g_free(name);
	}
	if (system->sysDescr) {
	    fix_string(system->sysDescr, &(system->_sysDescrLength));
	    mvprintw(sys_des_line, 10, "%.*s",
		     MIN(system->_sysDescrLength, COLS-11),
		     system->sysDescr);
	    clrtoeol();
	}
	if (do_contact_summary
	    && system->sysContact && system->_sysContactLength) {
	    fix_string(system->sysContact, &(system->_sysContactLength));
	    mvprintw(sys_con_line, 10, "%.*s",
		 MIN(system->_sysContactLength, COLS-11),
		     system->sysContact);
	    clrtoeol();
	}
	if (do_contact_summary
	    && system->sysLocation && system->_sysLocationLength) {
	    fix_string(system->sysLocation, &(system->_sysLocationLength));
	    mvprintw(sys_loc_line, 10, "%.*s",
		     MIN(system->_sysLocationLength, COLS-11),
		     system->sysLocation);
	    clrtoeol();
	}
    }
    
    last = now;
    if (system) snmpv2_mib_free_system(system);
    mvaddstr(0, (int) (COLS-strlen(timestr)-1), timestr);
    return 0;
}



static void
show_ip(GNetSnmp *peer, int flags)
{
    ip_mib_ip_t *ip = NULL;
    static guint32 ipInReceives = 0;
    static guint32 ipForwDatagrams = 0;
    static guint32 ipReasmOKs = 0;
    static guint32 ipFragOKs = 0;
    static guint32 ipOutSent = 0;
    static struct timeval last, now;
    double delta;
    int mask = IP_MIB_IPFORWDATAGRAMS | IP_MIB_IPINRECEIVES |
	    IP_MIB_IPOUTREQUESTS | IP_MIB_IPOUTDISCARDS |
	    IP_MIB_IPOUTNOROUTES | IP_MIB_IPFRAGOKS |
	    IP_MIB_IPFRAGFAILS | IP_MIB_IPFRAGCREATES |
	    IP_MIB_IPREASMOKS;

    if (flags & STOP_FLAG_RESTART) {
        last.tv_sec = last.tv_usec = 0;
    }

    ip_mib_get_ip(peer, &ip, mask);
    if (peer->error_status || !ip) {
        return;
    }
    
    gettimeofday(&now, NULL);
    delta = TV_DIFF(last, now);
    if (ip->ipInReceives && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipInReceives) - ipInReceives) / delta;
            mvprintw(ipv4_line, 10, (char *) fmt_kmg((guint32) f_val));
        }
        ipInReceives = *(ip->ipInReceives);
    } else {
        mvprintw(ipv4_line, 10, "----");
    }
    
    if (ip->ipForwDatagrams
        && ip->ipOutRequests
        && ip->ipOutDiscards
        && ip->ipOutNoRoutes
        && ip->ipFragOKs
        && ip->ipFragFails
        && ip->ipFragCreates && delta > TV_DELTA) {
        guint32 ipOut;
        ipOut = *(ip->ipOutRequests)
            + *(ip->ipForwDatagrams)
            - *(ip->ipOutDiscards)
            - *(ip->ipOutNoRoutes)
            - *(ip->ipFragOKs)
            - *(ip->ipFragFails)
            + *(ip->ipFragCreates);
        if (last.tv_sec && last.tv_usec) {
            mvprintw(ipv4_line, 22,
	     (char *) fmt_kmg((guint32) ((ipOut - ipOutSent) / delta)));
        }
        ipOutSent = ipOut;
    } else {
        mvprintw(ipv4_line, 22, "----");
    }
    
    if (ip->ipForwDatagrams && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipForwDatagrams) - ipForwDatagrams) / delta;
            mvprintw(ipv4_line, 35, (char *) fmt_kmg((guint32) f_val));
        }
        ipForwDatagrams = *(ip->ipForwDatagrams);
    } else {
        mvprintw(ipv4_line, 35, "----");
    }
    
    if (ip->ipReasmOKs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipReasmOKs) - ipReasmOKs) / delta;
            mvprintw(ipv4_line, 48, (char *) fmt_kmg((guint32) f_val));
        }
        ipReasmOKs = *(ip->ipReasmOKs);
    } else {
        mvprintw(ipv4_line, 48, "----");
    }
    
    if (ip->ipFragOKs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipFragOKs) - ipFragOKs) / delta;
	    mvprintw(ipv4_line, 62, (char *) fmt_kmg((guint32) f_val));
        }
        ipFragOKs = *(ip->ipFragOKs);
    } else {
        mvprintw(ipv4_line, 62, "----");
    }
    
    last = now;
    ip_mib_free_ip(ip);
}


static void
show_udp(GNetSnmp *peer, int flags)
{
    udp_mib_udp_t *udp = NULL;
    static guint32 udpInDatagrams = 0;
    static guint32 udpOutDatagrams = 0;
    static struct timeval last, now;
    double delta;
    int mask = (UDP_MIB_UDPINDATAGRAMS | UDP_MIB_UDPOUTDATAGRAMS);
    
    if (flags & STOP_FLAG_RESTART) {
        last.tv_sec = last.tv_usec = 0;
    }

    udp_mib_get_udp(peer, &udp, mask);
    if (peer->error_status || !udp) {
        return;
    }

    gettimeofday (&now, NULL);
    delta = TV_DIFF(last, now);
    if (udp->udpInDatagrams && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(udp->udpInDatagrams) - udpInDatagrams) / delta;
            mvprintw(udp_line, 10, (char *) fmt_kmg((guint32) f_val));
        }
        udpInDatagrams = *(udp->udpInDatagrams);
    } else {
        mvprintw(udp_line, 10, "----");
    }
    if (udp->udpOutDatagrams && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(udp->udpOutDatagrams) - udpOutDatagrams) / delta;
            mvprintw(udp_line, 22, (char *) fmt_kmg((guint32) f_val));
        }
        udpOutDatagrams = *(udp->udpOutDatagrams);
    } else {
        mvprintw(udp_line, 22, "----");
    }

    last = now;
    udp_mib_free_udp(udp);
}



static void
show_tcp(GNetSnmp *peer, int flags)
{
    tcp_mib_tcp_t *tcp = NULL;
    static guint32 tcpInSegs = 0;
    static guint32 tcpOutSegs = 0;
    static guint32 tcpActiveOpens = 0;
    static guint32 tcpPassiveOpens = 0; 
    static struct timeval last, now;
    double delta;
    int mask = (TCP_MIB_TCPINSEGS | TCP_MIB_TCPOUTSEGS | TCP_MIB_TCPCURRESTAB
	| TCP_MIB_TCPACTIVEOPENS | TCP_MIB_TCPPASSIVEOPENS);

    if (flags & STOP_FLAG_RESTART) {
        last.tv_sec = last.tv_usec = 0;
    }

    tcp_mib_get_tcp(peer, &tcp, mask);
    if (peer->error_status || !tcp) {
        return;
    }

    gettimeofday (&now, NULL);
    delta = TV_DIFF(last, now);
    if (tcp->tcpInSegs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpInSegs) - tcpInSegs) / delta;
            mvprintw(tcp_line, 10, (char *) fmt_kmg((guint32) f_val));
        }
        tcpInSegs = *(tcp->tcpInSegs);
    } else {
        mvprintw(tcp_line, 10, "----");
    }
    if (tcp->tcpOutSegs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpOutSegs) - tcpOutSegs) / delta;
            mvprintw(tcp_line, 22, (char *) fmt_kmg((guint32) f_val));
        }
        tcpOutSegs = *(tcp->tcpOutSegs);
    } else {
        mvprintw(tcp_line, 22, "----");
    }
    if (tcp->tcpCurrEstab) {
        mvprintw(tcp_line, 35, (char *) fmt_kmg(*(tcp->tcpCurrEstab)));
    } else {
        mvprintw(tcp_line, 35, "----");
    }
    if (tcp->tcpActiveOpens && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpActiveOpens) - tcpActiveOpens) / delta;
            mvprintw(tcp_line, 48, (char *) fmt_kmg((guint32) f_val));
        }
        tcpActiveOpens = *(tcp->tcpActiveOpens);
    } else {
        mvprintw(tcp_line, 48, "----");
    }
    if (tcp->tcpPassiveOpens && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpPassiveOpens) - tcpPassiveOpens) / delta;
            mvprintw(tcp_line, 62, (char *) fmt_kmg((guint32) f_val));
        }
	tcpPassiveOpens = *(tcp->tcpPassiveOpens);
    } else {
        mvprintw(tcp_line, 62, "----");
    }

    last = now;
    tcp_mib_free_tcp(tcp);
}



static void
show_interior(GNetSnmp *peer)
{
    int y = 0;
    GURI *uri;
    gchar *name = NULL;

    uri = gnet_snmp_get_uri(peer);
    if (uri) {
	name = gnet_uri_get_string(uri);
    }
    
    clear();
    y = 0;
    mvprintw(y, 10, "%s", name ? name : "?");
    if (name) g_free(name); name = NULL;
    mvaddstr(y++, 0, "Agent:");
    sys_des_line = y;
    mvaddstr(y++, 0, "Descr:");
    if (do_contact_summary) {
        sys_con_line = y;
        mvaddstr(y++, 0, "Contact:");
        sys_loc_line = y;
        mvaddstr(y++, 0, "Location:");
    }
    if (do_network_summary) {
        ipv4_line = y;
        mvaddstr(y++, 0, "IPv4:     ---- pps in ---- pps out ---- pps fwd ---- pps rasm ---- pps frag");
#ifdef IPV6
        ipv6_line = y;
        mvaddstr(y++, 0, "IPv6:     ---- pps in ---- pps out");
#endif
    }
    if (do_transport_summary) {
        udp_line = y;
        mvaddstr(y++, 0, "UDP:      ---- pps in ---- pps out");
        tcp_line = y;
        mvaddstr(y++, 0, "TCP:      ---- sps in ---- sps out ---- con est ---- con aopn ---- con popn");
    }
    if (do_mode_summary) {
	mode_line = y++;
    }
    status_line = y++;

    if (mode_win) {
	delwin(mode_win);
    }
    mode_win = newwin(LINES-y, COLS, y, 0);
}



static void
help(scli_cmd_t *cmd, int argc, char **argv)
{
    int y = 0;
    
    clear();
    mvprintw(y++, 0, "scli version %s %s", VERSION, scli_copyright);
    y++;
    mvprintw(y++, 0, "Interactive monitor commands are:");
    y++;
    mvprintw(y++, 0, "space\tUpdate the display");
    mvprintw(y++, 0, "^L\tRedraw the screen");
    mvprintw(y++, 0, "h or ?\tPrint this list");
    mvprintw(y++, 0, "c\tToggle display of contact summary information");
    mvprintw(y++, 0, "d\tSet the delay in seconds between updates");
    mvprintw(y++, 0, "m\tToggle display of mode specific summary information");
    mvprintw(y++, 0, "n\tToggle display of network layer summary information");
    mvprintw(y++, 0, "t\tToggle display of transport layer summary information");
    mvprintw(y++, 0, "w\tFreeze the screen until someone hits a key");
    mvprintw(y++, 0, "q\tQuit the monitoring mode");
    mvprintw(y++, 0, "x\tExit scli immediately");
    y++;
    mvprintw(y++, 0, "Press any key to continue");
    timeout(-1);
    (void) getch();
    clear();
}



static int
mainloop(scli_interp_t *interp, scli_cmd_t *cmd, int argc, char **argv)
{
    int c, num, flags = 0;
    char *input, buffer[80], *end;
    int code = SCLI_OK;
    
    flags |= STOP_FLAG_RESTART;
    flags |= STOP_FLAG_NODELAY;

    while (! (flags & STOP_FLAG_DONE)) {
        if (flags & STOP_FLAG_RESTART) {
            show_interior(interp->peer);
        }
        flags |= show_system(interp->peer, flags);
        if (! (flags & STOP_FLAG_SNMP_FAILURE)) {
            if (do_network_summary) {
                show_ip(interp->peer, flags);
            }
            if (do_transport_summary) {
                show_udp(interp->peer, flags);
                show_tcp(interp->peer, flags);
            }
	    if (do_mode_summary) {
		show_mode_summary(cmd->path);
	    }
        }
	move(status_line, 0);
        refresh();
        if (! (flags & STOP_FLAG_SNMP_FAILURE)) {
	    scli_interp_reset(interp);
	    if (! (interp->flags & SCLI_INTERP_FLAG_DRY)
		|| ((interp->flags & SCLI_INTERP_FLAG_DRY) && (cmd->flags & SCLI_CMD_FLAG_DRY))) {
		code = (cmd->func) (interp, argc, argv);
	    } else {
		code = SCLI_OK;
	    }
	    if (code != SCLI_OK) {
		break;
	    }
	    if (! interp->result->len && ! interp->header->len) {
		g_string_append(interp->header, "NO DATA AVAILABLE");
	    }
	    page(mode_win, interp);
	}
        move(status_line, 0);
        clrtoeol();
	if (flags & STOP_FLAG_SNMP_FAILURE) {
	    const char *error = NULL;
	    if (interp->peer && interp->peer->error_status) {
		error = gnet_snmp_enum_get_label(gnet_snmp_enum_error_table,
						 interp->peer->error_status);
	    }
	    scli_interp_reset(interp);
	    g_string_assign(interp->header, "NO DATA AVAILABLE");
	    page(mode_win, interp);
	    show_message(error ? error : "internalError");
	}
	if (flags & STOP_FLAG_NODELAY) {
	    timeout(1000);
	} else {
	    timeout(interp->delay);	
	}
        flags = 0;
        switch (c = getch()) {
        case ERR:       /* timeout */
            break;
#ifdef KEY_RESIZE
	case KEY_RESIZE:
	    /* ignore this one */
	    break;
#endif
        case ' ':
            break;
        case 'q':
	case 'Q':
	    code = SCLI_OK;
            flags |= STOP_FLAG_DONE;
            break;
	case 'x':
	case 'X':
	    code = SCLI_EXIT;
	    flags |= STOP_FLAG_DONE;
	    break;
        case 'h':
        case '?':
            help(cmd, argc, argv);
            flags |= STOP_FLAG_RESTART;
            break;
        case '\f':
            flags |= STOP_FLAG_RESTART;
            break;
        case 'c':
            do_contact_summary = ! do_contact_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of contact summary information %s",
		       do_contact_summary ? "on" : "off");
            show_message(buffer);
            flags |= STOP_FLAG_RESTART;
            break;
        case 'd':
            input = prompt("Delay between updates (seconds): ");
	    num = strtol(input, &end, 0);
	    if (*end || num <= 0) {
		g_snprintf(buffer, sizeof(buffer), "Invalid value `%s'", input);
	    } else {
		interp->delay = num * 1000;
		g_snprintf(buffer, sizeof(buffer),
			   "Delay changed to %d seconds.", interp->delay / 1000);
	    }
	    show_message(buffer);
            break;
	case 'm':
            do_mode_summary = ! do_mode_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of mode specific summary information %s",
		       do_mode_summary ? "on" : "off");
            show_message(buffer);
            flags |= STOP_FLAG_RESTART;
	    break;
        case 'n':
            do_network_summary = ! do_network_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of network layer summary information %s",
		       do_network_summary ? "on" : "off");
            show_message(buffer);
            flags |= STOP_FLAG_RESTART;
            break;
        case 't':
            do_transport_summary = ! do_transport_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of transport layer summary information %s",
		       do_transport_summary ? "on" : "off");
            show_message(buffer);
            flags |= STOP_FLAG_RESTART;
            break;
	case 'w':
            show_message("Press any key to continue: ");
	    timeout(-1);
	    (void) getch();
	    break;
        default:
            g_snprintf(buffer, sizeof(buffer),
		       "Unknown command `%c (%d)' -- hit `h' for help", c, c);
            show_message(buffer);
            break;
        }
    }
    return code;
}



int
scli_monitor(scli_interp_t *interp, scli_cmd_t *cmd, int argc, char **argv)
{
    int code = SCLI_OK;

    scli_curses_on();
    g_snmp_list_decode_hook = snmp_decode_hook;
    code = mainloop(interp, cmd, argc, argv);
    if (code == SCLI_OK || code == SCLI_EXIT) {
	scli_interp_reset(interp);
    }
    scli_curses_off();
    return code;
}


struct loop_data {
    scli_interp_t *interp;
    scli_cmd_t *cmd;
    int argc;
    char **argv;
};


static gboolean
loop_iteration(gpointer data)
{
    struct loop_data *loop_data = (struct loop_data *) data;
    scli_interp_t *interp = loop_data->interp;
    scli_cmd_t *cmd = loop_data->cmd;
    int argc = loop_data->argc;
    char **argv = loop_data->argv;
    
    g_printerr("loop_iteration()\n");
    scli_interp_reset(interp);
    if (! (interp->flags & SCLI_INTERP_FLAG_DRY)
	|| ((interp->flags & SCLI_INTERP_FLAG_DRY) && (cmd->flags & SCLI_CMD_FLAG_DRY))) {
	(void) (cmd->func) (interp, argc, argv);
    }
    g_print("%s\n%s", interp->header->str, interp->result->str);
    return TRUE;
}



static gboolean
loop_input(GIOChannel *source, GIOCondition condition, gpointer data)
{
    GMainLoop *loop = (GMainLoop *) data;
    g_printerr("loop_input()\n");
    g_main_quit(loop);
    return TRUE;
}



int
scli_loop(scli_interp_t *interp, scli_cmd_t *cmd, int argc, char **argv)
{
    GMainLoop *loop;
    GIOChannel *channel;
    struct loop_data loop_data;
    int code;

    if (! (interp->flags & SCLI_INTERP_FLAG_DRY)
	|| ((interp->flags & SCLI_INTERP_FLAG_DRY) && (cmd->flags & SCLI_CMD_FLAG_DRY))) {
	code = (cmd->func) (interp, argc, argv);
    } else {
	code = SCLI_OK;
    }
    if (code != SCLI_OK) {
	return code;
    }

    loop_data.interp = interp;
    loop_data.cmd = cmd;
    loop_data.argc = argc;
    loop_data.argv = argv;

    loop = g_main_new(TRUE);
    
    g_timeout_add(1000, loop_iteration, &loop_data);

    /*
    (void) initscr();
    (void) cbreak();
    */

    channel = g_io_channel_unix_new(fileno(stdin));
    g_io_add_watch(channel, (G_IO_IN | G_IO_PRI), loop_input, loop);
    g_io_channel_unref(channel);

    while(g_main_is_running(loop)) {
	g_main_run(loop);
    }
    g_main_destroy(loop);

    return SCLI_OK;
}
