/* 
 * ospf.c -- scli ospf mode implementation
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

#include "ip-mib.h"
#include "if-mib.h"
#include "ospf-mib.h"



static int
cmd_ospf_info(scli_interp_t *interp, int argc, char **argv)
{
   ospf_mib_ospfGeneralGroup_t *ospfGeneralGroup = NULL;

   g_return_val_if_fail(interp, SCLI_ERROR);

   if (ospf_mib_get_ospfGeneralGroup(interp->peer, &ospfGeneralGroup)) {
       return SCLI_ERROR;
   }

   if (ospfGeneralGroup) {
       if (ospfGeneralGroup->ospfRouterId) {
           g_string_sprintfa(interp->result, "Router-ID: %s\n",
	   	fmt_ipv4_address(ospfGeneralGroup->ospfRouterId,
				 SCLI_FMT_NAME_OR_ADDR));
       }

       if (ospfGeneralGroup->ospfAdminStat) {
           g_string_append(interp->result, "AdminStatus: ");
           fmt_enum(interp->result, 8, ospf_mib_enums_ospfIfAdminStat,
           	ospfGeneralGroup->ospfAdminStat);
           g_string_append(interp->result, "\n");
       }

       if (ospfGeneralGroup->ospfVersionNumber) {
           g_string_sprintfa(interp->result, "OSPF protocol version: %u\n", 
	       *ospfGeneralGroup->ospfVersionNumber);
       }

       if (ospfGeneralGroup->ospfAreaBdrRtrStatus && 
	   *ospfGeneralGroup->ospfAreaBdrRtrStatus == 1) {
           g_string_sprintfa(interp->result,
	   	"This router is an ABR (area border router).\n");
       }
       if (ospfGeneralGroup->ospfASBdrRtrStatus &&
           *ospfGeneralGroup->ospfASBdrRtrStatus == 1) {
           g_string_sprintfa(interp->result,
	   	"This router is an ASBR (Autonomous System border router).\n");
       }

       if (ospfGeneralGroup->ospfExternLsaCount) {
           g_string_sprintfa(interp->result,
	   	"Number of external link-state advertisements: %u\n", 
		*ospfGeneralGroup->ospfExternLsaCount);
       }

       if (ospfGeneralGroup->ospfExternLsaCksumSum) {
	   g_string_sprintfa(interp->result,
		"Sum of Link-state checksum: %u\n", 
		*ospfGeneralGroup->ospfExternLsaCksumSum);
       }

       if (ospfGeneralGroup->ospfTOSSupport && 
           (*ospfGeneralGroup->ospfTOSSupport == 1)) {
           g_string_sprintfa(interp->result,
		"This router supports TOS routing.\n");
       }

       if (ospfGeneralGroup->ospfOriginateNewLsas) {
           g_string_sprintfa(interp->result,
	        "Number of advertised LSAs: %u\n", 
		*ospfGeneralGroup->ospfOriginateNewLsas);
       }

       if (ospfGeneralGroup->ospfRxNewLsas) {
           g_string_sprintfa(interp->result,
	   	"Number of received LSAs: %u\n", 
		*ospfGeneralGroup->ospfRxNewLsas);
       }

       if (ospfGeneralGroup->ospfExtLsdbLimit) {
           g_string_append(interp->result, 
	        "Maximum number of AS-external-LSAs entries: ");
           if (*ospfGeneralGroup->ospfExtLsdbLimit == -1) {
	       g_string_append(interp->result, "unlimited\n");
           } else {
               g_string_sprintfa(interp->result, "%u\n", 
	            *ospfGeneralGroup->ospfExtLsdbLimit);
           }
       }

       /* MISSING: ospfMulticastExtensions ::= { ospfGeneralGroup 12 } */
    
       if (ospfGeneralGroup->ospfExitOverflowInterval) { 
           g_string_append(interp->result, "Leave Overflow state: "); 
           if (*ospfGeneralGroup->ospfExitOverflowInterval > 0) { 
               g_string_sprintfa(interp->result, "after %u sec.\n", 
		    *ospfGeneralGroup->ospfExitOverflowInterval);
           } else {
	       g_string_append(interp->result, "never\n");
           }
       }

       if (ospfGeneralGroup->ospfDemandExtensions &&
	   *ospfGeneralGroup->ospfDemandExtensions == 1) {
         g_string_sprintfa(interp->result,"This router supports demand routing.\n");
       }
   }

   if (ospfGeneralGroup) ospf_mib_free_ospfGeneralGroup(ospfGeneralGroup);
   
   return SCLI_OK;
}



static void
show_ospf_area(GString *s, ospf_mib_ospfAreaEntry_t *ospfAreaEntry)
{
    g_string_append(s, "\nArea: ");
    if (ospfAreaEntry->ospfAreaId) {
	g_string_sprintfa(s,"%-15s", 
			  fmt_ipv4_address(ospfAreaEntry->ospfAreaId,
					   SCLI_FMT_NAME_OR_ADDR));
    } else {
	g_string_append(s, "?   ");
    }
    
    g_string_append(s, "Area status: ");
    if (ospfAreaEntry->ospfAreaStatus) {
	fmt_enum(s, 13, ospf_mib_enums_ospfAreaStatus,
		 ospfAreaEntry->ospfAreaStatus);
    } else {
	g_string_append(s, "?");
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Auth-Type: ");
    if (ospfAreaEntry->ospfAuthType) {
	switch (*ospfAreaEntry->ospfAuthType) {
	case 0:
	    g_string_append(s, "none  ");
	    break;
	case 1:
	    g_string_append(s, "pwd   ");
	    break;
	case 2:
	    g_string_append(s, "md5   ");
	    break;
	default:
	    g_string_append(s, "?     ");
	    break;
	}
    } else {
	g_string_append(s, "?     ");
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "AS external LSAs: ");
    if (ospfAreaEntry->ospfImportAsExtern) {	 
	fmt_enum(s, 16, ospf_mib_enums_ospfImportAsExtern,
		 ospfAreaEntry->ospfImportAsExtern);
    } else {
	g_string_append(s, "?");
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Send summary LSAs: ");
    if (ospfAreaEntry->ospfAreaSummary) {
	switch (*ospfAreaEntry->ospfAreaSummary) {
	case 1:
	    g_string_append(s, "no  ");
	    break;
	case 2:
	    g_string_append(s, "yes ");
	    break;
	default:
	    g_string_append(s, "?   ");
	    break;
	}
    } else {
	g_string_append(s, "?");
    }
    g_string_append(s, "\n\n");
    
    g_string_append(s, "SPF    ABR    ASBR   LSA    checksum\n");
    /* No of times of SPF calculation */
    if (ospfAreaEntry->ospfSpfRuns) {
	g_string_sprintfa(s,"%-5u  ", *ospfAreaEntry->ospfSpfRuns);
    } else {
	g_string_sprintfa(s,"%-5s  ", "?");
    }
    
    /* No of ABRs in this area */
    if (ospfAreaEntry->ospfAreaBdrRtrCount) {
	g_string_sprintfa(s,"%-5u  ", *ospfAreaEntry->ospfAreaBdrRtrCount);
    } else {
	g_string_sprintfa(s,"%-5s  ", "?");
    }
    
    /* No of ASBRs in this area */
    if (ospfAreaEntry->ospfAsBdrRtrCount) {
	g_string_sprintfa(s,"%-5u  ", *ospfAreaEntry->ospfAsBdrRtrCount);
    } else {
	g_string_sprintfa(s,"%-5s  ", "?");
    }
    
    /* No of LSAs in database */
    if (ospfAreaEntry->ospfAreaLsaCount) {
	g_string_sprintfa(s,"%-5u  ", *ospfAreaEntry->ospfAreaLsaCount);
    } else {
	g_string_sprintfa(s,"%-5s  ", "?");
    }
    
    /* LSA database checksum */
    if (ospfAreaEntry->ospfAreaLsaCksumSum) {
	g_string_sprintfa(s,"%-5u  ", *ospfAreaEntry->ospfAreaLsaCksumSum);
    } else {
	g_string_sprintfa(s,"%-5s  ", "?");
    }
    g_string_append(s, "\n");
}



static int
cmd_ospf_area(scli_interp_t *interp, int argc, char **argv)
{
   int i;
   ospf_mib_ospfAreaEntry_t **ospfAreaTable = NULL;

   g_return_val_if_fail(interp, SCLI_ERROR);

   if (ospf_mib_get_ospfAreaTable(interp->peer, &ospfAreaTable)) {
       return SCLI_ERROR;
   }

   if (ospfAreaTable) {
       for (i = 0; ospfAreaTable[i]; i++) {
	   if (i) {
	       g_string_append(interp->result, "\n");
	   }
	   show_ospf_area(interp->result, ospfAreaTable[i]);
       }
   }

   if (ospfAreaTable) ospf_mib_free_ospfAreaTable(ospfAreaTable);

   return SCLI_OK;
}



static void
show_ospf_interfaces(GString *s, ospf_mib_ospfIfEntry_t *ospfIfEntry,
		     ifEntry_t **ifTable, ifXEntry_t **ifXTable,
		     ipAddrEntry_t **ipAddrTable)
{
    int j;
    
    if (ospfIfEntry->ospfAddressLessIf
	&& (ospfIfEntry->ospfAddressLessIf > 0)) {
	
	if (ifXTable) {
	    for (j = 0; ifXTable[j]; j++) {
		if (ifXTable[j]->ifIndex == ospfIfEntry->ospfAddressLessIf) {
	            g_string_sprintfa(s, "Interface: %.*s\n", 
				      (int) ifXTable[j]->_ifNameLength,
				      ifXTable[j]->ifName);
		    break;
		}
	    }
	} else if (ifTable) {
	    for (j = 0; ifTable[j]; j++) {
		if (ifTable[j]->ifIndex == ospfIfEntry->ospfAddressLessIf) {
                    g_string_sprintfa(s, "Interface: %.*s\n", 
				      (int) ifTable[j]->_ifDescrLength,
				      ifTable[j]->ifDescr);
		    break;
		}
	    }
	} 
	
	if (ipAddrTable) {
	    for (j = 0; ipAddrTable[j]; j++) {
		if (ipAddrTable[j]->ipAdEntIfIndex &&
		    (ospfIfEntry->ospfAddressLessIf == 
		     *(ipAddrTable[j]->ipAdEntIfIndex))) {
		    g_string_sprintfa(s, "IP Address: %s\n", 
		      fmt_ipv4_address(ipAddrTable[j]->ipAdEntAddr,
				       SCLI_FMT_NAME_OR_ADDR));
		    break;
		}
	    }
	}
    } else if (ospfIfEntry->ospfIfIpAddress) {
	g_string_sprintfa(s,"IP Address: %s\n", 
			  fmt_ipv4_address(ospfIfEntry->ospfIfIpAddress,
					   SCLI_FMT_NAME_OR_ADDR));
    } 
    
    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, 16, ospf_mib_enums_ospfIfAdminStat,
	     ospfIfEntry->ospfIfAdminStat);
    g_string_append(s, "\n");
    
    g_string_append(s, "IfType: ");
    if (ospfIfEntry->ospfIfType) {
	fmt_enum(s, 16, ospf_mib_enums_ospfIfType,
		 ospfIfEntry->ospfIfType);
    } else {
	g_string_append(s, "?");
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Area: ");
    if (ospfIfEntry->ospfIfAreaId) {
	g_string_sprintfa(s,"%s", 
			  fmt_ipv4_address(ospfIfEntry->ospfIfAreaId,
					   SCLI_FMT_NAME_OR_ADDR));
    } else {
	g_string_append(s, "?");
    }
    g_string_append(s, "\n");
}



static int
cmd_ospf_interfaces(scli_interp_t *interp, int argc, char **argv)
{
   ospf_mib_ospfIfEntry_t **ospfIfTable = NULL;
   ifEntry_t **ifTable = NULL;
   ifXEntry_t **ifXTable = NULL;
   ipAddrEntry_t **ipAddrTable = NULL;
   int i;

   g_return_val_if_fail(interp, SCLI_ERROR);

   if (ospf_mib_get_ospfIfTable(interp->peer, &ospfIfTable)) {
       return SCLI_ERROR;
   }

   (void) if_mib_get_ifTable(interp->peer, &ifTable);
   (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
   (void) ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable);

   if (ospfIfTable) {
       for (i = 0; ospfIfTable[i]; i++) {
	   if (i) {
	       g_string_append(interp->result, "\n");
	   }
	   show_ospf_interfaces(interp->result, ospfIfTable[i],
				ifTable, ifXTable, ipAddrTable);
       }
   }

   if (ifXTable) if_mib_free_ifXTable(ifXTable);
   if (ifTable) if_mib_free_ifTable(ifTable);
   if (ipAddrTable) ip_mib_free_ipAddrTable(ipAddrTable);

   return SCLI_OK;
}



void
scli_init_ospf_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
        { "show ip ospf area", 
	  SCLI_CMD_FLAG_NEED_PEER,
	  "show OSPF areas",
	   cmd_ospf_area },
	{ "show ip ospf info", 
	  SCLI_CMD_FLAG_NEED_PEER,
	  "general OSPF information",
	   cmd_ospf_info },
	{ "show ip ospf interface", 
	  SCLI_CMD_FLAG_NEED_PEER,
	  "show OSPF interfaces",
	   cmd_ospf_interfaces },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t ospf_mode = {
	"ospf",
	"scli mode to display and configure OSPF parameters",
	cmds
    };
    
    scli_register_mode(interp, &ospf_mode);
}
