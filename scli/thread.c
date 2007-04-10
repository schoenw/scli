/* 
 * thread.c -- thread specific functions for the scli command interpreter
 *
 * Copyright (C) 2007 Juergen Schoenwaelder
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

gpointer
scli_thread(gpointer data)
{
    scli_interp_t *interp = data;
    scli_message_t *msg;
    gpointer cmd;
    int i, code;

    if (! interp) {
	return NULL;
    }

    while (1) {
	cmd = g_async_queue_pop(interp->cmd_queue);
	if (! cmd) {
	    break;
	}
	msg = cmd;
	code = scli_eval_argc_argv(msg->interp, msg->argc, msg->argv);
	for (i = 0; i < msg->argc; i++) {
	    g_free(msg->argv[i]);
	}
	g_free(msg->argv);
	if (code == SCLI_EXIT) {
	    break;
	}
    }
    return NULL;
}



int
scli_thread_eval_argc_argv(scli_interp_t *interp, int argc, char **argv)
{
    scli_message_t *msg;
    int i;

    msg = g_new0(scli_message_t, 1);
    msg->interp = interp;
    msg->argc = argc;
    msg->argv = g_new0(char*, argc+1);
    for (i = 0; i < argc; i++) {
	msg->argv[i] = g_strdup(argv[i]);
    }

    g_async_queue_push(interp->cmd_queue, msg);
}
