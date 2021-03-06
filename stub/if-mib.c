/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli --scli-set --scli-create --scli-delete \
 *     --scli-exclude='ifTestEntry' IF-MIB
 *
 * Derived from IF-MIB:
 *   The MIB module to describe generic objects for network
 *   interface sub-layers.  This MIB is an updated version of
 *   MIB-II's ifTable, and incorporates the extensions defined in
 *   RFC 1229.
 *
 * Revision 2000-06-14 00:00:
 *   Clarifications agreed upon by the Interfaces MIB WG, and
 *   published as RFC 2863.
 *
 * Revision 1996-02-28 21:55:
 *   Revisions made by the Interfaces MIB WG, and published in
 *   RFC 2233.
 *
 * Revision 1993-11-08 21:55:
 *   Initial revision, published as part of RFC 1573.
 *
 * $Id$
 */

#include "if-mib.h"

GNetSnmpEnum const if_mib_enums_ifAdminStatus[] = {
    { IF_MIB_IFADMINSTATUS_UP,      "up" },
    { IF_MIB_IFADMINSTATUS_DOWN,    "down" },
    { IF_MIB_IFADMINSTATUS_TESTING, "testing" },
    { 0, NULL }
};

GNetSnmpEnum const if_mib_enums_ifOperStatus[] = {
    { IF_MIB_IFOPERSTATUS_UP,             "up" },
    { IF_MIB_IFOPERSTATUS_DOWN,           "down" },
    { IF_MIB_IFOPERSTATUS_TESTING,        "testing" },
    { IF_MIB_IFOPERSTATUS_UNKNOWN,        "unknown" },
    { IF_MIB_IFOPERSTATUS_DORMANT,        "dormant" },
    { IF_MIB_IFOPERSTATUS_NOTPRESENT,     "notPresent" },
    { IF_MIB_IFOPERSTATUS_LOWERLAYERDOWN, "lowerLayerDown" },
    { 0, NULL }
};

GNetSnmpEnum const if_mib_enums_ifLinkUpDownTrapEnable[] = {
    { IF_MIB_IFLINKUPDOWNTRAPENABLE_ENABLED,  "enabled" },
    { IF_MIB_IFLINKUPDOWNTRAPENABLE_DISABLED, "disabled" },
    { 0, NULL }
};

GNetSnmpEnum const if_mib_enums_ifRcvAddressType[] = {
    { IF_MIB_IFRCVADDRESSTYPE_OTHER,       "other" },
    { IF_MIB_IFRCVADDRESSTYPE_VOLATILE,    "volatile" },
    { IF_MIB_IFRCVADDRESSTYPE_NONVOLATILE, "nonVolatile" },
    { 0, NULL }
};


static guint32 const linkDown[]
	= { IF_MIB_LINKDOWN };
static guint32 const linkUp[]
	= { IF_MIB_LINKUP };

GNetSnmpIdentity const if_mib_notifications[] = {
    { linkDown,
      G_N_ELEMENTS(linkDown),
      "linkDown" },
    { linkUp,
      G_N_ELEMENTS(linkUp),
      "linkUp" },
    { 0, 0, NULL }
};


static guint16 ifDescr_constraints[] = {0U, 255U, 0, 0};
static guint16 ifName_constraints[] = {0U, 255U, 0, 0};
static guint16 ifAlias_constraints[] = {0U, 64U, 0, 0};


static guint32 const interfaces_oid[] = {1, 3, 6, 1, 2, 1, 2};

static GNetSnmpAttribute interfaces_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFNUMBER, "ifNumber",
       NULL,
      G_STRUCT_OFFSET(if_mib_interfaces_t, ifNumber),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const ifEntry_oid[] = {1, 3, 6, 1, 2, 1, 2, 2, 1};

static GNetSnmpAttribute ifEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      IF_MIB_IFDESCR, "ifDescr",
       ifDescr_constraints,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifDescr),
      G_STRUCT_OFFSET(if_mib_ifEntry_t, _ifDescrLength),
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFTYPE, "ifType",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifType),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFMTU, "ifMtu",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifMtu),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      IF_MIB_IFSPEED, "ifSpeed",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifSpeed),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      IF_MIB_IFPHYSADDRESS, "ifPhysAddress",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifPhysAddress),
      G_STRUCT_OFFSET(if_mib_ifEntry_t, _ifPhysAddressLength),
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFADMINSTATUS, "ifAdminStatus",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifAdminStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFOPERSTATUS, "ifOperStatus",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifOperStatus),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_TIMETICKS,
      IF_MIB_IFLASTCHANGE, "ifLastChange",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifLastChange),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINOCTETS, "ifInOctets",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifInOctets),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINUCASTPKTS, "ifInUcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifInUcastPkts),
      0,
      0 },
    { 12, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINNUCASTPKTS, "ifInNUcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifInNUcastPkts),
      0,
      0 },
    { 13, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINDISCARDS, "ifInDiscards",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifInDiscards),
      0,
      0 },
    { 14, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINERRORS, "ifInErrors",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifInErrors),
      0,
      0 },
    { 15, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINUNKNOWNPROTOS, "ifInUnknownProtos",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifInUnknownProtos),
      0,
      0 },
    { 16, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFOUTOCTETS, "ifOutOctets",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifOutOctets),
      0,
      0 },
    { 17, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFOUTUCASTPKTS, "ifOutUcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifOutUcastPkts),
      0,
      0 },
    { 18, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFOUTNUCASTPKTS, "ifOutNUcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifOutNUcastPkts),
      0,
      0 },
    { 19, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFOUTDISCARDS, "ifOutDiscards",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifOutDiscards),
      0,
      0 },
    { 20, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFOUTERRORS, "ifOutErrors",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifOutErrors),
      0,
      0 },
    { 21, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      IF_MIB_IFOUTQLEN, "ifOutQLen",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifOutQLen),
      0,
      0 },
    { 22, GNET_SNMP_VARBIND_TYPE_OBJECTID,
      IF_MIB_IFSPECIFIC, "ifSpecific",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifEntry_t, ifSpecific),
      G_STRUCT_OFFSET(if_mib_ifEntry_t, _ifSpecificLength),
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const ifMIBObjects_oid[] = {1, 3, 6, 1, 2, 1, 31, 1};

static GNetSnmpAttribute ifMIBObjects_attr[] = {
    { 5, GNET_SNMP_VARBIND_TYPE_TIMETICKS,
      IF_MIB_IFTABLELASTCHANGE, "ifTableLastChange",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifMIBObjects_t, ifTableLastChange),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_TIMETICKS,
      IF_MIB_IFSTACKLASTCHANGE, "ifStackLastChange",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifMIBObjects_t, ifStackLastChange),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const ifXEntry_oid[] = {1, 3, 6, 1, 2, 1, 31, 1, 1, 1};

static GNetSnmpAttribute ifXEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      IF_MIB_IFNAME, "ifName",
       ifName_constraints,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifName),
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, _ifNameLength),
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINMULTICASTPKTS, "ifInMulticastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifInMulticastPkts),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFINBROADCASTPKTS, "ifInBroadcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifInBroadcastPkts),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFOUTMULTICASTPKTS, "ifOutMulticastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifOutMulticastPkts),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      IF_MIB_IFOUTBROADCASTPKTS, "ifOutBroadcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifOutBroadcastPkts),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCINOCTETS, "ifHCInOctets",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCInOctets),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCINUCASTPKTS, "ifHCInUcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCInUcastPkts),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCINMULTICASTPKTS, "ifHCInMulticastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCInMulticastPkts),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCINBROADCASTPKTS, "ifHCInBroadcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCInBroadcastPkts),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCOUTOCTETS, "ifHCOutOctets",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCOutOctets),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCOUTUCASTPKTS, "ifHCOutUcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCOutUcastPkts),
      0,
      0 },
    { 12, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCOUTMULTICASTPKTS, "ifHCOutMulticastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCOutMulticastPkts),
      0,
      0 },
    { 13, GNET_SNMP_VARBIND_TYPE_COUNTER64,
      IF_MIB_IFHCOUTBROADCASTPKTS, "ifHCOutBroadcastPkts",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHCOutBroadcastPkts),
      0,
      0 },
    { 14, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFLINKUPDOWNTRAPENABLE, "ifLinkUpDownTrapEnable",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifLinkUpDownTrapEnable),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 15, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      IF_MIB_IFHIGHSPEED, "ifHighSpeed",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifHighSpeed),
      0,
      0 },
    { 16, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFPROMISCUOUSMODE, "ifPromiscuousMode",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifPromiscuousMode),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 17, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFCONNECTORPRESENT, "ifConnectorPresent",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifConnectorPresent),
      0,
      0 },
    { 18, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      IF_MIB_IFALIAS, "ifAlias",
       ifAlias_constraints,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifAlias),
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, _ifAliasLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 19, GNET_SNMP_VARBIND_TYPE_TIMETICKS,
      IF_MIB_IFCOUNTERDISCONTINUITYTIME, "ifCounterDiscontinuityTime",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifXEntry_t, ifCounterDiscontinuityTime),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const ifStackEntry_oid[] = {1, 3, 6, 1, 2, 1, 31, 1, 2, 1};

static GNetSnmpAttribute ifStackEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFSTACKSTATUS, "ifStackStatus",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifStackEntry_t, ifStackStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const ifRcvAddressEntry_oid[] = {1, 3, 6, 1, 2, 1, 31, 1, 4, 1};

static GNetSnmpAttribute ifRcvAddressEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFRCVADDRESSSTATUS, "ifRcvAddressStatus",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifRcvAddressEntry_t, ifRcvAddressStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      IF_MIB_IFRCVADDRESSTYPE, "ifRcvAddressType",
       NULL,
      G_STRUCT_OFFSET(if_mib_ifRcvAddressEntry_t, ifRcvAddressType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


if_mib_interfaces_t *
if_mib_new_interfaces()
{
    if_mib_interfaces_t *interfaces;

    interfaces = (if_mib_interfaces_t *) g_malloc0(sizeof(if_mib_interfaces_t) + sizeof(gpointer));
    return interfaces;
}

static inline if_mib_interfaces_t *
assign_interfaces(GList *vbl)
{
    if_mib_interfaces_t *interfaces;
    char *p;

    interfaces = if_mib_new_interfaces();
    p = (char *) interfaces + sizeof(if_mib_interfaces_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, interfaces_oid, G_N_ELEMENTS(interfaces_oid),
                      interfaces_attr, interfaces);

    return interfaces;
}

void
if_mib_get_interfaces(GNetSnmp *s, if_mib_interfaces_t **interfaces, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    static const guint32 _base[] = {1, 3, 6, 1, 2, 1, 2, 0};
    guint32 base[128];

    *interfaces = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 8, 7, interfaces_attr, mask);

    out = gnet_snmp_sync_getnext(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if ((error && *error) || s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *interfaces = assign_interfaces(out);
    }
}

void
if_mib_free_interfaces(if_mib_interfaces_t *interfaces)
{
    GList *vbl;
    char *p;

    if (interfaces) {
        p = (char *) interfaces + sizeof(if_mib_interfaces_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(interfaces);
    }
}

if_mib_ifEntry_t *
if_mib_new_ifEntry()
{
    if_mib_ifEntry_t *ifEntry;

    ifEntry = (if_mib_ifEntry_t *) g_malloc0(sizeof(if_mib_ifEntry_t) + sizeof(gpointer));
    return ifEntry;
}

static inline int
unpack_ifEntry(GNetSnmpVarBind *vb, if_mib_ifEntry_t *ifEntry)
{
    guint8 idx = 10;

    if (vb->oid_len < idx) return -1;
    ifEntry->ifIndex = vb->oid[idx++];
    if ((ifEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ifEntry(guint32 *base, gint32 ifIndex)
{
    guint8 idx = 10;

    base[idx++] = ifIndex;
    return idx;
}

static inline if_mib_ifEntry_t *
assign_ifEntry(GList *vbl)
{
    if_mib_ifEntry_t *ifEntry;
    char *p;

    ifEntry = if_mib_new_ifEntry();
    p = (char *) ifEntry + sizeof(if_mib_ifEntry_t);
    * (GList **) p = vbl;

    if (unpack_ifEntry((GNetSnmpVarBind *) vbl->data, ifEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ifEntry");
        g_free(ifEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ifEntry_oid, G_N_ELEMENTS(ifEntry_oid),
                      ifEntry_attr, ifEntry);

    return ifEntry;
}

void
if_mib_get_ifTable(GNetSnmp *s, if_mib_ifEntry_t ***ifEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 2, 2, 1, 0};
    guint32 base[128];

    *ifEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 10, 9, ifEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ifEntry = (if_mib_ifEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(if_mib_ifEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ifEntry)[i] = assign_ifEntry(row->data);
        }
    }
}

void
if_mib_get_ifEntry(GNetSnmp *s, if_mib_ifEntry_t **ifEntry, gint32 ifIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifEntry_oid, sizeof(ifEntry_oid));
    len = pack_ifEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ifEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 9, ifEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ifEntry = assign_ifEntry(out);
    }
}

void
if_mib_set_ifEntry(GNetSnmp *s, if_mib_ifEntry_t *ifEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifEntry_oid, sizeof(ifEntry_oid));
    len = pack_ifEntry(base, ifEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 9, ifEntry_attr, mask, ifEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
if_mib_free_ifEntry(if_mib_ifEntry_t *ifEntry)
{
    GList *vbl;
    char *p;

    if (ifEntry) {
        p = (char *) ifEntry + sizeof(if_mib_ifEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ifEntry);
    }
}

void
if_mib_free_ifTable(if_mib_ifEntry_t **ifEntry)
{
    int i;

    if (ifEntry) {
        for (i = 0; ifEntry[i]; i++) {
            if_mib_free_ifEntry(ifEntry[i]);
        }
        g_free(ifEntry);
    }
}

void
if_mib_set_ifAdminStatus(GNetSnmp *s, gint32 ifIndex, gint32 ifAdminStatus, GError **error)
{
    if_mib_ifEntry_t *ifEntry;

    if_mib_get_ifEntry(s, &ifEntry, ifIndex, IF_MIB_IFADMINSTATUS, error);
    if (error && *error) return;
    if (s->error_status || !ifEntry) return;
    ifEntry->ifAdminStatus = &ifAdminStatus;
    if_mib_set_ifEntry(s, ifEntry, IF_MIB_IFADMINSTATUS, error);
    if_mib_free_ifEntry(ifEntry);
}

if_mib_ifMIBObjects_t *
if_mib_new_ifMIBObjects()
{
    if_mib_ifMIBObjects_t *ifMIBObjects;

    ifMIBObjects = (if_mib_ifMIBObjects_t *) g_malloc0(sizeof(if_mib_ifMIBObjects_t) + sizeof(gpointer));
    return ifMIBObjects;
}

static inline if_mib_ifMIBObjects_t *
assign_ifMIBObjects(GList *vbl)
{
    if_mib_ifMIBObjects_t *ifMIBObjects;
    char *p;

    ifMIBObjects = if_mib_new_ifMIBObjects();
    p = (char *) ifMIBObjects + sizeof(if_mib_ifMIBObjects_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, ifMIBObjects_oid, G_N_ELEMENTS(ifMIBObjects_oid),
                      ifMIBObjects_attr, ifMIBObjects);

    return ifMIBObjects;
}

void
if_mib_get_ifMIBObjects(GNetSnmp *s, if_mib_ifMIBObjects_t **ifMIBObjects, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    static const guint32 _base[] = {1, 3, 6, 1, 2, 1, 31, 1, 0};
    guint32 base[128];

    *ifMIBObjects = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 9, 8, ifMIBObjects_attr, mask);

    out = gnet_snmp_sync_getnext(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if ((error && *error) || s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ifMIBObjects = assign_ifMIBObjects(out);
    }
}

void
if_mib_free_ifMIBObjects(if_mib_ifMIBObjects_t *ifMIBObjects)
{
    GList *vbl;
    char *p;

    if (ifMIBObjects) {
        p = (char *) ifMIBObjects + sizeof(if_mib_ifMIBObjects_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ifMIBObjects);
    }
}

if_mib_ifXEntry_t *
if_mib_new_ifXEntry()
{
    if_mib_ifXEntry_t *ifXEntry;

    ifXEntry = (if_mib_ifXEntry_t *) g_malloc0(sizeof(if_mib_ifXEntry_t) + sizeof(gpointer));
    return ifXEntry;
}

static inline int
unpack_ifXEntry(GNetSnmpVarBind *vb, if_mib_ifXEntry_t *ifXEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    ifXEntry->ifIndex = vb->oid[idx++];
    if ((ifXEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ifXEntry(guint32 *base, gint32 ifIndex)
{
    guint8 idx = 11;

    base[idx++] = ifIndex;
    return idx;
}

static inline if_mib_ifXEntry_t *
assign_ifXEntry(GList *vbl)
{
    if_mib_ifXEntry_t *ifXEntry;
    char *p;

    ifXEntry = if_mib_new_ifXEntry();
    p = (char *) ifXEntry + sizeof(if_mib_ifXEntry_t);
    * (GList **) p = vbl;

    if (unpack_ifXEntry((GNetSnmpVarBind *) vbl->data, ifXEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ifXEntry");
        g_free(ifXEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ifXEntry_oid, G_N_ELEMENTS(ifXEntry_oid),
                      ifXEntry_attr, ifXEntry);

    return ifXEntry;
}

void
if_mib_get_ifXTable(GNetSnmp *s, if_mib_ifXEntry_t ***ifXEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 31, 1, 1, 1, 0};
    guint32 base[128];

    *ifXEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, ifXEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ifXEntry = (if_mib_ifXEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(if_mib_ifXEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ifXEntry)[i] = assign_ifXEntry(row->data);
        }
    }
}

void
if_mib_get_ifXEntry(GNetSnmp *s, if_mib_ifXEntry_t **ifXEntry, gint32 ifIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifXEntry_oid, sizeof(ifXEntry_oid));
    len = pack_ifXEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifXEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ifXEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, ifXEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ifXEntry = assign_ifXEntry(out);
    }
}

void
if_mib_set_ifXEntry(GNetSnmp *s, if_mib_ifXEntry_t *ifXEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifXEntry_oid, sizeof(ifXEntry_oid));
    len = pack_ifXEntry(base, ifXEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifXEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, ifXEntry_attr, mask, ifXEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
if_mib_free_ifXEntry(if_mib_ifXEntry_t *ifXEntry)
{
    GList *vbl;
    char *p;

    if (ifXEntry) {
        p = (char *) ifXEntry + sizeof(if_mib_ifXEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ifXEntry);
    }
}

void
if_mib_free_ifXTable(if_mib_ifXEntry_t **ifXEntry)
{
    int i;

    if (ifXEntry) {
        for (i = 0; ifXEntry[i]; i++) {
            if_mib_free_ifXEntry(ifXEntry[i]);
        }
        g_free(ifXEntry);
    }
}

void
if_mib_set_ifLinkUpDownTrapEnable(GNetSnmp *s, gint32 ifIndex, gint32 ifLinkUpDownTrapEnable, GError **error)
{
    if_mib_ifXEntry_t *ifXEntry;

    if_mib_get_ifXEntry(s, &ifXEntry, ifIndex, IF_MIB_IFLINKUPDOWNTRAPENABLE, error);
    if (error && *error) return;
    if (s->error_status || !ifXEntry) return;
    ifXEntry->ifLinkUpDownTrapEnable = &ifLinkUpDownTrapEnable;
    if_mib_set_ifXEntry(s, ifXEntry, IF_MIB_IFLINKUPDOWNTRAPENABLE, error);
    if_mib_free_ifXEntry(ifXEntry);
}

void
if_mib_set_ifPromiscuousMode(GNetSnmp *s, gint32 ifIndex, gint32 ifPromiscuousMode, GError **error)
{
    if_mib_ifXEntry_t *ifXEntry;

    if_mib_get_ifXEntry(s, &ifXEntry, ifIndex, IF_MIB_IFPROMISCUOUSMODE, error);
    if (error && *error) return;
    if (s->error_status || !ifXEntry) return;
    ifXEntry->ifPromiscuousMode = &ifPromiscuousMode;
    if_mib_set_ifXEntry(s, ifXEntry, IF_MIB_IFPROMISCUOUSMODE, error);
    if_mib_free_ifXEntry(ifXEntry);
}

void
if_mib_set_ifAlias(GNetSnmp *s, gint32 ifIndex, guchar *ifAlias, guint16 _ifAliasLength, GError **error)
{
    if_mib_ifXEntry_t *ifXEntry;

    if_mib_get_ifXEntry(s, &ifXEntry, ifIndex, IF_MIB_IFALIAS, error);
    if (error && *error) return;
    if (s->error_status || !ifXEntry) return;
    ifXEntry->ifAlias = ifAlias;
    ifXEntry->_ifAliasLength = _ifAliasLength;
    if_mib_set_ifXEntry(s, ifXEntry, IF_MIB_IFALIAS, error);
    if_mib_free_ifXEntry(ifXEntry);
}

if_mib_ifStackEntry_t *
if_mib_new_ifStackEntry()
{
    if_mib_ifStackEntry_t *ifStackEntry;

    ifStackEntry = (if_mib_ifStackEntry_t *) g_malloc0(sizeof(if_mib_ifStackEntry_t) + sizeof(gpointer));
    return ifStackEntry;
}

static inline int
unpack_ifStackEntry(GNetSnmpVarBind *vb, if_mib_ifStackEntry_t *ifStackEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    ifStackEntry->ifStackHigherLayer = vb->oid[idx++];
    if ((ifStackEntry->ifStackHigherLayer < 0)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    ifStackEntry->ifStackLowerLayer = vb->oid[idx++];
    if ((ifStackEntry->ifStackLowerLayer < 0)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ifStackEntry(guint32 *base, gint32 ifStackHigherLayer, gint32 ifStackLowerLayer)
{
    guint8 idx = 11;

    base[idx++] = ifStackHigherLayer;
    base[idx++] = ifStackLowerLayer;
    return idx;
}

static inline if_mib_ifStackEntry_t *
assign_ifStackEntry(GList *vbl)
{
    if_mib_ifStackEntry_t *ifStackEntry;
    char *p;

    ifStackEntry = if_mib_new_ifStackEntry();
    p = (char *) ifStackEntry + sizeof(if_mib_ifStackEntry_t);
    * (GList **) p = vbl;

    if (unpack_ifStackEntry((GNetSnmpVarBind *) vbl->data, ifStackEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ifStackEntry");
        g_free(ifStackEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ifStackEntry_oid, G_N_ELEMENTS(ifStackEntry_oid),
                      ifStackEntry_attr, ifStackEntry);

    return ifStackEntry;
}

void
if_mib_get_ifStackTable(GNetSnmp *s, if_mib_ifStackEntry_t ***ifStackEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 31, 1, 2, 1, 0};
    guint32 base[128];

    *ifStackEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, ifStackEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ifStackEntry = (if_mib_ifStackEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(if_mib_ifStackEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ifStackEntry)[i] = assign_ifStackEntry(row->data);
        }
    }
}

void
if_mib_get_ifStackEntry(GNetSnmp *s, if_mib_ifStackEntry_t **ifStackEntry, gint32 ifStackHigherLayer, gint32 ifStackLowerLayer, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifStackEntry_oid, sizeof(ifStackEntry_oid));
    len = pack_ifStackEntry(base, ifStackHigherLayer, ifStackLowerLayer);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifStackEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ifStackEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, ifStackEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ifStackEntry = assign_ifStackEntry(out);
    }
}

void
if_mib_set_ifStackEntry(GNetSnmp *s, if_mib_ifStackEntry_t *ifStackEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifStackEntry_oid, sizeof(ifStackEntry_oid));
    len = pack_ifStackEntry(base, ifStackEntry->ifStackHigherLayer, ifStackEntry->ifStackLowerLayer);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifStackEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, ifStackEntry_attr, mask, ifStackEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
if_mib_free_ifStackEntry(if_mib_ifStackEntry_t *ifStackEntry)
{
    GList *vbl;
    char *p;

    if (ifStackEntry) {
        p = (char *) ifStackEntry + sizeof(if_mib_ifStackEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ifStackEntry);
    }
}

void
if_mib_free_ifStackTable(if_mib_ifStackEntry_t **ifStackEntry)
{
    int i;

    if (ifStackEntry) {
        for (i = 0; ifStackEntry[i]; i++) {
            if_mib_free_ifStackEntry(ifStackEntry[i]);
        }
        g_free(ifStackEntry);
    }
}

void
if_mib_create_ifStackEntry(GNetSnmp *s, gint32 ifStackHigherLayer, gint32 ifStackLowerLayer, GError **error)
{
    if_mib_ifStackEntry_t *ifStackEntry;
    gint32 create = 4; /* SNMPv2-TC::RowStatus createAndGo */

    ifStackEntry = if_mib_new_ifStackEntry();
    ifStackEntry->ifStackHigherLayer = ifStackHigherLayer;
    ifStackEntry->ifStackLowerLayer = ifStackLowerLayer;
    ifStackEntry->ifStackStatus = &create;
    if_mib_set_ifStackEntry(s, ifStackEntry, IF_MIB_IFSTACKSTATUS, error);
    if_mib_free_ifStackEntry(ifStackEntry);
}

void
if_mib_delete_ifStackEntry(GNetSnmp *s, gint32 ifStackHigherLayer, gint32 ifStackLowerLayer, GError **error)
{
    if_mib_ifStackEntry_t *ifStackEntry;
    gint32 destroy = 6; /* SNMPv2-TC::RowStatus destroy */

    if_mib_get_ifStackEntry(s, &ifStackEntry, ifStackHigherLayer, ifStackLowerLayer, IF_MIB_IFSTACKSTATUS, error);
    if (error && *error) return;
    if (s->error_status || !ifStackEntry) return;
    ifStackEntry->ifStackStatus = &destroy;
    if_mib_set_ifStackEntry(s, ifStackEntry, IF_MIB_IFSTACKSTATUS, error);
    if_mib_free_ifStackEntry(ifStackEntry);
}

if_mib_ifRcvAddressEntry_t *
if_mib_new_ifRcvAddressEntry()
{
    if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry;

    ifRcvAddressEntry = (if_mib_ifRcvAddressEntry_t *) g_malloc0(sizeof(if_mib_ifRcvAddressEntry_t) + sizeof(gpointer));
    return ifRcvAddressEntry;
}

static inline int
unpack_ifRcvAddressEntry(GNetSnmpVarBind *vb, if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry)
{
    guint8 idx = 11;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    ifRcvAddressEntry->ifIndex = vb->oid[idx++];
    if ((ifRcvAddressEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len > 117) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        ifRcvAddressEntry->ifRcvAddressAddress[i] = vb->oid[idx++];
    }
    ifRcvAddressEntry->_ifRcvAddressAddressLength = len;
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_ifRcvAddressEntry(guint32 *base, gint32 ifIndex, guchar *ifRcvAddressAddress, guint16 _ifRcvAddressAddressLength)
{
    guint8 idx = 11;
    guint16 i, len;

    base[idx++] = ifIndex;
    len = _ifRcvAddressAddressLength;
    base[idx++] = len;
    if (len > 117) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = ifRcvAddressAddress[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline if_mib_ifRcvAddressEntry_t *
assign_ifRcvAddressEntry(GList *vbl)
{
    if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry;
    char *p;

    ifRcvAddressEntry = if_mib_new_ifRcvAddressEntry();
    p = (char *) ifRcvAddressEntry + sizeof(if_mib_ifRcvAddressEntry_t);
    * (GList **) p = vbl;

    if (unpack_ifRcvAddressEntry((GNetSnmpVarBind *) vbl->data, ifRcvAddressEntry) < 0) {
        g_warning("%s: invalid instance identifier", "ifRcvAddressEntry");
        g_free(ifRcvAddressEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, ifRcvAddressEntry_oid, G_N_ELEMENTS(ifRcvAddressEntry_oid),
                      ifRcvAddressEntry_attr, ifRcvAddressEntry);

    return ifRcvAddressEntry;
}

void
if_mib_get_ifRcvAddressTable(GNetSnmp *s, if_mib_ifRcvAddressEntry_t ***ifRcvAddressEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 31, 1, 4, 1, 0};
    guint32 base[128];

    *ifRcvAddressEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, ifRcvAddressEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *ifRcvAddressEntry = (if_mib_ifRcvAddressEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(if_mib_ifRcvAddressEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*ifRcvAddressEntry)[i] = assign_ifRcvAddressEntry(row->data);
        }
    }
}

void
if_mib_get_ifRcvAddressEntry(GNetSnmp *s, if_mib_ifRcvAddressEntry_t **ifRcvAddressEntry, gint32 ifIndex, guchar *ifRcvAddressAddress, guint16 _ifRcvAddressAddressLength, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifRcvAddressEntry_oid, sizeof(ifRcvAddressEntry_oid));
    len = pack_ifRcvAddressEntry(base, ifIndex, ifRcvAddressAddress, _ifRcvAddressAddressLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifRcvAddressEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *ifRcvAddressEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, ifRcvAddressEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *ifRcvAddressEntry = assign_ifRcvAddressEntry(out);
    }
}

void
if_mib_set_ifRcvAddressEntry(GNetSnmp *s, if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, ifRcvAddressEntry_oid, sizeof(ifRcvAddressEntry_oid));
    len = pack_ifRcvAddressEntry(base, ifRcvAddressEntry->ifIndex, ifRcvAddressEntry->ifRcvAddressAddress, ifRcvAddressEntry->_ifRcvAddressAddressLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "ifRcvAddressEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, ifRcvAddressEntry_attr, mask, ifRcvAddressEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
if_mib_free_ifRcvAddressEntry(if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry)
{
    GList *vbl;
    char *p;

    if (ifRcvAddressEntry) {
        p = (char *) ifRcvAddressEntry + sizeof(if_mib_ifRcvAddressEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(ifRcvAddressEntry);
    }
}

void
if_mib_free_ifRcvAddressTable(if_mib_ifRcvAddressEntry_t **ifRcvAddressEntry)
{
    int i;

    if (ifRcvAddressEntry) {
        for (i = 0; ifRcvAddressEntry[i]; i++) {
            if_mib_free_ifRcvAddressEntry(ifRcvAddressEntry[i]);
        }
        g_free(ifRcvAddressEntry);
    }
}

void
if_mib_create_ifRcvAddressEntry(GNetSnmp *s, gint32 ifIndex, guchar *ifRcvAddressAddress, guint16 _ifRcvAddressAddressLength, GError **error)
{
    if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry;
    gint32 create = 4; /* SNMPv2-TC::RowStatus createAndGo */

    ifRcvAddressEntry = if_mib_new_ifRcvAddressEntry();
    ifRcvAddressEntry->ifIndex = ifIndex;
    memcpy(ifRcvAddressEntry->ifRcvAddressAddress, ifRcvAddressAddress, _ifRcvAddressAddressLength);
    ifRcvAddressEntry->ifRcvAddressStatus = &create;
    if_mib_set_ifRcvAddressEntry(s, ifRcvAddressEntry, IF_MIB_IFRCVADDRESSSTATUS, error);
    if_mib_free_ifRcvAddressEntry(ifRcvAddressEntry);
}

void
if_mib_delete_ifRcvAddressEntry(GNetSnmp *s, gint32 ifIndex, guchar *ifRcvAddressAddress, guint16 _ifRcvAddressAddressLength, GError **error)
{
    if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry;
    gint32 destroy = 6; /* SNMPv2-TC::RowStatus destroy */

    if_mib_get_ifRcvAddressEntry(s, &ifRcvAddressEntry, ifIndex, ifRcvAddressAddress, _ifRcvAddressAddressLength, IF_MIB_IFRCVADDRESSSTATUS, error);
    if (error && *error) return;
    if (s->error_status || !ifRcvAddressEntry) return;
    ifRcvAddressEntry->ifRcvAddressStatus = &destroy;
    if_mib_set_ifRcvAddressEntry(s, ifRcvAddressEntry, IF_MIB_IFRCVADDRESSSTATUS, error);
    if_mib_free_ifRcvAddressEntry(ifRcvAddressEntry);
}

void
if_mib_set_ifRcvAddressType(GNetSnmp *s, gint32 ifIndex, guchar *ifRcvAddressAddress, guint16 _ifRcvAddressAddressLength, gint32 ifRcvAddressType, GError **error)
{
    if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry;

    if_mib_get_ifRcvAddressEntry(s, &ifRcvAddressEntry, ifIndex, ifRcvAddressAddress, _ifRcvAddressAddressLength, IF_MIB_IFRCVADDRESSTYPE, error);
    if (error && *error) return;
    if (s->error_status || !ifRcvAddressEntry) return;
    ifRcvAddressEntry->ifRcvAddressType = &ifRcvAddressType;
    if_mib_set_ifRcvAddressEntry(s, ifRcvAddressEntry, IF_MIB_IFRCVADDRESSTYPE, error);
    if_mib_free_ifRcvAddressEntry(ifRcvAddressEntry);
}


