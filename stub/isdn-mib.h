/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Options:
 *   --scli-include='isdnBasicRateEntry|isdnBearerEntry|isdnEndpointEntry'
 *
 * Derived from ISDN-MIB:
 *   The MIB module to describe the
 *   management of ISDN interfaces.
 *
 * Revision 1996-09-23 16:42:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#ifndef _ISDN_MIB_H_
#define _ISDN_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define ISDN_MIB_ISDNBASICRATEIFTYPE_ISDNS 75
#define ISDN_MIB_ISDNBASICRATEIFTYPE_ISDNU 76

extern GSnmpEnum const isdn_mib_enums_isdnBasicRateIfType[];

#define ISDN_MIB_ISDNBASICRATELINETOPOLOGY_POINTTOPOINT      1
#define ISDN_MIB_ISDNBASICRATELINETOPOLOGY_POINTTOMULTIPOINT 2

extern GSnmpEnum const isdn_mib_enums_isdnBasicRateLineTopology[];

#define ISDN_MIB_ISDNBASICRATEIFMODE_TE 1
#define ISDN_MIB_ISDNBASICRATEIFMODE_NT 2

extern GSnmpEnum const isdn_mib_enums_isdnBasicRateIfMode[];

#define ISDN_MIB_ISDNBASICRATESIGNALMODE_ACTIVE   1
#define ISDN_MIB_ISDNBASICRATESIGNALMODE_INACTIVE 2

extern GSnmpEnum const isdn_mib_enums_isdnBasicRateSignalMode[];

#define ISDN_MIB_ISDNBEARERCHANNELTYPE_DIALUP 1
#define ISDN_MIB_ISDNBEARERCHANNELTYPE_LEASED 2

extern GSnmpEnum const isdn_mib_enums_isdnBearerChannelType[];

#define ISDN_MIB_ISDNBEAREROPERSTATUS_IDLE       1
#define ISDN_MIB_ISDNBEAREROPERSTATUS_CONNECTING 2
#define ISDN_MIB_ISDNBEAREROPERSTATUS_CONNECTED  3
#define ISDN_MIB_ISDNBEAREROPERSTATUS_ACTIVE     4

extern GSnmpEnum const isdn_mib_enums_isdnBearerOperStatus[];

#define ISDN_MIB_ISDNBEARERCALLORIGIN_UNKNOWN   1
#define ISDN_MIB_ISDNBEARERCALLORIGIN_ORIGINATE 2
#define ISDN_MIB_ISDNBEARERCALLORIGIN_ANSWER    3
#define ISDN_MIB_ISDNBEARERCALLORIGIN_CALLBACK  4

extern GSnmpEnum const isdn_mib_enums_isdnBearerCallOrigin[];

#define ISDN_MIB_ISDNBEARERINFOTYPE_UNKNOWN               1
#define ISDN_MIB_ISDNBEARERINFOTYPE_SPEECH                2
#define ISDN_MIB_ISDNBEARERINFOTYPE_UNRESTRICTEDDIGITAL   3
#define ISDN_MIB_ISDNBEARERINFOTYPE_UNRESTRICTEDDIGITAL56 4
#define ISDN_MIB_ISDNBEARERINFOTYPE_RESTRICTEDDIGITAL     5
#define ISDN_MIB_ISDNBEARERINFOTYPE_AUDIO31               6
#define ISDN_MIB_ISDNBEARERINFOTYPE_AUDIO7                7
#define ISDN_MIB_ISDNBEARERINFOTYPE_VIDEO                 8
#define ISDN_MIB_ISDNBEARERINFOTYPE_PACKETSWITCHED        9

extern GSnmpEnum const isdn_mib_enums_isdnBearerInfoType[];

#define ISDN_MIB_ISDNENDPOINTTEITYPE_DYNAMIC 1
#define ISDN_MIB_ISDNENDPOINTTEITYPE_STATIC  2

extern GSnmpEnum const isdn_mib_enums_isdnEndpointTeiType[];

#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_OTHER     1
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_DSS1      2
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_ETSI      3
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_DASS2     4
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_ESS4      5
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_ESS5      6
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_DMS100    7
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_DMS250    8
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_NI1       9
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_NI2       10
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_NI3       11
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN2       12
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN3       13
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN4       14
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN6       15
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_KDD       16
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_INS64     17
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_INS1500   18
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_ITR6      19
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_CORNET    20
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_TS013     21
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_TS014     22
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_QSIG      23
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_SWISSNET2 24
#define ISDN_MIB_ISDNSIGNALINGPROTOCOL_SWISSNET3 25

extern GSnmpEnum const isdn_mib_enums_IsdnSignalingProtocol[];


/*
 * C type definitions for ISDN-MIB::isdnBasicRateEntry.
 */

#define ISDN_MIB_ISDNBASICRATEIFTYPE       (1 << 0) 
#define ISDN_MIB_ISDNBASICRATELINETOPOLOGY (1 << 1) 
#define ISDN_MIB_ISDNBASICRATEIFMODE       (1 << 2) 
#define ISDN_MIB_ISDNBASICRATESIGNALMODE   (1 << 3) 

typedef struct {
    gint32   ifIndex;                        /* ro IF-MIB::InterfaceIndex */
    gint32   *isdnBasicRateIfType;           /* rw */
    gint32   *isdnBasicRateLineTopology;     /* rw */
    gint32   *isdnBasicRateIfMode;           /* rw */
    gint32   *isdnBasicRateSignalMode;       /* rw */
} isdn_mib_isdnBasicRateEntry_t;

extern void
isdn_mib_get_isdnBasicRateTable(GSnmpSession *s, isdn_mib_isdnBasicRateEntry_t ***isdnBasicRateEntry, gint64 mask);

extern void
isdn_mib_free_isdnBasicRateTable(isdn_mib_isdnBasicRateEntry_t **isdnBasicRateEntry);

extern isdn_mib_isdnBasicRateEntry_t *
isdn_mib_new_isdnBasicRateEntry(void);

extern void
isdn_mib_get_isdnBasicRateEntry(GSnmpSession *s, isdn_mib_isdnBasicRateEntry_t **isdnBasicRateEntry, gint32 ifIndex, gint64 mask);

extern void
isdn_mib_set_isdnBasicRateEntry(GSnmpSession *s, isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry, gint64 mask);

extern void
isdn_mib_free_isdnBasicRateEntry(isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry);

/*
 * C type definitions for ISDN-MIB::isdnBearerEntry.
 */

#define ISDN_MIB_ISDNBEARERCHANNELTYPE     (1 << 0) 
#define ISDN_MIB_ISDNBEAREROPERSTATUS      (1 << 1) 
#define ISDN_MIB_ISDNBEARERCHANNELNUMBER   (1 << 2) 
#define ISDN_MIB_ISDNBEARERPEERADDRESS     (1 << 3) 
#define ISDN_MIB_ISDNBEARERPEERSUBADDRESS  (1 << 4) 
#define ISDN_MIB_ISDNBEARERCALLORIGIN      (1 << 5) 
#define ISDN_MIB_ISDNBEARERINFOTYPE        (1 << 6) 
#define ISDN_MIB_ISDNBEARERMULTIRATE       (1 << 7) 
#define ISDN_MIB_ISDNBEARERCALLSETUPTIME   (1 << 8) 
#define ISDN_MIB_ISDNBEARERCALLCONNECTTIME (1 << 9) 
#define ISDN_MIB_ISDNBEARERCHARGEDUNITS    (1 << 10) 

typedef struct {
    gint32   ifIndex;                        /* ro IF-MIB::InterfaceIndex */
    gint32   *isdnBearerChannelType;         /* rw */
    gint32   *isdnBearerOperStatus;          /* ro */
    gint32   *isdnBearerChannelNumber;       /* ro */
    guchar   *isdnBearerPeerAddress;         /* ro SNMPv2-TC::DisplayString */
#define ISDN_MIB_ISDNBEARERPEERADDRESSMINLENGTH 0
#define ISDN_MIB_ISDNBEARERPEERADDRESSMAXLENGTH 255
    guint16  _isdnBearerPeerAddressLength;
    guchar   *isdnBearerPeerSubAddress;      /* ro SNMPv2-TC::DisplayString */
#define ISDN_MIB_ISDNBEARERPEERSUBADDRESSMINLENGTH 0
#define ISDN_MIB_ISDNBEARERPEERSUBADDRESSMAXLENGTH 255
    guint16  _isdnBearerPeerSubAddressLength;
    gint32   *isdnBearerCallOrigin;          /* ro */
    gint32   *isdnBearerInfoType;            /* ro */
    gint32   *isdnBearerMultirate;           /* ro SNMPv2-TC::TruthValue */
    guint32  *isdnBearerCallSetupTime;       /* ro SNMPv2-TC::TimeStamp */
    guint32  *isdnBearerCallConnectTime;     /* ro SNMPv2-TC::TimeStamp */
    guint32  *isdnBearerChargedUnits;        /* ro SNMPv2-SMI::Gauge32 */
} isdn_mib_isdnBearerEntry_t;

extern void
isdn_mib_get_isdnBearerTable(GSnmpSession *s, isdn_mib_isdnBearerEntry_t ***isdnBearerEntry, gint64 mask);

extern void
isdn_mib_free_isdnBearerTable(isdn_mib_isdnBearerEntry_t **isdnBearerEntry);

extern isdn_mib_isdnBearerEntry_t *
isdn_mib_new_isdnBearerEntry(void);

extern void
isdn_mib_get_isdnBearerEntry(GSnmpSession *s, isdn_mib_isdnBearerEntry_t **isdnBearerEntry, gint32 ifIndex, gint64 mask);

extern void
isdn_mib_set_isdnBearerEntry(GSnmpSession *s, isdn_mib_isdnBearerEntry_t *isdnBearerEntry, gint64 mask);

extern void
isdn_mib_free_isdnBearerEntry(isdn_mib_isdnBearerEntry_t *isdnBearerEntry);

/*
 * C type definitions for ISDN-MIB::isdnEndpointEntry.
 */

#define ISDN_MIB_ISDNENDPOINTIFINDEX  (1 << 0) 
#define ISDN_MIB_ISDNENDPOINTIFTYPE   (1 << 1) 
#define ISDN_MIB_ISDNENDPOINTTEITYPE  (1 << 2) 
#define ISDN_MIB_ISDNENDPOINTTEIVALUE (1 << 3) 
#define ISDN_MIB_ISDNENDPOINTSPID     (1 << 4) 
#define ISDN_MIB_ISDNENDPOINTSTATUS   (1 << 5) 

typedef struct {
    gint32   isdnEndpointIndex;         /* na */
    gint32   *isdnEndpointIfIndex;      /* ro IF-MIB::InterfaceIndex */
    gint32   *isdnEndpointIfType;       /* rw IANAifType-MIB::IANAifType */
    gint32   *isdnEndpointTeiType;      /* rw */
    gint32   *isdnEndpointTeiValue;     /* rw */
    guchar   *isdnEndpointSpid;         /* rw SNMPv2-TC::DisplayString */
#define ISDN_MIB_ISDNENDPOINTSPIDMINLENGTH 0
#define ISDN_MIB_ISDNENDPOINTSPIDMAXLENGTH 255
    guint16  _isdnEndpointSpidLength;
    gint32   *isdnEndpointStatus;       /* rw SNMPv2-TC::RowStatus */
} isdn_mib_isdnEndpointEntry_t;

extern void
isdn_mib_get_isdnEndpointTable(GSnmpSession *s, isdn_mib_isdnEndpointEntry_t ***isdnEndpointEntry, gint64 mask);

extern void
isdn_mib_free_isdnEndpointTable(isdn_mib_isdnEndpointEntry_t **isdnEndpointEntry);

extern isdn_mib_isdnEndpointEntry_t *
isdn_mib_new_isdnEndpointEntry(void);

extern void
isdn_mib_get_isdnEndpointEntry(GSnmpSession *s, isdn_mib_isdnEndpointEntry_t **isdnEndpointEntry, gint32 isdnEndpointIndex, gint64 mask);

extern void
isdn_mib_set_isdnEndpointEntry(GSnmpSession *s, isdn_mib_isdnEndpointEntry_t *isdnEndpointEntry, gint64 mask);

extern void
isdn_mib_free_isdnEndpointEntry(isdn_mib_isdnEndpointEntry_t *isdnEndpointEntry);


G_END_DECLS

#endif /* _ISDN_MIB_H_ */
