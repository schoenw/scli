/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Options:
 *   --scli-include='isdnBasicRateEntry|isdnBearerEntry'
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

GSnmpEnum const isdn_mib_enums_isdnBasicRateIfType[] = {
    { ISDN_MIB_ISDNBASICRATEIFTYPE_ISDNS, "isdns" },
    { ISDN_MIB_ISDNBASICRATEIFTYPE_ISDNU, "isdnu" },
    { 0, NULL }
};

GSnmpEnum const isdn_mib_enums_isdnBasicRateLineTopology[] = {
    { ISDN_MIB_ISDNBASICRATELINETOPOLOGY_POINTTOPOINT,      "pointToPoint" },
    { ISDN_MIB_ISDNBASICRATELINETOPOLOGY_POINTTOMULTIPOINT, "pointToMultipoint" },
    { 0, NULL }
};

GSnmpEnum const isdn_mib_enums_isdnBasicRateIfMode[] = {
    { ISDN_MIB_ISDNBASICRATEIFMODE_TE, "te" },
    { ISDN_MIB_ISDNBASICRATEIFMODE_NT, "nt" },
    { 0, NULL }
};

GSnmpEnum const isdn_mib_enums_isdnBasicRateSignalMode[] = {
    { ISDN_MIB_ISDNBASICRATESIGNALMODE_ACTIVE,   "active" },
    { ISDN_MIB_ISDNBASICRATESIGNALMODE_INACTIVE, "inactive" },
    { 0, NULL }
};

GSnmpEnum const isdn_mib_enums_isdnBearerChannelType[] = {
    { ISDN_MIB_ISDNBEARERCHANNELTYPE_DIALUP, "dialup" },
    { ISDN_MIB_ISDNBEARERCHANNELTYPE_LEASED, "leased" },
    { 0, NULL }
};

GSnmpEnum const isdn_mib_enums_isdnBearerOperStatus[] = {
    { ISDN_MIB_ISDNBEAREROPERSTATUS_IDLE,       "idle" },
    { ISDN_MIB_ISDNBEAREROPERSTATUS_CONNECTING, "connecting" },
    { ISDN_MIB_ISDNBEAREROPERSTATUS_CONNECTED,  "connected" },
    { ISDN_MIB_ISDNBEAREROPERSTATUS_ACTIVE,     "active" },
    { 0, NULL }
};

GSnmpEnum const isdn_mib_enums_isdnBearerCallOrigin[] = {
    { ISDN_MIB_ISDNBEARERCALLORIGIN_UNKNOWN,   "unknown" },
    { ISDN_MIB_ISDNBEARERCALLORIGIN_ORIGINATE, "originate" },
    { ISDN_MIB_ISDNBEARERCALLORIGIN_ANSWER,    "answer" },
    { ISDN_MIB_ISDNBEARERCALLORIGIN_CALLBACK,  "callback" },
    { 0, NULL }
};

GSnmpEnum const isdn_mib_enums_isdnBearerInfoType[] = {
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

GSnmpEnum const isdn_mib_enums_isdnBearerMultirate[] = {
    { ISDN_MIB_ISDNBEARERMULTIRATE_TRUE,  "true" },
    { ISDN_MIB_ISDNBEARERMULTIRATE_FALSE, "false" },
    { 0, NULL }
};


static guint32 isdnBearerChannelNumber_constraints[] = {1L, 30L, 0, 0};
static guint16 isdnBearerPeerAddress_constraints[] = {0, 255, 0, 0};
static guint16 isdnBearerPeerSubAddress_constraints[] = {0, 255, 0, 0};


static guint32 const isdnBasicRateEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 1, 1, 1};

static GSnmpAttribute isdnBasicRateEntry_attr[] = {
    { 1, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBASICRATEIFTYPE, "isdnBasicRateIfType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateIfType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBASICRATELINETOPOLOGY, "isdnBasicRateLineTopology",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateLineTopology),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBASICRATEIFMODE, "isdnBasicRateIfMode",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateIfMode),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBASICRATESIGNALMODE, "isdnBasicRateSignalMode",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBasicRateEntry_t, isdnBasicRateSignalMode),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const isdnBearerEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 2, 1, 1};

static GSnmpAttribute isdnBearerEntry_attr[] = {
    { 1, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBEARERCHANNELTYPE, "isdnBearerChannelType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerChannelType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBEAREROPERSTATUS, "isdnBearerOperStatus",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerOperStatus),
      0,
      0 },
    { 3, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBEARERCHANNELNUMBER, "isdnBearerChannelNumber",
       isdnBearerChannelNumber_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerChannelNumber),
      0,
      0 },
    { 4, G_SNMP_OCTETSTRING,
      ISDN_MIB_ISDNBEARERPEERADDRESS, "isdnBearerPeerAddress",
       isdnBearerPeerAddress_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerPeerAddress),
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, _isdnBearerPeerAddressLength),
      0 },
    { 5, G_SNMP_OCTETSTRING,
      ISDN_MIB_ISDNBEARERPEERSUBADDRESS, "isdnBearerPeerSubAddress",
       isdnBearerPeerSubAddress_constraints,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerPeerSubAddress),
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, _isdnBearerPeerSubAddressLength),
      0 },
    { 6, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBEARERCALLORIGIN, "isdnBearerCallOrigin",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerCallOrigin),
      0,
      0 },
    { 7, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBEARERINFOTYPE, "isdnBearerInfoType",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerInfoType),
      0,
      0 },
    { 8, G_SNMP_INTEGER32,
      ISDN_MIB_ISDNBEARERMULTIRATE, "isdnBearerMultirate",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerMultirate),
      0,
      0 },
    { 9, G_SNMP_TIMETICKS,
      ISDN_MIB_ISDNBEARERCALLSETUPTIME, "isdnBearerCallSetupTime",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerCallSetupTime),
      0,
      0 },
    { 10, G_SNMP_TIMETICKS,
      ISDN_MIB_ISDNBEARERCALLCONNECTTIME, "isdnBearerCallConnectTime",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerCallConnectTime),
      0,
      0 },
    { 11, G_SNMP_UNSIGNED32,
      ISDN_MIB_ISDNBEARERCHARGEDUNITS, "isdnBearerChargedUnits",
       NULL,
      G_STRUCT_OFFSET(isdn_mib_isdnBearerEntry_t, isdnBearerChargedUnits),
      0,
      0 },
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
unpack_isdnBasicRateEntry(GSnmpVarBind *vb, isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry)
{
    guint8 idx = 13;

    if (vb->id_len < idx) return -1;
    isdnBasicRateEntry->ifIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
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
assign_isdnBasicRateEntry(GSList *vbl)
{
    isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry;
    char *p;

    isdnBasicRateEntry = isdn_mib_new_isdnBasicRateEntry();
    if (! isdnBasicRateEntry) {
        return NULL;
    }

    p = (char *) isdnBasicRateEntry + sizeof(isdn_mib_isdnBasicRateEntry_t);
    * (GSList **) p = vbl;

    if (unpack_isdnBasicRateEntry((GSnmpVarBind *) vbl->data, isdnBasicRateEntry) < 0) {
        g_warning("%s: invalid instance identifier", "isdnBasicRateEntry");
        g_free(isdnBasicRateEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, isdnBasicRateEntry_oid, sizeof(isdnBasicRateEntry_oid)/sizeof(guint32),
                      isdnBasicRateEntry_attr, isdnBasicRateEntry);

    return isdnBasicRateEntry;
}

void
isdn_mib_get_isdnBasicRateTable(GSnmpSession *s, isdn_mib_isdnBasicRateEntry_t ***isdnBasicRateEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 1, 1, 1, 0};

    *isdnBasicRateEntry = NULL;

    gsnmp_attr_get(s, &in, base, 13, 12, isdnBasicRateEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *isdnBasicRateEntry = (isdn_mib_isdnBasicRateEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(isdn_mib_isdnBasicRateEntry_t *));
        if (! *isdnBasicRateEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*isdnBasicRateEntry)[i] = assign_isdnBasicRateEntry(row->data);
        }
    }
}

void
isdn_mib_get_isdnBasicRateEntry(GSnmpSession *s, isdn_mib_isdnBasicRateEntry_t **isdnBasicRateEntry, gint32 ifIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, isdnBasicRateEntry_oid, sizeof(isdnBasicRateEntry_oid));
    len = pack_isdnBasicRateEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBasicRateEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *isdnBasicRateEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 12, isdnBasicRateEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *isdnBasicRateEntry = assign_isdnBasicRateEntry(out);
    }
}

void
isdn_mib_set_isdnBasicRateEntry(GSnmpSession *s, isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, isdnBasicRateEntry_oid, sizeof(isdnBasicRateEntry_oid));
    len = pack_isdnBasicRateEntry(base, isdnBasicRateEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBasicRateEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 12, isdnBasicRateEntry_attr, mask, isdnBasicRateEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
isdn_mib_free_isdnBasicRateEntry(isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry)
{
    GSList *vbl;
    char *p;

    if (isdnBasicRateEntry) {
        p = (char *) isdnBasicRateEntry + sizeof(isdn_mib_isdnBasicRateEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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

void
isdn_mib_set_isdnBasicRateIfType(GSnmpSession *s, gint32 ifIndex, gint32 isdnBasicRateIfType)
{
    isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry;

    isdn_mib_get_isdnBasicRateEntry(s, &isdnBasicRateEntry, ifIndex, ISDN_MIB_ISDNBASICRATEIFTYPE);
    if (s->error_status || !isdnBasicRateEntry) return;
    isdnBasicRateEntry->isdnBasicRateIfType = &isdnBasicRateIfType;
    isdn_mib_set_isdnBasicRateEntry(s, isdnBasicRateEntry, ISDN_MIB_ISDNBASICRATEIFTYPE);
    isdn_mib_free_isdnBasicRateEntry(isdnBasicRateEntry);
}

void
isdn_mib_set_isdnBasicRateLineTopology(GSnmpSession *s, gint32 ifIndex, gint32 isdnBasicRateLineTopology)
{
    isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry;

    isdn_mib_get_isdnBasicRateEntry(s, &isdnBasicRateEntry, ifIndex, ISDN_MIB_ISDNBASICRATELINETOPOLOGY);
    if (s->error_status || !isdnBasicRateEntry) return;
    isdnBasicRateEntry->isdnBasicRateLineTopology = &isdnBasicRateLineTopology;
    isdn_mib_set_isdnBasicRateEntry(s, isdnBasicRateEntry, ISDN_MIB_ISDNBASICRATELINETOPOLOGY);
    isdn_mib_free_isdnBasicRateEntry(isdnBasicRateEntry);
}

void
isdn_mib_set_isdnBasicRateIfMode(GSnmpSession *s, gint32 ifIndex, gint32 isdnBasicRateIfMode)
{
    isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry;

    isdn_mib_get_isdnBasicRateEntry(s, &isdnBasicRateEntry, ifIndex, ISDN_MIB_ISDNBASICRATEIFMODE);
    if (s->error_status || !isdnBasicRateEntry) return;
    isdnBasicRateEntry->isdnBasicRateIfMode = &isdnBasicRateIfMode;
    isdn_mib_set_isdnBasicRateEntry(s, isdnBasicRateEntry, ISDN_MIB_ISDNBASICRATEIFMODE);
    isdn_mib_free_isdnBasicRateEntry(isdnBasicRateEntry);
}

void
isdn_mib_set_isdnBasicRateSignalMode(GSnmpSession *s, gint32 ifIndex, gint32 isdnBasicRateSignalMode)
{
    isdn_mib_isdnBasicRateEntry_t *isdnBasicRateEntry;

    isdn_mib_get_isdnBasicRateEntry(s, &isdnBasicRateEntry, ifIndex, ISDN_MIB_ISDNBASICRATESIGNALMODE);
    if (s->error_status || !isdnBasicRateEntry) return;
    isdnBasicRateEntry->isdnBasicRateSignalMode = &isdnBasicRateSignalMode;
    isdn_mib_set_isdnBasicRateEntry(s, isdnBasicRateEntry, ISDN_MIB_ISDNBASICRATESIGNALMODE);
    isdn_mib_free_isdnBasicRateEntry(isdnBasicRateEntry);
}

isdn_mib_isdnBearerEntry_t *
isdn_mib_new_isdnBearerEntry()
{
    isdn_mib_isdnBearerEntry_t *isdnBearerEntry;

    isdnBearerEntry = (isdn_mib_isdnBearerEntry_t *) g_malloc0(sizeof(isdn_mib_isdnBearerEntry_t) + sizeof(gpointer));
    return isdnBearerEntry;
}

static inline int
unpack_isdnBearerEntry(GSnmpVarBind *vb, isdn_mib_isdnBearerEntry_t *isdnBearerEntry)
{
    guint8 idx = 13;

    if (vb->id_len < idx) return -1;
    isdnBearerEntry->ifIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
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
assign_isdnBearerEntry(GSList *vbl)
{
    isdn_mib_isdnBearerEntry_t *isdnBearerEntry;
    char *p;

    isdnBearerEntry = isdn_mib_new_isdnBearerEntry();
    if (! isdnBearerEntry) {
        return NULL;
    }

    p = (char *) isdnBearerEntry + sizeof(isdn_mib_isdnBearerEntry_t);
    * (GSList **) p = vbl;

    if (unpack_isdnBearerEntry((GSnmpVarBind *) vbl->data, isdnBearerEntry) < 0) {
        g_warning("%s: invalid instance identifier", "isdnBearerEntry");
        g_free(isdnBearerEntry);
        return NULL;
    }

    gsnmp_attr_assign(vbl, isdnBearerEntry_oid, sizeof(isdnBearerEntry_oid)/sizeof(guint32),
                      isdnBearerEntry_attr, isdnBearerEntry);

    return isdnBearerEntry;
}

void
isdn_mib_get_isdnBearerTable(GSnmpSession *s, isdn_mib_isdnBearerEntry_t ***isdnBearerEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 20, 1, 2, 1, 1, 0};

    *isdnBearerEntry = NULL;

    gsnmp_attr_get(s, &in, base, 13, 12, isdnBearerEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *isdnBearerEntry = (isdn_mib_isdnBearerEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(isdn_mib_isdnBearerEntry_t *));
        if (! *isdnBearerEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*isdnBearerEntry)[i] = assign_isdnBearerEntry(row->data);
        }
    }
}

void
isdn_mib_get_isdnBearerEntry(GSnmpSession *s, isdn_mib_isdnBearerEntry_t **isdnBearerEntry, gint32 ifIndex, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, isdnBearerEntry_oid, sizeof(isdnBearerEntry_oid));
    len = pack_isdnBearerEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBearerEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    *isdnBearerEntry = NULL;

    gsnmp_attr_get(s, &in, base, len, 12, isdnBearerEntry_attr, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        if (s->error_status != G_SNMP_ERR_NOERROR) {
            g_snmp_vbl_free(out);
            return;
        }
        *isdnBearerEntry = assign_isdnBearerEntry(out);
    }
}

void
isdn_mib_set_isdnBearerEntry(GSnmpSession *s, isdn_mib_isdnBearerEntry_t *isdnBearerEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memset(base, 0, sizeof(base));
    memcpy(base, isdnBearerEntry_oid, sizeof(isdnBearerEntry_oid));
    len = pack_isdnBearerEntry(base, isdnBearerEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "isdnBearerEntry");
        s->error_status = G_SNMP_ERR_INTERNAL;
        return;
    }

    gsnmp_attr_set(s, &in, base, len, 12, isdnBearerEntry_attr, mask, isdnBearerEntry);

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
isdn_mib_free_isdnBearerEntry(isdn_mib_isdnBearerEntry_t *isdnBearerEntry)
{
    GSList *vbl;
    char *p;

    if (isdnBearerEntry) {
        p = (char *) isdnBearerEntry + sizeof(isdn_mib_isdnBearerEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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

void
isdn_mib_set_isdnBearerChannelType(GSnmpSession *s, gint32 ifIndex, gint32 isdnBearerChannelType)
{
    isdn_mib_isdnBearerEntry_t *isdnBearerEntry;

    isdn_mib_get_isdnBearerEntry(s, &isdnBearerEntry, ifIndex, ISDN_MIB_ISDNBEARERCHANNELTYPE);
    if (s->error_status || !isdnBearerEntry) return;
    isdnBearerEntry->isdnBearerChannelType = &isdnBearerChannelType;
    isdn_mib_set_isdnBearerEntry(s, isdnBearerEntry, ISDN_MIB_ISDNBEARERCHANNELTYPE);
    isdn_mib_free_isdnBearerEntry(isdnBearerEntry);
}


