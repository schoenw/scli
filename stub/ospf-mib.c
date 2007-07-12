/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli \
 *     --scli-include='ospfGeneralGroup|ospfAreaEntry|ospfIfEntry|ospfLsdbEntry' OSPF-MIB
 *
 * Derived from OSPF-MIB:
 *   The MIB module to describe the OSPF Version 2
 *   Protocol
 *
 * Revision 1995-01-20 12:25:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#include "ospf-mib.h"

GNetSnmpEnum const ospf_mib_enums_ospfVersionNumber[] = {
    { OSPF_MIB_OSPFVERSIONNUMBER_VERSION2, "version2" },
    { 0, NULL }
};

GNetSnmpEnum const ospf_mib_enums_ospfImportAsExtern[] = {
    { OSPF_MIB_OSPFIMPORTASEXTERN_IMPORTEXTERNAL,   "importExternal" },
    { OSPF_MIB_OSPFIMPORTASEXTERN_IMPORTNOEXTERNAL, "importNoExternal" },
    { OSPF_MIB_OSPFIMPORTASEXTERN_IMPORTNSSA,       "importNssa" },
    { 0, NULL }
};

GNetSnmpEnum const ospf_mib_enums_ospfAreaSummary[] = {
    { OSPF_MIB_OSPFAREASUMMARY_NOAREASUMMARY,   "noAreaSummary" },
    { OSPF_MIB_OSPFAREASUMMARY_SENDAREASUMMARY, "sendAreaSummary" },
    { 0, NULL }
};

GNetSnmpEnum const ospf_mib_enums_ospfLsdbType[] = {
    { OSPF_MIB_OSPFLSDBTYPE_ROUTERLINK,       "routerLink" },
    { OSPF_MIB_OSPFLSDBTYPE_NETWORKLINK,      "networkLink" },
    { OSPF_MIB_OSPFLSDBTYPE_SUMMARYLINK,      "summaryLink" },
    { OSPF_MIB_OSPFLSDBTYPE_ASSUMMARYLINK,    "asSummaryLink" },
    { OSPF_MIB_OSPFLSDBTYPE_ASEXTERNALLINK,   "asExternalLink" },
    { OSPF_MIB_OSPFLSDBTYPE_MULTICASTLINK,    "multicastLink" },
    { OSPF_MIB_OSPFLSDBTYPE_NSSAEXTERNALLINK, "nssaExternalLink" },
    { 0, NULL }
};

GNetSnmpEnum const ospf_mib_enums_ospfIfType[] = {
    { OSPF_MIB_OSPFIFTYPE_BROADCAST,         "broadcast" },
    { OSPF_MIB_OSPFIFTYPE_NBMA,              "nbma" },
    { OSPF_MIB_OSPFIFTYPE_POINTTOPOINT,      "pointToPoint" },
    { OSPF_MIB_OSPFIFTYPE_POINTTOMULTIPOINT, "pointToMultipoint" },
    { 0, NULL }
};

GNetSnmpEnum const ospf_mib_enums_ospfIfState[] = {
    { OSPF_MIB_OSPFIFSTATE_DOWN,                   "down" },
    { OSPF_MIB_OSPFIFSTATE_LOOPBACK,               "loopback" },
    { OSPF_MIB_OSPFIFSTATE_WAITING,                "waiting" },
    { OSPF_MIB_OSPFIFSTATE_POINTTOPOINT,           "pointToPoint" },
    { OSPF_MIB_OSPFIFSTATE_DESIGNATEDROUTER,       "designatedRouter" },
    { OSPF_MIB_OSPFIFSTATE_BACKUPDESIGNATEDROUTER, "backupDesignatedRouter" },
    { OSPF_MIB_OSPFIFSTATE_OTHERDESIGNATEDROUTER,  "otherDesignatedRouter" },
    { 0, NULL }
};

GNetSnmpEnum const ospf_mib_enums_ospfIfMulticastForwarding[] = {
    { OSPF_MIB_OSPFIFMULTICASTFORWARDING_BLOCKED,   "blocked" },
    { OSPF_MIB_OSPFIFMULTICASTFORWARDING_MULTICAST, "multicast" },
    { OSPF_MIB_OSPFIFMULTICASTFORWARDING_UNICAST,   "unicast" },
    { 0, NULL }
};

GNetSnmpEnum const ospf_mib_enums_Status[] = {
    { OSPF_MIB_STATUS_ENABLED,  "enabled" },
    { OSPF_MIB_STATUS_DISABLED, "disabled" },
    { 0, NULL }
};


static guint16 ospfRouterId_constraints[] = {4U, 4U, 0, 0};
static gint32 ospfExtLsdbLimit_constraints[] = {-1L, 2147483647L, 0, 0};
static gint32 ospfExitOverflowInterval_constraints[] = {0L, 2147483647L, 0, 0};
static guint16 ospfLsdbAdvertisement_constraints[] = {1U, 65535U, 0, 0};
static guint16 ospfIfAreaId_constraints[] = {4U, 4U, 0, 0};
static gint32 ospfIfRtrPriority_constraints[] = {0L, 255L, 0, 0};
static gint32 ospfIfTransitDelay_constraints[] = {0L, 3600L, 0, 0};
static gint32 ospfIfRetransInterval_constraints[] = {0L, 3600L, 0, 0};
static gint32 ospfIfHelloInterval_constraints[] = {1L, 65535L, 0, 0};
static gint32 ospfIfRtrDeadInterval_constraints[] = {0L, 2147483647L, 0, 0};
static gint32 ospfIfPollInterval_constraints[] = {0L, 2147483647L, 0, 0};
static guint16 ospfIfDesignatedRouter_constraints[] = {4U, 4U, 0, 0};
static guint16 ospfIfBackupDesignatedRouter_constraints[] = {4U, 4U, 0, 0};
static guint16 ospfIfAuthKey_constraints[] = {0U, 256U, 0, 0};
static gint32 ospfIfAuthType_constraints[] = {0L, 255L, 0, 0};


static guint32 const ospfGeneralGroup_oid[] = {1, 3, 6, 1, 2, 1, 14, 1};

static GNetSnmpAttribute ospfGeneralGroup_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      OSPF_MIB_OSPFROUTERID, "ospfRouterId",
       ospfRouterId_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfRouterId),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFADMINSTAT, "ospfAdminStat",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfAdminStat),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFVERSIONNUMBER, "ospfVersionNumber",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfVersionNumber),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFAREABDRRTRSTATUS, "ospfAreaBdrRtrStatus",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfAreaBdrRtrStatus),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFASBDRRTRSTATUS, "ospfASBdrRtrStatus",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfASBdrRtrStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      OSPF_MIB_OSPFEXTERNLSACOUNT, "ospfExternLsaCount",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfExternLsaCount),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFEXTERNLSACKSUMSUM, "ospfExternLsaCksumSum",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfExternLsaCksumSum),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFTOSSUPPORT, "ospfTOSSupport",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfTOSSupport),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      OSPF_MIB_OSPFORIGINATENEWLSAS, "ospfOriginateNewLsas",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfOriginateNewLsas),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      OSPF_MIB_OSPFRXNEWLSAS, "ospfRxNewLsas",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfRxNewLsas),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFEXTLSDBLIMIT, "ospfExtLsdbLimit",
       ospfExtLsdbLimit_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfExtLsdbLimit),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFMULTICASTEXTENSIONS, "ospfMulticastExtensions",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfMulticastExtensions),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 13, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFEXITOVERFLOWINTERVAL, "ospfExitOverflowInterval",
       ospfExitOverflowInterval_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfExitOverflowInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 14, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFDEMANDEXTENSIONS, "ospfDemandExtensions",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfGeneralGroup_t, ospfDemandExtensions),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const ospfAreaEntry_oid[] = {1, 3, 6, 1, 2, 1, 14, 2, 1};

static GNetSnmpAttribute ospfAreaEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFAUTHTYPE, "ospfAuthType",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfAuthType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIMPORTASEXTERN, "ospfImportAsExtern",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfImportAsExtern),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      OSPF_MIB_OSPFSPFRUNS, "ospfSpfRuns",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfSpfRuns),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      OSPF_MIB_OSPFAREABDRRTRCOUNT, "ospfAreaBdrRtrCount",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfAreaBdrRtrCount),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      OSPF_MIB_OSPFASBDRRTRCOUNT, "ospfAsBdrRtrCount",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfAsBdrRtrCount),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      OSPF_MIB_OSPFAREALSACOUNT, "ospfAreaLsaCount",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfAreaLsaCount),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFAREALSACKSUMSUM, "ospfAreaLsaCksumSum",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfAreaLsaCksumSum),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFAREASUMMARY, "ospfAreaSummary",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfAreaSummary),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 10, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFAREASTATUS, "ospfAreaStatus",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfAreaEntry_t, ospfAreaStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const ospfLsdbEntry_oid[] = {1, 3, 6, 1, 2, 1, 14, 4, 1};

static GNetSnmpAttribute ospfLsdbEntry_attr[] = {
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFLSDBSEQUENCE, "ospfLsdbSequence",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfLsdbEntry_t, ospfLsdbSequence),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFLSDBAGE, "ospfLsdbAge",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfLsdbEntry_t, ospfLsdbAge),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFLSDBCHECKSUM, "ospfLsdbChecksum",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfLsdbEntry_t, ospfLsdbChecksum),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      OSPF_MIB_OSPFLSDBADVERTISEMENT, "ospfLsdbAdvertisement",
       ospfLsdbAdvertisement_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfLsdbEntry_t, ospfLsdbAdvertisement),
      G_STRUCT_OFFSET(ospf_mib_ospfLsdbEntry_t, _ospfLsdbAdvertisementLength),
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const ospfIfEntry_oid[] = {1, 3, 6, 1, 2, 1, 14, 7, 1};

static GNetSnmpAttribute ospfIfEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      OSPF_MIB_OSPFIFAREAID, "ospfIfAreaId",
       ospfIfAreaId_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfAreaId),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFTYPE, "ospfIfType",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFADMINSTAT, "ospfIfAdminStat",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfAdminStat),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFRTRPRIORITY, "ospfIfRtrPriority",
       ospfIfRtrPriority_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfRtrPriority),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFTRANSITDELAY, "ospfIfTransitDelay",
       ospfIfTransitDelay_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfTransitDelay),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFRETRANSINTERVAL, "ospfIfRetransInterval",
       ospfIfRetransInterval_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfRetransInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFHELLOINTERVAL, "ospfIfHelloInterval",
       ospfIfHelloInterval_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfHelloInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 10, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFRTRDEADINTERVAL, "ospfIfRtrDeadInterval",
       ospfIfRtrDeadInterval_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfRtrDeadInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 11, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFPOLLINTERVAL, "ospfIfPollInterval",
       ospfIfPollInterval_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfPollInterval),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFSTATE, "ospfIfState",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfState),
      0,
      0 },
    { 13, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      OSPF_MIB_OSPFIFDESIGNATEDROUTER, "ospfIfDesignatedRouter",
       ospfIfDesignatedRouter_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfDesignatedRouter),
      0,
      0 },
    { 14, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      OSPF_MIB_OSPFIFBACKUPDESIGNATEDROUTER, "ospfIfBackupDesignatedRouter",
       ospfIfBackupDesignatedRouter_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfBackupDesignatedRouter),
      0,
      0 },
    { 15, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      OSPF_MIB_OSPFIFEVENTS, "ospfIfEvents",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfEvents),
      0,
      0 },
    { 16, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      OSPF_MIB_OSPFIFAUTHKEY, "ospfIfAuthKey",
       ospfIfAuthKey_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfAuthKey),
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, _ospfIfAuthKeyLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 17, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFSTATUS, "ospfIfStatus",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 18, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFMULTICASTFORWARDING, "ospfIfMulticastForwarding",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfMulticastForwarding),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 19, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFDEMAND, "ospfIfDemand",
       NULL,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfDemand),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 20, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      OSPF_MIB_OSPFIFAUTHTYPE, "ospfIfAuthType",
       ospfIfAuthType_constraints,
      G_STRUCT_OFFSET(ospf_mib_ospfIfEntry_t, ospfIfAuthType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


ospf_mib_ospfGeneralGroup_t *
ospf_mib_new_ospfGeneralGroup()
{
    ospf_mib_ospfGeneralGroup_t *ospfGeneralGroup;

    ospfGeneralGroup = (ospf_mib_ospfGeneralGroup_t *) g_malloc0(sizeof(ospf_mib_ospfGeneralGroup_t) + sizeof(gpointer));
    return ospfGeneralGroup;
}

static inline ospf_mib_ospfGeneralGroup_t *
assign_ospfGeneralGroup(GList *vbl)
{
    ospf_mib_ospfGeneralGroup_t *ospfGeneralGroup;
    char *p;

    ospfGeneralGroup = ospf_mib_new_ospfGeneralGroup();
    p = (char *) ospfGeneralGroup + sizeof(ospf_mib_ospfGeneralGroup_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, ospfGeneralGroup_oid, G_N_ELEMENTS(ospfGeneralGroup_oid),
                      ospfGeneralGroup_attr, ospfGeneralGroup);

    return ospfGeneralGroup;
}

void
ospf_mib_get_ospfGeneralGroup(GNetSnmp *s, ospf_mib_ospfGeneralGroup_t **ospfGeneralGroup, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static const guint32 _base[] = {1, 3, 6, 1, 2, 1, 14, 1, 0};
    guint32 base[128];

    *ospfGeneralGroup = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 9, 8, ospfGeneralGroup_attr, mask);

    out = gnet_snmp_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ospfGeneralGroup = assign_ospfGeneralGroup(out);
    }
}

void
ospf_mib_set_ospfGeneralGroup(GNetSnmp *s, ospf_mib_ospfGeneralGroup_t *ospfGeneralGroup, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 14, 1, 0, 0};

    gnet_snmp_attr_set(s, &in, base, 10, 8, ospfGeneralGroup_attr, mask, ospfGeneralGroup);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
ospf_mib_free_ospfGeneralGroup(ospf_mib_ospfGeneralGroup_t *ospfGeneralGroup)
{
    GList *vbl;
    char *p;

    if (ospfGeneralGroup) {
        p = (char *) ospfGeneralGroup + sizeof(ospf_mib_ospfGeneralGroup_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ospfGeneralGroup);
    }
}

ospf_mib_ospfAreaEntry_t *
ospf_mib_new_ospfAreaEntry()
{
    ospf_mib_ospfAreaEntry_t *ospfAreaEntry;

    ospfAreaEntry = (ospf_mib_ospfAreaEntry_t *) g_malloc0(sizeof(ospf_mib_ospfAreaEntry_t) + sizeof(gpointer));
    return ospfAreaEntry;
}

static inline int
unpack_ospfAreaEntry(GNetSnmpVarBind *vb, ospf_mib_ospfAreaEntry_t *ospfAreaEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ospfAreaEntry->ospfAreaId[i] = vb->oid[idx++];
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ospfAreaEntry(guint32 *base, guchar *ospfAreaId)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ospfAreaId[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline ospf_mib_ospfAreaEntry_t *
assign_ospfAreaEntry(GList *vbl)
{
    ospf_mib_ospfAreaEntry_t *ospfAreaEntry;
    char *p;

    ospfAreaEntry = ospf_mib_new_ospfAreaEntry();
    p = (char *) ospfAreaEntry + sizeof(ospf_mib_ospfAreaEntry_t);
    * (GList **) p = vbl;

    if (unpack_ospfAreaEntry((GNetSnmpVarBind *) vbl->data, ospfAreaEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ospfAreaEntry");
        g_free(ospfAreaEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ospfAreaEntry_oid, G_N_ELEMENTS(ospfAreaEntry_oid),
                      ospfAreaEntry_attr, ospfAreaEntry);

    return ospfAreaEntry;
}

void
ospf_mib_get_ospfAreaTable(GNetSnmp *s, ospf_mib_ospfAreaEntry_t ***ospfAreaEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 14, 2, 1, 0};
    guint32 base[128];

    *ospfAreaEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 10, 9, ospfAreaEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ospfAreaEntry = (ospf_mib_ospfAreaEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(ospf_mib_ospfAreaEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ospfAreaEntry)[i] = assign_ospfAreaEntry(row->data);
        }
    }
}

void
ospf_mib_get_ospfAreaEntry(GNetSnmp *s, ospf_mib_ospfAreaEntry_t **ospfAreaEntry, guchar *ospfAreaId, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ospfAreaEntry_oid, sizeof(ospfAreaEntry_oid));
    len = pack_ospfAreaEntry(base, ospfAreaId);
    if (len < 0) {
        g_warning("%s: invalid index values", "ospfAreaEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ospfAreaEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, ospfAreaEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ospfAreaEntry = assign_ospfAreaEntry(out);
    }
}

void
ospf_mib_set_ospfAreaEntry(GNetSnmp *s, ospf_mib_ospfAreaEntry_t *ospfAreaEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ospfAreaEntry_oid, sizeof(ospfAreaEntry_oid));
    len = pack_ospfAreaEntry(base, ospfAreaEntry->ospfAreaId);
    if (len < 0) {
        g_warning("%s: invalid index values", "ospfAreaEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 9, ospfAreaEntry_attr, mask, ospfAreaEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
ospf_mib_free_ospfAreaEntry(ospf_mib_ospfAreaEntry_t *ospfAreaEntry)
{
    GList *vbl;
    char *p;

    if (ospfAreaEntry) {
        p = (char *) ospfAreaEntry + sizeof(ospf_mib_ospfAreaEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ospfAreaEntry);
    }
}

void
ospf_mib_free_ospfAreaTable(ospf_mib_ospfAreaEntry_t **ospfAreaEntry)
{
    int i;

    if (ospfAreaEntry) {
        for (i = 0; ospfAreaEntry[i]; i++) {
            ospf_mib_free_ospfAreaEntry(ospfAreaEntry[i]);
        }
        g_free(ospfAreaEntry);
    }
}

ospf_mib_ospfLsdbEntry_t *
ospf_mib_new_ospfLsdbEntry()
{
    ospf_mib_ospfLsdbEntry_t *ospfLsdbEntry;

    ospfLsdbEntry = (ospf_mib_ospfLsdbEntry_t *) g_malloc0(sizeof(ospf_mib_ospfLsdbEntry_t) + sizeof(gpointer));
    return ospfLsdbEntry;
}

static inline int
unpack_ospfLsdbEntry(GNetSnmpVarBind *vb, ospf_mib_ospfLsdbEntry_t *ospfLsdbEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ospfLsdbEntry->ospfLsdbAreaId[i] = vb->oid[idx++];
    }
    if (vb->oid_len < idx) return -1;
    ospfLsdbEntry->ospfLsdbType = vb->oid[idx++];
    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ospfLsdbEntry->ospfLsdbLsid[i] = vb->oid[idx++];
    }
    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ospfLsdbEntry->ospfLsdbRouterId[i] = vb->oid[idx++];
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ospfLsdbEntry(guint32 *base, guchar *ospfLsdbAreaId, gint32 ospfLsdbType, guchar *ospfLsdbLsid, guchar *ospfLsdbRouterId)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ospfLsdbAreaId[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = ospfLsdbType;
    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ospfLsdbLsid[i];
        if (idx >= 128) return -1;
    }
    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ospfLsdbRouterId[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline ospf_mib_ospfLsdbEntry_t *
assign_ospfLsdbEntry(GList *vbl)
{
    ospf_mib_ospfLsdbEntry_t *ospfLsdbEntry;
    char *p;

    ospfLsdbEntry = ospf_mib_new_ospfLsdbEntry();
    p = (char *) ospfLsdbEntry + sizeof(ospf_mib_ospfLsdbEntry_t);
    * (GList **) p = vbl;

    if (unpack_ospfLsdbEntry((GNetSnmpVarBind *) vbl->data, ospfLsdbEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ospfLsdbEntry");
        g_free(ospfLsdbEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ospfLsdbEntry_oid, G_N_ELEMENTS(ospfLsdbEntry_oid),
                      ospfLsdbEntry_attr, ospfLsdbEntry);

    return ospfLsdbEntry;
}

void
ospf_mib_get_ospfLsdbTable(GNetSnmp *s, ospf_mib_ospfLsdbEntry_t ***ospfLsdbEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 14, 4, 1, 0};
    guint32 base[128];

    *ospfLsdbEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 10, 9, ospfLsdbEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ospfLsdbEntry = (ospf_mib_ospfLsdbEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(ospf_mib_ospfLsdbEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ospfLsdbEntry)[i] = assign_ospfLsdbEntry(row->data);
        }
    }
}

void
ospf_mib_get_ospfLsdbEntry(GNetSnmp *s, ospf_mib_ospfLsdbEntry_t **ospfLsdbEntry, guchar *ospfLsdbAreaId, gint32 ospfLsdbType, guchar *ospfLsdbLsid, guchar *ospfLsdbRouterId, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ospfLsdbEntry_oid, sizeof(ospfLsdbEntry_oid));
    len = pack_ospfLsdbEntry(base, ospfLsdbAreaId, ospfLsdbType, ospfLsdbLsid, ospfLsdbRouterId);
    if (len < 0) {
        g_warning("%s: invalid index values", "ospfLsdbEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ospfLsdbEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, ospfLsdbEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ospfLsdbEntry = assign_ospfLsdbEntry(out);
    }
}

void
ospf_mib_free_ospfLsdbEntry(ospf_mib_ospfLsdbEntry_t *ospfLsdbEntry)
{
    GList *vbl;
    char *p;

    if (ospfLsdbEntry) {
        p = (char *) ospfLsdbEntry + sizeof(ospf_mib_ospfLsdbEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ospfLsdbEntry);
    }
}

void
ospf_mib_free_ospfLsdbTable(ospf_mib_ospfLsdbEntry_t **ospfLsdbEntry)
{
    int i;

    if (ospfLsdbEntry) {
        for (i = 0; ospfLsdbEntry[i]; i++) {
            ospf_mib_free_ospfLsdbEntry(ospfLsdbEntry[i]);
        }
        g_free(ospfLsdbEntry);
    }
}

ospf_mib_ospfIfEntry_t *
ospf_mib_new_ospfIfEntry()
{
    ospf_mib_ospfIfEntry_t *ospfIfEntry;

    ospfIfEntry = (ospf_mib_ospfIfEntry_t *) g_malloc0(sizeof(ospf_mib_ospfIfEntry_t) + sizeof(gpointer));
    return ospfIfEntry;
}

static inline int
unpack_ospfIfEntry(GNetSnmpVarBind *vb, ospf_mib_ospfIfEntry_t *ospfIfEntry)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ospfIfEntry->ospfIfIpAddress[i] = vb->oid[idx++];
    }
    if (vb->oid_len < idx) return -1;
    ospfIfEntry->ospfAddressLessIf = vb->oid[idx++];
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ospfIfEntry(guint32 *base, guchar *ospfIfIpAddress, gint32 ospfAddressLessIf)
{
    guint8 idx = 10;
    guint16 i, len;

    len = 4;
    if (len != 4) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ospfIfIpAddress[i];
        if (idx >= 128) return -1;
    }
    base[idx++] = ospfAddressLessIf;
    return idx;
}

static inline ospf_mib_ospfIfEntry_t *
assign_ospfIfEntry(GList *vbl)
{
    ospf_mib_ospfIfEntry_t *ospfIfEntry;
    char *p;

    ospfIfEntry = ospf_mib_new_ospfIfEntry();
    p = (char *) ospfIfEntry + sizeof(ospf_mib_ospfIfEntry_t);
    * (GList **) p = vbl;

    if (unpack_ospfIfEntry((GNetSnmpVarBind *) vbl->data, ospfIfEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ospfIfEntry");
        g_free(ospfIfEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ospfIfEntry_oid, G_N_ELEMENTS(ospfIfEntry_oid),
                      ospfIfEntry_attr, ospfIfEntry);

    return ospfIfEntry;
}

void
ospf_mib_get_ospfIfTable(GNetSnmp *s, ospf_mib_ospfIfEntry_t ***ospfIfEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 14, 7, 1, 0};
    guint32 base[128];

    *ospfIfEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 10, 9, ospfIfEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ospfIfEntry = (ospf_mib_ospfIfEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(ospf_mib_ospfIfEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ospfIfEntry)[i] = assign_ospfIfEntry(row->data);
        }
    }
}

void
ospf_mib_get_ospfIfEntry(GNetSnmp *s, ospf_mib_ospfIfEntry_t **ospfIfEntry, guchar *ospfIfIpAddress, gint32 ospfAddressLessIf, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ospfIfEntry_oid, sizeof(ospfIfEntry_oid));
    len = pack_ospfIfEntry(base, ospfIfIpAddress, ospfAddressLessIf);
    if (len < 0) {
        g_warning("%s: invalid index values", "ospfIfEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ospfIfEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, ospfIfEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ospfIfEntry = assign_ospfIfEntry(out);
    }
}

void
ospf_mib_set_ospfIfEntry(GNetSnmp *s, ospf_mib_ospfIfEntry_t *ospfIfEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ospfIfEntry_oid, sizeof(ospfIfEntry_oid));
    len = pack_ospfIfEntry(base, ospfIfEntry->ospfIfIpAddress, ospfIfEntry->ospfAddressLessIf);
    if (len < 0) {
        g_warning("%s: invalid index values", "ospfIfEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 9, ospfIfEntry_attr, mask, ospfIfEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
ospf_mib_free_ospfIfEntry(ospf_mib_ospfIfEntry_t *ospfIfEntry)
{
    GList *vbl;
    char *p;

    if (ospfIfEntry) {
        p = (char *) ospfIfEntry + sizeof(ospf_mib_ospfIfEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ospfIfEntry);
    }
}

void
ospf_mib_free_ospfIfTable(ospf_mib_ospfIfEntry_t **ospfIfEntry)
{
    int i;

    if (ospfIfEntry) {
        for (i = 0; ospfIfEntry[i]; i++) {
            ospf_mib_free_ospfIfEntry(ospfIfEntry[i]);
        }
        g_free(ospfIfEntry);
    }
}


