/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from SNMP-TARGET-MIB revision 1998-08-04 00:00.
 *
 * $Id$
 */

#include "snmp-target-mib.h"

stls_table_t snmp_target_mib_enums_snmpTargetAddrStorageType[] = {
    { 1, "other" },
    { 2, "volatile" },
    { 3, "nonVolatile" },
    { 4, "permanent" },
    { 5, "readOnly" },
    { 0, NULL }
};

stls_table_t snmp_target_mib_enums_snmpTargetAddrRowStatus[] = {
    { 1, "active" },
    { 2, "notInService" },
    { 3, "notReady" },
    { 4, "createAndGo" },
    { 5, "createAndWait" },
    { 6, "destroy" },
    { 0, NULL }
};

stls_table_t snmp_target_mib_enums_snmpTargetParamsSecurityLevel[] = {
    { 1, "noAuthNoPriv" },
    { 2, "authNoPriv" },
    { 3, "authPriv" },
    { 0, NULL }
};

stls_table_t snmp_target_mib_enums_snmpTargetParamsStorageType[] = {
    { 1, "other" },
    { 2, "volatile" },
    { 3, "nonVolatile" },
    { 4, "permanent" },
    { 5, "readOnly" },
    { 0, NULL }
};

stls_table_t snmp_target_mib_enums_snmpTargetParamsRowStatus[] = {
    { 1, "active" },
    { 2, "notInService" },
    { 3, "notReady" },
    { 4, "createAndGo" },
    { 5, "createAndWait" },
    { 6, "destroy" },
    { 0, NULL }
};


static snmpTargetObjects_t *
assign_snmpTargetObjects(GSList *vbl)
{
    GSList *elem;
    snmpTargetObjects_t *snmpTargetObjects;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 12, 1};

    snmpTargetObjects = (snmpTargetObjects_t *) g_malloc0(sizeof(snmpTargetObjects_t) + sizeof(GSList *));
    if (! snmpTargetObjects) {
        return NULL;
    }

    p = (char *) snmpTargetObjects + sizeof(snmpTargetObjects_t);
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
            snmpTargetObjects->snmpTargetSpinLock = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 9 && vb->id[8] == 4) {
            snmpTargetObjects->snmpUnavailableContexts = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 9 && vb->id[8] == 5) {
            snmpTargetObjects->snmpUnknownContexts = &(vb->syntax.ui32[0]);
        }
    }

    return snmpTargetObjects;
}

int
snmp_target_mib_get_snmpTargetObjects(host_snmp *s, snmpTargetObjects_t **snmpTargetObjects)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 12, 1, 0};

    *snmpTargetObjects = NULL;

    base[8] = 1; stls_vbl_add_null(&in, base, 9);
    base[8] = 4; stls_vbl_add_null(&in, base, 9);
    base[8] = 5; stls_vbl_add_null(&in, base, 9);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *snmpTargetObjects = assign_snmpTargetObjects(out);

    return 0;
}

void
snmp_target_mib_free_snmpTargetObjects(snmpTargetObjects_t *snmpTargetObjects)
{
    GSList *vbl;
    char *p;

    if (snmpTargetObjects) {
        p = (char *) snmpTargetObjects + sizeof(snmpTargetObjects_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(snmpTargetObjects);
    }
}

static snmpTargetAddrEntry_t *
assign_snmpTargetAddrEntry(GSList *vbl)
{
    GSList *elem;
    snmpTargetAddrEntry_t *snmpTargetAddrEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 12, 1, 2, 1};

    snmpTargetAddrEntry = (snmpTargetAddrEntry_t *) g_malloc0(sizeof(snmpTargetAddrEntry_t) + sizeof(GSList *));
    if (! snmpTargetAddrEntry) {
        return NULL;
    }

    p = (char *) snmpTargetAddrEntry + sizeof(snmpTargetAddrEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        int idx = 11;
        {
            int i;
            if (vb->id_len < idx) goto illegal;
            snmpTargetAddrEntry->_snmpTargetAddrNameLength = vb->id[idx++];
            if (vb->id_len < idx + snmpTargetAddrEntry->_snmpTargetAddrNameLength) goto illegal;
            for (i = 0; i < snmpTargetAddrEntry->_snmpTargetAddrNameLength; i++) {
                snmpTargetAddrEntry->snmpTargetAddrName[i] = vb->id[idx++];
            }
        }
        if (vb->id_len > idx) { 
        illegal:
            g_warning("illegal snmpTargetAddrEntry instance identifier");
            g_free(snmpTargetAddrEntry);
            return NULL;
        }
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
            snmpTargetAddrEntry->_snmpTargetAddrTDomainLength = vb->syntax_len / sizeof(guint32);
            snmpTargetAddrEntry->snmpTargetAddrTDomain = vb->syntax.ui32;
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            snmpTargetAddrEntry->_snmpTargetAddrTAddressLength = vb->syntax_len;
            snmpTargetAddrEntry->snmpTargetAddrTAddress = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            snmpTargetAddrEntry->snmpTargetAddrTimeout = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            snmpTargetAddrEntry->snmpTargetAddrRetryCount = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            snmpTargetAddrEntry->_snmpTargetAddrTagListLength = vb->syntax_len;
            snmpTargetAddrEntry->snmpTargetAddrTagList = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 7) {
            snmpTargetAddrEntry->_snmpTargetAddrParamsLength = vb->syntax_len;
            snmpTargetAddrEntry->snmpTargetAddrParams = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 8) {
            snmpTargetAddrEntry->snmpTargetAddrStorageType = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 9) {
            snmpTargetAddrEntry->snmpTargetAddrRowStatus = &(vb->syntax.i32[0]);
        }
    }

    return snmpTargetAddrEntry;
}

int
snmp_target_mib_get_snmpTargetAddrEntry(host_snmp *s, snmpTargetAddrEntry_t ***snmpTargetAddrEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 12, 1, 2, 1, 0};

    *snmpTargetAddrEntry = NULL;

    base[10] = 2; stls_vbl_add_null(&in, base, 11);
    base[10] = 3; stls_vbl_add_null(&in, base, 11);
    base[10] = 4; stls_vbl_add_null(&in, base, 11);
    base[10] = 5; stls_vbl_add_null(&in, base, 11);
    base[10] = 6; stls_vbl_add_null(&in, base, 11);
    base[10] = 7; stls_vbl_add_null(&in, base, 11);
    base[10] = 8; stls_vbl_add_null(&in, base, 11);
    base[10] = 9; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *snmpTargetAddrEntry = (snmpTargetAddrEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmpTargetAddrEntry_t *));
    if (! *snmpTargetAddrEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*snmpTargetAddrEntry)[i] = assign_snmpTargetAddrEntry(row->data);
    }

    return 0;
}

void
snmp_target_mib_free_snmpTargetAddrEntry(snmpTargetAddrEntry_t **snmpTargetAddrEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (snmpTargetAddrEntry) {
        for (i = 0; snmpTargetAddrEntry[i]; i++) {
            p = (char *) snmpTargetAddrEntry[i] + sizeof(snmpTargetAddrEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(snmpTargetAddrEntry[i]);
        }
        g_free(snmpTargetAddrEntry);
    }
}

static snmpTargetParamsEntry_t *
assign_snmpTargetParamsEntry(GSList *vbl)
{
    GSList *elem;
    snmpTargetParamsEntry_t *snmpTargetParamsEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 12, 1, 3, 1};

    snmpTargetParamsEntry = (snmpTargetParamsEntry_t *) g_malloc0(sizeof(snmpTargetParamsEntry_t) + sizeof(GSList *));
    if (! snmpTargetParamsEntry) {
        return NULL;
    }

    p = (char *) snmpTargetParamsEntry + sizeof(snmpTargetParamsEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        int idx = 11;
        {
            int i;
            if (vb->id_len < idx) goto illegal;
            snmpTargetParamsEntry->_snmpTargetParamsNameLength = vb->id[idx++];
            if (vb->id_len < idx + snmpTargetParamsEntry->_snmpTargetParamsNameLength) goto illegal;
            for (i = 0; i < snmpTargetParamsEntry->_snmpTargetParamsNameLength; i++) {
                snmpTargetParamsEntry->snmpTargetParamsName[i] = vb->id[idx++];
            }
        }
        if (vb->id_len > idx) { 
        illegal:
            g_warning("illegal snmpTargetParamsEntry instance identifier");
            g_free(snmpTargetParamsEntry);
            return NULL;
        }
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
            snmpTargetParamsEntry->snmpTargetParamsMPModel = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            snmpTargetParamsEntry->snmpTargetParamsSecurityModel = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            snmpTargetParamsEntry->_snmpTargetParamsSecurityNameLength = vb->syntax_len;
            snmpTargetParamsEntry->snmpTargetParamsSecurityName = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            snmpTargetParamsEntry->snmpTargetParamsSecurityLevel = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            snmpTargetParamsEntry->snmpTargetParamsStorageType = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 11 && vb->id[10] == 7) {
            snmpTargetParamsEntry->snmpTargetParamsRowStatus = &(vb->syntax.i32[0]);
        }
    }

    return snmpTargetParamsEntry;
}

int
snmp_target_mib_get_snmpTargetParamsEntry(host_snmp *s, snmpTargetParamsEntry_t ***snmpTargetParamsEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 12, 1, 3, 1, 0};

    *snmpTargetParamsEntry = NULL;

    base[10] = 2; stls_vbl_add_null(&in, base, 11);
    base[10] = 3; stls_vbl_add_null(&in, base, 11);
    base[10] = 4; stls_vbl_add_null(&in, base, 11);
    base[10] = 5; stls_vbl_add_null(&in, base, 11);
    base[10] = 6; stls_vbl_add_null(&in, base, 11);
    base[10] = 7; stls_vbl_add_null(&in, base, 11);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *snmpTargetParamsEntry = (snmpTargetParamsEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmpTargetParamsEntry_t *));
    if (! *snmpTargetParamsEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*snmpTargetParamsEntry)[i] = assign_snmpTargetParamsEntry(row->data);
    }

    return 0;
}

void
snmp_target_mib_free_snmpTargetParamsEntry(snmpTargetParamsEntry_t **snmpTargetParamsEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (snmpTargetParamsEntry) {
        for (i = 0; snmpTargetParamsEntry[i]; i++) {
            p = (char *) snmpTargetParamsEntry[i] + sizeof(snmpTargetParamsEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(snmpTargetParamsEntry[i]);
        }
        g_free(snmpTargetParamsEntry);
    }
}


