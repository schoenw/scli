/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli \
 *     --scli-include='sonetMediumEntry|sonetSection' SONET-MIB
 *
 * Derived from SONET-MIB:
 *   The MIB module to describe SONET/SDH interface objects.
 *   
 *   Copyright (C) The Internet Society (2003).  This version
 *   of this MIB module is part of RFC 3592;  see the RFC
 *   itself for full legal notices.
 *
 * Revision 2003-08-11 00:00:
 *   The key changes made to this MIB module
 *   since its publication in RFC 2558
 *   are as follows.
 *   
 *   (1) Corrected typographical error
 *       (bellcore1991(2) in sonetSESthresholdSet)
 *   
 *   (2) Added support for sts192cSTM64(6) and
 *       sts768cSTM256(7) in sonetPathCurrentWidth
 *   
 *   (3) Corrected description of the applicability
 *       of VTs for SDH for improved accuracy
 *   
 *   (4) Added clarification in the SES description that
 *       CV counts should be frozen during SESs
 *   
 *   (5) Corrected typographical errors:
 *       - Line Alarm Indication Signal description of the
 *         Terminology section (20.5 --> 2.5 seconds)
 *       - In the Terminology section
 *         sonetSESThresholdSet  --> sonetSESthresholdSet
 *       
 *
 * Revision 1998-10-19 00:00:
 *   The RFC 2558 version of this MIB module.
 *   
 *   
 *   
 *   
 *   
 *   The key changes made to this MIB module
 *   since its initial publication in RFC 1595
 *   are as follows.
 *   
 *   (1) The MODULE-IDENTITY has been updated to reflect the
 *       changes to the MIB.
 *   
 *   (2) Where applicable, the textual conventions
 *       PerfCurrentCount and PerfIntervalCount from
 *       PerfHist-TC-MIB have been used in place of Gauge32.
 *   
 *   (3) An agent now has the option to delay updates to
 *       the various performance counts in lieu of performing
 *       retroactive adjustments upon entering into or exiting
 *       from unavailable time. This implementation option is
 *       described in Appendix A of this memo.
 *   
 *   (4) In order to make the SONET-MIB more useful for
 *       circuit provisioning, the formerly read-only objects
 *       sonetMediumType, sonetMediumLineCoding,
 *       sonetMediumLineType, and sonetMediumCircuitIdentifier
 *       have been given a MAX-ACCESS of read-write. The
 *       MIN-ACCESS remains read-only.
 *   
 *   (5) The DESCRIPTION clause for sonetMediumTimeElapsed has
 *       been updated to describe its behaviour if the duration
 *       of the current interval exceeds the maximum value.
 *   
 *   (6) The DESCRIPTION clause for sonetMediumValidIntervals
 *       has been updated to describe its behaviour when some
 *       intervals may be unavailable, and the object
 *       sonetMediumInvalidIntervals has been added to keep
 *       count of the number of missing intervals (if any).
 *   
 *   (7) The object sonetMediumLoopbackConfig has been added
 *       to enable or disable loopback configurations.
 *   
 *   (8) Because the error count thresholds for declaring
 *       severely errored seconds that are specified in ANSI
 *       T1.231-1993, ITU-T G.826-1995, and ANSI T1.231-1997
 *       are all different from each other and from the thresholds
 *       specified in RFC 1595, an enumerated INTEGER object
 *       sonetSESthresholdSet has been added to allow an agent
 *       to specify which threshold set is in use. Text has
 *       been added to Section 3 stating that if this object is
 *       not implemented the thresholds specified in RFC 1595
 *       should be assumed, and the table containing those
 *       thresholds has been moved to Appendix B of this memo.
 *   
 *   
 *   
 *   (9) A column with SYNTAX TruthValue has been added to each
 *       interval table.  The purpose of the additional column
 *       is to indicate, for each interval, whether the data
 *       is valid in the sense intended by ANSI T1.231 clause
 *       9.1.2.2 [T1.231a][T1.231b]. The objects in question are:
 *   
 *           sonetSectionIntervalValidData
 *           sonetLineIntervalValidData
 *           sonetFarEndLineIntervalValidData
 *           sonetPathIntervalValidData
 *           sonetFarEndPathIntervalValidData
 *           sonetVTIntervalValidData
 *           sonetFarEndVTIntervalValidData
 *   
 *   (10) The ranges for sonetPathCurrentStatus and
 *       sonetVTCurrentStatus have been made consistent
 *       with the DESCRIPTION clauses.
 *   
 *   (11) The conformance information has been updated. Previous
 *       conformance information from RFC 1595 has been
 *       deprecated. Some typographical errors in the deprecated
 *       section have been corrected in order to prevent
 *       MIB compilation errors.
 *
 * Revision 1994-01-03 00:00:
 *   The RFC 1595 version of this MIB module.
 *
 * $Id$
 */

#include "sonet-mib.h"

GNetSnmpEnum const sonet_mib_enums_sonetMediumType[] = {
    { SONET_MIB_SONETMEDIUMTYPE_SONET, "sonet" },
    { SONET_MIB_SONETMEDIUMTYPE_SDH,   "sdh" },
    { 0, NULL }
};

GNetSnmpEnum const sonet_mib_enums_sonetMediumLineCoding[] = {
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMOTHER, "sonetMediumOther" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMB3ZS,  "sonetMediumB3ZS" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMCMI,   "sonetMediumCMI" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMNRZ,   "sonetMediumNRZ" },
    { SONET_MIB_SONETMEDIUMLINECODING_SONETMEDIUMRZ,    "sonetMediumRZ" },
    { 0, NULL }
};

GNetSnmpEnum const sonet_mib_enums_sonetMediumLineType[] = {
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETOTHER,           "sonetOther" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETSHORTSINGLEMODE, "sonetShortSingleMode" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETLONGSINGLEMODE,  "sonetLongSingleMode" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETMULTIMODE,       "sonetMultiMode" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETCOAX,            "sonetCoax" },
    { SONET_MIB_SONETMEDIUMLINETYPE_SONETUTP,             "sonetUTP" },
    { 0, NULL }
};


static gint32 sonetMediumTimeElapsed_constraints[] = {1L, 900L, 0, 0};
static gint32 sonetMediumValidIntervals_constraints[] = {0L, 96L, 0, 0};
static guint16 sonetMediumCircuitIdentifier_constraints[] = {0U, 255U, 0, 0};
static gint32 sonetMediumInvalidIntervals_constraints[] = {0L, 96L, 0, 0};
static gint32 sonetSectionCurrentStatus_constraints[] = {1L, 6L, 0, 0};


static guint32 const sonetMediumEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 39, 1, 1, 1, 1};

static GNetSnmpAttribute sonetMediumEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETMEDIUMTYPE, "sonetMediumType",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETMEDIUMTIMEELAPSED, "sonetMediumTimeElapsed",
       sonetMediumTimeElapsed_constraints,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumTimeElapsed),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETMEDIUMVALIDINTERVALS, "sonetMediumValidIntervals",
       sonetMediumValidIntervals_constraints,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumValidIntervals),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETMEDIUMLINECODING, "sonetMediumLineCoding",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumLineCoding),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETMEDIUMLINETYPE, "sonetMediumLineType",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumLineType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SONET_MIB_SONETMEDIUMCIRCUITIDENTIFIER, "sonetMediumCircuitIdentifier",
       sonetMediumCircuitIdentifier_constraints,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumCircuitIdentifier),
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, _sonetMediumCircuitIdentifierLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETMEDIUMINVALIDINTERVALS, "sonetMediumInvalidIntervals",
       sonetMediumInvalidIntervals_constraints,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumInvalidIntervals),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_OCTETSTRING,
      SONET_MIB_SONETMEDIUMLOOPBACKCONFIG, "sonetMediumLoopbackConfig",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, sonetMediumLoopbackConfig),
      G_STRUCT_OFFSET(sonet_mib_sonetMediumEntry_t, _sonetMediumLoopbackConfigLength),
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const sonetSectionCurrentEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 39, 1, 2, 1, 1};

static GNetSnmpAttribute sonetSectionCurrentEntry_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETSECTIONCURRENTSTATUS, "sonetSectionCurrentStatus",
       sonetSectionCurrentStatus_constraints,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionCurrentEntry_t, sonetSectionCurrentStatus),
      0,
      0 },
    { 2, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONCURRENTESS, "sonetSectionCurrentESs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionCurrentEntry_t, sonetSectionCurrentESs),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONCURRENTSESS, "sonetSectionCurrentSESs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionCurrentEntry_t, sonetSectionCurrentSESs),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONCURRENTSEFSS, "sonetSectionCurrentSEFSs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionCurrentEntry_t, sonetSectionCurrentSEFSs),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONCURRENTCVS, "sonetSectionCurrentCVs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionCurrentEntry_t, sonetSectionCurrentCVs),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const sonetSectionIntervalEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 39, 1, 2, 2, 1};

static GNetSnmpAttribute sonetSectionIntervalEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONINTERVALESS, "sonetSectionIntervalESs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionIntervalEntry_t, sonetSectionIntervalESs),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONINTERVALSESS, "sonetSectionIntervalSESs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionIntervalEntry_t, sonetSectionIntervalSESs),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONINTERVALSEFSS, "sonetSectionIntervalSEFSs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionIntervalEntry_t, sonetSectionIntervalSEFSs),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_UNSIGNED32,
      SONET_MIB_SONETSECTIONINTERVALCVS, "sonetSectionIntervalCVs",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionIntervalEntry_t, sonetSectionIntervalCVs),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      SONET_MIB_SONETSECTIONINTERVALVALIDDATA, "sonetSectionIntervalValidData",
       NULL,
      G_STRUCT_OFFSET(sonet_mib_sonetSectionIntervalEntry_t, sonetSectionIntervalValidData),
      0,
      0 },
    { 0, 0, 0, NULL }
};


sonet_mib_sonetMediumEntry_t *
sonet_mib_new_sonetMediumEntry()
{
    sonet_mib_sonetMediumEntry_t *sonetMediumEntry;

    sonetMediumEntry = (sonet_mib_sonetMediumEntry_t *) g_malloc0(sizeof(sonet_mib_sonetMediumEntry_t) + sizeof(gpointer));
    return sonetMediumEntry;
}

static inline int
unpack_sonetMediumEntry(GNetSnmpVarBind *vb, sonet_mib_sonetMediumEntry_t *sonetMediumEntry)
{
    guint8 idx = 13;

    if (vb->oid_len < idx) return -1;
    sonetMediumEntry->ifIndex = vb->oid[idx++];
    if ((sonetMediumEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_sonetMediumEntry(guint32 *base, gint32 ifIndex)
{
    guint8 idx = 13;

    base[idx++] = ifIndex;
    return idx;
}

static inline sonet_mib_sonetMediumEntry_t *
assign_sonetMediumEntry(GList *vbl)
{
    sonet_mib_sonetMediumEntry_t *sonetMediumEntry;
    char *p;

    sonetMediumEntry = sonet_mib_new_sonetMediumEntry();
    p = (char *) sonetMediumEntry + sizeof(sonet_mib_sonetMediumEntry_t);
    * (GList **) p = vbl;

    if (unpack_sonetMediumEntry((GNetSnmpVarBind *) vbl->data, sonetMediumEntry) < 0) {
        g_warning("%s: invalid instance identifier", "sonetMediumEntry");
        g_free(sonetMediumEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, sonetMediumEntry_oid, G_N_ELEMENTS(sonetMediumEntry_oid),
                      sonetMediumEntry_attr, sonetMediumEntry);

    return sonetMediumEntry;
}

void
sonet_mib_get_sonetMediumTable(GNetSnmp *s, sonet_mib_sonetMediumEntry_t ***sonetMediumEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 39, 1, 1, 1, 1, 0};

    *sonetMediumEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 13, 12, sonetMediumEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *sonetMediumEntry = (sonet_mib_sonetMediumEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(sonet_mib_sonetMediumEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*sonetMediumEntry)[i] = assign_sonetMediumEntry(row->data);
        }
    }
}

void
sonet_mib_get_sonetMediumEntry(GNetSnmp *s, sonet_mib_sonetMediumEntry_t **sonetMediumEntry, gint32 ifIndex, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sonetMediumEntry_oid, sizeof(sonetMediumEntry_oid));
    len = pack_sonetMediumEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "sonetMediumEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *sonetMediumEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 12, sonetMediumEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *sonetMediumEntry = assign_sonetMediumEntry(out);
    }
}

void
sonet_mib_set_sonetMediumEntry(GNetSnmp *s, sonet_mib_sonetMediumEntry_t *sonetMediumEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sonetMediumEntry_oid, sizeof(sonetMediumEntry_oid));
    len = pack_sonetMediumEntry(base, sonetMediumEntry->ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "sonetMediumEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 12, sonetMediumEntry_attr, mask, sonetMediumEntry);

    out = gnet_snmp_sync_set(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
sonet_mib_free_sonetMediumEntry(sonet_mib_sonetMediumEntry_t *sonetMediumEntry)
{
    GList *vbl;
    char *p;

    if (sonetMediumEntry) {
        p = (char *) sonetMediumEntry + sizeof(sonet_mib_sonetMediumEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(sonetMediumEntry);
    }
}

void
sonet_mib_free_sonetMediumTable(sonet_mib_sonetMediumEntry_t **sonetMediumEntry)
{
    int i;

    if (sonetMediumEntry) {
        for (i = 0; sonetMediumEntry[i]; i++) {
            sonet_mib_free_sonetMediumEntry(sonetMediumEntry[i]);
        }
        g_free(sonetMediumEntry);
    }
}

sonet_mib_sonetSectionCurrentEntry_t *
sonet_mib_new_sonetSectionCurrentEntry()
{
    sonet_mib_sonetSectionCurrentEntry_t *sonetSectionCurrentEntry;

    sonetSectionCurrentEntry = (sonet_mib_sonetSectionCurrentEntry_t *) g_malloc0(sizeof(sonet_mib_sonetSectionCurrentEntry_t) + sizeof(gpointer));
    return sonetSectionCurrentEntry;
}

static inline int
unpack_sonetSectionCurrentEntry(GNetSnmpVarBind *vb, sonet_mib_sonetSectionCurrentEntry_t *sonetSectionCurrentEntry)
{
    guint8 idx = 13;

    if (vb->oid_len < idx) return -1;
    sonetSectionCurrentEntry->ifIndex = vb->oid[idx++];
    if ((sonetSectionCurrentEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_sonetSectionCurrentEntry(guint32 *base, gint32 ifIndex)
{
    guint8 idx = 13;

    base[idx++] = ifIndex;
    return idx;
}

static inline sonet_mib_sonetSectionCurrentEntry_t *
assign_sonetSectionCurrentEntry(GList *vbl)
{
    sonet_mib_sonetSectionCurrentEntry_t *sonetSectionCurrentEntry;
    char *p;

    sonetSectionCurrentEntry = sonet_mib_new_sonetSectionCurrentEntry();
    p = (char *) sonetSectionCurrentEntry + sizeof(sonet_mib_sonetSectionCurrentEntry_t);
    * (GList **) p = vbl;

    if (unpack_sonetSectionCurrentEntry((GNetSnmpVarBind *) vbl->data, sonetSectionCurrentEntry) < 0) {
        g_warning("%s: invalid instance identifier", "sonetSectionCurrentEntry");
        g_free(sonetSectionCurrentEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, sonetSectionCurrentEntry_oid, G_N_ELEMENTS(sonetSectionCurrentEntry_oid),
                      sonetSectionCurrentEntry_attr, sonetSectionCurrentEntry);

    return sonetSectionCurrentEntry;
}

void
sonet_mib_get_sonetSectionCurrentTable(GNetSnmp *s, sonet_mib_sonetSectionCurrentEntry_t ***sonetSectionCurrentEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 39, 1, 2, 1, 1, 0};

    *sonetSectionCurrentEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 13, 12, sonetSectionCurrentEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *sonetSectionCurrentEntry = (sonet_mib_sonetSectionCurrentEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(sonet_mib_sonetSectionCurrentEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*sonetSectionCurrentEntry)[i] = assign_sonetSectionCurrentEntry(row->data);
        }
    }
}

void
sonet_mib_get_sonetSectionCurrentEntry(GNetSnmp *s, sonet_mib_sonetSectionCurrentEntry_t **sonetSectionCurrentEntry, gint32 ifIndex, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sonetSectionCurrentEntry_oid, sizeof(sonetSectionCurrentEntry_oid));
    len = pack_sonetSectionCurrentEntry(base, ifIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "sonetSectionCurrentEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *sonetSectionCurrentEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 12, sonetSectionCurrentEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *sonetSectionCurrentEntry = assign_sonetSectionCurrentEntry(out);
    }
}

void
sonet_mib_free_sonetSectionCurrentEntry(sonet_mib_sonetSectionCurrentEntry_t *sonetSectionCurrentEntry)
{
    GList *vbl;
    char *p;

    if (sonetSectionCurrentEntry) {
        p = (char *) sonetSectionCurrentEntry + sizeof(sonet_mib_sonetSectionCurrentEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(sonetSectionCurrentEntry);
    }
}

void
sonet_mib_free_sonetSectionCurrentTable(sonet_mib_sonetSectionCurrentEntry_t **sonetSectionCurrentEntry)
{
    int i;

    if (sonetSectionCurrentEntry) {
        for (i = 0; sonetSectionCurrentEntry[i]; i++) {
            sonet_mib_free_sonetSectionCurrentEntry(sonetSectionCurrentEntry[i]);
        }
        g_free(sonetSectionCurrentEntry);
    }
}

sonet_mib_sonetSectionIntervalEntry_t *
sonet_mib_new_sonetSectionIntervalEntry()
{
    sonet_mib_sonetSectionIntervalEntry_t *sonetSectionIntervalEntry;

    sonetSectionIntervalEntry = (sonet_mib_sonetSectionIntervalEntry_t *) g_malloc0(sizeof(sonet_mib_sonetSectionIntervalEntry_t) + sizeof(gpointer));
    return sonetSectionIntervalEntry;
}

static inline int
unpack_sonetSectionIntervalEntry(GNetSnmpVarBind *vb, sonet_mib_sonetSectionIntervalEntry_t *sonetSectionIntervalEntry)
{
    guint8 idx = 13;

    if (vb->oid_len < idx) return -1;
    sonetSectionIntervalEntry->ifIndex = vb->oid[idx++];
    if ((sonetSectionIntervalEntry->ifIndex < 1)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    sonetSectionIntervalEntry->sonetSectionIntervalNumber = vb->oid[idx++];
    if ((sonetSectionIntervalEntry->sonetSectionIntervalNumber < 1 || sonetSectionIntervalEntry->sonetSectionIntervalNumber > 96)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_sonetSectionIntervalEntry(guint32 *base, gint32 ifIndex, gint32 sonetSectionIntervalNumber)
{
    guint8 idx = 13;

    base[idx++] = ifIndex;
    base[idx++] = sonetSectionIntervalNumber;
    return idx;
}

static inline sonet_mib_sonetSectionIntervalEntry_t *
assign_sonetSectionIntervalEntry(GList *vbl)
{
    sonet_mib_sonetSectionIntervalEntry_t *sonetSectionIntervalEntry;
    char *p;

    sonetSectionIntervalEntry = sonet_mib_new_sonetSectionIntervalEntry();
    p = (char *) sonetSectionIntervalEntry + sizeof(sonet_mib_sonetSectionIntervalEntry_t);
    * (GList **) p = vbl;

    if (unpack_sonetSectionIntervalEntry((GNetSnmpVarBind *) vbl->data, sonetSectionIntervalEntry) < 0) {
        g_warning("%s: invalid instance identifier", "sonetSectionIntervalEntry");
        g_free(sonetSectionIntervalEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, sonetSectionIntervalEntry_oid, G_N_ELEMENTS(sonetSectionIntervalEntry_oid),
                      sonetSectionIntervalEntry_attr, sonetSectionIntervalEntry);

    return sonetSectionIntervalEntry;
}

void
sonet_mib_get_sonetSectionIntervalTable(GNetSnmp *s, sonet_mib_sonetSectionIntervalEntry_t ***sonetSectionIntervalEntry, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 10, 39, 1, 2, 2, 1, 0};

    *sonetSectionIntervalEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, 13, 12, sonetSectionIntervalEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *sonetSectionIntervalEntry = (sonet_mib_sonetSectionIntervalEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(sonet_mib_sonetSectionIntervalEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*sonetSectionIntervalEntry)[i] = assign_sonetSectionIntervalEntry(row->data);
        }
    }
}

void
sonet_mib_get_sonetSectionIntervalEntry(GNetSnmp *s, sonet_mib_sonetSectionIntervalEntry_t **sonetSectionIntervalEntry, gint32 ifIndex, gint32 sonetSectionIntervalNumber, gint64 mask)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, sonetSectionIntervalEntry_oid, sizeof(sonetSectionIntervalEntry_oid));
    len = pack_sonetSectionIntervalEntry(base, ifIndex, sonetSectionIntervalNumber);
    if (len < 0) {
        g_warning("%s: invalid index values", "sonetSectionIntervalEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *sonetSectionIntervalEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 12, sonetSectionIntervalEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *sonetSectionIntervalEntry = assign_sonetSectionIntervalEntry(out);
    }
}

void
sonet_mib_free_sonetSectionIntervalEntry(sonet_mib_sonetSectionIntervalEntry_t *sonetSectionIntervalEntry)
{
    GList *vbl;
    char *p;

    if (sonetSectionIntervalEntry) {
        p = (char *) sonetSectionIntervalEntry + sizeof(sonet_mib_sonetSectionIntervalEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(sonetSectionIntervalEntry);
    }
}

void
sonet_mib_free_sonetSectionIntervalTable(sonet_mib_sonetSectionIntervalEntry_t **sonetSectionIntervalEntry)
{
    int i;

    if (sonetSectionIntervalEntry) {
        for (i = 0; sonetSectionIntervalEntry[i]; i++) {
            sonet_mib_free_sonetSectionIntervalEntry(sonetSectionIntervalEntry[i]);
        }
        g_free(sonetSectionIntervalEntry);
    }
}


