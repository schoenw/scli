/*
 * g_snmp_walt.h -- walk layer of the glib based snmp library
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

#ifndef _G_SNMP_WALK_H_
#define _G_SNMP_WALK_H_

typedef struct _GSnmpWalk
{
    GSnmpSession *session;
    GSList       *orig_objs;
    GSList	 *prev_objs;
    gpointer      data;
    gpointer     request;
    void      (* cb_error)();
    void      (* cb_row)();
    void      (* cb_finish)();
} GSnmpWalk;


GSnmpWalk*	g_snmp_walk_new(GSnmpSession *session,
				GSList *objs,
				void (* cb_error)(),
				void (* cb_row)(),
				void (* cb_finish)(),
				gpointer data);
void		g_snmp_walk_get(GSnmpWalk *walk);
void		g_snmp_walk_destroy(GSnmpWalk *walk);

/*
 * Another sync. entry point which is used by the scli package.
 */

GSList* g_snmp_session_sync_walk(GSnmpSession *s, GSList *vbl);

#endif /* _G_SNMP_WALK_H_ */
