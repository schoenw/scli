/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from DISMAN-SCHEDULE-MIB:
 *   This MIB module defines a MIB which provides mechanisms
 *   to schedule SNMP set operations periodically or at
 *   specific points in time.
 *
 * Revision 1998-11-17 18:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#include "disman-schedule-mib.h"

stls_table_t const disman_schedule_mib_enums_schedType[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDTYPE_PERIODIC,	"periodic" },
    { DISMAN_SCHEDULE_MIB_SCHEDTYPE_CALENDAR,	"calendar" },
    { DISMAN_SCHEDULE_MIB_SCHEDTYPE_ONESHOT,	"oneshot" },
    { 0, NULL }
};

stls_table_t const disman_schedule_mib_enums_schedAdminStatus[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_ENABLED,	"enabled" },
    { DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_DISABLED,	"disabled" },
    { 0, NULL }
};

stls_table_t const disman_schedule_mib_enums_schedOperStatus[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_ENABLED,	"enabled" },
    { DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_DISABLED,	"disabled" },
    { DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_FINISHED,	"finished" },
    { 0, NULL }
};

stls_table_t const disman_schedule_mib_enums_schedLastFailure[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NORESPONSE,	"noResponse" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOERROR,	"noError" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_TOOBIG,	"tooBig" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOSUCHNAME,	"noSuchName" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_BADVALUE,	"badValue" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_READONLY,	"readOnly" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_GENERR,	"genErr" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOACCESS,	"noAccess" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGTYPE,	"wrongType" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGLENGTH,	"wrongLength" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGENCODING,	"wrongEncoding" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGVALUE,	"wrongValue" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOCREATION,	"noCreation" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_INCONSISTENTVALUE,	"inconsistentValue" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_RESOURCEUNAVAILABLE,	"resourceUnavailable" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_COMMITFAILED,	"commitFailed" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_UNDOFAILED,	"undoFailed" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_AUTHORIZATIONERROR,	"authorizationError" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOTWRITABLE,	"notWritable" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_INCONSISTENTNAME,	"inconsistentName" },
    { 0, NULL }
};

stls_table_t const disman_schedule_mib_enums_schedStorageType[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_OTHER,	"other" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_VOLATILE,	"volatile" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_NONVOLATILE,	"nonVolatile" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_PERMANENT,	"permanent" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_READONLY,	"readOnly" },
    { 0, NULL }
};

stls_table_t const disman_schedule_mib_enums_schedRowStatus[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_ACTIVE,	"active" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_NOTINSERVICE,	"notInService" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_NOTREADY,	"notReady" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_CREATEANDGO,	"createAndGo" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_CREATEANDWAIT,	"createAndWait" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};


schedObjects_t *
disman_schedule_mib_new_schedObjects()
{
    schedObjects_t *schedObjects;

    schedObjects = (schedObjects_t *) g_malloc0(sizeof(schedObjects_t) + sizeof(gpointer));
    return schedObjects;
}

static schedObjects_t *
assign_schedObjects(GSList *vbl)
{
    GSList *elem;
    schedObjects_t *schedObjects;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 63, 1};

    schedObjects = disman_schedule_mib_new_schedObjects();
    if (! schedObjects) {
        return NULL;
    }

    p = (char *) schedObjects + sizeof(schedObjects_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 9 && vb->id[8] == 1) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedObjects->schedLocalTime = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedLocalTime");
            }
        }
    }

    return schedObjects;
}

int
disman_schedule_mib_get_schedObjects(host_snmp *s, schedObjects_t **schedObjects)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 63, 1, 0};

    *schedObjects = NULL;

    base[8] = 1; stls_vbl_add_null(&in, base, 9);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *schedObjects = assign_schedObjects(out);

    return 0;
}

void
disman_schedule_mib_free_schedObjects(schedObjects_t *schedObjects)
{
    GSList *vbl;
    char *p;

    if (schedObjects) {
        p = (char *) schedObjects + sizeof(schedObjects_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(schedObjects);
    }
}

schedEntry_t *
disman_schedule_mib_new_schedEntry()
{
    schedEntry_t *schedEntry;

    schedEntry = (schedEntry_t *) g_malloc0(sizeof(schedEntry_t) + sizeof(gpointer));
    return schedEntry;
}

static int
unpack_schedEntry(GSnmpVarBind *vb, schedEntry_t *schedEntry)
{
    int i, len, idx = 11;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        schedEntry->schedOwner[i] = vb->id[idx++];
    }
    schedEntry->_schedOwnerLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        schedEntry->schedName[i] = vb->id[idx++];
    }
    schedEntry->_schedNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static schedEntry_t *
assign_schedEntry(GSList *vbl)
{
    GSList *elem;
    schedEntry_t *schedEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 63, 1, 2, 1};

    schedEntry = disman_schedule_mib_new_schedEntry();
    if (! schedEntry) {
        return NULL;
    }

    p = (char *) schedEntry + sizeof(schedEntry_t);
    * (GSList **) p = vbl;

    if (unpack_schedEntry((GSnmpVarBind *) vbl->data, schedEntry) < 0) {
        g_warning("illegal schedEntry instance identifier");
        g_free(schedEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedDescrLength = vb->syntax_len;
                schedEntry->schedDescr = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedDescr");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                schedEntry->schedInterval = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for schedInterval");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedWeekDayLength = vb->syntax_len;
                schedEntry->schedWeekDay = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedWeekDay");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedMonthLength = vb->syntax_len;
                schedEntry->schedMonth = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedMonth");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 7) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedDayLength = vb->syntax_len;
                schedEntry->schedDay = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedDay");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 8) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedHourLength = vb->syntax_len;
                schedEntry->schedHour = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedHour");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 9) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedMinuteLength = vb->syntax_len;
                schedEntry->schedMinute = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedMinute");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 10) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedContextNameLength = vb->syntax_len;
                schedEntry->schedContextName = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedContextName");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 11) {
            if (vb->type == G_SNMP_OBJECT_ID) {
                schedEntry->_schedVariableLength = vb->syntax_len / sizeof(guint32);
                schedEntry->schedVariable = vb->syntax.ui32;
            } else {
                g_warning("illegal type for schedVariable");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 12) {
            if (vb->type == G_SNMP_INTEGER32) {
                schedEntry->schedValue = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for schedValue");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 13) {
            if (vb->type == G_SNMP_INTEGER32) {
                schedEntry->schedType = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for schedType");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 14) {
            if (vb->type == G_SNMP_INTEGER32) {
                schedEntry->schedAdminStatus = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for schedAdminStatus");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 15) {
            if (vb->type == G_SNMP_INTEGER32) {
                schedEntry->schedOperStatus = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for schedOperStatus");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 16) {
            if (vb->type == G_SNMP_COUNTER32) {
                schedEntry->schedFailures = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for schedFailures");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 17) {
            if (vb->type == G_SNMP_INTEGER32) {
                schedEntry->schedLastFailure = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for schedLastFailure");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 18) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                schedEntry->_schedLastFailedLength = vb->syntax_len;
                schedEntry->schedLastFailed = vb->syntax.uc;
            } else {
                g_warning("illegal type for schedLastFailed");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 19) {
            if (vb->type == G_SNMP_INTEGER32) {
                schedEntry->schedStorageType = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for schedStorageType");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 20) {
            if (vb->type == G_SNMP_INTEGER32) {
                schedEntry->schedRowStatus = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for schedRowStatus");
            }
        }
    }

    return schedEntry;
}

int
disman_schedule_mib_get_schedTable(host_snmp *s, schedEntry_t ***schedEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 63, 1, 2, 1, 0};

    *schedEntry = NULL;

    base[10] = 3; stls_vbl_add_null(&in, base, 11);
    base[10] = 4; stls_vbl_add_null(&in, base, 11);
    base[10] = 5; stls_vbl_add_null(&in, base, 11);
    base[10] = 6; stls_vbl_add_null(&in, base, 11);
    base[10] = 7; stls_vbl_add_null(&in, base, 11);
    base[10] = 8; stls_vbl_add_null(&in, base, 11);
    base[10] = 9; stls_vbl_add_null(&in, base, 11);
    base[10] = 10; stls_vbl_add_null(&in, base, 11);
    base[10] = 11; stls_vbl_add_null(&in, base, 11);
    base[10] = 12; stls_vbl_add_null(&in, base, 11);
    base[10] = 13; stls_vbl_add_null(&in, base, 11);
    base[10] = 14; stls_vbl_add_null(&in, base, 11);
    base[10] = 15; stls_vbl_add_null(&in, base, 11);
    base[10] = 16; stls_vbl_add_null(&in, base, 11);
    base[10] = 17; stls_vbl_add_null(&in, base, 11);
    base[10] = 18; stls_vbl_add_null(&in, base, 11);
    base[10] = 19; stls_vbl_add_null(&in, base, 11);
    base[10] = 20; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *schedEntry = (schedEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(schedEntry_t *));
    if (! *schedEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*schedEntry)[i] = assign_schedEntry(row->data);
    }

    return 0;
}

void
disman_schedule_mib_free_schedEntry(schedEntry_t *schedEntry)
{
    GSList *vbl;
    char *p;

    if (schedEntry) {
        p = (char *) schedEntry + sizeof(schedEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(schedEntry);
    }
}

void
disman_schedule_mib_free_schedTable(schedEntry_t **schedEntry)
{
    int i;

    if (schedEntry) {
        for (i = 0; schedEntry[i]; i++) {
            disman_schedule_mib_free_schedEntry(schedEntry[i]);
        }
        g_free(schedEntry);
    }
}


