/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from IP-MIB:
 *   The MIB module for managing IP and ICMP implementations,
 *   but excluding their management of IP routes.
 *
 * Revision 1994-11-01 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 1991-03-31 00:00:
 *   The initial revision of this MIB module was part of MIB-
 *   II.
 *
 * $Id$
 */

#ifndef _IP_MIB_H_
#define _IP_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

extern stls_table_t const ip_mib_enums_ipForwarding[];
extern stls_table_t const ip_mib_enums_ipNetToMediaType[];

/*
 * C type definitions for IP-MIB::ip.
 */

typedef struct ip {
    gint32   *ipForwarding;
    gint32   *ipDefaultTTL;
    guint32  *ipInReceives;
    guint32  *ipInHdrErrors;
    guint32  *ipInAddrErrors;
    guint32  *ipForwDatagrams;
    guint32  *ipInUnknownProtos;
    guint32  *ipInDiscards;
    guint32  *ipInDelivers;
    guint32  *ipOutRequests;
    guint32  *ipOutDiscards;
    guint32  *ipOutNoRoutes;
    gint32   *ipReasmTimeout;
    guint32  *ipReasmReqds;
    guint32  *ipReasmOKs;
    guint32  *ipReasmFails;
    guint32  *ipFragOKs;
    guint32  *ipFragFails;
    guint32  *ipFragCreates;
    guint32  *ipRoutingDiscards;
} ip_t;

extern ip_t *
ip_mib_new_ip();

extern int
ip_mib_get_ip(host_snmp *s, ip_t **ip);

extern int
ip_mib_set_ip(host_snmp *s, ip_t *ip);

extern void
ip_mib_free_ip(ip_t *ip);

/*
 * C type definitions for IP-MIB::ipAddrEntry.
 */

typedef struct ipAddrEntry {
    guchar   ipAdEntAddr[4];
    gint32   *ipAdEntIfIndex;
    guchar   *ipAdEntNetMask;
    gint32   *ipAdEntBcastAddr;
    gint32   *ipAdEntReasmMaxSize;
} ipAddrEntry_t;

extern int
ip_mib_get_ipAddrTable(host_snmp *s, ipAddrEntry_t ***ipAddrEntry);

extern void
ip_mib_free_ipAddrTable(ipAddrEntry_t **ipAddrEntry);

extern ipAddrEntry_t *
ip_mib_new_ipAddrEntry();

extern int
ip_mib_get_ipAddrEntry(host_snmp *s, ipAddrEntry_t **ipAddrEntry);

extern void
ip_mib_free_ipAddrEntry(ipAddrEntry_t *ipAddrEntry);

/*
 * C type definitions for IP-MIB::ipNetToMediaEntry.
 */

typedef struct ipNetToMediaEntry {
    gint32   ipNetToMediaIfIndex;
    guchar   ipNetToMediaNetAddress[4];
    guchar   *ipNetToMediaPhysAddress;
    gsize    _ipNetToMediaPhysAddressLength;
    gint32   *ipNetToMediaType;
} ipNetToMediaEntry_t;

extern int
ip_mib_get_ipNetToMediaTable(host_snmp *s, ipNetToMediaEntry_t ***ipNetToMediaEntry);

extern void
ip_mib_free_ipNetToMediaTable(ipNetToMediaEntry_t **ipNetToMediaEntry);

extern ipNetToMediaEntry_t *
ip_mib_new_ipNetToMediaEntry();

extern int
ip_mib_get_ipNetToMediaEntry(host_snmp *s, ipNetToMediaEntry_t **ipNetToMediaEntry);

extern int
ip_mib_set_ipNetToMediaEntry(host_snmp *s, ipNetToMediaEntry_t *ipNetToMediaEntry);

extern void
ip_mib_free_ipNetToMediaEntry(ipNetToMediaEntry_t *ipNetToMediaEntry);

/*
 * C type definitions for IP-MIB::icmp.
 */

typedef struct icmp {
    guint32  *icmpInMsgs;
    guint32  *icmpInErrors;
    guint32  *icmpInDestUnreachs;
    guint32  *icmpInTimeExcds;
    guint32  *icmpInParmProbs;
    guint32  *icmpInSrcQuenchs;
    guint32  *icmpInRedirects;
    guint32  *icmpInEchos;
    guint32  *icmpInEchoReps;
    guint32  *icmpInTimestamps;
    guint32  *icmpInTimestampReps;
    guint32  *icmpInAddrMasks;
    guint32  *icmpInAddrMaskReps;
    guint32  *icmpOutMsgs;
    guint32  *icmpOutErrors;
    guint32  *icmpOutDestUnreachs;
    guint32  *icmpOutTimeExcds;
    guint32  *icmpOutParmProbs;
    guint32  *icmpOutSrcQuenchs;
    guint32  *icmpOutRedirects;
    guint32  *icmpOutEchos;
    guint32  *icmpOutEchoReps;
    guint32  *icmpOutTimestamps;
    guint32  *icmpOutTimestampReps;
    guint32  *icmpOutAddrMasks;
    guint32  *icmpOutAddrMaskReps;
} icmp_t;

extern icmp_t *
ip_mib_new_icmp();

extern int
ip_mib_get_icmp(host_snmp *s, icmp_t **icmp);

extern void
ip_mib_free_icmp(icmp_t *icmp);


#endif /* _IP_MIB_H_ */
