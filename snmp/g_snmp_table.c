#include "config.h"
#include <glib.h>
#include "g_snmp.h"

static gboolean
g_snmp_table_done_callback(host_snmp *host, gpointer data, 
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
      if (!memcmp (cobj->id, obj->id, obj->id_len * sizeof (gulong)))
        {
          if (!index_len)
            {
              index_len = cobj->id_len - obj->id_len;
              g_memmove(index, cobj->id+obj->id_len, 
                        index_len * sizeof (gulong));
            }
          else
            {
              if ((j=memcmp(index, cobj->id+obj->id_len, 
                            MIN(index_len, cobj->id_len - obj->id_len)
                            * sizeof (gulong))))
                {
                  g_warning("Non-regular SNMP table");
                  if (j>0)
                    {
                       index_len = cobj->id_len - obj->id_len;
                       g_memmove(index, cobj->id+obj->id_len,
                                 index_len * sizeof (gulong));
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
      if (!memcmp (cobj->id, obj->id, obj->id_len * sizeof (gulong)))
        {
          if (cobj->id_len - obj->id_len == index_len)
            if (!memcmp(cobj->id + obj->id_len, index, 
                        index_len * sizeof (gulong)))
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
      nobj->id         = g_malloc(nobj->id_len * sizeof(gulong));
      g_memmove (nobj->id, obj->id, obj->id_len * sizeof(gulong));
      g_memmove (nobj->id + obj->id_len, index, index_len * sizeof(gulong));
      nobjs            = g_slist_append(nobjs, nobj);
    }
  if (table->cb_row)
    table->cb_row(otable, index_len, table->data);
  table->request = g_async_getnext(table->host, nobjs);
  return TRUE;
}  

static void
g_snmp_table_time_callback(host_snmp *host, gpointer data)
{
  Gsnmp_table * table;

  table = (Gsnmp_table *) data;
  table->request = 0;
  if (table->cb_error)
    table->cb_error(table->data);
  else
    g_snmp_table_destroy(table);  
}

Gsnmp_table *
g_snmp_table_new (host_snmp *host, GSList *objs, 
                  void (* cb_error)(), void (* cb_row)(), void (* cb_finish)(),
                  gpointer data)
{
  Gsnmp_table * table;

  table       = g_malloc0(sizeof(Gsnmp_table));
  table->host = g_malloc0(sizeof(host_snmp));

  table->host->domain  = host->domain;
  table->host->rcomm   = host->rcomm;
  table->host->wcomm   = host->wcomm;
  table->host->retries = host->retries;
  table->host->name    = host->name;
  table->host->status  = 0;
  table->host->port    = host->port;
  table->host->timeout = host->timeout;
  table->host->version = host->version;
  table->host->magic   = table;

  table->host->done_callback = g_snmp_table_done_callback;
  table->host->time_callback = g_snmp_table_time_callback;

  table->objs = objs;
  table->data = data;

  table->cb_error  = cb_error;
  table->cb_row    = cb_row;
  table->cb_finish = cb_finish;

  return table;
}

void
g_snmp_table_get(Gsnmp_table *table)
{
  GSList *objs;
  GSList *cobj;
  GSnmpVarBind *obj;
  GSnmpVarBind *nobj;


  objs = NULL; 
  cobj = table->objs;
  while (cobj)
    {
      obj = (GSnmpVarBind *) cobj->data;
      nobj             = g_malloc0(sizeof(GSnmpVarBind));
      nobj->type       = G_SNMP_NULL;
      nobj->syntax_len = 0;
      nobj->id_len     = obj->id_len;
      nobj->id         = g_malloc(obj->id_len * sizeof(gulong));
      memmove (nobj->id, obj->id, obj->id_len * sizeof(gulong));
      objs             = g_slist_append(objs, nobj);
      cobj = cobj->next;
    }
  table->request = g_async_getnext(table->host, objs);
}

void
g_snmp_table_destroy(Gsnmp_table *table)
{
  if (table->request)
    g_remove_request(table->request);
  g_slist_free(table->objs);
  g_free(table->host);
  g_free(table);
}
