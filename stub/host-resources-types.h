/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
 *
 * Derived from HOST-RESOURCES-TYPES:
 *   This MIB module registers type definitions for
 *   storage types, device types, and file system types.
 *   After the initial revision, this module will be
 *   maintained by IANA.
 *
 * Revision 2000-03-06 00:00:
 *   The original version of this module, published as RFC
 *   2790.
 *
 * $Id$
 */

#ifndef _HOST_RESOURCES_TYPES_H_
#define _HOST_RESOURCES_TYPES_H_

#include "g_snmp.h"

/*
 * Tables to map identities to strings and vice versa.
 */

#define HOST_RESOURCES_TYPES_HRSTORAGEOTHER	1,3,6,1,2,1,25,2,1,1
#define HOST_RESOURCES_TYPES_HRSTORAGERAM	1,3,6,1,2,1,25,2,1,2
#define HOST_RESOURCES_TYPES_HRSTORAGEVIRTUALMEMORY	1,3,6,1,2,1,25,2,1,3
#define HOST_RESOURCES_TYPES_HRSTORAGEFIXEDDISK	1,3,6,1,2,1,25,2,1,4
#define HOST_RESOURCES_TYPES_HRSTORAGEREMOVABLEDISK	1,3,6,1,2,1,25,2,1,5
#define HOST_RESOURCES_TYPES_HRSTORAGEFLOPPYDISK	1,3,6,1,2,1,25,2,1,6
#define HOST_RESOURCES_TYPES_HRSTORAGECOMPACTDISC	1,3,6,1,2,1,25,2,1,7
#define HOST_RESOURCES_TYPES_HRSTORAGERAMDISK	1,3,6,1,2,1,25,2,1,8
#define HOST_RESOURCES_TYPES_HRSTORAGEFLASHMEMORY	1,3,6,1,2,1,25,2,1,9
#define HOST_RESOURCES_TYPES_HRSTORAGENETWORKDISK	1,3,6,1,2,1,25,2,1,10
#define HOST_RESOURCES_TYPES_HRDEVICEOTHER	1,3,6,1,2,1,25,3,1,1
#define HOST_RESOURCES_TYPES_HRDEVICEUNKNOWN	1,3,6,1,2,1,25,3,1,2
#define HOST_RESOURCES_TYPES_HRDEVICEPROCESSOR	1,3,6,1,2,1,25,3,1,3
#define HOST_RESOURCES_TYPES_HRDEVICENETWORK	1,3,6,1,2,1,25,3,1,4
#define HOST_RESOURCES_TYPES_HRDEVICEPRINTER	1,3,6,1,2,1,25,3,1,5
#define HOST_RESOURCES_TYPES_HRDEVICEDISKSTORAGE	1,3,6,1,2,1,25,3,1,6
#define HOST_RESOURCES_TYPES_HRDEVICEVIDEO	1,3,6,1,2,1,25,3,1,10
#define HOST_RESOURCES_TYPES_HRDEVICEAUDIO	1,3,6,1,2,1,25,3,1,11
#define HOST_RESOURCES_TYPES_HRDEVICECOPROCESSOR	1,3,6,1,2,1,25,3,1,12
#define HOST_RESOURCES_TYPES_HRDEVICEKEYBOARD	1,3,6,1,2,1,25,3,1,13
#define HOST_RESOURCES_TYPES_HRDEVICEMODEM	1,3,6,1,2,1,25,3,1,14
#define HOST_RESOURCES_TYPES_HRDEVICEPARALLELPORT	1,3,6,1,2,1,25,3,1,15
#define HOST_RESOURCES_TYPES_HRDEVICEPOINTING	1,3,6,1,2,1,25,3,1,16
#define HOST_RESOURCES_TYPES_HRDEVICESERIALPORT	1,3,6,1,2,1,25,3,1,17
#define HOST_RESOURCES_TYPES_HRDEVICETAPE	1,3,6,1,2,1,25,3,1,18
#define HOST_RESOURCES_TYPES_HRDEVICECLOCK	1,3,6,1,2,1,25,3,1,19
#define HOST_RESOURCES_TYPES_HRDEVICEVOLATILEMEMORY	1,3,6,1,2,1,25,3,1,20
#define HOST_RESOURCES_TYPES_HRDEVICENONVOLATILEMEMORY	1,3,6,1,2,1,25,3,1,21
#define HOST_RESOURCES_TYPES_HRFSOTHER	1,3,6,1,2,1,25,3,9,1
#define HOST_RESOURCES_TYPES_HRFSUNKNOWN	1,3,6,1,2,1,25,3,9,2
#define HOST_RESOURCES_TYPES_HRFSBERKELEYFFS	1,3,6,1,2,1,25,3,9,3
#define HOST_RESOURCES_TYPES_HRFSSYS5FS	1,3,6,1,2,1,25,3,9,4
#define HOST_RESOURCES_TYPES_HRFSFAT	1,3,6,1,2,1,25,3,9,5
#define HOST_RESOURCES_TYPES_HRFSHPFS	1,3,6,1,2,1,25,3,9,6
#define HOST_RESOURCES_TYPES_HRFSHFS	1,3,6,1,2,1,25,3,9,7
#define HOST_RESOURCES_TYPES_HRFSMFS	1,3,6,1,2,1,25,3,9,8
#define HOST_RESOURCES_TYPES_HRFSNTFS	1,3,6,1,2,1,25,3,9,9
#define HOST_RESOURCES_TYPES_HRFSVNODE	1,3,6,1,2,1,25,3,9,10
#define HOST_RESOURCES_TYPES_HRFSJOURNALED	1,3,6,1,2,1,25,3,9,11
#define HOST_RESOURCES_TYPES_HRFSISO9660	1,3,6,1,2,1,25,3,9,12
#define HOST_RESOURCES_TYPES_HRFSROCKRIDGE	1,3,6,1,2,1,25,3,9,13
#define HOST_RESOURCES_TYPES_HRFSNFS	1,3,6,1,2,1,25,3,9,14
#define HOST_RESOURCES_TYPES_HRFSNETWARE	1,3,6,1,2,1,25,3,9,15
#define HOST_RESOURCES_TYPES_HRFSAFS	1,3,6,1,2,1,25,3,9,16
#define HOST_RESOURCES_TYPES_HRFSDFS	1,3,6,1,2,1,25,3,9,17
#define HOST_RESOURCES_TYPES_HRFSAPPLESHARE	1,3,6,1,2,1,25,3,9,18
#define HOST_RESOURCES_TYPES_HRFSRFS	1,3,6,1,2,1,25,3,9,19
#define HOST_RESOURCES_TYPES_HRFSDGCFS	1,3,6,1,2,1,25,3,9,20
#define HOST_RESOURCES_TYPES_HRFSBFS	1,3,6,1,2,1,25,3,9,21
#define HOST_RESOURCES_TYPES_HRFSFAT32	1,3,6,1,2,1,25,3,9,22
#define HOST_RESOURCES_TYPES_HRFSLINUXEXT2	1,3,6,1,2,1,25,3,9,23

extern GSnmpIdentity const host_resources_types_identities[];

#endif /* _HOST_RESOURCES_TYPES_H_ */
