/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli SNMP-NOTIFICATION-MIB
 *
 * Derived from SNMP-NOTIFICATION-MIB:
 *   This MIB module defines MIB objects which provide
 *   mechanisms to remotely configure the parameters
 *   used by an SNMP entity for the generation of
 *   notifications.
 *   
 *   Copyright (C) The Internet Society (2002). This
 *   version of this MIB module is part of RFC 3413;
 *   see the RFC itself for full legal notices.
 *
 * Revision 2002-10-14 00:00:
 *   Clarifications, published as
 *   RFC 3413.
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

#ifndef _SNMP_NOTIFICATION_MIB_H_
#define _SNMP_NOTIFICATION_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYTYPE_TRAP   1
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYTYPE_INFORM 2

extern GNetSnmpEnum const snmp_notification_mib_enums_snmpNotifyType[];

#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERTYPE_INCLUDED 1
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERTYPE_EXCLUDED 2

extern GNetSnmpEnum const snmp_notification_mib_enums_snmpNotifyFilterType[];


/*
 * C type definitions for SNMP-NOTIFICATION-MIB::snmpNotifyEntry.
 */

#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYTAG         (1 << 0) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYTYPE        (1 << 1) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYSTORAGETYPE (1 << 2) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS   (1 << 3) 

typedef struct {
    guchar   snmpNotifyName[32];         /* na */
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYNAMEMINLENGTH 1
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYNAMEMAXLENGTH 32
    guint16  _snmpNotifyNameLength;
    guchar   *snmpNotifyTag;             /* rw SNMP-TARGET-MIB::SnmpTagValue */
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYTAGMINLENGTH 0
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYTAGMAXLENGTH 255
    guint16  _snmpNotifyTagLength;
    gint32   *snmpNotifyType;            /* rw */
    gint32   *snmpNotifyStorageType;     /* rw SNMPv2-TC::StorageType */
    gint32   *snmpNotifyRowStatus;       /* rw SNMPv2-TC::RowStatus */
} snmp_notification_mib_snmpNotifyEntry_t;

extern void
snmp_notification_mib_get_snmpNotifyTable(GNetSnmp *s, snmp_notification_mib_snmpNotifyEntry_t ***snmpNotifyEntry, gint64 mask);

extern void
snmp_notification_mib_free_snmpNotifyTable(snmp_notification_mib_snmpNotifyEntry_t **snmpNotifyEntry);

extern snmp_notification_mib_snmpNotifyEntry_t *
snmp_notification_mib_new_snmpNotifyEntry(void);

extern void
snmp_notification_mib_get_snmpNotifyEntry(GNetSnmp *s, snmp_notification_mib_snmpNotifyEntry_t **snmpNotifyEntry, guchar *snmpNotifyName, guint16 _snmpNotifyNameLength, gint64 mask);

extern void
snmp_notification_mib_set_snmpNotifyEntry(GNetSnmp *s, snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry, gint64 mask);

extern void
snmp_notification_mib_free_snmpNotifyEntry(snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry);

/*
 * C type definitions for SNMP-NOTIFICATION-MIB::snmpNotifyFilterProfileEntry.
 */

#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILENAME      (1 << 0) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILESTORTYPE  (1 << 1) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS (1 << 2) 

typedef struct {
    guchar   snmpTargetParamsName[32];              /* na */
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSNAMEMINLENGTH 1
#define SNMP_TARGET_MIB_SNMPTARGETPARAMSNAMEMAXLENGTH 32
    guint16  _snmpTargetParamsNameLength;
    guchar   *snmpNotifyFilterProfileName;          /* rw */
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILENAMEMINLENGTH 1
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILENAMEMAXLENGTH 32
    guint16  _snmpNotifyFilterProfileNameLength;
    gint32   *snmpNotifyFilterProfileStorType;      /* rw SNMPv2-TC::StorageType */
    gint32   *snmpNotifyFilterProfileRowStatus;     /* rw SNMPv2-TC::RowStatus */
} snmp_notification_mib_snmpNotifyFilterProfileEntry_t;

extern void
snmp_notification_mib_get_snmpNotifyFilterProfileTable(GNetSnmp *s, snmp_notification_mib_snmpNotifyFilterProfileEntry_t ***snmpNotifyFilterProfileEntry, gint64 mask);

extern void
snmp_notification_mib_free_snmpNotifyFilterProfileTable(snmp_notification_mib_snmpNotifyFilterProfileEntry_t **snmpNotifyFilterProfileEntry);

extern snmp_notification_mib_snmpNotifyFilterProfileEntry_t *
snmp_notification_mib_new_snmpNotifyFilterProfileEntry(void);

extern void
snmp_notification_mib_get_snmpNotifyFilterProfileEntry(GNetSnmp *s, snmp_notification_mib_snmpNotifyFilterProfileEntry_t **snmpNotifyFilterProfileEntry, guchar *snmpTargetParamsName, guint16 _snmpTargetParamsNameLength, gint64 mask);

extern void
snmp_notification_mib_set_snmpNotifyFilterProfileEntry(GNetSnmp *s, snmp_notification_mib_snmpNotifyFilterProfileEntry_t *snmpNotifyFilterProfileEntry, gint64 mask);

extern void
snmp_notification_mib_free_snmpNotifyFilterProfileEntry(snmp_notification_mib_snmpNotifyFilterProfileEntry_t *snmpNotifyFilterProfileEntry);

/*
 * C type definitions for SNMP-NOTIFICATION-MIB::snmpNotifyFilterEntry.
 */

#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERMASK        (1 << 0) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERTYPE        (1 << 1) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSTORAGETYPE (1 << 2) 
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS   (1 << 3) 

typedef struct {
    guchar   snmpNotifyFilterProfileName[32];  /* rw */
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILENAMEMINLENGTH 1
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILENAMEMAXLENGTH 32
    guint16  _snmpNotifyFilterProfileNameLength;
    guint32  snmpNotifyFilterSubtree[117];      /* na ObjectIdentifier */
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSUBTREEMINLENGTH 0
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSUBTREEMAXLENGTH 117
    guint16  _snmpNotifyFilterSubtreeLength;
    guchar   *snmpNotifyFilterMask;            /* rw */
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERMASKMINLENGTH 0
#define SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERMASKMAXLENGTH 16
    guint16  _snmpNotifyFilterMaskLength;
    gint32   *snmpNotifyFilterType;            /* rw */
    gint32   *snmpNotifyFilterStorageType;     /* rw SNMPv2-TC::StorageType */
    gint32   *snmpNotifyFilterRowStatus;       /* rw SNMPv2-TC::RowStatus */
} snmp_notification_mib_snmpNotifyFilterEntry_t;

extern void
snmp_notification_mib_get_snmpNotifyFilterTable(GNetSnmp *s, snmp_notification_mib_snmpNotifyFilterEntry_t ***snmpNotifyFilterEntry, gint64 mask);

extern void
snmp_notification_mib_free_snmpNotifyFilterTable(snmp_notification_mib_snmpNotifyFilterEntry_t **snmpNotifyFilterEntry);

extern snmp_notification_mib_snmpNotifyFilterEntry_t *
snmp_notification_mib_new_snmpNotifyFilterEntry(void);

extern void
snmp_notification_mib_get_snmpNotifyFilterEntry(GNetSnmp *s, snmp_notification_mib_snmpNotifyFilterEntry_t **snmpNotifyFilterEntry, guchar *snmpNotifyFilterProfileName, guint16 _snmpNotifyFilterProfileNameLength, guint32 *snmpNotifyFilterSubtree, guint16 _snmpNotifyFilterSubtreeLength, gint64 mask);

extern void
snmp_notification_mib_set_snmpNotifyFilterEntry(GNetSnmp *s, snmp_notification_mib_snmpNotifyFilterEntry_t *snmpNotifyFilterEntry, gint64 mask);

extern void
snmp_notification_mib_free_snmpNotifyFilterEntry(snmp_notification_mib_snmpNotifyFilterEntry_t *snmpNotifyFilterEntry);


G_END_DECLS

#endif /* _SNMP_NOTIFICATION_MIB_H_ */
