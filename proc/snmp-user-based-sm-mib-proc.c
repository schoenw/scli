/* 
 * snmp-user-based-sm-mib-proc.c -- SNMP-USER-BASED-SM-MIB procedures
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

#include "snmpv2-tc.h"

#include "snmp-user-based-sm-mib-proc.h"

void
snmp_user_based_sm_mib_proc_clone_user(GNetSnmp *s,
				       guchar *user, size_t user_len,
				       guchar *dolly, size_t dolly_len,
				       GError **error)
{
    snmp_framework_mib_snmpEngine_t *snmpEngine;
    snmp_user_based_sm_mib_usmUserEntry_t *usmUser;
    gint32 createAndWait = SNMPV2_TC_ROWSTATUS_CREATEANDWAIT;
    
    snmp_framework_mib_get_snmpEngine(s, &snmpEngine, 0, error);
    if (error && *error) return;
    if (s->error_status) return;

    usmUser = snmp_user_based_sm_mib_new_usmUserEntry();
    if (! usmUser) {
      proc_error:
	s->error_status = GNET_SNMP_PDU_ERR_PROCEDURE;
	return;
    }

    if (! snmpEngine->snmpEngineID
	|| snmpEngine->_snmpEngineIDLength < SNMP_USER_BASED_SM_MIB_USMUSERENGINEIDMINLENGTH
	|| snmpEngine->_snmpEngineIDLength > SNMP_USER_BASED_SM_MIB_USMUSERENGINEIDMAXLENGTH) {
	goto proc_error;
    }
    
    memcpy(usmUser->usmUserEngineID,
	   snmpEngine->snmpEngineID,
	   snmpEngine->_snmpEngineIDLength);
    usmUser->_usmUserEngineIDLength = snmpEngine->_snmpEngineIDLength;
    memcpy(usmUser->usmUserName, user, user_len);
    usmUser->_usmUserNameLength = user_len;
#if 0
    /* this has to be a RowPointer rather a string */
    usmUser->usmUserCloneFrom = dolly;
    usmUser->_usmUserCloneFromLength = dolly_len;
#endif
    usmUser->usmUserStatus = &createAndWait;

    snmp_user_based_sm_mib_set_usmUserEntry(s, usmUser, 0, error);
    snmp_user_based_sm_mib_free_usmUserEntry(usmUser);
}

void
snmp_user_based_sm_mib_proc_delete_user(GNetSnmp *s,
					guchar *name, gsize name_len,
					guchar *group, gsize group_len,
					gint32 model,
					GError **error)
{
}
