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
 * Implementation of a SNMP messaging subsystem as of RFC2271
 */

#ifndef __G_MESSAGE_H__
#define __G_MESSAGE_H__

#include "g_snmp.h"

/* Processing Models as in RFC2271, page 40 */

#define PMODEL_SNMPV1  0
#define PMODEL_SNMPV2C 1
#define PMODEL_SNMPV2  2
#define PMODEL_SNMPV3  3

struct g_message
  {
     gboolean (*prepareOutgoingMessage) (
                         guint transportDomain,
                         struct sockaddr *transportAddress,
                         guint messageProcessingModel, 
                         guint securityModel,
                         GString *securityName, 
                         int securityLevel,
                         GString *contextEngineID, 
                         GString *contextName,
                         guint pduVersion, 
                         GSnmpPdu *PDU,
                         gboolean expectResponse, 
                         int sendPduHandle,
                         guint *outTransportDomain,
                         struct sockaddr **outTransportAddress,
                         gpointer *outgoingMessage,
                         guint *outgoingMessageLength);
     gboolean (*prepareResponseMessage) (
                         guint messageProcessingModel,
                         guint securityModel, 
                         GString *securityName,
                         int securityLevel, 
                         GString *contextEngineID,
                         GString *contextName, 
                         guint pduVersion, 
                         GSnmpPdu *PDU,
                         guint maxSizeResponseScopedPDU,
                         gpointer stateReference, 
                         guint statusInformation,
                         guint *outTransportDomain,
                         struct sockaddr **outTransportAddress,
                         gpointer *outgoingMessage,
                         guint *outgoingMessageLength);
     gboolean (*prepareDataElements) (
                         guint transportDomain,
                         struct sockaddr *transportAddress,
                         gpointer wholeMsg, 
                         int wholeMsgLength,
                         guint *messageProcessingModel, 
                         guint *securityModel,
                         GString **securityName, 
                         int *securityLevel,
                         GString **contextEngineID, 
                         GString **contextName,
                         guint *pduVersion, 
                         GSnmpPdu *PDU, 
                         guint *pduType,
                         int *sendPduHandle,
                         guint *maxSizeResponseScopedPDU,
                         guint *statusInformation, 
                         gpointer *stateReference);
     gboolean (*releaseState) (
                         gpointer stateReference);
  };

gboolean g_message_init(void);

#endif /* __G_MESSAGE_H__ */

/* EOF */
