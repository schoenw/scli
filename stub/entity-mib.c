/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from ENTITY-MIB revision 1999-12-07 00:00.
 *
 * $Id$
 */

#include "entity-mib.h"

stls_table_t entity_mib_enums_entPhysicalClass[] = {
    { 1, "other" },
    { 2, "unknown" },
    { 3, "chassis" },
    { 4, "backplane" },
    { 5, "container" },
    { 6, "powerSupply" },
    { 7, "fan" },
    { 8, "sensor" },
    { 9, "module" },
    { 10, "port" },
    { 11, "stack" },
    { 0, NULL }
};

stls_table_t entity_mib_enums_entPhysicalIsFRU[] = {
    { 1, "true" },
    { 2, "false" },
    { 0, NULL }
};


static entPhysicalEntry_t *
assign_entPhysicalEntry(GSList *vbl)
{
    GSList *elem;
    entPhysicalEntry_t *entPhysicalEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 1, 1, 1};

    entPhysicalEntry = (entPhysicalEntry_t *) g_malloc0(sizeof(entPhysicalEntry_t) + sizeof(GSList *));
    if (! entPhysicalEntry) {
        return NULL;
    }

    p = (char *) entPhysicalEntry + sizeof(entPhysicalEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        entPhysicalEntry->entPhysicalIndex = (gint32 *) &(vb->id[12]);
        if (vb->id_len > 13) return NULL;
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
        if (vb->id_len > 12 && vb->id[11] == 2) {
            entPhysicalEntry->_entPhysicalDescrLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalDescr = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            entPhysicalEntry->_entPhysicalVendorTypeLength = vb->syntax_len / sizeof(guint32);
            entPhysicalEntry->entPhysicalVendorType = vb->syntax.ui32;
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            entPhysicalEntry->entPhysicalContainedIn = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            entPhysicalEntry->entPhysicalClass = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            entPhysicalEntry->entPhysicalParentRelPos = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            entPhysicalEntry->_entPhysicalNameLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalName = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            entPhysicalEntry->_entPhysicalHardwareRevLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalHardwareRev = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 9) {
            entPhysicalEntry->_entPhysicalFirmwareRevLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalFirmwareRev = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 10) {
            entPhysicalEntry->_entPhysicalSoftwareRevLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalSoftwareRev = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 11) {
            entPhysicalEntry->_entPhysicalSerialNumLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalSerialNum = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 12) {
            entPhysicalEntry->_entPhysicalMfgNameLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalMfgName = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 13) {
            entPhysicalEntry->_entPhysicalModelNameLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalModelName = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 14) {
            entPhysicalEntry->_entPhysicalAliasLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalAlias = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 15) {
            entPhysicalEntry->_entPhysicalAssetIDLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalAssetID = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 16) {
            entPhysicalEntry->entPhysicalIsFRU = &(vb->syntax.i32[0]);
        }
    }

    return entPhysicalEntry;
}

int
entity_mib_get_entPhysicalEntry(host_snmp *s, entPhysicalEntry_t ***entPhysicalEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 1, 1, 1, 0};

    *entPhysicalEntry = NULL;

    base[11] = 2; stls_vbl_add_null(&in, base, 12);
    base[11] = 3; stls_vbl_add_null(&in, base, 12);
    base[11] = 4; stls_vbl_add_null(&in, base, 12);
    base[11] = 5; stls_vbl_add_null(&in, base, 12);
    base[11] = 6; stls_vbl_add_null(&in, base, 12);
    base[11] = 7; stls_vbl_add_null(&in, base, 12);
    base[11] = 8; stls_vbl_add_null(&in, base, 12);
    base[11] = 9; stls_vbl_add_null(&in, base, 12);
    base[11] = 10; stls_vbl_add_null(&in, base, 12);
    base[11] = 11; stls_vbl_add_null(&in, base, 12);
    base[11] = 12; stls_vbl_add_null(&in, base, 12);
    base[11] = 13; stls_vbl_add_null(&in, base, 12);
    base[11] = 14; stls_vbl_add_null(&in, base, 12);
    base[11] = 15; stls_vbl_add_null(&in, base, 12);
    base[11] = 16; stls_vbl_add_null(&in, base, 12);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *entPhysicalEntry = (entPhysicalEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entPhysicalEntry_t *));
    if (! *entPhysicalEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*entPhysicalEntry)[i] = assign_entPhysicalEntry(row->data);
    }

    return 0;
}

void
entity_mib_free_entPhysicalEntry(entPhysicalEntry_t **entPhysicalEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (entPhysicalEntry) {
        for (i = 0; entPhysicalEntry[i]; i++) {
            p = (char *) entPhysicalEntry[i] + sizeof(entPhysicalEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(entPhysicalEntry[i]);
        }
        g_free(entPhysicalEntry);
    }
}

static entLogicalEntry_t *
assign_entLogicalEntry(GSList *vbl)
{
    GSList *elem;
    entLogicalEntry_t *entLogicalEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 2, 1, 1};

    entLogicalEntry = (entLogicalEntry_t *) g_malloc0(sizeof(entLogicalEntry_t) + sizeof(GSList *));
    if (! entLogicalEntry) {
        return NULL;
    }

    p = (char *) entLogicalEntry + sizeof(entLogicalEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        entLogicalEntry->entLogicalIndex = (gint32 *) &(vb->id[12]);
        if (vb->id_len > 13) return NULL;
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
        if (vb->id_len > 12 && vb->id[11] == 2) {
            entLogicalEntry->_entLogicalDescrLength = vb->syntax_len;
            entLogicalEntry->entLogicalDescr = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            entLogicalEntry->_entLogicalTypeLength = vb->syntax_len / sizeof(guint32);
            entLogicalEntry->entLogicalType = vb->syntax.ui32;
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            entLogicalEntry->_entLogicalCommunityLength = vb->syntax_len;
            entLogicalEntry->entLogicalCommunity = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            entLogicalEntry->_entLogicalTAddressLength = vb->syntax_len;
            entLogicalEntry->entLogicalTAddress = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            entLogicalEntry->_entLogicalTDomainLength = vb->syntax_len / sizeof(guint32);
            entLogicalEntry->entLogicalTDomain = vb->syntax.ui32;
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            entLogicalEntry->_entLogicalContextEngineIDLength = vb->syntax_len;
            entLogicalEntry->entLogicalContextEngineID = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            entLogicalEntry->_entLogicalContextNameLength = vb->syntax_len;
            entLogicalEntry->entLogicalContextName = vb->syntax.uc;
        }
    }

    return entLogicalEntry;
}

int
entity_mib_get_entLogicalEntry(host_snmp *s, entLogicalEntry_t ***entLogicalEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 2, 1, 1, 0};

    *entLogicalEntry = NULL;

    base[11] = 2; stls_vbl_add_null(&in, base, 12);
    base[11] = 3; stls_vbl_add_null(&in, base, 12);
    base[11] = 4; stls_vbl_add_null(&in, base, 12);
    base[11] = 5; stls_vbl_add_null(&in, base, 12);
    base[11] = 6; stls_vbl_add_null(&in, base, 12);
    base[11] = 7; stls_vbl_add_null(&in, base, 12);
    base[11] = 8; stls_vbl_add_null(&in, base, 12);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *entLogicalEntry = (entLogicalEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entLogicalEntry_t *));
    if (! *entLogicalEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*entLogicalEntry)[i] = assign_entLogicalEntry(row->data);
    }

    return 0;
}

void
entity_mib_free_entLogicalEntry(entLogicalEntry_t **entLogicalEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (entLogicalEntry) {
        for (i = 0; entLogicalEntry[i]; i++) {
            p = (char *) entLogicalEntry[i] + sizeof(entLogicalEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(entLogicalEntry[i]);
        }
        g_free(entLogicalEntry);
    }
}

static entLPMappingEntry_t *
assign_entLPMappingEntry(GSList *vbl)
{
    GSList *elem;
    entLPMappingEntry_t *entLPMappingEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 1, 1};

    entLPMappingEntry = (entLPMappingEntry_t *) g_malloc0(sizeof(entLPMappingEntry_t) + sizeof(GSList *));
    if (! entLPMappingEntry) {
        return NULL;
    }

    p = (char *) entLPMappingEntry + sizeof(entLPMappingEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        entLPMappingEntry->entLogicalIndex = (gint32 *) &(vb->id[12]);
        entLPMappingEntry->entLPPhysicalIndex = (gint32 *) &(vb->id[13]);
        if (vb->id_len > 14) return NULL;
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
    }

    return entLPMappingEntry;
}

int
entity_mib_get_entLPMappingEntry(host_snmp *s, entLPMappingEntry_t ***entLPMappingEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 1, 1, 0};

    *entLPMappingEntry = NULL;


    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *entLPMappingEntry = (entLPMappingEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entLPMappingEntry_t *));
    if (! *entLPMappingEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*entLPMappingEntry)[i] = assign_entLPMappingEntry(row->data);
    }

    return 0;
}

void
entity_mib_free_entLPMappingEntry(entLPMappingEntry_t **entLPMappingEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (entLPMappingEntry) {
        for (i = 0; entLPMappingEntry[i]; i++) {
            p = (char *) entLPMappingEntry[i] + sizeof(entLPMappingEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(entLPMappingEntry[i]);
        }
        g_free(entLPMappingEntry);
    }
}

static entAliasMappingEntry_t *
assign_entAliasMappingEntry(GSList *vbl)
{
    GSList *elem;
    entAliasMappingEntry_t *entAliasMappingEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 2, 1};

    entAliasMappingEntry = (entAliasMappingEntry_t *) g_malloc0(sizeof(entAliasMappingEntry_t) + sizeof(GSList *));
    if (! entAliasMappingEntry) {
        return NULL;
    }

    p = (char *) entAliasMappingEntry + sizeof(entAliasMappingEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        entAliasMappingEntry->entPhysicalIndex = (gint32 *) &(vb->id[12]);
        entAliasMappingEntry->entAliasLogicalIndexOrZero = (gint32 *) &(vb->id[13]);
        if (vb->id_len > 14) return NULL;
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
        if (vb->id_len > 12 && vb->id[11] == 2) {
            entAliasMappingEntry->_entAliasMappingIdentifierLength = vb->syntax_len / sizeof(guint32);
            entAliasMappingEntry->entAliasMappingIdentifier = vb->syntax.ui32;
        }
    }

    return entAliasMappingEntry;
}

int
entity_mib_get_entAliasMappingEntry(host_snmp *s, entAliasMappingEntry_t ***entAliasMappingEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 2, 1, 0};

    *entAliasMappingEntry = NULL;

    base[11] = 2; stls_vbl_add_null(&in, base, 12);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *entAliasMappingEntry = (entAliasMappingEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entAliasMappingEntry_t *));
    if (! *entAliasMappingEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*entAliasMappingEntry)[i] = assign_entAliasMappingEntry(row->data);
    }

    return 0;
}

void
entity_mib_free_entAliasMappingEntry(entAliasMappingEntry_t **entAliasMappingEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (entAliasMappingEntry) {
        for (i = 0; entAliasMappingEntry[i]; i++) {
            p = (char *) entAliasMappingEntry[i] + sizeof(entAliasMappingEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(entAliasMappingEntry[i]);
        }
        g_free(entAliasMappingEntry);
    }
}

static entPhysicalContainsEntry_t *
assign_entPhysicalContainsEntry(GSList *vbl)
{
    GSList *elem;
    entPhysicalContainsEntry_t *entPhysicalContainsEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 3, 1};

    entPhysicalContainsEntry = (entPhysicalContainsEntry_t *) g_malloc0(sizeof(entPhysicalContainsEntry_t) + sizeof(GSList *));
    if (! entPhysicalContainsEntry) {
        return NULL;
    }

    p = (char *) entPhysicalContainsEntry + sizeof(entPhysicalContainsEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        entPhysicalContainsEntry->entPhysicalIndex = (gint32 *) &(vb->id[12]);
        entPhysicalContainsEntry->entPhysicalChildIndex = (gint32 *) &(vb->id[13]);
        if (vb->id_len > 14) return NULL;
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
    }

    return entPhysicalContainsEntry;
}

int
entity_mib_get_entPhysicalContainsEntry(host_snmp *s, entPhysicalContainsEntry_t ***entPhysicalContainsEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 3, 1, 0};

    *entPhysicalContainsEntry = NULL;


    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *entPhysicalContainsEntry = (entPhysicalContainsEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entPhysicalContainsEntry_t *));
    if (! *entPhysicalContainsEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*entPhysicalContainsEntry)[i] = assign_entPhysicalContainsEntry(row->data);
    }

    return 0;
}

void
entity_mib_free_entPhysicalContainsEntry(entPhysicalContainsEntry_t **entPhysicalContainsEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (entPhysicalContainsEntry) {
        for (i = 0; entPhysicalContainsEntry[i]; i++) {
            p = (char *) entPhysicalContainsEntry[i] + sizeof(entPhysicalContainsEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(entPhysicalContainsEntry[i]);
        }
        g_free(entPhysicalContainsEntry);
    }
}

static entityGeneral_t *
assign_entityGeneral(GSList *vbl)
{
    GSList *elem;
    entityGeneral_t *entityGeneral;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 4};

    entityGeneral = (entityGeneral_t *) g_malloc0(sizeof(entityGeneral_t) + sizeof(GSList *));
    if (! entityGeneral) {
        return NULL;
    }

    p = (char *) entityGeneral + sizeof(entityGeneral_t);
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
        if (vb->id_len > 10 && vb->id[9] == 1) {
            entityGeneral->entLastChangeTime = &(vb->syntax.ui32[0]);
        }
    }

    return entityGeneral;
}

int
entity_mib_get_entityGeneral(host_snmp *s, entityGeneral_t **entityGeneral)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 4, 0};

    *entityGeneral = NULL;

    base[9] = 1; stls_vbl_add_null(&in, base, 10);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *entityGeneral = assign_entityGeneral(out);

    return 0;
}

void
entity_mib_free_entityGeneral(entityGeneral_t *entityGeneral)
{
    GSList *vbl;
    char *p;

    if (entityGeneral) {
        p = (char *) entityGeneral + sizeof(entityGeneral_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(entityGeneral);
    }
}


