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
    gint32 const number;
    gchar  const *label;
} stls_enum_t;

gchar const *
stls_enum_get_label(stls_enum_t const *table, gint32 const id);

gint32
stls_enum_get_number(stls_enum_t const *table, gchar const *str);

typedef struct {
    guint32 const *oid;
    gsize const oidlen;
    gchar const *label;
} stls_identity_t;

gchar const *
stls_identity_get_label(stls_identity_t const *table,
			guint32 const *oid, gsize oidlen);
guint32 *
stls_identity_get_identity(stls_identity_t const *table,
			   gchar const *str, gsize *oidlen);

/*
 * SNMP toolkit independent functions to create and free varbind lists.
 */

typedef struct {
    guint32 const	subid;
    GSnmpVarBindType	type;
    gchar		*label;
} stls_stub_attr_t;

typedef struct {
    guint32 const	*base;
    gsize		size;
    stls_stub_attr_t	*attributes;
} stls_stut_obj_t;

extern void
stls_vbl_add_null(GSList **vbl, guint32 const *oid, gsize const len);

extern void
stls_vbl_free(GSList *vbl);

extern void
stls_vbl_attributes(host_snmp *s, GSList **vbl, guint32 *base, guint idx,
		    stls_stub_attr_t *attributes);

extern int
stls_vb_lookup(GSnmpVarBind *vb, guint32 const *base, gsize const base_len,
	       stls_stub_attr_t *attributes, guint32 *idx);

/*
 * SNMP toolkit independent API functions used by the stub code.
 */

extern GSList *
stls_snmp_getnext(host_snmp *s, GSList *vbl);

extern GSList *
stls_snmp_gettable(host_snmp *s, GSList *vbl);

/*
 * Some generic conversion functions that we need in several tools.
 */

extern const char *
stls_fmt_timeticks(guint32 timeticks);


#endif

