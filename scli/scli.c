/* 
 * scli.c -- emulate a command line interface via SNMP
 *
 *       After more than 10 years of SNMP, I felt it is time for the
 *       first really useful command line SNMP management tool. ;-)
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
#include <signal.h>
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#include <readline/readline.h>
#include <readline/history.h>

static scli_interp_t *current_interp = NULL;

/*
 * Make sure we quit curses when we receive signals to abort the
 * process. Otherwise, we might leave the terminal in an unusable
 * state.
 */

static void
onsignal(int n)
{
    scli_curses_off();
    exit(n);
}

/*
 * Track window change events using whatever mechanism is available.
 */

static void
onwinch(int n)
{
    scli_get_screen(NULL, NULL);
    (void) signal(SIGWINCH, onwinch);	/* some systems need this */
}

/*
 * This is the main loop of the scli command interpreter. It reads a
 * command and calls the function which has been register to process
 * the command.
 */

static void
mainloop(scli_interp_t *interp)
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
	    g_print("\n");
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
generator(char const *text, int state)
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

#ifdef HAVE_RL_COMPLETION_MATCHES
    matches = rl_completion_matches(text, generator);
#else
    matches = completion_matches(text, generator);
#endif

    /*
     * Do not switch to filename completion if no matches were found.
     */
    
    if (! matches) {
       rl_completion_entry_function = (Function *) completion;
    }
    
    return matches;
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
 * Print some usage information if the user fails to call the
 * program correctly.
 */

static void
usage()
{
    g_print("Usage: scli [OPTION] [hostname [community]]\n");
    g_print(
	"Options:\n"
	"  -V, --version     show version information and exit\n"
	"  -c, --command     process the given command and exit\n"
	"  -d, --delay       delay in seconds between screen updates (default 5)\n"
	"  -f, --file        process commands from a file and exit\n"
	"  -h, --help        display this help and exit\n"
	"  -n, --norc        do not evaluate ~/.sclirc on startup\n"
	"  -p, --port        port number of the SNMP agent (default 161)\n"
	"  -r, --retries     number of retries (default 3)\n"
	"  -t, --timeout     timeout between retries in milliseconds (default 500)\n"
	"  -x, --xml         produce machine readable XML output\n"
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
    int c;
    
    int norc = 0, port = 161, delay = 5000, retries = 3, timeout = 500000;
    int xml = 0;

    static struct option const long_options[] =
    {
        { "version", no_argument,       0, 'V' },
	{ "command", required_argument, 0, 'c' },
        { "delay",   required_argument, 0, 'd' },
        { "file",    required_argument, 0, 'f' },
        { "help",    no_argument,       0, 'h' },
        { "norc",    no_argument,       0, 'n' },
        { "port",    required_argument, 0, 'p' },
	{ "retries", required_argument, 0, 'r' },
	{ "timeout", required_argument, 0, 't' },
	{ "xml",     no_argument,	0, 'x' },
        { NULL, 0, NULL, 0}
    };

    while ((c = getopt_long(argc, argv, "Vc:d:f:hnp:r:t:x", long_options,
                            (int *) 0)) != EOF) {
        switch (c) {
        case 'V':
	    g_print("scli version %s\n", VERSION);
	    g_print("Copyright %s\n", scli_copyright);
	    g_print("scli comes with ABSOLUTELY NO WARRANTY.\n"
		    "You may redistribute copies of scli under\n"
		    "the terms of the GNU General Public License.\n");
	    exit(0);
	case 'c':
	    cmd = optarg;
	    break;
        case 'd':
            if (atoi(optarg) > 0) {
                delay = atoi(optarg) * 1000;
            }
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
	case 'x':
	    xml = 1;
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
     * Setting up curses in such a way that we are sure to restore
     * the tty into something useful when we are done.
     */

    signal(SIGINT, onsignal);
    signal(SIGTERM, onsignal);
    signal(SIGHUP, onsignal);
    signal(SIGQUIT, onsignal);
    signal(SIGWINCH, onwinch);

    /*
     * Initialize the interpreter. Register the toplevel commands.
     */

    interp = scli_interp_create();

    if (file == NULL && cmd == NULL && isatty(0)) {
	interp->flags |= SCLI_INTERP_FLAG_INTERACTIVE;
    }

    interp->delay = delay;

    if (xml) {
	interp->flags |= SCLI_INTERP_FLAG_XML;
    }

    if (scli_interp_interactive(interp)) {
	g_print("scli version %s %s\n", VERSION, scli_copyright);
    }

    if (scli_interp_interactive(interp)) {
	if (scli_set_pager(interp, getenv("PAGER")) < 0) {
	    g_warning("$PAGER contains unsafe characters - ignored\n");
	}
    }

    if (scli_cmd_open(interp, argc-optind+1, argv+optind-1) != SCLI_OK) {
	g_printerr(interp->result->str);
    }

    scli_init_scli_mode(interp);
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

    if (scli_interp_interactive(interp)) {
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
	mainloop(interp);
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

    return 0;
}
