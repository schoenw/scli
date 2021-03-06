/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli SNMP-VIEW-BASED-ACM-MIB
 *
 * Derived from SNMP-VIEW-BASED-ACM-MIB:
 *   The management information definitions for the
 *   View-based Access Control Model for SNMP.
 *   
 *   Copyright (C) The Internet Society (2002). This
 *   version of this MIB module is part of RFC 3415;
 *   see the RFC itself for full legal notices.
 *
 * Revision 2002-10-16 00:00:
 *   Clarifications, published as RFC3415
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

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH_EXACT  1
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH_PREFIX 2

extern GNetSnmpEnum const snmp_view_based_acm_mib_enums_vacmAccessContextMatch[];

#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_INCLUDED 1
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_EXCLUDED 2

extern GNetSnmpEnum const snmp_view_based_acm_mib_enums_vacmViewTreeFamilyType[];


/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmContextEntry.
 */

#define SNMP_VIEW_BASED_ACM_MIB_VACMCONTEXTNAME (1 << 0) 

typedef struct {
    guchar   vacmContextName[32];  /* ro */
#define SNMP_VIEW_BASED_ACM_MIB_VACMCONTEXTNAMEMINLENGTH 0
#define SNMP_VIEW_BASED_ACM_MIB_VACMCONTEXTNAMEMAXLENGTH 32
    guint16  _vacmContextNameLength;
} snmp_view_based_acm_mib_vacmContextEntry_t;

extern void
snmp_view_based_acm_mib_get_vacmContextTable(GNetSnmp *s, snmp_view_based_acm_mib_vacmContextEntry_t ***vacmContextEntry, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmContextTable(snmp_view_based_acm_mib_vacmContextEntry_t **vacmContextEntry);

extern snmp_view_based_acm_mib_vacmContextEntry_t *
snmp_view_based_acm_mib_new_vacmContextEntry(void);

extern void
snmp_view_based_acm_mib_get_vacmContextEntry(GNetSnmp *s, snmp_view_based_acm_mib_vacmContextEntry_t **vacmContextEntry, guchar *vacmContextName, guint16 _vacmContextNameLength, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmContextEntry(snmp_view_based_acm_mib_vacmContextEntry_t *vacmContextEntry);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmSecurityToGroupEntry.
 */

#define SNMP_VIEW_BASED_ACM_MIB_VACMGROUPNAME                  (1 << 0) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTORAGETYPE (1 << 1) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS      (1 << 2) 

typedef struct {
    gint32   vacmSecurityModel;                   /* na */
    guchar   vacmSecurityName[32];                /* na */
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYNAMEMINLENGTH 1
#define SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYNAMEMAXLENGTH 32
    guint16  _vacmSecurityNameLength;
    guchar   *vacmGroupName;                      /* rw */
#define SNMP_VIEW_BASED_ACM_MIB_VACMGROUPNAMEMINLENGTH 1
#define SNMP_VIEW_BASED_ACM_MIB_VACMGROUPNAMEMAXLENGTH 32
    guint16  _vacmGroupNameLength;
    gint32   *vacmSecurityToGroupStorageType;     /* rw SNMPv2-TC::StorageType */
    gint32   *vacmSecurityToGroupStatus;          /* rw SNMPv2-TC::RowStatus */
} snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t;

extern void
snmp_view_based_acm_mib_get_vacmSecurityToGroupTable(GNetSnmp *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t ***vacmSecurityToGroupEntry, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmSecurityToGroupTable(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmSecurityToGroupEntry);

extern snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *
snmp_view_based_acm_mib_new_vacmSecurityToGroupEntry(void);

extern void
snmp_view_based_acm_mib_get_vacmSecurityToGroupEntry(GNetSnmp *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmSecurityToGroupEntry, gint32 vacmSecurityModel, guchar *vacmSecurityName, guint16 _vacmSecurityNameLength, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_set_vacmSecurityToGroupEntry(GNetSnmp *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmSecurityToGroupEntry(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmAccessEntry.
 */

#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH   (1 << 0) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSREADVIEWNAME   (1 << 1) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSWRITEVIEWNAME  (1 << 2) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSNOTIFYVIEWNAME (1 << 3) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTORAGETYPE    (1 << 4) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS         (1 << 5) 

typedef struct {
    guchar   vacmGroupName[32];             /* rw */
#define SNMP_VIEW_BASED_ACM_MIB_VACMGROUPNAMEMINLENGTH 1
#define SNMP_VIEW_BASED_ACM_MIB_VACMGROUPNAMEMAXLENGTH 32
    guint16  _vacmGroupNameLength;
    guchar   vacmAccessContextPrefix[32];   /* na */
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTPREFIXMINLENGTH 0
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTPREFIXMAXLENGTH 32
    guint16  _vacmAccessContextPrefixLength;
    gint32   vacmAccessSecurityModel;       /* na SNMP-FRAMEWORK-MIB::SnmpSecurityModel */
    gint32   vacmAccessSecurityLevel;       /* na SNMP-FRAMEWORK-MIB::SnmpSecurityLevel */
    gint32   *vacmAccessContextMatch;       /* rw */
    guchar   *vacmAccessReadViewName;       /* rw */
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSREADVIEWNAMEMINLENGTH 0
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSREADVIEWNAMEMAXLENGTH 32
    guint16  _vacmAccessReadViewNameLength;
    guchar   *vacmAccessWriteViewName;      /* rw */
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSWRITEVIEWNAMEMINLENGTH 0
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSWRITEVIEWNAMEMAXLENGTH 32
    guint16  _vacmAccessWriteViewNameLength;
    guchar   *vacmAccessNotifyViewName;     /* rw */
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSNOTIFYVIEWNAMEMINLENGTH 0
#define SNMP_VIEW_BASED_ACM_MIB_VACMACCESSNOTIFYVIEWNAMEMAXLENGTH 32
    guint16  _vacmAccessNotifyViewNameLength;
    gint32   *vacmAccessStorageType;        /* rw SNMPv2-TC::StorageType */
    gint32   *vacmAccessStatus;             /* rw SNMPv2-TC::RowStatus */
} snmp_view_based_acm_mib_vacmAccessEntry_t;

extern void
snmp_view_based_acm_mib_get_vacmAccessTable(GNetSnmp *s, snmp_view_based_acm_mib_vacmAccessEntry_t ***vacmAccessEntry, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmAccessTable(snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessEntry);

extern snmp_view_based_acm_mib_vacmAccessEntry_t *
snmp_view_based_acm_mib_new_vacmAccessEntry(void);

extern void
snmp_view_based_acm_mib_get_vacmAccessEntry(GNetSnmp *s, snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessEntry, guchar *vacmGroupName, guint16 _vacmGroupNameLength, guchar *vacmAccessContextPrefix, guint16 _vacmAccessContextPrefixLength, gint32 vacmAccessSecurityModel, gint32 vacmAccessSecurityLevel, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_set_vacmAccessEntry(GNetSnmp *s, snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmAccessEntry(snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmMIBViews.
 */

#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWSPINLOCK (1 << 0) 

typedef struct {
    gint32   *vacmViewSpinLock;     /* rw SNMPv2-TC::TestAndIncr */
} snmp_view_based_acm_mib_vacmMIBViews_t;

extern snmp_view_based_acm_mib_vacmMIBViews_t *
snmp_view_based_acm_mib_new_vacmMIBViews(void);

extern void
snmp_view_based_acm_mib_get_vacmMIBViews(GNetSnmp *s, snmp_view_based_acm_mib_vacmMIBViews_t **vacmMIBViews, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_set_vacmMIBViews(GNetSnmp *s, snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmMIBViews(snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews);

/*
 * C type definitions for SNMP-VIEW-BASED-ACM-MIB::vacmViewTreeFamilyEntry.
 */

#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYMASK        (1 << 0) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE        (1 << 1) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTORAGETYPE (1 << 2) 
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS      (1 << 3) 

typedef struct {
    guchar   vacmViewTreeFamilyViewName[32];     /* na */
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYVIEWNAMEMINLENGTH 1
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYVIEWNAMEMAXLENGTH 32
    guint16  _vacmViewTreeFamilyViewNameLength;
    guint32  vacmViewTreeFamilySubtree[116];      /* na ObjectIdentifier */
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSUBTREEMINLENGTH 0
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSUBTREEMAXLENGTH 116
    guint16  _vacmViewTreeFamilySubtreeLength;
    guchar   *vacmViewTreeFamilyMask;            /* rw */
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYMASKMINLENGTH 0
#define SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYMASKMAXLENGTH 16
    guint16  _vacmViewTreeFamilyMaskLength;
    gint32   *vacmViewTreeFamilyType;            /* rw */
    gint32   *vacmViewTreeFamilyStorageType;     /* rw SNMPv2-TC::StorageType */
    gint32   *vacmViewTreeFamilyStatus;          /* rw SNMPv2-TC::RowStatus */
} snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t;

extern void
snmp_view_based_acm_mib_get_vacmViewTreeFamilyTable(GNetSnmp *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t ***vacmViewTreeFamilyEntry, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmViewTreeFamilyTable(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTreeFamilyEntry);

extern snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *
snmp_view_based_acm_mib_new_vacmViewTreeFamilyEntry(void);

extern void
snmp_view_based_acm_mib_get_vacmViewTreeFamilyEntry(GNetSnmp *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTreeFamilyEntry, guchar *vacmViewTreeFamilyViewName, guint16 _vacmViewTreeFamilyViewNameLength, guint32 *vacmViewTreeFamilySubtree, guint16 _vacmViewTreeFamilySubtreeLength, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_set_vacmViewTreeFamilyEntry(GNetSnmp *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry, gint64 mask, GError **error);

extern void
snmp_view_based_acm_mib_free_vacmViewTreeFamilyEntry(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry);


G_END_DECLS

#endif /* _SNMP_VIEW_BASED_ACM_MIB_H_ */
