/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Options:
 *   --scli-include='dot3StatsEntry'
 *
 * Derived from EtherLike-MIB:
 *   The MIB module to describe generic objects for
 *   Ethernet-like network interfaces.
 *   
 *   The following reference is used throughout this
 *   MIB module:
 *   
 *   [IEEE 802.3 Std] refers to:
 *      IEEE Std 802.3, 1998 Edition: 'Information
 *      technology - Telecommunications and
 *      information exchange between systems -
 *      Local and metropolitan area networks -
 *      Specific requirements - Part 3: Carrier
 *      sense multiple access with collision
 *      detection (CSMA/CD) access method and
 *      physical layer specifications',
 *      September 1998.
 *   
 *   Of particular interest is Clause 30, '10Mb/s,
 *   100Mb/s and 1000Mb/s Management'.
 *
 * Revision 1999-08-24 04:00:
 *   Updated to include support for 1000 Mb/sec
 *   interfaces and full-duplex interfaces.
 *   This version published as RFC 2665.
 *
 * Revision 1998-06-03 21:50:
 *   Updated to include support for 100 Mb/sec
 *   interfaces.
 *   This version published as RFC 2358.
 *
 * Revision 1994-02-03 04:00:
 *   Initial version, published as RFC 1650.
 *
 * $Id$
 */

#include "etherlike-mib.h"

GSnmpEnum const etherlike_mib_enums_dot3StatsDuplexStatus[] = {
    { ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_UNKNOWN,    "unknown" },
    { ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_HALFDUPLEX, "halfDuplex" },
    { ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_FULLDUPLEX, "fullDuplex" },
    { 0, NULL }
};


static guint32 const dot3StatsEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 7, 2, 1};

static GSnmpAttribute dot3StatsEntry_attr[] = {
    { 2, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSALIGNMENTERRORS, "dot3StatsAlignmentErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsAlignmentErrors),
      0,
      0 },
    { 3, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSFCSERRORS, "dot3StatsFCSErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsFCSErrors),
      0,
      0 },
    { 4, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSSINGLECOLLISIONFRAMES, "dot3StatsSingleCollisionFrames",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsSingleCollisionFrames),
      0,
      0 },
    { 5, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSMULTIPLECOLLISIONFRAMES, "dot3StatsMultipleCollisionFrames",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsMultipleCollisionFrames),
      0,
      0 },
    { 6, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSSQETESTERRORS, "dot3StatsSQETestErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsSQETestErrors),
      0,
      0 },
    { 7, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSDEFERREDTRANSMISSIONS, "dot3StatsDeferredTransmissions",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsDeferredTransmissions),
      0,
      0 },
    { 8, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSLATECOLLISIONS, "dot3StatsLateCollisions",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsLateCollisions),
      0,
      0 },
    { 9, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSEXCESSIVECOLLISIONS, "dot3StatsExcessiveCollisions",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsExcessiveCollisions),
      0,
      0 },
    { 10, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSINTERNALMACTRANSMITERRORS, "dot3StatsInternalMacTransmitErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsInternalMacTransmitErrors),
      0,
      0 },
    { 11, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSCARRIERSENSEERRORS, "dot3StatsCarrierSenseErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsCarrierSenseErrors),
      0,
      0 },
    { 13, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSFRAMETOOLONGS, "dot3StatsFrameTooLongs",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsFrameTooLongs),
      0,
      0 },
    { 16, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSINTERNALMACRECEIVEERRORS, "dot3StatsInternalMacReceiveErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsInternalMacReceiveErrors),
      0,
      0 },
    { 17, G_SNMP_OBJECTID,
      ETHERLIKE_MIB_DOT3STATSETHERCHIPSET, "dot3StatsEtherChipSet",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsEtherChipSet),
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, _dot3StatsEtherChipSetLength),
      0 },
    { 18, G_SNMP_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSSYMBOLERRORS, "dot3StatsSymbolErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsSymbolErrors),
      0,
      0 },
    { 19, G_SNMP_INTEGER32,
      ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS, "dot3StatsDuplexStatus",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsDuplexStatus),
      0,
      0 },
    { 0, 0, 0, NULL }
};


etherlike_mib_dot3StatsEntry_t *
etherlike_mib_new_dot3StatsEntry()
{
    etherlike_mib_dot3StatsEntry_t *dot3StatsEntry;

    dot3StatsEntry = (etherlike_mib_dot3StatsEntry_t *) g_malloc0(sizeof(etherlike_mib_dot3StatsEntry_t) + sizeof(gpointer));
    return dot3StatsEntry;
}

static inline int
unpack_dot3StatsEntry(GSnmpVarBind *vb, etherlike_mib_dot3StatsEntry_t *dot3StatsEntry)
{
    guint8 idx = 11;

    if (vb->id_len < idx) return -1;
    dot3StatsEntry->dot3StatsIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static inline gint8
pack_dot3StatsEntry(guint32 *base, gint32 dot3StatsIndex)
{
    guint8 idx = 11;

    base[idx++] = dot3StatsIndex;
    return idx;
}

static inline etherlike_mib_dot3StatsEntry_t *
assign_dot3StatsEntry(GSList *vbl)
{
    etherlike_mib_dot3StatsEntry_t *dot3StatsEntry;
    char *p;

    dot3StatsEntry = etherlike_mib_new_dot3StatsEntry();
    if (! dot3StatsEntry) {
        return NULL;
    }

    p = (char *) dot3StatsEntry + sizeof(etherlike_mib_dot3StatsEntry_t);
    * (GSList **) p = vbl;

    if (unpack_dot3StatsEntry((GSnmpVarBind *) vbl->data, dot3StatsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "dot3StatsEntry");
        g_free(dot3StatsEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, dot3StatsEntry_oid, sizeof(dot3StatsEntry_oid)/sizeof(guint32),
                      dot3StatsEntry_attr, dot3StatsEntry);

    return dot3StatsEntry;
}

void
etherlike_mib_get_dot3StatsTable(GSnmpSession *s, etherlike_mib_dot3StatsEntry_t ***dot3StatsEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 7, 2, 1, 0};

    *dot3StatsEntry = NULL;

    gsnmp_attr_get(s, &in, base, 11, 10, dot3StatsEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *dot3StatsEntry = (etherlike_mib_dot3StatsEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(etherlike_mib_dot3StatsEntry_t *));
        if (! *dot3StatsEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*dot3StatsEntry)[i] = assign_dot3StatsEntry(row->data);
        }
    }
}

void
etherlike_mib_get_dot3StatsEntry(GSnmpSession *s, etherlike_mib_dot3StatsEntry_t **dot3StatsEntry, gint32 dot3StatsIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, dot3StatsEntry_oid, sizeof(dot3StatsEntry_oid));
    len = pack_dot3StatsEntry(base, dot3StatsIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "dot3StatsEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *dot3StatsEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 10, dot3StatsEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *dot3StatsEntry = assign_dot3StatsEntry(out);
    }
}

void
etherlike_mib_free_dot3StatsEntry(etherlike_mib_dot3StatsEntry_t *dot3StatsEntry)
{
    GSList *vbl;
    char *p;

    if (dot3StatsEntry) {
        p = (char *) dot3StatsEntry + sizeof(etherlike_mib_dot3StatsEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(dot3StatsEntry);
    }
}

void
etherlike_mib_free_dot3StatsTable(etherlike_mib_dot3StatsEntry_t **dot3StatsEntry)
{
    int i;

    if (dot3StatsEntry) {
        for (i = 0; dot3StatsEntry[i]; i++) {
            etherlike_mib_free_dot3StatsEntry(dot3StatsEntry[i]);
        }
        g_free(dot3StatsEntry);
    }
}


