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

#include "scli.h"

#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    char *input, *expansion, *prompt;
    int result, code = SCLI_OK;

    g_return_if_fail(interp);

    while (code != SCLI_EXIT) {
	current_interp = interp;
	prompt = scli_prompt(interp);
	input = readline(prompt);
	g_free(prompt);
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
	result = history_expand(input, &expansion);
	if (result < 0 || result == 2) {
	    free(input);
	    free(expansion);
	    continue;
	}
	free(input); input = expansion;
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
	    return (g_strdup(cmd->name));
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

    /* Don't switch to filename completion if no matches ware found. */
    if (! matches) {
       rl_completion_entry_function = (Function *) completion;
    }
    
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
    printf("Usage: scli [OPTION] [hostname [community]]\n");
    printf(
	"Options:\n"
	"  -V, --version     show version information and exit\n"
	"  -c, --command     process the given command and exit\n"
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
    char *file = NULL;
    char *cmd = NULL;
    int c, i;
    
    int norc = 0, port = 161, delay = 5000, retries = 3, timeout = 500000;

    static scli_cmd_t cmds[] = {
        { "create scli alias",
	  0,
	  "create an scli command alias",
	  scli_cmd_alias },
	{ "close",
	  0,
	  "close the association to a remote SNMP agent",
	  scli_cmd_close },
	{ "exit",
	  0,
	  "exit the scli command line program",
	  scli_cmd_exit },
	{ "help",
	  0,
	  "help about the current mode and commands",
	  scli_cmd_help },
	{ "history",
	  0,
	  "display the command history list with line numbers",
	  scli_cmd_history },
	{ "open",
	  0,
	  "open an association to a remote SNMP agent",
	  scli_cmd_open },
	{ "show scli aliases",
	  0,
	  "show information about scli aliases",
	  scli_cmd_show_aliases },
	{ "show scli association",
	  0,
	  "show information about the current scli association",
	  scli_cmd_show_peer },
	{ "show scli term",
	  0,
	  "show information about the terminal parameters",
	  scli_cmd_show_term },
	{ "delete scli alias",
	  0,
	  "delete an scli command alias",
	  scli_cmd_unalias },
	{ NULL, 0, NULL, NULL }
    };

    static struct option const long_options[] =
    {
        { "version", no_argument,       0, 'V' },
	{ "command", required_argument, 0, 'c' },
        { "file",    required_argument, 0, 'f' },
        { "help",    no_argument,       0, 'h' },
        { "norc",    no_argument,       0, 'n' },
        { "port",    required_argument, 0, 'p' },
	{ "retries", required_argument, 0, 'r' },
	{ "timeout", required_argument, 0, 't' },
        { NULL, 0, NULL, 0}
    };

    while ((c = getopt_long(argc, argv, "Vc:f:hnp:r:t:", long_options,
                            (int *) 0)) != EOF) {
        switch (c) {
        case 'V':
            printf("scli %s\n", VERSION);
            exit(0);
	case 'c':
	    cmd = optarg;
	    break;
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

    if (/*argc-optind < 1 ||*/ argc-optind > 2) {
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
     * Initialize the g_snmp library.
     */

    if (! g_snmp_init(FALSE)) {
	g_error("scli: Initialization of SNMP library failed");
        exit(1);
    }

    /*
     * Initialize the interpreter. Register the toplevel commands.
     */

    interp = scli_interp_create();

    for (i = 0; cmds[i].path; i++) {
	scli_create_command(interp, cmds + i);
    }

    if (file == NULL && cmd == NULL && isatty(0)) {
	interp->flags |= SCLI_INTERP_FLAG_INTERACTIVE;
    }

    if (interp->flags & SCLI_INTERP_FLAG_INTERACTIVE) {
	char *pager = getenv("PAGER");
	if (pager) {
	    /* xxx do a sanity-check here ? */
	    interp->pager = g_strdup(pager);
	}
    }

    if (interp->flags & SCLI_INTERP_FLAG_INTERACTIVE) {
	printf("scli version %s %s\n", VERSION, scli_copyright);
    }

    if (scli_cmd_open(interp, argc-optind+1, argv+optind-1) != SCLI_OK) {
	fputs(interp->result->str, stdout);
    }

    scli_init_system_mode(interp);
    scli_init_entity_mode(interp);
    scli_init_disman_mode(interp);
    scli_init_snmp_mode(interp);
    scli_init_ip_mode(interp);
    scli_init_udp_mode(interp);
    scli_init_tcp_mode(interp);
    scli_init_interface_mode(interp);
    scli_init_bridge_mode(interp);
    scli_init_atm_mode(interp);
    scli_init_ether_mode(interp);
    scli_init_ospf_mode(interp);
    scli_init_printer_mode(interp);

    if (! norc) {
	(void) scli_eval_init_file(interp);
    }

    if (interp->flags & SCLI_INTERP_FLAG_INTERACTIVE) {
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
	    if (access(path, W_OK) != 0) {
		close(creat(path, 0600));
	    }
	    if (access(path, W_OK) == 0) {
		int history_file_size = 1000;	/* arbitrary choice */
		char *histfilesize = getenv("HISTFILESIZE");
		if (histfilesize) {
		    history_file_size = atoi(histfilesize);
		}
		stifle_history(history_file_size);
		if (write_history(path) != 0) {
		    perror("scli: writing history failed");
		}
	    }
	    g_free(path);
	}
    } else if (file) {
	(void) scli_eval_file(interp, file);
    } else if (cmd) {
	(void) scli_eval(interp, cmd);
    } else {
	(void) scli_eval_file_stream(interp, stdin);
    }

#ifdef HAVE_DMALLOC_H
    dmalloc_shutdown();
#endif

    return 0;
}
