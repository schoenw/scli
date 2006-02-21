/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli SNMPv2-TC
 *
 * Derived from SNMPv2-TC:
 *
 * $Id$
 */

#include "snmpv2-tc.h"

GNetSnmpEnum const snmpv2_tc_enums_TruthValue[] = {
    { SNMPV2_TC_TRUTHVALUE_TRUE,  "true" },
    { SNMPV2_TC_TRUTHVALUE_FALSE, "false" },
    { 0, NULL }
};

GNetSnmpEnum const snmpv2_tc_enums_RowStatus[] = {
    { SNMPV2_TC_ROWSTATUS_ACTIVE,        "active" },
    { SNMPV2_TC_ROWSTATUS_NOTINSERVICE,  "notInService" },
    { SNMPV2_TC_ROWSTATUS_NOTREADY,      "notReady" },
    { SNMPV2_TC_ROWSTATUS_CREATEANDGO,   "createAndGo" },
    { SNMPV2_TC_ROWSTATUS_CREATEANDWAIT, "createAndWait" },
    { SNMPV2_TC_ROWSTATUS_DESTROY,       "destroy" },
    { 0, NULL }
};

GNetSnmpEnum const snmpv2_tc_enums_StorageType[] = {
    { SNMPV2_TC_STORAGETYPE_OTHER,       "other" },
    { SNMPV2_TC_STORAGETYPE_VOLATILE,    "volatile" },
    { SNMPV2_TC_STORAGETYPE_NONVOLATILE, "nonVolatile" },
    { SNMPV2_TC_STORAGETYPE_PERMANENT,   "permanent" },
    { SNMPV2_TC_STORAGETYPE_READONLY,    "readOnly" },
    { 0, NULL }
};


