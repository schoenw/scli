/* 
 * basic.c -- basic functions for the scli command interpreter
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

#include "snmpv2-mib.h"

#include <ctype.h>
#include <errno.h>
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif
#ifdef HAVE_TERMIOS_H
#include <termios.h>
#endif


char const scli_copyright[] = "(c) 2001-2002 Juergen Schoenwaelder";

static int scli_curses_running = 0;


struct error_info {
    const int code;
    const char *fmt;
};

static const struct error_info error_infos[] = {
    { SCLI_MSG,			"%s" },
    { SCLI_OK,			"ok" },
    { SCLI_EXIT,		"ok" },
    { SCLI_ERROR,		"%s" },
    { SCLI_ERROR_NOPEER,	"no association to a remote SNMP agent" },
    { SCLI_ERROR_NOXML,		"command `%s' does not support xml" },
    { SCLI_SYNTAX,		NULL },
    { SCLI_SYNTAX_NUMARGS,	NULL },
    { SCLI_SYNTAX_REGEXP,	"invalid regular expression" },
    { SCLI_SYNTAX_NUMBER,	"invalid number" },
    { SCLI_SYNTAX_VALUE,	"invalid value" },
    { SCLI_SYNTAX_TOKENIZER,	NULL },
    { SCLI_SYNTAX_COMMAND,	NULL },
    { SCLI_SNMP,		NULL },
    { SCLI_SNMP_NAME,		"name lookup failed" },
    { 0, NULL }
};


void
scli_curses_on()
{
    if (! scli_curses_running) {
	(void) initscr();
	(void) cbreak();
	(void) noecho();
	(void) nonl();
    }
    scli_curses_running = 1;
}



void
scli_curses_off()
{
    if (scli_curses_running) {
	if (! isendwin()) (void) endwin();
    }
    scli_curses_running = 0;
}



int
scli_set_pager(scli_interp_t *interp, const char *pager)
{
    char *unsafe = ";'\\\"&|<>";

    if (pager) {
	if (strpbrk(pager, unsafe)) {
	    return -1;
	}
    }

    if (interp->pager) {
	g_free(interp->pager);
	interp->pager = NULL;
    }
    if (pager) {
	interp->pager=g_strdup(pager);
    }
    return 0;
}



void
scli_snmp_error(scli_interp_t *interp)
{
    if (interp->peer) {
	const char *error;
	error = gsnmp_enum_get_label(gsnmp_enum_error_table,
				     interp->peer->error_status);
	g_string_sprintfa(interp->result,
			  "%s", error ? error : "internalError");
	if ((int) (interp->peer->error_status) > 0) {
	    g_string_sprintfa(interp->result,
			      "@%d", interp->peer->error_index);
	}
    }
}



void
scli_get_screen(int *lines, int *columns)
{
    int rows = 24, cols = 80;	/* best guess defaults */
    
#ifdef HAVE_RESIZETERM
    struct winsize size;
    
    do {
	errno = 0;
	if (ioctl(fileno(stdout), TIOCGWINSZ, &size) < 0 && errno != EINTR) {
	    goto failure;
	}
    } while (errno == EINTR);

    if (scli_curses_running) {
	resizeterm(size.ws_row, size.ws_col);
	wrefresh(curscr);			/* Linux needs this */
    }

    rows = size.ws_row;
    cols = size.ws_col;
#endif

 failure:
    if (lines) *lines = rows;
    if (columns) *columns = cols;
}



static gint
mode_compare(gconstpointer a, gconstpointer b)
{
    scli_mode_t *mode_a = (scli_mode_t *) a;
    scli_mode_t *mode_b = (scli_mode_t *) b;

    return strcmp(mode_a->name, mode_b->name);
}



static void
page(scli_interp_t *interp, GString *s)
{
    FILE *f = NULL;
    int i, cnt, cols, rows;

    if (scli_interp_interactive(interp)) {
	if (g_snmp_list_decode_hook) {
	    g_print("\r                               \r");
	}
    } else {
    nopager:
	g_print("%s", s->str);
	return;
    }

    
    if (! interp->pager) {
	goto nopager;
    }

    for (i = 0, cnt = 0; s->str[i]; i++) {
	if (s->str[i] == '\n') {
	    cnt++;
	}
    }

    scli_get_screen(&rows, &cols);
    if (cnt < rows) {
	goto nopager;
    }

    /* Do not get fooled by nasty IFS tricks. */
    if (putenv("IFS= \t") < 0) {
	g_warning("putenv failed - ignoring pager");
	goto nopager;
    }
    
    f = popen(interp->pager, "w");
    if (! f) {
	goto nopager;
    }
    fputs(s->str, f);
    fflush(f);
    (void) pclose(f);
}



scli_interp_t*
scli_interp_create()
{
    scli_interp_t *interp;

    interp = g_malloc0(sizeof(scli_interp_t));
    interp->cmd_root = g_node_new(NULL);
    interp->result = g_string_new(NULL);
    interp->header = g_string_new(NULL);
    interp->epoch = time(NULL);
    interp->regex_flags = REG_EXTENDED|REG_NOSUB;
    interp->port = 161;

    return interp;
}



void
scli_interp_delete(scli_interp_t *interp)
{
    if (interp) {
	if (interp->cmd_root) {
	    g_node_destroy(interp->cmd_root);
	}
	if (interp->peer) {
	    g_free(interp->peer);
	}
	if (interp->result) {
	    g_string_free(interp->result, 1);
	}
	if (interp->header) {
	    g_string_free(interp->header, 1);
	}
	if (interp->pager) {
	    g_free(interp->pager);
	}
	g_free(interp);
    }
}



void
scli_interp_reset(scli_interp_t *interp)
{
    g_string_truncate(interp->result, 0);
    g_string_truncate(interp->header, 0);
    if (interp->xml_doc) {
	xmlFreeDoc(interp->xml_doc);
    }
    interp->xml_doc = xmlNewDoc("1.0");
    interp->xml_doc->children = xmlNewDocNode(interp->xml_doc, NULL, "scli", NULL);
    interp->xml_node = interp->xml_doc->children;
    xmlSetProp(interp->xml_node, "version", VERSION);
}



void
scli_register_mode(scli_interp_t *interp, scli_mode_t *mode)
{
    int i;
    
    if (interp && mode) {
	interp->mode_list = g_slist_insert_sorted(interp->mode_list,
						  mode, mode_compare);
    }

    for (i = 0; mode->cmds[i].path; i++) {
	scli_create_command(interp, mode->cmds + i);
    }
}



scli_alarm_t*
scli_alarm_create(scli_interp_t *interp, char *desc)
{
    scli_alarm_t *alarm;

    alarm = g_malloc0(sizeof(scli_alarm_t));
    alarm->detected = time(NULL);
    alarm->verified = alarm->detected;
    if (desc) alarm->desc = g_strdup(desc);

    interp->alarm_list = g_slist_append(interp->alarm_list, alarm);

    return alarm;
}



void
scli_alarm_delete(scli_interp_t *interp, scli_alarm_t *alarm)
{
    g_slist_remove(interp->alias_list, alarm);
    
    if (alarm->desc) g_free(alarm->desc);
    g_free(alarm);
}



static char *
next_token(char *string, char *out)
{
    char *p = string, *d = out;
    int dquote = 0;
    int squote = 0;

    while (*p && isspace((int) *p)) p++;	/* skip white space */
    while (*p) {
	switch (*p) {
	case '\"':
	    if (dquote) {
		if (p[1] && !isspace((int) p[1])) {
		    p++;
		    return NULL;
		} else {
		    p++;
		    goto done;
		}
	    } else {
		dquote = 1;
		p++;
	    }
	    break;
	case '\'':
	    if (squote) {
		if (p[1] && !isspace((int) p[1])) {
		    p++;
		    return NULL;
		} else {
		    p++;
		    goto done;
		}
	    } else {
		squote = 1;
		p++;
	    }
	    break;
	case '\\':
	    switch (p[1]) {
	    case 0:
		break;
	    case 'f':
		p += 2; *d++ = '\f';
		break;
	    case 'n':
		p += 2; *d++ = '\n';
		break;
	    case 'r':
		p += 2; *d++ = '\r';
		break;
	    case 't':
		p += 2; *d++ = '\t';
		break;
	    case 'v':
		p += 2; *d++ = '\v';
		break;
	    default:
		p++;			/* skip backslash and */
		*d++ = *p++;		/* copy next character */
	    }
	    break;
	case ' ':
	case '\f':
	case '\n':
	case '\r':
	case '\t':
	case '\v':
	    if (dquote || squote) {
		*d++ = *p++;		/* just copy */
	    } else {
		goto done;
	    }
	    break;
	case '#':
	    if (dquote || squote) {
		*d++ = *p++;		/* just copy */
	    } else {
		*d = 0;
		return NULL;
	    }
	    break;
	default:
	    *d++ = *p++;		/* just copy */
	    break;
	}
    }

    if (dquote || squote) {
	return NULL;
    }

 done:
    while (*p && isspace((int) *p)) p++;	/* skip white space */
    *d = 0;
    return p;
}



/*
 * Split a string into an argc/argv pair which can be passed to
 * command procedures. The memory pointed to by argv is dynamically
 * allocated; in addition to the array of pointers, it also holds
 * copies of all the list elements. It is the caller's responsibility
 * to free up all of this storage.
 *
 * XXX This code should allow ; as command separator.
 */

int
scli_split(char *string, int *argc, char ***argv)
{
    size_t size;
    char *d, *p;
    
    for (size = 1, p = string; *p; p++) {
	if (isspace((int) *p)) {
	    size++;
	}
    }
    size++;			/* leave space for final NULL pointer. */

    *argv = (char **) g_malloc0(((size * sizeof(char *)) + (p - string) + 1));

    *argc = 0;
    p = string;
    d = ((char *) *argv) + size*sizeof(char *);

    while (*p && isspace((int) *p)) p++;
    if (*p == '#') {
	return SCLI_OK;
    }
    
    while (p && *p) {
	p = next_token(p, d);
	if (! p) {
	    g_free(*argv);
	    *argv = NULL;
	    *argc = 0;
	    return SCLI_ERROR;
	}
	(*argv)[(*argc)++] = d;
	d += strlen(d) + 1;
    }

    return SCLI_OK;
}



static char *
expand_alias(scli_interp_t *interp, char *cmd)
{
    char *rest, *token;
    char *new_cmd = NULL;
    GSList *elem;
    
    /*
     * We should perhaps allow the expansion of other aliases during alias
     * expansion and only complain about alias expansion loops...
     */

    token = g_strdup(cmd);
    rest = next_token(cmd, token);
    if (token) {
	for (elem = interp->alias_list; elem; elem = g_slist_next(elem)) {
	    scli_alias_t *alias = (scli_alias_t *) elem->data;
	    if (strcmp(alias->name, token) == 0) {
		new_cmd = g_strdup_printf("%s %s",
					  alias->value, rest ? rest : "");
		return new_cmd;
	    }
	}
    }
    g_free(token);
    return NULL;
}

    

int
scli_create_command(scli_interp_t *interp, scli_cmd_t *cmd)
{
    int i, argc;
    char **argv;
    GNode *node, *child;

    if (! cmd->path) {
	g_node_append(interp->cmd_root, g_node_new(cmd));
	return SCLI_OK;
    }
    
    if (scli_split(cmd->path, &argc, &argv) != SCLI_OK) {
	return SCLI_ERROR;
    }

    if (argc == 0) {
	g_node_append(interp->cmd_root, g_node_new(cmd));
	return SCLI_OK;
    }

    cmd->name = g_strdup(argv[argc-1]);
    
    node = interp->cmd_root;
    for (i = 0; i < argc-1; i++) {
	for (child = g_node_first_child(node);
	     child;
	     child = g_node_next_sibling(child)) {
	    scli_cmd_t *this_cmd = (scli_cmd_t *) child->data;
	    if (strcmp(this_cmd->name, argv[i]) == 0) {
		break;
	    }
	}
	if (! child) {
	    scli_cmd_t *newcmd;
	    newcmd = (scli_cmd_t *) g_malloc0(sizeof(scli_cmd_t));
	    newcmd->name = g_strdup(argv[i]);
	    child = g_node_append(node, g_node_new(newcmd));
	}
	node = child;
    }

    if (node) {
	node = g_node_append(node, g_node_new(cmd));
    }

    g_free(argv);

    return SCLI_OK;
}



static void
snmp_decode_hook(GSList *list)
{
    static char x[] = { '-', '/', '-', '\\', '|' };
    static int i = 0, c = 0, n = 0;
    static time_t start, now;

    if (! list) {
	i = 0, c = 0, n = 0;
	start = time(NULL);
	return;
    }

    now = time(NULL);
    
    n++, c += g_slist_length(list), i = (i+1) % 5;
    g_print("\r%c %6.2f vps %6.2f vpm\r", x[i],
	    (now > start) ? c / (double) (now - start) : 0,
	    c / (double) n);
    fflush(stdout);
}



static xmlNodePtr
get_xml_tree(scli_interp_t *interp, char *xpath)
{
    int i, argc;
    char **argv;
    xmlNodePtr tree, sibling;

    g_return_val_if_fail(interp && xpath, NULL);
    
    if (scli_split(xpath, &argc, &argv) != SCLI_OK) {
	return NULL;
    }
    
    tree = xmlDocGetRootElement(interp->xml_doc);
    for (i = 0; i < argc; i++) {
	for (sibling = tree->children; sibling; sibling = sibling->next) {
	    if (strcmp(sibling->name, argv[i]) == 0) {
		break;
	    }
	}
	tree = sibling ? sibling : xmlNewChild(tree, NULL, argv[i], NULL);
    }

    g_free(argv);
    return tree;
}



static void
show_result(scli_interp_t *interp, int code)
{
    xmlChar *buffer;
    int len;

    if (scli_interp_xml(interp)) {
	xmlDocDumpFormatMemory(interp->xml_doc, &buffer, &len, 1);
	g_string_truncate(interp->header, 0);
	g_string_assign(interp->result, buffer);
	xmlFree(buffer);
    }
    if (! scli_interp_recursive(interp) && interp->header->len) {
	g_string_prepend_c(interp->result, '\n');
	g_string_prepend(interp->result, interp->header->str);
    }
    page(interp, interp->result);
}



static void
show_xxx(scli_interp_t *interp, scli_cmd_t *cmd, int code)
{
    int i;
    gchar *reason = NULL;

    for (i = 0; error_infos[i].code; i++) {
	if (error_infos[i].code == code) break;
    }
    g_assert(error_infos[i].code);
    
    switch (code) {
    case SCLI_SYNTAX_VALUE:
    case SCLI_SYNTAX_NUMBER:
    case SCLI_SYNTAX_REGEXP:
	reason = g_strdup_printf(error_infos[i].fmt);
	break;
    case SCLI_SYNTAX_NUMARGS:
	reason = g_strdup_printf("wrong number of arguments: should be `%s%s%s'",
		cmd->path,
		cmd->options ? " " : "",
		cmd->options ? cmd->options : "");
	break;
    case SCLI_SYNTAX:
	reason = g_strdup_printf("%3d usage: %s %s", code, cmd->path,
				 cmd->options ? cmd->options : "");
	break;
    case SCLI_SNMP:
	if (interp->peer) {
	    const char *error;
	    error = gsnmp_enum_get_label(gsnmp_enum_error_table,
					 interp->peer->error_status);
	    reason = g_strdup_printf("%s", error ? error : "internalError");
#if 0
	    if ((int) (interp->peer->error_status) > 0) {
		g_print("@%d", interp->peer->error_index);
	    }
#endif
	} else {
	    reason = g_strdup("SNMP communication error (timeout)");
	}
	break;

    case SCLI_SNMP_NAME:
	reason = g_strdup_printf("%s", error_infos[i].fmt);
	break;
    case SCLI_ERROR:
	reason = g_strdup_printf(error_infos[i].fmt,
			 interp->result->str ? interp->result->str : "");
	break;
    case SCLI_ERROR_NOPEER:
	reason = g_strdup_printf(error_infos[i].fmt);
	break;
    case SCLI_ERROR_NOXML:
	reason = g_strdup_printf(error_infos[i].fmt, cmd->path);
	break;
    case SCLI_OK:
    case SCLI_EXIT:
	reason = g_strdup("ok");
	break;
    }

    if (scli_interp_xml(interp)) {
	if (code != SCLI_OK && code != SCLI_EXIT) {
	    scli_interp_reset(interp);
	}
	if (interp->xml_doc && interp->xml_doc->children) {
	    xmlNodePtr top = interp->xml_doc->children;
	    xml_set_prop(top, "code", "%3d", code);
	    if (reason) {
		xml_set_prop(top, "reason", "%s", reason);
	    }
	    if (interp->peer) {
		xml_set_prop(top, "peer", interp->peer->taddress);
	    }
	    xml_set_prop(top, "date", "%s", fmt_timeticks(0));
	}
	if (! (scli_interp_recursive(interp))) {
	    show_result(interp, code);
	}
    } else {
	if (code == SCLI_OK || code == SCLI_EXIT) {
	    if (! (scli_interp_recursive(interp))
		&& ! (cmd->flags & SCLI_CMD_FLAG_MONITOR)) {
		show_result(interp, code);
	    }
	} else {
	    g_printerr("%s\n", reason);
	}
    }

    if (reason) g_free(reason);

    if (code == SCLI_EXIT) {
	interp->flags &= ~SCLI_INTERP_FLAG_RECURSIVE;
    }
}



static int
eval_all_cmd_node(scli_interp_t *interp, GNode *node, GString *s)
{
    scli_cmd_t *cmd, *root_cmd;
    int code;
    
    root_cmd = node->data;
    
    for (node = g_node_first_child(node);
	 node && scli_interp_recursive(interp);
	 node = g_node_next_sibling(node)) {
	cmd = node->data;
	if (G_NODE_IS_LEAF(node)) {
	    scli_cmd_t *cmd = node->data;
	    if (cmd
		&& !(cmd->flags & SCLI_CMD_FLAG_NORECURSE)
		&& !(cmd->flags & SCLI_CMD_FLAG_NEED_PEER && !interp->peer)) {
		code = scli_eval_cmd(interp, cmd, 0, NULL);
		if (code == SCLI_OK && interp->result->len) {
		    if (s->len) {
			g_string_append(s, "\n");
		    }
		    if (! scli_interp_xml(interp)) {
			g_string_sprintfa(s, "# %s",
					  cmd->path ? cmd->path : "");
			if (cmd->flags & SCLI_CMD_FLAG_NEED_PEER) {
			    g_string_sprintfa(s, " [%s]",
			      (interp->peer) ? interp->peer->taddress : "?");
			    g_string_sprintfa(s, " [%s]", fmt_timeticks(0));
			}
			g_string_sprintfa(s, "\n\n");
			if (interp->header->len) {
			    g_string_prepend_c(interp->result, '\n');
			    g_string_prepend(interp->result, interp->header->str);
			}
			g_string_append(s, interp->result->str);
		    }
		}
		if (code == SCLI_EXIT) {
		    return code;
		}
	    }
	} else {
	    code = eval_all_cmd_node(interp, node, s);
	    if (code == SCLI_EXIT) {
		return code;
	    }
	}
    }

    return SCLI_OK;
}



int
scli_eval_cmd(scli_interp_t *interp, scli_cmd_t *cmd, int argc, char **argv)
{
    int code = SCLI_OK;

    g_return_val_if_fail(cmd && cmd->func, SCLI_OK);

    g_string_truncate(interp->result, 0);
    g_string_truncate(interp->header, 0);
    if (! scli_interp_dry(interp)
	&& cmd->flags & SCLI_CMD_FLAG_NEED_PEER && ! interp->peer) {
	code = SCLI_ERROR_NOPEER;
	goto done;
    }

    if (scli_interp_xml(interp) && ! (cmd->flags & SCLI_CMD_FLAG_XML)) {
	if (! scli_interp_recursive(interp)) {
	    code = SCLI_ERROR_NOXML;
	    goto done;
	} else {
	    return SCLI_OK;
	}
    }

    if (scli_interp_xml(interp)) {
	interp->xml_node = get_xml_tree(interp, cmd->xpath);
    }

    if (cmd->flags & SCLI_CMD_FLAG_MONITOR) {
	interp->flags |= SCLI_INTERP_FLAG_MONITOR;
	code = scli_monitor(interp, cmd, argc, argv);
	interp->flags &= ~SCLI_INTERP_FLAG_MONITOR;
    } else if (cmd->flags & SCLI_CMD_FLAG_LOOP) {
	interp->flags |= SCLI_INTERP_FLAG_LOOP;
	code = scli_loop(interp, cmd, argc, argv);
	interp->flags &= ~SCLI_INTERP_FLAG_LOOP;
    } else {
	if (! scli_interp_dry(interp)
	    || (scli_interp_dry(interp) && (cmd->flags & SCLI_CMD_FLAG_DRY))) {
	    code = (cmd->func) (interp, argc, argv);
	} else {
	    code = SCLI_OK;
	}
    }

 done:
    show_xxx(interp, cmd, code);
    return code;
}



int
scli_eval_argc_argv(scli_interp_t *interp, int argc, char **argv)
{
    GNode *node = NULL;
    gboolean done = FALSE;
    int i, code = SCLI_OK;

    scli_interp_reset(interp);

    node = g_node_first_child(interp->cmd_root);
    for (i = 0; i < argc && ! done; i++) {
	while (node) {
	    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
	    if (cmd && strcmp(cmd->name, argv[i]) == 0) {
		break;
	    }
	    node = g_node_next_sibling(node);
	}
	if (! node) {
	    break;
	}
	if (i < argc-1 && ! G_NODE_IS_LEAF(node)) {
	    node = g_node_first_child(node);
	} else if (G_NODE_IS_LEAF(node)) {
	    if (scli_interp_interactive(interp)) {
		snmp_decode_hook(NULL);
		g_snmp_list_decode_hook = snmp_decode_hook;
	    } else {
		g_snmp_list_decode_hook = NULL;
	    }
	    code = scli_eval_cmd(interp, (scli_cmd_t *) node->data, argc - i, argv + i);
	    done = TRUE;
	} else if (! G_NODE_IS_LEAF(node)) {
	    GString *s;
	    done = TRUE;
	    interp->flags |= SCLI_INTERP_FLAG_RECURSIVE;
	    if (scli_interp_interactive(interp)) {
		snmp_decode_hook(NULL);
		g_snmp_list_decode_hook = snmp_decode_hook;
	    } else {
		g_snmp_list_decode_hook = NULL;
	    }
	    s = g_string_new(NULL);
	    code = eval_all_cmd_node(interp, node, s);
	    g_string_assign(interp->result, s->str);
	    g_string_free(s, 1);
	    show_result(interp, code);
	    scli_interp_reset(interp);
	    interp->flags &= ~SCLI_INTERP_FLAG_RECURSIVE;
	}
    }

    if (! done) {
	int j;
	g_print("%3d invalid command name \"", SCLI_SYNTAX_COMMAND);
	for (j = 0; j <= i; j++) {
	    g_print("%s%s", j ? " ": "", argv[j]);
	}
	g_print("\"\n");
	code = SCLI_SYNTAX;
    }

    return code;
}



int
scli_eval_string(scli_interp_t *interp, char *cmd)
{
    char **argv;
    char *expanded_cmd = NULL;
    int argc, code = SCLI_OK;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    g_return_val_if_fail(interp->cmd_root, SCLI_ERROR);

    if (! cmd) {
	return SCLI_OK;
    }

    if (scli_interp_interactive(interp)
	&& (expanded_cmd = expand_alias(interp, cmd))) {
	code = scli_split(expanded_cmd, &argc, &argv);
	g_free(expanded_cmd);
    } else {
	code = scli_split(cmd, &argc, &argv);
    }

    if (code != SCLI_OK) {
	g_print("%3d failed to tokenize input\n", SCLI_SYNTAX_TOKENIZER);
	return SCLI_ERROR;
    }

    if (argc == 0) {
	if (argv) g_free(argv);
	return SCLI_OK;
    }

    code = scli_eval_argc_argv(interp, argc, argv);

    if (argv) {
	g_free(argv);
    }

    return code;
}



int
scli_eval_file_stream(scli_interp_t *interp, FILE *stream)
{
    char buffer[1024];
    int code = SCLI_OK;
    int len;
    GString *s;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    g_return_val_if_fail(stream, SCLI_ERROR);

    s = g_string_new(NULL);
    while (code != SCLI_EXIT
	   && code != SCLI_ERROR
	   && fgets(buffer, sizeof(buffer), stream) != NULL) {
	len = strlen(buffer);
	if (len > 1
	    && buffer[len-1] == '\n'
	    && buffer[len-2] == '\\'
	    && (len == 2 || buffer[len-3] != '\\')) {
	    buffer[len-2] = 0;
	    g_string_append(s, buffer);
	} else {
	    g_string_append(s, buffer);
	    code = scli_eval_string(interp, s->str);
	    g_string_truncate(s, 0);
	}
    }
    g_string_free(s, 1);
    
    return code;
}



int
scli_eval_file(scli_interp_t *interp, char *path)
{
    FILE *stream;
    int code;

    g_return_val_if_fail(interp, SCLI_ERROR);
    g_return_val_if_fail(path, SCLI_ERROR);

    stream = fopen(path, "r");
    if (! stream) {
	g_print("%3d failed to open file \"%s\": %s\n", SCLI_ERROR,
		path, g_strerror(errno));
	return SCLI_ERROR;
    }
    code = scli_eval_file_stream(interp, stream);
    (void) fclose(stream);

    return code;
}



int
scli_eval_init_file(scli_interp_t *interp)
{
    gchar *home, *path;
    int code = SCLI_OK;

    g_return_val_if_fail(interp, SCLI_ERROR);

    home = g_get_home_dir();
    if (! home) {
	return SCLI_ERROR;
    }

    path = g_strdup_printf("%s/.sclirc", home);
    if (access(path, R_OK) == 0) {
	code = scli_eval_file(interp, path);
    }
    g_free(path);
    
    return code;
}



int
scli_open_community(scli_interp_t *interp, char *host, int port,
		    char *community)
{
    snmpv2_mib_system_t *system = NULL;

    if (interp->peer) {
	scli_close(interp);
    }

    interp->peer = g_snmp_session_new(G_SNMP_TDOMAIN_UDP_IPV4, host, port);
    if (! interp->peer) {
	return SCLI_SNMP_NAME;
    }
    
    interp->peer->rcomm = g_strdup(community ? community : "public");
    interp->peer->wcomm = g_strdup(interp->peer->rcomm);
    interp->peer->retries = 3;
    interp->peer->timeout = 1;
    interp->peer->version = G_SNMP_V2C;

    /*
     * Lets see how we can talk to this guy. We first try to speek
     * SNMPv2c (since this protocol does much better error handling)
     * and we fall back to SNMPv1 only if this is necessary.
     */

    g_snmp_list_decode_hook = NULL;

    if (scli_interp_interactive(interp)) {
	g_print("%3d Trying SNMPv2c ... ", SCLI_MSG);
    }
    snmpv2_mib_get_system(interp->peer, &system, SNMPV2_MIB_SYSUPTIME);
    if (interp->peer->error_status == 0) {
	if (scli_interp_interactive(interp)) {
	    g_print("good!\n");
	}
    } else {
	if (scli_interp_interactive(interp)) {
	    g_print("timeout.\n%d Trying SNMPv1  ... ", SCLI_MSG);
	}
	interp->peer->version = G_SNMP_V1;
	snmpv2_mib_get_system(interp->peer, &system, SNMPV2_MIB_SYSUPTIME);
	if (interp->peer->error_status == 0) {
	    if (scli_interp_interactive(interp)) {
		g_print("ok.\n");
	    }
	} else {
	    if (scli_interp_interactive(interp)) {
		g_print("timeout.\n");
	    }
	    scli_close(interp);
	}
    }
    if (system) {
	snmpv2_mib_free_system(system);
    }

    if (! interp->peer) {
	return SCLI_SNMP;
    }
    
    interp->epoch = time(NULL);
    return SCLI_OK;
}



void
scli_close(scli_interp_t *interp)
{
    g_return_if_fail(interp);

    if (interp->peer) {
	g_snmp_session_destroy(interp->peer);
	interp->peer = NULL;
	interp->epoch = time(NULL);
    }
}



char*
scli_prompt(scli_interp_t *interp)
{
    char *prompt;
    
    if (interp->peer) {
	prompt = g_strdup_printf("(%s) scli > ", interp->peer->taddress);
    } else {
	prompt = g_strdup_printf("scli > ");
    }

    return prompt;
}
