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
#include <regex.h>

#include <libxml/xmlmemory.h>
#include <libxml/tree.h>

#include <glib.h>
#include <gmodule.h>

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
 *
 * Theory of scli return codes:
 *
 * 1xy - transient messages
 * 2xy - positive completion
 * 3xy - generic error codes
 * 4xy - errors detected before command processing
 * 5xy - communication failure
 */

#define SCLI_MSG		100	/* arbitrary message */
#define SCLI_OK			200	/* normal return code */
#define SCLI_EXIT		201	/* return and exit the command loop */
#define SCLI_ERROR		300	/* generic error return code */
#define SCLI_ERROR_NOPEER	301	/* no association to SNMP peer */
#define SCLI_ERROR_NOXML	302	/* command does not support XML */
#define SCLI_SYNTAX		400	/* generic syntax error */
#define SCLI_SYNTAX_NUMARGS	401	/* syntax error in number of args */
#define SCLI_SYNTAX_REGEXP	402	/* syntax error in regexp */
#define SCLI_SYNTAX_NUMBER	403	/* syntax error in number */
#define SCLI_SYNTAX_VALUE	404	/* syntax error in value */
#define SCLI_SYNTAX_TOKENIZER	405	/* syntax error in tokenizer */
#define SCLI_SYNTAX_COMMAND	406	/* syntax error unknown command */
#define SCLI_SNMP		500	/* snmp error return code */
#define SCLI_SNMP_NAME		501	/* snmp name lookup error */


typedef struct scli_interp	scli_interp_t;
typedef struct scli_mode	scli_mode_t;
typedef struct scli_cmd		scli_cmd_t;
typedef struct scli_alias	scli_alias_t;
typedef struct scli_alarm	scli_alarm_t;


#define SCLI_CMD_FLAG_NEED_PEER	(1 << 0)
#define SCLI_CMD_FLAG_MONITOR	(1 << 1)
#define SCLI_CMD_FLAG_LOOP	(1 << 2)
#define SCLI_CMD_FLAG_XML	(1 << 3)
#define SCLI_CMD_FLAG_DRY	(1 << 4)
#define SCLI_CMD_FLAG_NORECURSE	(1 << 5)

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
    GModule *module;		/* module handle (if any) */
};

struct scli_alias {
    char *name;			/* name of the command alias */
    char *value;		/* value of the command alias */
};

/*
 * The following severity values are aligned with ITU M.3100
 * and X.733 and the IETF DISMAN Alarm MIB.
 */

#define SCLI_ALARM_SEVERITY_CLEARED		0x01
#define SCLI_ALARM_SEVERITY_INDETERMINATE	0x02
#define SCLI_ALARM_SEVERITY_CRITICAL		0x03
#define SCLI_ALARM_SEVERITY_MAJOR		0x04
#define SCLI_ALARM_SEVERITY_MINOR		0x05
#define SCLI_ALARM_SEVERITY_WARNING		0x06

/*
 * The following trend indication values are aligned with
 * ITU M.3100 and X.733 and the IETF DISMAN Alarm MIB.
 */

#define SCLI_ALARM_TREN_MORESEVERE	0x01
#define SCLI_ALARM_TREN_NOCHANGE	0x02
#define SCLI_ALARM_TREN_LESSSEVERE	0x03

struct scli_alarm {
    time_t	detected;	/* detection time of the alarm */
    time_t	verified;	/* last verification of the alarm */
    time_t	cleared;	/* clear time of the alarm */
    gchar	*desc;		/* description of the alarm */
    int		state;		/* state of the alarm */
    int		severity;	/* perceived severity of the alarm */
    int		trend;		/* trend indication */
    gpointer	detector;	/* identification of the detector */
    gpointer	resource;	/* identification of the resource */
};


#define SCLI_INTERP_FLAG_INTERACTIVE	0x01
#define SCLI_INTERP_FLAG_RECURSIVE	0x02
#define SCLI_INTERP_FLAG_MONITOR	0x04
#define SCLI_INTERP_FLAG_LOOP		0x08
#define SCLI_INTERP_FLAG_XML		0x10
#define SCLI_INTERP_FLAG_DRY		0x20

struct scli_interp {
    GNode *cmd_root;		/* root of the command tree */
    GSList *mode_list;		/* list of registered modes */
    GSList *alias_list;		/* list of command aliases */
    GSList *alarm_list;		/* list of detected alarms */
    int	flags;			/* interpreter flags */
    GString *result;		/* string result buffer */
    GString *header;		/* header line to display */
    xmlDocPtr xml_doc;		/* xml document if we produce xml output */
    xmlNodePtr xml_node;	/* current xml node in the xml document */
    char *pager;		/* external pager we are using */
    GSnmpSession *peer;		/* snmp peer we are talking to */
    gint delay;			/* delay between updates in milliseconds */
    int port;			/* default port number, defaults to 161 */
    time_t epoch;		/* epoch (used to invalidate cached data) */
    int xid;			/* transaction identifier for each transaction */
    int regex_flags;		/* regular expression flags (see regcomp(3)) */
};

extern scli_interp_t *
scli_interp_create(void);

extern void
scli_interp_delete(scli_interp_t *interp);

extern void
scli_interp_reset(scli_interp_t *interp);

#define scli_interp_interactive(interp) \
	(interp->flags & SCLI_INTERP_FLAG_INTERACTIVE)
#define scli_interp_recursive(interp) \
	(interp->flags & SCLI_INTERP_FLAG_RECURSIVE)
#define scli_interp_xml(interp) \
	(interp->flags & SCLI_INTERP_FLAG_XML)
#define scli_interp_monitor(interp) \
	(interp->flags & SCLI_INTERP_FLAG_MONITOR)
#define scli_interp_dry(interp) \
	(interp->flags & SCLI_INTERP_FLAG_DRY)

extern scli_alarm_t *
scli_alarm_create(scli_interp_t *interp, char *desc);

extern void
scli_alarm_delete(scli_interp_t *interp, scli_alarm_t *alarm);

extern int
scli_split(char *string, int *argc, char ***argv);

extern int
scli_monitor(scli_interp_t *interp, scli_cmd_t *cmd, int argc, char **argv);

extern int
scli_loop(scli_interp_t *interp, scli_cmd_t *cmd, int argc, char **argv);

extern int
scli_eval_cmd(scli_interp_t *interp, scli_cmd_t *cmd, int argc, char **argv);

extern int
scli_eval_argc_argv(scli_interp_t *interp, int argc, char **argv);

extern int
scli_eval_string(scli_interp_t *interp, char *s);

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
scli_curses_on(void);

extern void
scli_curses_off(void);

extern int
scli_set_pager(scli_interp_t *interp, const char *pager);

extern void
scli_snmp_error(scli_interp_t *interp);

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
scli_init_isdn_mode(scli_interp_t *interp);

extern void
scli_init_rs232_mode(scli_interp_t *interp);

extern void
scli_init_cisco_mode(scli_interp_t *interp);

extern void
scli_init_nortel_mode(scli_interp_t *interp);

extern void
scli_init_netsnmp_mode(scli_interp_t *interp);

/* 
 * A data structure used to obtain vendor information from the
 * enterprise OID. See the file vendors.c for details.
 */
 
typedef struct scli_vendor {
    guint32  id;
    char     *name;
    char     *url;
} scli_vendor_t;

extern const scli_vendor_t*
scli_get_vendor(guint32 enterp);

extern const scli_vendor_t*
scli_get_vendor_oid(guint32 oid[], gsize len);

extern const scli_vendor_t*
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
fmt_udp_port(unsigned short int port, int flags);

extern char*
fmt_tcp_port(unsigned short int port, int flags);

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

extern const char*
fmt_tdomain(guint32 *tdomain, gsize tdomain_len);

extern const char*
fmt_taddress(guint32 *tdomain, gsize tdomain_len,
	     guchar *taddress, gsize taddress_len);
    
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

