/* 
 * scli.c -- emulate a command line interface on top of SNMP
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

#include "scli.h"

#include <string.h>
#include <errno.h>
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
    int result, len, code = SCLI_OK;
    GString *s;

    g_return_if_fail(interp);

    s = g_string_new(NULL);
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
	len = strlen(input);
	if (len > 0
	    && input[len-1] == '\\'
	    && (len == 1 || input[len-2] != '\\')) {
	    input[len-1] = 0;
	    g_string_append(s, input);
	} else {
	    g_string_append(s, input);
	    add_history(s->str);
	    code = scli_eval_string(interp, s->str);
	    g_string_truncate(s, 0);
	}
	free(input);
    }
    g_string_free(s, 1);
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
    static GSList *last_elem = NULL;

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
	if (argc == 0 || (argc < 2 && len && !isspace((int) text[len-1]))) {
	    last_elem = interp->alias_list;
	} else {
	    last_elem = NULL;
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

    if (! node && last_elem) {
	GSList *elem;
	for (elem = last_elem; elem; elem = g_slist_next(elem)) {
	    scli_alias_t *alias = (scli_alias_t *) elem->data;
	    if (strncmp(alias->name, text, len) == 0) {
		last_elem = g_slist_next(elem);
		return (g_strdup(alias->name));
	    }
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
#ifdef HAVE_RL_COMPLETION_MATCHES
       rl_completion_entry_function = (rl_compentry_func_t *) completion;
#else
       rl_completion_entry_function = (Function *) completion;
#endif
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
 * The main of scli. Parse arguments, initialize the SNMP session and
 * fall into the mainloop() until we are done.
 */

int
main(int argc, char **argv)
{
    scli_interp_t *interp;
    int i, c;
    gint args = 0;

    GError *error = NULL;
    GOptionContext *context;
    static gboolean opt_bool_version = FALSE;
    static gchar *opt_string_cmd = NULL;
    static gchar *opt_string_file = NULL;
    static gboolean opt_bool_dry = FALSE;
    static gboolean opt_bool_quiet = FALSE;
    static gboolean opt_bool_norc = FALSE;
    static gint opt_int_delay = 5000;
    static gchar **opt_string_array_args = NULL;

    static gboolean opt_bool_xml = FALSE;
    static gboolean opt_bool_inet = FALSE;

    static GOptionEntry entries[] = {
	{ "version", 'V', 0, G_OPTION_ARG_NONE, &opt_bool_version,
	  "Show version information and exit", NULL },
	{ "command", 'c', 0, G_OPTION_ARG_STRING, &opt_string_cmd,
	  "Process the scli command C and exit", "C" },
	{ "file", 'f', 0, G_OPTION_ARG_FILENAME, &opt_string_file,
	  "Process scli commands from file F and exit", "F" },
	{ "delay", 'd', 0, G_OPTION_ARG_INT, &opt_int_delay,
	  "Set the delay between screen to D seconds (default 5)", "D" },
	{ "dry", 's', 0, G_OPTION_ARG_NONE, &opt_bool_dry,
	  "Parse commands but do not execute them", NULL },
	{ "norc", 'n', 0, G_OPTION_ARG_NONE, &opt_bool_norc,
	  "Do not evaluate ~/.sclirc on startup", NULL },
	{ "quiet", 'q', 0, G_OPTION_ARG_NONE, &opt_bool_quiet,
	  "Suppress informational messages", NULL },

	{ "xml", 'x', 0, G_OPTION_ARG_NONE, &opt_bool_xml,
	  "Produce machine readable XML output", NULL },
	{ "inet", 'i', 0, G_OPTION_ARG_NONE, &opt_bool_inet,
	  "Execute in 'inet/netconf' protocol mode (experimental)", NULL },

	{ G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_STRING_ARRAY,
	  &opt_string_array_args, NULL, NULL },
	{ NULL }
    };

    context = g_option_context_new("[hostname [community]]");
    g_option_context_add_main_entries(context, entries, NULL);
    g_option_context_add_group (context, gnet_snmp_get_option_group());
    if (! g_option_context_parse(context, &argc, &argv, &error)) {
	g_printerr("%s: %s\n", g_get_prgname(),
		   (error && error->message) ? error->message
		   : "option parsing failed");
	return 1;
    }

    /*
     * Check the number of optional paramters we received.
     */

    for (args = 0;
	 opt_string_array_args && opt_string_array_args[args]; args++) ;
    if (args > 2) {
	g_printerr("%s: illegal number of arguments; use --help for help\n",
		   g_get_prgname());
        exit(1);
    }

    /*
     * Handle simple requests first...
     */

    if (opt_bool_version) {
	g_print("scli version %s\n", PACKAGE_VERSION);
	g_print("Copyright %s\n", scli_copyright);
	g_print("scli comes with ABSOLUTELY NO WARRANTY.\n"
		"You may redistribute copies of scli under\n"
		"the terms of the GNU General Public License.\n");
	exit(0);
    }

    /*
     * Inet/netconf protocol mode implies some other settings.
     */

    if (opt_bool_inet) {
	opt_bool_norc = TRUE;
	opt_bool_xml = TRUE;
	opt_bool_quiet = TRUE;
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

#if 0
    /*
     * Initialize the g_snmp library.
     */

    if (! gnet_snmp_init(FALSE)) {
	g_error("scli: initialization of SNMP library failed");
        exit(1);
    }
#endif

    /*
     * Setting up curses in such a way that we are sure to restore
     * the tty into something useful when we are done.
     */

    signal(SIGINT, onsignal);
    signal(SIGTERM, onsignal);
    signal(SIGHUP, onsignal);
    signal(SIGQUIT, onsignal);
    signal(SIGWINCH, onwinch);
    if (! opt_bool_inet) {
	signal(SIGPIPE, SIG_IGN);
    }

    /*
     * Initialize the interpreter. Register the toplevel commands.
     */

    interp = scli_interp_create(NULL);

    if (opt_string_file == NULL && opt_string_cmd == NULL && isatty(0)) {
	interp->flags |= SCLI_INTERP_FLAG_INTERACTIVE;
    }

    interp->delay = opt_int_delay;

    if (opt_bool_inet) {
	interp->flags |= SCLI_INTERP_FLAG_PROTO;
    }

    if (opt_bool_xml) {
	interp->flags |= SCLI_INTERP_FLAG_XML;
#if 0
	xmlXPathInit();
#endif
    }

    if (opt_bool_dry) {
	interp->flags |= SCLI_INTERP_FLAG_DRY;
    }

    if (opt_bool_quiet) {
	interp->flags |= SCLI_INTERP_FLAG_QUIET;
    }

    if (!scli_interp_quiet(interp)) {
	g_print("%3d-scli version %s %s\n",
		SCLI_MSG, PACKAGE_VERSION, scli_copyright);
    }

    if (scli_interp_interactive(interp) && ! scli_interp_proto(interp)) {
	if (scli_set_pager(interp, getenv("PAGER")) < 0) {
	    g_warning("$PAGER contains unsafe characters - ignored\n");
	}
    }

    scli_interp_init(interp);

    if (args) {
	char *margv[] = { "open", NULL, NULL, NULL };
	int i;
	for (i = 0; opt_string_array_args[i]
		 && i < sizeof(margv)/sizeof(margv[0]); i++) {
	    margv[i+1] = opt_string_array_args[i];
	}
	(void) scli_eval_argc_argv(interp, i+1, margv);
    }

    if (!opt_bool_norc) {
	(void) scli_eval_init_file(interp);
    }

    if (opt_bool_inet) {
	c = scli_netconf_mainloop(interp, stdin);
	return (c == SCLI_OK) ? 0 : 1;
    }

    if (scli_interp_interactive(interp)) {
        const gchar *home = g_get_home_dir();
	gchar *path = NULL;
	readline_init();
	using_history();
	if (home) {
	    path = g_strdup_printf("%s/.scli_history", home);
	    if (access(path, R_OK) == 0) {
		if (read_history(path) != 0) {
		    g_printerr("scli: reading history failed: %s",
			       g_strerror(errno));
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
		    g_printerr("scli: writing history failed: %s",
			       g_strerror(errno));
		}
	    }
	    g_free(path);
	}
    } else if (opt_string_file) {
	(void) scli_eval_file(interp, opt_string_file);
    } else if (opt_string_cmd) {
	(void) scli_eval_string(interp, opt_string_cmd);
    } else {
	interp->flags |= SCLI_INTERP_FLAG_PROTO;
	(void) scli_eval_file_stream(interp, stdin);
    }

    return 0;
}
