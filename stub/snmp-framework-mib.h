/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli SNMP-FRAMEWORK-MIB
 *
 * Derived from SNMP-FRAMEWORK-MIB:
 *   The SNMP Management Architecture MIB
 *   
 *   Copyright (C) The Internet Society (2002). This
 *   version of this MIB module is part of RFC 3411;
 *   see the RFC itself for full legal notices.
 *
 * Revision 2002-10-14 00:00:
 *   Changes in this revision:
 *   - Updated various administrative information.
 *   - Corrected some typos.
 *   - Corrected typo in description of SnmpEngineID
 *     that led to range overlap for 127.
 *   - Changed '255a' to '255t' in definition of
 *     SnmpAdminString to align with current SMI.
 *   - Reworded 'reserved' for value zero in
 *     DESCRIPTION of SnmpSecurityModel.
 *   - The algorithm for allocating security models
 *     should give 256 per enterprise block, rather
 *     than 255.
 *   - The example engine ID of 'abcd' is not
 *     legal. Replaced with '800002b804616263'H based
 *     on example enterprise 696, string 'abc'.
 *   - Added clarification that engineID should
 *     persist across re-initializations.
 *   This revision published as RFC 3411.
 *
 * Revision 1999-01-19 00:00:
 *   Updated editors' addresses, fixed typos.
 *   Published as RFC 2571.
 *
 * Revision 1997-11-20 00:00:
 *   The initial version, published in RFC 2271.
 *
 * $Id$
 */

#ifndef _SNMP_FRAMEWORK_MIB_H_
#define _SNMP_FRAMEWORK_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMP_FRAMEWORK_MIB_SNMPSECURITYLEVEL_NOAUTHNOPRIV 1
#define SNMP_FRAMEWORK_MIB_SNMPSECURITYLEVEL_AUTHNOPRIV   2
#define SNMP_FRAMEWORK_MIB_SNMPSECURITYLEVEL_AUTHPRIV     3

extern GNetSnmpEnum const snmp_framework_mib_enums_SnmpSecurityLevel[];


/*
 * Tables to map identities to strings and vice versa.
 */

#define SNMP_FRAMEWORK_MIB_SNMPAUTHPROTOCOLS	1,3,6,1,6,3,10,1,1
#define SNMP_FRAMEWORK_MIB_SNMPPRIVPROTOCOLS	1,3,6,1,6,3,10,1,2

extern GNetSnmpIdentity const snmp_framework_mib_identities[];

/*
 * C type definitions for SNMP-FRAMEWORK-MIB::snmpEngine.
 */

#define SNMP_FRAMEWORK_MIB_SNMPENGINEID             (1 << 0) 
#define SNMP_FRAMEWORK_MIB_SNMPENGINEBOOTS          (1 << 1) 
#define SNMP_FRAMEWORK_MIB_SNMPENGINETIME           (1 << 2) 
#define SNMP_FRAMEWORK_MIB_SNMPENGINEMAXMESSAGESIZE (1 << 3) 

typedef struct {
    guchar   *snmpEngineID;                 /* ro SNMP-FRAMEWORK-MIB::SnmpEngineID */
#define SNMP_FRAMEWORK_MIB_SNMPENGINEIDMINLENGTH 5
#define SNMP_FRAMEWORK_MIB_SNMPENGINEIDMAXLENGTH 32
    guint16  _snmpEngineIDLength;
    gint32   *snmpEngineBoots;              /* ro */
    gint32   *snmpEngineTime;               /* ro [seconds] */
    gint32   *snmpEngineMaxMessageSize;     /* ro */
} snmp_framework_mib_snmpEngine_t;

extern snmp_framework_mib_snmpEngine_t *
snmp_framework_mib_new_snmpEngine(void);

extern void
snmp_framework_mib_get_snmpEngine(GNetSnmp *s, snmp_framework_mib_snmpEngine_t **snmpEngine, gint64 mask, GError **error);

extern void
snmp_framework_mib_free_snmpEngine(snmp_framework_mib_snmpEngine_t *snmpEngine);


G_END_DECLS

#endif /* _SNMP_FRAMEWORK_MIB_H_ */
