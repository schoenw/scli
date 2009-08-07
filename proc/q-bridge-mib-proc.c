/* 
 * q-bridge-mib-proc.c -- Q-BRIDGE-MIB procedures
 *
 * Copyright (C) 2008 Juergen Schoenwaelder
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
 * @(#) $Id: disman-script-mib-proc.c 1995 2006-08-22 21:58:46Z schoenw $
 */

#include "snmpv2-tc.h"

#include "q-bridge-mib-proc.h"

void
q_bridge_mib_proc_create_vlan(GNetSnmp *s,
			      guint vlanIndex,
			      gchar *vlanName,
			      GError **error)
{
    q_bridge_mib_dot1qVlanStaticEntry_t *vlanEntry;
    gint32 createAndGo = SNMPV2_TC_ROWSTATUS_CREATEANDGO;
    size_t len;

    len = strlen(vlanName);
    if (len < Q_BRIDGE_MIB_DOT1QVLANSTATICNAMEMINLENGTH
	|| len > Q_BRIDGE_MIB_DOT1QVLANSTATICNAMEMAXLENGTH) {
	s->error_status = GNET_SNMP_PDU_ERR_PROCEDURE;
	return;
    }

    if (vlanIndex < 1 || vlanIndex > 4094) {
	s->error_status = GNET_SNMP_PDU_ERR_PROCEDURE;
	return;
    }

    vlanEntry = q_bridge_mib_new_dot1qVlanStaticEntry();
    if (! vlanEntry) {
	s->error_status = GNET_SNMP_PDU_ERR_PROCEDURE;
	return;
    }

    vlanEntry->dot1qVlanStaticName = vlanName;
    vlanEntry->_dot1qVlanStaticNameLength = len;
    vlanEntry->dot1qVlanIndex = vlanIndex;
    vlanEntry->dot1qVlanStaticRowStatus = &createAndGo;
    q_bridge_mib_set_dot1qVlanStaticEntry(s, vlanEntry,
			  Q_BRIDGE_MIB_DOT1QVLANSTATICNAME
			  | Q_BRIDGE_MIB_DOT1QVLANSTATICROWSTATUS, error);
    q_bridge_mib_free_dot1qVlanStaticEntry(vlanEntry);
}

void
q_bridge_mib_proc_delete_vlan(GNetSnmp *s,
			      guint vlanIndex,
			      GError **error)
{
    q_bridge_mib_dot1qVlanStaticEntry_t *vlanEntry;
    gint32 destroy = SNMPV2_TC_ROWSTATUS_DESTROY;
    
    q_bridge_mib_get_dot1qVlanStaticEntry(s, &vlanEntry, vlanIndex,
					  Q_BRIDGE_MIB_DOT1QVLANSTATICROWSTATUS, error);
    if ((error && *error) || s->error_status || !vlanEntry) return;
    vlanEntry->dot1qVlanStaticRowStatus = &destroy;
    q_bridge_mib_set_dot1qVlanStaticEntry(s, vlanEntry,
			  Q_BRIDGE_MIB_DOT1QVLANSTATICROWSTATUS, error);
    q_bridge_mib_free_dot1qVlanStaticEntry(vlanEntry);
}
