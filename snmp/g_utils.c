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



GSnmpEnum const gsnmp_enum_error_table[] = {
    { G_SNMP_ERR_PROCEDURE,		"procedureError" },
    { G_SNMP_ERR_INTERNAL,		"internalError" },
    { G_SNMP_ERR_NORESPONSE,		"noResponse" },
    { G_SNMP_ERR_NOERROR,		"noError" },
    { G_SNMP_ERR_TOOBIG,		"tooBig" },
    { G_SNMP_ERR_NOSUCHNAME,		"noSuchName"},
    { G_SNMP_ERR_BADVALUE,		"badValue" },
    { G_SNMP_ERR_READONLY,		"readOnly" },
    { G_SNMP_ERR_GENERROR,		"genErr" },
    { G_SNMP_ERR_NOACCESS,		"noAccess" },
    { G_SNMP_ERR_WRONGTYPE,		"wrongType" },
    { G_SNMP_ERR_WRONGLENGTH,		"wrongLength" },
    { G_SNMP_ERR_WRONGENCODING,		"wrongEncoding" },
    { G_SNMP_ERR_WRONGVALUE,		"wrongValue" },
    { G_SNMP_ERR_NOCREATION,		"noCreation" },
    { G_SNMP_ERR_INCONSISTENTVALUE,	"inconsistentValue" },
    { G_SNMP_ERR_RESOURCEUNAVAILABLE,	"resourceUnavailable" },
    { G_SNMP_ERR_COMMITFAILED,		"commitFailed" },
    { G_SNMP_ERR_UNDOFAILED,		"undoFailed" },
    { G_SNMP_ERR_AUTHORIZATIONERROR,	"authorizationError" },
    { G_SNMP_ERR_NOTWRITABLE,		"notWritable" },
    { G_SNMP_ERR_INCONSISTENTNAME,	"inconsistentName" },
    { 0, 0 }
};



GSnmpEnum const gsnmp_enum_type_table[] = {
    { G_SNMP_NULL,		"NULL" },
    { G_SNMP_OCTETSTRING,	"OCTET STRING" },
    { G_SNMP_OBJECTID,		"OBJECT IDENTIFIER" },
    { G_SNMP_IPADDRESS,		"IpAddress" },
    { G_SNMP_INTEGER32,		"Integer32" },
    { G_SNMP_UNSIGNED32,	"Unsigned32" },
    { G_SNMP_COUNTER32,		"Counter32" },
    { G_SNMP_TIMETICKS,		"TimeTicks" },
    { G_SNMP_OPAQUE,		"Opaque" },
    { G_SNMP_COUNTER64,		"Counter64" },
    { G_SNMP_NOSUCHOBJECT,	"NoSuchObject" },
    { G_SNMP_NOSUCHINSTANCE,	"NoSuchInstance" },
    { G_SNMP_ENDOFMIBVIEW,	"EndOfMibView" },
    { 0, 0 }
};



GSnmpEnum const gsnmp_enum_pdu_table[] = {
    { G_SNMP_PDU_GET,		"get" },
    { G_SNMP_PDU_NEXT,		"get-next" },
    { G_SNMP_PDU_RESPONSE,	"response" },
    { G_SNMP_PDU_SET,		"set" },
    { G_SNMP_PDU_TRAP1,		"trap1" },
    { G_SNMP_PDU_BULK,		"get-bulk" },
    { G_SNMP_PDU_INFORM,	"inform" },
    { G_SNMP_PDU_TRAP2,		"trap2" },
    { 0, 0 }
};



GSnmpEnum const gsnmp_enum_debug_table[] = {
    { G_SNMP_DEBUG_REQUESTS,	"request" },
    { G_SNMP_DEBUG_SESSION,	"session" },
    { G_SNMP_DEBUG_TRANSPORT,	"transport" },
    { G_SNMP_DEBUG_PACKET,	"packet" },
    { G_SNMP_DEBUG_ASN1,	"asn1" },
    { 0, 0 }
};



GSnmpEnum const gsnmp_enum_tdomain_table[] = {
    { G_SNMP_TDOMAIN_NONE,	"none" },
    { G_SNMP_TDOMAIN_UDP_IPV4,	"udp/ipv4" },
    { G_SNMP_TDOMAIN_UDP_IPV6,	"udp/ipv6" },
    { G_SNMP_TDOMAIN_IPX,	"ipx" },
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
