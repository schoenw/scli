/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3-pre1:
 *   smidump -f scli IANAifType-MIB
 *
 * Derived from IANAifType-MIB:
 *   This MIB module defines the IANAifType Textual
 *   Convention, and thus the enumerated values of
 *   the ifType object defined in MIB-II's ifTable.
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

#ifndef _IANAIFTYPE_MIB_H_
#define _IANAIFTYPE_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define IANAIFTYPE_MIB_IANAIFTYPE_OTHER                         1
#define IANAIFTYPE_MIB_IANAIFTYPE_REGULAR1822                   2
#define IANAIFTYPE_MIB_IANAIFTYPE_HDH1822                       3
#define IANAIFTYPE_MIB_IANAIFTYPE_DDNX25                        4
#define IANAIFTYPE_MIB_IANAIFTYPE_RFC877X25                     5
#define IANAIFTYPE_MIB_IANAIFTYPE_ETHERNETCSMACD                6
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88023CSMACD                7
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88024TOKENBUS              8
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88025TOKENRING             9
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88026MAN                   10
#define IANAIFTYPE_MIB_IANAIFTYPE_STARLAN                       11
#define IANAIFTYPE_MIB_IANAIFTYPE_PROTEON10MBIT                 12
#define IANAIFTYPE_MIB_IANAIFTYPE_PROTEON80MBIT                 13
#define IANAIFTYPE_MIB_IANAIFTYPE_HYPERCHANNEL                  14
#define IANAIFTYPE_MIB_IANAIFTYPE_FDDI                          15
#define IANAIFTYPE_MIB_IANAIFTYPE_LAPB                          16
#define IANAIFTYPE_MIB_IANAIFTYPE_SDLC                          17
#define IANAIFTYPE_MIB_IANAIFTYPE_DS1                           18
#define IANAIFTYPE_MIB_IANAIFTYPE_E1                            19
#define IANAIFTYPE_MIB_IANAIFTYPE_BASICISDN                     20
#define IANAIFTYPE_MIB_IANAIFTYPE_PRIMARYISDN                   21
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPPOINTTOPOINTSERIAL        22
#define IANAIFTYPE_MIB_IANAIFTYPE_PPP                           23
#define IANAIFTYPE_MIB_IANAIFTYPE_SOFTWARELOOPBACK              24
#define IANAIFTYPE_MIB_IANAIFTYPE_EON                           25
#define IANAIFTYPE_MIB_IANAIFTYPE_ETHERNET3MBIT                 26
#define IANAIFTYPE_MIB_IANAIFTYPE_NSIP                          27
#define IANAIFTYPE_MIB_IANAIFTYPE_SLIP                          28
#define IANAIFTYPE_MIB_IANAIFTYPE_ULTRA                         29
#define IANAIFTYPE_MIB_IANAIFTYPE_DS3                           30
#define IANAIFTYPE_MIB_IANAIFTYPE_SIP                           31
#define IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAY                    32
#define IANAIFTYPE_MIB_IANAIFTYPE_RS232                         33
#define IANAIFTYPE_MIB_IANAIFTYPE_PARA                          34
#define IANAIFTYPE_MIB_IANAIFTYPE_ARCNET                        35
#define IANAIFTYPE_MIB_IANAIFTYPE_ARCNETPLUS                    36
#define IANAIFTYPE_MIB_IANAIFTYPE_ATM                           37
#define IANAIFTYPE_MIB_IANAIFTYPE_MIOX25                        38
#define IANAIFTYPE_MIB_IANAIFTYPE_SONET                         39
#define IANAIFTYPE_MIB_IANAIFTYPE_X25PLE                        40
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88022LLC                   41
#define IANAIFTYPE_MIB_IANAIFTYPE_LOCALTALK                     42
#define IANAIFTYPE_MIB_IANAIFTYPE_SMDSDXI                       43
#define IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAYSERVICE             44
#define IANAIFTYPE_MIB_IANAIFTYPE_V35                           45
#define IANAIFTYPE_MIB_IANAIFTYPE_HSSI                          46
#define IANAIFTYPE_MIB_IANAIFTYPE_HIPPI                         47
#define IANAIFTYPE_MIB_IANAIFTYPE_MODEM                         48
#define IANAIFTYPE_MIB_IANAIFTYPE_AAL5                          49
#define IANAIFTYPE_MIB_IANAIFTYPE_SONETPATH                     50
#define IANAIFTYPE_MIB_IANAIFTYPE_SONETVT                       51
#define IANAIFTYPE_MIB_IANAIFTYPE_SMDSICIP                      52
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPVIRTUAL                   53
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPMULTIPLEXOR               54
#define IANAIFTYPE_MIB_IANAIFTYPE_IEEE80212                     55
#define IANAIFTYPE_MIB_IANAIFTYPE_FIBRECHANNEL                  56
#define IANAIFTYPE_MIB_IANAIFTYPE_HIPPIINTERFACE                57
#define IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAYINTERCONNECT        58
#define IANAIFTYPE_MIB_IANAIFTYPE_AFLANE8023                    59
#define IANAIFTYPE_MIB_IANAIFTYPE_AFLANE8025                    60
#define IANAIFTYPE_MIB_IANAIFTYPE_CCTEMUL                       61
#define IANAIFTYPE_MIB_IANAIFTYPE_FASTETHER                     62
#define IANAIFTYPE_MIB_IANAIFTYPE_ISDN                          63
#define IANAIFTYPE_MIB_IANAIFTYPE_V11                           64
#define IANAIFTYPE_MIB_IANAIFTYPE_V36                           65
#define IANAIFTYPE_MIB_IANAIFTYPE_G703AT64K                     66
#define IANAIFTYPE_MIB_IANAIFTYPE_G703AT2MB                     67
#define IANAIFTYPE_MIB_IANAIFTYPE_QLLC                          68
#define IANAIFTYPE_MIB_IANAIFTYPE_FASTETHERFX                   69
#define IANAIFTYPE_MIB_IANAIFTYPE_CHANNEL                       70
#define IANAIFTYPE_MIB_IANAIFTYPE_IEEE80211                     71
#define IANAIFTYPE_MIB_IANAIFTYPE_IBM370PARCHAN                 72
#define IANAIFTYPE_MIB_IANAIFTYPE_ESCON                         73
#define IANAIFTYPE_MIB_IANAIFTYPE_DLSW                          74
#define IANAIFTYPE_MIB_IANAIFTYPE_ISDNS                         75
#define IANAIFTYPE_MIB_IANAIFTYPE_ISDNU                         76
#define IANAIFTYPE_MIB_IANAIFTYPE_LAPD                          77
#define IANAIFTYPE_MIB_IANAIFTYPE_IPSWITCH                      78
#define IANAIFTYPE_MIB_IANAIFTYPE_RSRB                          79
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMLOGICAL                    80
#define IANAIFTYPE_MIB_IANAIFTYPE_DS0                           81
#define IANAIFTYPE_MIB_IANAIFTYPE_DS0BUNDLE                     82
#define IANAIFTYPE_MIB_IANAIFTYPE_BSC                           83
#define IANAIFTYPE_MIB_IANAIFTYPE_ASYNC                         84
#define IANAIFTYPE_MIB_IANAIFTYPE_CNR                           85
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88025DTR                   86
#define IANAIFTYPE_MIB_IANAIFTYPE_EPLRS                         87
#define IANAIFTYPE_MIB_IANAIFTYPE_ARAP                          88
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPCNLS                      89
#define IANAIFTYPE_MIB_IANAIFTYPE_HOSTPAD                       90
#define IANAIFTYPE_MIB_IANAIFTYPE_TERMPAD                       91
#define IANAIFTYPE_MIB_IANAIFTYPE_FRAMERELAYMPI                 92
#define IANAIFTYPE_MIB_IANAIFTYPE_X213                          93
#define IANAIFTYPE_MIB_IANAIFTYPE_ADSL                          94
#define IANAIFTYPE_MIB_IANAIFTYPE_RADSL                         95
#define IANAIFTYPE_MIB_IANAIFTYPE_SDSL                          96
#define IANAIFTYPE_MIB_IANAIFTYPE_VDSL                          97
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88025CRFPINT               98
#define IANAIFTYPE_MIB_IANAIFTYPE_MYRINET                       99
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEEM                       100
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEFXO                      101
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEFXS                      102
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEENCAP                    103
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERIP                   104
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMDXI                        105
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMFUNI                       106
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMIMA                        107
#define IANAIFTYPE_MIB_IANAIFTYPE_PPPMULTILINKBUNDLE            108
#define IANAIFTYPE_MIB_IANAIFTYPE_IPOVERCDLC                    109
#define IANAIFTYPE_MIB_IANAIFTYPE_IPOVERCLAW                    110
#define IANAIFTYPE_MIB_IANAIFTYPE_STACKTOSTACK                  111
#define IANAIFTYPE_MIB_IANAIFTYPE_VIRTUALIPADDRESS              112
#define IANAIFTYPE_MIB_IANAIFTYPE_MPC                           113
#define IANAIFTYPE_MIB_IANAIFTYPE_IPOVERATM                     114
#define IANAIFTYPE_MIB_IANAIFTYPE_ISO88025FIBER                 115
#define IANAIFTYPE_MIB_IANAIFTYPE_TDLC                          116
#define IANAIFTYPE_MIB_IANAIFTYPE_GIGABITETHERNET               117
#define IANAIFTYPE_MIB_IANAIFTYPE_HDLC                          118
#define IANAIFTYPE_MIB_IANAIFTYPE_LAPF                          119
#define IANAIFTYPE_MIB_IANAIFTYPE_V37                           120
#define IANAIFTYPE_MIB_IANAIFTYPE_X25MLP                        121
#define IANAIFTYPE_MIB_IANAIFTYPE_X25HUNTGROUP                  122
#define IANAIFTYPE_MIB_IANAIFTYPE_TRASNPHDLC                    123
#define IANAIFTYPE_MIB_IANAIFTYPE_INTERLEAVE                    124
#define IANAIFTYPE_MIB_IANAIFTYPE_FAST                          125
#define IANAIFTYPE_MIB_IANAIFTYPE_IP                            126
#define IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEMACLAYER             127
#define IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEDOWNSTREAM           128
#define IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEUPSTREAM             129
#define IANAIFTYPE_MIB_IANAIFTYPE_A12MPPSWITCH                  130
#define IANAIFTYPE_MIB_IANAIFTYPE_TUNNEL                        131
#define IANAIFTYPE_MIB_IANAIFTYPE_COFFEE                        132
#define IANAIFTYPE_MIB_IANAIFTYPE_CES                           133
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMSUBINTERFACE               134
#define IANAIFTYPE_MIB_IANAIFTYPE_L2VLAN                        135
#define IANAIFTYPE_MIB_IANAIFTYPE_L3IPVLAN                      136
#define IANAIFTYPE_MIB_IANAIFTYPE_L3IPXVLAN                     137
#define IANAIFTYPE_MIB_IANAIFTYPE_DIGITALPOWERLINE              138
#define IANAIFTYPE_MIB_IANAIFTYPE_MEDIAMAILOVERIP               139
#define IANAIFTYPE_MIB_IANAIFTYPE_DTM                           140
#define IANAIFTYPE_MIB_IANAIFTYPE_DCN                           141
#define IANAIFTYPE_MIB_IANAIFTYPE_IPFORWARD                     142
#define IANAIFTYPE_MIB_IANAIFTYPE_MSDSL                         143
#define IANAIFTYPE_MIB_IANAIFTYPE_IEEE1394                      144
#define IANAIFTYPE_MIB_IANAIFTYPE_IF_GSN                        145
#define IANAIFTYPE_MIB_IANAIFTYPE_DVBRCCMACLAYER                146
#define IANAIFTYPE_MIB_IANAIFTYPE_DVBRCCDOWNSTREAM              147
#define IANAIFTYPE_MIB_IANAIFTYPE_DVBRCCUPSTREAM                148
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMVIRTUAL                    149
#define IANAIFTYPE_MIB_IANAIFTYPE_MPLSTUNNEL                    150
#define IANAIFTYPE_MIB_IANAIFTYPE_SRP                           151
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERATM                  152
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERFRAMERELAY           153
#define IANAIFTYPE_MIB_IANAIFTYPE_IDSL                          154
#define IANAIFTYPE_MIB_IANAIFTYPE_COMPOSITELINK                 155
#define IANAIFTYPE_MIB_IANAIFTYPE_SS7SIGLINK                    156
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPWIRELESSP2P               157
#define IANAIFTYPE_MIB_IANAIFTYPE_FRFORWARD                     158
#define IANAIFTYPE_MIB_IANAIFTYPE_RFC1483                       159
#define IANAIFTYPE_MIB_IANAIFTYPE_USB                           160
#define IANAIFTYPE_MIB_IANAIFTYPE_IEEE8023ADLAG                 161
#define IANAIFTYPE_MIB_IANAIFTYPE_BGPPOLICYACCOUNTING           162
#define IANAIFTYPE_MIB_IANAIFTYPE_FRF16MFRBUNDLE                163
#define IANAIFTYPE_MIB_IANAIFTYPE_H323GATEKEEPER                164
#define IANAIFTYPE_MIB_IANAIFTYPE_H323PROXY                     165
#define IANAIFTYPE_MIB_IANAIFTYPE_MPLS                          166
#define IANAIFTYPE_MIB_IANAIFTYPE_MFSIGLINK                     167
#define IANAIFTYPE_MIB_IANAIFTYPE_HDSL2                         168
#define IANAIFTYPE_MIB_IANAIFTYPE_SHDSL                         169
#define IANAIFTYPE_MIB_IANAIFTYPE_DS1FDL                        170
#define IANAIFTYPE_MIB_IANAIFTYPE_POS                           171
#define IANAIFTYPE_MIB_IANAIFTYPE_DVBASIIN                      172
#define IANAIFTYPE_MIB_IANAIFTYPE_DVBASIOUT                     173
#define IANAIFTYPE_MIB_IANAIFTYPE_PLC                           174
#define IANAIFTYPE_MIB_IANAIFTYPE_NFAS                          175
#define IANAIFTYPE_MIB_IANAIFTYPE_TR008                         176
#define IANAIFTYPE_MIB_IANAIFTYPE_GR303RDT                      177
#define IANAIFTYPE_MIB_IANAIFTYPE_GR303IDT                      178
#define IANAIFTYPE_MIB_IANAIFTYPE_ISUP                          179
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPDOCSWIRELESSMACLAYER      180
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPDOCSWIRELESSDOWNSTREAM    181
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPDOCSWIRELESSUPSTREAM      182
#define IANAIFTYPE_MIB_IANAIFTYPE_HIPERLAN2                     183
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPBWAP2MP                   184
#define IANAIFTYPE_MIB_IANAIFTYPE_SONETOVERHEADCHANNEL          185
#define IANAIFTYPE_MIB_IANAIFTYPE_DIGITALWRAPPEROVERHEADCHANNEL 186
#define IANAIFTYPE_MIB_IANAIFTYPE_AAL2                          187
#define IANAIFTYPE_MIB_IANAIFTYPE_RADIOMAC                      188
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMRADIO                      189
#define IANAIFTYPE_MIB_IANAIFTYPE_IMT                           190
#define IANAIFTYPE_MIB_IANAIFTYPE_MVL                           191
#define IANAIFTYPE_MIB_IANAIFTYPE_REACHDSL                      192
#define IANAIFTYPE_MIB_IANAIFTYPE_FRDLCIENDPT                   193
#define IANAIFTYPE_MIB_IANAIFTYPE_ATMVCIENDPT                   194
#define IANAIFTYPE_MIB_IANAIFTYPE_OPTICALCHANNEL                195
#define IANAIFTYPE_MIB_IANAIFTYPE_OPTICALTRANSPORT              196
#define IANAIFTYPE_MIB_IANAIFTYPE_PROPATM                       197
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEOVERCABLE                198
#define IANAIFTYPE_MIB_IANAIFTYPE_INFINIBAND                    199
#define IANAIFTYPE_MIB_IANAIFTYPE_TELINK                        200
#define IANAIFTYPE_MIB_IANAIFTYPE_Q2931                         201
#define IANAIFTYPE_MIB_IANAIFTYPE_VIRTUALTG                     202
#define IANAIFTYPE_MIB_IANAIFTYPE_SIPTG                         203
#define IANAIFTYPE_MIB_IANAIFTYPE_SIPSIG                        204
#define IANAIFTYPE_MIB_IANAIFTYPE_DOCSCABLEUPSTREAMCHANNEL      205
#define IANAIFTYPE_MIB_IANAIFTYPE_ECONET                        206
#define IANAIFTYPE_MIB_IANAIFTYPE_PON155                        207
#define IANAIFTYPE_MIB_IANAIFTYPE_PON622                        208
#define IANAIFTYPE_MIB_IANAIFTYPE_BRIDGE                        209
#define IANAIFTYPE_MIB_IANAIFTYPE_LINEGROUP                     210
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEEMFGD                    211
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEFGDEANA                  212
#define IANAIFTYPE_MIB_IANAIFTYPE_VOICEDID                      213
#define IANAIFTYPE_MIB_IANAIFTYPE_MPEGTRANSPORT                 214
#define IANAIFTYPE_MIB_IANAIFTYPE_SIXTOFOUR                     215
#define IANAIFTYPE_MIB_IANAIFTYPE_GTP                           216
#define IANAIFTYPE_MIB_IANAIFTYPE_PDNETHERLOOP1                 217
#define IANAIFTYPE_MIB_IANAIFTYPE_PDNETHERLOOP2                 218
#define IANAIFTYPE_MIB_IANAIFTYPE_OPTICALCHANNELGROUP           219

extern GNetSnmpEnum const ianaiftype_mib_enums_IANAifType[];


G_END_DECLS

#endif /* _IANAIFTYPE_MIB_H_ */