/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from MAU-MIB:
 *   Management information for 802.3 MAUs.
 *   
 *   The following reference is used throughout
 *   this MIB module:
 *   
 *   [IEEE 802.3 Std] refers to
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
 *   This version published as RFC 2668. Updated
 *   to include support for 1000 Mb/sec
 *   MAUs and flow control negotiation.
 *
 * Revision 1997-10-31 00:00:
 *   This version published as RFC 2239.
 *
 * Revision 1993-09-30 00:00:
 *   Initial version, published as RFC 1515.
 *
 * $Id$
 */

#ifndef _MAU_MIB_H_
#define _MAU_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define MAU_MIB_RPMAUSTATUS_OTHER	1
#define MAU_MIB_RPMAUSTATUS_UNKNOWN	2
#define MAU_MIB_RPMAUSTATUS_OPERATIONAL	3
#define MAU_MIB_RPMAUSTATUS_STANDBY	4
#define MAU_MIB_RPMAUSTATUS_SHUTDOWN	5
#define MAU_MIB_RPMAUSTATUS_RESET	6

extern stls_enum_t const mau_mib_enums_rpMauStatus[];

#define MAU_MIB_RPMAUMEDIAAVAILABLE_OTHER	1
#define MAU_MIB_RPMAUMEDIAAVAILABLE_UNKNOWN	2
#define MAU_MIB_RPMAUMEDIAAVAILABLE_AVAILABLE	3
#define MAU_MIB_RPMAUMEDIAAVAILABLE_NOTAVAILABLE	4
#define MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTEFAULT	5
#define MAU_MIB_RPMAUMEDIAAVAILABLE_INVALIDSIGNAL	6
#define MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTEJABBER	7
#define MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTELINKLOSS	8
#define MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTETEST	9
#define MAU_MIB_RPMAUMEDIAAVAILABLE_OFFLINE	10
#define MAU_MIB_RPMAUMEDIAAVAILABLE_AUTONEGERROR	11

extern stls_enum_t const mau_mib_enums_rpMauMediaAvailable[];

#define MAU_MIB_RPMAUJABBERSTATE_OTHER	1
#define MAU_MIB_RPMAUJABBERSTATE_UNKNOWN	2
#define MAU_MIB_RPMAUJABBERSTATE_NOJABBER	3
#define MAU_MIB_RPMAUJABBERSTATE_JABBERING	4

extern stls_enum_t const mau_mib_enums_rpMauJabberState[];

#define MAU_MIB_RPJACKTYPE_OTHER	1
#define MAU_MIB_RPJACKTYPE_RJ45	2
#define MAU_MIB_RPJACKTYPE_RJ45S	3
#define MAU_MIB_RPJACKTYPE_DB9	4
#define MAU_MIB_RPJACKTYPE_BNC	5
#define MAU_MIB_RPJACKTYPE_FAUI	6
#define MAU_MIB_RPJACKTYPE_MAUI	7
#define MAU_MIB_RPJACKTYPE_FIBERSC	8
#define MAU_MIB_RPJACKTYPE_FIBERMIC	9
#define MAU_MIB_RPJACKTYPE_FIBERST	10
#define MAU_MIB_RPJACKTYPE_TELCO	11
#define MAU_MIB_RPJACKTYPE_MTRJ	12
#define MAU_MIB_RPJACKTYPE_HSSDC	13

extern stls_enum_t const mau_mib_enums_rpJackType[];

#define MAU_MIB_IFMAUSTATUS_OTHER	1
#define MAU_MIB_IFMAUSTATUS_UNKNOWN	2
#define MAU_MIB_IFMAUSTATUS_OPERATIONAL	3
#define MAU_MIB_IFMAUSTATUS_STANDBY	4
#define MAU_MIB_IFMAUSTATUS_SHUTDOWN	5
#define MAU_MIB_IFMAUSTATUS_RESET	6

extern stls_enum_t const mau_mib_enums_ifMauStatus[];

#define MAU_MIB_IFMAUMEDIAAVAILABLE_OTHER	1
#define MAU_MIB_IFMAUMEDIAAVAILABLE_UNKNOWN	2
#define MAU_MIB_IFMAUMEDIAAVAILABLE_AVAILABLE	3
#define MAU_MIB_IFMAUMEDIAAVAILABLE_NOTAVAILABLE	4
#define MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTEFAULT	5
#define MAU_MIB_IFMAUMEDIAAVAILABLE_INVALIDSIGNAL	6
#define MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTEJABBER	7
#define MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTELINKLOSS	8
#define MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTETEST	9
#define MAU_MIB_IFMAUMEDIAAVAILABLE_OFFLINE	10
#define MAU_MIB_IFMAUMEDIAAVAILABLE_AUTONEGERROR	11

extern stls_enum_t const mau_mib_enums_ifMauMediaAvailable[];

#define MAU_MIB_IFMAUJABBERSTATE_OTHER	1
#define MAU_MIB_IFMAUJABBERSTATE_UNKNOWN	2
#define MAU_MIB_IFMAUJABBERSTATE_NOJABBER	3
#define MAU_MIB_IFMAUJABBERSTATE_JABBERING	4

extern stls_enum_t const mau_mib_enums_ifMauJabberState[];

#define MAU_MIB_IFMAUAUTONEGSUPPORTED_TRUE	1
#define MAU_MIB_IFMAUAUTONEGSUPPORTED_FALSE	2

extern stls_enum_t const mau_mib_enums_ifMauAutoNegSupported[];

#define MAU_MIB_IFJACKTYPE_OTHER	1
#define MAU_MIB_IFJACKTYPE_RJ45	2
#define MAU_MIB_IFJACKTYPE_RJ45S	3
#define MAU_MIB_IFJACKTYPE_DB9	4
#define MAU_MIB_IFJACKTYPE_BNC	5
#define MAU_MIB_IFJACKTYPE_FAUI	6
#define MAU_MIB_IFJACKTYPE_MAUI	7
#define MAU_MIB_IFJACKTYPE_FIBERSC	8
#define MAU_MIB_IFJACKTYPE_FIBERMIC	9
#define MAU_MIB_IFJACKTYPE_FIBERST	10
#define MAU_MIB_IFJACKTYPE_TELCO	11
#define MAU_MIB_IFJACKTYPE_MTRJ	12
#define MAU_MIB_IFJACKTYPE_HSSDC	13

extern stls_enum_t const mau_mib_enums_ifJackType[];

#define MAU_MIB_BROADMAUXMTRCVSPLITTYPE_OTHER	1
#define MAU_MIB_BROADMAUXMTRCVSPLITTYPE_SINGLE	2
#define MAU_MIB_BROADMAUXMTRCVSPLITTYPE_DUAL	3

extern stls_enum_t const mau_mib_enums_broadMauXmtRcvSplitType[];

#define MAU_MIB_IFMAUAUTONEGADMINSTATUS_ENABLED	1
#define MAU_MIB_IFMAUAUTONEGADMINSTATUS_DISABLED	2

extern stls_enum_t const mau_mib_enums_ifMauAutoNegAdminStatus[];

#define MAU_MIB_IFMAUAUTONEGREMOTESIGNALING_DETECTED	1
#define MAU_MIB_IFMAUAUTONEGREMOTESIGNALING_NOTDETECTED	2

extern stls_enum_t const mau_mib_enums_ifMauAutoNegRemoteSignaling[];

#define MAU_MIB_IFMAUAUTONEGCONFIG_OTHER	1
#define MAU_MIB_IFMAUAUTONEGCONFIG_CONFIGURING	2
#define MAU_MIB_IFMAUAUTONEGCONFIG_COMPLETE	3
#define MAU_MIB_IFMAUAUTONEGCONFIG_DISABLED	4
#define MAU_MIB_IFMAUAUTONEGCONFIG_PARALLELDETECTFAIL	5

extern stls_enum_t const mau_mib_enums_ifMauAutoNegConfig[];

#define MAU_MIB_IFMAUAUTONEGRESTART_RESTART	1
#define MAU_MIB_IFMAUAUTONEGRESTART_NORESTART	2

extern stls_enum_t const mau_mib_enums_ifMauAutoNegRestart[];

#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_NOERROR	1
#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_OFFLINE	2
#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_LINKFAILURE	3
#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_AUTONEGERROR	4

extern stls_enum_t const mau_mib_enums_ifMauAutoNegRemoteFaultAdvertised[];

#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_NOERROR	1
#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_OFFLINE	2
#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_LINKFAILURE	3
#define MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_AUTONEGERROR	4

extern stls_enum_t const mau_mib_enums_ifMauAutoNegRemoteFaultReceived[];


/*
 * Tables to map identities to strings and vice versa.
 */

#define MAU_MIB_DOT3MAUTYPEAUI	1,3,6,1,2,1,26,4,1
#define MAU_MIB_DOT3MAUTYPE10BASE5	1,3,6,1,2,1,26,4,2
#define MAU_MIB_DOT3MAUTYPEFOIRL	1,3,6,1,2,1,26,4,3
#define MAU_MIB_DOT3MAUTYPE10BASE2	1,3,6,1,2,1,26,4,4
#define MAU_MIB_DOT3MAUTYPE10BASET	1,3,6,1,2,1,26,4,5
#define MAU_MIB_DOT3MAUTYPE10BASEFP	1,3,6,1,2,1,26,4,6
#define MAU_MIB_DOT3MAUTYPE10BASEFB	1,3,6,1,2,1,26,4,7
#define MAU_MIB_DOT3MAUTYPE10BASEFL	1,3,6,1,2,1,26,4,8
#define MAU_MIB_DOT3MAUTYPE10BROAD36	1,3,6,1,2,1,26,4,9
#define MAU_MIB_DOT3MAUTYPE10BASETHD	1,3,6,1,2,1,26,4,10
#define MAU_MIB_DOT3MAUTYPE10BASETFD	1,3,6,1,2,1,26,4,11
#define MAU_MIB_DOT3MAUTYPE10BASEFLHD	1,3,6,1,2,1,26,4,12
#define MAU_MIB_DOT3MAUTYPE10BASEFLFD	1,3,6,1,2,1,26,4,13
#define MAU_MIB_DOT3MAUTYPE100BASET4	1,3,6,1,2,1,26,4,14
#define MAU_MIB_DOT3MAUTYPE100BASETXHD	1,3,6,1,2,1,26,4,15
#define MAU_MIB_DOT3MAUTYPE100BASETXFD	1,3,6,1,2,1,26,4,16
#define MAU_MIB_DOT3MAUTYPE100BASEFXHD	1,3,6,1,2,1,26,4,17
#define MAU_MIB_DOT3MAUTYPE100BASEFXFD	1,3,6,1,2,1,26,4,18
#define MAU_MIB_DOT3MAUTYPE100BASET2HD	1,3,6,1,2,1,26,4,19
#define MAU_MIB_DOT3MAUTYPE100BASET2FD	1,3,6,1,2,1,26,4,20
#define MAU_MIB_DOT3MAUTYPE1000BASEXHD	1,3,6,1,2,1,26,4,21
#define MAU_MIB_DOT3MAUTYPE1000BASEXFD	1,3,6,1,2,1,26,4,22
#define MAU_MIB_DOT3MAUTYPE1000BASELXHD	1,3,6,1,2,1,26,4,23
#define MAU_MIB_DOT3MAUTYPE1000BASELXFD	1,3,6,1,2,1,26,4,24
#define MAU_MIB_DOT3MAUTYPE1000BASESXHD	1,3,6,1,2,1,26,4,25
#define MAU_MIB_DOT3MAUTYPE1000BASESXFD	1,3,6,1,2,1,26,4,26
#define MAU_MIB_DOT3MAUTYPE1000BASECXHD	1,3,6,1,2,1,26,4,27
#define MAU_MIB_DOT3MAUTYPE1000BASECXFD	1,3,6,1,2,1,26,4,28
#define MAU_MIB_DOT3MAUTYPE1000BASETHD	1,3,6,1,2,1,26,4,29
#define MAU_MIB_DOT3MAUTYPE1000BASETFD	1,3,6,1,2,1,26,4,30

/*
 * C type definitions for MAU-MIB::rpMauEntry.
 */

typedef struct rpMauEntry {
    gint32   rpMauGroupIndex;
    gint32   rpMauPortIndex;
    gint32   rpMauIndex;
    guint32  *rpMauType;
    gsize    _rpMauTypeLength;
    gint32   *rpMauStatus;
    gint32   *rpMauMediaAvailable;
    guint32  *rpMauMediaAvailableStateExits;
    gint32   *rpMauJabberState;
    guint32  *rpMauJabberingStateEnters;
    guint32  *rpMauFalseCarriers;
} rpMauEntry_t;

extern int
mau_mib_get_rpMauTable(host_snmp *s, rpMauEntry_t ***rpMauEntry);

extern void
mau_mib_free_rpMauTable(rpMauEntry_t **rpMauEntry);

extern rpMauEntry_t *
mau_mib_new_rpMauEntry();

extern int
mau_mib_get_rpMauEntry(host_snmp *s, rpMauEntry_t **rpMauEntry);

extern int
mau_mib_set_rpMauEntry(host_snmp *s, rpMauEntry_t *rpMauEntry);

extern void
mau_mib_free_rpMauEntry(rpMauEntry_t *rpMauEntry);

/*
 * C type definitions for MAU-MIB::rpJackEntry.
 */

typedef struct rpJackEntry {
    gint32   rpMauGroupIndex;
    gint32   rpMauPortIndex;
    gint32   rpMauIndex;
    gint32   rpJackIndex;
    gint32   *rpJackType;
} rpJackEntry_t;

extern int
mau_mib_get_rpJackTable(host_snmp *s, rpJackEntry_t ***rpJackEntry);

extern void
mau_mib_free_rpJackTable(rpJackEntry_t **rpJackEntry);

extern rpJackEntry_t *
mau_mib_new_rpJackEntry();

extern int
mau_mib_get_rpJackEntry(host_snmp *s, rpJackEntry_t **rpJackEntry);

extern void
mau_mib_free_rpJackEntry(rpJackEntry_t *rpJackEntry);

/*
 * C type definitions for MAU-MIB::ifMauEntry.
 */

typedef struct ifMauEntry {
    gint32   ifMauIfIndex;
    gint32   ifMauIndex;
    guint32  *ifMauType;
    gsize    _ifMauTypeLength;
    gint32   *ifMauStatus;
    gint32   *ifMauMediaAvailable;
    guint32  *ifMauMediaAvailableStateExits;
    gint32   *ifMauJabberState;
    guint32  *ifMauJabberingStateEnters;
    guint32  *ifMauFalseCarriers;
    gint32   *ifMauTypeList;
    guint32  *ifMauDefaultType;
    gsize    _ifMauDefaultTypeLength;
    gint32   *ifMauAutoNegSupported;
    guchar   *ifMauTypeListBits;
    gsize    _ifMauTypeListBitsLength;
} ifMauEntry_t;

extern int
mau_mib_get_ifMauTable(host_snmp *s, ifMauEntry_t ***ifMauEntry);

extern void
mau_mib_free_ifMauTable(ifMauEntry_t **ifMauEntry);

extern ifMauEntry_t *
mau_mib_new_ifMauEntry();

extern int
mau_mib_get_ifMauEntry(host_snmp *s, ifMauEntry_t **ifMauEntry);

extern int
mau_mib_set_ifMauEntry(host_snmp *s, ifMauEntry_t *ifMauEntry);

extern void
mau_mib_free_ifMauEntry(ifMauEntry_t *ifMauEntry);

/*
 * C type definitions for MAU-MIB::ifJackEntry.
 */

typedef struct ifJackEntry {
    gint32   ifMauIfIndex;
    gint32   ifMauIndex;
    gint32   ifJackIndex;
    gint32   *ifJackType;
} ifJackEntry_t;

extern int
mau_mib_get_ifJackTable(host_snmp *s, ifJackEntry_t ***ifJackEntry);

extern void
mau_mib_free_ifJackTable(ifJackEntry_t **ifJackEntry);

extern ifJackEntry_t *
mau_mib_new_ifJackEntry();

extern int
mau_mib_get_ifJackEntry(host_snmp *s, ifJackEntry_t **ifJackEntry);

extern void
mau_mib_free_ifJackEntry(ifJackEntry_t *ifJackEntry);

/*
 * C type definitions for MAU-MIB::broadMauBasicEntry.
 */

typedef struct broadMauBasicEntry {
    gint32   broadMauIfIndex;
    gint32   broadMauIndex;
    gint32   *broadMauXmtRcvSplitType;
    gint32   *broadMauXmtCarrierFreq;
    gint32   *broadMauTranslationFreq;
} broadMauBasicEntry_t;

extern int
mau_mib_get_broadMauBasicTable(host_snmp *s, broadMauBasicEntry_t ***broadMauBasicEntry);

extern void
mau_mib_free_broadMauBasicTable(broadMauBasicEntry_t **broadMauBasicEntry);

extern broadMauBasicEntry_t *
mau_mib_new_broadMauBasicEntry();

extern int
mau_mib_get_broadMauBasicEntry(host_snmp *s, broadMauBasicEntry_t **broadMauBasicEntry);

extern void
mau_mib_free_broadMauBasicEntry(broadMauBasicEntry_t *broadMauBasicEntry);

/*
 * C type definitions for MAU-MIB::ifMauAutoNegEntry.
 */

typedef struct ifMauAutoNegEntry {
    gint32   ifMauIfIndex;
    gint32   ifMauIndex;
    gint32   *ifMauAutoNegAdminStatus;
    gint32   *ifMauAutoNegRemoteSignaling;
    gint32   *ifMauAutoNegConfig;
    gint32   *ifMauAutoNegCapability;
    gint32   *ifMauAutoNegCapAdvertised;
    gint32   *ifMauAutoNegCapReceived;
    gint32   *ifMauAutoNegRestart;
    guchar   *ifMauAutoNegCapabilityBits;
    gsize    _ifMauAutoNegCapabilityBitsLength;
    guchar   *ifMauAutoNegCapAdvertisedBits;
    gsize    _ifMauAutoNegCapAdvertisedBitsLength;
    guchar   *ifMauAutoNegCapReceivedBits;
    gsize    _ifMauAutoNegCapReceivedBitsLength;
    gint32   *ifMauAutoNegRemoteFaultAdvertised;
    gint32   *ifMauAutoNegRemoteFaultReceived;
} ifMauAutoNegEntry_t;

extern int
mau_mib_get_ifMauAutoNegTable(host_snmp *s, ifMauAutoNegEntry_t ***ifMauAutoNegEntry);

extern void
mau_mib_free_ifMauAutoNegTable(ifMauAutoNegEntry_t **ifMauAutoNegEntry);

extern ifMauAutoNegEntry_t *
mau_mib_new_ifMauAutoNegEntry();

extern int
mau_mib_get_ifMauAutoNegEntry(host_snmp *s, ifMauAutoNegEntry_t **ifMauAutoNegEntry);

extern int
mau_mib_set_ifMauAutoNegEntry(host_snmp *s, ifMauAutoNegEntry_t *ifMauAutoNegEntry);

extern void
mau_mib_free_ifMauAutoNegEntry(ifMauAutoNegEntry_t *ifMauAutoNegEntry);


#endif /* _MAU_MIB_H_ */