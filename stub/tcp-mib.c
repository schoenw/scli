/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
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

GSnmpEnum const tcp_mib_enums_tcpRtoAlgorithm[] = {
    { TCP_MIB_TCPRTOALGORITHM_OTHER,    "other" },
    { TCP_MIB_TCPRTOALGORITHM_CONSTANT, "constant" },
    { TCP_MIB_TCPRTOALGORITHM_RSRE,     "rsre" },
    { TCP_MIB_TCPRTOALGORITHM_VANJ,     "vanj" },
    { 0, NULL }
};

GSnmpEnum const tcp_mib_enums_tcpConnState[] = {
    { TCP_MIB_TCPCONNSTATE_CLOSED,      "closed" },
    { TCP_MIB_TCPCONNSTATE_LISTEN,      "listen" },
    { TCP_MIB_TCPCONNSTATE_SYNSENT,     "synSent" },
    { TCP_MIB_TCPCONNSTATE_SYNRECEIVED, "synReceived" },
    { TCP_MIB_TCPCONNSTATE_ESTABLISHED, "established" },
    { TCP_MIB_TCPCONNSTATE_FINWAIT1,    "finWait1" },
    { TCP_MIB_TCPCONNSTATE_FINWAIT2,    "finWait2" },
    { TCP_MIB_TCPCONNSTATE_CLOSEWAIT,   "closeWait" },
    { TCP_MIB_TCPCONNSTATE_LASTACK,     "lastAck" },
    { TCP_MIB_TCPCONNSTATE_CLOSING,     "closing" },
    { TCP_MIB_TCPCONNSTATE_TIMEWAIT,    "timeWait" },
    { TCP_MIB_TCPCONNSTATE_DELETETCB,   "deleteTCB" },
    { 0, NULL }
};


static guint32 const tcp_oid[] = {1, 3, 6, 1, 2, 1, 6};

static GSnmpAttribute tcp_attr[] = {
    { 1, G_SNMP_INTEGER32,
      TCP_MIB_TCPRTOALGORITHM, "tcpRtoAlgorithm",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRtoAlgorithm),
      0,
      0 },
    { 2, G_SNMP_INTEGER32,
      TCP_MIB_TCPRTOMIN, "tcpRtoMin",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRtoMin),
      0,
      0 },
    { 3, G_SNMP_INTEGER32,
      TCP_MIB_TCPRTOMAX, "tcpRtoMax",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRtoMax),
      0,
      0 },
    { 4, G_SNMP_INTEGER32,
      TCP_MIB_TCPMAXCONN, "tcpMaxConn",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpMaxConn),
      0,
      0 },
    { 5, G_SNMP_COUNTER32,
      TCP_MIB_TCPACTIVEOPENS, "tcpActiveOpens",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpActiveOpens),
      0,
      0 },
    { 6, G_SNMP_COUNTER32,
      TCP_MIB_TCPPASSIVEOPENS, "tcpPassiveOpens",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpPassiveOpens),
      0,
      0 },
    { 7, G_SNMP_COUNTER32,
      TCP_MIB_TCPATTEMPTFAILS, "tcpAttemptFails",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpAttemptFails),
      0,
      0 },
    { 8, G_SNMP_COUNTER32,
      TCP_MIB_TCPESTABRESETS, "tcpEstabResets",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpEstabResets),
      0,
      0 },
    { 9, G_SNMP_UNSIGNED32,
      TCP_MIB_TCPCURRESTAB, "tcpCurrEstab",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpCurrEstab),
      0,
      0 },
    { 10, G_SNMP_COUNTER32,
      TCP_MIB_TCPINSEGS, "tcpInSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpInSegs),
      0,
      0 },
    { 11, G_SNMP_COUNTER32,
      TCP_MIB_TCPOUTSEGS, "tcpOutSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpOutSegs),
      0,
      0 },
    { 12, G_SNMP_COUNTER32,
      TCP_MIB_TCPRETRANSSEGS, "tcpRetransSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRetransSegs),
      0,
      0 },
    { 14, G_SNMP_COUNTER32,
      TCP_MIB_TCPINERRS, "tcpInErrs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpInErrs),
      0,
      0 },
    { 15, G_SNMP_COUNTER32,
      TCP_MIB_TCPOUTRSTS, "tcpOutRsts",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpOutRsts),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const tcpConnEntry_oid[] = {1, 3, 6, 1, 2, 1, 6, 13, 1};

static GSnmpAttribute tcpConnEntry_attr[] = {
    { 1, G_SNMP_INTEGER32,
      TCP_MIB_TCPCONNSTATE, "tcpConnState",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcpConnEntry_t, tcpConnState),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


tcp_mib_tcp_t *
tcp_mib_new_tcp()
{
    tcp_mib_tcp_t *tcp;

    tcp = (tcp_mib_tcp_t *) g_malloc0(sizeof(tcp_mib_tcp_t) + sizeof(gpointer));
    return tcp;
}

static inline tcp_mib_tcp_t *
assign_tcp(GSList *vbl)
{
    tcp_mib_tcp_t *tcp;
    char *p;

    tcp = tcp_mib_new_tcp();
    if (! tcp) {
        return NULL;
    }

    p = (char *) tcp + sizeof(tcp_mib_tcp_t);
    * (GSList **) p = vbl;

    gsnmp_attr_assign(vbl, tcp_oid, sizeof(tcp_oid)/sizeof(guint32),
                      tcp_attr, tcp);

    return tcp;
}

void
tcp_mib_get_tcp(GSnmpSession *s, tcp_mib_tcp_t **tcp, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 6, 0};

    *tcp = NULL;

    gsnmp_attr_get(s, &in, base, 8, 7, tcp_attr, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *tcp = assign_tcp(out);
    }
}

void
tcp_mib_free_tcp(tcp_mib_tcp_t *tcp)
{
    GSList *vbl;
    char *p;

    if (tcp) {
        p = (char *) tcp + sizeof(tcp_mib_tcp_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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

static inline int
unpack_tcpConnEntry(GSnmpVarBind *vb, tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    guint8 idx = 10;
    guint16 i, len;

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

static inline int
pack_tcpConnEntry(guint32 *base, guchar *tcpConnLocalAddress, gint32 tcpConnLocalPort, guchar *tcpConnRemAddress, gint32 tcpConnRemPort)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = tcpConnLocalAddress[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = tcpConnLocalPort;
    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = tcpConnRemAddress[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = tcpConnRemPort;
    return idx;
}

static inline tcp_mib_tcpConnEntry_t *
assign_tcpConnEntry(GSList *vbl)
{
    tcp_mib_tcpConnEntry_t *tcpConnEntry;
    char *p;

    tcpConnEntry = tcp_mib_new_tcpConnEntry();
    if (! tcpConnEntry) {
        return NULL;
    }

    p = (char *) tcpConnEntry + sizeof(tcp_mib_tcpConnEntry_t);
    * (GSList **) p = vbl;

    if (unpack_tcpConnEntry((GSnmpVarBind *) vbl->data, tcpConnEntry) < 0) {
        g_warning("%s: invalid instance identifier", "tcpConnEntry");
        g_free(tcpConnEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, tcpConnEntry_oid, sizeof(tcpConnEntry_oid)/sizeof(guint32),
                      tcpConnEntry_attr, tcpConnEntry);

    return tcpConnEntry;
}

void
tcp_mib_get_tcpConnTable(GSnmpSession *s, tcp_mib_tcpConnEntry_t ***tcpConnEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 6, 13, 1, 0};

    *tcpConnEntry = NULL;

    gsnmp_attr_get(s, &in, base, 10, 9, tcpConnEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *tcpConnEntry = (tcp_mib_tcpConnEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(tcp_mib_tcpConnEntry_t *));
        if (! *tcpConnEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*tcpConnEntry)[i] = assign_tcpConnEntry(row->data);
        }
    }
}

void
tcp_mib_get_tcpConnEntry(GSnmpSession *s, tcp_mib_tcpConnEntry_t **tcpConnEntry, guchar *tcpConnLocalAddress, gint32 tcpConnLocalPort, guchar *tcpConnRemAddress, gint32 tcpConnRemPort, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, tcpConnEntry_oid, sizeof(tcpConnEntry_oid));
    len = pack_tcpConnEntry(base, tcpConnLocalAddress, tcpConnLocalPort, tcpConnRemAddress, tcpConnRemPort);
    if (len < 0) {
        g_warning("%s: invalid index values", "tcpConnEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *tcpConnEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 9, tcpConnEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *tcpConnEntry = assign_tcpConnEntry(out);
    }
}

void
tcp_mib_set_tcpConnEntry(GSnmpSession *s, tcp_mib_tcpConnEntry_t *tcpConnEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, tcpConnEntry_oid, sizeof(tcpConnEntry_oid));
    len = pack_tcpConnEntry(base, tcpConnEntry->tcpConnLocalAddress, tcpConnEntry->tcpConnLocalPort, tcpConnEntry->tcpConnRemAddress, tcpConnEntry->tcpConnRemPort);
    if (len < 0) {
        g_warning("%s: invalid index values", "tcpConnEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 9, tcpConnEntry_attr, mask, tcpConnEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
tcp_mib_free_tcpConnEntry(tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    GSList *vbl;
    char *p;

    if (tcpConnEntry) {
        p = (char *) tcpConnEntry + sizeof(tcp_mib_tcpConnEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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


