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

#include "g_snmp.h"

static gboolean
g_snmp_table_done_callback(GSnmpSession *session, gpointer data, 
                           GSnmpPdu *spdu, GSList *objs)
{
  Gsnmp_table  * table;
  GSList       * nobjs; /* New list of objects for next query */
  GSnmpVarBind * cobj;  /* Current object being processed */
  GSnmpVarBind * obj;   /* Base object being processed */
  GSnmpVarBind * nobj;  /* New NULL object for next query */
  GHashTable   * otable;
  int           rows;
  int           i,j, *p;
  guint         index[SNMP_SIZE_OBJECTID];
  int           index_len;

  table = (Gsnmp_table *) data;
  table->request = 0;
  rows = g_slist_length(table->objs);
/* We got error back. */
  if (spdu->request.error_status)
    {
      if (table->cb_error)
        table->cb_error(table->data);
      else
        g_snmp_table_destroy(table);  
      return TRUE;
    }
/* Check if the number of requested variables matches the number of returned
   variables */
  if (g_slist_length(objs) != rows)
    {
      if (table->cb_error)
        table->cb_error(table->data);
      else
        g_snmp_table_destroy(table);  
      return TRUE;
    }
  index_len = 0;
/* Search smallest index in all valid returned columns. */
  for (i=0; i<rows; i++)
    {
      obj  = (GSnmpVarBind *) g_slist_nth_data(table->objs, i);
      cobj = (GSnmpVarBind *) g_slist_nth_data(objs, i);
      if (cobj->id_len >= obj->id_len
	  && !memcmp (cobj->id, obj->id, obj->id_len * sizeof (guint32)))
        {
          if (!index_len)
            {
              index_len = cobj->id_len - obj->id_len;
              g_memmove(index, cobj->id+obj->id_len, 
                        index_len * sizeof (guint32));
            }
          else
            {
              if ((j=memcmp(index, cobj->id+obj->id_len, 
                            MIN(index_len, cobj->id_len - obj->id_len)
                            * sizeof (guint32))))
                {
		    /* g_warning("Non-regular SNMP table"); (js) */
                  if (j>0)
                    {
                       index_len = cobj->id_len - obj->id_len;
                       g_memmove(index, cobj->id+obj->id_len,
                                 index_len * sizeof (guint32));
                    }
                }
              if (cobj->id_len - obj->id_len < index_len)
                {
                  g_warning("SNMP table index length changed");
                  index_len = cobj->id_len - obj->id_len;
                }
            }
        }
    }
/* If no valid columns found, table query must be finished. */
  if (!index_len)
    {
      if (table->cb_finish)
        table->cb_finish(table->data);
      else
        g_snmp_table_destroy(table);
      return TRUE;
    }
/* Build hash for callback and construct query for next row. */
  otable = g_hash_table_new(g_int_hash, g_int_equal);
  nobjs = NULL;
  for (i=0; i<rows; i++)
    {
      obj  = (GSnmpVarBind *) g_slist_nth_data(table->objs, i);
      cobj = (GSnmpVarBind *) g_slist_nth_data(objs, i);
      if (!memcmp (cobj->id, obj->id, obj->id_len * sizeof (guint32)))
        {
          if (cobj->id_len - obj->id_len == index_len)
            if (!memcmp(cobj->id + obj->id_len, index, 
                        index_len * sizeof (guint32)))
              {
                p = g_malloc(sizeof(int));
                *p = i;
                g_hash_table_insert(otable, p, cobj);
              }
        }
      nobj             = g_malloc0(sizeof(GSnmpVarBind));
      nobj->type       = G_SNMP_NULL;
      nobj->syntax_len = 0;
      nobj->id_len     = obj->id_len + index_len;
      nobj->id         = g_malloc(nobj->id_len * sizeof(guint32));
      g_memmove (nobj->id, obj->id, obj->id_len * sizeof(guint32));
      g_memmove (nobj->id + obj->id_len, index, index_len * sizeof(guint32));
      nobjs            = g_slist_append(nobjs, nobj);
    }
  if (table->cb_row)
    table->cb_row(otable, index_len, table->data);
  g_hash_table_destroy(otable);
  table->request = g_snmp_session_async_getnext(table->session, nobjs);
  return TRUE;
}  


static void
g_snmp_table_time_callback(GSnmpSession *session, gpointer data)
{
    Gsnmp_table * table;
    
    table = (Gsnmp_table *) data;
    table->request = 0;
    if (table->cb_error) {
	table->cb_error(table->data);
    } else {
	g_snmp_table_destroy(table);
    }
}


Gsnmp_table *
g_snmp_table_new(GSnmpSession *session, GSList *objs, 
		 void (* cb_error)(), void (* cb_row)(), void (* cb_finish)(),
		 gpointer data)
{
    GSList *elem;
    Gsnmp_table *table;

    table          = g_malloc0(sizeof(Gsnmp_table));
    table->session = g_malloc0(sizeof(GSnmpSession));
    
    table->session->domain  = session->domain;
    table->session->rcomm   = session->rcomm;
    table->session->wcomm   = session->wcomm;
    table->session->retries = session->retries;
    table->session->name    = session->name;
    table->session->error_status  = 0;
    table->session->port    = session->port;
    table->session->timeout = session->timeout;
    table->session->version = session->version;
    table->session->magic   = table;
    
    table->session->done_callback = g_snmp_table_done_callback;
    table->session->time_callback = g_snmp_table_time_callback;
    
    for (elem = objs; elem; elem = g_slist_next(elem)) {
	GSnmpVarBind *obj, *nobj;
	obj  = (GSnmpVarBind *) elem->data;
	nobj = g_snmp_varbind_new(obj->id, obj->id_len, G_SNMP_NULL, NULL, 0);
	table->objs = g_slist_append(table->objs, nobj);
    }
    table->data = data;
    
    table->cb_error  = cb_error;
    table->cb_row    = cb_row;
    table->cb_finish = cb_finish;
    
    return table;
}


void
g_snmp_table_get(Gsnmp_table *table)
{
    table->request = g_snmp_session_async_getnext(table->session, table->objs);
}


void
g_snmp_table_destroy(Gsnmp_table *table)
{
    GSList *elem;
    
    if (table->request) {
	g_snmp_request_dequeue(table->request);
	g_snmp_request_destroy(table->request);
    }
    for (elem = table->objs; elem; elem = g_slist_next(elem)) {
	g_snmp_varbind_free((GSnmpVarBind *) elem->data);
    }
    g_slist_free(table->objs);
    g_free(table->session);
    g_free(table);
}

/*
 * Another entry point which is used by the scli package.
 */

static GMainLoop *loop = NULL;


static void
cb_finish(gpointer *data)
{
    if (loop) g_main_quit(loop);
}

static void
cb_error(gpointer *data)
{
    if (loop) g_main_quit(loop);
}

static void
append_elem(gpointer key, gpointer value, gpointer user_data)
{
    GSList **list = (GSList **) user_data;
    
    GSnmpVarBind *obj = (GSnmpVarBind *) value;

    *list = g_slist_append(*list, obj);

    if (obj->type == G_SNMP_ENDOFMIBVIEW) {
	cb_finish(user_data);
	return;
    }
}



static void
cb_row(GHashTable *table, int index_len, gpointer *data)
{
    GSList *rowlist = NULL;
    GSList **tablelist = (GSList **) data;

    g_hash_table_foreach(table, append_elem, &rowlist);

    *tablelist = g_slist_append(*tablelist, rowlist);
}


GSList *
gsnmp_gettable(GSnmpSession *s, GSList *in)
{
    Gsnmp_table *table;
    GSList *tablelist = NULL;

    table = g_snmp_table_new(s, in, cb_error, cb_row, cb_finish, &tablelist);

    g_snmp_table_get(table);

    loop = g_main_new(TRUE);
    while (loop && g_main_is_running(loop)) {
	g_main_run(loop);
    }
    g_main_destroy(loop);
    loop = NULL;

    g_snmp_table_destroy(table);
    
    return tablelist;
}

