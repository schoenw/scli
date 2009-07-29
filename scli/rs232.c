/* 
 * rs232.c -- scli rs232 mode implementation
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

#include "scli.h"

#include "rs-232-mib.h"


static void
fmt_rs232_detail(GString *s, rs_232_mib_rs232PortEntry_t *portEntry,
		 rs_232_mib_rs232AsyncPortEntry_t *asyncPortEntry,
		 rs_232_mib_rs232SyncPortEntry_t *syncPortEntry)
{
    const char *e;
    int const indent = 18;

    g_string_sprintfa(s, "%-*s%d\n", indent, "Interface:",
		      portEntry->rs232PortIndex);

    e = fmt_enum(rs_232_mib_enums_rs232PortType, portEntry->rs232PortType);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Port Type:", e);
    }

    if (portEntry->rs232PortInSpeed) {
	g_string_sprintfa(s, "%-*s%d bps\n", indent, "Speed In:",
			  *portEntry->rs232PortInSpeed);
    }

    if (portEntry->rs232PortOutSpeed) {
	g_string_sprintfa(s, "%-*s%d bps\n", indent, "Speed Out:",
			  *portEntry->rs232PortOutSpeed);
    }

    e = fmt_enum(rs_232_mib_enums_rs232PortInFlowType,
		 portEntry->rs232PortInFlowType);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Flow Control In:", e);
    }

    e = fmt_enum(rs_232_mib_enums_rs232PortOutFlowType,
		 portEntry->rs232PortOutFlowType);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Flow Control Out:", e);
    }

    if (asyncPortEntry) {

	if (asyncPortEntry->rs232AsyncPortBits) {
	    g_string_sprintfa(s, "%-*s%d\n", indent, "Data Bits:",
			      *asyncPortEntry->rs232AsyncPortBits);
	}

	e = fmt_enum(rs_232_mib_enums_rs232AsyncPortStopBits,
		     asyncPortEntry->rs232AsyncPortStopBits);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Stop Bits:", e);
	}

	e = fmt_enum(rs_232_mib_enums_rs232AsyncPortParity,
		     asyncPortEntry->rs232AsyncPortParity);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Parity:", e);
	}

	e = fmt_enum(rs_232_mib_enums_rs232AsyncPortAutobaud,
		     asyncPortEntry->rs232AsyncPortAutobaud);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Autobaud:", e);
	}
    }

    if (syncPortEntry) {

	e = fmt_enum(rs_232_mib_enums_rs232SyncPortClockSource,
		     syncPortEntry->rs232SyncPortClockSource);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Clock Source:", e);
	}

	e = fmt_enum(rs_232_mib_enums_rs232SyncPortRole,
		     syncPortEntry->rs232SyncPortRole);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Port Role:", e);
	}
	
	e = fmt_enum(rs_232_mib_enums_rs232SyncPortEncoding,
		     syncPortEntry->rs232SyncPortEncoding);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Port Encoding:", e);
	}
	
	e = fmt_enum(rs_232_mib_enums_rs232SyncPortRTSControl,
		     syncPortEntry->rs232SyncPortRTSControl);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Port RTS Control:", e);
	}
	
	if (syncPortEntry->rs232SyncPortRTSCTSDelay) {
	    g_string_sprintfa(s, "%-*s%d ms\n", indent, "Port RTSCTS Delay:",
			      *syncPortEntry->rs232SyncPortRTSCTSDelay);
	}

	e = fmt_enum(rs_232_mib_enums_rs232SyncPortMode,
		     syncPortEntry->rs232SyncPortMode);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Port Mode:", e);
	}
	
	e = fmt_enum(rs_232_mib_enums_rs232SyncPortIdlePattern,
		     syncPortEntry->rs232SyncPortIdlePattern);
	if (e) {
	    g_string_sprintfa(s, "%-*s%s\n", indent, "Idle Pattern:", e);
	}
	
	if (syncPortEntry->rs232SyncPortMinFlags) {
	    g_string_sprintfa(s, "%-*s%d ms\n", indent, "Port Min Flags:",
			      *syncPortEntry->rs232SyncPortMinFlags);
	}
    }
}



static int
show_rs232_details(scli_interp_t *interp, int argc, char **argv)
{
    rs_232_mib_rs232PortEntry_t **portTable = NULL;
    rs_232_mib_rs232AsyncPortEntry_t **asyncPortTable = NULL;
    rs_232_mib_rs232SyncPortEntry_t **syncPortTable = NULL;
    int i, j;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rs_232_mib_get_rs232PortTable(interp->peer, &portTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    rs_232_mib_get_rs232AsyncPortTable(interp->peer, &asyncPortTable, 0, NULL);
    rs_232_mib_get_rs232SyncPortTable(interp->peer, &syncPortTable, 0, NULL);

    if (portTable) {
	for (i = 0; portTable[i]; i++) {
	    rs_232_mib_rs232AsyncPortEntry_t *asyncPortEntry = NULL;
	    rs_232_mib_rs232SyncPortEntry_t *syncPortEntry = NULL;
	    if (asyncPortTable) {
		for (j = 0; asyncPortTable[j]; j++) {
		    if (asyncPortTable[j]->rs232AsyncPortIndex
			== portTable[i]->rs232PortIndex) {
			asyncPortEntry = asyncPortTable[j];
			break;
		    }
		}
	    }
	    if (syncPortTable) {
		for (j = 0; syncPortTable[j]; j++) {
		    if (syncPortTable[j]->rs232SyncPortIndex
			== portTable[i]->rs232PortIndex) {
			syncPortEntry = syncPortTable[j];
			break;
		    }
		}
	    }
	    if (i) g_string_append(interp->result, "\n");
	    fmt_rs232_detail(interp->result, portTable[i],
			     asyncPortEntry, syncPortEntry);
	}
    }

    if (syncPortTable) rs_232_mib_free_rs232SyncPortTable(syncPortTable);
    if (asyncPortTable) rs_232_mib_free_rs232AsyncPortTable(asyncPortTable);
    if (portTable) rs_232_mib_free_rs232PortTable(portTable);
    
    return SCLI_OK;
}



void
scli_init_rs232_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show rs232 details", NULL,
	  "The `show rs232 details' command describes the selected RS 232\n"
	  "interfaces in detail.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rs232_details },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t rs232_mode = {
	"rs232",
	"The rs232 scli mode is based on the RS-232-MIB as published\n"
	"in RFC 1659.",
	cmds
    };
    
    scli_register_mode(interp, &rs232_mode);
}
