/* 
 * entity.c -- scli snmp mode implementation
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


static void
fmt_string(GString *s, char *label, int width, guchar *string, gsize len)
{
    if (string) {
	g_string_sprintfa(s, "%-*s %.*s", width, label, (int) len, string);
    }
}


static int
cmd_snmp(scli_interp_t *interp, int argc, char **argv)
{
    snmpEngine_t *snmpEngine;
    sysOREntry_t **sysOREntry;
    GString *s;
    int i;
    int const indent = 18;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (snmp_framework_mib_get_snmpEngine(interp->peer, &snmpEngine)) {
	return SCLI_ERROR;
    }

    s = interp->result;
    if (snmpEngine) {
	if (snmpEngine->snmpEngineBoots) {
	    g_string_sprintfa(s, "Boots: %u times\n",
			      *(snmpEngine->snmpEngineBoots));
	}
	if (snmpEngine->snmpEngineTime) {
	    g_string_sprintfa(s, "Time: %u seconds since last change of boots\n",
			      *(snmpEngine->snmpEngineTime));
	}
	if (snmpEngine->snmpEngineMaxMessageSize) {
	    g_string_sprintfa(s, "MMSZ: %u byte\n",
			      *(snmpEngine->snmpEngineMaxMessageSize));
	}
	snmp_framework_mib_free_snmpEngine(snmpEngine);
    }
    
    if (snmpv2_mib_get_sysOREntry(interp->peer, &sysOREntry)) {
	return SCLI_ERROR;
    }

    if (sysOREntry) {
	for (i = 0; sysOREntry[i]; i++) {
	    g_string_sprintfa(s, "%3d: %.*s\n",
			      *(sysOREntry[i]->sysORIndex),
			      (int) sysOREntry[i]->_sysORDescrLength,
			      sysOREntry[i]->sysORDescr);
	}
	snmpv2_mib_free_sysOREntry(sysOREntry);
    }
    
    return SCLI_OK;
}



void
scli_init_snmp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "snmp", NULL, NULL },
	{ "show snmp", "engine",
	  "show information about the snmp engine", cmd_snmp },
	{ NULL, NULL, NULL, NULL }
    };
    
    static scli_mode_t snmp_mode = {
	"snmp",
	"scli mode to display and configure snmp specific information",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &snmp_mode);
}
