/* 
 * sflow5-mib-proc.c -- SFLOW5-MIB procedures
 *
 * Copyright (C) 2007 Juergen Schoenwaelder
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
 * @(#) $Id: if-mib-proc.c 709 2004-10-14 20:11:17Z schoenw $
 */

#include "sflow5-mib-proc.h"

void
sflow5_mib_proc_create_receiver(GNetSnmp *s, guchar *myaddr, guint16 myport,
				guint32 rate, guint32 interval, guint32 timeout,
				GError **error)
{
    sflow5_mib_sFlowRcvrEntry_t **rcvrTable = NULL;
    sflow5_mib_sFlowRcvrEntry_t *rcvrEntry = NULL;
    int i, last_owner = -1, first_free = -1;

    gint32 def_port = 6343;
    gint32 def_timeout = 3600;
    gint32 def_rate = 512;
    guchar *def_owner = "scli";

    sflow5_mib_get_sFlowRcvrTable(s, &rcvrTable, SFLOW5_MIB_SFLOWRCVROWNER, error);
    if ((error && *error) || s->error_status || !rcvrTable) return;
    for (i = 0; rcvrTable[i]; i++) {
	if (rcvrTable[i]->_sFlowRcvrOwnerLength == 0 && first_free < 0) {
	    first_free = rcvrTable[i]->sFlowRcvrIndex;
	}
    }
    if (rcvrTable) sflow5_mib_free_sFlowRcvrTable(rcvrTable);

    if (first_free <= 0 && last_owner <= 0) {
    proc_error:
	s->error_status = GNET_SNMP_PDU_ERR_PROCEDURE;
	return;
    }

    g_printerr("** use entry at index %d\n", first_free < 0 ? last_owner : first_free);

    rcvrEntry = sflow5_mib_new_sFlowRcvrEntry();
    if (! rcvrEntry) {
	goto proc_error;
    }

    if (first_free > 0) {
	rcvrEntry->sFlowRcvrIndex = first_free;
    } else {
	rcvrEntry->sFlowRcvrIndex = last_owner;
    }
    rcvrEntry->sFlowRcvrPort = &def_port;
    rcvrEntry->sFlowRcvrTimeout = &def_timeout;
    rcvrEntry->sFlowRcvrOwner = def_owner;
    rcvrEntry->_sFlowRcvrOwnerLength = strlen(def_owner);
    
    sflow5_mib_set_sFlowRcvrEntry(s, rcvrEntry, 0
				  | SFLOW5_MIB_SFLOWRCVROWNER
				  | SFLOW5_MIB_SFLOWRCVRTIMEOUT
#if 0
				  | SFLOW5_MIB_SFLOWRCVRADDRESSTYPE
				  | SFLOW5_MIB_SFLOWRCVRADDRESS
#endif
				  | SFLOW5_MIB_SFLOWRCVRPORT,
				  error);
    sflow5_mib_free_sFlowRcvrEntry(rcvrEntry);
    if ((error && *error) || s->error_status) return;
    
    /* xxx */
}
