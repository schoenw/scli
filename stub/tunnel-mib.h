/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from TUNNEL-MIB:
 *   The MIB module for management of IP Tunnels, independent of
 *   the specific encapsulation scheme in use.
 *
 * Revision 1999-08-24 12:00:
 *   Initial version, published as RFC 2667.
 *
 * $Id$
 */

#ifndef _TUNNEL_MIB_H_
#define _TUNNEL_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_OTHER   1
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_DIRECT  2
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_GRE     3
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_MINIMAL 4
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_L2TP    5
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_PPTP    6
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_L2F     7
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_UDP     8
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD_ATMP    9

extern GSnmpEnum const tunnel_mib_enums_tunnelIfEncapsMethod[];

#define TUNNEL_MIB_TUNNELIFSECURITY_NONE  1
#define TUNNEL_MIB_TUNNELIFSECURITY_IPSEC 2
#define TUNNEL_MIB_TUNNELIFSECURITY_OTHER 3

extern GSnmpEnum const tunnel_mib_enums_tunnelIfSecurity[];

#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_OTHER   1
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_DIRECT  2
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_GRE     3
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_MINIMAL 4
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_L2TP    5
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_PPTP    6
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_L2F     7
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_UDP     8
#define TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_ATMP    9

extern GSnmpEnum const tunnel_mib_enums_tunnelConfigEncapsMethod[];

#define TUNNEL_MIB_TUNNELCONFIGSTATUS_ACTIVE        1
#define TUNNEL_MIB_TUNNELCONFIGSTATUS_NOTINSERVICE  2
#define TUNNEL_MIB_TUNNELCONFIGSTATUS_NOTREADY      3
#define TUNNEL_MIB_TUNNELCONFIGSTATUS_CREATEANDGO   4
#define TUNNEL_MIB_TUNNELCONFIGSTATUS_CREATEANDWAIT 5
#define TUNNEL_MIB_TUNNELCONFIGSTATUS_DESTROY       6

extern GSnmpEnum const tunnel_mib_enums_tunnelConfigStatus[];


/*
 * C type definitions for TUNNEL-MIB::tunnelIfEntry.
 */

#define TUNNEL_MIB_TUNNELIFLOCALADDRESS  (1 << 0) 
#define TUNNEL_MIB_TUNNELIFREMOTEADDRESS (1 << 1) 
#define TUNNEL_MIB_TUNNELIFENCAPSMETHOD  (1 << 2) 
#define TUNNEL_MIB_TUNNELIFHOPLIMIT      (1 << 3) 
#define TUNNEL_MIB_TUNNELIFSECURITY      (1 << 4) 
#define TUNNEL_MIB_TUNNELIFTOS           (1 << 5) 

typedef struct {
    gint32   ifIndex;
    guchar   *tunnelIfLocalAddress;
#define TUNNEL_MIB_TUNNELIFLOCALADDRESSLENGTH 4
    guchar   *tunnelIfRemoteAddress;
#define TUNNEL_MIB_TUNNELIFREMOTEADDRESSLENGTH 4
    gint32   *tunnelIfEncapsMethod;
    gint32   *tunnelIfHopLimit;
    gint32   *tunnelIfSecurity;
    gint32   *tunnelIfTOS;
} tunnel_mib_tunnelIfEntry_t;

extern void
tunnel_mib_get_tunnelIfTable(GSnmpSession *s, tunnel_mib_tunnelIfEntry_t ***tunnelIfEntry, gint mask);

extern void
tunnel_mib_free_tunnelIfTable(tunnel_mib_tunnelIfEntry_t **tunnelIfEntry);

extern tunnel_mib_tunnelIfEntry_t *
tunnel_mib_new_tunnelIfEntry(void);

extern void
tunnel_mib_get_tunnelIfEntry(GSnmpSession *s, tunnel_mib_tunnelIfEntry_t **tunnelIfEntry, gint32 ifIndex, gint mask);

extern void
tunnel_mib_set_tunnelIfEntry(GSnmpSession *s, tunnel_mib_tunnelIfEntry_t *tunnelIfEntry, gint mask);

extern void
tunnel_mib_free_tunnelIfEntry(tunnel_mib_tunnelIfEntry_t *tunnelIfEntry);

/*
 * C type definitions for TUNNEL-MIB::tunnelConfigEntry.
 */

#define TUNNEL_MIB_TUNNELCONFIGIFINDEX (1 << 0) 
#define TUNNEL_MIB_TUNNELCONFIGSTATUS  (1 << 1) 

typedef struct {
    guchar   tunnelConfigLocalAddress[4];
#define TUNNEL_MIB_TUNNELCONFIGLOCALADDRESSLENGTH 4
    guchar   tunnelConfigRemoteAddress[4];
#define TUNNEL_MIB_TUNNELCONFIGREMOTEADDRESSLENGTH 4
    gint32   tunnelConfigEncapsMethod;
    gint32   tunnelConfigID;
    gint32   *tunnelConfigIfIndex;
    gint32   *tunnelConfigStatus;
} tunnel_mib_tunnelConfigEntry_t;

extern void
tunnel_mib_get_tunnelConfigTable(GSnmpSession *s, tunnel_mib_tunnelConfigEntry_t ***tunnelConfigEntry, gint mask);

extern void
tunnel_mib_free_tunnelConfigTable(tunnel_mib_tunnelConfigEntry_t **tunnelConfigEntry);

extern tunnel_mib_tunnelConfigEntry_t *
tunnel_mib_new_tunnelConfigEntry(void);

extern void
tunnel_mib_get_tunnelConfigEntry(GSnmpSession *s, tunnel_mib_tunnelConfigEntry_t **tunnelConfigEntry, guchar *tunnelConfigLocalAddress, guchar *tunnelConfigRemoteAddress, gint32 tunnelConfigEncapsMethod, gint32 tunnelConfigID, gint mask);

extern void
tunnel_mib_set_tunnelConfigEntry(GSnmpSession *s, tunnel_mib_tunnelConfigEntry_t *tunnelConfigEntry, gint mask);

extern void
tunnel_mib_free_tunnelConfigEntry(tunnel_mib_tunnelConfigEntry_t *tunnelConfigEntry);


#endif /* _TUNNEL_MIB_H_ */
