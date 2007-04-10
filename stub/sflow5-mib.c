/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli SFLOW5-MIB
 *
 * Derived from SFLOW5-MIB:
 *   The MIB module for managing the generation and transportation
 *   of sFlow data records.
 *
 * Revision 2003-10-18 00:00:
 *   Version 1.3 (draft 5)
 *   
 *   Allow set to SFlowReceiver if it doesn't change
 *   value.
 *
 * Revision 2003-09-24 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 2003-09-24 00:00:
 *   Version 1.3 (draft 4)
 *   
 *   Default value of sFlowRcvrAddress should be '00000000' h.
 *   Default value of sFlowCpReceiver should be 0.
 *
 * Revision 2003-04-08 00:00:
 *   Version 1.3 (draft 3)
 *   
 *   Clarify semantics of counter polling interval, 
 *   sFlowCpInterval.
 *
 * Revision 2002-09-17 00:00:
 *   Version 1.3 (draft 2)
 *   
 *   Adds support for multiple sFlow samplers per sFlowDataSource.
 *   Moved to sflow.org enterprise number.
 *   Splits flow sampling, counter polling and receiver 
 *   specification into separate tables.
 *
 * Revision 2001-07-31 00:00:
 *   Version 1.2
 *   
 *   Brings MIB into SMI v2 compliance.
 *
 * Revision 2001-05-01 00:00:
 *   Version 1.1
 *   
 *   Adds sfDatagramVersion.
 *
 * $Id$
 */

#include "sflow5-mib.h"

static guint16 sFlowVersion_constraints[] = {0U, 255U, 0, 0};
static guint16 sFlowAgentAddress_constraints[] = {0U, 255U, 0, 0};
static guint16 sFlowRcvrOwner_constraints[] = {0U, 127U, 0, 0};
static guint16 sFlowRcvrAddress_constraints[] = {0U, 255U, 0, 0};


static guint32 const sFlowAgent_oid[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1};

static GNetSnmpAttribute sFlowAgent_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SFLOW5_MIB_SFLOWVERSION, "sFlowVersion",
       sFlowVersion_constraints,
      G_STRUCT_OFFSET(sflow5_mib_sFlowAgent_t, sFlowVersion),
      G_STRUCT_OFFSET(sflow5_mib_sFlowAgent_t, _sFlowVersionLength),
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWAGENTADDRESSTYPE, "sFlowAgentAddressType",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowAgent_t, sFlowAgentAddressType),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SFLOW5_MIB_SFLOWAGENTADDRESS, "sFlowAgentAddress",
       sFlowAgentAddress_constraints,
      G_STRUCT_OFFSET(sflow5_mib_sFlowAgent_t, sFlowAgentAddress),
      G_STRUCT_OFFSET(sflow5_mib_sFlowAgent_t, _sFlowAgentAddressLength),
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const sFlowRcvrEntry_oid[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1, 4, 1};

static GNetSnmpAttribute sFlowRcvrEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SFLOW5_MIB_SFLOWRCVROWNER, "sFlowRcvrOwner",
       sFlowRcvrOwner_constraints,
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, sFlowRcvrOwner),
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, _sFlowRcvrOwnerLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWRCVRTIMEOUT, "sFlowRcvrTimeout",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, sFlowRcvrTimeout),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWRCVRMAXIMUMDATAGRAMSIZE, "sFlowRcvrMaximumDatagramSize",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, sFlowRcvrMaximumDatagramSize),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWRCVRADDRESSTYPE, "sFlowRcvrAddressType",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, sFlowRcvrAddressType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SFLOW5_MIB_SFLOWRCVRADDRESS, "sFlowRcvrAddress",
       sFlowRcvrAddress_constraints,
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, sFlowRcvrAddress),
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, _sFlowRcvrAddressLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWRCVRPORT, "sFlowRcvrPort",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, sFlowRcvrPort),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWRCVRDATAGRAMVERSION, "sFlowRcvrDatagramVersion",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowRcvrEntry_t, sFlowRcvrDatagramVersion),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const sFlowFsEntry_oid[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1, 5, 1};

static GNetSnmpAttribute sFlowFsEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWFSRECEIVER, "sFlowFsReceiver",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowFsEntry_t, sFlowFsReceiver),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWFSPACKETSAMPLINGRATE, "sFlowFsPacketSamplingRate",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowFsEntry_t, sFlowFsPacketSamplingRate),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWFSMAXIMUMHEADERSIZE, "sFlowFsMaximumHeaderSize",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowFsEntry_t, sFlowFsMaximumHeaderSize),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const sFlowCpEntry_oid[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1, 6, 1};

static GNetSnmpAttribute sFlowCpEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWCPRECEIVER, "sFlowCpReceiver",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowCpEntry_t, sFlowCpReceiver),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SFLOW5_MIB_SFLOWCPINTERVAL, "sFlowCpInterval",
       NULL,
      G_STRUCT_OFFSET(sflow5_mib_sFlowCpEntry_t, sFlowCpInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


sflow5_mib_sFlowAgent_t *
sflow5_mib_new_sFlowAgent()
{
    sflow5_mib_sFlowAgent_t *sFlowAgent;

    sFlowAgent = (sflow5_mib_sFlowAgent_t *) g_malloc0(sizeof(sflow5_mib_sFlowAgent_t) + sizeof(gpointer));
    return sFlowAgent;
}

static inline sflow5_mib_sFlowAgent_t *
assign_sFlowAgent(GList *vbl)
{
    sflow5_mib_sFlowAgent_t *sFlowAgent;
    char *p;

    sFlowAgent = sflow5_mib_new_sFlowAgent();
    p = (char *) sFlowAgent + sizeof(sflow5_mib_sFlowAgent_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, sFlowAgent_oid, G_N_ELEMENTS(sFlowAgent_oid),
                      sFlowAgent_attr, sFlowAgent);

    return sFlowAgent;
}

void
sflow5_mib_get_sFlowAgent(GNetSnmp *s, sflow5_mib_sFlowAgent_t **sFlowAgent, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1, 0};

    *sFlowAgent = NULL;

    gnet_snmp_attr_get(s, &in, base, 10, 9, sFlowAgent_attr, mask);

    out = gnet_snmp_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *sFlowAgent = assign_sFlowAgent(out);
    }
}

void
sflow5_mib_free_sFlowAgent(sflow5_mib_sFlowAgent_t *sFlowAgent)
{
    GList *vbl;
    char *p;

    if (sFlowAgent) {
        p = (char *) sFlowAgent + sizeof(sflow5_mib_sFlowAgent_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(sFlowAgent);
    }
}

sflow5_mib_sFlowRcvrEntry_t *
sflow5_mib_new_sFlowRcvrEntry()
{
    sflow5_mib_sFlowRcvrEntry_t *sFlowRcvrEntry;

    sFlowRcvrEntry = (sflow5_mib_sFlowRcvrEntry_t *) g_malloc0(sizeof(sflow5_mib_sFlowRcvrEntry_t) + sizeof(gpointer));
    return sFlowRcvrEntry;
}

static inline int
unpack_sFlowRcvrEntry(GNetSnmpVarBind *vb, sflow5_mib_sFlowRcvrEntry_t *sFlowRcvrEntry)
{
    guint8 idx = 12;

    if (vb->oid_len < idx) return -1;
    sFlowRcvrEntry->sFlowRcvrIndex = vb->oid[idx++];
    if ((sFlowRcvrEntry->sFlowRcvrIndex < 1 || sFlowRcvrEntry->sFlowRcvrIndex > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_sFlowRcvrEntry(guint32 *base, gint32 sFlowRcvrIndex)
{
    guint8 idx = 12;

    base[idx++] = sFlowRcvrIndex;
    return idx;
}

static inline sflow5_mib_sFlowRcvrEntry_t *
assign_sFlowRcvrEntry(GList *vbl)
{
    sflow5_mib_sFlowRcvrEntry_t *sFlowRcvrEntry;
    char *p;

    sFlowRcvrEntry = sflow5_mib_new_sFlowRcvrEntry();
    p = (char *) sFlowRcvrEntry + sizeof(sflow5_mib_sFlowRcvrEntry_t);
    * (GList **) p = vbl;

    if (unpack_sFlowRcvrEntry((GNetSnmpVarBind *) vbl->data, sFlowRcvrEntry) < 0) {
        g_warning("%s: invalid instance identifier", "sFlowRcvrEntry");
        g_free(sFlowRcvrEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, sFlowRcvrEntry_oid, G_N_ELEMENTS(sFlowRcvrEntry_oid),
                      sFlowRcvrEntry_attr, sFlowRcvrEntry);

    return sFlowRcvrEntry;
}

void
sflow5_mib_get_sFlowRcvrTable(GNetSnmp *s, sflow5_mib_sFlowRcvrEntry_t ***sFlowRcvrEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1, 4, 1, 0};

    *sFlowRcvrEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 12, 11, sFlowRcvrEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *sFlowRcvrEntry = (sflow5_mib_sFlowRcvrEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(sflow5_mib_sFlowRcvrEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*sFlowRcvrEntry)[i] = assign_sFlowRcvrEntry(row->data);
        }
    }
}

void
sflow5_mib_get_sFlowRcvrEntry(GNetSnmp *s, sflow5_mib_sFlowRcvrEntry_t **sFlowRcvrEntry, gint32 sFlowRcvrIndex, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sFlowRcvrEntry_oid, sizeof(sFlowRcvrEntry_oid));
    len = pack_sFlowRcvrEntry(base, sFlowRcvrIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "sFlowRcvrEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *sFlowRcvrEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, sFlowRcvrEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *sFlowRcvrEntry = assign_sFlowRcvrEntry(out);
    }
}

void
sflow5_mib_set_sFlowRcvrEntry(GNetSnmp *s, sflow5_mib_sFlowRcvrEntry_t *sFlowRcvrEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sFlowRcvrEntry_oid, sizeof(sFlowRcvrEntry_oid));
    len = pack_sFlowRcvrEntry(base, sFlowRcvrEntry->sFlowRcvrIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "sFlowRcvrEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 11, sFlowRcvrEntry_attr, mask, sFlowRcvrEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
sflow5_mib_free_sFlowRcvrEntry(sflow5_mib_sFlowRcvrEntry_t *sFlowRcvrEntry)
{
    GList *vbl;
    char *p;

    if (sFlowRcvrEntry) {
        p = (char *) sFlowRcvrEntry + sizeof(sflow5_mib_sFlowRcvrEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(sFlowRcvrEntry);
    }
}

void
sflow5_mib_free_sFlowRcvrTable(sflow5_mib_sFlowRcvrEntry_t **sFlowRcvrEntry)
{
    int i;

    if (sFlowRcvrEntry) {
        for (i = 0; sFlowRcvrEntry[i]; i++) {
            sflow5_mib_free_sFlowRcvrEntry(sFlowRcvrEntry[i]);
        }
        g_free(sFlowRcvrEntry);
    }
}

sflow5_mib_sFlowFsEntry_t *
sflow5_mib_new_sFlowFsEntry()
{
    sflow5_mib_sFlowFsEntry_t *sFlowFsEntry;

    sFlowFsEntry = (sflow5_mib_sFlowFsEntry_t *) g_malloc0(sizeof(sflow5_mib_sFlowFsEntry_t) + sizeof(gpointer));
    return sFlowFsEntry;
}

static inline int
unpack_sFlowFsEntry(GNetSnmpVarBind *vb, sflow5_mib_sFlowFsEntry_t *sFlowFsEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (vb->oid_len < idx + len) return -1;
    if (len > 116) return -1;
    for (i = 0; i < len; i++) {
        sFlowFsEntry->sFlowFsDataSource[i] = vb->oid[idx++];
    }
    sFlowFsEntry->_sFlowFsDataSourceLength = len;
    if (vb->oid_len < idx) return -1;
    sFlowFsEntry->sFlowFsInstance = vb->oid[idx++];
    if ((sFlowFsEntry->sFlowFsInstance < 1 || sFlowFsEntry->sFlowFsInstance > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_sFlowFsEntry(guint32 *base, guint32 *sFlowFsDataSource, guint16 _sFlowFsDataSourceLength, gint32 sFlowFsInstance)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _sFlowFsDataSourceLength;
    base[idx++] = len;
    if (len > 116) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = sFlowFsDataSource[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = sFlowFsInstance;
    return idx;
}

static inline sflow5_mib_sFlowFsEntry_t *
assign_sFlowFsEntry(GList *vbl)
{
    sflow5_mib_sFlowFsEntry_t *sFlowFsEntry;
    char *p;

    sFlowFsEntry = sflow5_mib_new_sFlowFsEntry();
    p = (char *) sFlowFsEntry + sizeof(sflow5_mib_sFlowFsEntry_t);
    * (GList **) p = vbl;

    if (unpack_sFlowFsEntry((GNetSnmpVarBind *) vbl->data, sFlowFsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "sFlowFsEntry");
        g_free(sFlowFsEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, sFlowFsEntry_oid, G_N_ELEMENTS(sFlowFsEntry_oid),
                      sFlowFsEntry_attr, sFlowFsEntry);

    return sFlowFsEntry;
}

void
sflow5_mib_get_sFlowFsTable(GNetSnmp *s, sflow5_mib_sFlowFsEntry_t ***sFlowFsEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1, 5, 1, 0};

    *sFlowFsEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 12, 11, sFlowFsEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *sFlowFsEntry = (sflow5_mib_sFlowFsEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(sflow5_mib_sFlowFsEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*sFlowFsEntry)[i] = assign_sFlowFsEntry(row->data);
        }
    }
}

void
sflow5_mib_get_sFlowFsEntry(GNetSnmp *s, sflow5_mib_sFlowFsEntry_t **sFlowFsEntry, guint32 *sFlowFsDataSource, guint16 _sFlowFsDataSourceLength, gint32 sFlowFsInstance, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sFlowFsEntry_oid, sizeof(sFlowFsEntry_oid));
    len = pack_sFlowFsEntry(base, sFlowFsDataSource, _sFlowFsDataSourceLength, sFlowFsInstance);
    if (len < 0) {
        g_warning("%s: invalid index values", "sFlowFsEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *sFlowFsEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, sFlowFsEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *sFlowFsEntry = assign_sFlowFsEntry(out);
    }
}

void
sflow5_mib_set_sFlowFsEntry(GNetSnmp *s, sflow5_mib_sFlowFsEntry_t *sFlowFsEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sFlowFsEntry_oid, sizeof(sFlowFsEntry_oid));
    len = pack_sFlowFsEntry(base, sFlowFsEntry->sFlowFsDataSource, sFlowFsEntry->_sFlowFsDataSourceLength, sFlowFsEntry->sFlowFsInstance);
    if (len < 0) {
        g_warning("%s: invalid index values", "sFlowFsEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 11, sFlowFsEntry_attr, mask, sFlowFsEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
sflow5_mib_free_sFlowFsEntry(sflow5_mib_sFlowFsEntry_t *sFlowFsEntry)
{
    GList *vbl;
    char *p;

    if (sFlowFsEntry) {
        p = (char *) sFlowFsEntry + sizeof(sflow5_mib_sFlowFsEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(sFlowFsEntry);
    }
}

void
sflow5_mib_free_sFlowFsTable(sflow5_mib_sFlowFsEntry_t **sFlowFsEntry)
{
    int i;

    if (sFlowFsEntry) {
        for (i = 0; sFlowFsEntry[i]; i++) {
            sflow5_mib_free_sFlowFsEntry(sFlowFsEntry[i]);
        }
        g_free(sFlowFsEntry);
    }
}

sflow5_mib_sFlowCpEntry_t *
sflow5_mib_new_sFlowCpEntry()
{
    sflow5_mib_sFlowCpEntry_t *sFlowCpEntry;

    sFlowCpEntry = (sflow5_mib_sFlowCpEntry_t *) g_malloc0(sizeof(sflow5_mib_sFlowCpEntry_t) + sizeof(gpointer));
    return sFlowCpEntry;
}

static inline int
unpack_sFlowCpEntry(GNetSnmpVarBind *vb, sflow5_mib_sFlowCpEntry_t *sFlowCpEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (vb->oid_len < idx + len) return -1;
    if (len > 116) return -1;
    for (i = 0; i < len; i++) {
        sFlowCpEntry->sFlowCpDataSource[i] = vb->oid[idx++];
    }
    sFlowCpEntry->_sFlowCpDataSourceLength = len;
    if (vb->oid_len < idx) return -1;
    sFlowCpEntry->sFlowCpInstance = vb->oid[idx++];
    if ((sFlowCpEntry->sFlowCpInstance < 1 || sFlowCpEntry->sFlowCpInstance > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_sFlowCpEntry(guint32 *base, guint32 *sFlowCpDataSource, guint16 _sFlowCpDataSourceLength, gint32 sFlowCpInstance)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _sFlowCpDataSourceLength;
    base[idx++] = len;
    if (len > 116) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = sFlowCpDataSource[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = sFlowCpInstance;
    return idx;
}

static inline sflow5_mib_sFlowCpEntry_t *
assign_sFlowCpEntry(GList *vbl)
{
    sflow5_mib_sFlowCpEntry_t *sFlowCpEntry;
    char *p;

    sFlowCpEntry = sflow5_mib_new_sFlowCpEntry();
    p = (char *) sFlowCpEntry + sizeof(sflow5_mib_sFlowCpEntry_t);
    * (GList **) p = vbl;

    if (unpack_sFlowCpEntry((GNetSnmpVarBind *) vbl->data, sFlowCpEntry) < 0) {
        g_warning("%s: invalid instance identifier", "sFlowCpEntry");
        g_free(sFlowCpEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, sFlowCpEntry_oid, G_N_ELEMENTS(sFlowCpEntry_oid),
                      sFlowCpEntry_attr, sFlowCpEntry);

    return sFlowCpEntry;
}

void
sflow5_mib_get_sFlowCpTable(GNetSnmp *s, sflow5_mib_sFlowCpEntry_t ***sFlowCpEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 14706, 1, 1, 6, 1, 0};

    *sFlowCpEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 12, 11, sFlowCpEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *sFlowCpEntry = (sflow5_mib_sFlowCpEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(sflow5_mib_sFlowCpEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*sFlowCpEntry)[i] = assign_sFlowCpEntry(row->data);
        }
    }
}

void
sflow5_mib_get_sFlowCpEntry(GNetSnmp *s, sflow5_mib_sFlowCpEntry_t **sFlowCpEntry, guint32 *sFlowCpDataSource, guint16 _sFlowCpDataSourceLength, gint32 sFlowCpInstance, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sFlowCpEntry_oid, sizeof(sFlowCpEntry_oid));
    len = pack_sFlowCpEntry(base, sFlowCpDataSource, _sFlowCpDataSourceLength, sFlowCpInstance);
    if (len < 0) {
        g_warning("%s: invalid index values", "sFlowCpEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *sFlowCpEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, sFlowCpEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *sFlowCpEntry = assign_sFlowCpEntry(out);
    }
}

void
sflow5_mib_set_sFlowCpEntry(GNetSnmp *s, sflow5_mib_sFlowCpEntry_t *sFlowCpEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sFlowCpEntry_oid, sizeof(sFlowCpEntry_oid));
    len = pack_sFlowCpEntry(base, sFlowCpEntry->sFlowCpDataSource, sFlowCpEntry->_sFlowCpDataSourceLength, sFlowCpEntry->sFlowCpInstance);
    if (len < 0) {
        g_warning("%s: invalid index values", "sFlowCpEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 11, sFlowCpEntry_attr, mask, sFlowCpEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
sflow5_mib_free_sFlowCpEntry(sflow5_mib_sFlowCpEntry_t *sFlowCpEntry)
{
    GList *vbl;
    char *p;

    if (sFlowCpEntry) {
        p = (char *) sFlowCpEntry + sizeof(sflow5_mib_sFlowCpEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(sFlowCpEntry);
    }
}

void
sflow5_mib_free_sFlowCpTable(sflow5_mib_sFlowCpEntry_t **sFlowCpEntry)
{
    int i;

    if (sFlowCpEntry) {
        for (i = 0; sFlowCpEntry[i]; i++) {
            sflow5_mib_free_sFlowCpEntry(sFlowCpEntry[i]);
        }
        g_free(sFlowCpEntry);
    }
}

