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

#include <regex.h>
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
fmt_cmd_tree(GString *s, GNode *node, char *prefix)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    int len;
    const int width = 24;

    len = strlen(prefix);
    
    if (cmd) {
	g_string_sprintfa(s, "%s- ", prefix);
	g_string_sprintfa(s, "%-*s %s %s\n", (width-len > 0) ? width-len : 0,
			  cmd->name, cmd->path ? cmd->path : "",
			  cmd->options ? cmd->options : "");
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
	fmt_cmd_tree(s, node, new_prefix);
	g_free(new_prefix);
    }
}



static int
show_scli_command_tree(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (interp->cmd_root) {
	fmt_cmd_tree(interp->result, interp->cmd_root, "");
    }
    return SCLI_OK;
}



static int
show_scli_command_details(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    int i, j, c;
    regex_t _regex_cmd, *regex_cmd = NULL;
    char *cmd;

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_cmd = &_regex_cmd;
	if (regcomp(regex_cmd, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX;
	}
    }
    
    for (c = 0, elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	for (i = 0; mode->cmds[i].path; i++) {
	    cmd = g_strdup_printf("%s %s",
			  mode->cmds[i].path,
			  mode->cmds[i].options ? mode->cmds[i].options : "");
	    if (regex_cmd) {
		if (regexec(regex_cmd, cmd, (size_t) 0, NULL, 0) != 0) {
		    g_free(cmd);
		    continue;
		}
	    }
	    if (c) {
		g_string_append(interp->result, "\n");
	    }
	    g_string_sprintfa(interp->result, "Command:     %s\n", cmd);
	    g_string_append(interp->result, "Description: ");
	    for (j = 0; mode->cmds[i].desc[j]; j++) {
		g_string_append_c(interp->result, mode->cmds[i].desc[j]);
		if (mode->cmds[i].desc[j] == '\n') {
		    g_string_append(interp->result, "             ");
		}
	    }
	    g_string_append_c(interp->result, '\n');
	    g_string_sprintfa(interp->result, "Formats:     scli%s\n",
		      (mode->cmds[i].flags & SCLI_CMD_FLAG_XML) ? ",xml" : "");
	    g_string_sprintfa(interp->result, "Mode:        %s\n",
			      mode->name);
	    g_free(cmd);
	    c++;
	}
    }

    if (regex_cmd) regfree(regex_cmd); 
    
    return SCLI_OK;
}



static int
show_scli_command_info(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    int mode_width = 6;
    int i;
    regex_t _regex_cmd, *regex_cmd = NULL;
    char *cmd;

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_cmd = &_regex_cmd;
	if (regcomp(regex_cmd, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX;
	}
    }
    
    for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	if (strlen(mode->name) > mode_width) {
	    mode_width = strlen(mode->name);
	}
    }

    g_string_sprintfa(interp->header, "%-*s COMMAND", mode_width, "MODE");
    
    for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	for (i = 0; mode->cmds[i].path; i++) {
	    cmd = g_strdup_printf("%s %s",
			  mode->cmds[i].path,
			  mode->cmds[i].options ? mode->cmds[i].options : "");
	    if (regex_cmd) {
		if (regexec(regex_cmd, cmd, (size_t) 0, NULL, 0) != 0) {
		    g_free(cmd);
		    continue;
		}
	    }
	    g_string_sprintfa(interp->result, "%-*s %s\n", mode_width,
			      mode->name, cmd);
	    g_free(cmd);
	}
    }

    if (regex_cmd) regfree(regex_cmd); 
    
    return SCLI_OK;
}



static int
show_scli_mode_details(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    char *s, *cmd;
    int i, c;
    regex_t _regex_mode, *regex_mode = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX;
    }

    if (argc == 2) {
	regex_mode = &_regex_mode;
	if (regcomp(regex_mode, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_SYNTAX;
	}
    }
    
    for (c = 0, elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	if (regex_mode) {
	    if (regexec(regex_mode, mode->name, (size_t) 0, NULL, 0) != 0) {
		continue;
	    }
	}
	if (c) {
	    g_string_append(interp->result, " \n");
	}
	s = g_strdup_printf("%s MODE", mode->name);
	g_strup(s);
	g_string_sprintfa(interp->result, "%s\n\n%s\n \n", s, mode->desc);
	g_free(s);
	for (i = 0; mode->cmds[i].path; i++) {
	    cmd = g_strdup_printf("%s %s",
			  mode->cmds[i].path,
			  mode->cmds[i].options ? mode->cmds[i].options : "");
	    g_string_sprintfa(interp->result, "    %s\n", cmd);
	    g_free(cmd);
	}
	for (i = 0; mode->cmds[i].path; i++) {
	    g_string_sprintfa(interp->result, "\n%s\n", mode->cmds[i].desc);
	}
	c++;
    }

    if (regex_mode) regfree(regex_mode); 
    
    return SCLI_OK;
}


#if 0
static int
show_scli_modes(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    g_string_sprintfa(interp->header, "%-15s %s", "MODE", "DESCRIPTION");
    for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	g_string_sprintfa(interp->result, "%-15s %s\n",
			  mode->name, mode->desc);
    }
    return SCLI_OK;
}
#endif


static int
help(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    g_string_sprintfa(interp->result,
      "scli is a command interpreter which can be used to browse,\n"
      "monitor and configure SNMP enabled devices. scli commands are\n"
      "organized in a hierarchy. The top-level commands are:\n"
      "\n"
      " - open         Establish an association to a remote SNMP agent.\n"
      " - close        Close the association to a remote SNMP agent.\n"
      " - exit         Exit the scli command interpreter.\n"
      " - help         Show this help information.\n"
      " - history      Show the history of the last scli commands.\n"
      " - create       Create new object instance on the remote SNMP agent.\n"
      " - delete       Delete object instances from the remote SNMP agent.\n"
      " - set          Modify object instances on the remote SNMP agent.\n"
      " - show         Show information provided by the remote SNMP agent.\n"
      " - monitor      Monitor information provided by the remote SNMP agent.\n"
      "\n"
      "Use the \"show scli command tree\" command to look at the complete\n"
      "scli command tree and \"show scli command details\" command to obtain\n"
      "a detailed description of the various scli commands.\n");
    
    return SCLI_OK;
}



static int
history(scli_interp_t *interp, int argc, char **argv)
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
create_scli_alias(scli_interp_t *interp, int argc, char **argv)
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
delete_scli_alias(scli_interp_t *interp, int argc, char **argv)
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
show_scli_command_aliases(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alias_t *alias;
    int name_width = 16;
    int value_width = 16;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

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

    g_string_sprintfa(interp->result, "%-*s %s\n", indent, "Version:",
		      VERSION);
    
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
			      "Protocol:", label);
	} else {
	    g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			      "Protocol:", interp->peer->version);
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
	{ "open", "<hostname> [<community>]",
	  0,
	  "open an association to a remote SNMP agent",
	  scli_cmd_open },
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
	  "display some help information",
	  help },
	{ "history", NULL,
	  0,
	  "display the command history list with line numbers",
	  history },
        { "create scli alias", "<name> <value>",
	  0,
	  "create an alias for an scli command",
	  create_scli_alias },
	{ "delete scli alias", "<name>",
	  0,
	  "delete an scli command alias",
	  delete_scli_alias },
	{ "set scli debugging", "[<layer> ...]",
	  0,
	  "set interpreter debugging options",
	  set_scli_debugging },
	{ "set scli pager", "<pager>",
	  0,
	  "set pager used by the interpreter",
	  set_scli_pager },
	{ "set scli format", "<pager>",
	  SCLI_CMD_FLAG_XML,
	  "set output format of the interpreter",
	  set_scli_format },
	{ "show scli info", NULL,
	  0,
	  "show status information about the scli interpreter",
	  show_scli_info },
#if 0
	{ "show scli modes", NULL,
	  0,
	  "show information about the scli modes",
	  show_scli_modes },
#endif
	{ "show scli command info", "[<regex>]",
	  0,
	  "show summary information about the scli commands",
	  show_scli_command_info },
	{ "show scli command details", "[<regex>]",
	  0,
	  "show information about the scli commands",
	  show_scli_command_details },
	{ "show scli command tree", NULL,
	  0,
	  "show the scli command tree",
	  show_scli_command_tree },
	{ "show scli command aliases", NULL,
	  0,
	  "show information about the scli command aliases",
	  show_scli_command_aliases },
	{ "show scli mode details", "[<regex>]",
	  0,
	  "show information about the scli modes",
	  show_scli_mode_details },
	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t scli_mode = {
	"scli",
	"scli mode to display and configure scli parameters",
	cmds
    };

    scli_register_mode(interp, &scli_mode);
}
