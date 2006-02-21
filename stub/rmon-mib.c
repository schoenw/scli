/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli \
 *     --scli-include='historyControlEntry' RMON-MIB
 *
 * Derived from RMON-MIB:
 *   Remote network monitoring devices, often called
 *   monitors or probes, are instruments that exist for
 *   the purpose of managing a network. This MIB defines
 *   objects for managing remote network monitoring devices.
 *
 * Revision 2000-05-11 00:00:
 *   Reformatted into SMIv2 format.
 *   
 *   This version published as RFC 2819.
 *
 * Revision 1995-02-01 00:00:
 *   Bug fixes, clarifications and minor changes based on
 *   implementation experience, published as RFC1757 [18].
 *   
 *   Two changes were made to object definitions:
 *   
 *   1) A new status bit has been defined for the
 *   captureBufferPacketStatus object, indicating that the
 *   packet order within the capture buffer may not be identical to
 *   the packet order as received off the wire.  This bit may only
 *   be used for packets transmitted by the probe.  Older NMS
 *   applications can safely ignore this status bit, which might be
 *   used by newer agents.
 *   
 *   2) The packetMatch trap has been removed.  This trap was never
 *   actually 'approved' and was not added to this document along
 *   with the risingAlarm and fallingAlarm traps. The packetMatch
 *   trap could not be throttled, which could cause disruption of
 *   normal network traffic under some circumstances. An NMS should
 *   configure a risingAlarm threshold on the appropriate
 *   channelMatches instance if a trap is desired for a packetMatch
 *   event. Note that logging of packetMatch events is still
 *   supported--only trap generation for such events has been
 *   removed.
 *   
 *   In addition, several clarifications to individual object
 *   definitions have been added to assist agent and NMS
 *   implementors:
 *   
 *   - global definition of 'good packets' and 'bad packets'
 *   
 *   - more detailed text governing conceptual row creation and
 *     modification
 *   
 *   - instructions for probes relating to interface changes and
 *     disruptions
 *   
 *   - clarification of some ethernet counter definitions
 *   
 *   - recommended formula for calculating network utilization
 *   
 *   - clarification of channel and captureBuffer behavior for some
 *     unusual conditions
 *   
 *   - examples of proper instance naming for each table
 *
 * Revision 1991-11-01 00:00:
 *   The original version of this MIB, published as RFC1271.
 *
 * $Id$
 */

#include "rmon-mib.h"

GNetSnmpEnum const rmon_mib_enums_EntryStatus[] = {
    { RMON_MIB_ENTRYSTATUS_VALID,         "valid" },
    { RMON_MIB_ENTRYSTATUS_CREATEREQUEST, "createRequest" },
    { RMON_MIB_ENTRYSTATUS_UNDERCREATION, "underCreation" },
    { RMON_MIB_ENTRYSTATUS_INVALID,       "invalid" },
    { 0, NULL }
};


static guint32 const risingAlarm[]
	= { RMON_MIB_RISINGALARM };
static guint32 const fallingAlarm[]
	= { RMON_MIB_FALLINGALARM };

GNetSnmpIdentity const rmon_mib_notifications[] = {
    { risingAlarm,
      G_N_ELEMENTS(risingAlarm),
      "risingAlarm" },
    { fallingAlarm,
      G_N_ELEMENTS(fallingAlarm),
      "fallingAlarm" },
    { 0, 0, NULL }
};


static gint32 historyControlBucketsRequested_constraints[] = {1L, 65535L, 0, 0};
static gint32 historyControlBucketsGranted_constraints[] = {1L, 65535L, 0, 0};
static gint32 historyControlInterval_constraints[] = {1L, 3600L, 0, 0};
static guint16 historyControlOwner_constraints[] = {0U, 127U, 0, 0};


static guint32 const historyControlEntry_oid[] = {1, 3, 6, 1, 2, 1, 16, 2, 1, 1};

static GNetSnmpAttribute historyControlEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OBJECTID,
      RMON_MIB_HISTORYCONTROLDATASOURCE, "historyControlDataSource",
       NULL,
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, historyControlDataSource),
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, _historyControlDataSourceLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RMON_MIB_HISTORYCONTROLBUCKETSREQUESTED, "historyControlBucketsRequested",
       historyControlBucketsRequested_constraints,
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, historyControlBucketsRequested),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RMON_MIB_HISTORYCONTROLBUCKETSGRANTED, "historyControlBucketsGranted",
       historyControlBucketsGranted_constraints,
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, historyControlBucketsGranted),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RMON_MIB_HISTORYCONTROLINTERVAL, "historyControlInterval",
       historyControlInterval_constraints,
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, historyControlInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RMON_MIB_HISTORYCONTROLOWNER, "historyControlOwner",
       historyControlOwner_constraints,
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, historyControlOwner),
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, _historyControlOwnerLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RMON_MIB_HISTORYCONTROLSTATUS, "historyControlStatus",
       NULL,
      G_STRUCT_OFFSET(rmon_mib_historyControlEntry_t, historyControlStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


rmon_mib_historyControlEntry_t *
rmon_mib_new_historyControlEntry()
{
    rmon_mib_historyControlEntry_t *historyControlEntry;

    historyControlEntry = (rmon_mib_historyControlEntry_t *) g_malloc0(sizeof(rmon_mib_historyControlEntry_t) + sizeof(gpointer));
    return historyControlEntry;
}

static inline int
unpack_historyControlEntry(GNetSnmpVarBind *vb, rmon_mib_historyControlEntry_t *historyControlEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    historyControlEntry->historyControlIndex = vb->oid[idx++];
    if ((historyControlEntry->historyControlIndex < 1 || historyControlEntry->historyControlIndex > 65535)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_historyControlEntry(guint32 *base, gint32 historyControlIndex)
{
    guint8 idx = 11;

    base[idx++] = historyControlIndex;
    return idx;
}

static inline rmon_mib_historyControlEntry_t *
assign_historyControlEntry(GList *vbl)
{
    rmon_mib_historyControlEntry_t *historyControlEntry;
    char *p;

    historyControlEntry = rmon_mib_new_historyControlEntry();
    p = (char *) historyControlEntry + sizeof(rmon_mib_historyControlEntry_t);
    * (GList **) p = vbl;

    if (unpack_historyControlEntry((GNetSnmpVarBind *) vbl->data, historyControlEntry) < 0) {
        g_warning("%s: invalid instance identifier", "historyControlEntry");
        g_free(historyControlEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, historyControlEntry_oid, G_N_ELEMENTS(historyControlEntry_oid),
                      historyControlEntry_attr, historyControlEntry);

    return historyControlEntry;
}

void
rmon_mib_get_historyControlTable(GNetSnmp *s, rmon_mib_historyControlEntry_t ***historyControlEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 16, 2, 1, 1, 0};

    *historyControlEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 11, 10, historyControlEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *historyControlEntry = (rmon_mib_historyControlEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rmon_mib_historyControlEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*historyControlEntry)[i] = assign_historyControlEntry(row->data);
        }
    }
}

void
rmon_mib_get_historyControlEntry(GNetSnmp *s, rmon_mib_historyControlEntry_t **historyControlEntry, gint32 historyControlIndex, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, historyControlEntry_oid, sizeof(historyControlEntry_oid));
    len = pack_historyControlEntry(base, historyControlIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "historyControlEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *historyControlEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, historyControlEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *historyControlEntry = assign_historyControlEntry(out);
    }
}

void
rmon_mib_set_historyControlEntry(GNetSnmp *s, rmon_mib_historyControlEntry_t *historyControlEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, historyControlEntry_oid, sizeof(historyControlEntry_oid));
    len = pack_historyControlEntry(base, historyControlEntry->historyControlIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "historyControlEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, historyControlEntry_attr, mask, historyControlEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
rmon_mib_free_historyControlEntry(rmon_mib_historyControlEntry_t *historyControlEntry)
{
    GList *vbl;
    char *p;

    if (historyControlEntry) {
        p = (char *) historyControlEntry + sizeof(rmon_mib_historyControlEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(historyControlEntry);
    }
}

void
rmon_mib_free_historyControlTable(rmon_mib_historyControlEntry_t **historyControlEntry)
{
    int i;

    if (historyControlEntry) {
        for (i = 0; historyControlEntry[i]; i++) {
            rmon_mib_free_historyControlEntry(historyControlEntry[i]);
        }
        g_free(historyControlEntry);
    }
}


