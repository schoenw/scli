/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3-pre1:
 *   smidump -f scli \
 *     --scli-include='ipRouteEntry' RFC1213-MIB
 *
 * Derived from RFC1213-MIB:
 *
 * $Id$
 */

#include "rfc1213-mib.h"

GNetSnmpEnum const rfc1213_mib_enums_ipRouteType[] = {
    { RFC1213_MIB_IPROUTETYPE_OTHER,    "other" },
    { RFC1213_MIB_IPROUTETYPE_INVALID,  "invalid" },
    { RFC1213_MIB_IPROUTETYPE_DIRECT,   "direct" },
    { RFC1213_MIB_IPROUTETYPE_INDIRECT, "indirect" },
    { 0, NULL }
};

GNetSnmpEnum const rfc1213_mib_enums_ipRouteProto[] = {
    { RFC1213_MIB_IPROUTEPROTO_OTHER,     "other" },
    { RFC1213_MIB_IPROUTEPROTO_LOCAL,     "local" },
    { RFC1213_MIB_IPROUTEPROTO_NETMGMT,   "netmgmt" },
    { RFC1213_MIB_IPROUTEPROTO_ICMP,      "icmp" },
    { RFC1213_MIB_IPROUTEPROTO_EGP,       "egp" },
    { RFC1213_MIB_IPROUTEPROTO_GGP,       "ggp" },
    { RFC1213_MIB_IPROUTEPROTO_HELLO,     "hello" },
    { RFC1213_MIB_IPROUTEPROTO_RIP,       "rip" },
    { RFC1213_MIB_IPROUTEPROTO_IS_IS,     "is-is" },
    { RFC1213_MIB_IPROUTEPROTO_ES_IS,     "es-is" },
    { RFC1213_MIB_IPROUTEPROTO_CISCOIGRP, "ciscoIgrp" },
    { RFC1213_MIB_IPROUTEPROTO_BBNSPFIGP, "bbnSpfIgp" },
    { RFC1213_MIB_IPROUTEPROTO_OSPF,      "ospf" },
    { RFC1213_MIB_IPROUTEPROTO_BGP,       "bgp" },
    { 0, NULL }
};


static guint16 ipRouteNextHop_constraints[] = {4U, 4U, 0, 0};
static guint16 ipRouteMask_constraints[] = {4U, 4U, 0, 0};


static guint32 const ipRouteEntry_oid[] = {1, 3, 6, 1, 2, 1, 4, 21, 1};

static GNetSnmpAttribute ipRouteEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEIFINDEX, "ipRouteIfIndex",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteIfIndex),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC1, "ipRouteMetric1",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric1),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC2, "ipRouteMetric2",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric2),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC3, "ipRouteMetric3",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric3),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC4, "ipRouteMetric4",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric4),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      RFC1213_MIB_IPROUTENEXTHOP, "ipRouteNextHop",
       ipRouteNextHop_constraints,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteNextHop),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTETYPE, "ipRouteType",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEPROTO, "ipRouteProto",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteProto),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEAGE, "ipRouteAge",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteAge),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 11, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      RFC1213_MIB_IPROUTEMASK, "ipRouteMask",
       ipRouteMask_constraints,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMask),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC5, "ipRouteMetric5",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric5),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 13, GNET_SNMP_VARBIND_TYPE_OBJECTID,
      RFC1213_MIB_IPROUTEINFO, "ipRouteInfo",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteInfo),
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, _ipRouteInfoLength),
      0 },
    { 0, 0, 0, NULL }
};


rfc1213_mib_ipRouteEntry_t *
rfc1213_mib_new_ipRouteEntry()
{
    rfc1213_mib_ipRouteEntry_t *ipRouteEntry;

    ipRouteEntry = (rfc1213_mib_ipRouteEntry_t *) g_malloc0(sizeof(rfc1213_mib_ipRouteEntry_t) + sizeof(gpointer));
    return ipRouteEntry;
}

static inline int
unpack_ipRouteEntry(GNetSnmpVarBind *vb, rfc1213_mib_ipRouteEntry_t *ipRouteEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipRouteEntry->ipRouteDest[i] = vb->oid[idx++];
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ipRouteEntry(guint32 *base, guchar *ipRouteDest)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ipRouteDest[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline rfc1213_mib_ipRouteEntry_t *
assign_ipRouteEntry(GList *vbl)
{
    rfc1213_mib_ipRouteEntry_t *ipRouteEntry;
    char *p;

    ipRouteEntry = rfc1213_mib_new_ipRouteEntry();
    p = (char *) ipRouteEntry + sizeof(rfc1213_mib_ipRouteEntry_t);
    * (GList **) p = vbl;

    if (unpack_ipRouteEntry((GNetSnmpVarBind *) vbl->data, ipRouteEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ipRouteEntry");
        g_free(ipRouteEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ipRouteEntry_oid, G_N_ELEMENTS(ipRouteEntry_oid),
                      ipRouteEntry_attr, ipRouteEntry);

    return ipRouteEntry;
}

void
rfc1213_mib_get_ipRouteTable(GNetSnmp *s, rfc1213_mib_ipRouteEntry_t ***ipRouteEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 21, 1, 0};

    *ipRouteEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 10, 9, ipRouteEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ipRouteEntry = (rfc1213_mib_ipRouteEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rfc1213_mib_ipRouteEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ipRouteEntry)[i] = assign_ipRouteEntry(row->data);
        }
    }
}

void
rfc1213_mib_get_ipRouteEntry(GNetSnmp *s, rfc1213_mib_ipRouteEntry_t **ipRouteEntry, guchar *ipRouteDest, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ipRouteEntry_oid, sizeof(ipRouteEntry_oid));
    len = pack_ipRouteEntry(base, ipRouteDest);
    if (len < 0) {
        g_warning("%s: invalid index values", "ipRouteEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *ipRouteEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, ipRouteEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *ipRouteEntry = assign_ipRouteEntry(out);
    }
}

void
rfc1213_mib_set_ipRouteEntry(GNetSnmp *s, rfc1213_mib_ipRouteEntry_t *ipRouteEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ipRouteEntry_oid, sizeof(ipRouteEntry_oid));
    len = pack_ipRouteEntry(base, ipRouteEntry->ipRouteDest);
    if (len < 0) {
        g_warning("%s: invalid index values", "ipRouteEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 9, ipRouteEntry_attr, mask, ipRouteEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
rfc1213_mib_free_ipRouteEntry(rfc1213_mib_ipRouteEntry_t *ipRouteEntry)
{
    GList *vbl;
    char *p;

    if (ipRouteEntry) {
        p = (char *) ipRouteEntry + sizeof(rfc1213_mib_ipRouteEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(ipRouteEntry);
    }
}

void
rfc1213_mib_free_ipRouteTable(rfc1213_mib_ipRouteEntry_t **ipRouteEntry)
{
    int i;

    if (ipRouteEntry) {
        for (i = 0; ipRouteEntry[i]; i++) {
            rfc1213_mib_free_ipRouteEntry(ipRouteEntry[i]);
        }
        g_free(ipRouteEntry);
    }
}


