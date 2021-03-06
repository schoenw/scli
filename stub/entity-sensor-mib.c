/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli ENTITY-SENSOR-MIB
 *
 * Derived from ENTITY-SENSOR-MIB:
 *   This module defines Entity MIB extensions for physical
 *   sensors.
 *   
 *   Copyright (C) The Internet Society (2002). This version
 *   of this MIB module is part of RFC 3433; see the RFC
 *   itself for full legal notices.
 *
 * Revision 2002-12-16 00:00:
 *   Initial version of the Entity Sensor MIB module, published
 *   as RFC 3433.
 *
 * $Id$
 */

#include "entity-sensor-mib.h"

GNetSnmpEnum const entity_sensor_mib_enums_EntitySensorDataType[] = {
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_OTHER,      "other" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_UNKNOWN,    "unknown" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_VOLTSAC,    "voltsAC" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_VOLTSDC,    "voltsDC" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_AMPERES,    "amperes" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_WATTS,      "watts" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_HERTZ,      "hertz" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_CELSIUS,    "celsius" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_PERCENTRH,  "percentRH" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_RPM,        "rpm" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_CMM,        "cmm" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_TRUTHVALUE, "truthvalue" },
    { 0, NULL }
};

GNetSnmpEnum const entity_sensor_mib_enums_EntitySensorDataScale[] = {
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_YOCTO, "yocto" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_ZEPTO, "zepto" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_ATTO,  "atto" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_FEMTO, "femto" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_PICO,  "pico" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_NANO,  "nano" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_MICRO, "micro" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_MILLI, "milli" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_UNITS, "units" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_KILO,  "kilo" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_MEGA,  "mega" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_GIGA,  "giga" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_TERA,  "tera" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_EXA,   "exa" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_PETA,  "peta" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_ZETTA, "zetta" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_YOTTA, "yotta" },
    { 0, NULL }
};

GNetSnmpEnum const entity_sensor_mib_enums_EntitySensorStatus[] = {
    { ENTITY_SENSOR_MIB_ENTITYSENSORSTATUS_OK,             "ok" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORSTATUS_UNAVAILABLE,    "unavailable" },
    { ENTITY_SENSOR_MIB_ENTITYSENSORSTATUS_NONOPERATIONAL, "nonoperational" },
    { 0, NULL }
};


static gint32 entPhySensorPrecision_constraints[] = {-8L, 9L, 0, 0};
static gint32 entPhySensorValue_constraints[] = {-1000000000L, 1000000000L, 0, 0};
static guint16 entPhySensorUnitsDisplay_constraints[] = {0U, 255U, 0, 0};


static guint32 const entPhySensorEntry_oid[] = {1, 3, 6, 1, 2, 1, 99, 1, 1, 1};

static GNetSnmpAttribute entPhySensorEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ENTITY_SENSOR_MIB_ENTPHYSENSORTYPE, "entPhySensorType",
       NULL,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorType),
      0,
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ENTITY_SENSOR_MIB_ENTPHYSENSORSCALE, "entPhySensorScale",
       NULL,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorScale),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ENTITY_SENSOR_MIB_ENTPHYSENSORPRECISION, "entPhySensorPrecision",
       entPhySensorPrecision_constraints,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorPrecision),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ENTITY_SENSOR_MIB_ENTPHYSENSORVALUE, "entPhySensorValue",
       entPhySensorValue_constraints,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorValue),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ENTITY_SENSOR_MIB_ENTPHYSENSOROPERSTATUS, "entPhySensorOperStatus",
       NULL,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorOperStatus),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      ENTITY_SENSOR_MIB_ENTPHYSENSORUNITSDISPLAY, "entPhySensorUnitsDisplay",
       entPhySensorUnitsDisplay_constraints,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorUnitsDisplay),
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, _entPhySensorUnitsDisplayLength),
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_TIMETICKS,
      ENTITY_SENSOR_MIB_ENTPHYSENSORVALUETIMESTAMP, "entPhySensorValueTimeStamp",
       NULL,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorValueTimeStamp),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      ENTITY_SENSOR_MIB_ENTPHYSENSORVALUEUPDATERATE, "entPhySensorValueUpdateRate",
       NULL,
      G_STRUCT_OFFSET(entity_sensor_mib_entPhySensorEntry_t, entPhySensorValueUpdateRate),
      0,
      0 },
    { 0, 0, 0, NULL }
};


entity_sensor_mib_entPhySensorEntry_t *
entity_sensor_mib_new_entPhySensorEntry()
{
    entity_sensor_mib_entPhySensorEntry_t *entPhySensorEntry;

    entPhySensorEntry = (entity_sensor_mib_entPhySensorEntry_t *) g_malloc0(sizeof(entity_sensor_mib_entPhySensorEntry_t) + sizeof(gpointer));
    return entPhySensorEntry;
}

static inline int
unpack_entPhySensorEntry(GNetSnmpVarBind *vb, entity_sensor_mib_entPhySensorEntry_t *entPhySensorEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    entPhySensorEntry->entPhysicalIndex = vb->oid[idx++];
    if ((entPhySensorEntry->entPhysicalIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_entPhySensorEntry(guint32 *base, gint32 entPhysicalIndex)
{
    guint8 idx = 11;

    base[idx++] = entPhysicalIndex;
    return idx;
}

static inline entity_sensor_mib_entPhySensorEntry_t *
assign_entPhySensorEntry(GList *vbl)
{
    entity_sensor_mib_entPhySensorEntry_t *entPhySensorEntry;
    char *p;

    entPhySensorEntry = entity_sensor_mib_new_entPhySensorEntry();
    p = (char *) entPhySensorEntry + sizeof(entity_sensor_mib_entPhySensorEntry_t);
    * (GList **) p = vbl;

    if (unpack_entPhySensorEntry((GNetSnmpVarBind *) vbl->data, entPhySensorEntry) < 0) {
        g_warning("%s: invalid instance identifier", "entPhySensorEntry");
        g_free(entPhySensorEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, entPhySensorEntry_oid, G_N_ELEMENTS(entPhySensorEntry_oid),
                      entPhySensorEntry_attr, entPhySensorEntry);

    return entPhySensorEntry;
}

void
entity_sensor_mib_get_entPhySensorTable(GNetSnmp *s, entity_sensor_mib_entPhySensorEntry_t ***entPhySensorEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 99, 1, 1, 1, 0};
    guint32 base[128];

    *entPhySensorEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, entPhySensorEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *entPhySensorEntry = (entity_sensor_mib_entPhySensorEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(entity_sensor_mib_entPhySensorEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*entPhySensorEntry)[i] = assign_entPhySensorEntry(row->data);
        }
    }
}

void
entity_sensor_mib_get_entPhySensorEntry(GNetSnmp *s, entity_sensor_mib_entPhySensorEntry_t **entPhySensorEntry, gint32 entPhysicalIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, entPhySensorEntry_oid, sizeof(entPhySensorEntry_oid));
    len = pack_entPhySensorEntry(base, entPhysicalIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "entPhySensorEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *entPhySensorEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, entPhySensorEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *entPhySensorEntry = assign_entPhySensorEntry(out);
    }
}

void
entity_sensor_mib_free_entPhySensorEntry(entity_sensor_mib_entPhySensorEntry_t *entPhySensorEntry)
{
    GList *vbl;
    char *p;

    if (entPhySensorEntry) {
        p = (char *) entPhySensorEntry + sizeof(entity_sensor_mib_entPhySensorEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(entPhySensorEntry);
    }
}

void
entity_sensor_mib_free_entPhySensorTable(entity_sensor_mib_entPhySensorEntry_t **entPhySensorEntry)
{
    int i;

    if (entPhySensorEntry) {
        for (i = 0; entPhySensorEntry[i]; i++) {
            entity_sensor_mib_free_entPhySensorEntry(entPhySensorEntry[i]);
        }
        g_free(entPhySensorEntry);
    }
}


