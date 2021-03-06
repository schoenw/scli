/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli LM-SENSORS-MIB
 *
 * Derived from LM-SENSORS-MIB:
 *   This MIB module defines objects for lm_sensor derived data.
 *
 * Revision 2000-11-05 00:00:
 *   Derived from DISKIO-MIB ex UCD.
 *
 * $Id$
 */

#include "lm-sensors-mib.h"

static guint16 lmTempSensorsDevice_constraints[] = {0U, 255U, 0, 0};
static guint16 lmFanSensorsDevice_constraints[] = {0U, 255U, 0, 0};
static guint16 lmVoltSensorsDevice_constraints[] = {0U, 255U, 0, 0};
static guint16 lmMiscSensorsDevice_constraints[] = {0U, 255U, 0, 0};


static guint32 const lmTempSensorsEntry_oid[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 2, 1};

static GNetSnmpAttribute lmTempSensorsEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      LM_SENSORS_MIB_LMTEMPSENSORSDEVICE, "lmTempSensorsDevice",
       lmTempSensorsDevice_constraints,
      G_STRUCT_OFFSET(lm_sensors_mib_lmTempSensorsEntry_t, lmTempSensorsDevice),
      G_STRUCT_OFFSET(lm_sensors_mib_lmTempSensorsEntry_t, _lmTempSensorsDeviceLength),
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      LM_SENSORS_MIB_LMTEMPSENSORSVALUE, "lmTempSensorsValue",
       NULL,
      G_STRUCT_OFFSET(lm_sensors_mib_lmTempSensorsEntry_t, lmTempSensorsValue),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const lmFanSensorsEntry_oid[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 3, 1};

static GNetSnmpAttribute lmFanSensorsEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      LM_SENSORS_MIB_LMFANSENSORSDEVICE, "lmFanSensorsDevice",
       lmFanSensorsDevice_constraints,
      G_STRUCT_OFFSET(lm_sensors_mib_lmFanSensorsEntry_t, lmFanSensorsDevice),
      G_STRUCT_OFFSET(lm_sensors_mib_lmFanSensorsEntry_t, _lmFanSensorsDeviceLength),
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      LM_SENSORS_MIB_LMFANSENSORSVALUE, "lmFanSensorsValue",
       NULL,
      G_STRUCT_OFFSET(lm_sensors_mib_lmFanSensorsEntry_t, lmFanSensorsValue),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const lmVoltSensorsEntry_oid[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 4, 1};

static GNetSnmpAttribute lmVoltSensorsEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      LM_SENSORS_MIB_LMVOLTSENSORSDEVICE, "lmVoltSensorsDevice",
       lmVoltSensorsDevice_constraints,
      G_STRUCT_OFFSET(lm_sensors_mib_lmVoltSensorsEntry_t, lmVoltSensorsDevice),
      G_STRUCT_OFFSET(lm_sensors_mib_lmVoltSensorsEntry_t, _lmVoltSensorsDeviceLength),
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      LM_SENSORS_MIB_LMVOLTSENSORSVALUE, "lmVoltSensorsValue",
       NULL,
      G_STRUCT_OFFSET(lm_sensors_mib_lmVoltSensorsEntry_t, lmVoltSensorsValue),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const lmMiscSensorsEntry_oid[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 5, 1};

static GNetSnmpAttribute lmMiscSensorsEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      LM_SENSORS_MIB_LMMISCSENSORSDEVICE, "lmMiscSensorsDevice",
       lmMiscSensorsDevice_constraints,
      G_STRUCT_OFFSET(lm_sensors_mib_lmMiscSensorsEntry_t, lmMiscSensorsDevice),
      G_STRUCT_OFFSET(lm_sensors_mib_lmMiscSensorsEntry_t, _lmMiscSensorsDeviceLength),
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      LM_SENSORS_MIB_LMMISCSENSORSVALUE, "lmMiscSensorsValue",
       NULL,
      G_STRUCT_OFFSET(lm_sensors_mib_lmMiscSensorsEntry_t, lmMiscSensorsValue),
      0,
      0 },
    { 0, 0, 0, NULL }
};


lm_sensors_mib_lmTempSensorsEntry_t *
lm_sensors_mib_new_lmTempSensorsEntry()
{
    lm_sensors_mib_lmTempSensorsEntry_t *lmTempSensorsEntry;

    lmTempSensorsEntry = (lm_sensors_mib_lmTempSensorsEntry_t *) g_malloc0(sizeof(lm_sensors_mib_lmTempSensorsEntry_t) + sizeof(gpointer));
    return lmTempSensorsEntry;
}

static inline int
unpack_lmTempSensorsEntry(GNetSnmpVarBind *vb, lm_sensors_mib_lmTempSensorsEntry_t *lmTempSensorsEntry)
{
    guint8 idx = 12;

    if (vb->oid_len < idx) return -1;
    lmTempSensorsEntry->lmTempSensorsIndex = vb->oid[idx++];
    if ((lmTempSensorsEntry->lmTempSensorsIndex < 0 || lmTempSensorsEntry->lmTempSensorsIndex > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_lmTempSensorsEntry(guint32 *base, gint32 lmTempSensorsIndex)
{
    guint8 idx = 12;

    base[idx++] = lmTempSensorsIndex;
    return idx;
}

static inline lm_sensors_mib_lmTempSensorsEntry_t *
assign_lmTempSensorsEntry(GList *vbl)
{
    lm_sensors_mib_lmTempSensorsEntry_t *lmTempSensorsEntry;
    char *p;

    lmTempSensorsEntry = lm_sensors_mib_new_lmTempSensorsEntry();
    p = (char *) lmTempSensorsEntry + sizeof(lm_sensors_mib_lmTempSensorsEntry_t);
    * (GList **) p = vbl;

    if (unpack_lmTempSensorsEntry((GNetSnmpVarBind *) vbl->data, lmTempSensorsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "lmTempSensorsEntry");
        g_free(lmTempSensorsEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, lmTempSensorsEntry_oid, G_N_ELEMENTS(lmTempSensorsEntry_oid),
                      lmTempSensorsEntry_attr, lmTempSensorsEntry);

    return lmTempSensorsEntry;
}

void
lm_sensors_mib_get_lmTempSensorsTable(GNetSnmp *s, lm_sensors_mib_lmTempSensorsEntry_t ***lmTempSensorsEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 2, 1, 0};
    guint32 base[128];

    *lmTempSensorsEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 12, 11, lmTempSensorsEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *lmTempSensorsEntry = (lm_sensors_mib_lmTempSensorsEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(lm_sensors_mib_lmTempSensorsEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*lmTempSensorsEntry)[i] = assign_lmTempSensorsEntry(row->data);
        }
    }
}

void
lm_sensors_mib_get_lmTempSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmTempSensorsEntry_t **lmTempSensorsEntry, gint32 lmTempSensorsIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, lmTempSensorsEntry_oid, sizeof(lmTempSensorsEntry_oid));
    len = pack_lmTempSensorsEntry(base, lmTempSensorsIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "lmTempSensorsEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *lmTempSensorsEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, lmTempSensorsEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *lmTempSensorsEntry = assign_lmTempSensorsEntry(out);
    }
}

void
lm_sensors_mib_free_lmTempSensorsEntry(lm_sensors_mib_lmTempSensorsEntry_t *lmTempSensorsEntry)
{
    GList *vbl;
    char *p;

    if (lmTempSensorsEntry) {
        p = (char *) lmTempSensorsEntry + sizeof(lm_sensors_mib_lmTempSensorsEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(lmTempSensorsEntry);
    }
}

void
lm_sensors_mib_free_lmTempSensorsTable(lm_sensors_mib_lmTempSensorsEntry_t **lmTempSensorsEntry)
{
    int i;

    if (lmTempSensorsEntry) {
        for (i = 0; lmTempSensorsEntry[i]; i++) {
            lm_sensors_mib_free_lmTempSensorsEntry(lmTempSensorsEntry[i]);
        }
        g_free(lmTempSensorsEntry);
    }
}

lm_sensors_mib_lmFanSensorsEntry_t *
lm_sensors_mib_new_lmFanSensorsEntry()
{
    lm_sensors_mib_lmFanSensorsEntry_t *lmFanSensorsEntry;

    lmFanSensorsEntry = (lm_sensors_mib_lmFanSensorsEntry_t *) g_malloc0(sizeof(lm_sensors_mib_lmFanSensorsEntry_t) + sizeof(gpointer));
    return lmFanSensorsEntry;
}

static inline int
unpack_lmFanSensorsEntry(GNetSnmpVarBind *vb, lm_sensors_mib_lmFanSensorsEntry_t *lmFanSensorsEntry)
{
    guint8 idx = 12;

    if (vb->oid_len < idx) return -1;
    lmFanSensorsEntry->lmFanSensorsIndex = vb->oid[idx++];
    if ((lmFanSensorsEntry->lmFanSensorsIndex < 0 || lmFanSensorsEntry->lmFanSensorsIndex > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_lmFanSensorsEntry(guint32 *base, gint32 lmFanSensorsIndex)
{
    guint8 idx = 12;

    base[idx++] = lmFanSensorsIndex;
    return idx;
}

static inline lm_sensors_mib_lmFanSensorsEntry_t *
assign_lmFanSensorsEntry(GList *vbl)
{
    lm_sensors_mib_lmFanSensorsEntry_t *lmFanSensorsEntry;
    char *p;

    lmFanSensorsEntry = lm_sensors_mib_new_lmFanSensorsEntry();
    p = (char *) lmFanSensorsEntry + sizeof(lm_sensors_mib_lmFanSensorsEntry_t);
    * (GList **) p = vbl;

    if (unpack_lmFanSensorsEntry((GNetSnmpVarBind *) vbl->data, lmFanSensorsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "lmFanSensorsEntry");
        g_free(lmFanSensorsEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, lmFanSensorsEntry_oid, G_N_ELEMENTS(lmFanSensorsEntry_oid),
                      lmFanSensorsEntry_attr, lmFanSensorsEntry);

    return lmFanSensorsEntry;
}

void
lm_sensors_mib_get_lmFanSensorsTable(GNetSnmp *s, lm_sensors_mib_lmFanSensorsEntry_t ***lmFanSensorsEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 3, 1, 0};
    guint32 base[128];

    *lmFanSensorsEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 12, 11, lmFanSensorsEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *lmFanSensorsEntry = (lm_sensors_mib_lmFanSensorsEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(lm_sensors_mib_lmFanSensorsEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*lmFanSensorsEntry)[i] = assign_lmFanSensorsEntry(row->data);
        }
    }
}

void
lm_sensors_mib_get_lmFanSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmFanSensorsEntry_t **lmFanSensorsEntry, gint32 lmFanSensorsIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, lmFanSensorsEntry_oid, sizeof(lmFanSensorsEntry_oid));
    len = pack_lmFanSensorsEntry(base, lmFanSensorsIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "lmFanSensorsEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *lmFanSensorsEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, lmFanSensorsEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *lmFanSensorsEntry = assign_lmFanSensorsEntry(out);
    }
}

void
lm_sensors_mib_free_lmFanSensorsEntry(lm_sensors_mib_lmFanSensorsEntry_t *lmFanSensorsEntry)
{
    GList *vbl;
    char *p;

    if (lmFanSensorsEntry) {
        p = (char *) lmFanSensorsEntry + sizeof(lm_sensors_mib_lmFanSensorsEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(lmFanSensorsEntry);
    }
}

void
lm_sensors_mib_free_lmFanSensorsTable(lm_sensors_mib_lmFanSensorsEntry_t **lmFanSensorsEntry)
{
    int i;

    if (lmFanSensorsEntry) {
        for (i = 0; lmFanSensorsEntry[i]; i++) {
            lm_sensors_mib_free_lmFanSensorsEntry(lmFanSensorsEntry[i]);
        }
        g_free(lmFanSensorsEntry);
    }
}

lm_sensors_mib_lmVoltSensorsEntry_t *
lm_sensors_mib_new_lmVoltSensorsEntry()
{
    lm_sensors_mib_lmVoltSensorsEntry_t *lmVoltSensorsEntry;

    lmVoltSensorsEntry = (lm_sensors_mib_lmVoltSensorsEntry_t *) g_malloc0(sizeof(lm_sensors_mib_lmVoltSensorsEntry_t) + sizeof(gpointer));
    return lmVoltSensorsEntry;
}

static inline int
unpack_lmVoltSensorsEntry(GNetSnmpVarBind *vb, lm_sensors_mib_lmVoltSensorsEntry_t *lmVoltSensorsEntry)
{
    guint8 idx = 12;

    if (vb->oid_len < idx) return -1;
    lmVoltSensorsEntry->lmVoltSensorsIndex = vb->oid[idx++];
    if ((lmVoltSensorsEntry->lmVoltSensorsIndex < 0 || lmVoltSensorsEntry->lmVoltSensorsIndex > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_lmVoltSensorsEntry(guint32 *base, gint32 lmVoltSensorsIndex)
{
    guint8 idx = 12;

    base[idx++] = lmVoltSensorsIndex;
    return idx;
}

static inline lm_sensors_mib_lmVoltSensorsEntry_t *
assign_lmVoltSensorsEntry(GList *vbl)
{
    lm_sensors_mib_lmVoltSensorsEntry_t *lmVoltSensorsEntry;
    char *p;

    lmVoltSensorsEntry = lm_sensors_mib_new_lmVoltSensorsEntry();
    p = (char *) lmVoltSensorsEntry + sizeof(lm_sensors_mib_lmVoltSensorsEntry_t);
    * (GList **) p = vbl;

    if (unpack_lmVoltSensorsEntry((GNetSnmpVarBind *) vbl->data, lmVoltSensorsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "lmVoltSensorsEntry");
        g_free(lmVoltSensorsEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, lmVoltSensorsEntry_oid, G_N_ELEMENTS(lmVoltSensorsEntry_oid),
                      lmVoltSensorsEntry_attr, lmVoltSensorsEntry);

    return lmVoltSensorsEntry;
}

void
lm_sensors_mib_get_lmVoltSensorsTable(GNetSnmp *s, lm_sensors_mib_lmVoltSensorsEntry_t ***lmVoltSensorsEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 4, 1, 0};
    guint32 base[128];

    *lmVoltSensorsEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 12, 11, lmVoltSensorsEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *lmVoltSensorsEntry = (lm_sensors_mib_lmVoltSensorsEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(lm_sensors_mib_lmVoltSensorsEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*lmVoltSensorsEntry)[i] = assign_lmVoltSensorsEntry(row->data);
        }
    }
}

void
lm_sensors_mib_get_lmVoltSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmVoltSensorsEntry_t **lmVoltSensorsEntry, gint32 lmVoltSensorsIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, lmVoltSensorsEntry_oid, sizeof(lmVoltSensorsEntry_oid));
    len = pack_lmVoltSensorsEntry(base, lmVoltSensorsIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "lmVoltSensorsEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *lmVoltSensorsEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, lmVoltSensorsEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *lmVoltSensorsEntry = assign_lmVoltSensorsEntry(out);
    }
}

void
lm_sensors_mib_free_lmVoltSensorsEntry(lm_sensors_mib_lmVoltSensorsEntry_t *lmVoltSensorsEntry)
{
    GList *vbl;
    char *p;

    if (lmVoltSensorsEntry) {
        p = (char *) lmVoltSensorsEntry + sizeof(lm_sensors_mib_lmVoltSensorsEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(lmVoltSensorsEntry);
    }
}

void
lm_sensors_mib_free_lmVoltSensorsTable(lm_sensors_mib_lmVoltSensorsEntry_t **lmVoltSensorsEntry)
{
    int i;

    if (lmVoltSensorsEntry) {
        for (i = 0; lmVoltSensorsEntry[i]; i++) {
            lm_sensors_mib_free_lmVoltSensorsEntry(lmVoltSensorsEntry[i]);
        }
        g_free(lmVoltSensorsEntry);
    }
}

lm_sensors_mib_lmMiscSensorsEntry_t *
lm_sensors_mib_new_lmMiscSensorsEntry()
{
    lm_sensors_mib_lmMiscSensorsEntry_t *lmMiscSensorsEntry;

    lmMiscSensorsEntry = (lm_sensors_mib_lmMiscSensorsEntry_t *) g_malloc0(sizeof(lm_sensors_mib_lmMiscSensorsEntry_t) + sizeof(gpointer));
    return lmMiscSensorsEntry;
}

static inline int
unpack_lmMiscSensorsEntry(GNetSnmpVarBind *vb, lm_sensors_mib_lmMiscSensorsEntry_t *lmMiscSensorsEntry)
{
    guint8 idx = 12;

    if (vb->oid_len < idx) return -1;
    lmMiscSensorsEntry->lmMiscSensorsIndex = vb->oid[idx++];
    if ((lmMiscSensorsEntry->lmMiscSensorsIndex < 0 || lmMiscSensorsEntry->lmMiscSensorsIndex > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_lmMiscSensorsEntry(guint32 *base, gint32 lmMiscSensorsIndex)
{
    guint8 idx = 12;

    base[idx++] = lmMiscSensorsIndex;
    return idx;
}

static inline lm_sensors_mib_lmMiscSensorsEntry_t *
assign_lmMiscSensorsEntry(GList *vbl)
{
    lm_sensors_mib_lmMiscSensorsEntry_t *lmMiscSensorsEntry;
    char *p;

    lmMiscSensorsEntry = lm_sensors_mib_new_lmMiscSensorsEntry();
    p = (char *) lmMiscSensorsEntry + sizeof(lm_sensors_mib_lmMiscSensorsEntry_t);
    * (GList **) p = vbl;

    if (unpack_lmMiscSensorsEntry((GNetSnmpVarBind *) vbl->data, lmMiscSensorsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "lmMiscSensorsEntry");
        g_free(lmMiscSensorsEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, lmMiscSensorsEntry_oid, G_N_ELEMENTS(lmMiscSensorsEntry_oid),
                      lmMiscSensorsEntry_attr, lmMiscSensorsEntry);

    return lmMiscSensorsEntry;
}

void
lm_sensors_mib_get_lmMiscSensorsTable(GNetSnmp *s, lm_sensors_mib_lmMiscSensorsEntry_t ***lmMiscSensorsEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 4, 1, 2021, 13, 16, 5, 1, 0};
    guint32 base[128];

    *lmMiscSensorsEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 12, 11, lmMiscSensorsEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *lmMiscSensorsEntry = (lm_sensors_mib_lmMiscSensorsEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(lm_sensors_mib_lmMiscSensorsEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*lmMiscSensorsEntry)[i] = assign_lmMiscSensorsEntry(row->data);
        }
    }
}

void
lm_sensors_mib_get_lmMiscSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmMiscSensorsEntry_t **lmMiscSensorsEntry, gint32 lmMiscSensorsIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, lmMiscSensorsEntry_oid, sizeof(lmMiscSensorsEntry_oid));
    len = pack_lmMiscSensorsEntry(base, lmMiscSensorsIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "lmMiscSensorsEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *lmMiscSensorsEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, lmMiscSensorsEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *lmMiscSensorsEntry = assign_lmMiscSensorsEntry(out);
    }
}

void
lm_sensors_mib_free_lmMiscSensorsEntry(lm_sensors_mib_lmMiscSensorsEntry_t *lmMiscSensorsEntry)
{
    GList *vbl;
    char *p;

    if (lmMiscSensorsEntry) {
        p = (char *) lmMiscSensorsEntry + sizeof(lm_sensors_mib_lmMiscSensorsEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(lmMiscSensorsEntry);
    }
}

void
lm_sensors_mib_free_lmMiscSensorsTable(lm_sensors_mib_lmMiscSensorsEntry_t **lmMiscSensorsEntry)
{
    int i;

    if (lmMiscSensorsEntry) {
        for (i = 0; lmMiscSensorsEntry[i]; i++) {
            lm_sensors_mib_free_lmMiscSensorsEntry(lmMiscSensorsEntry[i]);
        }
        g_free(lmMiscSensorsEntry);
    }
}


