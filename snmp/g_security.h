/*
 * $Id$
 * GXSNMP -- An snmp management application
 * Copyright (C) 1998 Gregory McLean & Jochen Friedrich
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
 * Implementation of a SNMP security module as of RFC2271
 */

#ifndef __G_SECURITY_H
#define __G_SECURITY_H

#include "g_snmp.h"
#include "g_sha.h"
#include "g_md5.h"

/* Security models as in RFC2271, page 39 */

#define SMODEL_ANY     0
#define SMODEL_SNMPV1  1
#define SMODEL_SNMPV2C 2
#define SMODEL_USM     3

#define SLEVEL_NANP    0
#define SLEVEL_ANP     1
#define SLEVEL_AP      3

struct g_security
  {
    gboolean (*generateRequestMsg) ();
    gboolean (*processIncomingMsg) ();
    gboolean (*generateResponseMsg) ();
  };

/* Authentification types */
#define AUTH_COMMUNITY           1
#define AUTH_USEC                2

#define AUTH_COMLEN              255

/* Typedefs */

typedef struct  _SNMP_AUTH       SNMP_AUTH;

/* Authentication */

struct _SNMP_AUTH
{
    guint           type;
    guchar          name[AUTH_COMLEN];
    guint           nlen;
    guchar          ahash[20];
    guint           alen;
    guchar          phash[20];
    guint           plen;
};

void g_password_to_key_md5(guchar *password, guint passwordlen, guchar *key);
void g_password_to_key_sha(guchar *password, guint passwordlen, guchar *key);
void g_localize_key_md5(guchar *key, guchar *engineID, guint enginelen);
void g_localize_key_sha(guchar *key, guchar *engineID, guint enginelen);

#endif /* __G_SECURITY_H */

/* EOF */
