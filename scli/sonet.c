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


static void
fmt_sonet_media(GString *s, sonet_mib_sonetMediumEntry_t *sonetMediumEntry)
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
    g_string_sprintfa(s, "%s", e ? e : "");

    g_string_append(s, "\n");
}



static int
show_sonet_media(scli_interp_t *interp, int argc, char **argv)
{
    sonet_mib_sonetMediumEntry_t **sonetMediumTable = NULL;
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
	g_string_sprintfa(interp->header,
			  "INTERFACE TYPE  CODING LINE-TYPE");
	for (i = 0; sonetMediumTable[i]; i++) {
	    fmt_sonet_media(interp->result, sonetMediumTable[i]);
	}
    }

    if (sonetMediumTable) sonet_mib_free_sonetMediumTable(sonetMediumTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



void
scli_init_sonet_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show sonet media", NULL,
	  "The `show sonet media' command displays information about ...\n",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_sonet_media },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t sonet_mode = {
	"sonet",
	"The sonet scli mode is based on the SONET-MIB as published\n"
	"in RFC 2558.",
	cmds
    };
    
    scli_register_mode(interp, &sonet_mode);
}
