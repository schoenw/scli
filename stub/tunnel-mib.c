/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.16 for the stools package.
 *
 * Derived from TUNNEL-MIB:
 *   The MIB module for management of IP Tunnels, independent of
 *   the specific encapsulation scheme in use.
 *
 * Revision 1999-08-24 12:00:
 *   Initial version, published as RFC 2667.
 *
 * $Id$
 */

#include "tunnel-mib.h"

stls_enum_t const tunnel_mib_enums_tunnelIfEncapsMethod[] = {
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_OTHER,	"other" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_DIRECT,	"direct" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_GRE,	"gre" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_MINIMAL,	"minimal" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_L2TP,	"l2tp" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_PPTP,	"pptp" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_L2F,	"l2f" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_UDP,	"udp" },
    { TUNNEL_MIB_TUNNELIFENCAPSMETHOD_ATMP,	"atmp" },
    { 0, NULL }
};

stls_enum_t const tunnel_mib_enums_tunnelIfSecurity[] = {
    { TUNNEL_MIB_TUNNELIFSECURITY_NONE,	"none" },
    { TUNNEL_MIB_TUNNELIFSECURITY_IPSEC,	"ipsec" },
    { TUNNEL_MIB_TUNNELIFSECURITY_OTHER,	"other" },
    { 0, NULL }
};

stls_enum_t const tunnel_mib_enums_tunnelConfigEncapsMethod[] = {
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_OTHER,	"other" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_DIRECT,	"direct" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_GRE,	"gre" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_MINIMAL,	"minimal" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_L2TP,	"l2tp" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_PPTP,	"pptp" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_L2F,	"l2f" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_UDP,	"udp" },
    { TUNNEL_MIB_TUNNELCONFIGENCAPSMETHOD_ATMP,	"atmp" },
    { 0, NULL }
};

stls_enum_t const tunnel_mib_enums_tunnelConfigStatus[] = {
    { TUNNEL_MIB_TUNNELCONFIGSTATUS_ACTIVE,	"active" },
    { TUNNEL_MIB_TUNNELCONFIGSTATUS_NOTINSERVICE,	"notInService" },
    { TUNNEL_MIB_TUNNELCONFIGSTATUS_NOTREADY,	"notReady" },
    { TUNNEL_MIB_TUNNELCONFIGSTATUS_CREATEANDGO,	"createAndGo" },
    { TUNNEL_MIB_TUNNELCONFIGSTATUS_CREATEANDWAIT,	"createAndWait" },
    { TUNNEL_MIB_TUNNELCONFIGSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};


static stls_stub_attr_t _tunnelIfEntry[] = {
    { 1, G_SNMP_IPADDRESS, "tunnelIfLocalAddress" },
    { 2, G_SNMP_IPADDRESS, "tunnelIfRemoteAddress" },
    { 3, G_SNMP_INTEGER32, "tunnelIfEncapsMethod" },
    { 4, G_SNMP_INTEGER32, "tunnelIfHopLimit" },
    { 5, G_SNMP_INTEGER32, "tunnelIfSecurity" },
    { 6, G_SNMP_INTEGER32, "tunnelIfTOS" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _tunnelConfigEntry[] = {
    { 5, G_SNMP_INTEGER32, "tunnelConfigIfIndex" },
    { 6, G_SNMP_INTEGER32, "tunnelConfigStatus" },
    { 0, 0, NULL }
};


tunnel_mib_tunnelIfEntry_t *
tunnel_mib_new_tunnelIfEntry()
{
    tunnel_mib_tunnelIfEntry_t *tunnelIfEntry;

    tunnelIfEntry = (tunnel_mib_tunnelIfEntry_t *) g_malloc0(sizeof(tunnel_mib_tunnelIfEntry_t) + sizeof(gpointer));
    return tunnelIfEntry;
}

static int
unpack_tunnelIfEntry(GSnmpVarBind *vb, tunnel_mib_tunnelIfEntry_t *tunnelIfEntry)
{
    int idx = 13;

    if (vb->id_len < idx) return -1;
    tunnelIfEntry->ifIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static tunnel_mib_tunnelIfEntry_t *
assign_tunnelIfEntry(GSList *vbl)
{
    GSList *elem;
    tunnel_mib_tunnelIfEntry_t *tunnelIfEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 10, 131, 1, 1, 1, 1};

    tunnelIfEntry = tunnel_mib_new_tunnelIfEntry();
    if (! tunnelIfEntry) {
        return NULL;
    }

    p = (char *) tunnelIfEntry + sizeof(tunnel_mib_tunnelIfEntry_t);
    * (GSList **) p = vbl;

    if (unpack_tunnelIfEntry((GSnmpVarBind *) vbl->data, tunnelIfEntry) < 0) {
        g_warning("illegal tunnelIfEntry instance identifier");
        g_free(tunnelIfEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _tunnelIfEntry, &idx) < 0) continue;

        switch (idx) {
        case 1:
            tunnelIfEntry->tunnelIfLocalAddress = vb->syntax.uc;
            break;
        case 2:
            tunnelIfEntry->tunnelIfRemoteAddress = vb->syntax.uc;
            break;
        case 3:
            tunnelIfEntry->tunnelIfEncapsMethod = &(vb->syntax.i32[0]);
            break;
        case 4:
            tunnelIfEntry->tunnelIfHopLimit = &(vb->syntax.i32[0]);
            break;
        case 5:
            tunnelIfEntry->tunnelIfSecurity = &(vb->syntax.i32[0]);
            break;
        case 6:
            tunnelIfEntry->tunnelIfTOS = &(vb->syntax.i32[0]);
            break;
        };
    }

    return tunnelIfEntry;
}

int
tunnel_mib_get_tunnelIfTable(GSnmpSession *s, tunnel_mib_tunnelIfEntry_t ***tunnelIfEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 131, 1, 1, 1, 1, 0};

    *tunnelIfEntry = NULL;

    stls_vbl_attributes(s, &in, base, 12, _tunnelIfEntry);

    out = stls_snmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *tunnelIfEntry = (tunnel_mib_tunnelIfEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(tunnel_mib_tunnelIfEntry_t *));
    if (! *tunnelIfEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*tunnelIfEntry)[i] = assign_tunnelIfEntry(row->data);
    }

    return 0;
}

void
tunnel_mib_free_tunnelIfEntry(tunnel_mib_tunnelIfEntry_t *tunnelIfEntry)
{
    GSList *vbl;
    char *p;

    if (tunnelIfEntry) {
        p = (char *) tunnelIfEntry + sizeof(tunnel_mib_tunnelIfEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(tunnelIfEntry);
    }
}

void
tunnel_mib_free_tunnelIfTable(tunnel_mib_tunnelIfEntry_t **tunnelIfEntry)
{
    int i;

    if (tunnelIfEntry) {
        for (i = 0; tunnelIfEntry[i]; i++) {
            tunnel_mib_free_tunnelIfEntry(tunnelIfEntry[i]);
        }
        g_free(tunnelIfEntry);
    }
}

tunnel_mib_tunnelConfigEntry_t *
tunnel_mib_new_tunnelConfigEntry()
{
    tunnel_mib_tunnelConfigEntry_t *tunnelConfigEntry;

    tunnelConfigEntry = (tunnel_mib_tunnelConfigEntry_t *) g_malloc0(sizeof(tunnel_mib_tunnelConfigEntry_t) + sizeof(gpointer));
    return tunnelConfigEntry;
}

static int
unpack_tunnelConfigEntry(GSnmpVarBind *vb, tunnel_mib_tunnelConfigEntry_t *tunnelConfigEntry)
{
    int i, len, idx = 13;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tunnelConfigEntry->tunnelConfigLocalAddress[i] = vb->id[idx++];
    }
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        tunnelConfigEntry->tunnelConfigRemoteAddress[i] = vb->id[idx++];
    }
    if (vb->id_len < idx) return -1;
    tunnelConfigEntry->tunnelConfigEncapsMethod = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    tunnelConfigEntry->tunnelConfigID = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static tunnel_mib_tunnelConfigEntry_t *
assign_tunnelConfigEntry(GSList *vbl)
{
    GSList *elem;
    tunnel_mib_tunnelConfigEntry_t *tunnelConfigEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 10, 131, 1, 1, 2, 1};

    tunnelConfigEntry = tunnel_mib_new_tunnelConfigEntry();
    if (! tunnelConfigEntry) {
        return NULL;
    }

    p = (char *) tunnelConfigEntry + sizeof(tunnel_mib_tunnelConfigEntry_t);
    * (GSList **) p = vbl;

    if (unpack_tunnelConfigEntry((GSnmpVarBind *) vbl->data, tunnelConfigEntry) < 0) {
        g_warning("illegal tunnelConfigEntry instance identifier");
        g_free(tunnelConfigEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _tunnelConfigEntry, &idx) < 0) continue;

        switch (idx) {
        case 5:
            tunnelConfigEntry->tunnelConfigIfIndex = &(vb->syntax.i32[0]);
            break;
        case 6:
            tunnelConfigEntry->tunnelConfigStatus = &(vb->syntax.i32[0]);
            break;
        };
    }

    return tunnelConfigEntry;
}

int
tunnel_mib_get_tunnelConfigTable(GSnmpSession *s, tunnel_mib_tunnelConfigEntry_t ***tunnelConfigEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 131, 1, 1, 2, 1, 0};

    *tunnelConfigEntry = NULL;

    stls_vbl_attributes(s, &in, base, 12, _tunnelConfigEntry);

    out = stls_snmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *tunnelConfigEntry = (tunnel_mib_tunnelConfigEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(tunnel_mib_tunnelConfigEntry_t *));
    if (! *tunnelConfigEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*tunnelConfigEntry)[i] = assign_tunnelConfigEntry(row->data);
    }

    return 0;
}

void
tunnel_mib_free_tunnelConfigEntry(tunnel_mib_tunnelConfigEntry_t *tunnelConfigEntry)
{
    GSList *vbl;
    char *p;

    if (tunnelConfigEntry) {
        p = (char *) tunnelConfigEntry + sizeof(tunnel_mib_tunnelConfigEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(tunnelConfigEntry);
    }
}

void
tunnel_mib_free_tunnelConfigTable(tunnel_mib_tunnelConfigEntry_t **tunnelConfigEntry)
{
    int i;

    if (tunnelConfigEntry) {
        for (i = 0; tunnelConfigEntry[i]; i++) {
            tunnel_mib_free_tunnelConfigEntry(tunnelConfigEntry[i]);
        }
        g_free(tunnelConfigEntry);
    }
}


