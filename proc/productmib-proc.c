/* 
 * productmib-proc.c -- PRODUCTMIB procedures
 *
 * Copyright (C) 2002 Juergen Schoenwaelder
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

#include "if-mib.h"

#include "productmib-proc.h"

void
productmib_proc_create_vlan(GNetSnmp *s, gint32 vlanId,
			    guchar *name, gsize name_len, guint32 type)
{
    productmib_a3ComVirtualGroup_t *vg = NULL;
    productmib_a3ComVlanIfEntry_t *vlanEntry;
    gint32 createAndGo = PRODUCTMIB_ROWSTATUS_CREATEANDGO;

    productmib_get_a3ComVirtualGroup(s, &vg, 0);
    if (s->error_status || !vg) return;
    vlanEntry = productmib_new_a3ComVlanIfEntry();
    if (! vlanEntry) return;
    if (!vg->a3ComNextAvailableVirtIfIndex
	|| vg->a3ComNextAvailableVirtIfIndex == 0) {
	s->error_status = GNET_SNMP_ERR_PROCEDURE;
	return;
    }
    vlanEntry->a3ComVlanIfIndex = *vg->a3ComNextAvailableVirtIfIndex;
    vlanEntry->a3ComVlanIfDescr = name;
    vlanEntry->_a3ComVlanIfDescrLength = name_len;
    vlanEntry->a3ComVlanIfGlobalIdentifier = &vlanId;
    vlanEntry->a3ComVlanIfType = &type;
    vlanEntry->a3ComVlanIfStatus = &createAndGo;
    productmib_set_a3ComVlanIfEntry(s, vlanEntry, 0);
    productmib_free_a3ComVlanIfEntry(vlanEntry);
}



void
productmib_proc_delete_vlan(GNetSnmp *s, gint32 ifIndex)
{
    productmib_a3ComVlanIfEntry_t *vlanEntry;
    gint32 destroy = PRODUCTMIB_ROWSTATUS_DESTROY;

    productmib_get_a3ComVlanIfEntry(s, &vlanEntry, ifIndex,
				    PRODUCTMIB_A3COMVLANIFSTATUS);
    if (s->error_status || !vlanEntry) return;
    vlanEntry->a3ComVlanIfStatus = &destroy;
    productmib_set_a3ComVlanIfEntry(s, vlanEntry,
				    PRODUCTMIB_A3COMVLANIFSTATUS);
    productmib_free_a3ComVlanIfEntry(vlanEntry);
}


void
productmib_proc_set_vlan_port_member(GNetSnmp *s,
				     gint32 ifIndex,
				     guchar *bits,
				     gsize bits_len)
{
    if_mib_ifStackEntry_t **ifStackTable = NULL;
    int i;

    if_mib_get_ifStackTable(s, &ifStackTable, 0);
    if (s->error_status) return;

    for (i = 0; ifStackTable[i]; i++) {
	if (ifStackTable[i]->ifStackHigherLayer == ifIndex) {
	    gint32 ll = ifStackTable[i]->ifStackLowerLayer;
	    if (ll / 8 < bits_len) {
		int bit = bits[ll/8] & 1 << (7-(ll%8));
		if (! bit) {
		    if_mib_delete_ifStackEntry(s,
					       ifStackTable[i]->ifStackHigherLayer,
					       ifStackTable[i]->ifStackLowerLayer);
		    /* xxx error handling ? xxx */
		}
	    }
	}
    }

    for (i = 0; i < bits_len * 8; i++) {
	int bit = bits[i/8] & 1 << (7-(i%8));
	if (bit) {
	    if_mib_create_ifStackEntry(s, ifIndex, i);
	    /* xxx error handling ? xxx */
	}
    }

    if (ifStackTable) if_mib_free_ifStackTable(ifStackTable);
}
