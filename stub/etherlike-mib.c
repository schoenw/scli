/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli \
 *     --scli-include='dot3StatsEntry' EtherLike-MIB
 *
 * Derived from EtherLike-MIB:
 *   The MIB module to describe generic objects for
 *   ethernet-like network interfaces.
 *   
 *   The following reference is used throughout this
 *   MIB module:
 *   
 *   [IEEE 802.3 Std] refers to:
 *      IEEE Std 802.3, 2002 Edition: 'IEEE Standard
 *   
 *   
 *   
 *      for Information technology -
 *      Telecommunications and information exchange
 *      between systems - Local and metropolitan
 *      area networks - Specific requirements -
 *      Part 3: Carrier sense multiple access with
 *      collision detection (CSMA/CD) access method
 *      and physical layer specifications', as
 *      amended by IEEE Std 802.3ae-2002:
 *      'Amendment: Media Access Control (MAC)
 *      Parameters, Physical Layer, and Management
 *      Parameters for 10 Gb/s Operation', August,
 *      2002.
 *   
 *   Of particular interest is Clause 30, '10 Mb/s,
 *   100 Mb/s, 1000 Mb/s, and 10 Gb/s Management'.
 *   
 *   Copyright (C) The Internet Society (2003).  This
 *   version of this MIB module is part of RFC 3635;
 *   see the RFC itself for full legal notices.
 *
 * Revision 2003-09-19 00:00:
 *   Updated to include support for 10 Gb/sec
 *   interfaces.  This resulted in the following
 *   revisions:
 *   
 *   - Updated dot3StatsAlignmentErrors and
 *     dot3StatsSymbolErrors DESCRIPTIONs to
 *     reflect behaviour at 10 Gb/s
 *   - Added dot3StatsRateControlAbility and
 *     dot3RateControlStatus for management
 *     of the Rate Control function in 10 Gb/s
 *     WAN applications
 *   - Added 64-bit versions of all counters
 *     that are used on high-speed ethernet
 *     interfaces
 *   - Added object groups to contain the new
 *     objects
 *   - Deprecated etherStatsBaseGroup and
 *     split into etherStatsBaseGroup2 and
 *     etherStatsHalfDuplexGroup, so that
 *     interfaces which can only operate at
 *     full-duplex do not need to implement
 *     half-duplex-only statistics
 *   - Deprecated dot3Compliance and replaced
 *     it with dot3Compliance2, which includes
 *     the compliance information for the new
 *     object groups
 *   
 *   
 *   
 *   
 *   In addition, the dot3Tests and dot3Errors
 *   object identities have been deprecated,
 *   since there is no longer a standard method
 *   for using them.
 *   
 *   This version published as RFC 3635.
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

GNetSnmpEnum const etherlike_mib_enums_dot3StatsDuplexStatus[] = {
    { ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_UNKNOWN,    "unknown" },
    { ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_HALFDUPLEX, "halfDuplex" },
    { ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS_FULLDUPLEX, "fullDuplex" },
    { 0, NULL }
};

GNetSnmpEnum const etherlike_mib_enums_dot3StatsRateControlStatus[] = {
    { ETHERLIKE_MIB_DOT3STATSRATECONTROLSTATUS_RATECONTROLOFF, "rateControlOff" },
    { ETHERLIKE_MIB_DOT3STATSRATECONTROLSTATUS_RATECONTROLON,  "rateControlOn" },
    { ETHERLIKE_MIB_DOT3STATSRATECONTROLSTATUS_UNKNOWN,        "unknown" },
    { 0, NULL }
};


static guint32 const dot3StatsEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 7, 2, 1};

static GNetSnmpAttribute dot3StatsEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSALIGNMENTERRORS, "dot3StatsAlignmentErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsAlignmentErrors),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSFCSERRORS, "dot3StatsFCSErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsFCSErrors),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSSINGLECOLLISIONFRAMES, "dot3StatsSingleCollisionFrames",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsSingleCollisionFrames),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSMULTIPLECOLLISIONFRAMES, "dot3StatsMultipleCollisionFrames",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsMultipleCollisionFrames),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSSQETESTERRORS, "dot3StatsSQETestErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsSQETestErrors),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSDEFERREDTRANSMISSIONS, "dot3StatsDeferredTransmissions",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsDeferredTransmissions),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSLATECOLLISIONS, "dot3StatsLateCollisions",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsLateCollisions),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSEXCESSIVECOLLISIONS, "dot3StatsExcessiveCollisions",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsExcessiveCollisions),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSINTERNALMACTRANSMITERRORS, "dot3StatsInternalMacTransmitErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsInternalMacTransmitErrors),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSCARRIERSENSEERRORS, "dot3StatsCarrierSenseErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsCarrierSenseErrors),
      0,
      0 },
    { 13, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSFRAMETOOLONGS, "dot3StatsFrameTooLongs",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsFrameTooLongs),
      0,
      0 },
    { 16, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSINTERNALMACRECEIVEERRORS, "dot3StatsInternalMacReceiveErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsInternalMacReceiveErrors),
      0,
      0 },
    { 17, GNET_SNMP_VARBIND_TYPE_OBJECTID,
      ETHERLIKE_MIB_DOT3STATSETHERCHIPSET, "dot3StatsEtherChipSet",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsEtherChipSet),
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, _dot3StatsEtherChipSetLength),
      0 },
    { 18, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      ETHERLIKE_MIB_DOT3STATSSYMBOLERRORS, "dot3StatsSymbolErrors",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsSymbolErrors),
      0,
      0 },
    { 19, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ETHERLIKE_MIB_DOT3STATSDUPLEXSTATUS, "dot3StatsDuplexStatus",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsDuplexStatus),
      0,
      0 },
    { 20, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ETHERLIKE_MIB_DOT3STATSRATECONTROLABILITY, "dot3StatsRateControlAbility",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsRateControlAbility),
      0,
      0 },
    { 21, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ETHERLIKE_MIB_DOT3STATSRATECONTROLSTATUS, "dot3StatsRateControlStatus",
       NULL,
      G_STRUCT_OFFSET(etherlike_mib_dot3StatsEntry_t, dot3StatsRateControlStatus),
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
unpack_dot3StatsEntry(GNetSnmpVarBind *vb, etherlike_mib_dot3StatsEntry_t *dot3StatsEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    dot3StatsEntry->dot3StatsIndex = vb->oid[idx++];
    if ((dot3StatsEntry->dot3StatsIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
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
assign_dot3StatsEntry(GList *vbl)
{
    etherlike_mib_dot3StatsEntry_t *dot3StatsEntry;
    char *p;

    dot3StatsEntry = etherlike_mib_new_dot3StatsEntry();
    p = (char *) dot3StatsEntry + sizeof(etherlike_mib_dot3StatsEntry_t);
    * (GList **) p = vbl;

    if (unpack_dot3StatsEntry((GNetSnmpVarBind *) vbl->data, dot3StatsEntry) < 0) {
        g_warning("%s: invalid instance identifier", "dot3StatsEntry");
        g_free(dot3StatsEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, dot3StatsEntry_oid, G_N_ELEMENTS(dot3StatsEntry_oid),
                      dot3StatsEntry_attr, dot3StatsEntry);

    return dot3StatsEntry;
}

void
etherlike_mib_get_dot3StatsTable(GNetSnmp *s, etherlike_mib_dot3StatsEntry_t ***dot3StatsEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 7, 2, 1, 0};
    guint32 base[128];

    *dot3StatsEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, dot3StatsEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *dot3StatsEntry = (etherlike_mib_dot3StatsEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(etherlike_mib_dot3StatsEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*dot3StatsEntry)[i] = assign_dot3StatsEntry(row->data);
        }
    }
}

void
etherlike_mib_get_dot3StatsEntry(GNetSnmp *s, etherlike_mib_dot3StatsEntry_t **dot3StatsEntry, gint32 dot3StatsIndex, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, dot3StatsEntry_oid, sizeof(dot3StatsEntry_oid));
    len = pack_dot3StatsEntry(base, dot3StatsIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "dot3StatsEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *dot3StatsEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, dot3StatsEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *dot3StatsEntry = assign_dot3StatsEntry(out);
    }
}

void
etherlike_mib_free_dot3StatsEntry(etherlike_mib_dot3StatsEntry_t *dot3StatsEntry)
{
    GList *vbl;
    char *p;

    if (dot3StatsEntry) {
        p = (char *) dot3StatsEntry + sizeof(etherlike_mib_dot3StatsEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
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


