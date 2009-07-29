/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli SNMP-TARGET-MIB
 *
 * Derived from SNMP-TARGET-MIB:
 *   This MIB module defines MIB objects which provide
 *   mechanisms to remotely configure the parameters used
 *   by an SNMP entity for the generation of SNMP messages.
 *   
 *   Copyright (C) The Internet Society (2002). This
 *   version of this MIB module is part of RFC 3413;
 *   see the RFC itself for full legal notices.
 *
 * Revision 2002-10-14 00:00:
 *   Fixed DISPLAY-HINTS for UTF-8 strings, fixed hex
 *   value of LF characters, clarified meaning of zero
 *   length tag values, improved tag list examples.
 *   Published as RFC 3413.
 *
 * Revision 1998-08-04 00:00:
 *   Clarifications, published as
 *   RFC 2573.
 *
 * Revision 1997-07-14 00:00:
 *   The initial revision, published as RFC2273.
 *
 * $Id$
 */

#ifndef _SNMP_TARGET_MIB_H_
#define _SNMP_TARGET_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * C type definitions for SNMP-TARGET-MIB::snmpTargetObjects.
 */

#define SNMP_TARGET_MIB_SNMPTARGETSPINLOCK      (1 << 0) 
#define SNMP_TARGET_MIB_SNMPUNAVAILABLECONTEXTS (1 << 1) 
#define SNMP_TARGET_MIB_SNMPUNKNOWNCONTEXTS     (1 << 2) 

typedef struct {
    gint32   *snmpTargetSpinLock;          /* rw SNMPv2-TC::TestAndIncr */
    guint32  *snmpUnavailableContexts;     /* ro SNMPv2-SMI::Counter32 */
    guint32  *snmpUnknownContexts;         /* ro SNMPv2-SMI::Counter32 */
} snmp_target_mib_snmpTargetObjects_t;

extern snmp_target_mib_snmpTargetObjects_t *
snmp_target_mib_new_snmpTargetObjects(void);

extern void
snmp_target_mib_get_snmpTargetObjects(GNetSnmp *s, snmp_target_mib_snmpTargetObjects_t **snmpTargetObjects, gint64 mask, GError **error);

extern void
snmp_target_mib_set_snmpTargetObjects(GNetSnmp *s, snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects, gint64 mask, GError **error);

extern void
snmp_target_mib_free_snmpTargetObjects(snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects);

/*
 * C type definitions for SNMP-TARGET-MIB::snmpTargetAddrEntry.
 */

#define SNMP_TARGET_MIB_SNMPTARGETADDRTDOMAIN     (1 << 0) 
#define SNMP_TARGET_MIB_SNMPTARGETADDRTADDRESS    (1 << 1) 
#define SNMP_TARGET_MIB_SNMPTARGETADDRTIMEOUT     (1 << 2) 
#define SNMP_TARGET_MIB_SNMPTARGETADDRRETRYCOUNT  (1 << 3) 
#define SNMP_TARGET_MIB_SNMPTARGETADDRTAGLIST     (1 << 4) 
#define SNMP_TARGET_MIB_SNMPTARGETADDRPARAMS      (1 << 5) 
#define SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE (1 << 6) 
#define SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS   (1 << 7) 

typedef struct {
    guchar   snmpTargetAddrName[32];         /* na */
#define SNMP_TARGET_MIB_SNMPTARGETADDRNAMEMINLENGTH 1
#define SNMP_TARGET_MIB_SNMPTARGETADDRNAMEMAXLENGTH 32
    guint16  _snmpTargetAddrNameLength;
    guint32  *snmpTargetAddrTDomain;         /* rw SNMPv2-TC::TDomain */
#define SNMP_TARGET_MIB_SNMPTARGETADDRTDOMAINMINLENGTH 0
#define SNMP_TARGET_MIB_SNMPTARGETADDRTDOMAINMAXLENGTH 128
    guint16  _snmpTargetAddrTDomainLength;
    guchar   *snmpTargetAddrTAddress;        /* rw SNMPv2-TC::TAddress */
#define SNMP_TARGET_MIB_SNMPTARGETADDRTADDRESSMINLENGTH 1
#define SNMP_TARGET_MIB_SNMPTARGETADDRTADDRESSMAXLENGTH 255
    guint16  _snmpTargetAddrTAddressLength;
    gint32   *snmpTargetAddrTimeout;         /* rw SNMPv2-TC::TimeInterval */
    gint32   *snmpTargetAddrRetryCount;      /* rw */
    guchar   *snmpTargetAddrTagList;         /* rw SNMP-TARGET-MIB::SnmpTagList */
#define SNMP_TARGET_MIB_SNMPTARGETADDRTAGLISTMINLENGTH 0
#define SNMP_TARGET_MIB_SNMPTARGETADDRTAGLISTMAXLENGTH 255
    guint16  _snmpTargetAddrTagListLength;
    guchar   *snmpTargetAddrParams;          /* rw */
#define SNMP_TARGET_MIB_SNMPTARGETADDRPARAMSMINLENGTH 1
#define SNMP_TARGET_MIB_SNMPTARGETADDRPARAMSMAXLENGTH 32
    guint16  _snmpTargetAddrParamsLength;
    gint32   *snmpTargetAddrStorageType;     /* rw SNMPv2-TC::StorageType */
    gint32   *snmpTargetAddrRowStatus;       /* rw SNMPv2-TC::RowStatus */
} snmp_target_mib_snmpTargetAddrEntry_t;

extern void
snmp_target_mib_get_snmpTargetAddrTable(GNetSnmp *s, snmp_target_mib_snmpTargetAddrEntry_t ***snmpTargetAddrEntry, gint64 mask, GError **error);

extern void
snmp_target_mib_free_snmpTargetAddrTable(snmp_target_mib_snmpTargetAddrEntry_t **snmpTargetAddrEntry);

extern snmp_target_mib_snmpTargetAddrEntry_t *
snmp_target_mib_new_snmpTargetAddrEntry(void);

extern void
snmp_target_mib_get_snmpTargetAddrEntry(GNetSnmp *s, snmp_target_mib_snmpTargetAddrEntry_t **snmpTargetAddrEntry, guchar *snmpTargetAddrName, guint16 _snmpTargetAddrNameLength, gint64 mask, GError **error);

extern void
snmp_target_mib_set_snmpTargetAddrEntry(GNetSnmp *s, snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry, gint64 mask, GError **error);

extern void
snmp_target_mib_free_snmpTargetAddrEntry(snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry);

/*
 * C type definitions for SNMP-TARGET-MIB::snmpTargetParamsEntry.
 */

#define SNMP_TARGET_MIB_SNMPTARGETPARAMSMPMODEL       (1 << 0) 
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYMODEL (1 << 1) 
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYNAME  (1 << 2) 
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL (1 << 3) 
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE   (1 << 4) 
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS     (1 << 5) 

typedef struct {
    guchar   snmpTargetParamsName[32];           /* na */
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSNAMEMINLENGTH 1
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSNAMEMAXLENGTH 32
    guint16  _snmpTargetParamsNameLength;
    gint32   *snmpTargetParamsMPModel;           /* rw SNMP-FRAMEWORK-MIB::SnmpMessageProcessingModel */
    gint32   *snmpTargetParamsSecurityModel;     /* rw */
    guchar   *snmpTargetParamsSecurityName;      /* rw SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYNAMEMINLENGTH 0
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYNAMEMAXLENGTH 255
    guint16  _snmpTargetParamsSecurityNameLength;
    gint32   *snmpTargetParamsSecurityLevel;     /* rw SNMP-FRAMEWORK-MIB::SnmpSecurityLevel */
    gint32   *snmpTargetParamsStorageType;       /* rw SNMPv2-TC::StorageType */
    gint32   *snmpTargetParamsRowStatus;         /* rw SNMPv2-TC::RowStatus */
} snmp_target_mib_snmpTargetParamsEntry_t;

extern void
snmp_target_mib_get_snmpTargetParamsTable(GNetSnmp *s, snmp_target_mib_snmpTargetParamsEntry_t ***snmpTargetParamsEntry, gint64 mask, GError **error);

extern void
snmp_target_mib_free_snmpTargetParamsTable(snmp_target_mib_snmpTargetParamsEntry_t **snmpTargetParamsEntry);

extern snmp_target_mib_snmpTargetParamsEntry_t *
snmp_target_mib_new_snmpTargetParamsEntry(void);

extern void
snmp_target_mib_get_snmpTargetParamsEntry(GNetSnmp *s, snmp_target_mib_snmpTargetParamsEntry_t **snmpTargetParamsEntry, guchar *snmpTargetParamsName, guint16 _snmpTargetParamsNameLength, gint64 mask, GError **error);

extern void
snmp_target_mib_set_snmpTargetParamsEntry(GNetSnmp *s, snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry, gint64 mask, GError **error);

extern void
snmp_target_mib_free_snmpTargetParamsEntry(snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry);


G_END_DECLS

#endif /* _SNMP_TARGET_MIB_H_ */
