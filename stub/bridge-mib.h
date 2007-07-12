/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli BRIDGE-MIB
 *
 * Derived from BRIDGE-MIB:
 *   The Bridge MIB module for managing devices that support
 *   IEEE 802.1D.
 *   
 *   Copyright (C) The Internet Society (2005).  This version of
 *   this MIB module is part of RFC 4188; see the RFC itself for
 *   full legal notices.
 *
 * Revision 2005-09-19 00:00:
 *   Third revision, published as part of RFC 4188.
 *   
 *   The MIB module has been converted to SMIv2 format.
 *   Conformance statements have been added and some
 *   description and reference clauses have been updated.
 *   
 *   The object dot1dStpPortPathCost32 was added to
 *   support IEEE 802.1t and the permissible values of
 *   dot1dStpPriority and dot1dStpPortPriority have been
 *   clarified for bridges supporting IEEE 802.1t or
 *   IEEE 802.1w.
 *   
 *   The interpretation of dot1dStpTimeSinceTopologyChange
 *   has been clarified for bridges supporting the Rapid
 *   Spanning Tree Protocol (RSTP).
 *
 * Revision 1993-07-31 00:00:
 *   Second revision, published as part of RFC 1493.
 *
 * Revision 1991-12-31 00:00:
 *   Initial revision, published as part of RFC 1286.
 *
 * $Id$
 */

#ifndef _BRIDGE_MIB_H_
#define _BRIDGE_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define BRIDGE_MIB_DOT1DBASETYPE_UNKNOWN          1
#define BRIDGE_MIB_DOT1DBASETYPE_TRANSPARENT_ONLY 2
#define BRIDGE_MIB_DOT1DBASETYPE_SOURCEROUTE_ONLY 3
#define BRIDGE_MIB_DOT1DBASETYPE_SRT              4

extern GNetSnmpEnum const bridge_mib_enums_dot1dBaseType[];

#define BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_UNKNOWN   1
#define BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_DECLB100  2
#define BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION_IEEE8021D 3

extern GNetSnmpEnum const bridge_mib_enums_dot1dStpProtocolSpecification[];

#define BRIDGE_MIB_DOT1DSTPPORTSTATE_DISABLED   1
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_BLOCKING   2
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_LISTENING  3
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_LEARNING   4
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_FORWARDING 5
#define BRIDGE_MIB_DOT1DSTPPORTSTATE_BROKEN     6

extern GNetSnmpEnum const bridge_mib_enums_dot1dStpPortState[];

#define BRIDGE_MIB_DOT1DSTPPORTENABLE_ENABLED  1
#define BRIDGE_MIB_DOT1DSTPPORTENABLE_DISABLED 2

extern GNetSnmpEnum const bridge_mib_enums_dot1dStpPortEnable[];

#define BRIDGE_MIB_DOT1DTPFDBSTATUS_OTHER   1
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_INVALID 2
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_LEARNED 3
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_SELF    4
#define BRIDGE_MIB_DOT1DTPFDBSTATUS_MGMT    5

extern GNetSnmpEnum const bridge_mib_enums_dot1dTpFdbStatus[];

#define BRIDGE_MIB_DOT1DSTATICSTATUS_OTHER           1
#define BRIDGE_MIB_DOT1DSTATICSTATUS_INVALID         2
#define BRIDGE_MIB_DOT1DSTATICSTATUS_PERMANENT       3
#define BRIDGE_MIB_DOT1DSTATICSTATUS_DELETEONRESET   4
#define BRIDGE_MIB_DOT1DSTATICSTATUS_DELETEONTIMEOUT 5

extern GNetSnmpEnum const bridge_mib_enums_dot1dStaticStatus[];


/*
 * Tables to map notifications to strings and vice versa.
 */

#define BRIDGE_MIB_NEWROOT	1,3,6,1,2,1,17,0,1
#define BRIDGE_MIB_TOPOLOGYCHANGE	1,3,6,1,2,1,17,0,2

extern GNetSnmpIdentity const bridge_mib_notifications[];

/*
 * C type definitions for BRIDGE-MIB::dot1dBase.
 */

#define BRIDGE_MIB_DOT1DBASEBRIDGEADDRESS (1 << 0) 
#define BRIDGE_MIB_DOT1DBASENUMPORTS      (1 << 1) 
#define BRIDGE_MIB_DOT1DBASETYPE          (1 << 2) 

typedef struct {
    guchar   *dot1dBaseBridgeAddress;     /* ro SNMPv2-TC::MacAddress */
#define BRIDGE_MIB_DOT1DBASEBRIDGEADDRESSLENGTH 6
    gint32   *dot1dBaseNumPorts;          /* ro Integer32 [ports] */
    gint32   *dot1dBaseType;              /* ro */
} bridge_mib_dot1dBase_t;

extern bridge_mib_dot1dBase_t *
bridge_mib_new_dot1dBase(void);

extern void
bridge_mib_get_dot1dBase(GNetSnmp *s, bridge_mib_dot1dBase_t **dot1dBase, gint64 mask);

extern void
bridge_mib_free_dot1dBase(bridge_mib_dot1dBase_t *dot1dBase);

/*
 * C type definitions for BRIDGE-MIB::dot1dBasePortEntry.
 */

#define BRIDGE_MIB_DOT1DBASEPORT                      (1 << 0) 
#define BRIDGE_MIB_DOT1DBASEPORTIFINDEX               (1 << 1) 
#define BRIDGE_MIB_DOT1DBASEPORTCIRCUIT               (1 << 2) 
#define BRIDGE_MIB_DOT1DBASEPORTDELAYEXCEEDEDDISCARDS (1 << 3) 
#define BRIDGE_MIB_DOT1DBASEPORTMTUEXCEEDEDDISCARDS   (1 << 4) 

typedef struct {
    gint32   dot1dBasePort;                           /* ro */
    gint32   *dot1dBasePortIfIndex;                   /* ro IF-MIB::InterfaceIndex */
    guint32  *dot1dBasePortCircuit;                   /* ro ObjectIdentifier */
#define BRIDGE_MIB_DOT1DBASEPORTCIRCUITMINLENGTH 0
#define BRIDGE_MIB_DOT1DBASEPORTCIRCUITMAXLENGTH 128
    guint16  _dot1dBasePortCircuitLength;
    guint32  *dot1dBasePortDelayExceededDiscards;     /* ro SNMPv2-SMI::Counter32 */
    guint32  *dot1dBasePortMtuExceededDiscards;       /* ro SNMPv2-SMI::Counter32 */
} bridge_mib_dot1dBasePortEntry_t;

extern void
bridge_mib_get_dot1dBasePortTable(GNetSnmp *s, bridge_mib_dot1dBasePortEntry_t ***dot1dBasePortEntry, gint64 mask);

extern void
bridge_mib_free_dot1dBasePortTable(bridge_mib_dot1dBasePortEntry_t **dot1dBasePortEntry);

extern bridge_mib_dot1dBasePortEntry_t *
bridge_mib_new_dot1dBasePortEntry(void);

extern void
bridge_mib_get_dot1dBasePortEntry(GNetSnmp *s, bridge_mib_dot1dBasePortEntry_t **dot1dBasePortEntry, gint32 dot1dBasePort, gint64 mask);

extern void
bridge_mib_free_dot1dBasePortEntry(bridge_mib_dot1dBasePortEntry_t *dot1dBasePortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dStp.
 */

#define BRIDGE_MIB_DOT1DSTPPROTOCOLSPECIFICATION   (1 << 0) 
#define BRIDGE_MIB_DOT1DSTPPRIORITY                (1 << 1) 
#define BRIDGE_MIB_DOT1DSTPTIMESINCETOPOLOGYCHANGE (1 << 2) 
#define BRIDGE_MIB_DOT1DSTPTOPCHANGES              (1 << 3) 
#define BRIDGE_MIB_DOT1DSTPDESIGNATEDROOT          (1 << 4) 
#define BRIDGE_MIB_DOT1DSTPROOTCOST                (1 << 5) 
#define BRIDGE_MIB_DOT1DSTPROOTPORT                (1 << 6) 
#define BRIDGE_MIB_DOT1DSTPMAXAGE                  (1 << 7) 
#define BRIDGE_MIB_DOT1DSTPHELLOTIME               (1 << 8) 
#define BRIDGE_MIB_DOT1DSTPHOLDTIME                (1 << 9) 
#define BRIDGE_MIB_DOT1DSTPFORWARDDELAY            (1 << 10) 
#define BRIDGE_MIB_DOT1DSTPBRIDGEMAXAGE            (1 << 11) 
#define BRIDGE_MIB_DOT1DSTPBRIDGEHELLOTIME         (1 << 12) 
#define BRIDGE_MIB_DOT1DSTPBRIDGEFORWARDDELAY      (1 << 13) 

typedef struct {
    gint32   *dot1dStpProtocolSpecification;       /* ro */
    gint32   *dot1dStpPriority;                    /* rw */
    guint32  *dot1dStpTimeSinceTopologyChange;     /* ro SNMPv2-SMI::TimeTicks [centi-seconds] */
    guint32  *dot1dStpTopChanges;                  /* ro SNMPv2-SMI::Counter32 */
    guchar   *dot1dStpDesignatedRoot;              /* ro BRIDGE-MIB::BridgeId */
#define BRIDGE_MIB_DOT1DSTPDESIGNATEDROOTLENGTH 8
    gint32   *dot1dStpRootCost;                    /* ro Integer32 */
    gint32   *dot1dStpRootPort;                    /* ro Integer32 */
    gint32   *dot1dStpMaxAge;                      /* ro BRIDGE-MIB::Timeout [centi-seconds] */
    gint32   *dot1dStpHelloTime;                   /* ro BRIDGE-MIB::Timeout [centi-seconds] */
    gint32   *dot1dStpHoldTime;                    /* ro Integer32 [centi-seconds] */
    gint32   *dot1dStpForwardDelay;                /* ro BRIDGE-MIB::Timeout [centi-seconds] */
    gint32   *dot1dStpBridgeMaxAge;                /* rw [centi-seconds] */
    gint32   *dot1dStpBridgeHelloTime;             /* rw [centi-seconds] */
    gint32   *dot1dStpBridgeForwardDelay;          /* rw [centi-seconds] */
} bridge_mib_dot1dStp_t;

extern bridge_mib_dot1dStp_t *
bridge_mib_new_dot1dStp(void);

extern void
bridge_mib_get_dot1dStp(GNetSnmp *s, bridge_mib_dot1dStp_t **dot1dStp, gint64 mask);

extern void
bridge_mib_set_dot1dStp(GNetSnmp *s, bridge_mib_dot1dStp_t *dot1dStp, gint64 mask);

extern void
bridge_mib_free_dot1dStp(bridge_mib_dot1dStp_t *dot1dStp);

/*
 * C type definitions for BRIDGE-MIB::dot1dStpPortEntry.
 */

#define BRIDGE_MIB_DOT1DSTPPORT                   (1 << 0) 
#define BRIDGE_MIB_DOT1DSTPPORTPRIORITY           (1 << 1) 
#define BRIDGE_MIB_DOT1DSTPPORTSTATE              (1 << 2) 
#define BRIDGE_MIB_DOT1DSTPPORTENABLE             (1 << 3) 
#define BRIDGE_MIB_DOT1DSTPPORTPATHCOST           (1 << 4) 
#define BRIDGE_MIB_DOT1DSTPPORTDESIGNATEDROOT     (1 << 5) 
#define BRIDGE_MIB_DOT1DSTPPORTDESIGNATEDCOST     (1 << 6) 
#define BRIDGE_MIB_DOT1DSTPPORTDESIGNATEDBRIDGE   (1 << 7) 
#define BRIDGE_MIB_DOT1DSTPPORTDESIGNATEDPORT     (1 << 8) 
#define BRIDGE_MIB_DOT1DSTPPORTFORWARDTRANSITIONS (1 << 9) 
#define BRIDGE_MIB_DOT1DSTPPORTPATHCOST32         (1 << 10) 

typedef struct {
    gint32   dot1dStpPort;                        /* ro */
    gint32   *dot1dStpPortPriority;               /* rw */
    gint32   *dot1dStpPortState;                  /* ro */
    gint32   *dot1dStpPortEnable;                 /* rw */
    gint32   *dot1dStpPortPathCost;               /* rw */
    guchar   *dot1dStpPortDesignatedRoot;         /* ro BRIDGE-MIB::BridgeId */
#define BRIDGE_MIB_DOT1DSTPPORTDESIGNATEDROOTLENGTH 8
    gint32   *dot1dStpPortDesignatedCost;         /* ro Integer32 */
    guchar   *dot1dStpPortDesignatedBridge;       /* ro BRIDGE-MIB::BridgeId */
#define BRIDGE_MIB_DOT1DSTPPORTDESIGNATEDBRIDGELENGTH 8
    guchar   *dot1dStpPortDesignatedPort;         /* ro */
#define BRIDGE_MIB_DOT1DSTPPORTDESIGNATEDPORTLENGTH 2
    guint32  *dot1dStpPortForwardTransitions;     /* ro SNMPv2-SMI::Counter32 */
    gint32   *dot1dStpPortPathCost32;             /* rw */
} bridge_mib_dot1dStpPortEntry_t;

extern void
bridge_mib_get_dot1dStpPortTable(GNetSnmp *s, bridge_mib_dot1dStpPortEntry_t ***dot1dStpPortEntry, gint64 mask);

extern void
bridge_mib_free_dot1dStpPortTable(bridge_mib_dot1dStpPortEntry_t **dot1dStpPortEntry);

extern bridge_mib_dot1dStpPortEntry_t *
bridge_mib_new_dot1dStpPortEntry(void);

extern void
bridge_mib_get_dot1dStpPortEntry(GNetSnmp *s, bridge_mib_dot1dStpPortEntry_t **dot1dStpPortEntry, gint32 dot1dStpPort, gint64 mask);

extern void
bridge_mib_set_dot1dStpPortEntry(GNetSnmp *s, bridge_mib_dot1dStpPortEntry_t *dot1dStpPortEntry, gint64 mask);

extern void
bridge_mib_free_dot1dStpPortEntry(bridge_mib_dot1dStpPortEntry_t *dot1dStpPortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dTp.
 */

#define BRIDGE_MIB_DOT1DTPLEARNEDENTRYDISCARDS (1 << 0) 
#define BRIDGE_MIB_DOT1DTPAGINGTIME            (1 << 1) 

typedef struct {
    guint32  *dot1dTpLearnedEntryDiscards;     /* ro SNMPv2-SMI::Counter32 */
    gint32   *dot1dTpAgingTime;                /* rw [seconds] */
} bridge_mib_dot1dTp_t;

extern bridge_mib_dot1dTp_t *
bridge_mib_new_dot1dTp(void);

extern void
bridge_mib_get_dot1dTp(GNetSnmp *s, bridge_mib_dot1dTp_t **dot1dTp, gint64 mask);

extern void
bridge_mib_set_dot1dTp(GNetSnmp *s, bridge_mib_dot1dTp_t *dot1dTp, gint64 mask);

extern void
bridge_mib_free_dot1dTp(bridge_mib_dot1dTp_t *dot1dTp);

/*
 * C type definitions for BRIDGE-MIB::dot1dTpFdbEntry.
 */

#define BRIDGE_MIB_DOT1DTPFDBADDRESS (1 << 0) 
#define BRIDGE_MIB_DOT1DTPFDBPORT    (1 << 1) 
#define BRIDGE_MIB_DOT1DTPFDBSTATUS  (1 << 2) 

typedef struct {
    guchar   dot1dTpFdbAddress[6];  /* ro SNMPv2-TC::MacAddress */
#define BRIDGE_MIB_DOT1DTPFDBADDRESSLENGTH 6
    gint32   *dot1dTpFdbPort;        /* ro Integer32 */
    gint32   *dot1dTpFdbStatus;      /* ro */
} bridge_mib_dot1dTpFdbEntry_t;

extern void
bridge_mib_get_dot1dTpFdbTable(GNetSnmp *s, bridge_mib_dot1dTpFdbEntry_t ***dot1dTpFdbEntry, gint64 mask);

extern void
bridge_mib_free_dot1dTpFdbTable(bridge_mib_dot1dTpFdbEntry_t **dot1dTpFdbEntry);

extern bridge_mib_dot1dTpFdbEntry_t *
bridge_mib_new_dot1dTpFdbEntry(void);

extern void
bridge_mib_get_dot1dTpFdbEntry(GNetSnmp *s, bridge_mib_dot1dTpFdbEntry_t **dot1dTpFdbEntry, guchar *dot1dTpFdbAddress, gint64 mask);

extern void
bridge_mib_free_dot1dTpFdbEntry(bridge_mib_dot1dTpFdbEntry_t *dot1dTpFdbEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dTpPortEntry.
 */

#define BRIDGE_MIB_DOT1DTPPORT           (1 << 0) 
#define BRIDGE_MIB_DOT1DTPPORTMAXINFO    (1 << 1) 
#define BRIDGE_MIB_DOT1DTPPORTINFRAMES   (1 << 2) 
#define BRIDGE_MIB_DOT1DTPPORTOUTFRAMES  (1 << 3) 
#define BRIDGE_MIB_DOT1DTPPORTINDISCARDS (1 << 4) 

typedef struct {
    gint32   dot1dTpPort;                /* ro */
    gint32   *dot1dTpPortMaxInfo;        /* ro Integer32 [bytes] */
    guint32  *dot1dTpPortInFrames;       /* ro SNMPv2-SMI::Counter32 [frames] */
    guint32  *dot1dTpPortOutFrames;      /* ro SNMPv2-SMI::Counter32 [frames] */
    guint32  *dot1dTpPortInDiscards;     /* ro SNMPv2-SMI::Counter32 [frames] */
} bridge_mib_dot1dTpPortEntry_t;

extern void
bridge_mib_get_dot1dTpPortTable(GNetSnmp *s, bridge_mib_dot1dTpPortEntry_t ***dot1dTpPortEntry, gint64 mask);

extern void
bridge_mib_free_dot1dTpPortTable(bridge_mib_dot1dTpPortEntry_t **dot1dTpPortEntry);

extern bridge_mib_dot1dTpPortEntry_t *
bridge_mib_new_dot1dTpPortEntry(void);

extern void
bridge_mib_get_dot1dTpPortEntry(GNetSnmp *s, bridge_mib_dot1dTpPortEntry_t **dot1dTpPortEntry, gint32 dot1dTpPort, gint64 mask);

extern void
bridge_mib_free_dot1dTpPortEntry(bridge_mib_dot1dTpPortEntry_t *dot1dTpPortEntry);

/*
 * C type definitions for BRIDGE-MIB::dot1dStaticEntry.
 */

#define BRIDGE_MIB_DOT1DSTATICADDRESS       (1 << 0) 
#define BRIDGE_MIB_DOT1DSTATICRECEIVEPORT   (1 << 1) 
#define BRIDGE_MIB_DOT1DSTATICALLOWEDTOGOTO (1 << 2) 
#define BRIDGE_MIB_DOT1DSTATICSTATUS        (1 << 3) 

typedef struct {
    guchar   dot1dStaticAddress[6];        /* rw SNMPv2-TC::MacAddress */
#define BRIDGE_MIB_DOT1DSTATICADDRESSLENGTH 6
    gint32   dot1dStaticReceivePort;        /* rw */
    guchar   *dot1dStaticAllowedToGoTo;     /* rw */
#define BRIDGE_MIB_DOT1DSTATICALLOWEDTOGOTOMINLENGTH 0
#define BRIDGE_MIB_DOT1DSTATICALLOWEDTOGOTOMAXLENGTH 512
    guint16  _dot1dStaticAllowedToGoToLength;
    gint32   *dot1dStaticStatus;            /* rw */
} bridge_mib_dot1dStaticEntry_t;

extern void
bridge_mib_get_dot1dStaticTable(GNetSnmp *s, bridge_mib_dot1dStaticEntry_t ***dot1dStaticEntry, gint64 mask);

extern void
bridge_mib_free_dot1dStaticTable(bridge_mib_dot1dStaticEntry_t **dot1dStaticEntry);

extern bridge_mib_dot1dStaticEntry_t *
bridge_mib_new_dot1dStaticEntry(void);

extern void
bridge_mib_get_dot1dStaticEntry(GNetSnmp *s, bridge_mib_dot1dStaticEntry_t **dot1dStaticEntry, guchar *dot1dStaticAddress, gint32 dot1dStaticReceivePort, gint64 mask);

extern void
bridge_mib_set_dot1dStaticEntry(GNetSnmp *s, bridge_mib_dot1dStaticEntry_t *dot1dStaticEntry, gint64 mask);

extern void
bridge_mib_free_dot1dStaticEntry(bridge_mib_dot1dStaticEntry_t *dot1dStaticEntry);


G_END_DECLS

#endif /* _BRIDGE_MIB_H_ */
