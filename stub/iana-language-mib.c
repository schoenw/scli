/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from IANA-LANGUAGE-MIB:
 *   The MIB module registers object identifier values for
 *   well-known programming and scripting languages. Every
 *   language registration MUST describe the format used
 *   when transferring scripts written in this language.
 *   
 *   Any additions or changes to the contents of this MIB
 *   module require Designated Expert Review as defined in
 *   the Guidelines for Writing IANA Considerations Section
 *   document. The Designated Expert will be selected by
 *   the IESG Area Director of the OPS Area.
 *   
 *   Note, this module does not have to register all possible
 *   languages since languages are identified by object
 *   identifier values. It is therefore possible to registered 
 *   languages in private OID trees. The references given below are not
 *   normative with regard to the language version. Other
 *   references might be better suited to describe some newer 
 *   versions of this language. The references are only
 *   provided as `a pointer into the right direction'.
 *
 * Revision 2000-05-10 00:00:
 *   Import mib-2 instead of experimental, so that
 *   this module compiles
 *
 * Revision 1999-09-09 09:00:
 *   Initial version as published at time of
 *   publication of RFC 2591.
 *
 * $Id$
 */

#include "iana-language-mib.h"

static guint32 const ianaLangJavaByteCode[]
	= { IANA_LANGUAGE_MIB_IANALANGJAVABYTECODE };
static guint32 const ianaLangTcl[]
	= { IANA_LANGUAGE_MIB_IANALANGTCL };
static guint32 const ianaLangPerl[]
	= { IANA_LANGUAGE_MIB_IANALANGPERL };
static guint32 const ianaLangScheme[]
	= { IANA_LANGUAGE_MIB_IANALANGSCHEME };
static guint32 const ianaLangSRSL[]
	= { IANA_LANGUAGE_MIB_IANALANGSRSL };
static guint32 const ianaLangPSL[]
	= { IANA_LANGUAGE_MIB_IANALANGPSL };
static guint32 const ianaLangSMSL[]
	= { IANA_LANGUAGE_MIB_IANALANGSMSL };

stls_identity_t const iana_language_mib_identities[] = {
    { ianaLangJavaByteCode,
      sizeof(ianaLangJavaByteCode)/sizeof(guint32),
      "ianaLangJavaByteCode" },
    { ianaLangTcl,
      sizeof(ianaLangTcl)/sizeof(guint32),
      "ianaLangTcl" },
    { ianaLangPerl,
      sizeof(ianaLangPerl)/sizeof(guint32),
      "ianaLangPerl" },
    { ianaLangScheme,
      sizeof(ianaLangScheme)/sizeof(guint32),
      "ianaLangScheme" },
    { ianaLangSRSL,
      sizeof(ianaLangSRSL)/sizeof(guint32),
      "ianaLangSRSL" },
    { ianaLangPSL,
      sizeof(ianaLangPSL)/sizeof(guint32),
      "ianaLangPSL" },
    { ianaLangSMSL,
      sizeof(ianaLangSMSL)/sizeof(guint32),
      "ianaLangSMSL" },
    { 0, 0, NULL }
};


