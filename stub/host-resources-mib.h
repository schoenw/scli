/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli HOST-RESOURCES-MIB
 *
 * Derived from HOST-RESOURCES-MIB:
 *   This MIB is for use in managing host systems. The term
 *   `host' is construed to mean any computer that communicates
 *   with other similar computers attached to the internet and
 *   that is directly used by one or more human beings. Although
 *   this MIB does not necessarily apply to devices whose primary
 *   function is communications services (e.g., terminal servers,
 *   routers, bridges, monitoring equipment), such relevance is
 *   not explicitly precluded.  This MIB instruments attributes
 *   common to all internet hosts including, for example, both
 *   personal computers and systems that run variants of Unix.
 *
 * Revision 2000-03-06 00:00:
 *   Clarifications and bug fixes based on implementation
 *   experience.  This revision was also reformatted in the SMIv2
 *   format. The revisions made were:
 *   
 *   New RFC document standards:
 *      Added Copyright notice, updated introduction to SNMP
 *      Framework, updated references section, added reference to
 *      RFC 2119, and added a meaningful Security Considerations
 *      section.
 *   
 *   New IANA considerations section for registration of new types
 *   
 *   Conversion to new SMIv2 syntax for the following types and
 *   macros:
 *       Counter32, Integer32, Gauge32, MODULE-IDENTITY,
 *       OBJECT-TYPE, TEXTUAL-CONVENTION, OBJECT-IDENTITY,
 *       MODULE-COMPLIANCE, OBJECT-GROUP
 *   
 *   Used new Textual Conventions:
 *       TruthValue, DateAndTime, AutonomousType,
 *       InterfaceIndexOrZero
 *   
 *   Fixed typo in hrPrinterStatus.
 *   
 *   Added missing error bits to hrPrinterDetectedErrorState and
 *   clarified confusion resulting from suggested mappings to
 *   hrPrinterStatus.
 *   Clarified that size of objects of type
 *   InternationalDisplayString is number of octets, not number
 *   of encoded symbols.
 *   
 *   Clarified the use of the following objects based on
 *   implementation experience:
 *       hrSystemInitialLoadDevice, hrSystemInitialLoadParameters,
 *       hrMemorySize, hrStorageSize, hrStorageAllocationFailures,
 *       hrDeviceErrors, hrProcessorLoad, hrNetworkIfIndex,
 *       hrDiskStorageCapacity, hrSWRunStatus, hrSWRunPerfCPU,
 *       and hrSWInstalledDate.
 *   
 *   Clarified implementation technique for hrSWInstalledTable.
 *   
 *   Used new AUGMENTS clause for hrSWRunPerfTable.
 *   
 *   Added Internationalization Considerations section.
 *   
 *   This revision published as RFC2790.
 *
 * Revision 1999-10-20 22:00:
 *   The original version of this MIB, published as
 *   RFC1514.
 *
 * $Id$
 */

#ifndef _HOST_RESOURCES_MIB_H_
#define _HOST_RESOURCES_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define HOST_RESOURCES_MIB_HRDEVICESTATUS_UNKNOWN 1
#define HOST_RESOURCES_MIB_HRDEVICESTATUS_RUNNING 2
#define HOST_RESOURCES_MIB_HRDEVICESTATUS_WARNING 3
#define HOST_RESOURCES_MIB_HRDEVICESTATUS_TESTING 4
#define HOST_RESOURCES_MIB_HRDEVICESTATUS_DOWN    5

extern GNetSnmpEnum const host_resources_mib_enums_hrDeviceStatus[];

#define HOST_RESOURCES_MIB_HRPRINTERSTATUS_OTHER    1
#define HOST_RESOURCES_MIB_HRPRINTERSTATUS_UNKNOWN  2
#define HOST_RESOURCES_MIB_HRPRINTERSTATUS_IDLE     3
#define HOST_RESOURCES_MIB_HRPRINTERSTATUS_PRINTING 4
#define HOST_RESOURCES_MIB_HRPRINTERSTATUS_WARMUP   5

extern GNetSnmpEnum const host_resources_mib_enums_hrPrinterStatus[];

#define HOST_RESOURCES_MIB_HRDISKSTORAGEACCESS_READWRITE 1
#define HOST_RESOURCES_MIB_HRDISKSTORAGEACCESS_READONLY  2

extern GNetSnmpEnum const host_resources_mib_enums_hrDiskStorageAccess[];

#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_OTHER           1
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_UNKNOWN         2
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_HARDDISK        3
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_FLOPPYDISK      4
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_OPTICALDISKROM  5
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_OPTICALDISKWORM 6
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_OPTICALDISKRW   7
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA_RAMDISK         8

extern GNetSnmpEnum const host_resources_mib_enums_hrDiskStorageMedia[];

#define HOST_RESOURCES_MIB_HRFSACCESS_READWRITE 1
#define HOST_RESOURCES_MIB_HRFSACCESS_READONLY  2

extern GNetSnmpEnum const host_resources_mib_enums_hrFSAccess[];

#define HOST_RESOURCES_MIB_HRSWRUNTYPE_UNKNOWN         1
#define HOST_RESOURCES_MIB_HRSWRUNTYPE_OPERATINGSYSTEM 2
#define HOST_RESOURCES_MIB_HRSWRUNTYPE_DEVICEDRIVER    3
#define HOST_RESOURCES_MIB_HRSWRUNTYPE_APPLICATION     4

extern GNetSnmpEnum const host_resources_mib_enums_hrSWRunType[];

#define HOST_RESOURCES_MIB_HRSWRUNSTATUS_RUNNING     1
#define HOST_RESOURCES_MIB_HRSWRUNSTATUS_RUNNABLE    2
#define HOST_RESOURCES_MIB_HRSWRUNSTATUS_NOTRUNNABLE 3
#define HOST_RESOURCES_MIB_HRSWRUNSTATUS_INVALID     4

extern GNetSnmpEnum const host_resources_mib_enums_hrSWRunStatus[];

#define HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_UNKNOWN         1
#define HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_OPERATINGSYSTEM 2
#define HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_DEVICEDRIVER    3
#define HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE_APPLICATION     4

extern GNetSnmpEnum const host_resources_mib_enums_hrSWInstalledType[];


/*
 * C type definitions for HOST-RESOURCES-MIB::hrSystem.
 */

#define HOST_RESOURCES_MIB_HRSYSTEMUPTIME                (1 << 0) 
#define HOST_RESOURCES_MIB_HRSYSTEMDATE                  (1 << 1) 
#define HOST_RESOURCES_MIB_HRSYSTEMINITIALLOADDEVICE     (1 << 2) 
#define HOST_RESOURCES_MIB_HRSYSTEMINITIALLOADPARAMETERS (1 << 3) 
#define HOST_RESOURCES_MIB_HRSYSTEMNUMUSERS              (1 << 4) 
#define HOST_RESOURCES_MIB_HRSYSTEMPROCESSES             (1 << 5) 
#define HOST_RESOURCES_MIB_HRSYSTEMMAXPROCESSES          (1 << 6) 

typedef struct {
    guint32  *hrSystemUptime;                    /* ro SNMPv2-SMI::TimeTicks */
    guchar   *hrSystemDate;                      /* rw SNMPv2-TC::DateAndTime */
#define HOST_RESOURCES_MIB_HRSYSTEMDATEMINLENGTH 8
#define HOST_RESOURCES_MIB_HRSYSTEMDATEMAXLENGTH 11
    guint16  _hrSystemDateLength;
    gint32   *hrSystemInitialLoadDevice;         /* rw */
    guchar   *hrSystemInitialLoadParameters;     /* rw */
#define HOST_RESOURCES_MIB_HRSYSTEMINITIALLOADPARAMETERSMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSYSTEMINITIALLOADPARAMETERSMAXLENGTH 128
    guint16  _hrSystemInitialLoadParametersLength;
    guint32  *hrSystemNumUsers;                  /* ro SNMPv2-SMI::Gauge32 */
    guint32  *hrSystemProcesses;                 /* ro SNMPv2-SMI::Gauge32 */
    gint32   *hrSystemMaxProcesses;              /* ro */
} host_resources_mib_hrSystem_t;

extern host_resources_mib_hrSystem_t *
host_resources_mib_new_hrSystem(void);

extern void
host_resources_mib_get_hrSystem(GNetSnmp *s, host_resources_mib_hrSystem_t **hrSystem, gint64 mask);

extern void
host_resources_mib_set_hrSystem(GNetSnmp *s, host_resources_mib_hrSystem_t *hrSystem, gint64 mask);

extern void
host_resources_mib_free_hrSystem(host_resources_mib_hrSystem_t *hrSystem);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrStorage.
 */

#define HOST_RESOURCES_MIB_HRMEMORYSIZE (1 << 0) 

typedef struct {
    gint32   *hrMemorySize;     /* ro HOST-RESOURCES-MIB::KBytes [KBytes] */
} host_resources_mib_hrStorage_t;

extern host_resources_mib_hrStorage_t *
host_resources_mib_new_hrStorage(void);

extern void
host_resources_mib_get_hrStorage(GNetSnmp *s, host_resources_mib_hrStorage_t **hrStorage, gint64 mask);

extern void
host_resources_mib_free_hrStorage(host_resources_mib_hrStorage_t *hrStorage);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrStorageEntry.
 */

#define HOST_RESOURCES_MIB_HRSTORAGEINDEX              (1 << 0) 
#define HOST_RESOURCES_MIB_HRSTORAGETYPE               (1 << 1) 
#define HOST_RESOURCES_MIB_HRSTORAGEDESCR              (1 << 2) 
#define HOST_RESOURCES_MIB_HRSTORAGEALLOCATIONUNITS    (1 << 3) 
#define HOST_RESOURCES_MIB_HRSTORAGESIZE               (1 << 4) 
#define HOST_RESOURCES_MIB_HRSTORAGEUSED               (1 << 5) 
#define HOST_RESOURCES_MIB_HRSTORAGEALLOCATIONFAILURES (1 << 6) 

typedef struct {
    gint32   hrStorageIndex;                   /* ro */
    guint32  *hrStorageType;                   /* ro SNMPv2-TC::AutonomousType */
#define HOST_RESOURCES_MIB_HRSTORAGETYPEMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSTORAGETYPEMAXLENGTH 128
    guint16  _hrStorageTypeLength;
    guchar   *hrStorageDescr;                  /* ro SNMPv2-TC::DisplayString */
#define HOST_RESOURCES_MIB_HRSTORAGEDESCRMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSTORAGEDESCRMAXLENGTH 255
    guint16  _hrStorageDescrLength;
    gint32   *hrStorageAllocationUnits;        /* ro [Bytes] */
    gint32   *hrStorageSize;                   /* rw */
    gint32   *hrStorageUsed;                   /* ro */
    guint32  *hrStorageAllocationFailures;     /* ro SNMPv2-SMI::Counter32 */
} host_resources_mib_hrStorageEntry_t;

extern void
host_resources_mib_get_hrStorageTable(GNetSnmp *s, host_resources_mib_hrStorageEntry_t ***hrStorageEntry, gint64 mask);

extern void
host_resources_mib_free_hrStorageTable(host_resources_mib_hrStorageEntry_t **hrStorageEntry);

extern host_resources_mib_hrStorageEntry_t *
host_resources_mib_new_hrStorageEntry(void);

extern void
host_resources_mib_get_hrStorageEntry(GNetSnmp *s, host_resources_mib_hrStorageEntry_t **hrStorageEntry, gint32 hrStorageIndex, gint64 mask);

extern void
host_resources_mib_set_hrStorageEntry(GNetSnmp *s, host_resources_mib_hrStorageEntry_t *hrStorageEntry, gint64 mask);

extern void
host_resources_mib_free_hrStorageEntry(host_resources_mib_hrStorageEntry_t *hrStorageEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrDeviceEntry.
 */

#define HOST_RESOURCES_MIB_HRDEVICEINDEX  (1 << 0) 
#define HOST_RESOURCES_MIB_HRDEVICETYPE   (1 << 1) 
#define HOST_RESOURCES_MIB_HRDEVICEDESCR  (1 << 2) 
#define HOST_RESOURCES_MIB_HRDEVICEID     (1 << 3) 
#define HOST_RESOURCES_MIB_HRDEVICESTATUS (1 << 4) 
#define HOST_RESOURCES_MIB_HRDEVICEERRORS (1 << 5) 

typedef struct {
    gint32   hrDeviceIndex;       /* ro */
    guint32  *hrDeviceType;       /* ro SNMPv2-TC::AutonomousType */
#define HOST_RESOURCES_MIB_HRDEVICETYPEMINLENGTH 0
#define HOST_RESOURCES_MIB_HRDEVICETYPEMAXLENGTH 128
    guint16  _hrDeviceTypeLength;
    guchar   *hrDeviceDescr;      /* ro */
#define HOST_RESOURCES_MIB_HRDEVICEDESCRMINLENGTH 0
#define HOST_RESOURCES_MIB_HRDEVICEDESCRMAXLENGTH 64
    guint16  _hrDeviceDescrLength;
    guint32  *hrDeviceID;         /* ro HOST-RESOURCES-MIB::ProductID */
#define HOST_RESOURCES_MIB_HRDEVICEIDMINLENGTH 0
#define HOST_RESOURCES_MIB_HRDEVICEIDMAXLENGTH 128
    guint16  _hrDeviceIDLength;
    gint32   *hrDeviceStatus;     /* ro */
    guint32  *hrDeviceErrors;     /* ro SNMPv2-SMI::Counter32 */
} host_resources_mib_hrDeviceEntry_t;

extern void
host_resources_mib_get_hrDeviceTable(GNetSnmp *s, host_resources_mib_hrDeviceEntry_t ***hrDeviceEntry, gint64 mask);

extern void
host_resources_mib_free_hrDeviceTable(host_resources_mib_hrDeviceEntry_t **hrDeviceEntry);

extern host_resources_mib_hrDeviceEntry_t *
host_resources_mib_new_hrDeviceEntry(void);

extern void
host_resources_mib_get_hrDeviceEntry(GNetSnmp *s, host_resources_mib_hrDeviceEntry_t **hrDeviceEntry, gint32 hrDeviceIndex, gint64 mask);

extern void
host_resources_mib_free_hrDeviceEntry(host_resources_mib_hrDeviceEntry_t *hrDeviceEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrProcessorEntry.
 */

#define HOST_RESOURCES_MIB_HRPROCESSORFRWID (1 << 0) 
#define HOST_RESOURCES_MIB_HRPROCESSORLOAD  (1 << 1) 

typedef struct {
    gint32   hrDeviceIndex;         /* ro */
    guint32  *hrProcessorFrwID;     /* ro HOST-RESOURCES-MIB::ProductID */
#define HOST_RESOURCES_MIB_HRPROCESSORFRWIDMINLENGTH 0
#define HOST_RESOURCES_MIB_HRPROCESSORFRWIDMAXLENGTH 128
    guint16  _hrProcessorFrwIDLength;
    gint32   *hrProcessorLoad;      /* ro */
} host_resources_mib_hrProcessorEntry_t;

extern void
host_resources_mib_get_hrProcessorTable(GNetSnmp *s, host_resources_mib_hrProcessorEntry_t ***hrProcessorEntry, gint64 mask);

extern void
host_resources_mib_free_hrProcessorTable(host_resources_mib_hrProcessorEntry_t **hrProcessorEntry);

extern host_resources_mib_hrProcessorEntry_t *
host_resources_mib_new_hrProcessorEntry(void);

extern void
host_resources_mib_get_hrProcessorEntry(GNetSnmp *s, host_resources_mib_hrProcessorEntry_t **hrProcessorEntry, gint32 hrDeviceIndex, gint64 mask);

extern void
host_resources_mib_free_hrProcessorEntry(host_resources_mib_hrProcessorEntry_t *hrProcessorEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrNetworkEntry.
 */

#define HOST_RESOURCES_MIB_HRNETWORKIFINDEX (1 << 0) 

typedef struct {
    gint32   hrDeviceIndex;         /* ro */
    gint32   *hrNetworkIfIndex;     /* ro IF-MIB::InterfaceIndexOrZero */
} host_resources_mib_hrNetworkEntry_t;

extern void
host_resources_mib_get_hrNetworkTable(GNetSnmp *s, host_resources_mib_hrNetworkEntry_t ***hrNetworkEntry, gint64 mask);

extern void
host_resources_mib_free_hrNetworkTable(host_resources_mib_hrNetworkEntry_t **hrNetworkEntry);

extern host_resources_mib_hrNetworkEntry_t *
host_resources_mib_new_hrNetworkEntry(void);

extern void
host_resources_mib_get_hrNetworkEntry(GNetSnmp *s, host_resources_mib_hrNetworkEntry_t **hrNetworkEntry, gint32 hrDeviceIndex, gint64 mask);

extern void
host_resources_mib_free_hrNetworkEntry(host_resources_mib_hrNetworkEntry_t *hrNetworkEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrPrinterEntry.
 */

#define HOST_RESOURCES_MIB_HRPRINTERSTATUS             (1 << 0) 
#define HOST_RESOURCES_MIB_HRPRINTERDETECTEDERRORSTATE (1 << 1) 

typedef struct {
    gint32   hrDeviceIndex;                    /* ro */
    gint32   *hrPrinterStatus;                 /* ro */
    guchar   *hrPrinterDetectedErrorState;     /* ro OctetString */
#define HOST_RESOURCES_MIB_HRPRINTERDETECTEDERRORSTATEMINLENGTH 0
#define HOST_RESOURCES_MIB_HRPRINTERDETECTEDERRORSTATEMAXLENGTH 65535
    guint16  _hrPrinterDetectedErrorStateLength;
} host_resources_mib_hrPrinterEntry_t;

extern void
host_resources_mib_get_hrPrinterTable(GNetSnmp *s, host_resources_mib_hrPrinterEntry_t ***hrPrinterEntry, gint64 mask);

extern void
host_resources_mib_free_hrPrinterTable(host_resources_mib_hrPrinterEntry_t **hrPrinterEntry);

extern host_resources_mib_hrPrinterEntry_t *
host_resources_mib_new_hrPrinterEntry(void);

extern void
host_resources_mib_get_hrPrinterEntry(GNetSnmp *s, host_resources_mib_hrPrinterEntry_t **hrPrinterEntry, gint32 hrDeviceIndex, gint64 mask);

extern void
host_resources_mib_free_hrPrinterEntry(host_resources_mib_hrPrinterEntry_t *hrPrinterEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrDiskStorageEntry.
 */

#define HOST_RESOURCES_MIB_HRDISKSTORAGEACCESS    (1 << 0) 
#define HOST_RESOURCES_MIB_HRDISKSTORAGEMEDIA     (1 << 1) 
#define HOST_RESOURCES_MIB_HRDISKSTORAGEREMOVEBLE (1 << 2) 
#define HOST_RESOURCES_MIB_HRDISKSTORAGECAPACITY  (1 << 3) 

typedef struct {
    gint32   hrDeviceIndex;               /* ro */
    gint32   *hrDiskStorageAccess;        /* ro */
    gint32   *hrDiskStorageMedia;         /* ro */
    gint32   *hrDiskStorageRemoveble;     /* ro SNMPv2-TC::TruthValue */
    gint32   *hrDiskStorageCapacity;      /* ro HOST-RESOURCES-MIB::KBytes [KBytes] */
} host_resources_mib_hrDiskStorageEntry_t;

extern void
host_resources_mib_get_hrDiskStorageTable(GNetSnmp *s, host_resources_mib_hrDiskStorageEntry_t ***hrDiskStorageEntry, gint64 mask);

extern void
host_resources_mib_free_hrDiskStorageTable(host_resources_mib_hrDiskStorageEntry_t **hrDiskStorageEntry);

extern host_resources_mib_hrDiskStorageEntry_t *
host_resources_mib_new_hrDiskStorageEntry(void);

extern void
host_resources_mib_get_hrDiskStorageEntry(GNetSnmp *s, host_resources_mib_hrDiskStorageEntry_t **hrDiskStorageEntry, gint32 hrDeviceIndex, gint64 mask);

extern void
host_resources_mib_free_hrDiskStorageEntry(host_resources_mib_hrDiskStorageEntry_t *hrDiskStorageEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrPartitionEntry.
 */

#define HOST_RESOURCES_MIB_HRPARTITIONINDEX   (1 << 0) 
#define HOST_RESOURCES_MIB_HRPARTITIONLABEL   (1 << 1) 
#define HOST_RESOURCES_MIB_HRPARTITIONID      (1 << 2) 
#define HOST_RESOURCES_MIB_HRPARTITIONSIZE    (1 << 3) 
#define HOST_RESOURCES_MIB_HRPARTITIONFSINDEX (1 << 4) 

typedef struct {
    gint32   hrDeviceIndex;           /* ro */
    gint32   hrPartitionIndex;        /* ro */
    guchar   *hrPartitionLabel;       /* ro */
#define HOST_RESOURCES_MIB_HRPARTITIONLABELMINLENGTH 0
#define HOST_RESOURCES_MIB_HRPARTITIONLABELMAXLENGTH 128
    guint16  _hrPartitionLabelLength;
    guchar   *hrPartitionID;          /* ro OctetString */
#define HOST_RESOURCES_MIB_HRPARTITIONIDMINLENGTH 0
#define HOST_RESOURCES_MIB_HRPARTITIONIDMAXLENGTH 65535
    guint16  _hrPartitionIDLength;
    gint32   *hrPartitionSize;        /* ro HOST-RESOURCES-MIB::KBytes [KBytes] */
    gint32   *hrPartitionFSIndex;     /* ro */
} host_resources_mib_hrPartitionEntry_t;

extern void
host_resources_mib_get_hrPartitionTable(GNetSnmp *s, host_resources_mib_hrPartitionEntry_t ***hrPartitionEntry, gint64 mask);

extern void
host_resources_mib_free_hrPartitionTable(host_resources_mib_hrPartitionEntry_t **hrPartitionEntry);

extern host_resources_mib_hrPartitionEntry_t *
host_resources_mib_new_hrPartitionEntry(void);

extern void
host_resources_mib_get_hrPartitionEntry(GNetSnmp *s, host_resources_mib_hrPartitionEntry_t **hrPartitionEntry, gint32 hrDeviceIndex, gint32 hrPartitionIndex, gint64 mask);

extern void
host_resources_mib_free_hrPartitionEntry(host_resources_mib_hrPartitionEntry_t *hrPartitionEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrFSEntry.
 */

#define HOST_RESOURCES_MIB_HRFSINDEX                 (1 << 0) 
#define HOST_RESOURCES_MIB_HRFSMOUNTPOINT            (1 << 1) 
#define HOST_RESOURCES_MIB_HRFSREMOTEMOUNTPOINT      (1 << 2) 
#define HOST_RESOURCES_MIB_HRFSTYPE                  (1 << 3) 
#define HOST_RESOURCES_MIB_HRFSACCESS                (1 << 4) 
#define HOST_RESOURCES_MIB_HRFSBOOTABLE              (1 << 5) 
#define HOST_RESOURCES_MIB_HRFSSTORAGEINDEX          (1 << 6) 
#define HOST_RESOURCES_MIB_HRFSLASTFULLBACKUPDATE    (1 << 7) 
#define HOST_RESOURCES_MIB_HRFSLASTPARTIALBACKUPDATE (1 << 8) 

typedef struct {
    gint32   hrFSIndex;                      /* ro */
    guchar   *hrFSMountPoint;                /* ro */
#define HOST_RESOURCES_MIB_HRFSMOUNTPOINTMINLENGTH 0
#define HOST_RESOURCES_MIB_HRFSMOUNTPOINTMAXLENGTH 128
    guint16  _hrFSMountPointLength;
    guchar   *hrFSRemoteMountPoint;          /* ro */
#define HOST_RESOURCES_MIB_HRFSREMOTEMOUNTPOINTMINLENGTH 0
#define HOST_RESOURCES_MIB_HRFSREMOTEMOUNTPOINTMAXLENGTH 128
    guint16  _hrFSRemoteMountPointLength;
    guint32  *hrFSType;                      /* ro SNMPv2-TC::AutonomousType */
#define HOST_RESOURCES_MIB_HRFSTYPEMINLENGTH 0
#define HOST_RESOURCES_MIB_HRFSTYPEMAXLENGTH 128
    guint16  _hrFSTypeLength;
    gint32   *hrFSAccess;                    /* ro */
    gint32   *hrFSBootable;                  /* ro SNMPv2-TC::TruthValue */
    gint32   *hrFSStorageIndex;              /* ro */
    guchar   *hrFSLastFullBackupDate;        /* rw SNMPv2-TC::DateAndTime */
#define HOST_RESOURCES_MIB_HRFSLASTFULLBACKUPDATEMINLENGTH 8
#define HOST_RESOURCES_MIB_HRFSLASTFULLBACKUPDATEMAXLENGTH 11
    guint16  _hrFSLastFullBackupDateLength;
    guchar   *hrFSLastPartialBackupDate;     /* rw SNMPv2-TC::DateAndTime */
#define HOST_RESOURCES_MIB_HRFSLASTPARTIALBACKUPDATEMINLENGTH 8
#define HOST_RESOURCES_MIB_HRFSLASTPARTIALBACKUPDATEMAXLENGTH 11
    guint16  _hrFSLastPartialBackupDateLength;
} host_resources_mib_hrFSEntry_t;

extern void
host_resources_mib_get_hrFSTable(GNetSnmp *s, host_resources_mib_hrFSEntry_t ***hrFSEntry, gint64 mask);

extern void
host_resources_mib_free_hrFSTable(host_resources_mib_hrFSEntry_t **hrFSEntry);

extern host_resources_mib_hrFSEntry_t *
host_resources_mib_new_hrFSEntry(void);

extern void
host_resources_mib_get_hrFSEntry(GNetSnmp *s, host_resources_mib_hrFSEntry_t **hrFSEntry, gint32 hrFSIndex, gint64 mask);

extern void
host_resources_mib_set_hrFSEntry(GNetSnmp *s, host_resources_mib_hrFSEntry_t *hrFSEntry, gint64 mask);

extern void
host_resources_mib_free_hrFSEntry(host_resources_mib_hrFSEntry_t *hrFSEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWRun.
 */

#define HOST_RESOURCES_MIB_HRSWOSINDEX (1 << 0) 

typedef struct {
    gint32   *hrSWOSIndex;     /* ro */
} host_resources_mib_hrSWRun_t;

extern host_resources_mib_hrSWRun_t *
host_resources_mib_new_hrSWRun(void);

extern void
host_resources_mib_get_hrSWRun(GNetSnmp *s, host_resources_mib_hrSWRun_t **hrSWRun, gint64 mask);

extern void
host_resources_mib_free_hrSWRun(host_resources_mib_hrSWRun_t *hrSWRun);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWRunEntry.
 */

#define HOST_RESOURCES_MIB_HRSWRUNINDEX      (1 << 0) 
#define HOST_RESOURCES_MIB_HRSWRUNNAME       (1 << 1) 
#define HOST_RESOURCES_MIB_HRSWRUNID         (1 << 2) 
#define HOST_RESOURCES_MIB_HRSWRUNPATH       (1 << 3) 
#define HOST_RESOURCES_MIB_HRSWRUNPARAMETERS (1 << 4) 
#define HOST_RESOURCES_MIB_HRSWRUNTYPE       (1 << 5) 
#define HOST_RESOURCES_MIB_HRSWRUNSTATUS     (1 << 6) 

typedef struct {
    gint32   hrSWRunIndex;           /* ro */
    guchar   *hrSWRunName;           /* ro */
#define HOST_RESOURCES_MIB_HRSWRUNNAMEMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSWRUNNAMEMAXLENGTH 64
    guint16  _hrSWRunNameLength;
    guint32  *hrSWRunID;             /* ro HOST-RESOURCES-MIB::ProductID */
#define HOST_RESOURCES_MIB_HRSWRUNIDMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSWRUNIDMAXLENGTH 128
    guint16  _hrSWRunIDLength;
    guchar   *hrSWRunPath;           /* ro */
#define HOST_RESOURCES_MIB_HRSWRUNPATHMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSWRUNPATHMAXLENGTH 128
    guint16  _hrSWRunPathLength;
    guchar   *hrSWRunParameters;     /* ro */
#define HOST_RESOURCES_MIB_HRSWRUNPARAMETERSMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSWRUNPARAMETERSMAXLENGTH 128
    guint16  _hrSWRunParametersLength;
    gint32   *hrSWRunType;           /* ro */
    gint32   *hrSWRunStatus;         /* rw */
} host_resources_mib_hrSWRunEntry_t;

extern void
host_resources_mib_get_hrSWRunTable(GNetSnmp *s, host_resources_mib_hrSWRunEntry_t ***hrSWRunEntry, gint64 mask);

extern void
host_resources_mib_free_hrSWRunTable(host_resources_mib_hrSWRunEntry_t **hrSWRunEntry);

extern host_resources_mib_hrSWRunEntry_t *
host_resources_mib_new_hrSWRunEntry(void);

extern void
host_resources_mib_get_hrSWRunEntry(GNetSnmp *s, host_resources_mib_hrSWRunEntry_t **hrSWRunEntry, gint32 hrSWRunIndex, gint64 mask);

extern void
host_resources_mib_set_hrSWRunEntry(GNetSnmp *s, host_resources_mib_hrSWRunEntry_t *hrSWRunEntry, gint64 mask);

extern void
host_resources_mib_free_hrSWRunEntry(host_resources_mib_hrSWRunEntry_t *hrSWRunEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWRunPerfEntry.
 */

#define HOST_RESOURCES_MIB_HRSWRUNPERFCPU (1 << 0) 
#define HOST_RESOURCES_MIB_HRSWRUNPERFMEM (1 << 1) 

typedef struct {
    gint32   hrSWRunIndex;        /* ro */
    gint32   *hrSWRunPerfCPU;     /* ro */
    gint32   *hrSWRunPerfMem;     /* ro HOST-RESOURCES-MIB::KBytes [KBytes] */
} host_resources_mib_hrSWRunPerfEntry_t;

extern void
host_resources_mib_get_hrSWRunPerfTable(GNetSnmp *s, host_resources_mib_hrSWRunPerfEntry_t ***hrSWRunPerfEntry, gint64 mask);

extern void
host_resources_mib_free_hrSWRunPerfTable(host_resources_mib_hrSWRunPerfEntry_t **hrSWRunPerfEntry);

extern host_resources_mib_hrSWRunPerfEntry_t *
host_resources_mib_new_hrSWRunPerfEntry(void);

extern void
host_resources_mib_get_hrSWRunPerfEntry(GNetSnmp *s, host_resources_mib_hrSWRunPerfEntry_t **hrSWRunPerfEntry, gint32 hrSWRunIndex, gint64 mask);

extern void
host_resources_mib_free_hrSWRunPerfEntry(host_resources_mib_hrSWRunPerfEntry_t *hrSWRunPerfEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWInstalled.
 */

#define HOST_RESOURCES_MIB_HRSWINSTALLEDLASTCHANGE     (1 << 0) 
#define HOST_RESOURCES_MIB_HRSWINSTALLEDLASTUPDATETIME (1 << 1) 

typedef struct {
    guint32  *hrSWInstalledLastChange;         /* ro SNMPv2-SMI::TimeTicks */
    guint32  *hrSWInstalledLastUpdateTime;     /* ro SNMPv2-SMI::TimeTicks */
} host_resources_mib_hrSWInstalled_t;

extern host_resources_mib_hrSWInstalled_t *
host_resources_mib_new_hrSWInstalled(void);

extern void
host_resources_mib_get_hrSWInstalled(GNetSnmp *s, host_resources_mib_hrSWInstalled_t **hrSWInstalled, gint64 mask);

extern void
host_resources_mib_free_hrSWInstalled(host_resources_mib_hrSWInstalled_t *hrSWInstalled);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWInstalledEntry.
 */

#define HOST_RESOURCES_MIB_HRSWINSTALLEDINDEX (1 << 0) 
#define HOST_RESOURCES_MIB_HRSWINSTALLEDNAME  (1 << 1) 
#define HOST_RESOURCES_MIB_HRSWINSTALLEDID    (1 << 2) 
#define HOST_RESOURCES_MIB_HRSWINSTALLEDTYPE  (1 << 3) 
#define HOST_RESOURCES_MIB_HRSWINSTALLEDDATE  (1 << 4) 

typedef struct {
    gint32   hrSWInstalledIndex;      /* ro */
    guchar   *hrSWInstalledName;      /* ro */
#define HOST_RESOURCES_MIB_HRSWINSTALLEDNAMEMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSWINSTALLEDNAMEMAXLENGTH 64
    guint16  _hrSWInstalledNameLength;
    guint32  *hrSWInstalledID;        /* ro HOST-RESOURCES-MIB::ProductID */
#define HOST_RESOURCES_MIB_HRSWINSTALLEDIDMINLENGTH 0
#define HOST_RESOURCES_MIB_HRSWINSTALLEDIDMAXLENGTH 128
    guint16  _hrSWInstalledIDLength;
    gint32   *hrSWInstalledType;      /* ro */
    guchar   *hrSWInstalledDate;      /* ro SNMPv2-TC::DateAndTime */
#define HOST_RESOURCES_MIB_HRSWINSTALLEDDATEMINLENGTH 8
#define HOST_RESOURCES_MIB_HRSWINSTALLEDDATEMAXLENGTH 11
    guint16  _hrSWInstalledDateLength;
} host_resources_mib_hrSWInstalledEntry_t;

extern void
host_resources_mib_get_hrSWInstalledTable(GNetSnmp *s, host_resources_mib_hrSWInstalledEntry_t ***hrSWInstalledEntry, gint64 mask);

extern void
host_resources_mib_free_hrSWInstalledTable(host_resources_mib_hrSWInstalledEntry_t **hrSWInstalledEntry);

extern host_resources_mib_hrSWInstalledEntry_t *
host_resources_mib_new_hrSWInstalledEntry(void);

extern void
host_resources_mib_get_hrSWInstalledEntry(GNetSnmp *s, host_resources_mib_hrSWInstalledEntry_t **hrSWInstalledEntry, gint32 hrSWInstalledIndex, gint64 mask);

extern void
host_resources_mib_free_hrSWInstalledEntry(host_resources_mib_hrSWInstalledEntry_t *hrSWInstalledEntry);


G_END_DECLS

#endif /* _HOST_RESOURCES_MIB_H_ */
