/* 
 * stools.c -- library of MIB stub procedures
 *
 * Copyright (C) 2001 Juergen Schoenwaelder
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 * @(#) $Id$
 */

#include "stools.h"

#include <stdio.h>

static GMainLoop *loop = NULL;


static void
cb_finish(gpointer *data)
{
    if (loop) g_main_quit(loop);
}

static void
cb_error(gpointer *data)
{
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




char *
stls_table_get_value(stls_table_t *table, gint32 id)
{
    int i;

    for (i = 0; table[i].str; i++) {
	if (id == table[i].id) {
	    return table[i].str;
	}
    }

    return NULL;
}

gint32
stls_table_get_id(stls_table_t *table, char *str)
{
    int i;

    for (i = 0; table[i].str; i++) {
	if (strcmp(str, table[i].str) == 0) {
	    return table[i].id;
	}
    }

    return 0; /* xxx */
}

void
stls_vbl_add_null(GSList **vbl, guint32 const *oid, gsize const len)
{
    GSnmpVarBind *vb;

    vb = g_snmp_varbind_new(oid, len, G_SNMP_NULL, NULL, 0);
    *vbl = g_slist_append(*vbl, vb);
}

void
stls_vbl_free(GSList *vbl)
{
    GSList *elem;

    if (vbl) {
	for (elem = vbl; elem; elem = g_slist_next(elem)) {
	    g_snmp_varbind_free((GSnmpVarBind *) elem->data);
	}
	g_slist_free(vbl);
    }
}

GSList *
stls_snmp_getnext(host_snmp *s, GSList *vbl)
{
    return g_sync_getnext(s, vbl);
}

GSList *
stls_snmp_gettable(host_snmp *s, GSList *in)
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
