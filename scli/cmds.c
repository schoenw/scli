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

#include "scli.h"

#include <readline/history.h>


int
scli_cmd_exit(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);
        
    return SCLI_EXIT;
}



static void
print_cmd_tree(GString *s, GNode *node, char *prefix)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    int len;

    len = strlen(prefix);
    
    if (cmd) {
	g_string_sprintfa(s, "%s- ", prefix);
	g_string_sprintfa(s, "%-*s %s\n", (20-len > 0) ? 20-len : 0,
			  cmd->name, cmd->desc ? cmd->desc : "");
    }

    for (node = g_node_first_child(node);
	 node; node = g_node_next_sibling(node)) {
	char *new_prefix;
	new_prefix = g_malloc(len + 3);
	strcpy(new_prefix, prefix);
	if (new_prefix[len-1] == '`') {
	    new_prefix[len-1] = ' ';
	}
	if (g_node_next_sibling(node)) {
	    strcat(new_prefix, len ? "  |" : " ");
	} else {
	    strcat(new_prefix, len ? "  `" : " ");
	}
	print_cmd_tree(s, node, new_prefix);
	g_free(new_prefix);
    }
}



int
scli_cmd_help(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    GString *s;

    g_return_val_if_fail(interp, SCLI_ERROR);
        
    s = interp->result;
    g_string_sprintfa(s, "scli version %s %s\n\n", VERSION, scli_copyright);
    g_string_append(s, "Supported modes:\n");
    for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	g_string_sprintfa(s, "%-15s %s\n", mode->name, mode->desc);
    }
    g_string_append(s, "\nList of scli commands:\n");
    if (interp->cmd_root) {
	print_cmd_tree(s, interp->cmd_root, "");
	g_string_append(s, "\n");
    }

    interp->result = s;
    return SCLI_OK;
}



int
scli_cmd_history(scli_interp_t *interp, int argc, char **argv)
{
    HIST_ENTRY **the_list;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    the_list = history_list();
    if (the_list) {
	for (i = 0; the_list[i]; i++) {
	    g_string_sprintfa(interp->result, "%4d %s\n",
			      i + history_base, the_list[i]->line);
	}
    }

    return SCLI_OK;
}



int
scli_cmd_open(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc == 2) {
	scli_open_community(interp, argv[1], 161, NULL);
    } else if (argc == 3) {
	scli_open_community(interp, argv[1], 161, argv[2]);
    } else {
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



int
scli_cmd_close(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    scli_close(interp);

    return SCLI_OK;
}
