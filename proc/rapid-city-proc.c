/* 
 * rapid-city-proc.c -- RAPID-CITY procedures
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

#include "snmpv2-tc.h"

#include "rapid-city-proc.h"

void
rapid_city_proc_create_vlan(GNetSnmp *s,
			    gint32 vlanid,
			    guchar *name,
			    gsize name_len,
			    guint32 type)
{
    rapid_city_rcVlanEntry_t *vlanEntry;
    gint32 createAndGo = SNMPV2_TC_ROWSTATUS_CREATEANDGO;
    
    vlanEntry = rapid_city_new_rcVlanEntry();
    if (vlanEntry) {
	vlanEntry->rcVlanId = vlanid;
	vlanEntry->rcVlanName = name;
	vlanEntry->_rcVlanNameLength = name_len;
	vlanEntry->rcVlanType = &type;
	vlanEntry->rcVlanRowStatus = &createAndGo;
	rapid_city_set_rcVlanEntry(s, vlanEntry,
				   RAPID_CITY_RCVLANNAME
				   | RAPID_CITY_RCVLANTYPE
				   | RAPID_CITY_RCVLANROWSTATUS);
	rapid_city_free_rcVlanEntry(vlanEntry);
    }
}



void
rapid_city_proc_delete_vlan(GNetSnmp *s, gint32 vlanid)
{
    rapid_city_rcVlanEntry_t *vlanEntry;
    gint32 destroy = SNMPV2_TC_ROWSTATUS_DESTROY;

    rapid_city_get_rcVlanEntry(s, &vlanEntry, vlanid,
			       RAPID_CITY_RCVLANROWSTATUS);
    if (s->error_status || !vlanEntry) return;
    vlanEntry->rcVlanRowStatus = &destroy;
    rapid_city_set_rcVlanEntry(s, vlanEntry,
			       RAPID_CITY_RCVLANROWSTATUS);
    rapid_city_free_rcVlanEntry(vlanEntry);
}



void
rapid_city_proc_set_vlan_port_default(GNetSnmp *s,
				      gint32 port,
				      gint32 vlanid)
{
    rapid_city_rcVlanPortEntry_t *rcVlanPortEntry;

    rapid_city_get_rcVlanPortEntry(s, &rcVlanPortEntry, port,
				   RAPID_CITY_RCVLANPORTDEFAULTVLANID);
    if (s->error_status || !rcVlanPortEntry) return;
    rcVlanPortEntry->rcVlanPortDefaultVlanId = &vlanid;
    rapid_city_set_rcVlanPortEntry(s, rcVlanPortEntry,
				   RAPID_CITY_RCVLANPORTDEFAULTVLANID);
    rapid_city_free_rcVlanPortEntry(rcVlanPortEntry);
}



void
rapid_city_proc_set_vlan_port_member(GNetSnmp *s,
				     gint32 vlanid,
				     guchar *ports)
{
    rapid_city_rcVlanEntry_t *rcVlanEntry;

    rapid_city_get_rcVlanEntry(s, &rcVlanEntry, vlanid,
			       RAPID_CITY_RCVLANPORTMEMBERS);
    if (s->error_status || !rcVlanEntry) return;
    rcVlanEntry->rcVlanPortMembers = ports;
    rapid_city_set_rcVlanEntry(s, rcVlanEntry,
			       RAPID_CITY_RCVLANPORTMEMBERS);
    rapid_city_free_rcVlanEntry(rcVlanEntry);
}
