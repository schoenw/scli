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

#include "disman-script-mib-proc.h"

void
disman_script_mib_proc_create_script(GSnmpSession *s,
				     char *owner,
				     char *name,
				     char *descr)
{
    disman_script_mib_smScriptEntry_t *smScriptEntry;
    gint32 createAndGo = DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_CREATEANDGO;
    
    smScriptEntry = disman_script_mib_new_smScriptEntry();
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
