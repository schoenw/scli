/*
 * g_snmp.h -- public header of the glib based snmp library
 *
 * Copyright (c) 1998 Gregory McLean & Jochen Friedrich
 * Copyright (c) 2001 Juergen Schoenwaelder
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

#ifndef _G_SNMP_H_
#define _G_SNMP_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <glib.h>

/* Our Enterprise Handle */

#define ENTERPRISE_GNOME 3319

/* SNMP Versions */

typedef enum {
    G_SNMP_V1    = 0,
    G_SNMP_V2C   = 1,
    G_SNMP_V3    = 3
} GSnmpVersion;

/* Default Sizes */

#define SNMP_SIZE_COMM              256
#define SNMP_SIZE_OBJECTID          128
#define SNMP_SIZE_BUFCHR            256
#define SNMP_SIZE_BUFINT            128

#define SNMP_SIZE_SMALLOBJECTID     16

/* Requests */

typedef enum {
    G_SNMP_PDU_GET	= 0,
    G_SNMP_PDU_NEXT	= 1,
    G_SNMP_PDU_RESPONSE	= 2,
    G_SNMP_PDU_SET	= 3,
    G_SNMP_PDU_TRAP1	= 4,
    G_SNMP_PDU_BULK	= 5,
    G_SNMP_PDU_INFORM	= 6,
    G_SNMP_PDU_TRAP2	= 7
} GSnmpPduType;

/* Errors */

typedef enum {
    G_SNMP_ERR_PROCEDURE	      = -3,
    G_SNMP_ERR_INTERNAL		      = -2,
    G_SNMP_ERR_NORESPONSE	      = -1,
    G_SNMP_ERR_NOERROR		      = 0,
    G_SNMP_ERR_TOOBIG                 = 1,
    G_SNMP_ERR_NOSUCHNAME             = 2,
    G_SNMP_ERR_BADVALUE               = 3,
    G_SNMP_ERR_READONLY               = 4,
    G_SNMP_ERR_GENERROR               = 5,
    G_SNMP_ERR_NOACCESS               = 6,
    G_SNMP_ERR_WRONGTYPE              = 7,
    G_SNMP_ERR_WRONGLENGTH            = 8,
    G_SNMP_ERR_WRONGENCODING          = 9,
    G_SNMP_ERR_WRONGVALUE             = 10,
    G_SNMP_ERR_NOCREATION             = 11,
    G_SNMP_ERR_INCONSISTENTVALUE      = 12,
    G_SNMP_ERR_RESOURCEUNAVAILABLE    = 13,
    G_SNMP_ERR_COMMITFAILED           = 14,
    G_SNMP_ERR_UNDOFAILED             = 15,
    G_SNMP_ERR_AUTHORIZATIONERROR     = 16,
    G_SNMP_ERR_NOTWRITABLE            = 17,
    G_SNMP_ERR_INCONSISTENTNAME       = 18
} GSnmpError;

/* General SNMP V1 Traps */		/* xxx fix this - really needed */

#define SNMP_TRAP_COLDSTART          0
#define SNMP_TRAP_WARMSTART          1
#define SNMP_TRAP_LINKDOWN           2
#define SNMP_TRAP_LINKUP             3
#define SNMP_TRAP_AUTFAILURE         4
#define SNMP_TRAP_EQPNEIGHBORLOSS    5
#define SNMP_TRAP_ENTSPECIFIC        6


typedef enum {
    G_SNMP_NULL		  = 0,
    G_SNMP_OCTETSTRING	  = 1,
    G_SNMP_OBJECTID	  = 2,
    G_SNMP_IPADDRESS	  = 3,
    G_SNMP_INTEGER32	  = 4,
    G_SNMP_UNSIGNED32	  = 5,	/* also used for Gauge32 */
    G_SNMP_COUNTER32	  = 6,
    G_SNMP_TIMETICKS	  = 7,
    G_SNMP_OPAQUE	  = 8,
    G_SNMP_COUNTER64	  = 9,
    G_SNMP_NOSUCHOBJECT   = 10,
    G_SNMP_NOSUCHINSTANCE = 11,
    G_SNMP_ENDOFMIBVIEW   = 12
} GSnmpVarBindType;


/* Typedefs */

typedef struct  _GSnmpReqResp		GSnmpReqResp;
typedef struct  _GSnmpV1Trap		GSnmpV1Trap;
typedef union   _GSnmpPdu		GSnmpPdu;
typedef union   _GSnmpVarBindSyntax     GSnmpVarBindSyntax;
typedef struct  _GSnmpVarBind		GSnmpVarBind;

union _GSnmpVarBindSyntax
{
    guchar   uc[1];	/*  8 bit unsigned */
    gint32   i32[1];	/* 32 bit signed   */
    guint32  ui32[1];	/* 32 bit unsigned */
    gint64   i64[1];	/* 64 bit signed   */
    guint64  ui64[1];	/* 64 bit unsigned */
};

struct _GSnmpVarBind
{
    guint32		*id;
    guint8		id_len;
    GSnmpVarBindType	type;
    guint16		syntax_len;
    GSnmpVarBindSyntax	syntax;
};

struct _GSnmpReqResp
{
    GSnmpPduType type;
    gint32       id;
    GSnmpError   error_status;
    guint32      error_index;
    GSList      *variables;
};

struct _GSnmpV1Trap
{
    GSnmpPduType type;
    guint32     *id;
    guint        id_len;
    guint32      ip_address;
    guint32      general;
    guint32      specific;
    guint32      time;
    GSList      *variables;
};

union _GSnmpPdu			/* xxx are three structures really needed */
{
    GSnmpPduType type;
    GSnmpV1Trap  trap;
    GSnmpReqResp request;
};

/* Include other SNMP headers */

#include "g_asn1.h"
#include "g_message.h"
#include "g_security.h"
#include "g_transport.h"
#include "g_session.h"
#include "g_dispatch.h"
#include "g_utils.h"
#include "g_snmp_table.h"
#include "g_snmp_walk.h"

/* SNMP V1 trap names */

extern const char *SnmpTrap[];		/* xxx fix this - really needed ? */

/* Variables that control SNMP library debugging features. */

typedef enum
{
  G_SNMP_DEBUG_REQUESTS	 = 1 << 0,
  G_SNMP_DEBUG_SESSION	 = 1 << 1,
  G_SNMP_DEBUG_TRANSPORT = 1 << 2,
  G_SNMP_DEBUG_PACKET	 = 1 << 3,
  G_SNMP_DEBUG_ASN1	 = 1 << 4,
  G_SNMP_DEBUG_ALL	 = G_SNMP_DEBUG_REQUESTS
			 | G_SNMP_DEBUG_SESSION
			 | G_SNMP_DEBUG_TRANSPORT
			 | G_SNMP_DEBUG_PACKET
			 | G_SNMP_DEBUG_ASN1,
  G_SNMP_DEBUG_MASK	 = 0x1f
} GSnmpDebugFlags;

extern GSnmpDebugFlags g_snmp_debug_flags;

/* SNMP encoding and decoding */
 
gboolean g_snmp_pdu_v1_encode ( ASN1_SCK *asn1, GSnmpPdu *pdu);
gboolean g_snmp_pdu_v1_decode ( ASN1_SCK *asn1, GSnmpPdu *pdu);
gboolean g_snmp_pdu_v2_encode ( ASN1_SCK *asn1, GSnmpPdu *pdu);
gboolean g_snmp_pdu_v2_decode ( ASN1_SCK *asn1, GSnmpPdu *pdu);
gboolean g_snmp_pdu_v3_encode ( ASN1_SCK *asn1, GSnmpPdu *pdu, 
         char *cenid, int cenidlen, char *cname, int cnamelen);
gboolean g_snmp_pdu_v3_decode ( ASN1_SCK *asn1, GSnmpPdu *pdu,
         char **cenid, int *cenidlen, char **cname, int *cnamelen);

/* SNMP hooks for debugging, profiling, statistics, ... */

void (*g_snmp_list_decode_hook)(GSList *list);
void (*g_snmp_list_encode_hook)(GSList *list);

/* SNMP varbind and varbind list management */

GSnmpVarBind* g_snmp_varbind_new(guint32 const *oid, gsize const len,
				 GSnmpVarBindType const type,
				 gpointer const value,
				 gsize const value_len);
void          g_snmp_varbind_free(GSnmpVarBind *vb);


void	      g_snmp_vbl_add(GSList **vbl,
			     guint32 const *oid, gsize const len,
			     GSnmpVarBindType const type,
			     gpointer const value,
			     gsize const value_len);
void	      g_snmp_vbl_add_null(GSList **vbl,
				  guint32 const *oid, gsize const len);
void	      g_snmp_vbl_free(GSList *vbl);

#endif
/* EOF */
