/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
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

snmpEngine_t *
snmp_framework_mib_new_snmpEngine()
{
    snmpEngine_t *snmpEngine;

    snmpEngine = (snmpEngine_t *) g_malloc0(sizeof(snmpEngine_t) + sizeof(gpointer));
    return snmpEngine;
}

static snmpEngine_t *
assign_snmpEngine(GSList *vbl)
{
    GSList *elem;
    snmpEngine_t *snmpEngine;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 10, 2, 1};

    snmpEngine = snmp_framework_mib_new_snmpEngine();
    if (! snmpEngine) {
        return NULL;
    }

    p = (char *) snmpEngine + sizeof(snmpEngine_t);
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
            snmpEngine->_snmpEngineIDLength = vb->syntax_len;
            snmpEngine->snmpEngineID = vb->syntax.uc;
        }
        if (vb->id_len > 10 && vb->id[9] == 2) {
            snmpEngine->snmpEngineBoots = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 3) {
            snmpEngine->snmpEngineTime = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 10 && vb->id[9] == 4) {
            snmpEngine->snmpEngineMaxMessageSize = &(vb->syntax.i32[0]);
        }
    }

    return snmpEngine;
}

int
snmp_framework_mib_get_snmpEngine(host_snmp *s, snmpEngine_t **snmpEngine)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 10, 2, 1, 0};

    *snmpEngine = NULL;

    base[9] = 1; stls_vbl_add_null(&in, base, 10);
    base[9] = 2; stls_vbl_add_null(&in, base, 10);
    base[9] = 3; stls_vbl_add_null(&in, base, 10);
    base[9] = 4; stls_vbl_add_null(&in, base, 10);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *snmpEngine = assign_snmpEngine(out);

    return 0;
}

void
snmp_framework_mib_free_snmpEngine(snmpEngine_t *snmpEngine)
{
    GSList *vbl;
    char *p;

    if (snmpEngine) {
        p = (char *) snmpEngine + sizeof(snmpEngine_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(snmpEngine);
    }
}


