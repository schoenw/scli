/* 
 * sflow.c -- scli sflow mode implementation
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
 * @(#) $Id: udp.c 712 2004-10-14 20:51:26Z schoenw $
 */

#include "scli.h"

#include "sflow5-mib.h"



static int
show_sflow_info(scli_interp_t *interp, int argc, char **argv)
{
    sflow5_mib_sFlowAgent_t *agent = NULL;
    int const indent = 17;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    sflow5_mib_get_sFlowAgent(interp->peer, &agent, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (agent) {
	const char *e;
	
	if (agent->sFlowVersion) {
	    g_string_sprintfa(interp->result, "%-*s %.*s\n",
			      indent, "sFlow Version:",
			      agent->_sFlowVersionLength, agent->sFlowVersion);
	}

	e = fmt_inet_address(agent->sFlowAgentAddressType,
			     agent->sFlowAgentAddress,
			     agent->_sFlowAgentAddressLength);
	if (e) {
	    g_string_sprintfa(interp->result, "%-*s %s\n",
			      indent, "sFlow Address:", e);
	}
    }

    if (agent) sflow5_mib_free_sFlowAgent(agent);
    
    return SCLI_OK;
}



static void
fmt_sflow_receiver(GString *s, sflow5_mib_sFlowRcvrEntry_t *rcvrEntry)
{
    const char *e;
    
    g_string_sprintfa(s, "sFlow Rcvr Index: %d\n", rcvrEntry->sFlowRcvrIndex);

    if (rcvrEntry->sFlowRcvrOwner) {
	g_string_sprintfa(s, "sFlow Rcvr Owner: %.*s\n",
			  rcvrEntry->_sFlowRcvrOwnerLength,
			  rcvrEntry->sFlowRcvrOwner);
    }

    e = fmt_inet_address(rcvrEntry->sFlowRcvrAddressType,
			 rcvrEntry->sFlowRcvrAddress,
			 rcvrEntry->_sFlowRcvrAddressLength);
    if (e) {
	g_string_sprintfa(s, "sFlow Rcvr Addr: %s\n", e);
    }
    if (rcvrEntry->sFlowRcvrPort) {
	g_string_sprintfa(s, "sFlow Rcvr Port: %d\n",
			  *rcvrEntry->sFlowRcvrPort);
    }

    if (rcvrEntry->sFlowRcvrDatagramVersion) {
	g_string_sprintfa(s, "sFlow Rcvr Version: %d\n",
			  *rcvrEntry->sFlowRcvrDatagramVersion);
    }
    
    if (rcvrEntry->sFlowRcvrTimeout) {
	g_string_sprintfa(s, "sFlow Rcvr Timeout: %d [seconds]\n",
			  *rcvrEntry->sFlowRcvrTimeout);
    }

    if (rcvrEntry->sFlowRcvrMaximumDatagramSize) {
	g_string_sprintfa(s, "sFlow Rcvr MaxSize: %d [bytes]\n",
			  *rcvrEntry->sFlowRcvrMaximumDatagramSize);
    }
}



static int
show_sflow_receiver(scli_interp_t *interp, int argc, char **argv)
{
    sflow5_mib_sFlowRcvrEntry_t **rcvrEntry = NULL;
    int const indent = 17;
    int i, c;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    sflow5_mib_get_sFlowRcvrTable(interp->peer, &rcvrEntry, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (rcvrEntry) {
        for (i = 0, c = 0; rcvrEntry[i]; i++) {
	    if (i) g_string_append(interp->result, "\n");
	    fmt_sflow_receiver(interp->result, rcvrEntry[i]);
	}
    }

    if (rcvrEntry) sflow5_mib_free_sFlowRcvrTable(rcvrEntry);
    
    return SCLI_OK;
}



void
scli_init_sflow_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show sflow info", NULL,
	  "The `show sflow info' command displays information about\n"
	  "an sflow implementation.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  "sflow", NULL,
	  show_sflow_info },

	{ "show sflow receiver", NULL,
	  "The `show sflow receiver' command displays information about\n"
	  "sflow receivers.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  "sflow", NULL,
	  show_sflow_receiver },

	/* show sflow source */

	/* show sflow */
	
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t sflow_mode = {
	"udp",
	"The scli sflow mode is based on the SFLOW-MIB as published in\n"
	"RFC 3176 and the SFLOW5-MIB published on the slow.org web site. It\n"
	"provides commands to browse information specific to sflow probes.",
	cmds
    };
    
    scli_register_mode(interp, &sflow_mode);
}
