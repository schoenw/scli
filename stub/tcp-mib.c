/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.16 for the stools package.
 *
 * Derived from TCP-MIB:
 *   The MIB module for managing TCP implementations.
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

#include "tcp-mib.h"

stls_enum_t const tcp_mib_enums_tcpRtoAlgorithm[] = {
    { TCP_MIB_TCPRTOALGORITHM_OTHER,	"other" },
    { TCP_MIB_TCPRTOALGORITHM_CONSTANT,	"constant" },
    { TCP_MIB_TCPRTOALGORITHM_RSRE,	"rsre" },
    { TCP_MIB_TCPRTOALGORITHM_VANJ,	"vanj" },
    { 0, NULL }
};

stls_enum_t const tcp_mib_enums_tcpConnState[] = {
    { TCP_MIB_TCPCONNSTATE_CLOSED,	"closed" },
    { TCP_MIB_TCPCONNSTATE_LISTEN,	"listen" },
    { TCP_MIB_TCPCONNSTATE_SYNSENT,	"synSent" },
    { TCP_MIB_TCPCONNSTATE_SYNRECEIVED,	"synReceived" },
    { TCP_MIB_TCPCONNSTATE_ESTABLISHED,	"established" },
    { TCP_MIB_TCPCONNSTATE_FINWAIT1,	"finWait1" },
    { TCP_MIB_TCPCONNSTATE_FINWAIT2,	"finWait2" },
    { TCP_MIB_TCPCONNSTATE_CLOSEWAIT,	"closeWait" },
    { TCP_MIB_TCPCONNSTATE_LASTACK,	"lastAck" },
    { TCP_MIB_TCPCONNSTATE_CLOSING,	"closing" },
    { TCP_MIB_TCPCONNSTATE_TIMEWAIT,	"timeWait" },
    { TCP_MIB_TCPCONNSTATE_DELETETCB,	"deleteTCB" },
    { 0, NULL }
};


static stls_stub_attr_t _tcp[] = {
    { 1, G_SNMP_INTEGER32, "tcpRtoAlgorithm" },
    { 2, G_SNMP_INTEGER32, "tcpRtoMin" },
    { 3, G_SNMP_INTEGER32, "tcpRtoMax" },
    { 4, G_SNMP_INTEGER32, "tcpMaxConn" },
    { 5, G_SNMP_COUNTER32, "tcpActiveOpens" },
    { 6, G_SNMP_COUNTER32, "tcpPassiveOpens" },
    { 7, G_SNMP_COUNTER32, "tcpAttemptFails" },
    { 8, G_SNMP_COUNTER32, "tcpEstabResets" },
    { 9, G_SNMP_UNSIGNED32, "tcpCurrEstab" },
    { 10, G_SNMP_COUNTER32, "tcpInSegs" },
    { 11, G_SNMP_COUNTER32, "tcpOutSegs" },
    { 12, G_SNMP_COUNTER32, "tcpRetransSegs" },
    { 14, G_SNMP_COUNTER32, "tcpInErrs" },
    { 15, G_SNMP_COUNTER32, "tcpOutRsts" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _tcpConnEntry[] = {
    { 1, G_SNMP_INTEGER32, "tcpConnState" },
    { 0, 0, NULL }
};


tcp_mib_tcp_t *
tcp_mib_new_tcp()
{
    tcp_mib_tcp_t *tcp;

    tcp = (tcp_mib_tcp_t *) g_malloc0(sizeof(tcp_mib_tcp_t) + sizeof(gpointer));
    return tcp;
}

static tcp_mib_tcp_t *
assign_tcp(GSList *vbl)
{
    GSList *elem;
    tcp_mib_tcp_t *tcp;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 6};

    tcp = tcp_mib_new_tcp();
    if (! tcp) {
        return NULL;
    }

    p = (char *) tcp + sizeof(tcp_mib_tcp_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _tcp, &idx) < 0) continue;

        switch (idx) {
        case 1:
            tcp->tcpRtoAlgorithm = &(vb->syntax.i32[0]);
            break;
        case 2:
            tcp->tcpRtoMin = &(vb->syntax.i32[0]);
            break;
        case 3:
            tcp->tcpRtoMax = &(vb->syntax.i32[0]);
            break;
        case 4:
            tcp->tcpMaxConn = &(vb->syntax.i32[0]);
            break;
        case 5:
            tcp->tcpActiveOpens = &(vb->syntax.ui32[0]);
            break;
        case 6:
            tcp->tcpPassiveOpens = &(vb->syntax.ui32[0]);
            break;
        case 7:
            tcp->tcpAttemptFails = &(vb->syntax.ui32[0]);
            break;
        case 8:
            tcp->tcpEstabResets = &(vb->syntax.ui32[0]);
            break;
        case 9:
            tcp->tcpCurrEstab = &(vb->syntax.ui32[0]);
            break;
        case 10:
            tcp->tcpInSegs = &(vb->syntax.ui32[0]);
            break;
        case 11:
            tcp->tcpOutSegs = &(vb->syntax.ui32[0]);
            break;
        case 12:
            tcp->tcpRetransSegs = &(vb->syntax.ui32[0]);
            break;
        case 14:
            tcp->tcpInErrs = &(vb->syntax.ui32[0]);
            break;
        case 15:
            tcp->tcpOutRsts = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return tcp;
}

int
tcp_mib_get_tcp(GSnmpSession *s, tcp_mib_tcp_t **tcp)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 6, 0};

    *tcp = NULL;

    stls_vbl_attributes(s, &in, base, 7, _tcp);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *tcp = assign_tcp(out);

    return 0;
}

void
tcp_mib_free_tcp(tcp_mib_tcp_t *tcp)
{
    GSList *vbl;
    char *p;

    if (tcp) {
        p = (char *) tcp + sizeof(tcp_mib_tcp_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(tcp);
    }
}

tcp_mib_tcpConnEntry_t *
tcp_mib_new_tcpConnEntry()
{
    tcp_mib_tcpConnEntry_t *tcpConnEntry;

    tcpConnEntry = (tcp_mib_tcpConnEntry_t *) g_malloc0(sizeof(tcp_mib_tcpConnEntry_t) + sizeof(gpointer));
    return tcpConnEntry;
}

static int
unpack_tcpConnEntry(GSnmpVarBind *vb, tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    int i, len, idx = 10;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tcpConnEntry->tcpConnLocalAddress[i] = vb->id[idx++];
    }
    if (vb->id_len < idx) return -1;
    tcpConnEntry->tcpConnLocalPort = vb->id[idx++];
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tcpConnEntry->tcpConnRemAddress[i] = vb->id[idx++];
    }
    if (vb->id_len < idx) return -1;
    tcpConnEntry->tcpConnRemPort = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static tcp_mib_tcpConnEntry_t *
assign_tcpConnEntry(GSList *vbl)
{
    GSList *elem;
    tcp_mib_tcpConnEntry_t *tcpConnEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 6, 13, 1};

    tcpConnEntry = tcp_mib_new_tcpConnEntry();
    if (! tcpConnEntry) {
        return NULL;
    }

    p = (char *) tcpConnEntry + sizeof(tcp_mib_tcpConnEntry_t);
    * (GSList **) p = vbl;

    if (unpack_tcpConnEntry((GSnmpVarBind *) vbl->data, tcpConnEntry) < 0) {
        g_warning("illegal tcpConnEntry instance identifier");
        g_free(tcpConnEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _tcpConnEntry, &idx) < 0) continue;

        switch (idx) {
        case 1:
            tcpConnEntry->tcpConnState = &(vb->syntax.i32[0]);
            break;
        };
    }

    return tcpConnEntry;
}

int
tcp_mib_get_tcpConnTable(GSnmpSession *s, tcp_mib_tcpConnEntry_t ***tcpConnEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 6, 13, 1, 0};

    *tcpConnEntry = NULL;

    stls_vbl_attributes(s, &in, base, 9, _tcpConnEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *tcpConnEntry = (tcp_mib_tcpConnEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(tcp_mib_tcpConnEntry_t *));
    if (! *tcpConnEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*tcpConnEntry)[i] = assign_tcpConnEntry(row->data);
    }

    return 0;
}

void
tcp_mib_free_tcpConnEntry(tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    GSList *vbl;
    char *p;

    if (tcpConnEntry) {
        p = (char *) tcpConnEntry + sizeof(tcp_mib_tcpConnEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(tcpConnEntry);
    }
}

void
tcp_mib_free_tcpConnTable(tcp_mib_tcpConnEntry_t **tcpConnEntry)
{
    int i;

    if (tcpConnEntry) {
        for (i = 0; tcpConnEntry[i]; i++) {
            tcp_mib_free_tcpConnEntry(tcpConnEntry[i]);
        }
        g_free(tcpConnEntry);
    }
}


