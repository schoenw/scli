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

#include <ctype.h>


char const scli_copyright[] = "(c) 2001 Juergen Schoenwaelder";


scli_interp_t*
scli_interp_create()
{
    scli_interp_t *interp;

    interp = g_malloc0(sizeof(scli_interp_t));
    interp->cmd_root = g_node_new(NULL);
    interp->peer = g_malloc0(sizeof(host_snmp));
    interp->result = g_string_new(NULL);

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
	g_free(interp);
    }
}


void
scli_register_mode(scli_interp_t *interp, scli_mode_t *mode)
{
    int i;
    
    if (interp && mode) {
	interp->mode_list = g_slist_append(interp->mode_list, mode);
    }

    for (i = 0; mode->cmds[i].name; i++) {
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
    GNode *node;

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
    
    node = interp->cmd_root;
    for (i = 0; i < argc; i++) {
	for (node = g_node_first_child(node);
	     node;
	     node = g_node_next_sibling(node)) {
	    scli_cmd_t *this_cmd = (scli_cmd_t *) node->data;
	    if (strcmp(this_cmd->name, argv[i]) == 0) {
		break;
	    }
	}
	if (! node) {
	    g_free(argv);
	    return SCLI_ERROR;
	}
    }

    if (node) {
	node = g_node_append(node, g_node_new(cmd));
    }

    return SCLI_OK;
}


static int
eval_cmd_node(scli_interp_t *interp, GNode *node, int argc, char **argv)
{
    scli_cmd_t *cmd = (scli_cmd_t *) node->data;
    int code = SCLI_OK;
   
    if (cmd->func) {
	g_string_truncate(interp->result, 0);
	code = (cmd->func) (interp, argc, argv);
	if (interp->result) {
	    fputs(interp->result->str, stdout);
	}
    }

    return code;
}



static int
eval_all_cmd_node(scli_interp_t *interp, GNode *node)
{
    for (node = g_node_first_child(node);
	 node; node = g_node_next_sibling(node)) {
	if (G_NODE_IS_LEAF(node)) {
	    scli_cmd_t *cmd = node->data;
	    if (cmd) {
		printf("scli > %s %s\n", cmd->path, cmd->name);
		eval_cmd_node(interp, node, 0, NULL);
	    }
	} else {
	    eval_all_cmd_node(interp, node);
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
	    code = eval_cmd_node(interp, node, argc - i, argv + i);
	    done = 1;
	} else if (! G_NODE_IS_LEAF(node)) {
	    done = 1;
	    code = eval_all_cmd_node(interp, node);
	}
    }

    if (! done) {
	int j;
	printf("invalid command name \"");
	for (j = 0; j <= i; j++) {
	    printf("%s%s", j ? " ": "", argv[j]);
	}
	printf("\"\n");
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
    
    g_assert(interp);
    g_assert(stream);

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

    g_assert(interp);
    g_assert(path);

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

    g_assert(interp);

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
