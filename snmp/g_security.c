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

#include <config.h>               /* pull in the autoconf detected stuff */
#include "g_snmp.h"
#ifdef HAVE_STRING_H
#include <string.h>
#endif

/* This module defines the API to the SNMP RFC layer. Requests are routed
 * to the appropriate transport (e.g. IPv4 or IPv6 or IPX) by using the
 * message processing compatible with the given PDU version (V1, V2C,
 * or V3). Applications will prefer to use the sync or async event loop
 * API presented by the g_session layer.
 */

/*
   statusInformation =
     authenticateOutgoingMsg(
     IN   authKey                   -- secret key for authentication
     IN   wholeMsg                  -- unauthenticated complete message
     OUT  authenticatedWholeMsg     -- complete authenticated message
          )

   statusInformation =
     authenticateIncomingMsg(
     IN   authKey                   -- secret key for authentication
     IN   authParameters            -- as received on the wire
     IN   wholeMsg                  -- as received on the wire
     OUT  authenticatedWholeMsg     -- complete authenticated message
          )

   statusInformation =
     encryptData(
     IN    encryptKey               -- secret key for encryption
     IN    dataToEncrypt            -- data to encrypt (scopedPDU)
     OUT   encryptedData            -- encrypted data (encryptedPDU)
     OUT   privParameters           -- filled in by service provider
           )

   statusInformation =
     decryptData(
     IN    decryptKey               -- secret key for decrypting
     IN    privParameters           -- as received on the wire
     IN    encryptedData            -- encrypted data (encryptedPDU)
     OUT   decryptedData            -- decrypted data (scopedPDU)
              )

   statusInformation =            -- success or errorIndication
     generateRequestMsg(
     IN   messageProcessingModel  -- typically, SNMP version
     IN   globalData              -- message header, admin data
     IN   maxMessageSize          -- of the sending SNMP entity
     IN   securityModel           -- for the outgoing message
     IN   securityEngineID        -- authoritative SNMP entity
     IN   securityName            -- on behalf of this principal
     IN   securityLevel           -- Level of Security requested
     IN   scopedPDU               -- message (plaintext) payload
     OUT  securityParameters      -- filled in by Security Module
     OUT  wholeMsg                -- complete generated message
     OUT  wholeMsgLength          -- length of generated message
          )

   statusInformation =            -- success or errorIndication
     generateResponseMsg(
     IN   messageProcessingModel  -- typically, SNMP version
     IN   globalData              -- message header, admin data
     IN   maxMessageSize          -- of the sending SNMP entity
     IN   securityModel           -- for the outgoing message
     IN   securityEngineID        -- authoritative SNMP entity
     IN   securityName            -- on behalf of this principal
     IN   securityLevel           -- Level of Security requested
     IN   scopedPDU               -- message (plaintext) payload
     IN   securityStateReference  -- reference to security state
                                  -- information from original
                                  -- request
     OUT  securityParameters      -- filled in by Security Module
     OUT  wholeMsg                -- complete generated message
     OUT  wholeMsgLength          -- length of generated message
           )

   statusInformation =             -- errorIndication or success
                                   -- error counter OID/value if error
     processIncomingMsg(
     IN   messageProcessingModel   -- typically, SNMP version
     IN   maxMessageSize           -- of the sending SNMP entity
     IN   securityParameters       -- for the received message
     IN   securityModel            -- for the received message
     IN   securityLevel            -- Level of Security
     IN   wholeMsg                 -- as received on the wire
     IN   wholeMsgLength           -- length as received on the wire
     OUT  securityEngineID         -- authoritative SNMP entity
     OUT  securityName             -- identification of the principal
     OUT  scopedPDU,               -- message (plaintext) payload
     OUT  maxSizeResponseScopedPDU -- maximum size of the Response PDU
     OUT  securityStateReference   -- reference to security state
          )                        -- information, needed for response

*/

/*
 * USMSecurityParametersSyntax DEFINITIONS IMPLICIT TAGS ::= BEGIN
 *
 *    UsmSecurityParameters ::=
 *        SEQUENCE {
 *         -- global User-based security parameters
 *            msgAuthoritativeEngineID     OCTET STRING,
 *            msgAuthoritativeEngineBoots  INTEGER (0..2147483647),
 *            msgAuthoritativeEngineTime   INTEGER (0..2147483647),
 *            msgUserName                  OCTET STRING (SIZE(1..32)),
 *         -- authentication protocol specific parameters
 *            msgAuthenticationParameters  OCTET STRING,
 *         -- privacy protocol specific parameters
 *            msgPrivacyParameters         OCTET STRING
 *        }
 * END
 */

/* This is from RFC2274 */

/*    guchar *password;          IN
 *    guint   passwordlen;       IN
 *    guchar *engineID;          IN  - pointer to snmpEngineID
 *    guint   enginelen;         IN  - length of snmpEngineID
 *    guchar *key;               OUT - caller supplies pointer to 16
 *                                     octet buffer
 */

void g_password_to_key_md5(guchar *password, guint passwordlen, guchar *key)
{
  MD5_CTX     MD;
  guchar      *cp, password_buf[64];
  gulong      password_index = 0;
  gulong      count = 0, i;

  MD5Init (&MD);   /* initialize MD5 */

  /**********************************************/
  /* Use while loop until we've done 1 Megabyte */
  /**********************************************/

  while (count < 1048576) 
    {
      cp = password_buf;
      for(i = 0; i < 64; i++) 
        {
          /*************************************************/
          /* Take the next octet of the password, wrapping */
          /* to the beginning of the password as necessary.*/
          /*************************************************/
          *cp++ = password[ password_index++ % passwordlen ];
        }
      MD5Update (&MD, password_buf, 64);
      count += 64;
    }
  MD5Final (key, &MD);              /* tell MD5 we're done */

  /*****************************************************/
  /* Now localize the key with the engineID and pass   */
  /* through MD5 to produce final key                  */
  /* May want to ensure that engineLength <= 32,       */
  /* otherwise need to use a buffer larger than 64     */
  /*****************************************************/
}

void g_localize_key_md5(guchar *key, guchar *engineID, guint enginelen)
{
  MD5_CTX     MD;
  guchar      password_buf[64];

  g_memmove (password_buf, key, 16);
  g_memmove (password_buf+16, engineID, enginelen);
  g_memmove (password_buf+16+enginelen, key, 16);

  MD5Init (&MD);
  MD5Update (&MD, password_buf, 32+enginelen);
  MD5Final (key, &MD);

  return;
}

/*    guchar *password;          IN
 *    guint   passwordlen;       IN
 *    guchar *engineID;          IN  - pointer to snmpEngineID
 *    guint   enginelen;         IN  - length of snmpEngineID
 *    guchar *key;               OUT - caller supplies pointer to 20
 *                                     octet buffer
 */

void g_password_to_key_sha(guchar *password, guint passwordlen, guchar *key)
{
  SHA_CTX     SH;
  guchar      *cp, password_buf[72];
  gulong      password_index = 0;
  gulong      count = 0, i;

  SHAInit (&SH);   /* initialize SHA */

  /**********************************************/
  /* Use while loop until we've done 1 Megabyte */
  /**********************************************/
  while (count < 1048576) 
    {
      cp = password_buf;
      for(i = 0; i < 64; i++) 
        {
          /*************************************************/
          /* Take the next octet of the password, wrapping */
          /* to the beginning of the password as necessary.*/
          /*************************************************/
          *cp++ = password[ password_index++ % passwordlen ];
        }
      SHAUpdate (&SH, password_buf, 64);
      count += 64;
    }
  SHAFinal (key, &SH);              /* tell SHA we're done */
  /*****************************************************/
  /* Now localize the key with the engineID and pass   */
  /* through SHA to produce final key                  */
  /* May want to ensure that engineLength <= 32,       */
  /* otherwise need to use a buffer larger than 72     */
  /*****************************************************/
}

void g_localize_key_sha(guchar *key, guchar *engineID, guint enginelen)
{
  SHA_CTX     SH;
  guchar      password_buf[72];

  g_memmove (password_buf, key, 20);
  g_memmove (password_buf+20, engineID, enginelen);
  g_memmove (password_buf+20+enginelen, key, 20);

  SHAInit (&SH);
  SHAUpdate (&SH, password_buf, 40+enginelen);
  SHAFinal (key, &SH);

  return;
}
