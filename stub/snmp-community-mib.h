/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
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

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTORAGETYPE_OTHER       1
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTORAGETYPE_VOLATILE    2
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTORAGETYPE_NONVOLATILE 3
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTORAGETYPE_PERMANENT   4
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTORAGETYPE_READONLY    5

extern GSnmpEnum const snmp_community_mib_enums_snmpCommunityStorageType[];

#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTATUS_ACTIVE        1
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTATUS_NOTINSERVICE  2
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTATUS_NOTREADY      3
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTATUS_CREATEANDGO   4
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTATUS_CREATEANDWAIT 5
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSTATUS_DESTROY       6

extern GSnmpEnum const snmp_community_mib_enums_snmpCommunityStatus[];


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
    guchar   snmpCommunityIndex[32];
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYINDEXMINLENGTH 1
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYINDEXMAXLENGTH 32
    guint16  _snmpCommunityIndexLength;
    guchar   *snmpCommunityName;
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYNAMEMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYNAMEMAXLENGTH 65535
    guint16  _snmpCommunityNameLength;
    guchar   *snmpCommunitySecurityName;
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSECURITYNAMEMINLENGTH 1
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYSECURITYNAMEMAXLENGTH 32
    guint16  _snmpCommunitySecurityNameLength;
    guchar   *snmpCommunityContextEngineID;
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTENGINEIDMINLENGTH 5
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTENGINEIDMAXLENGTH 32
    guint16  _snmpCommunityContextEngineIDLength;
    guchar   *snmpCommunityContextName;
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTNAMEMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYCONTEXTNAMEMAXLENGTH 32
    guint16  _snmpCommunityContextNameLength;
    guchar   *snmpCommunityTransportTag;
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYTRANSPORTTAGMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPCOMMUNITYTRANSPORTTAGMAXLENGTH 255
    guint16  _snmpCommunityTransportTagLength;
    gint32   *snmpCommunityStorageType;
    gint32   *snmpCommunityStatus;
} snmp_community_mib_snmpCommunityEntry_t;

extern void
snmp_community_mib_get_snmpCommunityTable(GSnmpSession *s, snmp_community_mib_snmpCommunityEntry_t ***snmpCommunityEntry, gint mask);

extern void
snmp_community_mib_free_snmpCommunityTable(snmp_community_mib_snmpCommunityEntry_t **snmpCommunityEntry);

extern snmp_community_mib_snmpCommunityEntry_t *
snmp_community_mib_new_snmpCommunityEntry(void);

extern void
snmp_community_mib_get_snmpCommunityEntry(GSnmpSession *s, snmp_community_mib_snmpCommunityEntry_t **snmpCommunityEntry, guchar *snmpCommunityIndex, guint16 _snmpCommunityIndexLength, gint mask);

extern void
snmp_community_mib_set_snmpCommunityEntry(GSnmpSession *s, snmp_community_mib_snmpCommunityEntry_t *snmpCommunityEntry, gint mask);

extern void
snmp_community_mib_free_snmpCommunityEntry(snmp_community_mib_snmpCommunityEntry_t *snmpCommunityEntry);

/*
 * C type definitions for SNMP-COMMUNITY-MIB::snmpTargetAddrExtEntry.
 */

#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRTMASK (1 << 0) 
#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRMMS   (1 << 1) 

typedef struct {
    guchar   snmpTargetAddrName[32];
#define SNMP_TARGET_MIB_SNMPTARGETADDRNAMEMINLENGTH 1
#define SNMP_TARGET_MIB_SNMPTARGETADDRNAMEMAXLENGTH 32
    guint16  _snmpTargetAddrNameLength;
    guchar   *snmpTargetAddrTMask;
#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRTMASKMINLENGTH 0
#define SNMP_COMMUNITY_MIB_SNMPTARGETADDRTMASKMAXLENGTH 255
    guint16  _snmpTargetAddrTMaskLength;
    gint32   *snmpTargetAddrMMS;
} snmp_community_mib_snmpTargetAddrExtEntry_t;

extern void
snmp_community_mib_get_snmpTargetAddrExtTable(GSnmpSession *s, snmp_community_mib_snmpTargetAddrExtEntry_t ***snmpTargetAddrExtEntry, gint mask);

extern void
snmp_community_mib_free_snmpTargetAddrExtTable(snmp_community_mib_snmpTargetAddrExtEntry_t **snmpTargetAddrExtEntry);

extern snmp_community_mib_snmpTargetAddrExtEntry_t *
snmp_community_mib_new_snmpTargetAddrExtEntry(void);

extern void
snmp_community_mib_get_snmpTargetAddrExtEntry(GSnmpSession *s, snmp_community_mib_snmpTargetAddrExtEntry_t **snmpTargetAddrExtEntry, guchar *snmpTargetAddrName, guint16 _snmpTargetAddrNameLength, gint mask);

extern void
snmp_community_mib_set_snmpTargetAddrExtEntry(GSnmpSession *s, snmp_community_mib_snmpTargetAddrExtEntry_t *snmpTargetAddrExtEntry, gint mask);

extern void
snmp_community_mib_free_snmpTargetAddrExtEntry(snmp_community_mib_snmpTargetAddrExtEntry_t *snmpTargetAddrExtEntry);


#endif /* _SNMP_COMMUNITY_MIB_H_ */
