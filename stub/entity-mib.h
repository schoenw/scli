/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Derived from ENTITY-MIB:
 *   The MIB module for representing multiple logical
 *   entities supported by a single SNMP agent.
 *
 * Revision 1999-12-07 00:00:
 *   Initial Version of Entity MIB (Version 2).
 *   This revision obsoletes RFC 2037.
 *   This version published as RFC 2737.
 *
 * Revision 1996-10-31 00:00:
 *   Initial version (version 1), published as
 *   RFC 2037.
 *
 * $Id$
 */

#ifndef _ENTITY_MIB_H_
#define _ENTITY_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define ENTITY_MIB_PHYSICALCLASS_OTHER       1
#define ENTITY_MIB_PHYSICALCLASS_UNKNOWN     2
#define ENTITY_MIB_PHYSICALCLASS_CHASSIS     3
#define ENTITY_MIB_PHYSICALCLASS_BACKPLANE   4
#define ENTITY_MIB_PHYSICALCLASS_CONTAINER   5
#define ENTITY_MIB_PHYSICALCLASS_POWERSUPPLY 6
#define ENTITY_MIB_PHYSICALCLASS_FAN         7
#define ENTITY_MIB_PHYSICALCLASS_SENSOR      8
#define ENTITY_MIB_PHYSICALCLASS_MODULE      9
#define ENTITY_MIB_PHYSICALCLASS_PORT        10
#define ENTITY_MIB_PHYSICALCLASS_STACK       11

extern GSnmpEnum const entity_mib_enums_PhysicalClass[];


/*
 * C type definitions for ENTITY-MIB::entPhysicalEntry.
 */

#define ENTITY_MIB_ENTPHYSICALDESCR        (1 << 0) 
#define ENTITY_MIB_ENTPHYSICALVENDORTYPE   (1 << 1) 
#define ENTITY_MIB_ENTPHYSICALCONTAINEDIN  (1 << 2) 
#define ENTITY_MIB_ENTPHYSICALCLASS        (1 << 3) 
#define ENTITY_MIB_ENTPHYSICALPARENTRELPOS (1 << 4) 
#define ENTITY_MIB_ENTPHYSICALNAME         (1 << 5) 
#define ENTITY_MIB_ENTPHYSICALHARDWAREREV  (1 << 6) 
#define ENTITY_MIB_ENTPHYSICALFIRMWAREREV  (1 << 7) 
#define ENTITY_MIB_ENTPHYSICALSOFTWAREREV  (1 << 8) 
#define ENTITY_MIB_ENTPHYSICALSERIALNUM    (1 << 9) 
#define ENTITY_MIB_ENTPHYSICALMFGNAME      (1 << 10) 
#define ENTITY_MIB_ENTPHYSICALMODELNAME    (1 << 11) 
#define ENTITY_MIB_ENTPHYSICALALIAS        (1 << 12) 
#define ENTITY_MIB_ENTPHYSICALASSETID      (1 << 13) 
#define ENTITY_MIB_ENTPHYSICALISFRU        (1 << 14) 

typedef struct {
    gint32   entPhysicalIndex;             /* na ENTITY-MIB::PhysicalIndex */
    guchar   *entPhysicalDescr;            /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTPHYSICALDESCRMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALDESCRMAXLENGTH 255
    guint16  _entPhysicalDescrLength;
    guint32  *entPhysicalVendorType;       /* ro SNMPv2-TC::AutonomousType */
#define ENTITY_MIB_ENTPHYSICALVENDORTYPEMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALVENDORTYPEMAXLENGTH 128
    guint16  _entPhysicalVendorTypeLength;
    gint32   *entPhysicalContainedIn;      /* ro */
    gint32   *entPhysicalClass;            /* ro ENTITY-MIB::PhysicalClass */
    gint32   *entPhysicalParentRelPos;     /* ro */
    guchar   *entPhysicalName;             /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTPHYSICALNAMEMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALNAMEMAXLENGTH 255
    guint16  _entPhysicalNameLength;
    guchar   *entPhysicalHardwareRev;      /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTPHYSICALHARDWAREREVMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALHARDWAREREVMAXLENGTH 255
    guint16  _entPhysicalHardwareRevLength;
    guchar   *entPhysicalFirmwareRev;      /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTPHYSICALFIRMWAREREVMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALFIRMWAREREVMAXLENGTH 255
    guint16  _entPhysicalFirmwareRevLength;
    guchar   *entPhysicalSoftwareRev;      /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTPHYSICALSOFTWAREREVMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALSOFTWAREREVMAXLENGTH 255
    guint16  _entPhysicalSoftwareRevLength;
    guchar   *entPhysicalSerialNum;        /* rw */
#define ENTITY_MIB_ENTPHYSICALSERIALNUMMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALSERIALNUMMAXLENGTH 32
    guint16  _entPhysicalSerialNumLength;
    guchar   *entPhysicalMfgName;          /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTPHYSICALMFGNAMEMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALMFGNAMEMAXLENGTH 255
    guint16  _entPhysicalMfgNameLength;
    guchar   *entPhysicalModelName;        /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTPHYSICALMODELNAMEMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALMODELNAMEMAXLENGTH 255
    guint16  _entPhysicalModelNameLength;
    guchar   *entPhysicalAlias;            /* rw */
#define ENTITY_MIB_ENTPHYSICALALIASMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALALIASMAXLENGTH 32
    guint16  _entPhysicalAliasLength;
    guchar   *entPhysicalAssetID;          /* rw */
#define ENTITY_MIB_ENTPHYSICALASSETIDMINLENGTH 0
#define ENTITY_MIB_ENTPHYSICALASSETIDMAXLENGTH 32
    guint16  _entPhysicalAssetIDLength;
    gint32   *entPhysicalIsFRU;            /* ro SNMPv2-TC::TruthValue */
} entity_mib_entPhysicalEntry_t;

extern void
entity_mib_get_entPhysicalTable(GSnmpSession *s, entity_mib_entPhysicalEntry_t ***entPhysicalEntry, gint64 mask);

extern void
entity_mib_free_entPhysicalTable(entity_mib_entPhysicalEntry_t **entPhysicalEntry);

extern entity_mib_entPhysicalEntry_t *
entity_mib_new_entPhysicalEntry(void);

extern void
entity_mib_get_entPhysicalEntry(GSnmpSession *s, entity_mib_entPhysicalEntry_t **entPhysicalEntry, gint32 entPhysicalIndex, gint64 mask);

extern void
entity_mib_set_entPhysicalEntry(GSnmpSession *s, entity_mib_entPhysicalEntry_t *entPhysicalEntry, gint64 mask);

extern void
entity_mib_free_entPhysicalEntry(entity_mib_entPhysicalEntry_t *entPhysicalEntry);

/*
 * C type definitions for ENTITY-MIB::entLogicalEntry.
 */

#define ENTITY_MIB_ENTLOGICALDESCR           (1 << 0) 
#define ENTITY_MIB_ENTLOGICALTYPE            (1 << 1) 
#define ENTITY_MIB_ENTLOGICALCOMMUNITY       (1 << 2) 
#define ENTITY_MIB_ENTLOGICALTADDRESS        (1 << 3) 
#define ENTITY_MIB_ENTLOGICALTDOMAIN         (1 << 4) 
#define ENTITY_MIB_ENTLOGICALCONTEXTENGINEID (1 << 5) 
#define ENTITY_MIB_ENTLOGICALCONTEXTNAME     (1 << 6) 

typedef struct {
    gint32   entLogicalIndex;                /* na */
    guchar   *entLogicalDescr;               /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTLOGICALDESCRMINLENGTH 0
#define ENTITY_MIB_ENTLOGICALDESCRMAXLENGTH 255
    guint16  _entLogicalDescrLength;
    guint32  *entLogicalType;                /* ro SNMPv2-TC::AutonomousType */
#define ENTITY_MIB_ENTLOGICALTYPEMINLENGTH 0
#define ENTITY_MIB_ENTLOGICALTYPEMAXLENGTH 128
    guint16  _entLogicalTypeLength;
    guchar   *entLogicalCommunity;           /* ro */
#define ENTITY_MIB_ENTLOGICALCOMMUNITYMINLENGTH 0
#define ENTITY_MIB_ENTLOGICALCOMMUNITYMAXLENGTH 255
    guint16  _entLogicalCommunityLength;
    guchar   *entLogicalTAddress;            /* ro SNMPv2-TC::TAddress */
#define ENTITY_MIB_ENTLOGICALTADDRESSMINLENGTH 1
#define ENTITY_MIB_ENTLOGICALTADDRESSMAXLENGTH 255
    guint16  _entLogicalTAddressLength;
    guint32  *entLogicalTDomain;             /* ro SNMPv2-TC::TDomain */
#define ENTITY_MIB_ENTLOGICALTDOMAINMINLENGTH 0
#define ENTITY_MIB_ENTLOGICALTDOMAINMAXLENGTH 128
    guint16  _entLogicalTDomainLength;
    guchar   *entLogicalContextEngineID;     /* ro ENTITY-MIB::SnmpEngineIdOrNone */
#define ENTITY_MIB_ENTLOGICALCONTEXTENGINEIDMINLENGTH 0
#define ENTITY_MIB_ENTLOGICALCONTEXTENGINEIDMAXLENGTH 32
    guint16  _entLogicalContextEngineIDLength;
    guchar   *entLogicalContextName;         /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_MIB_ENTLOGICALCONTEXTNAMEMINLENGTH 0
#define ENTITY_MIB_ENTLOGICALCONTEXTNAMEMAXLENGTH 255
    guint16  _entLogicalContextNameLength;
} entity_mib_entLogicalEntry_t;

extern void
entity_mib_get_entLogicalTable(GSnmpSession *s, entity_mib_entLogicalEntry_t ***entLogicalEntry, gint64 mask);

extern void
entity_mib_free_entLogicalTable(entity_mib_entLogicalEntry_t **entLogicalEntry);

extern entity_mib_entLogicalEntry_t *
entity_mib_new_entLogicalEntry(void);

extern void
entity_mib_get_entLogicalEntry(GSnmpSession *s, entity_mib_entLogicalEntry_t **entLogicalEntry, gint32 entLogicalIndex, gint64 mask);

extern void
entity_mib_free_entLogicalEntry(entity_mib_entLogicalEntry_t *entLogicalEntry);

/*
 * C type definitions for ENTITY-MIB::entLPMappingEntry.
 */

#define ENTITY_MIB_ENTLPPHYSICALINDEX (1 << 0) 

typedef struct {
    gint32   entLogicalIndex;         /* na */
    gint32   entLPPhysicalIndex;      /* ro ENTITY-MIB::PhysicalIndex */
} entity_mib_entLPMappingEntry_t;

extern void
entity_mib_get_entLPMappingTable(GSnmpSession *s, entity_mib_entLPMappingEntry_t ***entLPMappingEntry, gint64 mask);

extern void
entity_mib_free_entLPMappingTable(entity_mib_entLPMappingEntry_t **entLPMappingEntry);

extern entity_mib_entLPMappingEntry_t *
entity_mib_new_entLPMappingEntry(void);

extern void
entity_mib_get_entLPMappingEntry(GSnmpSession *s, entity_mib_entLPMappingEntry_t **entLPMappingEntry, gint32 entLogicalIndex, gint32 entLPPhysicalIndex, gint64 mask);

extern void
entity_mib_free_entLPMappingEntry(entity_mib_entLPMappingEntry_t *entLPMappingEntry);

/*
 * C type definitions for ENTITY-MIB::entAliasMappingEntry.
 */

#define ENTITY_MIB_ENTALIASMAPPINGIDENTIFIER (1 << 0) 

typedef struct {
    gint32   entPhysicalIndex;               /* na ENTITY-MIB::PhysicalIndex */
    gint32   entAliasLogicalIndexOrZero;     /* na */
    guint32  *entAliasMappingIdentifier;     /* ro SNMPv2-TC::RowPointer */
#define ENTITY_MIB_ENTALIASMAPPINGIDENTIFIERMINLENGTH 0
#define ENTITY_MIB_ENTALIASMAPPINGIDENTIFIERMAXLENGTH 128
    guint16  _entAliasMappingIdentifierLength;
} entity_mib_entAliasMappingEntry_t;

extern void
entity_mib_get_entAliasMappingTable(GSnmpSession *s, entity_mib_entAliasMappingEntry_t ***entAliasMappingEntry, gint64 mask);

extern void
entity_mib_free_entAliasMappingTable(entity_mib_entAliasMappingEntry_t **entAliasMappingEntry);

extern entity_mib_entAliasMappingEntry_t *
entity_mib_new_entAliasMappingEntry(void);

extern void
entity_mib_get_entAliasMappingEntry(GSnmpSession *s, entity_mib_entAliasMappingEntry_t **entAliasMappingEntry, gint32 entPhysicalIndex, gint32 entAliasLogicalIndexOrZero, gint64 mask);

extern void
entity_mib_free_entAliasMappingEntry(entity_mib_entAliasMappingEntry_t *entAliasMappingEntry);

/*
 * C type definitions for ENTITY-MIB::entPhysicalContainsEntry.
 */

#define ENTITY_MIB_ENTPHYSICALCHILDINDEX (1 << 0) 

typedef struct {
    gint32   entPhysicalIndex;           /* na ENTITY-MIB::PhysicalIndex */
    gint32   entPhysicalChildIndex;      /* ro ENTITY-MIB::PhysicalIndex */
} entity_mib_entPhysicalContainsEntry_t;

extern void
entity_mib_get_entPhysicalContainsTable(GSnmpSession *s, entity_mib_entPhysicalContainsEntry_t ***entPhysicalContainsEntry, gint64 mask);

extern void
entity_mib_free_entPhysicalContainsTable(entity_mib_entPhysicalContainsEntry_t **entPhysicalContainsEntry);

extern entity_mib_entPhysicalContainsEntry_t *
entity_mib_new_entPhysicalContainsEntry(void);

extern void
entity_mib_get_entPhysicalContainsEntry(GSnmpSession *s, entity_mib_entPhysicalContainsEntry_t **entPhysicalContainsEntry, gint32 entPhysicalIndex, gint32 entPhysicalChildIndex, gint64 mask);

extern void
entity_mib_free_entPhysicalContainsEntry(entity_mib_entPhysicalContainsEntry_t *entPhysicalContainsEntry);

/*
 * C type definitions for ENTITY-MIB::entityGeneral.
 */

#define ENTITY_MIB_ENTLASTCHANGETIME (1 << 0) 

typedef struct {
    guint32  *entLastChangeTime;     /* ro SNMPv2-TC::TimeStamp */
} entity_mib_entityGeneral_t;

extern entity_mib_entityGeneral_t *
entity_mib_new_entityGeneral(void);

extern void
entity_mib_get_entityGeneral(GSnmpSession *s, entity_mib_entityGeneral_t **entityGeneral, gint64 mask);

extern void
entity_mib_free_entityGeneral(entity_mib_entityGeneral_t *entityGeneral);


G_END_DECLS

#endif /* _ENTITY_MIB_H_ */
