/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Derived from NOTIFICATION-LOG-MIB:
 *   The MIB module for logging SNMP Notifications, that is, Traps
 *   
 *   
 *   and Informs.
 *
 * Revision 2000-11-27 00:00:
 *   This is the initial version of this MIB.
 *   Published as RFC 3014
 *
 * $Id$
 */

#ifndef _NOTIFICATION_LOG_MIB_H_
#define _NOTIFICATION_LOG_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGADMINSTATUS_ENABLED  1
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGADMINSTATUS_DISABLED 2

extern GSnmpEnum const notification_log_mib_enums_nlmConfigLogAdminStatus[];

#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS_DISABLED    1
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS_OPERATIONAL 2
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS_NOFILTER    3

extern GSnmpEnum const notification_log_mib_enums_nlmConfigLogOperStatus[];

#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_COUNTER32   1
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_UNSIGNED32  2
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_TIMETICKS   3
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_INTEGER32   4
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_IPADDRESS   5
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_OCTETSTRING 6
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_OBJECTID    7
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_COUNTER64   8
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE_OPAQUE      9

extern GSnmpEnum const notification_log_mib_enums_nlmLogVariableValueType[];


/*
 * C type definitions for NOTIFICATION-LOG-MIB::nlmConfig.
 */

#define NOTIFICATION_LOG_MIB_NLMCONFIGGLOBALENTRYLIMIT (1 << 0) 
#define NOTIFICATION_LOG_MIB_NLMCONFIGGLOBALAGEOUT     (1 << 1) 

typedef struct {
    guint32  *nlmConfigGlobalEntryLimit;     /* rw Unsigned32 */
    guint32  *nlmConfigGlobalAgeOut;         /* rw Unsigned32 */
} notification_log_mib_nlmConfig_t;

extern notification_log_mib_nlmConfig_t *
notification_log_mib_new_nlmConfig(void);

extern void
notification_log_mib_get_nlmConfig(GSnmpSession *s, notification_log_mib_nlmConfig_t **nlmConfig, gint64 mask);

extern void
notification_log_mib_set_nlmConfig(GSnmpSession *s, notification_log_mib_nlmConfig_t *nlmConfig, gint64 mask);

extern void
notification_log_mib_free_nlmConfig(notification_log_mib_nlmConfig_t *nlmConfig);

/*
 * C type definitions for NOTIFICATION-LOG-MIB::nlmConfigLogEntry.
 */

#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGFILTERNAME  (1 << 0) 
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYLIMIT  (1 << 1) 
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGADMINSTATUS (1 << 2) 
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGOPERSTATUS  (1 << 3) 
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGSTORAGETYPE (1 << 4) 
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGENTRYSTATUS (1 << 5) 

typedef struct {
    guchar   nlmLogName[32];               /* na */
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMAXLENGTH 32
    guint16  _nlmLogNameLength;
    guchar   *nlmConfigLogFilterName;      /* rw */
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGFILTERNAMEMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMCONFIGLOGFILTERNAMEMAXLENGTH 32
    guint16  _nlmConfigLogFilterNameLength;
    guint32  *nlmConfigLogEntryLimit;      /* rw Unsigned32 */
    gint32   *nlmConfigLogAdminStatus;     /* rw */
    gint32   *nlmConfigLogOperStatus;      /* ro */
    gint32   *nlmConfigLogStorageType;     /* rw SNMPv2-TC::StorageType */
    gint32   *nlmConfigLogEntryStatus;     /* rw SNMPv2-TC::RowStatus */
} notification_log_mib_nlmConfigLogEntry_t;

extern void
notification_log_mib_get_nlmConfigLogTable(GSnmpSession *s, notification_log_mib_nlmConfigLogEntry_t ***nlmConfigLogEntry, gint64 mask);

extern void
notification_log_mib_free_nlmConfigLogTable(notification_log_mib_nlmConfigLogEntry_t **nlmConfigLogEntry);

extern notification_log_mib_nlmConfigLogEntry_t *
notification_log_mib_new_nlmConfigLogEntry(void);

extern void
notification_log_mib_get_nlmConfigLogEntry(GSnmpSession *s, notification_log_mib_nlmConfigLogEntry_t **nlmConfigLogEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, gint64 mask);

extern void
notification_log_mib_set_nlmConfigLogEntry(GSnmpSession *s, notification_log_mib_nlmConfigLogEntry_t *nlmConfigLogEntry, gint64 mask);

extern void
notification_log_mib_free_nlmConfigLogEntry(notification_log_mib_nlmConfigLogEntry_t *nlmConfigLogEntry);

/*
 * C type definitions for NOTIFICATION-LOG-MIB::nlmStats.
 */

#define NOTIFICATION_LOG_MIB_NLMSTATSGLOBALNOTIFICATIONSLOGGED (1 << 0) 
#define NOTIFICATION_LOG_MIB_NLMSTATSGLOBALNOTIFICATIONSBUMPED (1 << 1) 

typedef struct {
    guint32  *nlmStatsGlobalNotificationsLogged;     /* ro SNMPv2-SMI::Counter32 */
    guint32  *nlmStatsGlobalNotificationsBumped;     /* ro SNMPv2-SMI::Counter32 */
} notification_log_mib_nlmStats_t;

extern notification_log_mib_nlmStats_t *
notification_log_mib_new_nlmStats(void);

extern void
notification_log_mib_get_nlmStats(GSnmpSession *s, notification_log_mib_nlmStats_t **nlmStats, gint64 mask);

extern void
notification_log_mib_free_nlmStats(notification_log_mib_nlmStats_t *nlmStats);

/*
 * C type definitions for NOTIFICATION-LOG-MIB::nlmStatsLogEntry.
 */

#define NOTIFICATION_LOG_MIB_NLMSTATSLOGNOTIFICATIONSLOGGED (1 << 0) 
#define NOTIFICATION_LOG_MIB_NLMSTATSLOGNOTIFICATIONSBUMPED (1 << 1) 

typedef struct {
    guchar   nlmLogName[32];                      /* na */
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMAXLENGTH 32
    guint16  _nlmLogNameLength;
    guint32  *nlmStatsLogNotificationsLogged;     /* ro SNMPv2-SMI::Counter32 */
    guint32  *nlmStatsLogNotificationsBumped;     /* ro SNMPv2-SMI::Counter32 */
} notification_log_mib_nlmStatsLogEntry_t;

extern void
notification_log_mib_get_nlmStatsLogTable(GSnmpSession *s, notification_log_mib_nlmStatsLogEntry_t ***nlmStatsLogEntry, gint64 mask);

extern void
notification_log_mib_free_nlmStatsLogTable(notification_log_mib_nlmStatsLogEntry_t **nlmStatsLogEntry);

extern notification_log_mib_nlmStatsLogEntry_t *
notification_log_mib_new_nlmStatsLogEntry(void);

extern void
notification_log_mib_get_nlmStatsLogEntry(GSnmpSession *s, notification_log_mib_nlmStatsLogEntry_t **nlmStatsLogEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, gint64 mask);

extern void
notification_log_mib_free_nlmStatsLogEntry(notification_log_mib_nlmStatsLogEntry_t *nlmStatsLogEntry);

/*
 * C type definitions for NOTIFICATION-LOG-MIB::nlmLogEntry.
 */

#define NOTIFICATION_LOG_MIB_NLMLOGTIME            (1 << 0) 
#define NOTIFICATION_LOG_MIB_NLMLOGDATEANDTIME     (1 << 1) 
#define NOTIFICATION_LOG_MIB_NLMLOGENGINEID        (1 << 2) 
#define NOTIFICATION_LOG_MIB_NLMLOGENGINETADDRESS  (1 << 3) 
#define NOTIFICATION_LOG_MIB_NLMLOGENGINETDOMAIN   (1 << 4) 
#define NOTIFICATION_LOG_MIB_NLMLOGCONTEXTENGINEID (1 << 5) 
#define NOTIFICATION_LOG_MIB_NLMLOGCONTEXTNAME     (1 << 6) 
#define NOTIFICATION_LOG_MIB_NLMLOGNOTIFICATIONID  (1 << 7) 

typedef struct {
    guchar   nlmLogName[32];             /* na */
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMAXLENGTH 32
    guint16  _nlmLogNameLength;
    guint32  nlmLogIndex;                /* na */
    guint32  *nlmLogTime;                /* ro SNMPv2-TC::TimeStamp */
    guchar   *nlmLogDateAndTime;         /* ro SNMPv2-TC::DateAndTime */
#define NOTIFICATION_LOG_MIB_NLMLOGDATEANDTIMEMINLENGTH 8
#define NOTIFICATION_LOG_MIB_NLMLOGDATEANDTIMEMAXLENGTH 11
    guint16  _nlmLogDateAndTimeLength;
    guchar   *nlmLogEngineID;            /* ro SNMP-FRAMEWORK-MIB::SnmpEngineID */
#define NOTIFICATION_LOG_MIB_NLMLOGENGINEIDMINLENGTH 5
#define NOTIFICATION_LOG_MIB_NLMLOGENGINEIDMAXLENGTH 32
    guint16  _nlmLogEngineIDLength;
    guchar   *nlmLogEngineTAddress;      /* ro SNMPv2-TC::TAddress */
#define NOTIFICATION_LOG_MIB_NLMLOGENGINETADDRESSMINLENGTH 1
#define NOTIFICATION_LOG_MIB_NLMLOGENGINETADDRESSMAXLENGTH 255
    guint16  _nlmLogEngineTAddressLength;
    guint32  *nlmLogEngineTDomain;       /* ro SNMPv2-TC::TDomain */
#define NOTIFICATION_LOG_MIB_NLMLOGENGINETDOMAINMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGENGINETDOMAINMAXLENGTH 128
    guint16  _nlmLogEngineTDomainLength;
    guchar   *nlmLogContextEngineID;     /* ro SNMP-FRAMEWORK-MIB::SnmpEngineID */
#define NOTIFICATION_LOG_MIB_NLMLOGCONTEXTENGINEIDMINLENGTH 5
#define NOTIFICATION_LOG_MIB_NLMLOGCONTEXTENGINEIDMAXLENGTH 32
    guint16  _nlmLogContextEngineIDLength;
    guchar   *nlmLogContextName;         /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define NOTIFICATION_LOG_MIB_NLMLOGCONTEXTNAMEMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGCONTEXTNAMEMAXLENGTH 255
    guint16  _nlmLogContextNameLength;
    guint32  *nlmLogNotificationID;      /* ro ObjectIdentifier */
#define NOTIFICATION_LOG_MIB_NLMLOGNOTIFICATIONIDMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGNOTIFICATIONIDMAXLENGTH 128
    guint16  _nlmLogNotificationIDLength;
} notification_log_mib_nlmLogEntry_t;

extern void
notification_log_mib_get_nlmLogTable(GSnmpSession *s, notification_log_mib_nlmLogEntry_t ***nlmLogEntry, gint64 mask);

extern void
notification_log_mib_free_nlmLogTable(notification_log_mib_nlmLogEntry_t **nlmLogEntry);

extern notification_log_mib_nlmLogEntry_t *
notification_log_mib_new_nlmLogEntry(void);

extern void
notification_log_mib_get_nlmLogEntry(GSnmpSession *s, notification_log_mib_nlmLogEntry_t **nlmLogEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, guint32 nlmLogIndex, gint64 mask);

extern void
notification_log_mib_free_nlmLogEntry(notification_log_mib_nlmLogEntry_t *nlmLogEntry);

/*
 * C type definitions for NOTIFICATION-LOG-MIB::nlmLogVariableEntry.
 */

#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEID             (1 << 0) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEVALUETYPE      (1 << 1) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLECOUNTER32VAL   (1 << 2) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEUNSIGNED32VAL  (1 << 3) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLETIMETICKSVAL   (1 << 4) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEINTEGER32VAL   (1 << 5) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOCTETSTRINGVAL (1 << 6) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEIPADDRESSVAL   (1 << 7) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOIDVAL         (1 << 8) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLECOUNTER64VAL   (1 << 9) 
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOPAQUEVAL      (1 << 10) 

typedef struct {
    guchar   nlmLogName[32];                    /* na */
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGNAMEMAXLENGTH 32
    guint16  _nlmLogNameLength;
    guint32  nlmLogIndex;                       /* na */
    guint32  nlmLogVariableIndex;               /* na */
    guint32  *nlmLogVariableID;                 /* ro ObjectIdentifier */
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEIDMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEIDMAXLENGTH 128
    guint16  _nlmLogVariableIDLength;
    gint32   *nlmLogVariableValueType;          /* ro */
    guint32  *nlmLogVariableCounter32Val;       /* ro SNMPv2-SMI::Counter32 */
    guint32  *nlmLogVariableUnsigned32Val;      /* ro Unsigned32 */
    guint32  *nlmLogVariableTimeTicksVal;       /* ro SNMPv2-SMI::TimeTicks */
    gint32   *nlmLogVariableInteger32Val;       /* ro Integer32 */
    guchar   *nlmLogVariableOctetStringVal;     /* ro OctetString */
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOCTETSTRINGVALMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOCTETSTRINGVALMAXLENGTH 65535
    guint16  _nlmLogVariableOctetStringValLength;
    guchar   *nlmLogVariableIpAddressVal;       /* ro SNMPv2-SMI::IpAddress */
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEIPADDRESSVALLENGTH 4
    guint32  *nlmLogVariableOidVal;             /* ro ObjectIdentifier */
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOIDVALMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOIDVALMAXLENGTH 128
    guint16  _nlmLogVariableOidValLength;
    guint64  *nlmLogVariableCounter64Val;       /* ro SNMPv2-SMI::Counter64 */
    guchar   *nlmLogVariableOpaqueVal;          /* ro SNMPv2-SMI::Opaque */
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOPAQUEVALMINLENGTH 0
#define NOTIFICATION_LOG_MIB_NLMLOGVARIABLEOPAQUEVALMAXLENGTH 65535
    guint16  _nlmLogVariableOpaqueValLength;
} notification_log_mib_nlmLogVariableEntry_t;

extern void
notification_log_mib_get_nlmLogVariableTable(GSnmpSession *s, notification_log_mib_nlmLogVariableEntry_t ***nlmLogVariableEntry, gint64 mask);

extern void
notification_log_mib_free_nlmLogVariableTable(notification_log_mib_nlmLogVariableEntry_t **nlmLogVariableEntry);

extern notification_log_mib_nlmLogVariableEntry_t *
notification_log_mib_new_nlmLogVariableEntry(void);

extern void
notification_log_mib_get_nlmLogVariableEntry(GSnmpSession *s, notification_log_mib_nlmLogVariableEntry_t **nlmLogVariableEntry, guchar *nlmLogName, guint16 _nlmLogNameLength, guint32 nlmLogIndex, guint32 nlmLogVariableIndex, gint64 mask);

extern void
notification_log_mib_free_nlmLogVariableEntry(notification_log_mib_nlmLogVariableEntry_t *nlmLogVariableEntry);


G_END_DECLS

#endif /* _NOTIFICATION_LOG_MIB_H_ */
