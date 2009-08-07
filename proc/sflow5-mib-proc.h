/* 
 * sflow50mib-proc.h -- SFLOW5-MIB procedures
 *
 * Copyright (C) 2007 Juergen Schoenwaelder
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
 * @(#) $Id: if-mib-proc.h 709 2004-10-14 20:11:17Z schoenw $
 */

#ifndef _SFLOW5_MIB_PROC_H_
#define _SFLOW5_MIB_PROC_H_

#include "sflow5-mib.h"

extern void
sflow5_mib_proc_create_receiver(GNetSnmp *s, guchar *receiver, guint16 port,
				guint32 rate, guint32 interval, guint32 timeout,
				GError **error);

#endif /* _SFLOW5_MIB_PROC_H_ */
