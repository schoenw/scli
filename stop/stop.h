/* 
 * stop.h -- display SNMP MIB data in a top-like format
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

#ifndef _STOP_H
#define _STOP_H

#include <stdlib.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <curses.h>
#include <time.h>

/*
 * Flags that are passed to the mode driver in order to give him a
 * chance to redraw the screen or to recover from a discontinuity.
 */

#define STOP_FLAG_RESTART       0x01	/* restart everything */
#define STOP_FLAG_DONE          0x02	/* stop is quitting */
#define STOP_FLAG_NODELAY	0x04	/* sometimes we have no delay */
#define STOP_FLAG_SNMP_FAILURE	0x08	/* indicates a previous SNMP
					   failure in this poll */

/*
 * Macros to compute time differences.
 */

#define TV_DIFF(t1, t2) (1.0 * (t2.tv_sec - t1.tv_sec) + \
                         (t2.tv_usec - t1.tv_usec) / 1000000.0)
#define TV_DELTA	0.1

/*
 * Structure used to register new modes. Every mode has a name and a
 * function which is called periodically to update a window with mode
 * specific information.
 */

typedef struct stop_mode {
    char *name;			/* name of the mode */
    char *desc;			/* short description of the mode */
    void (*func) (WINDOW *win, host_snmp *peer, int);
				/* function to handle the mode */
} stop_mode_t;

extern void
stop_show_message(char *message);

extern char*
stop_prompt(char *message);

extern void
stop_show_mode_summary_line(char *message);

extern void
stop_register_mode(stop_mode_t *mode);

extern void
stop_init_interface_mode();

extern void
stop_init_process_mode();

#endif /* _STOP_H */
