/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Derived from SNMP-FRAMEWORK-MIB:
 *   The SNMP Management Architecture MIB
 *   
 *   Copyright (C) The Internet Society (2002). This
 *   version of this MIB module is part of RFC 3411;
 *   see the RFC itself for full legal notices.
 *   
 *
 * Revision 2002-10-14 00:00:
 *   Changes in this revision:
 *   - Updated various administrative information.
 *   - Corrected some typos.
 *   - Corrected typo in description of SnmpEngineID
 *     that led to range overlap for 127.
 *   - Changed '255a' to '255t' in definition of
 *     SnmpAdminString to align with current SMI.
 *   - Reworded 'reserved' for value zero in
 *     DESCRIPTION of SnmpSecurityModel.
 *   - The algorithm for allocating security models
 *     should give 256 per enterprise block, rather
 *     than 255.
 *   - The example engine ID of 'abcd' is not
 *     legal. Replaced with '800002b804616263'H based
 *     on example enterprise 696, string 'abc'.
 *   - Added clarification that engineID should
 *     persist across re-initializations.
 *   This revision published as RFC 3411.
 *   
 *
 * Revision 1999-01-19 00:00:
 *   Updated editors' addresses, fixed typos.
 *   Published as RFC 2571.
 *   
 *
 * Revision 1997-11-20 00:00:
 *   The initial version, published in RFC 2271.
 *   
 *
 * $Id$
 */

#include "snmp-framework-mib.h"

GSnmpEnum const snmp_framework_mib_enums_SnmpSecurityLevel[] = {
    { SNMP_FRAMEWORK_MIB_SNMPSECURITYLEVEL_NOAUTHNOPRIV, "noAuthNoPriv" },
    { SNMP_FRAMEWORK_MIB_SNMPSECURITYLEVEL_AUTHNOPRIV,   "authNoPriv" },
    { SNMP_FRAMEWORK_MIB_SNMPSECURITYLEVEL_AUTHPRIV,     "authPriv" },
    { 0, NULL }
};


static guint32 const snmpAuthProtocols[]
	= { SNMP_FRAMEWORK_MIB_SNMPAUTHPROTOCOLS };
static guint32 const snmpPrivProtocols[]
	= { SNMP_FRAMEWORK_MIB_SNMPPRIVPROTOCOLS };

GSnmpIdentity const snmp_framework_mib_identities[] = {
    { snmpAuthProtocols,
      sizeof(snmpAuthProtocols)/sizeof(guint32),
      "snmpAuthProtocols" },
    { snmpPrivProtocols,
      sizeof(snmpPrivProtocols)/sizeof(guint32),
      "snmpPrivProtocols" },
    { 0, 0, NULL }
};


static guint16 snmpEngineID_constraints[] = {5U, 32U, 0, 0};
static gint32 snmpEngineBoots_constraints[] = {1L, 2147483647L, 0, 0};
static gint32 snmpEngineTime_constraints[] = {0L, 2147483647L, 0, 0};
static gint32 snmpEngineMaxMessageSize_constraints[] = {484L, 2147483647L, 0, 0};


static guint32 const snmpEngine_oid[] = {1, 3, 6, 1, 6, 3, 10, 2, 1};

static GSnmpAttribute snmpEngine_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SNMP_FRAMEWORK_MIB_SNMPENGINEID, "snmpEngineID",
       snmpEngineID_constraints,
      G_STRUCT_OFFSET(snmp_framework_mib_snmpEngine_t, snmpEngineID),
      G_STRUCT_OFFSET(snmp_framework_mib_snmpEngine_t, _snmpEngineIDLength),
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_FRAMEWORK_MIB_SNMPENGINEBOOTS, "snmpEngineBoots",
       snmpEngineBoots_constraints,
      G_STRUCT_OFFSET(snmp_framework_mib_snmpEngine_t, snmpEngineBoots),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_FRAMEWORK_MIB_SNMPENGINETIME, "snmpEngineTime",
       snmpEngineTime_constraints,
      G_STRUCT_OFFSET(snmp_framework_mib_snmpEngine_t, snmpEngineTime),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SNMP_FRAMEWORK_MIB_SNMPENGINEMAXMESSAGESIZE, "snmpEngineMaxMessageSize",
       snmpEngineMaxMessageSize_constraints,
      G_STRUCT_OFFSET(snmp_framework_mib_snmpEngine_t, snmpEngineMaxMessageSize),
      0,
      0 },
    { 0, 0, 0, NULL }
};


snmp_framework_mib_snmpEngine_t *
snmp_framework_mib_new_snmpEngine()
{
    snmp_framework_mib_snmpEngine_t *snmpEngine;

    snmpEngine = (snmp_framework_mib_snmpEngine_t *) g_malloc0(sizeof(snmp_framework_mib_snmpEngine_t) + sizeof(gpointer));
    return snmpEngine;
}

static inline snmp_framework_mib_snmpEngine_t *
assign_snmpEngine(GList *vbl)
{
    snmp_framework_mib_snmpEngine_t *snmpEngine;
    char *p;

    snmpEngine = snmp_framework_mib_new_snmpEngine();
    p = (char *) snmpEngine + sizeof(snmp_framework_mib_snmpEngine_t);
    * (GList **) p = vbl;

    gsnmp_attr_assign(vbl, snmpEngine_oid, sizeof(snmpEngine_oid)/sizeof(guint32),
                      snmpEngine_attr, snmpEngine);

    return snmpEngine;
}

void
snmp_framework_mib_get_snmpEngine(GSnmpSession *s, snmp_framework_mib_snmpEngine_t **snmpEngine, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 10, 2, 1, 0};

    *snmpEngine = NULL;

    gsnmp_attr_get(s, &in, base, 10, 9, snmpEngine_attr, mask);

    out = g_snmp_session_sync_getnext(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_free, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_free, NULL);
            g_list_free(out);
            return;
        }
        *snmpEngine = assign_snmpEngine(out);
    }
}

void
snmp_framework_mib_free_snmpEngine(snmp_framework_mib_snmpEngine_t *snmpEngine)
{
    GList *vbl;
    char *p;

    if (snmpEngine) {
        p = (char *) snmpEngine + sizeof(snmp_framework_mib_snmpEngine_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_free, NULL);
        g_list_free(vbl);
        g_free(snmpEngine);
    }
}


