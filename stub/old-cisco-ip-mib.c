/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from OLD-CISCO-IP-MIB:
 *
 * $Id$
 */

#include "old-cisco-ip-mib.h"

typedef struct {
    guint32 const     subid;
    GSnmpVarBindType  type;
    gint              tag;
    gchar            *label;
} attribute_t;

static void
add_attributes(GSnmpSession *s, GSList **vbl, guint32 *base, gsize len,
                guint idx, attribute_t *attributes, gint mask)
{
    int i;

    for (i = 0; attributes[i].label; i++) {
        if (! mask || (mask & attributes[i].tag)) {
            if (attributes[i].type != G_SNMP_COUNTER64
                || s->version > G_SNMP_V1) {
                base[idx] = attributes[i].subid;
                g_snmp_vbl_add_null(vbl, base, len);
            }
        }
    }
}

static int
lookup(GSnmpVarBind *vb, guint32 const *base, gsize const base_len,
	    attribute_t *attributes, guint32 *idx)
{
    int i;

    if (vb->type == G_SNMP_ENDOFMIBVIEW
        || (vb->type == G_SNMP_NOSUCHOBJECT)
        || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
        return -1;
    }
    
    if (memcmp(vb->id, base, base_len * sizeof(guint32)) != 0) {
	return -2;
    }

    for (i = 0; attributes[i].label; i++) {
	if (vb->id_len > base_len && vb->id[base_len] == attributes[i].subid) {
	    if (vb->type != attributes[i].type) {
		g_warning("type tag 0x%02x does not match 0x%02x (%s)",
			  vb->type, attributes[i].type, attributes[i].label);
		return -3;
	    }
	    *idx = attributes[i].subid;
	    return 0;
	}
    }
    
    return -4;
}

static guint32 const oid_lip[] = {1, 3, 6, 1, 4, 1, 9, 2, 4};

static attribute_t attr_lip[] = {
    { 4, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_ACTTHRESH, "actThresh" },
    { 5, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_ACTLOSTPKTS, "actLostPkts" },
    { 6, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_ACTLOSTBYTS, "actLostByts" },
    { 8, G_SNMP_TIMETICKS, OLD_CISCO_IP_MIB_ACTAGE, "actAge" },
    { 10, G_SNMP_TIMETICKS, OLD_CISCO_IP_MIB_CKACTAGE, "ckactAge" },
    { 11, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_ACTCHECKPOINT, "actCheckPoint" },
    { 12, G_SNMP_COUNTER32, OLD_CISCO_IP_MIB_IPNOACCESS, "ipNoaccess" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_lipAddrEntry[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 1, 1};

static attribute_t attr_lipAddrEntry[] = {
    { 1, G_SNMP_OCTET_STRING, OLD_CISCO_IP_MIB_LOCIPHOW, "locIPHow" },
    { 2, G_SNMP_IPADDRESS, OLD_CISCO_IP_MIB_LOCIPWHO, "locIPWho" },
    { 3, G_SNMP_IPADDRESS, OLD_CISCO_IP_MIB_LOCIPHELPER, "locIPHelper" },
    { 4, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_LOCIPSECURITY, "locIPSecurity" },
    { 5, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_LOCIPREDIRECTS, "locIPRedirects" },
    { 6, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_LOCIPUNREACH, "locIPUnreach" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_lipRouteEntry[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 2, 1};

static attribute_t attr_lipRouteEntry[] = {
    { 1, G_SNMP_IPADDRESS, OLD_CISCO_IP_MIB_LOCRTMASK, "locRtMask" },
    { 2, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_LOCRTCOUNT, "locRtCount" },
    { 3, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_LOCRTUSES, "locRtUses" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_lipAccountEntry[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 7, 1};

static attribute_t attr_lipAccountEntry[] = {
    { 3, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_ACTPKTS, "actPkts" },
    { 4, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_ACTBYTS, "actByts" },
    { 5, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_ACTVIOLATION, "actViolation" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_lipCkAccountEntry[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 9, 1};

static attribute_t attr_lipCkAccountEntry[] = {
    { 3, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_CKACTPKTS, "ckactPkts" },
    { 4, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_CKACTBYTS, "ckactByts" },
    { 5, G_SNMP_INTEGER32, OLD_CISCO_IP_MIB_CKACTVIOLATION, "ckactViolation" },
    { 0, 0, 0, NULL }
};


old_cisco_ip_mib_lip_t *
old_cisco_ip_mib_new_lip()
{
    old_cisco_ip_mib_lip_t *lip;

    lip = (old_cisco_ip_mib_lip_t *) g_malloc0(sizeof(old_cisco_ip_mib_lip_t) + sizeof(gpointer));
    return lip;
}

static old_cisco_ip_mib_lip_t *
assign_lip(GSList *vbl)
{
    GSList *elem;
    old_cisco_ip_mib_lip_t *lip;
    guint32 idx;
    char *p;

    lip = old_cisco_ip_mib_new_lip();
    if (! lip) {
        return NULL;
    }

    p = (char *) lip + sizeof(old_cisco_ip_mib_lip_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_lip, sizeof(oid_lip)/sizeof(guint32),
                   attr_lip, &idx) < 0) continue;

        switch (idx) {
        case 4:
            lip->actThresh = &(vb->syntax.i32[0]);
            break;
        case 5:
            lip->actLostPkts = &(vb->syntax.i32[0]);
            break;
        case 6:
            lip->actLostByts = &(vb->syntax.i32[0]);
            break;
        case 8:
            lip->actAge = &(vb->syntax.ui32[0]);
            break;
        case 10:
            lip->ckactAge = &(vb->syntax.ui32[0]);
            break;
        case 11:
            lip->actCheckPoint = &(vb->syntax.i32[0]);
            break;
        case 12:
            lip->ipNoaccess = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return lip;
}

void
old_cisco_ip_mib_get_lip(GSnmpSession *s, old_cisco_ip_mib_lip_t **lip, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 0};

    *lip = NULL;

    add_attributes(s, &in, base, 10, 9, attr_lip, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *lip = assign_lip(out);
    }
}

void
old_cisco_ip_mib_set_lip(GSnmpSession *s, old_cisco_ip_mib_lip_t *lip, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 0, 0};

    if (lip->actCheckPoint) {
        base[9] = 11;
        g_snmp_vbl_add(&in, base, sizeof(base)/sizeof(guint32),
                       G_SNMP_INTEGER32,
                       lip->actCheckPoint,
                       0);
    }

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
old_cisco_ip_mib_free_lip(old_cisco_ip_mib_lip_t *lip)
{
    GSList *vbl;
    char *p;

    if (lip) {
        p = (char *) lip + sizeof(old_cisco_ip_mib_lip_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(lip);
    }
}

old_cisco_ip_mib_lipAddrEntry_t *
old_cisco_ip_mib_new_lipAddrEntry()
{
    old_cisco_ip_mib_lipAddrEntry_t *lipAddrEntry;

    lipAddrEntry = (old_cisco_ip_mib_lipAddrEntry_t *) g_malloc0(sizeof(old_cisco_ip_mib_lipAddrEntry_t) + sizeof(gpointer));
    return lipAddrEntry;
}

static int
unpack_lipAddrEntry(GSnmpVarBind *vb, old_cisco_ip_mib_lipAddrEntry_t *lipAddrEntry)
{
    int i, len, idx = 12;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        lipAddrEntry->ipAdEntAddr[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_lipAddrEntry(guint32 *base, guchar *ipAdEntAddr)
{
    int i, len, idx = 12;

    len = 4;
    for (i = 0; i < len; i++) {
        base[idx++] = ipAdEntAddr[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static old_cisco_ip_mib_lipAddrEntry_t *
assign_lipAddrEntry(GSList *vbl)
{
    GSList *elem;
    old_cisco_ip_mib_lipAddrEntry_t *lipAddrEntry;
    guint32 idx;
    char *p;

    lipAddrEntry = old_cisco_ip_mib_new_lipAddrEntry();
    if (! lipAddrEntry) {
        return NULL;
    }

    p = (char *) lipAddrEntry + sizeof(old_cisco_ip_mib_lipAddrEntry_t);
    * (GSList **) p = vbl;

    if (unpack_lipAddrEntry((GSnmpVarBind *) vbl->data, lipAddrEntry) < 0) {
        g_warning("illegal lipAddrEntry instance identifier");
        g_free(lipAddrEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_lipAddrEntry, sizeof(oid_lipAddrEntry)/sizeof(guint32),
                   attr_lipAddrEntry, &idx) < 0) continue;

        switch (idx) {
        case 1:
            lipAddrEntry->_locIPHowLength = vb->syntax_len;
            lipAddrEntry->locIPHow = vb->syntax.uc;
            break;
        case 2:
            lipAddrEntry->locIPWho = vb->syntax.uc;
            break;
        case 3:
            lipAddrEntry->locIPHelper = vb->syntax.uc;
            break;
        case 4:
            lipAddrEntry->locIPSecurity = &(vb->syntax.i32[0]);
            break;
        case 5:
            lipAddrEntry->locIPRedirects = &(vb->syntax.i32[0]);
            break;
        case 6:
            lipAddrEntry->locIPUnreach = &(vb->syntax.i32[0]);
            break;
        };
    }

    return lipAddrEntry;
}

void
old_cisco_ip_mib_get_lipAddrTable(GSnmpSession *s, old_cisco_ip_mib_lipAddrEntry_t ***lipAddrEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 1, 1, 0};

    *lipAddrEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_lipAddrEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *lipAddrEntry = (old_cisco_ip_mib_lipAddrEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(old_cisco_ip_mib_lipAddrEntry_t *));
        if (! *lipAddrEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*lipAddrEntry)[i] = assign_lipAddrEntry(row->data);
        }
    }
}

void
old_cisco_ip_mib_get_lipAddrEntry(GSnmpSession *s, old_cisco_ip_mib_lipAddrEntry_t **lipAddrEntry, guchar *ipAdEntAddr, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    int len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_lipAddrEntry, sizeof(oid_lipAddrEntry));
    len = pack_lipAddrEntry(base, ipAdEntAddr);
    if (len < 0) {
        g_warning("illegal lipAddrEntry index values");
        return;
    }

    *lipAddrEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_lipAddrEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *lipAddrEntry = assign_lipAddrEntry(out);
    }
}

void
old_cisco_ip_mib_free_lipAddrEntry(old_cisco_ip_mib_lipAddrEntry_t *lipAddrEntry)
{
    GSList *vbl;
    char *p;

    if (lipAddrEntry) {
        p = (char *) lipAddrEntry + sizeof(old_cisco_ip_mib_lipAddrEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(lipAddrEntry);
    }
}

void
old_cisco_ip_mib_free_lipAddrTable(old_cisco_ip_mib_lipAddrEntry_t **lipAddrEntry)
{
    int i;

    if (lipAddrEntry) {
        for (i = 0; lipAddrEntry[i]; i++) {
            old_cisco_ip_mib_free_lipAddrEntry(lipAddrEntry[i]);
        }
        g_free(lipAddrEntry);
    }
}

old_cisco_ip_mib_lipRouteEntry_t *
old_cisco_ip_mib_new_lipRouteEntry()
{
    old_cisco_ip_mib_lipRouteEntry_t *lipRouteEntry;

    lipRouteEntry = (old_cisco_ip_mib_lipRouteEntry_t *) g_malloc0(sizeof(old_cisco_ip_mib_lipRouteEntry_t) + sizeof(gpointer));
    return lipRouteEntry;
}

static int
unpack_lipRouteEntry(GSnmpVarBind *vb, old_cisco_ip_mib_lipRouteEntry_t *lipRouteEntry)
{
    int i, len, idx = 12;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        lipRouteEntry->ipRouteDest[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_lipRouteEntry(guint32 *base, guchar *ipRouteDest)
{
    int i, len, idx = 12;

    len = 4;
    for (i = 0; i < len; i++) {
        base[idx++] = ipRouteDest[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static old_cisco_ip_mib_lipRouteEntry_t *
assign_lipRouteEntry(GSList *vbl)
{
    GSList *elem;
    old_cisco_ip_mib_lipRouteEntry_t *lipRouteEntry;
    guint32 idx;
    char *p;

    lipRouteEntry = old_cisco_ip_mib_new_lipRouteEntry();
    if (! lipRouteEntry) {
        return NULL;
    }

    p = (char *) lipRouteEntry + sizeof(old_cisco_ip_mib_lipRouteEntry_t);
    * (GSList **) p = vbl;

    if (unpack_lipRouteEntry((GSnmpVarBind *) vbl->data, lipRouteEntry) < 0) {
        g_warning("illegal lipRouteEntry instance identifier");
        g_free(lipRouteEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_lipRouteEntry, sizeof(oid_lipRouteEntry)/sizeof(guint32),
                   attr_lipRouteEntry, &idx) < 0) continue;

        switch (idx) {
        case 1:
            lipRouteEntry->locRtMask = vb->syntax.uc;
            break;
        case 2:
            lipRouteEntry->locRtCount = &(vb->syntax.i32[0]);
            break;
        case 3:
            lipRouteEntry->locRtUses = &(vb->syntax.i32[0]);
            break;
        };
    }

    return lipRouteEntry;
}

void
old_cisco_ip_mib_get_lipRouteTable(GSnmpSession *s, old_cisco_ip_mib_lipRouteEntry_t ***lipRouteEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 2, 1, 0};

    *lipRouteEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_lipRouteEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *lipRouteEntry = (old_cisco_ip_mib_lipRouteEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(old_cisco_ip_mib_lipRouteEntry_t *));
        if (! *lipRouteEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*lipRouteEntry)[i] = assign_lipRouteEntry(row->data);
        }
    }
}

void
old_cisco_ip_mib_get_lipRouteEntry(GSnmpSession *s, old_cisco_ip_mib_lipRouteEntry_t **lipRouteEntry, guchar *ipRouteDest, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    int len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_lipRouteEntry, sizeof(oid_lipRouteEntry));
    len = pack_lipRouteEntry(base, ipRouteDest);
    if (len < 0) {
        g_warning("illegal lipRouteEntry index values");
        return;
    }

    *lipRouteEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_lipRouteEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *lipRouteEntry = assign_lipRouteEntry(out);
    }
}

void
old_cisco_ip_mib_free_lipRouteEntry(old_cisco_ip_mib_lipRouteEntry_t *lipRouteEntry)
{
    GSList *vbl;
    char *p;

    if (lipRouteEntry) {
        p = (char *) lipRouteEntry + sizeof(old_cisco_ip_mib_lipRouteEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(lipRouteEntry);
    }
}

void
old_cisco_ip_mib_free_lipRouteTable(old_cisco_ip_mib_lipRouteEntry_t **lipRouteEntry)
{
    int i;

    if (lipRouteEntry) {
        for (i = 0; lipRouteEntry[i]; i++) {
            old_cisco_ip_mib_free_lipRouteEntry(lipRouteEntry[i]);
        }
        g_free(lipRouteEntry);
    }
}

old_cisco_ip_mib_lipAccountEntry_t *
old_cisco_ip_mib_new_lipAccountEntry()
{
    old_cisco_ip_mib_lipAccountEntry_t *lipAccountEntry;

    lipAccountEntry = (old_cisco_ip_mib_lipAccountEntry_t *) g_malloc0(sizeof(old_cisco_ip_mib_lipAccountEntry_t) + sizeof(gpointer));
    return lipAccountEntry;
}

static int
unpack_lipAccountEntry(GSnmpVarBind *vb, old_cisco_ip_mib_lipAccountEntry_t *lipAccountEntry)
{
    int i, len, idx = 12;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        lipAccountEntry->actSrc[i] = vb->id[idx++];
    }
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        lipAccountEntry->actDst[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_lipAccountEntry(guint32 *base, guchar *actSrc, guchar *actDst)
{
    int i, len, idx = 12;

    len = 4;
    for (i = 0; i < len; i++) {
        base[idx++] = actSrc[i];
        if (idx >= 128) return -1;
    }
    len = 4;
    for (i = 0; i < len; i++) {
        base[idx++] = actDst[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static old_cisco_ip_mib_lipAccountEntry_t *
assign_lipAccountEntry(GSList *vbl)
{
    GSList *elem;
    old_cisco_ip_mib_lipAccountEntry_t *lipAccountEntry;
    guint32 idx;
    char *p;

    lipAccountEntry = old_cisco_ip_mib_new_lipAccountEntry();
    if (! lipAccountEntry) {
        return NULL;
    }

    p = (char *) lipAccountEntry + sizeof(old_cisco_ip_mib_lipAccountEntry_t);
    * (GSList **) p = vbl;

    if (unpack_lipAccountEntry((GSnmpVarBind *) vbl->data, lipAccountEntry) < 0) {
        g_warning("illegal lipAccountEntry instance identifier");
        g_free(lipAccountEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_lipAccountEntry, sizeof(oid_lipAccountEntry)/sizeof(guint32),
                   attr_lipAccountEntry, &idx) < 0) continue;

        switch (idx) {
        case 3:
            lipAccountEntry->actPkts = &(vb->syntax.i32[0]);
            break;
        case 4:
            lipAccountEntry->actByts = &(vb->syntax.i32[0]);
            break;
        case 5:
            lipAccountEntry->actViolation = &(vb->syntax.i32[0]);
            break;
        };
    }

    return lipAccountEntry;
}

void
old_cisco_ip_mib_get_lipAccountingTable(GSnmpSession *s, old_cisco_ip_mib_lipAccountEntry_t ***lipAccountEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 7, 1, 0};

    *lipAccountEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_lipAccountEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *lipAccountEntry = (old_cisco_ip_mib_lipAccountEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(old_cisco_ip_mib_lipAccountEntry_t *));
        if (! *lipAccountEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*lipAccountEntry)[i] = assign_lipAccountEntry(row->data);
        }
    }
}

void
old_cisco_ip_mib_get_lipAccountEntry(GSnmpSession *s, old_cisco_ip_mib_lipAccountEntry_t **lipAccountEntry, guchar *actSrc, guchar *actDst, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    int len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_lipAccountEntry, sizeof(oid_lipAccountEntry));
    len = pack_lipAccountEntry(base, actSrc, actDst);
    if (len < 0) {
        g_warning("illegal lipAccountEntry index values");
        return;
    }

    *lipAccountEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_lipAccountEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *lipAccountEntry = assign_lipAccountEntry(out);
    }
}

void
old_cisco_ip_mib_free_lipAccountEntry(old_cisco_ip_mib_lipAccountEntry_t *lipAccountEntry)
{
    GSList *vbl;
    char *p;

    if (lipAccountEntry) {
        p = (char *) lipAccountEntry + sizeof(old_cisco_ip_mib_lipAccountEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(lipAccountEntry);
    }
}

void
old_cisco_ip_mib_free_lipAccountingTable(old_cisco_ip_mib_lipAccountEntry_t **lipAccountEntry)
{
    int i;

    if (lipAccountEntry) {
        for (i = 0; lipAccountEntry[i]; i++) {
            old_cisco_ip_mib_free_lipAccountEntry(lipAccountEntry[i]);
        }
        g_free(lipAccountEntry);
    }
}

old_cisco_ip_mib_lipCkAccountEntry_t *
old_cisco_ip_mib_new_lipCkAccountEntry()
{
    old_cisco_ip_mib_lipCkAccountEntry_t *lipCkAccountEntry;

    lipCkAccountEntry = (old_cisco_ip_mib_lipCkAccountEntry_t *) g_malloc0(sizeof(old_cisco_ip_mib_lipCkAccountEntry_t) + sizeof(gpointer));
    return lipCkAccountEntry;
}

static int
unpack_lipCkAccountEntry(GSnmpVarBind *vb, old_cisco_ip_mib_lipCkAccountEntry_t *lipCkAccountEntry)
{
    int i, len, idx = 12;

    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        lipCkAccountEntry->ckactSrc[i] = vb->id[idx++];
    }
    len = 4;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        lipCkAccountEntry->ckactDst[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static int
pack_lipCkAccountEntry(guint32 *base, guchar *ckactSrc, guchar *ckactDst)
{
    int i, len, idx = 12;

    len = 4;
    for (i = 0; i < len; i++) {
        base[idx++] = ckactSrc[i];
        if (idx >= 128) return -1;
    }
    len = 4;
    for (i = 0; i < len; i++) {
        base[idx++] = ckactDst[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static old_cisco_ip_mib_lipCkAccountEntry_t *
assign_lipCkAccountEntry(GSList *vbl)
{
    GSList *elem;
    old_cisco_ip_mib_lipCkAccountEntry_t *lipCkAccountEntry;
    guint32 idx;
    char *p;

    lipCkAccountEntry = old_cisco_ip_mib_new_lipCkAccountEntry();
    if (! lipCkAccountEntry) {
        return NULL;
    }

    p = (char *) lipCkAccountEntry + sizeof(old_cisco_ip_mib_lipCkAccountEntry_t);
    * (GSList **) p = vbl;

    if (unpack_lipCkAccountEntry((GSnmpVarBind *) vbl->data, lipCkAccountEntry) < 0) {
        g_warning("illegal lipCkAccountEntry instance identifier");
        g_free(lipCkAccountEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_lipCkAccountEntry, sizeof(oid_lipCkAccountEntry)/sizeof(guint32),
                   attr_lipCkAccountEntry, &idx) < 0) continue;

        switch (idx) {
        case 3:
            lipCkAccountEntry->ckactPkts = &(vb->syntax.i32[0]);
            break;
        case 4:
            lipCkAccountEntry->ckactByts = &(vb->syntax.i32[0]);
            break;
        case 5:
            lipCkAccountEntry->ckactViolation = &(vb->syntax.i32[0]);
            break;
        };
    }

    return lipCkAccountEntry;
}

void
old_cisco_ip_mib_get_lipCkAccountingTable(GSnmpSession *s, old_cisco_ip_mib_lipCkAccountEntry_t ***lipCkAccountEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 4, 1, 9, 2, 4, 9, 1, 0};

    *lipCkAccountEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_lipCkAccountEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *lipCkAccountEntry = (old_cisco_ip_mib_lipCkAccountEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(old_cisco_ip_mib_lipCkAccountEntry_t *));
        if (! *lipCkAccountEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*lipCkAccountEntry)[i] = assign_lipCkAccountEntry(row->data);
        }
    }
}

void
old_cisco_ip_mib_get_lipCkAccountEntry(GSnmpSession *s, old_cisco_ip_mib_lipCkAccountEntry_t **lipCkAccountEntry, guchar *ckactSrc, guchar *ckactDst, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    int len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_lipCkAccountEntry, sizeof(oid_lipCkAccountEntry));
    len = pack_lipCkAccountEntry(base, ckactSrc, ckactDst);
    if (len < 0) {
        g_warning("illegal lipCkAccountEntry index values");
        return;
    }

    *lipCkAccountEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_lipCkAccountEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *lipCkAccountEntry = assign_lipCkAccountEntry(out);
    }
}

void
old_cisco_ip_mib_free_lipCkAccountEntry(old_cisco_ip_mib_lipCkAccountEntry_t *lipCkAccountEntry)
{
    GSList *vbl;
    char *p;

    if (lipCkAccountEntry) {
        p = (char *) lipCkAccountEntry + sizeof(old_cisco_ip_mib_lipCkAccountEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(lipCkAccountEntry);
    }
}

void
old_cisco_ip_mib_free_lipCkAccountingTable(old_cisco_ip_mib_lipCkAccountEntry_t **lipCkAccountEntry)
{
    int i;

    if (lipCkAccountEntry) {
        for (i = 0; lipCkAccountEntry[i]; i++) {
            old_cisco_ip_mib_free_lipCkAccountEntry(lipCkAccountEntry[i]);
        }
        g_free(lipCkAccountEntry);
    }
}


