/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from IP-FORWARD-MIB revision 1996-09-19 00:00.
 *
 * $Id$
 */

#include "ip-forward-mib.h"

stls_table_t ip_forward_mib_enums_ipForwardType[] = {
    { 1, "other" },
    { 2, "invalid" },
    { 3, "local" },
    { 4, "remote" },
    { 0, NULL }
};

stls_table_t ip_forward_mib_enums_ipForwardProto[] = {
    { 1, "other" },
    { 2, "local" },
    { 3, "netmgmt" },
    { 4, "icmp" },
    { 5, "egp" },
    { 6, "ggp" },
    { 7, "hello" },
    { 8, "rip" },
    { 9, "is-is" },
    { 10, "es-is" },
    { 11, "ciscoIgrp" },
    { 12, "bbnSpfIgp" },
    { 13, "ospf" },
    { 14, "bgp" },
    { 15, "idpr" },
    { 0, NULL }
};

stls_table_t ip_forward_mib_enums_ipCidrRouteType[] = {
    { 1, "other" },
    { 2, "reject" },
    { 3, "local" },
    { 4, "remote" },
    { 0, NULL }
};

stls_table_t ip_forward_mib_enums_ipCidrRouteProto[] = {
    { 1, "other" },
    { 2, "local" },
    { 3, "netmgmt" },
    { 4, "icmp" },
    { 5, "egp" },
    { 6, "ggp" },
    { 7, "hello" },
    { 8, "rip" },
    { 9, "isIs" },
    { 10, "esIs" },
    { 11, "ciscoIgrp" },
    { 12, "bbnSpfIgp" },
    { 13, "ospf" },
    { 14, "bgp" },
    { 15, "idpr" },
    { 16, "ciscoEigrp" },
    { 0, NULL }
};

stls_table_t ip_forward_mib_enums_ipCidrRouteStatus[] = {
    { 1, "active" },
    { 2, "notInService" },
    { 3, "notReady" },
    { 4, "createAndGo" },
    { 5, "createAndWait" },
    { 6, "destroy" },
    { 0, NULL }
};


ipForward_t *
ip_forward_mib_new_ipForward()
{
    ipForward_t *ipForward;

    ipForward = (ipForward_t *) g_malloc0(sizeof(ipForward_t) + sizeof(gpointer));
    return ipForward;
}

static ipForward_t *
assign_ipForward(GSList *vbl)
{
    GSList *elem;
    ipForward_t *ipForward;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 4, 24};

    ipForward = ip_forward_mib_new_ipForward();
    if (! ipForward) {
        return NULL;
    }

    p = (char *) ipForward + sizeof(ipForward_t);
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
        if (vb->id_len > 9 && vb->id[8] == 1) {
            ipForward->ipForwardNumber = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 9 && vb->id[8] == 3) {
            ipForward->ipCidrRouteNumber = &(vb->syntax.ui32[0]);
        }
    }

    return ipForward;
}

int
ip_forward_mib_get_ipForward(host_snmp *s, ipForward_t **ipForward)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 24, 0};

    *ipForward = NULL;

    base[8] = 1; stls_vbl_add_null(&in, base, 9);
    base[8] = 3; stls_vbl_add_null(&in, base, 9);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *ipForward = assign_ipForward(out);

    return 0;
}

void
ip_forward_mib_free_ipForward(ipForward_t *ipForward)
{
    GSList *vbl;
    char *p;

    if (ipForward) {
        p = (char *) ipForward + sizeof(ipForward_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(ipForward);
    }
}

ipForwardEntry_t *
ip_forward_mib_new_ipForwardEntry()
{
    ipForwardEntry_t *ipForwardEntry;

    ipForwardEntry = (ipForwardEntry_t *) g_malloc0(sizeof(ipForwardEntry_t) + sizeof(gpointer));
    return ipForwardEntry;
}

static int
unpack_ipForwardEntry(GSnmpVarBind *vb, ipForwardEntry_t *ipForwardEntry)
{
    int i, len, idx = 11;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipForwardEntry->ipForwardDest[i] = vb->id[idx++];
    }
    if (vb->id_len < idx) return -1;
    ipForwardEntry->ipForwardProto = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    ipForwardEntry->ipForwardPolicy = vb->id[idx++];
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipForwardEntry->ipForwardNextHop[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static ipForwardEntry_t *
assign_ipForwardEntry(GSList *vbl)
{
    GSList *elem;
    ipForwardEntry_t *ipForwardEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 4, 24, 2, 1};

    ipForwardEntry = ip_forward_mib_new_ipForwardEntry();
    if (! ipForwardEntry) {
        return NULL;
    }

    p = (char *) ipForwardEntry + sizeof(ipForwardEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ipForwardEntry((GSnmpVarBind *) vbl->data, ipForwardEntry) < 0) {
        g_warning("illegal ipForwardEntry instance identifier");
        g_free(ipForwardEntry);
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
        if (vb->id_len > 11 && vb->id[10] == 2) {
            ipForwardEntry->ipForwardMask = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            ipForwardEntry->ipForwardIfIndex = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            ipForwardEntry->ipForwardType = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 8) {
            ipForwardEntry->ipForwardAge = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 9) {
            ipForwardEntry->_ipForwardInfoLength = vb->syntax_len / sizeof(guint32);
            ipForwardEntry->ipForwardInfo = vb->syntax.ui32;
        }
        if (vb->id_len > 11 && vb->id[10] == 10) {
            ipForwardEntry->ipForwardNextHopAS = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 11) {
            ipForwardEntry->ipForwardMetric1 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 12) {
            ipForwardEntry->ipForwardMetric2 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 13) {
            ipForwardEntry->ipForwardMetric3 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 14) {
            ipForwardEntry->ipForwardMetric4 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 15) {
            ipForwardEntry->ipForwardMetric5 = &(vb->syntax.i32[0]);
        }
    }

    return ipForwardEntry;
}

int
ip_forward_mib_get_ipForwardTable(host_snmp *s, ipForwardEntry_t ***ipForwardEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 24, 2, 1, 0};

    *ipForwardEntry = NULL;

    base[10] = 2; stls_vbl_add_null(&in, base, 11);
    base[10] = 5; stls_vbl_add_null(&in, base, 11);
    base[10] = 6; stls_vbl_add_null(&in, base, 11);
    base[10] = 8; stls_vbl_add_null(&in, base, 11);
    base[10] = 9; stls_vbl_add_null(&in, base, 11);
    base[10] = 10; stls_vbl_add_null(&in, base, 11);
    base[10] = 11; stls_vbl_add_null(&in, base, 11);
    base[10] = 12; stls_vbl_add_null(&in, base, 11);
    base[10] = 13; stls_vbl_add_null(&in, base, 11);
    base[10] = 14; stls_vbl_add_null(&in, base, 11);
    base[10] = 15; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *ipForwardEntry = (ipForwardEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(ipForwardEntry_t *));
    if (! *ipForwardEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*ipForwardEntry)[i] = assign_ipForwardEntry(row->data);
    }

    return 0;
}

void
ip_forward_mib_free_ipForwardEntry(ipForwardEntry_t *ipForwardEntry)
{
    GSList *vbl;
    char *p;

    if (ipForwardEntry) {
        p = (char *) ipForwardEntry + sizeof(ipForwardEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(ipForwardEntry);
    }
}

void
ip_forward_mib_free_ipForwardTable(ipForwardEntry_t **ipForwardEntry)
{
    int i;

    if (ipForwardEntry) {
        for (i = 0; ipForwardEntry[i]; i++) {
            ip_forward_mib_free_ipForwardEntry(ipForwardEntry[i]);
        }
        g_free(ipForwardEntry);
    }
}

ipCidrRouteEntry_t *
ip_forward_mib_new_ipCidrRouteEntry()
{
    ipCidrRouteEntry_t *ipCidrRouteEntry;

    ipCidrRouteEntry = (ipCidrRouteEntry_t *) g_malloc0(sizeof(ipCidrRouteEntry_t) + sizeof(gpointer));
    return ipCidrRouteEntry;
}

static int
unpack_ipCidrRouteEntry(GSnmpVarBind *vb, ipCidrRouteEntry_t *ipCidrRouteEntry)
{
    int i, len, idx = 11;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipCidrRouteEntry->ipCidrRouteDest[i] = vb->id[idx++];
    }
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipCidrRouteEntry->ipCidrRouteMask[i] = vb->id[idx++];
    }
    if (vb->id_len < idx) return -1;
    ipCidrRouteEntry->ipCidrRouteTos = vb->id[idx++];
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipCidrRouteEntry->ipCidrRouteNextHop[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static ipCidrRouteEntry_t *
assign_ipCidrRouteEntry(GSList *vbl)
{
    GSList *elem;
    ipCidrRouteEntry_t *ipCidrRouteEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 4, 24, 4, 1};

    ipCidrRouteEntry = ip_forward_mib_new_ipCidrRouteEntry();
    if (! ipCidrRouteEntry) {
        return NULL;
    }

    p = (char *) ipCidrRouteEntry + sizeof(ipCidrRouteEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ipCidrRouteEntry((GSnmpVarBind *) vbl->data, ipCidrRouteEntry) < 0) {
        g_warning("illegal ipCidrRouteEntry instance identifier");
        g_free(ipCidrRouteEntry);
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
        if (vb->id_len > 11 && vb->id[10] == 5) {
            ipCidrRouteEntry->ipCidrRouteIfIndex = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            ipCidrRouteEntry->ipCidrRouteType = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 7) {
            ipCidrRouteEntry->ipCidrRouteProto = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 8) {
            ipCidrRouteEntry->ipCidrRouteAge = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 9) {
            ipCidrRouteEntry->_ipCidrRouteInfoLength = vb->syntax_len / sizeof(guint32);
            ipCidrRouteEntry->ipCidrRouteInfo = vb->syntax.ui32;
        }
        if (vb->id_len > 11 && vb->id[10] == 10) {
            ipCidrRouteEntry->ipCidrRouteNextHopAS = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 11) {
            ipCidrRouteEntry->ipCidrRouteMetric1 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 12) {
            ipCidrRouteEntry->ipCidrRouteMetric2 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 13) {
            ipCidrRouteEntry->ipCidrRouteMetric3 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 14) {
            ipCidrRouteEntry->ipCidrRouteMetric4 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 15) {
            ipCidrRouteEntry->ipCidrRouteMetric5 = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 16) {
            ipCidrRouteEntry->ipCidrRouteStatus = &(vb->syntax.i32[0]);
        }
    }

    return ipCidrRouteEntry;
}

int
ip_forward_mib_get_ipCidrRouteTable(host_snmp *s, ipCidrRouteEntry_t ***ipCidrRouteEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 24, 4, 1, 0};

    *ipCidrRouteEntry = NULL;

    base[10] = 5; stls_vbl_add_null(&in, base, 11);
    base[10] = 6; stls_vbl_add_null(&in, base, 11);
    base[10] = 7; stls_vbl_add_null(&in, base, 11);
    base[10] = 8; stls_vbl_add_null(&in, base, 11);
    base[10] = 9; stls_vbl_add_null(&in, base, 11);
    base[10] = 10; stls_vbl_add_null(&in, base, 11);
    base[10] = 11; stls_vbl_add_null(&in, base, 11);
    base[10] = 12; stls_vbl_add_null(&in, base, 11);
    base[10] = 13; stls_vbl_add_null(&in, base, 11);
    base[10] = 14; stls_vbl_add_null(&in, base, 11);
    base[10] = 15; stls_vbl_add_null(&in, base, 11);
    base[10] = 16; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *ipCidrRouteEntry = (ipCidrRouteEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(ipCidrRouteEntry_t *));
    if (! *ipCidrRouteEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*ipCidrRouteEntry)[i] = assign_ipCidrRouteEntry(row->data);
    }

    return 0;
}

void
ip_forward_mib_free_ipCidrRouteEntry(ipCidrRouteEntry_t *ipCidrRouteEntry)
{
    GSList *vbl;
    char *p;

    if (ipCidrRouteEntry) {
        p = (char *) ipCidrRouteEntry + sizeof(ipCidrRouteEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(ipCidrRouteEntry);
    }
}

void
ip_forward_mib_free_ipCidrRouteTable(ipCidrRouteEntry_t **ipCidrRouteEntry)
{
    int i;

    if (ipCidrRouteEntry) {
        for (i = 0; ipCidrRouteEntry[i]; i++) {
            ip_forward_mib_free_ipCidrRouteEntry(ipCidrRouteEntry[i]);
        }
        g_free(ipCidrRouteEntry);
    }
}


