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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "scli.h"

#include "snmpv2-mib.h"

#include <ctype.h>
#include <errno.h>
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif


char const scli_copyright[] = "(c) 2001 Juergen Schoenwaelder";

static int scli_curses_running = 0;


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
    char *file_name;
    char cmd[1024];
    FILE *f = NULL;
    int i, cnt, cols, rows;

    if (scli_interp_interactive(interp)) {
	if (g_snmp_list_decode_hook) {
	    g_print("\r                                 \r");
	}
    } else {
    nopager:
	g_print(s->str);
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

    file_name = tmpnam(NULL);
    if (! file_name) {
	goto nopager;
    }
    f = fopen(file_name, "w");
    if (! f) {
	goto nopager;
    }
    fputs(s->str, f);
    fflush(f);
    g_snprintf(cmd, sizeof(cmd), "less %s", file_name);
    (void) system(cmd);
    (void) fclose(f);
    (void) unlink(file_name);
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



/*
 * Split a string into an argc/argv pair which can be passed to
 * command procedures. The memory pointed to by argv is dynamically
 * allocated; in addition to the array of pointers, it also holds
 * copies of all the list elements. It is the caller's responsibility
 * to free up all of this storage.
 *
 * XXX This code should handle "quoted strings".
 * XXX This code should handle ; as command separators.
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

    *argv = (char **) g_malloc(((size * sizeof(char *)) + (p - string) + 1));
    
    for (*argc = 0, p = string, d = ((char *) *argv) + size*sizeof(char *);
	 *p != 0; ) {
	(*argv)[*argc] = NULL;
	while (*p && isspace((int) *p)) p++;
	if (*argc == 0 && *p == '#') {
	    break;
	}
	if (*p) {
	    char *s = p;
	    (*argv)[(*argc)++] = d;
	    while (*p && !isspace((int) *p)) p++;
	    memcpy(d, s, p-s);
	    d += p-s;
	    *d++ = 0;
	    while (*p && isspace((int) *p)) p++;
	}
    }
    
    return SCLI_OK;
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
    g_print("\r%c %6.2f vps %6.2f vpm \r", x[i],
	    (now > start) ? c / (double) (now - start) : 0,
	    c / (double) n);
    fflush(stdout);
}



static int
eval_cmd_node(scli_interp_t *interp, GNode *node, int argc, char **argv)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    int code = SCLI_OK;

    if (cmd->func) {
	g_string_truncate(interp->result, 0);
	g_string_truncate(interp->header, 0);
	if (cmd->flags & SCLI_CMD_FLAG_NEED_PEER && ! interp->peer) {
	    g_printerr("no association to a remote SNMP agent\n");
	    return SCLI_ERROR;
	}
	if (cmd->flags & SCLI_CMD_FLAG_MONITOR) {
	    code = scli_monitor(interp, node, argc, argv);
	} else {
	    code = (cmd->func) (interp, argc, argv);
	    if (interp->flags & SCLI_INTERP_FLAG_RECURSIVE) {
		return code;
	    }
	    if (interp->header->len) {
		g_string_prepend_c(interp->result, '\n');
		g_string_prepend(interp->result, interp->header->str);
	    }
	    if (interp->result->len) {
		page(interp, interp->result);
	    }
	}
    }

    return code;
}



static int
eval_all_cmd_node(scli_interp_t *interp, GNode *node, GString *s)
{
    int code;
    
    for (node = g_node_first_child(node);
	 node; node = g_node_next_sibling(node)) {
	if (G_NODE_IS_LEAF(node)) {
	    scli_cmd_t *cmd = node->data;
	    if (cmd
		&& !(cmd->flags & SCLI_CMD_FLAG_NEED_PEER && !interp->peer)) {
		code = eval_cmd_node(interp, node, 0, NULL);
		if (code == SCLI_OK && interp->result->len) {
		    if (s->len) {
			g_string_append(s, "\n");
		    }
		    if (! scli_interp_xml(interp)) {
			g_string_sprintfa(s, "%c %s [%s]\n\n", '#',
					  cmd->desc ? cmd->desc : "",
				  (interp->peer) ? interp->peer->name : "?");
		    }
		    if (interp->header->len) {
			g_string_prepend_c(interp->result, '\n');
			g_string_prepend(interp->result, interp->header->str);
		    }
		    g_string_append(s, interp->result->str);
		}
	    }
	} else {
	    eval_all_cmd_node(interp, node, s);
	}
    }

    return SCLI_OK;
}

    

int
scli_eval(scli_interp_t *interp, char *cmd)
{
    char **argv;
    int i, done = 0, argc, code = SCLI_OK;
    GNode *node = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    g_return_val_if_fail(interp->cmd_root, SCLI_ERROR);

    if (! cmd) {
	return SCLI_OK;
    }

    (void) scli_split(cmd, &argc, &argv);
    if (argc == 0) {
	if (argv) g_free(argv);
	return SCLI_OK;
    }

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
	    code = eval_cmd_node(interp, node, argc - i, argv + i);
	    done = 1;
	} else if (! G_NODE_IS_LEAF(node)) {
	    GString *s;
	    done = 1;
	    interp->flags |= SCLI_INTERP_FLAG_RECURSIVE;
	    s = g_string_new(NULL);
	    if (scli_interp_interactive(interp)) {
		snmp_decode_hook(NULL);
		g_snmp_list_decode_hook = snmp_decode_hook;
	    } else {
		g_snmp_list_decode_hook = NULL;
	    }
	    code = eval_all_cmd_node(interp, node, s);
	    page(interp, s);
	    g_string_free(s, 1);
	    g_string_truncate(interp->result, 0);
	    interp->flags &= ~SCLI_INTERP_FLAG_RECURSIVE;
	}
    }

    if (! done) {
	int j;
	g_printerr("invalid command name \"");
	for (j = 0; j <= i; j++) {
	    g_printerr("%s%s", j ? " ": "", argv[j]);
	}
	g_printerr("\"\n");
	code = SCLI_ERROR;
    }

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
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    g_return_val_if_fail(stream, SCLI_ERROR);

    while (code != SCLI_EXIT
	   && code != SCLI_ERROR
	   && fgets(buffer, sizeof(buffer), stream) != NULL) {
	code = scli_eval(interp, buffer);
    }
    
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

    path = g_malloc(strlen(home) + 20);
    strcpy(path, home);
    strcat(path, "/.sclirc");
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

    interp->peer = g_malloc0(sizeof(GSnmpSession));
    interp->peer->domain = AF_INET;
    interp->peer->name = g_strdup(host);
    interp->peer->port = port;
    interp->peer->rcomm = g_strdup(community ? community : "public");
    interp->peer->wcomm = interp->peer->rcomm;
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
	g_print("Trying SNMPv2c ... ");
    }
    if (snmpv2_mib_get_system(interp->peer, &system) == 0 && system) {
	if (scli_interp_interactive(interp)) {
	    g_print("good!\n");
	}
    } else {
	if (scli_interp_interactive(interp)) {
	    g_print("timeout.\nTrying SNMPv1  ... ");
	}
	interp->peer->version = G_SNMP_V1;
	if (snmpv2_mib_get_system(interp->peer, &system) == 0 && system) {
	    if (scli_interp_interactive(interp)) {
		g_print("ok.\n");
	    }
	} else {
	    if (scli_interp_interactive(interp)) {
		g_print("timeout.\nGiving up!\n");
	    }
	    scli_close(interp);
	}
    }
    if (system) {
	snmpv2_mib_free_system(system);
    }

    interp->epoch = time(NULL);
    return 0;
}



void
scli_close(scli_interp_t *interp)
{
    g_return_if_fail(interp);

    if (interp->peer) {
	if (interp->peer->name) g_free(interp->peer->name);
	if (interp->peer->rcomm) g_free(interp->peer->rcomm);
	g_free(interp->peer);
	interp->peer = NULL;
	interp->epoch = time(NULL);
    }
}



char*
scli_prompt(scli_interp_t *interp)
{
    char *prompt;
    
    prompt = g_malloc0(20
		       + (interp->peer ? strlen(interp->peer->name) : 0));
    if (interp->peer) {
	strcat(prompt, "(");
	strcat(prompt, interp->peer->name);
	strcat(prompt, ") scli > ");
    } else {
	strcat(prompt, "scli > ");
    }

    return prompt;
}
