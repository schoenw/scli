/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.2-pre1:
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

#include "snmp-view-based-acm-mib.h"

GSnmpEnum const snmp_view_based_acm_mib_enums_vacmAccessContextMatch[] = {
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH_EXACT,  "exact" },
    { SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH_PREFIX, "prefix" },
    { 0, NULL }
};

GSnmpEnum const snmp_view_based_acm_mib_enums_vacmViewTreeFamilyType[] = {
    { SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_INCLUDED, "included" },
    { SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE_EXCLUDED, "excluded" },
    { 0, NULL }
};


static guint16 vacmContextName_constraints[] = {0U, 32U, 0, 0};
static guint16 vacmGroupName_constraints[] = {1U, 32U, 0, 0};
static guint16 vacmAccessReadViewName_constraints[] = {0U, 32U, 0, 0};
static guint16 vacmAccessWriteViewName_constraints[] = {0U, 32U, 0, 0};
static guint16 vacmAccessNotifyViewName_constraints[] = {0U, 32U, 0, 0};
static gint32 vacmViewSpinLock_constraints[] = {0L, 2147483647L, 0, 0};
static guint16 vacmViewTreeFamilyMask_constraints[] = {0U, 16U, 0, 0};


static guint32 const vacmContextEntry_oid[] = {1, 3, 6, 1, 6, 3, 16, 1, 1, 1};

static GSnmpAttribute vacmContextEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_VIEW_BASED_ACM_MIB_VACMCONTEXTNAME, "vacmContextName",
       vacmContextName_constraints,
      -1,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmContextEntry_t, _vacmContextNameLength),
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const vacmSecurityToGroupEntry_oid[] = {1, 3, 6, 1, 6, 3, 16, 1, 2, 1};

static GSnmpAttribute vacmSecurityToGroupEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_VIEW_BASED_ACM_MIB_VACMGROUPNAME, "vacmGroupName",
       vacmGroupName_constraints,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t, vacmGroupName),
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t, _vacmGroupNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTORAGETYPE, "vacmSecurityToGroupStorageType",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t, vacmSecurityToGroupStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMSECURITYTOGROUPSTATUS, "vacmSecurityToGroupStatus",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t, vacmSecurityToGroupStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const vacmAccessEntry_oid[] = {1, 3, 6, 1, 6, 3, 16, 1, 4, 1};

static GSnmpAttribute vacmAccessEntry_attr[] = {
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMACCESSCONTEXTMATCH, "vacmAccessContextMatch",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, vacmAccessContextMatch),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_VIEW_BASED_ACM_MIB_VACMACCESSREADVIEWNAME, "vacmAccessReadViewName",
       vacmAccessReadViewName_constraints,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, vacmAccessReadViewName),
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, _vacmAccessReadViewNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_VIEW_BASED_ACM_MIB_VACMACCESSWRITEVIEWNAME, "vacmAccessWriteViewName",
       vacmAccessWriteViewName_constraints,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, vacmAccessWriteViewName),
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, _vacmAccessWriteViewNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_VIEW_BASED_ACM_MIB_VACMACCESSNOTIFYVIEWNAME, "vacmAccessNotifyViewName",
       vacmAccessNotifyViewName_constraints,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, vacmAccessNotifyViewName),
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, _vacmAccessNotifyViewNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTORAGETYPE, "vacmAccessStorageType",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, vacmAccessStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMACCESSSTATUS, "vacmAccessStatus",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmAccessEntry_t, vacmAccessStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const vacmMIBViews_oid[] = {1, 3, 6, 1, 6, 3, 16, 1, 5};

static GSnmpAttribute vacmMIBViews_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMVIEWSPINLOCK, "vacmViewSpinLock",
       vacmViewSpinLock_constraints,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmMIBViews_t, vacmViewSpinLock),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const vacmViewTreeFamilyEntry_oid[] = {1, 3, 6, 1, 6, 3, 16, 1, 5, 2, 1};

static GSnmpAttribute vacmViewTreeFamilyEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYMASK, "vacmViewTreeFamilyMask",
       vacmViewTreeFamilyMask_constraints,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t, vacmViewTreeFamilyMask),
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t, _vacmViewTreeFamilyMaskLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYTYPE, "vacmViewTreeFamilyType",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t, vacmViewTreeFamilyType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTORAGETYPE, "vacmViewTreeFamilyStorageType",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t, vacmViewTreeFamilyStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_VIEW_BASED_ACM_MIB_VACMVIEWTREEFAMILYSTATUS, "vacmViewTreeFamilyStatus",
       NULL,
      G_STRUCT_OFFSET(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t, vacmViewTreeFamilyStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


snmp_view_based_acm_mib_vacmContextEntry_t *
snmp_view_based_acm_mib_new_vacmContextEntry()
{
    snmp_view_based_acm_mib_vacmContextEntry_t *vacmContextEntry;

    vacmContextEntry = (snmp_view_based_acm_mib_vacmContextEntry_t *) g_malloc0(sizeof(snmp_view_based_acm_mib_vacmContextEntry_t) + sizeof(gpointer));
    return vacmContextEntry;
}

static inline int
unpack_vacmContextEntry(GNetSnmpVarBind *vb, snmp_view_based_acm_mib_vacmContextEntry_t *vacmContextEntry)
{
    guint8 idx = 11;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len > 32) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        vacmContextEntry->vacmContextName[i] = vb->oid[idx++];
    }
    vacmContextEntry->_vacmContextNameLength = len;
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_vacmContextEntry(guint32 *base, guchar *vacmContextName, guint16 _vacmContextNameLength)
{
    guint8 idx = 11;
    guint16 i, len;

    len = _vacmContextNameLength;
    base[idx++] = len;
    if (len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = vacmContextName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline snmp_view_based_acm_mib_vacmContextEntry_t *
assign_vacmContextEntry(GList *vbl)
{
    snmp_view_based_acm_mib_vacmContextEntry_t *vacmContextEntry;
    char *p;

    vacmContextEntry = snmp_view_based_acm_mib_new_vacmContextEntry();
    p = (char *) vacmContextEntry + sizeof(snmp_view_based_acm_mib_vacmContextEntry_t);
    * (GList **) p = vbl;

    if (unpack_vacmContextEntry((GNetSnmpVarBind *) vbl->data, vacmContextEntry) < 0) {
        g_warning("%s: invalid instance identifier", "vacmContextEntry");
        g_free(vacmContextEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, vacmContextEntry_oid, sizeof(vacmContextEntry_oid)/sizeof(guint32),
                      vacmContextEntry_attr, vacmContextEntry);

    return vacmContextEntry;
}

void
snmp_view_based_acm_mib_get_vacmContextTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmContextEntry_t ***vacmContextEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 16, 1, 1, 1, 0};

    *vacmContextEntry = NULL;

    gsnmp_attr_get(s, &in, base, 11, 10, vacmContextEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *vacmContextEntry = (snmp_view_based_acm_mib_vacmContextEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(snmp_view_based_acm_mib_vacmContextEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*vacmContextEntry)[i] = assign_vacmContextEntry(row->data);
        }
    }
}

void
snmp_view_based_acm_mib_get_vacmContextEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmContextEntry_t **vacmContextEntry, guchar *vacmContextName, guint16 _vacmContextNameLength, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, vacmContextEntry_oid, sizeof(vacmContextEntry_oid));
    len = pack_vacmContextEntry(base, vacmContextName, _vacmContextNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "vacmContextEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *vacmContextEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 10, vacmContextEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *vacmContextEntry = assign_vacmContextEntry(out);
    }
}

void
snmp_view_based_acm_mib_free_vacmContextEntry(snmp_view_based_acm_mib_vacmContextEntry_t *vacmContextEntry)
{
    GList *vbl;
    char *p;

    if (vacmContextEntry) {
        p = (char *) vacmContextEntry + sizeof(snmp_view_based_acm_mib_vacmContextEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(vacmContextEntry);
    }
}

void
snmp_view_based_acm_mib_free_vacmContextTable(snmp_view_based_acm_mib_vacmContextEntry_t **vacmContextEntry)
{
    int i;

    if (vacmContextEntry) {
        for (i = 0; vacmContextEntry[i]; i++) {
            snmp_view_based_acm_mib_free_vacmContextEntry(vacmContextEntry[i]);
        }
        g_free(vacmContextEntry);
    }
}

snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *
snmp_view_based_acm_mib_new_vacmSecurityToGroupEntry()
{
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry;

    vacmSecurityToGroupEntry = (snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *) g_malloc0(sizeof(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t) + sizeof(gpointer));
    return vacmSecurityToGroupEntry;
}

static inline int
unpack_vacmSecurityToGroupEntry(GNetSnmpVarBind *vb, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry)
{
    guint8 idx = 11;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    vacmSecurityToGroupEntry->vacmSecurityModel = vb->oid[idx++];
    if ((vacmSecurityToGroupEntry->vacmSecurityModel < 1)
        && (vacmSecurityToGroupEntry->vacmSecurityModel < 0)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len < 1 || len > 32) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        vacmSecurityToGroupEntry->vacmSecurityName[i] = vb->oid[idx++];
    }
    vacmSecurityToGroupEntry->_vacmSecurityNameLength = len;
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_vacmSecurityToGroupEntry(guint32 *base, gint32 vacmSecurityModel, guchar *vacmSecurityName, guint16 _vacmSecurityNameLength)
{
    guint8 idx = 11;
    guint16 i, len;

    base[idx++] = vacmSecurityModel;
    len = _vacmSecurityNameLength;
    base[idx++] = len;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = vacmSecurityName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *
assign_vacmSecurityToGroupEntry(GList *vbl)
{
    snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry;
    char *p;

    vacmSecurityToGroupEntry = snmp_view_based_acm_mib_new_vacmSecurityToGroupEntry();
    p = (char *) vacmSecurityToGroupEntry + sizeof(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t);
    * (GList **) p = vbl;

    if (unpack_vacmSecurityToGroupEntry((GNetSnmpVarBind *) vbl->data, vacmSecurityToGroupEntry) < 0) {
        g_warning("%s: invalid instance identifier", "vacmSecurityToGroupEntry");
        g_free(vacmSecurityToGroupEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, vacmSecurityToGroupEntry_oid, sizeof(vacmSecurityToGroupEntry_oid)/sizeof(guint32),
                      vacmSecurityToGroupEntry_attr, vacmSecurityToGroupEntry);

    return vacmSecurityToGroupEntry;
}

void
snmp_view_based_acm_mib_get_vacmSecurityToGroupTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t ***vacmSecurityToGroupEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 16, 1, 2, 1, 0};

    *vacmSecurityToGroupEntry = NULL;

    gsnmp_attr_get(s, &in, base, 11, 10, vacmSecurityToGroupEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *vacmSecurityToGroupEntry = (snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*vacmSecurityToGroupEntry)[i] = assign_vacmSecurityToGroupEntry(row->data);
        }
    }
}

void
snmp_view_based_acm_mib_get_vacmSecurityToGroupEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmSecurityToGroupEntry, gint32 vacmSecurityModel, guchar *vacmSecurityName, guint16 _vacmSecurityNameLength, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, vacmSecurityToGroupEntry_oid, sizeof(vacmSecurityToGroupEntry_oid));
    len = pack_vacmSecurityToGroupEntry(base, vacmSecurityModel, vacmSecurityName, _vacmSecurityNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "vacmSecurityToGroupEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *vacmSecurityToGroupEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 10, vacmSecurityToGroupEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *vacmSecurityToGroupEntry = assign_vacmSecurityToGroupEntry(out);
    }
}

void
snmp_view_based_acm_mib_set_vacmSecurityToGroupEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, vacmSecurityToGroupEntry_oid, sizeof(vacmSecurityToGroupEntry_oid));
    len = pack_vacmSecurityToGroupEntry(base, vacmSecurityToGroupEntry->vacmSecurityModel, vacmSecurityToGroupEntry->vacmSecurityName, vacmSecurityToGroupEntry->_vacmSecurityNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "vacmSecurityToGroupEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 10, vacmSecurityToGroupEntry_attr, mask, vacmSecurityToGroupEntry);

    out = g_snmp_session_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
snmp_view_based_acm_mib_free_vacmSecurityToGroupEntry(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t *vacmSecurityToGroupEntry)
{
    GList *vbl;
    char *p;

    if (vacmSecurityToGroupEntry) {
        p = (char *) vacmSecurityToGroupEntry + sizeof(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(vacmSecurityToGroupEntry);
    }
}

void
snmp_view_based_acm_mib_free_vacmSecurityToGroupTable(snmp_view_based_acm_mib_vacmSecurityToGroupEntry_t **vacmSecurityToGroupEntry)
{
    int i;

    if (vacmSecurityToGroupEntry) {
        for (i = 0; vacmSecurityToGroupEntry[i]; i++) {
            snmp_view_based_acm_mib_free_vacmSecurityToGroupEntry(vacmSecurityToGroupEntry[i]);
        }
        g_free(vacmSecurityToGroupEntry);
    }
}

snmp_view_based_acm_mib_vacmAccessEntry_t *
snmp_view_based_acm_mib_new_vacmAccessEntry()
{
    snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry;

    vacmAccessEntry = (snmp_view_based_acm_mib_vacmAccessEntry_t *) g_malloc0(sizeof(snmp_view_based_acm_mib_vacmAccessEntry_t) + sizeof(gpointer));
    return vacmAccessEntry;
}

static inline int
unpack_vacmAccessEntry(GNetSnmpVarBind *vb, snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry)
{
    guint8 idx = 11;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len < 1 || len > 32) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        vacmAccessEntry->vacmGroupName[i] = vb->oid[idx++];
    }
    vacmAccessEntry->_vacmGroupNameLength = len;
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len > 32) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        vacmAccessEntry->vacmAccessContextPrefix[i] = vb->oid[idx++];
    }
    vacmAccessEntry->_vacmAccessContextPrefixLength = len;
    if (vb->oid_len < idx) return -1;
    vacmAccessEntry->vacmAccessSecurityModel = vb->oid[idx++];
    if ((vacmAccessEntry->vacmAccessSecurityModel < 0)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    vacmAccessEntry->vacmAccessSecurityLevel = vb->oid[idx++];
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_vacmAccessEntry(guint32 *base, guchar *vacmGroupName, guint16 _vacmGroupNameLength, guchar *vacmAccessContextPrefix, guint16 _vacmAccessContextPrefixLength, gint32 vacmAccessSecurityModel, gint32 vacmAccessSecurityLevel)
{
    guint8 idx = 11;
    guint16 i, len;

    len = _vacmGroupNameLength;
    base[idx++] = len;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = vacmGroupName[i];
        if (idx >= 128) return -1;
    }
    len = _vacmAccessContextPrefixLength;
    base[idx++] = len;
    if (len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = vacmAccessContextPrefix[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = vacmAccessSecurityModel;
    base[idx++] = vacmAccessSecurityLevel;
    return idx;
}

static inline snmp_view_based_acm_mib_vacmAccessEntry_t *
assign_vacmAccessEntry(GList *vbl)
{
    snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry;
    char *p;

    vacmAccessEntry = snmp_view_based_acm_mib_new_vacmAccessEntry();
    p = (char *) vacmAccessEntry + sizeof(snmp_view_based_acm_mib_vacmAccessEntry_t);
    * (GList **) p = vbl;

    if (unpack_vacmAccessEntry((GNetSnmpVarBind *) vbl->data, vacmAccessEntry) < 0) {
        g_warning("%s: invalid instance identifier", "vacmAccessEntry");
        g_free(vacmAccessEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, vacmAccessEntry_oid, sizeof(vacmAccessEntry_oid)/sizeof(guint32),
                      vacmAccessEntry_attr, vacmAccessEntry);

    return vacmAccessEntry;
}

void
snmp_view_based_acm_mib_get_vacmAccessTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmAccessEntry_t ***vacmAccessEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 16, 1, 4, 1, 0};

    *vacmAccessEntry = NULL;

    gsnmp_attr_get(s, &in, base, 11, 10, vacmAccessEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *vacmAccessEntry = (snmp_view_based_acm_mib_vacmAccessEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(snmp_view_based_acm_mib_vacmAccessEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*vacmAccessEntry)[i] = assign_vacmAccessEntry(row->data);
        }
    }
}

void
snmp_view_based_acm_mib_get_vacmAccessEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessEntry, guchar *vacmGroupName, guint16 _vacmGroupNameLength, guchar *vacmAccessContextPrefix, guint16 _vacmAccessContextPrefixLength, gint32 vacmAccessSecurityModel, gint32 vacmAccessSecurityLevel, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, vacmAccessEntry_oid, sizeof(vacmAccessEntry_oid));
    len = pack_vacmAccessEntry(base, vacmGroupName, _vacmGroupNameLength, vacmAccessContextPrefix, _vacmAccessContextPrefixLength, vacmAccessSecurityModel, vacmAccessSecurityLevel);
    if (len < 0) {
        g_warning("%s: invalid index values", "vacmAccessEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *vacmAccessEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 10, vacmAccessEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *vacmAccessEntry = assign_vacmAccessEntry(out);
    }
}

void
snmp_view_based_acm_mib_set_vacmAccessEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, vacmAccessEntry_oid, sizeof(vacmAccessEntry_oid));
    len = pack_vacmAccessEntry(base, vacmAccessEntry->vacmGroupName, vacmAccessEntry->_vacmGroupNameLength, vacmAccessEntry->vacmAccessContextPrefix, vacmAccessEntry->_vacmAccessContextPrefixLength, vacmAccessEntry->vacmAccessSecurityModel, vacmAccessEntry->vacmAccessSecurityLevel);
    if (len < 0) {
        g_warning("%s: invalid index values", "vacmAccessEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 10, vacmAccessEntry_attr, mask, vacmAccessEntry);

    out = g_snmp_session_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
snmp_view_based_acm_mib_free_vacmAccessEntry(snmp_view_based_acm_mib_vacmAccessEntry_t *vacmAccessEntry)
{
    GList *vbl;
    char *p;

    if (vacmAccessEntry) {
        p = (char *) vacmAccessEntry + sizeof(snmp_view_based_acm_mib_vacmAccessEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(vacmAccessEntry);
    }
}

void
snmp_view_based_acm_mib_free_vacmAccessTable(snmp_view_based_acm_mib_vacmAccessEntry_t **vacmAccessEntry)
{
    int i;

    if (vacmAccessEntry) {
        for (i = 0; vacmAccessEntry[i]; i++) {
            snmp_view_based_acm_mib_free_vacmAccessEntry(vacmAccessEntry[i]);
        }
        g_free(vacmAccessEntry);
    }
}

snmp_view_based_acm_mib_vacmMIBViews_t *
snmp_view_based_acm_mib_new_vacmMIBViews()
{
    snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews;

    vacmMIBViews = (snmp_view_based_acm_mib_vacmMIBViews_t *) g_malloc0(sizeof(snmp_view_based_acm_mib_vacmMIBViews_t) + sizeof(gpointer));
    return vacmMIBViews;
}

static inline snmp_view_based_acm_mib_vacmMIBViews_t *
assign_vacmMIBViews(GList *vbl)
{
    snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews;
    char *p;

    vacmMIBViews = snmp_view_based_acm_mib_new_vacmMIBViews();
    p = (char *) vacmMIBViews + sizeof(snmp_view_based_acm_mib_vacmMIBViews_t);
    * (GList **) p = vbl;

    gsnmp_attr_assign(vbl, vacmMIBViews_oid, sizeof(vacmMIBViews_oid)/sizeof(guint32),
                      vacmMIBViews_attr, vacmMIBViews);

    return vacmMIBViews;
}

void
snmp_view_based_acm_mib_get_vacmMIBViews(GSnmpSession *s, snmp_view_based_acm_mib_vacmMIBViews_t **vacmMIBViews, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 16, 1, 5, 0};

    *vacmMIBViews = NULL;

    gsnmp_attr_get(s, &in, base, 10, 9, vacmMIBViews_attr, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *vacmMIBViews = assign_vacmMIBViews(out);
    }
}

void
snmp_view_based_acm_mib_set_vacmMIBViews(GSnmpSession *s, snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 16, 1, 5, 0, 0};

    gsnmp_attr_set(s, &in, base, 11, 9, vacmMIBViews_attr, mask, vacmMIBViews);

    out = g_snmp_session_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
snmp_view_based_acm_mib_free_vacmMIBViews(snmp_view_based_acm_mib_vacmMIBViews_t *vacmMIBViews)
{
    GList *vbl;
    char *p;

    if (vacmMIBViews) {
        p = (char *) vacmMIBViews + sizeof(snmp_view_based_acm_mib_vacmMIBViews_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(vacmMIBViews);
    }
}

snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *
snmp_view_based_acm_mib_new_vacmViewTreeFamilyEntry()
{
    snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry;

    vacmViewTreeFamilyEntry = (snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *) g_malloc0(sizeof(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t) + sizeof(gpointer));
    return vacmViewTreeFamilyEntry;
}

static inline int
unpack_vacmViewTreeFamilyEntry(GNetSnmpVarBind *vb, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len < 1 || len > 32) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        vacmViewTreeFamilyEntry->vacmViewTreeFamilyViewName[i] = vb->oid[idx++];
    }
    vacmViewTreeFamilyEntry->_vacmViewTreeFamilyViewNameLength = len;
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (vb->oid_len < idx + len) return -1;
    if (len > 116) return -1;
    for (i = 0; i < len; i++) {
        vacmViewTreeFamilyEntry->vacmViewTreeFamilySubtree[i] = vb->oid[idx++];
    }
    vacmViewTreeFamilyEntry->_vacmViewTreeFamilySubtreeLength = len;
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_vacmViewTreeFamilyEntry(guint32 *base, guchar *vacmViewTreeFamilyViewName, guint16 _vacmViewTreeFamilyViewNameLength, guint32 *vacmViewTreeFamilySubtree, guint16 _vacmViewTreeFamilySubtreeLength)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _vacmViewTreeFamilyViewNameLength;
    base[idx++] = len;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = vacmViewTreeFamilyViewName[i];
        if (idx >= 128) return -1;
    }
    len = _vacmViewTreeFamilySubtreeLength;
    base[idx++] = len;
    if (len > 116) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = vacmViewTreeFamilySubtree[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *
assign_vacmViewTreeFamilyEntry(GList *vbl)
{
    snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry;
    char *p;

    vacmViewTreeFamilyEntry = snmp_view_based_acm_mib_new_vacmViewTreeFamilyEntry();
    p = (char *) vacmViewTreeFamilyEntry + sizeof(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t);
    * (GList **) p = vbl;

    if (unpack_vacmViewTreeFamilyEntry((GNetSnmpVarBind *) vbl->data, vacmViewTreeFamilyEntry) < 0) {
        g_warning("%s: invalid instance identifier", "vacmViewTreeFamilyEntry");
        g_free(vacmViewTreeFamilyEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, vacmViewTreeFamilyEntry_oid, sizeof(vacmViewTreeFamilyEntry_oid)/sizeof(guint32),
                      vacmViewTreeFamilyEntry_attr, vacmViewTreeFamilyEntry);

    return vacmViewTreeFamilyEntry;
}

void
snmp_view_based_acm_mib_get_vacmViewTreeFamilyTable(GSnmpSession *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t ***vacmViewTreeFamilyEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 16, 1, 5, 2, 1, 0};

    *vacmViewTreeFamilyEntry = NULL;

    gsnmp_attr_get(s, &in, base, 12, 11, vacmViewTreeFamilyEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *vacmViewTreeFamilyEntry = (snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*vacmViewTreeFamilyEntry)[i] = assign_vacmViewTreeFamilyEntry(row->data);
        }
    }
}

void
snmp_view_based_acm_mib_get_vacmViewTreeFamilyEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTreeFamilyEntry, guchar *vacmViewTreeFamilyViewName, guint16 _vacmViewTreeFamilyViewNameLength, guint32 *vacmViewTreeFamilySubtree, guint16 _vacmViewTreeFamilySubtreeLength, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, vacmViewTreeFamilyEntry_oid, sizeof(vacmViewTreeFamilyEntry_oid));
    len = pack_vacmViewTreeFamilyEntry(base, vacmViewTreeFamilyViewName, _vacmViewTreeFamilyViewNameLength, vacmViewTreeFamilySubtree, _vacmViewTreeFamilySubtreeLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "vacmViewTreeFamilyEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *vacmViewTreeFamilyEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 11, vacmViewTreeFamilyEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *vacmViewTreeFamilyEntry = assign_vacmViewTreeFamilyEntry(out);
    }
}

void
snmp_view_based_acm_mib_set_vacmViewTreeFamilyEntry(GSnmpSession *s, snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, vacmViewTreeFamilyEntry_oid, sizeof(vacmViewTreeFamilyEntry_oid));
    len = pack_vacmViewTreeFamilyEntry(base, vacmViewTreeFamilyEntry->vacmViewTreeFamilyViewName, vacmViewTreeFamilyEntry->_vacmViewTreeFamilyViewNameLength, vacmViewTreeFamilyEntry->vacmViewTreeFamilySubtree, vacmViewTreeFamilyEntry->_vacmViewTreeFamilySubtreeLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "vacmViewTreeFamilyEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 11, vacmViewTreeFamilyEntry_attr, mask, vacmViewTreeFamilyEntry);

    out = g_snmp_session_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
snmp_view_based_acm_mib_free_vacmViewTreeFamilyEntry(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t *vacmViewTreeFamilyEntry)
{
    GList *vbl;
    char *p;

    if (vacmViewTreeFamilyEntry) {
        p = (char *) vacmViewTreeFamilyEntry + sizeof(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(vacmViewTreeFamilyEntry);
    }
}

void
snmp_view_based_acm_mib_free_vacmViewTreeFamilyTable(snmp_view_based_acm_mib_vacmViewTreeFamilyEntry_t **vacmViewTreeFamilyEntry)
{
    int i;

    if (vacmViewTreeFamilyEntry) {
        for (i = 0; vacmViewTreeFamilyEntry[i]; i++) {
            snmp_view_based_acm_mib_free_vacmViewTreeFamilyEntry(vacmViewTreeFamilyEntry[i]);
        }
        g_free(vacmViewTreeFamilyEntry);
    }
}


