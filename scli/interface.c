/* 
 * interface.c -- scli interface mode implementation
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

#include "snmpv2-mib.h"
#include "if-mib.h"
#include "ip-mib.h"

#include <regex.h>



static void
fmt_ifStatus(GString *s, gint32 *admin, gint32 *oper,
	     gint32 *conn, gint32 *prom)
{
    static stls_enum_t const admin_states[] = {
	{ IF_MIB_IFADMINSTATUS_UP,	"U" },
	{ IF_MIB_IFADMINSTATUS_DOWN,	"D" },
	{ IF_MIB_IFADMINSTATUS_TESTING,	"T" },
	{ 0, NULL }
    };

    static stls_enum_t const oper_states[] = {
	{ IF_MIB_IFOPERSTATUS_UP,		"U" },
	{ IF_MIB_IFOPERSTATUS_DOWN,		"D" },
	{ IF_MIB_IFOPERSTATUS_TESTING,		"T" },
	{ IF_MIB_IFOPERSTATUS_UNKNOWN,		"?" },
	{ IF_MIB_IFOPERSTATUS_DORMANT,		"O" },
	{ IF_MIB_IFOPERSTATUS_NOTPRESENT,	"N" },
	{ IF_MIB_IFOPERSTATUS_LOWERLAYERDOWN,	"L" },
	{ 0, NULL }
    };

    static stls_enum_t const conn_states[] = {
	{ IF_MIB_IFCONNECTORPRESENT_TRUE,	"C" },
	{ IF_MIB_IFCONNECTORPRESENT_FALSE,	"N" },
	{ 0, NULL }
    };

    static stls_enum_t const prom_states[] = {
	{ IF_MIB_IFPROMISCUOUSMODE_TRUE,	"P" },
	{ IF_MIB_IFPROMISCUOUSMODE_FALSE,	"N" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, admin_states, admin);
    fmt_enum(s, 1, oper_states, oper);
    fmt_enum(s, 1, conn_states, conn);
    fmt_enum(s, 1, prom_states, prom);
}



static int
match_interface(regex_t *regex_iface,
		if_mib_ifEntry_t *ifEntry, if_mib_ifXEntry_t *ifXEntry)
{
#if 0
    long l;
    char *end;
#endif
    int status;
    
    if (! regex_iface) {
	return 1;
    }

#if 0
    l = strtol(iface, &end, 0);
    if (end != iface) {
	return (ifEntry->ifIndex == l);
    }
#endif

    if (ifXEntry && ifXEntry->ifName) {
	char *string = g_malloc0(ifXEntry->_ifNameLength + 1);
	memcpy(string, ifXEntry->ifName, ifXEntry->_ifNameLength);
	status = regexec(regex_iface, string, (size_t) 0, NULL, 0);
	g_free(string);
	if (status == 0) {
	    return 1;
	}
    }

    /*
     * Does it really make sense to filter on the description?
     * If yes, then it should be obvious (which implies another
     * option).
     */

    if (ifEntry->ifDescr) {
	char *string = g_malloc0(ifEntry->_ifDescrLength + 1);
	memcpy(string, ifEntry->ifDescr, ifEntry->_ifDescrLength);
	status = regexec(regex_iface, string, (size_t) 0, NULL, 0);
	g_free(string);
	if (status == 0) {
	    return 1;
	}
    }

    return 0;
}
    


static void
show_if_details(GString *s,
		if_mib_ifEntry_t *ifEntry,
		if_mib_ifXEntry_t *ifXEntry,
		snmpv2_mib_system_t *system,
		ip_mib_ipAddrEntry_t **ipAddrTable)
{
    int j;
    char *name;
    int const width = 20;

    g_string_sprintfa(s, "Interface:   %-*d", width,
		      ifEntry->ifIndex);
    if (ifXEntry && ifXEntry->ifName) {
	g_string_sprintfa(s, " Name:    %.*s\n",
			  (int) ifXEntry->_ifNameLength,
			  ifXEntry->ifName);
    } else {
	g_string_append(s, " Name:\n");
    }
	
    g_string_append(s, "OperStatus:  ");
    fmt_enum(s, width, if_mib_enums_ifOperStatus, ifEntry->ifOperStatus);
    if (ifEntry->ifPhysAddress && ifEntry->_ifPhysAddressLength) {
	g_string_append(s, " Address: ");
	for (j = 0; j < ifEntry->_ifPhysAddressLength; j++) {
	    g_string_sprintfa(s, "%s%02X", (j == 0) ? "" : ":",
			      ifEntry->ifPhysAddress[j]);
	}
	/* See RFC 2665 section 3.2.6. why the test below is so ugly... */
	if (ifEntry->ifType && ifEntry->_ifPhysAddressLength == 6
	    && (*ifEntry->ifType == IF_MIB_IFTYPE_ETHERNETCSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_ISO88023CSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_STARLAN
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHER
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHERFX
		|| *ifEntry->ifType == IF_MIB_IFTYPE_GIGABITETHERNET)) {
	    name = fmt_ether_address(ifEntry->ifPhysAddress, SCLI_FMT_NAME);
	    if (name) {
		g_string_sprintfa(s, " (%s)", name);
	    }
	}
	g_string_append(s, "\n");
    } else {
	g_string_append(s, " Address:\n");
    }
    
    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, width, if_mib_enums_ifAdminStatus, ifEntry->ifAdminStatus);
    g_string_append(s, " Type:    ");
    fmt_enum(s, width, if_mib_enums_ifType, ifEntry->ifType);
    g_string_append(s, "\n");
    
    g_string_append(s, "Traps:       ");
    fmt_enum(s, width, if_mib_enums_ifLinkUpDownTrapEnable,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifLinkUpDownTrapEnable : NULL);
    if (ifEntry->ifMtu) {
	g_string_sprintfa(s, " MTU:     %d byte\n", *(ifEntry->ifMtu));
    } else {
	g_string_append(s, " MTU:\n");
    }
    
    g_string_append(s, "Connector:   ");
    fmt_enum(s, width, if_mib_enums_ifConnectorPresent,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifConnectorPresent : NULL);
    if (ifEntry->ifSpeed) {
	if (*(ifEntry->ifSpeed) == 0xffffffff
	    && ifXEntry && ifXEntry->ifHighSpeed) {
	    g_string_sprintfa(s, " Speed:   %s bps\n",
			      fmt_gtp(*(ifXEntry->ifHighSpeed)));
	} else {
	    g_string_sprintfa(s, " Speed:   %s bps\n",
			      fmt_kmg(*(ifEntry->ifSpeed)));
	}
    } else {
	g_string_append(s, " Speed:\n");
    }
    
    g_string_append(s, "Promiscuous: ");
    fmt_enum(s, width, if_mib_enums_ifPromiscuousMode,
	     (ifXEntry && ifXEntry) ? ifXEntry->ifPromiscuousMode : NULL);
    if (ifEntry->ifLastChange && system && system->sysUpTime) {
	guint32 dsecs = *(system->sysUpTime) - *(ifEntry->ifLastChange);
	g_string_sprintfa(s, " Change:  %s\n",
			  stls_fmt_timeticks(dsecs));
    } else {
	g_string_append(s, " Change:\n");
    }

    if (ipAddrTable) {
	for (j = 0; ipAddrTable[j]; j++) {
	    if (ipAddrTable[j]->ipAdEntIfIndex
		&& (ifEntry->ifIndex == *(ipAddrTable[j]->ipAdEntIfIndex))) {
		if (ipAddrTable[j]->ipAdEntAddr
		    && ipAddrTable[j]->ipAdEntNetMask) {
		    g_string_sprintfa(s, "IP Address:  %-*s", width,
		      fmt_ipv4_address(ipAddrTable[j]->ipAdEntAddr,
				       SCLI_FMT_ADDR));
		    g_string_sprintfa(s, " Prefix:  %s\n",
		      fmt_ipv4_mask(ipAddrTable[j]->ipAdEntNetMask));
		}
	    }
	}
    }
    
    if (ifEntry->ifDescr && ifEntry->_ifDescrLength) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) ifEntry->_ifDescrLength,
			  ifEntry->ifDescr);
    }
    
    if (ifXEntry && ifXEntry
	&& ifXEntry->ifAlias && ifXEntry->_ifAliasLength) {
	g_string_sprintfa(s, "Alias:       %.*s\n",
			  (int) ifXEntry->_ifAliasLength,
			  ifXEntry->ifAlias);
    }
}



static int
cmd_if_details(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    snmpv2_mib_system_t *system = NULL;
    ip_mib_ipAddrEntry_t **ipAddrTable = NULL;
    regex_t _regex_iface, *regex_iface = NULL;
    int i, c;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_ERROR;	/* xxx report error */
	}
    }

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    (void) snmpv2_mib_get_system(interp->peer, &system);
    (void) ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable);

    if (ifTable) {
	for (i = 0, c = 0; ifTable[i]; i++) {
	    if (match_interface(regex_iface, ifTable[i],
				ifXTable ? ifXTable[i] : NULL)) {
		if (c) {
		    g_string_append(interp->result, "\n");
		}
		show_if_details(interp->result, ifTable[i],
				ifXTable ? ifXTable[i] : NULL,
				system, ipAddrTable);
		c++;
	    }
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (system) snmpv2_mib_free_system(system);
    if (ipAddrTable) ip_mib_free_ipAddrTable(ipAddrTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



static void
show_if_info(GString *s,
	     if_mib_ifEntry_t *ifEntry,
	     if_mib_ifXEntry_t *ifXEntry,
	     int type_width, int name_width)
{
    g_string_sprintfa(s, "%6u     ", ifEntry->ifIndex);

    fmt_ifStatus(s,
		 ifEntry->ifAdminStatus, ifEntry->ifOperStatus,
		 ifXEntry ? ifXEntry->ifConnectorPresent : NULL,
		 ifXEntry ? ifXEntry->ifPromiscuousMode : NULL);

    if (ifEntry->ifMtu) {
	g_string_sprintfa(s, " %5d", *(ifEntry->ifMtu));
    } else {
	g_string_sprintfa(s, "      ");
    }

    g_string_append(s, " ");
    fmt_enum(s, type_width, if_mib_enums_ifType, ifEntry->ifType);
    g_string_append(s, " ");

    if (ifEntry->ifSpeed) {
	if (*(ifEntry->ifSpeed) == 0xffffffff
	    && ifXEntry && ifXEntry->ifHighSpeed) {
	    g_string_sprintfa(s, "  %4s ",
			      fmt_gtp(*(ifXEntry->ifHighSpeed)));
	} else {
	    g_string_sprintfa(s, "  %4s ",
			      fmt_kmg(*(ifEntry->ifSpeed)));
	}
    } else {
	g_string_append(s, "       ");
    }

    if (ifXEntry && ifXEntry->ifName) {
	g_string_sprintfa(s, "%-*.*s ", name_width,
			  (int) ifXEntry->_ifNameLength,
			  ifXEntry->ifName);
    } else {
	g_string_sprintfa(s, "%*s ", name_width, "");
    }

    if (ifEntry->ifDescr) {
	g_string_sprintfa(s, "%.*s",
			  (int) ifEntry->_ifDescrLength,
			  ifEntry->ifDescr);
    }

    g_string_append(s, "\n");
}



static int
cmd_if_info(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int name_width = 6;
    int type_width = 6;
    regex_t _regex_iface, *regex_iface = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_ERROR;	/* xxx report error */
	}
    }

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    if (ifTable) {
	for (i = 0; ifTable[i]; i++) {
	    if (ifXTable && ifXTable[i]) {
		if (ifXTable[i]->_ifNameLength > name_width) {
		    name_width = ifXTable[i]->_ifNameLength;
		}
	    }
	    if (ifTable[i]->ifType) {
		char const *label;
		label = stls_enum_get_label(if_mib_enums_ifType,
					*ifTable[i]->ifType);
		if (label && strlen(label) > type_width) {
		    type_width = strlen(label);
		}
	    }
	}
	g_string_sprintfa(interp->header,
		  "INTERFACE STATUS  MTU %-*s  SPEED %-*s DESCRIPTION",
			  type_width, "TYPE",
			  name_width, "NAME");
	for (i = 0; ifTable[i]; i++) {
	    if (match_interface(regex_iface, ifTable[i],
				ifXTable ? ifXTable[i] : NULL)) {
		show_if_info(interp->result, ifTable[i],
			     ifXTable ? ifXTable[i] : NULL,
			     type_width, name_width);
	    }
	}
    }

    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}



static void
show_if_stack(GString *s, if_mib_ifStackEntry_t *ifStackEntry)
{
    /*
     *      ,-- if2 
     * if1 -+-- if3
     *      `-- if4
     *
     * if5 -,
     * if6 -+-- if8
     * if7 -'
     */

    g_string_sprintfa(s, "%8d %8d\n",
		      ifStackEntry->ifStackHigherLayer,
		      ifStackEntry->ifStackLowerLayer);
}



static int
cmd_if_stack(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifStackEntry_t **ifStackTable = NULL;
    int i;

    if (if_mib_get_ifStackTable(interp->peer, &ifStackTable)) {
	return SCLI_ERROR;
    }
    
    if (ifStackTable) {
	g_string_sprintfa(interp->header, "  HIGHER    LOWER");
	for (i = 0; ifStackTable[i]; i++) {
	    show_if_stack(interp->result, ifStackTable[i]);
	}
    }

    if (ifStackTable) if_mib_free_ifStackTable(ifStackTable);
    
    return SCLI_OK;
}



typedef struct {
    guint32 inOctets;
    guint32 outOctets;
    guint32 inPkts;
    guint32 outPkts;
    guint32 inErrors;
    guint32 outErrors;
} if_stats_t;



static int
cmd_if_stats(scli_interp_t *interp, int argc, char **argv)
{
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    static struct timeval last, now;
    double delta;
    static if_stats_t *stats = NULL;
    static time_t epoch = 0;
    regex_t _regex_iface, *regex_iface = NULL;
    int i;

    if (argc > 1) {
	regex_iface = &_regex_iface;
	if (regcomp(regex_iface, argv[1], REG_EXTENDED|REG_NOSUB) != 0) {
	    return SCLI_ERROR;	/* xxx report error */
	}
    }

    if (if_mib_get_ifTable(interp->peer, &ifTable)) {
	if (regex_iface) regfree(regex_iface);
	return SCLI_ERROR;
    }
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);

    if (epoch < interp->epoch) {
	if (stats) g_free(stats);
	stats = NULL;
	last.tv_sec = last.tv_usec = 0;
    }

    if (! stats && ifTable) {
	for (i = 0; ifTable[i]; i++) ;
	stats = (if_stats_t *) g_malloc0(i * sizeof(if_stats_t));
    }

    epoch = time(NULL);
    gettimeofday(&now, NULL);
    delta = TV_DIFF(last, now);

    if (ifTable) {
	g_string_append(interp->header, "INDEX STAT SPEED "
			"I-BPS O-BPS I-PPS O-PPS I-ERR O-ERR  DESCRIPTION");
	for (i = 0; ifTable[i]; i++) {
	    GString *s;
	    if (! match_interface(regex_iface, ifTable[i],
				  ifXTable ? ifXTable[i] : NULL)) {
		continue;
	    }
	    s = interp->result;
	    g_string_sprintfa(s, "%5u ", ifTable[i]->ifIndex);
	    fmt_ifStatus(s,
			 ifTable[i]->ifAdminStatus, ifTable[i]->ifOperStatus,
	 (ifXTable && ifXTable[i]) ? ifXTable[i]->ifConnectorPresent : NULL,
	 (ifXTable && ifXTable[i]) ? ifXTable[i]->ifPromiscuousMode : NULL);

	    if (ifTable[i]->ifSpeed) {
		if (*(ifTable[i]->ifSpeed) == 0xffffffff
		    && ifXTable && ifXTable[i]->ifHighSpeed) {
		    g_string_sprintfa(s, " %5s",
				      fmt_gtp(*(ifXTable[i]->ifHighSpeed)));
		} else {
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg(*(ifTable[i]->ifSpeed)));
		}
	    } else {
		g_string_sprintfa(s, "  ----");
	    }

	    fmt_counter_dt(s, ifTable[i]->ifInOctets, &(stats[i].inOctets),
			   &last, delta);

	    fmt_counter_dt(s, ifTable[i]->ifOutOctets, &(stats[i].outOctets),
			   &last, delta);
	    
	    if (ifTable[i]->ifInUcastPkts && delta > TV_DELTA) {
		guint32 pkts;
		pkts = *(ifTable[i]->ifInUcastPkts);
		if (ifXTable && ifXTable[i]->ifInMulticastPkts
		    && ifXTable[i]->ifInBroadcastPkts) {
		    pkts += *(ifXTable[i]->ifInMulticastPkts);
		    pkts += *(ifXTable[i]->ifInBroadcastPkts);
		} else if (ifTable[i]->ifInNUcastPkts) {
		    pkts += *(ifTable[i]->ifInNUcastPkts);
		} else {
		    /* might be fixed length ??? */
		}
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (pkts - stats[i].inPkts) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].inPkts = pkts;
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    if (ifTable[i]->ifOutUcastPkts && delta > TV_DELTA) {
		guint32 pkts;
		pkts = *(ifTable[i]->ifOutUcastPkts);
		if (ifXTable && ifXTable[i]->ifOutMulticastPkts
		    && ifXTable[i]->ifOutBroadcastPkts) {
		    pkts += *(ifXTable[i]->ifOutMulticastPkts);
		    pkts += *(ifXTable[i]->ifOutBroadcastPkts);
		} else if (ifTable[i]->ifOutNUcastPkts) {
		    pkts += *(ifTable[i]->ifOutNUcastPkts);
		} else {
		    /* might be fixed length ??? */
		}
		if (last.tv_sec && last.tv_usec) {
		    double f_val = (pkts - stats[i].outPkts) / delta;
		    g_string_sprintfa(s, " %5s",
				      fmt_kmg((guint32) f_val));
		} else {
		    g_string_sprintfa(s, "  ----");
		}
		stats[i].outPkts = pkts;
	    } else {
		g_string_sprintfa(s, "  ----");
	    }
	    
	    fmt_counter_dt(s, ifTable[i]->ifInErrors, &(stats[i].inErrors),
			   &last, delta);

	    fmt_counter_dt(s, ifTable[i]->ifOutErrors, &(stats[i].outErrors),
			   &last, delta);
	    
	    if (ifTable[i]->ifDescr && ifTable[i]->_ifDescrLength) {
		g_string_sprintfa(s, "  %.*s",
				  (int) ifTable[i]->_ifDescrLength,
				  ifTable[i]->ifDescr);
	    }
	    g_string_append(s, "\n");
	}
    }
    
    last = now;
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    if (regex_iface) regfree(regex_iface);

    return SCLI_OK;
}


/*
 * <man>
 *   show interface info [name]
 *   show interface details [name]
 * </man>
 */


void
scli_init_interface_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show interface info",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "network interface summary",
	  cmd_if_info },
	{ "show interface stats",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "network interface statistics",
	  cmd_if_stats },
	{ "show interface details",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "network interface details",
	  cmd_if_details },
	{ "show interface stack",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "network interface stacking",
	  cmd_if_stack },
	{ "monitor interface stats",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  "network interface statistics",
	  cmd_if_stats },
	{ NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t if_mib_mode = {
	"interface",
	"scli mode to display and configure interface parameters",
	cmds
    };

    scli_register_mode(interp, &if_mib_mode);
}
