/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from DISMAN-SCHEDULE-MIB revision 1998-11-17 18:00.
 *
 * $Id$
 */

#ifndef _DISMAN_SCHEDULE_MIB_H_
#define _DISMAN_SCHEDULE_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

extern stls_table_t disman_schedule_mib_enums_schedType[];
extern stls_table_t disman_schedule_mib_enums_schedAdminStatus[];
extern stls_table_t disman_schedule_mib_enums_schedOperStatus[];
extern stls_table_t disman_schedule_mib_enums_schedLastFailure[];
extern stls_table_t disman_schedule_mib_enums_schedStorageType[];
extern stls_table_t disman_schedule_mib_enums_schedRowStatus[];

/*
 * C type definitions for DISMAN-SCHEDULE-MIB::schedObjects.
 */

typedef struct schedObjects {
    guchar   *schedLocalTime;
} schedObjects_t;

extern int
disman_schedule_mib_get_schedObjects(host_snmp *s, schedObjects_t **schedObjects);

extern void
disman_schedule_mib_free_schedObjects(schedObjects_t *schedObjects);

/*
 * C type definitions for DISMAN-SCHEDULE-MIB::schedEntry.
 */

typedef struct schedEntry {
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
} schedEntry_t;

extern int
disman_schedule_mib_get_schedEntry(host_snmp *s, schedEntry_t ***schedEntry);

extern void
disman_schedule_mib_free_schedEntry(schedEntry_t **schedEntry);


#endif /* _DISMAN_SCHEDULE_MIB_H_ */
