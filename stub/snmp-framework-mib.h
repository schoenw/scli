/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
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

#include "stools.h"

/*
 * C type definitions for SNMP-FRAMEWORK-MIB::snmpEngine.
 */

typedef struct snmpEngine {
    guchar   *snmpEngineID;
    gsize    _snmpEngineIDLength;
    gint32   *snmpEngineBoots;
    gint32   *snmpEngineTime;
    gint32   *snmpEngineMaxMessageSize;
} snmpEngine_t;

extern snmpEngine_t *
snmp_framework_mib_new_snmpEngine();

extern int
snmp_framework_mib_get_snmpEngine(host_snmp *s, snmpEngine_t **snmpEngine);

extern void
snmp_framework_mib_free_snmpEngine(snmpEngine_t *snmpEngine);


#endif /* _SNMP_FRAMEWORK_MIB_H_ */
