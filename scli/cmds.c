/* 
 * cmds.c -- basic commands for the scli command interpreter
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
#include "scli.h"




int
scli_cmd_exit(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);
        
    if (argc != 1) {
	printf("wrong # args: should be \"exit\"\n");
	return SCLI_ERROR;
    }

    return SCLI_EXIT;
}



static gboolean
print_cmd(GNode *node, gpointer data)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    int i, depth;
    GString *s;

    if (cmd) {
	s = g_string_new(NULL);
	depth = g_node_depth(node);
	for (i = 2; i < depth; i++) {
	    if (i == 2) {
		s = g_string_append(s, "  ");
	    } else {
		s = g_string_append(s, "| ");
	    }
	}
	if (depth > 2) {
	    s = g_string_append(s, "+-");
	}
	s = g_string_append(s, cmd->name);
	printf("%-20s %s\n", s->str, cmd->desc);
	g_string_free(s, 1);
    }
    return FALSE;
}



int
scli_cmd_help(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;

    g_return_val_if_fail(interp, SCLI_ERROR);
        
    if (argc != 1) {
	printf("wrong # args: should be \"help\"\n");
	return SCLI_ERROR;
    }
    
    printf("scli version %s %s\n\n", VERSION, scli_copyright);
    printf("Supported modes:\n");
    for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	printf("%-15s %s\n", mode->name, mode->desc);
    }
    printf("\n");
    printf("List of scli commands:\n");
    if (interp->cmd_root) {
	g_node_traverse(interp->cmd_root, G_PRE_ORDER, G_TRAVERSE_ALL,
			G_MAXINT, print_cmd, NULL);
	printf("\n");
    }

    return SCLI_OK;
}

