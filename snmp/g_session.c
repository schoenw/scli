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
 * Snmp session support
 */

#ifndef lint
static char const copyright[] =
"@(#) Copyright (c) 1998 Gregory McLean & Jochen Friedrich";
#endif
static char const rcsid[] =
"$Id$";

#include "g_snmp.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>                   /* Quite the memmove warning */

extern int     errno;

static GSList  *rq_list     = NULL;   /* track the active requests */
static gint     id          = 1;      /* SNMP request id */

/*
 * lookup address of node and set port number or default.
 * Maybe this one should be nuked completely. gnome has a nice async
 * dns helper and the collector might use cached IP addresses for speedup
 * anyways.
 *
 */

gboolean
g_setup_address (host_snmp *host)
{
  if (!g_lookup_address(host->domain, host->name, &host->address))
    return FALSE;
 
  return TRUE;
}

/* 
 * query/set one mib from a snmp host
 *
 * host    -- Host info in question
 * callback-- Pointer to function that will handle the reply 
 *
 */

/* Asynchronous SNMP functions */

gpointer
g_async_send (host_snmp *host, GSnmpPduType type,
	      GSList *objs, guint arg1, guint arg2)
{
  snmp_request * request;
  time_t         now;
  int            model = 0, pduv = 0;

  now = time(NULL);

#ifdef SNMP_DEBUG
  printf("g_async_send for %s\n", host->name);
#endif
  request = g_malloc(sizeof(snmp_request));
#ifdef SNMP_DEBUG
  printf("New request: %p\n", request);
#endif

  if (host->done_callback)
    request->callback = host->done_callback;
  else
    request->callback = NULL;

  if (host->time_callback)
    request->timeout  = host->time_callback;
  else
    request->timeout  = NULL;

  if (!g_setup_address(host))
    {
      g_free(request);
      return NULL;
    }

  request->pdu.request.id           = id++;
  request->pdu.request.error_status = arg1;
  request->pdu.request.error_index  = arg2;
  request->pdu.request.variables    = objs;

  if (type == G_SNMP_PDU_SET)
    {
      request->auth=g_string_new(host->wcomm);
    }
  else
    {
      request->auth=g_string_new(host->rcomm);
    }

  request->pdu.type	            = type;
  request->retries                  = host->retries;
  request->timeoutval               = host->timeout;
  request->magic                    = host->magic;
  request->version                  = host->version;
  request->domain                   = host->domain;
  request->address                  = host->address;
  request->host                     = host;
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
        printf("Unknown version!!!\n");
    }
#ifdef SNMP_DEBUG 
  printf("sending Pdu for %s, version %d\n", host->name, request->version);
#endif
  sendPdu(request->domain, request->address, model, SMODEL_ANY, 
          request->auth, SLEVEL_NANP, NULL, NULL, pduv, &request->pdu, TRUE);

  rq_list = g_slist_append(rq_list, request);

  return request;
}

gpointer
g_async_get (host_snmp *host, GSList *pdu)
{
  return g_async_send(host, G_SNMP_PDU_GET, pdu, 0, 0);
}

gpointer
g_async_getnext (host_snmp *host, GSList *pdu)
{
  return g_async_send(host, G_SNMP_PDU_NEXT, pdu, 0, 0);
}

gpointer
g_async_bulk (host_snmp *host, GSList *pdu, guint nonrep, guint maxiter)
{
  return g_async_send(host, G_SNMP_PDU_BULK, pdu, nonrep, maxiter);
}

gpointer
g_async_set (host_snmp *host, GSList *pdu)
{
  return g_async_send(host, G_SNMP_PDU_SET, pdu, 0, 0);
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
cb_time(host_snmp *host, void *magic)
{
  struct syncmagic *sm = (struct syncmagic *) magic;
  sm->result = NULL;
#ifdef SNMP_DEBUG
  g_print("cb_time: Quit loop %p\n", sm->loop);
#endif
  g_main_quit(sm->loop);
}

static gboolean
cb_done (host_snmp *host, void *magic, GSnmpPdu *spdu, GSList *objs)
{
  struct syncmagic *sm = (struct syncmagic *) magic;
  sm->result = objs;
#ifdef SNMP_DEBUG
  g_print("cb_done: Quit loop %p\n", sm->loop);
#endif
  g_main_quit(sm->loop);
  return FALSE;
}

GSList *
g_sync_send (host_snmp *host, GSnmpPduType type,
	     GSList *objs, guint arg1, guint arg2)
{
  struct syncmagic * magic;
  GSList *result;

  magic = (struct syncmagic *) g_malloc(sizeof(struct syncmagic));
  magic->loop = g_main_new(TRUE);
#ifdef SNMP_DEBUG
  g_print("g_sync_send: New loop %p\n", magic->loop);
#endif
  host->done_callback = cb_done;
  host->time_callback = cb_time;
  host->magic = magic;
  if (!g_async_send (host, type, objs, arg1, arg2))
    {
#ifdef SNMP_DEBUG
      g_print("g_sync_send: error in async_send. Free loop %p\n", magic->loop);
#endif
      g_main_destroy(magic->loop);
      g_free(magic);
      return NULL;
    }

  while(g_main_is_running(magic->loop))
    {
      g_main_run(magic->loop);
    }
#ifdef SNMP_DEBUG
    g_print("g_sync_send: Free loop %p\n", magic->loop);
#endif
    g_main_destroy(magic->loop);

  result = magic->result;
  g_free(magic);
  return result;
}

GSList *
g_sync_get (host_snmp *host, GSList *pdu)
{
  return g_sync_send(host, G_SNMP_PDU_GET, pdu, 0, 0);
}

GSList *
g_sync_getnext (host_snmp *host, GSList *pdu)
{
  return g_sync_send(host, G_SNMP_PDU_NEXT, pdu, 0, 0);
}

GSList *
g_sync_bulk (host_snmp *host, GSList *pdu, guint nonrep, guint maxiter)
{
  return g_sync_send(host, G_SNMP_PDU_BULK, pdu, nonrep, maxiter);
}

GSList *
g_sync_set (host_snmp *host, GSList *pdu)
{
  return g_sync_send(host, G_SNMP_PDU_SET, pdu, 0, 0);
}

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

/*
 * The request queue functions
 */

snmp_request *
g_find_request (guint reqid)
{
  GSList       * list;
  snmp_request * retval;

  list = rq_list;
  while(list)
    {
      retval = (snmp_request *) list->data;
      if(retval->pdu.request.id == reqid)
	  return retval;
      list = list->next;
    }
  return NULL;
}

gboolean
g_remove_request (snmp_request *request)
{
#ifdef SNMP_DEBUG
  printf("Removing request: %p\n", request);
#endif
  rq_list = g_slist_remove(rq_list, request);
  g_free(request);
  return TRUE;
}

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
  mylist = rq_list;

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
              rq_list = g_slist_remove(rq_list, request);
              if (request->timeout)
                {
#ifdef SNMP_DEBUG
                   printf("Calling time callback for request: %p\n", request);
#endif
                   request->timeout(request->host, request->magic);
                }
              g_free(request);
              goto again;
            }
        }
    }
  return TRUE;
}

void
g_session_response_pdu (guint messageProcessingModel,
  guint securityModel, GString *securityName, guint securityLevel, 
  GString *contextEngineID, GString *contextName, guint pduVersion,
  GSnmpPdu *PDU)
{
  GSList             *objs;
  snmp_request       *request;

  if (PDU->type == G_SNMP_PDU_TRAP1)
    objs = PDU->trap.variables;
  else
    objs = PDU->request.variables;
  if ((request = g_find_request(PDU->request.id)))
    {
      if (memcmp(securityName->str, request->auth->str, securityName->len))
        {
          g_slist_free(objs);
          return;
        }
      rq_list = g_slist_remove(rq_list, request);
      request->host->status = PDU->request.error_status;
      if (request->callback)
        {
#ifdef SNMP_DEBUG
          printf("Calling done callback for request: %p\n", request);
#endif
          if (request->callback(request->host, request->magic, PDU, objs))
            g_slist_free(objs);
        }
      else  
        g_slist_free(objs);
      g_free(request);
    }
  else
    g_slist_free(objs);
}

/* EOF */
