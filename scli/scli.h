/* 
 * scli.h -- emulate a command line interface via SNMP
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

#ifndef _SCLI_H
#define _SCLI_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <time.h>
#ifdef HAVE_NCURSES_H
#include <ncurses.h>
#else
#include <curses.h>
#endif

#include <libxml/xmlmemory.h>
#include <libxml/tree.h>

#include "g_snmp.h"


extern char const scli_copyright[];	/* copyright message (surprise) */


/*
 * Some defines used internally to compute time differences and
 * to check whether the polling interval was too short.
 */

#define TV_DIFF(t1, t2) (1.0 * (t2.tv_sec - t1.tv_sec) + \
                         (t2.tv_usec - t1.tv_usec) / 1000000.0)
#define TV_DELTA	0.1

/*
 * The return codes used by the scli commands functions.
 */

#define SCLI_OK			0	/* normal return code */
#define SCLI_ERROR		1	/* generic error return code */
#define SCLI_EXIT		2	/* return and exit the command loop */
#define SCLI_SYNTAX		3	/* generic syntax error */
#define SCLI_SYNTAX_REGEXP	4	/* syntax error in regexp */


typedef struct scli_interp	scli_interp_t;
typedef struct scli_mode	scli_mode_t;
typedef struct scli_cmd		scli_cmd_t;
typedef struct scli_alias	scli_alias_t;


#define SCLI_CMD_FLAG_NEED_PEER	0x01
#define SCLI_CMD_FLAG_MONITOR	0x02
#define SCLI_CMD_FLAG_XML	0x04

struct scli_cmd {
    char *path;			/* absolute command name */
    char *options;		/* options accepted by the command */
    char *desc;			/* description of the command */
    int   flags;		/* command flags (see above) */
    char *xpath;		/* xml path */
    char *xsd;			/* xml schema definition */
    int (*func) (scli_interp_t *interp, int argc, char **argv);
				/* function implementing the command */
    char *name;			/* name of the command (last elem of path) */
};

struct scli_mode {
    char *name;			/* name of the mode */
    char *desc;			/* description of the mode */
    scli_cmd_t *cmds;		/* array of command provided by the mode */
};

struct scli_alias {
    char *name;			/* name of the command alias */
    char *value;		/* value of the command alias */
};


#define SCLI_INTERP_FLAG_INTERACTIVE	0x01
#define SCLI_INTERP_FLAG_RECURSIVE	0x02
#define SCLI_INTERP_FLAG_XML		0x04
#define SCLI_INTERP_FLAG_MONITOR	0x08

struct scli_interp {
    GNode *cmd_root;		/* root of the command tree */
    GSList *mode_list;		/* list of registered modes */
    GSList *alias_list;		/* list of command aliases */
    int	flags;			/* interpreter flags */
    GString *result;		/* string result buffer */
    GString *header;		/* header line to display */
    xmlDocPtr xml_doc;		/* xml document if we produce xml output */
    xmlNodePtr xml_node;	/* current xml node in the xml document */
    char *pager;		/* external pager we are using */
    GSnmpSession *peer;		/* snmp peer we are talking to */
    gint delay;			/* delay between updates in milliseconds */
    time_t epoch;		/* epoch used to invalidate cached data */
};

extern scli_interp_t *
scli_interp_create();

extern void
scli_interp_delete();

#define scli_interp_interactive(interp) \
	(interp->flags & SCLI_INTERP_FLAG_INTERACTIVE)
#define scli_interp_recursive(interp) \
	(interp->flags & SCLI_INTERP_FLAG_RECURSIVE)
#define scli_interp_xml(interp) \
	(interp->flags & SCLI_INTERP_FLAG_XML)
#define scli_interp_monitor(interp) \
	(interp->flags & SCLI_INTERP_FLAG_MONITOR)

extern int
scli_split(char *string, int *argc, char ***argv);

extern int
scli_monitor(scli_interp_t *interp, GNode *node, int argc, char **argv);

extern int
scli_eval(scli_interp_t *interp, char *cmd);

extern int
scli_eval_file(scli_interp_t *interp, char *path);

extern int
scli_eval_file_stream(scli_interp_t *interp, FILE *stream);

extern int
scli_eval_init_file(scli_interp_t *interp);

extern void
scli_register_mode(scli_interp_t *interp, scli_mode_t *mode);

extern int
scli_create_command(scli_interp_t *interp, scli_cmd_t *cmd);

extern int
scli_open_community(scli_interp_t *interp, char *host, int port,
		    char *community);
extern void
scli_close(scli_interp_t *interp);

extern char*
scli_prompt(scli_interp_t *interp);

extern void
scli_get_screen(int *rows, int *cols);

extern void
scli_curses_on();

extern void
scli_curses_off();

extern int
scli_set_pager(scli_interp_t *interp, const char *pager);

extern void
scli_snmp_error(scli_interp_t *interp);

/*
 * Core scli commands:	XXX this should not be visible across modules XXX
 */

extern int
scli_cmd_open(scli_interp_t *interp, int argc, char **argv);

/*
 * Initialization functions for the various scli modes.
 */

extern void
scli_init_scli_mode(scli_interp_t *interp);

extern void
scli_init_system_mode(scli_interp_t *interp);

extern void
scli_init_entity_mode(scli_interp_t *interp);

extern void
scli_init_interface_mode(scli_interp_t *interp);

extern void
scli_init_disman_mode(scli_interp_t *interp);

extern void
scli_init_snmp_mode(scli_interp_t *interp);

extern void
scli_init_ip_mode(scli_interp_t *interp);

extern void
scli_init_udp_mode(scli_interp_t *interp);

extern void
scli_init_tcp_mode(scli_interp_t *interp);

extern void
scli_init_bridge_mode(scli_interp_t *interp);

extern void
scli_init_atm_mode(scli_interp_t *interp);

extern void
scli_init_ether_mode(scli_interp_t *interp);

extern void
scli_init_ospf_mode(scli_interp_t *interp);

extern void
scli_init_printer_mode(scli_interp_t *interp);

extern void
scli_init_cisco_mode(scli_interp_t *interp);

extern void
scli_init_nortel_mode(scli_interp_t *interp);

/* 
 * A data structure used to obtain vendor information from the
 * enterprise OID. See the file vendors.c for details.
 */
 
typedef struct scli_vendor {
    guint32  id;
    char     *name;
    char     *url;
} scli_vendor_t;

extern scli_vendor_t*
scli_get_iana_vendor(guint32 oid[], gsize len);

extern scli_vendor_t*
scli_get_ieee_vendor(guint32 prefix);

/*
 * Formatting utilities that are used frequently by scli modes.
 */

extern const char *
fmt_timeticks(guint32 timeticks);

extern char const *
fmt_date_and_time(guchar *data, gsize len);

extern char const *
fmt_date_and_time_delta(guchar *date1, gsize len1, guchar *date2, gsize len2);

extern char const *
fmt_seconds(guint32 seconds);

extern char const *
fmt_enum(GSnmpEnum const *table, gint32 *number);

extern void
xxx_enum(GString *s, int width, GSnmpEnum const *table, gint32 *number);

extern char const *
fmt_kmg(guint32 number);

extern char const *
fmt_gtp(guint32 number);

#define SCLI_FMT_ADDR		0x01
#define SCLI_FMT_NAME		0x02
#define SCLI_FMT_NAME_OR_ADDR	(SCLI_FMT_ADDR | SCLI_FMT_NAME)

extern char*
fmt_udp_port(int port, int flags);

extern char*
fmt_tcp_port(int port, int flags);

extern char*
fmt_ipv4_address(guchar *addr, int flags);

extern char*
fmt_ipv4_mask(guchar *addr);

extern char*
fmt_ether_address(guchar *addr, int flags);

extern void
fmt_counter_dt(GString *s, guint32 *new_counter, guint32 *old_counter,
	       struct timeval *last, double delta);
extern void
fmt_display_string(GString *s, int indent, char *label, int len, char *string);
    
/*
 * XML utilities.
 */

extern void
xml_set_prop(xmlNodePtr node, const xmlChar *name, const char *fmt, ...)
    G_GNUC_PRINTF(3, 4);

extern void
xml_set_content(xmlNodePtr node, const char *fmt, ...)
    G_GNUC_PRINTF(2, 3);

extern xmlNodePtr
xml_new_child(xmlNodePtr parent, xmlNsPtr ns, const xmlChar *name,
	      const char *format, ...) G_GNUC_PRINTF(4, 5);
    
#endif /* _SCLI_H */

