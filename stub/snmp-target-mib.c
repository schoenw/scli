/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from SNMP-TARGET-MIB:
 *   This MIB module defines MIB objects which provide
 *   mechanisms to remotely configure the parameters used
 *   by an SNMP entity for the generation of SNMP messages.
 *
 * Revision 1998-08-04 00:00:
 *   Clarifications, published as
 *   RFC2573.
 *
 * Revision 1997-07-14 00:00:
 *   The initial revision, published as RFC2273.
 *
 * $Id$
 */

#include "snmp-target-mib.h"

GSnmpEnum const snmp_target_mib_enums_snmpTargetAddrStorageType[] = {
    { SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_OTHER,       "other" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_VOLATILE,    "volatile" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_NONVOLATILE, "nonVolatile" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_PERMANENT,   "permanent" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE_READONLY,    "readOnly" },
    { 0, NULL }
};

GSnmpEnum const snmp_target_mib_enums_snmpTargetAddrRowStatus[] = {
    { SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_ACTIVE,        "active" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_NOTINSERVICE,  "notInService" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_NOTREADY,      "notReady" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_CREATEANDGO,   "createAndGo" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_CREATEANDWAIT, "createAndWait" },
    { SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS_DESTROY,       "destroy" },
    { 0, NULL }
};

GSnmpEnum const snmp_target_mib_enums_snmpTargetParamsSecurityLevel[] = {
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL_NOAUTHNOPRIV, "noAuthNoPriv" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL_AUTHNOPRIV,   "authNoPriv" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL_AUTHPRIV,     "authPriv" },
    { 0, NULL }
};

GSnmpEnum const snmp_target_mib_enums_snmpTargetParamsStorageType[] = {
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_OTHER,       "other" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_VOLATILE,    "volatile" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_NONVOLATILE, "nonVolatile" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_PERMANENT,   "permanent" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE_READONLY,    "readOnly" },
    { 0, NULL }
};

GSnmpEnum const snmp_target_mib_enums_snmpTargetParamsRowStatus[] = {
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_ACTIVE,        "active" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_NOTINSERVICE,  "notInService" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_NOTREADY,      "notReady" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_CREATEANDGO,   "createAndGo" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_CREATEANDWAIT, "createAndWait" },
    { SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS_DESTROY,       "destroy" },
    { 0, NULL }
};


static guint32 snmpTargetSpinLock_constraints[] = {0L, 2147483647L, 0, 0};
static guint16 snmpTargetAddrTAddress_constraints[] = {1, 255, 0, 0};
static guint32 snmpTargetAddrTimeout_constraints[] = {0L, 2147483647L, 0, 0};
static guint32 snmpTargetAddrRetryCount_constraints[] = {0L, 255L, 0, 0};
static guint16 snmpTargetAddrTagList_constraints[] = {0, 255, 0, 0};
static guint16 snmpTargetAddrParams_constraints[] = {1, 32, 0, 255, 0, 0};
static guint32 snmpTargetParamsMPModel_constraints[] = {0L, 2147483647L, 0, 0};
static guint32 snmpTargetParamsSecurityModel_constraints[] = {1L, 2147483647L, 0L, 2147483647L, 0, 0};
static guint16 snmpTargetParamsSecurityName_constraints[] = {0, 255, 0, 0};


static guint32 const snmpTargetObjects_oid[] = {1, 3, 6, 1, 6, 3, 12, 1};

static GSnmpAttribute snmpTargetObjects_attr[] = {
    { 1, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETSPINLOCK, "snmpTargetSpinLock",
       snmpTargetSpinLock_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetObjects_t, snmpTargetSpinLock),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_COUNTER32,
      SNMP_TARGET_MIB_SNMPUNAVAILABLECONTEXTS, "snmpUnavailableContexts",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetObjects_t, snmpUnavailableContexts),
      0,
      0 },
    { 5, G_SNMP_COUNTER32,
      SNMP_TARGET_MIB_SNMPUNKNOWNCONTEXTS, "snmpUnknownContexts",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetObjects_t, snmpUnknownContexts),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const snmpTargetAddrEntry_oid[] = {1, 3, 6, 1, 6, 3, 12, 1, 2, 1};

static GSnmpAttribute snmpTargetAddrEntry_attr[] = {
    { 2, G_SNMP_OBJECTID,
      SNMP_TARGET_MIB_SNMPTARGETADDRTDOMAIN, "snmpTargetAddrTDomain",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrTDomain),
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, _snmpTargetAddrTDomainLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, G_SNMP_OCTETSTRING,
      SNMP_TARGET_MIB_SNMPTARGETADDRTADDRESS, "snmpTargetAddrTAddress",
       snmpTargetAddrTAddress_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrTAddress),
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, _snmpTargetAddrTAddressLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETADDRTIMEOUT, "snmpTargetAddrTimeout",
       snmpTargetAddrTimeout_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrTimeout),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETADDRRETRYCOUNT, "snmpTargetAddrRetryCount",
       snmpTargetAddrRetryCount_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrRetryCount),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, G_SNMP_OCTETSTRING,
      SNMP_TARGET_MIB_SNMPTARGETADDRTAGLIST, "snmpTargetAddrTagList",
       snmpTargetAddrTagList_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrTagList),
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, _snmpTargetAddrTagListLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, G_SNMP_OCTETSTRING,
      SNMP_TARGET_MIB_SNMPTARGETADDRPARAMS, "snmpTargetAddrParams",
       snmpTargetAddrParams_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrParams),
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, _snmpTargetAddrParamsLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETADDRSTORAGETYPE, "snmpTargetAddrStorageType",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETADDRROWSTATUS, "snmpTargetAddrRowStatus",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetAddrEntry_t, snmpTargetAddrRowStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const snmpTargetParamsEntry_oid[] = {1, 3, 6, 1, 6, 3, 12, 1, 3, 1};

static GSnmpAttribute snmpTargetParamsEntry_attr[] = {
    { 2, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETPARAMSMPMODEL, "snmpTargetParamsMPModel",
       snmpTargetParamsMPModel_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetParamsEntry_t, snmpTargetParamsMPModel),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYMODEL, "snmpTargetParamsSecurityModel",
       snmpTargetParamsSecurityModel_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetParamsEntry_t, snmpTargetParamsSecurityModel),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_OCTETSTRING,
      SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYNAME, "snmpTargetParamsSecurityName",
       snmpTargetParamsSecurityName_constraints,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetParamsEntry_t, snmpTargetParamsSecurityName),
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetParamsEntry_t, _snmpTargetParamsSecurityNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETPARAMSSECURITYLEVEL, "snmpTargetParamsSecurityLevel",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetParamsEntry_t, snmpTargetParamsSecurityLevel),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETPARAMSSTORAGETYPE, "snmpTargetParamsStorageType",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetParamsEntry_t, snmpTargetParamsStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, G_SNMP_INTEGER32,
      SNMP_TARGET_MIB_SNMPTARGETPARAMSROWSTATUS, "snmpTargetParamsRowStatus",
       NULL,
      G_STRUCT_OFFSET(snmp_target_mib_snmpTargetParamsEntry_t, snmpTargetParamsRowStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


snmp_target_mib_snmpTargetObjects_t *
snmp_target_mib_new_snmpTargetObjects()
{
    snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects;

    snmpTargetObjects = (snmp_target_mib_snmpTargetObjects_t *) g_malloc0(sizeof(snmp_target_mib_snmpTargetObjects_t) + sizeof(gpointer));
    return snmpTargetObjects;
}

static snmp_target_mib_snmpTargetObjects_t *
assign_snmpTargetObjects(GSList *vbl)
{
    snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects;
    char *p;

    snmpTargetObjects = snmp_target_mib_new_snmpTargetObjects();
    if (! snmpTargetObjects) {
        return NULL;
    }

    p = (char *) snmpTargetObjects + sizeof(snmp_target_mib_snmpTargetObjects_t);
    * (GSList **) p = vbl;

    gsnmp_attr_assign(vbl, snmpTargetObjects_oid, sizeof(snmpTargetObjects_oid)/sizeof(guint32),
                      snmpTargetObjects_attr, snmpTargetObjects);

    return snmpTargetObjects;
}

void
snmp_target_mib_get_snmpTargetObjects(GSnmpSession *s, snmp_target_mib_snmpTargetObjects_t **snmpTargetObjects, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 12, 1, 0};

    *snmpTargetObjects = NULL;

    gsnmp_attr_get(s, &in, base, 9, 8, snmpTargetObjects_attr, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *snmpTargetObjects = assign_snmpTargetObjects(out);
    }
}

void
snmp_target_mib_set_snmpTargetObjects(GSnmpSession *s, snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 12, 1, 0, 0};

    gsnmp_attr_set(s, &in, base, 10, 8, snmpTargetObjects_attr, mask, snmpTargetObjects);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_target_mib_free_snmpTargetObjects(snmp_target_mib_snmpTargetObjects_t *snmpTargetObjects)
{
    GSList *vbl;
    char *p;

    if (snmpTargetObjects) {
        p = (char *) snmpTargetObjects + sizeof(snmp_target_mib_snmpTargetObjects_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpTargetObjects);
    }
}

snmp_target_mib_snmpTargetAddrEntry_t *
snmp_target_mib_new_snmpTargetAddrEntry()
{
    snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry;

    snmpTargetAddrEntry = (snmp_target_mib_snmpTargetAddrEntry_t *) g_malloc0(sizeof(snmp_target_mib_snmpTargetAddrEntry_t) + sizeof(gpointer));
    return snmpTargetAddrEntry;
}

static int
unpack_snmpTargetAddrEntry(GSnmpVarBind *vb, snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry)
{
    guint8 idx = 11;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id_len - idx;
    if (len < 1 || len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        snmpTargetAddrEntry->snmpTargetAddrName[i] = vb->id[idx++];
    }
    snmpTargetAddrEntry->_snmpTargetAddrNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_snmpTargetAddrEntry(guint32 *base, guchar *snmpTargetAddrName, guint16 _snmpTargetAddrNameLength)
{
    guint8 idx = 11;
    guint16 i, len;

    len = _snmpTargetAddrNameLength;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = snmpTargetAddrName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static snmp_target_mib_snmpTargetAddrEntry_t *
assign_snmpTargetAddrEntry(GSList *vbl)
{
    snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry;
    char *p;

    snmpTargetAddrEntry = snmp_target_mib_new_snmpTargetAddrEntry();
    if (! snmpTargetAddrEntry) {
        return NULL;
    }

    p = (char *) snmpTargetAddrEntry + sizeof(snmp_target_mib_snmpTargetAddrEntry_t);
    * (GSList **) p = vbl;

    if (unpack_snmpTargetAddrEntry((GSnmpVarBind *) vbl->data, snmpTargetAddrEntry) < 0) {
        g_warning("%s: invalid instance identifier", "snmpTargetAddrEntry");
        g_free(snmpTargetAddrEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, snmpTargetAddrEntry_oid, sizeof(snmpTargetAddrEntry_oid)/sizeof(guint32),
                      snmpTargetAddrEntry_attr, snmpTargetAddrEntry);

    return snmpTargetAddrEntry;
}

void
snmp_target_mib_get_snmpTargetAddrTable(GSnmpSession *s, snmp_target_mib_snmpTargetAddrEntry_t ***snmpTargetAddrEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 12, 1, 2, 1, 0};

    *snmpTargetAddrEntry = NULL;

    gsnmp_attr_get(s, &in, base, 11, 10, snmpTargetAddrEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *snmpTargetAddrEntry = (snmp_target_mib_snmpTargetAddrEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmp_target_mib_snmpTargetAddrEntry_t *));
        if (! *snmpTargetAddrEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*snmpTargetAddrEntry)[i] = assign_snmpTargetAddrEntry(row->data);
        }
    }
}

void
snmp_target_mib_get_snmpTargetAddrEntry(GSnmpSession *s, snmp_target_mib_snmpTargetAddrEntry_t **snmpTargetAddrEntry, guchar *snmpTargetAddrName, guint16 _snmpTargetAddrNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, snmpTargetAddrEntry_oid, sizeof(snmpTargetAddrEntry_oid));
    len = pack_snmpTargetAddrEntry(base, snmpTargetAddrName, _snmpTargetAddrNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "snmpTargetAddrEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *snmpTargetAddrEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 10, snmpTargetAddrEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *snmpTargetAddrEntry = assign_snmpTargetAddrEntry(out);
    }
}

void
snmp_target_mib_set_snmpTargetAddrEntry(GSnmpSession *s, snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, snmpTargetAddrEntry_oid, sizeof(snmpTargetAddrEntry_oid));
    len = pack_snmpTargetAddrEntry(base, snmpTargetAddrEntry->snmpTargetAddrName, snmpTargetAddrEntry->_snmpTargetAddrNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "snmpTargetAddrEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 10, snmpTargetAddrEntry_attr, mask, snmpTargetAddrEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_target_mib_free_snmpTargetAddrEntry(snmp_target_mib_snmpTargetAddrEntry_t *snmpTargetAddrEntry)
{
    GSList *vbl;
    char *p;

    if (snmpTargetAddrEntry) {
        p = (char *) snmpTargetAddrEntry + sizeof(snmp_target_mib_snmpTargetAddrEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpTargetAddrEntry);
    }
}

void
snmp_target_mib_free_snmpTargetAddrTable(snmp_target_mib_snmpTargetAddrEntry_t **snmpTargetAddrEntry)
{
    int i;

    if (snmpTargetAddrEntry) {
        for (i = 0; snmpTargetAddrEntry[i]; i++) {
            snmp_target_mib_free_snmpTargetAddrEntry(snmpTargetAddrEntry[i]);
        }
        g_free(snmpTargetAddrEntry);
    }
}

snmp_target_mib_snmpTargetParamsEntry_t *
snmp_target_mib_new_snmpTargetParamsEntry()
{
    snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry;

    snmpTargetParamsEntry = (snmp_target_mib_snmpTargetParamsEntry_t *) g_malloc0(sizeof(snmp_target_mib_snmpTargetParamsEntry_t) + sizeof(gpointer));
    return snmpTargetParamsEntry;
}

static int
unpack_snmpTargetParamsEntry(GSnmpVarBind *vb, snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry)
{
    guint8 idx = 11;
    guint16 i, len;

    if (vb->id_len < idx) return -1;
    len = vb->id_len - idx;
    if (len < 1 || len > 32) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        snmpTargetParamsEntry->snmpTargetParamsName[i] = vb->id[idx++];
    }
    snmpTargetParamsEntry->_snmpTargetParamsNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_snmpTargetParamsEntry(guint32 *base, guchar *snmpTargetParamsName, guint16 _snmpTargetParamsNameLength)
{
    guint8 idx = 11;
    guint16 i, len;

    len = _snmpTargetParamsNameLength;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = snmpTargetParamsName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static snmp_target_mib_snmpTargetParamsEntry_t *
assign_snmpTargetParamsEntry(GSList *vbl)
{
    snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry;
    char *p;

    snmpTargetParamsEntry = snmp_target_mib_new_snmpTargetParamsEntry();
    if (! snmpTargetParamsEntry) {
        return NULL;
    }

    p = (char *) snmpTargetParamsEntry + sizeof(snmp_target_mib_snmpTargetParamsEntry_t);
    * (GSList **) p = vbl;

    if (unpack_snmpTargetParamsEntry((GSnmpVarBind *) vbl->data, snmpTargetParamsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "snmpTargetParamsEntry");
        g_free(snmpTargetParamsEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, snmpTargetParamsEntry_oid, sizeof(snmpTargetParamsEntry_oid)/sizeof(guint32),
                      snmpTargetParamsEntry_attr, snmpTargetParamsEntry);

    return snmpTargetParamsEntry;
}

void
snmp_target_mib_get_snmpTargetParamsTable(GSnmpSession *s, snmp_target_mib_snmpTargetParamsEntry_t ***snmpTargetParamsEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 12, 1, 3, 1, 0};

    *snmpTargetParamsEntry = NULL;

    gsnmp_attr_get(s, &in, base, 11, 10, snmpTargetParamsEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *snmpTargetParamsEntry = (snmp_target_mib_snmpTargetParamsEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmp_target_mib_snmpTargetParamsEntry_t *));
        if (! *snmpTargetParamsEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*snmpTargetParamsEntry)[i] = assign_snmpTargetParamsEntry(row->data);
        }
    }
}

void
snmp_target_mib_get_snmpTargetParamsEntry(GSnmpSession *s, snmp_target_mib_snmpTargetParamsEntry_t **snmpTargetParamsEntry, guchar *snmpTargetParamsName, guint16 _snmpTargetParamsNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, snmpTargetParamsEntry_oid, sizeof(snmpTargetParamsEntry_oid));
    len = pack_snmpTargetParamsEntry(base, snmpTargetParamsName, _snmpTargetParamsNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "snmpTargetParamsEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *snmpTargetParamsEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 10, snmpTargetParamsEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *snmpTargetParamsEntry = assign_snmpTargetParamsEntry(out);
    }
}

void
snmp_target_mib_set_snmpTargetParamsEntry(GSnmpSession *s, snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, snmpTargetParamsEntry_oid, sizeof(snmpTargetParamsEntry_oid));
    len = pack_snmpTargetParamsEntry(base, snmpTargetParamsEntry->snmpTargetParamsName, snmpTargetParamsEntry->_snmpTargetParamsNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "snmpTargetParamsEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 10, snmpTargetParamsEntry_attr, mask, snmpTargetParamsEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_target_mib_free_snmpTargetParamsEntry(snmp_target_mib_snmpTargetParamsEntry_t *snmpTargetParamsEntry)
{
    GSList *vbl;
    char *p;

    if (snmpTargetParamsEntry) {
        p = (char *) snmpTargetParamsEntry + sizeof(snmp_target_mib_snmpTargetParamsEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpTargetParamsEntry);
    }
}

void
snmp_target_mib_free_snmpTargetParamsTable(snmp_target_mib_snmpTargetParamsEntry_t **snmpTargetParamsEntry)
{
    int i;

    if (snmpTargetParamsEntry) {
        for (i = 0; snmpTargetParamsEntry[i]; i++) {
            snmp_target_mib_free_snmpTargetParamsEntry(snmpTargetParamsEntry[i]);
        }
        g_free(snmpTargetParamsEntry);
    }
}


