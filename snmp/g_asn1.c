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

/*
 * MODULE INFORMATION
 * ------------------ 
 *     FILE     NAME:       g_asn1.c
 *     SYSTEM   NAME:       ASN1 Basic Encoding
 *     ORIGINAL AUTHOR(S):  Dirk Wisse
 *     VERSION  NUMBER:     1
 *     CREATION DATE:       1990/11/22
 *
 * DESCRIPTION: ASN1 Basic Encoding Rules.
 *              Encoding takes place from end to begin. A normal
 *              procedure for definite encoding is:
 *
 *              g_asn1_open (asn1, buf, sizeof (buf), ASN1_ENC);
 *              g_asn1_eoc_encode (asn1, &end_of_seq);
 *              g_asn1_int32_encode (asn1, &end_of_int, 3);
 *              g_asn1_header_encode (asn1, end_of_int, 
 *                                    ASN1_UNI, ASN1_PRI, ASN1_INT);
 *              g_asn1_octets_encode (asn1, &end_of_octs, "String", 6);
 *              g_asn1_header_encode (asn1, end_of_octets, 
 *                                    ASN1_UNI, ASN1_PRI, ASN1_OTS);
 *              g_asn1_header_encode (asn1, end_of_seq, 
 *                                    ASN1_UNI, ASN1_CON, ASN1_SEQ);
 *              g_asn1_close (asn1, &buf_start, &buf_len);
 *
 *              To decode this we must do:
 *
 *              g_asn1_open (asn1, buf_start, buf_len, ASN1_DEC);
 *              g_asn1_header_decode (asn1, &end_of_seq, cls, con, tag);
 *              g_asn1_header_decode (asn1, &end_of_octs, cls, con, tag);
 *              g_asn1_octets_decode (asn1, end_of_octs, str, len);
 *              g_asn1_header_decode (asn1, &end_of_int, cls, con, tag);
 *              g_asn1_int32_decode (asn1, end_of_int, &integer);
 *              g_asn1_eoc_decode (asn1, end_of_seq);
 *              g_asn1_close (asn1, &buf_start, &buf_len);
 *              
 *              For indefinite encoding end_of_seq and &end_of_seq in the
 *              example above should be replaced by NULL.
 *              For indefinite decoding nothing has to be changed.
 *              This can be very useful if you want to decode both
 *              definite and indefinite encodings.
 */

#include "g_snmp.h"

/*
 * NAME:        g_asn1_open                                   [API]
 * SYNOPSIS:    void g_asn1_open
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guchar   *buf,
 *                      guint     len,
 *                      guint     mode
 *                  )
 * DESCRIPTION: Opens an ASN1 socket.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              buf:  Character buffer for encoding.
 *              len:  Length of character buffer.
 *              mode: Encoding, Decoding (ASN1_ENC, ASN1_DEC).
 *              Encoding starts at the end of the buffer, and
 *              proceeds to the beginning.
 * RETURNS:     void
 */

void
g_asn1_open(ASN1_SCK *asn1, guchar *buf, guint len, guint mode)
{
    asn1->begin = buf;
    asn1->end = buf + len;
    asn1->pointer = (mode == ASN1_ENC) ? buf + len : buf;
    asn1->error = ASN1_ERR_NOERROR;
}

/*
 * NAME:        g_asn1_close                                  [API]
 * SYNOPSIS:    void g_asn1_close
 *                  (
 *                      ASN1_SCK   *asn1,
 *                      guchar    **buf,
 *                      guint      *len
 *                  )
 * DESCRIPTION: Closes an ASN1 socket.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              buf: pointer to beginning of encoding.
 *              len: Length of encoding.
 * RETURNS:     void
 */

void 
g_asn1_close(ASN1_SCK *asn1, guchar **buf, guint *len)
{
    *buf   = asn1->pointer;
    *len   = asn1->end - asn1->pointer;
}



/*
 * NAME:        g_asn1_octet_encode
 * SYNOPSIS:    gboolean g_asn1_octet_encode
 *                  (
 *                      ASN1_SCK     *asn1,
 *                      guchar        ch
 *                  )
 * DESCRIPTION: Encodes an octet.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_octet_encode(ASN1_SCK *asn1, guchar ch)
{
    if (asn1->pointer <= asn1->begin)
	{
		asn1->error = ASN1_ERR_ENC_FULL;
        return FALSE;
	}
    *--(asn1->pointer) = ch;
    return TRUE;
}

/*
 * NAME:        g_asn1_octet_decode
 * SYNOPSIS:    gboolean g_asn1_octet_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guchar   *ch
 *                  )
 * DESCRIPTION: Decodes an octet.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_octet_decode(ASN1_SCK *asn1, guchar *ch)
{
    if (asn1->pointer >= asn1->end)
	{
		asn1->error = ASN1_ERR_DEC_EMPTY;
        return FALSE;
	}
    *ch = *(asn1->pointer)++;
    return TRUE;
}

/*
 * NAME:        g_asn1_tag_encode
 * SYNOPSIS:    gboolean g_asn1_tag_encode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint     tag
 *                  )
 * DESCRIPTION: Encodes a tag.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_tag_encode(ASN1_SCK *asn1, guint tag)
{
    guchar ch;

    ch = (guchar) (tag & 0x7F);
    tag >>= 7;
    if (!g_asn1_octet_encode(asn1, ch))
        return FALSE;
    while (tag > 0)
    {
        ch = (guchar) (tag | 0x80);
        tag >>= 7;
        if (!g_asn1_octet_encode(asn1, ch))
            return FALSE;
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_tag_decode
 * SYNOPSIS:    gboolean g_asn1_tag_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint    *tag
 *                  )
 * DESCRIPTION: Decodes a tag.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_tag_decode(ASN1_SCK *asn1, guint *tag)
{
    guchar ch;

    *tag = 0;
    do
    {
        if (!g_asn1_octet_decode(asn1, &ch))
            return FALSE;
        *tag <<= 7;
        *tag |= ch & 0x7F;
    }
    while ((ch & 0x80) == 0x80);
    return TRUE;
}

/*
 * NAME:        g_asn1_id_encode
 * SYNOPSIS:    gboolean g_asn1_id_encode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint     cls,
 *                      guint     con,
 *                      guint     tag
 *                  )
 * DESCRIPTION: Encodes an identifier.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_id_encode(ASN1_SCK *asn1, guint cls, guint con, guint tag)
{
    guint ch;

    if (tag >= 0x1F)
    {
        if (!g_asn1_tag_encode (asn1, tag))
            return FALSE;
        tag = 0x1F;
    }
    ch = (guchar) ((cls << 6) | (con << 5) | (tag));
    if (!g_asn1_octet_encode (asn1, ch))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_asn1_id_decode
 * SYNOPSIS:    gboolean g_asn1_id_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint    *cls,
 *                      guint    *con,
 *                      guint    *tag
 *                  )
 * DESCRIPTION: Decodes an identifier.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_id_decode(ASN1_SCK *asn1, guint *cls, guint *con, guint *tag)
{
    guchar ch;

    if (!g_asn1_octet_decode (asn1, &ch))
        return FALSE;
    *cls = (ch & 0xC0) >> 6;
    *con = (ch & 0x20) >> 5;
    *tag = (ch & 0x1F);
    if (*tag == 0x1F)
    {
        if (!g_asn1_tag_decode (asn1, tag))
            return FALSE;
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_length_encode
 * SYNOPSIS:    gboolean g_asn1_len_encode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint     def,
 *                      guint     len
 *                  )
 * DESCRIPTION: Encodes a definite or indefinite length.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_length_encode(ASN1_SCK *asn1, guint def, guint len)
{
    guchar ch, cnt;

    if (!def)
        ch = 0x80;
    else
    {
        if (len < 0x80)
            ch = (guchar) len;
        else
        {
            cnt = 0;
            while (len > 0)
            {
                ch = (guchar) len;
                len >>= 8;
                if (!g_asn1_octet_encode (asn1, ch))
                    return FALSE;
                cnt++;
            }
            ch = (guchar) (cnt | 0x80);
        }
    }
    if (!g_asn1_octet_encode (asn1, ch))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_asn1_length_decode
 * SYNOPSIS:    gboolean g_asn1_length_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint     def,
 *                      guint     len
 *                  )
 * DESCRIPTION: Decodes a definite or indefinite length.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_length_decode(ASN1_SCK *asn1, guint *def, guint *len)
{
    guchar ch, cnt;

    if (!g_asn1_octet_decode (asn1, &ch))
        return FALSE;
    if (ch == 0x80)
        *def = 0;
    else
    {
        *def = 1;
        if (ch < 0x80)
            *len = ch;
        else
        {
            cnt = (guchar) (ch & 0x7F);
            *len = 0;
            while (cnt > 0)
            {
                if (!g_asn1_octet_decode (asn1, &ch))
                    return FALSE;
                *len <<= 8;
                *len |= ch;
                cnt--;
            }
        }
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_header_encode                             [API]
 * SYNOPSIS:    gboolean g_asn1_header_encode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guchar   *eoc,
 *                      guint     cls,
 *                      guint     con,
 *                      guint     tag
 *                  )
 * DESCRIPTION: Encodes an ASN1 header.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding or NULL if
 *                   indefinite.
 *              cls: Class (see asn1.h)
 *              con: Primitive, Constructed (ASN_PRI, ASN_CON)
 *              tag: Tag (see asn1.h)
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_header_encode(ASN1_SCK *asn1, guchar *eoc, guint cls,
		     guint con, guint tag)
{
    guint def, len;

    if (eoc == 0)
    {
        def = 0;
        len = 0;
    }
    else
    {
        def = 1;
        len = eoc - asn1->pointer;
    }
    if (!g_asn1_length_encode (asn1, def, len))
        return FALSE;
    if (!g_asn1_id_encode (asn1, cls, con, tag))
        return FALSE;
    return TRUE;
}

/*
 * NAME:        g_asn1_header_decode
 * SYNOPSIS:    gboolean g_asn1_header_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guchar  **eoc,
 *                      guint    *cls,
 *                      guint    *con,
 *                      guint    *tag
 *                  )
 * DESCRIPTION: Decodes an ASN1 header.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding or 0 if
 *                   indefinite.
 *              cls: Class (see asn1.h)
 *              con: Primitive, Constructed (ASN_PRI, ASN_CON)
 *              tag: Tag (see asn1.h)
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_header_decode(ASN1_SCK *asn1, guchar **eoc, guint *cls,
		     guint *con, guint *tag)
{
    guint def, len;

    if (!g_asn1_id_decode (asn1, cls, con, tag))
        return FALSE;
    if (!g_asn1_length_decode (asn1, &def, &len))
        return FALSE;
    if (def)
        *eoc = asn1->pointer + len;
    else
        *eoc = 0;
    if (g_snmp_debug_flags & G_SNMP_DEBUG_ASN1 && *con) {
	g_printerr("asn1dec %p: CONSTRUCTED\n", asn1);
    }
    return TRUE;
}


/*
 * NAME:        g_asn1_eoc                                   [API]
 * SYNOPSIS:    gboolean g_asn1_eoc
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guchar   *eoc
 *                  )
 * DESCRIPTION: Checks if decoding is at End Of Contents.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding or 0 if
 *                   indefinite.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_eoc ( ASN1_SCK *asn1, guchar *eoc)
{
  if (eoc == 0)
    return (asn1->pointer [0] == 0x00 && asn1->pointer [1] == 0x00);
  else
    return (asn1->pointer >= eoc);
}

/*
 * NAME:        g_asn1_eoc_encode                                [API]
 * SYNOPSIS:    gboolean g_asn1_eoc_encode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar   **eoc
 *                  )
 * DESCRIPTION: Encodes End Of Contents.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding or 0 if
 *                   indefinite.
 *              If eoc is 0 it encodes an ASN1 End Of
 *              Contents (0x00 0x00), so it produces an
 *              indefinite length encoding. If eoc points to
 *              a character pointer, eoc is filled with the
 *              pointer to the last encoded octet. This pointer
 *              can be used in the next asn1_header_encode to determine
 *              the length of the encoding. This produces a
 *              definite length encoding.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_eoc_encode ( ASN1_SCK *asn1, guchar **eoc )        
{
  if (eoc == 0)
    {
      if (!g_asn1_octet_encode (asn1, 0x00))
	return FALSE;
      if (!g_asn1_octet_encode (asn1, 0x00))
	return FALSE;
      return TRUE;
    }
  else
    {
      *eoc = asn1->pointer;
      return TRUE;
    }
}

/*
 * NAME:        g_asn1_eoc_decode                                [API]
 * SYNOPSIS:    gboolean g_asn1_eoc_decode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar    *eoc
 *                  )
 * DESCRIPTION: Decodes End Of Contents.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding or 0 if
 *                   indefinite.
 *              If eoc is 0 it decodes an ASN1 End Of
 *              Contents (0x00 0x00), so it has to be an
 *              indefinite length encoding. If eoc is a
 *              character pointer, it probably was filled by
 *              asn1_header_decode, and should point to the octet
 *              after the last of the encoding. It is checked
 *              if this pointer points to the octet to be
 *              decoded. This only takes place in decoding a
 *              definite length encoding.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_eoc_decode (ASN1_SCK *asn1, guchar   *eoc)
{
  guchar ch;
    
  if (eoc == 0)
    {
      if (!g_asn1_octet_decode (asn1, &ch))
	return FALSE;
      if (ch != 0x00)
	{
	  asn1->error = ASN1_ERR_DEC_EOC_MISMATCH;
	  return FALSE;
	}
      if (!g_asn1_octet_decode (asn1, &ch))
	return FALSE;
      if (ch != 0x00)
	{
	  asn1->error = ASN1_ERR_DEC_EOC_MISMATCH;
	  return FALSE;
	}
      return TRUE;
    }
  else
    {
      if (asn1->pointer != eoc)
	{
	  asn1->error = ASN1_ERR_DEC_LENGTH_MISMATCH;
	  return FALSE;
	}
      return TRUE;
    }
}

/*
 * NAME:        g_asn1_null_encode                                [API]
 * SYNOPSIS:    gboolean g_asn1_null_encode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar   **eoc
 *                  )
 * DESCRIPTION: Encodes Null.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding.
 *              Encodes nothing but can be used to fill eoc.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_null_encode ( ASN1_SCK *asn1, guchar **eoc )
{
    *eoc = asn1->pointer;
    return TRUE;
}

/*
 * NAME:        g_asn1_null_decode                                [API]
 * SYNOPSIS:    gboolean g_asn1_null_decode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar    *eoc
 *                  )
 * DESCRIPTION: Decodes Null.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding or 0 if
 *                   indefinite.
 *              Decodes anything up to eoc.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_null_decode ( ASN1_SCK *asn1, guchar *eoc)
{
    asn1->pointer = eoc;
    if (g_snmp_debug_flags & G_SNMP_DEBUG_ASN1) {
	g_printerr("asn1dec %p: NULL\n", asn1);
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_int32_encode                              [API]
 * SYNOPSIS:    gboolean g_asn1_int32_encode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar   **eoc,
 *                      gint       integer
 *                  )
 * DESCRIPTION: Encodes Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_int32_encode ( ASN1_SCK *asn1, guchar **eoc, gint32 integer)
{
    guchar ch,sign;
    int    lim;
    
    *eoc = asn1->pointer;
    if (integer < 0) {
        lim  = -1;
        sign = 0x80;
    } else {
        lim  = 0;
        sign = 0x00;
    }
    do {
        ch = (guchar) integer;
        integer >>= 8;
        if (!g_asn1_octet_encode (asn1, ch))
            return FALSE;
    } while ((integer != lim) || (guchar) (ch & 0x80) != sign);
    return TRUE;
}

/*
 * NAME:        g_asn1_int32_decode                               [API]
 * SYNOPSIS:    gboolean g_asn1_int32_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guchar   *eoc
 *                      gint     *integer
 *                  )
 * DESCRIPTION: Decodes Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding or 0 if
 *                       indefinite.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_int32_decode ( ASN1_SCK *asn1, guchar *eoc, gint32 *integer)
{
    guchar ch;
    guint  len;
    
    if (!g_asn1_octet_decode (asn1, &ch))
        return FALSE;
    *integer = (gchar) ch;
    len = 1;
    while (asn1->pointer < eoc) {
        if (++len > sizeof (gint32)) {
	    asn1->error = ASN1_ERR_DEC_BADVALUE;
            return FALSE;
	}
        if (!g_asn1_octet_decode (asn1, &ch))
            return FALSE;
        *integer <<= 8;
        *integer |= ch;
    }
    if (g_snmp_debug_flags & G_SNMP_DEBUG_ASN1) {
	g_printerr("asn1dec %p: INTEGER %d\n", asn1, *integer);
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_int64_encode                            [API]
 * SYNOPSIS:    gboolean g_asn1_int64_encode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar   **eoc,
 *                      glong      integer
 *                  )
 * DESCRIPTION: Encodes Long Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_int64_encode ( ASN1_SCK *asn1, guchar **eoc, gint64 integer)
{
    guchar ch, sign;
    glong  lim;
    
    *eoc = asn1->pointer;
    if (integer < 0) {
        lim  = -1;
        sign = 0x80;
    } else {
        lim  = 0;
        sign = 0x00;
    }
    do {
        ch = (guchar) integer;
        integer >>= 8;
        if (!g_asn1_octet_encode (asn1, ch))
            return FALSE;
    } while ((integer != lim) || (guchar) (ch & 0x80) != sign);
    return TRUE;
}

/*
 * NAME:        g_asn1_int64_decode                            [API]
 * SYNOPSIS:    gboolean g_asn1_int64_decode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar    *eoc,
 *                      glong     *integer
 *                  )
 * DESCRIPTION: Decodes Long Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding or 0 if
 *                       indefinite.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_int64_decode ( ASN1_SCK *asn1, guchar *eoc, gint64 *integer)
{
    guchar ch;
    guint  len;

    if (!g_asn1_octet_decode (asn1, &ch))
        return FALSE;
    *integer = (gchar) ch;
    len = 1;
    while (asn1->pointer < eoc) {
	if (++len > sizeof (gint64)) {
	    asn1->error = ASN1_ERR_DEC_BADVALUE;
	    return FALSE;
	}
	if (!g_asn1_octet_decode (asn1, &ch))
	    return FALSE;
	*integer <<= 8;
	*integer |= ch;
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_uint32_encode                           [API]
 * SYNOPSIS:    gboolean g_asn1_uint32_encode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar   **eoc,
 *                      guint      integer
 *                  )
 * DESCRIPTION: Encodes Unsigned Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_uint32_encode ( ASN1_SCK *asn1, guchar **eoc, guint32 integer)
{
    guchar ch;
    
    *eoc = asn1->pointer;
    do {
	ch = (guchar) integer;
	integer >>= 8;
	if (!g_asn1_octet_encode (asn1, ch))
	    return FALSE;
    } while ((integer != 0) || (ch & 0x80) != 0x00);
    return TRUE;
}

/*
 * NAME:        g_asn1_uint32_decode                           [API]
 * SYNOPSIS:    gboolean g_asn1_uint32_decode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar    *eoc,
 *                      guint     *integer
 *                  )
 * DESCRIPTION: Decodes Unsigned Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding or 0 if
 *                       indefinite.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_uint32_decode ( ASN1_SCK *asn1, guchar *eoc, guint32 *integer)
{
    guchar ch;
    guint  len;
    
    if (!g_asn1_octet_decode (asn1, &ch))
        return FALSE;
    *integer = ch;
    len = (ch == 0) ? 0 : 1;
    while (asn1->pointer < eoc) {
        if (++len > sizeof (guint32)) {
	    asn1->error = ASN1_ERR_DEC_BADVALUE;
            return FALSE;
	}
        if (!g_asn1_octet_decode (asn1, &ch))
            return FALSE;
        *integer <<= 8;
        *integer |= ch;
    }
    if (g_snmp_debug_flags & G_SNMP_DEBUG_ASN1) {
	g_printerr("asn1dec %p: INTEGER %u\n", asn1, *integer);
    }
    return TRUE;
}

/*
 * NAME:        asn1_uint64_encode                         [API]
 * SYNOPSIS:    gboolean g_asn1_uint64_encode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar   **eoc,
 *                      gulong     integer
 *                  )
 * DESCRIPTION: Encodes Long Unsigned Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_uint64_encode ( ASN1_SCK *asn1, guchar **eoc, guint64 integer)
{
    guchar ch;

    *eoc = asn1->pointer;
    do {
        ch = (guchar) integer;
        integer >>= 8;
        if (!g_asn1_octet_encode (asn1, ch))
            return FALSE;
    }
    while ((integer != 0) || (ch & 0x80) != 0x00);
    return TRUE;
}

/*
 * NAME:        g_asn1_uint64_decode                         [API]
 * SYNOPSIS:    gboolean g_asn1_uint64_decode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar    *eoc,
 *                      gulong    *integer
 *                  )
 * DESCRIPTION: Decodes Long Unsigned Integer.
 *              Parameters:
 *              asn1:    pointer to ASN1 socket.
 *              eoc:     pointer to end of encoding or 0 if
 *                       indefinite.
 *              integer: Integer.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_uint64_decode ( ASN1_SCK *asn1, guchar *eoc, guint64 *integer)
{
    guchar ch;
    guint  len;

    if (!g_asn1_octet_decode (asn1, &ch))
        return FALSE;
    *integer = ch;
    len = (ch == 0) ? 0 : 1;
    while (asn1->pointer < eoc) {
        if (++len > sizeof (guint64)) {
	    asn1->error = ASN1_ERR_DEC_BADVALUE;
            return FALSE;
	}
        if (!g_asn1_octet_decode (asn1, &ch))
            return FALSE;
        *integer <<= 8;
        *integer |= ch;
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_octets_encode                                [API]
 * SYNOPSIS:    gboolean asn1_octets_encode
 *                  (
 *                      ASN1_SCK  *asn1,
 *                      guchar   **eoc,
 *                      guchar    *octets,
 *                      guint      len
 *                  )
 * DESCRIPTION: Encodes Octet String.
 *              Parameters:
 *              asn1:   pointer to ASN1 socket.
 *              eoc:    pointer to end of encoding.
 *              octets: pointer to begin of Octet GString.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_octets_encode ( ASN1_SCK *asn1, guchar **eoc, guchar *octets, guint len)
{
    guchar *ptr;

    *eoc = asn1->pointer;
    ptr = octets + len;
    
    while (len-- > 0) {
	if (!g_asn1_octet_encode (asn1, *--ptr))
	    return FALSE;
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_octets_decode                                [API]
 * SYNOPSIS:    g_asn1_octets_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guchar   *eoc,
 *                      guchar   *octets,
 *                      guint    *len
 *                  )
 * DESCRIPTION: Decodes Octet String.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              Eoc: pointer to end of encoding or 0 if
 *                   indefinite.
 *              Ots: pointer to Object GString*.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_octets_decode ( ASN1_SCK *asn1, guchar *eoc, guchar **octets, guint *len)
{
    guchar *ptr;
    
    *octets = NULL;
    *len = 0;
    *octets = g_malloc(eoc - asn1->pointer);
    ptr = *octets;
    while (asn1->pointer < eoc) {
	if (!g_asn1_octet_decode (asn1, (guchar *)ptr++)) {
	    g_free(*octets);
	    *octets = NULL;
	    return FALSE;
	}
	(*len)++;
    }
    if (g_snmp_debug_flags & G_SNMP_DEBUG_ASN1) {
	guint i;
	g_printerr("asn1dec %p: OCTET STRING '", asn1);
	for (i = 0; i < *len; i++) {
	    g_printerr("%02x", (*octets)[i]);
	}
	g_printerr("'h\n");
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_subid_encode
 * SYNOPSIS:    gboolean g_asn1_subid_encode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint32  subid
 *                  )
 * DESCRIPTION: Encodes Sub Identifier.
 *              Parameters:
 *              asn1:  pointer to ASN1 socket.
 *              subid: Sub Identifier.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_subid_encode ( ASN1_SCK *asn1, guint32 subid)
{
    guchar ch;
    
    ch = (guchar) (subid & 0x7F);
    subid >>= 7;
    if (!g_asn1_octet_encode (asn1, ch))
	return FALSE;
    while (subid > 0) {
	ch = (guchar) (subid | 0x80);
	subid >>= 7;
	if (!g_asn1_octet_encode (asn1, ch))
	    return FALSE;
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_subid_decode
 * SYNOPSIS:    gboolean g_asn1_subid_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      guint32 *subid
 *                  )
 * DESCRIPTION: Encodes Sub Identifier.
 *              Parameters:
 *              asn1:  pointer to ASN1 socket.
 *              subid: Sub Identifier.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_subid_decode ( ASN1_SCK *asn1, guint32 *subid)
{
    guchar ch;
    
    *subid = 0;
    do {
        if (!g_asn1_octet_decode(asn1, &ch))
            return FALSE;
        *subid <<= 7;
        *subid |= ch & 0x7F;
    }
    while ((ch & 0x80) == 0x80);
    return TRUE;
}

/*
 * NAME:        g_asn1_oid_encode                                [API]
 * SYNOPSIS:    gboolean g_asn1_oid_encode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      char    **eoc,
 *                      guint32  *oid,
 *                      guint     len
 *                  )
 * DESCRIPTION: Encodes Obect Identifier.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc: pointer to end of encoding.
 *              oid: pointer to begin of Object Identifier.
 *              len: Length of Object Identifier in gulongs.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_oid_encode ( ASN1_SCK *asn1, guchar **eoc, guint32 *oid,
		    guint len)
{
    gulong subid;
    guint l = len;
    
    *eoc = asn1->pointer;
    if (len < 2) {
	asn1->error = ASN1_ERR_ENC_BADVALUE;
	return FALSE;
    }
    subid = oid [1] + oid [0] * 40;
    oid += len;
    while (l-- > 2) {
	if (!g_asn1_subid_encode (asn1, *--oid))
	    return FALSE;
    }
    if (!g_asn1_subid_encode (asn1, subid))
	return FALSE;
    if (g_snmp_debug_flags & G_SNMP_DEBUG_ASN1) {
	guint i;
	g_printerr("asn1enc %p: OBJECT IDENTIFIER ", asn1);
	for (i = 0; i < len; i++) {
	    g_printerr("%s%u", i ? "." : "", oid[i]);
	}
	g_printerr("\n");
    }
    return TRUE;
}

/*
 * NAME:        g_asn1_oid_decode                                [API]
 * SYNOPSIS:    gboolean g_asn1_oid_decode
 *                  (
 *                      ASN1_SCK *asn1,
 *                      char     *eoc,
 *                      guint32  *oid,
 *                      guint    *len
 *                  )
 * DESCRIPTION: Decodes Obect Identifier.
 *              Parameters:
 *              asn1: pointer to ASN1 socket.
 *              eoc:  pointer to end of encoding or 0 if
 *                    indefinite.
 *              oid:  pointer to begin of Object Identifier.
 *              size: Size of Obect Identifier in gulongs
 *              len:  Length of Object Identifier in gulongs.
 * RETURNS:     gboolean success.
 */

gboolean 
g_asn1_oid_decode ( ASN1_SCK *asn1, guchar *eoc, guint32 **oid, 
		    guint *len)
{
    guint32 subid;
    guint  size;
    guint32 *optr;
    
    size = eoc - asn1->pointer + 1;
    *oid = g_malloc(size * sizeof(guint32));
    optr = *oid;
    
    if (!g_asn1_subid_decode (asn1, &subid)) {
	g_free(*oid);
	*oid = NULL;
	return FALSE;
    }
    if (subid < 40) {
	optr [0] = 0;
	optr [1] = subid;
    } else if (subid < 80) {
	optr [0] = 1;
	optr [1] = subid - 40;
    } else {
	optr [0] = 2;
	optr [1] = subid - 80;
    }
    *len = 2;
    optr += 2;
    while (asn1->pointer < eoc) {
	if (++(*len) > size) {
	    asn1->error = ASN1_ERR_DEC_BADVALUE;
	    g_free(*oid);
	    *oid = NULL;
	    return FALSE;
	}
	if (!g_asn1_subid_decode (asn1, optr++)) {
	    g_free(*oid);
	    *oid = NULL;
	    return FALSE;
        }
    }
    
    if (g_snmp_debug_flags & G_SNMP_DEBUG_ASN1) {
	guint i;
	g_printerr("asn1dec %p: OBJECT IDENTIFIER ", asn1);
	for (i = 0; i < *len; i++) {
	    g_printerr("%s%u", i ? "." : "", (*oid)[i]);
	}
	g_printerr("\n");
    }
    return TRUE;
}

/* EOF */
