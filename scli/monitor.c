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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "scli.h"

#include "snmpv2-mib.h"

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
snmp_decode_hook(GSList *list)
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
    int y = 0;

#if 0
    if (!interp->header->len && !interp->result->len) {
	stop_show_message("grrr");
    }
#endif
    
    if (interp->header->len) {
	wattron(win, A_REVERSE);
	mvwprintw(win, y++, 0, "%-*s", COLS, interp->header->str);
	wattroff(win, A_REVERSE);
    }

    if (interp->result->len) {
	mvwprintw(win, y, 0, interp->result->str);
	wclrtobot(win);
    }
    wrefresh(win);
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



static int
show_system(GSnmpSession *peer, int flags)
{
    snmpv2_mib_system_t *system = NULL;
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

#if 0
    if (snmpv2_mib_get_system(peer, &system) != 0 || system == NULL) {
	gchar *address = g_snmp_session_address(peer);
        move(0, 10);
        clrtoeol();
        mvprintw(0, 10, "%s", address);
        attron(A_BOLD);
        mvprintw(0, 10 + strlen(address) + 8, "SNMP communication problem");
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
        mvprintw(0, 10, "%s up %d %s %02d:%02d:%02d",
                 g_snmp_session_address(peer),
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
#endif
    
    last = now;
#if 0
    snmpv2_mib_free_system(system);
#endif
    mvaddstr(0, COLS-strlen(timestr)-1, timestr);
    return 0;
}



static void
show_interior(GSnmpSession *peer)
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
#if 0
    if (active_mode && do_mode_summary) {
	mode_line = y++;
    }
#endif
    status_line = y++;

    if (mode_win) {
	delwin(mode_win);
    }
    mode_win = newwin(LINES-y, COLS, y, 0);
}



static void
help()
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
    int c, flags = 0;
    char *input, buffer[80];
    int code;
    
    flags |= STOP_FLAG_RESTART;
    flags |= STOP_FLAG_NODELAY;
    while (! (flags & STOP_FLAG_DONE)) {
        if (flags & STOP_FLAG_RESTART) {
            show_interior(interp->peer);
        }
        flags |= show_system(interp->peer, flags);
        if (! (flags & STOP_FLAG_SNMP_FAILURE)) {
#if 0
            if (do_network_summary) {
                show_ip(interp->peer, flags);
            }
            if (do_transport_summary) {
                show_udp(interp->peer, flags);
                show_tcp(interp->peer, flags);
            }
#endif
        }
	move(status_line, 0);
        refresh();
        if (! (flags & STOP_FLAG_SNMP_FAILURE)) {
	    g_string_truncate(interp->result, 0);
	    g_string_truncate(interp->header, 0);
	    code = (cmd->func) (interp, argc, argv);
	    if (interp->result) {
		page(mode_win, interp);
	    }
	}
        move(status_line, 0);
        clrtoeol();
	if (flags & STOP_FLAG_NODELAY) {
	    timeout(1000);
	} else {
	    timeout(interp->delay);	
	}
        flags = 0;
#if 0	
	if (interrupted) {
	    onwinch(0);
	}
#endif
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
	case 'x':
	case 'X':
	    endwin();
	    g_print("\n");
	    exit(0);
        case 'h':
        case '?':
            help();
            flags |= STOP_FLAG_RESTART;
            break;
        case '\f':
            flags |= STOP_FLAG_RESTART;
            break;
#if 0
        case 'c':
            do_contact_summary = ! do_contact_summary;
            g_snprintf(buffer, sizeof(buffer),
		       "Display of contact summary information %s",
		       do_contact_summary ? "on" : "off");
            stop_show_message(buffer);
            flags |= STOP_FLAG_RESTART;
            break;
#endif
        case 'd':
            input = stop_prompt("Delay between updates (seconds): ");
            if (atoi(input) > 0) {
                interp->delay = atoi(input) * 1000;
            }
	    g_snprintf(buffer, sizeof(buffer),
		       "Delay changed to %d seconds.", interp->delay / 1000);
	    stop_show_message(buffer);
            break;
#if 0
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
#endif
	case 'w':
            stop_show_message("Press any key to continue: ");
	    timeout(-1);
	    (void) getch();
	    break;
        default:
            g_snprintf(buffer, sizeof(buffer),
		       "Unknown command `%c (%d)' -- hit `h' for help", c, c);
            stop_show_message(buffer);
            break;
        }
    }
    return SCLI_OK;
}



int
scli_monitor(scli_interp_t *interp, GNode *node, int argc, char **argv)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    int code = SCLI_OK;

    (void) initscr();
    (void) cbreak();
    (void) noecho();
    (void) nonl();

    g_snmp_list_decode_hook = snmp_decode_hook;
    code = mainloop(interp, cmd, argc, argv);
    if (code == SCLI_OK) {
	g_string_truncate(interp->result, 0);
    }

    (void) endwin();
    return code;
}

