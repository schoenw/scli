/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3-pre1:
 *   smidump -f scli SNMP-USER-BASED-SM-MIB
 *
 * Derived from SNMP-USER-BASED-SM-MIB:
 *   The management information definitions for the
 *   SNMP User-based Security Model.
 *   
 *   Copyright (C) The Internet Society (2002). This
 *   version of this MIB module is part of RFC 3414;
 *   see the RFC itself for full legal notices.
 *
 * Revision 2002-10-16 00:00:
 *   Changes in this revision:
 *   - Updated references and contact info.
 *   - Clarification to usmUserCloneFrom DESCRIPTION
 *     clause
 *   - Fixed 'command responder' into 'command generator'
 *     in last para of DESCRIPTION clause of
 *     usmUserTable.
 *   This revision published as RFC3414.
 *
 * Revision 1999-01-20 00:00:
 *   Clarifications, published as RFC2574
 *
 * Revision 1997-11-20 00:00:
 *   Initial version, published as RFC2274
 *
 * $Id$
 */

#include "snmp-user-based-sm-mib.h"

static guint32 const usmNoAuthProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMNOAUTHPROTOCOL };
static guint32 const usmHMACMD5AuthProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMHMACMD5AUTHPROTOCOL };
static guint32 const usmHMACSHAAuthProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMHMACSHAAUTHPROTOCOL };
static guint32 const usmNoPrivProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMNOPRIVPROTOCOL };
static guint32 const usmDESPrivProtocol[]
	= { SNMP_USER_BASED_SM_MIB_USMDESPRIVPROTOCOL };

GNetSnmpIdentity const snmp_user_based_sm_mib_identities[] = {
    { usmNoAuthProtocol,
      G_N_ELEMENTS(usmNoAuthProtocol),
      "usmNoAuthProtocol" },
    { usmHMACMD5AuthProtocol,
      G_N_ELEMENTS(usmHMACMD5AuthProtocol),
      "usmHMACMD5AuthProtocol" },
    { usmHMACSHAAuthProtocol,
      G_N_ELEMENTS(usmHMACSHAAuthProtocol),
      "usmHMACSHAAuthProtocol" },
    { usmNoPrivProtocol,
      G_N_ELEMENTS(usmNoPrivProtocol),
      "usmNoPrivProtocol" },
    { usmDESPrivProtocol,
      G_N_ELEMENTS(usmDESPrivProtocol),
      "usmDESPrivProtocol" },
    { 0, 0, NULL }
};


static gint32 usmUserSpinLock_constraints[] = {0L, 2147483647L, 0, 0};
static guint16 usmUserSecurityName_constraints[] = {0U, 255U, 0, 0};
static guint16 usmUserPublic_constraints[] = {0U, 32U, 0, 0};


static guint32 const usmStats_oid[] = {1, 3, 6, 1, 6, 3, 15, 1, 1};

static GNetSnmpAttribute usmStats_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      SNMP_USER_BASED_SM_MIB_USMSTATSUNSUPPORTEDSECLEVELS, "usmStatsUnsupportedSecLevels",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmStats_t, usmStatsUnsupportedSecLevels),
      0,
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      SNMP_USER_BASED_SM_MIB_USMSTATSNOTINTIMEWINDOWS, "usmStatsNotInTimeWindows",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmStats_t, usmStatsNotInTimeWindows),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      SNMP_USER_BASED_SM_MIB_USMSTATSUNKNOWNUSERNAMES, "usmStatsUnknownUserNames",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmStats_t, usmStatsUnknownUserNames),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      SNMP_USER_BASED_SM_MIB_USMSTATSUNKNOWNENGINEIDS, "usmStatsUnknownEngineIDs",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmStats_t, usmStatsUnknownEngineIDs),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      SNMP_USER_BASED_SM_MIB_USMSTATSWRONGDIGESTS, "usmStatsWrongDigests",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmStats_t, usmStatsWrongDigests),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      SNMP_USER_BASED_SM_MIB_USMSTATSDECRYPTIONERRORS, "usmStatsDecryptionErrors",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmStats_t, usmStatsDecryptionErrors),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const usmUser_oid[] = {1, 3, 6, 1, 6, 3, 15, 1, 2};

static GNetSnmpAttribute usmUser_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_USER_BASED_SM_MIB_USMUSERSPINLOCK, "usmUserSpinLock",
       usmUserSpinLock_constraints,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUser_t, usmUserSpinLock),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const usmUserEntry_oid[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 2, 1};

static GNetSnmpAttribute usmUserEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_USER_BASED_SM_MIB_USMUSERSECURITYNAME, "usmUserSecurityName",
       usmUserSecurityName_constraints,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserSecurityName),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserSecurityNameLength),
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_OBJECTID,
      SNMP_USER_BASED_SM_MIB_USMUSERCLONEFROM, "usmUserCloneFrom",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserCloneFrom),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserCloneFromLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_OBJECTID,
      SNMP_USER_BASED_SM_MIB_USMUSERAUTHPROTOCOL, "usmUserAuthProtocol",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserAuthProtocol),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserAuthProtocolLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_USER_BASED_SM_MIB_USMUSERAUTHKEYCHANGE, "usmUserAuthKeyChange",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserAuthKeyChange),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserAuthKeyChangeLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_USER_BASED_SM_MIB_USMUSEROWNAUTHKEYCHANGE, "usmUserOwnAuthKeyChange",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserOwnAuthKeyChange),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserOwnAuthKeyChangeLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_OBJECTID,
      SNMP_USER_BASED_SM_MIB_USMUSERPRIVPROTOCOL, "usmUserPrivProtocol",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserPrivProtocol),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserPrivProtocolLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_USER_BASED_SM_MIB_USMUSERPRIVKEYCHANGE, "usmUserPrivKeyChange",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserPrivKeyChange),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserPrivKeyChangeLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 10, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_USER_BASED_SM_MIB_USMUSEROWNPRIVKEYCHANGE, "usmUserOwnPrivKeyChange",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserOwnPrivKeyChange),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserOwnPrivKeyChangeLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 11, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_USER_BASED_SM_MIB_USMUSERPUBLIC, "usmUserPublic",
       usmUserPublic_constraints,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserPublic),
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, _usmUserPublicLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE, "usmUserStorageType",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserStorageType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 13, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_USER_BASED_SM_MIB_USMUSERSTATUS, "usmUserStatus",
       NULL,
      G_STRUCT_OFFSET(snmp_user_based_sm_mib_usmUserEntry_t, usmUserStatus),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};


snmp_user_based_sm_mib_usmStats_t *
snmp_user_based_sm_mib_new_usmStats()
{
    snmp_user_based_sm_mib_usmStats_t *usmStats;

    usmStats = (snmp_user_based_sm_mib_usmStats_t *) g_malloc0(sizeof(snmp_user_based_sm_mib_usmStats_t) + sizeof(gpointer));
    return usmStats;
}

static inline snmp_user_based_sm_mib_usmStats_t *
assign_usmStats(GList *vbl)
{
    snmp_user_based_sm_mib_usmStats_t *usmStats;
    char *p;

    usmStats = snmp_user_based_sm_mib_new_usmStats();
    p = (char *) usmStats + sizeof(snmp_user_based_sm_mib_usmStats_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, usmStats_oid, G_N_ELEMENTS(usmStats_oid),
                      usmStats_attr, usmStats);

    return usmStats;
}

void
snmp_user_based_sm_mib_get_usmStats(GNetSnmp *s, snmp_user_based_sm_mib_usmStats_t **usmStats, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 1, 0};

    *usmStats = NULL;

    gnet_snmp_attr_get(s, &in, base, 10, 9, usmStats_attr, mask);

    out = gnet_snmp_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *usmStats = assign_usmStats(out);
    }
}

void
snmp_user_based_sm_mib_free_usmStats(snmp_user_based_sm_mib_usmStats_t *usmStats)
{
    GList *vbl;
    char *p;

    if (usmStats) {
        p = (char *) usmStats + sizeof(snmp_user_based_sm_mib_usmStats_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(usmStats);
    }
}

snmp_user_based_sm_mib_usmUser_t *
snmp_user_based_sm_mib_new_usmUser()
{
    snmp_user_based_sm_mib_usmUser_t *usmUser;

    usmUser = (snmp_user_based_sm_mib_usmUser_t *) g_malloc0(sizeof(snmp_user_based_sm_mib_usmUser_t) + sizeof(gpointer));
    return usmUser;
}

static inline snmp_user_based_sm_mib_usmUser_t *
assign_usmUser(GList *vbl)
{
    snmp_user_based_sm_mib_usmUser_t *usmUser;
    char *p;

    usmUser = snmp_user_based_sm_mib_new_usmUser();
    p = (char *) usmUser + sizeof(snmp_user_based_sm_mib_usmUser_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, usmUser_oid, G_N_ELEMENTS(usmUser_oid),
                      usmUser_attr, usmUser);

    return usmUser;
}

void
snmp_user_based_sm_mib_get_usmUser(GNetSnmp *s, snmp_user_based_sm_mib_usmUser_t **usmUser, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 0};

    *usmUser = NULL;

    gnet_snmp_attr_get(s, &in, base, 10, 9, usmUser_attr, mask);

    out = gnet_snmp_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *usmUser = assign_usmUser(out);
    }
}

void
snmp_user_based_sm_mib_set_usmUser(GNetSnmp *s, snmp_user_based_sm_mib_usmUser_t *usmUser, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 0, 0};

    gnet_snmp_attr_set(s, &in, base, 11, 9, usmUser_attr, mask, usmUser);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
snmp_user_based_sm_mib_free_usmUser(snmp_user_based_sm_mib_usmUser_t *usmUser)
{
    GList *vbl;
    char *p;

    if (usmUser) {
        p = (char *) usmUser + sizeof(snmp_user_based_sm_mib_usmUser_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(usmUser);
    }
}

snmp_user_based_sm_mib_usmUserEntry_t *
snmp_user_based_sm_mib_new_usmUserEntry()
{
    snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry;

    usmUserEntry = (snmp_user_based_sm_mib_usmUserEntry_t *) g_malloc0(sizeof(snmp_user_based_sm_mib_usmUserEntry_t) + sizeof(gpointer));
    return usmUserEntry;
}

static inline int
unpack_usmUserEntry(GNetSnmpVarBind *vb, snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry)
{
    guint8 idx = 12;
    guint16 i, len;

    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len < 5 || len > 32) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        usmUserEntry->usmUserEngineID[i] = vb->oid[idx++];
    }
    usmUserEntry->_usmUserEngineIDLength = len;
    if (vb->oid_len < idx) return -1;
    len = vb->oid[idx++];
    if (len < 1 || len > 32) return -1;
    if (vb->oid_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        usmUserEntry->usmUserName[i] = vb->oid[idx++];
    }
    usmUserEntry->_usmUserNameLength = len;
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_usmUserEntry(guint32 *base, guchar *usmUserEngineID, guint16 _usmUserEngineIDLength, guchar *usmUserName, guint16 _usmUserNameLength)
{
    guint8 idx = 12;
    guint16 i, len;

    len = _usmUserEngineIDLength;
    base[idx++] = len;
    if (len < 5 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = usmUserEngineID[i];
        if (idx >= 128) return -1;
    }
    len = _usmUserNameLength;
    base[idx++] = len;
    if (len < 1 || len > 32) return -1;
    for (i = 0; i < len; i++) {
        base[idx++] = usmUserName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static inline snmp_user_based_sm_mib_usmUserEntry_t *
assign_usmUserEntry(GList *vbl)
{
    snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry;
    char *p;

    usmUserEntry = snmp_user_based_sm_mib_new_usmUserEntry();
    p = (char *) usmUserEntry + sizeof(snmp_user_based_sm_mib_usmUserEntry_t);
    * (GList **) p = vbl;

    if (unpack_usmUserEntry((GNetSnmpVarBind *) vbl->data, usmUserEntry) < 0) {
        g_warning("%s: invalid instance identifier", "usmUserEntry");
        g_free(usmUserEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, usmUserEntry_oid, G_N_ELEMENTS(usmUserEntry_oid),
                      usmUserEntry_attr, usmUserEntry);

    return usmUserEntry;
}

void
snmp_user_based_sm_mib_get_usmUserTable(GNetSnmp *s, snmp_user_based_sm_mib_usmUserEntry_t ***usmUserEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 2, 1, 0};

    *usmUserEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 12, 11, usmUserEntry_attr, mask);

    out = gsnmp_gettable(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *usmUserEntry = (snmp_user_based_sm_mib_usmUserEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(snmp_user_based_sm_mib_usmUserEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*usmUserEntry)[i] = assign_usmUserEntry(row->data);
        }
    }
}

void
snmp_user_based_sm_mib_get_usmUserEntry(GNetSnmp *s, snmp_user_based_sm_mib_usmUserEntry_t **usmUserEntry, guchar *usmUserEngineID, guint16 _usmUserEngineIDLength, guchar *usmUserName, guint16 _usmUserNameLength, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, usmUserEntry_oid, sizeof(usmUserEntry_oid));
    len = pack_usmUserEntry(base, usmUserEngineID, _usmUserEngineIDLength, usmUserName, _usmUserNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "usmUserEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    *usmUserEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 11, usmUserEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *usmUserEntry = assign_usmUserEntry(out);
    }
}

void
snmp_user_based_sm_mib_set_usmUserEntry(GNetSnmp *s, snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, usmUserEntry_oid, sizeof(usmUserEntry_oid));
    len = pack_usmUserEntry(base, usmUserEntry->usmUserEngineID, usmUserEntry->_usmUserEngineIDLength, usmUserEntry->usmUserName, usmUserEntry->_usmUserNameLength);
    if (len < 0) {
        g_warning("%s: invalid index values", "usmUserEntry");
        s->error_status = GNET_SNMP_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 11, usmUserEntry_attr, mask, usmUserEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(out);
    }
}

void
snmp_user_based_sm_mib_free_usmUserEntry(snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry)
{
    GList *vbl;
    char *p;

    if (usmUserEntry) {
        p = (char *) usmUserEntry + sizeof(snmp_user_based_sm_mib_usmUserEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(usmUserEntry);
    }
}

void
snmp_user_based_sm_mib_free_usmUserTable(snmp_user_based_sm_mib_usmUserEntry_t **usmUserEntry)
{
    int i;

    if (usmUserEntry) {
        for (i = 0; usmUserEntry[i]; i++) {
            snmp_user_based_sm_mib_free_usmUserEntry(usmUserEntry[i]);
        }
        g_free(usmUserEntry);
    }
}


