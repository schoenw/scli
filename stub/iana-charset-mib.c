/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli IANA-CHARSET-MIB
 *
 * Derived from IANA-CHARSET-MIB:
 *   This MIB module defines the IANACharset
 *   TEXTUAL-CONVENTION.  The IANACharset TC is used to
 *   specify the encoding of string objects defined in
 *   a MIB.
 *   
 *   Each version of this MIB will be released based on
 *   the IANA Charset Registry file (see RFC 2978) at
 *   http://www.iana.org/assignments/character-sets.
 *   
 *   Note:  The IANACharset TC, originally defined in
 *   RFC 1759, was inaccurately named CodedCharSet.
 *   
 *   Note:  Best practice is to define new MIB string
 *   objects with invariant UTF-8 (RFC 3629) syntax
 *   using the SnmpAdminString TC (defined in RFC 3411)
 *   in accordance with IETF Policy on Character Sets and
 *   Languages (RFC 2277).
 *   
 *   Copyright (C) The Internet Society (2004).  The
 *   initial version of this MIB module was published
 *   in RFC 3808; for full legal notices see the RFC
 *   itself.  Supplementary information may be
 *   available on
 *   http://www.ietf.org/copyrights/ianamib.html.
 *
 * Revision 2007-05-14 00:00:
 *   Registration of new charset 2107.
 *
 * Revision 2006-12-07 00:00:
 *   Registration of new charsets numbered 118, 119, 
 *   and 2106.
 *
 * Revision 2004-06-08 00:00:
 *   Original version transferred from Printer MIB,
 *   generated from the IANA maintained assignments
 *   http://www.iana.org/assignments/character-sets.
 *
 * $Id$
 */

#include "iana-charset-mib.h"

GNetSnmpEnum const iana_charset_mib_enums_IANACharset[] = {
    { IANA_CHARSET_MIB_IANACHARSET_OTHER,                     "other" },
    { IANA_CHARSET_MIB_IANACHARSET_UNKNOWN,                   "unknown" },
    { IANA_CHARSET_MIB_IANACHARSET_CSASCII,                   "csASCII" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATIN1,               "csISOLatin1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATIN2,               "csISOLatin2" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATIN3,               "csISOLatin3" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATIN4,               "csISOLatin4" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATINCYRILLIC,        "csISOLatinCyrillic" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATINARABIC,          "csISOLatinArabic" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATINGREEK,           "csISOLatinGreek" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATINHEBREW,          "csISOLatinHebrew" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATIN5,               "csISOLatin5" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOLATIN6,               "csISOLatin6" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISOTEXTCOMM,             "csISOTextComm" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHALFWIDTHKATAKANA,       "csHalfWidthKatakana" },
    { IANA_CHARSET_MIB_IANACHARSET_CSJISENCODING,             "csJISEncoding" },
    { IANA_CHARSET_MIB_IANACHARSET_CSSHIFTJIS,                "csShiftJIS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEUCPKDFMTJAPANESE,       "csEUCPkdFmtJapanese" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEUCFIXWIDJAPANESE,       "csEUCFixWidJapanese" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO4UNITEDKINGDOM,       "csISO4UnitedKingdom" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO11SWEDISHFORNAMES,    "csISO11SwedishForNames" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO15ITALIAN,            "csISO15Italian" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO17SPANISH,            "csISO17Spanish" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO21GERMAN,             "csISO21German" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO60DANISHNORWEGIAN,    "csISO60DanishNorwegian" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO69FRENCH,             "csISO69French" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO10646UTF1,            "csISO10646UTF1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO646BASIC1983,         "csISO646basic1983" },
    { IANA_CHARSET_MIB_IANACHARSET_CSINVARIANT,               "csINVARIANT" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO2INTLREFVERSION,      "csISO2IntlRefVersion" },
    { IANA_CHARSET_MIB_IANACHARSET_CSNATSSEFI,                "csNATSSEFI" },
    { IANA_CHARSET_MIB_IANACHARSET_CSNATSSEFIADD,             "csNATSSEFIADD" },
    { IANA_CHARSET_MIB_IANACHARSET_CSNATSDANO,                "csNATSDANO" },
    { IANA_CHARSET_MIB_IANACHARSET_CSNATSDANOADD,             "csNATSDANOADD" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO10SWEDISH,            "csISO10Swedish" },
    { IANA_CHARSET_MIB_IANACHARSET_CSKSC56011987,             "csKSC56011987" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO2022KR,               "csISO2022KR" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEUCKR,                   "csEUCKR" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO2022JP,               "csISO2022JP" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO2022JP2,              "csISO2022JP2" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO13JISC6220JP,         "csISO13JISC6220jp" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO14JISC6220RO,         "csISO14JISC6220ro" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO16PORTUGUESE,         "csISO16Portuguese" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO18GREEK7OLD,          "csISO18Greek7Old" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO19LATINGREEK,         "csISO19LatinGreek" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO25FRENCH,             "csISO25French" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO27LATINGREEK1,        "csISO27LatinGreek1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO5427CYRILLIC,         "csISO5427Cyrillic" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO42JISC62261978,       "csISO42JISC62261978" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO47BSVIEWDATA,         "csISO47BSViewdata" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO49INIS,               "csISO49INIS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO50INIS8,              "csISO50INIS8" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO51INISCYRILLIC,       "csISO51INISCyrillic" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO54271981,             "csISO54271981" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO5428GREEK,            "csISO5428Greek" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO57GB1988,             "csISO57GB1988" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO58GB231280,           "csISO58GB231280" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO61NORWEGIAN2,         "csISO61Norwegian2" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO70VIDEOTEXSUPP1,      "csISO70VideotexSupp1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO84PORTUGUESE2,        "csISO84Portuguese2" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO85SPANISH2,           "csISO85Spanish2" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO86HUNGARIAN,          "csISO86Hungarian" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO87JISX0208,           "csISO87JISX0208" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO88GREEK7,             "csISO88Greek7" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO89ASMO449,            "csISO89ASMO449" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO90,                   "csISO90" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO91JISC62291984A,      "csISO91JISC62291984a" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO92JISC62991984B,      "csISO92JISC62991984b" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO93JIS62291984BADD,    "csISO93JIS62291984badd" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO94JIS62291984HAND,    "csISO94JIS62291984hand" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO95JIS62291984HANDADD, "csISO95JIS62291984handadd" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO96JISC62291984KANA,   "csISO96JISC62291984kana" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO2033,                 "csISO2033" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO99NAPLPS,             "csISO99NAPLPS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO102T617BIT,           "csISO102T617bit" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO103T618BIT,           "csISO103T618bit" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO111ECMACYRILLIC,      "csISO111ECMACyrillic" },
    { IANA_CHARSET_MIB_IANACHARSET_CSA71,                     "csa71" },
    { IANA_CHARSET_MIB_IANACHARSET_CSA72,                     "csa72" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO123CSAZ24341985GR,    "csISO123CSAZ24341985gr" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO88596E,               "csISO88596E" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO88596I,               "csISO88596I" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO128T101G2,            "csISO128T101G2" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO88598E,               "csISO88598E" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO88598I,               "csISO88598I" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO139CSN369103,         "csISO139CSN369103" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO141JUSIB1002,         "csISO141JUSIB1002" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO143IECP271,           "csISO143IECP271" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO146SERBIAN,           "csISO146Serbian" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO147MACEDONIAN,        "csISO147Macedonian" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO150,                  "csISO150" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO151CUBA,              "csISO151Cuba" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO6937ADD,              "csISO6937Add" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO153GOST1976874,       "csISO153GOST1976874" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO8859SUPP,             "csISO8859Supp" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO10367BOX,             "csISO10367Box" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO158LAP,               "csISO158Lap" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO159JISX02121990,      "csISO159JISX02121990" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO646DANISH,            "csISO646Danish" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUSDK,                    "csUSDK" },
    { IANA_CHARSET_MIB_IANACHARSET_CSDKUS,                    "csDKUS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSKSC5636,                 "csKSC5636" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODE11UTF7,           "csUnicode11UTF7" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO2022CN,               "csISO2022CN" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO2022CNEXT,            "csISO2022CNEXT" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF8,                    "csUTF8" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO885913,               "csISO885913" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO885914,               "csISO885914" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO885915,               "csISO885915" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO885916,               "csISO885916" },
    { IANA_CHARSET_MIB_IANACHARSET_CSGBK,                     "csGBK" },
    { IANA_CHARSET_MIB_IANACHARSET_CSGB18030,                 "csGB18030" },
    { IANA_CHARSET_MIB_IANACHARSET_CSOSDEBCDICDF0415,         "csOSDEBCDICDF0415" },
    { IANA_CHARSET_MIB_IANACHARSET_CSOSDEBCDICDF03IRV,        "csOSDEBCDICDF03IRV" },
    { IANA_CHARSET_MIB_IANACHARSET_CSOSDEBCDICDF041,          "csOSDEBCDICDF041" },
    { IANA_CHARSET_MIB_IANACHARSET_CSISO115481,               "csISO115481" },
    { IANA_CHARSET_MIB_IANACHARSET_CSKZ1048,                  "csKZ1048" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODE,                 "csUnicode" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUCS4,                    "csUCS4" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODEASCII,            "csUnicodeASCII" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODELATIN1,           "csUnicodeLatin1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODEIBM1261,          "csUnicodeIBM1261" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODEIBM1268,          "csUnicodeIBM1268" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODEIBM1276,          "csUnicodeIBM1276" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODEIBM1264,          "csUnicodeIBM1264" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODEIBM1265,          "csUnicodeIBM1265" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNICODE11,               "csUnicode11" },
    { IANA_CHARSET_MIB_IANACHARSET_CSSCSU,                    "csSCSU" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF7,                    "csUTF7" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF16BE,                 "csUTF16BE" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF16LE,                 "csUTF16LE" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF16,                   "csUTF16" },
    { IANA_CHARSET_MIB_IANACHARSET_CSCESU8,                   "csCESU8" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF32,                   "csUTF32" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF32BE,                 "csUTF32BE" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUTF32LE,                 "csUTF32LE" },
    { IANA_CHARSET_MIB_IANACHARSET_CSBOCU1,                   "csBOCU1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS30LATIN1,         "csWindows30Latin1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS31LATIN1,         "csWindows31Latin1" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS31LATIN2,         "csWindows31Latin2" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS31LATIN5,         "csWindows31Latin5" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHPROMAN8,                "csHPRoman8" },
    { IANA_CHARSET_MIB_IANACHARSET_CSADOBESTANDARDENCODING,   "csAdobeStandardEncoding" },
    { IANA_CHARSET_MIB_IANACHARSET_CSVENTURAUS,               "csVenturaUS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSVENTURAINTERNATIONAL,    "csVenturaInternational" },
    { IANA_CHARSET_MIB_IANACHARSET_CSDECMCS,                  "csDECMCS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPC850MULTILINGUAL,       "csPC850Multilingual" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPCP852,                  "csPCp852" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPC8CODEPAGE437,          "csPC8CodePage437" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPC8DANISHNORWEGIAN,      "csPC8DanishNorwegian" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPC862LATINHEBREW,        "csPC862LatinHebrew" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPC8TURKISH,              "csPC8Turkish" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBMSYMBOLS,              "csIBMSymbols" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBMTHAI,                 "csIBMThai" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHPLEGAL,                 "csHPLegal" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHPPIFONT,                "csHPPiFont" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHPMATH8,                 "csHPMath8" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHPPSMATH,                "csHPPSMath" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHPDESKTOP,               "csHPDesktop" },
    { IANA_CHARSET_MIB_IANACHARSET_CSVENTURAMATH,             "csVenturaMath" },
    { IANA_CHARSET_MIB_IANACHARSET_CSMICROSOFTPUBLISHING,     "csMicrosoftPublishing" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS31J,              "csWindows31J" },
    { IANA_CHARSET_MIB_IANACHARSET_CSGB2312,                  "csGB2312" },
    { IANA_CHARSET_MIB_IANACHARSET_CSBIG5,                    "csBig5" },
    { IANA_CHARSET_MIB_IANACHARSET_CSMACINTOSH,               "csMacintosh" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM037,                  "csIBM037" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM038,                  "csIBM038" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM273,                  "csIBM273" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM274,                  "csIBM274" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM275,                  "csIBM275" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM277,                  "csIBM277" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM278,                  "csIBM278" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM280,                  "csIBM280" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM281,                  "csIBM281" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM284,                  "csIBM284" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM285,                  "csIBM285" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM290,                  "csIBM290" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM297,                  "csIBM297" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM420,                  "csIBM420" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM423,                  "csIBM423" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM424,                  "csIBM424" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM500,                  "csIBM500" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM851,                  "csIBM851" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM855,                  "csIBM855" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM857,                  "csIBM857" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM860,                  "csIBM860" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM861,                  "csIBM861" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM863,                  "csIBM863" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM864,                  "csIBM864" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM865,                  "csIBM865" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM868,                  "csIBM868" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM869,                  "csIBM869" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM870,                  "csIBM870" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM871,                  "csIBM871" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM880,                  "csIBM880" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM891,                  "csIBM891" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM903,                  "csIBM903" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBBM904,                 "csIBBM904" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM905,                  "csIBM905" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM918,                  "csIBM918" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM1026,                 "csIBM1026" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBMEBCDICATDE,           "csIBMEBCDICATDE" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICATDEA,             "csEBCDICATDEA" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICCAFR,              "csEBCDICCAFR" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICDKNO,              "csEBCDICDKNO" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICDKNOA,             "csEBCDICDKNOA" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICFISE,              "csEBCDICFISE" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICFISEA,             "csEBCDICFISEA" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICFR,                "csEBCDICFR" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICIT,                "csEBCDICIT" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICPT,                "csEBCDICPT" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICES,                "csEBCDICES" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICESA,               "csEBCDICESA" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICESS,               "csEBCDICESS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICUK,                "csEBCDICUK" },
    { IANA_CHARSET_MIB_IANACHARSET_CSEBCDICUS,                "csEBCDICUS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSUNKNOWN8BIT,             "csUnknown8BiT" },
    { IANA_CHARSET_MIB_IANACHARSET_CSMNEMONIC,                "csMnemonic" },
    { IANA_CHARSET_MIB_IANACHARSET_CSMNEM,                    "csMnem" },
    { IANA_CHARSET_MIB_IANACHARSET_CSVISCII,                  "csVISCII" },
    { IANA_CHARSET_MIB_IANACHARSET_CSVIQR,                    "csVIQR" },
    { IANA_CHARSET_MIB_IANACHARSET_CSKOI8R,                   "csKOI8R" },
    { IANA_CHARSET_MIB_IANACHARSET_CSHZGB2312,                "csHZGB2312" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM866,                  "csIBM866" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPC775BALTIC,             "csPC775Baltic" },
    { IANA_CHARSET_MIB_IANACHARSET_CSKOI8U,                   "csKOI8U" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM00858,                "csIBM00858" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM00924,                "csIBM00924" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01140,                "csIBM01140" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01141,                "csIBM01141" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01142,                "csIBM01142" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01143,                "csIBM01143" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01144,                "csIBM01144" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01145,                "csIBM01145" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01146,                "csIBM01146" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01147,                "csIBM01147" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01148,                "csIBM01148" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM01149,                "csIBM01149" },
    { IANA_CHARSET_MIB_IANACHARSET_CSBIG5HKSCS,               "csBig5HKSCS" },
    { IANA_CHARSET_MIB_IANACHARSET_CSIBM1047,                 "csIBM1047" },
    { IANA_CHARSET_MIB_IANACHARSET_CSPTCP154,                 "csPTCP154" },
    { IANA_CHARSET_MIB_IANACHARSET_CSAMIGA1251,               "csAmiga1251" },
    { IANA_CHARSET_MIB_IANACHARSET_CSKOI7SWITCHED,            "csKOI7switched" },
    { IANA_CHARSET_MIB_IANACHARSET_CSBRF,                     "csBRF" },
    { IANA_CHARSET_MIB_IANACHARSET_CSTSCII,                   "csTSCII" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1250,             "cswindows1250" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1251,             "cswindows1251" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1252,             "cswindows1252" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1253,             "cswindows1253" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1254,             "cswindows1254" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1255,             "cswindows1255" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1256,             "cswindows1256" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1257,             "cswindows1257" },
    { IANA_CHARSET_MIB_IANACHARSET_CSWINDOWS1258,             "cswindows1258" },
    { IANA_CHARSET_MIB_IANACHARSET_CSTIS620,                  "csTIS620" },
    { IANA_CHARSET_MIB_IANACHARSET_RESERVED,                  "reserved" },
    { 0, NULL }
};


