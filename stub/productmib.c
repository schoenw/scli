/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli \
 *     --scli-include='a3ComVlanIfEntry|a3ComVirtualGroup' PRODUCTMIB
 *
 * Derived from PRODUCTMIB:
 *
 * $Id$
 */

#include "productmib.h"

GNetSnmpEnum const productmib_enums_EntryStatus[] = {
    { PRODUCTMIB_ENTRYSTATUS_VALID,         "valid" },
    { PRODUCTMIB_ENTRYSTATUS_CREATEREQUEST, "createRequest" },
    { PRODUCTMIB_ENTRYSTATUS_UNDERCREATION, "underCreation" },
    { PRODUCTMIB_ENTRYSTATUS_INVALID,       "invalid" },
    { 0, NULL }
};

GNetSnmpEnum const productmib_enums_RowStatus[] = {
    { PRODUCTMIB_ROWSTATUS_ACTIVE,        "active" },
    { PRODUCTMIB_ROWSTATUS_NOTINSERVICE,  "notInService" },
    { PRODUCTMIB_ROWSTATUS_NOTREADY,      "notReady" },
    { PRODUCTMIB_ROWSTATUS_CREATEANDGO,   "createAndGo" },
    { PRODUCTMIB_ROWSTATUS_CREATEANDWAIT, "createAndWait" },
    { PRODUCTMIB_ROWSTATUS_DESTROY,       "destroy" },
    { 0, NULL }
};

GNetSnmpEnum const productmib_enums_A3ComVlanType[] = {
    { PRODUCTMIB_A3COMVLANTYPE_VLANLAYER2,            "vlanLayer2" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANDEFAULTPROTOCOLS,  "vlanDefaultProtocols" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANIPPROTOCOL,        "vlanIPProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANIPXPROTOCOL,       "vlanIPXProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANAPPLETALKPROTOCOL, "vlanAppleTalkProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANXNSPROTOCOL,       "vlanXNSProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANISOPROTOCOL,       "vlanISOProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANDECNETPROTOCOL,    "vlanDECNetProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANNETBIOSPROTOCOL,   "vlanNetBIOSProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANSNAPROTOCOL,       "vlanSNAProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANVINESPROTOCOL,     "vlanVINESProtocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANX25PROTOCOL,       "vlanX25Protocol" },
    { PRODUCTMIB_A3COMVLANTYPE_VLANIGMPPROTOCOL,      "vlanIGMPProtocol" },
    { 0, NULL }
};

GNetSnmpEnum const productmib_enums_A3ComVlanEncapsType[] = {
    { PRODUCTMIB_A3COMVLANENCAPSTYPE_VLANENCAPS3COMPROPRIETARYPDD, "vlanEncaps3ComProprietaryPDD" },
    { PRODUCTMIB_A3COMVLANENCAPSTYPE_VLANENCAPS8021Q,              "vlanEncaps8021q" },
    { PRODUCTMIB_A3COMVLANENCAPSTYPE_VLANENCAPSPRE8021QONCORE,     "vlanEncapsPre8021qONcore" },
    { 0, NULL }
};

GNetSnmpEnum const productmib_enums_TruthValue[] = {
    { PRODUCTMIB_TRUTHVALUE_TRUE,  "true" },
    { PRODUCTMIB_TRUTHVALUE_FALSE, "false" },
    { 0, NULL }
};


static guint32 const coldStart[]
	= { PRODUCTMIB_COLDSTART };
static guint32 const warmStart[]
	= { PRODUCTMIB_WARMSTART };
static guint32 const linkDown[]
	= { PRODUCTMIB_LINKDOWN };
static guint32 const linkUp[]
	= { PRODUCTMIB_LINKUP };
static guint32 const authenticationFailure[]
	= { PRODUCTMIB_AUTHENTICATIONFAILURE };
static guint32 const risingAlarm[]
	= { PRODUCTMIB_RISINGALARM };
static guint32 const fallingAlarm[]
	= { PRODUCTMIB_FALLINGALARM };
static guint32 const newRoot[]
	= { PRODUCTMIB_NEWROOT };
static guint32 const topologyChange[]
	= { PRODUCTMIB_TOPOLOGYCHANGE };
static guint32 const resResilienceSwitch[]
	= { PRODUCTMIB_RESRESILIENCESWITCH };
static guint32 const resStateChange[]
	= { PRODUCTMIB_RESSTATECHANGE };
static guint32 const brDatabaseFull[]
	= { PRODUCTMIB_BRDATABASEFULL };
static guint32 const secureAddressLearned[]
	= { PRODUCTMIB_SECUREADDRESSLEARNED };
static guint32 const remPollSuccessTrap[]
	= { PRODUCTMIB_REMPOLLSUCCESSTRAP };
static guint32 const remPollFailureTrap[]
	= { PRODUCTMIB_REMPOLLFAILURETRAP };
static guint32 const eventGenericTrap[]
	= { PRODUCTMIB_EVENTGENERICTRAP };
static guint32 const brDesktopMisconfiguration[]
	= { PRODUCTMIB_BRDESKTOPMISCONFIGURATION };
static guint32 const secureAddressLearned2[]
	= { PRODUCTMIB_SECUREADDRESSLEARNED2 };
static guint32 const secureViolation3[]
	= { PRODUCTMIB_SECUREVIOLATION3 };

GNetSnmpIdentity const productmib_notifications[] = {
    { coldStart,
      G_N_ELEMENTS(coldStart),
      "coldStart" },
    { warmStart,
      G_N_ELEMENTS(warmStart),
      "warmStart" },
    { linkDown,
      G_N_ELEMENTS(linkDown),
      "linkDown" },
    { linkUp,
      G_N_ELEMENTS(linkUp),
      "linkUp" },
    { authenticationFailure,
      G_N_ELEMENTS(authenticationFailure),
      "authenticationFailure" },
    { risingAlarm,
      G_N_ELEMENTS(risingAlarm),
      "risingAlarm" },
    { fallingAlarm,
      G_N_ELEMENTS(fallingAlarm),
      "fallingAlarm" },
    { newRoot,
      G_N_ELEMENTS(newRoot),
      "newRoot" },
    { topologyChange,
      G_N_ELEMENTS(topologyChange),
      "topologyChange" },
    { resResilienceSwitch,
      G_N_ELEMENTS(resResilienceSwitch),
      "resResilienceSwitch" },
    { resStateChange,
      G_N_ELEMENTS(resStateChange),
      "resStateChange" },
    { brDatabaseFull,
      G_N_ELEMENTS(brDatabaseFull),
      "brDatabaseFull" },
    { secureAddressLearned,
      G_N_ELEMENTS(secureAddressLearned),
      "secureAddressLearned" },
    { remPollSuccessTrap,
      G_N_ELEMENTS(remPollSuccessTrap),
      "remPollSuccessTrap" },
    { remPollFailureTrap,
      G_N_ELEMENTS(remPollFailureTrap),
      "remPollFailureTrap" },
    { eventGenericTrap,
      G_N_ELEMENTS(eventGenericTrap),
      "eventGenericTrap" },
    { brDesktopMisconfiguration,
      G_N_ELEMENTS(brDesktopMisconfiguration),
      "brDesktopMisconfiguration" },
    { secureAddressLearned2,
      G_N_ELEMENTS(secureAddressLearned2),
      "secureAddressLearned2" },
    { secureViolation3,
      G_N_ELEMENTS(secureViolation3),
      "secureViolation3" },
    { 0, 0, NULL }
};


static guint16 a3ComVlanIfDescr_constraints[] = {0U, 80U, 0, 0};
static gint32 a3ComVlanIfGlobalIdentifier_constraints[] = {0L, 65535L, 0, 0};


static guint32 const a3ComVlanIfEntry_oid[] = {1, 3, 6, 1, 4, 1, 43, 10, 1, 14, 1, 2, 1};

static GNetSnmpAttribute a3ComVlanIfEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      PRODUCTMIB_A3COMVLANIFDESCR, "a3ComVlanIfDescr",
       a3ComVlanIfDescr_constraints,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfDescr),
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, _a3ComVlanIfDescrLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      PRODUCTMIB_A3COMVLANIFTYPE, "a3ComVlanIfType",
       NULL,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      PRODUCTMIB_A3COMVLANIFGLOBALIDENTIFIER, "a3ComVlanIfGlobalIdentifier",
       a3ComVlanIfGlobalIdentifier_constraints,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfGlobalIdentifier),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      PRODUCTMIB_A3COMVLANIFINFO, "a3ComVlanIfInfo",
       NULL,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfInfo),
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, _a3ComVlanIfInfoLength),
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      PRODUCTMIB_A3COMVLANIFSTATUS, "a3ComVlanIfStatus",
       NULL,
      G_STRUCT_OFFSET(productmib_a3ComVlanIfEntry_t, a3ComVlanIfStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const a3ComVirtualGroup_oid[] = {1, 3, 6, 1, 4, 1, 43, 10, 1, 14, 3};

static GNetSnmpAttribute a3ComVirtualGroup_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      PRODUCTMIB_A3COMNEXTAVAILABLEVIRTIFINDEX, "a3ComNextAvailableVirtIfIndex",
       NULL,
      G_STRUCT_OFFSET(productmib_a3ComVirtualGroup_t, a3ComNextAvailableVirtIfIndex),
      0,
      0 },
    { 0, 0, 0, NULL }
};


productmib_a3ComVlanIfEntry_t *
productmib_new_a3ComVlanIfEntry()
{
    productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry;

    a3ComVlanIfEntry = (productmib_a3ComVlanIfEntry_t *) g_malloc0(sizeof(productmib_a3ComVlanIfEntry_t) + sizeof(gpointer));
    return a3ComVlanIfEntry;
}

static inline int
unpack_a3ComVlanIfEntry(GNetSnmpVarBind *vb, productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry)
{
    guint8 idx = 14;

    if (vb->oid_len < idx) return -1;
    a3ComVlanIfEntry->a3ComVlanIfIndex = vb->oid[idx++];
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_a3ComVlanIfEntry(guint32 *base, gint32 a3ComVlanIfIndex)
{
    guint8 idx = 14;

    base[idx++] = a3ComVlanIfIndex;
    return idx;
}

static inline productmib_a3ComVlanIfEntry_t *
assign_a3ComVlanIfEntry(GList *vbl)
{
    productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry;
    char *p;

    a3ComVlanIfEntry = productmib_new_a3ComVlanIfEntry();
    p = (char *) a3ComVlanIfEntry + sizeof(productmib_a3ComVlanIfEntry_t);
    * (GList **) p = vbl;

    if (unpack_a3ComVlanIfEntry((GNetSnmpVarBind *) vbl->data, a3ComVlanIfEntry) < 0) {
        g_warning("%s: invalid instance identifier", "a3ComVlanIfEntry");
        g_free(a3ComVlanIfEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, a3ComVlanIfEntry_oid, G_N_ELEMENTS(a3ComVlanIfEntry_oid),
                      a3ComVlanIfEntry_attr, a3ComVlanIfEntry);

    return a3ComVlanIfEntry;
}

void
productmib_get_a3ComVlanIfTable(GNetSnmp *s, productmib_a3ComVlanIfEntry_t ***a3ComVlanIfEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 4, 1, 43, 10, 1, 14, 1, 2, 1, 0};
    guint32 base[128];

    *a3ComVlanIfEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 14, 13, a3ComVlanIfEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *a3ComVlanIfEntry = (productmib_a3ComVlanIfEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(productmib_a3ComVlanIfEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*a3ComVlanIfEntry)[i] = assign_a3ComVlanIfEntry(row->data);
        }
    }
}

void
productmib_get_a3ComVlanIfEntry(GNetSnmp *s, productmib_a3ComVlanIfEntry_t **a3ComVlanIfEntry, gint32 a3ComVlanIfIndex, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, a3ComVlanIfEntry_oid, sizeof(a3ComVlanIfEntry_oid));
    len = pack_a3ComVlanIfEntry(base, a3ComVlanIfIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "a3ComVlanIfEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *a3ComVlanIfEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 13, a3ComVlanIfEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *a3ComVlanIfEntry = assign_a3ComVlanIfEntry(out);
    }
}

void
productmib_set_a3ComVlanIfEntry(GNetSnmp *s, productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, a3ComVlanIfEntry_oid, sizeof(a3ComVlanIfEntry_oid));
    len = pack_a3ComVlanIfEntry(base, a3ComVlanIfEntry->a3ComVlanIfIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "a3ComVlanIfEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 13, a3ComVlanIfEntry_attr, mask, a3ComVlanIfEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
productmib_free_a3ComVlanIfEntry(productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry)
{
    GList *vbl;
    char *p;

    if (a3ComVlanIfEntry) {
        p = (char *) a3ComVlanIfEntry + sizeof(productmib_a3ComVlanIfEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
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

productmib_a3ComVirtualGroup_t *
productmib_new_a3ComVirtualGroup()
{
    productmib_a3ComVirtualGroup_t *a3ComVirtualGroup;

    a3ComVirtualGroup = (productmib_a3ComVirtualGroup_t *) g_malloc0(sizeof(productmib_a3ComVirtualGroup_t) + sizeof(gpointer));
    return a3ComVirtualGroup;
}

static inline productmib_a3ComVirtualGroup_t *
assign_a3ComVirtualGroup(GList *vbl)
{
    productmib_a3ComVirtualGroup_t *a3ComVirtualGroup;
    char *p;

    a3ComVirtualGroup = productmib_new_a3ComVirtualGroup();
    p = (char *) a3ComVirtualGroup + sizeof(productmib_a3ComVirtualGroup_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, a3ComVirtualGroup_oid, G_N_ELEMENTS(a3ComVirtualGroup_oid),
                      a3ComVirtualGroup_attr, a3ComVirtualGroup);

    return a3ComVirtualGroup;
}

void
productmib_get_a3ComVirtualGroup(GNetSnmp *s, productmib_a3ComVirtualGroup_t **a3ComVirtualGroup, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static const guint32 _base[] = {1, 3, 6, 1, 4, 1, 43, 10, 1, 14, 3, 0};
    guint32 base[128];

    *a3ComVirtualGroup = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 12, 11, a3ComVirtualGroup_attr, mask);

    out = gnet_snmp_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *a3ComVirtualGroup = assign_a3ComVirtualGroup(out);
    }
}

void
productmib_free_a3ComVirtualGroup(productmib_a3ComVirtualGroup_t *a3ComVirtualGroup)
{
    GList *vbl;
    char *p;

    if (a3ComVirtualGroup) {
        p = (char *) a3ComVirtualGroup + sizeof(productmib_a3ComVirtualGroup_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(a3ComVirtualGroup);
    }
}


