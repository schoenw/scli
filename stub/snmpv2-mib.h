/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from SNMPv2-MIB:
 *   The MIB module for SNMPv2 entities.
 *
 * Revision 1995-11-09 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 1993-04-01 00:00:
 *   The initial revision of this MIB module was published as
 *   RFC 1450.
 *
 * $Id$
 */

#ifndef _SNMPV2_MIB_H_
#define _SNMPV2_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define SNMPV2_MIB_SNMPENABLEAUTHENTRAPS_ENABLED  1
#define SNMPV2_MIB_SNMPENABLEAUTHENTRAPS_DISABLED 2

extern GSnmpEnum const snmpv2_mib_enums_snmpEnableAuthenTraps[];


/*
 * C type definitions for SNMPv2-MIB::system.
 */

#define SNMPV2_MIB_SYSDESCR        (1 << 0) 
#define SNMPV2_MIB_SYSOBJECTID     (1 << 1) 
#define SNMPV2_MIB_SYSUPTIME       (1 << 2) 
#define SNMPV2_MIB_SYSCONTACT      (1 << 3) 
#define SNMPV2_MIB_SYSNAME         (1 << 4) 
#define SNMPV2_MIB_SYSLOCATION     (1 << 5) 
#define SNMPV2_MIB_SYSSERVICES     (1 << 6) 
#define SNMPV2_MIB_SYSORLASTCHANGE (1 << 7) 

typedef struct {
    guchar   *sysDescr;
#define SNMPV2_MIB_SYSDESCRMINLENGTH 0
#define SNMPV2_MIB_SYSDESCRMAXLENGTH 255
    guint16  _sysDescrLength;
    guint32  *sysObjectID;
#define SNMPV2_MIB_SYSOBJECTIDMINLENGTH 0
#define SNMPV2_MIB_SYSOBJECTIDMAXLENGTH 128
    guint16  _sysObjectIDLength;
    guint32  *sysUpTime;
    guchar   *sysContact;
#define SNMPV2_MIB_SYSCONTACTMINLENGTH 0
#define SNMPV2_MIB_SYSCONTACTMAXLENGTH 255
    guint16  _sysContactLength;
    guchar   *sysName;
#define SNMPV2_MIB_SYSNAMEMINLENGTH 0
#define SNMPV2_MIB_SYSNAMEMAXLENGTH 255
    guint16  _sysNameLength;
    guchar   *sysLocation;
#define SNMPV2_MIB_SYSLOCATIONMINLENGTH 0
#define SNMPV2_MIB_SYSLOCATIONMAXLENGTH 255
    guint16  _sysLocationLength;
    gint32   *sysServices;
    guint32  *sysORLastChange;
} snmpv2_mib_system_t;

extern snmpv2_mib_system_t *
snmpv2_mib_new_system(void);

extern void
snmpv2_mib_get_system(GSnmpSession *s, snmpv2_mib_system_t **system, gint mask);

extern void
snmpv2_mib_set_system(GSnmpSession *s, snmpv2_mib_system_t *system, gint mask);

extern void
snmpv2_mib_free_system(snmpv2_mib_system_t *system);

extern void
snmpv2_mib_set_sysContact(GSnmpSession *s, guchar *sysContact, guint16 _sysContactLength);

extern void
snmpv2_mib_set_sysName(GSnmpSession *s, guchar *sysName, guint16 _sysNameLength);

extern void
snmpv2_mib_set_sysLocation(GSnmpSession *s, guchar *sysLocation, guint16 _sysLocationLength);

/*
 * C type definitions for SNMPv2-MIB::sysOREntry.
 */

#define SNMPV2_MIB_SYSORID     (1 << 0) 
#define SNMPV2_MIB_SYSORDESCR  (1 << 1) 
#define SNMPV2_MIB_SYSORUPTIME (1 << 2) 

typedef struct {
    gint32   sysORIndex;
    guint32  *sysORID;
#define SNMPV2_MIB_SYSORIDMINLENGTH 0
#define SNMPV2_MIB_SYSORIDMAXLENGTH 128
    guint16  _sysORIDLength;
    guchar   *sysORDescr;
#define SNMPV2_MIB_SYSORDESCRMINLENGTH 0
#define SNMPV2_MIB_SYSORDESCRMAXLENGTH 255
    guint16  _sysORDescrLength;
    guint32  *sysORUpTime;
} snmpv2_mib_sysOREntry_t;

extern void
snmpv2_mib_get_sysORTable(GSnmpSession *s, snmpv2_mib_sysOREntry_t ***sysOREntry, gint mask);

extern void
snmpv2_mib_free_sysORTable(snmpv2_mib_sysOREntry_t **sysOREntry);

extern snmpv2_mib_sysOREntry_t *
snmpv2_mib_new_sysOREntry(void);

extern void
snmpv2_mib_get_sysOREntry(GSnmpSession *s, snmpv2_mib_sysOREntry_t **sysOREntry, gint32 sysORIndex, gint mask);

extern void
snmpv2_mib_free_sysOREntry(snmpv2_mib_sysOREntry_t *sysOREntry);

/*
 * C type definitions for SNMPv2-MIB::snmp.
 */

#define SNMPV2_MIB_SNMPINPKTS              (1 << 0) 
#define SNMPV2_MIB_SNMPOUTPKTS             (1 << 1) 
#define SNMPV2_MIB_SNMPINBADVERSIONS       (1 << 2) 
#define SNMPV2_MIB_SNMPINBADCOMMUNITYNAMES (1 << 3) 
#define SNMPV2_MIB_SNMPINBADCOMMUNITYUSES  (1 << 4) 
#define SNMPV2_MIB_SNMPINASNPARSEERRS      (1 << 5) 
#define SNMPV2_MIB_SNMPINTOOBIGS           (1 << 6) 
#define SNMPV2_MIB_SNMPINNOSUCHNAMES       (1 << 7) 
#define SNMPV2_MIB_SNMPINBADVALUES         (1 << 8) 
#define SNMPV2_MIB_SNMPINREADONLYS         (1 << 9) 
#define SNMPV2_MIB_SNMPINGENERRS           (1 << 10) 
#define SNMPV2_MIB_SNMPINTOTALREQVARS      (1 << 11) 
#define SNMPV2_MIB_SNMPINTOTALSETVARS      (1 << 12) 
#define SNMPV2_MIB_SNMPINGETREQUESTS       (1 << 13) 
#define SNMPV2_MIB_SNMPINGETNEXTS          (1 << 14) 
#define SNMPV2_MIB_SNMPINSETREQUESTS       (1 << 15) 
#define SNMPV2_MIB_SNMPINGETRESPONSES      (1 << 16) 
#define SNMPV2_MIB_SNMPINTRAPS             (1 << 17) 
#define SNMPV2_MIB_SNMPOUTTOOBIGS          (1 << 18) 
#define SNMPV2_MIB_SNMPOUTNOSUCHNAMES      (1 << 19) 
#define SNMPV2_MIB_SNMPOUTBADVALUES        (1 << 20) 
#define SNMPV2_MIB_SNMPOUTGENERRS          (1 << 21) 
#define SNMPV2_MIB_SNMPOUTGETREQUESTS      (1 << 22) 
#define SNMPV2_MIB_SNMPOUTGETNEXTS         (1 << 23) 
#define SNMPV2_MIB_SNMPOUTSETREQUESTS      (1 << 24) 
#define SNMPV2_MIB_SNMPOUTGETRESPONSES     (1 << 25) 
#define SNMPV2_MIB_SNMPOUTTRAPS            (1 << 26) 
#define SNMPV2_MIB_SNMPENABLEAUTHENTRAPS   (1 << 27) 
#define SNMPV2_MIB_SNMPSILENTDROPS         (1 << 28) 
#define SNMPV2_MIB_SNMPPROXYDROPS          (1 << 29) 

typedef struct {
    guint32  *snmpInPkts;
    guint32  *snmpOutPkts;
    guint32  *snmpInBadVersions;
    guint32  *snmpInBadCommunityNames;
    guint32  *snmpInBadCommunityUses;
    guint32  *snmpInASNParseErrs;
    guint32  *snmpInTooBigs;
    guint32  *snmpInNoSuchNames;
    guint32  *snmpInBadValues;
    guint32  *snmpInReadOnlys;
    guint32  *snmpInGenErrs;
    guint32  *snmpInTotalReqVars;
    guint32  *snmpInTotalSetVars;
    guint32  *snmpInGetRequests;
    guint32  *snmpInGetNexts;
    guint32  *snmpInSetRequests;
    guint32  *snmpInGetResponses;
    guint32  *snmpInTraps;
    guint32  *snmpOutTooBigs;
    guint32  *snmpOutNoSuchNames;
    guint32  *snmpOutBadValues;
    guint32  *snmpOutGenErrs;
    guint32  *snmpOutGetRequests;
    guint32  *snmpOutGetNexts;
    guint32  *snmpOutSetRequests;
    guint32  *snmpOutGetResponses;
    guint32  *snmpOutTraps;
    gint32   *snmpEnableAuthenTraps;
    guint32  *snmpSilentDrops;
    guint32  *snmpProxyDrops;
} snmpv2_mib_snmp_t;

extern snmpv2_mib_snmp_t *
snmpv2_mib_new_snmp(void);

extern void
snmpv2_mib_get_snmp(GSnmpSession *s, snmpv2_mib_snmp_t **snmp, gint mask);

extern void
snmpv2_mib_set_snmp(GSnmpSession *s, snmpv2_mib_snmp_t *snmp, gint mask);

extern void
snmpv2_mib_free_snmp(snmpv2_mib_snmp_t *snmp);

extern void
snmpv2_mib_set_snmpEnableAuthenTraps(GSnmpSession *s, gint32 snmpEnableAuthenTraps);

/*
 * C type definitions for SNMPv2-MIB::snmpSet.
 */

#define SNMPV2_MIB_SNMPSETSERIALNO (1 << 0) 
typedef struct {
    gint32   *snmpSetSerialNo;
} snmpv2_mib_snmpSet_t;

extern snmpv2_mib_snmpSet_t *
snmpv2_mib_new_snmpSet(void);

extern void
snmpv2_mib_get_snmpSet(GSnmpSession *s, snmpv2_mib_snmpSet_t **snmpSet, gint mask);

extern void
snmpv2_mib_set_snmpSet(GSnmpSession *s, snmpv2_mib_snmpSet_t *snmpSet, gint mask);

extern void
snmpv2_mib_free_snmpSet(snmpv2_mib_snmpSet_t *snmpSet);

extern void
snmpv2_mib_set_snmpSetSerialNo(GSnmpSession *s, gint32 snmpSetSerialNo);


#endif /* _SNMPV2_MIB_H_ */
