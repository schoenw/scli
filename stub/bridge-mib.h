/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from BRIDGE-MIB:
 *
 * $Id$
 */

#ifndef _BRIDGE_MIB_H_
#define _BRIDGE_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define BRIDGE_MIB_DOT1DBASETYPE_UNKNOWN	1
#define BRIDGE_MIB_DOT1DBASETYPE_TRANSPARENT_ONLY	2
#define BRIDGE_MIB_DOT1DBASETYPE_SOURCEROUTE_ONLY	3
#define BRIDGE_MIB_DOT1DBASETYPE_SRT	4

extern GSnmpEnum const bridge_mib_enums_dot1dBaseType[];

#define BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_UNKNOWN	1
#define BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_DECLB100	2
#define BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_IEEE8021D	3

extern GSnmpEnum const bridge_mib_enums_dot1dStpProtocolSpecification[];

#define BRIDGE_MIB_DOT1DSTPPORTSTATE_DISABLED	1
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_BLOCKING	2
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_LISTENING	3
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_LEARNING	4
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_FORWARDING	5
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_BROKEN	6

extern GSnmpEnum const bridge_mib_enums_dot1dStpPortState[];

#define BRIDGE_MIB_DOT1DSTPPORTENABLE_ENABLED	1
#define BRIDGE_MIB_DOT1DSTPPORTENABLE_DISABLED	2

extern GSnmpEnum const bridge_mib_enums_dot1dStpPortEnable[];

#define BRIDGE_MIB_DOT1DTPFDBSTATUS_OTHER	1
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_INVALID	2
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_LEARNED	3
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_SELF	4
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_MGMT	5

extern GSnmpEnum const bridge_mib_enums_dot1dTpFdbStatus[];

#define BRIDGE_MIB_DOT1DSTATICSTATUS_OTHER	1
#define BRIDGE_MIB_DOT1DSTATICSTATUS_INVALID	2
#define BRIDGE_MIB_DOT1DSTATICSTATUS_PERMANENT	3
#define BRIDGE_MIB_DOT1DSTATICSTATUS_DELETEONRESET	4
#define BRIDGE_MIB_DOT1DSTATICSTATUS_DELETEONTIMEOUT	5

extern GSnmpEnum const bridge_mib_enums_dot1dStaticStatus[];


/*
 * C type definitions for BRIDGE-MIB::dot1dBase.
 */

typedef struct {
    guchar   *dot1dBaseBridgeAddress;
    gint32   *dot1dBaseNumPorts;
    gint32   *dot1dBaseType;
} bridge_mib_dot1dBase_t;

extern bridge_mib_dot1dBase_t *
bridge_mib_new_dot1dBase();

extern int
bridge_mib_get_dot1dBase(GSnmpSession *s, bridge_mib_dot1dBase_t **dot1dBase);

extern void
bridge_mib_free_dot1dBase(bridge_mib_dot1dBase_t *dot1dBase);

/*
 * C type definitions for BRIDGE-MIB::dot1dBasePortEntry.
 */

typedef struct {
    gint32   dot1dBasePort;
    gint32   *dot1dBasePortIfIndex;
    guint32  *dot1dBasePortCircuit;
    gsize    _dot1dBasePortCircuitLength;
    guint32  *dot1dBasePortDelayExceededDiscards;
    guint32  *dot1dBasePortMtuExceededDiscards;
} bridge_mib_dot1dBasePortEntry_t;

extern int
bridge_mib_get_dot1dBasePortTable(GSnmpSession *s, bridge_mib_dot1dBasePortEntry_t ***dot1dBasePortEntry);

extern void
bridge_mib_free_dot1dBasePortTable(bridge_mib_dot1dBasePortEntry_t **dot1dBasePortEntry);

extern bridge_mib_dot1dBasePortEntry_t *
bridge_mib_new_dot1dBasePortEntry();

extern int
bridge_mib_get_dot1dBasePortEntry(GSnmpSession *s, bridge_mib_dot1dBasePortEntry_t **dot1dBasePortEntry);

extern void
bridge_mib_free_dot1dBasePortEntry(bridge_mib_dot1dBasePortEntry_t *dot1dBasePortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dStp.
 */

typedef struct {
    gint32   *dot1dStpProtocolSpecification;
    gint32   *dot1dStpPriority;
    guint32  *dot1dStpTimeSinceTopologyChange;
    guint32  *dot1dStpTopChanges;
    guchar   *dot1dStpDesignatedRoot;
    gint32   *dot1dStpRootCost;
    gint32   *dot1dStpRootPort;
    gint32   *dot1dStpMaxAge;
    gint32   *dot1dStpHelloTime;
    gint32   *dot1dStpHoldTime;
    gint32   *dot1dStpForwardDelay;
    gint32   *dot1dStpBridgeMaxAge;
    gint32   *dot1dStpBridgeHelloTime;
    gint32   *dot1dStpBridgeForwardDelay;
} bridge_mib_dot1dStp_t;

extern bridge_mib_dot1dStp_t *
bridge_mib_new_dot1dStp();

extern int
bridge_mib_get_dot1dStp(GSnmpSession *s, bridge_mib_dot1dStp_t **dot1dStp);

extern int
bridge_mib_set_dot1dStp(GSnmpSession *s, bridge_mib_dot1dStp_t *dot1dStp);

extern void
bridge_mib_free_dot1dStp(bridge_mib_dot1dStp_t *dot1dStp);

/*
 * C type definitions for BRIDGE-MIB::dot1dStpPortEntry.
 */

typedef struct {
    gint32   dot1dStpPort;
    gint32   *dot1dStpPortPriority;
    gint32   *dot1dStpPortState;
    gint32   *dot1dStpPortEnable;
    gint32   *dot1dStpPortPathCost;
    guchar   *dot1dStpPortDesignatedRoot;
    gint32   *dot1dStpPortDesignatedCost;
    guchar   *dot1dStpPortDesignatedBridge;
    guchar   *dot1dStpPortDesignatedPort;
    guint32  *dot1dStpPortForwardTransitions;
} bridge_mib_dot1dStpPortEntry_t;

extern int
bridge_mib_get_dot1dStpPortTable(GSnmpSession *s, bridge_mib_dot1dStpPortEntry_t ***dot1dStpPortEntry);

extern void
bridge_mib_free_dot1dStpPortTable(bridge_mib_dot1dStpPortEntry_t **dot1dStpPortEntry);

extern bridge_mib_dot1dStpPortEntry_t *
bridge_mib_new_dot1dStpPortEntry();

extern int
bridge_mib_get_dot1dStpPortEntry(GSnmpSession *s, bridge_mib_dot1dStpPortEntry_t **dot1dStpPortEntry);

extern int
bridge_mib_set_dot1dStpPortEntry(GSnmpSession *s, bridge_mib_dot1dStpPortEntry_t *dot1dStpPortEntry);

extern void
bridge_mib_free_dot1dStpPortEntry(bridge_mib_dot1dStpPortEntry_t *dot1dStpPortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dTp.
 */

typedef struct {
    guint32  *dot1dTpLearnedEntryDiscards;
    gint32   *dot1dTpAgingTime;
} bridge_mib_dot1dTp_t;

extern bridge_mib_dot1dTp_t *
bridge_mib_new_dot1dTp();

extern int
bridge_mib_get_dot1dTp(GSnmpSession *s, bridge_mib_dot1dTp_t **dot1dTp);

extern int
bridge_mib_set_dot1dTp(GSnmpSession *s, bridge_mib_dot1dTp_t *dot1dTp);

extern void
bridge_mib_free_dot1dTp(bridge_mib_dot1dTp_t *dot1dTp);

/*
 * C type definitions for BRIDGE-MIB::dot1dTpFdbEntry.
 */

typedef struct {
    guchar   dot1dTpFdbAddress[6];
    gint32   *dot1dTpFdbPort;
    gint32   *dot1dTpFdbStatus;
} bridge_mib_dot1dTpFdbEntry_t;

extern int
bridge_mib_get_dot1dTpFdbTable(GSnmpSession *s, bridge_mib_dot1dTpFdbEntry_t ***dot1dTpFdbEntry);

extern void
bridge_mib_free_dot1dTpFdbTable(bridge_mib_dot1dTpFdbEntry_t **dot1dTpFdbEntry);

extern bridge_mib_dot1dTpFdbEntry_t *
bridge_mib_new_dot1dTpFdbEntry();

extern int
bridge_mib_get_dot1dTpFdbEntry(GSnmpSession *s, bridge_mib_dot1dTpFdbEntry_t **dot1dTpFdbEntry);

extern void
bridge_mib_free_dot1dTpFdbEntry(bridge_mib_dot1dTpFdbEntry_t *dot1dTpFdbEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dTpPortEntry.
 */

typedef struct {
    gint32   dot1dTpPort;
    gint32   *dot1dTpPortMaxInfo;
    guint32  *dot1dTpPortInFrames;
    guint32  *dot1dTpPortOutFrames;
    guint32  *dot1dTpPortInDiscards;
} bridge_mib_dot1dTpPortEntry_t;

extern int
bridge_mib_get_dot1dTpPortTable(GSnmpSession *s, bridge_mib_dot1dTpPortEntry_t ***dot1dTpPortEntry);

extern void
bridge_mib_free_dot1dTpPortTable(bridge_mib_dot1dTpPortEntry_t **dot1dTpPortEntry);

extern bridge_mib_dot1dTpPortEntry_t *
bridge_mib_new_dot1dTpPortEntry();

extern int
bridge_mib_get_dot1dTpPortEntry(GSnmpSession *s, bridge_mib_dot1dTpPortEntry_t **dot1dTpPortEntry);

extern void
bridge_mib_free_dot1dTpPortEntry(bridge_mib_dot1dTpPortEntry_t *dot1dTpPortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dStaticEntry.
 */

typedef struct {
    guchar   dot1dStaticAddress[6];
    gint32   dot1dStaticReceivePort;
    guchar   *dot1dStaticAllowedToGoTo;
    gsize    _dot1dStaticAllowedToGoToLength;
    gint32   *dot1dStaticStatus;
} bridge_mib_dot1dStaticEntry_t;

extern int
bridge_mib_get_dot1dStaticTable(GSnmpSession *s, bridge_mib_dot1dStaticEntry_t ***dot1dStaticEntry);

extern void
bridge_mib_free_dot1dStaticTable(bridge_mib_dot1dStaticEntry_t **dot1dStaticEntry);

extern bridge_mib_dot1dStaticEntry_t *
bridge_mib_new_dot1dStaticEntry();

extern int
bridge_mib_get_dot1dStaticEntry(GSnmpSession *s, bridge_mib_dot1dStaticEntry_t **dot1dStaticEntry);

extern int
bridge_mib_set_dot1dStaticEntry(GSnmpSession *s, bridge_mib_dot1dStaticEntry_t *dot1dStaticEntry);

extern void
bridge_mib_free_dot1dStaticEntry(bridge_mib_dot1dStaticEntry_t *dot1dStaticEntry);


#endif /* _BRIDGE_MIB_H_ */
