/*
 * GSNMP -- glib-based SNMP implementation
 *
 * Copyright (C) 2001 Juergen Schoenwaelder
 * Copyright (C) 1998 Gregory McLean & Jochen Friedrich
 * Copyright (C) 1993 DNPAP Beholder Group
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id$
 */

#ifndef _GSNMP_UTILS_H_
#define _GSNMP_UTILS_H_

#include "g_snmp.h"

/*
 * The following types and the associated functions are used to
 * map enumerated numbers to labels and vice versa.
 */

typedef struct _GSnmpEnum	GSnmpEnum;
typedef struct _GSnmpIdentity	GSnmpIdentity;

struct _GSnmpEnum {
    gint32 const number;
    gchar  const *label;
};

gchar const *
gsnmp_enum_get_label(GSnmpEnum const *table, gint32 const id);

int
gsnmp_enum_get_number(GSnmpEnum const *table, gchar const *str,
		      gint32 *number);

struct _GSnmpIdentity {
    guint32 const *oid;
    gsize const oidlen;
    gchar const *label;
};

gchar const *
gsnmp_identity_get_label(GSnmpIdentity const *table,
			 guint32 const *oid, gsize oidlen);
guint32 *
gsnmp_identity_get_identity(GSnmpIdentity const *table,
			    gchar const *str, gsize *oidlen);

/*
 * SNMP specific enumerations
 */

extern GSnmpEnum const gsnmp_enum_version_table[];
extern GSnmpEnum const gsnmp_enum_error_table[];
extern GSnmpEnum const gsnmp_enum_debug_table[];
extern GSnmpEnum const gsnmp_enum_tdomain_table[];
extern GSnmpEnum const gsnmp_enum_type_table[];
extern GSnmpEnum const gsnmp_enum_pdu_table[];

/*
 * The following utilities are used by the scli stubs generated by the
 * smidump MIB compiler.
 */

typedef enum
{
    GSNMP_ATTR_FLAG_WRITABLE	= 1 << 0,
    GSNMP_ATTR_FLAG_MASK	= 0x01
} GSnmpAttrFlags;

typedef struct {
    const guint32	    subid;	/* column/scalar subid */
    const GSnmpVarBindType  type;	/* SNMP type of the value */
    const gint              tag;	/* internal identification tag */
    const gchar            *label;	/* label (used for error reports) */
    const gpointer	    constraints;/* range or size contraints */
    const gint              val_offset;	/* offset for the value pointer */
    const gint		    len_offset;	/* offset for the length pointer */
    const GSnmpAttrFlags    flags;	/* various flags, see above */
} GSnmpAttribute;

extern int gsnmp_attr_assign(GSList *vbl,
			     guint32 const *base, size_t const len,
			     const GSnmpAttribute *attributes,
			     const gpointer p);

extern void gsnmp_attr_get(const GSnmpSession *s, GSList **vbl,
			   guint32 *base, size_t const len, guint const idx,
			   const GSnmpAttribute *attributes, const gint mask);

extern void gsnmp_attr_set(const GSnmpSession *s, GSList **vbl,
			   guint32 *base, size_t len, guint const idx,
			   const GSnmpAttribute *attributes, const gint mask,
			   const gpointer p);

#endif
