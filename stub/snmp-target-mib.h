/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from SNMP-TARGET-MIB:
 *   This MIB module defines MIB objects which provide
 *   mechanisms to remotely configure the parameters used
 *   by an SNMP entity for the generation of SNMP messages.
 *
 * Revision 1998-08-04 00:00:
 *   Clarifications, published as
 *   RFC2573.
 *
 * Revision 1997-07-14 00:00:
 *   The initial revision, published as RFC2273.
 *
 * $Id$
 */

#ifndef _SNMP_TARGET_MIB_H_
#define _SNMP_TARGET_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_OTHER	1
#define SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_VOLATILE	2
#define SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_NONVOLATILE	3
#define SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_PERMANENT	4
#define SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_READONLY	5

extern stls_enum_t const snmp_target_mib_enums_snmpTargetAddrStorageType[];

#define SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_ACTIVE	1
#define SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_NOTINSERVICE	2
#define SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_NOTREADY	3
#define SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_CREATEANDGO	4
#define SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_CREATEANDWAIT	5
#define SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_DESTROY	6

extern stls_enum_t const snmp_target_mib_enums_snmpTargetAddrRowStatus[];

#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL_NOAUTHNOPRIV	1
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL_AUTHNOPRIV	2
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL_AUTHPRIV	3

extern stls_enum_t const snmp_target_mib_enums_snmpTargetParamsSecurityLevel[];

#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_OTHER	1
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_VOLATILE	2
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_NONVOLATILE	3
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_PERMANENT	4
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_READONLY	5

extern stls_enum_t const snmp_target_mib_enums_snmpTargetParamsStorageType[];

#define SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_ACTIVE	1
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_NOTINSERVICE	2
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_NOTREADY	3
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_CREATEANDGO	4
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_CREATEANDWAIT	5
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_DESTROY	6

extern stls_enum_t const snmp_target_mib_enums_snmpTargetParamsRowStatus[];


/*
 * C type definitions for SNMP-TARGET-MIB::snmpTargetObjects.
 */

typedef struct {
    gint32   *snmpTargetSpinLock;
    guint32  *snmpUnavailableContexts;
    guint32  *snmpUnknownContexts;
} snmp_target_mib_snmpTargetObjects_t;

extern snmp_target_mib_snmpTargetObjects_t *
snmp_target_mib_new_snmpTargetObjects();

extern int
snmp_target_mib_get_snmpTargetObjects(GSnmpSession *s, snmp_target_mib_snmpTargetObjects_t **snmpTargetObjects);

extern int
snmp_target_mib_set_snmpTargetObjects(GSnmpSession *s, snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects);

extern void
snmp_target_mib_free_snmpTargetObjects(snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects);

/*
 * C type definitions for SNMP-TARGET-MIB::snmpTargetAddrEntry.
 */

typedef struct {
    guchar   snmpTargetAddrName[32];
    gsize    _snmpTargetAddrNameLength;
    guint32  *snmpTargetAddrTDomain;
    gsize    _snmpTargetAddrTDomainLength;
    guchar   *snmpTargetAddrTAddress;
    gsize    _snmpTargetAddrTAddressLength;
    gint32   *snmpTargetAddrTimeout;
    gint32   *snmpTargetAddrRetryCount;
    guchar   *snmpTargetAddrTagList;
    gsize    _snmpTargetAddrTagListLength;
    guchar   *snmpTargetAddrParams;
    gsize    _snmpTargetAddrParamsLength;
    gint32   *snmpTargetAddrStorageType;
    gint32   *snmpTargetAddrRowStatus;
} snmp_target_mib_snmpTargetAddrEntry_t;

extern int
snmp_target_mib_get_snmpTargetAddrTable(GSnmpSession *s, snmp_target_mib_snmpTargetAddrEntry_t ***snmpTargetAddrEntry);

extern void
snmp_target_mib_free_snmpTargetAddrTable(snmp_target_mib_snmpTargetAddrEntry_t **snmpTargetAddrEntry);

extern snmp_target_mib_snmpTargetAddrEntry_t *
snmp_target_mib_new_snmpTargetAddrEntry();

extern int
snmp_target_mib_get_snmpTargetAddrEntry(GSnmpSession *s, snmp_target_mib_snmpTargetAddrEntry_t **snmpTargetAddrEntry);

extern int
snmp_target_mib_set_snmpTargetAddrEntry(GSnmpSession *s, snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry);

extern void
snmp_target_mib_free_snmpTargetAddrEntry(snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry);

/*
 * C type definitions for SNMP-TARGET-MIB::snmpTargetParamsEntry.
 */

typedef struct {
    guchar   snmpTargetParamsName[32];
    gsize    _snmpTargetParamsNameLength;
    gint32   *snmpTargetParamsMPModel;
    gint32   *snmpTargetParamsSecurityModel;
    guchar   *snmpTargetParamsSecurityName;
    gsize    _snmpTargetParamsSecurityNameLength;
    gint32   *snmpTargetParamsSecurityLevel;
    gint32   *snmpTargetParamsStorageType;
    gint32   *snmpTargetParamsRowStatus;
} snmp_target_mib_snmpTargetParamsEntry_t;

extern int
snmp_target_mib_get_snmpTargetParamsTable(GSnmpSession *s, snmp_target_mib_snmpTargetParamsEntry_t ***snmpTargetParamsEntry);

extern void
snmp_target_mib_free_snmpTargetParamsTable(snmp_target_mib_snmpTargetParamsEntry_t **snmpTargetParamsEntry);

extern snmp_target_mib_snmpTargetParamsEntry_t *
snmp_target_mib_new_snmpTargetParamsEntry();

extern int
snmp_target_mib_get_snmpTargetParamsEntry(GSnmpSession *s, snmp_target_mib_snmpTargetParamsEntry_t **snmpTargetParamsEntry);

extern int
snmp_target_mib_set_snmpTargetParamsEntry(GSnmpSession *s, snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry);

extern void
snmp_target_mib_free_snmpTargetParamsEntry(snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry);


#endif /* _SNMP_TARGET_MIB_H_ */
