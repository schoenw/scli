/* 
 * snmp-view-based-acm-mib-proc.h -- SNMP-VIEW-BASED-ACM-MIB procedures
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

#ifndef _SNMP_VIEW_BASED_ACM_MIB_PROC_H_
#define _SNMP_VIEW_BASED_ACM_MIB_PROC_H_

#include "snmp-view-based-acm-mib.h"

extern void
snmp_view_based_acm_mib_proc_create_member(GNetSnmp *s,
					   guchar *name,
					   guchar *group,
					   gint32 model,
					   GError **error);

extern void
snmp_view_based_acm_mib_proc_delete_member(GNetSnmp *s,
					   guchar *name, gsize name_len,
					   guchar *group, gsize group_len,
					   gint32 model,
					   GError **error);


#endif /* _SNMP_VIEW_BASED_ACM_MIB_PROC_H_ */
