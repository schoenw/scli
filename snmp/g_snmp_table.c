/*
 * g_snmp_table.c -- table layer of the glib based snmp library
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

static gboolean
g_snmp_table_done_callback(GSnmpSession *session, gpointer data, 
                           GSnmpPdu *spdu, GSList *objs)
{
    GSnmpTable   *table;
    GSList       *nobjs; /* New list of objects for next query */
    GSnmpVarBind *cobj;  /* Current object being processed */
    GSnmpVarBind *obj;   /* Base object being processed */
    GSnmpVarBind *nobj;  /* New NULL object for next query */
    GHashTable   *otable;
    int           rows;
    int           i,j, *p;
    guint32       index[SNMP_SIZE_OBJECTID];
    int           index_len;
    
    session->error_status = spdu->request.error_status;
    session->error_index = spdu->request.error_index;
    
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: error-status = %d, error-index = %d\n",
		   session, session->error_status, session->error_index);
    }
    
    table = (GSnmpTable *) data;
    table->request = 0;
    
  rows = g_slist_length(table->objs);
  if (spdu->request.error_status == G_SNMP_ERR_NOSUCHNAME) {
      if (table->cb_finish)
        table->cb_finish(table->data);
      else
        g_snmp_table_destroy(table);
      return TRUE;
  }
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
    GSnmpTable *table;
    
    table = (GSnmpTable *) data;
    table->request = 0;
    if (table->cb_error) {
	table->cb_error(table->data);
    } else {
	g_snmp_table_destroy(table);
    }

    session->error_index = 0;
    session->error_status = G_SNMP_ERR_NORESPONSE;
}


GSnmpTable *
g_snmp_table_new(GSnmpSession *session, GSList *objs, 
		 void (* cb_error)(), void (* cb_row)(), void (* cb_finish)(),
		 gpointer data)
{
    GSList *elem;
    GSnmpTable *table;

    table          = g_malloc0(sizeof(GSnmpTable));

    table->session = g_snmp_session_clone(session);
    table->session->magic = table;
    table->session->done_callback = g_snmp_table_done_callback;
    table->session->time_callback = g_snmp_table_time_callback;
    
    for (elem = objs; elem; elem = g_slist_next(elem)) {
	GSnmpVarBind *obj = (GSnmpVarBind *) elem->data;
	g_snmp_vbl_add_null(&table->objs, obj->id, obj->id_len);
    }
    table->data = data;
    
    table->cb_error  = cb_error;
    table->cb_row    = cb_row;
    table->cb_finish = cb_finish;
    
    return table;
}


void
g_snmp_table_get(GSnmpTable *table)
{
    table->request = g_snmp_session_async_getnext(table->session, table->objs);
}


void
g_snmp_table_destroy(GSnmpTable *table)
{
    if (table->request) {
	g_snmp_request_dequeue(table->request);
	g_snmp_request_destroy(table->request);
    }
    g_snmp_vbl_free(table->objs);
    g_snmp_session_destroy(table->session);
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
    GSnmpTable *table;
    GSList *tablelist = NULL;

    table = g_snmp_table_new(s, in, cb_error, cb_row, cb_finish, &tablelist);

    g_snmp_table_get(table);

    loop = g_main_new(TRUE);
    while (loop && g_main_is_running(loop)) {
	g_main_run(loop);
    }
    g_main_destroy(loop);
    loop = NULL;

    s->error_status = table->session->error_status;
    s->error_index = table->session->error_index;

    g_snmp_table_destroy(table);
    
    return tablelist;
}

