/* 
 * cmds.c -- basic commands for the scli command interpreter
 *
 * Copyright (C) 2001-2009 Juergen Schoenwaelder
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
#include <arpa/inet.h>



static GNetSnmpEnum const scli_regex_table[] = {
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
    GSList *elem;
    scli_interp_t *slave = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);
        
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    /*
     * Wait until all threads have finished they command queues.  The
     * clean way would be to ship an exit command to all threads and
     * then to wait until the threads terminate themself.
     */

    for (elem = interp->slave_list; elem; elem = g_slist_next(elem)) {
	slave = (scli_interp_t *) elem->data;
	if (slave->thread) {
	    char *cmd_exit = "exit";
	    g_print("xxx pushing exit %p\n", slave->thread);
	    scli_thread_eval_argc_argv(slave, 1, &cmd_exit);
	}
    }
	    
 again:
    for (elem = interp->slave_list; elem; elem = g_slist_next(elem)) {
	slave = (scli_interp_t *) elem->data;
	if (slave->thread) {
	    g_print("xxx joining %p\n", slave->thread);
	    (void) g_thread_join(slave->thread);
	    g_print("xxx joining %p done\n", slave->thread);
	    slave->thread = NULL;
	    goto again;
	}
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
	    "\n"
	    "<xsd:element name=\"scli\" type=\"ScliType\"/>\n"
	    "\n"
	    "<xsd:complexType name=\"ScliType\">\n"
	    "  <xsd:sequence>\n"
	    "    <xsd:element name=\"system\" type=\"SystemType\" minOccurs=\"0\"/>\n"		    
	    "    <xsd:element name=\"devices\" type=\"DevicesType\" minOccurs=\"0\"/>\n"		    
	    "  </xsd:sequence>\n"
	    "  <xsd:attribute name=\"version\" type=\"xsd:NMTOKEN\"/>\n"
	    "  <xsd:attribute name=\"peer\" type=\"xsd:NMTOKEN\"/>\n"
	    "  <xsd:attribute name=\"date\" type=\"xsd:string\"/>\n"
	    "</xsd:complexType>\n"
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
    gchar *host;
    gint ipv6, port = 161;
    gchar *community = NULL;
    GInetAddr *addr;
    GNetSnmpTAddress *taddr;
    int code;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

#if 0
    if (argc < 2 || argc > 4) {
        return SCLI_SYNTAX_NUMARGS;
    }

    host = argv[1];
    if (argc == 3) {
	community = argv[2];
    }
    if (argc == 4) {
        port = atoi(argv[2]);
	community = argv[3];
    }

    taddr = gnet_snmp_trans

    addr = gnet_inetaddr_new(host, port);
    if (! addr) {
	return SCLI_SYNTAX_VALUE;
    }

    ipv6 = gnet_inetaddr_is_ipv6(addr);

    /*
     * We prefer to use TCP so try TCP first and fall back to UDP if
     * this fails for whatever reason. Note that this may lead to a
     * long long TCP timeout. Should we have an option to force the
     * transport domain? Yes, lets add an scli configuration property
     * which lists the sequence of transports to probe.
     */
#if 1
    interp->tdomain
	    = ipv6 ? GNET_SNMP_TDOMAIN_TCP_IPV6 : GNET_SNMP_TDOMAIN_TCP_IPV4;
    
    code = scli_open_community(interp, interp->tdomain,
			       interp->taddress, community);
    if (code == SCLI_OK) {
	return code;
    }
#endif
    interp->tdomain
	    = ipv6 ? GNET_SNMP_TDOMAIN_UDP_IPV6 : GNET_SNMP_TDOMAIN_UDP_IPV4;
    code = scli_open_community(interp, interp->tdomain,
			       interp->taddress, community);
#else
    if (argc != 2) {
        return SCLI_SYNTAX_NUMARGS;
    }
    code = scli_open_community(interp, argv[1]);
#endif
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
scli_interp_eval(scli_interp_t *interp, int argc, char **argv)
{
    GSList *elem;
    scli_interp_t *slave = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc < 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    for (elem = interp->slave_list; elem; elem = g_slist_next(elem)) {
	slave = (scli_interp_t *) elem->data;
	if (strcmp(slave->name, argv[0]) == 0) {
	    break;
	}
    }

    if (! elem || !slave) {
	return SCLI_ERROR;
    }

    if (slave->thread) {
	(void) scli_thread_eval_argc_argv(slave, argc-1, argv+1);
    } else {
	(void) scli_eval_argc_argv(slave, argc-1, argv+1);
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

    for (elem = interp->slave_list; elem; elem = g_slist_next(elem)) {
	slave = (scli_interp_t *) elem->data;
	if (strcmp(slave->name, argv[1]) == 0) {
	    g_string_sprintfa(interp->result,
			      "interp `%s' already exists", argv[1]);
	    return SCLI_ERROR;
	}
    }

    slave = scli_interp_create(argv[1]);
    scli_interp_init(slave);
    if (scli_interp_proto(interp)) {
	slave->flags |= SCLI_INTERP_FLAG_PROTO;
    }
    slave->master = interp;
    interp->slave_list = g_slist_append(interp->slave_list, slave);

    cmd = g_new0(scli_cmd_t, 1);
    cmd->path = g_strdup(argv[1]);
    cmd->options = "command arg1 arg2 ...";
    cmd->flags = SCLI_CMD_FLAG_DYNAMIC;
    cmd->desc = g_strdup_printf("The `%s' command is used to invoke commands\n"
				"in the scli interpreter named %s.",
				argv[1], argv[1]);
    cmd->func = scli_interp_eval;
    scli_create_command(interp, cmd);

    slave->cmd_queue = g_async_queue_new();
    slave->thread = g_thread_create(scli_thread, slave, TRUE, NULL);

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
    for (elem = interp->slave_list; elem; elem = g_slist_next(elem)) {
	slave = (scli_interp_t *) elem->data;
	if (regexec(regex_name, slave->name, (size_t) 0, NULL, 0) == 0) {
	    interp->slave_list = g_slist_remove(interp->slave_list,
						elem->data);
	    scli_interp_delete(slave);
	    goto again;
	}
    }

    if (regex_name) regfree(regex_name);
    
    return SCLI_OK;
}



static int
show_scli_info(scli_interp_t *interp, int argc, char **argv)
{
    int const indent = 18;
    int rows, cols, c;
    GNetSnmpEnum const *dft;
    char const *label;
    char const *fmt;
    GSList *elem;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    g_string_sprintfa(interp->result, "%-*s %s\n", indent, "Version:",
		      VERSION);
    
    g_string_sprintfa(interp->result, "%-*s %lu\n", indent, "Epoch:",
		      interp->epoch);

    fmt = "scli";
    if (scli_interp_xml(interp)) {
	fmt = interp->flags & SCLI_INTERP_FLAG_FMT ? "fxml" : "xml";
    }
    g_string_sprintfa(interp->result, "%-*s %s\n", indent, "Format:", fmt);

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
    for (dft = gnet_snmp_enum_debug_table, c = 0; dft && dft->label; dft++) {
	if (gnet_snmp_debug_flags & dft->number) {
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
	gchar *name = gnet_snmp_get_uri_string(interp->peer);
	if (name) {
	    g_string_sprintfa(interp->result, "%-*s %s\n",
			      indent, "URI:", name);
	    g_free(name);
	}
	g_string_sprintfa(interp->result, "%-*s %u\n", indent,
			  "Retries:", gnet_snmp_get_retries(interp->peer));
	g_string_sprintfa(interp->result, "%-*s %u ms\n", indent,
			  "Timeout:", gnet_snmp_get_timeout(interp->peer));
	g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			  "Community:", gnet_snmp_get_community(interp->peer));
	label = gnet_snmp_enum_get_label(gnet_snmp_enum_version_table,
				 (gint32) gnet_snmp_get_version(interp->peer));
	if (label) {
	    g_string_sprintfa(interp->result, "%-*s %s\n", indent,
			      "Protocol:", label);
	} else {
	    g_string_sprintfa(interp->result, "%-*s %d\n", indent,
			      "Protocol:", gnet_snmp_get_version(interp->peer));
	}
    }

    if (interp->slave_list) {
	g_string_sprintfa(interp->result, "%-*s", indent, "Interpreters:");
	for (elem = interp->slave_list; elem; elem = g_slist_next(elem)) {
	    scli_interp_t *slave = (scli_interp_t *) elem->data;
	    g_string_sprintfa(interp->result, " %s", slave->name);
	}
	g_string_sprintfa(interp->result, "\n");
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
    GNetSnmpEnum const *dft;
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
    GNetSnmpDebugFlags flags = 0;
    GNetSnmpEnum const *dft;
    regex_t _regex_flags, *regex_flags = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc < 1 || argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 1) {
	gnet_snmp_debug_flags = 0;
	return SCLI_OK;
    }
    
    regex_flags = &_regex_flags;
    if (regcomp(regex_flags, argv[1], interp->regex_flags) != 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_REGEXP;
    }
    
    for (dft = gnet_snmp_enum_debug_table; dft && dft->label; dft++) {
	if (regexec(regex_flags, dft->label, (size_t) 0, NULL, 0) == 0) {
	    flags |= dft->number;
	}
    }
    gnet_snmp_debug_flags = flags;

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
set_scli_retries(scli_interp_t *interp, int argc, char **argv)
{
    char *end;
    guint32 retries; 

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    retries = strtoul(argv[1], &end, 0);
    if (*end || retries < 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_NUMBER;
    }

    if (scli_set_retries(interp, retries) < 0) {
	g_string_sprintfa(interp->result,
			  "illegal number of retries `%u'", retries);
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
set_scli_timeout(scli_interp_t *interp, int argc, char **argv)
{
    char *end;
    guint32 timeout; 

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    timeout = strtoul(argv[1], &end, 0);
    if (*end || timeout < 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_NUMBER;
    }

    if (scli_set_timeout(interp, timeout) < 0) {
	g_string_sprintfa(interp->result,
			  "illegal timeout `%u'", timeout);
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
	interp->flags &= ~SCLI_INTERP_FLAG_FMT;
    } else if (strcmp(argv[1], "fxml") == 0) {
	interp->flags |= SCLI_INTERP_FLAG_XML;
	interp->flags |= SCLI_INTERP_FLAG_FMT;
    } else if (strcmp(argv[1], "scli") == 0) {
	interp->flags &= ~SCLI_INTERP_FLAG_XML;
	interp->flags &= ~SCLI_INTERP_FLAG_FMT;
    } else {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_VALUE;	
    }

    return SCLI_OK;
}


static int
set_scli_mode(scli_interp_t *interp, int argc, char **argv)
{
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (strcmp(argv[1], "protocol") == 0) {
	interp->flags |= SCLI_INTERP_FLAG_PROTO;
    } else if (strcmp(argv[1], "normal") == 0) {
	interp->flags &= ~SCLI_INTERP_FLAG_PROTO;
    } else {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_VALUE;	
    }

    return SCLI_OK;
}



static void
fmt_walk(GString *s, GNetSnmpVarBind *vb)
{
    int i, printable;
    const char *t;
    
    for (i = 0; i < vb->oid_len; i++) {
	g_string_sprintfa(s, "%s%d",
			  i ? "." : "", vb->oid[i]);
    }
    t = gnet_snmp_enum_get_label(gnet_snmp_enum_type_table, vb->type);
    g_string_append(s, " = ");
    if (t) {
        g_string_sprintfa(s, "[%s] ", t);
    }
    switch (vb->type) {
    case GNET_SNMP_VARBIND_TYPE_INTEGER32:
	g_string_sprintfa(s, "%d", vb->value.i32);
	break;
    case GNET_SNMP_VARBIND_TYPE_UNSIGNED32:
    case GNET_SNMP_VARBIND_TYPE_COUNTER32:
    case GNET_SNMP_VARBIND_TYPE_TIMETICKS:
	g_string_sprintfa(s, "%u", vb->value.ui32);
	break;
    case GNET_SNMP_VARBIND_TYPE_COUNTER64:
	g_string_sprintfa(s, "%llu", vb->value.ui64);
	break;
    case GNET_SNMP_VARBIND_TYPE_IPADDRESS:
	if (vb->value_len == 4) {
	    g_string_sprintfa(s, "%d.%d.%d.%d",
			      vb->value.ui8v[0],
			      vb->value.ui8v[1],
			      vb->value.ui8v[2],
			      vb->value.ui8v[3]);
	}
	break;
    case GNET_SNMP_VARBIND_TYPE_OPAQUE:
	for (i = 0; i < vb->value_len; i++) {
	    g_string_sprintfa(s, "%s%02x", i ? ":" : "", vb->value.ui8v[i]);
	}
	break;
    case GNET_SNMP_VARBIND_TYPE_OCTETSTRING:
	for (i = 0, printable = 1; i < vb->value_len; i++) {
	    printable = printable && isprint((int) vb->value.ui8v[i]);
	}
	if (printable && vb->value_len) {
	    g_string_append(s, " \"");
	    for (i = 0; i < vb->value_len; i++) {
		g_string_append_c(s, vb->value.ui8v[i]);
	    }
	    g_string_append(s, "\"");
	} else {
	    for (i = 0; i < vb->value_len; i++) {
		g_string_sprintfa(s, "%s%02x", i ? ":" : "", vb->value.ui8v[i]);
	    }
	}
	break;
    case GNET_SNMP_VARBIND_TYPE_OBJECTID:
	for (i = 0; i < vb->value_len; i++) {
	    g_string_sprintfa(s, "%s%d",
			      i ? "." : "", vb->value.ui32v[i]);
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
    GList *in = NULL, *out = NULL;
    guint32 base[GNET_SNMP_SIZE_OBJECTID];
    GList *elem;
    int i, len;
    char *p;
    GError *error = NULL;
    GNetSnmpVarBind *vb;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc < 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    for (i = 1; i < argc; i++) {
	for (len = 0, p = argv[i]; p && *p && len < GNET_SNMP_SIZE_OBJECTID; len++) {
	    base[len] = strtoul(p, &p, 0);
	    if (p && *p) {
		if (*p == '.') {
		    p++;
		} else {
	            g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
		    g_list_free(in);
		    g_string_assign(interp->result, argv[i]);
		    return SCLI_SYNTAX_VALUE;
		}
	    }
	}
	if ((p && *p) || len < 2 || base[0] > 2 || base[1] > 40) {
	    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
	    g_list_free(in);
	    g_string_assign(interp->result, argv[i]);
	    return SCLI_SYNTAX_VALUE;
	}
	vb = gnet_snmp_varbind_new(base, len,
				   GNET_SNMP_VARBIND_TYPE_NULL, NULL, 0);
	in = g_list_append(in, vb);
    }

    out = gnet_snmp_sync_walk(interp->peer, in, &error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (error) {
	g_string_assign(interp->result, error->message);
	return SCLI_ERROR;
    }
    if (out) {
	for (elem = out; elem; elem = g_list_next(elem)) {
	    fmt_walk(interp->result, (GNetSnmpVarBind *) elem->data);
	}
    }
    g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(out);
            
    return SCLI_OK;
}



struct scan_elem {
    GNetSnmpTAddress *taddress;	/* xxx - not very efficient */
    int descr_len;
    char *descr;
};

static void
scan_elem_free(gpointer data, gpointer user_data)
{
    struct scan_elem *p = data;
    if (p) {
	if (p->taddress) gnet_snmp_taddress_delete(p->taddress);
	if (p->descr) g_free(p->descr);
	g_free(p);
    }
}

struct scanmagic {
    GMainLoop *loop;
    guint count;
    GList *scan_list;
};

static void
append_flat_string(GString *s, int len, char *string)
{
    int i;
    char last = 0;
    
    /* Remove leading and trailing white-space characters first. */

    while (len && isspace((int) string[0])) {
	string++, len--;
    }
    while (len && isspace((int) string[len-1])) {
	len--;
    }

    /* Turn \r and \n into white space characters (but only if there
       are no other white space characters. Display non-printable
       characters as special sequences such as \245. */

    for (i = 0; i < len; i++) {
	if (string[i] == '\r' || string[i] == '\n') {
  	    if (isspace(last) || isspace(string[i+1])) {
		continue;
	    } else {
	        g_string_append_c(s, ' ');
	    }
	} else {
	    if (isprint((int) string[i])) {
		g_string_append_c(s, string[i]);
	    } else {
		g_string_sprintfa(s, "\\%o", string[i]);
	    }
	}
    }
}

static gint
scan_cmp(gconstpointer a, gconstpointer b)
{
    struct scan_elem *n_a = (struct scan_elem *) a;
    struct scan_elem *n_b = (struct scan_elem *) b;
    gchar ip_a[GNET_INETADDR_MAX_LEN];
    gchar ip_b[GNET_INETADDR_MAX_LEN];
    gint len_a, len_b;

    len_a = gnet_inetaddr_get_length(n_a->taddress->inetaddr);
    len_b = gnet_inetaddr_get_length(n_b->taddress->inetaddr);

    gnet_inetaddr_get_bytes(n_a->taddress->inetaddr, ip_a);
    gnet_inetaddr_get_bytes(n_b->taddress->inetaddr, ip_b);

    if (len_a == len_b) {
	return memcmp(ip_a, ip_b, len_a);
    }

    return (len_a < len_b) ? -1 : 1;
}

static void
scan_print(gpointer data, gpointer user_data)
{
    struct scan_elem *p = (struct scan_elem *) data;
    scli_interp_t *interp = (scli_interp_t *) user_data;
    gchar *name = NULL;

    name = gnet_snmp_taddress_get_short_name(p->taddress);
    g_string_sprintfa(interp->result, "%-16s ", name);
    if (p->descr_len && p->descr) {
	append_flat_string(interp->result, p->descr_len, p->descr);
    }
    g_string_append(interp->result, "\n");
    g_free(name);
}

static gboolean
scan_one_done(GNetSnmp *s, GNetSnmpPdu *pdu, GList *vbl, gpointer magic)
{
    struct scanmagic *sm = (struct scanmagic *) magic;
    GNetSnmpVarBind *vb = NULL;
    
    sm->count--;
    if (sm->count <= 0) g_main_quit(sm->loop);
    if (s->error_status == GNET_SNMP_PDU_ERR_NOERROR && vbl) {
	struct scan_elem *p;
	p = g_new0(struct scan_elem, 1);
	p->taddress = gnet_snmp_taddress_clone(s->taddress);
	vb = vbl->data;
	if (vb->type == GNET_SNMP_VARBIND_TYPE_OCTETSTRING) {
	    p->descr_len = vb->value_len;
	    p->descr = vb->value.ui8v;
	}
	sm->scan_list = g_list_insert_sorted(sm->scan_list, p, scan_cmp);
    }
    gnet_snmp_delete(s);
    return TRUE;
}

static void
scan_one_time(GNetSnmp *s, void *magic)
{
    struct scanmagic *sm = (struct scanmagic *) magic;
    sm->count--;
    if (sm->count <= 0) g_main_quit(sm->loop);
    gnet_snmp_delete(s);
}

static void
scan_one(char *host, int port, char *community, gpointer magic)
{
    GInetAddr *inetaddr;
    GNetSnmpTDomain tdomain;
    GNetSnmpTAddress *taddress;
    GNetSnmp *s;
    static GList *in = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 1, 1, 0};
    GNetSnmpVarBind *vb;
    GError *error = NULL;

    inetaddr = gnet_inetaddr_new(host, port); /* xxx where to release? */
    if (! inetaddr) {
        g_warning("failed to convert address");
	return;
    }

    taddress = gnet_snmp_taddress_new_inet(
    	gnet_inetaddr_is_ipv6(inetaddr) ? GNET_SNMP_TDOMAIN_UDP_IPV6 : GNET_SNMP_TDOMAIN_UDP_IPV4, inetaddr);
    if (! taddress) {
        g_warning("failed to generate transport address");
	return;
    }

    s = gnet_snmp_new();
    gnet_snmp_set_transport(s, taddress);
    gnet_snmp_set_community(s, community ? community : "public");
    gnet_snmp_set_version(s, GNET_SNMP_V1);
    if (! s) {
	g_warning("failed to create session: %s\n", host);
	if (taddress) gnet_snmp_taddress_delete(taddress);
	if (inetaddr) gnet_inetaddr_delete(inetaddr);
	return;
    }

    if (! in) {
	vb = gnet_snmp_varbind_new(base, G_N_ELEMENTS(base),
				   GNET_SNMP_VARBIND_TYPE_NULL, NULL, 0);
	in = g_list_append(in, vb);
    }

    s->done_callback = scan_one_done;
    s->time_callback = scan_one_time;
    s->magic = magic;

    if (gnet_snmp_async_get(s, in, &error) == NULL) {
        g_warning("failed to send async request%s%s",
		  error ? ": " : "",
		  error ? error->message : "");
	if (taddress) gnet_snmp_taddress_delete(taddress);
	if (inetaddr) gnet_inetaddr_delete(inetaddr);
	return;
    }
    ((struct scanmagic *) magic)->count++;
    if (taddress) gnet_snmp_taddress_delete(taddress);
    if (inetaddr) gnet_inetaddr_delete(inetaddr);
}


static int
cmd_scli_scan(scli_interp_t *interp, int argc, char **argv)
{
    int prefix;
    GInetAddr *addr = NULL;
    struct scanmagic *magic;

    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc < 2 || argc > 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    /* xxx accept port numbers? accept an optional community name? version? */

    /*
     * Check the network argument which should be of the format
     * a.b.c.d/e where the lower case letters are decimal numbers
     * in a suitable range.
     */

    {
	char *p, *end;
	
	p = strchr(argv[1], '/');
	if (! p)  {
	    return SCLI_SYNTAX_VALUE;
	}
	*p = '\0', p++;
	prefix = strtol(p, &end, 0);
	if (*end || prefix < 0 || prefix > 31) {
	    g_string_assign(interp->result, p);
	    return SCLI_SYNTAX_VALUE;
	}
	
	addr = gnet_inetaddr_new(argv[1], 161);
	if (! addr) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_VALUE;
	}
    }

    if (scli_interp_dry(interp)) {
	gnet_inetaddr_delete(addr);
	return SCLI_OK;
    }

    magic = g_new0(struct scanmagic, 1);
    magic->loop = g_main_new(TRUE);

    /* put the sending loop also into the main loop so that we already
     * process responses while we are still sending requests - in fact,
     * we should do some nice traffic shaping like scotty did */
    
    {
	 guint32 ip, start, end;
	 struct in_addr ipaddr;
	 char buf[INET_ADDRSTRLEN];
	 gchar bin_addr[GNET_INETADDR_MAX_LEN];
	 gchar bin_addr_len = 0;

	 bin_addr_len = gnet_inetaddr_get_length(addr);
	 gnet_inetaddr_get_bytes(addr, bin_addr);

	 /* xxx this ipv4 specific and should be fixed */

	 start = (ntohl(* (guint32 *) bin_addr) >> (32-prefix)) << (32-prefix);
	 end = start + (1 << (32-prefix));
	 for (ip = start + 1; ip < end; ip++) {
	      ipaddr.s_addr = htonl(ip);
	      inet_ntop(AF_INET, &ipaddr, buf, sizeof(buf));
	      scan_one(buf, 161, argc == 3 ? argv[2] : "public", magic);
	 }
    }

    while(g_main_is_running(magic->loop)) {
	g_main_run(magic->loop);
    }
    g_main_destroy(magic->loop);
    g_list_foreach(magic->scan_list, scan_print, (gpointer) interp);
    g_list_foreach(magic->scan_list, scan_elem_free, NULL);
    g_free(magic);

    gnet_inetaddr_delete(addr);

    if (interp->result->len) {
	g_string_sprintfa(interp->header,
			  "ADDRESS          DESCRIPTION");
    }

    return SCLI_OK;
}


int
cmd_scli_sleep(scli_interp_t *interp, int argc, char **argv)
{
    char *end;
    guint32 secs;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    secs = strtoul(argv[1], &end, 0);
    if (*end || secs < 0) {
	g_string_assign(interp->result, argv[1]);
	return SCLI_SYNTAX_NUMBER;
    }

    sleep(secs);

    return SCLI_OK;
}


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

	{ "run scli walk", "<oid> [<oid> ...]",
	  "The `run scli walk' command is a debugging utility which simply\n"
	  "performs a MIB walk. Note that scli does not have general MIB\n"
	  "knowledge and hence the output requires some post-processing.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_scli_walk },

	{ "run scli scan", "<network> [community]",
	  "The `run scli scan' command is a utility which scans an IPv4\n"
	  "address space identified by the <network> argument. The <network>\n"
	  "must be specified in the format <ipv4address>/<prefix>.\n"
	  "The optional <community> argument is the community string\n"
	  "needed to communicate with the remote SNMP agent. The default\n"
	  "community string is \"public\".",
	  0,
	  NULL, NULL,
	  cmd_scli_scan },

	{ "run scli sleep", "<secs>",
	  "The `run scli sleep' command simply sleeps for the given amount\n"
	  "of seconds.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  cmd_scli_sleep },

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

	{ "set scli retries", "<retries>",
	  "The `set scli retries' command defines the number of SNMP\n"
	  "request retries before giving up requesting a certain object.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_scli_retries },

	{ "set scli timeout", "<milliseconds>",
	  "The `set scli timeout' command defines the number milliseconds\n"
	  "between subsequent SNMP request retries.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_scli_timeout },
	
	{ "set scli format", "<fmt>",
	  "The `set scli format' command defines the output format used by\n"
	  "subsequent scli commands. The currently supported formats are\n"
	  "\"scli\" and \"xml\". The \"scli\" format is the default output\n"
	  "format and described in this documentation. The \"xml\" output\n"
	  "format is experimental and therefore not described here.",
	  SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_NORECURSE,
	  "", NULL,
	  set_scli_format },
	
	{ "set scli mode", "<mode>",
	  "The `set scli mode' command defines the scli mode used by\n"
	  "subsequent scli commands. Setting the mode to \"protocol\"\n"
	  "will force scli to work in protocol mode. Setting the mode to\n"
	  "\"normal\" causes scli to work in normal mode where certain\n"
	  "status messages are suppressed.",
	  SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_NORECURSE,
	  "", NULL,
	  set_scli_mode },
	
	{ "show scli info", NULL,
	  "The `show scli info' command displays the current status of the\n"
	  "scli interpreter.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_info },

	{ "show scli command info", "[<regex>]",
	  "The `show scli command info' command displays summary information\n"
	  "about scli commands. The optional regular expression <regex> is\n"
	  "matched against the command names to select the scli commands.",
	  SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  show_scli_command_info },

	{ "show scli command details", "[<regex>]",
	  "The `show scli command details' command displays detailed information\n"
	  "about scli commands. The optional regular expression <regex> is\n"
	  "matched against the command names to select the scli commands.",
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
