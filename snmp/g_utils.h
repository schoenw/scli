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

gint32
gsnmp_enum_get_number(GSnmpEnum const *table, gchar const *str);

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

#endif
