/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from ENTITY-MIB:
 *   The MIB module for representing multiple logical
 *   entities supported by a single SNMP agent.
 *
 * Revision 1999-12-07 00:00:
 *   Initial Version of Entity MIB (Version 2).
 *   This revision obsoletes RFC 2037.
 *   This version published as RFC 2737.
 *
 * Revision 1996-10-31 00:00:
 *   Initial version (version 1), published as
 *   RFC 2037.
 *
 * $Id$
 */

#include "entity-mib.h"

stls_table_t const entity_mib_enums_entPhysicalClass[] = {
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

stls_table_t const entity_mib_enums_entPhysicalIsFRU[] = {
    { 1, "true" },
    { 2, "false" },
    { 0, NULL }
};


entPhysicalEntry_t *
entity_mib_new_entPhysicalEntry()
{
    entPhysicalEntry_t *entPhysicalEntry;

    entPhysicalEntry = (entPhysicalEntry_t *) g_malloc0(sizeof(entPhysicalEntry_t) + sizeof(gpointer));
    return entPhysicalEntry;
}

static int
unpack_entPhysicalEntry(GSnmpVarBind *vb, entPhysicalEntry_t *entPhysicalEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entPhysicalEntry->entPhysicalIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static entPhysicalEntry_t *
assign_entPhysicalEntry(GSList *vbl)
{
    GSList *elem;
    entPhysicalEntry_t *entPhysicalEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 1, 1, 1};

    entPhysicalEntry = entity_mib_new_entPhysicalEntry();
    if (! entPhysicalEntry) {
        return NULL;
    }

    p = (char *) entPhysicalEntry + sizeof(entPhysicalEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entPhysicalEntry((GSnmpVarBind *) vbl->data, entPhysicalEntry) < 0) {
        g_warning("illegal entPhysicalEntry instance identifier");
        g_free(entPhysicalEntry);
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
        if (vb->id_len > 12 && vb->id[11] == 2) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalDescrLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalDescr = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalDescr");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            if (vb->type == G_SNMP_OBJECT_ID) {
                entPhysicalEntry->_entPhysicalVendorTypeLength = vb->syntax_len / sizeof(guint32);
                entPhysicalEntry->entPhysicalVendorType = vb->syntax.ui32;
            } else {
                g_warning("illegal type for entPhysicalVendorType");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            if (vb->type == G_SNMP_INTEGER32) {
                entPhysicalEntry->entPhysicalContainedIn = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for entPhysicalContainedIn");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            if (vb->type == G_SNMP_INTEGER32) {
                entPhysicalEntry->entPhysicalClass = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for entPhysicalClass");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            if (vb->type == G_SNMP_INTEGER32) {
                entPhysicalEntry->entPhysicalParentRelPos = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for entPhysicalParentRelPos");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalNameLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalName = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalName");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalHardwareRevLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalHardwareRev = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalHardwareRev");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 9) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalFirmwareRevLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalFirmwareRev = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalFirmwareRev");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 10) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalSoftwareRevLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalSoftwareRev = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalSoftwareRev");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 11) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalSerialNumLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalSerialNum = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalSerialNum");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 12) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalMfgNameLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalMfgName = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalMfgName");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 13) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalModelNameLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalModelName = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalModelName");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 14) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalAliasLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalAlias = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalAlias");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 15) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entPhysicalEntry->_entPhysicalAssetIDLength = vb->syntax_len;
                entPhysicalEntry->entPhysicalAssetID = vb->syntax.uc;
            } else {
                g_warning("illegal type for entPhysicalAssetID");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 16) {
            if (vb->type == G_SNMP_INTEGER32) {
                entPhysicalEntry->entPhysicalIsFRU = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for entPhysicalIsFRU");
            }
        }
    }

    return entPhysicalEntry;
}

int
entity_mib_get_entPhysicalTable(host_snmp *s, entPhysicalEntry_t ***entPhysicalEntry)
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
entity_mib_free_entPhysicalEntry(entPhysicalEntry_t *entPhysicalEntry)
{
    GSList *vbl;
    char *p;

    if (entPhysicalEntry) {
        p = (char *) entPhysicalEntry + sizeof(entPhysicalEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(entPhysicalEntry);
    }
}

void
entity_mib_free_entPhysicalTable(entPhysicalEntry_t **entPhysicalEntry)
{
    int i;

    if (entPhysicalEntry) {
        for (i = 0; entPhysicalEntry[i]; i++) {
            entity_mib_free_entPhysicalEntry(entPhysicalEntry[i]);
        }
        g_free(entPhysicalEntry);
    }
}

entLogicalEntry_t *
entity_mib_new_entLogicalEntry()
{
    entLogicalEntry_t *entLogicalEntry;

    entLogicalEntry = (entLogicalEntry_t *) g_malloc0(sizeof(entLogicalEntry_t) + sizeof(gpointer));
    return entLogicalEntry;
}

static int
unpack_entLogicalEntry(GSnmpVarBind *vb, entLogicalEntry_t *entLogicalEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entLogicalEntry->entLogicalIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static entLogicalEntry_t *
assign_entLogicalEntry(GSList *vbl)
{
    GSList *elem;
    entLogicalEntry_t *entLogicalEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 2, 1, 1};

    entLogicalEntry = entity_mib_new_entLogicalEntry();
    if (! entLogicalEntry) {
        return NULL;
    }

    p = (char *) entLogicalEntry + sizeof(entLogicalEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entLogicalEntry((GSnmpVarBind *) vbl->data, entLogicalEntry) < 0) {
        g_warning("illegal entLogicalEntry instance identifier");
        g_free(entLogicalEntry);
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
        if (vb->id_len > 12 && vb->id[11] == 2) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entLogicalEntry->_entLogicalDescrLength = vb->syntax_len;
                entLogicalEntry->entLogicalDescr = vb->syntax.uc;
            } else {
                g_warning("illegal type for entLogicalDescr");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            if (vb->type == G_SNMP_OBJECT_ID) {
                entLogicalEntry->_entLogicalTypeLength = vb->syntax_len / sizeof(guint32);
                entLogicalEntry->entLogicalType = vb->syntax.ui32;
            } else {
                g_warning("illegal type for entLogicalType");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entLogicalEntry->_entLogicalCommunityLength = vb->syntax_len;
                entLogicalEntry->entLogicalCommunity = vb->syntax.uc;
            } else {
                g_warning("illegal type for entLogicalCommunity");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entLogicalEntry->_entLogicalTAddressLength = vb->syntax_len;
                entLogicalEntry->entLogicalTAddress = vb->syntax.uc;
            } else {
                g_warning("illegal type for entLogicalTAddress");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            if (vb->type == G_SNMP_OBJECT_ID) {
                entLogicalEntry->_entLogicalTDomainLength = vb->syntax_len / sizeof(guint32);
                entLogicalEntry->entLogicalTDomain = vb->syntax.ui32;
            } else {
                g_warning("illegal type for entLogicalTDomain");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entLogicalEntry->_entLogicalContextEngineIDLength = vb->syntax_len;
                entLogicalEntry->entLogicalContextEngineID = vb->syntax.uc;
            } else {
                g_warning("illegal type for entLogicalContextEngineID");
            }
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                entLogicalEntry->_entLogicalContextNameLength = vb->syntax_len;
                entLogicalEntry->entLogicalContextName = vb->syntax.uc;
            } else {
                g_warning("illegal type for entLogicalContextName");
            }
        }
    }

    return entLogicalEntry;
}

int
entity_mib_get_entLogicalTable(host_snmp *s, entLogicalEntry_t ***entLogicalEntry)
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
entity_mib_free_entLogicalEntry(entLogicalEntry_t *entLogicalEntry)
{
    GSList *vbl;
    char *p;

    if (entLogicalEntry) {
        p = (char *) entLogicalEntry + sizeof(entLogicalEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(entLogicalEntry);
    }
}

void
entity_mib_free_entLogicalTable(entLogicalEntry_t **entLogicalEntry)
{
    int i;

    if (entLogicalEntry) {
        for (i = 0; entLogicalEntry[i]; i++) {
            entity_mib_free_entLogicalEntry(entLogicalEntry[i]);
        }
        g_free(entLogicalEntry);
    }
}

entLPMappingEntry_t *
entity_mib_new_entLPMappingEntry()
{
    entLPMappingEntry_t *entLPMappingEntry;

    entLPMappingEntry = (entLPMappingEntry_t *) g_malloc0(sizeof(entLPMappingEntry_t) + sizeof(gpointer));
    return entLPMappingEntry;
}

static int
unpack_entLPMappingEntry(GSnmpVarBind *vb, entLPMappingEntry_t *entLPMappingEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entLPMappingEntry->entLogicalIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    entLPMappingEntry->entLPPhysicalIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static entLPMappingEntry_t *
assign_entLPMappingEntry(GSList *vbl)
{
    GSList *elem;
    entLPMappingEntry_t *entLPMappingEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 1, 1};

    entLPMappingEntry = entity_mib_new_entLPMappingEntry();
    if (! entLPMappingEntry) {
        return NULL;
    }

    p = (char *) entLPMappingEntry + sizeof(entLPMappingEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entLPMappingEntry((GSnmpVarBind *) vbl->data, entLPMappingEntry) < 0) {
        g_warning("illegal entLPMappingEntry instance identifier");
        g_free(entLPMappingEntry);
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
    }

    return entLPMappingEntry;
}

int
entity_mib_get_entLPMappingTable(host_snmp *s, entLPMappingEntry_t ***entLPMappingEntry)
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
entity_mib_free_entLPMappingEntry(entLPMappingEntry_t *entLPMappingEntry)
{
    GSList *vbl;
    char *p;

    if (entLPMappingEntry) {
        p = (char *) entLPMappingEntry + sizeof(entLPMappingEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(entLPMappingEntry);
    }
}

void
entity_mib_free_entLPMappingTable(entLPMappingEntry_t **entLPMappingEntry)
{
    int i;

    if (entLPMappingEntry) {
        for (i = 0; entLPMappingEntry[i]; i++) {
            entity_mib_free_entLPMappingEntry(entLPMappingEntry[i]);
        }
        g_free(entLPMappingEntry);
    }
}

entAliasMappingEntry_t *
entity_mib_new_entAliasMappingEntry()
{
    entAliasMappingEntry_t *entAliasMappingEntry;

    entAliasMappingEntry = (entAliasMappingEntry_t *) g_malloc0(sizeof(entAliasMappingEntry_t) + sizeof(gpointer));
    return entAliasMappingEntry;
}

static int
unpack_entAliasMappingEntry(GSnmpVarBind *vb, entAliasMappingEntry_t *entAliasMappingEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entAliasMappingEntry->entPhysicalIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    entAliasMappingEntry->entAliasLogicalIndexOrZero = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static entAliasMappingEntry_t *
assign_entAliasMappingEntry(GSList *vbl)
{
    GSList *elem;
    entAliasMappingEntry_t *entAliasMappingEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 2, 1};

    entAliasMappingEntry = entity_mib_new_entAliasMappingEntry();
    if (! entAliasMappingEntry) {
        return NULL;
    }

    p = (char *) entAliasMappingEntry + sizeof(entAliasMappingEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entAliasMappingEntry((GSnmpVarBind *) vbl->data, entAliasMappingEntry) < 0) {
        g_warning("illegal entAliasMappingEntry instance identifier");
        g_free(entAliasMappingEntry);
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
        if (vb->id_len > 12 && vb->id[11] == 2) {
            if (vb->type == G_SNMP_OBJECT_ID) {
                entAliasMappingEntry->_entAliasMappingIdentifierLength = vb->syntax_len / sizeof(guint32);
                entAliasMappingEntry->entAliasMappingIdentifier = vb->syntax.ui32;
            } else {
                g_warning("illegal type for entAliasMappingIdentifier");
            }
        }
    }

    return entAliasMappingEntry;
}

int
entity_mib_get_entAliasMappingTable(host_snmp *s, entAliasMappingEntry_t ***entAliasMappingEntry)
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
entity_mib_free_entAliasMappingEntry(entAliasMappingEntry_t *entAliasMappingEntry)
{
    GSList *vbl;
    char *p;

    if (entAliasMappingEntry) {
        p = (char *) entAliasMappingEntry + sizeof(entAliasMappingEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(entAliasMappingEntry);
    }
}

void
entity_mib_free_entAliasMappingTable(entAliasMappingEntry_t **entAliasMappingEntry)
{
    int i;

    if (entAliasMappingEntry) {
        for (i = 0; entAliasMappingEntry[i]; i++) {
            entity_mib_free_entAliasMappingEntry(entAliasMappingEntry[i]);
        }
        g_free(entAliasMappingEntry);
    }
}

entPhysicalContainsEntry_t *
entity_mib_new_entPhysicalContainsEntry()
{
    entPhysicalContainsEntry_t *entPhysicalContainsEntry;

    entPhysicalContainsEntry = (entPhysicalContainsEntry_t *) g_malloc0(sizeof(entPhysicalContainsEntry_t) + sizeof(gpointer));
    return entPhysicalContainsEntry;
}

static int
unpack_entPhysicalContainsEntry(GSnmpVarBind *vb, entPhysicalContainsEntry_t *entPhysicalContainsEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entPhysicalContainsEntry->entPhysicalIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    entPhysicalContainsEntry->entPhysicalChildIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static entPhysicalContainsEntry_t *
assign_entPhysicalContainsEntry(GSList *vbl)
{
    GSList *elem;
    entPhysicalContainsEntry_t *entPhysicalContainsEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 3, 1};

    entPhysicalContainsEntry = entity_mib_new_entPhysicalContainsEntry();
    if (! entPhysicalContainsEntry) {
        return NULL;
    }

    p = (char *) entPhysicalContainsEntry + sizeof(entPhysicalContainsEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entPhysicalContainsEntry((GSnmpVarBind *) vbl->data, entPhysicalContainsEntry) < 0) {
        g_warning("illegal entPhysicalContainsEntry instance identifier");
        g_free(entPhysicalContainsEntry);
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
    }

    return entPhysicalContainsEntry;
}

int
entity_mib_get_entPhysicalContainsTable(host_snmp *s, entPhysicalContainsEntry_t ***entPhysicalContainsEntry)
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
entity_mib_free_entPhysicalContainsEntry(entPhysicalContainsEntry_t *entPhysicalContainsEntry)
{
    GSList *vbl;
    char *p;

    if (entPhysicalContainsEntry) {
        p = (char *) entPhysicalContainsEntry + sizeof(entPhysicalContainsEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(entPhysicalContainsEntry);
    }
}

void
entity_mib_free_entPhysicalContainsTable(entPhysicalContainsEntry_t **entPhysicalContainsEntry)
{
    int i;

    if (entPhysicalContainsEntry) {
        for (i = 0; entPhysicalContainsEntry[i]; i++) {
            entity_mib_free_entPhysicalContainsEntry(entPhysicalContainsEntry[i]);
        }
        g_free(entPhysicalContainsEntry);
    }
}

entityGeneral_t *
entity_mib_new_entityGeneral()
{
    entityGeneral_t *entityGeneral;

    entityGeneral = (entityGeneral_t *) g_malloc0(sizeof(entityGeneral_t) + sizeof(gpointer));
    return entityGeneral;
}

static entityGeneral_t *
assign_entityGeneral(GSList *vbl)
{
    GSList *elem;
    entityGeneral_t *entityGeneral;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 47, 1, 4};

    entityGeneral = entity_mib_new_entityGeneral();
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
            if (vb->type == G_SNMP_TIMETICKS) {
                entityGeneral->entLastChangeTime = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for entLastChangeTime");
            }
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


