/* 
 * sonet.c -- scli sonet mode implementation
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
#include "sonet-mib.h"


static GSnmpEnum const sonetMediumType[] = {
    { SONET_MIB_SONETMEDIUMTYPE_SONET, "SONET" },
    { SONET_MIB_SONETMEDIUMTYPE_SDH,   "SDH" },
    { 0, NULL }
};

static GSnmpEnum const sonetMediumLineCoding[] = {
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMOTHER, "other" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMB3ZS,  "B3ZS" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMCMI,   "CMI" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMNRZ,   "NRZ" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMRZ,    "RZ" },
    { 0, NULL }
};

static GSnmpEnum const sonetMediumLineType[] = {
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETOTHER,           "other" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETSHORTSINGLEMODE, "ShortSingleMode" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETLONGSINGLEMODE,  "LongSingleMode" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETMULTIMODE,       "MultiMode" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETCOAX,            "Coax" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETUTP,             "UTP" },
    { 0, NULL }
};



static int
get_line_type_width(sonet_mib_sonetMediumEntry_t **sonetMediumTable)
{
    int i, line_type_width = 9;

    if (sonetMediumTable) {
	for (i = 0; sonetMediumTable[i]; i++) {
	    if (sonetMediumTable[i]->sonetMediumLineType) {
		char const *label;
		label = fmt_enum(sonetMediumLineType,
				 sonetMediumTable[i]->sonetMediumLineType);
		if (label && strlen(label) > line_type_width) {
		    line_type_width = strlen(label);
		}
	    }
	}
    }
    return line_type_width;
}



static void
fmt_sonet_media(GString *s, sonet_mib_sonetMediumEntry_t *sonetMediumEntry,
		if_mib_ifEntry_t *ifEntry, int line_type_width)
{
    const char *e;
    
    g_string_sprintfa(s, "%9u ", sonetMediumEntry->ifIndex);

    e = fmt_enum(sonetMediumType,
		 sonetMediumEntry->sonetMediumType);
    g_string_sprintfa(s, "%-5s ", e ? e : "");

    e = fmt_enum(sonetMediumLineCoding,
		 sonetMediumEntry->sonetMediumLineCoding);
    g_string_sprintfa(s, "%-5s  ", e ? e : "");

    e = fmt_enum(sonetMediumLineType,
		 sonetMediumEntry->sonetMediumLineType);
    g_string_sprintfa(s, "%-*s ", line_type_width, e ? e : "");
    
    if (ifEntry && ifEntry->ifDescr) {
	g_string_sprintfa(s, "%.*s",
			  (int) ifEntry->_ifDescrLength, ifEntry->ifDescr);
    }

    g_string_append(s, "\n");
}



static int
show_sonet_media(scli_interp_t *interp, int argc, char **argv)
{
    sonet_mib_sonetMediumEntry_t **sonetMediumTable = NULL;
    int line_type_width;
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

    sonet_mib_get_sonetMediumTable(interp->peer, &sonetMediumTable, 0);
    if (interp->peer->error_status) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_SNMP;
    }

    if (sonetMediumTable) {
	if_mib_ifEntry_t *ifEntry;
	g_string_sprintfa(interp->header,
			  "INTERFACE TYPE  CODING LINE-TYPE");
	for (i = 0; sonetMediumTable[i]; i++) {
	    if_mib_get_ifEntry(interp->peer, &ifEntry,
			       sonetMediumTable[i]->ifIndex, IF_MIB_IFDESCR);
	    line_type_width = get_line_type_width(sonetMediumTable);
	    if (interface_match(regex_iface, ifEntry)) {
		fmt_sonet_media(interp->result, sonetMediumTable[i], ifEntry,
				line_type_width);
	    }
	    if (ifEntry) {
		if_mib_free_ifEntry(ifEntry);
	    }
	}
    }

    if (sonetMediumTable) sonet_mib_free_sonetMediumTable(sonetMediumTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



/*
$ show sonet section stats

INTERFACE INTERVAL LOST   ES  SES SEFS   CV DESCRIPTION
        4     666s  --  ---- ---- ---- ---- ATM/0
        5     123s  --  ---- ---- ---- ---- ATM/1

$ show sonet section history

INTERFACE INTERVAL LOST   ES  SES SEFS   CV DESCRIPTION
        4     15m   SF  ---- ---- ---- ---- ATM/0
        4     30m   --  ---- ---- ---- ---- ATM/0
        4     45m   --  ---- ---- ---- ---- ATM/0
        4     60m   --  ---- ---- ---- ---- ATM/0
*/

static void
fmt_sonet_section_stats(GString *s,
			sonet_mib_sonetSectionCurrentEntry_t *sonetSectionEntry)
{
    const char *e;
    
    g_string_sprintfa(s, "%9u ", sonetSectionEntry->ifIndex);

    g_string_sprintfa(s, "%8s ", "");

    if (sonetSectionEntry->sonetSectionCurrentStatus) {
	gint32 t = *sonetSectionEntry->sonetSectionCurrentStatus;
	g_string_sprintfa(s, " %c%c  ",
			  (t == 0x02) ? 'S' : '-',
			  (t == 0x04) ? 'F' : '-');
	
    } else {
	g_string_sprintfa(s, " %2s  ", "");
    }

    if (sonetSectionEntry->sonetSectionCurrentESs) {
	e = fmt_kmg(*sonetSectionEntry->sonetSectionCurrentESs);
	g_string_sprintfa(s, "%5s ", e);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }

    if (sonetSectionEntry->sonetSectionCurrentSESs) {
	e = fmt_kmg(*sonetSectionEntry->sonetSectionCurrentSESs);
	g_string_sprintfa(s, "%5s ", e);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }

    if (sonetSectionEntry->sonetSectionCurrentSESs) {
	e = fmt_kmg(*sonetSectionEntry->sonetSectionCurrentSESs);
	g_string_sprintfa(s, "%5s ", e);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }

    if (sonetSectionEntry->sonetSectionCurrentSEFSs) {
	e = fmt_kmg(*sonetSectionEntry->sonetSectionCurrentSEFSs);
	g_string_sprintfa(s, "%5s ", e);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }

    g_string_append(s, "\n");
}



static int
show_sonet_section_stats(scli_interp_t *interp, int argc, char **argv)
{
    sonet_mib_sonetSectionCurrentEntry_t **sonetSectionTable = NULL;
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

    sonet_mib_get_sonetSectionCurrentTable(interp->peer, &sonetSectionTable, 0);
    if (interp->peer->error_status) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_SNMP;
    }

    if (sonetSectionTable) {
	g_string_sprintfa(interp->header,
			  "INTERFACE INTERVAL LOST    ES   SES  SEFS    CV DESCRIPTION");
	for (i = 0; sonetSectionTable[i]; i++) {
	    fmt_sonet_section_stats(interp->result, sonetSectionTable[i]);
	}
    }

    if (sonetSectionTable)
	sonet_mib_free_sonetSectionCurrentTable(sonetSectionTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}


void
scli_init_sonet_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show sonet media", "[<regexp>]",
	  "The `show sonet media' command displays information about the\n"
	  "configuration of SONET/SDH interfaces.\n",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_sonet_media },

	{ "show sonet section stats", NULL,
	  "The `show sonet section stats' command displays statistics\n"
	  "about SONET/SDH section errors. The command outputs a table\n"
	  "which has the following columns:\n"
	  "\n"
	  "  INTERFACE	 network interface number\n"
	  "  INTERVAL    xxx\n"
	  "  LOST        xxx\n"
	  "  ES          errored seconds\n"
	  "  SES	 severely errored seconds\n"
	  "  SEFS	 severely errored framing seconds\n"
	  "  CV          coding violations\n"
	  "  DESCRIPTION description of the network interface",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_sonet_section_stats },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t sonet_mode = {
	"sonet",
	"The sonet scli mode is based on the SONET-MIB as published\n"
	"in RFC 2558. It provides commands to manage Synchronous Optical\n"
	"Network/Synchronous Digital Hierarchy (SONET/SDH) interfaces.",
	cmds
    };
    
    scli_register_mode(interp, &sonet_mode);
}
