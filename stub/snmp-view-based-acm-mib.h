/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from SNMP-VIEW-BASED-ACM-MIB:
 *   The management information definitions for the
 *   View-based Access Control Model for SNMP.
 *   
 *
 * Revision 1999-01-20 00:00:
 *   Clarifications, published as RFC2575
 *
 * Revision 1997-11-20 00:00:
 *   Initial version, published as RFC2275
 *
 * $Id$
 */

#ifndef _SNMP_VIEW_BASED_ACM_MIB_H_
#define _SNMP_VIEW_BASED_ACM_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTORAGETYPE_OTHER	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTORAGETYPE_VOLATILE	2
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTORAGETYPE_NONVOLATILE	3
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTORAGETYPE_PERMANENT	4
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTORAGETYPE_READONLY	5

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmSecurityToGroupStorageType[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_ACTIVE	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_NOTINSERVICE	2
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_NOTREADY	3
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_CREATEANDGO	4
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_CREATEANDWAIT	5
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS_DESTROY	6

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmSecurityToGroupStatus[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_NOAUTHNOPRIV	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_AUTHNOPRIV	2
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSECURITYLEVEL_AUTHPRIV	3

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmAccessSecurityLevel[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH_EXACT	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH_PREFIX	2

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmAccessContextMatch[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTORAGETYPE_OTHER	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTORAGETYPE_VOLATILE	2
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTORAGETYPE_NONVOLATILE	3
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTORAGETYPE_PERMANENT	4
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTORAGETYPE_READONLY	5

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmAccessStorageType[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS_ACTIVE	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS_NOTINSERVICE	2
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS_NOTREADY	3
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS_CREATEANDGO	4
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS_CREATEANDWAIT	5
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS_DESTROY	6

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmAccessStatus[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_INCLUDED	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_EXCLUDED	2

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmViewTreeFamilyType[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTORAGETYPE_OTHER	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTORAGETYPE_VOLATILE	2
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTORAGETYPE_NONVOLATILE	3
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTORAGETYPE_PERMANENT	4
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTORAGETYPE_READONLY	5

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmViewTreeFamilyStorageType[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS_ACTIVE	1
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS_NOTINSERVICE	2
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS_NOTREADY	3
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS_CREATEANDGO	4
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS_CREATEANDWAIT	5
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS_DESTROY	6

extern GSnmpEnum const snmp_view_based_acm_mib_enums_vacmViewTreeFamilyStatus[];


/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmContextEntry.
 */

typedef struct {
    guchar   vacmContextName[32];
    gsize    _vacmContextNameLength;
} snmp_view_based_acm_mib_vacmContextEntry_t;

extern int
snmp_view_based_acm_mib_get_vacmContextTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmContextEntry_t ***vacmContextEntry);

extern void
snmp_view_based_acm_mib_free_vacmContextTable(snmp_view_based_acm_mib_vacmContextEntry_t **vacmContextEntry);

extern snmp_view_based_acm_mib_vacmContextEntry_t *
snmp_view_based_acm_mib_new_vacmContextEntry();

extern int
snmp_view_based_acm_mib_get_vacmContextEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmContextEntry_t **vacmContextEntry);

extern void
snmp_view_based_acm_mib_free_vacmContextEntry(snmp_view_based_acm_mib_vacmContextEntry_t *vacmContextEntry);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmSecurityToGroupEntry.
 */

typedef struct {
    gint32   vacmSecurityModel;
    guchar   vacmSecurityName[32];
    gsize    _vacmSecurityNameLength;
    guchar   *vacmGroupName;
    gsize    _vacmGroupNameLength;
    gint32   *vacmSecurityToGroupStorageType;
    gint32   *vacmSecurityToGroupStatus;
} snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t;

extern int
snmp_view_based_acm_mib_get_vacmSecurityToGroupTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t ***vacmSecurityToGroupEntry);

extern void
snmp_view_based_acm_mib_free_vacmSecurityToGroupTable(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmSecurityToGroupEntry);

extern snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *
snmp_view_based_acm_mib_new_vacmSecurityToGroupEntry();

extern int
snmp_view_based_acm_mib_get_vacmSecurityToGroupEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmSecurityToGroupEntry);

extern int
snmp_view_based_acm_mib_set_vacmSecurityToGroupEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry);

extern void
snmp_view_based_acm_mib_free_vacmSecurityToGroupEntry(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmAccessEntry.
 */

typedef struct {
    guchar   vacmGroupName[32];
    gsize    _vacmGroupNameLength;
    guchar   vacmAccessContextPrefix[32];
    gsize    _vacmAccessContextPrefixLength;
    gint32   vacmAccessSecurityModel;
    gint32   vacmAccessSecurityLevel;
    gint32   *vacmAccessContextMatch;
    guchar   *vacmAccessReadViewName;
    gsize    _vacmAccessReadViewNameLength;
    guchar   *vacmAccessWriteViewName;
    gsize    _vacmAccessWriteViewNameLength;
    guchar   *vacmAccessNotifyViewName;
    gsize    _vacmAccessNotifyViewNameLength;
    gint32   *vacmAccessStorageType;
    gint32   *vacmAccessStatus;
} snmp_view_based_acm_mib_vacmAccessEntry_t;

extern int
snmp_view_based_acm_mib_get_vacmAccessTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmAccessEntry_t ***vacmAccessEntry);

extern void
snmp_view_based_acm_mib_free_vacmAccessTable(snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessEntry);

extern snmp_view_based_acm_mib_vacmAccessEntry_t *
snmp_view_based_acm_mib_new_vacmAccessEntry();

extern int
snmp_view_based_acm_mib_get_vacmAccessEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessEntry);

extern int
snmp_view_based_acm_mib_set_vacmAccessEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry);

extern void
snmp_view_based_acm_mib_free_vacmAccessEntry(snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmMIBViews.
 */

typedef struct {
    gint32   *vacmViewSpinLock;
} snmp_view_based_acm_mib_vacmMIBViews_t;

extern snmp_view_based_acm_mib_vacmMIBViews_t *
snmp_view_based_acm_mib_new_vacmMIBViews();

extern int
snmp_view_based_acm_mib_get_vacmMIBViews(GSnmpSession *s, snmp_view_based_acm_mib_vacmMIBViews_t **vacmMIBViews);

extern int
snmp_view_based_acm_mib_set_vacmMIBViews(GSnmpSession *s, snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews);

extern void
snmp_view_based_acm_mib_free_vacmMIBViews(snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmViewTreeFamilyEntry.
 */

typedef struct {
    guchar   vacmViewTreeFamilyViewName[32];
    gsize    _vacmViewTreeFamilyViewNameLength;
    guint32  vacmViewTreeFamilySubtree[128];
    gsize    _vacmViewTreeFamilySubtreeLength;
    guchar   *vacmViewTreeFamilyMask;
    gsize    _vacmViewTreeFamilyMaskLength;
    gint32   *vacmViewTreeFamilyType;
    gint32   *vacmViewTreeFamilyStorageType;
    gint32   *vacmViewTreeFamilyStatus;
} snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t;

extern int
snmp_view_based_acm_mib_get_vacmViewTreeFamilyTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t ***vacmViewTreeFamilyEntry);

extern void
snmp_view_based_acm_mib_free_vacmViewTreeFamilyTable(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTreeFamilyEntry);

extern snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *
snmp_view_based_acm_mib_new_vacmViewTreeFamilyEntry();

extern int
snmp_view_based_acm_mib_get_vacmViewTreeFamilyEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTreeFamilyEntry);

extern int
snmp_view_based_acm_mib_set_vacmViewTreeFamilyEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry);

extern void
snmp_view_based_acm_mib_free_vacmViewTreeFamilyEntry(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry);


#endif /* _SNMP_VIEW_BASED_ACM_MIB_H_ */
