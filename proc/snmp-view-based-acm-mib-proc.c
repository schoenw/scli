/* 
 * snmp-view-based-acm-mib-proc.c -- SNMP-VIEW-BASED-ACM-MIB procedures
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

#include "snmp-view-based-acm-mib-proc.h"

void
snmp_view_based_acm_mib_proc_create_member(GSnmpSession *s,
					   guchar *name,
					   guchar *group,
					   gint32 model)
{
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmGroupEntry;
    gint32 createAndGo = SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_CREATEANDGO;

    vacmGroupEntry = snmp_view_based_acm_mib_new_vacmSecurityToGroupEntry();
    if (! vacmGroupEntry) {
	s->error_status = G_SNMP_ERR_PROCEDURE;
	return;
    }
    vacmGroupEntry->_vacmSecurityNameLength = strlen(name);
    memcpy(vacmGroupEntry->vacmSecurityName, name,
	   vacmGroupEntry->_vacmSecurityNameLength);
    vacmGroupEntry->_vacmGroupNameLength = strlen(group);
    vacmGroupEntry->vacmGroupName = group;
    vacmGroupEntry->vacmSecurityModel = model;
    vacmGroupEntry->vacmSecurityToGroupStatus = &createAndGo;
    snmp_view_based_acm_mib_set_vacmSecurityToGroupEntry(s, vacmGroupEntry, 0);
    snmp_view_based_acm_mib_free_vacmSecurityToGroupEntry(vacmGroupEntry);
}

void
snmp_view_based_acm_mib_proc_delete_member(GSnmpSession *s,
					   guchar *name, gsize name_len,
					   guchar *group, gsize group_len,
					   gint32 model)
{
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmGroupEntry;
    gint32 destroy = SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_DESTROY;

    vacmGroupEntry = snmp_view_based_acm_mib_new_vacmSecurityToGroupEntry();
    if (! vacmGroupEntry) {
	s->error_status = G_SNMP_ERR_PROCEDURE;
	return;
    }
    vacmGroupEntry->_vacmSecurityNameLength = name_len;
    memcpy(vacmGroupEntry->vacmSecurityName, name,
	   vacmGroupEntry->_vacmSecurityNameLength);
    vacmGroupEntry->_vacmGroupNameLength = group_len;
    vacmGroupEntry->vacmGroupName = group;
    vacmGroupEntry->vacmSecurityModel = 0;
    vacmGroupEntry->vacmSecurityToGroupStatus = &destroy;
    snmp_view_based_acm_mib_set_vacmSecurityToGroupEntry(s, vacmGroupEntry, 0);
    snmp_view_based_acm_mib_free_vacmSecurityToGroupEntry(vacmGroupEntry);
}

#if 0
void
disman_script_mib_proc_create_script(GSnmpSession *s,
				     guchar *owner,
				     guchar *name,
				     guchar *descr)
{
    disman_script_mib_smScriptEntry_t *smScriptEntry;
    gint32 createAndGo = DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_CREATEANDGO;
    
    smScriptEntry = disman_script_mib_new_smScriptEntry();
    if (! smScriptEntry) {
	s->error_status = G_SNMP_ERR_PROCEDURE;
	return;
    }
    strcpy(smScriptEntry->smScriptOwner, owner);
    smScriptEntry->_smScriptOwnerLength = strlen(owner);
    strcpy(smScriptEntry->smScriptName, name);
    smScriptEntry->_smScriptNameLength = strlen(name);
    smScriptEntry->smScriptDescr = descr;
    smScriptEntry->_smScriptDescrLength = strlen(descr);
    smScriptEntry->smScriptRowStatus = &createAndGo;
    disman_script_mib_set_smScriptEntry(s, smScriptEntry, 0);
    disman_script_mib_free_smScriptEntry(smScriptEntry);
}
#endif
