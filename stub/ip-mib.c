/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli \
 *     --scli-exclude='icmp' IP-MIB
 *
 * Derived from IP-MIB:
 *   The MIB module for managing IP and ICMP implementations,
 *   but excluding their management of IP routes.
 *
 * Revision 1994-11-01 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 1991-03-31 00:00:
 *   The initial revision of this MIB module was part of MIB-
 *   II.
 *
 * $Id$
 */

#include "ip-mib.h"

GNetSnmpEnum const ip_mib_enums_ipForwarding[] = {
    { IP_MIB_IPFORWARDING_FORWARDING,    "forwarding" },
    { IP_MIB_IPFORWARDING_NOTFORWARDING, "notForwarding" },
    { 0, NULL }
};

GNetSnmpEnum const ip_mib_enums_ipNetToMediaType[] = {
    { IP_MIB_IPNETTOMEDIATYPE_OTHER,   "other" },
    { IP_MIB_IPNETTOMEDIATYPE_INVALID, "invalid" },
    { IP_MIB_IPNETTOMEDIATYPE_DYNAMIC, "dynamic" },
    { IP_MIB_IPNETTOMEDIATYPE_STATIC,  "static" },
    { 0, NULL }
};


static gint32 ipDefaultTTL_constraints[] = {1L, 255L, 0, 0};
static gint32 ipAdEntIfIndex_constraints[] = {1L, 2147483647L, 0, 0};
static guint16 ipAdEntNetMask_constraints[] = {4U, 4U, 0, 0};
static gint32 ipAdEntBcastAddr_constraints[] = {0L, 1L, 0, 0};
static gint32 ipAdEntReasmMaxSize_constraints[] = {0L, 65535L, 0, 0};


static guint32 const ip_oid[] = {1, 3, 6, 1, 2, 1, 4};

static GNetSnmpAttribute ip_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IP_MIB_IPFORWARDING, "ipForwarding",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipForwarding),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IP_MIB_IPDEFAULTTTL, "ipDefaultTTL",
       ipDefaultTTL_constraints,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipDefaultTTL),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPINRECEIVES, "ipInReceives",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipInReceives),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPINHDRERRORS, "ipInHdrErrors",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipInHdrErrors),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPINADDRERRORS, "ipInAddrErrors",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipInAddrErrors),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPFORWDATAGRAMS, "ipForwDatagrams",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipForwDatagrams),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPINUNKNOWNPROTOS, "ipInUnknownProtos",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipInUnknownProtos),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPINDISCARDS, "ipInDiscards",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipInDiscards),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPINDELIVERS, "ipInDelivers",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipInDelivers),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPOUTREQUESTS, "ipOutRequests",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipOutRequests),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPOUTDISCARDS, "ipOutDiscards",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipOutDiscards),
      0,
      0 },
    { 12, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPOUTNOROUTES, "ipOutNoRoutes",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipOutNoRoutes),
      0,
      0 },
    { 13, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IP_MIB_IPREASMTIMEOUT, "ipReasmTimeout",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipReasmTimeout),
      0,
      0 },
    { 14, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPREASMREQDS, "ipReasmReqds",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipReasmReqds),
      0,
      0 },
    { 15, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPREASMOKS, "ipReasmOKs",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipReasmOKs),
      0,
      0 },
    { 16, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPREASMFAILS, "ipReasmFails",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipReasmFails),
      0,
      0 },
    { 17, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPFRAGOKS, "ipFragOKs",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipFragOKs),
      0,
      0 },
    { 18, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPFRAGFAILS, "ipFragFails",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipFragFails),
      0,
      0 },
    { 19, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPFRAGCREATES, "ipFragCreates",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipFragCreates),
      0,
      0 },
    { 23, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IP_MIB_IPROUTINGDISCARDS, "ipRoutingDiscards",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ip_t, ipRoutingDiscards),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const ipAddrEntry_oid[] = {1, 3, 6, 1, 2, 1, 4, 20, 1};

static GNetSnmpAttribute ipAddrEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IP_MIB_IPADENTIFINDEX, "ipAdEntIfIndex",
       ipAdEntIfIndex_constraints,
      G_STRUCT_OFFSET(ip_mib_ipAddrEntry_t, ipAdEntIfIndex),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      IP_MIB_IPADENTNETMASK, "ipAdEntNetMask",
       ipAdEntNetMask_constraints,
      G_STRUCT_OFFSET(ip_mib_ipAddrEntry_t, ipAdEntNetMask),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IP_MIB_IPADENTBCASTADDR, "ipAdEntBcastAddr",
       ipAdEntBcastAddr_constraints,
      G_STRUCT_OFFSET(ip_mib_ipAddrEntry_t, ipAdEntBcastAddr),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IP_MIB_IPADENTREASMMAXSIZE, "ipAdEntReasmMaxSize",
       ipAdEntReasmMaxSize_constraints,
      G_STRUCT_OFFSET(ip_mib_ipAddrEntry_t, ipAdEntReasmMaxSize),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const ipNetToMediaEntry_oid[] = {1, 3, 6, 1, 2, 1, 4, 22, 1};

static GNetSnmpAttribute ipNetToMediaEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      IP_MIB_IPNETTOMEDIAPHYSADDRESS, "ipNetToMediaPhysAddress",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ipNetToMediaEntry_t, ipNetToMediaPhysAddress),
      G_STRUCT_OFFSET(ip_mib_ipNetToMediaEntry_t, _ipNetToMediaPhysAddressLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IP_MIB_IPNETTOMEDIATYPE, "ipNetToMediaType",
       NULL,
      G_STRUCT_OFFSET(ip_mib_ipNetToMediaEntry_t, ipNetToMediaType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


ip_mib_ip_t *
ip_mib_new_ip()
{
    ip_mib_ip_t *ip;

    ip = (ip_mib_ip_t *) g_malloc0(sizeof(ip_mib_ip_t) + sizeof(gpointer));
    return ip;
}

static inline ip_mib_ip_t *
assign_ip(GList *vbl)
{
    ip_mib_ip_t *ip;
    char *p;

    ip = ip_mib_new_ip();
    p = (char *) ip + sizeof(ip_mib_ip_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, ip_oid, G_N_ELEMENTS(ip_oid),
                      ip_attr, ip);

    return ip;
}

void
ip_mib_get_ip(GNetSnmp *s, ip_mib_ip_t **ip, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 0};

    *ip = NULL;

    gnet_snmp_attr_get(s, &in, base, 8, 7, ip_attr, mask);

    out = gnet_snmp_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ip = assign_ip(out);
    }
}

void
ip_mib_set_ip(GNetSnmp *s, ip_mib_ip_t *ip, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 0, 0};

    gnet_snmp_attr_set(s, &in, base, 9, 7, ip_attr, mask, ip);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
ip_mib_free_ip(ip_mib_ip_t *ip)
{
    GList *vbl;
    char *p;

    if (ip) {
        p = (char *) ip + sizeof(ip_mib_ip_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ip);
    }
}

ip_mib_ipAddrEntry_t *
ip_mib_new_ipAddrEntry()
{
    ip_mib_ipAddrEntry_t *ipAddrEntry;

    ipAddrEntry = (ip_mib_ipAddrEntry_t *) g_malloc0(sizeof(ip_mib_ipAddrEntry_t) + sizeof(gpointer));
    return ipAddrEntry;
}

static inline int
unpack_ipAddrEntry(GNetSnmpVarBind *vb, ip_mib_ipAddrEntry_t *ipAddrEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipAddrEntry->ipAdEntAddr[i] = vb->oid[idx++];
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ipAddrEntry(guint32 *base, guchar *ipAdEntAddr)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ipAdEntAddr[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline ip_mib_ipAddrEntry_t *
assign_ipAddrEntry(GList *vbl)
{
    ip_mib_ipAddrEntry_t *ipAddrEntry;
    char *p;

    ipAddrEntry = ip_mib_new_ipAddrEntry();
    p = (char *) ipAddrEntry + sizeof(ip_mib_ipAddrEntry_t);
    * (GList **) p = vbl;

    if (unpack_ipAddrEntry((GNetSnmpVarBind *) vbl->data, ipAddrEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ipAddrEntry");
        g_free(ipAddrEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ipAddrEntry_oid, G_N_ELEMENTS(ipAddrEntry_oid),
                      ipAddrEntry_attr, ipAddrEntry);

    return ipAddrEntry;
}

void
ip_mib_get_ipAddrTable(GNetSnmp *s, ip_mib_ipAddrEntry_t ***ipAddrEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 20, 1, 0};

    *ipAddrEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 10, 9, ipAddrEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ipAddrEntry = (ip_mib_ipAddrEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(ip_mib_ipAddrEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ipAddrEntry)[i] = assign_ipAddrEntry(row->data);
        }
    }
}

void
ip_mib_get_ipAddrEntry(GNetSnmp *s, ip_mib_ipAddrEntry_t **ipAddrEntry, guchar *ipAdEntAddr, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ipAddrEntry_oid, sizeof(ipAddrEntry_oid));
    len = pack_ipAddrEntry(base, ipAdEntAddr);
    if (len < 0) {
        g_warning("%s: invalid index values", "ipAddrEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ipAddrEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, ipAddrEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ipAddrEntry = assign_ipAddrEntry(out);
    }
}

void
ip_mib_free_ipAddrEntry(ip_mib_ipAddrEntry_t *ipAddrEntry)
{
    GList *vbl;
    char *p;

    if (ipAddrEntry) {
        p = (char *) ipAddrEntry + sizeof(ip_mib_ipAddrEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ipAddrEntry);
    }
}

void
ip_mib_free_ipAddrTable(ip_mib_ipAddrEntry_t **ipAddrEntry)
{
    int i;

    if (ipAddrEntry) {
        for (i = 0; ipAddrEntry[i]; i++) {
            ip_mib_free_ipAddrEntry(ipAddrEntry[i]);
        }
        g_free(ipAddrEntry);
    }
}

ip_mib_ipNetToMediaEntry_t *
ip_mib_new_ipNetToMediaEntry()
{
    ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry;

    ipNetToMediaEntry = (ip_mib_ipNetToMediaEntry_t *) g_malloc0(sizeof(ip_mib_ipNetToMediaEntry_t) + sizeof(gpointer));
    return ipNetToMediaEntry;
}

static inline int
unpack_ipNetToMediaEntry(GNetSnmpVarBind *vb, ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    ipNetToMediaEntry->ipNetToMediaIfIndex = vb->oid[idx++];
    if ((ipNetToMediaEntry->ipNetToMediaIfIndex < 1)) {
         return -1;
    }
    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipNetToMediaEntry->ipNetToMediaNetAddress[i] = vb->oid[idx++];
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ipNetToMediaEntry(guint32 *base, gint32 ipNetToMediaIfIndex, guchar *ipNetToMediaNetAddress)
{
    guint8 idx = 10;
    guint16 i, len;

    base[idx++] = ipNetToMediaIfIndex;
    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ipNetToMediaNetAddress[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline ip_mib_ipNetToMediaEntry_t *
assign_ipNetToMediaEntry(GList *vbl)
{
    ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry;
    char *p;

    ipNetToMediaEntry = ip_mib_new_ipNetToMediaEntry();
    p = (char *) ipNetToMediaEntry + sizeof(ip_mib_ipNetToMediaEntry_t);
    * (GList **) p = vbl;

    if (unpack_ipNetToMediaEntry((GNetSnmpVarBind *) vbl->data, ipNetToMediaEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ipNetToMediaEntry");
        g_free(ipNetToMediaEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ipNetToMediaEntry_oid, G_N_ELEMENTS(ipNetToMediaEntry_oid),
                      ipNetToMediaEntry_attr, ipNetToMediaEntry);

    return ipNetToMediaEntry;
}

void
ip_mib_get_ipNetToMediaTable(GNetSnmp *s, ip_mib_ipNetToMediaEntry_t ***ipNetToMediaEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 22, 1, 0};

    *ipNetToMediaEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 10, 9, ipNetToMediaEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ipNetToMediaEntry = (ip_mib_ipNetToMediaEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(ip_mib_ipNetToMediaEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ipNetToMediaEntry)[i] = assign_ipNetToMediaEntry(row->data);
        }
    }
}

void
ip_mib_get_ipNetToMediaEntry(GNetSnmp *s, ip_mib_ipNetToMediaEntry_t **ipNetToMediaEntry, gint32 ipNetToMediaIfIndex, guchar *ipNetToMediaNetAddress, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ipNetToMediaEntry_oid, sizeof(ipNetToMediaEntry_oid));
    len = pack_ipNetToMediaEntry(base, ipNetToMediaIfIndex, ipNetToMediaNetAddress);
    if (len < 0) {
        g_warning("%s: invalid index values", "ipNetToMediaEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ipNetToMediaEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, ipNetToMediaEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ipNetToMediaEntry = assign_ipNetToMediaEntry(out);
    }
}

void
ip_mib_set_ipNetToMediaEntry(GNetSnmp *s, ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ipNetToMediaEntry_oid, sizeof(ipNetToMediaEntry_oid));
    len = pack_ipNetToMediaEntry(base, ipNetToMediaEntry->ipNetToMediaIfIndex, ipNetToMediaEntry->ipNetToMediaNetAddress);
    if (len < 0) {
        g_warning("%s: invalid index values", "ipNetToMediaEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 9, ipNetToMediaEntry_attr, mask, ipNetToMediaEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
ip_mib_free_ipNetToMediaEntry(ip_mib_ipNetToMediaEntry_t *ipNetToMediaEntry)
{
    GList *vbl;
    char *p;

    if (ipNetToMediaEntry) {
        p = (char *) ipNetToMediaEntry + sizeof(ip_mib_ipNetToMediaEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ipNetToMediaEntry);
    }
}

void
ip_mib_free_ipNetToMediaTable(ip_mib_ipNetToMediaEntry_t **ipNetToMediaEntry)
{
    int i;

    if (ipNetToMediaEntry) {
        for (i = 0; ipNetToMediaEntry[i]; i++) {
            ip_mib_free_ipNetToMediaEntry(ipNetToMediaEntry[i]);
        }
        g_free(ipNetToMediaEntry);
    }
}


