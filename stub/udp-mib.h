/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from UDP-MIB revision 1994-11-01 00:00.
 *
 * $Id$
 */

#ifndef _UDP_MIB_H_
#define _UDP_MIB_H_

#include "stools.h"

/*
 * C type definitions for UDP-MIB::udp.
 */

typedef struct udp {
    guint32  *udpInDatagrams;
    guint32  *udpNoPorts;
    guint32  *udpInErrors;
    guint32  *udpOutDatagrams;
} udp_t;

extern int
udp_mib_get_udp(host_snmp *s, udp_t **udp);

extern void
udp_mib_free_udp(udp_t *udp);

/*
 * C type definitions for UDP-MIB::udpEntry.
 */

typedef struct udpEntry {
    guchar   *udpLocalAddress;
    gint32   *udpLocalPort;
} udpEntry_t;

extern int
udp_mib_get_udpEntry(host_snmp *s, udpEntry_t ***udpEntry);

extern void
udp_mib_free_udpEntry(udpEntry_t **udpEntry);


#endif /* _UDP_MIB_H_ */
