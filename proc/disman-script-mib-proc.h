/* 
 * disman-script-mib-proc.h -- DISMAN-SCRIPT-MIB procedures
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

#ifndef _DISMAN_SCRIPT_MIB_PROC_H_
#define _DISMAN_SCRIPT_MIB_PROC_H_

#include "disman-script-mib.h"

/*
 *  proc create_script(smScriptOwner, smScriptName, smScriptDescr)
 *  {
 *      set(smScriptDescr, smScriptRowStatus=createAndGo);
 *  }
 */

extern void
disman_script_mib_proc_create_script(GSnmpSession *s,
				     guchar *owner,
				     guchar *name,
				     guchar *descr);

extern void
disman_script_mib_proc_create_run(GSnmpSession *s,
				  guchar *lowner,
				  guchar *lname,
				  guchar *args);


#endif /* _DISMAN_SCRIPT_MIB_PROC_H_ */
