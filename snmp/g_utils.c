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



int
gsnmp_attr_assign(GSList *vbl,
		  guint32 const *base, guint8 const len,
		  const GSnmpAttribute *attributes, const gpointer p)
{
    GSList *elem;
    int i, n = 0;
    gpointer **gp;

    if (!p) {
	return 0;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
	 GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

	 if (vb->type == G_SNMP_ENDOFMIBVIEW
	     || (vb->type == G_SNMP_NOSUCHOBJECT)
	     || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
	      continue;
	 }
    
	 if (memcmp(vb->id, base, len * sizeof(guint32)) != 0) {
	      continue;
	 }

	 for (i = 0; attributes[i].label; i++) {
	      if (vb->id_len > len && vb->id[len] == attributes[i].subid) {
		   break;
	      }
	 }

	 if (! attributes[i].label) {
	      continue;
	 }
    
	 if (vb->type != attributes[i].type) {
	      const char *a = gsnmp_enum_get_label(gsnmp_enum_type_table, vb->type);
	      const char *b = gsnmp_enum_get_label(gsnmp_enum_type_table, attributes[i].type);
	      g_warning("%s: type mismatch: %s%s%s", attributes[i].label,
			(a) ? a : "", (a || b) ? " != " : "", (b) ? b : "");
	      continue;
	 }

	 gp = G_STRUCT_MEMBER_P(p, attributes[i].val_offset);
	 switch (vb->type) {
	 case G_SNMP_INTEGER32:
	     if (attributes[i].constraints) {
		 gint32 *range = (gint32 *) attributes[i].constraints;
		 while (range[0] != 0 || range[1] != 0) {
		     if (vb->syntax.i32[0] < range[0]
			 || vb->syntax.i32[0] > range[1]) {
			 g_warning("%s: value not within range contraints",
				   attributes[i].label);
			 gp = NULL;
		     }
		     range += 2;
		 }
	     }
	     if (gp) *gp = (gpointer) &(vb->syntax.i32[0]);
	     break;
	 case G_SNMP_UNSIGNED32:
	 case G_SNMP_COUNTER32:
	 case G_SNMP_TIMETICKS:
	     if (attributes[i].constraints) {
		 guint32 *range = (guint32 *) attributes[i].constraints;
		 while (range[0] != 0 || range[1] != 0) {
		     if (vb->syntax.i32[0] < range[0]
			 || vb->syntax.i32[0] > range[1]) {
			 g_warning("%s: value not within range contraints",
				   attributes[i].label);
			 gp = NULL;
		     }
		     range += 2;
		 }
	     }
	     if (gp) *gp = (gpointer) &(vb->syntax.ui32[0]);
	     break;
	 case G_SNMP_OCTETSTRING:
	     if (attributes[i].constraints) {
		 guint16 *size = (guint16 *) attributes[i].constraints;
		 while (size[0] != 0 || size[1] != 0) {
		     if (vb->syntax_len < size[0]
			 || vb->syntax_len > size[1]) {
			 g_warning("%s: value not within size contraints",
				   attributes[i].label);
			 gp = NULL;
		     }
		     size += 2;
		 }
	     }
	     if (gp) *gp = (gpointer) vb->syntax.uc;
	     break;
	 case G_SNMP_OBJECTID:
	     *gp = (gpointer) vb->syntax.ui32;
	     break;
	 default:
	     break;
	 }
	 if (attributes[i].len_offset) {
	     guint16 *lp;
	     lp = (guint16 *) G_STRUCT_MEMBER_P(p, attributes[i].len_offset);
	     *lp = vb->syntax_len;
	 }
	 n++;
    }

    return n;
}



void
gsnmp_attr_get(const GSnmpSession *s, GSList **vbl,
	       guint32 *base, guint8 const len, guint const idx,
	       const GSnmpAttribute *attributes, const gint mask)
{
    int i;
    
    for (i = 0; attributes[i].label; i++) {
	 if (! mask || (mask & attributes[i].tag)) {
	      if (attributes[i].type != G_SNMP_COUNTER64
		  || s->version > G_SNMP_V1) {
		   base[idx] = attributes[i].subid;
		   g_snmp_vbl_add_null(vbl, base, len);
	      }
	 }
    }
}



void
gsnmp_attr_set(const GSnmpSession *s, GSList **vbl,
	       guint32 *base, guint8 const len, guint const idx,
	       const GSnmpAttribute *attributes, const gint mask,
	       const gpointer p)
{
    int i;
    gpointer **gp;
    guint16 *lp;

    if (!p) {
	return;
    }

    for (i = 0; attributes[i].label; i++) {
	if (mask && !(mask & attributes[i].tag)) {
	    continue;
	}
	if ((attributes[i].type == G_SNMP_COUNTER64 && s->version == G_SNMP_V1)) {
	    continue;
	}
	if (! (attributes[i].flags & GSNMP_ATTR_FLAG_WRITABLE)) {
	    continue;
	}
	gp = G_STRUCT_MEMBER_P(p, attributes[i].val_offset);
	if (attributes[i].len_offset) {
	    lp = (guint16 *) G_STRUCT_MEMBER_P(p, attributes[i].len_offset);
	} else {
	    lp = 0;
	}
	base[idx] = attributes[i].subid;
	g_snmp_vbl_add(vbl, base, len, attributes[i].type,
		       *gp, lp ? *lp : 0);
    }
}

