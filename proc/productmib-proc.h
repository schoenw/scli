/* 
 * productmib-proc.h -- PRODUCTMIB procedures
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

#ifndef _PRODUCTMIB_PROC_H_
#define _PRODUCTMIB_PROC_H_

#include "g_snmp.h"

#include "productmib.h"


extern void
productmib_proc_create_vlan(GSnmpSession *s, gint32 vlanid,
			    guchar *name, guint32 type);
extern void
productmib_proc_delete_vlan(GSnmpSession *s, gint32 ifIndex);

extern void
productmib_proc_set_vlan_port_member(GSnmpSession *s, gint32 ifIndex,
				     guchar *ports, gsize ports_len);
    
#endif /* _PRODUCTMIB_PROC_H_ */
