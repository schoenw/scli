/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from SNMP-USER-BASED-SM-MIB revision 1999-01-20 00:00.
 *
 * $Id$
 */

#include "snmp-user-based-sm-mib.h"

stls_table_t snmp_user_based_sm_mib_enums_usmUserStorageType[] = {
    { 1, "other" },
    { 2, "volatile" },
    { 3, "nonVolatile" },
    { 4, "permanent" },
    { 5, "readOnly" },
    { 0, NULL }
};

stls_table_t snmp_user_based_sm_mib_enums_usmUserStatus[] = {
    { 1, "active" },
    { 2, "notInService" },
    { 3, "notReady" },
    { 4, "createAndGo" },
    { 5, "createAndWait" },
    { 6, "destroy" },
    { 0, NULL }
};


static usmStats_t *
assign_usmStats(GSList *vbl)
{
    GSList *elem;
    usmStats_t *usmStats;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 15, 1, 1};

    usmStats = (usmStats_t *) g_malloc0(sizeof(usmStats_t) + sizeof(GSList *));
    if (! usmStats) {
        return NULL;
    }

    p = (char *) usmStats + sizeof(usmStats_t);
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
        if (vb->id_len > 10 && vb->id[9] == 1) {
            usmStats->usmStatsUnsupportedSecLevels = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 2) {
            usmStats->usmStatsNotInTimeWindows = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 3) {
            usmStats->usmStatsUnknownUserNames = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 4) {
            usmStats->usmStatsUnknownEngineIDs = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 5) {
            usmStats->usmStatsWrongDigests = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 6) {
            usmStats->usmStatsDecryptionErrors = &(vb->syntax.ui32[0]);
        }
    }

    return usmStats;
}

int
snmp_user_based_sm_mib_get_usmStats(host_snmp *s, usmStats_t **usmStats)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 1, 0};

    *usmStats = NULL;

    base[9] = 1; stls_vbl_add_null(&in, base, 10);
    base[9] = 2; stls_vbl_add_null(&in, base, 10);
    base[9] = 3; stls_vbl_add_null(&in, base, 10);
    base[9] = 4; stls_vbl_add_null(&in, base, 10);
    base[9] = 5; stls_vbl_add_null(&in, base, 10);
    base[9] = 6; stls_vbl_add_null(&in, base, 10);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *usmStats = assign_usmStats(out);

    return 0;
}

void
snmp_user_based_sm_mib_free_usmStats(usmStats_t *usmStats)
{
    GSList *vbl;
    char *p;

    if (usmStats) {
        p = (char *) usmStats + sizeof(usmStats_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(usmStats);
    }
}

static usmUser_t *
assign_usmUser(GSList *vbl)
{
    GSList *elem;
    usmUser_t *usmUser;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2};

    usmUser = (usmUser_t *) g_malloc0(sizeof(usmUser_t) + sizeof(GSList *));
    if (! usmUser) {
        return NULL;
    }

    p = (char *) usmUser + sizeof(usmUser_t);
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
        if (vb->id_len > 10 && vb->id[9] == 1) {
            usmUser->usmUserSpinLock = &(vb->syntax.i32[0]);
        }
    }

    return usmUser;
}

int
snmp_user_based_sm_mib_get_usmUser(host_snmp *s, usmUser_t **usmUser)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 0};

    *usmUser = NULL;

    base[9] = 1; stls_vbl_add_null(&in, base, 10);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *usmUser = assign_usmUser(out);

    return 0;
}

void
snmp_user_based_sm_mib_free_usmUser(usmUser_t *usmUser)
{
    GSList *vbl;
    char *p;

    if (usmUser) {
        p = (char *) usmUser + sizeof(usmUser_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(usmUser);
    }
}

static int
unpack_usmUserEntry(GSnmpVarBind *vb, usmUserEntry_t *usmUserEntry)
{
    int i, len, idx = 12;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        usmUserEntry->usmUserEngineID[i] = vb->id[idx++];
    }
    usmUserEntry->_usmUserEngineIDLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        usmUserEntry->usmUserName[i] = vb->id[idx++];
    }
    usmUserEntry->_usmUserNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static usmUserEntry_t *
assign_usmUserEntry(GSList *vbl)
{
    GSList *elem;
    usmUserEntry_t *usmUserEntry;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 2, 1};

    usmUserEntry = (usmUserEntry_t *) g_malloc0(sizeof(usmUserEntry_t) + sizeof(GSList *));
    if (! usmUserEntry) {
        return NULL;
    }

    p = (char *) usmUserEntry + sizeof(usmUserEntry_t);
    * (GSList **) p = vbl;

    if (unpack_usmUserEntry((GSnmpVarBind *) vbl->data, usmUserEntry) < 0) {
        g_warning("illegal usmUserEntry instance identifier");
        g_free(usmUserEntry);
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
        if (vb->id_len > 12 && vb->id[11] == 3) {
            usmUserEntry->_usmUserSecurityNameLength = vb->syntax_len;
            usmUserEntry->usmUserSecurityName = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            usmUserEntry->_usmUserCloneFromLength = vb->syntax_len / sizeof(guint32);
            usmUserEntry->usmUserCloneFrom = vb->syntax.ui32;
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            usmUserEntry->_usmUserAuthProtocolLength = vb->syntax_len / sizeof(guint32);
            usmUserEntry->usmUserAuthProtocol = vb->syntax.ui32;
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            usmUserEntry->_usmUserAuthKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserAuthKeyChange = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            usmUserEntry->_usmUserOwnAuthKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserOwnAuthKeyChange = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            usmUserEntry->_usmUserPrivProtocolLength = vb->syntax_len / sizeof(guint32);
            usmUserEntry->usmUserPrivProtocol = vb->syntax.ui32;
        }
        if (vb->id_len > 12 && vb->id[11] == 9) {
            usmUserEntry->_usmUserPrivKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserPrivKeyChange = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 10) {
            usmUserEntry->_usmUserOwnPrivKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserOwnPrivKeyChange = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 11) {
            usmUserEntry->_usmUserPublicLength = vb->syntax_len;
            usmUserEntry->usmUserPublic = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 12) {
            usmUserEntry->usmUserStorageType = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 13) {
            usmUserEntry->usmUserStatus = &(vb->syntax.i32[0]);
        }
    }

    return usmUserEntry;
}

int
snmp_user_based_sm_mib_get_usmUserEntry(host_snmp *s, usmUserEntry_t ***usmUserEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 2, 1, 0};

    *usmUserEntry = NULL;

    base[11] = 3; stls_vbl_add_null(&in, base, 12);
    base[11] = 4; stls_vbl_add_null(&in, base, 12);
    base[11] = 5; stls_vbl_add_null(&in, base, 12);
    base[11] = 6; stls_vbl_add_null(&in, base, 12);
    base[11] = 7; stls_vbl_add_null(&in, base, 12);
    base[11] = 8; stls_vbl_add_null(&in, base, 12);
    base[11] = 9; stls_vbl_add_null(&in, base, 12);
    base[11] = 10; stls_vbl_add_null(&in, base, 12);
    base[11] = 11; stls_vbl_add_null(&in, base, 12);
    base[11] = 12; stls_vbl_add_null(&in, base, 12);
    base[11] = 13; stls_vbl_add_null(&in, base, 12);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *usmUserEntry = (usmUserEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(usmUserEntry_t *));
    if (! *usmUserEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*usmUserEntry)[i] = assign_usmUserEntry(row->data);
    }

    return 0;
}

void
snmp_user_based_sm_mib_free_usmUserEntry(usmUserEntry_t **usmUserEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (usmUserEntry) {
        for (i = 0; usmUserEntry[i]; i++) {
            p = (char *) usmUserEntry[i] + sizeof(usmUserEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(usmUserEntry[i]);
        }
        g_free(usmUserEntry);
    }
}


