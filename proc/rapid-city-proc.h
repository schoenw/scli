/* 
 * rapid-city-proc.h -- RAPID-CITY procedures
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

#ifndef _RAPID_CITY_PROC_H_
#define _RAPID_CITY_PROC_H_

#include "rapid-city.h"

extern void
rapid_city_proc_create_vlan(GNetSnmp *s, gint32 vlanid,
			    guchar *name, gsize name_len, guint32 type);
extern void
rapid_city_proc_delete_vlan(GNetSnmp *s, gint32 vlanid);

extern void
rapid_city_proc_set_vlan_port_default(GNetSnmp *s, gint32 port,
				      gint32 vlanid);
extern void
rapid_city_proc_set_vlan_port_member(GNetSnmp *s, gint32 vlanid,
				     guchar *ports);
    
#endif /* _RAPID_CITY_PROC_H_ */
