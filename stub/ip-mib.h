/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.0 for the scli package.
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

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define IP_MIB_IPFORWARDING_FORWARDING	1
#define IP_MIB_IPFORWARDING_NOTFORWARDING	2

extern GSnmpEnum const ip_mib_enums_ipForwarding[];

#define IP_MIB_IPNETTOMEDIATYPE_OTHER	1
#define IP_MIB_IPNETTOMEDIATYPE_INVALID	2
#define IP_MIB_IPNETTOMEDIATYPE_DYNAMIC	3
#define IP_MIB_IPNETTOMEDIATYPE_STATIC	4

extern GSnmpEnum const ip_mib_enums_ipNetToMediaType[];


/*
 * C type definitions for IP-MIB::ip.
 */

#define IP_MIB_IPFORWARDING	0x1 
#define IP_MIB_IPDEFAULTTTL	0x2 
#define IP_MIB_IPINRECEIVES	0x4 
#define IP_MIB_IPINHDRERRORS	0x8 
#define IP_MIB_IPINADDRERRORS	0x10 
#define IP_MIB_IPFORWDATAGRAMS	0x20 
#define IP_MIB_IPINUNKNOWNPROTOS	0x40 
#define IP_MIB_IPINDISCARDS	0x80 
#define IP_MIB_IPINDELIVERS	0x100 
#define IP_MIB_IPOUTREQUESTS	0x200 
#define IP_MIB_IPOUTDISCARDS	0x400 
#define IP_MIB_IPOUTNOROUTES	0x800 
#define IP_MIB_IPREASMTIMEOUT	0x1000 
#define IP_MIB_IPREASMREQDS	0x2000 
#define IP_MIB_IPREASMOKS	0x4000 
#define IP_MIB_IPREASMFAILS	0x8000 
#define IP_MIB_IPFRAGOKS	0x10000 
#define IP_MIB_IPFRAGFAILS	0x20000 
#define IP_MIB_IPFRAGCREATES	0x40000 
#define IP_MIB_IPROUTINGDISCARDS	0x80000 

typedef struct {
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
} ip_mib_ip_t;

extern ip_mib_ip_t *
ip_mib_new_ip(void);

extern void
ip_mib_get_ip(GSnmpSession *s, ip_mib_ip_t **ip, gint mask);

extern void
ip_mib_set_ip(GSnmpSession *s, ip_mib_ip_t *ip, gint mask);

extern void
ip_mib_free_ip(ip_mib_ip_t *ip);

/*
 * C type definitions for IP-MIB::ipAddrEntry.
 */

#define IP_MIB_IPADENTADDR	0x1 
#define IP_MIB_IPADENTIFINDEX	0x2 
#define IP_MIB_IPADENTNETMASK	0x4 
#define IP_MIB_IPADENTBCASTADDR	0x8 
#define IP_MIB_IPADENTREASMMAXSIZE	0x10 

typedef struct {
#define IP_MIB_IPADENTADDRLENGTH 4
    guchar   ipAdEntAddr[4];
    gint32   *ipAdEntIfIndex;
#define IP_MIB_IPADENTNETMASKLENGTH 4
    guchar   *ipAdEntNetMask;
    gint32   *ipAdEntBcastAddr;
    gint32   *ipAdEntReasmMaxSize;
} ip_mib_ipAddrEntry_t;

extern void
ip_mib_get_ipAddrTable(GSnmpSession *s, ip_mib_ipAddrEntry_t ***ipAddrEntry, gint mask);

extern void
ip_mib_free_ipAddrTable(ip_mib_ipAddrEntry_t **ipAddrEntry);

extern ip_mib_ipAddrEntry_t *
ip_mib_new_ipAddrEntry(void);

extern void
ip_mib_get_ipAddrEntry(GSnmpSession *s, ip_mib_ipAddrEntry_t **ipAddrEntry, guchar *ipAdEntAddr, gint mask);

extern void
ip_mib_free_ipAddrEntry(ip_mib_ipAddrEntry_t *ipAddrEntry);

/*
 * C type definitions for IP-MIB::ipNetToMediaEntry.
 */

#define IP_MIB_IPNETTOMEDIAIFINDEX	0x1 
#define IP_MIB_IPNETTOMEDIAPHYSADDRESS	0x2 
#define IP_MIB_IPNETTOMEDIANETADDRESS	0x4 
#define IP_MIB_IPNETTOMEDIATYPE	0x8 

typedef struct {
    gint32   ipNetToMediaIfIndex;
#define IP_MIB_IPNETTOMEDIANETADDRESSLENGTH 4
    guchar   ipNetToMediaNetAddress[4];
    guchar   *ipNetToMediaPhysAddress;
    guint16  _ipNetToMediaPhysAddressLength;	/* (0..65535) */
    gint32   *ipNetToMediaType;
} ip_mib_ipNetToMediaEntry_t;

extern void
ip_mib_get_ipNetToMediaTable(GSnmpSession *s, ip_mib_ipNetToMediaEntry_t ***ipNetToMediaEntry, gint mask);

extern void
ip_mib_free_ipNetToMediaTable(ip_mib_ipNetToMediaEntry_t **ipNetToMediaEntry);

extern ip_mib_ipNetToMediaEntry_t *
ip_mib_new_ipNetToMediaEntry(void);

extern void
ip_mib_get_ipNetToMediaEntry(GSnmpSession *s, ip_mib_ipNetToMediaEntry_t **ipNetToMediaEntry, gint32 ipNetToMediaIfIndex, guchar *ipNetToMediaNetAddress, gint mask);

extern void
ip_mib_set_ipNetToMediaEntry(GSnmpSession *s, ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry, gint mask);

extern void
ip_mib_free_ipNetToMediaEntry(ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry);

/*
 * C type definitions for IP-MIB::icmp.
 */

#define IP_MIB_ICMPINMSGS	0x1 
#define IP_MIB_ICMPINERRORS	0x2 
#define IP_MIB_ICMPINDESTUNREACHS	0x4 
#define IP_MIB_ICMPINTIMEEXCDS	0x8 
#define IP_MIB_ICMPINPARMPROBS	0x10 
#define IP_MIB_ICMPINSRCQUENCHS	0x20 
#define IP_MIB_ICMPINREDIRECTS	0x40 
#define IP_MIB_ICMPINECHOS	0x80 
#define IP_MIB_ICMPINECHOREPS	0x100 
#define IP_MIB_ICMPINTIMESTAMPS	0x200 
#define IP_MIB_ICMPINTIMESTAMPREPS	0x400 
#define IP_MIB_ICMPINADDRMASKS	0x800 
#define IP_MIB_ICMPINADDRMASKREPS	0x1000 
#define IP_MIB_ICMPOUTMSGS	0x2000 
#define IP_MIB_ICMPOUTERRORS	0x4000 
#define IP_MIB_ICMPOUTDESTUNREACHS	0x8000 
#define IP_MIB_ICMPOUTTIMEEXCDS	0x10000 
#define IP_MIB_ICMPOUTPARMPROBS	0x20000 
#define IP_MIB_ICMPOUTSRCQUENCHS	0x40000 
#define IP_MIB_ICMPOUTREDIRECTS	0x80000 
#define IP_MIB_ICMPOUTECHOS	0x100000 
#define IP_MIB_ICMPOUTECHOREPS	0x200000 
#define IP_MIB_ICMPOUTTIMESTAMPS	0x400000 
#define IP_MIB_ICMPOUTTIMESTAMPREPS	0x800000 
#define IP_MIB_ICMPOUTADDRMASKS	0x1000000 
#define IP_MIB_ICMPOUTADDRMASKREPS	0x2000000 

typedef struct {
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
} ip_mib_icmp_t;

extern ip_mib_icmp_t *
ip_mib_new_icmp(void);

extern void
ip_mib_get_icmp(GSnmpSession *s, ip_mib_icmp_t **icmp, gint mask);

extern void
ip_mib_free_icmp(ip_mib_icmp_t *icmp);


#endif /* _IP_MIB_H_ */
