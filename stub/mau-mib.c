/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from MAU-MIB:
 *   Management information for 802.3 MAUs.
 *   
 *   The following reference is used throughout
 *   this MIB module:
 *   
 *   [IEEE 802.3 Std] refers to
 *      IEEE Std 802.3, 1998 Edition: 'Information
 *      technology - Telecommunications and
 *      information exchange between systems -
 *      Local and metropolitan area networks -
 *      Specific requirements - Part 3: Carrier
 *      sense multiple access with collision
 *      detection (CSMA/CD) access method and
 *      physical layer specifications',
 *      September 1998.
 *   
 *   Of particular interest is Clause 30, '10Mb/s,
 *   100Mb/s and 1000Mb/s Management'.
 *
 * Revision 1999-08-24 04:00:
 *   This version published as RFC 2668. Updated
 *   to include support for 1000 Mb/sec
 *   MAUs and flow control negotiation.
 *
 * Revision 1997-10-31 00:00:
 *   This version published as RFC 2239.
 *
 * Revision 1993-09-30 00:00:
 *   Initial version, published as RFC 1515.
 *
 * $Id$
 */

#include "mau-mib.h"

stls_enum_t const mau_mib_enums_rpMauStatus[] = {
    { MAU_MIB_RPMAUSTATUS_OTHER,	"other" },
    { MAU_MIB_RPMAUSTATUS_UNKNOWN,	"unknown" },
    { MAU_MIB_RPMAUSTATUS_OPERATIONAL,	"operational" },
    { MAU_MIB_RPMAUSTATUS_STANDBY,	"standby" },
    { MAU_MIB_RPMAUSTATUS_SHUTDOWN,	"shutdown" },
    { MAU_MIB_RPMAUSTATUS_RESET,	"reset" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_rpMauMediaAvailable[] = {
    { MAU_MIB_RPMAUMEDIAAVAILABLE_OTHER,	"other" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_UNKNOWN,	"unknown" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_AVAILABLE,	"available" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_NOTAVAILABLE,	"notAvailable" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTEFAULT,	"remoteFault" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_INVALIDSIGNAL,	"invalidSignal" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTEJABBER,	"remoteJabber" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTELINKLOSS,	"remoteLinkLoss" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_REMOTETEST,	"remoteTest" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_OFFLINE,	"offline" },
    { MAU_MIB_RPMAUMEDIAAVAILABLE_AUTONEGERROR,	"autoNegError" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_rpMauJabberState[] = {
    { MAU_MIB_RPMAUJABBERSTATE_OTHER,	"other" },
    { MAU_MIB_RPMAUJABBERSTATE_UNKNOWN,	"unknown" },
    { MAU_MIB_RPMAUJABBERSTATE_NOJABBER,	"noJabber" },
    { MAU_MIB_RPMAUJABBERSTATE_JABBERING,	"jabbering" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_rpJackType[] = {
    { MAU_MIB_RPJACKTYPE_OTHER,	"other" },
    { MAU_MIB_RPJACKTYPE_RJ45,	"rj45" },
    { MAU_MIB_RPJACKTYPE_RJ45S,	"rj45S" },
    { MAU_MIB_RPJACKTYPE_DB9,	"db9" },
    { MAU_MIB_RPJACKTYPE_BNC,	"bnc" },
    { MAU_MIB_RPJACKTYPE_FAUI,	"fAUI" },
    { MAU_MIB_RPJACKTYPE_MAUI,	"mAUI" },
    { MAU_MIB_RPJACKTYPE_FIBERSC,	"fiberSC" },
    { MAU_MIB_RPJACKTYPE_FIBERMIC,	"fiberMIC" },
    { MAU_MIB_RPJACKTYPE_FIBERST,	"fiberST" },
    { MAU_MIB_RPJACKTYPE_TELCO,	"telco" },
    { MAU_MIB_RPJACKTYPE_MTRJ,	"mtrj" },
    { MAU_MIB_RPJACKTYPE_HSSDC,	"hssdc" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauStatus[] = {
    { MAU_MIB_IFMAUSTATUS_OTHER,	"other" },
    { MAU_MIB_IFMAUSTATUS_UNKNOWN,	"unknown" },
    { MAU_MIB_IFMAUSTATUS_OPERATIONAL,	"operational" },
    { MAU_MIB_IFMAUSTATUS_STANDBY,	"standby" },
    { MAU_MIB_IFMAUSTATUS_SHUTDOWN,	"shutdown" },
    { MAU_MIB_IFMAUSTATUS_RESET,	"reset" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauMediaAvailable[] = {
    { MAU_MIB_IFMAUMEDIAAVAILABLE_OTHER,	"other" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_UNKNOWN,	"unknown" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_AVAILABLE,	"available" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_NOTAVAILABLE,	"notAvailable" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTEFAULT,	"remoteFault" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_INVALIDSIGNAL,	"invalidSignal" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTEJABBER,	"remoteJabber" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTELINKLOSS,	"remoteLinkLoss" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_REMOTETEST,	"remoteTest" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_OFFLINE,	"offline" },
    { MAU_MIB_IFMAUMEDIAAVAILABLE_AUTONEGERROR,	"autoNegError" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauJabberState[] = {
    { MAU_MIB_IFMAUJABBERSTATE_OTHER,	"other" },
    { MAU_MIB_IFMAUJABBERSTATE_UNKNOWN,	"unknown" },
    { MAU_MIB_IFMAUJABBERSTATE_NOJABBER,	"noJabber" },
    { MAU_MIB_IFMAUJABBERSTATE_JABBERING,	"jabbering" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauAutoNegSupported[] = {
    { MAU_MIB_IFMAUAUTONEGSUPPORTED_TRUE,	"true" },
    { MAU_MIB_IFMAUAUTONEGSUPPORTED_FALSE,	"false" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifJackType[] = {
    { MAU_MIB_IFJACKTYPE_OTHER,	"other" },
    { MAU_MIB_IFJACKTYPE_RJ45,	"rj45" },
    { MAU_MIB_IFJACKTYPE_RJ45S,	"rj45S" },
    { MAU_MIB_IFJACKTYPE_DB9,	"db9" },
    { MAU_MIB_IFJACKTYPE_BNC,	"bnc" },
    { MAU_MIB_IFJACKTYPE_FAUI,	"fAUI" },
    { MAU_MIB_IFJACKTYPE_MAUI,	"mAUI" },
    { MAU_MIB_IFJACKTYPE_FIBERSC,	"fiberSC" },
    { MAU_MIB_IFJACKTYPE_FIBERMIC,	"fiberMIC" },
    { MAU_MIB_IFJACKTYPE_FIBERST,	"fiberST" },
    { MAU_MIB_IFJACKTYPE_TELCO,	"telco" },
    { MAU_MIB_IFJACKTYPE_MTRJ,	"mtrj" },
    { MAU_MIB_IFJACKTYPE_HSSDC,	"hssdc" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_broadMauXmtRcvSplitType[] = {
    { MAU_MIB_BROADMAUXMTRCVSPLITTYPE_OTHER,	"other" },
    { MAU_MIB_BROADMAUXMTRCVSPLITTYPE_SINGLE,	"single" },
    { MAU_MIB_BROADMAUXMTRCVSPLITTYPE_DUAL,	"dual" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauAutoNegAdminStatus[] = {
    { MAU_MIB_IFMAUAUTONEGADMINSTATUS_ENABLED,	"enabled" },
    { MAU_MIB_IFMAUAUTONEGADMINSTATUS_DISABLED,	"disabled" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauAutoNegRemoteSignaling[] = {
    { MAU_MIB_IFMAUAUTONEGREMOTESIGNALING_DETECTED,	"detected" },
    { MAU_MIB_IFMAUAUTONEGREMOTESIGNALING_NOTDETECTED,	"notdetected" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauAutoNegConfig[] = {
    { MAU_MIB_IFMAUAUTONEGCONFIG_OTHER,	"other" },
    { MAU_MIB_IFMAUAUTONEGCONFIG_CONFIGURING,	"configuring" },
    { MAU_MIB_IFMAUAUTONEGCONFIG_COMPLETE,	"complete" },
    { MAU_MIB_IFMAUAUTONEGCONFIG_DISABLED,	"disabled" },
    { MAU_MIB_IFMAUAUTONEGCONFIG_PARALLELDETECTFAIL,	"parallelDetectFail" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauAutoNegRestart[] = {
    { MAU_MIB_IFMAUAUTONEGRESTART_RESTART,	"restart" },
    { MAU_MIB_IFMAUAUTONEGRESTART_NORESTART,	"norestart" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauAutoNegRemoteFaultAdvertised[] = {
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_NOERROR,	"noError" },
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_OFFLINE,	"offline" },
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_LINKFAILURE,	"linkFailure" },
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTADVERTISED_AUTONEGERROR,	"autoNegError" },
    { 0, NULL }
};

stls_enum_t const mau_mib_enums_ifMauAutoNegRemoteFaultReceived[] = {
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_NOERROR,	"noError" },
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_OFFLINE,	"offline" },
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_LINKFAILURE,	"linkFailure" },
    { MAU_MIB_IFMAUAUTONEGREMOTEFAULTRECEIVED_AUTONEGERROR,	"autoNegError" },
    { 0, NULL }
};


static guint32 const dot3MauTypeAUI[]
	= { MAU_MIB_DOT3MAUTYPEAUI };
static guint32 const dot3MauType10Base5[]
	= { MAU_MIB_DOT3MAUTYPE10BASE5 };
static guint32 const dot3MauTypeFoirl[]
	= { MAU_MIB_DOT3MAUTYPEFOIRL };
static guint32 const dot3MauType10Base2[]
	= { MAU_MIB_DOT3MAUTYPE10BASE2 };
static guint32 const dot3MauType10BaseT[]
	= { MAU_MIB_DOT3MAUTYPE10BASET };
static guint32 const dot3MauType10BaseFP[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFP };
static guint32 const dot3MauType10BaseFB[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFB };
static guint32 const dot3MauType10BaseFL[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFL };
static guint32 const dot3MauType10Broad36[]
	= { MAU_MIB_DOT3MAUTYPE10BROAD36 };
static guint32 const dot3MauType10BaseTHD[]
	= { MAU_MIB_DOT3MAUTYPE10BASETHD };
static guint32 const dot3MauType10BaseTFD[]
	= { MAU_MIB_DOT3MAUTYPE10BASETFD };
static guint32 const dot3MauType10BaseFLHD[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFLHD };
static guint32 const dot3MauType10BaseFLFD[]
	= { MAU_MIB_DOT3MAUTYPE10BASEFLFD };
static guint32 const dot3MauType100BaseT4[]
	= { MAU_MIB_DOT3MAUTYPE100BASET4 };
static guint32 const dot3MauType100BaseTXHD[]
	= { MAU_MIB_DOT3MAUTYPE100BASETXHD };
static guint32 const dot3MauType100BaseTXFD[]
	= { MAU_MIB_DOT3MAUTYPE100BASETXFD };
static guint32 const dot3MauType100BaseFXHD[]
	= { MAU_MIB_DOT3MAUTYPE100BASEFXHD };
static guint32 const dot3MauType100BaseFXFD[]
	= { MAU_MIB_DOT3MAUTYPE100BASEFXFD };
static guint32 const dot3MauType100BaseT2HD[]
	= { MAU_MIB_DOT3MAUTYPE100BASET2HD };
static guint32 const dot3MauType100BaseT2FD[]
	= { MAU_MIB_DOT3MAUTYPE100BASET2FD };
static guint32 const dot3MauType1000BaseXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASEXHD };
static guint32 const dot3MauType1000BaseXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASEXFD };
static guint32 const dot3MauType1000BaseLXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASELXHD };
static guint32 const dot3MauType1000BaseLXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASELXFD };
static guint32 const dot3MauType1000BaseSXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASESXHD };
static guint32 const dot3MauType1000BaseSXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASESXFD };
static guint32 const dot3MauType1000BaseCXHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASECXHD };
static guint32 const dot3MauType1000BaseCXFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASECXFD };
static guint32 const dot3MauType1000BaseTHD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASETHD };
static guint32 const dot3MauType1000BaseTFD[]
	= { MAU_MIB_DOT3MAUTYPE1000BASETFD };

stls_identity_t const mau_mib_identities[] = {
    { dot3MauTypeAUI,
      sizeof(dot3MauTypeAUI)/sizeof(guint32),
      "dot3MauTypeAUI" },
    { dot3MauType10Base5,
      sizeof(dot3MauType10Base5)/sizeof(guint32),
      "dot3MauType10Base5" },
    { dot3MauTypeFoirl,
      sizeof(dot3MauTypeFoirl)/sizeof(guint32),
      "dot3MauTypeFoirl" },
    { dot3MauType10Base2,
      sizeof(dot3MauType10Base2)/sizeof(guint32),
      "dot3MauType10Base2" },
    { dot3MauType10BaseT,
      sizeof(dot3MauType10BaseT)/sizeof(guint32),
      "dot3MauType10BaseT" },
    { dot3MauType10BaseFP,
      sizeof(dot3MauType10BaseFP)/sizeof(guint32),
      "dot3MauType10BaseFP" },
    { dot3MauType10BaseFB,
      sizeof(dot3MauType10BaseFB)/sizeof(guint32),
      "dot3MauType10BaseFB" },
    { dot3MauType10BaseFL,
      sizeof(dot3MauType10BaseFL)/sizeof(guint32),
      "dot3MauType10BaseFL" },
    { dot3MauType10Broad36,
      sizeof(dot3MauType10Broad36)/sizeof(guint32),
      "dot3MauType10Broad36" },
    { dot3MauType10BaseTHD,
      sizeof(dot3MauType10BaseTHD)/sizeof(guint32),
      "dot3MauType10BaseTHD" },
    { dot3MauType10BaseTFD,
      sizeof(dot3MauType10BaseTFD)/sizeof(guint32),
      "dot3MauType10BaseTFD" },
    { dot3MauType10BaseFLHD,
      sizeof(dot3MauType10BaseFLHD)/sizeof(guint32),
      "dot3MauType10BaseFLHD" },
    { dot3MauType10BaseFLFD,
      sizeof(dot3MauType10BaseFLFD)/sizeof(guint32),
      "dot3MauType10BaseFLFD" },
    { dot3MauType100BaseT4,
      sizeof(dot3MauType100BaseT4)/sizeof(guint32),
      "dot3MauType100BaseT4" },
    { dot3MauType100BaseTXHD,
      sizeof(dot3MauType100BaseTXHD)/sizeof(guint32),
      "dot3MauType100BaseTXHD" },
    { dot3MauType100BaseTXFD,
      sizeof(dot3MauType100BaseTXFD)/sizeof(guint32),
      "dot3MauType100BaseTXFD" },
    { dot3MauType100BaseFXHD,
      sizeof(dot3MauType100BaseFXHD)/sizeof(guint32),
      "dot3MauType100BaseFXHD" },
    { dot3MauType100BaseFXFD,
      sizeof(dot3MauType100BaseFXFD)/sizeof(guint32),
      "dot3MauType100BaseFXFD" },
    { dot3MauType100BaseT2HD,
      sizeof(dot3MauType100BaseT2HD)/sizeof(guint32),
      "dot3MauType100BaseT2HD" },
    { dot3MauType100BaseT2FD,
      sizeof(dot3MauType100BaseT2FD)/sizeof(guint32),
      "dot3MauType100BaseT2FD" },
    { dot3MauType1000BaseXHD,
      sizeof(dot3MauType1000BaseXHD)/sizeof(guint32),
      "dot3MauType1000BaseXHD" },
    { dot3MauType1000BaseXFD,
      sizeof(dot3MauType1000BaseXFD)/sizeof(guint32),
      "dot3MauType1000BaseXFD" },
    { dot3MauType1000BaseLXHD,
      sizeof(dot3MauType1000BaseLXHD)/sizeof(guint32),
      "dot3MauType1000BaseLXHD" },
    { dot3MauType1000BaseLXFD,
      sizeof(dot3MauType1000BaseLXFD)/sizeof(guint32),
      "dot3MauType1000BaseLXFD" },
    { dot3MauType1000BaseSXHD,
      sizeof(dot3MauType1000BaseSXHD)/sizeof(guint32),
      "dot3MauType1000BaseSXHD" },
    { dot3MauType1000BaseSXFD,
      sizeof(dot3MauType1000BaseSXFD)/sizeof(guint32),
      "dot3MauType1000BaseSXFD" },
    { dot3MauType1000BaseCXHD,
      sizeof(dot3MauType1000BaseCXHD)/sizeof(guint32),
      "dot3MauType1000BaseCXHD" },
    { dot3MauType1000BaseCXFD,
      sizeof(dot3MauType1000BaseCXFD)/sizeof(guint32),
      "dot3MauType1000BaseCXFD" },
    { dot3MauType1000BaseTHD,
      sizeof(dot3MauType1000BaseTHD)/sizeof(guint32),
      "dot3MauType1000BaseTHD" },
    { dot3MauType1000BaseTFD,
      sizeof(dot3MauType1000BaseTFD)/sizeof(guint32),
      "dot3MauType1000BaseTFD" },
    { 0, 0, NULL }
};


static stls_stub_attr_t _rpMauEntry[] = {
    { 4, G_SNMP_OBJECT_ID, "rpMauType" },
    { 5, G_SNMP_INTEGER32, "rpMauStatus" },
    { 6, G_SNMP_INTEGER32, "rpMauMediaAvailable" },
    { 7, G_SNMP_COUNTER32, "rpMauMediaAvailableStateExits" },
    { 8, G_SNMP_INTEGER32, "rpMauJabberState" },
    { 9, G_SNMP_COUNTER32, "rpMauJabberingStateEnters" },
    { 10, G_SNMP_COUNTER32, "rpMauFalseCarriers" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _rpJackEntry[] = {
    { 2, G_SNMP_INTEGER32, "rpJackType" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _ifMauEntry[] = {
    { 3, G_SNMP_OBJECT_ID, "ifMauType" },
    { 4, G_SNMP_INTEGER32, "ifMauStatus" },
    { 5, G_SNMP_INTEGER32, "ifMauMediaAvailable" },
    { 6, G_SNMP_COUNTER32, "ifMauMediaAvailableStateExits" },
    { 7, G_SNMP_INTEGER32, "ifMauJabberState" },
    { 8, G_SNMP_COUNTER32, "ifMauJabberingStateEnters" },
    { 9, G_SNMP_COUNTER32, "ifMauFalseCarriers" },
    { 10, G_SNMP_INTEGER32, "ifMauTypeList" },
    { 11, G_SNMP_OBJECT_ID, "ifMauDefaultType" },
    { 12, G_SNMP_INTEGER32, "ifMauAutoNegSupported" },
    { 13, G_SNMP_OCTET_STRING, "ifMauTypeListBits" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _ifJackEntry[] = {
    { 2, G_SNMP_INTEGER32, "ifJackType" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _broadMauBasicEntry[] = {
    { 3, G_SNMP_INTEGER32, "broadMauXmtRcvSplitType" },
    { 4, G_SNMP_INTEGER32, "broadMauXmtCarrierFreq" },
    { 5, G_SNMP_INTEGER32, "broadMauTranslationFreq" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _ifMauAutoNegEntry[] = {
    { 1, G_SNMP_INTEGER32, "ifMauAutoNegAdminStatus" },
    { 2, G_SNMP_INTEGER32, "ifMauAutoNegRemoteSignaling" },
    { 4, G_SNMP_INTEGER32, "ifMauAutoNegConfig" },
    { 5, G_SNMP_INTEGER32, "ifMauAutoNegCapability" },
    { 6, G_SNMP_INTEGER32, "ifMauAutoNegCapAdvertised" },
    { 7, G_SNMP_INTEGER32, "ifMauAutoNegCapReceived" },
    { 8, G_SNMP_INTEGER32, "ifMauAutoNegRestart" },
    { 9, G_SNMP_OCTET_STRING, "ifMauAutoNegCapabilityBits" },
    { 10, G_SNMP_OCTET_STRING, "ifMauAutoNegCapAdvertisedBits" },
    { 11, G_SNMP_OCTET_STRING, "ifMauAutoNegCapReceivedBits" },
    { 12, G_SNMP_INTEGER32, "ifMauAutoNegRemoteFaultAdvertised" },
    { 13, G_SNMP_INTEGER32, "ifMauAutoNegRemoteFaultReceived" },
    { 0, 0, NULL }
};


rpMauEntry_t *
mau_mib_new_rpMauEntry()
{
    rpMauEntry_t *rpMauEntry;

    rpMauEntry = (rpMauEntry_t *) g_malloc0(sizeof(rpMauEntry_t) + sizeof(gpointer));
    return rpMauEntry;
}

static int
unpack_rpMauEntry(GSnmpVarBind *vb, rpMauEntry_t *rpMauEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    rpMauEntry->rpMauGroupIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    rpMauEntry->rpMauPortIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    rpMauEntry->rpMauIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static rpMauEntry_t *
assign_rpMauEntry(GSList *vbl)
{
    GSList *elem;
    rpMauEntry_t *rpMauEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 26, 1, 1, 1};

    rpMauEntry = mau_mib_new_rpMauEntry();
    if (! rpMauEntry) {
        return NULL;
    }

    p = (char *) rpMauEntry + sizeof(rpMauEntry_t);
    * (GSList **) p = vbl;

    if (unpack_rpMauEntry((GSnmpVarBind *) vbl->data, rpMauEntry) < 0) {
        g_warning("illegal rpMauEntry instance identifier");
        g_free(rpMauEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _rpMauEntry, &idx) < 0) continue;

        switch (idx) {
        case 4:
            rpMauEntry->_rpMauTypeLength = vb->syntax_len / sizeof(guint32);
            rpMauEntry->rpMauType = vb->syntax.ui32;
            break;
        case 5:
            rpMauEntry->rpMauStatus = &(vb->syntax.i32[0]);
            break;
        case 6:
            rpMauEntry->rpMauMediaAvailable = &(vb->syntax.i32[0]);
            break;
        case 7:
            rpMauEntry->rpMauMediaAvailableStateExits = &(vb->syntax.ui32[0]);
            break;
        case 8:
            rpMauEntry->rpMauJabberState = &(vb->syntax.i32[0]);
            break;
        case 9:
            rpMauEntry->rpMauJabberingStateEnters = &(vb->syntax.ui32[0]);
            break;
        case 10:
            rpMauEntry->rpMauFalseCarriers = &(vb->syntax.ui32[0]);
            break;
        };
    }

    return rpMauEntry;
}

int
mau_mib_get_rpMauTable(host_snmp *s, rpMauEntry_t ***rpMauEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 26, 1, 1, 1, 0};

    *rpMauEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _rpMauEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *rpMauEntry = (rpMauEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(rpMauEntry_t *));
    if (! *rpMauEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*rpMauEntry)[i] = assign_rpMauEntry(row->data);
    }

    return 0;
}

void
mau_mib_free_rpMauEntry(rpMauEntry_t *rpMauEntry)
{
    GSList *vbl;
    char *p;

    if (rpMauEntry) {
        p = (char *) rpMauEntry + sizeof(rpMauEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(rpMauEntry);
    }
}

void
mau_mib_free_rpMauTable(rpMauEntry_t **rpMauEntry)
{
    int i;

    if (rpMauEntry) {
        for (i = 0; rpMauEntry[i]; i++) {
            mau_mib_free_rpMauEntry(rpMauEntry[i]);
        }
        g_free(rpMauEntry);
    }
}

rpJackEntry_t *
mau_mib_new_rpJackEntry()
{
    rpJackEntry_t *rpJackEntry;

    rpJackEntry = (rpJackEntry_t *) g_malloc0(sizeof(rpJackEntry_t) + sizeof(gpointer));
    return rpJackEntry;
}

static int
unpack_rpJackEntry(GSnmpVarBind *vb, rpJackEntry_t *rpJackEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    rpJackEntry->rpMauGroupIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    rpJackEntry->rpMauPortIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    rpJackEntry->rpMauIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    rpJackEntry->rpJackIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static rpJackEntry_t *
assign_rpJackEntry(GSList *vbl)
{
    GSList *elem;
    rpJackEntry_t *rpJackEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 26, 1, 2, 1};

    rpJackEntry = mau_mib_new_rpJackEntry();
    if (! rpJackEntry) {
        return NULL;
    }

    p = (char *) rpJackEntry + sizeof(rpJackEntry_t);
    * (GSList **) p = vbl;

    if (unpack_rpJackEntry((GSnmpVarBind *) vbl->data, rpJackEntry) < 0) {
        g_warning("illegal rpJackEntry instance identifier");
        g_free(rpJackEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _rpJackEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            rpJackEntry->rpJackType = &(vb->syntax.i32[0]);
            break;
        };
    }

    return rpJackEntry;
}

int
mau_mib_get_rpJackTable(host_snmp *s, rpJackEntry_t ***rpJackEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 26, 1, 2, 1, 0};

    *rpJackEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _rpJackEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *rpJackEntry = (rpJackEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(rpJackEntry_t *));
    if (! *rpJackEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*rpJackEntry)[i] = assign_rpJackEntry(row->data);
    }

    return 0;
}

void
mau_mib_free_rpJackEntry(rpJackEntry_t *rpJackEntry)
{
    GSList *vbl;
    char *p;

    if (rpJackEntry) {
        p = (char *) rpJackEntry + sizeof(rpJackEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(rpJackEntry);
    }
}

void
mau_mib_free_rpJackTable(rpJackEntry_t **rpJackEntry)
{
    int i;

    if (rpJackEntry) {
        for (i = 0; rpJackEntry[i]; i++) {
            mau_mib_free_rpJackEntry(rpJackEntry[i]);
        }
        g_free(rpJackEntry);
    }
}

ifMauEntry_t *
mau_mib_new_ifMauEntry()
{
    ifMauEntry_t *ifMauEntry;

    ifMauEntry = (ifMauEntry_t *) g_malloc0(sizeof(ifMauEntry_t) + sizeof(gpointer));
    return ifMauEntry;
}

static int
unpack_ifMauEntry(GSnmpVarBind *vb, ifMauEntry_t *ifMauEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    ifMauEntry->ifMauIfIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    ifMauEntry->ifMauIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static ifMauEntry_t *
assign_ifMauEntry(GSList *vbl)
{
    GSList *elem;
    ifMauEntry_t *ifMauEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 26, 2, 1, 1};

    ifMauEntry = mau_mib_new_ifMauEntry();
    if (! ifMauEntry) {
        return NULL;
    }

    p = (char *) ifMauEntry + sizeof(ifMauEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ifMauEntry((GSnmpVarBind *) vbl->data, ifMauEntry) < 0) {
        g_warning("illegal ifMauEntry instance identifier");
        g_free(ifMauEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _ifMauEntry, &idx) < 0) continue;

        switch (idx) {
        case 3:
            ifMauEntry->_ifMauTypeLength = vb->syntax_len / sizeof(guint32);
            ifMauEntry->ifMauType = vb->syntax.ui32;
            break;
        case 4:
            ifMauEntry->ifMauStatus = &(vb->syntax.i32[0]);
            break;
        case 5:
            ifMauEntry->ifMauMediaAvailable = &(vb->syntax.i32[0]);
            break;
        case 6:
            ifMauEntry->ifMauMediaAvailableStateExits = &(vb->syntax.ui32[0]);
            break;
        case 7:
            ifMauEntry->ifMauJabberState = &(vb->syntax.i32[0]);
            break;
        case 8:
            ifMauEntry->ifMauJabberingStateEnters = &(vb->syntax.ui32[0]);
            break;
        case 9:
            ifMauEntry->ifMauFalseCarriers = &(vb->syntax.ui32[0]);
            break;
        case 10:
            ifMauEntry->ifMauTypeList = &(vb->syntax.i32[0]);
            break;
        case 11:
            ifMauEntry->_ifMauDefaultTypeLength = vb->syntax_len / sizeof(guint32);
            ifMauEntry->ifMauDefaultType = vb->syntax.ui32;
            break;
        case 12:
            ifMauEntry->ifMauAutoNegSupported = &(vb->syntax.i32[0]);
            break;
        case 13:
            ifMauEntry->_ifMauTypeListBitsLength = vb->syntax_len;
            ifMauEntry->ifMauTypeListBits = vb->syntax.uc;
            break;
        };
    }

    return ifMauEntry;
}

int
mau_mib_get_ifMauTable(host_snmp *s, ifMauEntry_t ***ifMauEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 26, 2, 1, 1, 0};

    *ifMauEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _ifMauEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *ifMauEntry = (ifMauEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(ifMauEntry_t *));
    if (! *ifMauEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*ifMauEntry)[i] = assign_ifMauEntry(row->data);
    }

    return 0;
}

void
mau_mib_free_ifMauEntry(ifMauEntry_t *ifMauEntry)
{
    GSList *vbl;
    char *p;

    if (ifMauEntry) {
        p = (char *) ifMauEntry + sizeof(ifMauEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(ifMauEntry);
    }
}

void
mau_mib_free_ifMauTable(ifMauEntry_t **ifMauEntry)
{
    int i;

    if (ifMauEntry) {
        for (i = 0; ifMauEntry[i]; i++) {
            mau_mib_free_ifMauEntry(ifMauEntry[i]);
        }
        g_free(ifMauEntry);
    }
}

ifJackEntry_t *
mau_mib_new_ifJackEntry()
{
    ifJackEntry_t *ifJackEntry;

    ifJackEntry = (ifJackEntry_t *) g_malloc0(sizeof(ifJackEntry_t) + sizeof(gpointer));
    return ifJackEntry;
}

static int
unpack_ifJackEntry(GSnmpVarBind *vb, ifJackEntry_t *ifJackEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    ifJackEntry->ifMauIfIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    ifJackEntry->ifMauIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    ifJackEntry->ifJackIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static ifJackEntry_t *
assign_ifJackEntry(GSList *vbl)
{
    GSList *elem;
    ifJackEntry_t *ifJackEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 26, 2, 2, 1};

    ifJackEntry = mau_mib_new_ifJackEntry();
    if (! ifJackEntry) {
        return NULL;
    }

    p = (char *) ifJackEntry + sizeof(ifJackEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ifJackEntry((GSnmpVarBind *) vbl->data, ifJackEntry) < 0) {
        g_warning("illegal ifJackEntry instance identifier");
        g_free(ifJackEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _ifJackEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            ifJackEntry->ifJackType = &(vb->syntax.i32[0]);
            break;
        };
    }

    return ifJackEntry;
}

int
mau_mib_get_ifJackTable(host_snmp *s, ifJackEntry_t ***ifJackEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 26, 2, 2, 1, 0};

    *ifJackEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _ifJackEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *ifJackEntry = (ifJackEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(ifJackEntry_t *));
    if (! *ifJackEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*ifJackEntry)[i] = assign_ifJackEntry(row->data);
    }

    return 0;
}

void
mau_mib_free_ifJackEntry(ifJackEntry_t *ifJackEntry)
{
    GSList *vbl;
    char *p;

    if (ifJackEntry) {
        p = (char *) ifJackEntry + sizeof(ifJackEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(ifJackEntry);
    }
}

void
mau_mib_free_ifJackTable(ifJackEntry_t **ifJackEntry)
{
    int i;

    if (ifJackEntry) {
        for (i = 0; ifJackEntry[i]; i++) {
            mau_mib_free_ifJackEntry(ifJackEntry[i]);
        }
        g_free(ifJackEntry);
    }
}

broadMauBasicEntry_t *
mau_mib_new_broadMauBasicEntry()
{
    broadMauBasicEntry_t *broadMauBasicEntry;

    broadMauBasicEntry = (broadMauBasicEntry_t *) g_malloc0(sizeof(broadMauBasicEntry_t) + sizeof(gpointer));
    return broadMauBasicEntry;
}

static int
unpack_broadMauBasicEntry(GSnmpVarBind *vb, broadMauBasicEntry_t *broadMauBasicEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    broadMauBasicEntry->broadMauIfIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    broadMauBasicEntry->broadMauIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static broadMauBasicEntry_t *
assign_broadMauBasicEntry(GSList *vbl)
{
    GSList *elem;
    broadMauBasicEntry_t *broadMauBasicEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 26, 3, 1, 1};

    broadMauBasicEntry = mau_mib_new_broadMauBasicEntry();
    if (! broadMauBasicEntry) {
        return NULL;
    }

    p = (char *) broadMauBasicEntry + sizeof(broadMauBasicEntry_t);
    * (GSList **) p = vbl;

    if (unpack_broadMauBasicEntry((GSnmpVarBind *) vbl->data, broadMauBasicEntry) < 0) {
        g_warning("illegal broadMauBasicEntry instance identifier");
        g_free(broadMauBasicEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _broadMauBasicEntry, &idx) < 0) continue;

        switch (idx) {
        case 3:
            broadMauBasicEntry->broadMauXmtRcvSplitType = &(vb->syntax.i32[0]);
            break;
        case 4:
            broadMauBasicEntry->broadMauXmtCarrierFreq = &(vb->syntax.i32[0]);
            break;
        case 5:
            broadMauBasicEntry->broadMauTranslationFreq = &(vb->syntax.i32[0]);
            break;
        };
    }

    return broadMauBasicEntry;
}

int
mau_mib_get_broadMauBasicTable(host_snmp *s, broadMauBasicEntry_t ***broadMauBasicEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 26, 3, 1, 1, 0};

    *broadMauBasicEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _broadMauBasicEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *broadMauBasicEntry = (broadMauBasicEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(broadMauBasicEntry_t *));
    if (! *broadMauBasicEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*broadMauBasicEntry)[i] = assign_broadMauBasicEntry(row->data);
    }

    return 0;
}

void
mau_mib_free_broadMauBasicEntry(broadMauBasicEntry_t *broadMauBasicEntry)
{
    GSList *vbl;
    char *p;

    if (broadMauBasicEntry) {
        p = (char *) broadMauBasicEntry + sizeof(broadMauBasicEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(broadMauBasicEntry);
    }
}

void
mau_mib_free_broadMauBasicTable(broadMauBasicEntry_t **broadMauBasicEntry)
{
    int i;

    if (broadMauBasicEntry) {
        for (i = 0; broadMauBasicEntry[i]; i++) {
            mau_mib_free_broadMauBasicEntry(broadMauBasicEntry[i]);
        }
        g_free(broadMauBasicEntry);
    }
}

ifMauAutoNegEntry_t *
mau_mib_new_ifMauAutoNegEntry()
{
    ifMauAutoNegEntry_t *ifMauAutoNegEntry;

    ifMauAutoNegEntry = (ifMauAutoNegEntry_t *) g_malloc0(sizeof(ifMauAutoNegEntry_t) + sizeof(gpointer));
    return ifMauAutoNegEntry;
}

static int
unpack_ifMauAutoNegEntry(GSnmpVarBind *vb, ifMauAutoNegEntry_t *ifMauAutoNegEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    ifMauAutoNegEntry->ifMauIfIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    ifMauAutoNegEntry->ifMauIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static ifMauAutoNegEntry_t *
assign_ifMauAutoNegEntry(GSList *vbl)
{
    GSList *elem;
    ifMauAutoNegEntry_t *ifMauAutoNegEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 26, 5, 1, 1};

    ifMauAutoNegEntry = mau_mib_new_ifMauAutoNegEntry();
    if (! ifMauAutoNegEntry) {
        return NULL;
    }

    p = (char *) ifMauAutoNegEntry + sizeof(ifMauAutoNegEntry_t);
    * (GSList **) p = vbl;

    if (unpack_ifMauAutoNegEntry((GSnmpVarBind *) vbl->data, ifMauAutoNegEntry) < 0) {
        g_warning("illegal ifMauAutoNegEntry instance identifier");
        g_free(ifMauAutoNegEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _ifMauAutoNegEntry, &idx) < 0) continue;

        switch (idx) {
        case 1:
            ifMauAutoNegEntry->ifMauAutoNegAdminStatus = &(vb->syntax.i32[0]);
            break;
        case 2:
            ifMauAutoNegEntry->ifMauAutoNegRemoteSignaling = &(vb->syntax.i32[0]);
            break;
        case 4:
            ifMauAutoNegEntry->ifMauAutoNegConfig = &(vb->syntax.i32[0]);
            break;
        case 5:
            ifMauAutoNegEntry->ifMauAutoNegCapability = &(vb->syntax.i32[0]);
            break;
        case 6:
            ifMauAutoNegEntry->ifMauAutoNegCapAdvertised = &(vb->syntax.i32[0]);
            break;
        case 7:
            ifMauAutoNegEntry->ifMauAutoNegCapReceived = &(vb->syntax.i32[0]);
            break;
        case 8:
            ifMauAutoNegEntry->ifMauAutoNegRestart = &(vb->syntax.i32[0]);
            break;
        case 9:
            ifMauAutoNegEntry->_ifMauAutoNegCapabilityBitsLength = vb->syntax_len;
            ifMauAutoNegEntry->ifMauAutoNegCapabilityBits = vb->syntax.uc;
            break;
        case 10:
            ifMauAutoNegEntry->_ifMauAutoNegCapAdvertisedBitsLength = vb->syntax_len;
            ifMauAutoNegEntry->ifMauAutoNegCapAdvertisedBits = vb->syntax.uc;
            break;
        case 11:
            ifMauAutoNegEntry->_ifMauAutoNegCapReceivedBitsLength = vb->syntax_len;
            ifMauAutoNegEntry->ifMauAutoNegCapReceivedBits = vb->syntax.uc;
            break;
        case 12:
            ifMauAutoNegEntry->ifMauAutoNegRemoteFaultAdvertised = &(vb->syntax.i32[0]);
            break;
        case 13:
            ifMauAutoNegEntry->ifMauAutoNegRemoteFaultReceived = &(vb->syntax.i32[0]);
            break;
        };
    }

    return ifMauAutoNegEntry;
}

int
mau_mib_get_ifMauAutoNegTable(host_snmp *s, ifMauAutoNegEntry_t ***ifMauAutoNegEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 26, 5, 1, 1, 0};

    *ifMauAutoNegEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _ifMauAutoNegEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *ifMauAutoNegEntry = (ifMauAutoNegEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(ifMauAutoNegEntry_t *));
    if (! *ifMauAutoNegEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*ifMauAutoNegEntry)[i] = assign_ifMauAutoNegEntry(row->data);
    }

    return 0;
}

void
mau_mib_free_ifMauAutoNegEntry(ifMauAutoNegEntry_t *ifMauAutoNegEntry)
{
    GSList *vbl;
    char *p;

    if (ifMauAutoNegEntry) {
        p = (char *) ifMauAutoNegEntry + sizeof(ifMauAutoNegEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(ifMauAutoNegEntry);
    }
}

void
mau_mib_free_ifMauAutoNegTable(ifMauAutoNegEntry_t **ifMauAutoNegEntry)
{
    int i;

    if (ifMauAutoNegEntry) {
        for (i = 0; ifMauAutoNegEntry[i]; i++) {
            mau_mib_free_ifMauAutoNegEntry(ifMauAutoNegEntry[i]);
        }
        g_free(ifMauAutoNegEntry);
    }
}

