/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from IP-MIB revision 1994-11-01 00:00.
 *
 * $Id$
 */

#include "ip-mib.h"

stls_table_t ip_mib_enums_ipForwarding[] = {
    { 1, "forwarding" },
    { 2, "notForwarding" },
    { 0, NULL }
};

stls_table_t ip_mib_enums_ipNetToMediaType[] = {
    { 1, "other" },
    { 2, "invalid" },
    { 3, "dynamic" },
    { 4, "static" },
    { 0, NULL }
};


static ip_t *
assign_ip(GSList *vbl)
{
    GSList *elem;
    ip_t *ip;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 4};

    ip = (ip_t *) g_malloc0(sizeof(ip_t) + sizeof(GSList *));
    if (! ip) {
        return NULL;
    }

    p = (char *) ip + sizeof(ip_t);
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
        if (vb->id_len > 8 && vb->id[7] == 1) {
            ip->ipForwarding = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 2) {
            ip->ipDefaultTTL = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 3) {
            ip->ipInReceives = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 4) {
            ip->ipInHdrErrors = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 5) {
            ip->ipInAddrErrors = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 6) {
            ip->ipForwDatagrams = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 7) {
            ip->ipInUnknownProtos = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 8) {
            ip->ipInDiscards = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 9) {
            ip->ipInDelivers = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 10) {
            ip->ipOutRequests = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 11) {
            ip->ipOutDiscards = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 12) {
            ip->ipOutNoRoutes = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 13) {
            ip->ipReasmTimeout = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 14) {
            ip->ipReasmReqds = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 15) {
            ip->ipReasmOKs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 16) {
            ip->ipReasmFails = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 17) {
            ip->ipFragOKs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 18) {
            ip->ipFragFails = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 19) {
            ip->ipFragCreates = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 23) {
            ip->ipRoutingDiscards = &(vb->syntax.ui32[0]);
        }
    }

    return ip;
}

int
ip_mib_get_ip(host_snmp *s, ip_t **ip)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 0};

    *ip = NULL;

    base[7] = 1; stls_vbl_add_null(&in, base, 8);
    base[7] = 2; stls_vbl_add_null(&in, base, 8);
    base[7] = 3; stls_vbl_add_null(&in, base, 8);
    base[7] = 4; stls_vbl_add_null(&in, base, 8);
    base[7] = 5; stls_vbl_add_null(&in, base, 8);
    base[7] = 6; stls_vbl_add_null(&in, base, 8);
    base[7] = 7; stls_vbl_add_null(&in, base, 8);
    base[7] = 8; stls_vbl_add_null(&in, base, 8);
    base[7] = 9; stls_vbl_add_null(&in, base, 8);
    base[7] = 10; stls_vbl_add_null(&in, base, 8);
    base[7] = 11; stls_vbl_add_null(&in, base, 8);
    base[7] = 12; stls_vbl_add_null(&in, base, 8);
    base[7] = 13; stls_vbl_add_null(&in, base, 8);
    base[7] = 14; stls_vbl_add_null(&in, base, 8);
    base[7] = 15; stls_vbl_add_null(&in, base, 8);
    base[7] = 16; stls_vbl_add_null(&in, base, 8);
    base[7] = 17; stls_vbl_add_null(&in, base, 8);
    base[7] = 18; stls_vbl_add_null(&in, base, 8);
    base[7] = 19; stls_vbl_add_null(&in, base, 8);
    base[7] = 23; stls_vbl_add_null(&in, base, 8);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *ip = assign_ip(out);

    return 0;
}

void
ip_mib_free_ip(ip_t *ip)
{
    GSList *vbl;
    char *p;

    if (ip) {
        p = (char *) ip + sizeof(ip_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(ip);
    }
}

static int
unpack_ipAddrEntry(GSnmpVarBind *vb, ipAddrEntry_t *ipAddrEntry)
{
    int i, len, idx = 10;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipAddrEntry->ipAdEntAddr[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static ipAddrEntry_t *
assign_ipAddrEntry(GSList *vbl)
{
    GSList *elem;
    ipAddrEntry_t *ipAddrEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 4, 20, 1};

    ipAddrEntry = (ipAddrEntry_t *) g_malloc0(sizeof(ipAddrEntry_t) + sizeof(GSList *));
    if (! ipAddrEntry) {
        return NULL;
    }

    p = (char *) ipAddrEntry + sizeof(ipAddrEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ipAddrEntry((GSnmpVarBind *) vbl->data, ipAddrEntry) < 0) {
        g_warning("illegal ipAddrEntry instance identifier");
        g_free(ipAddrEntry);
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
        if (vb->id_len > 10 && vb->id[9] == 2) {
            ipAddrEntry->ipAdEntIfIndex = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 3) {
            ipAddrEntry->ipAdEntNetMask = vb->syntax.uc;
        }
        if (vb->id_len > 10 && vb->id[9] == 4) {
            ipAddrEntry->ipAdEntBcastAddr = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 5) {
            ipAddrEntry->ipAdEntReasmMaxSize = &(vb->syntax.i32[0]);
        }
    }

    return ipAddrEntry;
}

int
ip_mib_get_ipAddrEntry(host_snmp *s, ipAddrEntry_t ***ipAddrEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 20, 1, 0};

    *ipAddrEntry = NULL;

    base[9] = 2; stls_vbl_add_null(&in, base, 10);
    base[9] = 3; stls_vbl_add_null(&in, base, 10);
    base[9] = 4; stls_vbl_add_null(&in, base, 10);
    base[9] = 5; stls_vbl_add_null(&in, base, 10);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *ipAddrEntry = (ipAddrEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(ipAddrEntry_t *));
    if (! *ipAddrEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*ipAddrEntry)[i] = assign_ipAddrEntry(row->data);
    }

    return 0;
}

void
ip_mib_free_ipAddrEntry(ipAddrEntry_t **ipAddrEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (ipAddrEntry) {
        for (i = 0; ipAddrEntry[i]; i++) {
            p = (char *) ipAddrEntry[i] + sizeof(ipAddrEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(ipAddrEntry[i]);
        }
        g_free(ipAddrEntry);
    }
}

static int
unpack_ipNetToMediaEntry(GSnmpVarBind *vb, ipNetToMediaEntry_t *ipNetToMediaEntry)
{
    int i, len, idx = 10;

    if (vb->id_len < idx) return -1;
    ipNetToMediaEntry->ipNetToMediaIfIndex = vb->id[idx++];
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ipNetToMediaEntry->ipNetToMediaNetAddress[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static ipNetToMediaEntry_t *
assign_ipNetToMediaEntry(GSList *vbl)
{
    GSList *elem;
    ipNetToMediaEntry_t *ipNetToMediaEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 4, 22, 1};

    ipNetToMediaEntry = (ipNetToMediaEntry_t *) g_malloc0(sizeof(ipNetToMediaEntry_t) + sizeof(GSList *));
    if (! ipNetToMediaEntry) {
        return NULL;
    }

    p = (char *) ipNetToMediaEntry + sizeof(ipNetToMediaEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ipNetToMediaEntry((GSnmpVarBind *) vbl->data, ipNetToMediaEntry) < 0) {
        g_warning("illegal ipNetToMediaEntry instance identifier");
        g_free(ipNetToMediaEntry);
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
        if (vb->id_len > 10 && vb->id[9] == 2) {
            ipNetToMediaEntry->_ipNetToMediaPhysAddressLength = vb->syntax_len;
            ipNetToMediaEntry->ipNetToMediaPhysAddress = vb->syntax.uc;
        }
        if (vb->id_len > 10 && vb->id[9] == 4) {
            ipNetToMediaEntry->ipNetToMediaType = &(vb->syntax.i32[0]);
        }
    }

    return ipNetToMediaEntry;
}

int
ip_mib_get_ipNetToMediaEntry(host_snmp *s, ipNetToMediaEntry_t ***ipNetToMediaEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 4, 22, 1, 0};

    *ipNetToMediaEntry = NULL;

    base[9] = 2; stls_vbl_add_null(&in, base, 10);
    base[9] = 4; stls_vbl_add_null(&in, base, 10);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *ipNetToMediaEntry = (ipNetToMediaEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(ipNetToMediaEntry_t *));
    if (! *ipNetToMediaEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*ipNetToMediaEntry)[i] = assign_ipNetToMediaEntry(row->data);
    }

    return 0;
}

void
ip_mib_free_ipNetToMediaEntry(ipNetToMediaEntry_t **ipNetToMediaEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (ipNetToMediaEntry) {
        for (i = 0; ipNetToMediaEntry[i]; i++) {
            p = (char *) ipNetToMediaEntry[i] + sizeof(ipNetToMediaEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(ipNetToMediaEntry[i]);
        }
        g_free(ipNetToMediaEntry);
    }
}

static icmp_t *
assign_icmp(GSList *vbl)
{
    GSList *elem;
    icmp_t *icmp;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 5};

    icmp = (icmp_t *) g_malloc0(sizeof(icmp_t) + sizeof(GSList *));
    if (! icmp) {
        return NULL;
    }

    p = (char *) icmp + sizeof(icmp_t);
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
        if (vb->id_len > 8 && vb->id[7] == 1) {
            icmp->icmpInMsgs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 2) {
            icmp->icmpInErrors = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 3) {
            icmp->icmpInDestUnreachs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 4) {
            icmp->icmpInTimeExcds = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 5) {
            icmp->icmpInParmProbs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 6) {
            icmp->icmpInSrcQuenchs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 7) {
            icmp->icmpInRedirects = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 8) {
            icmp->icmpInEchos = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 9) {
            icmp->icmpInEchoReps = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 10) {
            icmp->icmpInTimestamps = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 11) {
            icmp->icmpInTimestampReps = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 12) {
            icmp->icmpInAddrMasks = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 13) {
            icmp->icmpInAddrMaskReps = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 14) {
            icmp->icmpOutMsgs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 15) {
            icmp->icmpOutErrors = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 16) {
            icmp->icmpOutDestUnreachs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 17) {
            icmp->icmpOutTimeExcds = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 18) {
            icmp->icmpOutParmProbs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 19) {
            icmp->icmpOutSrcQuenchs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 20) {
            icmp->icmpOutRedirects = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 21) {
            icmp->icmpOutEchos = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 22) {
            icmp->icmpOutEchoReps = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 23) {
            icmp->icmpOutTimestamps = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 24) {
            icmp->icmpOutTimestampReps = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 25) {
            icmp->icmpOutAddrMasks = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 26) {
            icmp->icmpOutAddrMaskReps = &(vb->syntax.ui32[0]);
        }
    }

    return icmp;
}

int
ip_mib_get_icmp(host_snmp *s, icmp_t **icmp)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 5, 0};

    *icmp = NULL;

    base[7] = 1; stls_vbl_add_null(&in, base, 8);
    base[7] = 2; stls_vbl_add_null(&in, base, 8);
    base[7] = 3; stls_vbl_add_null(&in, base, 8);
    base[7] = 4; stls_vbl_add_null(&in, base, 8);
    base[7] = 5; stls_vbl_add_null(&in, base, 8);
    base[7] = 6; stls_vbl_add_null(&in, base, 8);
    base[7] = 7; stls_vbl_add_null(&in, base, 8);
    base[7] = 8; stls_vbl_add_null(&in, base, 8);
    base[7] = 9; stls_vbl_add_null(&in, base, 8);
    base[7] = 10; stls_vbl_add_null(&in, base, 8);
    base[7] = 11; stls_vbl_add_null(&in, base, 8);
    base[7] = 12; stls_vbl_add_null(&in, base, 8);
    base[7] = 13; stls_vbl_add_null(&in, base, 8);
    base[7] = 14; stls_vbl_add_null(&in, base, 8);
    base[7] = 15; stls_vbl_add_null(&in, base, 8);
    base[7] = 16; stls_vbl_add_null(&in, base, 8);
    base[7] = 17; stls_vbl_add_null(&in, base, 8);
    base[7] = 18; stls_vbl_add_null(&in, base, 8);
    base[7] = 19; stls_vbl_add_null(&in, base, 8);
    base[7] = 20; stls_vbl_add_null(&in, base, 8);
    base[7] = 21; stls_vbl_add_null(&in, base, 8);
    base[7] = 22; stls_vbl_add_null(&in, base, 8);
    base[7] = 23; stls_vbl_add_null(&in, base, 8);
    base[7] = 24; stls_vbl_add_null(&in, base, 8);
    base[7] = 25; stls_vbl_add_null(&in, base, 8);
    base[7] = 26; stls_vbl_add_null(&in, base, 8);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *icmp = assign_icmp(out);

    return 0;
}

void
ip_mib_free_icmp(icmp_t *icmp)
{
    GSList *vbl;
    char *p;

    if (icmp) {
        p = (char *) icmp + sizeof(icmp_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(icmp);
    }
}


