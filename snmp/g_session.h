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
 */

#ifndef __G_SESSION_H__
#define __G_SESSION_H__

/*
 * In an effort to reduce the redundant code the callbacks from the
 * snmp lib callbacks are routed through one routine, that in turn will
 * match up the reqid and invoke the proper callback in the gui code.
 * This allows for a very clear separation of the snmp lib and the gui
 * interface. The queue routine will copy the return values from the 
 * snmp query to the per host structure and then invoke the callback.
 * the call back should return 1 and the queue entry will be purged.
 * This will also invalidate values returned.
 */

/*
 * Basic snmp info on a per session basis.
 */

typedef struct _GSnmpSession {
  struct sockaddr *address;
  guint         domain;
  gchar        *rcomm;
  gchar        *wcomm;
  guint         retries;
  gchar         *name;
  guint         status;
  guint         port;
  guint         timeout;
  GSnmpVersion  version;
  gboolean      (*done_callback) (); /* what to call when complete */
  void          (*time_callback) (); /* what to call on a timeout */
  gpointer      magic;         /* can be used to pass additional data to cb */
} GSnmpSession;

GSnmpSession*	g_snmp_session_new();
void		g_snmp_session_destroy(GSnmpSession *s);

gpointer g_snmp_session_async_set    (GSnmpSession *session,
				      GSList *vbl);
gpointer g_snmp_session_async_get    (GSnmpSession *session,
				      GSList *vbl);
gpointer g_snmp_session_async_getnext(GSnmpSession *session,
				      GSList *vbl);
gpointer g_snmp_session_async_getbulk(GSnmpSession *session,
				      GSList *vbl,
				      guint32 nonrep,
				      guint32 maxrep);

GSList* g_snmp_session_sync_set      (GSnmpSession *session,
				      GSList *vbl);
GSList* g_snmp_session_sync_get      (GSnmpSession *session,
				      GSList *vbl);
GSList* g_snmp_session_sync_getnext  (GSnmpSession *session,
				      GSList *vbl);
GSList* g_snmp_session_sync_getbulk  (GSnmpSession *session,
				      GSList *vbl,
				      guint32 nonrep,
				      guint32 maxrep);

typedef struct _snmp_request {
  gboolean            (*callback) ();
  void                (*timeout) ();
  GSnmpSession        *session;
  GString             *auth;
  GSnmpPdu             pdu;
  struct sockaddr     *address;
  guint                domain;
  time_t               time;
  guint                retries;
  guint                timeoutval;
  GSnmpVersion         version;
  gpointer             magic;
} snmp_request;


snmp_request*	g_snmp_request_new();
void		g_snmp_request_destroy(snmp_request *request);

void		g_snmp_request_queue(snmp_request *request);
void		g_snmp_request_dequeue(snmp_request *request);
snmp_request*	g_snmp_request_find(gint32 request_id);

/*
 * Session API
 */

int g_snmp_timeout_cb        (gpointer    data);
void g_snmp_input_cb         (gpointer    data);

void g_session_response_pdu (guint messageProcessingModel,
  guint securityModel, GString *securityName, guint securityLevel, 
  GString *contextEngineID, GString *contextName, guint pduVersion,
  GSnmpPdu *PDU);

#endif

/* EOF */
