/* 
 * ether.c -- scli ether mode implementation
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

#include "scli.h"

#include "mau-mib.h"
#include "etherlike-mib.h"



static void
show_ether_mau_info(GString *s, ifMauEntry_t *ifMauEntry)
{
    g_string_sprintfa(s, "%7u ", ifMauEntry->ifMauIfIndex);
    g_string_sprintfa(s, "%7u ", ifMauEntry->ifMauIndex);
    
    fmt_enum(s, 12, mau_mib_enums_ifMauStatus,
	     ifMauEntry->ifMauStatus);

    fmt_enum(s, 14, mau_mib_enums_ifMauMediaAvailable,
	     ifMauEntry->ifMauMediaAvailable);

    fmt_enum(s, 9, mau_mib_enums_ifMauJabberState,
	     ifMauEntry->ifMauJabberState);

    fmt_enum(s, 5, mau_mib_enums_ifMauAutoNegSupported,
	     ifMauEntry->ifMauAutoNegSupported);

    /* ifMauEntry->ifMauTypeListBits */

    /* foreach jack on this mau:
       ifJackEntry->ifJackType */

    /* auto negotiation information:
       ifMauAutoNegEntry->ifMauAutoNegAdminStatus
       ifMauAutoNegEntry->ifMauAutoNegRemoteSignaling
       ifMauAutoNegEntry->ifMauAutoNegConfig
       ifMauAutoNegEntry->ifMauAutoNegCapabilityBits
       ifMauAutoNegEntry->ifMauAutoNegCapAdvertisedBits
       ifMauAutoNegEntry->ifMauAutoNegCapReceivedBits
       ifMauAutoNegEntry->ifMauAutoNegRemoteFaultAdvertised
       ifMauAutoNegEntry->ifMauAutoNegRemoteFaultReceived
     */

    g_string_append(s, "\n");
}



static int
cmd_ether_mau_info(scli_interp_t *interp, int argc, char **argv)
{
    ifMauEntry_t **ifMauTable = NULL;
    ifJackEntry_t **ifJackTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (mau_mib_get_ifMauTable(interp->peer, &ifMauTable)) {
	return SCLI_ERROR;
    }

    (void) mau_mib_get_ifJackTable(interp->peer, &ifJackTable);

    if (ifMauTable) {
	g_string_sprintfa(interp->result,
		  "Interface   Mau Status      Media         Jabber   AutoNeg\n");
	for (i = 0; ifMauTable[i]; i++) {
	    show_ether_mau_info(interp->result, ifMauTable[i]);
	}
    }

    if (ifJackTable) mau_mib_free_ifJackTable(ifJackTable);
    if (ifMauTable) mau_mib_free_ifMauTable(ifMauTable);
    
    return SCLI_OK;
}



void
scli_init_ether_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show ethernet mau",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "ethernet medium attachment unit parameters",
	  cmd_ether_mau_info },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t ether_mode = {
	"ether",
	"scli mode to display and configure ethernet parameters",
	cmds
    };
    
    scli_register_mode(interp, &ether_mode);
}
