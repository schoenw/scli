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
 * Defines and variables for snmp support
 */

#ifndef __G_TRANSPORT_H__
#define __G_TRANSPORT_H__

#include "g_snmp.h"

#define MAX_DGRAM_SIZE 32768

struct g_transport
  {
     guint	 model;		/* Transport model number */
     gchar     * name;		/* Name of transport method */
     gboolean (*sendMessage) (
                         struct sockaddr *transportAddress,
                         gpointer outgoingMessage,
                         guint outgoingMessageLength);
     void     (*receiveMessage) ();
     gboolean (*resolveAddress) (
                         guchar *hostName,
                         struct sockaddr **transportAddress);
     guint    (*getSocket) ();
  };

gboolean g_transport_init(gboolean dobind);

#endif /* __G_TRANSPORT_H__ */

/* EOF */
