/* 
 * disman-script-mib-proc.c -- DISMAN-SCRIPT-MIB procedures
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

#include "disman-script-mib-proc.h"

void
disman_script_mib_proc_create_script(GNetSnmp *s,
				     guchar *owner,
				     guchar *name,
				     guchar *descr)
{
    disman_script_mib_smScriptEntry_t *smScriptEntry;
    gint32 createAndGo = SNMPV2_TC_ROWSTATUS_CREATEANDGO;
    
    smScriptEntry = disman_script_mib_new_smScriptEntry();
    if (! smScriptEntry) {
	s->error_status = GNET_SNMP_ERR_PROCEDURE;
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


/*
 * This implements the procedure described in section 7.6 of RFC 3165.
 */

void
disman_script_mib_proc_create_run(GNetSnmp *s,
				  guchar *lowner,
				  guchar *lname,
				  guchar *args)
{
    disman_script_mib_smLaunchEntry_t *smLaunchEntry;
    disman_script_mib_smRunEntry_t *smRunEntry;
    gint32 smRunIndex;
    int i, done = 0;

    disman_script_mib_get_smLaunchEntry(s, &smLaunchEntry,
					lowner, strlen(lowner),
					lname, strlen(lname),
					DISMAN_SCRIPT_MIB_SMLAUNCHRUNINDEXNEXT);
    if (s->error_status) return;
    if (!smLaunchEntry || !smLaunchEntry->smLaunchRunIndexNext) {
    proc_error:
	s->error_status = GNET_SNMP_ERR_PROCEDURE;
	return;
    }
    smRunIndex = *smLaunchEntry->smLaunchRunIndexNext;
    smLaunchEntry->smLaunchArgument = args;
    smLaunchEntry->_smLaunchArgumentLength = args ? strlen(args) : 0;
    smLaunchEntry->smLaunchStart = &smRunIndex;
    disman_script_mib_set_smLaunchEntry(s, smLaunchEntry,
					DISMAN_SCRIPT_MIB_SMLAUNCHSTART
					| DISMAN_SCRIPT_MIB_SMLAUNCHARGUMENT);
    disman_script_mib_free_smLaunchEntry(smLaunchEntry);
    if (s->error_status) return;
    for (i = 0; i < 5 && ! done; i++) {
	disman_script_mib_get_smRunEntry(s, &smRunEntry,
					 lowner, strlen(lowner),
					 lname, strlen(lname),
					 smRunIndex,
					 DISMAN_SCRIPT_MIB_SMRUNSTATE);
	if (s->error_status) return;	/* oops - cleanup ? */
	if (! smRunEntry) goto proc_error;
	done = ! smRunEntry->smRunState
	    || *smRunEntry->smRunState == DISMAN_SCRIPT_MIB_SMRUNSTATE_EXECUTING
	    || *smRunEntry->smRunState == DISMAN_SCRIPT_MIB_SMRUNSTATE_SUSPENDED
	    || *smRunEntry->smRunState == DISMAN_SCRIPT_MIB_SMRUNSTATE_TERMINATED;
	    
	disman_script_mib_free_smRunEntry(smRunEntry);
    }
    if (! done) goto proc_error;
}
