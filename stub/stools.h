/* 
 * stools.h -- library of MIB stub procedures
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

#ifndef _STOOLS_H
#define _STOOLS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

#include "g_snmp.h"


/*
 * The following structure and the associated functions are used to
 * map enumerated numbers to labels and vice versa. The tables are
 * usually generated automatically by the smidump compiler.
 */

typedef struct {
    gint32 id;
    gchar  *str;
} stls_table_t;

gchar * stls_table_get_value(stls_table_t const *table, gint32 const id);
gint32 stls_table_get_id(stls_table_t const *table, gchar const *str);


/*
 * SNMP toolkit independent functions to create and free varbind lists.
 */

extern void
stls_vbl_add_null(GSList **vbl, guint32 const *oid, gsize const len);

extern void
stls_vbl_free(GSList *vbl);


/*
 * SNMP toolkit independent API functions used by the stub code.
 */

extern GSList *
stls_snmp_getnext(host_snmp *s, GSList *vbl);

extern GSList *
stls_snmp_gettable(host_snmp *s, GSList *vbl);


/*
 * The MIB module stub headers that are part of the stools distribution.
 */

#include "if-mib.h"
#include "ip-mib.h"
#include "ip-forward-mib.h"
#include "tcp-mib.h"
#include "udp-mib.h"
#include "snmpv2-mib.h"
#include "host-resources-mib.h"
#include "entity-mib.h"
#include "bridge-mib.h"
#include "disman-script-mib.h"
#include "disman-schedule-mib.h"
#include "snmp-framework-mib.h"
#include "snmp-mpd-mib.h"
#include "snmp-user-based-sm-mib.h"
#include "snmp-community-mib.h"
#include "snmp-view-based-acm-mib.h"
#include "snmp-target-mib.h"
#include "tunnel-mib.h"

#endif

