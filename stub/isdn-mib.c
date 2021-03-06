/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli \
 *     --scli-include='isdnBasicRateEntry|isdnBearerEntry|isdnEndpointEntry' ISDN-MIB
 *
 * Derived from ISDN-MIB:
 *   The MIB module to describe the
 *   management of ISDN interfaces.
 *
 * Revision 1996-09-23 16:42:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#include "isdn-mib.h"

GNetSnmpEnum const isdn_mib_enums_isdnBasicRateIfType[] = {
    { ISDN_MIB_ISDNBASICRATEIFTYPE_ISDNS, "isdns" },
    { ISDN_MIB_ISDNBASICRATEIFTYPE_ISDNU, "isdnu" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnBasicRateLineTopology[] = {
    { ISDN_MIB_ISDNBASICRATELINETOPOLOGY_POINTTOPOINT,      "pointToPoint" },
    { ISDN_MIB_ISDNBASICRATELINETOPOLOGY_POINTTOMULTIPOINT, "pointToMultipoint" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnBasicRateIfMode[] = {
    { ISDN_MIB_ISDNBASICRATEIFMODE_TE, "te" },
    { ISDN_MIB_ISDNBASICRATEIFMODE_NT, "nt" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnBasicRateSignalMode[] = {
    { ISDN_MIB_ISDNBASICRATESIGNALMODE_ACTIVE,   "active" },
    { ISDN_MIB_ISDNBASICRATESIGNALMODE_INACTIVE, "inactive" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnBearerChannelType[] = {
    { ISDN_MIB_ISDNBEARERCHANNELTYPE_DIALUP, "dialup" },
    { ISDN_MIB_ISDNBEARERCHANNELTYPE_LEASED, "leased" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnBearerOperStatus[] = {
    { ISDN_MIB_ISDNBEAREROPERSTATUS_IDLE,       "idle" },
    { ISDN_MIB_ISDNBEAREROPERSTATUS_CONNECTING, "connecting" },
    { ISDN_MIB_ISDNBEAREROPERSTATUS_CONNECTED,  "connected" },
    { ISDN_MIB_ISDNBEAREROPERSTATUS_ACTIVE,     "active" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnBearerCallOrigin[] = {
    { ISDN_MIB_ISDNBEARERCALLORIGIN_UNKNOWN,   "unknown" },
    { ISDN_MIB_ISDNBEARERCALLORIGIN_ORIGINATE, "originate" },
    { ISDN_MIB_ISDNBEARERCALLORIGIN_ANSWER,    "answer" },
    { ISDN_MIB_ISDNBEARERCALLORIGIN_CALLBACK,  "callback" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnBearerInfoType[] = {
    { ISDN_MIB_ISDNBEARERINFOTYPE_UNKNOWN,               "unknown" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_SPEECH,                "speech" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_UNRESTRICTEDDIGITAL,   "unrestrictedDigital" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_UNRESTRICTEDDIGITAL56, "unrestrictedDigital56" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_RESTRICTEDDIGITAL,     "restrictedDigital" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_AUDIO31,               "audio31" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_AUDIO7,                "audio7" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_VIDEO,                 "video" },
    { ISDN_MIB_ISDNBEARERINFOTYPE_PACKETSWITCHED,        "packetSwitched" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_isdnEndpointTeiType[] = {
    { ISDN_MIB_ISDNENDPOINTTEITYPE_DYNAMIC, "dynamic" },
    { ISDN_MIB_ISDNENDPOINTTEITYPE_STATIC,  "static" },
    { 0, NULL }
};

GNetSnmpEnum const isdn_mib_enums_IsdnSignalingProtocol[] = {
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_OTHER,     "other" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_DSS1,      "dss1" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_ETSI,      "etsi" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_DASS2,     "dass2" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_ESS4,      "ess4" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_ESS5,      "ess5" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_DMS100,    "dms100" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_DMS250,    "dms250" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_NI1,       "ni1" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_NI2,       "ni2" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_NI3,       "ni3" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN2,       "vn2" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN3,       "vn3" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN4,       "vn4" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_VN6,       "vn6" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_KDD,       "kdd" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_INS64,     "ins64" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_INS1500,   "ins1500" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_ITR6,      "itr6" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_CORNET,    "cornet" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_TS013,     "ts013" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_TS014,     "ts014" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_QSIG,      "qsig" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_SWISSNET2, "swissnet2" },
    { ISDN_MIB_ISDNSIGNALINGPROTOCOL_SWISSNET3, "swissnet3" },
    { 0, NULL }
};


static guint32 const isdnMibCallInformation[]
	= { ISDN_MIB_ISDNMIBCALLINFORMATION };

GNetSnmpIdentity const isdn_mib_notifications[] = {
    { isdnMibCallInformation,
      G_N_ELEMENTS(isdnMibCallInformation),
      "isdnMibCallInformation" },
    { 0, 0, NULL }
};


static gint32 isdnBearerChannelNumber_constraints[] = {1L, 30L, 0, 0};
static guint16 isdnBearerPeerAddress_constraints[] = {0U, 255U, 0, 0};
static guint16 isdnBearerPeerSubAddress_constraints[] = {0U, 255U, 0, 0};
static gint32 isdnEndpointIfIndex_constraints[] = {1L, 2147483647L, 0, 0};
static gint32 isdnEndpointTeiValue_constraints[] = {0L, 255L, 0, 0};
static guint16 isdnEndpointSpid_constraints[] = {0U, 255U, 0, 0};


static guint32 const isdnBasicRateEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 1, 1, 1};

static GNetSnmpAttribute isdnBasicRateEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBASICRATEIFTYPE, "isdnBasicRateIfType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateIfType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBASICRATELINETOPOLOGY, "isdnBasicRateLineTopology",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateLineTopology),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBASICRATEIFMODE, "isdnBasicRateIfMode",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateIfMode),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBASICRATESIGNALMODE, "isdnBasicRateSignalMode",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateSignalMode),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const isdnBearerEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 2, 1, 1};

static GNetSnmpAttribute isdnBearerEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBEARERCHANNELTYPE, "isdnBearerChannelType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerChannelType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBEAREROPERSTATUS, "isdnBearerOperStatus",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerOperStatus),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBEARERCHANNELNUMBER, "isdnBearerChannelNumber",
       isdnBearerChannelNumber_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerChannelNumber),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      ISDN_MIB_ISDNBEARERPEERADDRESS, "isdnBearerPeerAddress",
       isdnBearerPeerAddress_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerPeerAddress),
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, _isdnBearerPeerAddressLength),
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      ISDN_MIB_ISDNBEARERPEERSUBADDRESS, "isdnBearerPeerSubAddress",
       isdnBearerPeerSubAddress_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerPeerSubAddress),
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, _isdnBearerPeerSubAddressLength),
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBEARERCALLORIGIN, "isdnBearerCallOrigin",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerCallOrigin),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBEARERINFOTYPE, "isdnBearerInfoType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerInfoType),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNBEARERMULTIRATE, "isdnBearerMultirate",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerMultirate),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_TIMETICKS,
      ISDN_MIB_ISDNBEARERCALLSETUPTIME, "isdnBearerCallSetupTime",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerCallSetupTime),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_TIMETICKS,
      ISDN_MIB_ISDNBEARERCALLCONNECTTIME, "isdnBearerCallConnectTime",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerCallConnectTime),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      ISDN_MIB_ISDNBEARERCHARGEDUNITS, "isdnBearerChargedUnits",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerChargedUnits),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const isdnEndpointEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 4, 2, 1};

static GNetSnmpAttribute isdnEndpointEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNENDPOINTIFINDEX, "isdnEndpointIfIndex",
       isdnEndpointIfIndex_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnEndpointEntry_t, isdnEndpointIfIndex),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNENDPOINTIFTYPE, "isdnEndpointIfType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnEndpointEntry_t, isdnEndpointIfType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNENDPOINTTEITYPE, "isdnEndpointTeiType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnEndpointEntry_t, isdnEndpointTeiType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNENDPOINTTEIVALUE, "isdnEndpointTeiValue",
       isdnEndpointTeiValue_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnEndpointEntry_t, isdnEndpointTeiValue),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      ISDN_MIB_ISDNENDPOINTSPID, "isdnEndpointSpid",
       isdnEndpointSpid_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnEndpointEntry_t, isdnEndpointSpid),
      G_STRUCT_OFFSET(isdn_mib_isdnEndpointEntry_t, _isdnEndpointSpidLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ISDN_MIB_ISDNENDPOINTSTATUS, "isdnEndpointStatus",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnEndpointEntry_t, isdnEndpointStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


isdn_mib_isdnBasicRateEntry_t *
isdn_mib_new_isdnBasicRateEntry()
{
    isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry;

    isdnBasicRateEntry = (isdn_mib_isdnBasicRateEntry_t *) g_malloc0(sizeof(isdn_mib_isdnBasicRateEntry_t) + sizeof(gpointer));
    return isdnBasicRateEntry;
}

static inline int
unpack_isdnBasicRateEntry(GNetSnmpVarBind *vb, isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry)
{
    guint8 idx = 13;

    if (vb->oid_len < idx) return -1;
    isdnBasicRateEntry->ifIndex = vb->oid[idx++];
    if ((isdnBasicRateEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_isdnBasicRateEntry(guint32 *base, gint32 ifIndex)
{
    guint8 idx = 13;

    base[idx++] = ifIndex;
    return idx;
}

static inline isdn_mib_isdnBasicRateEntry_t *
assign_isdnBasicRateEntry(GList *vbl)
{
    isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry;
    char *p;

    isdnBasicRateEntry = isdn_mib_new_isdnBasicRateEntry();
    p = (char *) isdnBasicRateEntry + sizeof(isdn_mib_isdnBasicRateEntry_t);
    * (GList **) p = vbl;

    if (unpack_isdnBasicRateEntry((GNetSnmpVarBind *) vbl->data, isdnBasicRateEntry) < 0) {
        g_warning("%s: invalid instance identifier", "isdnBasicRateEntry");
        g_free(isdnBasicRateEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, isdnBasicRateEntry_oid, G_N_ELEMENTS(isdnBasicRateEntry_oid),
                      isdnBasicRateEntry_attr, isdnBasicRateEntry);

    return isdnBasicRateEntry;
}

void
isdn_mib_get_isdnBasicRateTable(GNetSnmp *s, isdn_mib_isdnBasicRateEntry_t ***isdnBasicRateEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 1, 1, 1, 0};
    guint32 base[128];

    *isdnBasicRateEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 13, 12, isdnBasicRateEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *isdnBasicRateEntry = (isdn_mib_isdnBasicRateEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(isdn_mib_isdnBasicRateEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*isdnBasicRateEntry)[i] = assign_isdnBasicRateEntry(row->data);
        }
    }
}

void
isdn_mib_get_isdnBasicRateEntry(GNetSnmp *s, isdn_mib_isdnBasicRateEntry_t **isdnBasicRateEntry, gint32 ifIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, isdnBasicRateEntry_oid, sizeof(isdnBasicRateEntry_oid));
    len = pack_isdnBasicRateEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBasicRateEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *isdnBasicRateEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 12, isdnBasicRateEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *isdnBasicRateEntry = assign_isdnBasicRateEntry(out);
    }
}

void
isdn_mib_set_isdnBasicRateEntry(GNetSnmp *s, isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, isdnBasicRateEntry_oid, sizeof(isdnBasicRateEntry_oid));
    len = pack_isdnBasicRateEntry(base, isdnBasicRateEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBasicRateEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 12, isdnBasicRateEntry_attr, mask, isdnBasicRateEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
isdn_mib_free_isdnBasicRateEntry(isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry)
{
    GList *vbl;
    char *p;

    if (isdnBasicRateEntry) {
        p = (char *) isdnBasicRateEntry + sizeof(isdn_mib_isdnBasicRateEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(isdnBasicRateEntry);
    }
}

void
isdn_mib_free_isdnBasicRateTable(isdn_mib_isdnBasicRateEntry_t **isdnBasicRateEntry)
{
    int i;

    if (isdnBasicRateEntry) {
        for (i = 0; isdnBasicRateEntry[i]; i++) {
            isdn_mib_free_isdnBasicRateEntry(isdnBasicRateEntry[i]);
        }
        g_free(isdnBasicRateEntry);
    }
}

isdn_mib_isdnBearerEntry_t *
isdn_mib_new_isdnBearerEntry()
{
    isdn_mib_isdnBearerEntry_t *isdnBearerEntry;

    isdnBearerEntry = (isdn_mib_isdnBearerEntry_t *) g_malloc0(sizeof(isdn_mib_isdnBearerEntry_t) + sizeof(gpointer));
    return isdnBearerEntry;
}

static inline int
unpack_isdnBearerEntry(GNetSnmpVarBind *vb, isdn_mib_isdnBearerEntry_t *isdnBearerEntry)
{
    guint8 idx = 13;

    if (vb->oid_len < idx) return -1;
    isdnBearerEntry->ifIndex = vb->oid[idx++];
    if ((isdnBearerEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_isdnBearerEntry(guint32 *base, gint32 ifIndex)
{
    guint8 idx = 13;

    base[idx++] = ifIndex;
    return idx;
}

static inline isdn_mib_isdnBearerEntry_t *
assign_isdnBearerEntry(GList *vbl)
{
    isdn_mib_isdnBearerEntry_t *isdnBearerEntry;
    char *p;

    isdnBearerEntry = isdn_mib_new_isdnBearerEntry();
    p = (char *) isdnBearerEntry + sizeof(isdn_mib_isdnBearerEntry_t);
    * (GList **) p = vbl;

    if (unpack_isdnBearerEntry((GNetSnmpVarBind *) vbl->data, isdnBearerEntry) < 0) {
        g_warning("%s: invalid instance identifier", "isdnBearerEntry");
        g_free(isdnBearerEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, isdnBearerEntry_oid, G_N_ELEMENTS(isdnBearerEntry_oid),
                      isdnBearerEntry_attr, isdnBearerEntry);

    return isdnBearerEntry;
}

void
isdn_mib_get_isdnBearerTable(GNetSnmp *s, isdn_mib_isdnBearerEntry_t ***isdnBearerEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 2, 1, 1, 0};
    guint32 base[128];

    *isdnBearerEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 13, 12, isdnBearerEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *isdnBearerEntry = (isdn_mib_isdnBearerEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(isdn_mib_isdnBearerEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*isdnBearerEntry)[i] = assign_isdnBearerEntry(row->data);
        }
    }
}

void
isdn_mib_get_isdnBearerEntry(GNetSnmp *s, isdn_mib_isdnBearerEntry_t **isdnBearerEntry, gint32 ifIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, isdnBearerEntry_oid, sizeof(isdnBearerEntry_oid));
    len = pack_isdnBearerEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBearerEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *isdnBearerEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 12, isdnBearerEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *isdnBearerEntry = assign_isdnBearerEntry(out);
    }
}

void
isdn_mib_set_isdnBearerEntry(GNetSnmp *s, isdn_mib_isdnBearerEntry_t *isdnBearerEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, isdnBearerEntry_oid, sizeof(isdnBearerEntry_oid));
    len = pack_isdnBearerEntry(base, isdnBearerEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBearerEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 12, isdnBearerEntry_attr, mask, isdnBearerEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
isdn_mib_free_isdnBearerEntry(isdn_mib_isdnBearerEntry_t *isdnBearerEntry)
{
    GList *vbl;
    char *p;

    if (isdnBearerEntry) {
        p = (char *) isdnBearerEntry + sizeof(isdn_mib_isdnBearerEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(isdnBearerEntry);
    }
}

void
isdn_mib_free_isdnBearerTable(isdn_mib_isdnBearerEntry_t **isdnBearerEntry)
{
    int i;

    if (isdnBearerEntry) {
        for (i = 0; isdnBearerEntry[i]; i++) {
            isdn_mib_free_isdnBearerEntry(isdnBearerEntry[i]);
        }
        g_free(isdnBearerEntry);
    }
}

isdn_mib_isdnEndpointEntry_t *
isdn_mib_new_isdnEndpointEntry()
{
    isdn_mib_isdnEndpointEntry_t *isdnEndpointEntry;

    isdnEndpointEntry = (isdn_mib_isdnEndpointEntry_t *) g_malloc0(sizeof(isdn_mib_isdnEndpointEntry_t) + sizeof(gpointer));
    return isdnEndpointEntry;
}

static inline int
unpack_isdnEndpointEntry(GNetSnmpVarBind *vb, isdn_mib_isdnEndpointEntry_t *isdnEndpointEntry)
{
    guint8 idx = 13;

    if (vb->oid_len < idx) return -1;
    isdnEndpointEntry->isdnEndpointIndex = vb->oid[idx++];
    if ((isdnEndpointEntry->isdnEndpointIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_isdnEndpointEntry(guint32 *base, gint32 isdnEndpointIndex)
{
    guint8 idx = 13;

    base[idx++] = isdnEndpointIndex;
    return idx;
}

static inline isdn_mib_isdnEndpointEntry_t *
assign_isdnEndpointEntry(GList *vbl)
{
    isdn_mib_isdnEndpointEntry_t *isdnEndpointEntry;
    char *p;

    isdnEndpointEntry = isdn_mib_new_isdnEndpointEntry();
    p = (char *) isdnEndpointEntry + sizeof(isdn_mib_isdnEndpointEntry_t);
    * (GList **) p = vbl;

    if (unpack_isdnEndpointEntry((GNetSnmpVarBind *) vbl->data, isdnEndpointEntry) < 0) {
        g_warning("%s: invalid instance identifier", "isdnEndpointEntry");
        g_free(isdnEndpointEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, isdnEndpointEntry_oid, G_N_ELEMENTS(isdnEndpointEntry_oid),
                      isdnEndpointEntry_attr, isdnEndpointEntry);

    return isdnEndpointEntry;
}

void
isdn_mib_get_isdnEndpointTable(GNetSnmp *s, isdn_mib_isdnEndpointEntry_t ***isdnEndpointEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 4, 2, 1, 0};
    guint32 base[128];

    *isdnEndpointEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 13, 12, isdnEndpointEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *isdnEndpointEntry = (isdn_mib_isdnEndpointEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(isdn_mib_isdnEndpointEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*isdnEndpointEntry)[i] = assign_isdnEndpointEntry(row->data);
        }
    }
}

void
isdn_mib_get_isdnEndpointEntry(GNetSnmp *s, isdn_mib_isdnEndpointEntry_t **isdnEndpointEntry, gint32 isdnEndpointIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, isdnEndpointEntry_oid, sizeof(isdnEndpointEntry_oid));
    len = pack_isdnEndpointEntry(base, isdnEndpointIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnEndpointEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *isdnEndpointEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 12, isdnEndpointEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *isdnEndpointEntry = assign_isdnEndpointEntry(out);
    }
}

void
isdn_mib_set_isdnEndpointEntry(GNetSnmp *s, isdn_mib_isdnEndpointEntry_t *isdnEndpointEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, isdnEndpointEntry_oid, sizeof(isdnEndpointEntry_oid));
    len = pack_isdnEndpointEntry(base, isdnEndpointEntry->isdnEndpointIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnEndpointEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 12, isdnEndpointEntry_attr, mask, isdnEndpointEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
isdn_mib_free_isdnEndpointEntry(isdn_mib_isdnEndpointEntry_t *isdnEndpointEntry)
{
    GList *vbl;
    char *p;

    if (isdnEndpointEntry) {
        p = (char *) isdnEndpointEntry + sizeof(isdn_mib_isdnEndpointEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(isdnEndpointEntry);
    }
}

void
isdn_mib_free_isdnEndpointTable(isdn_mib_isdnEndpointEntry_t **isdnEndpointEntry)
{
    int i;

    if (isdnEndpointEntry) {
        for (i = 0; isdnEndpointEntry[i]; i++) {
            isdn_mib_free_isdnEndpointEntry(isdnEndpointEntry[i]);
        }
        g_free(isdnEndpointEntry);
    }
}


