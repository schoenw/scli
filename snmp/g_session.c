/*
 * g_session.c -- session layer of the glib based snmp library
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

#include "g_snmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>

static GSList  *request_queue = NULL;   /* queue of active requests */

/*
 * Allocate a new session data structure.
 */

GSnmpSession*
g_snmp_session_new(GSnmpTDomain tdomain, gchar *hostname, guint16 port)
{
    GSnmpSession *session;

    session = g_malloc0(sizeof(GSnmpSession));
    session->tdomain = tdomain;
    session->taddress = hostname ? g_strdup(hostname) : NULL;
    session->port = port;
    session->retries = 3;
    session->timeout = 1;
    session->version = G_SNMP_V2C;

    if (! g_lookup_address(session->tdomain, session->taddress,
			   session->port, &session->address)) {
	if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	    g_printerr("session %p: lookup failed\n", session);
	}
	g_snmp_session_destroy(session);
	return NULL;
    }
    
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: new\n", session);
    }
    return session;
}

/*
 * Clone a session data structure.
 */

GSnmpSession*
g_snmp_session_clone(GSnmpSession *session)
{
    GSnmpSession *clone;

    clone = g_snmp_session_new(session->tdomain, session->taddress, session->port);
    clone->port    = session->port;
    clone->retries = session->retries;
    clone->timeout = session->timeout;
    clone->version = session->version;
    if (session->rcomm) {
	clone->rcomm = g_strdup(session->rcomm);
    }
    if (session->wcomm) {
	clone->wcomm = g_strdup(session->wcomm);
    }

    return clone;
}

/*
 * Destroy a session data structure.
 */

void
g_snmp_session_destroy(GSnmpSession *session)
{
    /* XXX delete all requests that refer to this session first */

    if (session->taddress) g_free(session->taddress);
    if (session->rcomm) g_free(session->rcomm);
    if (session->wcomm) g_free(session->wcomm);
    if (session->address) g_free(session->address);
    g_free(session);

    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: destroyed\n", session);
    }
}

/*
 * Allocate a new request data structure.
 */

GSnmpRequest*
g_snmp_request_new()
{
    GSnmpRequest *request;

    request = g_malloc0(sizeof(GSnmpRequest));
    request->auth = g_string_new(NULL);
    
    if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
	g_printerr("request %p: new\n", request);
    }

    return request;
}

/*
 * Destroy a request data structure.
 */

void
g_snmp_request_destroy(GSnmpRequest *request)
{
    g_return_if_fail(request);
    
    if (request->auth) {
	g_string_free(request->auth, 1);
    }
    g_free(request);

    if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
	g_printerr("request %p: destroyed\n", request);
    }
}

/*
 * Add a request to the global queue of outstanding requests.
 * XXX This is not thread-safe.
 */

void
g_snmp_request_queue(GSnmpRequest *request)
{
    g_return_if_fail(request);
    
    request_queue = g_slist_append(request_queue, request);
    if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
	g_printerr("request %p: queued\n", request);
    }
}

/*
 * Remove a request from the global queue of outstanding requests.
 * XXX This is not thread-safe.
 */

void
g_snmp_request_dequeue(GSnmpRequest *request)
{
    g_return_if_fail(request);

    request_queue = g_slist_remove(request_queue, request);
    if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
	g_printerr("request %p: dequeued\n", request);
    }
}

/*
 * Find the request with a given request id in the global queue of
 * outstanding requests.
 * XXX This is not thread-safe.
 */

GSnmpRequest*
g_snmp_request_find(gint32 id)
{
    GSList *elem;

    for (elem = request_queue; elem; elem = g_slist_next(elem)) {
	GSnmpRequest *request = (GSnmpRequest *) elem->data;
	if (request->pdu.request.id == id) {
	    if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
		g_printerr("request %p: found\n", request);
	    }
	    return request;
	}
    }

    return NULL;
}


/* 
 * query/set one mib from a snmp host
 *
 * host    -- Host info in question
 * callback-- Pointer to function that will handle the reply 
 *
 */

/* Asynchronous SNMP functions */

static gpointer
g_async_send(GSnmpSession *session, GSnmpPduType type,
	     GSList *objs, guint32 arg1, guint32 arg2)
{
    GSnmpRequest *request;
    time_t        now;
    int           model = 0, pduv = 0;
    static gint32 id = -1;
    
    if (id < 0) {
	id = random();
    }
    
    now = time(NULL);

#ifdef SNMP_DEBUG
    printf("g_async_send for %s\n", host->name);
#endif

    session->error_status = G_SNMP_ERR_NOERROR;
    session->error_index = 0;
    
    request = g_snmp_request_new();
    request->callback = session->done_callback;
    request->timeout  = session->time_callback;
    request->pdu.request.id           = id++;
    request->pdu.request.error_status = arg1;
    request->pdu.request.error_index  = arg2;
    request->pdu.request.variables    = objs;
    if (type == G_SNMP_PDU_SET) {
	request->auth = g_string_append(request->auth, session->wcomm);
    } else {
	request->auth = g_string_append(request->auth, session->rcomm);
    }
    request->pdu.type	            = type;
    request->retries                = session->retries;
    request->timeoutval             = session->timeout;
    request->magic                  = session->magic;
    request->version                = session->version;
    request->tdomain                = session->tdomain;
    request->taddress               = session->taddress;
    request->address                = session->address;
    request->session                = session;
    request->time                   = now + request->timeoutval;

    switch (request->version) {
    case 0: 
	model = PMODEL_SNMPV1;
	pduv  = PDUV1;
	break;
    case 1: 
	model = PMODEL_SNMPV2C;
	pduv  = PDUV2;
	break;
    case 3: 
	model = PMODEL_SNMPV3;
	pduv  = PDUV2;
	break;
    default:
	g_assert_not_reached();
    }
#ifdef SNMP_DEBUG 
    printf("sending Pdu for %s, version %d\n", session->name, request->version);
#endif
    sendPdu(request->tdomain, request->address, model, SMODEL_ANY, 
	    request->auth, SLEVEL_NANP, NULL, NULL, pduv, &request->pdu, TRUE);
    
    g_snmp_request_queue(request);
    
    return request;
}

gpointer
g_snmp_session_async_set(GSnmpSession *session, GSList *pdu)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_async_set pdu %p\n", session, pdu);
    }
    return g_async_send(session, G_SNMP_PDU_SET, pdu, 0, 0);
}

gpointer
g_snmp_session_async_get(GSnmpSession *session, GSList *pdu)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_async_get pdu %p\n", session, pdu);
    }
    return g_async_send(session, G_SNMP_PDU_GET, pdu, 0, 0);
}

gpointer
g_snmp_session_async_getnext(GSnmpSession *session, GSList *pdu)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_async_getnext pdu %p\n", session, pdu);
    }
    return g_async_send(session, G_SNMP_PDU_NEXT, pdu, 0, 0);
}

gpointer
g_snmp_session_async_getbulk(GSnmpSession *session, GSList *pdu,
			     guint32 nonrep, guint32 maxrep)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_async_getbulk pdu %p\n", session, pdu);
    }
    return g_async_send(session, G_SNMP_PDU_BULK, pdu, nonrep, maxrep);
}

/* Synchronous SNMP functions */

struct inputcb {
  int sock_nr;
  void (*receiveMessage)();
};

struct syncmagic {
    GMainLoop *loop;
    GSList *result;
};

static void
cb_time(GSnmpSession *session, void *magic)
{
    struct syncmagic *sm = (struct syncmagic *) magic;
    sm->result = NULL;
    session->error_index = 0;
    session->error_status = G_SNMP_ERR_NORESPONSE;
#ifdef SNMP_DEBUG
    g_print("cb_time: Quit loop %p\n", sm->loop);
#endif
    g_main_quit(sm->loop);
}

static gboolean
cb_done(GSnmpSession *session, GSnmpPdu *spdu, GSList *objs, gpointer magic)
{
    struct syncmagic *sm = (struct syncmagic *) magic;
    sm->result = objs;
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: error-status = %d, error-index = %d\n",
		   session, session->error_status, session->error_index);
    }
    g_main_quit(sm->loop);
    return FALSE;
}

static GSList *
g_sync_send(GSnmpSession *session, GSnmpPduType type,
	    GSList *objs, guint32 arg1, guint32 arg2)
{
    struct syncmagic * magic;
    GSList *result;
    
    magic = (struct syncmagic *) g_malloc(sizeof(struct syncmagic));
    magic->loop = g_main_new(TRUE);
    
    session->done_callback = cb_done;
    session->time_callback = cb_time;
    session->magic = magic;
    if (! g_async_send(session, type, objs, arg1, arg2)) {
	if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	    g_printerr("session %p: g_sync_send failed to send PDU\n", session);
	}
	g_main_destroy(magic->loop);
	g_free(magic);
	return NULL;
    }
    
    while(g_main_is_running(magic->loop)) {
	g_main_run(magic->loop);
    }
    g_main_destroy(magic->loop);
    result = magic->result;
    g_free(magic);
    return result;
}

GSList *
g_snmp_session_sync_set(GSnmpSession *session, GSList *pdu)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_sync_set pdu %p\n", session, pdu);
    }
    return g_sync_send(session, G_SNMP_PDU_SET, pdu, 0, 0);
}

GSList *
g_snmp_session_sync_get(GSnmpSession *session, GSList *pdu)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_sync_get pdu %p\n", session, pdu);
    }
    return g_sync_send(session, G_SNMP_PDU_GET, pdu, 0, 0);
}

GSList *
g_snmp_session_sync_getnext(GSnmpSession *session, GSList *pdu)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_sync_getnext pdu %p\n", session, pdu);
    }
    return g_sync_send(session, G_SNMP_PDU_NEXT, pdu, 0, 0);
}

GSList *
g_snmp_session_sync_getbulk(GSnmpSession *session, GSList *pdu,
			    guint32 nonrep, guint32 maxrep)
{
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: g_sync_getbulk pdu %p\n", session, pdu);
    }
    return g_sync_send(session, G_SNMP_PDU_BULK, pdu, nonrep, maxrep);
}

#if 0
gboolean
g_pdu_add_oid(GSList **pdu, guint32 *myoid, guint mylength,
	      GSnmpVarBindType type, gpointer value)
{
  GSnmpVarBind *obj;

  obj = g_snmp_varbind_new(myoid, mylength, type, value, -1);
  if (! obj) {
      return FALSE;
  }
  *pdu = g_slist_append(*pdu, obj);
  return TRUE;
}
#endif

#if 0
/* This should be nuked once the new parser and mib module are available.
   For now, either use this or the print function in struct tree          */

void 
g_snmp_printf(char *buf, int buflen, GSnmpVarBind *obj)
{
  int i;
  /*
   * Changed all the sprintf's to snprintf, paranoid I know but
   * I'd rather not get caught with any buffer overflows..
   */
  switch(obj->type)
    {
      case G_SNMP_INTEGER32:
        g_snprintf(buf, buflen, "%d", obj->syntax.i32[0]);
        break;
      case G_SNMP_COUNTER32:
      case G_SNMP_UNSIGNED32:
        g_snprintf(buf, buflen, "%u", obj->syntax.ui32[0]);
        break;
      case G_SNMP_TIMETICKS:
	/* replaced this duplicated code with a call to existing code */
	/* timetick_string (obj->syntax.ul[0], buf); */
        g_snprintf(buf, buflen, "%u", obj->syntax.ui32[0]);
        break;
      case G_SNMP_OCTET_STRING:
      case G_SNMP_OPAQUE:
        /* xxx fix this (data is not necessarily printable) */
        memcpy(buf, obj->syntax.uc,
	       obj->syntax_len > buflen ? buflen: obj->syntax_len);
	buf[obj->syntax_len > buflen ? buflen: obj->syntax_len] = '\0';
        break;
      case G_SNMP_IPADDRESS:
        if (obj->syntax_len == 4) /* IPv4 */
          g_snprintf(buf, buflen, "%d.%d.%d.%d", obj->syntax.uc[0],
                                               obj->syntax.uc[1],
                                               obj->syntax.uc[2],
                                               obj->syntax.uc[3]);
        break;
      case G_SNMP_OBJECT_ID:
        g_snprintf(buf, buflen, "%u", obj->syntax.ui32[0]);
        i=1;
        while(i < obj->syntax_len / sizeof(guint32))
          g_snprintf(buf+strlen(buf), buflen-strlen(buf), ".%u", 
                   obj->syntax.ui32[i++]);
        break;
      case G_SNMP_COUNTER64:
        g_snprintf(buf, buflen, "%llu", obj->syntax.ui64[0]);
	break;
      case G_SNMP_NULL:
        g_snprintf(buf, buflen, "<null>");
        break;
      case G_SNMP_NOSUCHOBJECT:
        g_snprintf(buf, buflen, "<nosuchobject>");
        break;
      case G_SNMP_NOSUCHINSTANCE:
        g_snprintf(buf, buflen, "<nosuchinstance>");
        break;
      case G_SNMP_ENDOFMIBVIEW:
        g_snprintf(buf, buflen, "<endofmibview>");
        break;
    }
}
#endif

/*
 * The low level callbacks
 */

int
g_snmp_timeout_cb (gpointer data)
{
    GSList       *mylist;
    time_t        now;
    GSnmpRequest *request;
    int           model = 0, pduv = 0;
    
  again:
    now = time(NULL);
    mylist = request_queue;
    
    while (mylist) {
	request = (GSnmpRequest *) mylist->data;
	mylist = mylist->next;
	if (request->time <= now) {
	    if (request->retries) {
		request->retries--;
		request->time = now + request->timeoutval;
		/* 
		 * Again what happens on a -1 return to sendto
		 */
		switch (request->version) {
		case G_SNMP_V1: 
		    model = PMODEL_SNMPV1;
		    pduv  = PDUV1;
		    break;
		case G_SNMP_V2C: 
		    model = PMODEL_SNMPV2C;
		    pduv  = PDUV2;
		    break;
		case G_SNMP_V3: 
		    model = PMODEL_SNMPV3;
		    pduv  = PDUV2;
		    break;
		}
		
		sendPdu(request->tdomain, request->address, model, SMODEL_ANY, 
			request->auth, SLEVEL_NANP, NULL, NULL, pduv, 
			&request->pdu, TRUE);
	    } else {
		g_snmp_request_dequeue(request);
		if (request->timeout) {
		    if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
			g_printerr("request %p: timeout callback invoked\n",
				   request);
		    }
		    request->timeout(request->session, request->magic);
		}
		g_snmp_request_destroy(request);
		goto again;
	    }
	}
    }
    return TRUE;
}

void
g_session_response_pdu(guint messageProcessingModel,
		       guint securityModel,
		       GString *securityName,
		       guint securityLevel, 
		       GString *contextEngineID,
		       GString *contextName,
		       guint pduVersion,
		       GSnmpPdu *PDU)
{
    GSList       *vbl;
    GSnmpRequest *request;

    if (PDU->type == G_SNMP_PDU_TRAP1) {
	vbl = PDU->trap.variables;
    } else {
	vbl = PDU->request.variables;
    }

    request = g_snmp_request_find(PDU->request.id);
    if (! request) {
	g_snmp_vbl_free(vbl);
	return;
    }
    
    /* XXX this needs to be generalized I think */
    
    if (memcmp(securityName->str, request->auth->str, securityName->len)) {
	g_snmp_vbl_free(vbl);
	return;
    }

    g_snmp_request_dequeue(request);
    request->session->error_status = PDU->request.error_status;
    request->session->error_index = PDU->request.error_index;
    if (! request->callback) {
	g_snmp_vbl_free(vbl);
	g_snmp_request_destroy(request);
	return;
    }

    if (request->callback(request->session, PDU, vbl, request->magic)) {
	if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
	    g_printerr("request %p: callback invoked\n", request);
	}
	/* g_snmp_vbl_free(vbl); */
    }
    g_snmp_request_destroy(request);
}

/* EOF */
