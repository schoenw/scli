/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from SNMP-FRAMEWORK-MIB:
 *   The SNMP Management Architecture MIB
 *
 * Revision 1999-01-19 00:00:
 *   Updated editors' addresses, fixed typos.
 *   Published as RFC2571.
 *   
 *
 * Revision 1997-11-20 00:00:
 *   The initial version, published in RFC 2271.
 *   
 *
 * $Id$
 */

#include "snmp-framework-mib.h"

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


typedef struct {
    guint32 const     subid;
    GSnmpVarBindType  type;
    gchar            *label;
} stls_stub_attr_t;

static void
add_attributes(GSnmpSession *s, GSList **vbl, guint32 *base, guint idx,
               stls_stub_attr_t *attributes)
{
    int i;

    for (i = 0; attributes[i].label; i++) {
        if (attributes[i].type != G_SNMP_COUNTER64 || s->version > G_SNMP_V1) {
            base[idx] = attributes[i].subid;
            g_snmp_vbl_add_null(vbl, base, idx + 1);
        }
    }
}

static int
lookup(GSnmpVarBind *vb, guint32 const *base, gsize const base_len,
	    stls_stub_attr_t *attributes, guint32 *idx)
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

static stls_stub_attr_t _snmpEngine[] = {
    { 1, G_SNMP_OCTET_STRING, "snmpEngineID" },
    { 2, G_SNMP_INTEGER32, "snmpEngineBoots" },
    { 3, G_SNMP_INTEGER32, "snmpEngineTime" },
    { 4, G_SNMP_INTEGER32, "snmpEngineMaxMessageSize" },
    { 0, 0, NULL }
};


snmp_framework_mib_snmpEngine_t *
snmp_framework_mib_new_snmpEngine()
{
    snmp_framework_mib_snmpEngine_t *snmpEngine;

    snmpEngine = (snmp_framework_mib_snmpEngine_t *) g_malloc0(sizeof(snmp_framework_mib_snmpEngine_t) + sizeof(gpointer));
    return snmpEngine;
}

static snmp_framework_mib_snmpEngine_t *
assign_snmpEngine(GSList *vbl)
{
    GSList *elem;
    snmp_framework_mib_snmpEngine_t *snmpEngine;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 10, 2, 1};

    snmpEngine = snmp_framework_mib_new_snmpEngine();
    if (! snmpEngine) {
        return NULL;
    }

    p = (char *) snmpEngine + sizeof(snmp_framework_mib_snmpEngine_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (lookup(vb, base, sizeof(base)/sizeof(guint32),
                   _snmpEngine, &idx) < 0) continue;

        switch (idx) {
        case 1:
            snmpEngine->_snmpEngineIDLength = vb->syntax_len;
            snmpEngine->snmpEngineID = vb->syntax.uc;
            break;
        case 2:
            snmpEngine->snmpEngineBoots = &(vb->syntax.i32[0]);
            break;
        case 3:
            snmpEngine->snmpEngineTime = &(vb->syntax.i32[0]);
            break;
        case 4:
            snmpEngine->snmpEngineMaxMessageSize = &(vb->syntax.i32[0]);
            break;
        };
    }

    return snmpEngine;
}

int
snmp_framework_mib_get_snmpEngine(GSnmpSession *s, snmp_framework_mib_snmpEngine_t **snmpEngine)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 10, 2, 1, 0};

    *snmpEngine = NULL;

    add_attributes(s, &in, base, 9, _snmpEngine);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (! out) {
        return -2;
    }

    *snmpEngine = assign_snmpEngine(out);

    return 0;
}

void
snmp_framework_mib_free_snmpEngine(snmp_framework_mib_snmpEngine_t *snmpEngine)
{
    GSList *vbl;
    char *p;

    if (snmpEngine) {
        p = (char *) snmpEngine + sizeof(snmp_framework_mib_snmpEngine_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpEngine);
    }
}


