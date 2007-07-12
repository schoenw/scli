/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli TCP-MIB
 *
 * Derived from TCP-MIB:
 *   The MIB module for managing TCP implementations.
 *   
 *   Copyright (C) The Internet Society (2005). This version
 *   of this MIB module is a part of RFC 4022; see the RFC
 *   itself for full legal notices.
 *
 * Revision 2005-02-18 00:00:
 *   IP version neutral revision, published as RFC 4022.
 *
 * Revision 1994-11-01 00:00:
 *   Initial SMIv2 version, published as RFC 2012.
 *
 * Revision 1991-03-31 00:00:
 *   The initial revision of this MIB module was part of
 *   MIB-II.
 *
 * $Id$
 */

#include "tcp-mib.h"

GNetSnmpEnum const tcp_mib_enums_tcpRtoAlgorithm[] = {
    { TCP_MIB_TCPRTOALGORITHM_OTHER,    "other" },
    { TCP_MIB_TCPRTOALGORITHM_CONSTANT, "constant" },
    { TCP_MIB_TCPRTOALGORITHM_RSRE,     "rsre" },
    { TCP_MIB_TCPRTOALGORITHM_VANJ,     "vanj" },
    { TCP_MIB_TCPRTOALGORITHM_RFC2988,  "rfc2988" },
    { 0, NULL }
};

GNetSnmpEnum const tcp_mib_enums_tcpConnState[] = {
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

GNetSnmpEnum const tcp_mib_enums_tcpConnectionState[] = {
    { TCP_MIB_TCPCONNECTIONSTATE_CLOSED,      "closed" },
    { TCP_MIB_TCPCONNECTIONSTATE_LISTEN,      "listen" },
    { TCP_MIB_TCPCONNECTIONSTATE_SYNSENT,     "synSent" },
    { TCP_MIB_TCPCONNECTIONSTATE_SYNRECEIVED, "synReceived" },
    { TCP_MIB_TCPCONNECTIONSTATE_ESTABLISHED, "established" },
    { TCP_MIB_TCPCONNECTIONSTATE_FINWAIT1,    "finWait1" },
    { TCP_MIB_TCPCONNECTIONSTATE_FINWAIT2,    "finWait2" },
    { TCP_MIB_TCPCONNECTIONSTATE_CLOSEWAIT,   "closeWait" },
    { TCP_MIB_TCPCONNECTIONSTATE_LASTACK,     "lastAck" },
    { TCP_MIB_TCPCONNECTIONSTATE_CLOSING,     "closing" },
    { TCP_MIB_TCPCONNECTIONSTATE_TIMEWAIT,    "timeWait" },
    { TCP_MIB_TCPCONNECTIONSTATE_DELETETCB,   "deleteTCB" },
    { 0, NULL }
};


static gint32 tcpRtoMin_constraints[] = {0L, 2147483647L, 0, 0};
static gint32 tcpRtoMax_constraints[] = {0L, 2147483647L, 0, 0};
static gint32 tcpMaxConn_constraints[] = {-1L, 2147483647L, 0, 0};


static guint32 const tcp_oid[] = {1, 3, 6, 1, 2, 1, 6};

static GNetSnmpAttribute tcp_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      TCP_MIB_TCPRTOALGORITHM, "tcpRtoAlgorithm",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRtoAlgorithm),
      0,
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      TCP_MIB_TCPRTOMIN, "tcpRtoMin",
       tcpRtoMin_constraints,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRtoMin),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      TCP_MIB_TCPRTOMAX, "tcpRtoMax",
       tcpRtoMax_constraints,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRtoMax),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      TCP_MIB_TCPMAXCONN, "tcpMaxConn",
       tcpMaxConn_constraints,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpMaxConn),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPACTIVEOPENS, "tcpActiveOpens",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpActiveOpens),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPPASSIVEOPENS, "tcpPassiveOpens",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpPassiveOpens),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPATTEMPTFAILS, "tcpAttemptFails",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpAttemptFails),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPESTABRESETS, "tcpEstabResets",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpEstabResets),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      TCP_MIB_TCPCURRESTAB, "tcpCurrEstab",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpCurrEstab),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPINSEGS, "tcpInSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpInSegs),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPOUTSEGS, "tcpOutSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpOutSegs),
      0,
      0 },
    { 12, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPRETRANSSEGS, "tcpRetransSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpRetransSegs),
      0,
      0 },
    { 14, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPINERRS, "tcpInErrs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpInErrs),
      0,
      0 },
    { 15, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      TCP_MIB_TCPOUTRSTS, "tcpOutRsts",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpOutRsts),
      0,
      0 },
    { 17, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      TCP_MIB_TCPHCINSEGS, "tcpHCInSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpHCInSegs),
      0,
      0 },
    { 18, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      TCP_MIB_TCPHCOUTSEGS, "tcpHCOutSegs",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcp_t, tcpHCOutSegs),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const tcpConnEntry_oid[] = {1, 3, 6, 1, 2, 1, 6, 13, 1};

static GNetSnmpAttribute tcpConnEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      TCP_MIB_TCPCONNSTATE, "tcpConnState",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcpConnEntry_t, tcpConnState),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const tcpConnectionEntry_oid[] = {1, 3, 6, 1, 2, 1, 6, 19, 1};

static GNetSnmpAttribute tcpConnectionEntry_attr[] = {
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      TCP_MIB_TCPCONNECTIONSTATE, "tcpConnectionState",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcpConnectionEntry_t, tcpConnectionState),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      TCP_MIB_TCPCONNECTIONPROCESS, "tcpConnectionProcess",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcpConnectionEntry_t, tcpConnectionProcess),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const tcpListenerEntry_oid[] = {1, 3, 6, 1, 2, 1, 6, 20, 1};

static GNetSnmpAttribute tcpListenerEntry_attr[] = {
    { 4, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      TCP_MIB_TCPLISTENERPROCESS, "tcpListenerProcess",
       NULL,
      G_STRUCT_OFFSET(tcp_mib_tcpListenerEntry_t, tcpListenerProcess),
      0,
      0 },
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
assign_tcp(GList *vbl)
{
    tcp_mib_tcp_t *tcp;
    char *p;

    tcp = tcp_mib_new_tcp();
    p = (char *) tcp + sizeof(tcp_mib_tcp_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, tcp_oid, G_N_ELEMENTS(tcp_oid),
                      tcp_attr, tcp);

    return tcp;
}

void
tcp_mib_get_tcp(GNetSnmp *s, tcp_mib_tcp_t **tcp, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static const guint32 _base[] = {1, 3, 6, 1, 2, 1, 6, 0};
    guint32 base[128];

    *tcp = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 8, 7, tcp_attr, mask);

    out = gnet_snmp_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *tcp = assign_tcp(out);
    }
}

void
tcp_mib_free_tcp(tcp_mib_tcp_t *tcp)
{
    GList *vbl;
    char *p;

    if (tcp) {
        p = (char *) tcp + sizeof(tcp_mib_tcp_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
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
unpack_tcpConnEntry(GNetSnmpVarBind *vb, tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tcpConnEntry->tcpConnLocalAddress[i] = vb->oid[idx++];
    }
    if (vb->oid_len < idx) return -1;
    tcpConnEntry->tcpConnLocalPort = vb->oid[idx++];
    if ((tcpConnEntry->tcpConnLocalPort < 0 || tcpConnEntry->tcpConnLocalPort > 65535)) {
         return -1;
    }
    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tcpConnEntry->tcpConnRemAddress[i] = vb->oid[idx++];
    }
    if (vb->oid_len < idx) return -1;
    tcpConnEntry->tcpConnRemPort = vb->oid[idx++];
    if ((tcpConnEntry->tcpConnRemPort < 0 || tcpConnEntry->tcpConnRemPort > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
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
assign_tcpConnEntry(GList *vbl)
{
    tcp_mib_tcpConnEntry_t *tcpConnEntry;
    char *p;

    tcpConnEntry = tcp_mib_new_tcpConnEntry();
    p = (char *) tcpConnEntry + sizeof(tcp_mib_tcpConnEntry_t);
    * (GList **) p = vbl;

    if (unpack_tcpConnEntry((GNetSnmpVarBind *) vbl->data, tcpConnEntry) < 0) {
        g_warning("%s: invalid instance identifier", "tcpConnEntry");
        g_free(tcpConnEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, tcpConnEntry_oid, G_N_ELEMENTS(tcpConnEntry_oid),
                      tcpConnEntry_attr, tcpConnEntry);

    return tcpConnEntry;
}

void
tcp_mib_get_tcpConnTable(GNetSnmp *s, tcp_mib_tcpConnEntry_t ***tcpConnEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 6, 13, 1, 0};
    guint32 base[128];

    *tcpConnEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 10, 9, tcpConnEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *tcpConnEntry = (tcp_mib_tcpConnEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(tcp_mib_tcpConnEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*tcpConnEntry)[i] = assign_tcpConnEntry(row->data);
        }
    }
}

void
tcp_mib_get_tcpConnEntry(GNetSnmp *s, tcp_mib_tcpConnEntry_t **tcpConnEntry, guchar *tcpConnLocalAddress, gint32 tcpConnLocalPort, guchar *tcpConnRemAddress, gint32 tcpConnRemPort, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, tcpConnEntry_oid, sizeof(tcpConnEntry_oid));
    len = pack_tcpConnEntry(base, tcpConnLocalAddress, tcpConnLocalPort, tcpConnRemAddress, tcpConnRemPort);
    if (len < 0) {
        g_warning("%s: invalid index values", "tcpConnEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *tcpConnEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, tcpConnEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *tcpConnEntry = assign_tcpConnEntry(out);
    }
}

void
tcp_mib_set_tcpConnEntry(GNetSnmp *s, tcp_mib_tcpConnEntry_t *tcpConnEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, tcpConnEntry_oid, sizeof(tcpConnEntry_oid));
    len = pack_tcpConnEntry(base, tcpConnEntry->tcpConnLocalAddress, tcpConnEntry->tcpConnLocalPort, tcpConnEntry->tcpConnRemAddress, tcpConnEntry->tcpConnRemPort);
    if (len < 0) {
        g_warning("%s: invalid index values", "tcpConnEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 9, tcpConnEntry_attr, mask, tcpConnEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
tcp_mib_free_tcpConnEntry(tcp_mib_tcpConnEntry_t *tcpConnEntry)
{
    GList *vbl;
    char *p;

    if (tcpConnEntry) {
        p = (char *) tcpConnEntry + sizeof(tcp_mib_tcpConnEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
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

tcp_mib_tcpConnectionEntry_t *
tcp_mib_new_tcpConnectionEntry()
{
    tcp_mib_tcpConnectionEntry_t *tcpConnectionEntry;

    tcpConnectionEntry = (tcp_mib_tcpConnectionEntry_t *) g_malloc0(sizeof(tcp_mib_tcpConnectionEntry_t) + sizeof(gpointer));
    return tcpConnectionEntry;
}

static inline int
unpack_tcpConnectionEntry(GNetSnmpVarBind *vb, tcp_mib_tcpConnectionEntry_t *tcpConnectionEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    tcpConnectionEntry->tcpConnectionLocalAddressType = vb->oid[idx++];
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len > 118) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tcpConnectionEntry->tcpConnectionLocalAddress[i] = vb->oid[idx++];
    }
    tcpConnectionEntry->_tcpConnectionLocalAddressLength = len;
    if (vb->oid_len < idx) return -1;
    tcpConnectionEntry->tcpConnectionLocalPort = vb->oid[idx++];
     if ((tcpConnectionEntry->tcpConnectionLocalPort > 65535)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    tcpConnectionEntry->tcpConnectionRemAddressType = vb->oid[idx++];
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len > 118) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tcpConnectionEntry->tcpConnectionRemAddress[i] = vb->oid[idx++];
    }
    tcpConnectionEntry->_tcpConnectionRemAddressLength = len;
    if (vb->oid_len < idx) return -1;
    tcpConnectionEntry->tcpConnectionRemPort = vb->oid[idx++];
     if ((tcpConnectionEntry->tcpConnectionRemPort > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_tcpConnectionEntry(guint32 *base, gint32 tcpConnectionLocalAddressType, guchar *tcpConnectionLocalAddress, guint16 _tcpConnectionLocalAddressLength, guint32 tcpConnectionLocalPort, gint32 tcpConnectionRemAddressType, guchar *tcpConnectionRemAddress, guint16 _tcpConnectionRemAddressLength, guint32 tcpConnectionRemPort)
{
    guint8 idx = 10;
    guint16 i, len;

    base[idx++] = tcpConnectionLocalAddressType;
    len = _tcpConnectionLocalAddressLength;
    base[idx++] = len;
    if (len > 118) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = tcpConnectionLocalAddress[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = tcpConnectionLocalPort;
    base[idx++] = tcpConnectionRemAddressType;
    len = _tcpConnectionRemAddressLength;
    base[idx++] = len;
    if (len > 118) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = tcpConnectionRemAddress[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = tcpConnectionRemPort;
    return idx;
}

static inline tcp_mib_tcpConnectionEntry_t *
assign_tcpConnectionEntry(GList *vbl)
{
    tcp_mib_tcpConnectionEntry_t *tcpConnectionEntry;
    char *p;

    tcpConnectionEntry = tcp_mib_new_tcpConnectionEntry();
    p = (char *) tcpConnectionEntry + sizeof(tcp_mib_tcpConnectionEntry_t);
    * (GList **) p = vbl;

    if (unpack_tcpConnectionEntry((GNetSnmpVarBind *) vbl->data, tcpConnectionEntry) < 0) {
        g_warning("%s: invalid instance identifier", "tcpConnectionEntry");
        g_free(tcpConnectionEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, tcpConnectionEntry_oid, G_N_ELEMENTS(tcpConnectionEntry_oid),
                      tcpConnectionEntry_attr, tcpConnectionEntry);

    return tcpConnectionEntry;
}

void
tcp_mib_get_tcpConnectionTable(GNetSnmp *s, tcp_mib_tcpConnectionEntry_t ***tcpConnectionEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 6, 19, 1, 0};
    guint32 base[128];

    *tcpConnectionEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 10, 9, tcpConnectionEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *tcpConnectionEntry = (tcp_mib_tcpConnectionEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(tcp_mib_tcpConnectionEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*tcpConnectionEntry)[i] = assign_tcpConnectionEntry(row->data);
        }
    }
}

void
tcp_mib_get_tcpConnectionEntry(GNetSnmp *s, tcp_mib_tcpConnectionEntry_t **tcpConnectionEntry, gint32 tcpConnectionLocalAddressType, guchar *tcpConnectionLocalAddress, guint16 _tcpConnectionLocalAddressLength, guint32 tcpConnectionLocalPort, gint32 tcpConnectionRemAddressType, guchar *tcpConnectionRemAddress, guint16 _tcpConnectionRemAddressLength, guint32 tcpConnectionRemPort, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, tcpConnectionEntry_oid, sizeof(tcpConnectionEntry_oid));
    len = pack_tcpConnectionEntry(base, tcpConnectionLocalAddressType, tcpConnectionLocalAddress, _tcpConnectionLocalAddressLength, tcpConnectionLocalPort, tcpConnectionRemAddressType, tcpConnectionRemAddress, _tcpConnectionRemAddressLength, tcpConnectionRemPort);
    if (len < 0) {
        g_warning("%s: invalid index values", "tcpConnectionEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *tcpConnectionEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, tcpConnectionEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *tcpConnectionEntry = assign_tcpConnectionEntry(out);
    }
}

void
tcp_mib_set_tcpConnectionEntry(GNetSnmp *s, tcp_mib_tcpConnectionEntry_t *tcpConnectionEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, tcpConnectionEntry_oid, sizeof(tcpConnectionEntry_oid));
    len = pack_tcpConnectionEntry(base, tcpConnectionEntry->tcpConnectionLocalAddressType, tcpConnectionEntry->tcpConnectionLocalAddress, tcpConnectionEntry->_tcpConnectionLocalAddressLength, tcpConnectionEntry->tcpConnectionLocalPort, tcpConnectionEntry->tcpConnectionRemAddressType, tcpConnectionEntry->tcpConnectionRemAddress, tcpConnectionEntry->_tcpConnectionRemAddressLength, tcpConnectionEntry->tcpConnectionRemPort);
    if (len < 0) {
        g_warning("%s: invalid index values", "tcpConnectionEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 9, tcpConnectionEntry_attr, mask, tcpConnectionEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
tcp_mib_free_tcpConnectionEntry(tcp_mib_tcpConnectionEntry_t *tcpConnectionEntry)
{
    GList *vbl;
    char *p;

    if (tcpConnectionEntry) {
        p = (char *) tcpConnectionEntry + sizeof(tcp_mib_tcpConnectionEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(tcpConnectionEntry);
    }
}

void
tcp_mib_free_tcpConnectionTable(tcp_mib_tcpConnectionEntry_t **tcpConnectionEntry)
{
    int i;

    if (tcpConnectionEntry) {
        for (i = 0; tcpConnectionEntry[i]; i++) {
            tcp_mib_free_tcpConnectionEntry(tcpConnectionEntry[i]);
        }
        g_free(tcpConnectionEntry);
    }
}

tcp_mib_tcpListenerEntry_t *
tcp_mib_new_tcpListenerEntry()
{
    tcp_mib_tcpListenerEntry_t *tcpListenerEntry;

    tcpListenerEntry = (tcp_mib_tcpListenerEntry_t *) g_malloc0(sizeof(tcp_mib_tcpListenerEntry_t) + sizeof(gpointer));
    return tcpListenerEntry;
}

static inline int
unpack_tcpListenerEntry(GNetSnmpVarBind *vb, tcp_mib_tcpListenerEntry_t *tcpListenerEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    tcpListenerEntry->tcpListenerLocalAddressType = vb->oid[idx++];
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len > 118) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tcpListenerEntry->tcpListenerLocalAddress[i] = vb->oid[idx++];
    }
    tcpListenerEntry->_tcpListenerLocalAddressLength = len;
    if (vb->oid_len < idx) return -1;
    tcpListenerEntry->tcpListenerLocalPort = vb->oid[idx++];
     if ((tcpListenerEntry->tcpListenerLocalPort > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_tcpListenerEntry(guint32 *base, gint32 tcpListenerLocalAddressType, guchar *tcpListenerLocalAddress, guint16 _tcpListenerLocalAddressLength, guint32 tcpListenerLocalPort)
{
    guint8 idx = 10;
    guint16 i, len;

    base[idx++] = tcpListenerLocalAddressType;
    len = _tcpListenerLocalAddressLength;
    base[idx++] = len;
    if (len > 118) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = tcpListenerLocalAddress[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = tcpListenerLocalPort;
    return idx;
}

static inline tcp_mib_tcpListenerEntry_t *
assign_tcpListenerEntry(GList *vbl)
{
    tcp_mib_tcpListenerEntry_t *tcpListenerEntry;
    char *p;

    tcpListenerEntry = tcp_mib_new_tcpListenerEntry();
    p = (char *) tcpListenerEntry + sizeof(tcp_mib_tcpListenerEntry_t);
    * (GList **) p = vbl;

    if (unpack_tcpListenerEntry((GNetSnmpVarBind *) vbl->data, tcpListenerEntry) < 0) {
        g_warning("%s: invalid instance identifier", "tcpListenerEntry");
        g_free(tcpListenerEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, tcpListenerEntry_oid, G_N_ELEMENTS(tcpListenerEntry_oid),
                      tcpListenerEntry_attr, tcpListenerEntry);

    return tcpListenerEntry;
}

void
tcp_mib_get_tcpListenerTable(GNetSnmp *s, tcp_mib_tcpListenerEntry_t ***tcpListenerEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 6, 20, 1, 0};
    guint32 base[128];

    *tcpListenerEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 10, 9, tcpListenerEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *tcpListenerEntry = (tcp_mib_tcpListenerEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(tcp_mib_tcpListenerEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*tcpListenerEntry)[i] = assign_tcpListenerEntry(row->data);
        }
    }
}

void
tcp_mib_get_tcpListenerEntry(GNetSnmp *s, tcp_mib_tcpListenerEntry_t **tcpListenerEntry, gint32 tcpListenerLocalAddressType, guchar *tcpListenerLocalAddress, guint16 _tcpListenerLocalAddressLength, guint32 tcpListenerLocalPort, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, tcpListenerEntry_oid, sizeof(tcpListenerEntry_oid));
    len = pack_tcpListenerEntry(base, tcpListenerLocalAddressType, tcpListenerLocalAddress, _tcpListenerLocalAddressLength, tcpListenerLocalPort);
    if (len < 0) {
        g_warning("%s: invalid index values", "tcpListenerEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *tcpListenerEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, tcpListenerEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *tcpListenerEntry = assign_tcpListenerEntry(out);
    }
}

void
tcp_mib_free_tcpListenerEntry(tcp_mib_tcpListenerEntry_t *tcpListenerEntry)
{
    GList *vbl;
    char *p;

    if (tcpListenerEntry) {
        p = (char *) tcpListenerEntry + sizeof(tcp_mib_tcpListenerEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(tcpListenerEntry);
    }
}

void
tcp_mib_free_tcpListenerTable(tcp_mib_tcpListenerEntry_t **tcpListenerEntry)
{
    int i;

    if (tcpListenerEntry) {
        for (i = 0; tcpListenerEntry[i]; i++) {
            tcp_mib_free_tcpListenerEntry(tcpListenerEntry[i]);
        }
        g_free(tcpListenerEntry);
    }
}


