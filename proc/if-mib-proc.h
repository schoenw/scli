/* 
 * if-mib-proc.h -- IF-MIB procedures
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

#ifndef _IF_MIB_PROC_H_
#define _IF_MIB_PROC_H_

#include "g_snmp.h"

#include "if-mib.h"

/*
 *  proc set_interface_status(ifAdminStatus)
 *  {
 *      set(ifAdminStatus);
 *  }
 */

extern void
if_mib_proc_stack_interface(GSnmpSession *s,
			    gint32 ifStackLowerLayer,
			    gint32 ifStackHigherLayer);

extern void
if_mib_proc_unstack_interface(GSnmpSession *s,
			      gint32 ifStackLowerLayer,
			      gint32 ifStackHigherLayer);
    
extern void
if_mib_proc_set_interface_status(GSnmpSession *s,
				 gint32 ifIndex,
				 gint32 ifAdminStatus);

extern void
if_mib_proc_set_interface_alias(GSnmpSession *s,
				gint32 ifIndex,
				guchar *alias,
				gsize alias_len);

extern void
if_mib_proc_set_interface_promiscuous(GSnmpSession *s,
				      gint32 ifIndex,
				      gint32 ifPromiscuousMode);

extern void
if_mib_proc_set_notifications(GSnmpSession *s,
			      gint32 ifIndex,
			      gint32 ifLinkUpDownTrapEnable);
    
extern void
if_mib_proc_get_ifTable(GSnmpSession *s,
			if_mib_ifEntry_t ***ifEntry,
			gint mask,
			time_t epoch);

extern void
if_mib_proc_free_ifTable(if_mib_ifEntry_t **ifEntry);

#endif /* _IF_MIB_PROC_H_ */
