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

#include <ctype.h>
#include <readline/history.h>


static GSnmpEnum const scli_regex_table[] = {
    { REG_EXTENDED,      "extended" },
    { REG_ICASE,	 "case-insensitive" },
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
	return SCLI_SYNTAX_NUMARGS;
    }

    return SCLI_EXIT;
}



static void
fmt_cmd_tree(GString *s, GNode *node, char *prefix)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    size_t len;
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
	new_prefix = g_malloc(len + 4);
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
	return SCLI_SYNTAX_NUMARGS;
    }

    if (interp->cmd_root) {
	fmt_cmd_tree(interp->result, interp->cmd_root, "");
    }
    return SCLI_OK;
}



struct show_scli_command_data {
    scli_interp_t *interp;
    regex_t *regex_cmd;
    int width;
    int cnt;
};



static void
fmt_cmd_info(GString *s, scli_cmd_t *cmd, int width)
{
    g_string_sprintfa(s, " %c%c%c  ",
		      cmd->flags & SCLI_CMD_FLAG_XML ? 'X' : '-',
		      cmd->flags & SCLI_CMD_FLAG_NEED_PEER ? 'S' : '-',
		      cmd->flags & SCLI_CMD_FLAG_NORECURSE ? '-' : 'R');
    g_string_sprintfa(s, "%-*s %s\n", width, cmd->path, cmd->options ? cmd->options : "");
}



static gboolean
show_scli_command_info_pass1(GNode *node, gpointer data)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    struct show_scli_command_data *x = (struct show_scli_command_data *) data;

    if (! x->regex_cmd || regexec(x->regex_cmd, cmd->path, (size_t) 0, NULL, 0) == 0) {
	if (strlen(cmd->path) > x->width) {
	    x->width = strlen(cmd->path);
	}
    }

    return FALSE;
}



static gboolean
show_scli_command_info_pass2(GNode *node, gpointer data)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    struct show_scli_command_data *x = (struct show_scli_command_data *) data;
    
    if (! x->regex_cmd || regexec(x->regex_cmd, cmd->path, (size_t) 0, NULL, 0) == 0) {
	fmt_cmd_info(x->interp->result, cmd, x->width);
    }

    return FALSE;
}



static int
show_scli_command_info(scli_interp_t *interp, int argc, char **argv)
{
    regex_t _regex_cmd, *regex_cmd = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_cmd = &_regex_cmd;
	if (regcomp(regex_cmd, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (interp->cmd_root) {
	struct show_scli_command_data x;
	x.interp = interp;
	x.width = 8;
	x.regex_cmd = regex_cmd;
	g_node_traverse(interp->cmd_root, G_IN_ORDER, G_TRAVERSE_LEAFS, -1,
			show_scli_command_info_pass1, &x);
	g_string_sprintfa(interp->header, "FLAGS %-*s ARGUMENTS", x.width, "COMMAND");
	g_node_traverse(interp->cmd_root, G_IN_ORDER, G_TRAVERSE_LEAFS, -1,
			show_scli_command_info_pass2, &x);
    }

    if (regex_cmd) regfree(regex_cmd);

    return SCLI_OK;
}



static void
fmt_cmd_details(GString *s, scli_cmd_t *cmd)
{
    const int indent = 14;
    g_string_sprintfa(s, "%-*s%s\n", indent, "Command:", cmd->path);
    if (cmd->options) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Arguments:", cmd->options);
    }
    g_string_sprintfa(s, "%-*sscli%s\n", indent, "Formats:",
		      cmd->flags & SCLI_CMD_FLAG_XML ? ", xml" : "");
    if (cmd->desc) {
	fmt_indent_string(s, indent, "Description:", strlen(cmd->desc), cmd->desc);
	//g_string_sprintfa(s, "Description:\n%s\n", cmd->desc);
    }
    if (cmd->xsd) {
	fmt_indent_string(s, indent, "Schema:", strlen(cmd->xsd), cmd->xsd);
    }
}



static gboolean
show_scli_command_details_pass1(GNode *node, gpointer data)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    struct show_scli_command_data *x = (struct show_scli_command_data *) data;
    
    if (! x->regex_cmd || regexec(x->regex_cmd, cmd->path, (size_t) 0, NULL, 0) == 0) {
	if (x->cnt) {
	    g_string_append(x->interp->result, "\n");
	}
	fmt_cmd_details(x->interp->result, cmd);
	x->cnt++;
    }

    return FALSE;
}



static int
show_scli_command_details(scli_interp_t *interp, int argc, char **argv)
{
    regex_t _regex_cmd, *regex_cmd = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_cmd = &_regex_cmd;
	if (regcomp(regex_cmd, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (interp->cmd_root) {
	struct show_scli_command_data x;
	x.interp = interp;
	x.width = 8;
	x.regex_cmd = regex_cmd;
	x.cnt = 0;
	g_node_traverse(interp->cmd_root, G_IN_ORDER, G_TRAVERSE_LEAFS, -1,
			show_scli_command_details_pass1, &x);
    }

    if (regex_cmd) regfree(regex_cmd);

    return SCLI_OK;
}



static int
show_scli_modes(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    char *s;
    int i, c;
    regex_t _regex_mode, *regex_mode = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_mode = &_regex_mode;
	if (regcomp(regex_mode, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
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
	    g_string_sprintfa(interp->result, "    %s %s\n", 
			      mode->cmds[i].path,
			      mode->cmds[i].options ? mode->cmds[i].options : "");
	}
	for (i = 0; mode->cmds[i].path; i++) {
	    g_string_sprintfa(interp->result, "\n%s\n", mode->cmds[i].desc);
	}
	c++;
    }

    if (regex_mode) regfree(regex_mode); 
    
    return SCLI_OK;
}



static int
show_scli_schema(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode;
    int i, c;
    regex_t _regex_mode, *regex_mode = NULL;

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_mode = &_regex_mode;
	if (regcomp(regex_mode, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    g_string_append(interp->result,
		    "<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\n"
		    "\n"
		    "<xsd:annotation>\n"
		    "  <xsd:documentation xml:lang=\"en\">\n"
		    "    XML schema definition for the output produced by scli version " VERSION ".\n"
		    "  </xsd:documentation>\n"
		    "</xsd:annotation>\n"
		    "\n");

    for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	if (regex_mode) {
	    if (regexec(regex_mode, mode->name, (size_t) 0, NULL, 0) != 0) {
		continue;
	    }
	}

	g_string_sprintfa(interp->result, "<!-- %s mode -->\n\n", mode->name);
	
	for (i = 0, c = 0; mode->cmds[i].path; i++) {
	    if (mode->cmds[i].xsd) {
		if (c) g_string_append(interp->result, "\n");
		g_string_sprintfa(interp->result, "%s\n", mode->cmds[i].xsd);
		c++;
	    }
	}
    }

    g_string_append(interp->result, "\n</xsd:schema>\n");
    
    if (regex_mode) regfree(regex_mode); 
    
    return SCLI_OK;
}



static int
help(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    g_string_sprintfa(interp->result,
      "Scli is a command interpreter which can be used to browse,\n"
      "monitor and configure SNMP enabled devices. All scli commands\n"
      "are organized in a hierarchy. The top-level commands are:\n"
      "\n"
      " - open         Establish an association to a remote SNMP agent.\n"
      " - close        Close the association to a remote SNMP agent.\n"
      " - exit         Exit the scli command interpreter.\n"
      " - help         Show this help information.\n"
      " - history      Show the history of the last scli commands.\n"
      " - create       Create object instances on the remote SNMP agent.\n"
      " - delete       Delete object instances from the remote SNMP agent.\n"
      " - set          Modify object instances on the remote SNMP agent.\n"
      " - show         Show information provided by the remote SNMP agent.\n"
      " - monitor      Monitor information provided by the remote SNMP agent.\n"
      " - dump         Dump scli command sequences to restore configurations.\n"
      "\n"
      "Use the \"show scli command tree\" command to browse the complete\n"
      "scli command tree and the \"show scli modes\" command to obtain\n"
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
	return SCLI_SYNTAX_NUMARGS;
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



static int
scli_cmd_open(scli_interp_t *interp, int argc, char **argv)
{
    int code;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc == 2) {
	code = scli_open_community(interp, argv[1], interp->port, NULL);
    } else if (argc == 3) {
	code = scli_open_community(interp, argv[1], interp->port, argv[2]);
    } else {
	code = SCLI_SYNTAX_NUMARGS;
    }

    return code;
}



static int
cmd_scli_close(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    scli_close(interp);

    return SCLI_OK;
}



static int
cmd_scli_load(scli_interp_t *interp, int argc, char **argv)
{
    GModule *module;
    gpointer pointer;
    gchar *path;
    GString *symbol;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    path = g_module_build_path(SCLI_PLUGIN_PATH, argv[1]);
    module = g_module_open(path, 0);
    if (! module) {
	g_string_sprintfa(interp->result, "%s", g_module_error());
	g_free(path);
	return SCLI_ERROR;
    }
    g_free(path);

    symbol = g_string_new(NULL);
    g_string_sprintfa(symbol, "scli_init_%s_mode", argv[1]);
    if (! g_module_symbol(module, symbol->str, &pointer)) {
	g_string_sprintfa(interp->result, "%s", g_module_error());
	g_module_close(module);
	g_string_free(symbol, 1);
	return SCLI_ERROR;
    }
    g_string_free(symbol, 1);

    /*
     * Call the init function and save the module pointer,
     * lookup the new mode data structure and save the module
     * pointer in there. xxx
     */

    return SCLI_OK;
}



static int
cmd_scli_unload(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_mode_t *mode = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    for (elem = interp->mode_list; elem; elem = g_slist_next(elem)) {
	mode = (scli_mode_t *) elem->data;
	if (strcmp(mode->name, argv[1]) == 0 && mode->module) {
	    break;
	}
    }

    if (elem && mode) {
	if (! g_module_close(mode->module)) {
	    g_string_sprintfa(interp->result, "%s", g_module_error());
	    return SCLI_ERROR;
	}
    }

    return SCLI_OK;
}



static int
create_scli_alias(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alias_t *alias = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
	alias = (scli_alias_t *) elem->data;
	if (strcmp(alias->name, argv[1]) == 0) break;
    }

    if (elem) {
	g_free(alias->value);
	alias->value = g_strdup_printf(argv[2]);
    } else {
	alias = g_new0(scli_alias_t, 1);
	alias->name = g_strdup(argv[1]);
	alias->value = g_strdup(argv[2]);
	interp->alias_list = g_slist_insert_sorted(interp->alias_list,
						   alias, alias_compare);
    }
    
    return SCLI_OK;
}



static int
delete_scli_alias(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alias_t *alias = NULL;
    regex_t _regex_name, *regex_name = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    regex_name = &_regex_name;
    if (regcomp(regex_name, argv[1], interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }
    
 again:
    for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
	alias = (scli_alias_t *) elem->data;
	if (regexec(regex_name, alias->name, (size_t) 0, NULL, 0) == 0) {
	    interp->alias_list = g_slist_remove(interp->alias_list,
						elem->data);
	    g_free(alias->name);
	    g_free(alias->value);
	    g_free(alias);
	    goto again;
	}
    }

    if (regex_name) regfree(regex_name);
    
    return SCLI_OK;
}



static int
show_scli_aliases(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alias_t *alias;
    int name_width = 16;
    int value_width = 16;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
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
create_scli_interp(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_interp_t *slave = NULL;
    scli_cmd_t *cmd;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    for (elem = interp->interp_list; elem; elem = g_slist_next(elem)) {
	slave = (scli_interp_t *) elem->data;
	if (strcmp(slave->name, argv[1]) == 0) {
	    g_string_sprintfa(interp->result,
			      "interp `%s' already exists", argv[1]);
	    return SCLI_ERROR;
	}
    }

    slave = scli_interp_create(argv[1]);
    scli_interp_init(slave);
    interp->interp_list = g_slist_append(interp->interp_list, slave);

    cmd = g_new0(scli_cmd_t, 1);
    cmd->path = g_strdup(argv[1]);
    cmd->flags = SCLI_CMD_FLAG_DYNAMIC;
    cmd->desc = g_strdup_printf("The `%s' command is used to invoke commands\n"
				"in the scli interpreter named %s.",
				argv[1], argv[1]);
    scli_create_command(interp, cmd);
    
    return SCLI_OK;
}



static int
delete_scli_interp(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_interp_t *slave = NULL;
    regex_t _regex_name, *regex_name = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    regex_name = &_regex_name;
    if (regcomp(regex_name, argv[1], interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }
    
 again:
    for (elem = interp->interp_list; elem; elem = g_slist_next(elem)) {
	slave = (scli_interp_t *) elem->data;
	if (regexec(regex_name, slave->name, (size_t) 0, NULL, 0) == 0) {
	    interp->interp_list = g_slist_remove(interp->interp_list,
						 elem->data);
	    scli_interp_delete(slave);
	    goto again;
	}
    }

    if (regex_name) regfree(regex_name);
    
    return SCLI_OK;
}



static int
show_scli_interps(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_interp_t *slave;
    int name_width = 16;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (interp->interp_list) {
	for (elem = interp->interp_list; elem; elem = g_slist_next(elem)) {
	    slave = (scli_interp_t *) elem->data;
	    if (strlen(slave->name) > name_width) {
		name_width = strlen(slave->name);
	    }
	}
	g_string_sprintfa(interp->header, "%-*s xxx",
			  name_width, "NAME");
	for (elem = interp->interp_list; elem; elem = g_slist_next(elem)) {
	    slave = (scli_interp_t *) elem->data;
	    g_string_sprintfa(interp->result, "%-*s\n",
			      name_width, slave->name);
	}
    }

    return SCLI_OK;
}



static int
show_scli_info(scli_interp_t *interp, int argc, char **argv)
{
    int const indent = 18;
    int rows, cols, c;
    GSnmpEnum const *dft;
    char const *label;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
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

    g_string_sprintfa(interp->result, "%-*s ", indent, "Regex:");
    for (dft = scli_regex_table, c = 0; dft && dft->label; dft++) {
	if (interp->regex_flags & dft->number) {
	    g_string_sprintfa(interp->result, "%s%s", c ? "|" : "", dft->label);
	    c++;
	}
    }
    g_string_append(interp->result, "\n");

    g_string_sprintfa(interp->result, "%-*s ", indent, "Debugging:");
    for (dft = gsnmp_enum_debug_table, c = 0; dft && dft->label; dft++) {
	if (g_snmp_debug_flags & dft->number) {
	    g_string_sprintfa(interp->result, "%s%s", c ? "|" : "", dft->label);
	    c++;
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
	label = gsnmp_enum_get_label(gsnmp_enum_tdomain_table,
				     (gint32) interp->peer->tdomain);
	if (label) {
	    g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			      "TDomain:", label);
	}
	g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			  "TAddress:", interp->peer->taddress);
	g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			  "Port:", interp->peer->port);
	g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			  "Retries:", interp->peer->retries);
	g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			  "Timeout:", interp->peer->timeout);
	g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			  "Community:", interp->peer->rcomm);
	label = gsnmp_enum_get_label(gsnmp_enum_version_table,
				     (gint32) interp->peer->version);
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



static void
fmt_alarm_info(GString *s, scli_alarm_t *alarm)
{	
    struct tm *tm;

    tm = localtime(&alarm->detected);
    g_string_sprintfa(s, "%04d-%02d-%02d %02d:%02d:%02d ",
		      tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
		      tm->tm_hour, tm->tm_min, tm->tm_sec);
    g_string_sprintfa(s, "%s\n", alarm->desc);
}



static int
show_scli_alarm_info(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_alarm_t *alarm;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (interp->alarm_list) {
	g_string_sprintfa(interp->header, "DETECTED            VERIFIED            DESCRIPTION");
	for (elem = interp->alarm_list; elem; elem = g_slist_next(elem)) {
	    alarm = (scli_alarm_t *) elem->data;
	    fmt_alarm_info(interp->result, alarm);
	}
    }

    return SCLI_OK;
}



static int
set_scli_regex(scli_interp_t *interp, int argc, char **argv)
{
    int flags = 0;
    GSnmpEnum const *dft;
    regex_t _regex_flags, *regex_flags = NULL;

    if (argc < 1 || argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 1) {
	interp->regex_flags = 0;
	return SCLI_OK;
    }

    regex_flags = &_regex_flags;
    if (regcomp(regex_flags, argv[1], interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }

    for (dft = scli_regex_table; dft && dft->label; dft++) {
	if (regexec(regex_flags, dft->label, (size_t) 0, NULL, 0) == 0) {
	    flags |= dft->number;
	}
    }
    interp->regex_flags = flags;
    
    if (regex_flags) regfree(regex_flags);

    return SCLI_OK;
}



static int
set_scli_debugging(scli_interp_t *interp, int argc, char **argv)
{
    GSnmpDebugFlags flags = 0;
    GSnmpEnum const *dft;
    regex_t _regex_flags, *regex_flags = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc < 1 || argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 1) {
	g_snmp_debug_flags = 0;
	return SCLI_OK;
    }
    
    regex_flags = &_regex_flags;
    if (regcomp(regex_flags, argv[1], interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }
    
    for (dft = gsnmp_enum_debug_table; dft && dft->label; dft++) {
	if (regexec(regex_flags, dft->label, (size_t) 0, NULL, 0) == 0) {
	    flags |= dft->number;
	}
    }
    g_snmp_debug_flags = flags;

    if (regex_flags) regfree(regex_flags);

    return SCLI_OK;
}



static int
set_scli_pager(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
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
	return SCLI_SYNTAX_NUMARGS;
    }

    if (strcmp(argv[1], "xml") == 0) {
	interp->flags |= SCLI_INTERP_FLAG_XML;
    } else if (strcmp(argv[1], "scli") == 0) {
	interp->flags &= ~SCLI_INTERP_FLAG_XML;
    } else {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_VALUE;	
    }

    return SCLI_OK;
}


#if 0
static int
cmd_scli_probe(scli_interp_t *interp, int argc, char **argv)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 1, 1, 0};
    GSnmpSession *s = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    s = g_snmp_session_clone(interp->peer);
    g_snmp_vbl_add_null(&in, base, sizeof(base)/sizeof(guint32));
    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
	g_snmp_vbl_free(out);
    }
    g_snmp_session_destroy(s);

    return SCLI_OK;
}



static void
fmt_walk(GString *s, GSnmpVarBind *vb)
{
    int i, printable;
    
    for (i = 0; i < vb->id_len; i++) {
	g_string_sprintfa(s, "%s%d",
			  i ? "." : "", vb->id[i]);
    }
    g_string_append(s, " = ");
    switch (vb->type) {
    case G_SNMP_INTEGER32:
	g_string_sprintfa(s, "%d", vb->syntax.i32[0]);
	break;
    case G_SNMP_UNSIGNED32:
    case G_SNMP_COUNTER32:
    case G_SNMP_TIMETICKS:
	g_string_sprintfa(s, "%u", vb->syntax.ui32[0]);
	break;
    case G_SNMP_COUNTER64:
	g_string_sprintfa(s, "%llu", vb->syntax.ui64[0]);
	break;
    case G_SNMP_IPADDRESS:
	if (vb->syntax_len == 4) {
	    g_string_sprintfa(s, "%d.%d.%d.%d",
			      vb->syntax.uc[0],
			      vb->syntax.uc[1],
			      vb->syntax.uc[2],
			      vb->syntax.uc[3]);
	}
	break;
    case G_SNMP_OCTET_STRING:
    case G_SNMP_OPAQUE:
	for (i = 0; i < vb->syntax_len; i++) {
	    g_string_sprintfa(s, "%s%02x", i ? ":" : "", vb->syntax.uc[i]);
	}
	for (i = 0, printable = 1; i < vb->syntax_len; i++) {
	    printable = printable && isprint((int) vb->syntax.uc[i]);
	}
	if (printable && vb->syntax_len) {
	    g_string_append(s, " \"");
	    for (i = 0; i < vb->syntax_len; i++) {
		g_string_append_c(s, vb->syntax.uc[i]);
	    }
	    g_string_append(s, "\"");
	}
	break;
    case G_SNMP_OBJECT_ID:
	for (i = 0; i < vb->syntax_len/sizeof(guint32); i++) {
	    g_string_sprintfa(s, "%s%d",
			      i ? "." : "", vb->syntax.ui32[i]);
	}
	break;
    default:
	break;
    }
    g_string_append_c(s, '\n');
}



static int
cmd_scli_walk(scli_interp_t *interp, int argc, char **argv)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[SNMP_SIZE_OBJECTID];
    GSnmpSession *s = NULL;
    GSList *elem;
    int i, len;
    char *p;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc < 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    for (i = 1; i < argc; i++) {
	for (len = 0, p = argv[i]; p && *p && len < SNMP_SIZE_OBJECTID; len++) {
	    base[len] = strtoul(p, &p, 0);
	    if (p && *p) {
		if (*p == '.') {
		    p++;
		} else {
		    g_snmp_vbl_free(in);
		    g_string_assign(interp->result, argv[i]);
		    return SCLI_SYNTAX_VALUE;
		}
	    }
	}
	if ((p && *p) || len < 2 || base[0] > 2 || base[1] > 40) {
	    g_snmp_vbl_free(in);
	    g_string_assign(interp->result, argv[i]);
	    return SCLI_SYNTAX_VALUE;
	}
	g_snmp_vbl_add_null(&in, base, len);
    }

    s = g_snmp_session_clone(interp->peer);
    out = g_snmp_session_sync_walk(s, in);
    g_snmp_vbl_free(in);
    if (out) {
	for (elem = out; elem; elem = g_slist_next(elem)) {
	    fmt_walk(interp->result, (GSnmpVarBind *) elem->data);
	}
	g_snmp_vbl_free(out);
    }
    g_snmp_session_destroy(s);
            
    return SCLI_OK;
}
#endif


void
scli_init_scli_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "open", "<nodename> [<community>]",
	  "The `open' command establishes an association to a remote SNMP\n"
	  "agent. The <nodename> argument is the DNS name or the IP\n"
	  "address of the remote node. Scli will try to talk to the SNMP\n"
	  "agent on this node by using the default port number (usually 161)\n"
	  "and the default transport mapping (usually SNMP over UDP).\n"
	  "The optional <community> argument is the community string\n"
	  "needed to communicate with the remote SNMP agent. The default\n"
	  "community string is \"public\". Opening an association while\n"
	  "an association is already established is not considered an\n"
	  "error. The existing established association will be closed\n"
	  "automatically before an attempt to create a new association\n"
	  "is started.",
	  SCLI_CMD_FLAG_XML,
	  "", NULL,
	  scli_cmd_open },

	{ "close", NULL,
	  "The `close' command closes an established association to a remote\n"
	  "SNMP agent. Invoking the close command when no association is\n"
	  "established is not considered an error and will do just nothing.",
	  SCLI_CMD_FLAG_XML,
	  "", NULL,
	  cmd_scli_close },
#if 0
	{ "probe", NULL,
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_scli_probe },

	{ "walk", "<oid> [<oid> ...]",
	  "The `walk' command is a low-level debugging utility which simply\n"
	  "performs a MIB walk. Note that scli does not have general MIB\n"
	  "knowledge and hence the output requires some post-processing.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_scli_walk },
#endif
	{ "create scli plugin", "<module>",
	  "The `create scli plugin' command dynamically loads an scli mode\n"
	  "into a running scli process. This can be used to dynamically\n"
	  "extend scli with modules coming from other sources. Dynamic\n"
	  "loadable modules also simplify the development and management\n"
	  "of site-specific modules.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  cmd_scli_load },

	{ "delete scli plugin", "<module>",
	  "The `delete scli plugin' command removes a previously loaded\n"
	  "modules from a running scli process.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  cmd_scli_unload },

	{ "exit", NULL,
	  "The `exit' command terminates the scli interpreter. An end of file\n"
	  "in the standard input stream will also terminate the the scli\n"
	  "interpreter.",
	  SCLI_CMD_FLAG_XML,
	  "", NULL,
	  cmd_scli_exit },

	{ "help", NULL,
	  "The `help' command displays some help information including a list\n"
	  "of all top-level scli commands.",
	  0,
	  NULL, NULL,
	  help },

	{ "history", NULL,
	  "The `history' command displays the scli command history list with\n"
	  "line numbers.",
	  0,
	  NULL, NULL,
	  history },

        { "create scli alias", "<name> <value>",
	  "The `create scli alias' command creates the alias <name> for the\n"
	  "scli command (fragment) <value>. If the alias <name> already\n"
	  "exists, then the new <value> will be assigned to the existing\n"
	  "alias.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  create_scli_alias },
	
	{ "delete scli alias", "<regexp>",
	  "The `delete scli alias' command removes previously defined\n"
	  "aliases from the scli interpreter. The regular expression\n"
	  "<regexp> is matched against all alias names in order to\n"
	  "select the aliases that are deleted.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  delete_scli_alias },
	
        { "create scli interp", "<name>",
	  "The `create scli interp' command creates a new internal scli\n"
	  "interpreter with the name <name>.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  create_scli_interp },
	
	{ "delete scli interp", "<regexp>",
	  "The `delete scli interp' command deletes previously defined\n"
	  "scli interpreters from the main scli interpreter. The regular\n"
	  "expression <regexp> is matched against all alias names in order\n"
	  "to select the interpreter(s) to be removed.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  delete_scli_interp },
	
	{ "set scli regex", "[<regexp>]",
	  "The `set scli regex' command controls how scli matches regular\n"
	  "expressions. The optional regular expression <regexp> is\n"
	  "matched against the regular expression options. A successful\n"
	  "match turns a regular expression option on while an unsuccessful\n"
          "match turns a regular expression option off. Invoking the command\n"
	  "without the <regexp> argument will turn all regular expression\n"
	  "options off. The currently defined regular expression options\n"
	  "are \"extended\" for POSIX extended regular expressions and\n"
	  "\"case-insensitive\" for case insensitive matches.",
	  SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_NORECURSE,
	  "", NULL,
	  set_scli_regex },
	
	{ "set scli debugging", "[<regexp>]",
	  "The `set scli debugging' command sets the debugging level of\n"
	  "the SNMP engine. The optional regular expression <regexp> is\n"
	  "matched against the debugging levels. A successful match turns\n"
	  "a debugging level on while an unsuccessful match turns a\n"
	  "debugging level off. Invoking the command without the <regexp>\n"
	  "argument will turn all debugging levels off. The currently\n"
	  "defined debugging levels are \"session\" for the SNMP session\n"
	  "layer, \"request\" for the SNMP request handling layer, \n"
	  "\"transport\" for the SNMP transport layer, \"packet\" for\n"
	  "the SNMP packet layer, and \"asn1\" for the ASN.1 coding layer.",
	  SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_NORECURSE,
	  "", NULL,
	  set_scli_debugging },
	
	{ "set scli pager", "<pager>",
	  "The `set scli pager' command defines the shell command which is\n"
	  "used as a pager if the output produced by an scli command does\n"
	  "not fit on a single screen. The output is passed to the <pager>\n"
	  "shell command via its standard input stream.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_scli_pager },
	
	{ "set scli format", "<fmt>",
	  "The `set scli format' command defines the output format used by\n"
	  "subsequent scli commands. The currently supported formats are\n"
	  "\"scli\" and \"xml\". The \"scli\" format is the default output\n"
	  "format and described in this documentation. The \"xml\" output\n"
	  "format is experimental and therefore not described here.",
	  SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_NORECURSE,
	  "", NULL,
	  set_scli_format },
	
	{ "show scli info", NULL,
	  "The `show scli info' command displays the current status of the\n"
	  "scli interpreter.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_info },

	{ "show scli command info", "[<regex]",
	  "The `show scli command info' command displays summary information\n"
	  "about scli commands. The optional regular expression <regexp> is\n"
	  "matched against the command names to select the scli commands.\n",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_command_info },

	{ "show scli command details", "[<regex]",
	  "The `show scli command details' command displays detailed information\n"
	  "about scli commands. The optional regular expression <regexp> is\n"
	  "matched against the command names to select the scli commands.\n",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_command_details },

	{ "show scli command tree", NULL,
	  "The `show scli command tree' command displays the scli command\n"
	  "tree. The full command syntax is displayed for each leaf node.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_command_tree },

	{ "show scli aliases", NULL,
	  "The `show scli aliases' command lists all scli command aliases.\n"
	  "The first column in the generated table lists the aliase names\n"
	  "while the second column shows the alias values.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_aliases },

	{ "show scli interps", NULL,
	  "The `show scli interps' command lists all scli interpreters.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_interps },

	{ "show scli modes", "[<regex>]",
	  "The `show scli modes' command shows information about the scli\n"
	  "modes. An scli mode is a logical grouping of related commands\n"
	  "(e.g., all commands that deal with printers). The optional\n"
	  "regular expression <regex> can be use to select a subset of\n"
	  "the available scli modes.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_modes },

	{ "show scli schema", "[<regex>]",
	  "The `show scli schema' command produces xml schema definitions for\n"
	  "the selected scli modes. An scli mode is a logical grouping of\n"
	  "related commands (e.g., all commands that deal with printers).\n"
	  "The optional regular expression <regex> can be use to select a\n"
	  "subset of the available scli modes.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_schema },

	{ "show scli alarm info", NULL,
	  "The `show scli alarm info' command displays summary information\n"
	  "about all known alarms.",
	  0,
	  NULL, NULL,
	  show_scli_alarm_info },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t scli_mode = {
	"scli",
	"The scli mode provides commands that can be used to display and\n"
	"manipulate the internal state of the scli interpreter.",
	cmds
    };

    scli_register_mode(interp, &scli_mode);
}
