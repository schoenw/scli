/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli DISMAN-SCHEDULE-MIB
 *
 * Derived from DISMAN-SCHEDULE-MIB:
 *   This MIB module defines a MIB which provides mechanisms to
 *   schedule SNMP set operations periodically or at specific
 *   points in time.
 *
 * Revision 2002-01-07 00:00:
 *   Revised version, published as RFC 3231.
 *   
 *   This revision introduces a new object type called
 *   schedTriggers.  Created new conformance and compliance
 *   statements that take care of the new schedTriggers object.
 *   
 *   Several clarifications have been added to remove ambiguities
 *   that were discovered and reported by implementors.
 *
 * Revision 1998-11-17 18:00:
 *   Initial version, published as RFC 2591.
 *
 * $Id$
 */

#ifndef _DISMAN_SCHEDULE_MIB_H_
#define _DISMAN_SCHEDULE_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define DISMAN_SCHEDULE_MIB_SCHEDTYPE_PERIODIC 1
#define DISMAN_SCHEDULE_MIB_SCHEDTYPE_CALENDAR 2
#define DISMAN_SCHEDULE_MIB_SCHEDTYPE_ONESHOT  3

extern GNetSnmpEnum const disman_schedule_mib_enums_schedType[];

#define DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_ENABLED  1
#define DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_DISABLED 2

extern GNetSnmpEnum const disman_schedule_mib_enums_schedAdminStatus[];

#define DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_ENABLED  1
#define DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_DISABLED 2
#define DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_FINISHED 3

extern GNetSnmpEnum const disman_schedule_mib_enums_schedOperStatus[];

#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_NORESPONSE          -1
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_NOERROR             0
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_TOOBIG              1
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_NOSUCHNAME          2
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_BADVALUE            3
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_READONLY            4
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_GENERR              5
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_NOACCESS            6
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_WRONGTYPE           7
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_WRONGLENGTH         8
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_WRONGENCODING       9
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_WRONGVALUE          10
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_NOCREATION          11
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_INCONSISTENTVALUE   12
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_RESOURCEUNAVAILABLE 13
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_COMMITFAILED        14
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_UNDOFAILED          15
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_AUTHORIZATIONERROR  16
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_NOTWRITABLE         17
#define DISMAN_SCHEDULE_MIB_SNMPPDUERRORSTATUS_INCONSISTENTNAME    18

extern GNetSnmpEnum const disman_schedule_mib_enums_SnmpPduErrorStatus[];


/*
 * Tables to map notifications to strings and vice versa.
 */

#define DISMAN_SCHEDULE_MIB_SCHEDACTIONFAILURE	1,3,6,1,2,1,63,2,0,1

extern GNetSnmpIdentity const disman_schedule_mib_notifications[];

/*
 * C type definitions for DISMAN-SCHEDULE-MIB::schedObjects.
 */

#define DISMAN_SCHEDULE_MIB_SCHEDLOCALTIME (1 << 0) 

typedef struct {
    guchar   *schedLocalTime;     /* ro */
#define DISMAN_SCHEDULE_MIB_SCHEDLOCALTIMELENGTH 11
} disman_schedule_mib_schedObjects_t;

extern disman_schedule_mib_schedObjects_t *
disman_schedule_mib_new_schedObjects(void);

extern void
disman_schedule_mib_get_schedObjects(GNetSnmp *s, disman_schedule_mib_schedObjects_t **schedObjects, gint64 mask, GError **error);

extern void
disman_schedule_mib_free_schedObjects(disman_schedule_mib_schedObjects_t *schedObjects);

/*
 * C type definitions for DISMAN-SCHEDULE-MIB::schedEntry.
 */

#define DISMAN_SCHEDULE_MIB_SCHEDDESCR       (1 << 0) 
#define DISMAN_SCHEDULE_MIB_SCHEDINTERVAL    (1 << 1) 
#define DISMAN_SCHEDULE_MIB_SCHEDWEEKDAY     (1 << 2) 
#define DISMAN_SCHEDULE_MIB_SCHEDMONTH       (1 << 3) 
#define DISMAN_SCHEDULE_MIB_SCHEDDAY         (1 << 4) 
#define DISMAN_SCHEDULE_MIB_SCHEDHOUR        (1 << 5) 
#define DISMAN_SCHEDULE_MIB_SCHEDMINUTE      (1 << 6) 
#define DISMAN_SCHEDULE_MIB_SCHEDCONTEXTNAME (1 << 7) 
#define DISMAN_SCHEDULE_MIB_SCHEDVARIABLE    (1 << 8) 
#define DISMAN_SCHEDULE_MIB_SCHEDVALUE       (1 << 9) 
#define DISMAN_SCHEDULE_MIB_SCHEDTYPE        (1 << 10) 
#define DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS (1 << 11) 
#define DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS  (1 << 12) 
#define DISMAN_SCHEDULE_MIB_SCHEDFAILURES    (1 << 13) 
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE (1 << 14) 
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILED  (1 << 15) 
#define DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE (1 << 16) 
#define DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS   (1 << 17) 
#define DISMAN_SCHEDULE_MIB_SCHEDTRIGGERS    (1 << 18) 

typedef struct {
    guchar   schedOwner[32];        /* na */
#define DISMAN_SCHEDULE_MIB_SCHEDOWNERMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDOWNERMAXLENGTH 32
    guint16  _schedOwnerLength;
    guchar   schedName[32];         /* na */
#define DISMAN_SCHEDULE_MIB_SCHEDNAMEMINLENGTH 1
#define DISMAN_SCHEDULE_MIB_SCHEDNAMEMAXLENGTH 32
    guint16  _schedNameLength;
    guchar   *schedDescr;           /* rw SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define DISMAN_SCHEDULE_MIB_SCHEDDESCRMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDDESCRMAXLENGTH 255
    guint16  _schedDescrLength;
    guint32  *schedInterval;        /* rw Unsigned32 [seconds] */
    guchar   *schedWeekDay;         /* rw */
#define DISMAN_SCHEDULE_MIB_SCHEDWEEKDAYMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDWEEKDAYMAXLENGTH 1
    guint16  _schedWeekDayLength;
    guchar   *schedMonth;           /* rw */
#define DISMAN_SCHEDULE_MIB_SCHEDMONTHMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDMONTHMAXLENGTH 2
    guint16  _schedMonthLength;
    guchar   *schedDay;             /* rw */
#define DISMAN_SCHEDULE_MIB_SCHEDDAYMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDDAYMAXLENGTH 8
    guint16  _schedDayLength;
    guchar   *schedHour;            /* rw */
#define DISMAN_SCHEDULE_MIB_SCHEDHOURMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDHOURMAXLENGTH 3
    guint16  _schedHourLength;
    guchar   *schedMinute;          /* rw */
#define DISMAN_SCHEDULE_MIB_SCHEDMINUTEMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDMINUTEMAXLENGTH 8
    guint16  _schedMinuteLength;
    guchar   *schedContextName;     /* rw */
#define DISMAN_SCHEDULE_MIB_SCHEDCONTEXTNAMEMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDCONTEXTNAMEMAXLENGTH 32
    guint16  _schedContextNameLength;
    guint32  *schedVariable;        /* rw SNMPv2-TC::VariablePointer */
#define DISMAN_SCHEDULE_MIB_SCHEDVARIABLEMINLENGTH 0
#define DISMAN_SCHEDULE_MIB_SCHEDVARIABLEMAXLENGTH 128
    guint16  _schedVariableLength;
    gint32   *schedValue;           /* rw Integer32 */
    gint32   *schedType;            /* rw */
    gint32   *schedAdminStatus;     /* rw */
    gint32   *schedOperStatus;      /* ro */
    guint32  *schedFailures;        /* ro SNMPv2-SMI::Counter32 */
    gint32   *schedLastFailure;     /* ro DISMAN-SCHEDULE-MIB::SnmpPduErrorStatus */
    guchar   *schedLastFailed;      /* ro SNMPv2-TC::DateAndTime */
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILEDMINLENGTH 8
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILEDMAXLENGTH 11
    guint16  _schedLastFailedLength;
    gint32   *schedStorageType;     /* rw SNMPv2-TC::StorageType */
    gint32   *schedRowStatus;       /* rw SNMPv2-TC::RowStatus */
    guint32  *schedTriggers;        /* ro SNMPv2-SMI::Counter32 */
} disman_schedule_mib_schedEntry_t;

extern void
disman_schedule_mib_get_schedTable(GNetSnmp *s, disman_schedule_mib_schedEntry_t ***schedEntry, gint64 mask, GError **error);

extern void
disman_schedule_mib_free_schedTable(disman_schedule_mib_schedEntry_t **schedEntry);

extern disman_schedule_mib_schedEntry_t *
disman_schedule_mib_new_schedEntry(void);

extern void
disman_schedule_mib_get_schedEntry(GNetSnmp *s, disman_schedule_mib_schedEntry_t **schedEntry, guchar *schedOwner, guint16 _schedOwnerLength, guchar *schedName, guint16 _schedNameLength, gint64 mask, GError **error);

extern void
disman_schedule_mib_set_schedEntry(GNetSnmp *s, disman_schedule_mib_schedEntry_t *schedEntry, gint64 mask, GError **error);

extern void
disman_schedule_mib_free_schedEntry(disman_schedule_mib_schedEntry_t *schedEntry);


G_END_DECLS

#endif /* _DISMAN_SCHEDULE_MIB_H_ */
