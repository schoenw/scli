/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from BRIDGE-MIB revision [unknown].
 *
 * $Id$
 */

#ifndef _BRIDGE_MIB_H_
#define _BRIDGE_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

extern stls_table_t bridge_mib_enums_dot1dBaseType[];
extern stls_table_t bridge_mib_enums_dot1dStpProtocolSpecification[];
extern stls_table_t bridge_mib_enums_dot1dStpPortState[];
extern stls_table_t bridge_mib_enums_dot1dStpPortEnable[];
extern stls_table_t bridge_mib_enums_dot1dTpFdbStatus[];
extern stls_table_t bridge_mib_enums_dot1dStaticStatus[];

/*
 * C type definitions for BRIDGE-MIB::dot1dBase.
 */

typedef struct dot1dBase {
    guchar   *dot1dBaseBridgeAddress;
    gint32   *dot1dBaseNumPorts;
    gint32   *dot1dBaseType;
} dot1dBase_t;

extern dot1dBase_t *
bridge_mib_new_dot1dBase();

extern int
bridge_mib_get_dot1dBase(host_snmp *s, dot1dBase_t **dot1dBase);

extern void
bridge_mib_free_dot1dBase(dot1dBase_t *dot1dBase);

/*
 * C type definitions for BRIDGE-MIB::dot1dBasePortEntry.
 */

typedef struct dot1dBasePortEntry {
    gint32   dot1dBasePort;
    gint32   *dot1dBasePortIfIndex;
    guint32  *dot1dBasePortCircuit;
    gsize    _dot1dBasePortCircuitLength;
    guint32  *dot1dBasePortDelayExceededDiscards;
    guint32  *dot1dBasePortMtuExceededDiscards;
} dot1dBasePortEntry_t;

extern int
bridge_mib_get_dot1dBasePortTable(host_snmp *s, dot1dBasePortEntry_t ***dot1dBasePortEntry);

extern void
bridge_mib_free_dot1dBasePortTable(dot1dBasePortEntry_t **dot1dBasePortEntry);

extern dot1dBasePortEntry_t *
bridge_mib_new_dot1dBasePortEntry();

extern int
bridge_mib_get_dot1dBasePortEntry(host_snmp *s, dot1dBasePortEntry_t **dot1dBasePortEntry);

extern void
bridge_mib_free_dot1dBasePortEntry(dot1dBasePortEntry_t *dot1dBasePortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dStp.
 */

typedef struct dot1dStp {
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
} dot1dStp_t;

extern dot1dStp_t *
bridge_mib_new_dot1dStp();

extern int
bridge_mib_get_dot1dStp(host_snmp *s, dot1dStp_t **dot1dStp);

extern int
bridge_mib_set_dot1dStp(host_snmp *s, dot1dStp_t *dot1dStp);

extern void
bridge_mib_free_dot1dStp(dot1dStp_t *dot1dStp);

/*
 * C type definitions for BRIDGE-MIB::dot1dStpPortEntry.
 */

typedef struct dot1dStpPortEntry {
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
} dot1dStpPortEntry_t;

extern int
bridge_mib_get_dot1dStpPortTable(host_snmp *s, dot1dStpPortEntry_t ***dot1dStpPortEntry);

extern void
bridge_mib_free_dot1dStpPortTable(dot1dStpPortEntry_t **dot1dStpPortEntry);

extern dot1dStpPortEntry_t *
bridge_mib_new_dot1dStpPortEntry();

extern int
bridge_mib_get_dot1dStpPortEntry(host_snmp *s, dot1dStpPortEntry_t **dot1dStpPortEntry);

extern int
bridge_mib_set_dot1dStpPortEntry(host_snmp *s, dot1dStpPortEntry_t *dot1dStpPortEntry);

extern void
bridge_mib_free_dot1dStpPortEntry(dot1dStpPortEntry_t *dot1dStpPortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dTp.
 */

typedef struct dot1dTp {
    guint32  *dot1dTpLearnedEntryDiscards;
    gint32   *dot1dTpAgingTime;
} dot1dTp_t;

extern dot1dTp_t *
bridge_mib_new_dot1dTp();

extern int
bridge_mib_get_dot1dTp(host_snmp *s, dot1dTp_t **dot1dTp);

extern int
bridge_mib_set_dot1dTp(host_snmp *s, dot1dTp_t *dot1dTp);

extern void
bridge_mib_free_dot1dTp(dot1dTp_t *dot1dTp);

/*
 * C type definitions for BRIDGE-MIB::dot1dTpFdbEntry.
 */

typedef struct dot1dTpFdbEntry {
    guchar   dot1dTpFdbAddress[6];
    gint32   *dot1dTpFdbPort;
    gint32   *dot1dTpFdbStatus;
} dot1dTpFdbEntry_t;

extern int
bridge_mib_get_dot1dTpFdbTable(host_snmp *s, dot1dTpFdbEntry_t ***dot1dTpFdbEntry);

extern void
bridge_mib_free_dot1dTpFdbTable(dot1dTpFdbEntry_t **dot1dTpFdbEntry);

extern dot1dTpFdbEntry_t *
bridge_mib_new_dot1dTpFdbEntry();

extern int
bridge_mib_get_dot1dTpFdbEntry(host_snmp *s, dot1dTpFdbEntry_t **dot1dTpFdbEntry);

extern void
bridge_mib_free_dot1dTpFdbEntry(dot1dTpFdbEntry_t *dot1dTpFdbEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dTpPortEntry.
 */

typedef struct dot1dTpPortEntry {
    gint32   dot1dTpPort;
    gint32   *dot1dTpPortMaxInfo;
    guint32  *dot1dTpPortInFrames;
    guint32  *dot1dTpPortOutFrames;
    guint32  *dot1dTpPortInDiscards;
} dot1dTpPortEntry_t;

extern int
bridge_mib_get_dot1dTpPortTable(host_snmp *s, dot1dTpPortEntry_t ***dot1dTpPortEntry);

extern void
bridge_mib_free_dot1dTpPortTable(dot1dTpPortEntry_t **dot1dTpPortEntry);

extern dot1dTpPortEntry_t *
bridge_mib_new_dot1dTpPortEntry();

extern int
bridge_mib_get_dot1dTpPortEntry(host_snmp *s, dot1dTpPortEntry_t **dot1dTpPortEntry);

extern void
bridge_mib_free_dot1dTpPortEntry(dot1dTpPortEntry_t *dot1dTpPortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dStaticEntry.
 */

typedef struct dot1dStaticEntry {
    guchar   dot1dStaticAddress[6];
    gint32   dot1dStaticReceivePort;
    guchar   *dot1dStaticAllowedToGoTo;
    gsize    _dot1dStaticAllowedToGoToLength;
    gint32   *dot1dStaticStatus;
} dot1dStaticEntry_t;

extern int
bridge_mib_get_dot1dStaticTable(host_snmp *s, dot1dStaticEntry_t ***dot1dStaticEntry);

extern void
bridge_mib_free_dot1dStaticTable(dot1dStaticEntry_t **dot1dStaticEntry);

extern dot1dStaticEntry_t *
bridge_mib_new_dot1dStaticEntry();

extern int
bridge_mib_get_dot1dStaticEntry(host_snmp *s, dot1dStaticEntry_t **dot1dStaticEntry);

extern int
bridge_mib_set_dot1dStaticEntry(host_snmp *s, dot1dStaticEntry_t *dot1dStaticEntry);

extern void
bridge_mib_free_dot1dStaticEntry(dot1dStaticEntry_t *dot1dStaticEntry);


#endif /* _BRIDGE_MIB_H_ */
