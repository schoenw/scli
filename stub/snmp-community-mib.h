/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from SNMP-COMMUNITY-MIB revision 2000-03-06 00:00.
 *
 * $Id$
 */

#ifndef _SNMP_COMMUNITY_MIB_H_
#define _SNMP_COMMUNITY_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

extern stls_table_t snmp_community_mib_enums_snmpCommunityStorageType[];
extern stls_table_t snmp_community_mib_enums_snmpCommunityStatus[];

/*
 * C type definitions for SNMP-COMMUNITY-MIB::snmpCommunityEntry.
 */

typedef struct snmpCommunityEntry {
    guchar   *snmpCommunityIndex;
    gsize    _snmpCommunityIndexLength;
    guchar   *snmpCommunityName;
    gsize    _snmpCommunityNameLength;
    guchar   *snmpCommunitySecurityName;
    gsize    _snmpCommunitySecurityNameLength;
    guchar   *snmpCommunityContextEngineID;
    gsize    _snmpCommunityContextEngineIDLength;
    guchar   *snmpCommunityContextName;
    gsize    _snmpCommunityContextNameLength;
    guchar   *snmpCommunityTransportTag;
    gsize    _snmpCommunityTransportTagLength;
    gint32   *snmpCommunityStorageType;
    gint32   *snmpCommunityStatus;
} snmpCommunityEntry_t;

extern int
snmp_community_mib_get_snmpCommunityEntry(host_snmp *s, snmpCommunityEntry_t ***snmpCommunityEntry);

extern void
snmp_community_mib_free_snmpCommunityEntry(snmpCommunityEntry_t **snmpCommunityEntry);

/*
 * C type definitions for SNMP-COMMUNITY-MIB::snmpTargetAddrExtEntry.
 */

typedef struct snmpTargetAddrExtEntry {
    guchar   *snmpTargetAddrName;
    gsize    _snmpTargetAddrNameLength;
    guchar   *snmpTargetAddrTMask;
    gsize    _snmpTargetAddrTMaskLength;
    gint32   *snmpTargetAddrMMS;
} snmpTargetAddrExtEntry_t;

extern int
snmp_community_mib_get_snmpTargetAddrExtEntry(host_snmp *s, snmpTargetAddrExtEntry_t ***snmpTargetAddrExtEntry);

extern void
snmp_community_mib_free_snmpTargetAddrExtEntry(snmpTargetAddrExtEntry_t **snmpTargetAddrExtEntry);


#endif /* _SNMP_COMMUNITY_MIB_H_ */