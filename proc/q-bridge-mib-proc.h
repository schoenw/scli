/* 
 * q-bridge-mib-proc.h -- Q-BRIDGE-MIB procedures
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
 * @(#) $Id: disman-script-mib-proc.h 709 2004-10-14 20:11:17Z schoenw $
 */

#ifndef _Q_BRIDGE_MIB_PROC_H_
#define _Q_BRIDGE_MIB_PROC_H_

#include "q-bridge-mib.h"

extern void
q_bridge_mib_proc_create_vlan(GNetSnmp *s,
			      guint vlanIndex,
			      gchar *vlanName,
			      GError **error);

extern void
q_bridge_mib_proc_delete_vlan(GNetSnmp *s,
			      guint vlanIndex,
			      GError **error);

#endif /* _Q_BRIDGE_MIB_PROC_H_ */
