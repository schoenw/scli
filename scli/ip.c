/* 
 * ip.c -- scli ip mode implementation
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

#include "scli.h"

#include "ip-mib.h"
#include "ip-forward-mib.h"
#include "tunnel-mib.h"
#include "if-mib.h"
#include "rfc1213-mib.h"



GSnmpEnum const forwarding[] = {
    { IP_MIB_IPFORWARDING_FORWARDING,	"enabled" },
    { IP_MIB_IPFORWARDING_NOTFORWARDING,	"disabled" },
    { 0, NULL }
};



static void
fmt_ip_forward(GString *s,
	       ip_forward_mib_ipCidrRouteEntry_t *ipCidrRouteEntry)
{
    g_string_append(s, "\n");
}



static void
fmt_ip_route(GString *s,
	     rfc1213_mib_ipRouteEntry_t *ipRouteEntry,
	     if_mib_ifXEntry_t **ifXTable,
	     if_mib_ifEntry_t **ifTable)
{
    const char *label;
    int i, pos;
    
    if (ipRouteEntry->ipRouteDest
	&& ipRouteEntry->ipRouteNextHop
	&& ipRouteEntry->ipRouteMask
	&& ipRouteEntry->ipRouteIfIndex) {
	g_string_sprintfa(s, "%s%s%n",
			  fmt_ipv4_address(ipRouteEntry->ipRouteDest,
					   SCLI_FMT_ADDR),
			  fmt_ipv4_mask(ipRouteEntry->ipRouteMask), &pos);
	g_string_sprintfa(s, "%*s", MAX(20-pos, 1), "");
	
	g_string_sprintfa(s, "%-16s",
			  fmt_ipv4_address(ipRouteEntry->ipRouteNextHop,
					   SCLI_FMT_ADDR));

	label = NULL;
	if (ipRouteEntry->ipRouteType) {
	    label = gsnmp_enum_get_label(rfc1213_mib_enums_ipRouteType,
					 *ipRouteEntry->ipRouteType);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	label = NULL;
	if (ipRouteEntry->ipRouteProto) {
	    label = gsnmp_enum_get_label(rfc1213_mib_enums_ipRouteProto,
					*ipRouteEntry->ipRouteProto);
	}
	g_string_sprintfa(s, "%-10s", label ? label : "");

	g_string_sprintfa(s, "%2d", *ipRouteEntry->ipRouteIfIndex);

	if (ifXTable) {
	    for (i = 0; ifXTable[i]; i++) {
		if(ifXTable[i]->ifIndex == *ipRouteEntry->ipRouteIfIndex) {
		    g_string_sprintfa(s, " (%.*s)",
				      (int) ifXTable[i]->_ifNameLength,
				      ifXTable[i]->ifName);
		    break;
		}
	    }
	} else if (ifTable) {
	    for (i = 0; ifTable[i]; i++) {
		if(ifTable[i]->ifIndex == *ipRouteEntry->ipRouteIfIndex) {
		    g_string_sprintfa(s, " (%.*s)",
				      (int) ifTable[i]->_ifDescrLength,
				      ifTable[i]->ifDescr);
		    break;
		}
	    }
	}
	g_string_append(s, "\n");
    }
}



static int
show_ip_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    ip_forward_mib_ipCidrRouteEntry_t **ipCidrRouteTable = NULL;
    rfc1213_mib_ipRouteEntry_t **ipRouteTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    ip_forward_mib_get_ipCidrRouteTable(interp->peer, &ipCidrRouteTable, 0);
    if (interp->peer->error_status || !ipCidrRouteTable) {
	rfc1213_mib_get_ipRouteTable(interp->peer, &ipRouteTable, 0);
	if (interp->peer->error_status) {
	    return SCLI_SNMP;
	}
    }

    if (ipCidrRouteTable || ipRouteTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, 0);
	if_mib_get_ifXTable(interp->peer, &ifXTable, 0);
	g_string_sprintfa(interp->header, "%-20s%-16s%-10s%-10s%s",
		  "DESTINATION", "NEXT HOP", "TYPE", "PROTO", "INTERFACE");
	if (ipCidrRouteTable) {
	    for (i = 0; ipCidrRouteTable[i]; i++) {
		fmt_ip_forward(interp->result, ipCidrRouteTable[i]);
	    }
	}
	if (! ipCidrRouteTable && ipRouteTable) {
	    for (i = 0; ipRouteTable[i]; i++) {
		fmt_ip_route(interp->result, ipRouteTable[i],
			     ifXTable, ifTable);
	    }
	}
    }

    if (ifTable)
	if_mib_free_ifTable(ifTable);
    if (ifXTable)
	if_mib_free_ifXTable(ifXTable);
    if (ipRouteTable)
	rfc1213_mib_free_ipRouteTable(ipRouteTable);
    if (ipCidrRouteTable)
	ip_forward_mib_free_ipCidrRouteTable(ipCidrRouteTable);

    return SCLI_OK;
}



static void
fmt_ip_address(GString *s, ip_mib_ipAddrEntry_t *ipAddrEntry)
{
    unsigned prefix = 0;
    char *name;
    int i, j;

    if (ipAddrEntry->ipAdEntNetMask) {
	for (i = 0; i < 4; i++) {
	    for (j = 0; j < 8; j++) {
		if ((1 << (7-j)) & (ipAddrEntry->ipAdEntNetMask)[i]) {
		    prefix++;
		} else {
		    i = 4;
		    break;
		}
	    }
	}
    }
	      
    if (ipAddrEntry->ipAdEntIfIndex) {
	g_string_sprintfa(s, "%6u    ", *(ipAddrEntry->ipAdEntIfIndex));
    } else {
	g_string_sprintfa(s, "%6s    ", "");
    }
    g_string_sprintfa(s, "%-16s ",
	      fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_ADDR));
    if (ipAddrEntry->ipAdEntNetMask) {
	g_string_sprintfa(s, "%-6s",
			  fmt_ipv4_mask(ipAddrEntry->ipAdEntNetMask));;
    } else {
	g_string_sprintfa(s, "%-6s", "");
    }
    name = fmt_ipv4_address(ipAddrEntry->ipAdEntAddr, SCLI_FMT_NAME);
    if (name) {
	g_string_append(s, name);
    }
    g_string_append(s, "\n");
}



static int
show_ip_addresses(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ipAddrEntry_t **ipAddrTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    ip_mib_get_ipAddrTable(interp->peer, &ipAddrTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (ipAddrTable) {
	g_string_sprintfa(interp->header,
			  "INTERFACE ADDRESS        PREFIX  NAME");
	for (i = 0; ipAddrTable[i]; i++) {
	    fmt_ip_address(interp->result, ipAddrTable[i]);
	}
    }

    if (ipAddrTable) ip_mib_free_ipAddrTable(ipAddrTable);

    return SCLI_OK;
}



static void
fmt_ip_tunnel(GString *s,
	      tunnel_mib_tunnelIfEntry_t *tunnelIfEntry,
	      if_mib_ifXEntry_t **ifXTable,
	      if_mib_ifEntry_t **ifTable)
{
    int i;
    const char *e;

    g_return_if_fail(tunnelIfEntry);

    if (tunnelIfEntry->tunnelIfLocalAddress) {
	g_string_sprintfa(s, "%-15s  ",
		  fmt_ipv4_address(tunnelIfEntry->tunnelIfLocalAddress,
				   SCLI_FMT_ADDR));
    } else {
	g_string_sprintfa(s, "%-15s  ", "-");
    }

    if (tunnelIfEntry->tunnelIfRemoteAddress) {
	g_string_sprintfa(s, "%-15s  ",
		  fmt_ipv4_address(tunnelIfEntry->tunnelIfRemoteAddress,
				   SCLI_FMT_ADDR));
    } else {
	g_string_sprintfa(s, "%-15s  ", "-");
    }

    e = fmt_enum(tunnel_mib_enums_tunnelIfEncapsMethod,
		 tunnelIfEntry->tunnelIfEncapsMethod);
    g_string_sprintfa(s, "%-8s", e ? e : "-");

    e = fmt_enum(tunnel_mib_enums_tunnelIfSecurity,
		 tunnelIfEntry->tunnelIfSecurity);
    g_string_sprintfa(s, "%-6s", e ? e : "-");

    if (tunnelIfEntry->tunnelIfHopLimit) {
	g_string_sprintfa(s, "%3d  ", *tunnelIfEntry->tunnelIfHopLimit);
    } else {
	g_string_sprintfa(s, "%3s  ", "---");
    }
    
    if (tunnelIfEntry->tunnelIfTOS) {
	switch (*tunnelIfEntry->tunnelIfTOS) {
	case -1:
	    /* A value of -1 indicates that the bits are copied from the
	     * payload's header. */
	    g_string_append(s, "CP");
	    break;
	case -2:
	    /* A value of -2 indicates that a traffic conditioner is
	     * invoked and more information may be available in a traffic
	     * conditioner MIB. */
	    g_string_append(s, "TC");
	    break;
        default:
	    g_string_sprintfa(s, "%2d", *tunnelIfEntry->tunnelIfTOS);
	    break;
	}
    } else {
	g_string_append(s, "--");
    }

    if (tunnelIfEntry->ifIndex) {
	g_string_sprintfa(s, " %2u", tunnelIfEntry->ifIndex);
        if (ifXTable) {
	    for (i = 0; ifXTable[i]; i++) {
	        if(ifXTable[i]->ifIndex == tunnelIfEntry->ifIndex) {
		   g_string_sprintfa(s, " (%.*s)",
                         (int) ifXTable[i]->_ifNameLength,
			 ifXTable[i]->ifName);
		   break;
		}
	    }
	} else if (ifTable) {
            for (i = 0; ifTable[i]; i++) {
		if(ifTable[i]->ifIndex == tunnelIfEntry->ifIndex) {
		  g_string_sprintfa(s, " (%.*s)",
	                (int) ifTable[i]->_ifDescrLength,
			ifTable[i]->ifDescr);
		  break;
		}
	    }
	}
    }
    g_string_append(s, "\n");
}



static int
show_ip_tunnel(scli_interp_t *interp, int argc, char **argv)
{
    tunnel_mib_tunnelIfEntry_t **tunnelIfTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    if_mib_ifXEntry_t **ifXTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    tunnel_mib_get_tunnelIfTable(interp->peer, &tunnelIfTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    
    if (tunnelIfTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, 0);
	if_mib_get_ifXTable(interp->peer, &ifXTable, 0);
	g_string_append(interp->header,
	"LOCAL ADDRESS    REMOTE ADDRESS   TYPE    SEC.  TTL TOS INTERFACE");
	for (i = 0; tunnelIfTable[i]; i++) {
	    fmt_ip_tunnel(interp->result, tunnelIfTable[i],
			  ifXTable, ifTable);
	}
    }

    if (ifXTable) if_mib_free_ifXTable(ifXTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (tunnelIfTable) tunnel_mib_free_tunnelIfTable(tunnelIfTable);

    return SCLI_OK;
}



static void
fmt_ip_mapping(GString *s,
	       ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry,
	       if_mib_ifEntry_t *ifEntry)
{
    char *name;
    const char *e;
    int i;

    g_string_sprintfa(s, "%6u    ",
		      ipNetToMediaEntry->ipNetToMediaIfIndex);

    e = fmt_enum(ip_mib_enums_ipNetToMediaType,
		 ipNetToMediaEntry->ipNetToMediaType);
    g_string_sprintfa(s, "%-8s", e ? e : "");
    
    g_string_sprintfa(s, " %-16s ",
	      fmt_ipv4_address(ipNetToMediaEntry->ipNetToMediaNetAddress,
			       SCLI_FMT_ADDR));

    if (ipNetToMediaEntry->ipNetToMediaPhysAddress) {
	for (i = 0;
	     i < ipNetToMediaEntry->_ipNetToMediaPhysAddressLength; i++) {
	    g_string_sprintfa(s, "%s%02x", i ? ":" : "",
			      ipNetToMediaEntry->ipNetToMediaPhysAddress[i]);
	}
	/* See RFC 2665 section 3.2.6. why the test below is so ugly... */
	if (ifEntry && ifEntry->ifType
	    && ipNetToMediaEntry->_ipNetToMediaPhysAddressLength == 6
	    && (*ifEntry->ifType == IF_MIB_IFTYPE_ETHERNETCSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_ISO88023CSMACD
		|| *ifEntry->ifType == IF_MIB_IFTYPE_STARLAN
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHER
		|| *ifEntry->ifType == IF_MIB_IFTYPE_FASTETHERFX
		|| *ifEntry->ifType == IF_MIB_IFTYPE_GIGABITETHERNET)) {
	    name = fmt_ether_address(ipNetToMediaEntry->ipNetToMediaPhysAddress, SCLI_FMT_NAME);
	    if (name) {
		g_string_sprintfa(s, " (%s)", name);
	    }
	}
    }
    
    g_string_append(s, "\n");
}



static int
show_ip_mapping(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ipNetToMediaEntry_t **ipNetToMediaTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL, *ifEntry = NULL;
    int i, j;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    ip_mib_get_ipNetToMediaTable(interp->peer, &ipNetToMediaTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (ipNetToMediaTable) {
	if_mib_get_ifTable(interp->peer, &ifTable, 0);
	g_string_append(interp->header,
		"INTERFACE STATUS   ADDRESS          LOWER LAYER ADDRESS");
	for (i = 0; ipNetToMediaTable[i]; i++) {
	    if (ifTable) {
		for (j = 0; ifTable[j]; j++) {
		    if (ipNetToMediaTable[i]->ipNetToMediaIfIndex
			== ifTable[j]->ifIndex) break;
		}
		ifEntry = ifTable[j];
	    }
	    fmt_ip_mapping(interp->result, ipNetToMediaTable[i], ifEntry);
	}
    }


    if (ipNetToMediaTable) ip_mib_free_ipNetToMediaTable(ipNetToMediaTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    
    return SCLI_OK;
}



static void
fmt_ip_info(GString *s, ip_mib_ip_t *ip)
{
    int const indent = 16;
    const char *e;

    e = fmt_enum(forwarding, ip->ipForwarding);
    if (e) {
	g_string_sprintfa(s, "%-*s%s\n", indent, "Forwarding:", e);
    }

    if (ip->ipDefaultTTL) {
	g_string_sprintfa(s, "%-*s%d hops\n", indent, "Default TTL:",
			  *ip->ipDefaultTTL);
    }

    if (ip->ipReasmTimeout) {
	g_string_sprintfa(s, "%-*s%d seconds\n", indent, "Reasm Timeout:",
			  *ip->ipReasmTimeout);
    }
}



static int
show_ip_info(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    ip_mib_get_ip(interp->peer, &ip, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (ip) {
	fmt_ip_info(interp->result, ip);
    }

    if (ip) ip_mib_free_ip(ip);

    return SCLI_OK;
}



static int
set_ip_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;
    gint32 value;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (! gsnmp_enum_get_number(forwarding, argv[1], &value)) {
	return SCLI_SYNTAX_VALUE;
    }

    ip = ip_mib_new_ip();
    ip->ipForwarding = &value;
    ip_mib_set_ip(interp->peer, ip, IP_MIB_IPFORWARDING);
    ip_mib_free_ip(ip);

    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
set_ip_ttl(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;
    gint32 value;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    value = atoi(argv[1]);
    if (value < 1 || value > 255) {
	return SCLI_SYNTAX_NUMBER;
    }

    ip = ip_mib_new_ip();
    ip->ipDefaultTTL = &value;
    ip_mib_set_ip(interp->peer, ip, IP_MIB_IPDEFAULTTTL);
    ip_mib_free_ip(ip);

    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



static int
dump_ip(scli_interp_t *interp, int argc, char **argv)
{
    ip_mib_ip_t *ip;
    const char *e;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    ip_mib_get_ip(interp->peer, &ip, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (ip) {
	e = fmt_enum(forwarding, ip->ipForwarding);
	if (e) {
	    g_string_sprintfa(interp->result,
			      "set ip forwarding \"%s\"\n", e);
	}
	if (ip->ipDefaultTTL) {
	    g_string_sprintfa(interp->result,
			      "set ip ttl \"%d\"\n",
			      *ip->ipDefaultTTL);
	}
    }

    if (ip) ip_mib_free_ip(ip);

    return SCLI_OK;
}



void
scli_init_ip_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "set ip forwarding", "<value>",
	  "The set ip forwarding command controls whether the IP protocol\n"
	  "engine forwards IP datagrams or not. The <value> parameter must\n"
	  "be one of the strings \"enabled\" or \"disabled\".",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_ip_forwarding },
	
	{ "set ip ttl", "<number>",
	  "The set ip ttl command can be used to change the default\n"
	  "time to live (TTL) value used by the IP protocol engine. The\n"
	  "<number> parameter must be a number between 1 and 255 inclusive.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  set_ip_ttl },
	
	{ "show ip info", NULL,
	  "The show ip info command displays paramters of the IP\n"
	  "protocol engine, such as the default TTL or whether the\n"
	  "node is forwarding IP packets.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_ip_info },
	
	{ "show ip forwarding", NULL,
	  "The show ip forwarding command displays the IP forwarding data\n"
	  "base. The command generates a table with the following columns:\n"
	  "\n"
	  "  DESTINATION\n"
	  "  NEXT HOP\n"
	  "  TYPE\n"
	  "  PROTO\n"
	  "  INTERFACE",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_ip_forwarding },
	
	{ "show ip addresses", NULL,
	  "The show ip addresses command displays the IP addresses assigned\n"
	  "to network interfaces. The command generates a table with the\n"
	  "following columns:\n"
	  "\n"
	  "  INTERFACE network interface number\n"
	  "  ADDRESS   IP address\n"
	  "  PREFIX    IP address prefix length\n"
	  "  NAME      name of the IP address",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_ip_addresses },
	
	{ "show ip tunnel", NULL,
	  "The show ip tunnel command displays information about existing\n"
	  "IP tunnels.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_ip_tunnel },
	
	{ "show ip mapping", NULL,
	  "The show ip mapping command displays the mapping of IP address\n"
	  "to lower layer address (e.g., IEEE 802 addresses). The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  INTERFACE network interface number\n"
	  "  STATUS    status of the mapping entry\n"
	  "  ADDRESS   IP address\n"
	  "  ADDRESS   lower layer address",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_ip_mapping },
	
	{ "dump ip", NULL,
	  "The dump ip command generates a sequence of scli commands\n"
	  "which can be used to restore the IP configuration.\n",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  dump_ip },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t ip_mode = {
	"ip",
	"The ip scli mode is based on the IP-MIB as published in\n"
	"RFC 2011, the IP-FORWARD-MIB as published in RFC 2096, the\n"
	"IP-TUNNEL-MIB as published in RFC 2667 and the RFC1213-MIB\n"
	"as published in RFC 1213. It provides commands to browse,\n"
	"monitor and configure IP protocol engines.",
	cmds
    };
    
    scli_register_mode(interp, &ip_mode);
}
