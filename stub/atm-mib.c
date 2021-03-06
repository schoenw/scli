/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli \
 *     --scli-include='atmInterfaceConfEntry' ATM-MIB
 *
 * Derived from ATM-MIB:
 *   This is the MIB Module for ATM and AAL5-related
 *   objects for managing ATM interfaces, ATM virtual
 *   links, ATM cross-connects, AAL5 entities, and
 *   and AAL5 connections.
 *
 * Revision 1998-10-19 12:00:
 *   The initial revision of this module was published
 *   as RFC 1695. Key revisions include:
 *   o  Textual Conventions and OBJECT IDENTITIES have
 *      been moved to a separate MIB module.
 *   o  Applicability of objects to PVCs, SVCs and Soft
 *      PVCs has been clarified.
 *   o  DEFVAL clauses have been added.
 *   o  The relationship of ifIndex values with different
 *      layers and sublayers related to ATM has been
 *      clarified.
 *   o  atmTrafficQosClass has been deprecated
 *      and replaced with atmServiceCategory.
 *   o  atmInterfaceCurrentMaxVpiBits and
 *      atmInterfaceCurrentMaxVciBits have been added with
 *      a description on their relationship with other
 *      objects.
 *   o  atmInterfaceAddressType and atmInterfaceAdminAddress
 *      have been deprecated and replaced by
 *      atmInterfaceSubscrAddress.
 *   o  atmInterfaceTCAlarmState has been clarified.
 *   o  atmTrafficDescrParamIndexNext has been introduced
 *      in order to provide a manager a free
 *      atmTrafficDescrParamIndex value.
 *   o  The atmTrafficFrameDiscard capability has been added.
 *   o  A connection topology type (atmVpl/VclCastType) and
 *      a call control type (atmVpl/VclConnKind) have been
 *      added.
 *   o  aal2 has been added to atmVccAalType.
 *
 * Revision 1994-06-07 22:45:
 *   The RFC1695 version of this MIB module.
 *
 * $Id$
 */

#include "atm-mib.h"

GNetSnmpEnum const atm_mib_enums_atmInterfaceAddressType[] = {
    { ATM_MIB_ATMINTERFACEADDRESSTYPE_PRIVATE,    "private" },
    { ATM_MIB_ATMINTERFACEADDRESSTYPE_NSAPE164,   "nsapE164" },
    { ATM_MIB_ATMINTERFACEADDRESSTYPE_NATIVEE164, "nativeE164" },
    { ATM_MIB_ATMINTERFACEADDRESSTYPE_OTHER,      "other" },
    { 0, NULL }
};


static gint32 atmInterfaceMaxVpcs_constraints[] = {0L, 4096L, 0, 0};
static gint32 atmInterfaceMaxVccs_constraints[] = {0L, 65536L, 0, 0};
static gint32 atmInterfaceConfVpcs_constraints[] = {0L, 4096L, 0, 0};
static gint32 atmInterfaceConfVccs_constraints[] = {0L, 65536L, 0, 0};
static gint32 atmInterfaceMaxActiveVpiBits_constraints[] = {0L, 12L, 0, 0};
static gint32 atmInterfaceMaxActiveVciBits_constraints[] = {0L, 16L, 0, 0};
static gint32 atmInterfaceIlmiVpi_constraints[] = {0L, 4095L, 0, 0};
static gint32 atmInterfaceIlmiVci_constraints[] = {0L, 65535L, 0, 0};
static guint16 atmInterfaceAdminAddress_constraints[] = {0U, 40U, 0, 0};
static guint16 atmInterfaceMyNeighborIpAddress_constraints[] = {4U, 4U, 0, 0};
static guint16 atmInterfaceMyNeighborIfName_constraints[] = {0U, 255U, 0, 0};
static gint32 atmInterfaceCurrentMaxVpiBits_constraints[] = {0L, 12L, 0, 0};
static gint32 atmInterfaceCurrentMaxVciBits_constraints[] = {0L, 16L, 0, 0};
static guint16 atmInterfaceSubscrAddress_constraints[] = {0U, 40U, 0, 0};


static guint32 const atmInterfaceConfEntry_oid[] = {1, 3, 6, 1, 2, 1, 37, 1, 2, 1};

static GNetSnmpAttribute atmInterfaceConfEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACEMAXVPCS, "atmInterfaceMaxVpcs",
       atmInterfaceMaxVpcs_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceMaxVpcs),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACEMAXVCCS, "atmInterfaceMaxVccs",
       atmInterfaceMaxVccs_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceMaxVccs),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACECONFVPCS, "atmInterfaceConfVpcs",
       atmInterfaceConfVpcs_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceConfVpcs),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACECONFVCCS, "atmInterfaceConfVccs",
       atmInterfaceConfVccs_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceConfVccs),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACEMAXACTIVEVPIBITS, "atmInterfaceMaxActiveVpiBits",
       atmInterfaceMaxActiveVpiBits_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceMaxActiveVpiBits),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACEMAXACTIVEVCIBITS, "atmInterfaceMaxActiveVciBits",
       atmInterfaceMaxActiveVciBits_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceMaxActiveVciBits),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACEILMIVPI, "atmInterfaceIlmiVpi",
       atmInterfaceIlmiVpi_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceIlmiVpi),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACEILMIVCI, "atmInterfaceIlmiVci",
       atmInterfaceIlmiVci_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceIlmiVci),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACEADDRESSTYPE, "atmInterfaceAddressType",
       NULL,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceAddressType),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      ATM_MIB_ATMINTERFACEADMINADDRESS, "atmInterfaceAdminAddress",
       atmInterfaceAdminAddress_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceAdminAddress),
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, _atmInterfaceAdminAddressLength),
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_IPADDRESS,
      ATM_MIB_ATMINTERFACEMYNEIGHBORIPADDRESS, "atmInterfaceMyNeighborIpAddress",
       atmInterfaceMyNeighborIpAddress_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceMyNeighborIpAddress),
      4,
      GSNMP_ATTR_FLAG_WRITABLE|GSNMP_ATTR_FLAG_FIXED_LENGTH },
    { 12, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      ATM_MIB_ATMINTERFACEMYNEIGHBORIFNAME, "atmInterfaceMyNeighborIfName",
       atmInterfaceMyNeighborIfName_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceMyNeighborIfName),
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, _atmInterfaceMyNeighborIfNameLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 13, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACECURRENTMAXVPIBITS, "atmInterfaceCurrentMaxVpiBits",
       atmInterfaceCurrentMaxVpiBits_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceCurrentMaxVpiBits),
      0,
      0 },
    { 14, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      ATM_MIB_ATMINTERFACECURRENTMAXVCIBITS, "atmInterfaceCurrentMaxVciBits",
       atmInterfaceCurrentMaxVciBits_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceCurrentMaxVciBits),
      0,
      0 },
    { 15, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      ATM_MIB_ATMINTERFACESUBSCRADDRESS, "atmInterfaceSubscrAddress",
       atmInterfaceSubscrAddress_constraints,
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, atmInterfaceSubscrAddress),
      G_STRUCT_OFFSET(atm_mib_atmInterfaceConfEntry_t, _atmInterfaceSubscrAddressLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


atm_mib_atmInterfaceConfEntry_t *
atm_mib_new_atmInterfaceConfEntry()
{
    atm_mib_atmInterfaceConfEntry_t *atmInterfaceConfEntry;

    atmInterfaceConfEntry = (atm_mib_atmInterfaceConfEntry_t *) g_malloc0(sizeof(atm_mib_atmInterfaceConfEntry_t) + sizeof(gpointer));
    return atmInterfaceConfEntry;
}

static inline int
unpack_atmInterfaceConfEntry(GNetSnmpVarBind *vb, atm_mib_atmInterfaceConfEntry_t *atmInterfaceConfEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    atmInterfaceConfEntry->ifIndex = vb->oid[idx++];
    if ((atmInterfaceConfEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_atmInterfaceConfEntry(guint32 *base, gint32 ifIndex)
{
    guint8 idx = 11;

    base[idx++] = ifIndex;
    return idx;
}

static inline atm_mib_atmInterfaceConfEntry_t *
assign_atmInterfaceConfEntry(GList *vbl)
{
    atm_mib_atmInterfaceConfEntry_t *atmInterfaceConfEntry;
    char *p;

    atmInterfaceConfEntry = atm_mib_new_atmInterfaceConfEntry();
    p = (char *) atmInterfaceConfEntry + sizeof(atm_mib_atmInterfaceConfEntry_t);
    * (GList **) p = vbl;

    if (unpack_atmInterfaceConfEntry((GNetSnmpVarBind *) vbl->data, atmInterfaceConfEntry) < 0) {
        g_warning("%s: invalid instance identifier", "atmInterfaceConfEntry");
        g_free(atmInterfaceConfEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, atmInterfaceConfEntry_oid, G_N_ELEMENTS(atmInterfaceConfEntry_oid),
                      atmInterfaceConfEntry_attr, atmInterfaceConfEntry);

    return atmInterfaceConfEntry;
}

void
atm_mib_get_atmInterfaceConfTable(GNetSnmp *s, atm_mib_atmInterfaceConfEntry_t ***atmInterfaceConfEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 37, 1, 2, 1, 0};
    guint32 base[128];

    *atmInterfaceConfEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, atmInterfaceConfEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *atmInterfaceConfEntry = (atm_mib_atmInterfaceConfEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(atm_mib_atmInterfaceConfEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*atmInterfaceConfEntry)[i] = assign_atmInterfaceConfEntry(row->data);
        }
    }
}

void
atm_mib_get_atmInterfaceConfEntry(GNetSnmp *s, atm_mib_atmInterfaceConfEntry_t **atmInterfaceConfEntry, gint32 ifIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, atmInterfaceConfEntry_oid, sizeof(atmInterfaceConfEntry_oid));
    len = pack_atmInterfaceConfEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "atmInterfaceConfEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *atmInterfaceConfEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, atmInterfaceConfEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *atmInterfaceConfEntry = assign_atmInterfaceConfEntry(out);
    }
}

void
atm_mib_set_atmInterfaceConfEntry(GNetSnmp *s, atm_mib_atmInterfaceConfEntry_t *atmInterfaceConfEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, atmInterfaceConfEntry_oid, sizeof(atmInterfaceConfEntry_oid));
    len = pack_atmInterfaceConfEntry(base, atmInterfaceConfEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "atmInterfaceConfEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, atmInterfaceConfEntry_attr, mask, atmInterfaceConfEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
atm_mib_free_atmInterfaceConfEntry(atm_mib_atmInterfaceConfEntry_t *atmInterfaceConfEntry)
{
    GList *vbl;
    char *p;

    if (atmInterfaceConfEntry) {
        p = (char *) atmInterfaceConfEntry + sizeof(atm_mib_atmInterfaceConfEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(atmInterfaceConfEntry);
    }
}

void
atm_mib_free_atmInterfaceConfTable(atm_mib_atmInterfaceConfEntry_t **atmInterfaceConfEntry)
{
    int i;

    if (atmInterfaceConfEntry) {
        for (i = 0; atmInterfaceConfEntry[i]; i++) {
            atm_mib_free_atmInterfaceConfEntry(atmInterfaceConfEntry[i]);
        }
        g_free(atmInterfaceConfEntry);
    }
}


