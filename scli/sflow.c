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
#include "sflow5-mib-proc.h"


static int
show_sflow_info(scli_interp_t *interp, int argc, char **argv)
{
    sflow5_mib_sFlowAgent_t *agent = NULL;
    int const indent = 17;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    sflow5_mib_get_sFlowAgent(interp->peer, &agent, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
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
    int const indent = 20;
    
    g_string_sprintfa(s, "%-*s%d\n",
		      indent, "sFlow Rcvr Index:",
		      rcvrEntry->sFlowRcvrIndex);

    if (rcvrEntry->sFlowRcvrOwner) {
	g_string_sprintfa(s, "%-*s%.*s\n",
			  indent, "sFlow Rcvr Owner:",
			  rcvrEntry->_sFlowRcvrOwnerLength,
			  rcvrEntry->sFlowRcvrOwner);
    }

    e = fmt_inet_address(rcvrEntry->sFlowRcvrAddressType,
			 rcvrEntry->sFlowRcvrAddress,
			 rcvrEntry->_sFlowRcvrAddressLength);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n",
			  indent, "sFlow Rcvr Addr:", e);
    }
    if (rcvrEntry->sFlowRcvrPort) {
	g_string_sprintfa(s, "%-*s%d\n",
			  indent, "sFlow Rcvr Port:",
			  *rcvrEntry->sFlowRcvrPort);
    }

    if (rcvrEntry->sFlowRcvrDatagramVersion) {
	g_string_sprintfa(s, "%-*s%d\n",
			  indent, "sFlow Rcvr Version:",
			  *rcvrEntry->sFlowRcvrDatagramVersion);
    }
    
    if (rcvrEntry->sFlowRcvrTimeout) {
	g_string_sprintfa(s, "%-*s%d [seconds]\n",
			  indent, "sFlow Rcvr Timeout:",
			  *rcvrEntry->sFlowRcvrTimeout);
    }

    if (rcvrEntry->sFlowRcvrMaximumDatagramSize) {
	g_string_sprintfa(s, "%-*s%d [bytes]\n",
			  indent, "sFlow Rcvr MaxSize:",
			  *rcvrEntry->sFlowRcvrMaximumDatagramSize);
    }
}



static int
show_sflow_receiver(scli_interp_t *interp, int argc, char **argv)
{
    sflow5_mib_sFlowRcvrEntry_t **rcvrEntry = NULL;
    int i, c;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    sflow5_mib_get_sFlowRcvrTable(interp->peer, &rcvrEntry, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
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



static int
create_sflow_receiver(scli_interp_t *interp, int argc, char **argv)
{
    GError *error = NULL;
    
    sflow5_mib_proc_create_receiver(interp->peer, "nase", 42, 11, 22, 33, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    return SCLI_OK;
}



static int
delete_sflow_receiver(scli_interp_t *interp, int argc, char **argv)
{
    // retrieve receiver, search owner matching regex (arg1), if
    // present check matching address regex (arg2), call delete proc
    // for each match
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

	{ "create sflow receiver", NULL,
	  "xxx",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  "sflow", NULL,
	  create_sflow_receiver },
	
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
