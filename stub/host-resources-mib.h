/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from HOST-RESOURCES-MIB revision 2000-03-06 00:00.
 *
 * $Id$
 */

#ifndef _HOST_RESOURCES_MIB_H_
#define _HOST_RESOURCES_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

extern stls_table_t host_resources_mib_enums_hrDeviceStatus[];
extern stls_table_t host_resources_mib_enums_hrPrinterStatus[];
extern stls_table_t host_resources_mib_enums_hrDiskStorageAccess[];
extern stls_table_t host_resources_mib_enums_hrDiskStorageMedia[];
extern stls_table_t host_resources_mib_enums_hrDiskStorageRemoveble[];
extern stls_table_t host_resources_mib_enums_hrFSAccess[];
extern stls_table_t host_resources_mib_enums_hrFSBootable[];
extern stls_table_t host_resources_mib_enums_hrSWRunType[];
extern stls_table_t host_resources_mib_enums_hrSWRunStatus[];
extern stls_table_t host_resources_mib_enums_hrSWInstalledType[];

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSystem.
 */

typedef struct hrSystem {
    guint32  *hrSystemUptime;
    guchar   *hrSystemDate;
    gsize    _hrSystemDateLength;
    gint32   *hrSystemInitialLoadDevice;
    guchar   *hrSystemInitialLoadParameters;
    gsize    _hrSystemInitialLoadParametersLength;
    guint32  *hrSystemNumUsers;
    guint32  *hrSystemProcesses;
    gint32   *hrSystemMaxProcesses;
} hrSystem_t;

extern hrSystem_t *
host_resources_mib_new_hrSystem();

extern int
host_resources_mib_get_hrSystem(host_snmp *s, hrSystem_t **hrSystem);

extern int
host_resources_mib_set_hrSystem(host_snmp *s, hrSystem_t *hrSystem);

extern void
host_resources_mib_free_hrSystem(hrSystem_t *hrSystem);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrStorage.
 */

typedef struct hrStorage {
    gint32   *hrMemorySize;
} hrStorage_t;

extern hrStorage_t *
host_resources_mib_new_hrStorage();

extern int
host_resources_mib_get_hrStorage(host_snmp *s, hrStorage_t **hrStorage);

extern void
host_resources_mib_free_hrStorage(hrStorage_t *hrStorage);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrStorageEntry.
 */

typedef struct hrStorageEntry {
    gint32   hrStorageIndex;
    guint32  *hrStorageType;
    gsize    _hrStorageTypeLength;
    guchar   *hrStorageDescr;
    gsize    _hrStorageDescrLength;
    gint32   *hrStorageAllocationUnits;
    gint32   *hrStorageSize;
    gint32   *hrStorageUsed;
    guint32  *hrStorageAllocationFailures;
} hrStorageEntry_t;

extern int
host_resources_mib_get_hrStorageTable(host_snmp *s, hrStorageEntry_t ***hrStorageEntry);

extern void
host_resources_mib_free_hrStorageTable(hrStorageEntry_t **hrStorageEntry);

extern hrStorageEntry_t *
host_resources_mib_new_hrStorageEntry();

extern int
host_resources_mib_get_hrStorageEntry(host_snmp *s, hrStorageEntry_t **hrStorageEntry);

extern int
host_resources_mib_set_hrStorageEntry(host_snmp *s, hrStorageEntry_t *hrStorageEntry);

extern void
host_resources_mib_free_hrStorageEntry(hrStorageEntry_t *hrStorageEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrDeviceEntry.
 */

typedef struct hrDeviceEntry {
    gint32   hrDeviceIndex;
    guint32  *hrDeviceType;
    gsize    _hrDeviceTypeLength;
    guchar   *hrDeviceDescr;
    gsize    _hrDeviceDescrLength;
    guint32  *hrDeviceID;
    gsize    _hrDeviceIDLength;
    gint32   *hrDeviceStatus;
    guint32  *hrDeviceErrors;
} hrDeviceEntry_t;

extern int
host_resources_mib_get_hrDeviceTable(host_snmp *s, hrDeviceEntry_t ***hrDeviceEntry);

extern void
host_resources_mib_free_hrDeviceTable(hrDeviceEntry_t **hrDeviceEntry);

extern hrDeviceEntry_t *
host_resources_mib_new_hrDeviceEntry();

extern int
host_resources_mib_get_hrDeviceEntry(host_snmp *s, hrDeviceEntry_t **hrDeviceEntry);

extern void
host_resources_mib_free_hrDeviceEntry(hrDeviceEntry_t *hrDeviceEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrProcessorEntry.
 */

typedef struct hrProcessorEntry {
    gint32   hrDeviceIndex;
    guint32  *hrProcessorFrwID;
    gsize    _hrProcessorFrwIDLength;
    gint32   *hrProcessorLoad;
} hrProcessorEntry_t;

extern int
host_resources_mib_get_hrProcessorTable(host_snmp *s, hrProcessorEntry_t ***hrProcessorEntry);

extern void
host_resources_mib_free_hrProcessorTable(hrProcessorEntry_t **hrProcessorEntry);

extern hrProcessorEntry_t *
host_resources_mib_new_hrProcessorEntry();

extern int
host_resources_mib_get_hrProcessorEntry(host_snmp *s, hrProcessorEntry_t **hrProcessorEntry);

extern void
host_resources_mib_free_hrProcessorEntry(hrProcessorEntry_t *hrProcessorEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrNetworkEntry.
 */

typedef struct hrNetworkEntry {
    gint32   hrDeviceIndex;
    gint32   *hrNetworkIfIndex;
} hrNetworkEntry_t;

extern int
host_resources_mib_get_hrNetworkTable(host_snmp *s, hrNetworkEntry_t ***hrNetworkEntry);

extern void
host_resources_mib_free_hrNetworkTable(hrNetworkEntry_t **hrNetworkEntry);

extern hrNetworkEntry_t *
host_resources_mib_new_hrNetworkEntry();

extern int
host_resources_mib_get_hrNetworkEntry(host_snmp *s, hrNetworkEntry_t **hrNetworkEntry);

extern void
host_resources_mib_free_hrNetworkEntry(hrNetworkEntry_t *hrNetworkEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrPrinterEntry.
 */

typedef struct hrPrinterEntry {
    gint32   hrDeviceIndex;
    gint32   *hrPrinterStatus;
    guchar   *hrPrinterDetectedErrorState;
    gsize    _hrPrinterDetectedErrorStateLength;
} hrPrinterEntry_t;

extern int
host_resources_mib_get_hrPrinterTable(host_snmp *s, hrPrinterEntry_t ***hrPrinterEntry);

extern void
host_resources_mib_free_hrPrinterTable(hrPrinterEntry_t **hrPrinterEntry);

extern hrPrinterEntry_t *
host_resources_mib_new_hrPrinterEntry();

extern int
host_resources_mib_get_hrPrinterEntry(host_snmp *s, hrPrinterEntry_t **hrPrinterEntry);

extern void
host_resources_mib_free_hrPrinterEntry(hrPrinterEntry_t *hrPrinterEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrDiskStorageEntry.
 */

typedef struct hrDiskStorageEntry {
    gint32   hrDeviceIndex;
    gint32   *hrDiskStorageAccess;
    gint32   *hrDiskStorageMedia;
    gint32   *hrDiskStorageRemoveble;
    gint32   *hrDiskStorageCapacity;
} hrDiskStorageEntry_t;

extern int
host_resources_mib_get_hrDiskStorageTable(host_snmp *s, hrDiskStorageEntry_t ***hrDiskStorageEntry);

extern void
host_resources_mib_free_hrDiskStorageTable(hrDiskStorageEntry_t **hrDiskStorageEntry);

extern hrDiskStorageEntry_t *
host_resources_mib_new_hrDiskStorageEntry();

extern int
host_resources_mib_get_hrDiskStorageEntry(host_snmp *s, hrDiskStorageEntry_t **hrDiskStorageEntry);

extern void
host_resources_mib_free_hrDiskStorageEntry(hrDiskStorageEntry_t *hrDiskStorageEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrPartitionEntry.
 */

typedef struct hrPartitionEntry {
    gint32   hrDeviceIndex;
    gint32   hrPartitionIndex;
    guchar   *hrPartitionLabel;
    gsize    _hrPartitionLabelLength;
    guchar   *hrPartitionID;
    gsize    _hrPartitionIDLength;
    gint32   *hrPartitionSize;
    gint32   *hrPartitionFSIndex;
} hrPartitionEntry_t;

extern int
host_resources_mib_get_hrPartitionTable(host_snmp *s, hrPartitionEntry_t ***hrPartitionEntry);

extern void
host_resources_mib_free_hrPartitionTable(hrPartitionEntry_t **hrPartitionEntry);

extern hrPartitionEntry_t *
host_resources_mib_new_hrPartitionEntry();

extern int
host_resources_mib_get_hrPartitionEntry(host_snmp *s, hrPartitionEntry_t **hrPartitionEntry);

extern void
host_resources_mib_free_hrPartitionEntry(hrPartitionEntry_t *hrPartitionEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrFSEntry.
 */

typedef struct hrFSEntry {
    gint32   hrFSIndex;
    guchar   *hrFSMountPoint;
    gsize    _hrFSMountPointLength;
    guchar   *hrFSRemoteMountPoint;
    gsize    _hrFSRemoteMountPointLength;
    guint32  *hrFSType;
    gsize    _hrFSTypeLength;
    gint32   *hrFSAccess;
    gint32   *hrFSBootable;
    gint32   *hrFSStorageIndex;
    guchar   *hrFSLastFullBackupDate;
    gsize    _hrFSLastFullBackupDateLength;
    guchar   *hrFSLastPartialBackupDate;
    gsize    _hrFSLastPartialBackupDateLength;
} hrFSEntry_t;

extern int
host_resources_mib_get_hrFSTable(host_snmp *s, hrFSEntry_t ***hrFSEntry);

extern void
host_resources_mib_free_hrFSTable(hrFSEntry_t **hrFSEntry);

extern hrFSEntry_t *
host_resources_mib_new_hrFSEntry();

extern int
host_resources_mib_get_hrFSEntry(host_snmp *s, hrFSEntry_t **hrFSEntry);

extern int
host_resources_mib_set_hrFSEntry(host_snmp *s, hrFSEntry_t *hrFSEntry);

extern void
host_resources_mib_free_hrFSEntry(hrFSEntry_t *hrFSEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWRun.
 */

typedef struct hrSWRun {
    gint32   *hrSWOSIndex;
} hrSWRun_t;

extern hrSWRun_t *
host_resources_mib_new_hrSWRun();

extern int
host_resources_mib_get_hrSWRun(host_snmp *s, hrSWRun_t **hrSWRun);

extern void
host_resources_mib_free_hrSWRun(hrSWRun_t *hrSWRun);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWRunEntry.
 */

typedef struct hrSWRunEntry {
    gint32   hrSWRunIndex;
    guchar   *hrSWRunName;
    gsize    _hrSWRunNameLength;
    guint32  *hrSWRunID;
    gsize    _hrSWRunIDLength;
    guchar   *hrSWRunPath;
    gsize    _hrSWRunPathLength;
    guchar   *hrSWRunParameters;
    gsize    _hrSWRunParametersLength;
    gint32   *hrSWRunType;
    gint32   *hrSWRunStatus;
} hrSWRunEntry_t;

extern int
host_resources_mib_get_hrSWRunTable(host_snmp *s, hrSWRunEntry_t ***hrSWRunEntry);

extern void
host_resources_mib_free_hrSWRunTable(hrSWRunEntry_t **hrSWRunEntry);

extern hrSWRunEntry_t *
host_resources_mib_new_hrSWRunEntry();

extern int
host_resources_mib_get_hrSWRunEntry(host_snmp *s, hrSWRunEntry_t **hrSWRunEntry);

extern int
host_resources_mib_set_hrSWRunEntry(host_snmp *s, hrSWRunEntry_t *hrSWRunEntry);

extern void
host_resources_mib_free_hrSWRunEntry(hrSWRunEntry_t *hrSWRunEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWRunPerfEntry.
 */

typedef struct hrSWRunPerfEntry {
    gint32   hrSWRunIndex;
    gint32   *hrSWRunPerfCPU;
    gint32   *hrSWRunPerfMem;
} hrSWRunPerfEntry_t;

extern int
host_resources_mib_get_hrSWRunPerfTable(host_snmp *s, hrSWRunPerfEntry_t ***hrSWRunPerfEntry);

extern void
host_resources_mib_free_hrSWRunPerfTable(hrSWRunPerfEntry_t **hrSWRunPerfEntry);

extern hrSWRunPerfEntry_t *
host_resources_mib_new_hrSWRunPerfEntry();

extern int
host_resources_mib_get_hrSWRunPerfEntry(host_snmp *s, hrSWRunPerfEntry_t **hrSWRunPerfEntry);

extern void
host_resources_mib_free_hrSWRunPerfEntry(hrSWRunPerfEntry_t *hrSWRunPerfEntry);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWInstalled.
 */

typedef struct hrSWInstalled {
    guint32  *hrSWInstalledLastChange;
    guint32  *hrSWInstalledLastUpdateTime;
} hrSWInstalled_t;

extern hrSWInstalled_t *
host_resources_mib_new_hrSWInstalled();

extern int
host_resources_mib_get_hrSWInstalled(host_snmp *s, hrSWInstalled_t **hrSWInstalled);

extern void
host_resources_mib_free_hrSWInstalled(hrSWInstalled_t *hrSWInstalled);

/*
 * C type definitions for HOST-RESOURCES-MIB::hrSWInstalledEntry.
 */

typedef struct hrSWInstalledEntry {
    gint32   hrSWInstalledIndex;
    guchar   *hrSWInstalledName;
    gsize    _hrSWInstalledNameLength;
    guint32  *hrSWInstalledID;
    gsize    _hrSWInstalledIDLength;
    gint32   *hrSWInstalledType;
    guchar   *hrSWInstalledDate;
    gsize    _hrSWInstalledDateLength;
} hrSWInstalledEntry_t;

extern int
host_resources_mib_get_hrSWInstalledTable(host_snmp *s, hrSWInstalledEntry_t ***hrSWInstalledEntry);

extern void
host_resources_mib_free_hrSWInstalledTable(hrSWInstalledEntry_t **hrSWInstalledEntry);

extern hrSWInstalledEntry_t *
host_resources_mib_new_hrSWInstalledEntry();

extern int
host_resources_mib_get_hrSWInstalledEntry(host_snmp *s, hrSWInstalledEntry_t **hrSWInstalledEntry);

extern void
host_resources_mib_free_hrSWInstalledEntry(hrSWInstalledEntry_t *hrSWInstalledEntry);


#endif /* _HOST_RESOURCES_MIB_H_ */
