/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from NOTIFICATION-LOG-MIB:
 *   The MIB module for logging SNMP Notifications, that is, Traps
 *   
 *   
 *   and Informs.
 *
 * Revision 2000-11-27 00:00:
 *   This is the initial version of this MIB.
 *   Published as RFC 3014
 *
 * $Id$
 */

#include "notification-log-mib.h"

GSnmpEnum const notification_log_mib_enums_nlmConfigLogAdminStatus[] = {
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGADMINSTATUS_ENABLED,  "enabled" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGADMINSTATUS_DISABLED, "disabled" },
    { 0, NULL }
};

GSnmpEnum const notification_log_mib_enums_nlmConfigLogOperStatus[] = {
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS_DISABLED,    "disabled" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS_OPERATIONAL, "operational" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS_NOFILTER,    "noFilter" },
    { 0, NULL }
};

GSnmpEnum const notification_log_mib_enums_nlmConfigLogStorageType[] = {
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGSTORAGETYPE_OTHER,       "other" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGSTORAGETYPE_VOLATILE,    "volatile" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGSTORAGETYPE_NONVOLATILE, "nonVolatile" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGSTORAGETYPE_PERMANENT,   "permanent" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGSTORAGETYPE_READONLY,    "readOnly" },
    { 0, NULL }
};

GSnmpEnum const notification_log_mib_enums_nlmConfigLogEntryStatus[] = {
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS_ACTIVE,        "active" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS_NOTINSERVICE,  "notInService" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS_NOTREADY,      "notReady" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS_CREATEANDGO,   "createAndGo" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS_CREATEANDWAIT, "createAndWait" },
    { NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS_DESTROY,       "destroy" },
    { 0, NULL }
};

GSnmpEnum const notification_log_mib_enums_nlmLogVariableValueType[] = {
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_COUNTER32,   "counter32" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_UNSIGNED32,  "unsigned32" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_TIMETICKS,   "timeTicks" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_INTEGER32,   "integer32" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_IPADDRESS,   "ipAddress" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_OCTETSTRING, "octetString" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_OBJECTID,    "objectId" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_COUNTER64,   "counter64" },
    { NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_OPAQUE,      "opaque" },
    { 0, NULL }
};


static guint16 nlmConfigLogFilterName_constraints[] = {0, 32, 0, 0};
static guint16 nlmLogDateAndTime_constraints[] = {8, 8, 11, 11, 0, 0};
static guint16 nlmLogEngineID_constraints[] = {5, 32, 0, 0};
static guint16 nlmLogEngineTAddress_constraints[] = {1, 255, 0, 0};
static guint16 nlmLogContextEngineID_constraints[] = {5, 32, 0, 0};
static guint16 nlmLogContextName_constraints[] = {0, 255, 0, 0};
static guint16 nlmLogVariableIpAddressVal_constraints[] = {4, 4, 0, 0};


static guint32 const nlmConfig_oid[] = {1, 3, 6, 1, 2, 1, 92, 1, 1};

static GSnmpAttribute nlmConfig_attr[] = {
    { 1, G_SNMP_UNSIGNED32,
      NOTIFICATION_LOG_MIB_NLMCONFIGGLOBALENTRYLIMIT, "nlmConfigGlobalEntryLimit",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfig_t, nlmConfigGlobalEntryLimit),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, G_SNMP_UNSIGNED32,
      NOTIFICATION_LOG_MIB_NLMCONFIGGLOBALAGEOUT, "nlmConfigGlobalAgeOut",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfig_t, nlmConfigGlobalAgeOut),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const nlmConfigLogEntry_oid[] = {1, 3, 6, 1, 2, 1, 92, 1, 1, 3, 1};

static GSnmpAttribute nlmConfigLogEntry_attr[] = {
    { 2, G_SNMP_OCTETSTRING,
      NOTIFICATION_LOG_MIB_NLMCONFIGLOGFILTERNAME, "nlmConfigLogFilterName",
       nlmConfigLogFilterName_constraints,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfigLogEntry_t, nlmConfigLogFilterName),
      G_STRUCT_OFFSET(notification_log_mib_nlmConfigLogEntry_t, _nlmConfigLogFilterNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, G_SNMP_UNSIGNED32,
      NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYLIMIT, "nlmConfigLogEntryLimit",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfigLogEntry_t, nlmConfigLogEntryLimit),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_INTEGER32,
      NOTIFICATION_LOG_MIB_NLMCONFIGLOGADMINSTATUS, "nlmConfigLogAdminStatus",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfigLogEntry_t, nlmConfigLogAdminStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, G_SNMP_INTEGER32,
      NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS, "nlmConfigLogOperStatus",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfigLogEntry_t, nlmConfigLogOperStatus),
      0,
      0 },
    { 6, G_SNMP_INTEGER32,
      NOTIFICATION_LOG_MIB_NLMCONFIGLOGSTORAGETYPE, "nlmConfigLogStorageType",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfigLogEntry_t, nlmConfigLogStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, G_SNMP_INTEGER32,
      NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS, "nlmConfigLogEntryStatus",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmConfigLogEntry_t, nlmConfigLogEntryStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const nlmStats_oid[] = {1, 3, 6, 1, 2, 1, 92, 1, 2};

static GSnmpAttribute nlmStats_attr[] = {
    { 1, G_SNMP_COUNTER32,
      NOTIFICATION_LOG_MIB_NLMSTATSGLOBALNOTIFICATIONSLOGGED, "nlmStatsGlobalNotificationsLogged",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmStats_t, nlmStatsGlobalNotificationsLogged),
      0,
      0 },
    { 2, G_SNMP_COUNTER32,
      NOTIFICATION_LOG_MIB_NLMSTATSGLOBALNOTIFICATIONSBUMPED, "nlmStatsGlobalNotificationsBumped",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmStats_t, nlmStatsGlobalNotificationsBumped),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const nlmStatsLogEntry_oid[] = {1, 3, 6, 1, 2, 1, 92, 1, 2, 3, 1};

static GSnmpAttribute nlmStatsLogEntry_attr[] = {
    { 1, G_SNMP_COUNTER32,
      NOTIFICATION_LOG_MIB_NLMSTATSLOGNOTIFICATIONSLOGGED, "nlmStatsLogNotificationsLogged",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmStatsLogEntry_t, nlmStatsLogNotificationsLogged),
      0,
      0 },
    { 2, G_SNMP_COUNTER32,
      NOTIFICATION_LOG_MIB_NLMSTATSLOGNOTIFICATIONSBUMPED, "nlmStatsLogNotificationsBumped",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmStatsLogEntry_t, nlmStatsLogNotificationsBumped),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const nlmLogEntry_oid[] = {1, 3, 6, 1, 2, 1, 92, 1, 3, 1, 1};

static GSnmpAttribute nlmLogEntry_attr[] = {
    { 2, G_SNMP_TIMETICKS,
      NOTIFICATION_LOG_MIB_NLMLOGTIME, "nlmLogTime",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogTime),
      0,
      0 },
    { 3, G_SNMP_OCTETSTRING,
      NOTIFICATION_LOG_MIB_NLMLOGDATEANDTIME, "nlmLogDateAndTime",
       nlmLogDateAndTime_constraints,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogDateAndTime),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, _nlmLogDateAndTimeLength),
      0 },
    { 4, G_SNMP_OCTETSTRING,
      NOTIFICATION_LOG_MIB_NLMLOGENGINEID, "nlmLogEngineID",
       nlmLogEngineID_constraints,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogEngineID),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, _nlmLogEngineIDLength),
      0 },
    { 5, G_SNMP_OCTETSTRING,
      NOTIFICATION_LOG_MIB_NLMLOGENGINETADDRESS, "nlmLogEngineTAddress",
       nlmLogEngineTAddress_constraints,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogEngineTAddress),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, _nlmLogEngineTAddressLength),
      0 },
    { 6, G_SNMP_OBJECTID,
      NOTIFICATION_LOG_MIB_NLMLOGENGINETDOMAIN, "nlmLogEngineTDomain",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogEngineTDomain),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, _nlmLogEngineTDomainLength),
      0 },
    { 7, G_SNMP_OCTETSTRING,
      NOTIFICATION_LOG_MIB_NLMLOGCONTEXTENGINEID, "nlmLogContextEngineID",
       nlmLogContextEngineID_constraints,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogContextEngineID),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, _nlmLogContextEngineIDLength),
      0 },
    { 8, G_SNMP_OCTETSTRING,
      NOTIFICATION_LOG_MIB_NLMLOGCONTEXTNAME, "nlmLogContextName",
       nlmLogContextName_constraints,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogContextName),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, _nlmLogContextNameLength),
      0 },
    { 9, G_SNMP_OBJECTID,
      NOTIFICATION_LOG_MIB_NLMLOGNOTIFICATIONID, "nlmLogNotificationID",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, nlmLogNotificationID),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogEntry_t, _nlmLogNotificationIDLength),
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const nlmLogVariableEntry_oid[] = {1, 3, 6, 1, 2, 1, 92, 1, 3, 2, 1};

static GSnmpAttribute nlmLogVariableEntry_attr[] = {
    { 2, G_SNMP_OBJECTID,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEID, "nlmLogVariableID",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableID),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, _nlmLogVariableIDLength),
      0 },
    { 3, G_SNMP_INTEGER32,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE, "nlmLogVariableValueType",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableValueType),
      0,
      0 },
    { 4, G_SNMP_COUNTER32,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLECOUNTER32VAL, "nlmLogVariableCounter32Val",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableCounter32Val),
      0,
      0 },
    { 5, G_SNMP_UNSIGNED32,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEUNSIGNED32VAL, "nlmLogVariableUnsigned32Val",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableUnsigned32Val),
      0,
      0 },
    { 6, G_SNMP_TIMETICKS,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLETIMETICKSVAL, "nlmLogVariableTimeTicksVal",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableTimeTicksVal),
      0,
      0 },
    { 7, G_SNMP_INTEGER32,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEINTEGER32VAL, "nlmLogVariableInteger32Val",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableInteger32Val),
      0,
      0 },
    { 8, G_SNMP_OCTETSTRING,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOCTETSTRINGVAL, "nlmLogVariableOctetStringVal",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableOctetStringVal),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, _nlmLogVariableOctetStringValLength),
      0 },
    { 9, G_SNMP_IPADDRESS,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEIPADDRESSVAL, "nlmLogVariableIpAddressVal",
       nlmLogVariableIpAddressVal_constraints,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableIpAddressVal),
      0,
      0 },
    { 10, G_SNMP_OBJECTID,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOIDVAL, "nlmLogVariableOidVal",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableOidVal),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, _nlmLogVariableOidValLength),
      0 },
    { 11, G_SNMP_COUNTER64,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLECOUNTER64VAL, "nlmLogVariableCounter64Val",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableCounter64Val),
      0,
      0 },
    { 12, G_SNMP_OPAQUE,
      NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOPAQUEVAL, "nlmLogVariableOpaqueVal",
       NULL,
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, nlmLogVariableOpaqueVal),
      G_STRUCT_OFFSET(notification_log_mib_nlmLogVariableEntry_t, _nlmLogVariableOpaqueValLength),
      0 },
    { 0, 0, 0, NULL }
};


notification_log_mib_nlmConfig_t *
notification_log_mib_new_nlmConfig()
{
    notification_log_mib_nlmConfig_t *nlmConfig;

    nlmConfig = (notification_log_mib_nlmConfig_t *) g_malloc0(sizeof(notification_log_mib_nlmConfig_t) + sizeof(gpointer));
    return nlmConfig;
}

static notification_log_mib_nlmConfig_t *
assign_nlmConfig(GSList *vbl)
{
    notification_log_mib_nlmConfig_t *nlmConfig;
    char *p;

    nlmConfig = notification_log_mib_new_nlmConfig();
    if (! nlmConfig) {
        return NULL;
    }

    p = (char *) nlmConfig + sizeof(notification_log_mib_nlmConfig_t);
    * (GSList **) p = vbl;

    gsnmp_attr_assign(vbl, nlmConfig_oid, sizeof(nlmConfig_oid)/sizeof(guint32),
                      nlmConfig_attr, nlmConfig);

    return nlmConfig;
}

void
notification_log_mib_get_nlmConfig(GSnmpSession *s, notification_log_mib_nlmConfig_t **nlmConfig, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 92, 1, 1, 0};

    *nlmConfig = NULL;

    gsnmp_attr_get(s, &in, base, 10, 9, nlmConfig_attr, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *nlmConfig = assign_nlmConfig(out);
    }
}

void
notification_log_mib_set_nlmConfig(GSnmpSession *s, notification_log_mib_nlmConfig_t *nlmConfig, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 92, 1, 1, 0, 0};

    gsnmp_attr_set(s, &in, base, 11, 9, nlmConfig_attr, mask, nlmConfig);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
notification_log_mib_free_nlmConfig(notification_log_mib_nlmConfig_t *nlmConfig)
{
    GSList *vbl;
    char *p;

    if (nlmConfig) {
        p = (char *) nlmConfig + sizeof(notification_log_mib_nlmConfig_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(nlmConfig);
    }
}

notification_log_mib_nlmConfigLogEntry_t *
notification_log_mib_new_nlmConfigLogEntry()
{
    notification_log_mib_nlmConfigLogEntry_t *nlmConfigLogEntry;

    nlmConfigLogEntry = (notification_log_mib_nlmConfigLogEntry_t *) g_malloc0(sizeof(notification_log_mib_nlmConfigLogEntry_t) + sizeof(gpointer));
    return nlmConfigLogEntry;
}

static int
unpack_nlmConfigLogEntry(GSnmpVarBind *vb, notification_log_mib_nlmConfigLogEntry_t *nlmConfigLogEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        nlmConfigLogEntry->nlmLogName[i] = vb->id[idx++];
    }
    nlmConfigLogEntry->_nlmLogNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_nlmConfigLogEntry(guint32 *base, guchar *nlmLogName, guint16 _nlmLogNameLength)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _nlmLogNameLength;
    base[idx++] = len;
    if (len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = nlmLogName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static notification_log_mib_nlmConfigLogEntry_t *
assign_nlmConfigLogEntry(GSList *vbl)
{
    notification_log_mib_nlmConfigLogEntry_t *nlmConfigLogEntry;
    char *p;

    nlmConfigLogEntry = notification_log_mib_new_nlmConfigLogEntry();
    if (! nlmConfigLogEntry) {
        return NULL;
    }

    p = (char *) nlmConfigLogEntry + sizeof(notification_log_mib_nlmConfigLogEntry_t);
    * (GSList **) p = vbl;

    if (unpack_nlmConfigLogEntry((GSnmpVarBind *) vbl->data, nlmConfigLogEntry) < 0) {
        g_warning("%s: invalid instance identifier", "nlmConfigLogEntry");
        g_free(nlmConfigLogEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, nlmConfigLogEntry_oid, sizeof(nlmConfigLogEntry_oid)/sizeof(guint32),
                      nlmConfigLogEntry_attr, nlmConfigLogEntry);

    return nlmConfigLogEntry;
}

void
notification_log_mib_get_nlmConfigLogTable(GSnmpSession *s, notification_log_mib_nlmConfigLogEntry_t ***nlmConfigLogEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 92, 1, 1, 3, 1, 0};

    *nlmConfigLogEntry = NULL;

    gsnmp_attr_get(s, &in, base, 12, 11, nlmConfigLogEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *nlmConfigLogEntry = (notification_log_mib_nlmConfigLogEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(notification_log_mib_nlmConfigLogEntry_t *));
        if (! *nlmConfigLogEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*nlmConfigLogEntry)[i] = assign_nlmConfigLogEntry(row->data);
        }
    }
}

void
notification_log_mib_get_nlmConfigLogEntry(GSnmpSession *s, notification_log_mib_nlmConfigLogEntry_t **nlmConfigLogEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, nlmConfigLogEntry_oid, sizeof(nlmConfigLogEntry_oid));
    len = pack_nlmConfigLogEntry(base, nlmLogName, _nlmLogNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "nlmConfigLogEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *nlmConfigLogEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 11, nlmConfigLogEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *nlmConfigLogEntry = assign_nlmConfigLogEntry(out);
    }
}

void
notification_log_mib_set_nlmConfigLogEntry(GSnmpSession *s, notification_log_mib_nlmConfigLogEntry_t *nlmConfigLogEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, nlmConfigLogEntry_oid, sizeof(nlmConfigLogEntry_oid));
    len = pack_nlmConfigLogEntry(base, nlmConfigLogEntry->nlmLogName, nlmConfigLogEntry->_nlmLogNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "nlmConfigLogEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 11, nlmConfigLogEntry_attr, mask, nlmConfigLogEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
notification_log_mib_free_nlmConfigLogEntry(notification_log_mib_nlmConfigLogEntry_t *nlmConfigLogEntry)
{
    GSList *vbl;
    char *p;

    if (nlmConfigLogEntry) {
        p = (char *) nlmConfigLogEntry + sizeof(notification_log_mib_nlmConfigLogEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(nlmConfigLogEntry);
    }
}

void
notification_log_mib_free_nlmConfigLogTable(notification_log_mib_nlmConfigLogEntry_t **nlmConfigLogEntry)
{
    int i;

    if (nlmConfigLogEntry) {
        for (i = 0; nlmConfigLogEntry[i]; i++) {
            notification_log_mib_free_nlmConfigLogEntry(nlmConfigLogEntry[i]);
        }
        g_free(nlmConfigLogEntry);
    }
}

notification_log_mib_nlmStats_t *
notification_log_mib_new_nlmStats()
{
    notification_log_mib_nlmStats_t *nlmStats;

    nlmStats = (notification_log_mib_nlmStats_t *) g_malloc0(sizeof(notification_log_mib_nlmStats_t) + sizeof(gpointer));
    return nlmStats;
}

static notification_log_mib_nlmStats_t *
assign_nlmStats(GSList *vbl)
{
    notification_log_mib_nlmStats_t *nlmStats;
    char *p;

    nlmStats = notification_log_mib_new_nlmStats();
    if (! nlmStats) {
        return NULL;
    }

    p = (char *) nlmStats + sizeof(notification_log_mib_nlmStats_t);
    * (GSList **) p = vbl;

    gsnmp_attr_assign(vbl, nlmStats_oid, sizeof(nlmStats_oid)/sizeof(guint32),
                      nlmStats_attr, nlmStats);

    return nlmStats;
}

void
notification_log_mib_get_nlmStats(GSnmpSession *s, notification_log_mib_nlmStats_t **nlmStats, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 92, 1, 2, 0};

    *nlmStats = NULL;

    gsnmp_attr_get(s, &in, base, 10, 9, nlmStats_attr, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *nlmStats = assign_nlmStats(out);
    }
}

void
notification_log_mib_free_nlmStats(notification_log_mib_nlmStats_t *nlmStats)
{
    GSList *vbl;
    char *p;

    if (nlmStats) {
        p = (char *) nlmStats + sizeof(notification_log_mib_nlmStats_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(nlmStats);
    }
}

notification_log_mib_nlmStatsLogEntry_t *
notification_log_mib_new_nlmStatsLogEntry()
{
    notification_log_mib_nlmStatsLogEntry_t *nlmStatsLogEntry;

    nlmStatsLogEntry = (notification_log_mib_nlmStatsLogEntry_t *) g_malloc0(sizeof(notification_log_mib_nlmStatsLogEntry_t) + sizeof(gpointer));
    return nlmStatsLogEntry;
}

static int
unpack_nlmStatsLogEntry(GSnmpVarBind *vb, notification_log_mib_nlmStatsLogEntry_t *nlmStatsLogEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        nlmStatsLogEntry->nlmLogName[i] = vb->id[idx++];
    }
    nlmStatsLogEntry->_nlmLogNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_nlmStatsLogEntry(guint32 *base, guchar *nlmLogName, guint16 _nlmLogNameLength)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _nlmLogNameLength;
    base[idx++] = len;
    if (len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = nlmLogName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static notification_log_mib_nlmStatsLogEntry_t *
assign_nlmStatsLogEntry(GSList *vbl)
{
    notification_log_mib_nlmStatsLogEntry_t *nlmStatsLogEntry;
    char *p;

    nlmStatsLogEntry = notification_log_mib_new_nlmStatsLogEntry();
    if (! nlmStatsLogEntry) {
        return NULL;
    }

    p = (char *) nlmStatsLogEntry + sizeof(notification_log_mib_nlmStatsLogEntry_t);
    * (GSList **) p = vbl;

    if (unpack_nlmStatsLogEntry((GSnmpVarBind *) vbl->data, nlmStatsLogEntry) < 0) {
        g_warning("%s: invalid instance identifier", "nlmStatsLogEntry");
        g_free(nlmStatsLogEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, nlmStatsLogEntry_oid, sizeof(nlmStatsLogEntry_oid)/sizeof(guint32),
                      nlmStatsLogEntry_attr, nlmStatsLogEntry);

    return nlmStatsLogEntry;
}

void
notification_log_mib_get_nlmStatsLogTable(GSnmpSession *s, notification_log_mib_nlmStatsLogEntry_t ***nlmStatsLogEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 92, 1, 2, 3, 1, 0};

    *nlmStatsLogEntry = NULL;

    gsnmp_attr_get(s, &in, base, 12, 11, nlmStatsLogEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *nlmStatsLogEntry = (notification_log_mib_nlmStatsLogEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(notification_log_mib_nlmStatsLogEntry_t *));
        if (! *nlmStatsLogEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*nlmStatsLogEntry)[i] = assign_nlmStatsLogEntry(row->data);
        }
    }
}

void
notification_log_mib_get_nlmStatsLogEntry(GSnmpSession *s, notification_log_mib_nlmStatsLogEntry_t **nlmStatsLogEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, nlmStatsLogEntry_oid, sizeof(nlmStatsLogEntry_oid));
    len = pack_nlmStatsLogEntry(base, nlmLogName, _nlmLogNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "nlmStatsLogEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *nlmStatsLogEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 11, nlmStatsLogEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *nlmStatsLogEntry = assign_nlmStatsLogEntry(out);
    }
}

void
notification_log_mib_free_nlmStatsLogEntry(notification_log_mib_nlmStatsLogEntry_t *nlmStatsLogEntry)
{
    GSList *vbl;
    char *p;

    if (nlmStatsLogEntry) {
        p = (char *) nlmStatsLogEntry + sizeof(notification_log_mib_nlmStatsLogEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(nlmStatsLogEntry);
    }
}

void
notification_log_mib_free_nlmStatsLogTable(notification_log_mib_nlmStatsLogEntry_t **nlmStatsLogEntry)
{
    int i;

    if (nlmStatsLogEntry) {
        for (i = 0; nlmStatsLogEntry[i]; i++) {
            notification_log_mib_free_nlmStatsLogEntry(nlmStatsLogEntry[i]);
        }
        g_free(nlmStatsLogEntry);
    }
}

notification_log_mib_nlmLogEntry_t *
notification_log_mib_new_nlmLogEntry()
{
    notification_log_mib_nlmLogEntry_t *nlmLogEntry;

    nlmLogEntry = (notification_log_mib_nlmLogEntry_t *) g_malloc0(sizeof(notification_log_mib_nlmLogEntry_t) + sizeof(gpointer));
    return nlmLogEntry;
}

static int
unpack_nlmLogEntry(GSnmpVarBind *vb, notification_log_mib_nlmLogEntry_t *nlmLogEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        nlmLogEntry->nlmLogName[i] = vb->id[idx++];
    }
    nlmLogEntry->_nlmLogNameLength = len;
    if (vb->id_len < idx) return -1;
    nlmLogEntry->nlmLogIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_nlmLogEntry(guint32 *base, guchar *nlmLogName, guint16 _nlmLogNameLength, guint32 nlmLogIndex)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _nlmLogNameLength;
    base[idx++] = len;
    if (len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = nlmLogName[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = nlmLogIndex;
    return idx;
}

static notification_log_mib_nlmLogEntry_t *
assign_nlmLogEntry(GSList *vbl)
{
    notification_log_mib_nlmLogEntry_t *nlmLogEntry;
    char *p;

    nlmLogEntry = notification_log_mib_new_nlmLogEntry();
    if (! nlmLogEntry) {
        return NULL;
    }

    p = (char *) nlmLogEntry + sizeof(notification_log_mib_nlmLogEntry_t);
    * (GSList **) p = vbl;

    if (unpack_nlmLogEntry((GSnmpVarBind *) vbl->data, nlmLogEntry) < 0) {
        g_warning("%s: invalid instance identifier", "nlmLogEntry");
        g_free(nlmLogEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, nlmLogEntry_oid, sizeof(nlmLogEntry_oid)/sizeof(guint32),
                      nlmLogEntry_attr, nlmLogEntry);

    return nlmLogEntry;
}

void
notification_log_mib_get_nlmLogTable(GSnmpSession *s, notification_log_mib_nlmLogEntry_t ***nlmLogEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 92, 1, 3, 1, 1, 0};

    *nlmLogEntry = NULL;

    gsnmp_attr_get(s, &in, base, 12, 11, nlmLogEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *nlmLogEntry = (notification_log_mib_nlmLogEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(notification_log_mib_nlmLogEntry_t *));
        if (! *nlmLogEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*nlmLogEntry)[i] = assign_nlmLogEntry(row->data);
        }
    }
}

void
notification_log_mib_get_nlmLogEntry(GSnmpSession *s, notification_log_mib_nlmLogEntry_t **nlmLogEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, guint32 nlmLogIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, nlmLogEntry_oid, sizeof(nlmLogEntry_oid));
    len = pack_nlmLogEntry(base, nlmLogName, _nlmLogNameLength, nlmLogIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "nlmLogEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *nlmLogEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 11, nlmLogEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *nlmLogEntry = assign_nlmLogEntry(out);
    }
}

void
notification_log_mib_free_nlmLogEntry(notification_log_mib_nlmLogEntry_t *nlmLogEntry)
{
    GSList *vbl;
    char *p;

    if (nlmLogEntry) {
        p = (char *) nlmLogEntry + sizeof(notification_log_mib_nlmLogEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(nlmLogEntry);
    }
}

void
notification_log_mib_free_nlmLogTable(notification_log_mib_nlmLogEntry_t **nlmLogEntry)
{
    int i;

    if (nlmLogEntry) {
        for (i = 0; nlmLogEntry[i]; i++) {
            notification_log_mib_free_nlmLogEntry(nlmLogEntry[i]);
        }
        g_free(nlmLogEntry);
    }
}

notification_log_mib_nlmLogVariableEntry_t *
notification_log_mib_new_nlmLogVariableEntry()
{
    notification_log_mib_nlmLogVariableEntry_t *nlmLogVariableEntry;

    nlmLogVariableEntry = (notification_log_mib_nlmLogVariableEntry_t *) g_malloc0(sizeof(notification_log_mib_nlmLogVariableEntry_t) + sizeof(gpointer));
    return nlmLogVariableEntry;
}

static int
unpack_nlmLogVariableEntry(GSnmpVarBind *vb, notification_log_mib_nlmLogVariableEntry_t *nlmLogVariableEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        nlmLogVariableEntry->nlmLogName[i] = vb->id[idx++];
    }
    nlmLogVariableEntry->_nlmLogNameLength = len;
    if (vb->id_len < idx) return -1;
    nlmLogVariableEntry->nlmLogIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    nlmLogVariableEntry->nlmLogVariableIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_nlmLogVariableEntry(guint32 *base, guchar *nlmLogName, guint16 _nlmLogNameLength, guint32 nlmLogIndex, guint32 nlmLogVariableIndex)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _nlmLogNameLength;
    base[idx++] = len;
    if (len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = nlmLogName[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = nlmLogIndex;
    base[idx++] = nlmLogVariableIndex;
    return idx;
}

static notification_log_mib_nlmLogVariableEntry_t *
assign_nlmLogVariableEntry(GSList *vbl)
{
    notification_log_mib_nlmLogVariableEntry_t *nlmLogVariableEntry;
    char *p;

    nlmLogVariableEntry = notification_log_mib_new_nlmLogVariableEntry();
    if (! nlmLogVariableEntry) {
        return NULL;
    }

    p = (char *) nlmLogVariableEntry + sizeof(notification_log_mib_nlmLogVariableEntry_t);
    * (GSList **) p = vbl;

    if (unpack_nlmLogVariableEntry((GSnmpVarBind *) vbl->data, nlmLogVariableEntry) < 0) {
        g_warning("%s: invalid instance identifier", "nlmLogVariableEntry");
        g_free(nlmLogVariableEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, nlmLogVariableEntry_oid, sizeof(nlmLogVariableEntry_oid)/sizeof(guint32),
                      nlmLogVariableEntry_attr, nlmLogVariableEntry);

    return nlmLogVariableEntry;
}

void
notification_log_mib_get_nlmLogVariableTable(GSnmpSession *s, notification_log_mib_nlmLogVariableEntry_t ***nlmLogVariableEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 92, 1, 3, 2, 1, 0};

    *nlmLogVariableEntry = NULL;

    gsnmp_attr_get(s, &in, base, 12, 11, nlmLogVariableEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *nlmLogVariableEntry = (notification_log_mib_nlmLogVariableEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(notification_log_mib_nlmLogVariableEntry_t *));
        if (! *nlmLogVariableEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*nlmLogVariableEntry)[i] = assign_nlmLogVariableEntry(row->data);
        }
    }
}

void
notification_log_mib_get_nlmLogVariableEntry(GSnmpSession *s, notification_log_mib_nlmLogVariableEntry_t **nlmLogVariableEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, guint32 nlmLogIndex, guint32 nlmLogVariableIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, nlmLogVariableEntry_oid, sizeof(nlmLogVariableEntry_oid));
    len = pack_nlmLogVariableEntry(base, nlmLogName, _nlmLogNameLength, nlmLogIndex, nlmLogVariableIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "nlmLogVariableEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *nlmLogVariableEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 11, nlmLogVariableEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *nlmLogVariableEntry = assign_nlmLogVariableEntry(out);
    }
}

void
notification_log_mib_free_nlmLogVariableEntry(notification_log_mib_nlmLogVariableEntry_t *nlmLogVariableEntry)
{
    GSList *vbl;
    char *p;

    if (nlmLogVariableEntry) {
        p = (char *) nlmLogVariableEntry + sizeof(notification_log_mib_nlmLogVariableEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(nlmLogVariableEntry);
    }
}

void
notification_log_mib_free_nlmLogVariableTable(notification_log_mib_nlmLogVariableEntry_t **nlmLogVariableEntry)
{
    int i;

    if (nlmLogVariableEntry) {
        for (i = 0; nlmLogVariableEntry[i]; i++) {
            notification_log_mib_free_nlmLogVariableEntry(nlmLogVariableEntry[i]);
        }
        g_free(nlmLogVariableEntry);
    }
}


