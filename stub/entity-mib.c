/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.0 for the scli package.
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

GSnmpEnum const entity_mib_enums_entPhysicalClass[] = {
    { ENTITY_MIB_ENTPHYSICALCLASS_OTHER,	"other" },
    { ENTITY_MIB_ENTPHYSICALCLASS_UNKNOWN,	"unknown" },
    { ENTITY_MIB_ENTPHYSICALCLASS_CHASSIS,	"chassis" },
    { ENTITY_MIB_ENTPHYSICALCLASS_BACKPLANE,	"backplane" },
    { ENTITY_MIB_ENTPHYSICALCLASS_CONTAINER,	"container" },
    { ENTITY_MIB_ENTPHYSICALCLASS_POWERSUPPLY,	"powerSupply" },
    { ENTITY_MIB_ENTPHYSICALCLASS_FAN,	"fan" },
    { ENTITY_MIB_ENTPHYSICALCLASS_SENSOR,	"sensor" },
    { ENTITY_MIB_ENTPHYSICALCLASS_MODULE,	"module" },
    { ENTITY_MIB_ENTPHYSICALCLASS_PORT,	"port" },
    { ENTITY_MIB_ENTPHYSICALCLASS_STACK,	"stack" },
    { 0, NULL }
};

GSnmpEnum const entity_mib_enums_entPhysicalIsFRU[] = {
    { ENTITY_MIB_ENTPHYSICALISFRU_TRUE,	"true" },
    { ENTITY_MIB_ENTPHYSICALISFRU_FALSE,	"false" },
    { 0, NULL }
};


typedef struct {
    guint32 const     subid;
    GSnmpVarBindType  type;
    gint              tag;
    gchar            *label;
} attribute_t;

static void
add_attributes(GSnmpSession *s, GSList **vbl, guint32 *base, guint8 len,
                guint idx, attribute_t *attributes, gint mask)
{
    int i;

    for (i = 0; attributes[i].label; i++) {
        if (! mask || (mask & attributes[i].tag)) {
            if (attributes[i].type != G_SNMP_COUNTER64
                || s->version > G_SNMP_V1) {
                base[idx] = attributes[i].subid;
                g_snmp_vbl_add_null(vbl, base, len);
            }
        }
    }
}

static int
lookup(GSnmpVarBind *vb, guint32 const *base, guint16 const base_len,
	    attribute_t *attributes, guint32 *idx)
{
    int i;

    if (vb->type == G_SNMP_ENDOFMIBVIEW
        || (vb->type == G_SNMP_NOSUCHOBJECT)
        || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
        return -1;
    }
    
    if (memcmp(vb->id, base, base_len * sizeof(guint32)) != 0) {
	return -2;
    }

    for (i = 0; attributes[i].label; i++) {
	if (vb->id_len > base_len && vb->id[base_len] == attributes[i].subid) {
	    if (vb->type != attributes[i].type) {
		const char *a = gsnmp_enum_get_label(gsnmp_enum_type_table, vb->type);
		const char *b = gsnmp_enum_get_label(gsnmp_enum_type_table, attributes[i].type);
		g_warning("%s: type mismatch: %s%s%s", attributes[i].label,
		          (a) ? a : "", (a || b) ? " != " : "", (b) ? b : "");
		return -3;
	    }
	    *idx = attributes[i].subid;
	    return 0;
	}
    }
    
    return -4;
}

static guint32 const oid_entPhysicalEntry[] = {1, 3, 6, 1, 2, 1, 47, 1, 1, 1, 1};

static attribute_t attr_entPhysicalEntry[] = {
    { 2, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALDESCR, "entPhysicalDescr" },
    { 3, G_SNMP_OBJECTID, ENTITY_MIB_ENTPHYSICALVENDORTYPE, "entPhysicalVendorType" },
    { 4, G_SNMP_INTEGER32, ENTITY_MIB_ENTPHYSICALCONTAINEDIN, "entPhysicalContainedIn" },
    { 5, G_SNMP_INTEGER32, ENTITY_MIB_ENTPHYSICALCLASS, "entPhysicalClass" },
    { 6, G_SNMP_INTEGER32, ENTITY_MIB_ENTPHYSICALPARENTRELPOS, "entPhysicalParentRelPos" },
    { 7, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALNAME, "entPhysicalName" },
    { 8, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALHARDWAREREV, "entPhysicalHardwareRev" },
    { 9, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALFIRMWAREREV, "entPhysicalFirmwareRev" },
    { 10, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALSOFTWAREREV, "entPhysicalSoftwareRev" },
    { 11, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALSERIALNUM, "entPhysicalSerialNum" },
    { 12, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALMFGNAME, "entPhysicalMfgName" },
    { 13, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALMODELNAME, "entPhysicalModelName" },
    { 14, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALALIAS, "entPhysicalAlias" },
    { 15, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTPHYSICALASSETID, "entPhysicalAssetID" },
    { 16, G_SNMP_INTEGER32, ENTITY_MIB_ENTPHYSICALISFRU, "entPhysicalIsFRU" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_entLogicalEntry[] = {1, 3, 6, 1, 2, 1, 47, 1, 2, 1, 1};

static attribute_t attr_entLogicalEntry[] = {
    { 2, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTLOGICALDESCR, "entLogicalDescr" },
    { 3, G_SNMP_OBJECTID, ENTITY_MIB_ENTLOGICALTYPE, "entLogicalType" },
    { 4, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTLOGICALCOMMUNITY, "entLogicalCommunity" },
    { 5, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTLOGICALTADDRESS, "entLogicalTAddress" },
    { 6, G_SNMP_OBJECTID, ENTITY_MIB_ENTLOGICALTDOMAIN, "entLogicalTDomain" },
    { 7, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTLOGICALCONTEXTENGINEID, "entLogicalContextEngineID" },
    { 8, G_SNMP_OCTETSTRING, ENTITY_MIB_ENTLOGICALCONTEXTNAME, "entLogicalContextName" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_entLPMappingEntry[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 1, 1};

static attribute_t attr_entLPMappingEntry[] = {
    { 1, G_SNMP_INTEGER32, ENTITY_MIB_ENTLPPHYSICALINDEX, "entLPPhysicalIndex" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_entAliasMappingEntry[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 2, 1};

static attribute_t attr_entAliasMappingEntry[] = {
    { 2, G_SNMP_OBJECTID, ENTITY_MIB_ENTALIASMAPPINGIDENTIFIER, "entAliasMappingIdentifier" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_entPhysicalContainsEntry[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 3, 1};

static attribute_t attr_entPhysicalContainsEntry[] = {
    { 1, G_SNMP_INTEGER32, ENTITY_MIB_ENTPHYSICALCHILDINDEX, "entPhysicalChildIndex" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_entityGeneral[] = {1, 3, 6, 1, 2, 1, 47, 1, 4};

static attribute_t attr_entityGeneral[] = {
    { 1, G_SNMP_TIMETICKS, ENTITY_MIB_ENTLASTCHANGETIME, "entLastChangeTime" },
    { 0, 0, 0, NULL }
};


entity_mib_entPhysicalEntry_t *
entity_mib_new_entPhysicalEntry()
{
    entity_mib_entPhysicalEntry_t *entPhysicalEntry;

    entPhysicalEntry = (entity_mib_entPhysicalEntry_t *) g_malloc0(sizeof(entity_mib_entPhysicalEntry_t) + sizeof(gpointer));
    return entPhysicalEntry;
}

static int
unpack_entPhysicalEntry(GSnmpVarBind *vb, entity_mib_entPhysicalEntry_t *entPhysicalEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entPhysicalEntry->entPhysicalIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_entPhysicalEntry(guint32 *base, gint32 entPhysicalIndex)
{
    int idx = 12;

    base[idx++] = entPhysicalIndex;
    return idx;
}

static entity_mib_entPhysicalEntry_t *
assign_entPhysicalEntry(GSList *vbl)
{
    GSList *elem;
    entity_mib_entPhysicalEntry_t *entPhysicalEntry;
    guint32 idx;
    char *p;

    entPhysicalEntry = entity_mib_new_entPhysicalEntry();
    if (! entPhysicalEntry) {
        return NULL;
    }

    p = (char *) entPhysicalEntry + sizeof(entity_mib_entPhysicalEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entPhysicalEntry((GSnmpVarBind *) vbl->data, entPhysicalEntry) < 0) {
        g_warning("illegal entPhysicalEntry instance identifier");
        g_free(entPhysicalEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_entPhysicalEntry, sizeof(oid_entPhysicalEntry)/sizeof(guint32),
                   attr_entPhysicalEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            if (vb->syntax_len > 255) break;
            entPhysicalEntry->_entPhysicalDescrLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalDescr = vb->syntax.uc;
            break;
        case 3:
            if (vb->syntax_len > 128) break;
            entPhysicalEntry->_entPhysicalVendorTypeLength = vb->syntax_len / sizeof(guint32);
            entPhysicalEntry->entPhysicalVendorType = vb->syntax.ui32;
            break;
        case 4:
            entPhysicalEntry->entPhysicalContainedIn = &(vb->syntax.i32[0]);
            break;
        case 5:
            entPhysicalEntry->entPhysicalClass = &(vb->syntax.i32[0]);
            break;
        case 6:
            entPhysicalEntry->entPhysicalParentRelPos = &(vb->syntax.i32[0]);
            break;
        case 7:
            if (vb->syntax_len > 255) break;
            entPhysicalEntry->_entPhysicalNameLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalName = vb->syntax.uc;
            break;
        case 8:
            if (vb->syntax_len > 255) break;
            entPhysicalEntry->_entPhysicalHardwareRevLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalHardwareRev = vb->syntax.uc;
            break;
        case 9:
            if (vb->syntax_len > 255) break;
            entPhysicalEntry->_entPhysicalFirmwareRevLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalFirmwareRev = vb->syntax.uc;
            break;
        case 10:
            if (vb->syntax_len > 255) break;
            entPhysicalEntry->_entPhysicalSoftwareRevLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalSoftwareRev = vb->syntax.uc;
            break;
        case 11:
            if (vb->syntax_len > 32) break;
            entPhysicalEntry->_entPhysicalSerialNumLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalSerialNum = vb->syntax.uc;
            break;
        case 12:
            if (vb->syntax_len > 255) break;
            entPhysicalEntry->_entPhysicalMfgNameLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalMfgName = vb->syntax.uc;
            break;
        case 13:
            if (vb->syntax_len > 255) break;
            entPhysicalEntry->_entPhysicalModelNameLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalModelName = vb->syntax.uc;
            break;
        case 14:
            if (vb->syntax_len > 32) break;
            entPhysicalEntry->_entPhysicalAliasLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalAlias = vb->syntax.uc;
            break;
        case 15:
            if (vb->syntax_len > 32) break;
            entPhysicalEntry->_entPhysicalAssetIDLength = vb->syntax_len;
            entPhysicalEntry->entPhysicalAssetID = vb->syntax.uc;
            break;
        case 16:
            entPhysicalEntry->entPhysicalIsFRU = &(vb->syntax.i32[0]);
            break;
        };
    }

    return entPhysicalEntry;
}

void
entity_mib_get_entPhysicalTable(GSnmpSession *s, entity_mib_entPhysicalEntry_t ***entPhysicalEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 1, 1, 1, 0};

    *entPhysicalEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_entPhysicalEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *entPhysicalEntry = (entity_mib_entPhysicalEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entity_mib_entPhysicalEntry_t *));
        if (! *entPhysicalEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*entPhysicalEntry)[i] = assign_entPhysicalEntry(row->data);
        }
    }
}

void
entity_mib_get_entPhysicalEntry(GSnmpSession *s, entity_mib_entPhysicalEntry_t **entPhysicalEntry, gint32 entPhysicalIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_entPhysicalEntry, sizeof(oid_entPhysicalEntry));
    len = pack_entPhysicalEntry(base, entPhysicalIndex);
    if (len < 0) {
        g_warning("illegal entPhysicalEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *entPhysicalEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_entPhysicalEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *entPhysicalEntry = assign_entPhysicalEntry(out);
    }
}

void
entity_mib_set_entPhysicalEntry(GSnmpSession *s, entity_mib_entPhysicalEntry_t *entPhysicalEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_entPhysicalEntry, sizeof(oid_entPhysicalEntry));
    len = pack_entPhysicalEntry(base, entPhysicalEntry->entPhysicalIndex);
    if (len < 0) {
        g_warning("illegal entPhysicalEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    if (entPhysicalEntry->entPhysicalSerialNum) {
        base[11] = 11;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTETSTRING,
                       entPhysicalEntry->entPhysicalSerialNum,
                       entPhysicalEntry->_entPhysicalSerialNumLength);
    }
    if (entPhysicalEntry->entPhysicalAlias) {
        base[11] = 14;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTETSTRING,
                       entPhysicalEntry->entPhysicalAlias,
                       entPhysicalEntry->_entPhysicalAliasLength);
    }
    if (entPhysicalEntry->entPhysicalAssetID) {
        base[11] = 15;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTETSTRING,
                       entPhysicalEntry->entPhysicalAssetID,
                       entPhysicalEntry->_entPhysicalAssetIDLength);
    }

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
entity_mib_free_entPhysicalEntry(entity_mib_entPhysicalEntry_t *entPhysicalEntry)
{
    GSList *vbl;
    char *p;

    if (entPhysicalEntry) {
        p = (char *) entPhysicalEntry + sizeof(entity_mib_entPhysicalEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(entPhysicalEntry);
    }
}

void
entity_mib_free_entPhysicalTable(entity_mib_entPhysicalEntry_t **entPhysicalEntry)
{
    int i;

    if (entPhysicalEntry) {
        for (i = 0; entPhysicalEntry[i]; i++) {
            entity_mib_free_entPhysicalEntry(entPhysicalEntry[i]);
        }
        g_free(entPhysicalEntry);
    }
}

entity_mib_entLogicalEntry_t *
entity_mib_new_entLogicalEntry()
{
    entity_mib_entLogicalEntry_t *entLogicalEntry;

    entLogicalEntry = (entity_mib_entLogicalEntry_t *) g_malloc0(sizeof(entity_mib_entLogicalEntry_t) + sizeof(gpointer));
    return entLogicalEntry;
}

static int
unpack_entLogicalEntry(GSnmpVarBind *vb, entity_mib_entLogicalEntry_t *entLogicalEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entLogicalEntry->entLogicalIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_entLogicalEntry(guint32 *base, gint32 entLogicalIndex)
{
    int idx = 12;

    base[idx++] = entLogicalIndex;
    return idx;
}

static entity_mib_entLogicalEntry_t *
assign_entLogicalEntry(GSList *vbl)
{
    GSList *elem;
    entity_mib_entLogicalEntry_t *entLogicalEntry;
    guint32 idx;
    char *p;

    entLogicalEntry = entity_mib_new_entLogicalEntry();
    if (! entLogicalEntry) {
        return NULL;
    }

    p = (char *) entLogicalEntry + sizeof(entity_mib_entLogicalEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entLogicalEntry((GSnmpVarBind *) vbl->data, entLogicalEntry) < 0) {
        g_warning("illegal entLogicalEntry instance identifier");
        g_free(entLogicalEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_entLogicalEntry, sizeof(oid_entLogicalEntry)/sizeof(guint32),
                   attr_entLogicalEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            if (vb->syntax_len > 255) break;
            entLogicalEntry->_entLogicalDescrLength = vb->syntax_len;
            entLogicalEntry->entLogicalDescr = vb->syntax.uc;
            break;
        case 3:
            if (vb->syntax_len > 128) break;
            entLogicalEntry->_entLogicalTypeLength = vb->syntax_len / sizeof(guint32);
            entLogicalEntry->entLogicalType = vb->syntax.ui32;
            break;
        case 4:
            if (vb->syntax_len > 255) break;
            entLogicalEntry->_entLogicalCommunityLength = vb->syntax_len;
            entLogicalEntry->entLogicalCommunity = vb->syntax.uc;
            break;
        case 5:
            if (vb->syntax_len < 1 || vb->syntax_len > 255) break;
            entLogicalEntry->_entLogicalTAddressLength = vb->syntax_len;
            entLogicalEntry->entLogicalTAddress = vb->syntax.uc;
            break;
        case 6:
            if (vb->syntax_len > 128) break;
            entLogicalEntry->_entLogicalTDomainLength = vb->syntax_len / sizeof(guint32);
            entLogicalEntry->entLogicalTDomain = vb->syntax.ui32;
            break;
        case 7:
            if (vb->syntax_len > 32) break;
            entLogicalEntry->_entLogicalContextEngineIDLength = vb->syntax_len;
            entLogicalEntry->entLogicalContextEngineID = vb->syntax.uc;
            break;
        case 8:
            if (vb->syntax_len > 255) break;
            entLogicalEntry->_entLogicalContextNameLength = vb->syntax_len;
            entLogicalEntry->entLogicalContextName = vb->syntax.uc;
            break;
        };
    }

    return entLogicalEntry;
}

void
entity_mib_get_entLogicalTable(GSnmpSession *s, entity_mib_entLogicalEntry_t ***entLogicalEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 2, 1, 1, 0};

    *entLogicalEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_entLogicalEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *entLogicalEntry = (entity_mib_entLogicalEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entity_mib_entLogicalEntry_t *));
        if (! *entLogicalEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*entLogicalEntry)[i] = assign_entLogicalEntry(row->data);
        }
    }
}

void
entity_mib_get_entLogicalEntry(GSnmpSession *s, entity_mib_entLogicalEntry_t **entLogicalEntry, gint32 entLogicalIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_entLogicalEntry, sizeof(oid_entLogicalEntry));
    len = pack_entLogicalEntry(base, entLogicalIndex);
    if (len < 0) {
        g_warning("illegal entLogicalEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *entLogicalEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_entLogicalEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *entLogicalEntry = assign_entLogicalEntry(out);
    }
}

void
entity_mib_free_entLogicalEntry(entity_mib_entLogicalEntry_t *entLogicalEntry)
{
    GSList *vbl;
    char *p;

    if (entLogicalEntry) {
        p = (char *) entLogicalEntry + sizeof(entity_mib_entLogicalEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(entLogicalEntry);
    }
}

void
entity_mib_free_entLogicalTable(entity_mib_entLogicalEntry_t **entLogicalEntry)
{
    int i;

    if (entLogicalEntry) {
        for (i = 0; entLogicalEntry[i]; i++) {
            entity_mib_free_entLogicalEntry(entLogicalEntry[i]);
        }
        g_free(entLogicalEntry);
    }
}

entity_mib_entLPMappingEntry_t *
entity_mib_new_entLPMappingEntry()
{
    entity_mib_entLPMappingEntry_t *entLPMappingEntry;

    entLPMappingEntry = (entity_mib_entLPMappingEntry_t *) g_malloc0(sizeof(entity_mib_entLPMappingEntry_t) + sizeof(gpointer));
    return entLPMappingEntry;
}

static int
unpack_entLPMappingEntry(GSnmpVarBind *vb, entity_mib_entLPMappingEntry_t *entLPMappingEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entLPMappingEntry->entLogicalIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    entLPMappingEntry->entLPPhysicalIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_entLPMappingEntry(guint32 *base, gint32 entLogicalIndex, gint32 entLPPhysicalIndex)
{
    int idx = 12;

    base[idx++] = entLogicalIndex;
    base[idx++] = entLPPhysicalIndex;
    return idx;
}

static entity_mib_entLPMappingEntry_t *
assign_entLPMappingEntry(GSList *vbl)
{
    GSList *elem;
    entity_mib_entLPMappingEntry_t *entLPMappingEntry;
    guint32 idx;
    char *p;

    entLPMappingEntry = entity_mib_new_entLPMappingEntry();
    if (! entLPMappingEntry) {
        return NULL;
    }

    p = (char *) entLPMappingEntry + sizeof(entity_mib_entLPMappingEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entLPMappingEntry((GSnmpVarBind *) vbl->data, entLPMappingEntry) < 0) {
        g_warning("illegal entLPMappingEntry instance identifier");
        g_free(entLPMappingEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_entLPMappingEntry, sizeof(oid_entLPMappingEntry)/sizeof(guint32),
                   attr_entLPMappingEntry, &idx) < 0) continue;

        switch (idx) {
        };
    }

    return entLPMappingEntry;
}

void
entity_mib_get_entLPMappingTable(GSnmpSession *s, entity_mib_entLPMappingEntry_t ***entLPMappingEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 1, 1, 0};

    *entLPMappingEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_entLPMappingEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *entLPMappingEntry = (entity_mib_entLPMappingEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entity_mib_entLPMappingEntry_t *));
        if (! *entLPMappingEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*entLPMappingEntry)[i] = assign_entLPMappingEntry(row->data);
        }
    }
}

void
entity_mib_get_entLPMappingEntry(GSnmpSession *s, entity_mib_entLPMappingEntry_t **entLPMappingEntry, gint32 entLogicalIndex, gint32 entLPPhysicalIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_entLPMappingEntry, sizeof(oid_entLPMappingEntry));
    len = pack_entLPMappingEntry(base, entLogicalIndex, entLPPhysicalIndex);
    if (len < 0) {
        g_warning("illegal entLPMappingEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *entLPMappingEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_entLPMappingEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *entLPMappingEntry = assign_entLPMappingEntry(out);
    }
}

void
entity_mib_free_entLPMappingEntry(entity_mib_entLPMappingEntry_t *entLPMappingEntry)
{
    GSList *vbl;
    char *p;

    if (entLPMappingEntry) {
        p = (char *) entLPMappingEntry + sizeof(entity_mib_entLPMappingEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(entLPMappingEntry);
    }
}

void
entity_mib_free_entLPMappingTable(entity_mib_entLPMappingEntry_t **entLPMappingEntry)
{
    int i;

    if (entLPMappingEntry) {
        for (i = 0; entLPMappingEntry[i]; i++) {
            entity_mib_free_entLPMappingEntry(entLPMappingEntry[i]);
        }
        g_free(entLPMappingEntry);
    }
}

entity_mib_entAliasMappingEntry_t *
entity_mib_new_entAliasMappingEntry()
{
    entity_mib_entAliasMappingEntry_t *entAliasMappingEntry;

    entAliasMappingEntry = (entity_mib_entAliasMappingEntry_t *) g_malloc0(sizeof(entity_mib_entAliasMappingEntry_t) + sizeof(gpointer));
    return entAliasMappingEntry;
}

static int
unpack_entAliasMappingEntry(GSnmpVarBind *vb, entity_mib_entAliasMappingEntry_t *entAliasMappingEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entAliasMappingEntry->entPhysicalIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    entAliasMappingEntry->entAliasLogicalIndexOrZero = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_entAliasMappingEntry(guint32 *base, gint32 entPhysicalIndex, gint32 entAliasLogicalIndexOrZero)
{
    int idx = 12;

    base[idx++] = entPhysicalIndex;
    base[idx++] = entAliasLogicalIndexOrZero;
    return idx;
}

static entity_mib_entAliasMappingEntry_t *
assign_entAliasMappingEntry(GSList *vbl)
{
    GSList *elem;
    entity_mib_entAliasMappingEntry_t *entAliasMappingEntry;
    guint32 idx;
    char *p;

    entAliasMappingEntry = entity_mib_new_entAliasMappingEntry();
    if (! entAliasMappingEntry) {
        return NULL;
    }

    p = (char *) entAliasMappingEntry + sizeof(entity_mib_entAliasMappingEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entAliasMappingEntry((GSnmpVarBind *) vbl->data, entAliasMappingEntry) < 0) {
        g_warning("illegal entAliasMappingEntry instance identifier");
        g_free(entAliasMappingEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_entAliasMappingEntry, sizeof(oid_entAliasMappingEntry)/sizeof(guint32),
                   attr_entAliasMappingEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            if (vb->syntax_len > 128) break;
            entAliasMappingEntry->_entAliasMappingIdentifierLength = vb->syntax_len / sizeof(guint32);
            entAliasMappingEntry->entAliasMappingIdentifier = vb->syntax.ui32;
            break;
        };
    }

    return entAliasMappingEntry;
}

void
entity_mib_get_entAliasMappingTable(GSnmpSession *s, entity_mib_entAliasMappingEntry_t ***entAliasMappingEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 2, 1, 0};

    *entAliasMappingEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_entAliasMappingEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *entAliasMappingEntry = (entity_mib_entAliasMappingEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entity_mib_entAliasMappingEntry_t *));
        if (! *entAliasMappingEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*entAliasMappingEntry)[i] = assign_entAliasMappingEntry(row->data);
        }
    }
}

void
entity_mib_get_entAliasMappingEntry(GSnmpSession *s, entity_mib_entAliasMappingEntry_t **entAliasMappingEntry, gint32 entPhysicalIndex, gint32 entAliasLogicalIndexOrZero, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_entAliasMappingEntry, sizeof(oid_entAliasMappingEntry));
    len = pack_entAliasMappingEntry(base, entPhysicalIndex, entAliasLogicalIndexOrZero);
    if (len < 0) {
        g_warning("illegal entAliasMappingEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *entAliasMappingEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_entAliasMappingEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *entAliasMappingEntry = assign_entAliasMappingEntry(out);
    }
}

void
entity_mib_free_entAliasMappingEntry(entity_mib_entAliasMappingEntry_t *entAliasMappingEntry)
{
    GSList *vbl;
    char *p;

    if (entAliasMappingEntry) {
        p = (char *) entAliasMappingEntry + sizeof(entity_mib_entAliasMappingEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(entAliasMappingEntry);
    }
}

void
entity_mib_free_entAliasMappingTable(entity_mib_entAliasMappingEntry_t **entAliasMappingEntry)
{
    int i;

    if (entAliasMappingEntry) {
        for (i = 0; entAliasMappingEntry[i]; i++) {
            entity_mib_free_entAliasMappingEntry(entAliasMappingEntry[i]);
        }
        g_free(entAliasMappingEntry);
    }
}

entity_mib_entPhysicalContainsEntry_t *
entity_mib_new_entPhysicalContainsEntry()
{
    entity_mib_entPhysicalContainsEntry_t *entPhysicalContainsEntry;

    entPhysicalContainsEntry = (entity_mib_entPhysicalContainsEntry_t *) g_malloc0(sizeof(entity_mib_entPhysicalContainsEntry_t) + sizeof(gpointer));
    return entPhysicalContainsEntry;
}

static int
unpack_entPhysicalContainsEntry(GSnmpVarBind *vb, entity_mib_entPhysicalContainsEntry_t *entPhysicalContainsEntry)
{
    int idx = 12;

    if (vb->id_len < idx) return -1;
    entPhysicalContainsEntry->entPhysicalIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    entPhysicalContainsEntry->entPhysicalChildIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_entPhysicalContainsEntry(guint32 *base, gint32 entPhysicalIndex, gint32 entPhysicalChildIndex)
{
    int idx = 12;

    base[idx++] = entPhysicalIndex;
    base[idx++] = entPhysicalChildIndex;
    return idx;
}

static entity_mib_entPhysicalContainsEntry_t *
assign_entPhysicalContainsEntry(GSList *vbl)
{
    GSList *elem;
    entity_mib_entPhysicalContainsEntry_t *entPhysicalContainsEntry;
    guint32 idx;
    char *p;

    entPhysicalContainsEntry = entity_mib_new_entPhysicalContainsEntry();
    if (! entPhysicalContainsEntry) {
        return NULL;
    }

    p = (char *) entPhysicalContainsEntry + sizeof(entity_mib_entPhysicalContainsEntry_t);
    * (GSList **) p = vbl;

    if (unpack_entPhysicalContainsEntry((GSnmpVarBind *) vbl->data, entPhysicalContainsEntry) < 0) {
        g_warning("illegal entPhysicalContainsEntry instance identifier");
        g_free(entPhysicalContainsEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_entPhysicalContainsEntry, sizeof(oid_entPhysicalContainsEntry)/sizeof(guint32),
                   attr_entPhysicalContainsEntry, &idx) < 0) continue;

        switch (idx) {
        };
    }

    return entPhysicalContainsEntry;
}

void
entity_mib_get_entPhysicalContainsTable(GSnmpSession *s, entity_mib_entPhysicalContainsEntry_t ***entPhysicalContainsEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 3, 3, 1, 0};

    *entPhysicalContainsEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_entPhysicalContainsEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *entPhysicalContainsEntry = (entity_mib_entPhysicalContainsEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(entity_mib_entPhysicalContainsEntry_t *));
        if (! *entPhysicalContainsEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*entPhysicalContainsEntry)[i] = assign_entPhysicalContainsEntry(row->data);
        }
    }
}

void
entity_mib_get_entPhysicalContainsEntry(GSnmpSession *s, entity_mib_entPhysicalContainsEntry_t **entPhysicalContainsEntry, gint32 entPhysicalIndex, gint32 entPhysicalChildIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_entPhysicalContainsEntry, sizeof(oid_entPhysicalContainsEntry));
    len = pack_entPhysicalContainsEntry(base, entPhysicalIndex, entPhysicalChildIndex);
    if (len < 0) {
        g_warning("illegal entPhysicalContainsEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *entPhysicalContainsEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_entPhysicalContainsEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *entPhysicalContainsEntry = assign_entPhysicalContainsEntry(out);
    }
}

void
entity_mib_free_entPhysicalContainsEntry(entity_mib_entPhysicalContainsEntry_t *entPhysicalContainsEntry)
{
    GSList *vbl;
    char *p;

    if (entPhysicalContainsEntry) {
        p = (char *) entPhysicalContainsEntry + sizeof(entity_mib_entPhysicalContainsEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(entPhysicalContainsEntry);
    }
}

void
entity_mib_free_entPhysicalContainsTable(entity_mib_entPhysicalContainsEntry_t **entPhysicalContainsEntry)
{
    int i;

    if (entPhysicalContainsEntry) {
        for (i = 0; entPhysicalContainsEntry[i]; i++) {
            entity_mib_free_entPhysicalContainsEntry(entPhysicalContainsEntry[i]);
        }
        g_free(entPhysicalContainsEntry);
    }
}

entity_mib_entityGeneral_t *
entity_mib_new_entityGeneral()
{
    entity_mib_entityGeneral_t *entityGeneral;

    entityGeneral = (entity_mib_entityGeneral_t *) g_malloc0(sizeof(entity_mib_entityGeneral_t) + sizeof(gpointer));
    return entityGeneral;
}

static entity_mib_entityGeneral_t *
assign_entityGeneral(GSList *vbl)
{
    GSList *elem;
    entity_mib_entityGeneral_t *entityGeneral;
    guint32 idx;
    char *p;

    entityGeneral = entity_mib_new_entityGeneral();
    if (! entityGeneral) {
        return NULL;
    }

    p = (char *) entityGeneral + sizeof(entity_mib_entityGeneral_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_entityGeneral, sizeof(oid_entityGeneral)/sizeof(guint32),
                   attr_entityGeneral, &idx) < 0) continue;

        switch (idx) {
        case 1:
            entityGeneral->entLastChangeTime = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return entityGeneral;
}

void
entity_mib_get_entityGeneral(GSnmpSession *s, entity_mib_entityGeneral_t **entityGeneral, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 47, 1, 4, 0};

    *entityGeneral = NULL;

    add_attributes(s, &in, base, 10, 9, attr_entityGeneral, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *entityGeneral = assign_entityGeneral(out);
    }
}

void
entity_mib_free_entityGeneral(entity_mib_entityGeneral_t *entityGeneral)
{
    GSList *vbl;
    char *p;

    if (entityGeneral) {
        p = (char *) entityGeneral + sizeof(entity_mib_entityGeneral_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(entityGeneral);
    }
}


