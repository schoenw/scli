/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3-pre1:
 *   smidump -f scli \
 *     --scli-include='rcVlanEntry|rcVlanPortEntry' RAPID-CITY
 *
 * Derived from RAPID-CITY:
 *   Enterprise MIB for the Accelar product family.
 *
 * Revision 1997-01-01 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#include "rapid-city.h"

GNetSnmpEnum const rapid_city_enums_rcVlanAction[] = {
    { RAPID_CITY_RCVLANACTION_NONE,             "none" },
    { RAPID_CITY_RCVLANACTION_FLUSHMACFDB,      "flushMacFdb" },
    { RAPID_CITY_RCVLANACTION_FLUSHARP,         "flushArp" },
    { RAPID_CITY_RCVLANACTION_FLUSHIP,          "flushIp" },
    { RAPID_CITY_RCVLANACTION_FLUSHDYNMEMB,     "flushDynMemb" },
    { RAPID_CITY_RCVLANACTION_ALL,              "all" },
    { RAPID_CITY_RCVLANACTION_FLUSHSNOOPMEMB,   "flushSnoopMemb" },
    { RAPID_CITY_RCVLANACTION_TRIGGERRIPUPDATE, "triggerRipUpdate" },
    { RAPID_CITY_RCVLANACTION_FLUSHSNOOPMRTR,   "flushSnoopMRtr" },
    { 0, NULL }
};

GNetSnmpEnum const rapid_city_enums_rcVlanResult[] = {
    { RAPID_CITY_RCVLANRESULT_NONE,       "none" },
    { RAPID_CITY_RCVLANRESULT_INPROGRESS, "inProgress" },
    { RAPID_CITY_RCVLANRESULT_SUCCESS,    "success" },
    { RAPID_CITY_RCVLANRESULT_FAIL,       "fail" },
    { 0, NULL }
};

GNetSnmpEnum const rapid_city_enums_rcVlanType[] = {
    { RAPID_CITY_RCVLANTYPE_BYPORT,       "byPort" },
    { RAPID_CITY_RCVLANTYPE_BYIPSUBNET,   "byIpSubnet" },
    { RAPID_CITY_RCVLANTYPE_BYPROTOCOLID, "byProtocolId" },
    { RAPID_CITY_RCVLANTYPE_BYSRCMAC,     "bySrcMac" },
    { RAPID_CITY_RCVLANTYPE_BYDSTMCAST,   "byDstMcast" },
    { 0, NULL }
};

GNetSnmpEnum const rapid_city_enums_rcVlanProtocolId[] = {
    { RAPID_CITY_RCVLANPROTOCOLID_NONE,         "none" },
    { RAPID_CITY_RCVLANPROTOCOLID_IP,           "ip" },
    { RAPID_CITY_RCVLANPROTOCOLID_IPX802DOT3,   "ipx802dot3" },
    { RAPID_CITY_RCVLANPROTOCOLID_IPX802DOT2,   "ipx802dot2" },
    { RAPID_CITY_RCVLANPROTOCOLID_IPXSNAP,      "ipxSnap" },
    { RAPID_CITY_RCVLANPROTOCOLID_IPXETHERNET2, "ipxEthernet2" },
    { RAPID_CITY_RCVLANPROTOCOLID_APPLETALK,    "appleTalk" },
    { RAPID_CITY_RCVLANPROTOCOLID_DECLAT,       "decLat" },
    { RAPID_CITY_RCVLANPROTOCOLID_DECOTHER,     "decOther" },
    { RAPID_CITY_RCVLANPROTOCOLID_SNA802DOT2,   "sna802dot2" },
    { RAPID_CITY_RCVLANPROTOCOLID_SNAETHERNET2, "snaEthernet2" },
    { RAPID_CITY_RCVLANPROTOCOLID_NETBIOS,      "netBios" },
    { RAPID_CITY_RCVLANPROTOCOLID_XNS,          "xns" },
    { RAPID_CITY_RCVLANPROTOCOLID_VINES,        "vines" },
    { RAPID_CITY_RCVLANPROTOCOLID_IPV6,         "ipV6" },
    { RAPID_CITY_RCVLANPROTOCOLID_USRDEFINED,   "usrDefined" },
    { RAPID_CITY_RCVLANPROTOCOLID_RARP,         "rarp" },
    { 0, NULL }
};

GNetSnmpEnum const rapid_city_enums_rcVlanPortType[] = {
    { RAPID_CITY_RCVLANPORTTYPE_ACCESS, "access" },
    { RAPID_CITY_RCVLANPORTTYPE_TRUNK,  "trunk" },
    { 0, NULL }
};


static guint16 rcVlanName_constraints[] = {0U, 20U, 0, 0};
static gint32 rcVlanColor_constraints[] = {0L, 32L, 0, 0};
static gint32 rcVlanStgId_constraints[] = {0L, 128L, 0, 0};
static guint16 rcVlanPortMembers_constraints[] = {32U, 32U, 0, 0};
static guint16 rcVlanActiveMembers_constraints[] = {32U, 32U, 0, 0};
static guint16 rcVlanStaticMembers_constraints[] = {32U, 32U, 0, 0};
static guint16 rcVlanNotAllowToJoin_constraints[] = {32U, 32U, 0, 0};
static guint16 rcVlanSubnetAddr_constraints[] = {4U, 4U, 0, 0};
static guint16 rcVlanSubnetMask_constraints[] = {4U, 4U, 0, 0};
static gint32 rcVlanAgingTime_constraints[] = {10L, 1000000L, 0, 0};
static guint16 rcVlanMacAddress_constraints[] = {6U, 6U, 0, 0};
static gint32 rcVlanIgmpSnoopRobustness_constraints[] = {2L, 255L, 0, 0};
static gint32 rcVlanIgmpSnoopQueryInterval_constraints[] = {1L, 65535L, 0, 0};
static guint16 rcVlanIgmpSnoopMRouterPorts_constraints[] = {32U, 32U, 0, 0};
static guint16 rcVlanIgmpSnoopActiveMRouterPorts_constraints[] = {32U, 32U, 0, 0};
static guint16 rcVlanIgmpSnoopActiveQuerier_constraints[] = {4U, 4U, 0, 0};
static guint16 rcVlanPortVlanIds_constraints[] = {250U, 250U, 0, 0};
static gint32 rcVlanPortDefaultVlanId_constraints[] = {1L, 4094L, 0, 0};


static guint32 const rcVlanEntry_oid[] = {1, 3, 6, 1, 4, 1, 2272, 1, 3, 2, 1};

static GNetSnmpAttribute rcVlanEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANNAME, "rcVlanName",
       rcVlanName_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanName),
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, _rcVlanNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANCOLOR, "rcVlanColor",
       rcVlanColor_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanColor),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANHIGHPRIORITY, "rcVlanHighPriority",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanHighPriority),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANROUTINGENABLE, "rcVlanRoutingEnable",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanRoutingEnable),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANIFINDEX, "rcVlanIfIndex",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIfIndex),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANACTION, "rcVlanAction",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanAction),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANRESULT, "rcVlanResult",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanResult),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANSTGID, "rcVlanStgId",
       rcVlanStgId_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanStgId),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 10, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANTYPE, "rcVlanType",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 11, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANPORTMEMBERS, "rcVlanPortMembers",
       rcVlanPortMembers_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanPortMembers),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANACTIVEMEMBERS, "rcVlanActiveMembers",
       rcVlanActiveMembers_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanActiveMembers),
      0,
      0 },
    { 13, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANSTATICMEMBERS, "rcVlanStaticMembers",
       rcVlanStaticMembers_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanStaticMembers),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 14, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANNOTALLOWTOJOIN, "rcVlanNotAllowToJoin",
       rcVlanNotAllowToJoin_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanNotAllowToJoin),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 15, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPROTOCOLID, "rcVlanProtocolId",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanProtocolId),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 16, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      RAPID_CITY_RCVLANSUBNETADDR, "rcVlanSubnetAddr",
       rcVlanSubnetAddr_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanSubnetAddr),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 17, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      RAPID_CITY_RCVLANSUBNETMASK, "rcVlanSubnetMask",
       rcVlanSubnetMask_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanSubnetMask),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 18, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANAGINGTIME, "rcVlanAgingTime",
       rcVlanAgingTime_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanAgingTime),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 19, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANMACADDRESS, "rcVlanMacAddress",
       rcVlanMacAddress_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanMacAddress),
      0,
      0 },
    { 20, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANROWSTATUS, "rcVlanRowStatus",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanRowStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 21, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANIGMPSNOOPENABLE, "rcVlanIgmpSnoopEnable",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopEnable),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 22, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANIGMPSNOOPREPORTPROXYENABLE, "rcVlanIgmpSnoopReportProxyEnable",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopReportProxyEnable),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 23, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANIGMPSNOOPROBUSTNESS, "rcVlanIgmpSnoopRobustness",
       rcVlanIgmpSnoopRobustness_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopRobustness),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 24, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANIGMPSNOOPQUERYINTERVAL, "rcVlanIgmpSnoopQueryInterval",
       rcVlanIgmpSnoopQueryInterval_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopQueryInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 25, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANIGMPSNOOPMROUTERPORTS, "rcVlanIgmpSnoopMRouterPorts",
       rcVlanIgmpSnoopMRouterPorts_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopMRouterPorts),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 26, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANUSERDEFINEDPID, "rcVlanUserDefinedPid",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanUserDefinedPid),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 27, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANIGMPSNOOPACTIVEMROUTERPORTS, "rcVlanIgmpSnoopActiveMRouterPorts",
       rcVlanIgmpSnoopActiveMRouterPorts_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopActiveMRouterPorts),
      0,
      0 },
    { 28, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPROTOCOLIDS, "rcVlanProtocolIds",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanProtocolIds),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 29, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      RAPID_CITY_RCVLANIGMPSNOOPACTIVEQUERIER, "rcVlanIgmpSnoopActiveQuerier",
       rcVlanIgmpSnoopActiveQuerier_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopActiveQuerier),
      0,
      0 },
    { 30, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANIGMPSNOOPMROUTEREXPIRATION, "rcVlanIgmpSnoopMRouterExpiration",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopMRouterExpiration),
      0,
      0 },
    { 31, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANIGMPSNOOPQUERIERPORT, "rcVlanIgmpSnoopQuerierPort",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanEntry_t, rcVlanIgmpSnoopQuerierPort),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const rcVlanPortEntry_oid[] = {1, 3, 6, 1, 4, 1, 2272, 1, 3, 3, 1};

static GNetSnmpAttribute rcVlanPortEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPORTNUMVLANIDS, "rcVlanPortNumVlanIds",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanPortEntry_t, rcVlanPortNumVlanIds),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      RAPID_CITY_RCVLANPORTVLANIDS, "rcVlanPortVlanIds",
       rcVlanPortVlanIds_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanPortEntry_t, rcVlanPortVlanIds),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPORTTYPE, "rcVlanPortType",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanPortEntry_t, rcVlanPortType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPORTDISCARDTAGGEDFRAMES, "rcVlanPortDiscardTaggedFrames",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanPortEntry_t, rcVlanPortDiscardTaggedFrames),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPORTDISCARDUNTAGGEDFRAMES, "rcVlanPortDiscardUntaggedFrames",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanPortEntry_t, rcVlanPortDiscardUntaggedFrames),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPORTDEFAULTVLANID, "rcVlanPortDefaultVlanId",
       rcVlanPortDefaultVlanId_constraints,
      G_STRUCT_OFFSET(rapid_city_rcVlanPortEntry_t, rcVlanPortDefaultVlanId),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RAPID_CITY_RCVLANPORTPERFORMTAGGING, "rcVlanPortPerformTagging",
       NULL,
      G_STRUCT_OFFSET(rapid_city_rcVlanPortEntry_t, rcVlanPortPerformTagging),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


rapid_city_rcVlanEntry_t *
rapid_city_new_rcVlanEntry()
{
    rapid_city_rcVlanEntry_t *rcVlanEntry;

    rcVlanEntry = (rapid_city_rcVlanEntry_t *) g_malloc0(sizeof(rapid_city_rcVlanEntry_t) + sizeof(gpointer));
    return rcVlanEntry;
}

static inline int
unpack_rcVlanEntry(GNetSnmpVarBind *vb, rapid_city_rcVlanEntry_t *rcVlanEntry)
{
    guint8 idx = 12;

    if (vb->oid_len < idx) return -1;
    rcVlanEntry->rcVlanId = vb->oid[idx++];
    if ((rcVlanEntry->rcVlanId < 1 || rcVlanEntry->rcVlanId > 4094)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_rcVlanEntry(guint32 *base, gint32 rcVlanId)
{
    guint8 idx = 12;

    base[idx++] = rcVlanId;
    return idx;
}

static inline rapid_city_rcVlanEntry_t *
assign_rcVlanEntry(GList *vbl)
{
    rapid_city_rcVlanEntry_t *rcVlanEntry;
    char *p;

    rcVlanEntry = rapid_city_new_rcVlanEntry();
    p = (char *) rcVlanEntry + sizeof(rapid_city_rcVlanEntry_t);
    * (GList **) p = vbl;

    if (unpack_rcVlanEntry((GNetSnmpVarBind *) vbl->data, rcVlanEntry) < 0) {
        g_warning("%s: invalid instance identifier", "rcVlanEntry");
        g_free(rcVlanEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, rcVlanEntry_oid, G_N_ELEMENTS(rcVlanEntry_oid),
                      rcVlanEntry_attr, rcVlanEntry);

    return rcVlanEntry;
}

void
rapid_city_get_rcVlanTable(GNetSnmp *s, rapid_city_rcVlanEntry_t ***rcVlanEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 2272, 1, 3, 2, 1, 0};

    *rcVlanEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 12, 11, rcVlanEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *rcVlanEntry = (rapid_city_rcVlanEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rapid_city_rcVlanEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*rcVlanEntry)[i] = assign_rcVlanEntry(row->data);
        }
    }
}

void
rapid_city_get_rcVlanEntry(GNetSnmp *s, rapid_city_rcVlanEntry_t **rcVlanEntry, gint32 rcVlanId, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rcVlanEntry_oid, sizeof(rcVlanEntry_oid));
    len = pack_rcVlanEntry(base, rcVlanId);
    if (len < 0) {
        g_warning("%s: invalid index values", "rcVlanEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *rcVlanEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, rcVlanEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *rcVlanEntry = assign_rcVlanEntry(out);
    }
}

void
rapid_city_set_rcVlanEntry(GNetSnmp *s, rapid_city_rcVlanEntry_t *rcVlanEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rcVlanEntry_oid, sizeof(rcVlanEntry_oid));
    len = pack_rcVlanEntry(base, rcVlanEntry->rcVlanId);
    if (len < 0) {
        g_warning("%s: invalid index values", "rcVlanEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 11, rcVlanEntry_attr, mask, rcVlanEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
rapid_city_free_rcVlanEntry(rapid_city_rcVlanEntry_t *rcVlanEntry)
{
    GList *vbl;
    char *p;

    if (rcVlanEntry) {
        p = (char *) rcVlanEntry + sizeof(rapid_city_rcVlanEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(rcVlanEntry);
    }
}

void
rapid_city_free_rcVlanTable(rapid_city_rcVlanEntry_t **rcVlanEntry)
{
    int i;

    if (rcVlanEntry) {
        for (i = 0; rcVlanEntry[i]; i++) {
            rapid_city_free_rcVlanEntry(rcVlanEntry[i]);
        }
        g_free(rcVlanEntry);
    }
}

rapid_city_rcVlanPortEntry_t *
rapid_city_new_rcVlanPortEntry()
{
    rapid_city_rcVlanPortEntry_t *rcVlanPortEntry;

    rcVlanPortEntry = (rapid_city_rcVlanPortEntry_t *) g_malloc0(sizeof(rapid_city_rcVlanPortEntry_t) + sizeof(gpointer));
    return rcVlanPortEntry;
}

static inline int
unpack_rcVlanPortEntry(GNetSnmpVarBind *vb, rapid_city_rcVlanPortEntry_t *rcVlanPortEntry)
{
    guint8 idx = 12;

    if (vb->oid_len < idx) return -1;
    rcVlanPortEntry->rcVlanPortIndex = vb->oid[idx++];
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_rcVlanPortEntry(guint32 *base, gint32 rcVlanPortIndex)
{
    guint8 idx = 12;

    base[idx++] = rcVlanPortIndex;
    return idx;
}

static inline rapid_city_rcVlanPortEntry_t *
assign_rcVlanPortEntry(GList *vbl)
{
    rapid_city_rcVlanPortEntry_t *rcVlanPortEntry;
    char *p;

    rcVlanPortEntry = rapid_city_new_rcVlanPortEntry();
    p = (char *) rcVlanPortEntry + sizeof(rapid_city_rcVlanPortEntry_t);
    * (GList **) p = vbl;

    if (unpack_rcVlanPortEntry((GNetSnmpVarBind *) vbl->data, rcVlanPortEntry) < 0) {
        g_warning("%s: invalid instance identifier", "rcVlanPortEntry");
        g_free(rcVlanPortEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, rcVlanPortEntry_oid, G_N_ELEMENTS(rcVlanPortEntry_oid),
                      rcVlanPortEntry_attr, rcVlanPortEntry);

    return rcVlanPortEntry;
}

void
rapid_city_get_rcVlanPortTable(GNetSnmp *s, rapid_city_rcVlanPortEntry_t ***rcVlanPortEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 2272, 1, 3, 3, 1, 0};

    *rcVlanPortEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 12, 11, rcVlanPortEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *rcVlanPortEntry = (rapid_city_rcVlanPortEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rapid_city_rcVlanPortEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*rcVlanPortEntry)[i] = assign_rcVlanPortEntry(row->data);
        }
    }
}

void
rapid_city_get_rcVlanPortEntry(GNetSnmp *s, rapid_city_rcVlanPortEntry_t **rcVlanPortEntry, gint32 rcVlanPortIndex, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rcVlanPortEntry_oid, sizeof(rcVlanPortEntry_oid));
    len = pack_rcVlanPortEntry(base, rcVlanPortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rcVlanPortEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *rcVlanPortEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, rcVlanPortEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *rcVlanPortEntry = assign_rcVlanPortEntry(out);
    }
}

void
rapid_city_set_rcVlanPortEntry(GNetSnmp *s, rapid_city_rcVlanPortEntry_t *rcVlanPortEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rcVlanPortEntry_oid, sizeof(rcVlanPortEntry_oid));
    len = pack_rcVlanPortEntry(base, rcVlanPortEntry->rcVlanPortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rcVlanPortEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 11, rcVlanPortEntry_attr, mask, rcVlanPortEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
rapid_city_free_rcVlanPortEntry(rapid_city_rcVlanPortEntry_t *rcVlanPortEntry)
{
    GList *vbl;
    char *p;

    if (rcVlanPortEntry) {
        p = (char *) rcVlanPortEntry + sizeof(rapid_city_rcVlanPortEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(rcVlanPortEntry);
    }
}

void
rapid_city_free_rcVlanPortTable(rapid_city_rcVlanPortEntry_t **rcVlanPortEntry)
{
    int i;

    if (rcVlanPortEntry) {
        for (i = 0; rcVlanPortEntry[i]; i++) {
            rapid_city_free_rcVlanPortEntry(rcVlanPortEntry[i]);
        }
        g_free(rcVlanPortEntry);
    }
}


