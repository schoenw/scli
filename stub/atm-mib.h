/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from ATM-MIB:
 *   This is the MIB Module for ATM and AAL5-related
 *   objects for managing ATM interfaces, ATM virtual
 *   links, ATM cross-connects, AAL5 entities, and
 *   and AAL5 connections.
 *
 * Revision 1998-10-19 12:00:
 *   The initial revision of this module was published
 *   as RFC 1695. Key revisions include:
 *   o  Textual Conventions and OBJECT IDENTITIES have
 *      been moved to a separate MIB module.
 *   o  Applicability of objects to PVCs, SVCs and Soft
 *      PVCs has been clarified.
 *   o  DEFVAL clauses have been added.
 *   o  The relationship of ifIndex values with different
 *      layers and sublayers related to ATM has been
 *      clarified.
 *   o  atmTrafficQosClass has been deprecated
 *      and replaced with atmServiceCategory.
 *   o  atmInterfaceCurrentMaxVpiBits and
 *      atmInterfaceCurrentMaxVciBits have been added with
 *      a description on their relationship with other
 *      objects.
 *   o  atmInterfaceAddressType and atmInterfaceAdminAddress
 *      have been deprecated and replaced by
 *      atmInterfaceSubscrAddress.
 *   o  atmInterfaceTCAlarmState has been clarified.
 *   o  atmTrafficDescrParamIndexNext has been introduced
 *      in order to provide a manager a free
 *      atmTrafficDescrParamIndex value.
 *   o  The atmTrafficFrameDiscard capability has been added.
 *   o  A connection topology type (atmVpl/VclCastType) and
 *      a call control type (atmVpl/VclConnKind) have been
 *      added.
 *   o  aal2 has been added to atmVccAalType.
 *
 * Revision 1994-06-07 22:45:
 *   The RFC1695 version of this MIB module.
 *
 * $Id$
 */

#ifndef _ATM_MIB_H_
#define _ATM_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define ATM_MIB_ATMINTERFACEADDRESSTYPE_PRIVATE	1
#define ATM_MIB_ATMINTERFACEADDRESSTYPE_NSAPE164	2
#define ATM_MIB_ATMINTERFACEADDRESSTYPE_NATIVEE164	3
#define ATM_MIB_ATMINTERFACEADDRESSTYPE_OTHER	4

extern GSnmpEnum const atm_mib_enums_atmInterfaceAddressType[];

#define ATM_MIB_ATMINTERFACEDS3PLCPALARMSTATE_NOALARM	1
#define ATM_MIB_ATMINTERFACEDS3PLCPALARMSTATE_RECEIVEDFARENDALARM	2
#define ATM_MIB_ATMINTERFACEDS3PLCPALARMSTATE_INCOMINGLOF	3

extern GSnmpEnum const atm_mib_enums_atmInterfaceDs3PlcpAlarmState[];

#define ATM_MIB_ATMINTERFACETCALARMSTATE_NOALARM	1
#define ATM_MIB_ATMINTERFACETCALARMSTATE_LCDFAILURE	2

extern GSnmpEnum const atm_mib_enums_atmInterfaceTCAlarmState[];

#define ATM_MIB_ATMTRAFFICDESCRROWSTATUS_ACTIVE	1
#define ATM_MIB_ATMTRAFFICDESCRROWSTATUS_NOTINSERVICE	2
#define ATM_MIB_ATMTRAFFICDESCRROWSTATUS_NOTREADY	3
#define ATM_MIB_ATMTRAFFICDESCRROWSTATUS_CREATEANDGO	4
#define ATM_MIB_ATMTRAFFICDESCRROWSTATUS_CREATEANDWAIT	5
#define ATM_MIB_ATMTRAFFICDESCRROWSTATUS_DESTROY	6

extern GSnmpEnum const atm_mib_enums_atmTrafficDescrRowStatus[];

#define ATM_MIB_ATMSERVICECATEGORY_OTHER	1
#define ATM_MIB_ATMSERVICECATEGORY_CBR	2
#define ATM_MIB_ATMSERVICECATEGORY_RTVBR	3
#define ATM_MIB_ATMSERVICECATEGORY_NRTVBR	4
#define ATM_MIB_ATMSERVICECATEGORY_ABR	5
#define ATM_MIB_ATMSERVICECATEGORY_UBR	6

extern GSnmpEnum const atm_mib_enums_atmServiceCategory[];

#define ATM_MIB_ATMTRAFFICFRAMEDISCARD_TRUE	1
#define ATM_MIB_ATMTRAFFICFRAMEDISCARD_FALSE	2

extern GSnmpEnum const atm_mib_enums_atmTrafficFrameDiscard[];

#define ATM_MIB_ATMVPLADMINSTATUS_UP	1
#define ATM_MIB_ATMVPLADMINSTATUS_DOWN	2

extern GSnmpEnum const atm_mib_enums_atmVplAdminStatus[];

#define ATM_MIB_ATMVPLOPERSTATUS_UP	1
#define ATM_MIB_ATMVPLOPERSTATUS_DOWN	2
#define ATM_MIB_ATMVPLOPERSTATUS_UNKNOWN	3

extern GSnmpEnum const atm_mib_enums_atmVplOperStatus[];

#define ATM_MIB_ATMVPLROWSTATUS_ACTIVE	1
#define ATM_MIB_ATMVPLROWSTATUS_NOTINSERVICE	2
#define ATM_MIB_ATMVPLROWSTATUS_NOTREADY	3
#define ATM_MIB_ATMVPLROWSTATUS_CREATEANDGO	4
#define ATM_MIB_ATMVPLROWSTATUS_CREATEANDWAIT	5
#define ATM_MIB_ATMVPLROWSTATUS_DESTROY	6

extern GSnmpEnum const atm_mib_enums_atmVplRowStatus[];

#define ATM_MIB_ATMVPLCASTTYPE_P2P	1
#define ATM_MIB_ATMVPLCASTTYPE_P2MPROOT	2
#define ATM_MIB_ATMVPLCASTTYPE_P2MPLEAF	3

extern GSnmpEnum const atm_mib_enums_atmVplCastType[];

#define ATM_MIB_ATMVPLCONNKIND_PVC	1
#define ATM_MIB_ATMVPLCONNKIND_SVCINCOMING	2
#define ATM_MIB_ATMVPLCONNKIND_SVCOUTGOING	3
#define ATM_MIB_ATMVPLCONNKIND_SPVCINITIATOR	4
#define ATM_MIB_ATMVPLCONNKIND_SPVCTARGET	5

extern GSnmpEnum const atm_mib_enums_atmVplConnKind[];

#define ATM_MIB_ATMVCLADMINSTATUS_UP	1
#define ATM_MIB_ATMVCLADMINSTATUS_DOWN	2

extern GSnmpEnum const atm_mib_enums_atmVclAdminStatus[];

#define ATM_MIB_ATMVCLOPERSTATUS_UP	1
#define ATM_MIB_ATMVCLOPERSTATUS_DOWN	2
#define ATM_MIB_ATMVCLOPERSTATUS_UNKNOWN	3

extern GSnmpEnum const atm_mib_enums_atmVclOperStatus[];

#define ATM_MIB_ATMVCCAALTYPE_AAL1	1
#define ATM_MIB_ATMVCCAALTYPE_AAL34	2
#define ATM_MIB_ATMVCCAALTYPE_AAL5	3
#define ATM_MIB_ATMVCCAALTYPE_OTHER	4
#define ATM_MIB_ATMVCCAALTYPE_UNKNOWN	5
#define ATM_MIB_ATMVCCAALTYPE_AAL2	6

extern GSnmpEnum const atm_mib_enums_atmVccAalType[];

#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_VCMULTIPLEXROUTEDPROTOCOL	1
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_VCMULTIPLEXBRIDGEDPROTOCOL8023	2
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_VCMULTIPLEXBRIDGEDPROTOCOL8025	3
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_VCMULTIPLEXBRIDGEDPROTOCOL8026	4
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_VCMULTIPLEXLANEMULATION8023	5
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_VCMULTIPLEXLANEMULATION8025	6
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_LLCENCAPSULATION	7
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_MULTIPROTOCOLFRAMERELAYSSCS	8
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_OTHER	9
#define ATM_MIB_ATMVCCAAL5ENCAPSTYPE_UNKNOWN	10

extern GSnmpEnum const atm_mib_enums_atmVccAal5EncapsType[];

#define ATM_MIB_ATMVCLROWSTATUS_ACTIVE	1
#define ATM_MIB_ATMVCLROWSTATUS_NOTINSERVICE	2
#define ATM_MIB_ATMVCLROWSTATUS_NOTREADY	3
#define ATM_MIB_ATMVCLROWSTATUS_CREATEANDGO	4
#define ATM_MIB_ATMVCLROWSTATUS_CREATEANDWAIT	5
#define ATM_MIB_ATMVCLROWSTATUS_DESTROY	6

extern GSnmpEnum const atm_mib_enums_atmVclRowStatus[];

#define ATM_MIB_ATMVCLCASTTYPE_P2P	1
#define ATM_MIB_ATMVCLCASTTYPE_P2MPROOT	2
#define ATM_MIB_ATMVCLCASTTYPE_P2MPLEAF	3

extern GSnmpEnum const atm_mib_enums_atmVclCastType[];

#define ATM_MIB_ATMVCLCONNKIND_PVC	1
#define ATM_MIB_ATMVCLCONNKIND_SVCINCOMING	2
#define ATM_MIB_ATMVCLCONNKIND_SVCOUTGOING	3
#define ATM_MIB_ATMVCLCONNKIND_SPVCINITIATOR	4
#define ATM_MIB_ATMVCLCONNKIND_SPVCTARGET	5

extern GSnmpEnum const atm_mib_enums_atmVclConnKind[];

#define ATM_MIB_ATMVPCROSSCONNECTADMINSTATUS_UP	1
#define ATM_MIB_ATMVPCROSSCONNECTADMINSTATUS_DOWN	2

extern GSnmpEnum const atm_mib_enums_atmVpCrossConnectAdminStatus[];

#define ATM_MIB_ATMVPCROSSCONNECTL2HOPERSTATUS_UP	1
#define ATM_MIB_ATMVPCROSSCONNECTL2HOPERSTATUS_DOWN	2
#define ATM_MIB_ATMVPCROSSCONNECTL2HOPERSTATUS_UNKNOWN	3

extern GSnmpEnum const atm_mib_enums_atmVpCrossConnectL2HOperStatus[];

#define ATM_MIB_ATMVPCROSSCONNECTH2LOPERSTATUS_UP	1
#define ATM_MIB_ATMVPCROSSCONNECTH2LOPERSTATUS_DOWN	2
#define ATM_MIB_ATMVPCROSSCONNECTH2LOPERSTATUS_UNKNOWN	3

extern GSnmpEnum const atm_mib_enums_atmVpCrossConnectH2LOperStatus[];

#define ATM_MIB_ATMVPCROSSCONNECTROWSTATUS_ACTIVE	1
#define ATM_MIB_ATMVPCROSSCONNECTROWSTATUS_NOTINSERVICE	2
#define ATM_MIB_ATMVPCROSSCONNECTROWSTATUS_NOTREADY	3
#define ATM_MIB_ATMVPCROSSCONNECTROWSTATUS_CREATEANDGO	4
#define ATM_MIB_ATMVPCROSSCONNECTROWSTATUS_CREATEANDWAIT	5
#define ATM_MIB_ATMVPCROSSCONNECTROWSTATUS_DESTROY	6

extern GSnmpEnum const atm_mib_enums_atmVpCrossConnectRowStatus[];

#define ATM_MIB_ATMVCCROSSCONNECTADMINSTATUS_UP	1
#define ATM_MIB_ATMVCCROSSCONNECTADMINSTATUS_DOWN	2

extern GSnmpEnum const atm_mib_enums_atmVcCrossConnectAdminStatus[];

#define ATM_MIB_ATMVCCROSSCONNECTL2HOPERSTATUS_UP	1
#define ATM_MIB_ATMVCCROSSCONNECTL2HOPERSTATUS_DOWN	2
#define ATM_MIB_ATMVCCROSSCONNECTL2HOPERSTATUS_UNKNOWN	3

extern GSnmpEnum const atm_mib_enums_atmVcCrossConnectL2HOperStatus[];

#define ATM_MIB_ATMVCCROSSCONNECTH2LOPERSTATUS_UP	1
#define ATM_MIB_ATMVCCROSSCONNECTH2LOPERSTATUS_DOWN	2
#define ATM_MIB_ATMVCCROSSCONNECTH2LOPERSTATUS_UNKNOWN	3

extern GSnmpEnum const atm_mib_enums_atmVcCrossConnectH2LOperStatus[];

#define ATM_MIB_ATMVCCROSSCONNECTROWSTATUS_ACTIVE	1
#define ATM_MIB_ATMVCCROSSCONNECTROWSTATUS_NOTINSERVICE	2
#define ATM_MIB_ATMVCCROSSCONNECTROWSTATUS_NOTREADY	3
#define ATM_MIB_ATMVCCROSSCONNECTROWSTATUS_CREATEANDGO	4
#define ATM_MIB_ATMVCCROSSCONNECTROWSTATUS_CREATEANDWAIT	5
#define ATM_MIB_ATMVCCROSSCONNECTROWSTATUS_DESTROY	6

extern GSnmpEnum const atm_mib_enums_atmVcCrossConnectRowStatus[];


/*
 * C type definitions for ATM-MIB::atmMIBObjects.
 */

typedef struct {
    gint32   *atmVpCrossConnectIndexNext;
    gint32   *atmVcCrossConnectIndexNext;
    gint32   *atmTrafficDescrParamIndexNext;
} atm_mib_atmMIBObjects_t;

extern atm_mib_atmMIBObjects_t *
atm_mib_new_atmMIBObjects();

extern int
atm_mib_get_atmMIBObjects(GSnmpSession *s, atm_mib_atmMIBObjects_t **atmMIBObjects);

extern void
atm_mib_free_atmMIBObjects(atm_mib_atmMIBObjects_t *atmMIBObjects);

/*
 * C type definitions for ATM-MIB::atmInterfaceConfEntry.
 */

typedef struct {
    gint32   ifIndex;
    gint32   *atmInterfaceMaxVpcs;
    gint32   *atmInterfaceMaxVccs;
    gint32   *atmInterfaceConfVpcs;
    gint32   *atmInterfaceConfVccs;
    gint32   *atmInterfaceMaxActiveVpiBits;
    gint32   *atmInterfaceMaxActiveVciBits;
    gint32   *atmInterfaceIlmiVpi;
    gint32   *atmInterfaceIlmiVci;
    gint32   *atmInterfaceAddressType;
    guchar   *atmInterfaceAdminAddress;
    gsize    _atmInterfaceAdminAddressLength;
    guchar   *atmInterfaceMyNeighborIpAddress;
    guchar   *atmInterfaceMyNeighborIfName;
    gsize    _atmInterfaceMyNeighborIfNameLength;
    gint32   *atmInterfaceCurrentMaxVpiBits;
    gint32   *atmInterfaceCurrentMaxVciBits;
    guchar   *atmInterfaceSubscrAddress;
    gsize    _atmInterfaceSubscrAddressLength;
} atm_mib_atmInterfaceConfEntry_t;

extern int
atm_mib_get_atmInterfaceConfTable(GSnmpSession *s, atm_mib_atmInterfaceConfEntry_t ***atmInterfaceConfEntry);

extern void
atm_mib_free_atmInterfaceConfTable(atm_mib_atmInterfaceConfEntry_t **atmInterfaceConfEntry);

extern atm_mib_atmInterfaceConfEntry_t *
atm_mib_new_atmInterfaceConfEntry();

extern int
atm_mib_get_atmInterfaceConfEntry(GSnmpSession *s, atm_mib_atmInterfaceConfEntry_t **atmInterfaceConfEntry);

extern int
atm_mib_set_atmInterfaceConfEntry(GSnmpSession *s, atm_mib_atmInterfaceConfEntry_t *atmInterfaceConfEntry);

extern void
atm_mib_free_atmInterfaceConfEntry(atm_mib_atmInterfaceConfEntry_t *atmInterfaceConfEntry);

/*
 * C type definitions for ATM-MIB::atmInterfaceDs3PlcpEntry.
 */

typedef struct {
    gint32   ifIndex;
    guint32  *atmInterfaceDs3PlcpSEFSs;
    gint32   *atmInterfaceDs3PlcpAlarmState;
    guint32  *atmInterfaceDs3PlcpUASs;
} atm_mib_atmInterfaceDs3PlcpEntry_t;

extern int
atm_mib_get_atmInterfaceDs3PlcpTable(GSnmpSession *s, atm_mib_atmInterfaceDs3PlcpEntry_t ***atmInterfaceDs3PlcpEntry);

extern void
atm_mib_free_atmInterfaceDs3PlcpTable(atm_mib_atmInterfaceDs3PlcpEntry_t **atmInterfaceDs3PlcpEntry);

extern atm_mib_atmInterfaceDs3PlcpEntry_t *
atm_mib_new_atmInterfaceDs3PlcpEntry();

extern int
atm_mib_get_atmInterfaceDs3PlcpEntry(GSnmpSession *s, atm_mib_atmInterfaceDs3PlcpEntry_t **atmInterfaceDs3PlcpEntry);

extern void
atm_mib_free_atmInterfaceDs3PlcpEntry(atm_mib_atmInterfaceDs3PlcpEntry_t *atmInterfaceDs3PlcpEntry);

/*
 * C type definitions for ATM-MIB::atmInterfaceTCEntry.
 */

typedef struct {
    gint32   ifIndex;
    guint32  *atmInterfaceOCDEvents;
    gint32   *atmInterfaceTCAlarmState;
} atm_mib_atmInterfaceTCEntry_t;

extern int
atm_mib_get_atmInterfaceTCTable(GSnmpSession *s, atm_mib_atmInterfaceTCEntry_t ***atmInterfaceTCEntry);

extern void
atm_mib_free_atmInterfaceTCTable(atm_mib_atmInterfaceTCEntry_t **atmInterfaceTCEntry);

extern atm_mib_atmInterfaceTCEntry_t *
atm_mib_new_atmInterfaceTCEntry();

extern int
atm_mib_get_atmInterfaceTCEntry(GSnmpSession *s, atm_mib_atmInterfaceTCEntry_t **atmInterfaceTCEntry);

extern void
atm_mib_free_atmInterfaceTCEntry(atm_mib_atmInterfaceTCEntry_t *atmInterfaceTCEntry);

/*
 * C type definitions for ATM-MIB::atmTrafficDescrParamEntry.
 */

typedef struct {
    gint32   atmTrafficDescrParamIndex;
    guint32  *atmTrafficDescrType;
    gsize    _atmTrafficDescrTypeLength;
    gint32   *atmTrafficDescrParam1;
    gint32   *atmTrafficDescrParam2;
    gint32   *atmTrafficDescrParam3;
    gint32   *atmTrafficDescrParam4;
    gint32   *atmTrafficDescrParam5;
    gint32   *atmTrafficQoSClass;
    gint32   *atmTrafficDescrRowStatus;
    gint32   *atmServiceCategory;
    gint32   *atmTrafficFrameDiscard;
} atm_mib_atmTrafficDescrParamEntry_t;

extern int
atm_mib_get_atmTrafficDescrParamTable(GSnmpSession *s, atm_mib_atmTrafficDescrParamEntry_t ***atmTrafficDescrParamEntry);

extern void
atm_mib_free_atmTrafficDescrParamTable(atm_mib_atmTrafficDescrParamEntry_t **atmTrafficDescrParamEntry);

extern atm_mib_atmTrafficDescrParamEntry_t *
atm_mib_new_atmTrafficDescrParamEntry();

extern int
atm_mib_get_atmTrafficDescrParamEntry(GSnmpSession *s, atm_mib_atmTrafficDescrParamEntry_t **atmTrafficDescrParamEntry);

extern int
atm_mib_set_atmTrafficDescrParamEntry(GSnmpSession *s, atm_mib_atmTrafficDescrParamEntry_t *atmTrafficDescrParamEntry);

extern void
atm_mib_free_atmTrafficDescrParamEntry(atm_mib_atmTrafficDescrParamEntry_t *atmTrafficDescrParamEntry);

/*
 * C type definitions for ATM-MIB::atmVplEntry.
 */

typedef struct {
    gint32   ifIndex;
    gint32   atmVplVpi;
    gint32   *atmVplAdminStatus;
    gint32   *atmVplOperStatus;
    guint32  *atmVplLastChange;
    gint32   *atmVplReceiveTrafficDescrIndex;
    gint32   *atmVplTransmitTrafficDescrIndex;
    gint32   *atmVplCrossConnectIdentifier;
    gint32   *atmVplRowStatus;
    gint32   *atmVplCastType;
    gint32   *atmVplConnKind;
} atm_mib_atmVplEntry_t;

extern int
atm_mib_get_atmVplTable(GSnmpSession *s, atm_mib_atmVplEntry_t ***atmVplEntry);

extern void
atm_mib_free_atmVplTable(atm_mib_atmVplEntry_t **atmVplEntry);

extern atm_mib_atmVplEntry_t *
atm_mib_new_atmVplEntry();

extern int
atm_mib_get_atmVplEntry(GSnmpSession *s, atm_mib_atmVplEntry_t **atmVplEntry);

extern int
atm_mib_set_atmVplEntry(GSnmpSession *s, atm_mib_atmVplEntry_t *atmVplEntry);

extern void
atm_mib_free_atmVplEntry(atm_mib_atmVplEntry_t *atmVplEntry);

/*
 * C type definitions for ATM-MIB::atmVclEntry.
 */

typedef struct {
    gint32   ifIndex;
    gint32   atmVclVpi;
    gint32   atmVclVci;
    gint32   *atmVclAdminStatus;
    gint32   *atmVclOperStatus;
    guint32  *atmVclLastChange;
    gint32   *atmVclReceiveTrafficDescrIndex;
    gint32   *atmVclTransmitTrafficDescrIndex;
    gint32   *atmVccAalType;
    gint32   *atmVccAal5CpcsTransmitSduSize;
    gint32   *atmVccAal5CpcsReceiveSduSize;
    gint32   *atmVccAal5EncapsType;
    gint32   *atmVclCrossConnectIdentifier;
    gint32   *atmVclRowStatus;
    gint32   *atmVclCastType;
    gint32   *atmVclConnKind;
} atm_mib_atmVclEntry_t;

extern int
atm_mib_get_atmVclTable(GSnmpSession *s, atm_mib_atmVclEntry_t ***atmVclEntry);

extern void
atm_mib_free_atmVclTable(atm_mib_atmVclEntry_t **atmVclEntry);

extern atm_mib_atmVclEntry_t *
atm_mib_new_atmVclEntry();

extern int
atm_mib_get_atmVclEntry(GSnmpSession *s, atm_mib_atmVclEntry_t **atmVclEntry);

extern int
atm_mib_set_atmVclEntry(GSnmpSession *s, atm_mib_atmVclEntry_t *atmVclEntry);

extern void
atm_mib_free_atmVclEntry(atm_mib_atmVclEntry_t *atmVclEntry);

/*
 * C type definitions for ATM-MIB::atmVpCrossConnectEntry.
 */

typedef struct {
    gint32   atmVpCrossConnectIndex;
    gint32   atmVpCrossConnectLowIfIndex;
    gint32   atmVpCrossConnectLowVpi;
    gint32   atmVpCrossConnectHighIfIndex;
    gint32   atmVpCrossConnectHighVpi;
    gint32   *atmVpCrossConnectAdminStatus;
    gint32   *atmVpCrossConnectL2HOperStatus;
    gint32   *atmVpCrossConnectH2LOperStatus;
    guint32  *atmVpCrossConnectL2HLastChange;
    guint32  *atmVpCrossConnectH2LLastChange;
    gint32   *atmVpCrossConnectRowStatus;
} atm_mib_atmVpCrossConnectEntry_t;

extern int
atm_mib_get_atmVpCrossConnectTable(GSnmpSession *s, atm_mib_atmVpCrossConnectEntry_t ***atmVpCrossConnectEntry);

extern void
atm_mib_free_atmVpCrossConnectTable(atm_mib_atmVpCrossConnectEntry_t **atmVpCrossConnectEntry);

extern atm_mib_atmVpCrossConnectEntry_t *
atm_mib_new_atmVpCrossConnectEntry();

extern int
atm_mib_get_atmVpCrossConnectEntry(GSnmpSession *s, atm_mib_atmVpCrossConnectEntry_t **atmVpCrossConnectEntry);

extern int
atm_mib_set_atmVpCrossConnectEntry(GSnmpSession *s, atm_mib_atmVpCrossConnectEntry_t *atmVpCrossConnectEntry);

extern void
atm_mib_free_atmVpCrossConnectEntry(atm_mib_atmVpCrossConnectEntry_t *atmVpCrossConnectEntry);

/*
 * C type definitions for ATM-MIB::atmVcCrossConnectEntry.
 */

typedef struct {
    gint32   atmVcCrossConnectIndex;
    gint32   atmVcCrossConnectLowIfIndex;
    gint32   atmVcCrossConnectLowVpi;
    gint32   atmVcCrossConnectLowVci;
    gint32   atmVcCrossConnectHighIfIndex;
    gint32   atmVcCrossConnectHighVpi;
    gint32   atmVcCrossConnectHighVci;
    gint32   *atmVcCrossConnectAdminStatus;
    gint32   *atmVcCrossConnectL2HOperStatus;
    gint32   *atmVcCrossConnectH2LOperStatus;
    guint32  *atmVcCrossConnectL2HLastChange;
    guint32  *atmVcCrossConnectH2LLastChange;
    gint32   *atmVcCrossConnectRowStatus;
} atm_mib_atmVcCrossConnectEntry_t;

extern int
atm_mib_get_atmVcCrossConnectTable(GSnmpSession *s, atm_mib_atmVcCrossConnectEntry_t ***atmVcCrossConnectEntry);

extern void
atm_mib_free_atmVcCrossConnectTable(atm_mib_atmVcCrossConnectEntry_t **atmVcCrossConnectEntry);

extern atm_mib_atmVcCrossConnectEntry_t *
atm_mib_new_atmVcCrossConnectEntry();

extern int
atm_mib_get_atmVcCrossConnectEntry(GSnmpSession *s, atm_mib_atmVcCrossConnectEntry_t **atmVcCrossConnectEntry);

extern int
atm_mib_set_atmVcCrossConnectEntry(GSnmpSession *s, atm_mib_atmVcCrossConnectEntry_t *atmVcCrossConnectEntry);

extern void
atm_mib_free_atmVcCrossConnectEntry(atm_mib_atmVcCrossConnectEntry_t *atmVcCrossConnectEntry);

/*
 * C type definitions for ATM-MIB::aal5VccEntry.
 */

typedef struct {
    gint32   ifIndex;
    gint32   aal5VccVpi;
    gint32   aal5VccVci;
    guint32  *aal5VccCrcErrors;
    guint32  *aal5VccSarTimeOuts;
    guint32  *aal5VccOverSizedSDUs;
} atm_mib_aal5VccEntry_t;

extern int
atm_mib_get_aal5VccTable(GSnmpSession *s, atm_mib_aal5VccEntry_t ***aal5VccEntry);

extern void
atm_mib_free_aal5VccTable(atm_mib_aal5VccEntry_t **aal5VccEntry);

extern atm_mib_aal5VccEntry_t *
atm_mib_new_aal5VccEntry();

extern int
atm_mib_get_aal5VccEntry(GSnmpSession *s, atm_mib_aal5VccEntry_t **aal5VccEntry);

extern void
atm_mib_free_aal5VccEntry(atm_mib_aal5VccEntry_t *aal5VccEntry);


#endif /* _ATM_MIB_H_ */
