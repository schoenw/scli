/* 
 * isdn.c -- scli isdn mode implementation
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

#include "if-mib.h"
#include "isdn-mib.h"


static void
fmt_isdn_bri(GString *s, isdn_mib_isdnBasicRateEntry_t *briEntry,
	     if_mib_ifEntry_t *ifEntry)
{
    const char *e;
    
    g_string_sprintfa(s, "%9u ", briEntry->ifIndex);

    e = fmt_enum(isdn_mib_enums_isdnBasicRateIfType,
		 briEntry->isdnBasicRateIfType);
    g_string_sprintfa(s, "%-5s ", e ? e : "");
    
    e = fmt_enum(isdn_mib_enums_isdnBasicRateLineTopology,
		 briEntry->isdnBasicRateLineTopology);
    g_string_sprintfa(s, "%-17s ", e ? e : "");
    
    e = fmt_enum(isdn_mib_enums_isdnBasicRateIfMode,
		 briEntry->isdnBasicRateIfMode);
    g_string_sprintfa(s, " %-2s  ", e ? e : "");
    
    e = fmt_enum(isdn_mib_enums_isdnBasicRateSignalMode,
		 briEntry->isdnBasicRateSignalMode);
    g_string_sprintfa(s, "%-8s ", e ? e : "");
    
    if (ifEntry && ifEntry->ifDescr) {
	g_string_sprintfa(s, "%.*s",
			  (int) ifEntry->_ifDescrLength, ifEntry->ifDescr);
    }

    g_string_append(s, "\n");
}



static int
show_isdn_bri(scli_interp_t * interp, int argc, char **argv)
{
    isdn_mib_isdnBasicRateEntry_t **briTable = NULL;
    regex_t _regex_iface, *regex_iface = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], interp->regex_flags) != 0) {
	    g_string_assign(interp->result, argv[1]);
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_OK;
    }

    isdn_mib_get_isdnBasicRateTable(interp->peer, &briTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (briTable) {
	g_string_sprintfa(interp->header,
			  "INTERFACE TYPE  TOPOLOGY          MODE "
			  "SIGNAL   DESCRIPTION");
	for (i = 0; briTable[i]; i++) {
	    if_mib_ifEntry_t *ifEntry;
	    if_mib_get_ifEntry(interp->peer, &ifEntry,
			       briTable[i]->ifIndex, IF_MIB_IFDESCR);
	    if (interface_match(regex_iface, ifEntry)) {
		fmt_isdn_bri(interp->result, briTable[i], ifEntry);
	    }
	    if (ifEntry) if_mib_free_ifEntry(ifEntry);
	}
    }
    
    if (briTable)
	isdn_mib_free_isdnBasicRateTable(briTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



static void
fmt_isdn_bearer(GString *s, isdn_mib_isdnBearerEntry_t *bearerEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Interface:",
		      bearerEntry->ifIndex);

    e = fmt_enum(isdn_mib_enums_isdnBearerChannelType,
		 bearerEntry->isdnBearerChannelType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Channel Type:", e);
    }

    e = fmt_enum(isdn_mib_enums_isdnBearerOperStatus,
		 bearerEntry->isdnBearerOperStatus);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Status:", e);
    }

    if (bearerEntry->isdnBearerCallSetupTime) {
	e = fmt_timeticks(*bearerEntry->isdnBearerCallSetupTime);
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Setup:",
			  *bearerEntry->isdnBearerCallConnectTime ? e : "");
    }

    if (bearerEntry->isdnBearerCallConnectTime) {
	e = fmt_timeticks(*bearerEntry->isdnBearerCallConnectTime);
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Connect:",
			  *bearerEntry->isdnBearerCallConnectTime ? e : "");
    }

    if (bearerEntry->isdnBearerPeerAddress) {
	g_string_sprintfa(s, "%-*s %*s\n", indent, "Peer Address:",
			  bearerEntry->_isdnBearerPeerAddressLength,
			  bearerEntry->isdnBearerPeerAddress);
    }

    if (bearerEntry->isdnBearerPeerSubAddress) {
	g_string_sprintfa(s, "%-*s %*s\n", indent, "Peer SubAddress:",
			  bearerEntry->_isdnBearerPeerSubAddressLength,
			  bearerEntry->isdnBearerPeerSubAddress);
    }

    e = fmt_enum(isdn_mib_enums_isdnBearerCallOrigin,
		 bearerEntry->isdnBearerCallOrigin);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Origin:", e);
    }

    e = fmt_enum(isdn_mib_enums_isdnBearerInfoType,
		 bearerEntry->isdnBearerInfoType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Transfer Capability:", e);
    }

    if (bearerEntry->isdnBearerChargedUnits) {
	g_string_sprintfa(s, "%-*s %u\n", indent, "Charged Units:",
			  *bearerEntry->isdnBearerChargedUnits);
    }
}



static int
show_isdn_bearer(scli_interp_t * interp, int argc, char **argv)
{
    isdn_mib_isdnBearerEntry_t **bearerTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    isdn_mib_get_isdnBearerTable(interp->peer, &bearerTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (bearerTable) {
	for (i = 0; bearerTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_isdn_bearer(interp->result, bearerTable[i]);
	}
    }
    
    if (bearerTable)
	isdn_mib_free_isdnBearerTable(bearerTable);

    return SCLI_OK;
}



static void
fmt_isdn_endpoint(GString *s, isdn_mib_isdnEndpointEntry_t *endpointEntry)
{
    int const indent = 18;
    const char *e;

    if (endpointEntry->isdnEndpointIfIndex) {
	g_string_sprintfa(s, "%-*s %d\n", indent, "Interface:",
			  endpointEntry->isdnEndpointIfIndex);
    }

#if 0

    e = fmt_enum(isdn_mib_enums_isdnBearerChannelType,
		 bearerEntry->isdnBearerChannelType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Channel Type:", e);
    }

    e = fmt_enum(isdn_mib_enums_isdnBearerOperStatus,
		 bearerEntry->isdnBearerOperStatus);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Status:", e);
    }

    if (bearerEntry->isdnBearerCallSetupTime) {
	e = fmt_timeticks(*bearerEntry->isdnBearerCallSetupTime);
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Setup:",
			  *bearerEntry->isdnBearerCallConnectTime ? e : "");
    }

    if (bearerEntry->isdnBearerCallConnectTime) {
	e = fmt_timeticks(*bearerEntry->isdnBearerCallConnectTime);
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Connect:",
			  *bearerEntry->isdnBearerCallConnectTime ? e : "");
    }

    if (bearerEntry->isdnBearerPeerAddress) {
	g_string_sprintfa(s, "%-*s %*s\n", indent, "Peer Address:",
			  bearerEntry->_isdnBearerPeerAddressLength,
			  bearerEntry->isdnBearerPeerAddress);
    }

    if (bearerEntry->isdnBearerPeerSubAddress) {
	g_string_sprintfa(s, "%-*s %*s\n", indent, "Peer SubAddress:",
			  bearerEntry->_isdnBearerPeerSubAddressLength,
			  bearerEntry->isdnBearerPeerSubAddress);
    }

    e = fmt_enum(isdn_mib_enums_isdnBearerCallOrigin,
		 bearerEntry->isdnBearerCallOrigin);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Call Origin:", e);
    }

    e = fmt_enum(isdn_mib_enums_isdnBearerInfoType,
		 bearerEntry->isdnBearerInfoType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Transfer Capability:", e);
    }

    if (bearerEntry->isdnBearerChargedUnits) {
	g_string_sprintfa(s, "%-*s %u\n", indent, "Charged Units:",
			  *bearerEntry->isdnBearerChargedUnits);
    }
#endif
}



static int
show_isdn_endpoints(scli_interp_t * interp, int argc, char **argv)
{
    isdn_mib_isdnEndpointEntry_t **endpointTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    isdn_mib_get_isdnEndpointTable(interp->peer, &endpointTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (endpointTable) {
	for (i = 0; endpointTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_isdn_endpoint(interp->result, endpointTable[i]);
	}
    }
    
    if (endpointTable)
	isdn_mib_free_isdnEndpointTable(endpointTable);

    return SCLI_OK;
}



void
scli_init_isdn_mode(scli_interp_t * interp)
{
    static scli_cmd_t cmds[] = {

	{ "show isdn bri", "[<regexp>]",
	  "The `show isdn bri' command shows information about\n"
	  "the ISDN basic rate interfaces. The command outputs\n"
	  "a table which has the following columns:\n"
	  "\n"
	  "  INTERFACE   network interface number\n"
	  "  TYPE        type of the ISDN interface\n"
	  "  TOPOLOGY    line topology\n"
	  "  MODE        interface mode (te/nt)\n"
	  "  SIGNALING   signaling mode (active/inactive)\n"
	  "  DESCRIPTION description of the network interface",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_isdn_bri },

	{ "show isdn bearer", NULL,
	  "The `show isdn bearer' command shows information about\n"
	  "the ISDN B (bearer) channels.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_isdn_bearer },

	{ "show isdn endpoints", NULL,
	  "The `show isdn endpoints' command shows information about\n"
	  "the ISDN endpoints.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_isdn_endpoints },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };

    static scli_mode_t isdn_mode = {
	"isdn",
	"The scli isdn mode is based on the ISDN-MIB as published\n"
	"in RFC 2127.",
	cmds
    };

    scli_register_mode(interp, &isdn_mode);
}
