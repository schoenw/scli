/* 
 * vendors.c -- information about well known agent vendors
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "stools.h"
#include "scli.h"

static scli_vendor_t vendor_table[] = {
    {    9,	"Cisco Systems",	"http://www.cisco.com/" },
    {   11,	"Hewlett Packard",	"http://www.hp.com/" },
    {   42,	"Sun Microsystems",	"http://www.sun.com/" },
    {  253,	"Xerox",		"http://www.xerox.com/" },
    { 1575,	"TU Braunschweig",	NULL },
    { 2021,	"UCD-SNMP",		"http://ucd-snmp.ucdavis.edu/" },
    { 8072,	"NET-SNMP",		"http://net-snmp.sourceforge.net/" },
    {    0,	NULL,			NULL },
};


scli_vendor_t*
scli_get_vendor(guint32 oid[], gsize len)
{
    static guint32 const enterprises[] = { 1, 3, 6, 1, 4, 1 };
    int i, j;
    
    if (len <= sizeof(enterprises)/sizeof(guint32)) {
	return NULL;
    }
    
    for (i = 0; i < sizeof(enterprises)/sizeof(guint32); i++) {
	if (oid[i] != enterprises[i]) {
	    return NULL;
	}
    }

    for (j = 0; vendor_table[j].id; j++) {
	if (vendor_table[j].id == oid[i]) {
	    return &(vendor_table[j]);
	}
    }

    return NULL;
}
