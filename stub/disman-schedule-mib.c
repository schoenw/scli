/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
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

#include "disman-schedule-mib.h"

GSnmpEnum const disman_schedule_mib_enums_schedType[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDTYPE_PERIODIC, "periodic" },
    { DISMAN_SCHEDULE_MIB_SCHEDTYPE_CALENDAR, "calendar" },
    { DISMAN_SCHEDULE_MIB_SCHEDTYPE_ONESHOT,  "oneshot" },
    { 0, NULL }
};

GSnmpEnum const disman_schedule_mib_enums_schedAdminStatus[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_ENABLED,  "enabled" },
    { DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_DISABLED, "disabled" },
    { 0, NULL }
};

GSnmpEnum const disman_schedule_mib_enums_schedOperStatus[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_ENABLED,  "enabled" },
    { DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_DISABLED, "disabled" },
    { DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_FINISHED, "finished" },
    { 0, NULL }
};

GSnmpEnum const disman_schedule_mib_enums_schedLastFailure[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NORESPONSE,          "noResponse" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOERROR,             "noError" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_TOOBIG,              "tooBig" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOSUCHNAME,          "noSuchName" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_BADVALUE,            "badValue" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_READONLY,            "readOnly" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_GENERR,              "genErr" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOACCESS,            "noAccess" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGTYPE,           "wrongType" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGLENGTH,         "wrongLength" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGENCODING,       "wrongEncoding" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_WRONGVALUE,          "wrongValue" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOCREATION,          "noCreation" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_INCONSISTENTVALUE,   "inconsistentValue" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_RESOURCEUNAVAILABLE, "resourceUnavailable" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_COMMITFAILED,        "commitFailed" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_UNDOFAILED,          "undoFailed" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_AUTHORIZATIONERROR,  "authorizationError" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_NOTWRITABLE,         "notWritable" },
    { DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE_INCONSISTENTNAME,    "inconsistentName" },
    { 0, NULL }
};

GSnmpEnum const disman_schedule_mib_enums_schedStorageType[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_OTHER,       "other" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_VOLATILE,    "volatile" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_NONVOLATILE, "nonVolatile" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_PERMANENT,   "permanent" },
    { DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE_READONLY,    "readOnly" },
    { 0, NULL }
};

GSnmpEnum const disman_schedule_mib_enums_schedRowStatus[] = {
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_ACTIVE,        "active" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_NOTINSERVICE,  "notInService" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_NOTREADY,      "notReady" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_CREATEANDGO,   "createAndGo" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_CREATEANDWAIT, "createAndWait" },
    { DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS_DESTROY,       "destroy" },
    { 0, NULL }
};


static guint16 schedLocalTime_constraints[] = {11, 11, 0, 0};
static guint16 schedDescr_constraints[] = {0, 255, 0, 0};
static guint16 schedContextName_constraints[] = {0, 32, 0, 0};
static guint16 schedLastFailed_constraints[] = {8, 8, 11, 11, 0, 0};


static guint32 const schedObjects_oid[] = {1, 3, 6, 1, 2, 1, 63, 1};

static GSnmpAttribute schedObjects_attr[] = {
    { 1, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDLOCALTIME, "schedLocalTime",
       schedLocalTime_constraints,
      G_STRUCT_OFFSET(disman_schedule_mib_schedObjects_t, schedLocalTime),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const schedEntry_oid[] = {1, 3, 6, 1, 2, 1, 63, 1, 2, 1};

static GSnmpAttribute schedEntry_attr[] = {
    { 3, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDDESCR, "schedDescr",
       schedDescr_constraints,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedDescr),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedDescrLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_UNSIGNED32,
      DISMAN_SCHEDULE_MIB_SCHEDINTERVAL, "schedInterval",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDWEEKDAY, "schedWeekDay",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedWeekDay),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedWeekDayLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDMONTH, "schedMonth",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedMonth),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedMonthLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDDAY, "schedDay",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedDay),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedDayLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDHOUR, "schedHour",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedHour),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedHourLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDMINUTE, "schedMinute",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedMinute),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedMinuteLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 10, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDCONTEXTNAME, "schedContextName",
       schedContextName_constraints,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedContextName),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedContextNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 11, G_SNMP_OBJECTID,
      DISMAN_SCHEDULE_MIB_SCHEDVARIABLE, "schedVariable",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedVariable),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedVariableLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, G_SNMP_INTEGER32,
      DISMAN_SCHEDULE_MIB_SCHEDVALUE, "schedValue",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedValue),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 13, G_SNMP_INTEGER32,
      DISMAN_SCHEDULE_MIB_SCHEDTYPE, "schedType",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 14, G_SNMP_INTEGER32,
      DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS, "schedAdminStatus",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedAdminStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 15, G_SNMP_INTEGER32,
      DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS, "schedOperStatus",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedOperStatus),
      0,
      0 },
    { 16, G_SNMP_COUNTER32,
      DISMAN_SCHEDULE_MIB_SCHEDFAILURES, "schedFailures",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedFailures),
      0,
      0 },
    { 17, G_SNMP_INTEGER32,
      DISMAN_SCHEDULE_MIB_SCHEDLASTFAILURE, "schedLastFailure",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedLastFailure),
      0,
      0 },
    { 18, G_SNMP_OCTETSTRING,
      DISMAN_SCHEDULE_MIB_SCHEDLASTFAILED, "schedLastFailed",
       schedLastFailed_constraints,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedLastFailed),
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, _schedLastFailedLength),
      0 },
    { 19, G_SNMP_INTEGER32,
      DISMAN_SCHEDULE_MIB_SCHEDSTORAGETYPE, "schedStorageType",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 20, G_SNMP_INTEGER32,
      DISMAN_SCHEDULE_MIB_SCHEDROWSTATUS, "schedRowStatus",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedRowStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 21, G_SNMP_COUNTER32,
      DISMAN_SCHEDULE_MIB_SCHEDTRIGGERS, "schedTriggers",
       NULL,
      G_STRUCT_OFFSET(disman_schedule_mib_schedEntry_t, schedTriggers),
      0,
      0 },
    { 0, 0, 0, NULL }
};


disman_schedule_mib_schedObjects_t *
disman_schedule_mib_new_schedObjects()
{
    disman_schedule_mib_schedObjects_t *schedObjects;

    schedObjects = (disman_schedule_mib_schedObjects_t *) g_malloc0(sizeof(disman_schedule_mib_schedObjects_t) + sizeof(gpointer));
    return schedObjects;
}

static disman_schedule_mib_schedObjects_t *
assign_schedObjects(GSList *vbl)
{
    disman_schedule_mib_schedObjects_t *schedObjects;
    char *p;

    schedObjects = disman_schedule_mib_new_schedObjects();
    if (! schedObjects) {
        return NULL;
    }

    p = (char *) schedObjects + sizeof(disman_schedule_mib_schedObjects_t);
    * (GSList **) p = vbl;

    gsnmp_attr_assign(vbl, schedObjects_oid, sizeof(schedObjects_oid)/sizeof(guint32),
                      schedObjects_attr, schedObjects);

    return schedObjects;
}

void
disman_schedule_mib_get_schedObjects(GSnmpSession *s, disman_schedule_mib_schedObjects_t **schedObjects, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 63, 1, 0};

    *schedObjects = NULL;

    gsnmp_attr_get(s, &in, base, 9, 8, schedObjects_attr, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *schedObjects = assign_schedObjects(out);
    }
}

void
disman_schedule_mib_free_schedObjects(disman_schedule_mib_schedObjects_t *schedObjects)
{
    GSList *vbl;
    char *p;

    if (schedObjects) {
        p = (char *) schedObjects + sizeof(disman_schedule_mib_schedObjects_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(schedObjects);
    }
}

disman_schedule_mib_schedEntry_t *
disman_schedule_mib_new_schedEntry()
{
    disman_schedule_mib_schedEntry_t *schedEntry;

    schedEntry = (disman_schedule_mib_schedEntry_t *) g_malloc0(sizeof(disman_schedule_mib_schedEntry_t) + sizeof(gpointer));
    return schedEntry;
}

static int
unpack_schedEntry(GSnmpVarBind *vb, disman_schedule_mib_schedEntry_t *schedEntry)
{
    guint8 idx = 11;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        schedEntry->schedOwner[i] = vb->id[idx++];
    }
    schedEntry->_schedOwnerLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (len < 1 || len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        schedEntry->schedName[i] = vb->id[idx++];
    }
    schedEntry->_schedNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_schedEntry(guint32 *base, guchar *schedOwner, guint16 _schedOwnerLength, guchar *schedName, guint16 _schedNameLength)
{
    guint8 idx = 11;
    guint16 i, len;

    len = _schedOwnerLength;
    base[idx++] = len;
    if (len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = schedOwner[i];
        if (idx >= 128) return -1;
    }
    len = _schedNameLength;
    base[idx++] = len;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = schedName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static disman_schedule_mib_schedEntry_t *
assign_schedEntry(GSList *vbl)
{
    disman_schedule_mib_schedEntry_t *schedEntry;
    char *p;

    schedEntry = disman_schedule_mib_new_schedEntry();
    if (! schedEntry) {
        return NULL;
    }

    p = (char *) schedEntry + sizeof(disman_schedule_mib_schedEntry_t);
    * (GSList **) p = vbl;

    if (unpack_schedEntry((GSnmpVarBind *) vbl->data, schedEntry) < 0) {
        g_warning("%s: invalid instance identifier", "schedEntry");
        g_free(schedEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, schedEntry_oid, sizeof(schedEntry_oid)/sizeof(guint32),
                      schedEntry_attr, schedEntry);

    return schedEntry;
}

void
disman_schedule_mib_get_schedTable(GSnmpSession *s, disman_schedule_mib_schedEntry_t ***schedEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 63, 1, 2, 1, 0};

    *schedEntry = NULL;

    gsnmp_attr_get(s, &in, base, 11, 10, schedEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *schedEntry = (disman_schedule_mib_schedEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(disman_schedule_mib_schedEntry_t *));
        if (! *schedEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*schedEntry)[i] = assign_schedEntry(row->data);
        }
    }
}

void
disman_schedule_mib_get_schedEntry(GSnmpSession *s, disman_schedule_mib_schedEntry_t **schedEntry, guchar *schedOwner, guint16 _schedOwnerLength, guchar *schedName, guint16 _schedNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, schedEntry_oid, sizeof(schedEntry_oid));
    len = pack_schedEntry(base, schedOwner, _schedOwnerLength, schedName, _schedNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "schedEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *schedEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 10, schedEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *schedEntry = assign_schedEntry(out);
    }
}

void
disman_schedule_mib_set_schedEntry(GSnmpSession *s, disman_schedule_mib_schedEntry_t *schedEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, schedEntry_oid, sizeof(schedEntry_oid));
    len = pack_schedEntry(base, schedEntry->schedOwner, schedEntry->_schedOwnerLength, schedEntry->schedName, schedEntry->_schedNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "schedEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 10, schedEntry_attr, mask, schedEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
disman_schedule_mib_free_schedEntry(disman_schedule_mib_schedEntry_t *schedEntry)
{
    GSList *vbl;
    char *p;

    if (schedEntry) {
        p = (char *) schedEntry + sizeof(disman_schedule_mib_schedEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(schedEntry);
    }
}

void
disman_schedule_mib_free_schedTable(disman_schedule_mib_schedEntry_t **schedEntry)
{
    int i;

    if (schedEntry) {
        for (i = 0; schedEntry[i]; i++) {
            disman_schedule_mib_free_schedEntry(schedEntry[i]);
        }
        g_free(schedEntry);
    }
}


