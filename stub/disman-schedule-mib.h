/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.16 for the scli package.
 *
 * Derived from DISMAN-SCHEDULE-MIB:
 *   This MIB module defines a MIB which provides mechanisms to
 *   schedule SNMP set operations periodically or at specific
 *   points in time.
 *
 * Revision 2001-04-03 00:00:
 *   Revised version, published as RFC XXXX.
 *   
 *   This revision introduces a new object type called
 *   schedTriggers. Several clarifications have been added
 *   to remove ambiguities that were discovered and reported
 *   by implementors.
 *
 * Revision 1998-11-17 18:00:
 *   Initial version, published as RFC 2591.
 *
 * $Id$
 */

#ifndef _DISMAN_SCHEDULE_MIB_H_
#define _DISMAN_SCHEDULE_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define DISMAN_SCHEDULE_MIB_SCHEDTYPE_PERIODIC	1
#define DISMAN_SCHEDULE_MIB_SCHEDTYPE_CALENDAR	2
#define DISMAN_SCHEDULE_MIB_SCHEDTYPE_ONESHOT	3

extern GSnmpEnum const disman_schedule_mib_enums_schedType[];

#define DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_ENABLED	1
#define DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_DISABLED	2

extern GSnmpEnum const disman_schedule_mib_enums_schedAdminStatus[];

#define DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_ENABLED	1
#define DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_DISABLED	2
#define DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_FINISHED	3

extern GSnmpEnum const disman_schedule_mib_enums_schedOperStatus[];

#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NORESPONSE	-1
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOERROR	0
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_TOOBIG	1
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOSUCHNAME	2
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_BADVALUE	3
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_READONLY	4
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_GENERR	5
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOACCESS	6
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGTYPE	7
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGLENGTH	8
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGENCODING	9
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGVALUE	10
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOCREATION	11
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_INCONSISTENTVALUE	12
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_RESOURCEUNAVAILABLE	13
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_COMMITFAILED	14
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_UNDOFAILED	15
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_AUTHORIZATIONERROR	16
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOTWRITABLE	17
#define DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_INCONSISTENTNAME	18

extern GSnmpEnum const disman_schedule_mib_enums_schedLastFailure[];

#define DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_OTHER	1
#define DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_VOLATILE	2
#define DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_NONVOLATILE	3
#define DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_PERMANENT	4
#define DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_READONLY	5

extern GSnmpEnum const disman_schedule_mib_enums_schedStorageType[];

#define DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_ACTIVE	1
#define DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_NOTINSERVICE	2
#define DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_NOTREADY	3
#define DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_CREATEANDGO	4
#define DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_CREATEANDWAIT	5
#define DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_DESTROY	6

extern GSnmpEnum const disman_schedule_mib_enums_schedRowStatus[];


/*
 * C type definitions for DISMAN-SCHEDULE-MIB::schedObjects.
 */

typedef struct {
    guchar   *schedLocalTime;
} disman_schedule_mib_schedObjects_t;

extern disman_schedule_mib_schedObjects_t *
disman_schedule_mib_new_schedObjects();

extern int
disman_schedule_mib_get_schedObjects(GSnmpSession *s, disman_schedule_mib_schedObjects_t **schedObjects);

extern void
disman_schedule_mib_free_schedObjects(disman_schedule_mib_schedObjects_t *schedObjects);

/*
 * C type definitions for DISMAN-SCHEDULE-MIB::schedEntry.
 */

typedef struct {
    guchar   schedOwner[32];
    gsize    _schedOwnerLength;
    guchar   schedName[32];
    gsize    _schedNameLength;
    guchar   *schedDescr;
    gsize    _schedDescrLength;
    guint32  *schedInterval;
    guchar   *schedWeekDay;
    gsize    _schedWeekDayLength;
    guchar   *schedMonth;
    gsize    _schedMonthLength;
    guchar   *schedDay;
    gsize    _schedDayLength;
    guchar   *schedHour;
    gsize    _schedHourLength;
    guchar   *schedMinute;
    gsize    _schedMinuteLength;
    guchar   *schedContextName;
    gsize    _schedContextNameLength;
    guint32  *schedVariable;
    gsize    _schedVariableLength;
    gint32   *schedValue;
    gint32   *schedType;
    gint32   *schedAdminStatus;
    gint32   *schedOperStatus;
    guint32  *schedFailures;
    gint32   *schedLastFailure;
    guchar   *schedLastFailed;
    gsize    _schedLastFailedLength;
    gint32   *schedStorageType;
    gint32   *schedRowStatus;
    guint32  *schedTriggers;
} disman_schedule_mib_schedEntry_t;

extern int
disman_schedule_mib_get_schedTable(GSnmpSession *s, disman_schedule_mib_schedEntry_t ***schedEntry);

extern void
disman_schedule_mib_free_schedTable(disman_schedule_mib_schedEntry_t **schedEntry);

extern disman_schedule_mib_schedEntry_t *
disman_schedule_mib_new_schedEntry();

extern int
disman_schedule_mib_get_schedEntry(GSnmpSession *s, disman_schedule_mib_schedEntry_t **schedEntry);

extern int
disman_schedule_mib_set_schedEntry(GSnmpSession *s, disman_schedule_mib_schedEntry_t *schedEntry);

extern void
disman_schedule_mib_free_schedEntry(disman_schedule_mib_schedEntry_t *schedEntry);


#endif /* _DISMAN_SCHEDULE_MIB_H_ */
