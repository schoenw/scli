/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from RFC1213-MIB:
 *
 * $Id$
 */

#include "rfc1213-mib.h"

GSnmpEnum const rfc1213_mib_enums_ipRouteType[] = {
    { RFC1213_MIB_IPROUTETYPE_OTHER,    "other" },
    { RFC1213_MIB_IPROUTETYPE_INVALID,  "invalid" },
    { RFC1213_MIB_IPROUTETYPE_DIRECT,   "direct" },
    { RFC1213_MIB_IPROUTETYPE_INDIRECT, "indirect" },
    { 0, NULL }
};

GSnmpEnum const rfc1213_mib_enums_ipRouteProto[] = {
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


static guint16 ipRouteNextHop_constraints[] = {4, 4, 0, 0};
static guint16 ipRouteMask_constraints[] = {4, 4, 0, 0};


static guint32 const ipRouteEntry_oid[] = {1, 3, 6, 1, 2, 1, 4, 21, 1};

static GSnmpAttribute ipRouteEntry_attr[] = {
    { 2, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEIFINDEX, "ipRouteIfIndex",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteIfIndex),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC1, "ipRouteMetric1",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric1),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC2, "ipRouteMetric2",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric2),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC3, "ipRouteMetric3",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric3),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC4, "ipRouteMetric4",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric4),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, G_SNMP_IPADDRESS,
      RFC1213_MIB_IPROUTENEXTHOP, "ipRouteNextHop",
       ipRouteNextHop_constraints,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteNextHop),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTETYPE, "ipRouteType",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEPROTO, "ipRouteProto",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteProto),
      0,
      0 },
    { 10, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEAGE, "ipRouteAge",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteAge),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 11, G_SNMP_IPADDRESS,
      RFC1213_MIB_IPROUTEMASK, "ipRouteMask",
       ipRouteMask_constraints,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMask),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, G_SNMP_INTEGER32,
      RFC1213_MIB_IPROUTEMETRIC5, "ipRouteMetric5",
       NULL,
      G_STRUCT_OFFSET(rfc1213_mib_ipRouteEntry_t, ipRouteMetric5),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 13, G_SNMP_OBJECTID,
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

static int
unpack_ipRouteEntry(GSnmpVarBind *vb, rfc1213_mib_ipRouteEntry_t *ipRouteEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    if (len != 4) return -1;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipRouteEntry->ipRouteDest[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
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

static rfc1213_mib_ipRouteEntry_t *
assign_ipRouteEntry(GSList *vbl)
{
    rfc1213_mib_ipRouteEntry_t *ipRouteEntry;
    char *p;

    ipRouteEntry = rfc1213_mib_new_ipRouteEntry();
    if (! ipRouteEntry) {
        return NULL;
    }

    p = (char *) ipRouteEntry + sizeof(rfc1213_mib_ipRouteEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ipRouteEntry((GSnmpVarBind *) vbl->data, ipRouteEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ipRouteEntry");
        g_free(ipRouteEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, ipRouteEntry_oid, sizeof(ipRouteEntry_oid)/sizeof(guint32),
                      ipRouteEntry_attr, ipRouteEntry);

    return ipRouteEntry;
}

void
rfc1213_mib_get_ipRouteTable(GSnmpSession *s, rfc1213_mib_ipRouteEntry_t ***ipRouteEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 21, 1, 0};

    *ipRouteEntry = NULL;

    gsnmp_attr_get(s, &in, base, 10, 9, ipRouteEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *ipRouteEntry = (rfc1213_mib_ipRouteEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(rfc1213_mib_ipRouteEntry_t *));
        if (! *ipRouteEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*ipRouteEntry)[i] = assign_ipRouteEntry(row->data);
        }
    }
}

void
rfc1213_mib_get_ipRouteEntry(GSnmpSession *s, rfc1213_mib_ipRouteEntry_t **ipRouteEntry, guchar *ipRouteDest, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, ipRouteEntry_oid, sizeof(ipRouteEntry_oid));
    len = pack_ipRouteEntry(base, ipRouteDest);
    if (len < 0) {
        g_warning("%s: invalid index values", "ipRouteEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *ipRouteEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 9, ipRouteEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *ipRouteEntry = assign_ipRouteEntry(out);
    }
}

void
rfc1213_mib_set_ipRouteEntry(GSnmpSession *s, rfc1213_mib_ipRouteEntry_t *ipRouteEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, ipRouteEntry_oid, sizeof(ipRouteEntry_oid));
    len = pack_ipRouteEntry(base, ipRouteEntry->ipRouteDest);
    if (len < 0) {
        g_warning("%s: invalid index values", "ipRouteEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 9, ipRouteEntry_attr, mask, ipRouteEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
rfc1213_mib_free_ipRouteEntry(rfc1213_mib_ipRouteEntry_t *ipRouteEntry)
{
    GSList *vbl;
    char *p;

    if (ipRouteEntry) {
        p = (char *) ipRouteEntry + sizeof(rfc1213_mib_ipRouteEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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


