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

#include "productmib-proc.h"


void
productmib_proc_create_vlan(GSnmpSession *s, gint32 vlanId,
			     guchar *name, guint32 type)
{
    productmib_a3ComVirtualGroup_t *vg = NULL;
    productmib_a3ComVlanIfEntry_t *vlanEntry;
    gint32 createAndGo = PRODUCTMIB_A3COMVLANIFSTATUS_CREATEANDGO;

    productmib_get_a3ComVirtualGroup(s, &vg, 0);
    vlanEntry = productmib_new_a3ComVlanIfEntry();
    /* report error if there is no free index anymore ? */
    if (vg && vg->a3ComNextAvailableVirtIfIndex && vlanEntry) {
	/* check whether vg->a3ComNextAvailableVirtIfIndex is usable */
	vlanEntry->a3ComVlanIfIndex = *vg->a3ComNextAvailableVirtIfIndex;
	vlanEntry->a3ComVlanIfDescr = name;
	vlanEntry->_a3ComVlanIfDescrLength = strlen(name);
	vlanEntry->a3ComVlanIfGlobalIdentifier = &vlanId;
	vlanEntry->a3ComVlanIfType = &type;
	vlanEntry->a3ComVlanIfStatus = &createAndGo;
	productmib_set_a3ComVlanIfEntry(s, vlanEntry, 0);
	productmib_free_a3ComVlanIfEntry(vlanEntry);
    }
}



