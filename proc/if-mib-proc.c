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

void
if_mib_proc_set_interface_status(GSnmpSession *s,
				 gint32 ifIndex,
				 gint32 ifAdminStatus)
{
    if_mib_ifEntry_t *ifEntry;

    if_mib_get_ifEntry(s, &ifEntry, ifIndex, IF_MIB_IFADMINSTATUS);
    if (s->error_status) return;
    ifEntry->ifAdminStatus = &ifAdminStatus;
    if_mib_set_ifEntry(s, ifEntry, IF_MIB_IFADMINSTATUS);
    if_mib_free_ifEntry(ifEntry);
}


void
if_mib_proc_set_interface_alias(GSnmpSession *s,
				gint32 ifIndex,
				char *alias)
{
    if_mib_ifXEntry_t *ifXEntry;

    if_mib_get_ifXEntry(s, &ifXEntry, ifIndex, IF_MIB_IFALIAS);
    if (s->error_status) return;
    ifXEntry->ifAlias = alias;
    ifXEntry->_ifAliasLength = strlen(alias);
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
    if (s->error_status) return;
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
    if (s->error_status) return;
    ifXEntry->ifLinkUpDownTrapEnable = &ifLinkUpDownTrapEnable;
    if_mib_set_ifXEntry(s, ifXEntry, IF_MIB_IFLINKUPDOWNTRAPENABLE);
    if_mib_free_ifXEntry(ifXEntry);
}
