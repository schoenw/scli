/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.16 for the stools package.
 *
 * Derived from EtherLike-MIB:
 *   The MIB module to describe generic objects for
 *   Ethernet-like network interfaces.
 *   
 *   The following reference is used throughout this
 *   MIB module:
 *   
 *   [IEEE 802.3 Std] refers to:
 *      IEEE Std 802.3, 1998 Edition: 'Information
 *      technology - Telecommunications and
 *      information exchange between systems -
 *      Local and metropolitan area networks -
 *      Specific requirements - Part 3: Carrier
 *      sense multiple access with collision
 *      detection (CSMA/CD) access method and
 *      physical layer specifications',
 *      September 1998.
 *   
 *   Of particular interest is Clause 30, '10Mb/s,
 *   100Mb/s and 1000Mb/s Management'.
 *
 * Revision 1999-08-24 04:00:
 *   Updated to include support for 1000 Mb/sec
 *   interfaces and full-duplex interfaces.
 *   This version published as RFC 2665.
 *
 * Revision 1998-06-03 21:50:
 *   Updated to include support for 100 Mb/sec
 *   interfaces.
 *   This version published as RFC 2358.
 *
 * Revision 1994-02-03 04:00:
 *   Initial version, published as RFC 1650.
 *
 * $Id$
 */

#ifndef _ETHERLIKE_MIB_H_
#define _ETHERLIKE_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_UNKNOWN	1
#define ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_HALFDUPLEX	2
#define ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_FULLDUPLEX	3

extern stls_enum_t const etherlike_mib_enums_dot3StatsDuplexStatus[];

#define ETHERLIKE_MIB_DOT3PAUSEADMINMODE_DISABLED	1
#define ETHERLIKE_MIB_DOT3PAUSEADMINMODE_ENABLEDXMIT	2
#define ETHERLIKE_MIB_DOT3PAUSEADMINMODE_ENABLEDRCV	3
#define ETHERLIKE_MIB_DOT3PAUSEADMINMODE_ENABLEDXMITANDRCV	4

extern stls_enum_t const etherlike_mib_enums_dot3PauseAdminMode[];

#define ETHERLIKE_MIB_DOT3PAUSEOPERMODE_DISABLED	1
#define ETHERLIKE_MIB_DOT3PAUSEOPERMODE_ENABLEDXMIT	2
#define ETHERLIKE_MIB_DOT3PAUSEOPERMODE_ENABLEDRCV	3
#define ETHERLIKE_MIB_DOT3PAUSEOPERMODE_ENABLEDXMITANDRCV	4

extern stls_enum_t const etherlike_mib_enums_dot3PauseOperMode[];


/*
 * Tables to map identities to strings and vice versa.
 */

#define ETHERLIKE_MIB_DOT3TESTTDR	1,3,6,1,2,1,10,7,6,1
#define ETHERLIKE_MIB_DOT3TESTLOOPBACK	1,3,6,1,2,1,10,7,6,2
#define ETHERLIKE_MIB_DOT3ERRORINITERROR	1,3,6,1,2,1,10,7,7,1
#define ETHERLIKE_MIB_DOT3ERRORLOOPBACKERROR	1,3,6,1,2,1,10,7,7,2

extern stls_identity_t const etherlike_mib_identities[];

/*
 * C type definitions for EtherLike-MIB::dot3StatsEntry.
 */

typedef struct {
    gint32   dot3StatsIndex;
    guint32  *dot3StatsAlignmentErrors;
    guint32  *dot3StatsFCSErrors;
    guint32  *dot3StatsSingleCollisionFrames;
    guint32  *dot3StatsMultipleCollisionFrames;
    guint32  *dot3StatsSQETestErrors;
    guint32  *dot3StatsDeferredTransmissions;
    guint32  *dot3StatsLateCollisions;
    guint32  *dot3StatsExcessiveCollisions;
    guint32  *dot3StatsInternalMacTransmitErrors;
    guint32  *dot3StatsCarrierSenseErrors;
    guint32  *dot3StatsFrameTooLongs;
    guint32  *dot3StatsInternalMacReceiveErrors;
    guint32  *dot3StatsEtherChipSet;
    gsize    _dot3StatsEtherChipSetLength;
    guint32  *dot3StatsSymbolErrors;
    gint32   *dot3StatsDuplexStatus;
} etherlike_mib_dot3StatsEntry_t;

extern int
etherlike_mib_get_dot3StatsTable(GSnmpSession *s, etherlike_mib_dot3StatsEntry_t ***dot3StatsEntry);

extern void
etherlike_mib_free_dot3StatsTable(etherlike_mib_dot3StatsEntry_t **dot3StatsEntry);

extern etherlike_mib_dot3StatsEntry_t *
etherlike_mib_new_dot3StatsEntry();

extern int
etherlike_mib_get_dot3StatsEntry(GSnmpSession *s, etherlike_mib_dot3StatsEntry_t **dot3StatsEntry);

extern void
etherlike_mib_free_dot3StatsEntry(etherlike_mib_dot3StatsEntry_t *dot3StatsEntry);

/*
 * C type definitions for EtherLike-MIB::dot3CollEntry.
 */

typedef struct {
    gint32   ifIndex;
    gint32   dot3CollCount;
    guint32  *dot3CollFrequencies;
} etherlike_mib_dot3CollEntry_t;

extern int
etherlike_mib_get_dot3CollTable(GSnmpSession *s, etherlike_mib_dot3CollEntry_t ***dot3CollEntry);

extern void
etherlike_mib_free_dot3CollTable(etherlike_mib_dot3CollEntry_t **dot3CollEntry);

extern etherlike_mib_dot3CollEntry_t *
etherlike_mib_new_dot3CollEntry();

extern int
etherlike_mib_get_dot3CollEntry(GSnmpSession *s, etherlike_mib_dot3CollEntry_t **dot3CollEntry);

extern void
etherlike_mib_free_dot3CollEntry(etherlike_mib_dot3CollEntry_t *dot3CollEntry);

/*
 * C type definitions for EtherLike-MIB::dot3ControlEntry.
 */

typedef struct {
    gint32   dot3StatsIndex;
    guchar   *dot3ControlFunctionsSupported;
    gsize    _dot3ControlFunctionsSupportedLength;
    guint32  *dot3ControlInUnknownOpcodes;
} etherlike_mib_dot3ControlEntry_t;

extern int
etherlike_mib_get_dot3ControlTable(GSnmpSession *s, etherlike_mib_dot3ControlEntry_t ***dot3ControlEntry);

extern void
etherlike_mib_free_dot3ControlTable(etherlike_mib_dot3ControlEntry_t **dot3ControlEntry);

extern etherlike_mib_dot3ControlEntry_t *
etherlike_mib_new_dot3ControlEntry();

extern int
etherlike_mib_get_dot3ControlEntry(GSnmpSession *s, etherlike_mib_dot3ControlEntry_t **dot3ControlEntry);

extern void
etherlike_mib_free_dot3ControlEntry(etherlike_mib_dot3ControlEntry_t *dot3ControlEntry);

/*
 * C type definitions for EtherLike-MIB::dot3PauseEntry.
 */

typedef struct {
    gint32   dot3StatsIndex;
    gint32   *dot3PauseAdminMode;
    gint32   *dot3PauseOperMode;
    guint32  *dot3InPauseFrames;
    guint32  *dot3OutPauseFrames;
} etherlike_mib_dot3PauseEntry_t;

extern int
etherlike_mib_get_dot3PauseTable(GSnmpSession *s, etherlike_mib_dot3PauseEntry_t ***dot3PauseEntry);

extern void
etherlike_mib_free_dot3PauseTable(etherlike_mib_dot3PauseEntry_t **dot3PauseEntry);

extern etherlike_mib_dot3PauseEntry_t *
etherlike_mib_new_dot3PauseEntry();

extern int
etherlike_mib_get_dot3PauseEntry(GSnmpSession *s, etherlike_mib_dot3PauseEntry_t **dot3PauseEntry);

extern int
etherlike_mib_set_dot3PauseEntry(GSnmpSession *s, etherlike_mib_dot3PauseEntry_t *dot3PauseEntry);

extern void
etherlike_mib_free_dot3PauseEntry(etherlike_mib_dot3PauseEntry_t *dot3PauseEntry);


#endif /* _ETHERLIKE_MIB_H_ */
