/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.16 for the stools package.
 *
 * Derived from SNMPv2-MIB:
 *   The MIB module for SNMPv2 entities.
 *
 * Revision 1995-11-09 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 1993-04-01 00:00:
 *   The initial revision of this MIB module was published as
 *   RFC 1450.
 *
 * $Id$
 */

#include "snmpv2-mib.h"

stls_enum_t const snmpv2_mib_enums_snmpEnableAuthenTraps[] = {
    { SNMPV2_MIB_SNMPENABLEAUTHENTRAPS_ENABLED,	"enabled" },
    { SNMPV2_MIB_SNMPENABLEAUTHENTRAPS_DISABLED,	"disabled" },
    { 0, NULL }
};


static stls_stub_attr_t _system[] = {
    { 1, G_SNMP_OCTET_STRING, "sysDescr" },
    { 2, G_SNMP_OBJECT_ID, "sysObjectID" },
    { 3, G_SNMP_TIMETICKS, "sysUpTime" },
    { 4, G_SNMP_OCTET_STRING, "sysContact" },
    { 5, G_SNMP_OCTET_STRING, "sysName" },
    { 6, G_SNMP_OCTET_STRING, "sysLocation" },
    { 7, G_SNMP_INTEGER32, "sysServices" },
    { 8, G_SNMP_TIMETICKS, "sysORLastChange" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _sysOREntry[] = {
    { 2, G_SNMP_OBJECT_ID, "sysORID" },
    { 3, G_SNMP_OCTET_STRING, "sysORDescr" },
    { 4, G_SNMP_TIMETICKS, "sysORUpTime" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _snmp[] = {
    { 1, G_SNMP_COUNTER32, "snmpInPkts" },
    { 2, G_SNMP_COUNTER32, "snmpOutPkts" },
    { 3, G_SNMP_COUNTER32, "snmpInBadVersions" },
    { 4, G_SNMP_COUNTER32, "snmpInBadCommunityNames" },
    { 5, G_SNMP_COUNTER32, "snmpInBadCommunityUses" },
    { 6, G_SNMP_COUNTER32, "snmpInASNParseErrs" },
    { 8, G_SNMP_COUNTER32, "snmpInTooBigs" },
    { 9, G_SNMP_COUNTER32, "snmpInNoSuchNames" },
    { 10, G_SNMP_COUNTER32, "snmpInBadValues" },
    { 11, G_SNMP_COUNTER32, "snmpInReadOnlys" },
    { 12, G_SNMP_COUNTER32, "snmpInGenErrs" },
    { 13, G_SNMP_COUNTER32, "snmpInTotalReqVars" },
    { 14, G_SNMP_COUNTER32, "snmpInTotalSetVars" },
    { 15, G_SNMP_COUNTER32, "snmpInGetRequests" },
    { 16, G_SNMP_COUNTER32, "snmpInGetNexts" },
    { 17, G_SNMP_COUNTER32, "snmpInSetRequests" },
    { 18, G_SNMP_COUNTER32, "snmpInGetResponses" },
    { 19, G_SNMP_COUNTER32, "snmpInTraps" },
    { 20, G_SNMP_COUNTER32, "snmpOutTooBigs" },
    { 21, G_SNMP_COUNTER32, "snmpOutNoSuchNames" },
    { 22, G_SNMP_COUNTER32, "snmpOutBadValues" },
    { 24, G_SNMP_COUNTER32, "snmpOutGenErrs" },
    { 25, G_SNMP_COUNTER32, "snmpOutGetRequests" },
    { 26, G_SNMP_COUNTER32, "snmpOutGetNexts" },
    { 27, G_SNMP_COUNTER32, "snmpOutSetRequests" },
    { 28, G_SNMP_COUNTER32, "snmpOutGetResponses" },
    { 29, G_SNMP_COUNTER32, "snmpOutTraps" },
    { 30, G_SNMP_INTEGER32, "snmpEnableAuthenTraps" },
    { 31, G_SNMP_COUNTER32, "snmpSilentDrops" },
    { 32, G_SNMP_COUNTER32, "snmpProxyDrops" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _snmpSet[] = {
    { 1, G_SNMP_INTEGER32, "snmpSetSerialNo" },
    { 0, 0, NULL }
};


snmpv2_mib_system_t *
snmpv2_mib_new_system()
{
    snmpv2_mib_system_t *system;

    system = (snmpv2_mib_system_t *) g_malloc0(sizeof(snmpv2_mib_system_t) + sizeof(gpointer));
    return system;
}

static snmpv2_mib_system_t *
assign_system(GSList *vbl)
{
    GSList *elem;
    snmpv2_mib_system_t *system;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 1};

    system = snmpv2_mib_new_system();
    if (! system) {
        return NULL;
    }

    p = (char *) system + sizeof(snmpv2_mib_system_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _system, &idx) < 0) continue;

        switch (idx) {
        case 1:
            system->_sysDescrLength = vb->syntax_len;
            system->sysDescr = vb->syntax.uc;
            break;
        case 2:
            system->_sysObjectIDLength = vb->syntax_len / sizeof(guint32);
            system->sysObjectID = vb->syntax.ui32;
            break;
        case 3:
            system->sysUpTime = &(vb->syntax.ui32[0]);
            break;
        case 4:
            system->_sysContactLength = vb->syntax_len;
            system->sysContact = vb->syntax.uc;
            break;
        case 5:
            system->_sysNameLength = vb->syntax_len;
            system->sysName = vb->syntax.uc;
            break;
        case 6:
            system->_sysLocationLength = vb->syntax_len;
            system->sysLocation = vb->syntax.uc;
            break;
        case 7:
            system->sysServices = &(vb->syntax.i32[0]);
            break;
        case 8:
            system->sysORLastChange = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return system;
}

int
snmpv2_mib_get_system(host_snmp *s, snmpv2_mib_system_t **system)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 1, 0};

    *system = NULL;

    stls_vbl_attributes(s, &in, base, 7, _system);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *system = assign_system(out);

    return 0;
}

void
snmpv2_mib_free_system(snmpv2_mib_system_t *system)
{
    GSList *vbl;
    char *p;

    if (system) {
        p = (char *) system + sizeof(snmpv2_mib_system_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(system);
    }
}

snmpv2_mib_sysOREntry_t *
snmpv2_mib_new_sysOREntry()
{
    snmpv2_mib_sysOREntry_t *sysOREntry;

    sysOREntry = (snmpv2_mib_sysOREntry_t *) g_malloc0(sizeof(snmpv2_mib_sysOREntry_t) + sizeof(gpointer));
    return sysOREntry;
}

static int
unpack_sysOREntry(GSnmpVarBind *vb, snmpv2_mib_sysOREntry_t *sysOREntry)
{
    int idx = 10;

    if (vb->id_len < idx) return -1;
    sysOREntry->sysORIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static snmpv2_mib_sysOREntry_t *
assign_sysOREntry(GSList *vbl)
{
    GSList *elem;
    snmpv2_mib_sysOREntry_t *sysOREntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 1, 9, 1};

    sysOREntry = snmpv2_mib_new_sysOREntry();
    if (! sysOREntry) {
        return NULL;
    }

    p = (char *) sysOREntry + sizeof(snmpv2_mib_sysOREntry_t);
    * (GSList **) p = vbl;

    if (unpack_sysOREntry((GSnmpVarBind *) vbl->data, sysOREntry) < 0) {
        g_warning("illegal sysOREntry instance identifier");
        g_free(sysOREntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _sysOREntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            sysOREntry->_sysORIDLength = vb->syntax_len / sizeof(guint32);
            sysOREntry->sysORID = vb->syntax.ui32;
            break;
        case 3:
            sysOREntry->_sysORDescrLength = vb->syntax_len;
            sysOREntry->sysORDescr = vb->syntax.uc;
            break;
        case 4:
            sysOREntry->sysORUpTime = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return sysOREntry;
}

int
snmpv2_mib_get_sysORTable(host_snmp *s, snmpv2_mib_sysOREntry_t ***sysOREntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 1, 9, 1, 0};

    *sysOREntry = NULL;

    stls_vbl_attributes(s, &in, base, 9, _sysOREntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *sysOREntry = (snmpv2_mib_sysOREntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(snmpv2_mib_sysOREntry_t *));
    if (! *sysOREntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*sysOREntry)[i] = assign_sysOREntry(row->data);
    }

    return 0;
}

void
snmpv2_mib_free_sysOREntry(snmpv2_mib_sysOREntry_t *sysOREntry)
{
    GSList *vbl;
    char *p;

    if (sysOREntry) {
        p = (char *) sysOREntry + sizeof(snmpv2_mib_sysOREntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(sysOREntry);
    }
}

void
snmpv2_mib_free_sysORTable(snmpv2_mib_sysOREntry_t **sysOREntry)
{
    int i;

    if (sysOREntry) {
        for (i = 0; sysOREntry[i]; i++) {
            snmpv2_mib_free_sysOREntry(sysOREntry[i]);
        }
        g_free(sysOREntry);
    }
}

snmpv2_mib_snmp_t *
snmpv2_mib_new_snmp()
{
    snmpv2_mib_snmp_t *snmp;

    snmp = (snmpv2_mib_snmp_t *) g_malloc0(sizeof(snmpv2_mib_snmp_t) + sizeof(gpointer));
    return snmp;
}

static snmpv2_mib_snmp_t *
assign_snmp(GSList *vbl)
{
    GSList *elem;
    snmpv2_mib_snmp_t *snmp;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 11};

    snmp = snmpv2_mib_new_snmp();
    if (! snmp) {
        return NULL;
    }

    p = (char *) snmp + sizeof(snmpv2_mib_snmp_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _snmp, &idx) < 0) continue;

        switch (idx) {
        case 1:
            snmp->snmpInPkts = &(vb->syntax.ui32[0]);
            break;
        case 2:
            snmp->snmpOutPkts = &(vb->syntax.ui32[0]);
            break;
        case 3:
            snmp->snmpInBadVersions = &(vb->syntax.ui32[0]);
            break;
        case 4:
            snmp->snmpInBadCommunityNames = &(vb->syntax.ui32[0]);
            break;
        case 5:
            snmp->snmpInBadCommunityUses = &(vb->syntax.ui32[0]);
            break;
        case 6:
            snmp->snmpInASNParseErrs = &(vb->syntax.ui32[0]);
            break;
        case 8:
            snmp->snmpInTooBigs = &(vb->syntax.ui32[0]);
            break;
        case 9:
            snmp->snmpInNoSuchNames = &(vb->syntax.ui32[0]);
            break;
        case 10:
            snmp->snmpInBadValues = &(vb->syntax.ui32[0]);
            break;
        case 11:
            snmp->snmpInReadOnlys = &(vb->syntax.ui32[0]);
            break;
        case 12:
            snmp->snmpInGenErrs = &(vb->syntax.ui32[0]);
            break;
        case 13:
            snmp->snmpInTotalReqVars = &(vb->syntax.ui32[0]);
            break;
        case 14:
            snmp->snmpInTotalSetVars = &(vb->syntax.ui32[0]);
            break;
        case 15:
            snmp->snmpInGetRequests = &(vb->syntax.ui32[0]);
            break;
        case 16:
            snmp->snmpInGetNexts = &(vb->syntax.ui32[0]);
            break;
        case 17:
            snmp->snmpInSetRequests = &(vb->syntax.ui32[0]);
            break;
        case 18:
            snmp->snmpInGetResponses = &(vb->syntax.ui32[0]);
            break;
        case 19:
            snmp->snmpInTraps = &(vb->syntax.ui32[0]);
            break;
        case 20:
            snmp->snmpOutTooBigs = &(vb->syntax.ui32[0]);
            break;
        case 21:
            snmp->snmpOutNoSuchNames = &(vb->syntax.ui32[0]);
            break;
        case 22:
            snmp->snmpOutBadValues = &(vb->syntax.ui32[0]);
            break;
        case 24:
            snmp->snmpOutGenErrs = &(vb->syntax.ui32[0]);
            break;
        case 25:
            snmp->snmpOutGetRequests = &(vb->syntax.ui32[0]);
            break;
        case 26:
            snmp->snmpOutGetNexts = &(vb->syntax.ui32[0]);
            break;
        case 27:
            snmp->snmpOutSetRequests = &(vb->syntax.ui32[0]);
            break;
        case 28:
            snmp->snmpOutGetResponses = &(vb->syntax.ui32[0]);
            break;
        case 29:
            snmp->snmpOutTraps = &(vb->syntax.ui32[0]);
            break;
        case 30:
            snmp->snmpEnableAuthenTraps = &(vb->syntax.i32[0]);
            break;
        case 31:
            snmp->snmpSilentDrops = &(vb->syntax.ui32[0]);
            break;
        case 32:
            snmp->snmpProxyDrops = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return snmp;
}

int
snmpv2_mib_get_snmp(host_snmp *s, snmpv2_mib_snmp_t **snmp)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 11, 0};

    *snmp = NULL;

    stls_vbl_attributes(s, &in, base, 7, _snmp);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *snmp = assign_snmp(out);

    return 0;
}

void
snmpv2_mib_free_snmp(snmpv2_mib_snmp_t *snmp)
{
    GSList *vbl;
    char *p;

    if (snmp) {
        p = (char *) snmp + sizeof(snmpv2_mib_snmp_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(snmp);
    }
}

snmpv2_mib_snmpSet_t *
snmpv2_mib_new_snmpSet()
{
    snmpv2_mib_snmpSet_t *snmpSet;

    snmpSet = (snmpv2_mib_snmpSet_t *) g_malloc0(sizeof(snmpv2_mib_snmpSet_t) + sizeof(gpointer));
    return snmpSet;
}

static snmpv2_mib_snmpSet_t *
assign_snmpSet(GSList *vbl)
{
    GSList *elem;
    snmpv2_mib_snmpSet_t *snmpSet;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 6, 3, 1, 1, 6};

    snmpSet = snmpv2_mib_new_snmpSet();
    if (! snmpSet) {
        return NULL;
    }

    p = (char *) snmpSet + sizeof(snmpv2_mib_snmpSet_t);
    * (GSList **) p = vbl;

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _snmpSet, &idx) < 0) continue;

        switch (idx) {
        case 1:
            snmpSet->snmpSetSerialNo = &(vb->syntax.i32[0]);
            break;
        };
    }

    return snmpSet;
}

int
snmpv2_mib_get_snmpSet(host_snmp *s, snmpv2_mib_snmpSet_t **snmpSet)
{
    GSList *in = NULL, *out = NULL;
    static guint32 base[] = {1, 3, 6, 1, 6, 3, 1, 1, 6, 0};

    *snmpSet = NULL;

    stls_vbl_attributes(s, &in, base, 9, _snmpSet);

    out = stls_snmp_getnext(s, in);
    stls_vbl_free(in);
    if (! out) {
        return -2;
    }

    *snmpSet = assign_snmpSet(out);

    return 0;
}

void
snmpv2_mib_free_snmpSet(snmpv2_mib_snmpSet_t *snmpSet)
{
    GSList *vbl;
    char *p;

    if (snmpSet) {
        p = (char *) snmpSet + sizeof(snmpv2_mib_snmpSet_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(snmpSet);
    }
}


