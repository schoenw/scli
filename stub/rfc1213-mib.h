/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from RFC1213-MIB:
 *
 * $Id$
 */

#ifndef _RFC1213_MIB_H_
#define _RFC1213_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define RFC1213_MIB_IPROUTETYPE_OTHER	1
#define RFC1213_MIB_IPROUTETYPE_INVALID	2
#define RFC1213_MIB_IPROUTETYPE_DIRECT	3
#define RFC1213_MIB_IPROUTETYPE_INDIRECT	4

extern GSnmpEnum const rfc1213_mib_enums_ipRouteType[];

#define RFC1213_MIB_IPROUTEPROTO_OTHER	1
#define RFC1213_MIB_IPROUTEPROTO_LOCAL	2
#define RFC1213_MIB_IPROUTEPROTO_NETMGMT	3
#define RFC1213_MIB_IPROUTEPROTO_ICMP	4
#define RFC1213_MIB_IPROUTEPROTO_EGP	5
#define RFC1213_MIB_IPROUTEPROTO_GGP	6
#define RFC1213_MIB_IPROUTEPROTO_HELLO	7
#define RFC1213_MIB_IPROUTEPROTO_RIP	8
#define RFC1213_MIB_IPROUTEPROTO_IS_IS	9
#define RFC1213_MIB_IPROUTEPROTO_ES_IS	10
#define RFC1213_MIB_IPROUTEPROTO_CISCOIGRP	11
#define RFC1213_MIB_IPROUTEPROTO_BBNSPFIGP	12
#define RFC1213_MIB_IPROUTEPROTO_OSPF	13
#define RFC1213_MIB_IPROUTEPROTO_BGP	14

extern GSnmpEnum const rfc1213_mib_enums_ipRouteProto[];


/*
 * C type definitions for RFC1213-MIB::ipRouteEntry.
 */

#define RFC1213_MIB_IPROUTEDEST	0x1 
#define RFC1213_MIB_IPROUTEIFINDEX	0x2 
#define RFC1213_MIB_IPROUTEMETRIC1	0x4 
#define RFC1213_MIB_IPROUTEMETRIC2	0x8 
#define RFC1213_MIB_IPROUTEMETRIC3	0x10 
#define RFC1213_MIB_IPROUTEMETRIC4	0x20 
#define RFC1213_MIB_IPROUTENEXTHOP	0x40 
#define RFC1213_MIB_IPROUTETYPE	0x80 
#define RFC1213_MIB_IPROUTEPROTO	0x100 
#define RFC1213_MIB_IPROUTEAGE	0x200 
#define RFC1213_MIB_IPROUTEMASK	0x400 
#define RFC1213_MIB_IPROUTEMETRIC5	0x800 
#define RFC1213_MIB_IPROUTEINFO	0x1000 

typedef struct {
    guchar   ipRouteDest[4];
    gint32   *ipRouteIfIndex;
    gint32   *ipRouteMetric1;
    gint32   *ipRouteMetric2;
    gint32   *ipRouteMetric3;
    gint32   *ipRouteMetric4;
    guchar   *ipRouteNextHop;
    gint32   *ipRouteType;
    gint32   *ipRouteProto;
    gint32   *ipRouteAge;
    guchar   *ipRouteMask;
    gint32   *ipRouteMetric5;
    guint32  *ipRouteInfo;
    gsize    _ipRouteInfoLength;
} rfc1213_mib_ipRouteEntry_t;

extern void
rfc1213_mib_get_ipRouteTable(GSnmpSession *s, rfc1213_mib_ipRouteEntry_t ***ipRouteEntry, gint mask);

extern void
rfc1213_mib_free_ipRouteTable(rfc1213_mib_ipRouteEntry_t **ipRouteEntry);

extern rfc1213_mib_ipRouteEntry_t *
rfc1213_mib_new_ipRouteEntry(void);

extern void
rfc1213_mib_get_ipRouteEntry(GSnmpSession *s, rfc1213_mib_ipRouteEntry_t **ipRouteEntry, guchar *ipRouteDest, gint mask);

extern void
rfc1213_mib_set_ipRouteEntry(GSnmpSession *s, rfc1213_mib_ipRouteEntry_t *ipRouteEntry, gint mask);

extern void
rfc1213_mib_free_ipRouteEntry(rfc1213_mib_ipRouteEntry_t *ipRouteEntry);


#endif /* _RFC1213_MIB_H_ */
