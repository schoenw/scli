/* 
 * scli.c -- enumlate a command line interface via SNMP
 *
 *       After more than 10 years of SNMP, I felt it is time for the
 *       first really useful command line SNMP configuration tool. ;-)
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

#include <getopt.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

static scli_interp_t *current_interp = NULL;

/*
 * This is the main loop of the scli command interpreter. It reads a
 * command and calls the function which has been register to process
 * the command.
 */

static void
mainloop(scli_interp_t *interp, int delay)
{
    char *input;
    int code = SCLI_OK;

    g_assert(interp);

    while (code != SCLI_EXIT) {
	current_interp = interp;
	input = readline("scli > ");
	current_interp = NULL;
 	if (! input) {
	    printf("\n");
	    code = SCLI_EXIT;
	    break;
	}
	if (! *input) {
	    free(input);
	    continue;
	}
	add_history(input);
	
	code = scli_eval(interp, input);
	free(input);
    }
}

/*
 * Generator function for command completion.  STATE lets us know
 * whether to start from scratch; without any state (i.e. STATE == 0),
 * then we start at the top of the list.
 */

static char*
generator(char *text, int state)
{
    static int argc = 0;
    static char **argv = NULL;
    static size_t len;
    static GNode *last_node = NULL;

    scli_interp_t *interp = current_interp;	/* a hack, for sure */
    GNode *node;
    int i;

    /*
     * Check whether we have a valid command interpreter...
     */

    g_return_val_if_fail(interp, NULL);
    g_return_val_if_fail(interp->cmd_root, NULL);
    
    /*
     * If this is a new word to complete, initialize now.  This
     * includes saving the length of TEXT for efficiency, and
     * initializing the index variable to 0.
     */

    if (! state) {
	if (argv) {
	    g_free(argv);
	    argv = NULL;
	}
	if (scli_split(rl_line_buffer, &argc, &argv) != SCLI_OK) {
	    return NULL;
	}
	len = strlen(text);
	last_node = g_node_first_child(interp->cmd_root);
	for (i = 0; i < (len ? argc-1 : argc); i++) {
	    while (last_node) {
		scli_cmd_t *cmd = (scli_cmd_t *) last_node->data;
		if (strcmp(cmd->name, argv[i]) == 0) {
		    break;
		}
		last_node = g_node_next_sibling(last_node);
	    }
	    if (! last_node) {
		return NULL;
	    }
	    last_node = g_node_first_child(last_node);
	}
    }

    /*
     * Return the next name which partially matches from the command list.
     */

    for (node = last_node; node; node = g_node_next_sibling(node)) {
	scli_cmd_t *cmd = (scli_cmd_t *) node->data;
	if (strncmp(cmd->name, text, len) == 0) {
	    last_node = g_node_next_sibling(node);
	    return (strdup(cmd->name));
	}
    }

    return NULL;
}

/*
 *  Attempt to complete on the contents of TEXT.  START and END bound
 *  the region of rl_line_buffer that contains the word to complete.
 *  TEXT is the word to complete.  We can use the entire contents of
 *  rl_line_buffer in case we want to do some simple parsing.  Return
 *  the array of matches, or NULL if there aren't any.
 */

static char**
completion(char *text, int start, int end)
{
    char **matches;

    matches = (char **)NULL;

    /*
     * If this word is at the start of the line, then it is a command
     * to complete.  Otherwise it is the name of a file in the current
     * directory.
     */

    matches = completion_matches(text, generator);

    return (matches);
}

/*
 * Tell the GNU Readline library how to complete.  We want to try to
 * complete on command names if this is the first word in the line, or
 * on filenames if not.
 */

static void
readline_init()
{
    /* Allow conditional parsing of the ~/.inputrc file. */
    rl_readline_name = "scli";

    /* Tell the completer that we want a crack first. */
    rl_attempted_completion_function = (CPPFunction *) completion;
}

/*
 * Print some usage information if the user fails to call the program
 * correctly.
 */

static void
usage()
{
    printf("Usage: scli [OPTION] hostname [community]\n");
    printf(
	"Options:\n"
	"  -V, --version     show version information and exit\n"
	"  -f, --file        process commands from a file and exit\n"
	"  -h, --help        display this help and exit\n"
	"  -n, --norc        do not evaluate ~/.sclirc on startup\n"
	"  -p, --port        port number of the SNMP agent (default 161)\n"
	"  -r, --retries     number of retries (default 3)\n"
	"  -t, --timeout     timeout between retries in milliseconds (default 500)\n"
	);
}

/*
 * The main of scli. Parse arguments, initialize the SNMP session and
 * fall into the mainloop() until we are done.
 */

int
main(int argc, char **argv)
{
    scli_interp_t *interp;
    system_t *system = NULL;
    char *file = NULL;
    int c, i;
    
    int norc = 0, port = 161, delay = 5000, retries = 3, timeout = 500000;

    static scli_cmd_t cmds[] = {
	{ NULL, "help",
	  "help about the current mode and commands", scli_cmd_help },
	{ NULL, "exit",
	  "exit the scli command line program", scli_cmd_exit },
	{ NULL, "show",
	  "show information about a certain topic", NULL },
	{ NULL, NULL, NULL, NULL }
    };

    static struct option const long_options[] =
    {
        { "version", no_argument,       0, 'V' },
        { "file",    required_argument, 0, 'f' },
        { "help",    no_argument,       0, 'h' },
        { "norc",    no_argument,       0, 'n' },
        { "port",    required_argument, 0, 'p' },
	{ "retries", required_argument, 0, 'r' },
	{ "timeout", required_argument, 0, 't' },
        { NULL, 0, NULL, 0}
    };

    while ((c = getopt_long(argc, argv, "Vf:hnp:r:t:", long_options,
                            (int *) 0)) != EOF) {
        switch (c) {
        case 'V':
            printf("scli %s\n", VERSION);
            exit(0);
	case 'f':
	    file = optarg;
	    break;
        case 'h':
            usage();
            exit(0);
	case 'n':
	    norc = 1;
	    break;
        case 'p':
            if (atoi(optarg) <= 0 || atoi(optarg) > 65535) {
                port = atoi(optarg);
            }
            break;
	case 'r':
	    if (atoi(optarg) > 0) {
		retries = atoi(optarg);
	    }
	    break;
	case 't':
	    if (atoi(optarg) < 50) {
		timeout = 50 * 1000;
	    } else {
		timeout = atoi(optarg) * 1000;
	    }
	    break;
        default:
            usage();
            exit(1);
        }
    }

    if (argc-optind < 1 || argc-optind > 2) {
        usage();
        exit(1);
    }

    /*
     * Call the localtime() function to make sure the timezone
     * variable is set correctly. This is necessary at least on
     * Solaris machines.
     */

    {
	time_t t = 0;
	(void) localtime(&t);
    }

    /*
     * Initialize the interpreter. Register the toplevel commands.
     */

    interp = scli_interp_create();

    for (i = 0; cmds[i].name; i++) {
	scli_create_command(interp, cmds + i);
    }

    interp->interactive = (file == NULL && isatty(0));

    /*
     * Lets see how we can talk to this guy. We first try to speek
     * SNMPv2c (since this protocol does much better error handling)
     * and we fall back to SNMPv1 only if this is necessary.
     */
    
    memset(interp->peer, 0, sizeof(host_snmp));
    interp->peer->domain = AF_INET;
    interp->peer->name = g_strdup(argv[optind++]);
    interp->peer->port = port;
    interp->peer->rcomm = (argc-optind > 0) ? argv[optind++] : "public";
    interp->peer->wcomm = interp->peer->rcomm;
    interp->peer->retries = 3;
    interp->peer->timeout = 1;
    interp->peer->version = G_SNMP_V2C;

    if (interp->interactive) {
	printf("scli version %s %s\n", VERSION, scli_copyright);
    }
  
    if (! g_snmp_init(FALSE)) {
	g_error("scli: Initialisation of SNMP library failed");
        exit(1);
    }

    if (interp->interactive) {
	printf("Trying SNMPv2c ... ");
	fflush(stdout);
    }
    if (snmpv2_mib_get_system(interp->peer, &system) == 0 && system) {
	if (interp->interactive) {
	    printf("good!\n");
	}
    } else {
	if (interp->interactive) {
	    printf("timeout.\nTrying SNMPv1  ... ");
	    fflush(stdout);
	}
	interp->peer->version = G_SNMP_V1;
	if (snmpv2_mib_get_system(interp->peer, &system) == 0 && system) {
	    if (interp->interactive) {
		printf("ok.\n");
	    }
	} else {
	    if (interp->interactive) {
		printf("timeout.\nGiving up!\n");
	    }
	    exit(1);
	}
    }
    if (system) {
	snmpv2_mib_free_system(system);
    }
    if (interp->interactive) {
	printf("\n");
	fflush(stdout);
    }

    scli_init_system_mode(interp);
    scli_init_interface_mode(interp);

    if (! norc) {
	(void) scli_eval_init_file(interp);
    }

    if (interp->interactive) {
        gchar *home = g_get_home_dir();
	gchar *path = NULL;
	readline_init();
	using_history();
	if (home) {
	    path = g_malloc(strlen(home) + 20);
	    strcpy(path, home);
	    strcat(path, "/.scli_history");
	    if (access(path, R_OK) == 0) {
		if (read_history(path) != 0) {
		    perror("scli: reading history failed");
		}
	    }
	}
	mainloop(interp, delay);
	if (path) {
	    if (access(path, W_OK) == 0) {
		if (write_history(path) != 0) {
		    perror("scli: writing history failed");
		}
	    }
	    g_free(path);
	}
    } else {
	if (file) {
	    (void) scli_eval_file(interp, file);
	} else {
	    (void) scli_eval_file_stream(interp, stdin);
	}
    }

#ifdef HAVE_DMALLOC_H
    dmalloc_shutdown();
#endif

    return 0;
}
