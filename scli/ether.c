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



static guint32 const dot3MauTypeAUI[]
	= { MAU_MIB_DOT3MAUTYPEAUI };
static guint32 const dot3MauType10Base5[]
	= { MAU_MIB_DOT3MAUTYPE10BASE5 };
static guint32 const dot3MauTypeFoirl[]
	= { MAU_MIB_DOT3MAUTYPEFOIRL };
static guint32 const dot3MauType10Base2[]
	= { MAU_MIB_DOT3MAUTYPE10BASE2 };
static guint32 const dot3MauType10BaseT[]
	= { MAU_MIB_DOT3MAUTYPE10BASET };
static guint32 const dot3MauType10BaseFP[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFP };
static guint32 const dot3MauType10BaseFB[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFB };
static guint32 const dot3MauType10BaseFL[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFL };
static guint32 const dot3MauType10Broad36[]
	= { MAU_MIB_DOT3MAUTYPE10BROAD36 };
static guint32 const dot3MauType10BaseTHD[]
	= { MAU_MIB_DOT3MAUTYPE10BASETHD };
static guint32 const dot3MauType10BaseTFD[]
	= { MAU_MIB_DOT3MAUTYPE10BASETFD };
static guint32 const dot3MauType10BaseFLHD[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFLHD };
static guint32 const dot3MauType10BaseFLFD[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFLFD };
static guint32 const dot3MauType100BaseT4[]
	= { MAU_MIB_DOT3MAUTYPE100BASET4 };
static guint32 const dot3MauType100BaseTXHD[]
	= { MAU_MIB_DOT3MAUTYPE100BASETXHD };
static guint32 const dot3MauType100BaseTXFD[]
	= { MAU_MIB_DOT3MAUTYPE100BASETXFD };
static guint32 const dot3MauType100BaseFXHD[]
	= { MAU_MIB_DOT3MAUTYPE100BASEFXHD };
static guint32 const dot3MauType100BaseFXFD[]
	= { MAU_MIB_DOT3MAUTYPE100BASEFXFD };
static guint32 const dot3MauType100BaseT2HD[]
	= { MAU_MIB_DOT3MAUTYPE100BASET2HD };
static guint32 const dot3MauType100BaseT2FD[]
	= { MAU_MIB_DOT3MAUTYPE100BASET2FD };
static guint32 const dot3MauType1000BaseXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASEXHD };
static guint32 const dot3MauType1000BaseXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASEXFD };
static guint32 const dot3MauType1000BaseLXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASELXHD };
static guint32 const dot3MauType1000BaseLXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASELXFD };
static guint32 const dot3MauType1000BaseSXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASESXHD };
static guint32 const dot3MauType1000BaseSXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASESXFD };
static guint32 const dot3MauType1000BaseCXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASECXHD };
static guint32 const dot3MauType1000BaseCXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASECXFD };
static guint32 const dot3MauType1000BaseTHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASETHD };
static guint32 const dot3MauType1000BaseTFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASETFD };

stls_identity_t const mau_type_identities[] = {
    { dot3MauTypeAUI,
      sizeof(dot3MauTypeAUI)/sizeof(guint32),
      "AUI" },
    { dot3MauType10Base5,
      sizeof(dot3MauType10Base5)/sizeof(guint32),
      "10Base5" },
    { dot3MauTypeFoirl,
      sizeof(dot3MauTypeFoirl)/sizeof(guint32),
      "Foirl" },
    { dot3MauType10Base2,
      sizeof(dot3MauType10Base2)/sizeof(guint32),
      "10Base2" },
    { dot3MauType10BaseT,
      sizeof(dot3MauType10BaseT)/sizeof(guint32),
      "10BaseT" },
    { dot3MauType10BaseFP,
      sizeof(dot3MauType10BaseFP)/sizeof(guint32),
      "10BaseFP" },
    { dot3MauType10BaseFB,
      sizeof(dot3MauType10BaseFB)/sizeof(guint32),
      "10BaseFB" },
    { dot3MauType10BaseFL,
      sizeof(dot3MauType10BaseFL)/sizeof(guint32),
      "10BaseFL" },
    { dot3MauType10Broad36,
      sizeof(dot3MauType10Broad36)/sizeof(guint32),
      "10Broad36" },
    { dot3MauType10BaseTHD,
      sizeof(dot3MauType10BaseTHD)/sizeof(guint32),
      "10BaseTHD" },
    { dot3MauType10BaseTFD,
      sizeof(dot3MauType10BaseTFD)/sizeof(guint32),
      "10BaseTFD" },
    { dot3MauType10BaseFLHD,
      sizeof(dot3MauType10BaseFLHD)/sizeof(guint32),
      "10BaseFLHD" },
    { dot3MauType10BaseFLFD,
      sizeof(dot3MauType10BaseFLFD)/sizeof(guint32),
      "10BaseFLFD" },
    { dot3MauType100BaseT4,
      sizeof(dot3MauType100BaseT4)/sizeof(guint32),
      "100BaseT4" },
    { dot3MauType100BaseTXHD,
      sizeof(dot3MauType100BaseTXHD)/sizeof(guint32),
      "100BaseTXHD" },
    { dot3MauType100BaseTXFD,
      sizeof(dot3MauType100BaseTXFD)/sizeof(guint32),
      "100BaseTXFD" },
    { dot3MauType100BaseFXHD,
      sizeof(dot3MauType100BaseFXHD)/sizeof(guint32),
      "100BaseFXHD" },
    { dot3MauType100BaseFXFD,
      sizeof(dot3MauType100BaseFXFD)/sizeof(guint32),
      "100BaseFXFD" },
    { dot3MauType100BaseT2HD,
      sizeof(dot3MauType100BaseT2HD)/sizeof(guint32),
      "100BaseT2HD" },
    { dot3MauType100BaseT2FD,
      sizeof(dot3MauType100BaseT2FD)/sizeof(guint32),
      "100BaseT2FD" },
    { dot3MauType1000BaseXHD,
      sizeof(dot3MauType1000BaseXHD)/sizeof(guint32),
      "1000BaseXHD" },
    { dot3MauType1000BaseXFD,
      sizeof(dot3MauType1000BaseXFD)/sizeof(guint32),
      "1000BaseXFD" },
    { dot3MauType1000BaseLXHD,
      sizeof(dot3MauType1000BaseLXHD)/sizeof(guint32),
      "1000BaseLXHD" },
    { dot3MauType1000BaseLXFD,
      sizeof(dot3MauType1000BaseLXFD)/sizeof(guint32),
      "1000BaseLXFD" },
    { dot3MauType1000BaseSXHD,
      sizeof(dot3MauType1000BaseSXHD)/sizeof(guint32),
      "1000BaseSXHD" },
    { dot3MauType1000BaseSXFD,
      sizeof(dot3MauType1000BaseSXFD)/sizeof(guint32),
      "1000BaseSXFD" },
    { dot3MauType1000BaseCXHD,
      sizeof(dot3MauType1000BaseCXHD)/sizeof(guint32),
      "1000BaseCXHD" },
    { dot3MauType1000BaseCXFD,
      sizeof(dot3MauType1000BaseCXFD)/sizeof(guint32),
      "1000BaseCXFD" },
    { dot3MauType1000BaseTHD,
      sizeof(dot3MauType1000BaseTHD)/sizeof(guint32),
      "1000BaseTHD" },
    { dot3MauType1000BaseTFD,
      sizeof(dot3MauType1000BaseTFD)/sizeof(guint32),
      "1000BaseTFD" },
    { 0, 0, NULL }
};


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

    fmt_enum(s, 7, mau_mib_enums_ifMauAutoNegSupported,
	     ifMauEntry->ifMauAutoNegSupported);

    if (ifMauEntry->ifMauType) {
	g_string_sprintfa(s, " %s", 
		  stls_identity_get_label(mau_type_identities,
					  ifMauEntry->ifMauType,
					  ifMauEntry->_ifMauTypeLength));
    }

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
		  "Interface   Mau Status      Media         Jabber   AutoNeg Type\n");
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
