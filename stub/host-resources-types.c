/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Derived from HOST-RESOURCES-TYPES:
 *   This MIB module registers type definitions for
 *   storage types, device types, and file system types.
 *   
 *   After the initial revision, this module will be
 *   maintained by IANA.
 *
 * Revision 2000-03-06 00:00:
 *   The original version of this module, published as RFC
 *   2790.
 *
 * $Id$
 */

#include "host-resources-types.h"

static guint32 const hrStorageOther[]
	= { HOST_RESOURCES_TYPES_HRSTORAGEOTHER };
static guint32 const hrStorageRam[]
	= { HOST_RESOURCES_TYPES_HRSTORAGERAM };
static guint32 const hrStorageVirtualMemory[]
	= { HOST_RESOURCES_TYPES_HRSTORAGEVIRTUALMEMORY };
static guint32 const hrStorageFixedDisk[]
	= { HOST_RESOURCES_TYPES_HRSTORAGEFIXEDDISK };
static guint32 const hrStorageRemovableDisk[]
	= { HOST_RESOURCES_TYPES_HRSTORAGEREMOVABLEDISK };
static guint32 const hrStorageFloppyDisk[]
	= { HOST_RESOURCES_TYPES_HRSTORAGEFLOPPYDISK };
static guint32 const hrStorageCompactDisc[]
	= { HOST_RESOURCES_TYPES_HRSTORAGECOMPACTDISC };
static guint32 const hrStorageRamDisk[]
	= { HOST_RESOURCES_TYPES_HRSTORAGERAMDISK };
static guint32 const hrStorageFlashMemory[]
	= { HOST_RESOURCES_TYPES_HRSTORAGEFLASHMEMORY };
static guint32 const hrStorageNetworkDisk[]
	= { HOST_RESOURCES_TYPES_HRSTORAGENETWORKDISK };
static guint32 const hrDeviceOther[]
	= { HOST_RESOURCES_TYPES_HRDEVICEOTHER };
static guint32 const hrDeviceUnknown[]
	= { HOST_RESOURCES_TYPES_HRDEVICEUNKNOWN };
static guint32 const hrDeviceProcessor[]
	= { HOST_RESOURCES_TYPES_HRDEVICEPROCESSOR };
static guint32 const hrDeviceNetwork[]
	= { HOST_RESOURCES_TYPES_HRDEVICENETWORK };
static guint32 const hrDevicePrinter[]
	= { HOST_RESOURCES_TYPES_HRDEVICEPRINTER };
static guint32 const hrDeviceDiskStorage[]
	= { HOST_RESOURCES_TYPES_HRDEVICEDISKSTORAGE };
static guint32 const hrDeviceVideo[]
	= { HOST_RESOURCES_TYPES_HRDEVICEVIDEO };
static guint32 const hrDeviceAudio[]
	= { HOST_RESOURCES_TYPES_HRDEVICEAUDIO };
static guint32 const hrDeviceCoprocessor[]
	= { HOST_RESOURCES_TYPES_HRDEVICECOPROCESSOR };
static guint32 const hrDeviceKeyboard[]
	= { HOST_RESOURCES_TYPES_HRDEVICEKEYBOARD };
static guint32 const hrDeviceModem[]
	= { HOST_RESOURCES_TYPES_HRDEVICEMODEM };
static guint32 const hrDeviceParallelPort[]
	= { HOST_RESOURCES_TYPES_HRDEVICEPARALLELPORT };
static guint32 const hrDevicePointing[]
	= { HOST_RESOURCES_TYPES_HRDEVICEPOINTING };
static guint32 const hrDeviceSerialPort[]
	= { HOST_RESOURCES_TYPES_HRDEVICESERIALPORT };
static guint32 const hrDeviceTape[]
	= { HOST_RESOURCES_TYPES_HRDEVICETAPE };
static guint32 const hrDeviceClock[]
	= { HOST_RESOURCES_TYPES_HRDEVICECLOCK };
static guint32 const hrDeviceVolatileMemory[]
	= { HOST_RESOURCES_TYPES_HRDEVICEVOLATILEMEMORY };
static guint32 const hrDeviceNonVolatileMemory[]
	= { HOST_RESOURCES_TYPES_HRDEVICENONVOLATILEMEMORY };
static guint32 const hrFSOther[]
	= { HOST_RESOURCES_TYPES_HRFSOTHER };
static guint32 const hrFSUnknown[]
	= { HOST_RESOURCES_TYPES_HRFSUNKNOWN };
static guint32 const hrFSBerkeleyFFS[]
	= { HOST_RESOURCES_TYPES_HRFSBERKELEYFFS };
static guint32 const hrFSSys5FS[]
	= { HOST_RESOURCES_TYPES_HRFSSYS5FS };
static guint32 const hrFSFat[]
	= { HOST_RESOURCES_TYPES_HRFSFAT };
static guint32 const hrFSHPFS[]
	= { HOST_RESOURCES_TYPES_HRFSHPFS };
static guint32 const hrFSHFS[]
	= { HOST_RESOURCES_TYPES_HRFSHFS };
static guint32 const hrFSMFS[]
	= { HOST_RESOURCES_TYPES_HRFSMFS };
static guint32 const hrFSNTFS[]
	= { HOST_RESOURCES_TYPES_HRFSNTFS };
static guint32 const hrFSVNode[]
	= { HOST_RESOURCES_TYPES_HRFSVNODE };
static guint32 const hrFSJournaled[]
	= { HOST_RESOURCES_TYPES_HRFSJOURNALED };
static guint32 const hrFSiso9660[]
	= { HOST_RESOURCES_TYPES_HRFSISO9660 };
static guint32 const hrFSRockRidge[]
	= { HOST_RESOURCES_TYPES_HRFSROCKRIDGE };
static guint32 const hrFSNFS[]
	= { HOST_RESOURCES_TYPES_HRFSNFS };
static guint32 const hrFSNetware[]
	= { HOST_RESOURCES_TYPES_HRFSNETWARE };
static guint32 const hrFSAFS[]
	= { HOST_RESOURCES_TYPES_HRFSAFS };
static guint32 const hrFSDFS[]
	= { HOST_RESOURCES_TYPES_HRFSDFS };
static guint32 const hrFSAppleshare[]
	= { HOST_RESOURCES_TYPES_HRFSAPPLESHARE };
static guint32 const hrFSRFS[]
	= { HOST_RESOURCES_TYPES_HRFSRFS };
static guint32 const hrFSDGCFS[]
	= { HOST_RESOURCES_TYPES_HRFSDGCFS };
static guint32 const hrFSBFS[]
	= { HOST_RESOURCES_TYPES_HRFSBFS };
static guint32 const hrFSFAT32[]
	= { HOST_RESOURCES_TYPES_HRFSFAT32 };
static guint32 const hrFSLinuxExt2[]
	= { HOST_RESOURCES_TYPES_HRFSLINUXEXT2 };

GSnmpIdentity const host_resources_types_identities[] = {
    { hrStorageOther,
      sizeof(hrStorageOther)/sizeof(guint32),
      "hrStorageOther" },
    { hrStorageRam,
      sizeof(hrStorageRam)/sizeof(guint32),
      "hrStorageRam" },
    { hrStorageVirtualMemory,
      sizeof(hrStorageVirtualMemory)/sizeof(guint32),
      "hrStorageVirtualMemory" },
    { hrStorageFixedDisk,
      sizeof(hrStorageFixedDisk)/sizeof(guint32),
      "hrStorageFixedDisk" },
    { hrStorageRemovableDisk,
      sizeof(hrStorageRemovableDisk)/sizeof(guint32),
      "hrStorageRemovableDisk" },
    { hrStorageFloppyDisk,
      sizeof(hrStorageFloppyDisk)/sizeof(guint32),
      "hrStorageFloppyDisk" },
    { hrStorageCompactDisc,
      sizeof(hrStorageCompactDisc)/sizeof(guint32),
      "hrStorageCompactDisc" },
    { hrStorageRamDisk,
      sizeof(hrStorageRamDisk)/sizeof(guint32),
      "hrStorageRamDisk" },
    { hrStorageFlashMemory,
      sizeof(hrStorageFlashMemory)/sizeof(guint32),
      "hrStorageFlashMemory" },
    { hrStorageNetworkDisk,
      sizeof(hrStorageNetworkDisk)/sizeof(guint32),
      "hrStorageNetworkDisk" },
    { hrDeviceOther,
      sizeof(hrDeviceOther)/sizeof(guint32),
      "hrDeviceOther" },
    { hrDeviceUnknown,
      sizeof(hrDeviceUnknown)/sizeof(guint32),
      "hrDeviceUnknown" },
    { hrDeviceProcessor,
      sizeof(hrDeviceProcessor)/sizeof(guint32),
      "hrDeviceProcessor" },
    { hrDeviceNetwork,
      sizeof(hrDeviceNetwork)/sizeof(guint32),
      "hrDeviceNetwork" },
    { hrDevicePrinter,
      sizeof(hrDevicePrinter)/sizeof(guint32),
      "hrDevicePrinter" },
    { hrDeviceDiskStorage,
      sizeof(hrDeviceDiskStorage)/sizeof(guint32),
      "hrDeviceDiskStorage" },
    { hrDeviceVideo,
      sizeof(hrDeviceVideo)/sizeof(guint32),
      "hrDeviceVideo" },
    { hrDeviceAudio,
      sizeof(hrDeviceAudio)/sizeof(guint32),
      "hrDeviceAudio" },
    { hrDeviceCoprocessor,
      sizeof(hrDeviceCoprocessor)/sizeof(guint32),
      "hrDeviceCoprocessor" },
    { hrDeviceKeyboard,
      sizeof(hrDeviceKeyboard)/sizeof(guint32),
      "hrDeviceKeyboard" },
    { hrDeviceModem,
      sizeof(hrDeviceModem)/sizeof(guint32),
      "hrDeviceModem" },
    { hrDeviceParallelPort,
      sizeof(hrDeviceParallelPort)/sizeof(guint32),
      "hrDeviceParallelPort" },
    { hrDevicePointing,
      sizeof(hrDevicePointing)/sizeof(guint32),
      "hrDevicePointing" },
    { hrDeviceSerialPort,
      sizeof(hrDeviceSerialPort)/sizeof(guint32),
      "hrDeviceSerialPort" },
    { hrDeviceTape,
      sizeof(hrDeviceTape)/sizeof(guint32),
      "hrDeviceTape" },
    { hrDeviceClock,
      sizeof(hrDeviceClock)/sizeof(guint32),
      "hrDeviceClock" },
    { hrDeviceVolatileMemory,
      sizeof(hrDeviceVolatileMemory)/sizeof(guint32),
      "hrDeviceVolatileMemory" },
    { hrDeviceNonVolatileMemory,
      sizeof(hrDeviceNonVolatileMemory)/sizeof(guint32),
      "hrDeviceNonVolatileMemory" },
    { hrFSOther,
      sizeof(hrFSOther)/sizeof(guint32),
      "hrFSOther" },
    { hrFSUnknown,
      sizeof(hrFSUnknown)/sizeof(guint32),
      "hrFSUnknown" },
    { hrFSBerkeleyFFS,
      sizeof(hrFSBerkeleyFFS)/sizeof(guint32),
      "hrFSBerkeleyFFS" },
    { hrFSSys5FS,
      sizeof(hrFSSys5FS)/sizeof(guint32),
      "hrFSSys5FS" },
    { hrFSFat,
      sizeof(hrFSFat)/sizeof(guint32),
      "hrFSFat" },
    { hrFSHPFS,
      sizeof(hrFSHPFS)/sizeof(guint32),
      "hrFSHPFS" },
    { hrFSHFS,
      sizeof(hrFSHFS)/sizeof(guint32),
      "hrFSHFS" },
    { hrFSMFS,
      sizeof(hrFSMFS)/sizeof(guint32),
      "hrFSMFS" },
    { hrFSNTFS,
      sizeof(hrFSNTFS)/sizeof(guint32),
      "hrFSNTFS" },
    { hrFSVNode,
      sizeof(hrFSVNode)/sizeof(guint32),
      "hrFSVNode" },
    { hrFSJournaled,
      sizeof(hrFSJournaled)/sizeof(guint32),
      "hrFSJournaled" },
    { hrFSiso9660,
      sizeof(hrFSiso9660)/sizeof(guint32),
      "hrFSiso9660" },
    { hrFSRockRidge,
      sizeof(hrFSRockRidge)/sizeof(guint32),
      "hrFSRockRidge" },
    { hrFSNFS,
      sizeof(hrFSNFS)/sizeof(guint32),
      "hrFSNFS" },
    { hrFSNetware,
      sizeof(hrFSNetware)/sizeof(guint32),
      "hrFSNetware" },
    { hrFSAFS,
      sizeof(hrFSAFS)/sizeof(guint32),
      "hrFSAFS" },
    { hrFSDFS,
      sizeof(hrFSDFS)/sizeof(guint32),
      "hrFSDFS" },
    { hrFSAppleshare,
      sizeof(hrFSAppleshare)/sizeof(guint32),
      "hrFSAppleshare" },
    { hrFSRFS,
      sizeof(hrFSRFS)/sizeof(guint32),
      "hrFSRFS" },
    { hrFSDGCFS,
      sizeof(hrFSDGCFS)/sizeof(guint32),
      "hrFSDGCFS" },
    { hrFSBFS,
      sizeof(hrFSBFS)/sizeof(guint32),
      "hrFSBFS" },
    { hrFSFAT32,
      sizeof(hrFSFAT32)/sizeof(guint32),
      "hrFSFAT32" },
    { hrFSLinuxExt2,
      sizeof(hrFSLinuxExt2)/sizeof(guint32),
      "hrFSLinuxExt2" },
    { 0, 0, NULL }
};


