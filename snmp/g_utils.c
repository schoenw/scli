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
 * Foundation, Inc.,  59 Temple Place - Suite 330, Cambridge, MA 02139, USA.
 *
 * $Id$
 */

#include "g_snmp.h"


GSnmpEnum const gsnmp_enum_version_table[] = {
    { G_SNMP_V1,	"SNMPv1" },
    { G_SNMP_V2C,	"SNMPv2c" },
    { G_SNMP_V3,	"SNMPv3" },
    { 0, 0 }
};



GSnmpEnum const gsnmp_error_status_table[] = {
    { 0, "noError" },
    { 1, "tooBig" },
    { 2, "noSuchName"},
    { 3, "badValue" },
    { 4, "readOnly" },
    { 5, "genErr" },
    { 6, "noAccess" },
    { 7, "wrongType" },
    { 8, "wrongLength" },
    { 9, "wrongEncoding" },
    { 10, "wrongValue" },
    { 11, "noCreation" },
    { 12, "inconsistentValue" },
    { 13, "resourceUnavailable" },
    { 14, "commitFailed" },
    { 15, "undoFailed" },
    { 16, "authorizationError" },
    { 17, "notWritable" },
    { 18, "inconsistentName" },
    { 0, 0 }
};



GSnmpEnum const gsnmp_enum_debug_table[] = {
    { G_SNMP_DEBUG_REQUESTS,	"request" },
    { G_SNMP_DEBUG_SESSION,	"session" },
    { G_SNMP_DEBUG_TRANSPORT,	"transport" },
    { 0, 0 }
};



char const *
gsnmp_enum_get_label(GSnmpEnum const *table, gint32 const id)
{
    int i;

    for (i = 0; table[i].label; i++) {
	if (id == table[i].number) {
	    return table[i].label;
	}
    }

    return NULL;
}



int
gsnmp_enum_get_number(GSnmpEnum const *table, char const *str, gint32 *number)
{
    int i;

    for (i = 0; table[i].label; i++) {
	if (strcmp(str, table[i].label) == 0) {
	    if (number) *number = table[i].number;
	    return TRUE;
	}
    }

    return FALSE;
}



char const *
gsnmp_identity_get_label(GSnmpIdentity const *table,
			 guint32 const *oid, gsize oidlen)
{
    int i;

    if (! oid || oidlen <= 0) {
	return NULL;
    }

    for (i = 0; table[i].label; i++) {
	if (table[i].oidlen == oidlen
	    && memcmp(table[i].oid, oid, oidlen * sizeof(guint32)) == 0) {
	    return table[i].label;
	}
    }

    return NULL;
}
