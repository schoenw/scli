/* 
 * ianaiftype_mib_proc.c -- IANAifType-MIB procedures
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

#include "ianaiftype-mib-proc.h"

/*
 * See RFC 2665 section 3.2.6. why the test below is so ugly...
 */

extern int
ianaiftype_mib_proc_isether(gint32 ifType)
{
    return (ifType == IANAIFTYPE_MIB_IANAIFTYPE_ETHERNETCSMACD
	    || ifType == IANAIFTYPE_MIB_IANAIFTYPE_ISO88023CSMACD
	    || ifType == IANAIFTYPE_MIB_IANAIFTYPE_STARLAN
	    || ifType == IANAIFTYPE_MIB_IANAIFTYPE_FASTETHER
	    || ifType == IANAIFTYPE_MIB_IANAIFTYPE_FASTETHERFX
	    || ifType == IANAIFTYPE_MIB_IANAIFTYPE_GIGABITETHERNET);
}
