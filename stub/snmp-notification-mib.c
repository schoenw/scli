/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.0 for the scli package.
 *
 * Derived from SNMP-NOTIFICATION-MIB:
 *   This MIB module defines MIB objects which provide
 *   mechanisms to remotely configure the parameters
 *   used by an SNMP entity for the generation of
 *   notifications.
 *
 * Revision 1998-08-04 00:00:
 *   Clarifications, published as
 *   RFC2573
 *
 * Revision 1997-07-14 00:00:
 *   The initial revision, published as RFC2273.
 *
 * $Id$
 */

#include "snmp-notification-mib.h"

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyType[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYTYPE_TRAP,	"trap" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYTYPE_INFORM,	"inform" },
    { 0, NULL }
};

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyStorageType[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYSTORAGETYPE_OTHER,	"other" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYSTORAGETYPE_VOLATILE,	"volatile" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYSTORAGETYPE_NONVOLATILE,	"nonVolatile" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYSTORAGETYPE_PERMANENT,	"permanent" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYSTORAGETYPE_READONLY,	"readOnly" },
    { 0, NULL }
};

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyRowStatus[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS_ACTIVE,	"active" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS_NOTINSERVICE,	"notInService" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS_NOTREADY,	"notReady" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS_CREATEANDGO,	"createAndGo" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS_CREATEANDWAIT,	"createAndWait" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyFilterProfileStorType[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILESTORTYPE_OTHER,	"other" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILESTORTYPE_VOLATILE,	"volatile" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILESTORTYPE_NONVOLATILE,	"nonVolatile" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILESTORTYPE_PERMANENT,	"permanent" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILESTORTYPE_READONLY,	"readOnly" },
    { 0, NULL }
};

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyFilterProfileRowStatus[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS_ACTIVE,	"active" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS_NOTINSERVICE,	"notInService" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS_NOTREADY,	"notReady" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS_CREATEANDGO,	"createAndGo" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS_CREATEANDWAIT,	"createAndWait" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyFilterType[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERTYPE_INCLUDED,	"included" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERTYPE_EXCLUDED,	"excluded" },
    { 0, NULL }
};

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyFilterStorageType[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSTORAGETYPE_OTHER,	"other" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSTORAGETYPE_VOLATILE,	"volatile" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSTORAGETYPE_NONVOLATILE,	"nonVolatile" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSTORAGETYPE_PERMANENT,	"permanent" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSTORAGETYPE_READONLY,	"readOnly" },
    { 0, NULL }
};

GSnmpEnum const snmp_notification_mib_enums_snmpNotifyFilterRowStatus[] = {
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS_ACTIVE,	"active" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS_NOTINSERVICE,	"notInService" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS_NOTREADY,	"notReady" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS_CREATEANDGO,	"createAndGo" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS_CREATEANDWAIT,	"createAndWait" },
    { SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS_DESTROY,	"destroy" },
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
		g_warning("type tag 0x%02x does not match 0x%02x (%s)",
			  vb->type, attributes[i].type, attributes[i].label);
		return -3;
	    }
	    *idx = attributes[i].subid;
	    return 0;
	}
    }
    
    return -4;
}

static guint32 const oid_snmpNotifyEntry[] = {1, 3, 6, 1, 6, 3, 13, 1, 1, 1};

static attribute_t attr_snmpNotifyEntry[] = {
    { 2, G_SNMP_OCTET_STRING, SNMP_NOTIFICATION_MIB_SNMPNOTIFYTAG, "snmpNotifyTag" },
    { 3, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYTYPE, "snmpNotifyType" },
    { 4, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYSTORAGETYPE, "snmpNotifyStorageType" },
    { 5, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYROWSTATUS, "snmpNotifyRowStatus" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_snmpNotifyFilterProfileEntry[] = {1, 3, 6, 1, 6, 3, 13, 1, 2, 1};

static attribute_t attr_snmpNotifyFilterProfileEntry[] = {
    { 1, G_SNMP_OCTET_STRING, SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILENAME, "snmpNotifyFilterProfileName" },
    { 2, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILESTORTYPE, "snmpNotifyFilterProfileStorType" },
    { 3, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERPROFILEROWSTATUS, "snmpNotifyFilterProfileRowStatus" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_snmpNotifyFilterEntry[] = {1, 3, 6, 1, 6, 3, 13, 1, 3, 1};

static attribute_t attr_snmpNotifyFilterEntry[] = {
    { 2, G_SNMP_OCTET_STRING, SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERMASK, "snmpNotifyFilterMask" },
    { 3, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERTYPE, "snmpNotifyFilterType" },
    { 4, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERSTORAGETYPE, "snmpNotifyFilterStorageType" },
    { 5, G_SNMP_INTEGER32, SNMP_NOTIFICATION_MIB_SNMPNOTIFYFILTERROWSTATUS, "snmpNotifyFilterRowStatus" },
    { 0, 0, 0, NULL }
};


snmp_notification_mib_snmpNotifyEntry_t *
snmp_notification_mib_new_snmpNotifyEntry()
{
    snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry;

    snmpNotifyEntry = (snmp_notification_mib_snmpNotifyEntry_t *) g_malloc0(sizeof(snmp_notification_mib_snmpNotifyEntry_t) + sizeof(gpointer));
    return snmpNotifyEntry;
}

static int
unpack_snmpNotifyEntry(GSnmpVarBind *vb, snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry)
{
    int idx = 11;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id_len - idx;
    if (len < 1 || len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        snmpNotifyEntry->snmpNotifyName[i] = vb->id[idx++];
    }
    snmpNotifyEntry->_snmpNotifyNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_snmpNotifyEntry(guint32 *base, guchar *snmpNotifyName, guint16 _snmpNotifyNameLength)
{
    int idx = 11;
    guint16 i, len;

    len = _snmpNotifyNameLength;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = snmpNotifyName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static snmp_notification_mib_snmpNotifyEntry_t *
assign_snmpNotifyEntry(GSList *vbl)
{
    GSList *elem;
    snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry;
    guint32 idx;
    char *p;

    snmpNotifyEntry = snmp_notification_mib_new_snmpNotifyEntry();
    if (! snmpNotifyEntry) {
        return NULL;
    }

    p = (char *) snmpNotifyEntry + sizeof(snmp_notification_mib_snmpNotifyEntry_t);
    * (GSList **) p = vbl;

    if (unpack_snmpNotifyEntry((GSnmpVarBind *) vbl->data, snmpNotifyEntry) < 0) {
        g_warning("illegal snmpNotifyEntry instance identifier");
        g_free(snmpNotifyEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_snmpNotifyEntry, sizeof(oid_snmpNotifyEntry)/sizeof(guint32),
                   attr_snmpNotifyEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            if (vb->syntax_len > 255) break;
            snmpNotifyEntry->_snmpNotifyTagLength = vb->syntax_len;
            snmpNotifyEntry->snmpNotifyTag = vb->syntax.uc;
            break;
        case 3:
            snmpNotifyEntry->snmpNotifyType = &(vb->syntax.i32[0]);
            break;
        case 4:
            snmpNotifyEntry->snmpNotifyStorageType = &(vb->syntax.i32[0]);
            break;
        case 5:
            snmpNotifyEntry->snmpNotifyRowStatus = &(vb->syntax.i32[0]);
            break;
        };
    }

    return snmpNotifyEntry;
}

void
snmp_notification_mib_get_snmpNotifyTable(GSnmpSession *s, snmp_notification_mib_snmpNotifyEntry_t ***snmpNotifyEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 13, 1, 1, 1, 0};

    *snmpNotifyEntry = NULL;

    add_attributes(s, &in, base, 11, 10, attr_snmpNotifyEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *snmpNotifyEntry = (snmp_notification_mib_snmpNotifyEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmp_notification_mib_snmpNotifyEntry_t *));
        if (! *snmpNotifyEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*snmpNotifyEntry)[i] = assign_snmpNotifyEntry(row->data);
        }
    }
}

void
snmp_notification_mib_get_snmpNotifyEntry(GSnmpSession *s, snmp_notification_mib_snmpNotifyEntry_t **snmpNotifyEntry, guchar *snmpNotifyName, guint16 _snmpNotifyNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_snmpNotifyEntry, sizeof(oid_snmpNotifyEntry));
    len = pack_snmpNotifyEntry(base, snmpNotifyName, _snmpNotifyNameLength);
    if (len < 0) {
        g_warning("illegal snmpNotifyEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *snmpNotifyEntry = NULL;

    add_attributes(s, &in, base, len, 10, attr_snmpNotifyEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *snmpNotifyEntry = assign_snmpNotifyEntry(out);
    }
}

void
snmp_notification_mib_set_snmpNotifyEntry(GSnmpSession *s, snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_snmpNotifyEntry, sizeof(oid_snmpNotifyEntry));
    len = pack_snmpNotifyEntry(base, snmpNotifyEntry->snmpNotifyName, snmpNotifyEntry->_snmpNotifyNameLength);
    if (len < 0) {
        g_warning("illegal snmpNotifyEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    if (snmpNotifyEntry->snmpNotifyTag) {
        base[10] = 2;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       snmpNotifyEntry->snmpNotifyTag,
                       snmpNotifyEntry->_snmpNotifyTagLength);
    }
    if (snmpNotifyEntry->snmpNotifyType) {
        base[10] = 3;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyEntry->snmpNotifyType,
                       0);
    }
    if (snmpNotifyEntry->snmpNotifyStorageType) {
        base[10] = 4;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyEntry->snmpNotifyStorageType,
                       0);
    }
    if (snmpNotifyEntry->snmpNotifyRowStatus) {
        base[10] = 5;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyEntry->snmpNotifyRowStatus,
                       0);
    }

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_notification_mib_free_snmpNotifyEntry(snmp_notification_mib_snmpNotifyEntry_t *snmpNotifyEntry)
{
    GSList *vbl;
    char *p;

    if (snmpNotifyEntry) {
        p = (char *) snmpNotifyEntry + sizeof(snmp_notification_mib_snmpNotifyEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpNotifyEntry);
    }
}

void
snmp_notification_mib_free_snmpNotifyTable(snmp_notification_mib_snmpNotifyEntry_t **snmpNotifyEntry)
{
    int i;

    if (snmpNotifyEntry) {
        for (i = 0; snmpNotifyEntry[i]; i++) {
            snmp_notification_mib_free_snmpNotifyEntry(snmpNotifyEntry[i]);
        }
        g_free(snmpNotifyEntry);
    }
}

snmp_notification_mib_snmpNotifyFilterProfileEntry_t *
snmp_notification_mib_new_snmpNotifyFilterProfileEntry()
{
    snmp_notification_mib_snmpNotifyFilterProfileEntry_t *snmpNotifyFilterProfileEntry;

    snmpNotifyFilterProfileEntry = (snmp_notification_mib_snmpNotifyFilterProfileEntry_t *) g_malloc0(sizeof(snmp_notification_mib_snmpNotifyFilterProfileEntry_t) + sizeof(gpointer));
    return snmpNotifyFilterProfileEntry;
}

static int
unpack_snmpNotifyFilterProfileEntry(GSnmpVarBind *vb, snmp_notification_mib_snmpNotifyFilterProfileEntry_t *snmpNotifyFilterProfileEntry)
{
    int idx = 11;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id_len - idx;
    if (len < 1 || len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        snmpNotifyFilterProfileEntry->snmpTargetParamsName[i] = vb->id[idx++];
    }
    snmpNotifyFilterProfileEntry->_snmpTargetParamsNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_snmpNotifyFilterProfileEntry(guint32 *base, guchar *snmpTargetParamsName, guint16 _snmpTargetParamsNameLength)
{
    int idx = 11;
    guint16 i, len;

    len = _snmpTargetParamsNameLength;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = snmpTargetParamsName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static snmp_notification_mib_snmpNotifyFilterProfileEntry_t *
assign_snmpNotifyFilterProfileEntry(GSList *vbl)
{
    GSList *elem;
    snmp_notification_mib_snmpNotifyFilterProfileEntry_t *snmpNotifyFilterProfileEntry;
    guint32 idx;
    char *p;

    snmpNotifyFilterProfileEntry = snmp_notification_mib_new_snmpNotifyFilterProfileEntry();
    if (! snmpNotifyFilterProfileEntry) {
        return NULL;
    }

    p = (char *) snmpNotifyFilterProfileEntry + sizeof(snmp_notification_mib_snmpNotifyFilterProfileEntry_t);
    * (GSList **) p = vbl;

    if (unpack_snmpNotifyFilterProfileEntry((GSnmpVarBind *) vbl->data, snmpNotifyFilterProfileEntry) < 0) {
        g_warning("illegal snmpNotifyFilterProfileEntry instance identifier");
        g_free(snmpNotifyFilterProfileEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_snmpNotifyFilterProfileEntry, sizeof(oid_snmpNotifyFilterProfileEntry)/sizeof(guint32),
                   attr_snmpNotifyFilterProfileEntry, &idx) < 0) continue;

        switch (idx) {
        case 1:
            if (vb->syntax_len < 1 || vb->syntax_len > 32) break;
            snmpNotifyFilterProfileEntry->_snmpNotifyFilterProfileNameLength = vb->syntax_len;
            snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileName = vb->syntax.uc;
            break;
        case 2:
            snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileStorType = &(vb->syntax.i32[0]);
            break;
        case 3:
            snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileRowStatus = &(vb->syntax.i32[0]);
            break;
        };
    }

    return snmpNotifyFilterProfileEntry;
}

void
snmp_notification_mib_get_snmpNotifyFilterProfileTable(GSnmpSession *s, snmp_notification_mib_snmpNotifyFilterProfileEntry_t ***snmpNotifyFilterProfileEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 13, 1, 2, 1, 0};

    *snmpNotifyFilterProfileEntry = NULL;

    add_attributes(s, &in, base, 11, 10, attr_snmpNotifyFilterProfileEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *snmpNotifyFilterProfileEntry = (snmp_notification_mib_snmpNotifyFilterProfileEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmp_notification_mib_snmpNotifyFilterProfileEntry_t *));
        if (! *snmpNotifyFilterProfileEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*snmpNotifyFilterProfileEntry)[i] = assign_snmpNotifyFilterProfileEntry(row->data);
        }
    }
}

void
snmp_notification_mib_get_snmpNotifyFilterProfileEntry(GSnmpSession *s, snmp_notification_mib_snmpNotifyFilterProfileEntry_t **snmpNotifyFilterProfileEntry, guchar *snmpTargetParamsName, guint16 _snmpTargetParamsNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_snmpNotifyFilterProfileEntry, sizeof(oid_snmpNotifyFilterProfileEntry));
    len = pack_snmpNotifyFilterProfileEntry(base, snmpTargetParamsName, _snmpTargetParamsNameLength);
    if (len < 0) {
        g_warning("illegal snmpNotifyFilterProfileEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *snmpNotifyFilterProfileEntry = NULL;

    add_attributes(s, &in, base, len, 10, attr_snmpNotifyFilterProfileEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *snmpNotifyFilterProfileEntry = assign_snmpNotifyFilterProfileEntry(out);
    }
}

void
snmp_notification_mib_set_snmpNotifyFilterProfileEntry(GSnmpSession *s, snmp_notification_mib_snmpNotifyFilterProfileEntry_t *snmpNotifyFilterProfileEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_snmpNotifyFilterProfileEntry, sizeof(oid_snmpNotifyFilterProfileEntry));
    len = pack_snmpNotifyFilterProfileEntry(base, snmpNotifyFilterProfileEntry->snmpTargetParamsName, snmpNotifyFilterProfileEntry->_snmpTargetParamsNameLength);
    if (len < 0) {
        g_warning("illegal snmpNotifyFilterProfileEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    if (snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileName) {
        base[10] = 1;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileName,
                       snmpNotifyFilterProfileEntry->_snmpNotifyFilterProfileNameLength);
    }
    if (snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileStorType) {
        base[10] = 2;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileStorType,
                       0);
    }
    if (snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileRowStatus) {
        base[10] = 3;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyFilterProfileEntry->snmpNotifyFilterProfileRowStatus,
                       0);
    }

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_notification_mib_free_snmpNotifyFilterProfileEntry(snmp_notification_mib_snmpNotifyFilterProfileEntry_t *snmpNotifyFilterProfileEntry)
{
    GSList *vbl;
    char *p;

    if (snmpNotifyFilterProfileEntry) {
        p = (char *) snmpNotifyFilterProfileEntry + sizeof(snmp_notification_mib_snmpNotifyFilterProfileEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpNotifyFilterProfileEntry);
    }
}

void
snmp_notification_mib_free_snmpNotifyFilterProfileTable(snmp_notification_mib_snmpNotifyFilterProfileEntry_t **snmpNotifyFilterProfileEntry)
{
    int i;

    if (snmpNotifyFilterProfileEntry) {
        for (i = 0; snmpNotifyFilterProfileEntry[i]; i++) {
            snmp_notification_mib_free_snmpNotifyFilterProfileEntry(snmpNotifyFilterProfileEntry[i]);
        }
        g_free(snmpNotifyFilterProfileEntry);
    }
}

snmp_notification_mib_snmpNotifyFilterEntry_t *
snmp_notification_mib_new_snmpNotifyFilterEntry()
{
    snmp_notification_mib_snmpNotifyFilterEntry_t *snmpNotifyFilterEntry;

    snmpNotifyFilterEntry = (snmp_notification_mib_snmpNotifyFilterEntry_t *) g_malloc0(sizeof(snmp_notification_mib_snmpNotifyFilterEntry_t) + sizeof(gpointer));
    return snmpNotifyFilterEntry;
}

static int
unpack_snmpNotifyFilterEntry(GSnmpVarBind *vb, snmp_notification_mib_snmpNotifyFilterEntry_t *snmpNotifyFilterEntry)
{
    int idx = 11;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (len < 1 || len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        snmpNotifyFilterEntry->snmpNotifyFilterProfileName[i] = vb->id[idx++];
    }
    snmpNotifyFilterEntry->_snmpNotifyFilterProfileNameLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id_len - idx;
    if (len > 117) return -1;
    for (i = 0; i < len; i++) {
        snmpNotifyFilterEntry->snmpNotifyFilterSubtree[i] = vb->id[idx++];
    }
    snmpNotifyFilterEntry->_snmpNotifyFilterSubtreeLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_snmpNotifyFilterEntry(guint32 *base, guchar *snmpNotifyFilterProfileName, guint16 _snmpNotifyFilterProfileNameLength, guint32 *snmpNotifyFilterSubtree, guint16 _snmpNotifyFilterSubtreeLength)
{
    int idx = 11;
    guint16 i, len;

    len = _snmpNotifyFilterProfileNameLength;
    base[idx++] = len;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = snmpNotifyFilterProfileName[i];
        if (idx >= 128) return -1;
    }
    len = _snmpNotifyFilterSubtreeLength;
    if (len > 117) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = snmpNotifyFilterSubtree[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static snmp_notification_mib_snmpNotifyFilterEntry_t *
assign_snmpNotifyFilterEntry(GSList *vbl)
{
    GSList *elem;
    snmp_notification_mib_snmpNotifyFilterEntry_t *snmpNotifyFilterEntry;
    guint32 idx;
    char *p;

    snmpNotifyFilterEntry = snmp_notification_mib_new_snmpNotifyFilterEntry();
    if (! snmpNotifyFilterEntry) {
        return NULL;
    }

    p = (char *) snmpNotifyFilterEntry + sizeof(snmp_notification_mib_snmpNotifyFilterEntry_t);
    * (GSList **) p = vbl;

    if (unpack_snmpNotifyFilterEntry((GSnmpVarBind *) vbl->data, snmpNotifyFilterEntry) < 0) {
        g_warning("illegal snmpNotifyFilterEntry instance identifier");
        g_free(snmpNotifyFilterEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_snmpNotifyFilterEntry, sizeof(oid_snmpNotifyFilterEntry)/sizeof(guint32),
                   attr_snmpNotifyFilterEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            if (vb->syntax_len > 16) break;
            snmpNotifyFilterEntry->_snmpNotifyFilterMaskLength = vb->syntax_len;
            snmpNotifyFilterEntry->snmpNotifyFilterMask = vb->syntax.uc;
            break;
        case 3:
            snmpNotifyFilterEntry->snmpNotifyFilterType = &(vb->syntax.i32[0]);
            break;
        case 4:
            snmpNotifyFilterEntry->snmpNotifyFilterStorageType = &(vb->syntax.i32[0]);
            break;
        case 5:
            snmpNotifyFilterEntry->snmpNotifyFilterRowStatus = &(vb->syntax.i32[0]);
            break;
        };
    }

    return snmpNotifyFilterEntry;
}

void
snmp_notification_mib_get_snmpNotifyFilterTable(GSnmpSession *s, snmp_notification_mib_snmpNotifyFilterEntry_t ***snmpNotifyFilterEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 13, 1, 3, 1, 0};

    *snmpNotifyFilterEntry = NULL;

    add_attributes(s, &in, base, 11, 10, attr_snmpNotifyFilterEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *snmpNotifyFilterEntry = (snmp_notification_mib_snmpNotifyFilterEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmp_notification_mib_snmpNotifyFilterEntry_t *));
        if (! *snmpNotifyFilterEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*snmpNotifyFilterEntry)[i] = assign_snmpNotifyFilterEntry(row->data);
        }
    }
}

void
snmp_notification_mib_get_snmpNotifyFilterEntry(GSnmpSession *s, snmp_notification_mib_snmpNotifyFilterEntry_t **snmpNotifyFilterEntry, guchar *snmpNotifyFilterProfileName, guint16 _snmpNotifyFilterProfileNameLength, guint32 *snmpNotifyFilterSubtree, guint16 _snmpNotifyFilterSubtreeLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_snmpNotifyFilterEntry, sizeof(oid_snmpNotifyFilterEntry));
    len = pack_snmpNotifyFilterEntry(base, snmpNotifyFilterProfileName, _snmpNotifyFilterProfileNameLength, snmpNotifyFilterSubtree, _snmpNotifyFilterSubtreeLength);
    if (len < 0) {
        g_warning("illegal snmpNotifyFilterEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *snmpNotifyFilterEntry = NULL;

    add_attributes(s, &in, base, len, 10, attr_snmpNotifyFilterEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *snmpNotifyFilterEntry = assign_snmpNotifyFilterEntry(out);
    }
}

void
snmp_notification_mib_set_snmpNotifyFilterEntry(GSnmpSession *s, snmp_notification_mib_snmpNotifyFilterEntry_t *snmpNotifyFilterEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_snmpNotifyFilterEntry, sizeof(oid_snmpNotifyFilterEntry));
    len = pack_snmpNotifyFilterEntry(base, snmpNotifyFilterEntry->snmpNotifyFilterProfileName, snmpNotifyFilterEntry->_snmpNotifyFilterProfileNameLength, snmpNotifyFilterEntry->snmpNotifyFilterSubtree, snmpNotifyFilterEntry->_snmpNotifyFilterSubtreeLength);
    if (len < 0) {
        g_warning("illegal snmpNotifyFilterEntry index values");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    if (snmpNotifyFilterEntry->snmpNotifyFilterMask) {
        base[10] = 2;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       snmpNotifyFilterEntry->snmpNotifyFilterMask,
                       snmpNotifyFilterEntry->_snmpNotifyFilterMaskLength);
    }
    if (snmpNotifyFilterEntry->snmpNotifyFilterType) {
        base[10] = 3;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyFilterEntry->snmpNotifyFilterType,
                       0);
    }
    if (snmpNotifyFilterEntry->snmpNotifyFilterStorageType) {
        base[10] = 4;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyFilterEntry->snmpNotifyFilterStorageType,
                       0);
    }
    if (snmpNotifyFilterEntry->snmpNotifyFilterRowStatus) {
        base[10] = 5;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       snmpNotifyFilterEntry->snmpNotifyFilterRowStatus,
                       0);
    }

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_notification_mib_free_snmpNotifyFilterEntry(snmp_notification_mib_snmpNotifyFilterEntry_t *snmpNotifyFilterEntry)
{
    GSList *vbl;
    char *p;

    if (snmpNotifyFilterEntry) {
        p = (char *) snmpNotifyFilterEntry + sizeof(snmp_notification_mib_snmpNotifyFilterEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpNotifyFilterEntry);
    }
}

void
snmp_notification_mib_free_snmpNotifyFilterTable(snmp_notification_mib_snmpNotifyFilterEntry_t **snmpNotifyFilterEntry)
{
    int i;

    if (snmpNotifyFilterEntry) {
        for (i = 0; snmpNotifyFilterEntry[i]; i++) {
            snmp_notification_mib_free_snmpNotifyFilterEntry(snmpNotifyFilterEntry[i]);
        }
        g_free(snmpNotifyFilterEntry);
    }
}


