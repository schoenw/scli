/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from SNMP-FRAMEWORK-MIB:
 *   The SNMP Management Architecture MIB
 *
 * Revision 1999-01-19 00:00:
 *   Updated editors' addresses, fixed typos.
 *   Published as RFC2571.
 *   
 *
 * Revision 1997-11-20 00:00:
 *   The initial version, published in RFC 2271.
 *   
 *
 * $Id$
 */

#ifndef _SNMP_FRAMEWORK_MIB_H_
#define _SNMP_FRAMEWORK_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map identities to strings and vice versa.
 */

#define SNMP_FRAMEWORK_MIB_SNMPAUTHPROTOCOLS	1,3,6,1,6,3,10,1,1
#define SNMP_FRAMEWORK_MIB_SNMPPRIVPROTOCOLS	1,3,6,1,6,3,10,1,2

extern GSnmpIdentity const snmp_framework_mib_identities[];

/*
 * C type definitions for SNMP-FRAMEWORK-MIB::snmpEngine.
 */

#define SNMP_FRAMEWORK_MIB_SNMPENGINEID             (1 << 0) 
#define SNMP_FRAMEWORK_MIB_SNMPENGINEBOOTS          (1 << 1) 
#define SNMP_FRAMEWORK_MIB_SNMPENGINETIME           (1 << 2) 
#define SNMP_FRAMEWORK_MIB_SNMPENGINEMAXMESSAGESIZE (1 << 3) 

typedef struct {
    guchar   *snmpEngineID;
#define SNMP_FRAMEWORK_MIB_SNMPENGINEIDMINLENGTH 5
#define SNMP_FRAMEWORK_MIB_SNMPENGINEIDMAXLENGTH 32
    guint16  _snmpEngineIDLength;
    gint32   *snmpEngineBoots;
    gint32   *snmpEngineTime;
    gint32   *snmpEngineMaxMessageSize;
} snmp_framework_mib_snmpEngine_t;

extern snmp_framework_mib_snmpEngine_t *
snmp_framework_mib_new_snmpEngine(void);

extern void
snmp_framework_mib_get_snmpEngine(GSnmpSession *s, snmp_framework_mib_snmpEngine_t **snmpEngine, gint mask);

extern void
snmp_framework_mib_free_snmpEngine(snmp_framework_mib_snmpEngine_t *snmpEngine);


#endif /* _SNMP_FRAMEWORK_MIB_H_ */
