/*							-- DO NOT EDIT --
 * Generated by smidump version 0.5.0:
 *   smidump -f scli \
 *     --scli-include='lowpanStats' JACOBS-LOWPAN-MIB
 *
 * Derived from JACOBS-LOWPAN-MIB:
 *   The MIB module for monitoring nodes implementing the IPv6
 *   over Low-Power Wireless Personal Area Networks (6LoWPAN)
 *   protocol.
 *   
 *   
 *   
 *   Copyright (c) 2014 IETF Trust and the persons identified as
 *   authors of the code.  All rights reserved.
 *   
 *   Redistribution and use in source and binary forms, with or
 *   without modification, is permitted pursuant to, and subject
 *   to the license terms contained in, the Simplified BSD
 *   License set forth in Section 4.c of the IETF Trust's
 *   Legal Provisions Relating to IETF Documents
 *   (http://trustee.ietf.org/license-info).
 *
 * Revision 2014-04-08 00:00:
 *   Initial version, published as RFC XXXX.
 *
 * $Id$
 */

#include "jacobs-lowpan-mib.h"

static guint32 const lowpanStats_oid[] = {1, 3, 6, 1, 4, 1, 30982, 1, 3, 1, 1};

static GNetSnmpAttribute lowpanStats_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      JACOBS_LOWPAN_MIB_LOWPANREASMTIMEOUT, "lowpanReasmTimeout",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanReasmTimeout),
      0,
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINRECEIVES, "lowpanInReceives",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInReceives),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINHDRERRORS, "lowpanInHdrErrors",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInHdrErrors),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINMESHRECEIVES, "lowpanInMeshReceives",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInMeshReceives),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINMESHFORWDS, "lowpanInMeshForwds",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInMeshForwds),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINMESHDELIVERS, "lowpanInMeshDelivers",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInMeshDelivers),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINREASMREQDS, "lowpanInReasmReqds",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInReasmReqds),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINREASMFAILS, "lowpanInReasmFails",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInReasmFails),
      0,
      0 },
    { 9, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINREASMOKS, "lowpanInReasmOKs",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInReasmOKs),
      0,
      0 },
    { 10, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINCOMPREQDS, "lowpanInCompReqds",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInCompReqds),
      0,
      0 },
    { 11, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINCOMPFAILS, "lowpanInCompFails",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInCompFails),
      0,
      0 },
    { 12, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINCOMPOKS, "lowpanInCompOKs",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInCompOKs),
      0,
      0 },
    { 13, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINDISCARDS, "lowpanInDiscards",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInDiscards),
      0,
      0 },
    { 14, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANINDELIVERS, "lowpanInDelivers",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanInDelivers),
      0,
      0 },
    { 15, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTREQUESTS, "lowpanOutRequests",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutRequests),
      0,
      0 },
    { 16, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTCOMPREQDS, "lowpanOutCompReqds",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutCompReqds),
      0,
      0 },
    { 17, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTCOMPFAILS, "lowpanOutCompFails",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutCompFails),
      0,
      0 },
    { 18, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTCOMPOKS, "lowpanOutCompOKs",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutCompOKs),
      0,
      0 },
    { 19, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGREQDS, "lowpanOutFragReqds",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutFragReqds),
      0,
      0 },
    { 20, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGFAILS, "lowpanOutFragFails",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutFragFails),
      0,
      0 },
    { 21, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGOKS, "lowpanOutFragOKs",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutFragOKs),
      0,
      0 },
    { 22, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGCREATES, "lowpanOutFragCreates",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutFragCreates),
      0,
      0 },
    { 23, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHHOPLIMITEXCEEDS, "lowpanOutMeshHopLimitExceeds",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutMeshHopLimitExceeds),
      0,
      0 },
    { 24, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHNOROUTES, "lowpanOutMeshNoRoutes",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutMeshNoRoutes),
      0,
      0 },
    { 25, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHREQUESTS, "lowpanOutMeshRequests",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutMeshRequests),
      0,
      0 },
    { 26, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHFORWDS, "lowpanOutMeshForwds",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutMeshForwds),
      0,
      0 },
    { 27, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHTRANSMITS, "lowpanOutMeshTransmits",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutMeshTransmits),
      0,
      0 },
    { 28, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTDISCARDS, "lowpanOutDiscards",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutDiscards),
      0,
      0 },
    { 29, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      JACOBS_LOWPAN_MIB_LOWPANOUTTRANSMITS, "lowpanOutTransmits",
       NULL,
      G_STRUCT_OFFSET(jacobs_lowpan_mib_lowpanStats_t, lowpanOutTransmits),
      0,
      0 },
    { 0, 0, 0, NULL }
};


jacobs_lowpan_mib_lowpanStats_t *
jacobs_lowpan_mib_new_lowpanStats()
{
    jacobs_lowpan_mib_lowpanStats_t *lowpanStats;

    lowpanStats = (jacobs_lowpan_mib_lowpanStats_t *) g_malloc0(sizeof(jacobs_lowpan_mib_lowpanStats_t) + sizeof(gpointer));
    return lowpanStats;
}

static inline jacobs_lowpan_mib_lowpanStats_t *
assign_lowpanStats(GList *vbl)
{
    jacobs_lowpan_mib_lowpanStats_t *lowpanStats;
    char *p;

    lowpanStats = jacobs_lowpan_mib_new_lowpanStats();
    p = (char *) lowpanStats + sizeof(jacobs_lowpan_mib_lowpanStats_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, lowpanStats_oid, G_N_ELEMENTS(lowpanStats_oid),
                      lowpanStats_attr, lowpanStats);

    return lowpanStats;
}

void
jacobs_lowpan_mib_get_lowpanStats(GNetSnmp *s, jacobs_lowpan_mib_lowpanStats_t **lowpanStats, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    static const guint32 _base[] = {1, 3, 6, 1, 4, 1, 30982, 1, 3, 1, 1, 0};
    guint32 base[128];

    *lowpanStats = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 12, 11, lowpanStats_attr, mask);

    out = gnet_snmp_sync_getnext(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if ((error && *error) || s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *lowpanStats = assign_lowpanStats(out);
    }
}

void
jacobs_lowpan_mib_free_lowpanStats(jacobs_lowpan_mib_lowpanStats_t *lowpanStats)
{
    GList *vbl;
    char *p;

    if (lowpanStats) {
        p = (char *) lowpanStats + sizeof(jacobs_lowpan_mib_lowpanStats_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(lowpanStats);
    }
}


