/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Derived from UDP-MIB:
 *   The MIB module for managing UDP implementations.
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

#ifndef _UDP_MIB_H_
#define _UDP_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * C type definitions for UDP-MIB::udp.
 */

#define UDP_MIB_UDPINDATAGRAMS  (1 << 0) 
#define UDP_MIB_UDPNOPORTS      (1 << 1) 
#define UDP_MIB_UDPINERRORS     (1 << 2) 
#define UDP_MIB_UDPOUTDATAGRAMS (1 << 3) 

typedef struct {
    guint32  *udpInDatagrams;      /* ro SNMPv2-SMI::Counter32 */
    guint32  *udpNoPorts;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *udpInErrors;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *udpOutDatagrams;     /* ro SNMPv2-SMI::Counter32 */
} udp_mib_udp_t;

extern udp_mib_udp_t *
udp_mib_new_udp(void);

extern void
udp_mib_get_udp(GSnmpSession *s, udp_mib_udp_t **udp, gint64 mask);

extern void
udp_mib_free_udp(udp_mib_udp_t *udp);

/*
 * C type definitions for UDP-MIB::udpEntry.
 */

#define UDP_MIB_UDPLOCALADDRESS (1 << 0) 
#define UDP_MIB_UDPLOCALPORT    (1 << 1) 

typedef struct {
    guchar   udpLocalAddress[4];  /* ro SNMPv2-SMI::IpAddress */
#define UDP_MIB_UDPLOCALADDRESSLENGTH 4
    gint32   udpLocalPort;         /* ro */
} udp_mib_udpEntry_t;

extern void
udp_mib_get_udpTable(GSnmpSession *s, udp_mib_udpEntry_t ***udpEntry, gint64 mask);

extern void
udp_mib_free_udpTable(udp_mib_udpEntry_t **udpEntry);

extern udp_mib_udpEntry_t *
udp_mib_new_udpEntry(void);

extern void
udp_mib_get_udpEntry(GSnmpSession *s, udp_mib_udpEntry_t **udpEntry, guchar *udpLocalAddress, gint32 udpLocalPort, gint64 mask);

extern void
udp_mib_free_udpEntry(udp_mib_udpEntry_t *udpEntry);


G_END_DECLS

#endif /* _UDP_MIB_H_ */
