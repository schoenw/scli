/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from SNMP-MPD-MIB:
 *   The MIB for Message Processing and Dispatching
 *
 * Revision 1999-05-04 16:36:
 *   Updated addresses, published as RFC 2572.
 *
 * Revision 1997-09-30 00:00:
 *   Original version, published as RFC 2272.
 *
 * $Id$
 */

#include "snmp-mpd-mib.h"

static stls_stub_attr_t _snmpMPDStats[] = {
    { 1, G_SNMP_COUNTER32, "snmpUnknownSecurityModels" },
    { 2, G_SNMP_COUNTER32, "snmpInvalidMsgs" },
    { 3, G_SNMP_COUNTER32, "snmpUnknownPDUHandlers" },
    { 0, 0, NULL }
};


snmp_mpd_mib_snmpMPDStats_t *
snmp_mpd_mib_new_snmpMPDStats()
{
    snmp_mpd_mib_snmpMPDStats_t *snmpMPDStats;

    snmpMPDStats = (snmp_mpd_mib_snmpMPDStats_t *) g_malloc0(sizeof(snmp_mpd_mib_snmpMPDStats_t) + sizeof(gpointer));
    return snmpMPDStats;
}

static snmp_mpd_mib_snmpMPDStats_t *
assign_snmpMPDStats(GSList *vbl)
{
    GSList *elem;
    snmp_mpd_mib_snmpMPDStats_t *snmpMPDStats;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 11, 2, 1};

    snmpMPDStats = snmp_mpd_mib_new_snmpMPDStats();
    if (! snmpMPDStats) {
        return NULL;
    }

    p = (char *) snmpMPDStats + sizeof(snmp_mpd_mib_snmpMPDStats_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _snmpMPDStats, &idx) < 0) continue;

        switch (idx) {
        case 1:
            snmpMPDStats->snmpUnknownSecurityModels = &(vb->syntax.ui32[0]);
            break;
        case 2:
            snmpMPDStats->snmpInvalidMsgs = &(vb->syntax.ui32[0]);
            break;
        case 3:
            snmpMPDStats->snmpUnknownPDUHandlers = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return snmpMPDStats;
}

int
snmp_mpd_mib_get_snmpMPDStats(GSnmpSession *s, snmp_mpd_mib_snmpMPDStats_t **snmpMPDStats)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 11, 2, 1, 0};

    *snmpMPDStats = NULL;

    stls_vbl_attributes(s, &in, base, 9, _snmpMPDStats);

    out = g_snmp_session_sync_getnext(s, in);
    g_snmp_vbl_free(in);
    if (! out) {
        return -2;
    }

    *snmpMPDStats = assign_snmpMPDStats(out);

    return 0;
}

void
snmp_mpd_mib_free_snmpMPDStats(snmp_mpd_mib_snmpMPDStats_t *snmpMPDStats)
{
    GSList *vbl;
    char *p;

    if (snmpMPDStats) {
        p = (char *) snmpMPDStats + sizeof(snmp_mpd_mib_snmpMPDStats_t);
        vbl = * (GSList **) p;
        g_snmp_vbl_free(vbl);
        g_free(snmpMPDStats);
    }
}


