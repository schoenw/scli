/* 
 * stop.c -- display SNMP MIB data in a top-like format
 *
 *       After more than 10 years of SNMP, I felt it is time for the
 *       first really useful command line SNMP monitoring tool. ;-)
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

#include "stools.h"
#include "stop.h"

#include <stdio.h>
#include <signal.h>
#include <getopt.h>
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#undef IPV6

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

static GSList *mode_list = NULL;
static stop_mode_t *active_mode = NULL;

static WINDOW *mode_win = NULL;

static int interrupted = 0;

static char const copyright[] = "(c) 2001 Juergen Schoenwaelder";


static void
onsignal(int n)
{
    (void) endwin();
    exit(0);
}


static void
onwinch(int n)
{
#ifdef HAVE_RESIZETERM
    struct winsize size;

    if (ioctl(fileno(stdout), TIOCGWINSZ, &size) == 0) {
	resizeterm(size.ws_row, size.ws_col);
	wrefresh(curscr);		/* Linux needs this */
	interrupted = 0;
    } else {
	interrupted = 1;
    }
#endif
    (void) signal(SIGWINCH, onwinch);	/* some systems need this */
}


static void
fix_string(guchar *s, gsize *len)
{
    int i;

    for (i = 0; i < *len; i++) {
        if (s[i] == '\r' || s[i] == '\n') s[i] = ' ';
    }
}


void
stop_register_mode(stop_mode_t *mode)
{
    if (mode) {
	mode_list = g_slist_append(mode_list, mode);
	if (! active_mode) {
	    active_mode = mode;
	}
    }
}


void
stop_show_message(char *message)
{
    move(status_line, 0);
    clrtoeol();
    attron(A_BOLD);
    addstr(message);
    attroff(A_BOLD);
    refresh();
    sleep(1);
}


char*
stop_prompt(char *message)
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


void
stop_show_mode_summary_line(char *string)
{
    if (do_mode_summary) {
	move(mode_line, 0);
	mvprintw(mode_line, 0, "%.*s", MIN(strlen(string), COLS), string);
	clrtoeol();
    }
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


static void
show_interior(host_snmp *peer)
{
    int y = 0;
    
    clear();
    y = 0;
    mvprintw(y, 10, "%s:%d", peer->name, peer->port);
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
    if (active_mode && do_mode_summary) {
	mode_line = y++;
    }
    status_line = y++;

    if (mode_win) {
	delwin(mode_win);
    }
    mode_win = newwin(LINES-y, COLS, y, 0);
}


static int
show_system(host_snmp *peer, int flags)
{
    system_t *system = NULL;
    static struct timeval last, now;
    static guint32 sysUpTime = 0;
    char timestr[10];
    struct tm *now_tm;

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

    if (snmpv2_mib_get_system(peer, &system) != 0 || system == NULL) {
        move(0, 10);
        clrtoeol();
        mvprintw(0, 10, "%s:%d", peer->name, peer->port);
        attron(A_BOLD);
        mvprintw(0, 10 + strlen(peer->name) + 8,
                 "SNMP communication problem");
        attroff(A_BOLD);
        mvaddstr(0, COLS-strlen(timestr)-1, timestr);
        return STOP_FLAG_SNMP_FAILURE;
    }
    
    if (system->sysUpTime) {
	unsigned days, hours, minutes, seconds;
        guint32 secs;
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
        mvprintw(0, 10, "%s:%d up %d %s %02d:%02d:%02d",
                 peer->name, peer->port,
		 days, (days == 1) ? "day" : "days",
		 hours, minutes, seconds);
        sysUpTime = *(system->sysUpTime);
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
    
    last = now;
    snmpv2_mib_free_system(system);
    mvaddstr(0, COLS-strlen(timestr)-1, timestr);
    return 0;
}


static void
show_ip(host_snmp *peer, int flags)
{
    ip_t *ip = NULL;
    static guint32 ipInReceives = 0;
    static guint32 ipForwDatagrams = 0;
    static guint32 ipReasmOKs = 0;
    static guint32 ipFragOKs = 0;
    static guint32 ipOutSent = 0;
    static struct timeval last, now;
    double delta;

    if (flags & STOP_FLAG_RESTART) {
        last.tv_sec = last.tv_usec = 0;
    }

    if (ip_mib_get_ip(peer, &ip) != 0 || ip == NULL) {
        return;
    }
    
    gettimeofday (&now, NULL);
    delta = TV_DIFF(last, now);
    if (ip->ipInReceives && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipInReceives) - ipInReceives) / delta;
            mvprintw(ipv4_line, 10, fmt_kmg((guint32) f_val));
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
		     fmt_kmg((guint32) ((ipOut - ipOutSent) / delta)));
        }
        ipOutSent = ipOut;
    } else {
        mvprintw(ipv4_line, 22, "----");
    }
    
    if (ip->ipForwDatagrams && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipForwDatagrams) - ipForwDatagrams) / delta;
            mvprintw(ipv4_line, 35, fmt_kmg((guint32) f_val));
        }
        ipForwDatagrams = *(ip->ipForwDatagrams);
    } else {
        mvprintw(ipv4_line, 35, "----");
    }
    
    if (ip->ipReasmOKs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipReasmOKs) - ipReasmOKs) / delta;
            mvprintw(ipv4_line, 48, fmt_kmg((guint32) f_val));
        }
        ipReasmOKs = *(ip->ipReasmOKs);
    } else {
        mvprintw(ipv4_line, 48, "----");
    }
    
    if (ip->ipFragOKs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(ip->ipFragOKs) - ipFragOKs) / delta;
	    mvprintw(ipv4_line, 62, fmt_kmg((guint32) f_val));
        }
        ipFragOKs = *(ip->ipFragOKs);
    } else {
        mvprintw(ipv4_line, 62, "----");
    }
    
    last = now;
    ip_mib_free_ip(ip);
}


static void
show_udp(host_snmp *peer, int flags)
{
    udp_t *udp = NULL;
    static guint32 udpInDatagrams = 0;
    static guint32 udpOutDatagrams = 0;
    static struct timeval last, now;
    double delta;
    
    if (flags & STOP_FLAG_RESTART) {
        last.tv_sec = last.tv_usec = 0;
    }

    if (udp_mib_get_udp(peer, &udp) != 0 || udp == NULL) {
        return;
    }

    gettimeofday (&now, NULL);
    delta = TV_DIFF(last, now);
    if (udp->udpInDatagrams && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(udp->udpInDatagrams) - udpInDatagrams) / delta;
            mvprintw(udp_line, 10, fmt_kmg((guint32) f_val));
        }
        udpInDatagrams = *(udp->udpInDatagrams);
    } else {
        mvprintw(udp_line, 10, "----");
    }
    if (udp->udpOutDatagrams && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(udp->udpOutDatagrams) - udpOutDatagrams) / delta;
            mvprintw(udp_line, 22, fmt_kmg((guint32) f_val));
        }
        udpOutDatagrams = *(udp->udpOutDatagrams);
    } else {
        mvprintw(udp_line, 22, "----");
    }

    last = now;
    udp_mib_free_udp(udp);
}


static void
show_tcp(host_snmp *peer, int flags)
{
    tcp_t *tcp = NULL;
    static guint32 tcpInSegs = 0;
    static guint32 tcpOutSegs = 0;
    static guint32 tcpActiveOpens = 0;
    static guint32 tcpPassiveOpens = 0; 
    static struct timeval last, now;
    double delta;

    if (flags & STOP_FLAG_RESTART) {
        last.tv_sec = last.tv_usec = 0;
    }

    if (tcp_mib_get_tcp(peer, &tcp) != 0 || tcp == NULL) {
        return;
        
    }

    gettimeofday (&now, NULL);
    delta = TV_DIFF(last, now);
    if (tcp->tcpInSegs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpInSegs) - tcpInSegs) / delta;
            mvprintw(tcp_line, 10, fmt_kmg((guint32) f_val));
        }
        tcpInSegs = *(tcp->tcpInSegs);
    } else {
        mvprintw(tcp_line, 10, "----");
    }
    if (tcp->tcpOutSegs && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpOutSegs) - tcpOutSegs) / delta;
            mvprintw(tcp_line, 22, fmt_kmg((guint32) f_val));
        }
        tcpOutSegs = *(tcp->tcpOutSegs);
    } else {
        mvprintw(tcp_line, 22, "----");
    }
    if (tcp->tcpCurrEstab) {
        mvprintw(tcp_line, 35,
		 fmt_kmg(*(tcp->tcpCurrEstab)));
    } else {
        mvprintw(tcp_line, 35, "----");
    }
    if (tcp->tcpActiveOpens && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpActiveOpens) - tcpActiveOpens) / delta;
            mvprintw(tcp_line, 48, fmt_kmg((guint32) f_val));
        }
        tcpActiveOpens = *(tcp->tcpActiveOpens);
    } else {
        mvprintw(tcp_line, 48, "----");
    }
    if (tcp->tcpPassiveOpens && delta > TV_DELTA) {
        if (last.tv_sec && last.tv_usec) {
	    double f_val = (*(tcp->tcpPassiveOpens) - tcpPassiveOpens) / delta;
            mvprintw(tcp_line, 62, fmt_kmg((guint32) f_val));
        }
	tcpPassiveOpens = *(tcp->tcpPassiveOpens);
    } else {
        mvprintw(tcp_line, 62, "----");
    }

    last = now;
    tcp_mib_free_tcp(tcp);
}


static void
help()
{
    GSList *elem;
    int y = 0;
    
    clear();
    mvprintw(y++, 0, "stop version %s %s", VERSION, copyright);
    y++;
    mvprintw(y++, 0, "Interactive commands are:");
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
    mvprintw(y++, 0, "T\tToggle active mode to display");
    mvprintw(y++, 0, "q\tQuit");
    y++;
    mvprintw(y++, 0, "Available modes:");
    for (elem = mode_list; elem ; elem = g_slist_next(elem)) {
	stop_mode_t *mode = (stop_mode_t *) elem->data;
	mvprintw(y++, 0, "%s %-14s %s",
		 (mode == active_mode) ? "*" : " ",
		 mode->name, mode->desc);
    }
    y++;
    mvprintw(y++, 0, "Press any key to continue");
    timeout(-1);
    (void) getch();
    clear();
}


static void
mainloop(host_snmp *peer, int delay)
{
    int c, flags = 0;
    char *input, buffer[80];
    GSList *elem;
    GString *s;
    
    flags |= STOP_FLAG_RESTART;
    flags |= STOP_FLAG_NODELAY;
    while (! (flags & STOP_FLAG_DONE)) {
        if (flags & STOP_FLAG_RESTART) {
            show_interior(peer);
        }
        flags |= show_system(peer, flags);
        if (! (flags & STOP_FLAG_SNMP_FAILURE)) {
            if (do_network_summary) {
                show_ip(peer, flags);
            }
            if (do_transport_summary) {
                show_udp(peer, flags);
                show_tcp(peer, flags);
            }
        }
	move(status_line, 0);
        refresh();
        if (! (flags & STOP_FLAG_SNMP_FAILURE)) {
	    if (active_mode && active_mode->func && mode_win) {
		(active_mode->func)(mode_win, peer, flags);
		wrefresh(mode_win);
	    }
	}
        move(status_line, 0);
        clrtoeol();
	if (flags & STOP_FLAG_NODELAY) {
	    timeout(1000);
	} else {
	    timeout(delay);	
	}
        flags = 0;
	if (interrupted) {
	    onwinch(0);
	}
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
            flags |= STOP_FLAG_DONE;
            break;
        case 'h':
        case '?':
            help();
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
            stop_show_message(buffer);
            flags |= STOP_FLAG_RESTART;
            break;
        case 'd':
            input = stop_prompt("Delay between updates (seconds): ");
            if (atoi(input) > 0) {
                delay = atoi(input) * 1000;
            }
	    g_snprintf(buffer, sizeof(buffer),
		       "Delay changed to %d seconds.", delay / 1000);
	    stop_show_message(buffer);
            break;
	case 'm':
            do_mode_summary = ! do_mode_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of mode specific summary information %s",
		       do_mode_summary ? "on" : "off");
            stop_show_message(buffer);
            flags |= STOP_FLAG_RESTART;
	    break;
        case 'n':
            do_network_summary = ! do_network_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of network layer summary information %s",
		       do_network_summary ? "on" : "off");
            stop_show_message(buffer);
            flags |= STOP_FLAG_RESTART;
            break;
        case 't':
            do_transport_summary = ! do_transport_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of transport layer summary information %s",
		       do_transport_summary ? "on" : "off");
            stop_show_message(buffer);
            flags |= STOP_FLAG_RESTART;
            break;
	case 'w':
            stop_show_message("Press any key to continue: ");
	    timeout(-1);
	    (void) getch();
	    break;
        case 'T':
	    elem = g_slist_find(mode_list, active_mode);
	    if (elem) {
		elem = g_slist_next(elem);
	    }
	    if (! elem) {
		elem = mode_list;
	    }
	    active_mode = (stop_mode_t *) elem->data;
            flags |= STOP_FLAG_RESTART;
	    s = g_string_new(NULL);
	    g_string_sprintfa(s, "Switching to %s mode.", active_mode->name);
	    stop_show_message(s->str);
	    g_string_free(s, 1);
            break;
        default:
            g_snprintf(buffer, sizeof(buffer),
		       "Unknown command `%c (%d)' -- hit `h' for help", c, c);
            stop_show_message(buffer);
            break;
        }
    }
}


static void
usage()
{
    printf("Usage: stop [OPTION] hostname [community]\n");
    printf(
	"Options:\n"
	"  -V, --version     show version information and exit\n"
	"  -d, --delay       delay in seconds between screen updates (default 5)\n"
	"  -h, --help        display this help and exit\n"
	"  -m, --mode        select a certain display mode\n"
	"  -P, --port        port number of the SNMP agent (default 161)\n"
	"  -r, --retries     number of retries (default 5)\n"
	"  -t, --timeout     timeout between retries in milliseconds (default 200)\n"
	);
}


int
main(int argc, char **argv)
{
    host_snmp _peer, *peer = &_peer;
    system_t *system = NULL;
    int c, port = 161, delay = 5000, retries = 5, timeout = 200000;
    char *mode_name = NULL;

    /*
     * Option parsing etc...
     */

    static struct option const long_options[] =
    {
        { "version", no_argument,       0, 'V' },
        { "delay",   required_argument, 0, 'd' },
        { "help",    no_argument,       0, 'h' },
	{ "mode",    required_argument, 0, 'm' },
        { "port",    required_argument, 0, 'p' },
	{ "retries", required_argument, 0, 'r' },
	{ "timeout", required_argument, 0, 't' },
        { NULL, 0, NULL, 0}
    };

    while ((c = getopt_long(argc, argv, "Vd:hm:p:r:t:", long_options,
                            (int *) 0)) != EOF) {
        switch (c) {
        case 'V':
            printf("stop %s\n", VERSION);
            exit(0);
        case 'd':
            if (atoi(optarg) > 0) {
                delay = atoi(optarg) * 1000;
            }
            break;
        case 'h':
            usage();
            exit(0);
	case 'm':
	    mode_name = optarg;
	    break;
        case 'p':
            if (atoi(optarg) <= 0 || atoi(optarg) > 65535) {
                port = atoi(optarg);
            }
            break;
	case 'r':
	    if (atoi(optarg) > 0) {
		retries = atoi(optarg);
	    }
	    break;
	case 't':
	    if (atoi(optarg) < 50) {
		timeout = 50 * 1000;
	    } else {
		timeout = atoi(optarg) * 1000;
	    }
	    break;
        default:
            usage();
            exit(1);
        }
    }

    if (argc-optind < 1 || argc-optind > 2) {
        usage();
        exit(1);
    }

    /*
     * Call the localtime() function to make sure the timezone
     * variable is set correctly. This is necessary at least on
     * Solaris machines.
     */

    {
	time_t t = 0;
	(void) localtime(&t);
    }

    /*
     * Lets see how we can talk to this guy. We first try to speek
     * SNMPv2c (since this protocol does much better error handling)
     * and we fall back to SNMPv1 only if this is necessary.
     */
    
    memset(peer, 0, sizeof(host_snmp));
    peer->domain = AF_INET;
    peer->name = g_strdup(argv[optind++]);
    peer->port = port;
    peer->rcomm = (argc-optind > 0) ? argv[optind++] : "public";
    peer->wcomm = peer->rcomm;
    peer->retries = 3;
    peer->timeout = 1;
    peer->version = G_SNMP_V2C;

    printf("stop version %s %s\n", VERSION, copyright);
  
    if (! g_snmp_init(FALSE)) {
	g_error("scli: Initialisation of SNMP library failed");
        exit(1);
    }
        
    printf("Trying SNMPv2c ... ");
    fflush(stdout);
    if (snmpv2_mib_get_system(peer, &system) == 0 && system) {
	printf("good!\n");
    } else {
	printf("timeout.\nTrying SNMPv1  ... ");
	fflush(stdout);
	peer->version = G_SNMP_V1;
	if (snmpv2_mib_get_system(peer, &system) == 0 && system) {
	    printf("ok.\n");
	} else {
	    printf("timeout.\nGiving up!\n");
	    exit(1);
	}
    }

    if (system && system->sysDescr) {
	printf("\n%.*s\n", (int) system->_sysDescrLength, system->sysDescr);
    }
    
    snmpv2_mib_free_system(system);
    printf("\n");
    fflush(stdout);
    sleep(1);

    /*
     * Now initialize the various modes. We must do it here and not
     * earlier so that the modes can already use the curses based
     * infrastructure.
     */

    stop_init_interface_mode();
    stop_init_process_mode();

    if (mode_name) {
	GSList *elem;
	for (elem = mode_list; elem; elem = g_slist_next(elem)) {
	    stop_mode_t *mode = (stop_mode_t *) elem->data;
	    if (strcmp(mode->name, mode_name) == 0) {
		active_mode = mode;
		break;
	    }
	}
	if (! elem) {
	    fprintf(stderr, "stop: unknown mode \"%s\"\n", mode_name);
	    sleep(1);
	}
    }
    
    /*
     * Setting up curses in such a way that we are sure to restore
     * the tty into something useful when we are done.
     */

    signal(SIGINT, onsignal);
    signal(SIGTERM, onsignal);
    signal(SIGHUP, onsignal);
    signal(SIGQUIT, onsignal);
    signal(SIGWINCH, onwinch);

    (void) initscr();
    (void) cbreak();
    (void) noecho();
    (void) nonl();

    mainloop(peer, delay);

    (void) endwin();

    return 0;
}
