/* 
 * netconf.c -- basic netconf functions for the scli command interpreter
 *
 * Copyright (C) 2004 Juergen Schoenwaelder
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

#define EOM "<?eom?>"

static void
netconf_send_hello(scli_interp_t *interp)
{
    xmlDocPtr hello;
    xmlChar *buffer;
    int len;

    hello = xmlNewDoc("1.0");
    hello->children = xmlNewDocNode(interp->xml_doc, NULL, "hello", NULL);
    xmlNewChild(hello->children, NULL, "capabilities", NULL);

    xmlDocDumpFormatMemory(hello, &buffer, &len, 1);
    g_print("%.*s%s\n", len, buffer, EOM);
    xmlFree(buffer);
    xmlFreeDoc(hello);    
}


static gboolean
netconf_next_msg(FILE *stream, xmlDocPtr *msgPtr)
{
    static GString *s = NULL;
    char buffer[1024];
    gchar *p = NULL, *r = NULL;
    size_t len;
    
    if (! s) {
	s = g_string_new(NULL);
    }

    while (fgets(buffer, sizeof(buffer), stream) != NULL) {
	len = strlen(buffer);
	s = g_string_append_len(s, buffer, len);
	p = g_strstr_len(s->str, s->len, EOM);
	if (p) {
	    *p = 0;
	    if (msgPtr) {
		*msgPtr = xmlParseMemory(s->str, strlen(s->str));
		return (*msgPtr != NULL);
	    }
	    // xxx move the contents in the buffer
	}
    }
}


static int
netconf_recv_hello(scli_interp_t *interp)
{
    xmlDocPtr hello;

    if (! netconf_next_msg(stdin, &hello)) {
	return SCLI_ERROR;
    }

    g_print("<!-- ok - get hello message -->\n");
    // validate the message, if failure close (?) the connection?
    
    if (hello) xmlFreeDoc(hello);
    return SCLI_OK;
}


int
scli_netconf_mainloop(scli_interp_t *interp)
{
    xmlDocPtr msg;
    
    netconf_send_hello(interp);
    if (netconf_recv_hello(interp) != SCLI_OK) {
	return SCLI_ERROR;
    }
    
    while (netconf_next_msg(stdin, &msg)) {

	g_print("scli_netconf_eval: ++++++++++++++++++++++++++++++++++++\n");
	
        xmlFreeDoc(msg);    
    }

    return SCLI_OK;
}
