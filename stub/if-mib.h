/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.16 for the stools package.
 *
 * Derived from IF-MIB:
 *   The MIB module to describe generic objects for network
 *   interface sub-layers.  This MIB is an updated version of
 *   MIB-II's ifTable, and incorporates the extensions defined in
 *   RFC 1229.
 *
 * Revision 2000-06-14 00:00:
 *   Clarifications agreed upon by the Interfaces MIB WG, and
 *   published as RFC 2863.
 *
 * Revision 1996-02-28 21:55:
 *   Revisions made by the Interfaces MIB WG, and published in
 *   RFC 2233.
 *
 * Revision 1993-11-08 21:55:
 *   Initial revision, published as part of RFC 1573.
 *
 * $Id$
 */

#ifndef _IF_MIB_H_
#define _IF_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define IF_MIB_IFTYPE_OTHER	1
#define IF_MIB_IFTYPE_REGULAR1822	2
#define IF_MIB_IFTYPE_HDH1822	3
#define IF_MIB_IFTYPE_DDNX25	4
#define IF_MIB_IFTYPE_RFC877X25	5
#define IF_MIB_IFTYPE_ETHERNETCSMACD	6
#define IF_MIB_IFTYPE_ISO88023CSMACD	7
#define IF_MIB_IFTYPE_ISO88024TOKENBUS	8
#define IF_MIB_IFTYPE_ISO88025TOKENRING	9
#define IF_MIB_IFTYPE_ISO88026MAN	10
#define IF_MIB_IFTYPE_STARLAN	11
#define IF_MIB_IFTYPE_PROTEON10MBIT	12
#define IF_MIB_IFTYPE_PROTEON80MBIT	13
#define IF_MIB_IFTYPE_HYPERCHANNEL	14
#define IF_MIB_IFTYPE_FDDI	15
#define IF_MIB_IFTYPE_LAPB	16
#define IF_MIB_IFTYPE_SDLC	17
#define IF_MIB_IFTYPE_DS1	18
#define IF_MIB_IFTYPE_E1	19
#define IF_MIB_IFTYPE_BASICISDN	20
#define IF_MIB_IFTYPE_PRIMARYISDN	21
#define IF_MIB_IFTYPE_PROPPOINTTOPOINTSERIAL	22
#define IF_MIB_IFTYPE_PPP	23
#define IF_MIB_IFTYPE_SOFTWARELOOPBACK	24
#define IF_MIB_IFTYPE_EON	25
#define IF_MIB_IFTYPE_ETHERNET3MBIT	26
#define IF_MIB_IFTYPE_NSIP	27
#define IF_MIB_IFTYPE_SLIP	28
#define IF_MIB_IFTYPE_ULTRA	29
#define IF_MIB_IFTYPE_DS3	30
#define IF_MIB_IFTYPE_SIP	31
#define IF_MIB_IFTYPE_FRAMERELAY	32
#define IF_MIB_IFTYPE_RS232	33
#define IF_MIB_IFTYPE_PARA	34
#define IF_MIB_IFTYPE_ARCNET	35
#define IF_MIB_IFTYPE_ARCNETPLUS	36
#define IF_MIB_IFTYPE_ATM	37
#define IF_MIB_IFTYPE_MIOX25	38
#define IF_MIB_IFTYPE_SONET	39
#define IF_MIB_IFTYPE_X25PLE	40
#define IF_MIB_IFTYPE_ISO88022LLC	41
#define IF_MIB_IFTYPE_LOCALTALK	42
#define IF_MIB_IFTYPE_SMDSDXI	43
#define IF_MIB_IFTYPE_FRAMERELAYSERVICE	44
#define IF_MIB_IFTYPE_V35	45
#define IF_MIB_IFTYPE_HSSI	46
#define IF_MIB_IFTYPE_HIPPI	47
#define IF_MIB_IFTYPE_MODEM	48
#define IF_MIB_IFTYPE_AAL5	49
#define IF_MIB_IFTYPE_SONETPATH	50
#define IF_MIB_IFTYPE_SONETVT	51
#define IF_MIB_IFTYPE_SMDSICIP	52
#define IF_MIB_IFTYPE_PROPVIRTUAL	53
#define IF_MIB_IFTYPE_PROPMULTIPLEXOR	54
#define IF_MIB_IFTYPE_IEEE80212	55
#define IF_MIB_IFTYPE_FIBRECHANNEL	56
#define IF_MIB_IFTYPE_HIPPIINTERFACE	57
#define IF_MIB_IFTYPE_FRAMERELAYINTERCONNECT	58
#define IF_MIB_IFTYPE_AFLANE8023	59
#define IF_MIB_IFTYPE_AFLANE8025	60
#define IF_MIB_IFTYPE_CCTEMUL	61
#define IF_MIB_IFTYPE_FASTETHER	62
#define IF_MIB_IFTYPE_ISDN	63
#define IF_MIB_IFTYPE_V11	64
#define IF_MIB_IFTYPE_V36	65
#define IF_MIB_IFTYPE_G703AT64K	66
#define IF_MIB_IFTYPE_G703AT2MB	67
#define IF_MIB_IFTYPE_QLLC	68
#define IF_MIB_IFTYPE_FASTETHERFX	69
#define IF_MIB_IFTYPE_CHANNEL	70
#define IF_MIB_IFTYPE_IEEE80211	71
#define IF_MIB_IFTYPE_IBM370PARCHAN	72
#define IF_MIB_IFTYPE_ESCON	73
#define IF_MIB_IFTYPE_DLSW	74
#define IF_MIB_IFTYPE_ISDNS	75
#define IF_MIB_IFTYPE_ISDNU	76
#define IF_MIB_IFTYPE_LAPD	77
#define IF_MIB_IFTYPE_IPSWITCH	78
#define IF_MIB_IFTYPE_RSRB	79
#define IF_MIB_IFTYPE_ATMLOGICAL	80
#define IF_MIB_IFTYPE_DS0	81
#define IF_MIB_IFTYPE_DS0BUNDLE	82
#define IF_MIB_IFTYPE_BSC	83
#define IF_MIB_IFTYPE_ASYNC	84
#define IF_MIB_IFTYPE_CNR	85
#define IF_MIB_IFTYPE_ISO88025DTR	86
#define IF_MIB_IFTYPE_EPLRS	87
#define IF_MIB_IFTYPE_ARAP	88
#define IF_MIB_IFTYPE_PROPCNLS	89
#define IF_MIB_IFTYPE_HOSTPAD	90
#define IF_MIB_IFTYPE_TERMPAD	91
#define IF_MIB_IFTYPE_FRAMERELAYMPI	92
#define IF_MIB_IFTYPE_X213	93
#define IF_MIB_IFTYPE_ADSL	94
#define IF_MIB_IFTYPE_RADSL	95
#define IF_MIB_IFTYPE_SDSL	96
#define IF_MIB_IFTYPE_VDSL	97
#define IF_MIB_IFTYPE_ISO88025CRFPINT	98
#define IF_MIB_IFTYPE_MYRINET	99
#define IF_MIB_IFTYPE_VOICEEM	100
#define IF_MIB_IFTYPE_VOICEFXO	101
#define IF_MIB_IFTYPE_VOICEFXS	102
#define IF_MIB_IFTYPE_VOICEENCAP	103
#define IF_MIB_IFTYPE_VOICEOVERIP	104
#define IF_MIB_IFTYPE_ATMDXI	105
#define IF_MIB_IFTYPE_ATMFUNI	106
#define IF_MIB_IFTYPE_ATMIMA	107
#define IF_MIB_IFTYPE_PPPMULTILINKBUNDLE	108
#define IF_MIB_IFTYPE_IPOVERCDLC	109
#define IF_MIB_IFTYPE_IPOVERCLAW	110
#define IF_MIB_IFTYPE_STACKTOSTACK	111
#define IF_MIB_IFTYPE_VIRTUALIPADDRESS	112
#define IF_MIB_IFTYPE_MPC	113
#define IF_MIB_IFTYPE_IPOVERATM	114
#define IF_MIB_IFTYPE_ISO88025FIBER	115
#define IF_MIB_IFTYPE_TDLC	116
#define IF_MIB_IFTYPE_GIGABITETHERNET	117
#define IF_MIB_IFTYPE_HDLC	118
#define IF_MIB_IFTYPE_LAPF	119
#define IF_MIB_IFTYPE_V37	120
#define IF_MIB_IFTYPE_X25MLP	121
#define IF_MIB_IFTYPE_X25HUNTGROUP	122
#define IF_MIB_IFTYPE_TRASNPHDLC	123
#define IF_MIB_IFTYPE_INTERLEAVE	124
#define IF_MIB_IFTYPE_FAST	125
#define IF_MIB_IFTYPE_IP	126
#define IF_MIB_IFTYPE_DOCSCABLEMACLAYER	127
#define IF_MIB_IFTYPE_DOCSCABLEDOWNSTREAM	128
#define IF_MIB_IFTYPE_DOCSCABLEUPSTREAM	129
#define IF_MIB_IFTYPE_A12MPPSWITCH	130
#define IF_MIB_IFTYPE_TUNNEL	131
#define IF_MIB_IFTYPE_COFFEE	132
#define IF_MIB_IFTYPE_CES	133
#define IF_MIB_IFTYPE_ATMSUBINTERFACE	134
#define IF_MIB_IFTYPE_L2VLAN	135
#define IF_MIB_IFTYPE_L3IPVLAN	136
#define IF_MIB_IFTYPE_L3IPXVLAN	137
#define IF_MIB_IFTYPE_DIGITALPOWERLINE	138
#define IF_MIB_IFTYPE_MEDIAMAILOVERIP	139
#define IF_MIB_IFTYPE_DTM	140
#define IF_MIB_IFTYPE_DCN	141
#define IF_MIB_IFTYPE_IPFORWARD	142
#define IF_MIB_IFTYPE_MSDSL	143
#define IF_MIB_IFTYPE_IEEE1394	144
#define IF_MIB_IFTYPE_IF_GSN	145
#define IF_MIB_IFTYPE_DVBRCCMACLAYER	146
#define IF_MIB_IFTYPE_DVBRCCDOWNSTREAM	147
#define IF_MIB_IFTYPE_DVBRCCUPSTREAM	148
#define IF_MIB_IFTYPE_ATMVIRTUAL	149
#define IF_MIB_IFTYPE_MPLSTUNNEL	150
#define IF_MIB_IFTYPE_SRP	151
#define IF_MIB_IFTYPE_VOICEOVERATM	152
#define IF_MIB_IFTYPE_VOICEOVERFRAMERELAY	153
#define IF_MIB_IFTYPE_IDSL	154
#define IF_MIB_IFTYPE_COMPOSITELINK	155
#define IF_MIB_IFTYPE_SS7SIGLINK	156
#define IF_MIB_IFTYPE_PROPWIRELESSP2P	157
#define IF_MIB_IFTYPE_FRFORWARD	158
#define IF_MIB_IFTYPE_RFC1483	159
#define IF_MIB_IFTYPE_USB	160
#define IF_MIB_IFTYPE_IEEE8023ADLAG	161
#define IF_MIB_IFTYPE_BGPPOLICYACCOUNTING	162
#define IF_MIB_IFTYPE_FRF16MFRBUNDLE	163
#define IF_MIB_IFTYPE_H323GATEKEEPER	164
#define IF_MIB_IFTYPE_H323PROXY	165
#define IF_MIB_IFTYPE_MPLS	166
#define IF_MIB_IFTYPE_MFSIGLINK	167
#define IF_MIB_IFTYPE_HDSL2	168
#define IF_MIB_IFTYPE_SHDSL	169
#define IF_MIB_IFTYPE_DS1FDL	170
#define IF_MIB_IFTYPE_POS	171
#define IF_MIB_IFTYPE_DVBASILN	172
#define IF_MIB_IFTYPE_DVBASIOUT	173
#define IF_MIB_IFTYPE_PLC	174
#define IF_MIB_IFTYPE_NFAS	175
#define IF_MIB_IFTYPE_TR008	176
#define IF_MIB_IFTYPE_GR303RDT	177
#define IF_MIB_IFTYPE_GR303IDT	178
#define IF_MIB_IFTYPE_ISUP	179
#define IF_MIB_IFTYPE_PROPDOCSWIRELESSMACLAYER	180
#define IF_MIB_IFTYPE_PROPDOCSWIRELESSDOWNSTREAM	181
#define IF_MIB_IFTYPE_PROPDOCSWIRELESSUPSTREAM	182
#define IF_MIB_IFTYPE_HIPERLAN2	183
#define IF_MIB_IFTYPE_PROPBWAP2MP	184
#define IF_MIB_IFTYPE_SONETOVERHEADCHANNEL	185
#define IF_MIB_IFTYPE_DIGITALWRAPPEROVERHEADCHANNEL	186
#define IF_MIB_IFTYPE_AAL2	187
#define IF_MIB_IFTYPE_RADIOMAC	188
#define IF_MIB_IFTYPE_ATMRADIO	189

extern stls_enum_t const if_mib_enums_ifType[];

#define IF_MIB_IFADMINSTATUS_UP	1
#define IF_MIB_IFADMINSTATUS_DOWN	2
#define IF_MIB_IFADMINSTATUS_TESTING	3

extern stls_enum_t const if_mib_enums_ifAdminStatus[];

#define IF_MIB_IFOPERSTATUS_UP	1
#define IF_MIB_IFOPERSTATUS_DOWN	2
#define IF_MIB_IFOPERSTATUS_TESTING	3
#define IF_MIB_IFOPERSTATUS_UNKNOWN	4
#define IF_MIB_IFOPERSTATUS_DORMANT	5
#define IF_MIB_IFOPERSTATUS_NOTPRESENT	6
#define IF_MIB_IFOPERSTATUS_LOWERLAYERDOWN	7

extern stls_enum_t const if_mib_enums_ifOperStatus[];

#define IF_MIB_IFLINKUPDOWNTRAPENABLE_ENABLED	1
#define IF_MIB_IFLINKUPDOWNTRAPENABLE_DISABLED	2

extern stls_enum_t const if_mib_enums_ifLinkUpDownTrapEnable[];

#define IF_MIB_IFPROMISCUOUSMODE_TRUE	1
#define IF_MIB_IFPROMISCUOUSMODE_FALSE	2

extern stls_enum_t const if_mib_enums_ifPromiscuousMode[];

#define IF_MIB_IFCONNECTORPRESENT_TRUE	1
#define IF_MIB_IFCONNECTORPRESENT_FALSE	2

extern stls_enum_t const if_mib_enums_ifConnectorPresent[];

#define IF_MIB_IFSTACKSTATUS_ACTIVE	1
#define IF_MIB_IFSTACKSTATUS_NOTINSERVICE	2
#define IF_MIB_IFSTACKSTATUS_NOTREADY	3
#define IF_MIB_IFSTACKSTATUS_CREATEANDGO	4
#define IF_MIB_IFSTACKSTATUS_CREATEANDWAIT	5
#define IF_MIB_IFSTACKSTATUS_DESTROY	6

extern stls_enum_t const if_mib_enums_ifStackStatus[];

#define IF_MIB_IFTESTSTATUS_NOTINUSE	1
#define IF_MIB_IFTESTSTATUS_INUSE	2

extern stls_enum_t const if_mib_enums_ifTestStatus[];

#define IF_MIB_IFTESTRESULT_NONE	1
#define IF_MIB_IFTESTRESULT_SUCCESS	2
#define IF_MIB_IFTESTRESULT_INPROGRESS	3
#define IF_MIB_IFTESTRESULT_NOTSUPPORTED	4
#define IF_MIB_IFTESTRESULT_UNABLETORUN	5
#define IF_MIB_IFTESTRESULT_ABORTED	6
#define IF_MIB_IFTESTRESULT_FAILED	7

extern stls_enum_t const if_mib_enums_ifTestResult[];

#define IF_MIB_IFRCVADDRESSSTATUS_ACTIVE	1
#define IF_MIB_IFRCVADDRESSSTATUS_NOTINSERVICE	2
#define IF_MIB_IFRCVADDRESSSTATUS_NOTREADY	3
#define IF_MIB_IFRCVADDRESSSTATUS_CREATEANDGO	4
#define IF_MIB_IFRCVADDRESSSTATUS_CREATEANDWAIT	5
#define IF_MIB_IFRCVADDRESSSTATUS_DESTROY	6

extern stls_enum_t const if_mib_enums_ifRcvAddressStatus[];

#define IF_MIB_IFRCVADDRESSTYPE_OTHER	1
#define IF_MIB_IFRCVADDRESSTYPE_VOLATILE	2
#define IF_MIB_IFRCVADDRESSTYPE_NONVOLATILE	3

extern stls_enum_t const if_mib_enums_ifRcvAddressType[];


/*
 * C type definitions for IF-MIB::interfaces.
 */

typedef struct {
    gint32   *ifNumber;
} if_mib_interfaces_t;

extern if_mib_interfaces_t *
if_mib_new_interfaces();

extern int
if_mib_get_interfaces(GSnmpSession *s, if_mib_interfaces_t **interfaces);

extern void
if_mib_free_interfaces(if_mib_interfaces_t *interfaces);

/*
 * C type definitions for IF-MIB::ifEntry.
 */

typedef struct {
    gint32   ifIndex;
    guchar   *ifDescr;
    gsize    _ifDescrLength;
    gint32   *ifType;
    gint32   *ifMtu;
    guint32  *ifSpeed;
    guchar   *ifPhysAddress;
    gsize    _ifPhysAddressLength;
    gint32   *ifAdminStatus;
    gint32   *ifOperStatus;
    guint32  *ifLastChange;
    guint32  *ifInOctets;
    guint32  *ifInUcastPkts;
    guint32  *ifInNUcastPkts;
    guint32  *ifInDiscards;
    guint32  *ifInErrors;
    guint32  *ifInUnknownProtos;
    guint32  *ifOutOctets;
    guint32  *ifOutUcastPkts;
    guint32  *ifOutNUcastPkts;
    guint32  *ifOutDiscards;
    guint32  *ifOutErrors;
    guint32  *ifOutQLen;
    guint32  *ifSpecific;
    gsize    _ifSpecificLength;
} if_mib_ifEntry_t;

extern int
if_mib_get_ifTable(GSnmpSession *s, if_mib_ifEntry_t ***ifEntry);

extern void
if_mib_free_ifTable(if_mib_ifEntry_t **ifEntry);

extern if_mib_ifEntry_t *
if_mib_new_ifEntry();

extern int
if_mib_get_ifEntry(GSnmpSession *s, if_mib_ifEntry_t **ifEntry);

extern int
if_mib_set_ifEntry(GSnmpSession *s, if_mib_ifEntry_t *ifEntry);

extern void
if_mib_free_ifEntry(if_mib_ifEntry_t *ifEntry);

/*
 * C type definitions for IF-MIB::ifMIBObjects.
 */

typedef struct {
    guint32  *ifTableLastChange;
    guint32  *ifStackLastChange;
} if_mib_ifMIBObjects_t;

extern if_mib_ifMIBObjects_t *
if_mib_new_ifMIBObjects();

extern int
if_mib_get_ifMIBObjects(GSnmpSession *s, if_mib_ifMIBObjects_t **ifMIBObjects);

extern void
if_mib_free_ifMIBObjects(if_mib_ifMIBObjects_t *ifMIBObjects);

/*
 * C type definitions for IF-MIB::ifXEntry.
 */

typedef struct {
    gint32   ifIndex;
    guchar   *ifName;
    gsize    _ifNameLength;
    guint32  *ifInMulticastPkts;
    guint32  *ifInBroadcastPkts;
    guint32  *ifOutMulticastPkts;
    guint32  *ifOutBroadcastPkts;
    guint64  *ifHCInOctets; 
    guint64  *ifHCInUcastPkts; 
    guint64  *ifHCInMulticastPkts; 
    guint64  *ifHCInBroadcastPkts; 
    guint64  *ifHCOutOctets; 
    guint64  *ifHCOutUcastPkts; 
    guint64  *ifHCOutMulticastPkts; 
    guint64  *ifHCOutBroadcastPkts; 
    gint32   *ifLinkUpDownTrapEnable;
    guint32  *ifHighSpeed;
    gint32   *ifPromiscuousMode;
    gint32   *ifConnectorPresent;
    guchar   *ifAlias;
    gsize    _ifAliasLength;
    guint32  *ifCounterDiscontinuityTime;
} if_mib_ifXEntry_t;

extern int
if_mib_get_ifXTable(GSnmpSession *s, if_mib_ifXEntry_t ***ifXEntry);

extern void
if_mib_free_ifXTable(if_mib_ifXEntry_t **ifXEntry);

extern if_mib_ifXEntry_t *
if_mib_new_ifXEntry();

extern int
if_mib_get_ifXEntry(GSnmpSession *s, if_mib_ifXEntry_t **ifXEntry);

extern int
if_mib_set_ifXEntry(GSnmpSession *s, if_mib_ifXEntry_t *ifXEntry);

extern void
if_mib_free_ifXEntry(if_mib_ifXEntry_t *ifXEntry);

/*
 * C type definitions for IF-MIB::ifStackEntry.
 */

typedef struct {
    gint32   ifStackHigherLayer;
    gint32   ifStackLowerLayer;
    gint32   *ifStackStatus;
} if_mib_ifStackEntry_t;

extern int
if_mib_get_ifStackTable(GSnmpSession *s, if_mib_ifStackEntry_t ***ifStackEntry);

extern void
if_mib_free_ifStackTable(if_mib_ifStackEntry_t **ifStackEntry);

extern if_mib_ifStackEntry_t *
if_mib_new_ifStackEntry();

extern int
if_mib_get_ifStackEntry(GSnmpSession *s, if_mib_ifStackEntry_t **ifStackEntry);

extern int
if_mib_set_ifStackEntry(GSnmpSession *s, if_mib_ifStackEntry_t *ifStackEntry);

extern void
if_mib_free_ifStackEntry(if_mib_ifStackEntry_t *ifStackEntry);

/*
 * C type definitions for IF-MIB::ifTestEntry.
 */

typedef struct {
    gint32   ifIndex;
    gint32   *ifTestId;
    gint32   *ifTestStatus;
    guint32  *ifTestType;
    gsize    _ifTestTypeLength;
    gint32   *ifTestResult;
    guint32  *ifTestCode;
    gsize    _ifTestCodeLength;
    guchar   *ifTestOwner;
    gsize    _ifTestOwnerLength;
} if_mib_ifTestEntry_t;

extern int
if_mib_get_ifTestTable(GSnmpSession *s, if_mib_ifTestEntry_t ***ifTestEntry);

extern void
if_mib_free_ifTestTable(if_mib_ifTestEntry_t **ifTestEntry);

extern if_mib_ifTestEntry_t *
if_mib_new_ifTestEntry();

extern int
if_mib_get_ifTestEntry(GSnmpSession *s, if_mib_ifTestEntry_t **ifTestEntry);

extern int
if_mib_set_ifTestEntry(GSnmpSession *s, if_mib_ifTestEntry_t *ifTestEntry);

extern void
if_mib_free_ifTestEntry(if_mib_ifTestEntry_t *ifTestEntry);

/*
 * C type definitions for IF-MIB::ifRcvAddressEntry.
 */

typedef struct {
    gint32   ifIndex;
    guchar   ifRcvAddressAddress[128];
    gsize    _ifRcvAddressAddressLength;
    gint32   *ifRcvAddressStatus;
    gint32   *ifRcvAddressType;
} if_mib_ifRcvAddressEntry_t;

extern int
if_mib_get_ifRcvAddressTable(GSnmpSession *s, if_mib_ifRcvAddressEntry_t ***ifRcvAddressEntry);

extern void
if_mib_free_ifRcvAddressTable(if_mib_ifRcvAddressEntry_t **ifRcvAddressEntry);

extern if_mib_ifRcvAddressEntry_t *
if_mib_new_ifRcvAddressEntry();

extern int
if_mib_get_ifRcvAddressEntry(GSnmpSession *s, if_mib_ifRcvAddressEntry_t **ifRcvAddressEntry);

extern int
if_mib_set_ifRcvAddressEntry(GSnmpSession *s, if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry);

extern void
if_mib_free_ifRcvAddressEntry(if_mib_ifRcvAddressEntry_t *ifRcvAddressEntry);


#endif /* _IF_MIB_H_ */
