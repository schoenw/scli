/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from BRIDGE-MIB:
 *
 * $Id$
 */

#include "bridge-mib.h"

stls_table_t const bridge_mib_enums_dot1dBaseType[] = {
    { 1, "unknown" },
    { 2, "transparent-only" },
    { 3, "sourceroute-only" },
    { 4, "srt" },
    { 0, NULL }
};

stls_table_t const bridge_mib_enums_dot1dStpProtocolSpecification[] = {
    { 1, "unknown" },
    { 2, "decLb100" },
    { 3, "ieee8021d" },
    { 0, NULL }
};

stls_table_t const bridge_mib_enums_dot1dStpPortState[] = {
    { 1, "disabled" },
    { 2, "blocking" },
    { 3, "listening" },
    { 4, "learning" },
    { 5, "forwarding" },
    { 6, "broken" },
    { 0, NULL }
};

stls_table_t const bridge_mib_enums_dot1dStpPortEnable[] = {
    { 1, "enabled" },
    { 2, "disabled" },
    { 0, NULL }
};

stls_table_t const bridge_mib_enums_dot1dTpFdbStatus[] = {
    { 1, "other" },
    { 2, "invalid" },
    { 3, "learned" },
    { 4, "self" },
    { 5, "mgmt" },
    { 0, NULL }
};

stls_table_t const bridge_mib_enums_dot1dStaticStatus[] = {
    { 1, "other" },
    { 2, "invalid" },
    { 3, "permanent" },
    { 4, "deleteOnReset" },
    { 5, "deleteOnTimeout" },
    { 0, NULL }
};


dot1dBase_t *
bridge_mib_new_dot1dBase()
{
    dot1dBase_t *dot1dBase;

    dot1dBase = (dot1dBase_t *) g_malloc0(sizeof(dot1dBase_t) + sizeof(gpointer));
    return dot1dBase;
}

static dot1dBase_t *
assign_dot1dBase(GSList *vbl)
{
    GSList *elem;
    dot1dBase_t *dot1dBase;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 1};

    dot1dBase = bridge_mib_new_dot1dBase();
    if (! dot1dBase) {
        return NULL;
    }

    p = (char *) dot1dBase + sizeof(dot1dBase_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 9 && vb->id[8] == 1) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                dot1dBase->dot1dBaseBridgeAddress = vb->syntax.uc;
            } else {
                g_warning("illegal type for dot1dBaseBridgeAddress");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 2) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dBase->dot1dBaseNumPorts = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dBaseNumPorts");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 3) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dBase->dot1dBaseType = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dBaseType");
            }
        }
    }

    return dot1dBase;
}

int
bridge_mib_get_dot1dBase(host_snmp *s, dot1dBase_t **dot1dBase)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 1, 0};

    *dot1dBase = NULL;

    base[8] = 1; stls_vbl_add_null(&in, base, 9);
    base[8] = 2; stls_vbl_add_null(&in, base, 9);
    base[8] = 3; stls_vbl_add_null(&in, base, 9);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *dot1dBase = assign_dot1dBase(out);

    return 0;
}

void
bridge_mib_free_dot1dBase(dot1dBase_t *dot1dBase)
{
    GSList *vbl;
    char *p;

    if (dot1dBase) {
        p = (char *) dot1dBase + sizeof(dot1dBase_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dBase);
    }
}

dot1dBasePortEntry_t *
bridge_mib_new_dot1dBasePortEntry()
{
    dot1dBasePortEntry_t *dot1dBasePortEntry;

    dot1dBasePortEntry = (dot1dBasePortEntry_t *) g_malloc0(sizeof(dot1dBasePortEntry_t) + sizeof(gpointer));
    return dot1dBasePortEntry;
}

static int
unpack_dot1dBasePortEntry(GSnmpVarBind *vb, dot1dBasePortEntry_t *dot1dBasePortEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    dot1dBasePortEntry->dot1dBasePort = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static dot1dBasePortEntry_t *
assign_dot1dBasePortEntry(GSList *vbl)
{
    GSList *elem;
    dot1dBasePortEntry_t *dot1dBasePortEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 1, 4, 1};

    dot1dBasePortEntry = bridge_mib_new_dot1dBasePortEntry();
    if (! dot1dBasePortEntry) {
        return NULL;
    }

    p = (char *) dot1dBasePortEntry + sizeof(dot1dBasePortEntry_t);
    * (GSList **) p = vbl;

    if (unpack_dot1dBasePortEntry((GSnmpVarBind *) vbl->data, dot1dBasePortEntry) < 0) {
        g_warning("illegal dot1dBasePortEntry instance identifier");
        g_free(dot1dBasePortEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 2) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dBasePortEntry->dot1dBasePortIfIndex = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dBasePortIfIndex");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            if (vb->type == G_SNMP_OBJECT_ID) {
                dot1dBasePortEntry->_dot1dBasePortCircuitLength = vb->syntax_len / sizeof(guint32);
                dot1dBasePortEntry->dot1dBasePortCircuit = vb->syntax.ui32;
            } else {
                g_warning("illegal type for dot1dBasePortCircuit");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dBasePortEntry->dot1dBasePortDelayExceededDiscards = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dBasePortDelayExceededDiscards");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dBasePortEntry->dot1dBasePortMtuExceededDiscards = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dBasePortMtuExceededDiscards");
            }
        }
    }

    return dot1dBasePortEntry;
}

int
bridge_mib_get_dot1dBasePortTable(host_snmp *s, dot1dBasePortEntry_t ***dot1dBasePortEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 1, 4, 1, 0};

    *dot1dBasePortEntry = NULL;

    base[10] = 2; stls_vbl_add_null(&in, base, 11);
    base[10] = 3; stls_vbl_add_null(&in, base, 11);
    base[10] = 4; stls_vbl_add_null(&in, base, 11);
    base[10] = 5; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *dot1dBasePortEntry = (dot1dBasePortEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(dot1dBasePortEntry_t *));
    if (! *dot1dBasePortEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*dot1dBasePortEntry)[i] = assign_dot1dBasePortEntry(row->data);
    }

    return 0;
}

void
bridge_mib_free_dot1dBasePortEntry(dot1dBasePortEntry_t *dot1dBasePortEntry)
{
    GSList *vbl;
    char *p;

    if (dot1dBasePortEntry) {
        p = (char *) dot1dBasePortEntry + sizeof(dot1dBasePortEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dBasePortEntry);
    }
}

void
bridge_mib_free_dot1dBasePortTable(dot1dBasePortEntry_t **dot1dBasePortEntry)
{
    int i;

    if (dot1dBasePortEntry) {
        for (i = 0; dot1dBasePortEntry[i]; i++) {
            bridge_mib_free_dot1dBasePortEntry(dot1dBasePortEntry[i]);
        }
        g_free(dot1dBasePortEntry);
    }
}

dot1dStp_t *
bridge_mib_new_dot1dStp()
{
    dot1dStp_t *dot1dStp;

    dot1dStp = (dot1dStp_t *) g_malloc0(sizeof(dot1dStp_t) + sizeof(gpointer));
    return dot1dStp;
}

static dot1dStp_t *
assign_dot1dStp(GSList *vbl)
{
    GSList *elem;
    dot1dStp_t *dot1dStp;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 2};

    dot1dStp = bridge_mib_new_dot1dStp();
    if (! dot1dStp) {
        return NULL;
    }

    p = (char *) dot1dStp + sizeof(dot1dStp_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 9 && vb->id[8] == 1) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpProtocolSpecification = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpProtocolSpecification");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 2) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpPriority = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpPriority");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 3) {
            if (vb->type == G_SNMP_TIMETICKS) {
                dot1dStp->dot1dStpTimeSinceTopologyChange = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dStpTimeSinceTopologyChange");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 4) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dStp->dot1dStpTopChanges = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dStpTopChanges");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 5) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                dot1dStp->dot1dStpDesignatedRoot = vb->syntax.uc;
            } else {
                g_warning("illegal type for dot1dStpDesignatedRoot");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 6) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpRootCost = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpRootCost");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 7) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpRootPort = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpRootPort");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 8) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpMaxAge = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpMaxAge");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 9) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpHelloTime = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpHelloTime");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 10) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpHoldTime = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpHoldTime");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 11) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpForwardDelay = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpForwardDelay");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 12) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpBridgeMaxAge = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpBridgeMaxAge");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 13) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpBridgeHelloTime = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpBridgeHelloTime");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 14) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStp->dot1dStpBridgeForwardDelay = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpBridgeForwardDelay");
            }
        }
    }

    return dot1dStp;
}

int
bridge_mib_get_dot1dStp(host_snmp *s, dot1dStp_t **dot1dStp)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 2, 0};

    *dot1dStp = NULL;

    base[8] = 1; stls_vbl_add_null(&in, base, 9);
    base[8] = 2; stls_vbl_add_null(&in, base, 9);
    base[8] = 3; stls_vbl_add_null(&in, base, 9);
    base[8] = 4; stls_vbl_add_null(&in, base, 9);
    base[8] = 5; stls_vbl_add_null(&in, base, 9);
    base[8] = 6; stls_vbl_add_null(&in, base, 9);
    base[8] = 7; stls_vbl_add_null(&in, base, 9);
    base[8] = 8; stls_vbl_add_null(&in, base, 9);
    base[8] = 9; stls_vbl_add_null(&in, base, 9);
    base[8] = 10; stls_vbl_add_null(&in, base, 9);
    base[8] = 11; stls_vbl_add_null(&in, base, 9);
    base[8] = 12; stls_vbl_add_null(&in, base, 9);
    base[8] = 13; stls_vbl_add_null(&in, base, 9);
    base[8] = 14; stls_vbl_add_null(&in, base, 9);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *dot1dStp = assign_dot1dStp(out);

    return 0;
}

void
bridge_mib_free_dot1dStp(dot1dStp_t *dot1dStp)
{
    GSList *vbl;
    char *p;

    if (dot1dStp) {
        p = (char *) dot1dStp + sizeof(dot1dStp_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dStp);
    }
}

dot1dStpPortEntry_t *
bridge_mib_new_dot1dStpPortEntry()
{
    dot1dStpPortEntry_t *dot1dStpPortEntry;

    dot1dStpPortEntry = (dot1dStpPortEntry_t *) g_malloc0(sizeof(dot1dStpPortEntry_t) + sizeof(gpointer));
    return dot1dStpPortEntry;
}

static int
unpack_dot1dStpPortEntry(GSnmpVarBind *vb, dot1dStpPortEntry_t *dot1dStpPortEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    dot1dStpPortEntry->dot1dStpPort = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static dot1dStpPortEntry_t *
assign_dot1dStpPortEntry(GSList *vbl)
{
    GSList *elem;
    dot1dStpPortEntry_t *dot1dStpPortEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 2, 15, 1};

    dot1dStpPortEntry = bridge_mib_new_dot1dStpPortEntry();
    if (! dot1dStpPortEntry) {
        return NULL;
    }

    p = (char *) dot1dStpPortEntry + sizeof(dot1dStpPortEntry_t);
    * (GSList **) p = vbl;

    if (unpack_dot1dStpPortEntry((GSnmpVarBind *) vbl->data, dot1dStpPortEntry) < 0) {
        g_warning("illegal dot1dStpPortEntry instance identifier");
        g_free(dot1dStpPortEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 2) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStpPortEntry->dot1dStpPortPriority = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpPortPriority");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStpPortEntry->dot1dStpPortState = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpPortState");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStpPortEntry->dot1dStpPortEnable = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpPortEnable");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStpPortEntry->dot1dStpPortPathCost = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpPortPathCost");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                dot1dStpPortEntry->dot1dStpPortDesignatedRoot = vb->syntax.uc;
            } else {
                g_warning("illegal type for dot1dStpPortDesignatedRoot");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 7) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStpPortEntry->dot1dStpPortDesignatedCost = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStpPortDesignatedCost");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 8) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                dot1dStpPortEntry->dot1dStpPortDesignatedBridge = vb->syntax.uc;
            } else {
                g_warning("illegal type for dot1dStpPortDesignatedBridge");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 9) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                dot1dStpPortEntry->dot1dStpPortDesignatedPort = vb->syntax.uc;
            } else {
                g_warning("illegal type for dot1dStpPortDesignatedPort");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 10) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dStpPortEntry->dot1dStpPortForwardTransitions = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dStpPortForwardTransitions");
            }
        }
    }

    return dot1dStpPortEntry;
}

int
bridge_mib_get_dot1dStpPortTable(host_snmp *s, dot1dStpPortEntry_t ***dot1dStpPortEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 2, 15, 1, 0};

    *dot1dStpPortEntry = NULL;

    base[10] = 2; stls_vbl_add_null(&in, base, 11);
    base[10] = 3; stls_vbl_add_null(&in, base, 11);
    base[10] = 4; stls_vbl_add_null(&in, base, 11);
    base[10] = 5; stls_vbl_add_null(&in, base, 11);
    base[10] = 6; stls_vbl_add_null(&in, base, 11);
    base[10] = 7; stls_vbl_add_null(&in, base, 11);
    base[10] = 8; stls_vbl_add_null(&in, base, 11);
    base[10] = 9; stls_vbl_add_null(&in, base, 11);
    base[10] = 10; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *dot1dStpPortEntry = (dot1dStpPortEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(dot1dStpPortEntry_t *));
    if (! *dot1dStpPortEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*dot1dStpPortEntry)[i] = assign_dot1dStpPortEntry(row->data);
    }

    return 0;
}

void
bridge_mib_free_dot1dStpPortEntry(dot1dStpPortEntry_t *dot1dStpPortEntry)
{
    GSList *vbl;
    char *p;

    if (dot1dStpPortEntry) {
        p = (char *) dot1dStpPortEntry + sizeof(dot1dStpPortEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dStpPortEntry);
    }
}

void
bridge_mib_free_dot1dStpPortTable(dot1dStpPortEntry_t **dot1dStpPortEntry)
{
    int i;

    if (dot1dStpPortEntry) {
        for (i = 0; dot1dStpPortEntry[i]; i++) {
            bridge_mib_free_dot1dStpPortEntry(dot1dStpPortEntry[i]);
        }
        g_free(dot1dStpPortEntry);
    }
}

dot1dTp_t *
bridge_mib_new_dot1dTp()
{
    dot1dTp_t *dot1dTp;

    dot1dTp = (dot1dTp_t *) g_malloc0(sizeof(dot1dTp_t) + sizeof(gpointer));
    return dot1dTp;
}

static dot1dTp_t *
assign_dot1dTp(GSList *vbl)
{
    GSList *elem;
    dot1dTp_t *dot1dTp;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 4};

    dot1dTp = bridge_mib_new_dot1dTp();
    if (! dot1dTp) {
        return NULL;
    }

    p = (char *) dot1dTp + sizeof(dot1dTp_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 9 && vb->id[8] == 1) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dTp->dot1dTpLearnedEntryDiscards = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dTpLearnedEntryDiscards");
            }
        }
        if (vb->id_len > 9 && vb->id[8] == 2) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dTp->dot1dTpAgingTime = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dTpAgingTime");
            }
        }
    }

    return dot1dTp;
}

int
bridge_mib_get_dot1dTp(host_snmp *s, dot1dTp_t **dot1dTp)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 4, 0};

    *dot1dTp = NULL;

    base[8] = 1; stls_vbl_add_null(&in, base, 9);
    base[8] = 2; stls_vbl_add_null(&in, base, 9);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *dot1dTp = assign_dot1dTp(out);

    return 0;
}

void
bridge_mib_free_dot1dTp(dot1dTp_t *dot1dTp)
{
    GSList *vbl;
    char *p;

    if (dot1dTp) {
        p = (char *) dot1dTp + sizeof(dot1dTp_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dTp);
    }
}

dot1dTpFdbEntry_t *
bridge_mib_new_dot1dTpFdbEntry()
{
    dot1dTpFdbEntry_t *dot1dTpFdbEntry;

    dot1dTpFdbEntry = (dot1dTpFdbEntry_t *) g_malloc0(sizeof(dot1dTpFdbEntry_t) + sizeof(gpointer));
    return dot1dTpFdbEntry;
}

static int
unpack_dot1dTpFdbEntry(GSnmpVarBind *vb, dot1dTpFdbEntry_t *dot1dTpFdbEntry)
{
    int i, len, idx = 11;

    len = 6;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        dot1dTpFdbEntry->dot1dTpFdbAddress[i] = vb->id[idx++];
    }
    if (vb->id_len > idx) return -1;
    return 0;
}

static dot1dTpFdbEntry_t *
assign_dot1dTpFdbEntry(GSList *vbl)
{
    GSList *elem;
    dot1dTpFdbEntry_t *dot1dTpFdbEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 4, 3, 1};

    dot1dTpFdbEntry = bridge_mib_new_dot1dTpFdbEntry();
    if (! dot1dTpFdbEntry) {
        return NULL;
    }

    p = (char *) dot1dTpFdbEntry + sizeof(dot1dTpFdbEntry_t);
    * (GSList **) p = vbl;

    if (unpack_dot1dTpFdbEntry((GSnmpVarBind *) vbl->data, dot1dTpFdbEntry) < 0) {
        g_warning("illegal dot1dTpFdbEntry instance identifier");
        g_free(dot1dTpFdbEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 2) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dTpFdbEntry->dot1dTpFdbPort = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dTpFdbPort");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dTpFdbEntry->dot1dTpFdbStatus = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dTpFdbStatus");
            }
        }
    }

    return dot1dTpFdbEntry;
}

int
bridge_mib_get_dot1dTpFdbTable(host_snmp *s, dot1dTpFdbEntry_t ***dot1dTpFdbEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 4, 3, 1, 0};

    *dot1dTpFdbEntry = NULL;

    base[10] = 2; stls_vbl_add_null(&in, base, 11);
    base[10] = 3; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *dot1dTpFdbEntry = (dot1dTpFdbEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(dot1dTpFdbEntry_t *));
    if (! *dot1dTpFdbEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*dot1dTpFdbEntry)[i] = assign_dot1dTpFdbEntry(row->data);
    }

    return 0;
}

void
bridge_mib_free_dot1dTpFdbEntry(dot1dTpFdbEntry_t *dot1dTpFdbEntry)
{
    GSList *vbl;
    char *p;

    if (dot1dTpFdbEntry) {
        p = (char *) dot1dTpFdbEntry + sizeof(dot1dTpFdbEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dTpFdbEntry);
    }
}

void
bridge_mib_free_dot1dTpFdbTable(dot1dTpFdbEntry_t **dot1dTpFdbEntry)
{
    int i;

    if (dot1dTpFdbEntry) {
        for (i = 0; dot1dTpFdbEntry[i]; i++) {
            bridge_mib_free_dot1dTpFdbEntry(dot1dTpFdbEntry[i]);
        }
        g_free(dot1dTpFdbEntry);
    }
}

dot1dTpPortEntry_t *
bridge_mib_new_dot1dTpPortEntry()
{
    dot1dTpPortEntry_t *dot1dTpPortEntry;

    dot1dTpPortEntry = (dot1dTpPortEntry_t *) g_malloc0(sizeof(dot1dTpPortEntry_t) + sizeof(gpointer));
    return dot1dTpPortEntry;
}

static int
unpack_dot1dTpPortEntry(GSnmpVarBind *vb, dot1dTpPortEntry_t *dot1dTpPortEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    dot1dTpPortEntry->dot1dTpPort = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static dot1dTpPortEntry_t *
assign_dot1dTpPortEntry(GSList *vbl)
{
    GSList *elem;
    dot1dTpPortEntry_t *dot1dTpPortEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 4, 4, 1};

    dot1dTpPortEntry = bridge_mib_new_dot1dTpPortEntry();
    if (! dot1dTpPortEntry) {
        return NULL;
    }

    p = (char *) dot1dTpPortEntry + sizeof(dot1dTpPortEntry_t);
    * (GSList **) p = vbl;

    if (unpack_dot1dTpPortEntry((GSnmpVarBind *) vbl->data, dot1dTpPortEntry) < 0) {
        g_warning("illegal dot1dTpPortEntry instance identifier");
        g_free(dot1dTpPortEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 2) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dTpPortEntry->dot1dTpPortMaxInfo = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dTpPortMaxInfo");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dTpPortEntry->dot1dTpPortInFrames = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dTpPortInFrames");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dTpPortEntry->dot1dTpPortOutFrames = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dTpPortOutFrames");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            if (vb->type == G_SNMP_UNSIGNED32) {
                dot1dTpPortEntry->dot1dTpPortInDiscards = &(vb->syntax.ui32[0]);
            } else {
                g_warning("illegal type for dot1dTpPortInDiscards");
            }
        }
    }

    return dot1dTpPortEntry;
}

int
bridge_mib_get_dot1dTpPortTable(host_snmp *s, dot1dTpPortEntry_t ***dot1dTpPortEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 4, 4, 1, 0};

    *dot1dTpPortEntry = NULL;

    base[10] = 2; stls_vbl_add_null(&in, base, 11);
    base[10] = 3; stls_vbl_add_null(&in, base, 11);
    base[10] = 4; stls_vbl_add_null(&in, base, 11);
    base[10] = 5; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *dot1dTpPortEntry = (dot1dTpPortEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(dot1dTpPortEntry_t *));
    if (! *dot1dTpPortEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*dot1dTpPortEntry)[i] = assign_dot1dTpPortEntry(row->data);
    }

    return 0;
}

void
bridge_mib_free_dot1dTpPortEntry(dot1dTpPortEntry_t *dot1dTpPortEntry)
{
    GSList *vbl;
    char *p;

    if (dot1dTpPortEntry) {
        p = (char *) dot1dTpPortEntry + sizeof(dot1dTpPortEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dTpPortEntry);
    }
}

void
bridge_mib_free_dot1dTpPortTable(dot1dTpPortEntry_t **dot1dTpPortEntry)
{
    int i;

    if (dot1dTpPortEntry) {
        for (i = 0; dot1dTpPortEntry[i]; i++) {
            bridge_mib_free_dot1dTpPortEntry(dot1dTpPortEntry[i]);
        }
        g_free(dot1dTpPortEntry);
    }
}

dot1dStaticEntry_t *
bridge_mib_new_dot1dStaticEntry()
{
    dot1dStaticEntry_t *dot1dStaticEntry;

    dot1dStaticEntry = (dot1dStaticEntry_t *) g_malloc0(sizeof(dot1dStaticEntry_t) + sizeof(gpointer));
    return dot1dStaticEntry;
}

static int
unpack_dot1dStaticEntry(GSnmpVarBind *vb, dot1dStaticEntry_t *dot1dStaticEntry)
{
    int i, len, idx = 11;

    len = 6;
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        dot1dStaticEntry->dot1dStaticAddress[i] = vb->id[idx++];
    }
    if (vb->id_len < idx) return -1;
    dot1dStaticEntry->dot1dStaticReceivePort = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static dot1dStaticEntry_t *
assign_dot1dStaticEntry(GSList *vbl)
{
    GSList *elem;
    dot1dStaticEntry_t *dot1dStaticEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 17, 5, 1, 1};

    dot1dStaticEntry = bridge_mib_new_dot1dStaticEntry();
    if (! dot1dStaticEntry) {
        return NULL;
    }

    p = (char *) dot1dStaticEntry + sizeof(dot1dStaticEntry_t);
    * (GSList **) p = vbl;

    if (unpack_dot1dStaticEntry((GSnmpVarBind *) vbl->data, dot1dStaticEntry) < 0) {
        g_warning("illegal dot1dStaticEntry instance identifier");
        g_free(dot1dStaticEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (memcmp(vb->id, base, sizeof(base)) != 0) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            if (vb->type == G_SNMP_OCTET_STRING) {
                dot1dStaticEntry->_dot1dStaticAllowedToGoToLength = vb->syntax_len;
                dot1dStaticEntry->dot1dStaticAllowedToGoTo = vb->syntax.uc;
            } else {
                g_warning("illegal type for dot1dStaticAllowedToGoTo");
            }
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            if (vb->type == G_SNMP_INTEGER32) {
                dot1dStaticEntry->dot1dStaticStatus = &(vb->syntax.i32[0]);
            } else {
                g_warning("illegal type for dot1dStaticStatus");
            }
        }
    }

    return dot1dStaticEntry;
}

int
bridge_mib_get_dot1dStaticTable(host_snmp *s, dot1dStaticEntry_t ***dot1dStaticEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 17, 5, 1, 1, 0};

    *dot1dStaticEntry = NULL;

    base[10] = 3; stls_vbl_add_null(&in, base, 11);
    base[10] = 4; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *dot1dStaticEntry = (dot1dStaticEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(dot1dStaticEntry_t *));
    if (! *dot1dStaticEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*dot1dStaticEntry)[i] = assign_dot1dStaticEntry(row->data);
    }

    return 0;
}

void
bridge_mib_free_dot1dStaticEntry(dot1dStaticEntry_t *dot1dStaticEntry)
{
    GSList *vbl;
    char *p;

    if (dot1dStaticEntry) {
        p = (char *) dot1dStaticEntry + sizeof(dot1dStaticEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(dot1dStaticEntry);
    }
}

void
bridge_mib_free_dot1dStaticTable(dot1dStaticEntry_t **dot1dStaticEntry)
{
    int i;

    if (dot1dStaticEntry) {
        for (i = 0; dot1dStaticEntry[i]; i++) {
            bridge_mib_free_dot1dStaticEntry(dot1dStaticEntry[i]);
        }
        g_free(dot1dStaticEntry);
    }
}


