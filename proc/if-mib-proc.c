/* 
 * if-mib-proc.c -- IF-MIB procedures
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

#include "if-mib-proc.h"

#include <time.h>

#define CACHE_TIME	10

void
if_mib_proc_stack_interface(GSnmpSession *s,
			    gint32 ifStackLowerLayer,
			    gint32 ifStackHigherLayer)
{
    if_mib_ifStackEntry_t *ifStackEntry;
    gint32 createAndGo = IF_MIB_IFSTACKSTATUS_CREATEANDGO;

    ifStackEntry = if_mib_new_ifStackEntry();
    ifStackEntry->ifStackLowerLayer = ifStackLowerLayer;
    ifStackEntry->ifStackHigherLayer = ifStackHigherLayer;
    ifStackEntry->ifStackStatus = &createAndGo;
    if_mib_set_ifStackEntry(s, ifStackEntry, IF_MIB_IFSTACKSTATUS);
    if_mib_free_ifStackEntry(ifStackEntry);
}


void
if_mib_proc_unstack_interface(GSnmpSession *s,
			      gint32 ifStackLowerLayer,
			      gint32 ifStackHigherLayer)
{
    if_mib_ifStackEntry_t *ifStackEntry;
    gint32 destroy = IF_MIB_IFSTACKSTATUS_DESTROY;

    if_mib_get_ifStackEntry(s, &ifStackEntry, ifStackHigherLayer,
			    ifStackLowerLayer, IF_MIB_IFSTACKSTATUS);
    if (s->error_status || !ifStackEntry) return;
    ifStackEntry->ifStackStatus = &destroy;
    if_mib_set_ifStackEntry(s, ifStackEntry, IF_MIB_IFSTACKSTATUS);
    if_mib_free_ifStackEntry(ifStackEntry);
}


void
if_mib_proc_set_interface_status(GSnmpSession *s,
				 gint32 ifIndex,
				 gint32 ifAdminStatus)
{
    if_mib_ifEntry_t *ifEntry;

    if_mib_get_ifEntry(s, &ifEntry, ifIndex, IF_MIB_IFADMINSTATUS);
    if (s->error_status || !ifEntry) return;
    ifEntry->ifAdminStatus = &ifAdminStatus;
    if_mib_set_ifEntry(s, ifEntry, IF_MIB_IFADMINSTATUS);
    if_mib_free_ifEntry(ifEntry);
}


void
if_mib_proc_set_interface_alias(GSnmpSession *s,
				gint32 ifIndex,
				guchar *alias,
				gsize alias_len)
{
    if_mib_ifXEntry_t *ifXEntry;

    if_mib_get_ifXEntry(s, &ifXEntry, ifIndex, IF_MIB_IFALIAS);
    if (s->error_status || !ifXEntry) return;
    ifXEntry->ifAlias = alias;
    ifXEntry->_ifAliasLength = alias_len;
    if_mib_set_ifXEntry(s, ifXEntry, IF_MIB_IFALIAS);
    if_mib_free_ifXEntry(ifXEntry);
}


void
if_mib_proc_set_interface_promiscuous(GSnmpSession *s,
				      gint32 ifIndex,
				      gint32 ifPromiscuousMode)
{
    if_mib_ifXEntry_t *ifXEntry;

    if_mib_get_ifXEntry(s, &ifXEntry, ifIndex, IF_MIB_IFPROMISCUOUSMODE);
    if (s->error_status || !ifXEntry) return;
    ifXEntry->ifPromiscuousMode = &ifPromiscuousMode;
    if_mib_set_ifXEntry(s, ifXEntry, IF_MIB_IFPROMISCUOUSMODE);
    if_mib_free_ifXEntry(ifXEntry);
}


void
if_mib_proc_set_notifications(GSnmpSession *s,
			      gint32 ifIndex,
			      gint32 ifLinkUpDownTrapEnable)
{
    if_mib_ifXEntry_t *ifXEntry;

    if_mib_get_ifXEntry(s, &ifXEntry, ifIndex, IF_MIB_IFPROMISCUOUSMODE);
    if (s->error_status || !ifXEntry) return;
    ifXEntry->ifLinkUpDownTrapEnable = &ifLinkUpDownTrapEnable;
    if_mib_set_ifXEntry(s, ifXEntry, IF_MIB_IFLINKUPDOWNTRAPENABLE);
    if_mib_free_ifXEntry(ifXEntry);
}

typedef struct {
    gpointer data;
    time_t time;
    time_t epoch;
} ifEntry_t;


void
if_mib_proc_get_ifTable(GSnmpSession *s,
			if_mib_ifEntry_t ***ifEntry,
			gint mask,
			time_t epoch)
{
    static ifEntry_t cache = {NULL, 0};
    time_t now = time(NULL);

    if (cache.data) {
	if (cache.epoch == epoch && (now - cache.time) < CACHE_TIME) {
	    *ifEntry = cache.data;
	    return;
	}
	if_mib_free_ifTable(cache.data);
	cache.data = NULL;
    }

    if_mib_get_ifTable(s, ifEntry, mask);
    if (! s->error_status) {
	cache.data = *ifEntry;
	cache.time = now;
	cache.epoch = epoch;
    }
}



void
if_mib_proc_free_ifTable(if_mib_ifEntry_t **ifEntry)
{
}
