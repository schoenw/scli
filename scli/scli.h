/* 
 * scli.h -- emulate a command line interface via SNMP
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

#ifndef _SCLI_H
#define _SCLI_H

#include <stdlib.h>
#include <stdio.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include <time.h>

#include "stools.h"


extern char const scli_copyright[];


#define SCLI_OK		0
#define SCLI_ERROR	1
#define SCLI_EXIT	2


typedef struct scli_interp	scli_interp_t;
typedef struct scli_mode	scli_mode_t;
typedef struct scli_cmd		scli_cmd_t;


#define SCLI_CMD_FLAG_NEED_PEER	0x01

struct scli_cmd {
    char *path;			/* path where the command is registered */
    int   flags;		/* command flags */
    char *desc;			/* description of the command */
    int (*func) (scli_interp_t *interp, int argc, char **argv);
				/* function to implement the command */
    char *name;			/* name of the command (last elem of path) */
};

struct scli_mode {
    char *name;			/* name of the mode */
    char *desc;			/* description of the mode */
    scli_cmd_t *cmds;		/* array of command provided by the mode */
};

#define SCLI_INTERP_FLAG_INTERACTIVE	0x01
#define SCLI_INTERP_FLAG_RECURSIVE	0x02

struct scli_interp {
    GNode *cmd_root;		/* root of the command tree */
    GSList *mode_list;		/* root of list of registered modes */
    int	flags;			/* interpreter flags */
    GString *result;		/* string result buffer */
    host_snmp *peer;		/* the snmp peer we are talking to */
};

extern scli_interp_t *
scli_interp_create();

extern void
scli_interp_delete();

extern int
scli_split(char *string, int *argc, char ***argv);

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

/*
 * Core scli commands:
 */

extern int
scli_cmd_help(scli_interp_t *interp, int argc, char **argv);

extern int
scli_cmd_history(scli_interp_t *interp, int argc, char **argv);

extern int
scli_cmd_exit(scli_interp_t *interp, int argc, char **argv);

extern int
scli_cmd_open(scli_interp_t *interp, int argc, char **argv);

extern int
scli_cmd_close(scli_interp_t *interp, int argc, char **argv);

/*
 * Initialization functions for the various scli modes.
 */

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

extern void
fmt_time_ticks(GString *s, guint32 timeticks);

extern void
fmt_date_and_time(GString *s, guchar *data, gsize len);

extern char const *
fmt_date_and_time_delta(guchar *date1, gsize len1, guchar *date2, gsize len2);

extern char const *
fmt_seconds(guint32 number);

extern void
fmt_kbytes(GString *s, guint32 kbytes);

extern void
fmt_enum(GString *s, int width, stls_enum_t const *table, gint32 *number);

extern char*
fmt_kmg(guint32 number);

extern char*
fmt_gtp(guint32 number);

extern char*
fmt_udp_port(int port, int name);

extern char*
fmt_tcp_port(int port, int name);

extern char*
fmt_ipv4_address(guchar *addr, int name);

extern char*
fmt_ipv4_mask(guchar *addr);


#endif /* _SCLI_H */

