/* 
 * xml.c -- scli xml utilities used by many scli modes
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

#include "scli.h"

#include <stdarg.h>



void
xml_set_prop(xmlNodePtr node, const xmlChar *name, const char *format, ...)
{
    char *s;
    va_list args;

    va_start(args, format);
    s = g_strdup_vprintf(format, args);
    va_end(args);

    if (s) {
	xmlSetProp(node, name, s);
	g_free(s);
    }
}



void
xml_set_content(xmlNodePtr node, const char *format, ...)
{
    char *s;
    va_list args;

    va_start(args, format);
    s = g_strdup_vprintf(format, args);
    va_end(args);

    if (s) {
	xmlNodePtr text = xmlNewText(s);
	if (text) xmlAddChild(node, text);
	g_free(s);
    }
}



xmlNodePtr
xml_new_child(xmlNodePtr parent, xmlNsPtr ns, const xmlChar *name,
	      const char *format, ...)
{
    char *s;
    va_list args;
    xmlNodePtr node;

    node = xmlNewChild(parent, ns, name, NULL);
    if (node && format) {
	va_start(args, format);
	s = g_strdup_vprintf(format, args);
	va_end(args);

	if (s) {
	    xmlNodePtr text = xmlNewText(s);
	    if (text) xmlAddChild(node, text);
	    g_free(s);
	}
    }

    return node;
}
