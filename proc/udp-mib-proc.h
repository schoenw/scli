/* 
 * udp-mib-proc.h -- UDP-MIB procedures
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

#ifndef _UDP_MIB_PROC_H_
#define _UDP_MIB_PROC_H_

#include "udp-mib.h"

/*
 *  proc create_script(smScriptOwner, smScriptName, smScriptDescr)
 *  {
 *      set(smScriptDescr, smScriptRowStatus=createAndGo);
 *  }
 */

typedef struct {
    guint32 inDatagrams;
    guint32 outDatagrams;
    guint32 inDiscards;
} udp_mib_proc_stats_t;


extern void
udp_mib_proc_get_stats(GSnmpSession *s,
		       udp_mib_proc_stats_t **udpStatsEntry);


#endif /* _UDP_MIB_PROC_H_ */
