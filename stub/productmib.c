/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from PRODUCTMIB:
 *
 * $Id$
 */

#include "productmib.h"

GSnmpEnum const productmib_enums_a3ComVlanIfType[] = {
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANLAYER2,            "vlanLayer2" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANDEFAULTPROTOCOLS,  "vlanDefaultProtocols" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANIPPROTOCOL,        "vlanIPProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANIPXPROTOCOL,       "vlanIPXProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANAPPLETALKPROTOCOL, "vlanAppleTalkProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANXNSPROTOCOL,       "vlanXNSProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANISOPROTOCOL,       "vlanISOProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANDECNETPROTOCOL,    "vlanDECNetProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANNETBIOSPROTOCOL,   "vlanNetBIOSProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANSNAPROTOCOL,       "vlanSNAProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANVINESPROTOCOL,     "vlanVINESProtocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANX25PROTOCOL,       "vlanX25Protocol" },
    { PRODUCTMIB_A3COMVLANIFTYPE_VLANIGMPPROTOCOL,      "vlanIGMPProtocol" },
    { 0, NULL }
};

GSnmpEnum const productmib_enums_a3ComVlanIfStatus[] = {
    { PRODUCTMIB_A3COMVLANIFSTATUS_ACTIVE,        "active" },
    { PRODUCTMIB_A3COMVLANIFSTATUS_NOTINSERVICE,  "notInService" },
    { PRODUCTMIB_A3COMVLANIFSTATUS_NOTREADY,      "notReady" },
    { PRODUCTMIB_A3COMVLANIFSTATUS_CREATEANDGO,   "createAndGo" },
    { PRODUCTMIB_A3COMVLANIFSTATUS_CREATEANDWAIT, "createAndWait" },
    { PRODUCTMIB_A3COMVLANIFSTATUS_DESTROY,       "destroy" },
    { 0, NULL }
};


static guint16 a3ComVlanIfDescr_constraints[] = {0, 80, 0, 0};
static guint32 a3ComVlanIfGlobalIdentifier_constraints[] = {0L, 65535L, 0, 0};


static guint32 const a3ComVlanIfEntry_oid[] = {1, 3, 6, 1, 4, 1, 43, 10, 1, 14, 1, 2, 1};

static GSnmpAttribute a3ComVlanIfEntry_attr[] = {
    { 2, G_SNMP_OCTETSTRING,
      PRODUCTMIB_A3COMVLANIFDESCR, "a3ComVlanIfDescr",
       a3ComVlanIfDescr_constraints,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfDescr),
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, _a3ComVlanIfDescrLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, G_SNMP_INTEGER32,
      PRODUCTMIB_A3COMVLANIFTYPE, "a3ComVlanIfType",
       NULL,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_INTEGER32,
      PRODUCTMIB_A3COMVLANIFGLOBALIDENTIFIER, "a3ComVlanIfGlobalIdentifier",
       a3ComVlanIfGlobalIdentifier_constraints,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfGlobalIdentifier),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, G_SNMP_OCTETSTRING,
      PRODUCTMIB_A3COMVLANIFINFO, "a3ComVlanIfInfo",
       NULL,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfInfo),
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, _a3ComVlanIfInfoLength),
      0 },
    { 6, G_SNMP_INTEGER32,
      PRODUCTMIB_A3COMVLANIFSTATUS, "a3ComVlanIfStatus",
       NULL,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


productmib_a3ComVlanIfEntry_t *
productmib_new_a3ComVlanIfEntry()
{
    productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry;

    a3ComVlanIfEntry = (productmib_a3ComVlanIfEntry_t *) g_malloc0(sizeof(productmib_a3ComVlanIfEntry_t) + sizeof(gpointer));
    return a3ComVlanIfEntry;
}

static int
unpack_a3ComVlanIfEntry(GSnmpVarBind *vb, productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry)
{
    guint8 idx = 14;

    if (vb->id_len < idx) return -1;
    a3ComVlanIfEntry->a3ComVlanIfIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_a3ComVlanIfEntry(guint32 *base, gint32 a3ComVlanIfIndex)
{
    guint8 idx = 14;

    base[idx++] = a3ComVlanIfIndex;
    return idx;
}

static productmib_a3ComVlanIfEntry_t *
assign_a3ComVlanIfEntry(GSList *vbl)
{
    productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry;
    char *p;

    a3ComVlanIfEntry = productmib_new_a3ComVlanIfEntry();
    if (! a3ComVlanIfEntry) {
        return NULL;
    }

    p = (char *) a3ComVlanIfEntry + sizeof(productmib_a3ComVlanIfEntry_t);
    * (GSList **) p = vbl;

    if (unpack_a3ComVlanIfEntry((GSnmpVarBind *) vbl->data, a3ComVlanIfEntry) < 0) {
        g_warning("%s: invalid instance identifier", "a3ComVlanIfEntry");
        g_free(a3ComVlanIfEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, a3ComVlanIfEntry_oid, sizeof(a3ComVlanIfEntry_oid)/sizeof(guint32),
                      a3ComVlanIfEntry_attr, a3ComVlanIfEntry);

    return a3ComVlanIfEntry;
}

void
productmib_get_a3ComVlanIfTable(GSnmpSession *s, productmib_a3ComVlanIfEntry_t ***a3ComVlanIfEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 43, 10, 1, 14, 1, 2, 1, 0};

    *a3ComVlanIfEntry = NULL;

    gsnmp_attr_get(s, &in, base, 14, 13, a3ComVlanIfEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *a3ComVlanIfEntry = (productmib_a3ComVlanIfEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(productmib_a3ComVlanIfEntry_t *));
        if (! *a3ComVlanIfEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*a3ComVlanIfEntry)[i] = assign_a3ComVlanIfEntry(row->data);
        }
    }
}

void
productmib_get_a3ComVlanIfEntry(GSnmpSession *s, productmib_a3ComVlanIfEntry_t **a3ComVlanIfEntry, gint32 a3ComVlanIfIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, a3ComVlanIfEntry_oid, sizeof(a3ComVlanIfEntry_oid));
    len = pack_a3ComVlanIfEntry(base, a3ComVlanIfIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "a3ComVlanIfEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *a3ComVlanIfEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 13, a3ComVlanIfEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *a3ComVlanIfEntry = assign_a3ComVlanIfEntry(out);
    }
}

void
productmib_set_a3ComVlanIfEntry(GSnmpSession *s, productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, a3ComVlanIfEntry_oid, sizeof(a3ComVlanIfEntry_oid));
    len = pack_a3ComVlanIfEntry(base, a3ComVlanIfEntry->a3ComVlanIfIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "a3ComVlanIfEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 13, a3ComVlanIfEntry_attr, mask, a3ComVlanIfEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
productmib_free_a3ComVlanIfEntry(productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry)
{
    GSList *vbl;
    char *p;

    if (a3ComVlanIfEntry) {
        p = (char *) a3ComVlanIfEntry + sizeof(productmib_a3ComVlanIfEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(a3ComVlanIfEntry);
    }
}

void
productmib_free_a3ComVlanIfTable(productmib_a3ComVlanIfEntry_t **a3ComVlanIfEntry)
{
    int i;

    if (a3ComVlanIfEntry) {
        for (i = 0; a3ComVlanIfEntry[i]; i++) {
            productmib_free_a3ComVlanIfEntry(a3ComVlanIfEntry[i]);
        }
        g_free(a3ComVlanIfEntry);
    }
}


