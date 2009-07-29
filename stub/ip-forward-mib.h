/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli \
 *     --scli-exclude='ipForwardEntry' IP-FORWARD-MIB
 *
 * Derived from IP-FORWARD-MIB:
 *   The MIB module for the management of CIDR multipath IP
 *   Routes.
 *   
 *   Copyright (C) The Internet Society (2006).  This version
 *   of this MIB module is a part of RFC 4292; see the RFC
 *   itself for full legal notices.
 *
 * Revision 2006-02-01 00:00:
 *   IPv4/v6 version-independent revision.  Minimal changes
 *   were made to the original RFC 2096 MIB to allow easy
 *   upgrade of existing IPv4 implementations to the
 *   version-independent MIB.  These changes include:
 *   
 *   Adding inetCidrRouteDiscards as a replacement for the
 *   deprecated ipRoutingDiscards and ipv6DiscardedRoutes
 *   objects.
 *   
 *   Adding a new conformance statement to support the
 *   implementation of the IP Forwarding MIB in a
 *   read-only mode.
 *   
 *   
 *   
 *   
 *   The inetCidrRouteTable replaces the IPv4-specific
 *   ipCidrRouteTable, its related objects, and related
 *   conformance statements.
 *   
 *   Published as RFC 4292.
 *
 * Revision 1996-09-19 00:00:
 *   Revised to support CIDR routes.
 *   Published as RFC 2096.
 *
 * Revision 1992-07-02 21:56:
 *   Initial version, published as RFC 1354.
 *
 * $Id$
 */

#ifndef _IP_FORWARD_MIB_H_
#define _IP_FORWARD_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define IP_FORWARD_MIB_IPCIDRROUTETYPE_OTHER  1
#define IP_FORWARD_MIB_IPCIDRROUTETYPE_REJECT 2
#define IP_FORWARD_MIB_IPCIDRROUTETYPE_LOCAL  3
#define IP_FORWARD_MIB_IPCIDRROUTETYPE_REMOTE 4

extern GNetSnmpEnum const ip_forward_mib_enums_ipCidrRouteType[];

#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_OTHER      1
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_LOCAL      2
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_NETMGMT    3
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_ICMP       4
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_EGP        5
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_GGP        6
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_HELLO      7
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_RIP        8
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_ISIS       9
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_ESIS       10
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_CISCOIGRP  11
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_BBNSPFIGP  12
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_OSPF       13
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_BGP        14
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_IDPR       15
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO_CISCOEIGRP 16

extern GNetSnmpEnum const ip_forward_mib_enums_ipCidrRouteProto[];

#define IP_FORWARD_MIB_INETCIDRROUTETYPE_OTHER     1
#define IP_FORWARD_MIB_INETCIDRROUTETYPE_REJECT    2
#define IP_FORWARD_MIB_INETCIDRROUTETYPE_LOCAL     3
#define IP_FORWARD_MIB_INETCIDRROUTETYPE_REMOTE    4
#define IP_FORWARD_MIB_INETCIDRROUTETYPE_BLACKHOLE 5

extern GNetSnmpEnum const ip_forward_mib_enums_inetCidrRouteType[];


/*
 * C type definitions for IP-FORWARD-MIB::ipForward.
 */

#define IP_FORWARD_MIB_IPFORWARDNUMBER       (1 << 0) 
#define IP_FORWARD_MIB_IPCIDRROUTENUMBER     (1 << 1) 
#define IP_FORWARD_MIB_INETCIDRROUTENUMBER   (1 << 2) 
#define IP_FORWARD_MIB_INETCIDRROUTEDISCARDS (1 << 3) 

typedef struct {
    guint32  *ipForwardNumber;           /* ro SNMPv2-SMI::Gauge32 */
    guint32  *ipCidrRouteNumber;         /* ro SNMPv2-SMI::Gauge32 */
    guint32  *inetCidrRouteNumber;       /* ro SNMPv2-SMI::Gauge32 */
    guint32  *inetCidrRouteDiscards;     /* ro SNMPv2-SMI::Counter32 */
} ip_forward_mib_ipForward_t;

extern ip_forward_mib_ipForward_t *
ip_forward_mib_new_ipForward(void);

extern void
ip_forward_mib_get_ipForward(GNetSnmp *s, ip_forward_mib_ipForward_t **ipForward, gint64 mask, GError **error);

extern void
ip_forward_mib_free_ipForward(ip_forward_mib_ipForward_t *ipForward);

/*
 * C type definitions for IP-FORWARD-MIB::ipCidrRouteEntry.
 */

#define IP_FORWARD_MIB_IPCIDRROUTEDEST      (1 << 0) 
#define IP_FORWARD_MIB_IPCIDRROUTEMASK      (1 << 1) 
#define IP_FORWARD_MIB_IPCIDRROUTETOS       (1 << 2) 
#define IP_FORWARD_MIB_IPCIDRROUTENEXTHOP   (1 << 3) 
#define IP_FORWARD_MIB_IPCIDRROUTEIFINDEX   (1 << 4) 
#define IP_FORWARD_MIB_IPCIDRROUTETYPE      (1 << 5) 
#define IP_FORWARD_MIB_IPCIDRROUTEPROTO     (1 << 6) 
#define IP_FORWARD_MIB_IPCIDRROUTEAGE       (1 << 7) 
#define IP_FORWARD_MIB_IPCIDRROUTEINFO      (1 << 8) 
#define IP_FORWARD_MIB_IPCIDRROUTENEXTHOPAS (1 << 9) 
#define IP_FORWARD_MIB_IPCIDRROUTEMETRIC1   (1 << 10) 
#define IP_FORWARD_MIB_IPCIDRROUTEMETRIC2   (1 << 11) 
#define IP_FORWARD_MIB_IPCIDRROUTEMETRIC3   (1 << 12) 
#define IP_FORWARD_MIB_IPCIDRROUTEMETRIC4   (1 << 13) 
#define IP_FORWARD_MIB_IPCIDRROUTEMETRIC5   (1 << 14) 
#define IP_FORWARD_MIB_IPCIDRROUTESTATUS    (1 << 15) 

typedef struct {
    guchar   ipCidrRouteDest[4];       /* ro SNMPv2-SMI::IpAddress */
#define IP_FORWARD_MIB_IPCIDRROUTEDESTLENGTH 4
    guchar   ipCidrRouteMask[4];       /* ro SNMPv2-SMI::IpAddress */
#define IP_FORWARD_MIB_IPCIDRROUTEMASKLENGTH 4
    gint32   ipCidrRouteTos;            /* ro */
    guchar   ipCidrRouteNextHop[4];    /* ro SNMPv2-SMI::IpAddress */
#define IP_FORWARD_MIB_IPCIDRROUTENEXTHOPLENGTH 4
    gint32   *ipCidrRouteIfIndex;       /* rw Integer32 */
    gint32   *ipCidrRouteType;          /* rw */
    gint32   *ipCidrRouteProto;         /* ro */
    gint32   *ipCidrRouteAge;           /* ro Integer32 */
    guint32  *ipCidrRouteInfo;          /* rw ObjectIdentifier */
#define IP_FORWARD_MIB_IPCIDRROUTEINFOMINLENGTH 0
#define IP_FORWARD_MIB_IPCIDRROUTEINFOMAXLENGTH 128
    guint16  _ipCidrRouteInfoLength;
    gint32   *ipCidrRouteNextHopAS;     /* rw Integer32 */
    gint32   *ipCidrRouteMetric1;       /* rw Integer32 */
    gint32   *ipCidrRouteMetric2;       /* rw Integer32 */
    gint32   *ipCidrRouteMetric3;       /* rw Integer32 */
    gint32   *ipCidrRouteMetric4;       /* rw Integer32 */
    gint32   *ipCidrRouteMetric5;       /* rw Integer32 */
    gint32   *ipCidrRouteStatus;        /* rw SNMPv2-TC::RowStatus */
} ip_forward_mib_ipCidrRouteEntry_t;

extern void
ip_forward_mib_get_ipCidrRouteTable(GNetSnmp *s, ip_forward_mib_ipCidrRouteEntry_t ***ipCidrRouteEntry, gint64 mask, GError **error);

extern void
ip_forward_mib_free_ipCidrRouteTable(ip_forward_mib_ipCidrRouteEntry_t **ipCidrRouteEntry);

extern ip_forward_mib_ipCidrRouteEntry_t *
ip_forward_mib_new_ipCidrRouteEntry(void);

extern void
ip_forward_mib_get_ipCidrRouteEntry(GNetSnmp *s, ip_forward_mib_ipCidrRouteEntry_t **ipCidrRouteEntry, guchar *ipCidrRouteDest, guchar *ipCidrRouteMask, gint32 ipCidrRouteTos, guchar *ipCidrRouteNextHop, gint64 mask, GError **error);

extern void
ip_forward_mib_set_ipCidrRouteEntry(GNetSnmp *s, ip_forward_mib_ipCidrRouteEntry_t *ipCidrRouteEntry, gint64 mask, GError **error);

extern void
ip_forward_mib_free_ipCidrRouteEntry(ip_forward_mib_ipCidrRouteEntry_t *ipCidrRouteEntry);

/*
 * C type definitions for IP-FORWARD-MIB::inetCidrRouteEntry.
 */

#define IP_FORWARD_MIB_INETCIDRROUTEIFINDEX   (1 << 0) 
#define IP_FORWARD_MIB_INETCIDRROUTETYPE      (1 << 1) 
#define IP_FORWARD_MIB_INETCIDRROUTEPROTO     (1 << 2) 
#define IP_FORWARD_MIB_INETCIDRROUTEAGE       (1 << 3) 
#define IP_FORWARD_MIB_INETCIDRROUTENEXTHOPAS (1 << 4) 
#define IP_FORWARD_MIB_INETCIDRROUTEMETRIC1   (1 << 5) 
#define IP_FORWARD_MIB_INETCIDRROUTEMETRIC2   (1 << 6) 
#define IP_FORWARD_MIB_INETCIDRROUTEMETRIC3   (1 << 7) 
#define IP_FORWARD_MIB_INETCIDRROUTEMETRIC4   (1 << 8) 
#define IP_FORWARD_MIB_INETCIDRROUTEMETRIC5   (1 << 9) 
#define IP_FORWARD_MIB_INETCIDRROUTESTATUS    (1 << 10) 

typedef struct {
    gint32   inetCidrRouteDestType;       /* na INET-ADDRESS-MIB::InetAddressType */
    guchar   inetCidrRouteDest[117];       /* na INET-ADDRESS-MIB::InetAddress */
#define IP_FORWARD_MIB_INETCIDRROUTEDESTMINLENGTH 0
#define IP_FORWARD_MIB_INETCIDRROUTEDESTMAXLENGTH 117
    guint16  _inetCidrRouteDestLength;
    guint32  inetCidrRoutePfxLen;         /* na INET-ADDRESS-MIB::InetAddressPrefixLength */
    guint32  inetCidrRoutePolicy[117];     /* na ObjectIdentifier */
#define IP_FORWARD_MIB_INETCIDRROUTEPOLICYMINLENGTH 0
#define IP_FORWARD_MIB_INETCIDRROUTEPOLICYMAXLENGTH 117
    guint16  _inetCidrRoutePolicyLength;
    gint32   inetCidrRouteNextHopType;    /* na INET-ADDRESS-MIB::InetAddressType */
    guchar   inetCidrRouteNextHop[117];    /* na INET-ADDRESS-MIB::InetAddress */
#define IP_FORWARD_MIB_INETCIDRROUTENEXTHOPMINLENGTH 0
#define IP_FORWARD_MIB_INETCIDRROUTENEXTHOPMAXLENGTH 117
    guint16  _inetCidrRouteNextHopLength;
    gint32   *inetCidrRouteIfIndex;       /* rw IF-MIB::InterfaceIndexOrZero */
    gint32   *inetCidrRouteType;          /* rw */
    gint32   *inetCidrRouteProto;         /* ro IANA-RTPROTO-MIB::IANAipRouteProtocol */
    guint32  *inetCidrRouteAge;           /* ro SNMPv2-SMI::Gauge32 */
    guint32  *inetCidrRouteNextHopAS;     /* rw INET-ADDRESS-MIB::InetAutonomousSystemNumber */
    gint32   *inetCidrRouteMetric1;       /* rw Integer32 */
    gint32   *inetCidrRouteMetric2;       /* rw Integer32 */
    gint32   *inetCidrRouteMetric3;       /* rw Integer32 */
    gint32   *inetCidrRouteMetric4;       /* rw Integer32 */
    gint32   *inetCidrRouteMetric5;       /* rw Integer32 */
    gint32   *inetCidrRouteStatus;        /* rw SNMPv2-TC::RowStatus */
} ip_forward_mib_inetCidrRouteEntry_t;

extern void
ip_forward_mib_get_inetCidrRouteTable(GNetSnmp *s, ip_forward_mib_inetCidrRouteEntry_t ***inetCidrRouteEntry, gint64 mask, GError **error);

extern void
ip_forward_mib_free_inetCidrRouteTable(ip_forward_mib_inetCidrRouteEntry_t **inetCidrRouteEntry);

extern ip_forward_mib_inetCidrRouteEntry_t *
ip_forward_mib_new_inetCidrRouteEntry(void);

extern void
ip_forward_mib_get_inetCidrRouteEntry(GNetSnmp *s, ip_forward_mib_inetCidrRouteEntry_t **inetCidrRouteEntry, gint32 inetCidrRouteDestType, guchar *inetCidrRouteDest, guint16 _inetCidrRouteDestLength, guint32 inetCidrRoutePfxLen, guint32 *inetCidrRoutePolicy, guint16 _inetCidrRoutePolicyLength, gint32 inetCidrRouteNextHopType, guchar *inetCidrRouteNextHop, guint16 _inetCidrRouteNextHopLength, gint64 mask, GError **error);

extern void
ip_forward_mib_set_inetCidrRouteEntry(GNetSnmp *s, ip_forward_mib_inetCidrRouteEntry_t *inetCidrRouteEntry, gint64 mask, GError **error);

extern void
ip_forward_mib_free_inetCidrRouteEntry(ip_forward_mib_inetCidrRouteEntry_t *inetCidrRouteEntry);


G_END_DECLS

#endif /* _IP_FORWARD_MIB_H_ */
