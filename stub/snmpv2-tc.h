/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Derived from SNMPv2-TC:
 *
 * $Id$
 */

#ifndef _SNMPV2_TC_H_
#define _SNMPV2_TC_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMPV2_TC_TRUTHVALUE_TRUE  1
#define SNMPV2_TC_TRUTHVALUE_FALSE 2

extern GSnmpEnum const snmpv2_tc_enums_TruthValue[];

#define SNMPV2_TC_ROWSTATUS_ACTIVE        1
#define SNMPV2_TC_ROWSTATUS_NOTINSERVICE  2
#define SNMPV2_TC_ROWSTATUS_NOTREADY      3
#define SNMPV2_TC_ROWSTATUS_CREATEANDGO   4
#define SNMPV2_TC_ROWSTATUS_CREATEANDWAIT 5
#define SNMPV2_TC_ROWSTATUS_DESTROY       6

extern GSnmpEnum const snmpv2_tc_enums_RowStatus[];

#define SNMPV2_TC_STORAGETYPE_OTHER       1
#define SNMPV2_TC_STORAGETYPE_VOLATILE    2
#define SNMPV2_TC_STORAGETYPE_NONVOLATILE 3
#define SNMPV2_TC_STORAGETYPE_PERMANENT   4
#define SNMPV2_TC_STORAGETYPE_READONLY    5

extern GSnmpEnum const snmpv2_tc_enums_StorageType[];


G_END_DECLS

#endif /* _SNMPV2_TC_H_ */
