/*
 * g_session.h -- session layer of the glib based snmp library
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
 * Foundation, Inc.,  59 Temple Place - Suite 330, Cambridge, MA 02139, USA.
 *
 * $Id$
 */

#ifndef _G_SESSION_H_
#define _G_SESSION_H_

/*
 * Basic snmp info on a per session basis. Note that status
 * information of the last SNMP interaction is returned to the
 * application as part of the session structure. (!)
 */

typedef struct _GSnmpSession {
    struct sockaddr *address;
    GSnmpTDomain  tdomain;
    gchar        *taddress;
    guint16       port;
    gchar        *rcomm;
    gchar        *wcomm;
    guint         retries;
    gint32        error_status;
    guint32	  error_index;
    guint         timeout;
    GSnmpVersion  version;
    gboolean      (*done_callback) (); /* what to call when complete */
    void          (*time_callback) (); /* what to call on a timeout */
    gpointer      magic;               /* additional data for callbacks */
} GSnmpSession;

GSnmpSession*	g_snmp_session_new(GSnmpTDomain domain, gchar *address, guint16 port);
GSnmpSession*	g_snmp_session_clone(GSnmpSession *s);
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

typedef struct _GSnmpRequest {
    gboolean            (*callback) ();
    void                (*timeout) ();
    GSnmpSession        *session;
    GString             *auth;
    GSnmpPdu             pdu;
    struct sockaddr	*address;
    GSnmpTDomain         tdomain;
    gchar               *taddress;
    time_t               time;
    guint                retries;
    guint                timeoutval;
    GSnmpVersion         version;
    gpointer             magic;
} GSnmpRequest;


GSnmpRequest*	g_snmp_request_new(void);
void		g_snmp_request_destroy(GSnmpRequest *request);

void		g_snmp_request_queue(GSnmpRequest *request);
void		g_snmp_request_dequeue(GSnmpRequest *request);
GSnmpRequest*	g_snmp_request_find(gint32 request_id);

/*
 * Session API - the stuff below needs to be cleaned up. XXX
 */

int g_snmp_timeout_cb        (gpointer    data);
void g_snmp_input_cb         (gpointer    data);

void g_session_response_pdu (guint messageProcessingModel,
  guint securityModel, GString *securityName, guint securityLevel, 
  GString *contextEngineID, GString *contextName, guint pduVersion,
  GSnmpPdu *PDU);

#endif /* _G_SESSION_H_ */
