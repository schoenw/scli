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


static gint
alias_compare(gconstpointer a, gconstpointer b)
{
    scli_alias_t *alias_a = (scli_alias_t *) a;
    scli_alias_t *alias_b = (scli_alias_t *) b;

    return strcmp(alias_a->name, alias_b->name);
}



static int
cmd_scli_exit(scli_interp_t *interp, int argc, char **argv)
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



static int
cmd_scli_modes(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    GString *s;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (! scli_interp_xml(interp)) {
	s = interp->result;
	g_string_sprintfa(s, "%-15s %s\n", "Mode", "Description");
	for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	    mode = (scli_mode_t *) elem->data;
	    g_string_sprintfa(s, "%-15s %s\n", mode->name, mode->desc);
	}
	interp->result = s;
    }
    return SCLI_OK;
}



static int
cmd_scli_help(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (! scli_interp_xml(interp)) {
	if (interp->cmd_root) {
	    print_cmd_tree(interp->result, interp->cmd_root, "");
	    g_string_append(interp->result, "\n");
	}
    }
    return SCLI_OK;
}



static int
cmd_scli_history(scli_interp_t *interp, int argc, char **argv)
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



static int
cmd_scli_close(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    scli_close(interp);

    return SCLI_OK;
}



static int
cmd_scli_alias(scli_interp_t *interp, int argc, char **argv)
{
    scli_alias_t *alias = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc == 3) {
	alias = (scli_alias_t *) g_malloc0(sizeof(scli_alias_t));
	alias->name = g_strdup(argv[1]);
	alias->value = g_strdup(argv[2]);
	interp->alias_list = g_slist_insert_sorted(interp->alias_list,
						   alias, alias_compare);
    } else {
	return SCLI_ERROR;
    }
    
    return SCLI_OK;
}



static int
cmd_scli_unalias(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alias_t *alias = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_ERROR;
    }
    
 again:
    for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
	alias = (scli_alias_t *) elem->data;
	if (strcmp(alias->name, argv[1]) == 0) {
	    interp->alias_list = g_slist_remove(interp->alias_list,
						elem->data);
	    g_free(alias->name);
	    g_free(alias->value);
	    g_free(alias);
	    goto again;
	}
    }
    
    return SCLI_OK;
}



static int
cmd_scli_aliases(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alias_t *alias;
    int name_width = 16;
    int value_width = 16;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (interp->alias_list) {
	for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
	    alias = (scli_alias_t *) elem->data;
	    if (strlen(alias->name) > name_width) {
		name_width = strlen(alias->name);
	    }
	    if (strlen(alias->value) > value_width) {
		value_width = strlen(alias->value);
	    }
	}
	g_string_sprintfa(interp->result, "%-*s %-*s Usage\n",
			  name_width, "Alias Name",
			  value_width, "Alias Value");
	for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
	    alias = (scli_alias_t *) elem->data;
	    g_string_sprintfa(interp->result, "%-*s %-*s %4d\n",
			      name_width, alias->name,
			      value_width, alias->value,
			      alias->count);
	}
    }

    return SCLI_OK;
}



static int
cmd_scli_peer(scli_interp_t *interp, int argc, char **argv)
{
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (interp->peer) {
	g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			  "Host:", interp->peer->name);
	g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			  "Port:", interp->peer->port);
	g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			  "Retries:", interp->peer->retries);
	g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			  "Timeout:", interp->peer->timeout);
	g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			  "Community:", interp->peer->rcomm);
	g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			  "Version:", interp->peer->version);
    }

    return SCLI_OK;
}



static int
cmd_scli_term(scli_interp_t *interp, int argc, char **argv)
{
    int const indent = 18;
    int rows, cols;

    g_return_val_if_fail(interp, SCLI_ERROR);

    /* show terminal type ? */

    scli_get_screen(&rows, &cols);
    g_string_sprintfa(interp->result, "%-*s %d\n", indent,
		      "Rows:", rows);
    g_string_sprintfa(interp->result, "%-*s %d\n", indent,
		      "Columns:", cols);

    if (interp->pager) {
	g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			  "Pager:", interp->pager);
    }

    return SCLI_OK;
}



void
scli_init_scli_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
        { "create scli alias",
	  0,
	  "create an scli command alias",
	  cmd_scli_alias },
	{ "close",
	  0,
	  "close the association to a remote SNMP agent",
	  cmd_scli_close },
	{ "exit",
	  0,
	  "exit the scli command line program",
	  cmd_scli_exit },
	{ "help",
	  0,
	  "help about the current mode and commands",
	  cmd_scli_help },
	{ "history",
	  0,
	  "display the command history list with line numbers",
	  cmd_scli_history },
	{ "open",
	  0,
	  "open an association to a remote SNMP agent",
	  scli_cmd_open },
	{ "show scli aliases",
	  0,
	  "show information about scli aliases",
	  cmd_scli_aliases },
	{ "show scli association",
	  0,
	  "show information about the current scli association",
	  cmd_scli_peer },
	{ "show scli term",
	  0,
	  "show information about the terminal parameters",
	  cmd_scli_term },
	{ "show scli modes",
	  0,
	  "show information about the available modes",
	  cmd_scli_modes },
	{ "delete scli alias",
	  0,
	  "delete an scli command alias",
	  cmd_scli_unalias },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t scli_mode = {
	"scli",
	"scli mode to display and configure scli parameters",
	cmds
    };

    scli_register_mode(interp, &scli_mode);
}
