/*
 * g_snmp_walk.c -- walk layer of the glib based snmp library
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
g_snmp_walk_done_callback(GSnmpSession *session, 
			  GSnmpPdu *spdu, GSList *objs, gpointer data)
{
    GSnmpWalk   *walk;
    GSList	*elem, *orig_elem;
    int		endofviews = 0;
    
    session->error_status = spdu->request.error_status;
    session->error_index = spdu->request.error_index;
    
    if (g_snmp_debug_flags & G_SNMP_DEBUG_SESSION) {
	g_printerr("session %p: error-status = %d, error-index = %d\n",
		   session, session->error_status, session->error_index);
    }

    walk = (GSnmpWalk *) data;
    walk->request = 0;

    /*
     * Check whether we got an error or reached the end of the MIB view.
     */
    
    if (spdu->request.error_status == G_SNMP_ERR_NOSUCHNAME) {
	if (walk->cb_finish) {
	    walk->cb_finish(walk->data);
	} else {
	    g_snmp_walk_destroy(walk);
	}
	return TRUE;
    }
    if (spdu->request.error_status) {
	if (walk->cb_error) {
	    walk->cb_error(walk->data);
	} else {
	    g_snmp_walk_destroy(walk);
	}
	return TRUE;
    }

    /*
     * Check whether we got end of mib view exceptions for all varbinds.
     */

    for (elem = objs; elem; elem = elem = g_slist_next(elem)) {
	GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
	if (vb->type == G_SNMP_ENDOFMIBVIEW) {
	    endofviews++;
	}
    }
    if (endofviews == g_slist_length(objs)) {
	if (walk->cb_finish) {
	    walk->cb_finish(walk->data);
	} else {
	    g_snmp_walk_destroy(walk);
	}
	return TRUE;
    }

    /* xxx sanity check whether the new oid is larger than the previous */

    /* Check whether the new oid is within the scope of the walk. */

    for (elem = objs, orig_elem = walk->orig_objs;
	 elem && orig_elem;
	 elem = g_slist_next(elem), orig_elem = g_slist_next(orig_elem)) {
	GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
	GSnmpVarBind *orig_vb = (GSnmpVarBind *) orig_elem->data;

	if (vb->id_len < orig_vb->id_len
	    || memcmp(vb->id, orig_vb->id, orig_vb->id_len * sizeof(guint32))) {
	    if (walk->cb_finish) {
		walk->cb_finish(walk->data);
	    } else {
		g_snmp_walk_destroy(walk);
	    }
	    g_snmp_vbl_free(objs);
	    return TRUE;
	}
    }

    walk->prev_objs = objs;

    if (walk->cb_row) {
	walk->cb_row(objs, walk->data);
    }
    
    walk->request = g_snmp_session_async_getnext(session, objs);

    return TRUE;
}  



static void
g_snmp_walk_time_callback(GSnmpSession *session, gpointer data)
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



GSnmpWalk *
g_snmp_walk_new(GSnmpSession *session, GSList *objs, 
		void (* cb_error)(), void (* cb_row)(), void (* cb_finish)(),
		gpointer data)
{
    GSList *elem;
    GSnmpWalk *walk;

    walk          = g_malloc0(sizeof(GSnmpWalk));

    walk->session = g_snmp_session_clone(session);
    walk->session->magic = walk;
    walk->session->done_callback = g_snmp_walk_done_callback;
    walk->session->time_callback = g_snmp_walk_time_callback;
    
    for (elem = objs; elem; elem = g_slist_next(elem)) {
	GSnmpVarBind *obj = (GSnmpVarBind *) elem->data;
	g_snmp_vbl_add_null(&walk->orig_objs, obj->id, obj->id_len);
    }
    walk->data = data;
    
    walk->cb_error  = cb_error;
    walk->cb_row    = cb_row;
    walk->cb_finish = cb_finish;
    
    return walk;
}



void
g_snmp_walk_destroy(GSnmpWalk *walk)
{
    if (walk->request) {
	g_snmp_request_dequeue(walk->request);
	g_snmp_request_destroy(walk->request);
    }
    g_snmp_vbl_free(walk->orig_objs);
    g_snmp_session_destroy(walk->session);
    g_free(walk);
}



void
g_snmp_walk_get(GSnmpWalk *walk)
{
    walk->request = g_snmp_session_async_getnext(walk->session,
						 walk->orig_objs);
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
cb_row(GSList *vbl, gpointer *data)
{
    GSList **walklist = (GSList **) data;

    *walklist = g_slist_concat(*walklist, vbl);
}



GSList*
g_snmp_session_sync_walk(GSnmpSession *s, GSList *in)
{
    GSnmpWalk *walk;
    GSList *walklist = NULL;

    walk = g_snmp_walk_new(s, in, cb_error, cb_row, cb_finish, &walklist);

    g_snmp_walk_get(walk);

    loop = g_main_new(TRUE);
    while (loop && g_main_is_running(loop)) {
	g_main_run(loop);
    }
    g_main_destroy(loop);
    loop = NULL;

    s->error_status = walk->session->error_status;
    s->error_index = walk->session->error_index;

    g_snmp_walk_destroy(walk);
    
    return walklist;
}

