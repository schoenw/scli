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

#ifndef lint
static char const copyright[] =
"@(#) Copyright (c) 1998 Gregory McLean & Jochen Friedrich";
#endif
static char const rcsid[] =
"$Id$";

#include "g_snmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>                   /* Quite the memmove warning */

static GSList  *request_queue = NULL;   /* queue of active requests */

/*
 * lookup address of node and set port number or default.
 * Maybe this one should be nuked completely. gnome has a nice async
 * dns helper and the collector might use cached IP addresses for speedup
 * anyways.
 *
 */

gboolean
g_setup_address (GSnmpSession *session)
{
  if (!g_lookup_address(session->domain, session->name, &session->address))
    return FALSE;
 
  return TRUE;
}

/*
 * Allocate a new session data structure.
 */

GSnmpSession*
g_snmp_session_new()
{
    GSnmpSession *session;

    session = g_malloc0(sizeof(GSnmpSession));
    session->domain = G_SNMP_TDOMAIN_UDP_IPV4;
    session->name = "localhost";
    session->port = 161;
    session->retries = 3;
    session->timeout = 1;
    session->version = G_SNMP_V2C;

    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: new\n", session);
    }
    return session;
}

/*
 * Destroy a session data structure.
 */

void
g_snmp_session_destroy(GSnmpSession *session)
{
    /* XXX delete all requests that refer to this session first */

    if (session->name) g_free(session->name);
    if (session->rcomm) g_free(session->rcomm);
    if (session->address) g_free(session->address);
    g_free(session);

    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: destroyed\n", session);
    }
}

/*
 * Allocate a new request data structure.
 */

snmp_request*
g_snmp_request_new()
{
    snmp_request *request;

    request = g_malloc0(sizeof(snmp_request));
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
g_snmp_request_destroy(snmp_request *request)
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
g_snmp_request_queue(snmp_request *request)
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
g_snmp_request_dequeue(snmp_request *request)
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

snmp_request*
g_snmp_request_find(gint32 id)
{
    GSList *elem;

    for (elem = request_queue; elem; elem = g_slist_next(elem)) {
	snmp_request *request = (snmp_request *) elem->data;
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
  snmp_request *request;
  time_t        now;
  int           model = 0, pduv = 0;
  static gint32	id = -1;

  if (id < 0) {
      id = random();
  }

  now = time(NULL);

#ifdef SNMP_DEBUG
  printf("g_async_send for %s\n", host->name);
#endif
  request = g_snmp_request_new();

  if (session->done_callback)
    request->callback = session->done_callback;
  else
    request->callback = NULL;

  if (session->time_callback)
    request->timeout  = session->time_callback;
  else
    request->timeout  = NULL;

  if (!session->address) {
      if (!g_setup_address(session))
      {
	  g_snmp_request_destroy(request);
	  return NULL;
      }
  }

  request->pdu.request.id           = id++;
  request->pdu.request.error_status = arg1;
  request->pdu.request.error_index  = arg2;
  request->pdu.request.variables    = objs;

  if (type == G_SNMP_PDU_SET)
    {
      request->auth=g_string_append(request->auth, session->wcomm);
    }
  else
    {
      request->auth=g_string_append(request->auth, session->rcomm);
    }

  request->pdu.type	            = type;
  request->retries                  = session->retries;
  request->timeoutval               = session->timeout;
  request->magic                    = session->magic;
  request->version                  = session->version;
  request->domain                   = session->domain;
  request->address                  = session->address;
  request->session                  = session;
  request->time                     = now + request->timeoutval;

  switch (request->version)
    {
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
	g_printerr("Unknown protocol version!!!");
	g_snmp_request_destroy(request);
	return NULL;
    }
#ifdef SNMP_DEBUG 
  printf("sending Pdu for %s, version %d\n", session->name, request->version);
#endif
  sendPdu(request->domain, request->address, model, SMODEL_ANY, 
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
g_snmp_session_async_bulk(GSnmpSession *session, GSList *pdu,
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
#ifdef SNMP_DEBUG
  g_print("cb_time: Quit loop %p\n", sm->loop);
#endif
  g_main_quit(sm->loop);
}

static gboolean
cb_done (GSnmpSession *session, void *magic, GSnmpPdu *spdu, GSList *objs)
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
  if (!g_async_send(session, type, objs, arg1, arg2)) {
      if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	  g_printerr("session %p: g_sync_send failed to send PDU\n",
		     session);
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
g_snmp_session_sync_bulk(GSnmpSession *session, GSList *pdu,
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
  snmp_request *request;
  int           model = 0, pduv = 0;

#ifdef SNMP_DEBUG
  printf("SNMP Timeout called\n");
#endif

again:
  now = time(NULL);
  mylist = request_queue;

  while(mylist)
    {
      request = (snmp_request *) mylist->data;
      mylist = mylist->next;
      if (request->time <= now)
        {
          if (request->retries)
            {
              request->retries--;
              request->time = now + request->timeoutval;
	      /* 
               * Again what happens on a -1 return to sendto
	       */
              switch (request->version)
                {
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
 
              sendPdu(request->domain, request->address, model, SMODEL_ANY, 
                request->auth, SLEVEL_NANP, NULL, NULL, pduv, 
                &request->pdu, TRUE);
            }
          else
            {
		g_snmp_request_dequeue(request);
              if (request->timeout)
                {
#ifdef SNMP_DEBUG
                   printf("Calling time callback for request: %p\n", request);
#endif
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
    snmp_request *request;

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
    /* XXX what about the error index? */
    if (! request->callback) {
	g_snmp_vbl_free(vbl);
	g_snmp_request_destroy(request);
	return;
    }

    if (request->callback(request->session, request->magic, PDU, vbl)) {
	if (g_snmp_debug_flags & G_SNMP_DEBUG_REQUESTS) {
	    g_printerr("request %p: callback invoked\n", request);
	}
	/* g_snmp_vbl_free(vbl); */
    }
    g_snmp_request_destroy(request);
}

/* EOF */
