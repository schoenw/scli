/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from SNMP-USER-BASED-SM-MIB:
 *   The management information definitions for the
 *   SNMP User-based Security Model.
 *   
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

GSnmpEnum const snmp_user_based_sm_mib_enums_usmUserStorageType[] = {
    { SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE_OTHER,	"other" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE_VOLATILE,	"volatile" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE_NONVOLATILE,	"nonVolatile" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE_PERMANENT,	"permanent" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE_READONLY,	"readOnly" },
    { 0, NULL }
};

GSnmpEnum const snmp_user_based_sm_mib_enums_usmUserStatus[] = {
    { SNMP_USER_BASED_SM_MIB_USMUSERSTATUS_ACTIVE,	"active" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTATUS_NOTINSERVICE,	"notInService" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTATUS_NOTREADY,	"notReady" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTATUS_CREATEANDGO,	"createAndGo" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTATUS_CREATEANDWAIT,	"createAndWait" },
    { SNMP_USER_BASED_SM_MIB_USMUSERSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};


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

GSnmpIdentity const snmp_user_based_sm_mib_identities[] = {
    { usmNoAuthProtocol,
      sizeof(usmNoAuthProtocol)/sizeof(guint32),
      "usmNoAuthProtocol" },
    { usmHMACMD5AuthProtocol,
      sizeof(usmHMACMD5AuthProtocol)/sizeof(guint32),
      "usmHMACMD5AuthProtocol" },
    { usmHMACSHAAuthProtocol,
      sizeof(usmHMACSHAAuthProtocol)/sizeof(guint32),
      "usmHMACSHAAuthProtocol" },
    { usmNoPrivProtocol,
      sizeof(usmNoPrivProtocol)/sizeof(guint32),
      "usmNoPrivProtocol" },
    { usmDESPrivProtocol,
      sizeof(usmDESPrivProtocol)/sizeof(guint32),
      "usmDESPrivProtocol" },
    { 0, 0, NULL }
};


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

static guint32 const oid_usmStats[] = {1, 3, 6, 1, 6, 3, 15, 1, 1};

static attribute_t attr_usmStats[] = {
    { 1, G_SNMP_COUNTER32, SNMP_USER_BASED_SM_MIB_USMSTATSUNSUPPORTEDSECLEVELS, "usmStatsUnsupportedSecLevels" },
    { 2, G_SNMP_COUNTER32, SNMP_USER_BASED_SM_MIB_USMSTATSNOTINTIMEWINDOWS, "usmStatsNotInTimeWindows" },
    { 3, G_SNMP_COUNTER32, SNMP_USER_BASED_SM_MIB_USMSTATSUNKNOWNUSERNAMES, "usmStatsUnknownUserNames" },
    { 4, G_SNMP_COUNTER32, SNMP_USER_BASED_SM_MIB_USMSTATSUNKNOWNENGINEIDS, "usmStatsUnknownEngineIDs" },
    { 5, G_SNMP_COUNTER32, SNMP_USER_BASED_SM_MIB_USMSTATSWRONGDIGESTS, "usmStatsWrongDigests" },
    { 6, G_SNMP_COUNTER32, SNMP_USER_BASED_SM_MIB_USMSTATSDECRYPTIONERRORS, "usmStatsDecryptionErrors" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_usmUser[] = {1, 3, 6, 1, 6, 3, 15, 1, 2};

static attribute_t attr_usmUser[] = {
    { 1, G_SNMP_INTEGER32, SNMP_USER_BASED_SM_MIB_USMUSERSPINLOCK, "usmUserSpinLock" },
    { 0, 0, 0, NULL }
};

static guint32 const oid_usmUserEntry[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 2, 1};

static attribute_t attr_usmUserEntry[] = {
    { 3, G_SNMP_OCTET_STRING, SNMP_USER_BASED_SM_MIB_USMUSERSECURITYNAME, "usmUserSecurityName" },
    { 4, G_SNMP_OBJECT_ID, SNMP_USER_BASED_SM_MIB_USMUSERCLONEFROM, "usmUserCloneFrom" },
    { 5, G_SNMP_OBJECT_ID, SNMP_USER_BASED_SM_MIB_USMUSERAUTHPROTOCOL, "usmUserAuthProtocol" },
    { 6, G_SNMP_OCTET_STRING, SNMP_USER_BASED_SM_MIB_USMUSERAUTHKEYCHANGE, "usmUserAuthKeyChange" },
    { 7, G_SNMP_OCTET_STRING, SNMP_USER_BASED_SM_MIB_USMUSEROWNAUTHKEYCHANGE, "usmUserOwnAuthKeyChange" },
    { 8, G_SNMP_OBJECT_ID, SNMP_USER_BASED_SM_MIB_USMUSERPRIVPROTOCOL, "usmUserPrivProtocol" },
    { 9, G_SNMP_OCTET_STRING, SNMP_USER_BASED_SM_MIB_USMUSERPRIVKEYCHANGE, "usmUserPrivKeyChange" },
    { 10, G_SNMP_OCTET_STRING, SNMP_USER_BASED_SM_MIB_USMUSEROWNPRIVKEYCHANGE, "usmUserOwnPrivKeyChange" },
    { 11, G_SNMP_OCTET_STRING, SNMP_USER_BASED_SM_MIB_USMUSERPUBLIC, "usmUserPublic" },
    { 12, G_SNMP_INTEGER32, SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE, "usmUserStorageType" },
    { 13, G_SNMP_INTEGER32, SNMP_USER_BASED_SM_MIB_USMUSERSTATUS, "usmUserStatus" },
    { 0, 0, 0, NULL }
};


snmp_user_based_sm_mib_usmStats_t *
snmp_user_based_sm_mib_new_usmStats()
{
    snmp_user_based_sm_mib_usmStats_t *usmStats;

    usmStats = (snmp_user_based_sm_mib_usmStats_t *) g_malloc0(sizeof(snmp_user_based_sm_mib_usmStats_t) + sizeof(gpointer));
    return usmStats;
}

static snmp_user_based_sm_mib_usmStats_t *
assign_usmStats(GSList *vbl)
{
    GSList *elem;
    snmp_user_based_sm_mib_usmStats_t *usmStats;
    guint32 idx;
    char *p;

    usmStats = snmp_user_based_sm_mib_new_usmStats();
    if (! usmStats) {
        return NULL;
    }

    p = (char *) usmStats + sizeof(snmp_user_based_sm_mib_usmStats_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_usmStats, sizeof(oid_usmStats)/sizeof(guint32),
                   attr_usmStats, &idx) < 0) continue;

        switch (idx) {
        case 1:
            usmStats->usmStatsUnsupportedSecLevels = &(vb->syntax.ui32[0]);
            break;
        case 2:
            usmStats->usmStatsNotInTimeWindows = &(vb->syntax.ui32[0]);
            break;
        case 3:
            usmStats->usmStatsUnknownUserNames = &(vb->syntax.ui32[0]);
            break;
        case 4:
            usmStats->usmStatsUnknownEngineIDs = &(vb->syntax.ui32[0]);
            break;
        case 5:
            usmStats->usmStatsWrongDigests = &(vb->syntax.ui32[0]);
            break;
        case 6:
            usmStats->usmStatsDecryptionErrors = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return usmStats;
}

void
snmp_user_based_sm_mib_get_usmStats(GSnmpSession *s, snmp_user_based_sm_mib_usmStats_t **usmStats, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 1, 0};

    *usmStats = NULL;

    add_attributes(s, &in, base, 10, 9, attr_usmStats, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *usmStats = assign_usmStats(out);
    }
}

void
snmp_user_based_sm_mib_free_usmStats(snmp_user_based_sm_mib_usmStats_t *usmStats)
{
    GSList *vbl;
    char *p;

    if (usmStats) {
        p = (char *) usmStats + sizeof(snmp_user_based_sm_mib_usmStats_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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

static snmp_user_based_sm_mib_usmUser_t *
assign_usmUser(GSList *vbl)
{
    GSList *elem;
    snmp_user_based_sm_mib_usmUser_t *usmUser;
    guint32 idx;
    char *p;

    usmUser = snmp_user_based_sm_mib_new_usmUser();
    if (! usmUser) {
        return NULL;
    }

    p = (char *) usmUser + sizeof(snmp_user_based_sm_mib_usmUser_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_usmUser, sizeof(oid_usmUser)/sizeof(guint32),
                   attr_usmUser, &idx) < 0) continue;

        switch (idx) {
        case 1:
            usmUser->usmUserSpinLock = &(vb->syntax.i32[0]);
            break;
        };
    }

    return usmUser;
}

void
snmp_user_based_sm_mib_get_usmUser(GSnmpSession *s, snmp_user_based_sm_mib_usmUser_t **usmUser, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 0};

    *usmUser = NULL;

    add_attributes(s, &in, base, 10, 9, attr_usmUser, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *usmUser = assign_usmUser(out);
    }
}

void
snmp_user_based_sm_mib_set_usmUser(GSnmpSession *s, snmp_user_based_sm_mib_usmUser_t *usmUser, gint mask)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 0, 0};

    if (usmUser->usmUserSpinLock) {
        base[9] = 1;
        g_snmp_vbl_add(&in, base, sizeof(base)/sizeof(guint32),
                       G_SNMP_INTEGER32,
                       usmUser->usmUserSpinLock,
                       0);
    }

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_user_based_sm_mib_free_usmUser(snmp_user_based_sm_mib_usmUser_t *usmUser)
{
    GSList *vbl;
    char *p;

    if (usmUser) {
        p = (char *) usmUser + sizeof(snmp_user_based_sm_mib_usmUser_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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

static int
unpack_usmUserEntry(GSnmpVarBind *vb, snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry)
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

static int
pack_usmUserEntry(guint32 *base, guchar *usmUserEngineID, gsize _usmUserEngineIDLength, guchar *usmUserName, gsize _usmUserNameLength)
{
    int i, len, idx = 12;

    len = _usmUserEngineIDLength;
    base[idx++] = len;
    for (i = 0; i < len; i++) {
        base[idx++] = usmUserEngineID[i];
        if (idx >= 128) return -1;
    }
    len = _usmUserNameLength;
    base[idx++] = len;
    for (i = 0; i < len; i++) {
        base[idx++] = usmUserName[i];
        if (idx >= 128) return -1;
    }
    return idx;
}

static snmp_user_based_sm_mib_usmUserEntry_t *
assign_usmUserEntry(GSList *vbl)
{
    GSList *elem;
    snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry;
    guint32 idx;
    char *p;

    usmUserEntry = snmp_user_based_sm_mib_new_usmUserEntry();
    if (! usmUserEntry) {
        return NULL;
    }

    p = (char *) usmUserEntry + sizeof(snmp_user_based_sm_mib_usmUserEntry_t);
    * (GSList **) p = vbl;

    if (unpack_usmUserEntry((GSnmpVarBind *) vbl->data, usmUserEntry) < 0) {
        g_warning("illegal usmUserEntry instance identifier");
        g_free(usmUserEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, oid_usmUserEntry, sizeof(oid_usmUserEntry)/sizeof(guint32),
                   attr_usmUserEntry, &idx) < 0) continue;

        switch (idx) {
        case 3:
            usmUserEntry->_usmUserSecurityNameLength = vb->syntax_len;
            usmUserEntry->usmUserSecurityName = vb->syntax.uc;
            break;
        case 4:
            usmUserEntry->_usmUserCloneFromLength = vb->syntax_len / sizeof(guint32);
            usmUserEntry->usmUserCloneFrom = vb->syntax.ui32;
            break;
        case 5:
            usmUserEntry->_usmUserAuthProtocolLength = vb->syntax_len / sizeof(guint32);
            usmUserEntry->usmUserAuthProtocol = vb->syntax.ui32;
            break;
        case 6:
            usmUserEntry->_usmUserAuthKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserAuthKeyChange = vb->syntax.uc;
            break;
        case 7:
            usmUserEntry->_usmUserOwnAuthKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserOwnAuthKeyChange = vb->syntax.uc;
            break;
        case 8:
            usmUserEntry->_usmUserPrivProtocolLength = vb->syntax_len / sizeof(guint32);
            usmUserEntry->usmUserPrivProtocol = vb->syntax.ui32;
            break;
        case 9:
            usmUserEntry->_usmUserPrivKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserPrivKeyChange = vb->syntax.uc;
            break;
        case 10:
            usmUserEntry->_usmUserOwnPrivKeyChangeLength = vb->syntax_len;
            usmUserEntry->usmUserOwnPrivKeyChange = vb->syntax.uc;
            break;
        case 11:
            usmUserEntry->_usmUserPublicLength = vb->syntax_len;
            usmUserEntry->usmUserPublic = vb->syntax.uc;
            break;
        case 12:
            usmUserEntry->usmUserStorageType = &(vb->syntax.i32[0]);
            break;
        case 13:
            usmUserEntry->usmUserStatus = &(vb->syntax.i32[0]);
            break;
        };
    }

    return usmUserEntry;
}

void
snmp_user_based_sm_mib_get_usmUserTable(GSnmpSession *s, snmp_user_based_sm_mib_usmUserEntry_t ***usmUserEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 15, 1, 2, 2, 1, 0};

    *usmUserEntry = NULL;

    add_attributes(s, &in, base, 12, 11, attr_usmUserEntry, mask);

    out = gsnmp_gettable(s, in);
    /* g_snmp_vbl_free(in); */

    if (out) {
        *usmUserEntry = (snmp_user_based_sm_mib_usmUserEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmp_user_based_sm_mib_usmUserEntry_t *));
        if (! *usmUserEntry) {
            s->error_status = G_SNMP_ERR_INTERNAL;
            g_snmp_vbl_free(out);
            return;
        }
        for (row = out, i = 0; row; row = g_slist_next(row), i++) {
            (*usmUserEntry)[i] = assign_usmUserEntry(row->data);
        }
    }
}

void
snmp_user_based_sm_mib_get_usmUserEntry(GSnmpSession *s, snmp_user_based_sm_mib_usmUserEntry_t **usmUserEntry, guchar *usmUserEngineID, gsize _usmUserEngineIDLength, guchar *usmUserName, gsize _usmUserNameLength, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    int len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_usmUserEntry, sizeof(oid_usmUserEntry));
    len = pack_usmUserEntry(base, usmUserEngineID, _usmUserEngineIDLength, usmUserName, _usmUserNameLength);
    if (len < 0) {
        g_warning("illegal usmUserEntry index values");
        return;
    }

    *usmUserEntry = NULL;

    add_attributes(s, &in, base, len, 11, attr_usmUserEntry, mask);

    out = g_snmp_session_sync_get(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        *usmUserEntry = assign_usmUserEntry(out);
    }
}

void
snmp_user_based_sm_mib_set_usmUserEntry(GSnmpSession *s, snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry, gint mask)
{
    GSList *in = NULL, *out = NULL;
    guint32 base[128];
    int len;

    memset(base, 0, sizeof(base));
    memcpy(base, oid_usmUserEntry, sizeof(oid_usmUserEntry));
    len = pack_usmUserEntry(base, usmUserEntry->usmUserEngineID, usmUserEntry->_usmUserEngineIDLength, usmUserEntry->usmUserName, usmUserEntry->_usmUserNameLength);
    if (len < 0) {
        g_warning("illegal usmUserEntry index values");
        return;
    }

    if (usmUserEntry->usmUserCloneFrom) {
        base[11] = 4;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OBJECT_ID,
                       usmUserEntry->usmUserCloneFrom,
                       usmUserEntry->_usmUserCloneFromLength);
    }
    if (usmUserEntry->usmUserAuthProtocol) {
        base[11] = 5;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OBJECT_ID,
                       usmUserEntry->usmUserAuthProtocol,
                       usmUserEntry->_usmUserAuthProtocolLength);
    }
    if (usmUserEntry->usmUserAuthKeyChange) {
        base[11] = 6;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       usmUserEntry->usmUserAuthKeyChange,
                       usmUserEntry->_usmUserAuthKeyChangeLength);
    }
    if (usmUserEntry->usmUserOwnAuthKeyChange) {
        base[11] = 7;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       usmUserEntry->usmUserOwnAuthKeyChange,
                       usmUserEntry->_usmUserOwnAuthKeyChangeLength);
    }
    if (usmUserEntry->usmUserPrivProtocol) {
        base[11] = 8;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OBJECT_ID,
                       usmUserEntry->usmUserPrivProtocol,
                       usmUserEntry->_usmUserPrivProtocolLength);
    }
    if (usmUserEntry->usmUserPrivKeyChange) {
        base[11] = 9;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       usmUserEntry->usmUserPrivKeyChange,
                       usmUserEntry->_usmUserPrivKeyChangeLength);
    }
    if (usmUserEntry->usmUserOwnPrivKeyChange) {
        base[11] = 10;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       usmUserEntry->usmUserOwnPrivKeyChange,
                       usmUserEntry->_usmUserOwnPrivKeyChangeLength);
    }
    if (usmUserEntry->usmUserPublic) {
        base[11] = 11;
        g_snmp_vbl_add(&in, base, len, G_SNMP_OCTET_STRING,
                       usmUserEntry->usmUserPublic,
                       usmUserEntry->_usmUserPublicLength);
    }
    if (usmUserEntry->usmUserStorageType) {
        base[11] = 12;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       usmUserEntry->usmUserStorageType,
                       0);
    }
    if (usmUserEntry->usmUserStatus) {
        base[11] = 13;
        g_snmp_vbl_add(&in, base, len, G_SNMP_INTEGER32,
                       usmUserEntry->usmUserStatus,
                       0);
    }

    out = g_snmp_session_sync_set(s, in);
    g_snmp_vbl_free(in);
    if (out) {
        g_snmp_vbl_free(out);
    }
}

void
snmp_user_based_sm_mib_free_usmUserEntry(snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry)
{
    GSList *vbl;
    char *p;

    if (usmUserEntry) {
        p = (char *) usmUserEntry + sizeof(snmp_user_based_sm_mib_usmUserEntry_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
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


