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

#ifndef _G_ASN1_H_
#define _G_ASN1_H_

#define ASN1_UNI       0     /* Universal   */
#define ASN1_APL       1     /* Application */
#define ASN1_CTX       2     /* Context     */
#define ASN1_PRV       3     /* Private     */

                             /* Tag                */
#define ASN1_EOC       0     /* End Of Contents    */
#define ASN1_BOL       1     /* Boolean            */
#define ASN1_INT       2     /* Integer            */
#define ASN1_BTS       3     /* Bit String         */
#define ASN1_OTS       4     /* Octet String       */
#define ASN1_NUL       5     /* Null               */
#define ASN1_OJI       6     /* Object Identifier  */
#define ASN1_OJD       7     /* Object Description */
#define ASN1_EXT       8     /* External           */
#define ASN1_SEQ       16    /* Sequence           */
#define ASN1_SET       17    /* Set                */
#define ASN1_NUMSTR    18    /* Numerical String   */
#define ASN1_PRNSTR    19    /* Printable String   */
#define ASN1_TEXSTR    20    /* Teletext String    */
#define ASN1_VIDSTR    21    /* Video String       */
#define ASN1_IA5STR    22    /* IA5 String         */
#define ASN1_UNITIM    23    /* Universal Time     */
#define ASN1_GENTIM    24    /* General Time       */
#define ASN1_GRASTR    25    /* Graphical String   */
#define ASN1_VISSTR    26    /* Visible String     */
#define ASN1_GENSTR    27    /* General String     */

                             /* Primitie / Constructed */
#define ASN1_PRI     0       /* Primitive              */
#define ASN1_CON     1       /* Constructed            */

                             /* Mode to open ASN11 */
#define ASN1_ENC     0       /* _encodeoding           */
#define ASN1_DEC     1       /* _decodeoding           */
 

#define ASN1_ERR_NOERROR		0
#define ASN1_ERR_ENC_FULL		1
#define ASN1_ERR_DEC_EMPTY		2
#define ASN1_ERR_DEC_EOC_MISMATCH	3
#define ASN1_ERR_DEC_LENGTH_MISMATCH	4
#define ASN1_ERR_DEC_BADVALUE		5
#define ASN1_ERR_ENC_BADVALUE		6

typedef struct _ASN1_SCK ASN1_SCK;

struct _ASN1_SCK
{                              /* ASN1 socket                         */
    guchar    *pointer;        /* Octet just encoded or to be decoded */
    guchar    *begin;          /* First octet                         */
    guchar    *end;            /* Octet after last octet              */
    gint       error;          /* Error condition                     */
};


void g_asn1_open (ASN1_SCK *asn1, guchar *buf, guint len, guint mode);
void g_asn1_close (ASN1_SCK *asn1, guchar **buf, guint *len);
#if 0
gboolean g_asn1_octet_encode (ASN1_SCK *asn1, guchar ch);
gboolean g_asn1_octet_decode (ASN1_SCK *asn1, guchar *ch);
#endif
gboolean g_asn1_tag_encode (ASN1_SCK *asn1, guint tag);
gboolean g_asn1_tag_decode (ASN1_SCK *asn1, guint *tag);
gboolean g_asn1_id_encode (ASN1_SCK *asn1, guint cls, guint con, guint tag);
gboolean g_asn1_id_decode (ASN1_SCK *asn1, guint *cls, guint *con, guint *tag);
gboolean g_asn1_length_encode (ASN1_SCK *asn1, guint def, guint len);
gboolean g_asn1_length_decode (ASN1_SCK *asn1, guint *def, guint *len);
gboolean g_asn1_header_encode (ASN1_SCK *asn1, guchar *eoc, guint cls, 
                               guint con, guint tag);
gboolean g_asn1_header_decode (ASN1_SCK *asn1, guchar **eoc, guint *cls, 
                               guint *con, guint *tag);
gboolean g_asn1_eoc (ASN1_SCK *asn1, guchar *eoc);
gboolean g_asn1_eoc_encode (ASN1_SCK *asn1, guchar **eoc);
gboolean g_asn1_eoc_decode (ASN1_SCK *asn1, guchar *eoc);
gboolean g_asn1_null_encode (ASN1_SCK *asn1, guchar **eoc);
gboolean g_asn1_null_decode (ASN1_SCK *asn1, guchar *eoc);
gboolean g_asn1_int32_encode (ASN1_SCK *asn1, guchar **eoc, gint32 integer);
gboolean g_asn1_int32_decode (ASN1_SCK *asn1, guchar *eoc, gint32 *integer);
gboolean g_asn1_int64_encode (ASN1_SCK *asn1, guchar **eoc, gint64 integer);
gboolean g_asn1_int64_decode (ASN1_SCK *asn1, guchar *eoc, gint64 *integer);
gboolean g_asn1_uint32_encode (ASN1_SCK *asn1, guchar **eoc, guint32 integer);
gboolean g_asn1_uint32_decode (ASN1_SCK *asn1, guchar *eoc, guint32 *integer);
gboolean g_asn1_uint64_encode (ASN1_SCK *asn1, guchar **eoc, guint64 integer);
gboolean g_asn1_uint64_decode (ASN1_SCK *asn1, guchar *eoc, guint64 *integer);
gboolean g_asn1_octets_encode (ASN1_SCK *asn1, guchar **eoc, guchar *octs, 
                               guint len);
gboolean g_asn1_octets_decode (ASN1_SCK *asn1, guchar *eoc, guchar **octs,
                               guint *len);
#if 0
gboolean g_asn1_subid_encode (ASN1_SCK *asn1, guint32 subid);
gboolean g_asn1_subid_decode (ASN1_SCK *asn1, guint32 *subid);
#endif
gboolean g_asn1_oid_encode (ASN1_SCK *asn1, guchar **eoc, 
                            guint32 *oid, guint len);
gboolean g_asn1_oid_decode (ASN1_SCK *asn1, guchar *eoc, 
                            guint32 **oid, guint *len);
#endif
