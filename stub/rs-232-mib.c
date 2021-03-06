/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli RS-232-MIB
 *
 * Derived from RS-232-MIB:
 *   The MIB module for RS-232-like hardware devices.
 *
 * Revision 1994-05-26 17:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#include "rs-232-mib.h"

GNetSnmpEnum const rs_232_mib_enums_rs232PortType[] = {
    { RS_232_MIB_RS232PORTTYPE_OTHER, "other" },
    { RS_232_MIB_RS232PORTTYPE_RS232, "rs232" },
    { RS_232_MIB_RS232PORTTYPE_RS422, "rs422" },
    { RS_232_MIB_RS232PORTTYPE_RS423, "rs423" },
    { RS_232_MIB_RS232PORTTYPE_V35,   "v35" },
    { RS_232_MIB_RS232PORTTYPE_X21,   "x21" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232PortInFlowType[] = {
    { RS_232_MIB_RS232PORTINFLOWTYPE_NONE,   "none" },
    { RS_232_MIB_RS232PORTINFLOWTYPE_CTSRTS, "ctsRts" },
    { RS_232_MIB_RS232PORTINFLOWTYPE_DSRDTR, "dsrDtr" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232PortOutFlowType[] = {
    { RS_232_MIB_RS232PORTOUTFLOWTYPE_NONE,   "none" },
    { RS_232_MIB_RS232PORTOUTFLOWTYPE_CTSRTS, "ctsRts" },
    { RS_232_MIB_RS232PORTOUTFLOWTYPE_DSRDTR, "dsrDtr" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232AsyncPortStopBits[] = {
    { RS_232_MIB_RS232ASYNCPORTSTOPBITS_ONE,        "one" },
    { RS_232_MIB_RS232ASYNCPORTSTOPBITS_TWO,        "two" },
    { RS_232_MIB_RS232ASYNCPORTSTOPBITS_ONEANDHALF, "oneAndHalf" },
    { RS_232_MIB_RS232ASYNCPORTSTOPBITS_DYNAMIC,    "dynamic" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232AsyncPortParity[] = {
    { RS_232_MIB_RS232ASYNCPORTPARITY_NONE,  "none" },
    { RS_232_MIB_RS232ASYNCPORTPARITY_ODD,   "odd" },
    { RS_232_MIB_RS232ASYNCPORTPARITY_EVEN,  "even" },
    { RS_232_MIB_RS232ASYNCPORTPARITY_MARK,  "mark" },
    { RS_232_MIB_RS232ASYNCPORTPARITY_SPACE, "space" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232AsyncPortAutobaud[] = {
    { RS_232_MIB_RS232ASYNCPORTAUTOBAUD_ENABLED,  "enabled" },
    { RS_232_MIB_RS232ASYNCPORTAUTOBAUD_DISABLED, "disabled" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232SyncPortClockSource[] = {
    { RS_232_MIB_RS232SYNCPORTCLOCKSOURCE_INTERNAL, "internal" },
    { RS_232_MIB_RS232SYNCPORTCLOCKSOURCE_EXTERNAL, "external" },
    { RS_232_MIB_RS232SYNCPORTCLOCKSOURCE_SPLIT,    "split" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232SyncPortRole[] = {
    { RS_232_MIB_RS232SYNCPORTROLE_DTE, "dte" },
    { RS_232_MIB_RS232SYNCPORTROLE_DCE, "dce" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232SyncPortEncoding[] = {
    { RS_232_MIB_RS232SYNCPORTENCODING_NRZ,  "nrz" },
    { RS_232_MIB_RS232SYNCPORTENCODING_NRZI, "nrzi" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232SyncPortRTSControl[] = {
    { RS_232_MIB_RS232SYNCPORTRTSCONTROL_CONTROLLED, "controlled" },
    { RS_232_MIB_RS232SYNCPORTRTSCONTROL_CONSTANT,   "constant" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232SyncPortMode[] = {
    { RS_232_MIB_RS232SYNCPORTMODE_FDX,             "fdx" },
    { RS_232_MIB_RS232SYNCPORTMODE_HDX,             "hdx" },
    { RS_232_MIB_RS232SYNCPORTMODE_SIMPLEX_RECEIVE, "simplex-receive" },
    { RS_232_MIB_RS232SYNCPORTMODE_SIMPLEX_SEND,    "simplex-send" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232SyncPortIdlePattern[] = {
    { RS_232_MIB_RS232SYNCPORTIDLEPATTERN_MARK,  "mark" },
    { RS_232_MIB_RS232SYNCPORTIDLEPATTERN_SPACE, "space" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232InSigName[] = {
    { RS_232_MIB_RS232INSIGNAME_RTS,  "rts" },
    { RS_232_MIB_RS232INSIGNAME_CTS,  "cts" },
    { RS_232_MIB_RS232INSIGNAME_DSR,  "dsr" },
    { RS_232_MIB_RS232INSIGNAME_DTR,  "dtr" },
    { RS_232_MIB_RS232INSIGNAME_RI,   "ri" },
    { RS_232_MIB_RS232INSIGNAME_DCD,  "dcd" },
    { RS_232_MIB_RS232INSIGNAME_SQ,   "sq" },
    { RS_232_MIB_RS232INSIGNAME_SRS,  "srs" },
    { RS_232_MIB_RS232INSIGNAME_SRTS, "srts" },
    { RS_232_MIB_RS232INSIGNAME_SCTS, "scts" },
    { RS_232_MIB_RS232INSIGNAME_SDCD, "sdcd" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232InSigState[] = {
    { RS_232_MIB_RS232INSIGSTATE_NONE, "none" },
    { RS_232_MIB_RS232INSIGSTATE_ON,   "on" },
    { RS_232_MIB_RS232INSIGSTATE_OFF,  "off" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232OutSigName[] = {
    { RS_232_MIB_RS232OUTSIGNAME_RTS,  "rts" },
    { RS_232_MIB_RS232OUTSIGNAME_CTS,  "cts" },
    { RS_232_MIB_RS232OUTSIGNAME_DSR,  "dsr" },
    { RS_232_MIB_RS232OUTSIGNAME_DTR,  "dtr" },
    { RS_232_MIB_RS232OUTSIGNAME_RI,   "ri" },
    { RS_232_MIB_RS232OUTSIGNAME_DCD,  "dcd" },
    { RS_232_MIB_RS232OUTSIGNAME_SQ,   "sq" },
    { RS_232_MIB_RS232OUTSIGNAME_SRS,  "srs" },
    { RS_232_MIB_RS232OUTSIGNAME_SRTS, "srts" },
    { RS_232_MIB_RS232OUTSIGNAME_SCTS, "scts" },
    { RS_232_MIB_RS232OUTSIGNAME_SDCD, "sdcd" },
    { 0, NULL }
};

GNetSnmpEnum const rs_232_mib_enums_rs232OutSigState[] = {
    { RS_232_MIB_RS232OUTSIGSTATE_NONE, "none" },
    { RS_232_MIB_RS232OUTSIGSTATE_ON,   "on" },
    { RS_232_MIB_RS232OUTSIGSTATE_OFF,  "off" },
    { 0, NULL }
};


static gint32 rs232AsyncPortBits_constraints[] = {5L, 8L, 0, 0};


static guint32 const rs232_oid[] = {1, 3, 6, 1, 2, 1, 10, 33};

static GNetSnmpAttribute rs232_attr[] = {
    { 1, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232NUMBER, "rs232Number",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232_t, rs232Number),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const rs232PortEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 33, 2, 1};

static GNetSnmpAttribute rs232PortEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232PORTTYPE, "rs232PortType",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232PortEntry_t, rs232PortType),
      0,
      0 },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232PORTINSIGNUMBER, "rs232PortInSigNumber",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232PortEntry_t, rs232PortInSigNumber),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232PORTOUTSIGNUMBER, "rs232PortOutSigNumber",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232PortEntry_t, rs232PortOutSigNumber),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232PORTINSPEED, "rs232PortInSpeed",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232PortEntry_t, rs232PortInSpeed),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232PORTOUTSPEED, "rs232PortOutSpeed",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232PortEntry_t, rs232PortOutSpeed),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 7, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232PORTINFLOWTYPE, "rs232PortInFlowType",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232PortEntry_t, rs232PortInFlowType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232PORTOUTFLOWTYPE, "rs232PortOutFlowType",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232PortEntry_t, rs232PortOutFlowType),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const rs232AsyncPortEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 33, 3, 1};

static GNetSnmpAttribute rs232AsyncPortEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232ASYNCPORTBITS, "rs232AsyncPortBits",
       rs232AsyncPortBits_constraints,
      G_STRUCT_OFFSET(rs_232_mib_rs232AsyncPortEntry_t, rs232AsyncPortBits),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232ASYNCPORTSTOPBITS, "rs232AsyncPortStopBits",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232AsyncPortEntry_t, rs232AsyncPortStopBits),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 4, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232ASYNCPORTPARITY, "rs232AsyncPortParity",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232AsyncPortEntry_t, rs232AsyncPortParity),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 5, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232ASYNCPORTAUTOBAUD, "rs232AsyncPortAutobaud",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232AsyncPortEntry_t, rs232AsyncPortAutobaud),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232ASYNCPORTPARITYERRS, "rs232AsyncPortParityErrs",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232AsyncPortEntry_t, rs232AsyncPortParityErrs),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232ASYNCPORTFRAMINGERRS, "rs232AsyncPortFramingErrs",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232AsyncPortEntry_t, rs232AsyncPortFramingErrs),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232ASYNCPORTOVERRUNERRS, "rs232AsyncPortOverrunErrs",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232AsyncPortEntry_t, rs232AsyncPortOverrunErrs),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const rs232SyncPortEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 33, 4, 1};

static GNetSnmpAttribute rs232SyncPortEntry_attr[] = {
    { 2, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTCLOCKSOURCE, "rs232SyncPortClockSource",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortClockSource),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 3, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232SYNCPORTFRAMECHECKERRS, "rs232SyncPortFrameCheckErrs",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortFrameCheckErrs),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232SYNCPORTTRANSMITUNDERRUNERRS, "rs232SyncPortTransmitUnderrunErrs",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortTransmitUnderrunErrs),
      0,
      0 },
    { 5, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232SYNCPORTRECEIVEOVERRUNERRS, "rs232SyncPortReceiveOverrunErrs",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortReceiveOverrunErrs),
      0,
      0 },
    { 6, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232SYNCPORTINTERRUPTEDFRAMES, "rs232SyncPortInterruptedFrames",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortInterruptedFrames),
      0,
      0 },
    { 7, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232SYNCPORTABORTEDFRAMES, "rs232SyncPortAbortedFrames",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortAbortedFrames),
      0,
      0 },
    { 8, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTROLE, "rs232SyncPortRole",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortRole),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 9, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTENCODING, "rs232SyncPortEncoding",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortEncoding),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 10, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTRTSCONTROL, "rs232SyncPortRTSControl",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortRTSControl),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 11, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTRTSCTSDELAY, "rs232SyncPortRTSCTSDelay",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortRTSCTSDelay),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 12, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTMODE, "rs232SyncPortMode",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortMode),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 13, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTIDLEPATTERN, "rs232SyncPortIdlePattern",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortIdlePattern),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 14, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232SYNCPORTMINFLAGS, "rs232SyncPortMinFlags",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232SyncPortEntry_t, rs232SyncPortMinFlags),
      0,
      GSNMP_ATTR_FLAG_WRITABLE },
    { 0, 0, 0, NULL }
};

static guint32 const rs232InSigEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 33, 5, 1};

static GNetSnmpAttribute rs232InSigEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232INSIGSTATE, "rs232InSigState",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232InSigEntry_t, rs232InSigState),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232INSIGCHANGES, "rs232InSigChanges",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232InSigEntry_t, rs232InSigChanges),
      0,
      0 },
    { 0, 0, 0, NULL }
};

static guint32 const rs232OutSigEntry_oid[] = {1, 3, 6, 1, 2, 1, 10, 33, 6, 1};

static GNetSnmpAttribute rs232OutSigEntry_attr[] = {
    { 3, GNET_SNMP_VARBIND_TYPE_INTEGER32,
      RS_232_MIB_RS232OUTSIGSTATE, "rs232OutSigState",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232OutSigEntry_t, rs232OutSigState),
      0,
      0 },
    { 4, GNET_SNMP_VARBIND_TYPE_COUNTER32,
      RS_232_MIB_RS232OUTSIGCHANGES, "rs232OutSigChanges",
       NULL,
      G_STRUCT_OFFSET(rs_232_mib_rs232OutSigEntry_t, rs232OutSigChanges),
      0,
      0 },
    { 0, 0, 0, NULL }
};


rs_232_mib_rs232_t *
rs_232_mib_new_rs232()
{
    rs_232_mib_rs232_t *rs232;

    rs232 = (rs_232_mib_rs232_t *) g_malloc0(sizeof(rs_232_mib_rs232_t) + sizeof(gpointer));
    return rs232;
}

static inline rs_232_mib_rs232_t *
assign_rs232(GList *vbl)
{
    rs_232_mib_rs232_t *rs232;
    char *p;

    rs232 = rs_232_mib_new_rs232();
    p = (char *) rs232 + sizeof(rs_232_mib_rs232_t);
    * (GList **) p = vbl;

    gnet_snmp_attr_assign(vbl, rs232_oid, G_N_ELEMENTS(rs232_oid),
                      rs232_attr, rs232);

    return rs232;
}

void
rs_232_mib_get_rs232(GNetSnmp *s, rs_232_mib_rs232_t **rs232, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    static const guint32 _base[] = {1, 3, 6, 1, 2, 1, 10, 33, 0};
    guint32 base[128];

    *rs232 = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 9, 8, rs232_attr, mask);

    out = gnet_snmp_sync_getnext(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if ((error && *error) || s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *rs232 = assign_rs232(out);
    }
}

void
rs_232_mib_free_rs232(rs_232_mib_rs232_t *rs232)
{
    GList *vbl;
    char *p;

    if (rs232) {
        p = (char *) rs232 + sizeof(rs_232_mib_rs232_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(rs232);
    }
}

rs_232_mib_rs232PortEntry_t *
rs_232_mib_new_rs232PortEntry()
{
    rs_232_mib_rs232PortEntry_t *rs232PortEntry;

    rs232PortEntry = (rs_232_mib_rs232PortEntry_t *) g_malloc0(sizeof(rs_232_mib_rs232PortEntry_t) + sizeof(gpointer));
    return rs232PortEntry;
}

static inline int
unpack_rs232PortEntry(GNetSnmpVarBind *vb, rs_232_mib_rs232PortEntry_t *rs232PortEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    rs232PortEntry->rs232PortIndex = vb->oid[idx++];
    if ((rs232PortEntry->rs232PortIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_rs232PortEntry(guint32 *base, gint32 rs232PortIndex)
{
    guint8 idx = 11;

    base[idx++] = rs232PortIndex;
    return idx;
}

static inline rs_232_mib_rs232PortEntry_t *
assign_rs232PortEntry(GList *vbl)
{
    rs_232_mib_rs232PortEntry_t *rs232PortEntry;
    char *p;

    rs232PortEntry = rs_232_mib_new_rs232PortEntry();
    p = (char *) rs232PortEntry + sizeof(rs_232_mib_rs232PortEntry_t);
    * (GList **) p = vbl;

    if (unpack_rs232PortEntry((GNetSnmpVarBind *) vbl->data, rs232PortEntry) < 0) {
        g_warning("%s: invalid instance identifier", "rs232PortEntry");
        g_free(rs232PortEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, rs232PortEntry_oid, G_N_ELEMENTS(rs232PortEntry_oid),
                      rs232PortEntry_attr, rs232PortEntry);

    return rs232PortEntry;
}

void
rs_232_mib_get_rs232PortTable(GNetSnmp *s, rs_232_mib_rs232PortEntry_t ***rs232PortEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 33, 2, 1, 0};
    guint32 base[128];

    *rs232PortEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, rs232PortEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *rs232PortEntry = (rs_232_mib_rs232PortEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rs_232_mib_rs232PortEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*rs232PortEntry)[i] = assign_rs232PortEntry(row->data);
        }
    }
}

void
rs_232_mib_get_rs232PortEntry(GNetSnmp *s, rs_232_mib_rs232PortEntry_t **rs232PortEntry, gint32 rs232PortIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232PortEntry_oid, sizeof(rs232PortEntry_oid));
    len = pack_rs232PortEntry(base, rs232PortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232PortEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *rs232PortEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, rs232PortEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *rs232PortEntry = assign_rs232PortEntry(out);
    }
}

void
rs_232_mib_set_rs232PortEntry(GNetSnmp *s, rs_232_mib_rs232PortEntry_t *rs232PortEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232PortEntry_oid, sizeof(rs232PortEntry_oid));
    len = pack_rs232PortEntry(base, rs232PortEntry->rs232PortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232PortEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, rs232PortEntry_attr, mask, rs232PortEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
rs_232_mib_free_rs232PortEntry(rs_232_mib_rs232PortEntry_t *rs232PortEntry)
{
    GList *vbl;
    char *p;

    if (rs232PortEntry) {
        p = (char *) rs232PortEntry + sizeof(rs_232_mib_rs232PortEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(rs232PortEntry);
    }
}

void
rs_232_mib_free_rs232PortTable(rs_232_mib_rs232PortEntry_t **rs232PortEntry)
{
    int i;

    if (rs232PortEntry) {
        for (i = 0; rs232PortEntry[i]; i++) {
            rs_232_mib_free_rs232PortEntry(rs232PortEntry[i]);
        }
        g_free(rs232PortEntry);
    }
}

rs_232_mib_rs232AsyncPortEntry_t *
rs_232_mib_new_rs232AsyncPortEntry()
{
    rs_232_mib_rs232AsyncPortEntry_t *rs232AsyncPortEntry;

    rs232AsyncPortEntry = (rs_232_mib_rs232AsyncPortEntry_t *) g_malloc0(sizeof(rs_232_mib_rs232AsyncPortEntry_t) + sizeof(gpointer));
    return rs232AsyncPortEntry;
}

static inline int
unpack_rs232AsyncPortEntry(GNetSnmpVarBind *vb, rs_232_mib_rs232AsyncPortEntry_t *rs232AsyncPortEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    rs232AsyncPortEntry->rs232AsyncPortIndex = vb->oid[idx++];
    if ((rs232AsyncPortEntry->rs232AsyncPortIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_rs232AsyncPortEntry(guint32 *base, gint32 rs232AsyncPortIndex)
{
    guint8 idx = 11;

    base[idx++] = rs232AsyncPortIndex;
    return idx;
}

static inline rs_232_mib_rs232AsyncPortEntry_t *
assign_rs232AsyncPortEntry(GList *vbl)
{
    rs_232_mib_rs232AsyncPortEntry_t *rs232AsyncPortEntry;
    char *p;

    rs232AsyncPortEntry = rs_232_mib_new_rs232AsyncPortEntry();
    p = (char *) rs232AsyncPortEntry + sizeof(rs_232_mib_rs232AsyncPortEntry_t);
    * (GList **) p = vbl;

    if (unpack_rs232AsyncPortEntry((GNetSnmpVarBind *) vbl->data, rs232AsyncPortEntry) < 0) {
        g_warning("%s: invalid instance identifier", "rs232AsyncPortEntry");
        g_free(rs232AsyncPortEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, rs232AsyncPortEntry_oid, G_N_ELEMENTS(rs232AsyncPortEntry_oid),
                      rs232AsyncPortEntry_attr, rs232AsyncPortEntry);

    return rs232AsyncPortEntry;
}

void
rs_232_mib_get_rs232AsyncPortTable(GNetSnmp *s, rs_232_mib_rs232AsyncPortEntry_t ***rs232AsyncPortEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 33, 3, 1, 0};
    guint32 base[128];

    *rs232AsyncPortEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, rs232AsyncPortEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *rs232AsyncPortEntry = (rs_232_mib_rs232AsyncPortEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rs_232_mib_rs232AsyncPortEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*rs232AsyncPortEntry)[i] = assign_rs232AsyncPortEntry(row->data);
        }
    }
}

void
rs_232_mib_get_rs232AsyncPortEntry(GNetSnmp *s, rs_232_mib_rs232AsyncPortEntry_t **rs232AsyncPortEntry, gint32 rs232AsyncPortIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232AsyncPortEntry_oid, sizeof(rs232AsyncPortEntry_oid));
    len = pack_rs232AsyncPortEntry(base, rs232AsyncPortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232AsyncPortEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *rs232AsyncPortEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, rs232AsyncPortEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *rs232AsyncPortEntry = assign_rs232AsyncPortEntry(out);
    }
}

void
rs_232_mib_set_rs232AsyncPortEntry(GNetSnmp *s, rs_232_mib_rs232AsyncPortEntry_t *rs232AsyncPortEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232AsyncPortEntry_oid, sizeof(rs232AsyncPortEntry_oid));
    len = pack_rs232AsyncPortEntry(base, rs232AsyncPortEntry->rs232AsyncPortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232AsyncPortEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, rs232AsyncPortEntry_attr, mask, rs232AsyncPortEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
rs_232_mib_free_rs232AsyncPortEntry(rs_232_mib_rs232AsyncPortEntry_t *rs232AsyncPortEntry)
{
    GList *vbl;
    char *p;

    if (rs232AsyncPortEntry) {
        p = (char *) rs232AsyncPortEntry + sizeof(rs_232_mib_rs232AsyncPortEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(rs232AsyncPortEntry);
    }
}

void
rs_232_mib_free_rs232AsyncPortTable(rs_232_mib_rs232AsyncPortEntry_t **rs232AsyncPortEntry)
{
    int i;

    if (rs232AsyncPortEntry) {
        for (i = 0; rs232AsyncPortEntry[i]; i++) {
            rs_232_mib_free_rs232AsyncPortEntry(rs232AsyncPortEntry[i]);
        }
        g_free(rs232AsyncPortEntry);
    }
}

rs_232_mib_rs232SyncPortEntry_t *
rs_232_mib_new_rs232SyncPortEntry()
{
    rs_232_mib_rs232SyncPortEntry_t *rs232SyncPortEntry;

    rs232SyncPortEntry = (rs_232_mib_rs232SyncPortEntry_t *) g_malloc0(sizeof(rs_232_mib_rs232SyncPortEntry_t) + sizeof(gpointer));
    return rs232SyncPortEntry;
}

static inline int
unpack_rs232SyncPortEntry(GNetSnmpVarBind *vb, rs_232_mib_rs232SyncPortEntry_t *rs232SyncPortEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    rs232SyncPortEntry->rs232SyncPortIndex = vb->oid[idx++];
    if ((rs232SyncPortEntry->rs232SyncPortIndex < 1)) {
         return -1;
    }
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_rs232SyncPortEntry(guint32 *base, gint32 rs232SyncPortIndex)
{
    guint8 idx = 11;

    base[idx++] = rs232SyncPortIndex;
    return idx;
}

static inline rs_232_mib_rs232SyncPortEntry_t *
assign_rs232SyncPortEntry(GList *vbl)
{
    rs_232_mib_rs232SyncPortEntry_t *rs232SyncPortEntry;
    char *p;

    rs232SyncPortEntry = rs_232_mib_new_rs232SyncPortEntry();
    p = (char *) rs232SyncPortEntry + sizeof(rs_232_mib_rs232SyncPortEntry_t);
    * (GList **) p = vbl;

    if (unpack_rs232SyncPortEntry((GNetSnmpVarBind *) vbl->data, rs232SyncPortEntry) < 0) {
        g_warning("%s: invalid instance identifier", "rs232SyncPortEntry");
        g_free(rs232SyncPortEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, rs232SyncPortEntry_oid, G_N_ELEMENTS(rs232SyncPortEntry_oid),
                      rs232SyncPortEntry_attr, rs232SyncPortEntry);

    return rs232SyncPortEntry;
}

void
rs_232_mib_get_rs232SyncPortTable(GNetSnmp *s, rs_232_mib_rs232SyncPortEntry_t ***rs232SyncPortEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 33, 4, 1, 0};
    guint32 base[128];

    *rs232SyncPortEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, rs232SyncPortEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *rs232SyncPortEntry = (rs_232_mib_rs232SyncPortEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rs_232_mib_rs232SyncPortEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*rs232SyncPortEntry)[i] = assign_rs232SyncPortEntry(row->data);
        }
    }
}

void
rs_232_mib_get_rs232SyncPortEntry(GNetSnmp *s, rs_232_mib_rs232SyncPortEntry_t **rs232SyncPortEntry, gint32 rs232SyncPortIndex, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232SyncPortEntry_oid, sizeof(rs232SyncPortEntry_oid));
    len = pack_rs232SyncPortEntry(base, rs232SyncPortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232SyncPortEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *rs232SyncPortEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, rs232SyncPortEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *rs232SyncPortEntry = assign_rs232SyncPortEntry(out);
    }
}

void
rs_232_mib_set_rs232SyncPortEntry(GNetSnmp *s, rs_232_mib_rs232SyncPortEntry_t *rs232SyncPortEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232SyncPortEntry_oid, sizeof(rs232SyncPortEntry_oid));
    len = pack_rs232SyncPortEntry(base, rs232SyncPortEntry->rs232SyncPortIndex);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232SyncPortEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    gnet_snmp_attr_set(s, &in, base, len, 10, rs232SyncPortEntry_attr, mask, rs232SyncPortEntry);

    out = gnet_snmp_sync_set(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(out);
    }
}

void
rs_232_mib_free_rs232SyncPortEntry(rs_232_mib_rs232SyncPortEntry_t *rs232SyncPortEntry)
{
    GList *vbl;
    char *p;

    if (rs232SyncPortEntry) {
        p = (char *) rs232SyncPortEntry + sizeof(rs_232_mib_rs232SyncPortEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(rs232SyncPortEntry);
    }
}

void
rs_232_mib_free_rs232SyncPortTable(rs_232_mib_rs232SyncPortEntry_t **rs232SyncPortEntry)
{
    int i;

    if (rs232SyncPortEntry) {
        for (i = 0; rs232SyncPortEntry[i]; i++) {
            rs_232_mib_free_rs232SyncPortEntry(rs232SyncPortEntry[i]);
        }
        g_free(rs232SyncPortEntry);
    }
}

rs_232_mib_rs232InSigEntry_t *
rs_232_mib_new_rs232InSigEntry()
{
    rs_232_mib_rs232InSigEntry_t *rs232InSigEntry;

    rs232InSigEntry = (rs_232_mib_rs232InSigEntry_t *) g_malloc0(sizeof(rs_232_mib_rs232InSigEntry_t) + sizeof(gpointer));
    return rs232InSigEntry;
}

static inline int
unpack_rs232InSigEntry(GNetSnmpVarBind *vb, rs_232_mib_rs232InSigEntry_t *rs232InSigEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    rs232InSigEntry->rs232InSigPortIndex = vb->oid[idx++];
    if ((rs232InSigEntry->rs232InSigPortIndex < 1)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    rs232InSigEntry->rs232InSigName = vb->oid[idx++];
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_rs232InSigEntry(guint32 *base, gint32 rs232InSigPortIndex, gint32 rs232InSigName)
{
    guint8 idx = 11;

    base[idx++] = rs232InSigPortIndex;
    base[idx++] = rs232InSigName;
    return idx;
}

static inline rs_232_mib_rs232InSigEntry_t *
assign_rs232InSigEntry(GList *vbl)
{
    rs_232_mib_rs232InSigEntry_t *rs232InSigEntry;
    char *p;

    rs232InSigEntry = rs_232_mib_new_rs232InSigEntry();
    p = (char *) rs232InSigEntry + sizeof(rs_232_mib_rs232InSigEntry_t);
    * (GList **) p = vbl;

    if (unpack_rs232InSigEntry((GNetSnmpVarBind *) vbl->data, rs232InSigEntry) < 0) {
        g_warning("%s: invalid instance identifier", "rs232InSigEntry");
        g_free(rs232InSigEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, rs232InSigEntry_oid, G_N_ELEMENTS(rs232InSigEntry_oid),
                      rs232InSigEntry_attr, rs232InSigEntry);

    return rs232InSigEntry;
}

void
rs_232_mib_get_rs232InSigTable(GNetSnmp *s, rs_232_mib_rs232InSigEntry_t ***rs232InSigEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 33, 5, 1, 0};
    guint32 base[128];

    *rs232InSigEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, rs232InSigEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *rs232InSigEntry = (rs_232_mib_rs232InSigEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rs_232_mib_rs232InSigEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*rs232InSigEntry)[i] = assign_rs232InSigEntry(row->data);
        }
    }
}

void
rs_232_mib_get_rs232InSigEntry(GNetSnmp *s, rs_232_mib_rs232InSigEntry_t **rs232InSigEntry, gint32 rs232InSigPortIndex, gint32 rs232InSigName, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232InSigEntry_oid, sizeof(rs232InSigEntry_oid));
    len = pack_rs232InSigEntry(base, rs232InSigPortIndex, rs232InSigName);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232InSigEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *rs232InSigEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, rs232InSigEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *rs232InSigEntry = assign_rs232InSigEntry(out);
    }
}

void
rs_232_mib_free_rs232InSigEntry(rs_232_mib_rs232InSigEntry_t *rs232InSigEntry)
{
    GList *vbl;
    char *p;

    if (rs232InSigEntry) {
        p = (char *) rs232InSigEntry + sizeof(rs_232_mib_rs232InSigEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(rs232InSigEntry);
    }
}

void
rs_232_mib_free_rs232InSigTable(rs_232_mib_rs232InSigEntry_t **rs232InSigEntry)
{
    int i;

    if (rs232InSigEntry) {
        for (i = 0; rs232InSigEntry[i]; i++) {
            rs_232_mib_free_rs232InSigEntry(rs232InSigEntry[i]);
        }
        g_free(rs232InSigEntry);
    }
}

rs_232_mib_rs232OutSigEntry_t *
rs_232_mib_new_rs232OutSigEntry()
{
    rs_232_mib_rs232OutSigEntry_t *rs232OutSigEntry;

    rs232OutSigEntry = (rs_232_mib_rs232OutSigEntry_t *) g_malloc0(sizeof(rs_232_mib_rs232OutSigEntry_t) + sizeof(gpointer));
    return rs232OutSigEntry;
}

static inline int
unpack_rs232OutSigEntry(GNetSnmpVarBind *vb, rs_232_mib_rs232OutSigEntry_t *rs232OutSigEntry)
{
    guint8 idx = 11;

    if (vb->oid_len < idx) return -1;
    rs232OutSigEntry->rs232OutSigPortIndex = vb->oid[idx++];
    if ((rs232OutSigEntry->rs232OutSigPortIndex < 1)) {
         return -1;
    }
    if (vb->oid_len < idx) return -1;
    rs232OutSigEntry->rs232OutSigName = vb->oid[idx++];
    if (vb->oid_len > idx) return -1;
    return 0;
}

static inline gint8
pack_rs232OutSigEntry(guint32 *base, gint32 rs232OutSigPortIndex, gint32 rs232OutSigName)
{
    guint8 idx = 11;

    base[idx++] = rs232OutSigPortIndex;
    base[idx++] = rs232OutSigName;
    return idx;
}

static inline rs_232_mib_rs232OutSigEntry_t *
assign_rs232OutSigEntry(GList *vbl)
{
    rs_232_mib_rs232OutSigEntry_t *rs232OutSigEntry;
    char *p;

    rs232OutSigEntry = rs_232_mib_new_rs232OutSigEntry();
    p = (char *) rs232OutSigEntry + sizeof(rs_232_mib_rs232OutSigEntry_t);
    * (GList **) p = vbl;

    if (unpack_rs232OutSigEntry((GNetSnmpVarBind *) vbl->data, rs232OutSigEntry) < 0) {
        g_warning("%s: invalid instance identifier", "rs232OutSigEntry");
        g_free(rs232OutSigEntry);
        return NULL;
    }

    gnet_snmp_attr_assign(vbl, rs232OutSigEntry_oid, G_N_ELEMENTS(rs232OutSigEntry_oid),
                      rs232OutSigEntry_attr, rs232OutSigEntry);

    return rs232OutSigEntry;
}

void
rs_232_mib_get_rs232OutSigTable(GNetSnmp *s, rs_232_mib_rs232OutSigEntry_t ***rs232OutSigEntry, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    GList *row;
    int i;
    static guint32 const _base[] = {1, 3, 6, 1, 2, 1, 10, 33, 6, 1, 0};
    guint32 base[128];

    *rs232OutSigEntry = NULL;
    memcpy(base, _base, sizeof(_base));

    gnet_snmp_attr_get(s, &in, base, 11, 10, rs232OutSigEntry_attr, mask);

    out = gnet_snmp_sync_table(s, in, error);
    /* gnet_snmp_varbind_list_free(in); */

    if (out) {
        *rs232OutSigEntry = (rs_232_mib_rs232OutSigEntry_t **) g_malloc0((g_list_length(out) + 1) * sizeof(rs_232_mib_rs232OutSigEntry_t *));
        for (row = out, i = 0; row; row = g_list_next(row), i++) {
            (*rs232OutSigEntry)[i] = assign_rs232OutSigEntry(row->data);
        }
    }
}

void
rs_232_mib_get_rs232OutSigEntry(GNetSnmp *s, rs_232_mib_rs232OutSigEntry_t **rs232OutSigEntry, gint32 rs232OutSigPortIndex, gint32 rs232OutSigName, gint64 mask, GError **error)
{
    GList *in = NULL, *out = NULL;
    guint32 base[128];
    gint8 len;

    memcpy(base, rs232OutSigEntry_oid, sizeof(rs232OutSigEntry_oid));
    len = pack_rs232OutSigEntry(base, rs232OutSigPortIndex, rs232OutSigName);
    if (len < 0) {
        g_warning("%s: invalid index values", "rs232OutSigEntry");
        s->error_status = GNET_SNMP_PDU_ERR_INTERNAL;
        return;
    }

    *rs232OutSigEntry = NULL;

    gnet_snmp_attr_get(s, &in, base, len, 10, rs232OutSigEntry_attr, mask);

    out = gnet_snmp_sync_get(s, in, error);
    g_list_foreach(in, (GFunc) gnet_snmp_varbind_delete, NULL);
    g_list_free(in);
    if (out) {
        if (s->error_status != GNET_SNMP_PDU_ERR_NOERROR) {
            g_list_foreach(out, (GFunc) gnet_snmp_varbind_delete, NULL);
            g_list_free(out);
            return;
        }
        *rs232OutSigEntry = assign_rs232OutSigEntry(out);
    }
}

void
rs_232_mib_free_rs232OutSigEntry(rs_232_mib_rs232OutSigEntry_t *rs232OutSigEntry)
{
    GList *vbl;
    char *p;

    if (rs232OutSigEntry) {
        p = (char *) rs232OutSigEntry + sizeof(rs_232_mib_rs232OutSigEntry_t);
        vbl = * (GList **) p;
        g_list_foreach(vbl, (GFunc) gnet_snmp_varbind_delete, NULL);
        g_list_free(vbl);
        g_free(rs232OutSigEntry);
    }
}

void
rs_232_mib_free_rs232OutSigTable(rs_232_mib_rs232OutSigEntry_t **rs232OutSigEntry)
{
    int i;

    if (rs232OutSigEntry) {
        for (i = 0; rs232OutSigEntry[i]; i++) {
            rs_232_mib_free_rs232OutSigEntry(rs232OutSigEntry[i]);
        }
        g_free(rs232OutSigEntry);
    }
}


