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

#include "scli.h"

#include <readline/history.h>


typedef struct {
    GSnmpDebugFlags flag;
    gchar	    *name;
} SnmpDebugFlagToStringEntry;

static SnmpDebugFlagToStringEntry debug_flag_table[] = {
    { G_SNMP_DEBUG_REQUESTS, "request" },
    { G_SNMP_DEBUG_SESSION, "session" },
    { G_SNMP_DEBUG_TRANSPORT, "transport" },
    { 0, 0 }
};



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
        
    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    return SCLI_EXIT;
}



static void
print_cmd_tree(GString *s, GNode *node, char *prefix)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    int len;
    const int width = 24;

    len = strlen(prefix);
    
    if (cmd) {
	g_string_sprintfa(s, "%s- ", prefix);
	g_string_sprintfa(s, "%-*s %s\n", (width-len > 0) ? width-len : 0,
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
show_scli_modes(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    xmlNodePtr tree;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (scli_interp_xml(interp)) {
	for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	    mode = (scli_mode_t *) elem->data;
	    tree = xmlNewChild(interp->xml_node, NULL, "mode", mode->desc);
	    xmlSetProp(tree, "name", mode->name);
	}
    } else {
	g_string_sprintfa(interp->header, "%-15s %s", "MODE", "DESCRIPTION");
	for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	    mode = (scli_mode_t *) elem->data;
	    g_string_sprintfa(interp->result, "%-15s %s\n", mode->name, mode->desc);
	}
    }
    return SCLI_OK;
}



static int
cmd_scli_help(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (! scli_interp_xml(interp)) {
	g_string_sprintfa(interp->result,
			  "scli version " VERSION " command hierarchy:\n\n");
	if (interp->cmd_root) {
	    print_cmd_tree(interp->result, interp->cmd_root, "");
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

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

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
	return SCLI_SYNTAX;
    }

    return SCLI_OK;
}



static int
cmd_scli_close(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

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
	return SCLI_SYNTAX;
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
	return SCLI_SYNTAX;
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
show_scli_aliases(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alias_t *alias;
    int name_width = 16;
    int value_width = 16;
    xmlNodePtr tree;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (interp->alias_list) {
	if (scli_interp_xml(interp)) {
	    for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
		alias = (scli_alias_t *) elem->data;
		tree = xmlNewChild(interp->xml_node, NULL, "alias", alias->value);
		xmlSetProp(tree, "name", alias->name);
	    }
	} else {
	    for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
		alias = (scli_alias_t *) elem->data;
		if (strlen(alias->name) > name_width) {
		    name_width = strlen(alias->name);
		}
		if (strlen(alias->value) > value_width) {
		    value_width = strlen(alias->value);
		}
	    }
	    g_string_sprintfa(interp->header, "%-*s %-*s",
			      name_width, "ALIAS NAME",
			  value_width, "ALIAS VALUE");
	    for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
		alias = (scli_alias_t *) elem->data;
		g_string_sprintfa(interp->result, "%-*s %-*s\n",
				  name_width, alias->name,
				  value_width, alias->value);
	    }
	}
    }

    return SCLI_OK;
}



static int
show_scli_info(scli_interp_t *interp, int argc, char **argv)
{
    int const indent = 18;
    int rows, cols;
    SnmpDebugFlagToStringEntry *dft;
    char const *label;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    g_string_sprintfa(interp->result, "%-*s %lu\n", indent, "Epoch:",
		      interp->epoch);

    g_string_sprintfa(interp->result, "%-*s %s\n", indent, "Format:",
		      scli_interp_xml(interp) ? "xml" : "scli");

    g_string_sprintfa(interp->result, "%-*s %s\n", indent, "Interactive:",
		      scli_interp_interactive(interp) ? "true" : "false");

    g_string_sprintfa(interp->result, "%-*s %d seconds\n", indent, "Delay:",
		      interp->delay / 1000);

    g_string_sprintfa(interp->result, "%-*s ", indent, "Debugging:");
    for (dft = debug_flag_table; dft && dft->name; dft++) {
	if (g_snmp_debug_flags & dft->flag) {
	    g_string_sprintfa(interp->result, "%s ", dft->name);
	}
    }
    g_string_append(interp->result, "\n");

    scli_get_screen(&rows, &cols);
    g_string_sprintfa(interp->result, "%-*s %d\n", indent,
		      "Rows:", rows);
    g_string_sprintfa(interp->result, "%-*s %d\n", indent,
		      "Columns:", cols);
    g_string_sprintfa(interp->result, "%-*s %s\n", indent,
		      "Pager:", interp->pager ? interp->pager : "scli");

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
	label = gsnmp_enum_get_label(gsnmp_enum_version_table,
				     interp->peer->version);
	if (label) {
	    g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			      "Version:", label);
	} else {
	    g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			      "Version:", interp->peer->version);
	}
    }

    return SCLI_OK;
}



static int
set_scli_debugging(scli_interp_t *interp, int argc, char **argv)
{
    GSnmpDebugFlags flags = 0;
    SnmpDebugFlagToStringEntry *dft;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    for (i = 1; i < argc; i++) {
	for (dft = debug_flag_table; dft && dft->name; dft++) {
	    if (strcmp(argv[i], dft->name) == 0) {
		flags |= dft->flag;
		break;
	    }
	}
	if (! dft || ! dft->name) {
	    g_string_sprintfa(interp->result,
			      "unknown debugging option \"%s\"", argv[i]);
	    return SCLI_ERROR;
	}
    }

    g_snmp_debug_flags = flags;
    return SCLI_OK;
}



static int
set_scli_pager(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX;
    }

    if (scli_set_pager(interp, argv[1]) < 0) {
	g_string_sprintfa(interp->result,
			  "pager `%s' contains unsafe characters",
			  argv[1]);
	return SCLI_ERROR;	
    }

    return SCLI_OK;
}



static int
set_scli_format(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX;
    }

    if (strcmp(argv[1], "xml") == 0) {
	interp->flags |= SCLI_INTERP_FLAG_XML;
    } else if (strcmp(argv[1], "scli") == 0) {
	interp->flags &= ~SCLI_INTERP_FLAG_XML;
    } else {
	g_string_sprintfa(interp->result,
			  "unknown format `%s'", argv[1]);
	return SCLI_ERROR;	
    }

    return SCLI_OK;
}



void
scli_init_scli_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
        { "create scli alias", "<name> <value>",
	  0,
	  "create an alias for an scli command",
	  cmd_scli_alias },
	{ "close", NULL,
	  0,
	  "close the association to a remote SNMP agent",
	  cmd_scli_close },
	{ "exit", NULL,
	  0,
	  "exit the scli command line program",
	  cmd_scli_exit },
	{ "help", NULL,
	  0,
	  "help about the current mode and commands",
	  cmd_scli_help },
	{ "history", NULL,
	  0,
	  "display the command history list with line numbers",
	  cmd_scli_history },
	{ "open", "<hostname> [<community>]",
	  0,
	  "open an association to a remote SNMP agent",
	  scli_cmd_open },
	{ "show scli aliases", NULL,
	  0,
	  "show information about the interpreter aliases",
	  show_scli_aliases },
	{ "show scli info", NULL,
	  0,
	  "show status information about the interpreter",
	  show_scli_info },
	{ "show scli modes", NULL,
	  0,
	  "show information about the available interpreter modes",
	  show_scli_modes },
	{ "delete scli alias", "<name>",
	  0,
	  "delete an scli command alias",
	  cmd_scli_unalias },
	{ "set scli debugging", "<layer> ...",
	  0,
	  "set interpreter debugging options",
	  set_scli_debugging },
	{ "set scli pager", "<pager>",
	  0,
	  "set pager used by the interpreter",
	  set_scli_pager },
	{ "set scli format", "<pager>",
	  0,
	  "set output format of the interpreter",
	  set_scli_format },
	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t scli_mode = {
	"scli",
	"scli mode to display and configure scli parameters",
	cmds
    };

    scli_register_mode(interp, &scli_mode);
}
