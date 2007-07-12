/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli SNMP-COMMUNITY-MIB
 *
 * Derived from SNMP-COMMUNITY-MIB:
 *   This MIB module defines objects to help support coexistence
 *   between SNMPv1, SNMPv2c, and SNMPv3.
 *
 * Revision 2000-03-06 00:00:
 *   This version published as RFC 2576.
 *
 * Revision 1999-05-13 00:00:
 *   The Initial Revision
 *
 * $Id$
 */

#ifndef _SNMP_COMMUNITY_MIB_H_
#define _SNMP_COMMUNITY_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * C type definitions for SNMP-COMMUNITY-MIB::snmpCommunityEntry.
 */

#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYNAME            (1 << 0) 
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSECURITYNAME    (1 << 1) 
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTENGINEID (1 << 2) 
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTNAME     (1 << 3) 
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYTRANSPORTTAG    (1 << 4) 
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTORAGETYPE     (1 << 5) 
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTATUS          (1 << 6) 

typedef struct {
    guchar   snmpCommunityIndex[32];            /* na */
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYINDEXMINLENGTH 1
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYINDEXMAXLENGTH 32
    guint16  _snmpCommunityIndexLength;
    guchar   *snmpCommunityName;                /* rw OctetString */
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYNAMEMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYNAMEMAXLENGTH 65535
    guint16  _snmpCommunityNameLength;
    guchar   *snmpCommunitySecurityName;        /* rw */
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSECURITYNAMEMINLENGTH 1
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSECURITYNAMEMAXLENGTH 32
    guint16  _snmpCommunitySecurityNameLength;
    guchar   *snmpCommunityContextEngineID;     /* rw SNMP-FRAMEWORK-MIB::SnmpEngineID */
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTENGINEIDMINLENGTH 5
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTENGINEIDMAXLENGTH 32
    guint16  _snmpCommunityContextEngineIDLength;
    guchar   *snmpCommunityContextName;         /* rw */
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTNAMEMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTNAMEMAXLENGTH 32
    guint16  _snmpCommunityContextNameLength;
    guchar   *snmpCommunityTransportTag;        /* rw SNMP-TARGET-MIB::SnmpTagValue */
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYTRANSPORTTAGMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYTRANSPORTTAGMAXLENGTH 255
    guint16  _snmpCommunityTransportTagLength;
    gint32   *snmpCommunityStorageType;         /* rw SNMPv2-TC::StorageType */
    gint32   *snmpCommunityStatus;              /* rw SNMPv2-TC::RowStatus */
} snmp_community_mib_snmpCommunityEntry_t;

extern void
snmp_community_mib_get_snmpCommunityTable(GNetSnmp *s, snmp_community_mib_snmpCommunityEntry_t ***snmpCommunityEntry, gint64 mask);

extern void
snmp_community_mib_free_snmpCommunityTable(snmp_community_mib_snmpCommunityEntry_t **snmpCommunityEntry);

extern snmp_community_mib_snmpCommunityEntry_t *
snmp_community_mib_new_snmpCommunityEntry(void);

extern void
snmp_community_mib_get_snmpCommunityEntry(GNetSnmp *s, snmp_community_mib_snmpCommunityEntry_t **snmpCommunityEntry, guchar *snmpCommunityIndex, guint16 _snmpCommunityIndexLength, gint64 mask);

extern void
snmp_community_mib_set_snmpCommunityEntry(GNetSnmp *s, snmp_community_mib_snmpCommunityEntry_t *snmpCommunityEntry, gint64 mask);

extern void
snmp_community_mib_free_snmpCommunityEntry(snmp_community_mib_snmpCommunityEntry_t *snmpCommunityEntry);

/*
 * C type definitions for SNMP-COMMUNITY-MIB::snmpTargetAddrExtEntry.
 */

#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRTMASK (1 << 0) 
#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRMMS   (1 << 1) 

typedef struct {
    guchar   snmpTargetAddrName[32];   /* na */
#define SNMP_TARGET_MIB_SNMPTARGETADDRNAMEMINLENGTH 1
#define SNMP_TARGET_MIB_SNMPTARGETADDRNAMEMAXLENGTH 32
    guint16  _snmpTargetAddrNameLength;
    guchar   *snmpTargetAddrTMask;     /* rw */
#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRTMASKMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRTMASKMAXLENGTH 255
    guint16  _snmpTargetAddrTMaskLength;
    gint32   *snmpTargetAddrMMS;       /* rw */
} snmp_community_mib_snmpTargetAddrExtEntry_t;

extern void
snmp_community_mib_get_snmpTargetAddrExtTable(GNetSnmp *s, snmp_community_mib_snmpTargetAddrExtEntry_t ***snmpTargetAddrExtEntry, gint64 mask);

extern void
snmp_community_mib_free_snmpTargetAddrExtTable(snmp_community_mib_snmpTargetAddrExtEntry_t **snmpTargetAddrExtEntry);

extern snmp_community_mib_snmpTargetAddrExtEntry_t *
snmp_community_mib_new_snmpTargetAddrExtEntry(void);

extern void
snmp_community_mib_get_snmpTargetAddrExtEntry(GNetSnmp *s, snmp_community_mib_snmpTargetAddrExtEntry_t **snmpTargetAddrExtEntry, guchar *snmpTargetAddrName, guint16 _snmpTargetAddrNameLength, gint64 mask);

extern void
snmp_community_mib_set_snmpTargetAddrExtEntry(GNetSnmp *s, snmp_community_mib_snmpTargetAddrExtEntry_t *snmpTargetAddrExtEntry, gint64 mask);

extern void
snmp_community_mib_free_snmpTargetAddrExtEntry(snmp_community_mib_snmpTargetAddrExtEntry_t *snmpTargetAddrExtEntry);


G_END_DECLS

#endif /* _SNMP_COMMUNITY_MIB_H_ */
