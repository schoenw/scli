/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from UDP-MIB revision 1994-11-01 00:00.
 *
 * $Id$
 */

#include "udp-mib.h"

static udp_t *
assign_udp(GSList *vbl)
{
    GSList *elem;
    udp_t *udp;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 7};

    udp = (udp_t *) g_malloc0(sizeof(udp_t) + sizeof(GSList *));
    if (! udp) {
        return NULL;
    }

    p = (char *) udp + sizeof(udp_t);
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
            udp->udpInDatagrams = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 2) {
            udp->udpNoPorts = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 3) {
            udp->udpInErrors = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 8 && vb->id[7] == 4) {
            udp->udpOutDatagrams = &(vb->syntax.ui32[0]);
        }
    }

    return udp;
}

int
udp_mib_get_udp(host_snmp *s, udp_t **udp)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 7, 0};

    *udp = NULL;

    base[7] = 1; stls_vbl_add_null(&in, base, 8);
    base[7] = 2; stls_vbl_add_null(&in, base, 8);
    base[7] = 3; stls_vbl_add_null(&in, base, 8);
    base[7] = 4; stls_vbl_add_null(&in, base, 8);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *udp = assign_udp(out);

    return 0;
}

void
udp_mib_free_udp(udp_t *udp)
{
    GSList *vbl;
    char *p;

    if (udp) {
        p = (char *) udp + sizeof(udp_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(udp);
    }
}

static int
unpack_udpEntry(GSnmpVarBind *vb, udpEntry_t *udpEntry)
{
    int i, len, idx = 10;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        udpEntry->udpLocalAddress[i] = vb->id[idx++];
    }
    if (vb->id_len < idx) return -1;
    udpEntry->udpLocalPort = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static udpEntry_t *
assign_udpEntry(GSList *vbl)
{
    GSList *elem;
    udpEntry_t *udpEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 7, 5, 1};

    udpEntry = (udpEntry_t *) g_malloc0(sizeof(udpEntry_t) + sizeof(GSList *));
    if (! udpEntry) {
        return NULL;
    }

    p = (char *) udpEntry + sizeof(udpEntry_t);
    * (GSList **) p = vbl;

    if (unpack_udpEntry((GSnmpVarBind *) vbl->data, udpEntry) < 0) {
        g_warning("illegal udpEntry instance identifier");
        g_free(udpEntry);
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
    }

    return udpEntry;
}

int
udp_mib_get_udpEntry(host_snmp *s, udpEntry_t ***udpEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 7, 5, 1, 0};

    *udpEntry = NULL;


    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *udpEntry = (udpEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(udpEntry_t *));
    if (! *udpEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*udpEntry)[i] = assign_udpEntry(row->data);
    }

    return 0;
}

void
udp_mib_free_udpEntry(udpEntry_t **udpEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (udpEntry) {
        for (i = 0; udpEntry[i]; i++) {
            p = (char *) udpEntry[i] + sizeof(udpEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(udpEntry[i]);
        }
        g_free(udpEntry);
    }
}


