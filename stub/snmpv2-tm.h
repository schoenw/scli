/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.0 for the scli package.
 *
 * Derived from SNMPv2-TM:
 *
 * $Id$
 */

#ifndef _SNMPV2_TM_H_
#define _SNMPV2_TM_H_

#include "g_snmp.h"

/*
 * Tables to map identities to strings and vice versa.
 */

#define SNMPV2_TM_SNMPUDPDOMAIN	1,3,6,1,6,1,1
#define SNMPV2_TM_SNMPCLNSDOMAIN	1,3,6,1,6,1,2
#define SNMPV2_TM_SNMPCONSDOMAIN	1,3,6,1,6,1,3
#define SNMPV2_TM_SNMPDDPDOMAIN	1,3,6,1,6,1,4
#define SNMPV2_TM_SNMPIPXDOMAIN	1,3,6,1,6,1,5
#define SNMPV2_TM_RFC1157DOMAIN	1,3,6,1,6,2,1,1

extern GSnmpIdentity const snmpv2_tm_identities[];

#endif /* _SNMPV2_TM_H_ */