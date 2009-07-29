/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli IANAifType-MIB
 *
 * Derived from IANAifType-MIB:
 *   This MIB module defines the IANAifType Textual
 *   Convention, and thus the enumerated values of
 *   the ifType object defined in MIB-II's ifTable.
 *
 * Revision 2007-09-13 00:00:
 *   Registration of new IANAifTypes 243 and 244.
 *
 * Revision 2007-05-29 00:00:
 *   Changed the description for IANAifType 228.
 *
 * Revision 2007-03-08 00:00:
 *   Registration of new IANAifType 242.
 *
 * Revision 2007-01-23 00:00:
 *   Registration of new IANAifTypes 239, 240, and 241.
 *
 * Revision 2006-10-17 00:00:
 *   Deprecated/Obsoleted IANAifType 230.  Registration of 
 *   IANAifType 238.
 *
 * Revision 2006-09-25 00:00:
 *   Changed the description for IANA ifType 
 *   184 and added new IANA ifType 237.
 *
 * Revision 2006-08-17 00:00:
 *   Changed the descriptions for IANAifTypes
 *   20 and 21.
 *
 * Revision 2006-08-11 00:00:
 *   Changed the descriptions for IANAifTypes
 *   7, 11, 62, 69, and 117.
 *
 * Revision 2006-07-25 00:00:
 *   Registration of new IANA ifType 236.
 *
 * Revision 2006-06-14 00:00:
 *   Registration of new IANA ifType 235.
 *
 * Revision 2006-03-31 00:00:
 *   Registration of new IANA ifType 234.
 *
 * Revision 2006-03-30 00:00:
 *   Registration of new IANA ifType 233.
 *
 * Revision 2005-12-22 00:00:
 *   Registration of new IANA ifTypes 231 and 232.
 *
 * Revision 2005-10-10 00:00:
 *   Registration of new IANA ifType 230.
 *
 * Revision 2005-09-09 00:00:
 *   Registration of new IANA ifType 229.
 *
 * Revision 2005-05-27 00:00:
 *   Registration of new IANA ifType 228.
 *
 * Revision 2005-03-03 00:00:
 *   Added the IANAtunnelType TC and deprecated
 *   IANAifType sixToFour (215) per RFC4087.
 *
 * Revision 2004-11-22 00:00:
 *   Registration of new IANA ifType 227 per RFC4631.
 *
 * Revision 2004-06-17 00:00:
 *   Registration of new IANA ifType 226.
 *
 * Revision 2004-05-12 00:00:
 *   Added description for IANAifType 6, and 
 *   changed the descriptions for IANAifTypes
 *   180, 181, and 182.
 *
 * Revision 2004-05-07 00:00:
 *   Registration of new IANAifType 225.
 *
 * Revision 2003-08-25 00:00:
 *   Deprecated IANAifTypes 7 and 11. Obsoleted
 *   IANAifTypes 62, 69, and 117.  ethernetCsmacd (6)
 *   should be used instead of these values
 *
 * Revision 2003-08-18 00:00:
 *   Registration of new IANAifType
 *   224.
 *
 * Revision 2003-08-07 00:00:
 *   Registration of new IANAifTypes
 *   222 and 223.
 *
 * Revision 2003-03-18 00:00:
 *   Registration of new IANAifType
 *   221.
 *
 * Revision 2003-01-13 00:00:
 *   Registration of new IANAifType
 *   220.
 *
 * Revision 2002-10-17 00:00:
 *   Registration of new IANAifType
 *   219.
 *
 * Revision 2002-07-16 00:00:
 *   Registration of new IANAifTypes
 *   217 and 218.
 *
 * Revision 2002-07-10 00:00:
 *   Registration of new IANAifTypes
 *   215 and 216.
 *
 * Revision 2002-06-19 00:00:
 *   Registration of new IANAifType
 *   214.
 *
 * Revision 2002-01-04 00:00:
 *   Registration of new IANAifTypes
 *   211, 212 and 213.
 *
 * Revision 2001-12-20 00:00:
 *   Registration of new IANAifTypes
 *   209 and 210.
 *
 * Revision 2001-11-15 00:00:
 *   Registration of new IANAifTypes
 *   207 and 208.
 *
 * Revision 2001-11-06 00:00:
 *   Registration of new IANAifType
 *   206.
 *
 * Revision 2001-11-02 00:00:
 *   Registration of new IANAifType
 *   205.
 *
 * Revision 2001-10-16 00:00:
 *   Registration of new IANAifTypes
 *   199, 200, 201, 202, 203, and 204.
 *
 * Revision 2001-09-19 00:00:
 *   Registration of new IANAifType
 *   198.
 *
 * Revision 2001-05-11 00:00:
 *   Registration of new IANAifType
 *   197.
 *
 * Revision 2001-01-12 00:00:
 *   Registration of new IANAifTypes
 *   195 and 196.
 *
 * Revision 2000-12-19 00:00:
 *   Registration of new IANAifTypes
 *   193 and 194.
 *
 * Revision 2000-12-07 00:00:
 *   Registration of new IANAifTypes
 *   191 and 192.
 *
 * Revision 2000-12-04 00:00:
 *   Registration of new IANAifType
 *   190.
 *
 * Revision 2000-10-17 00:00:
 *   Registration of new IANAifTypes
 *   188 and 189.
 *
 * Revision 2000-10-02 00:00:
 *   Registration of new IANAifType 187.
 *
 * Revision 2000-09-01 00:00:
 *   Registration of new IANAifTypes
 *   184, 185, and 186.
 *
 * Revision 2000-08-24 00:00:
 *   Registration of new IANAifType 183.
 *
 * Revision 2000-08-23 00:00:
 *   Registration of new IANAifTypes
 *   174-182.
 *
 * Revision 2000-08-22 00:00:
 *   Registration of new IANAifTypes 170,
 *   171, 172 and 173.
 *
 * Revision 2000-04-25 00:00:
 *   Registration of new IANAifTypes 168 and 169.
 *
 * Revision 2000-03-06 00:00:
 *   Fixed a missing semi-colon in the IMPORT.
 *   Also cleaned up the REVISION log a bit.
 *   It is not complete, but from now on it will
 *   be maintained and kept up to date with each
 *   change to this MIB module.
 *
 * Revision 1999-10-08 14:30:
 *   Include new name assignments up to cnr(85).
 *   This is the first version available via the WWW
 *   at: ftp://ftp.isi.edu/mib/ianaiftype.mib
 *
 * Revision 1994-01-31 00:00:
 *   Initial version of this MIB as published in
 *   RFC 1573.
 *
 * $Id$
 */

#include "ianaiftype-mib.h"

GNetSnmpEnum const ianaiftype_mib_enums_IANAifType[] = {
    { IANAIFTYPE_MIB_IANAIFTYPE_OTHER,                         "other" },
    { IANAIFTYPE_MIB_IANAIFTYPE_REGULAR1822,                   "regular1822" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HDH1822,                       "hdh1822" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DDNX25,                        "ddnX25" },
    { IANAIFTYPE_MIB_IANAIFTYPE_RFC877X25,                     "rfc877x25" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ETHERNETCSMACD,                "ethernetCsmacd" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88023CSMACD,                "iso88023Csmacd" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88024TOKENBUS,              "iso88024TokenBus" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88025TOKENRING,             "iso88025TokenRing" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88026MAN,                   "iso88026Man" },
    { IANAIFTYPE_MIB_IANAIFTYPE_STARLAN,                       "starLan" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROTEON10MBIT,                 "proteon10Mbit" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROTEON80MBIT,                 "proteon80Mbit" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HYPERCHANNEL,                  "hyperchannel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FDDI,                          "fddi" },
    { IANAIFTYPE_MIB_IANAIFTYPE_LAPB,                          "lapb" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SDLC,                          "sdlc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DS1,                           "ds1" },
    { IANAIFTYPE_MIB_IANAIFTYPE_E1,                            "e1" },
    { IANAIFTYPE_MIB_IANAIFTYPE_BASICISDN,                     "basicISDN" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PRIMARYISDN,                   "primaryISDN" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPPOINTTOPOINTSERIAL,        "propPointToPointSerial" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PPP,                           "ppp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SOFTWARELOOPBACK,              "softwareLoopback" },
    { IANAIFTYPE_MIB_IANAIFTYPE_EON,                           "eon" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ETHERNET3MBIT,                 "ethernet3Mbit" },
    { IANAIFTYPE_MIB_IANAIFTYPE_NSIP,                          "nsip" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SLIP,                          "slip" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ULTRA,                         "ultra" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DS3,                           "ds3" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SIP,                           "sip" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAY,                    "frameRelay" },
    { IANAIFTYPE_MIB_IANAIFTYPE_RS232,                         "rs232" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PARA,                          "para" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ARCNET,                        "arcnet" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ARCNETPLUS,                    "arcnetPlus" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATM,                           "atm" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MIOX25,                        "miox25" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SONET,                         "sonet" },
    { IANAIFTYPE_MIB_IANAIFTYPE_X25PLE,                        "x25ple" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88022LLC,                   "iso88022llc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_LOCALTALK,                     "localTalk" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SMDSDXI,                       "smdsDxi" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAYSERVICE,             "frameRelayService" },
    { IANAIFTYPE_MIB_IANAIFTYPE_V35,                           "v35" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HSSI,                          "hssi" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HIPPI,                         "hippi" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MODEM,                         "modem" },
    { IANAIFTYPE_MIB_IANAIFTYPE_AAL5,                          "aal5" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SONETPATH,                     "sonetPath" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SONETVT,                       "sonetVT" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SMDSICIP,                      "smdsIcip" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPVIRTUAL,                   "propVirtual" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPMULTIPLEXOR,               "propMultiplexor" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IEEE80212,                     "ieee80212" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FIBRECHANNEL,                  "fibreChannel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HIPPIINTERFACE,                "hippiInterface" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAYINTERCONNECT,        "frameRelayInterconnect" },
    { IANAIFTYPE_MIB_IANAIFTYPE_AFLANE8023,                    "aflane8023" },
    { IANAIFTYPE_MIB_IANAIFTYPE_AFLANE8025,                    "aflane8025" },
    { IANAIFTYPE_MIB_IANAIFTYPE_CCTEMUL,                       "cctEmul" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FASTETHER,                     "fastEther" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISDN,                          "isdn" },
    { IANAIFTYPE_MIB_IANAIFTYPE_V11,                           "v11" },
    { IANAIFTYPE_MIB_IANAIFTYPE_V36,                           "v36" },
    { IANAIFTYPE_MIB_IANAIFTYPE_G703AT64K,                     "g703at64k" },
    { IANAIFTYPE_MIB_IANAIFTYPE_G703AT2MB,                     "g703at2mb" },
    { IANAIFTYPE_MIB_IANAIFTYPE_QLLC,                          "qllc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FASTETHERFX,                   "fastEtherFX" },
    { IANAIFTYPE_MIB_IANAIFTYPE_CHANNEL,                       "channel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IEEE80211,                     "ieee80211" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IBM370PARCHAN,                 "ibm370parChan" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ESCON,                         "escon" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DLSW,                          "dlsw" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISDNS,                         "isdns" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISDNU,                         "isdnu" },
    { IANAIFTYPE_MIB_IANAIFTYPE_LAPD,                          "lapd" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IPSWITCH,                      "ipSwitch" },
    { IANAIFTYPE_MIB_IANAIFTYPE_RSRB,                          "rsrb" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMLOGICAL,                    "atmLogical" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DS0,                           "ds0" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DS0BUNDLE,                     "ds0Bundle" },
    { IANAIFTYPE_MIB_IANAIFTYPE_BSC,                           "bsc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ASYNC,                         "async" },
    { IANAIFTYPE_MIB_IANAIFTYPE_CNR,                           "cnr" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88025DTR,                   "iso88025Dtr" },
    { IANAIFTYPE_MIB_IANAIFTYPE_EPLRS,                         "eplrs" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ARAP,                          "arap" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPCNLS,                      "propCnls" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HOSTPAD,                       "hostPad" },
    { IANAIFTYPE_MIB_IANAIFTYPE_TERMPAD,                       "termPad" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAYMPI,                 "frameRelayMPI" },
    { IANAIFTYPE_MIB_IANAIFTYPE_X213,                          "x213" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ADSL,                          "adsl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_RADSL,                         "radsl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SDSL,                          "sdsl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VDSL,                          "vdsl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88025CRFPINT,               "iso88025CRFPInt" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MYRINET,                       "myrinet" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEEM,                       "voiceEM" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEFXO,                      "voiceFXO" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEFXS,                      "voiceFXS" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEENCAP,                    "voiceEncap" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERIP,                   "voiceOverIp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMDXI,                        "atmDxi" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMFUNI,                       "atmFuni" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMIMA,                        "atmIma" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PPPMULTILINKBUNDLE,            "pppMultilinkBundle" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IPOVERCDLC,                    "ipOverCdlc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IPOVERCLAW,                    "ipOverClaw" },
    { IANAIFTYPE_MIB_IANAIFTYPE_STACKTOSTACK,                  "stackToStack" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VIRTUALIPADDRESS,              "virtualIpAddress" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MPC,                           "mpc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IPOVERATM,                     "ipOverAtm" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISO88025FIBER,                 "iso88025Fiber" },
    { IANAIFTYPE_MIB_IANAIFTYPE_TDLC,                          "tdlc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_GIGABITETHERNET,               "gigabitEthernet" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HDLC,                          "hdlc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_LAPF,                          "lapf" },
    { IANAIFTYPE_MIB_IANAIFTYPE_V37,                           "v37" },
    { IANAIFTYPE_MIB_IANAIFTYPE_X25MLP,                        "x25mlp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_X25HUNTGROUP,                  "x25huntGroup" },
    { IANAIFTYPE_MIB_IANAIFTYPE_TRASNPHDLC,                    "trasnpHdlc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_INTERLEAVE,                    "interleave" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FAST,                          "fast" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IP,                            "ip" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEMACLAYER,             "docsCableMaclayer" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEDOWNSTREAM,           "docsCableDownstream" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEUPSTREAM,             "docsCableUpstream" },
    { IANAIFTYPE_MIB_IANAIFTYPE_A12MPPSWITCH,                  "a12MppSwitch" },
    { IANAIFTYPE_MIB_IANAIFTYPE_TUNNEL,                        "tunnel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_COFFEE,                        "coffee" },
    { IANAIFTYPE_MIB_IANAIFTYPE_CES,                           "ces" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMSUBINTERFACE,               "atmSubInterface" },
    { IANAIFTYPE_MIB_IANAIFTYPE_L2VLAN,                        "l2vlan" },
    { IANAIFTYPE_MIB_IANAIFTYPE_L3IPVLAN,                      "l3ipvlan" },
    { IANAIFTYPE_MIB_IANAIFTYPE_L3IPXVLAN,                     "l3ipxvlan" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DIGITALPOWERLINE,              "digitalPowerline" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MEDIAMAILOVERIP,               "mediaMailOverIp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DTM,                           "dtm" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DCN,                           "dcn" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IPFORWARD,                     "ipForward" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MSDSL,                         "msdsl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IEEE1394,                      "ieee1394" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IF_GSN,                        "if-gsn" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBRCCMACLAYER,                "dvbRccMacLayer" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBRCCDOWNSTREAM,              "dvbRccDownstream" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBRCCUPSTREAM,                "dvbRccUpstream" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMVIRTUAL,                    "atmVirtual" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MPLSTUNNEL,                    "mplsTunnel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SRP,                           "srp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERATM,                  "voiceOverAtm" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERFRAMERELAY,           "voiceOverFrameRelay" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IDSL,                          "idsl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_COMPOSITELINK,                 "compositeLink" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SS7SIGLINK,                    "ss7SigLink" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPWIRELESSP2P,               "propWirelessP2P" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FRFORWARD,                     "frForward" },
    { IANAIFTYPE_MIB_IANAIFTYPE_RFC1483,                       "rfc1483" },
    { IANAIFTYPE_MIB_IANAIFTYPE_USB,                           "usb" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IEEE8023ADLAG,                 "ieee8023adLag" },
    { IANAIFTYPE_MIB_IANAIFTYPE_BGPPOLICYACCOUNTING,           "bgppolicyaccounting" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FRF16MFRBUNDLE,                "frf16MfrBundle" },
    { IANAIFTYPE_MIB_IANAIFTYPE_H323GATEKEEPER,                "h323Gatekeeper" },
    { IANAIFTYPE_MIB_IANAIFTYPE_H323PROXY,                     "h323Proxy" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MPLS,                          "mpls" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MFSIGLINK,                     "mfSigLink" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HDSL2,                         "hdsl2" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SHDSL,                         "shdsl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DS1FDL,                        "ds1FDL" },
    { IANAIFTYPE_MIB_IANAIFTYPE_POS,                           "pos" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBASIIN,                      "dvbAsiIn" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBASIOUT,                     "dvbAsiOut" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PLC,                           "plc" },
    { IANAIFTYPE_MIB_IANAIFTYPE_NFAS,                          "nfas" },
    { IANAIFTYPE_MIB_IANAIFTYPE_TR008,                         "tr008" },
    { IANAIFTYPE_MIB_IANAIFTYPE_GR303RDT,                      "gr303RDT" },
    { IANAIFTYPE_MIB_IANAIFTYPE_GR303IDT,                      "gr303IDT" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ISUP,                          "isup" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPDOCSWIRELESSMACLAYER,      "propDocsWirelessMaclayer" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPDOCSWIRELESSDOWNSTREAM,    "propDocsWirelessDownstream" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPDOCSWIRELESSUPSTREAM,      "propDocsWirelessUpstream" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HIPERLAN2,                     "hiperlan2" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPBWAP2MP,                   "propBWAp2Mp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SONETOVERHEADCHANNEL,          "sonetOverheadChannel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DIGITALWRAPPEROVERHEADCHANNEL, "digitalWrapperOverheadChannel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_AAL2,                          "aal2" },
    { IANAIFTYPE_MIB_IANAIFTYPE_RADIOMAC,                      "radioMAC" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMRADIO,                      "atmRadio" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IMT,                           "imt" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MVL,                           "mvl" },
    { IANAIFTYPE_MIB_IANAIFTYPE_REACHDSL,                      "reachDSL" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FRDLCIENDPT,                   "frDlciEndPt" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMVCIENDPT,                   "atmVciEndPt" },
    { IANAIFTYPE_MIB_IANAIFTYPE_OPTICALCHANNEL,                "opticalChannel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_OPTICALTRANSPORT,              "opticalTransport" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PROPATM,                       "propAtm" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERCABLE,                "voiceOverCable" },
    { IANAIFTYPE_MIB_IANAIFTYPE_INFINIBAND,                    "infiniband" },
    { IANAIFTYPE_MIB_IANAIFTYPE_TELINK,                        "teLink" },
    { IANAIFTYPE_MIB_IANAIFTYPE_Q2931,                         "q2931" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VIRTUALTG,                     "virtualTg" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SIPTG,                         "sipTg" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SIPSIG,                        "sipSig" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEUPSTREAMCHANNEL,      "docsCableUpstreamChannel" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ECONET,                        "econet" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PON155,                        "pon155" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PON622,                        "pon622" },
    { IANAIFTYPE_MIB_IANAIFTYPE_BRIDGE,                        "bridge" },
    { IANAIFTYPE_MIB_IANAIFTYPE_LINEGROUP,                     "linegroup" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEEMFGD,                    "voiceEMFGD" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEFGDEANA,                  "voiceFGDEANA" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEDID,                      "voiceDID" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MPEGTRANSPORT,                 "mpegTransport" },
    { IANAIFTYPE_MIB_IANAIFTYPE_SIXTOFOUR,                     "sixToFour" },
    { IANAIFTYPE_MIB_IANAIFTYPE_GTP,                           "gtp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PDNETHERLOOP1,                 "pdnEtherLoop1" },
    { IANAIFTYPE_MIB_IANAIFTYPE_PDNETHERLOOP2,                 "pdnEtherLoop2" },
    { IANAIFTYPE_MIB_IANAIFTYPE_OPTICALCHANNELGROUP,           "opticalChannelGroup" },
    { IANAIFTYPE_MIB_IANAIFTYPE_HOMEPNA,                       "homepna" },
    { IANAIFTYPE_MIB_IANAIFTYPE_GFP,                           "gfp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_CISCOISLVLAN,                  "ciscoISLvlan" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ACTELISMETALOOP,               "actelisMetaLOOP" },
    { IANAIFTYPE_MIB_IANAIFTYPE_FCIPLINK,                      "fcipLink" },
    { IANAIFTYPE_MIB_IANAIFTYPE_RPR,                           "rpr" },
    { IANAIFTYPE_MIB_IANAIFTYPE_QAM,                           "qam" },
    { IANAIFTYPE_MIB_IANAIFTYPE_LMP,                           "lmp" },
    { IANAIFTYPE_MIB_IANAIFTYPE_CBLVECTASTAR,                  "cblVectaStar" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEMCMTSDOWNSTREAM,      "docsCableMCmtsDownstream" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ADSL2,                         "adsl2" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MACSECCONTROLLEDIF,            "macSecControlledIF" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MACSECUNCONTROLLEDIF,          "macSecUncontrolledIF" },
    { IANAIFTYPE_MIB_IANAIFTYPE_AVICIOPTICALETHER,             "aviciOpticalEther" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ATMBOND,                       "atmbond" },
    { IANAIFTYPE_MIB_IANAIFTYPE_VOICEFGDOS,                    "voiceFGDOS" },
    { IANAIFTYPE_MIB_IANAIFTYPE_MOCAVERSION1,                  "mocaVersion1" },
    { IANAIFTYPE_MIB_IANAIFTYPE_IEEE80216WMAN,                 "ieee80216WMAN" },
    { IANAIFTYPE_MIB_IANAIFTYPE_ADSL2PLUS,                     "adsl2plus" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBRCSMACLAYER,                "dvbRcsMacLayer" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBTDM,                        "dvbTdm" },
    { IANAIFTYPE_MIB_IANAIFTYPE_DVBRCSTDMA,                    "dvbRcsTdma" },
    { IANAIFTYPE_MIB_IANAIFTYPE_X86LAPS,                       "x86Laps" },
    { IANAIFTYPE_MIB_IANAIFTYPE_WWANPP,                        "wwanPP" },
    { IANAIFTYPE_MIB_IANAIFTYPE_WWANPP2,                       "wwanPP2" },
    { 0, NULL }
};

GNetSnmpEnum const ianaiftype_mib_enums_IANAtunnelType[] = {
    { IANAIFTYPE_MIB_IANATUNNELTYPE_OTHER,       "other" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_DIRECT,      "direct" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_GRE,         "gre" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_MINIMAL,     "minimal" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_L2TP,        "l2tp" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_PPTP,        "pptp" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_L2F,         "l2f" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_UDP,         "udp" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_ATMP,        "atmp" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_MSDP,        "msdp" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_SIXTOFOUR,   "sixToFour" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_SIXOVERFOUR, "sixOverFour" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_ISATAP,      "isatap" },
    { IANAIFTYPE_MIB_IANATUNNELTYPE_TEREDO,      "teredo" },
    { 0, NULL }
};


