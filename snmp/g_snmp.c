/*
 * GXSNMP -- An snmp mangament application
 * Copyright (C) 1998 Gregory McLean & Jochen Friedrich
 * Beholder RMON ethernet network monitor, Copyright (C) 1993 DNPAP group
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
 */

/*
 * MODULE INFORMATION 
 * ------------------ 
 *     FILE     NAME:       g_snmp.c
 *     SYSTEM   NAME:       SNMP Packet Module
 *     ORIGINAL AUTHOR(S):  Dirk Wisse
 *     VERSION  NUMBER:     1
 *     CREATION DATE:       1990/11/28
 *
 * DESCRIPTION: SNMP Packet Module
 *
 */

#include "g_snmp.h"

#include <stdio.h>

GSnmpDebugFlags g_snmp_debug_flags = 0;

void (*g_snmp_list_decode_hook)(GSList *list) = NULL;
void (*g_snmp_list_encode_hook)(GSList *list) = NULL;

/*prototypes*/
static gboolean g_snmp_syntax2tag_cls(guint *tag, guint *cls, gint syntax);
static gboolean g_snmp_tag_cls2syntax(guint tag, guint cls, gushort *syntax);
static gboolean g_snmp_object_encode(ASN1_SCK *asn1, GSnmpVarBind *object);
static gboolean g_snmp_object_decode(ASN1_SCK *asn1, GSnmpVarBind **object);
static gboolean g_snmp_list_encode(ASN1_SCK *asn1, GSList *list);
static gboolean g_snmp_list_decode(ASN1_SCK *asn1, GSList **list);
static gboolean g_snmp_request_encode(ASN1_SCK *asn1, GSnmpRequest *request);
static gboolean g_snmp_request_decode(ASN1_SCK *asn1, GSnmpRequest *request);
static gboolean g_snmp_trap_encode(ASN1_SCK *asn1, GSnmpV1Trap *trap);
static gboolean g_snmp_trap_decode(ASN1_SCK *asn1, GSnmpV1Trap *trap);

#define SNMP_IPA    0
#define SNMP_CNT    1
#define SNMP_GGE    2
#define SNMP_TIT    3
#define SNMP_OPQ    4
#define SNMP_C64    6

#define SERR_NSO    0
#define SERR_NSI    1
#define SERR_EOM    2

static GSnmpError g_snmpErrStatus = G_SNMP_ERR_NOERROR;

typedef struct _SNMP_CNV SNMP_CNV;

struct _SNMP_CNV
{
  guint class;
  guint tag;
  gint  syntax;
};

const char *SnmpTrap[] =
{
  "cold start",
  "warm start",
  "link down",
  "link up",
  "authentication failure",
  "neighbor loss",
  "enterprise specific"
};

static SNMP_CNV SnmpCnv [] =
{
  {ASN1_UNI, ASN1_NUL, G_SNMP_NULL},
  {ASN1_UNI, ASN1_INT, G_SNMP_INTEGER32},
  {ASN1_UNI, ASN1_OTS, G_SNMP_OCTET_STRING},
  {ASN1_UNI, ASN1_OJI, G_SNMP_OBJECT_ID},
  {ASN1_APL, SNMP_IPA, G_SNMP_IPADDRESS},
  {ASN1_APL, SNMP_CNT, G_SNMP_COUNTER32},         /* Counter32 */
  {ASN1_APL, SNMP_GGE, G_SNMP_UNSIGNED32},        /* Gauge32 == Unsigned32  */
  {ASN1_APL, SNMP_TIT, G_SNMP_TIMETICKS},
  {ASN1_APL, SNMP_OPQ, G_SNMP_OPAQUE},

/* SNMPv2 data types and errors */

  {ASN1_APL, SNMP_C64, G_SNMP_COUNTER64},
  {ASN1_CTX, SERR_NSO, G_SNMP_NOSUCHOBJECT},
  {ASN1_CTX, SERR_NSI, G_SNMP_NOSUCHINSTANCE},
  {ASN1_CTX, SERR_EOM, G_SNMP_ENDOFMIBVIEW},
  {0,       0,       -1}
};

/*
 * NAME:        g_snmp_syntax2tag_cls
 * SYNOPSIS:    gboolean g_snmp_syntax2tag_cls
 *                  (
 *                      guint   *tag,
 *                      guint   *cls,
 *                      gint     syntax
 *                  )
 * DESCRIPTION: Converts Syntax tag to ASN1 tag and class.
 *              See SnmpCnv for conversion.
 * RETURNS:     gboolean success.
 */

static gboolean  
g_snmp_syntax2tag_cls ( guint *tag, guint *cls, gint syntax)
{
    SNMP_CNV *cnv;

    cnv = SnmpCnv;
    while (cnv->syntax != -1)
    {
        if (cnv->syntax == syntax)
        {
            *tag = cnv->tag;
            *cls = cnv->class;
            return TRUE;
        }
        cnv++;
    }
    g_snmpErrStatus = G_SNMP_ERR_BADVALUE;
    return FALSE;
}

/*
 * NAME:        g_snmp_tag_cls2syntax
 * SYNOPSIS:    gboolean g_snmp_tag_cls2syntax
 *                  (
 *                      guint    tag,
 *                      guint    cls,
 *                      gushort *syntax
 *                  )
 * DESCRIPTION: Converts ASN1 tag and class to Syntax tag.
 *              See SnmpCnv for conversion.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_tag_cls2syntax ( guint tag, guint cls, gushort *syntax)
{
    SNMP_CNV *cnv;

    cnv = SnmpCnv;
    while (cnv->syntax != -1)
    {
        if (cnv->tag == tag && cnv->class == cls)
        {
            *syntax = cnv->syntax;
            return TRUE;
        }
        cnv++;
    }
    g_snmpErrStatus = G_SNMP_ERR_BADVALUE;
    return FALSE;
}

/*
 * NAME:        g_snmp_varbind_new
 * SYNOPSIS:    void g_snmp_varbind_new
 *                  (
 *                      guint32 const   *oid,
 *			gsize            oid_len,
 *			GSnmpVarBindType type,
 *			gpointer         value,
 *			gsize            value_len
 *                  )
 * DESCRIPTION: Allocates and initializes a new GSnmpVarBind.
 * RETURNS:     GSnmpVarBind
 */

GSnmpVarBind *
g_snmp_varbind_new(guint32 const *oid, gsize oid_len, GSnmpVarBindType type,
		   gpointer value, gsize value_len)
{
    GSnmpVarBind *obj = NULL;
    gsize len = 0;

    switch (type) 
    {
      case G_SNMP_NULL:
      case G_SNMP_NOSUCHOBJECT:
      case G_SNMP_NOSUCHINSTANCE:
      case G_SNMP_ENDOFMIBVIEW:
	obj = g_malloc(sizeof(GSnmpVarBind));
        break;
      case G_SNMP_INTEGER32:
        obj = g_malloc(sizeof(GSnmpVarBind));
        obj->syntax.i32[0] = *((gint32 *) value);
        break;
      case G_SNMP_COUNTER32:
      case G_SNMP_UNSIGNED32:
      case G_SNMP_TIMETICKS:
        obj = g_malloc(sizeof(GSnmpVarBind));
        obj->syntax.ui32[0] = *((guint32 *) value);
        break;
      case G_SNMP_COUNTER64:
	obj = g_malloc(sizeof(GSnmpVarBind));
	obj->syntax.ui64[0] = *((guint64 *) value);
	break;
      case G_SNMP_OCTET_STRING:
      case G_SNMP_IPADDRESS:
      case G_SNMP_OPAQUE:
        len = value_len;
        obj = g_malloc(sizeof(GSnmpVarBind) + len);
        memcpy(obj->syntax.uc, value, len);
        break;
      case G_SNMP_OBJECT_ID:
	len = value_len;
	len *= sizeof(guint32);
        obj = g_malloc(sizeof(GSnmpVarBind) + len);
	memcpy(obj->syntax.ui32, value, len);
	break;
      default:
        return NULL;
    }

    obj->syntax_len = len;
    obj->id_len     = oid_len;
    obj->type       = type;
    obj->id         = g_malloc(oid_len * sizeof(guint32));
    
    g_memmove(obj->id, oid, oid_len * sizeof(guint32));

    return obj;
}

/*
 * NAME:        g_snmp_varbind_free
 * SYNOPSIS:    void g_snmp_varbind_free
 *                  (
 *                      GSnmpVarBind *vb
 *                  )
 * DESCRIPTION: Frees all memory associated with a varbind.
 * RETURNS:     none
 */

void
g_snmp_varbind_free(GSnmpVarBind *vb)
{
    if (vb) {
	g_free(vb->id);
	g_free(vb);
    }
}

/*
 * NAME:        g_snmp_vbl_add
 * SYNOPSIS:    void g_snmp_vbl_add
 *                  (
 *                      GSnmpVarBind *vb,
 *			guint32 const *oid,
 *			gsize const len,
 *			GSnmpVarBindType const type,
 *			gpointer const value,
 *			gsize const len
 *                  )
 * DESCRIPTION: Adds a NULL PDU to a varbind list.
 * RETURNS:     none
 */

void
g_snmp_vbl_add(GSList **vbl, guint32 const *oid, gsize const len,
	       GSnmpVarBindType const type,
	       gpointer const value, gsize const value_len)
{
    GSnmpVarBind *vb;

    vb = g_snmp_varbind_new(oid, len, type, value, value_len);
    if (vb) {
	*vbl = g_slist_append(*vbl, vb);
    }
}

/*
 * NAME:        g_snmp_vbl_add_null
 * SYNOPSIS:    void g_snmp_vbl_add_null
 *                  (
 *                      GSnmpVarBind *vb,
 *			guint32 const *oid,
 *			gsize const len
 *                  )
 * DESCRIPTION: Adds a NULL PDU to a varbind list.
 * RETURNS:     none
 */

void
g_snmp_vbl_add_null(GSList **vbl, guint32 const *oid, gsize const len)
{
    g_snmp_vbl_add(vbl, oid, len, G_SNMP_NULL, NULL, 0);
}

/*
 * NAME:        g_snmp_vbl_free
 * SYNOPSIS:    void g_snmp_vbl_free
 *                  (
 *                      GSnmpVarBind *vb
 *                  )
 * DESCRIPTION: Frees a complete varbind list.
 * RETURNS:     none
 */

void
g_snmp_vbl_free(GSList *vbl)
{
    GSList *elem;

    if (vbl) {
	for (elem = vbl; elem; elem = g_slist_next(elem)) {
	    g_snmp_varbind_free((GSnmpVarBind *) elem->data);
	}
	g_slist_free(vbl);
    }
}

/*
 * NAME:        g_snmp_object_encode
 * SYNOPSIS:    gboolean g_snmp_object_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_OBJECT  *obj,
 *                  )
 * DESCRIPTION: Encodes an object in ASN1.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_object_encode ( ASN1_SCK *asn1, GSnmpVarBind *obj)
{
    guint   cls, tag;
    guchar *eoc, *end;

    if (!g_asn1_eoc_encode (asn1, &eoc))
        return FALSE;
    switch (obj->type)
    {
        case G_SNMP_INTEGER32:
            if (!g_asn1_int32_encode (asn1, &end, obj->syntax.i32[0]))
                return FALSE;
            break;
        case G_SNMP_OCTET_STRING:
        case G_SNMP_OPAQUE:
            if (!g_asn1_octets_encode (asn1, &end, obj->syntax.uc, 
                                       obj->syntax_len))
                return FALSE;
            break;
        case G_SNMP_NULL:
	case G_SNMP_NOSUCHOBJECT:
	case G_SNMP_NOSUCHINSTANCE:
	case G_SNMP_ENDOFMIBVIEW:
            if (!g_asn1_null_encode (asn1, &end))
                return FALSE;
            break;
        case G_SNMP_OBJECT_ID:
            if (!g_asn1_oid_encode (asn1, &end, obj->syntax.ui32, 
                                    obj->syntax_len))
                return FALSE;
            break;
        case G_SNMP_IPADDRESS:
            if (!g_asn1_octets_encode (asn1, &end, obj->syntax.uc, 
                                       obj->syntax_len))
                return FALSE;
            break;
        case G_SNMP_COUNTER32:
        case G_SNMP_UNSIGNED32:
        case G_SNMP_TIMETICKS:
            if (!g_asn1_uint32_encode (asn1, &end, obj->syntax.ui32[0]))
                return FALSE;
            break;
        case G_SNMP_COUNTER64:
            if (!g_asn1_uint64_encode (asn1, &end, obj->syntax.ui64[0]))
                return FALSE;
	    break;
        default:
            g_snmpErrStatus = G_SNMP_ERR_BADVALUE;
            return FALSE;
    }
    if (!g_snmp_syntax2tag_cls (&tag, &cls, obj->type))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, cls, ASN1_PRI, tag))
        return FALSE;
    if (!g_asn1_oid_encode (asn1, &end, obj->id, obj->id_len))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_OJI))
        return FALSE;
    if (!g_asn1_header_encode (asn1, eoc, ASN1_UNI, ASN1_CON, ASN1_SEQ))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_object_decode
 * SYNOPSIS:    gboolean g_snmp_object_decode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_OBJECT  *obj,
 *                  )
 * DESCRIPTION: Decodes an object from ASN1.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_object_decode ( ASN1_SCK *asn1, GSnmpVarBind **obj)
{
  guint cls, con, tag, len, idlen;
  gushort type;
  guchar *eoc, *end, *p = NULL;
  guint32 *lp = NULL;
  guint32 *id;
  gint32 l;
  guint32 ul;
  guint64 ull;
  gpointer value = NULL;
  gsize value_len = 0;

  *obj = NULL;
  if (!g_asn1_header_decode (asn1, &eoc, &cls, &con, &tag))
    return FALSE;
  if (cls != ASN1_UNI || con != ASN1_CON || tag != ASN1_SEQ)
    return FALSE;
  if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
    return FALSE;
  if (cls != ASN1_UNI || con != ASN1_PRI || tag != ASN1_OJI)
    return FALSE;
  if (!g_asn1_oid_decode (asn1, end, &id, &idlen))
    return FALSE;
  if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
    {
      g_free(id);
      return FALSE;
    }
  if (con != ASN1_PRI)
    {
      g_snmpErrStatus = G_SNMP_ERR_BADVALUE;
      g_free(id);
      return FALSE;
    }
  if (!g_snmp_tag_cls2syntax (tag, cls, &type))
    {
      g_free(id);
      return FALSE;
    }
  switch (type)
    {
      case G_SNMP_INTEGER32:
        if (!g_asn1_int32_decode (asn1, end, &l))
          {
            g_free(id);
            return FALSE;
          }
	value = &l;
        break;
      case G_SNMP_OCTET_STRING:
      case G_SNMP_OPAQUE:
        if (!g_asn1_octets_decode (asn1, end, &p, &len))
          {
            g_free(id);
            return FALSE;
          }
	value = p;
	value_len = len;
        break;
      case G_SNMP_NULL:
      case G_SNMP_NOSUCHOBJECT:
      case G_SNMP_NOSUCHINSTANCE:
      case G_SNMP_ENDOFMIBVIEW:
        if (!g_asn1_null_decode (asn1, end))
          {
            g_free(id);
            return FALSE;
          }
        break;
      case G_SNMP_OBJECT_ID:
        if (!g_asn1_oid_decode (asn1, end, (guint32 **)&lp, &len))
          {
            g_free(id);
            return FALSE;
          }
	value = lp;
	value_len = len;
        break;
      case G_SNMP_IPADDRESS:
        if (!g_asn1_octets_decode (asn1, end, &p, &len))
          {
            g_free(id);
            return FALSE;
          }
        if (len != 4)
          {
            g_free(p);
            g_free(id);
            return FALSE;
          }
	value = p;
	value_len = len;
        break;
      case G_SNMP_COUNTER32:
      case G_SNMP_UNSIGNED32:
      case G_SNMP_TIMETICKS:
        if (!g_asn1_uint32_decode (asn1, end, &ul))
          {
            g_free(id);
            return FALSE;
          }
	value = &ul;
        break;
      case G_SNMP_COUNTER64:
	if (!g_asn1_uint64_decode (asn1, end, &ull))
	  {
	    g_free(id);
	    return FALSE;
	  }
	value = &ull;
        break;
      default:
        g_snmpErrStatus = G_SNMP_ERR_BADVALUE;
        g_free(id);
        return FALSE;
    }

  *obj = g_snmp_varbind_new(id, idlen, type, value, value_len);

  g_free(id);
  if (p) g_free(p);
  if (lp) g_free(lp);
  
  if (!g_asn1_eoc_decode (asn1, eoc))
    {
      g_snmp_varbind_free(*obj);
      *obj = NULL;
      return FALSE;
    }

  return TRUE;
}

/*
 * NAME:        g_snmp_list_encode
 * SYNOPSIS:    gboolean g_snmp_list_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      GSList       *list,
 *                  )
 * DESCRIPTION: Encodes a list of objects in ASN1.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_list_encode ( ASN1_SCK *asn1, GSList *list)
{
    guchar *eoc;
    GSList *elem;

    if (!g_asn1_eoc_encode (asn1, &eoc))
        return FALSE;

    /* Reverse list as we do backwards encoding here */

    list = g_slist_reverse(list);
    for (elem = list; elem; elem = g_slist_next(elem)) {
        if (!g_snmp_object_encode (asn1, elem->data))
            break;
    }
    list = g_slist_reverse(list);
    if (elem)
	return FALSE;
    if (!g_asn1_header_encode (asn1, eoc, ASN1_UNI, ASN1_CON, ASN1_SEQ))
        return FALSE;

    if (g_snmp_list_encode_hook) {
	g_snmp_list_encode_hook(list);
    }
    return TRUE;
}

/*
 * NAME:        g_snmp_list_decode
 * SYNOPSIS:    gboolean g_snmp_list_decode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      GSList      **list,
 *                      unsigned     LstSze,
 *                      unsigned     *LstLen
 *                  )
 * DESCRIPTION: Decodes a list of objects from ASN1.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_list_decode (ASN1_SCK *asn1, GSList **list)
{
    guint cls, con, tag;
    guchar *eoc;
    GSnmpVarBind *obj;

    *list = NULL;
    if (!g_asn1_header_decode (asn1, &eoc, &cls, &con, &tag))
        return FALSE;
    if (cls != ASN1_UNI || con != ASN1_CON || tag != ASN1_SEQ)
        return FALSE;
    while (!g_asn1_eoc_decode (asn1, eoc))
    {
        if (!g_snmp_object_decode (asn1, &obj))
	{
	    g_snmp_vbl_free(*list);
	    *list = NULL;
            return FALSE;
	}
	*list = g_slist_append(*list, obj);
    }
    if (!g_asn1_eoc_decode (asn1, eoc))
    {
	g_snmp_vbl_free(*list);
	*list = NULL;
        return FALSE;
    }
    if (g_snmp_list_decode_hook) {
	g_snmp_list_decode_hook(*list);
    }
    return TRUE;
}

/*
 * NAME:        g_snmp_requests_encode
 * SYNOPSIS:    gboolean g_snmp_request_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_REQUEST *request
 *                  )
 * DESCRIPTION: Encodes a request or response PDU in ASN1.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_request_encode ( ASN1_SCK *asn1, GSnmpRequest *request)
{
    guchar *end;

    if (!g_asn1_uint32_encode (asn1, &end, request->error_index))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_INT))
        return FALSE;
    if (!g_asn1_uint32_encode (asn1, &end, request->error_status))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_INT))
        return FALSE;
    if (!g_asn1_uint32_encode (asn1, &end, request->id))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_INT))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_request_decode
 * SYNOPSIS:    gboolean g_snmp_request_decode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_REQUEST *request
 *                  )
 * DESCRIPTION: Decodes a request or response PDU from ASN1.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_request_decode ( ASN1_SCK *asn1, GSnmpRequest *request)
{
    guint cls, con, tag;
    guchar *end;

    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (cls != ASN1_UNI || con != ASN1_PRI || tag != ASN1_INT)
        return FALSE;
    if (!g_asn1_uint32_decode (asn1, end, (guint32 *) &request->id))
        return FALSE;
    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (cls != ASN1_UNI || con != ASN1_PRI || tag != ASN1_INT)
        return FALSE;
    if (!g_asn1_uint32_decode (asn1, end, (guint32 *) &request->error_status))
        return FALSE;
    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (cls != ASN1_UNI || con != ASN1_PRI || tag != ASN1_INT)
        return FALSE;
    if (!g_asn1_uint32_decode (asn1, end, &request->error_index))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_trap_encode
 * SYNOPSIS:    gboolean g_snmp_trap_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      GSnmpV1Trap  *trap
 *                  )
 * DESCRIPTION: Encodes a trap PDU in ASN1.
 * RETURNS:     gboolean success.
 */
static gboolean 
g_snmp_trap_encode ( ASN1_SCK *asn1, GSnmpV1Trap *trap)
{
    guchar *end;

    if (!g_asn1_uint32_encode (asn1, &end, trap->time))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_APL, ASN1_PRI, SNMP_TIT))
        return FALSE;
    if (!g_asn1_uint32_encode (asn1, &end, trap->specific))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_INT))
        return FALSE;
    if (!g_asn1_uint32_encode (asn1, &end, trap->general))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_INT))
        return FALSE;
    if (!g_asn1_octets_encode (asn1, &end, (guchar *)&(trap->ip_address), 4))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_APL, ASN1_PRI, SNMP_IPA))
        return FALSE;
    if (!g_asn1_oid_encode (asn1, &end, trap->id, trap->id_len))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_OJI))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_trap_decode
 * SYNOPSIS:    gboolean g_snmp_trap_decode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      GSnmpV1Trap  *trap
 *                  )
 * DESCRIPTION: Decodes a trap PDU from ASN1.
 * RETURNS:     gboolean success.
 */

static gboolean 
g_snmp_trap_decode ( ASN1_SCK *asn1, GSnmpV1Trap *trap)
{
    guint cls, con, tag, len;
    guchar *end;

    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (cls != ASN1_UNI || con != ASN1_PRI || tag != ASN1_OJI)
        return FALSE;
    if (!g_asn1_oid_decode (asn1, end, &trap->id, &trap->id_len))
        return FALSE;
    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (!((cls == ASN1_APL && con == ASN1_PRI && tag == SNMP_IPA) ||
		(cls == ASN1_UNI && con == ASN1_PRI && tag == ASN1_OTS)))	/* needed for Banyan */
        return FALSE;
    if (!g_asn1_octets_decode (asn1, end, (guchar **)&trap->ip_address, &len))
        return FALSE;
    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (cls != ASN1_UNI || con != ASN1_PRI || tag != ASN1_INT)
        return FALSE;
    if (!g_asn1_uint32_decode (asn1, end, &trap->general))
        return FALSE;
    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (cls != ASN1_UNI || con != ASN1_PRI || tag != ASN1_INT)
        return FALSE;
    if (!g_asn1_uint32_decode (asn1, end, &trap->specific))
        return FALSE;
    if (!g_asn1_header_decode (asn1, &end, &cls, &con, &tag))
        return FALSE;
    if (!((cls == ASN1_APL && con == ASN1_PRI && tag == SNMP_TIT) ||
		(cls == ASN1_UNI && con == ASN1_PRI && tag == ASN1_INT)))
        return FALSE;
    if (!g_asn1_uint32_decode (asn1, end, &trap->time))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_pdu_v1_encode
 * SYNOPSIS:    gboolean g_snmp_pdu_v1_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_PDU     *pdu,
 *                  )
 * DESCRIPTION: Encodes a PDU in ASN1.
 *              Pdu is a union of snmp_ror and snmp_trp.
 * RETURNS:     gboolean success.
 */

gboolean 
g_snmp_pdu_v1_encode ( ASN1_SCK *asn1, GSnmpPdu *pdu)
{
    guchar *eoc;

    if (!g_asn1_eoc_encode (asn1, &eoc))
        return FALSE;
    switch (pdu->type)
    {
        case G_SNMP_PDU_GET:
        case G_SNMP_PDU_NEXT:
        case G_SNMP_PDU_RESPONSE:
        case G_SNMP_PDU_SET:
            if (!g_snmp_list_encode (asn1, pdu->request.variables))
                return FALSE;
            if (!g_snmp_request_encode (asn1, &pdu->request))
                return FALSE;
            break;
        case G_SNMP_PDU_TRAP1:
            if (!g_snmp_list_encode (asn1, pdu->trap.variables))
                return FALSE;
           if (!g_snmp_trap_encode (asn1, &pdu->trap))
                return FALSE;
            break;
        default:
            return FALSE;
    }
    if (!g_asn1_header_encode (asn1, eoc, ASN1_CTX, ASN1_CON, pdu->type))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_pdu_v2_encode
 * SYNOPSIS:    gboolean g_snmp_pdu_v2_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_PDU     *pdu,
 *                  )
 * DESCRIPTION: Encodes a PDU in ASN1.
 *              Pdu is a union of snmp_ror and snmp_trp.
 * RETURNS:     gboolean success.
 */

gboolean 
g_snmp_pdu_v2_encode ( ASN1_SCK *asn1, GSnmpPdu *pdu)
{
    guchar *eoc;

    if (!g_asn1_eoc_encode (asn1, &eoc))
        return FALSE;
    switch (pdu->type)
    {
        case G_SNMP_PDU_GET:
        case G_SNMP_PDU_NEXT:
        case G_SNMP_PDU_RESPONSE:
        case G_SNMP_PDU_SET:
	case G_SNMP_PDU_BULK:
	case G_SNMP_PDU_INFORM:
	case G_SNMP_PDU_TRAP2:
            if (!g_snmp_list_encode (asn1, pdu->request.variables))
                return FALSE;
            if (!g_snmp_request_encode (asn1, &pdu->request))
                return FALSE;
            break;
        default:
            return FALSE;
    }
    if (!g_asn1_header_encode (asn1, eoc, ASN1_CTX, ASN1_CON, pdu->type))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_pdu_v3_encode
 * SYNOPSIS:    gboolean g_snmp_pdu_v3_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_PDU     *pdu,
 *                  )
 * DESCRIPTION: Encodes a PDU in ASN1.
 *              Pdu is a union of snmp_ror and snmp_trp.
 * RETURNS:     gboolean success.
 */

gboolean 
g_snmp_pdu_v3_encode ( ASN1_SCK *asn1, GSnmpPdu *pdu, char *cenid, 
                       int cenidlen, char *cname, int cnamelen)
{
    guchar *eoc, *eoc1, *end;

    if (!g_asn1_eoc_encode (asn1, &eoc1))
        return FALSE;
    if (!g_asn1_eoc_encode (asn1, &eoc))
        return FALSE;
    switch (pdu->type)
    {
        case G_SNMP_PDU_GET:
        case G_SNMP_PDU_NEXT:
        case G_SNMP_PDU_RESPONSE:
        case G_SNMP_PDU_SET:
	case G_SNMP_PDU_BULK:
	case G_SNMP_PDU_INFORM:
	case G_SNMP_PDU_TRAP2:
            if (!g_snmp_list_encode (asn1, pdu->request.variables))
                return FALSE;
            if (!g_snmp_request_encode (asn1, &pdu->request))
                return FALSE;
            break;
        default:
            return FALSE;
    }

    if (!g_asn1_header_encode (asn1, eoc, ASN1_CTX, ASN1_CON, pdu->type))
        return FALSE;
    if (!g_asn1_octets_encode (asn1, &end, (guchar *) cname, cnamelen))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_OTS))
        return FALSE;
    if (!g_asn1_octets_encode (asn1, &end, (guchar *) cenid, cenidlen))
        return FALSE;
    if (!g_asn1_header_encode (asn1, end, ASN1_UNI, ASN1_PRI, ASN1_OTS))
        return FALSE;
    if (!g_asn1_header_encode (asn1, eoc1, ASN1_UNI, ASN1_CON, ASN1_SEQ))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_pdu_v1_decode
 * SYNOPSIS:    gboolean g_snmp_pdu_v1_decode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_PDU     *pdu
 *                  )
 * DESCRIPTION: Decodes a PDU from ASN1.
 *              pdu is a union of snmp_ror and snmp_trp.
 * RETURNS:     unsigned short success.
 */

gboolean 
g_snmp_pdu_v1_decode ( ASN1_SCK *asn1, GSnmpPdu *pdu)
{
    guint cls, con;
    guchar *eoc;

    if (!g_asn1_header_decode (asn1, &eoc, &cls, &con, (guint32 *) &pdu->type))
        return FALSE;
    if (cls != ASN1_CTX || con != ASN1_CON)
        return FALSE;
    switch (pdu->type)
    {
        case G_SNMP_PDU_GET:
        case G_SNMP_PDU_NEXT:
        case G_SNMP_PDU_RESPONSE:
        case G_SNMP_PDU_SET:
            if (!g_snmp_request_decode (asn1, &pdu->request))
                return FALSE;
            if (!g_snmp_list_decode (asn1, &pdu->request.variables))
                return FALSE;
            break;
        case G_SNMP_PDU_TRAP1:
            if (!g_snmp_trap_decode (asn1, &pdu->trap))
                return FALSE;
            if (!g_snmp_list_decode (asn1, &pdu->trap.variables))
                return FALSE;
            break;
        default:
            return FALSE;
    }
    if (!g_asn1_eoc_decode (asn1, eoc))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_pdu_v2_decode
 * SYNOPSIS:    gboolean g_snmp_pdu_v2_decode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_PDU     *pdu
 *                  )
 * DESCRIPTION: Decodes a PDU from ASN1.
 *              pdu is snmp_ror.
 * RETURNS:     unsigned short success.
 */

gboolean 
g_snmp_pdu_v2_decode ( ASN1_SCK *asn1, GSnmpPdu *pdu)
{
    guint cls, con;
    guchar *eoc;

    if (!g_asn1_header_decode (asn1, &eoc, &cls, &con, (guint32 *) &pdu->type))
        return FALSE;
    if (cls != ASN1_CTX || con != ASN1_CON)
        return FALSE;
    switch (pdu->type)
    {
        case G_SNMP_PDU_GET:
        case G_SNMP_PDU_NEXT:
        case G_SNMP_PDU_RESPONSE:
        case G_SNMP_PDU_SET:
        case G_SNMP_PDU_BULK:
        case G_SNMP_PDU_INFORM:
        case G_SNMP_PDU_TRAP2:
            if (!g_snmp_request_decode (asn1, &pdu->request))
                return FALSE;
            if (!g_snmp_list_decode (asn1, &pdu->request.variables))
                return FALSE;
            break;
        default:
            return FALSE;
    }
    if (!g_asn1_eoc_decode (asn1, eoc))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_snmp_pdu_v3_decode
 * SYNOPSIS:    gboolean g_snmp_pdu_v3_decode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      SNMP_PDU     *pdu
 *                  )
 * DESCRIPTION: Decodes a PDU from ASN1.
 *              pdu is snmp_ror.
 * RETURNS:     unsigned short success.
 */

gboolean 
g_snmp_pdu_v3_decode ( ASN1_SCK *asn1, GSnmpPdu *pdu, char **cenid, 
                       int *cenidlen, char **cname, int *cnamelen)
{
    guint cls, con;
    guchar *eoc;

    if (!g_asn1_header_decode (asn1, &eoc, &cls, &con, (guint32 *) &pdu->type))
        return FALSE;
    if (cls != ASN1_CTX || con != ASN1_CON)
        return FALSE;
    switch (pdu->type)
    {
        case G_SNMP_PDU_GET:
        case G_SNMP_PDU_NEXT:
        case G_SNMP_PDU_RESPONSE:
        case G_SNMP_PDU_SET:
        case G_SNMP_PDU_BULK:
        case G_SNMP_PDU_INFORM:
        case G_SNMP_PDU_TRAP2:
            if (!g_snmp_request_decode (asn1, &pdu->request))
                return FALSE;
            if (!g_snmp_list_decode (asn1, &pdu->request.variables))
                return FALSE;
            break;
        default:
            return FALSE;
    }
    if (!g_asn1_eoc_decode (asn1, eoc))
        return FALSE;
    return TRUE;
}

/* EOF */
