/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3-pre1:
 *   smidump -f scli \
 *     --scli-exclude='icmp' IP-MIB
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

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define IP_MIB_IPFORWARDING_FORWARDING    1
#define IP_MIB_IPFORWARDING_NOTFORWARDING 2

extern GNetSnmpEnum const ip_mib_enums_ipForwarding[];

#define IP_MIB_IPNETTOMEDIATYPE_OTHER   1
#define IP_MIB_IPNETTOMEDIATYPE_INVALID 2
#define IP_MIB_IPNETTOMEDIATYPE_DYNAMIC 3
#define IP_MIB_IPNETTOMEDIATYPE_STATIC  4

extern GNetSnmpEnum const ip_mib_enums_ipNetToMediaType[];


/*
 * C type definitions for IP-MIB::ip.
 */

#define IP_MIB_IPFORWARDING      (1 << 0) 
#define IP_MIB_IPDEFAULTTTL      (1 << 1) 
#define IP_MIB_IPINRECEIVES      (1 << 2) 
#define IP_MIB_IPINHDRERRORS     (1 << 3) 
#define IP_MIB_IPINADDRERRORS    (1 << 4) 
#define IP_MIB_IPFORWDATAGRAMS   (1 << 5) 
#define IP_MIB_IPINUNKNOWNPROTOS (1 << 6) 
#define IP_MIB_IPINDISCARDS      (1 << 7) 
#define IP_MIB_IPINDELIVERS      (1 << 8) 
#define IP_MIB_IPOUTREQUESTS     (1 << 9) 
#define IP_MIB_IPOUTDISCARDS     (1 << 10) 
#define IP_MIB_IPOUTNOROUTES     (1 << 11) 
#define IP_MIB_IPREASMTIMEOUT    (1 << 12) 
#define IP_MIB_IPREASMREQDS      (1 << 13) 
#define IP_MIB_IPREASMOKS        (1 << 14) 
#define IP_MIB_IPREASMFAILS      (1 << 15) 
#define IP_MIB_IPFRAGOKS         (1 << 16) 
#define IP_MIB_IPFRAGFAILS       (1 << 17) 
#define IP_MIB_IPFRAGCREATES     (1 << 18) 
#define IP_MIB_IPROUTINGDISCARDS (1 << 19) 

typedef struct {
    gint32   *ipForwarding;          /* rw */
    gint32   *ipDefaultTTL;          /* rw */
    guint32  *ipInReceives;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipInHdrErrors;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipInAddrErrors;        /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipForwDatagrams;       /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipInUnknownProtos;     /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipInDiscards;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipInDelivers;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipOutRequests;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipOutDiscards;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipOutNoRoutes;         /* ro SNMPv2-SMI::Counter32 */
    gint32   *ipReasmTimeout;        /* ro Integer32 */
    guint32  *ipReasmReqds;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipReasmOKs;            /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipReasmFails;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipFragOKs;             /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipFragFails;           /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipFragCreates;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *ipRoutingDiscards;     /* ro SNMPv2-SMI::Counter32 */
} ip_mib_ip_t;

extern ip_mib_ip_t *
ip_mib_new_ip(void);

extern void
ip_mib_get_ip(GNetSnmp *s, ip_mib_ip_t **ip, gint64 mask);

extern void
ip_mib_set_ip(GNetSnmp *s, ip_mib_ip_t *ip, gint64 mask);

extern void
ip_mib_free_ip(ip_mib_ip_t *ip);

/*
 * C type definitions for IP-MIB::ipAddrEntry.
 */

#define IP_MIB_IPADENTADDR         (1 << 0) 
#define IP_MIB_IPADENTIFINDEX      (1 << 1) 
#define IP_MIB_IPADENTNETMASK      (1 << 2) 
#define IP_MIB_IPADENTBCASTADDR    (1 << 3) 
#define IP_MIB_IPADENTREASMMAXSIZE (1 << 4) 

typedef struct {
    guchar   ipAdEntAddr[4];          /* ro SNMPv2-SMI::IpAddress */
#define IP_MIB_IPADENTADDRLENGTH 4
    gint32   *ipAdEntIfIndex;          /* ro */
    guchar   *ipAdEntNetMask;          /* ro SNMPv2-SMI::IpAddress */
#define IP_MIB_IPADENTNETMASKLENGTH 4
    gint32   *ipAdEntBcastAddr;        /* ro */
    gint32   *ipAdEntReasmMaxSize;     /* ro */
} ip_mib_ipAddrEntry_t;

extern void
ip_mib_get_ipAddrTable(GNetSnmp *s, ip_mib_ipAddrEntry_t ***ipAddrEntry, gint64 mask);

extern void
ip_mib_free_ipAddrTable(ip_mib_ipAddrEntry_t **ipAddrEntry);

extern ip_mib_ipAddrEntry_t *
ip_mib_new_ipAddrEntry(void);

extern void
ip_mib_get_ipAddrEntry(GNetSnmp *s, ip_mib_ipAddrEntry_t **ipAddrEntry, guchar *ipAdEntAddr, gint64 mask);

extern void
ip_mib_free_ipAddrEntry(ip_mib_ipAddrEntry_t *ipAddrEntry);

/*
 * C type definitions for IP-MIB::ipNetToMediaEntry.
 */

#define IP_MIB_IPNETTOMEDIAIFINDEX     (1 << 0) 
#define IP_MIB_IPNETTOMEDIAPHYSADDRESS (1 << 1) 
#define IP_MIB_IPNETTOMEDIANETADDRESS  (1 << 2) 
#define IP_MIB_IPNETTOMEDIATYPE        (1 << 3) 

typedef struct {
    gint32   ipNetToMediaIfIndex;          /* rw */
    guchar   ipNetToMediaNetAddress[4];   /* rw SNMPv2-SMI::IpAddress */
#define IP_MIB_IPNETTOMEDIANETADDRESSLENGTH 4
    guchar   *ipNetToMediaPhysAddress;     /* rw SNMPv2-TC::PhysAddress */
#define IP_MIB_IPNETTOMEDIAPHYSADDRESSMINLENGTH 0
#define IP_MIB_IPNETTOMEDIAPHYSADDRESSMAXLENGTH 65535
    guint16  _ipNetToMediaPhysAddressLength;
    gint32   *ipNetToMediaType;            /* rw */
} ip_mib_ipNetToMediaEntry_t;

extern void
ip_mib_get_ipNetToMediaTable(GNetSnmp *s, ip_mib_ipNetToMediaEntry_t ***ipNetToMediaEntry, gint64 mask);

extern void
ip_mib_free_ipNetToMediaTable(ip_mib_ipNetToMediaEntry_t **ipNetToMediaEntry);

extern ip_mib_ipNetToMediaEntry_t *
ip_mib_new_ipNetToMediaEntry(void);

extern void
ip_mib_get_ipNetToMediaEntry(GNetSnmp *s, ip_mib_ipNetToMediaEntry_t **ipNetToMediaEntry, gint32 ipNetToMediaIfIndex, guchar *ipNetToMediaNetAddress, gint64 mask);

extern void
ip_mib_set_ipNetToMediaEntry(GNetSnmp *s, ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry, gint64 mask);

extern void
ip_mib_free_ipNetToMediaEntry(ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry);


G_END_DECLS

#endif /* _IP_MIB_H_ */
