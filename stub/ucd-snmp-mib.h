/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from UCD-SNMP-MIB:
 *   This file defines the private UCD SNMP MIB extensions.
 *
 * Revision 2001-01-17 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 2002-01-04 00:00:
 *   Introduced LongDisplayString which is needed for allow
 *   for long configuration settings. Rewrote some definitions
 *   to make them more precise.
 *
 * Revision 2001-01-17 00:00:
 *   Added raw CPU and IO counters.
 *
 * Revision 1999-12-09 00:00:
 *   SMIv2 version converted from older MIB definitions.
 *
 * $Id$
 */

#ifndef _UCD_SNMP_MIB_H_
#define _UCD_SNMP_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define UCD_SNMP_MIB_PRERRORFLAG_OK    0
#define UCD_SNMP_MIB_PRERRORFLAG_ERROR 1

extern GSnmpEnum const ucd_snmp_mib_enums_prErrorFlag[];

#define UCD_SNMP_MIB_FILEERRORFLAG_TRUE  1
#define UCD_SNMP_MIB_FILEERRORFLAG_FALSE 2

extern GSnmpEnum const ucd_snmp_mib_enums_fileErrorFlag[];

#define UCD_SNMP_MIB_VERSIONDODEBUGGING_DISABLED 0
#define UCD_SNMP_MIB_VERSIONDODEBUGGING_ENABLED  1

extern GSnmpEnum const ucd_snmp_mib_enums_versionDoDebugging[];


/*
 * C type definitions for UCD-SNMP-MIB::prEntry.
 */

#define UCD_SNMP_MIB_PRINDEX      (1 << 0) 
#define UCD_SNMP_MIB_PRNAMES      (1 << 1) 
#define UCD_SNMP_MIB_PRMIN        (1 << 2) 
#define UCD_SNMP_MIB_PRMAX        (1 << 3) 
#define UCD_SNMP_MIB_PRCOUNT      (1 << 4) 
#define UCD_SNMP_MIB_PRERRORFLAG  (1 << 5) 
#define UCD_SNMP_MIB_PRERRMESSAGE (1 << 6) 
#define UCD_SNMP_MIB_PRERRFIX     (1 << 7) 
#define UCD_SNMP_MIB_PRERRFIXCMD  (1 << 8) 

typedef struct {
    gint32   prIndex;
    guchar   *prNames;
#define UCD_SNMP_MIB_PRNAMESMINLENGTH 0
#define UCD_SNMP_MIB_PRNAMESMAXLENGTH 255
    guint16  _prNamesLength;
    gint32   *prMin;
    gint32   *prMax;
    gint32   *prCount;
    gint32   *prErrorFlag;
    guchar   *prErrMessage;
#define UCD_SNMP_MIB_PRERRMESSAGEMINLENGTH 0
#define UCD_SNMP_MIB_PRERRMESSAGEMAXLENGTH 255
    guint16  _prErrMessageLength;
    gint32   *prErrFix;
    guchar   *prErrFixCmd;
#define UCD_SNMP_MIB_PRERRFIXCMDMINLENGTH 0
#define UCD_SNMP_MIB_PRERRFIXCMDMAXLENGTH 255
    guint16  _prErrFixCmdLength;
} ucd_snmp_mib_prEntry_t;

extern void
ucd_snmp_mib_get_prTable(GSnmpSession *s, ucd_snmp_mib_prEntry_t ***prEntry, gint mask);

extern void
ucd_snmp_mib_free_prTable(ucd_snmp_mib_prEntry_t **prEntry);

extern ucd_snmp_mib_prEntry_t *
ucd_snmp_mib_new_prEntry(void);

extern void
ucd_snmp_mib_get_prEntry(GSnmpSession *s, ucd_snmp_mib_prEntry_t **prEntry, gint32 prIndex, gint mask);

extern void
ucd_snmp_mib_set_prEntry(GSnmpSession *s, ucd_snmp_mib_prEntry_t *prEntry, gint mask);

extern void
ucd_snmp_mib_free_prEntry(ucd_snmp_mib_prEntry_t *prEntry);

/*
 * C type definitions for UCD-SNMP-MIB::memory.
 */

#define UCD_SNMP_MIB_MEMINDEX        (1 << 0) 
#define UCD_SNMP_MIB_MEMERRORNAME    (1 << 1) 
#define UCD_SNMP_MIB_MEMTOTALSWAP    (1 << 2) 
#define UCD_SNMP_MIB_MEMAVAILSWAP    (1 << 3) 
#define UCD_SNMP_MIB_MEMTOTALREAL    (1 << 4) 
#define UCD_SNMP_MIB_MEMAVAILREAL    (1 << 5) 
#define UCD_SNMP_MIB_MEMTOTALSWAPTXT (1 << 6) 
#define UCD_SNMP_MIB_MEMAVAILSWAPTXT (1 << 7) 
#define UCD_SNMP_MIB_MEMTOTALREALTXT (1 << 8) 
#define UCD_SNMP_MIB_MEMAVAILREALTXT (1 << 9) 
#define UCD_SNMP_MIB_MEMTOTALFREE    (1 << 10) 
#define UCD_SNMP_MIB_MEMMINIMUMSWAP  (1 << 11) 
#define UCD_SNMP_MIB_MEMSHARED       (1 << 12) 
#define UCD_SNMP_MIB_MEMBUFFER       (1 << 13) 
#define UCD_SNMP_MIB_MEMCACHED       (1 << 14) 
#define UCD_SNMP_MIB_MEMSWAPERROR    (1 << 15) 
#define UCD_SNMP_MIB_MEMSWAPERRORMSG (1 << 16) 

typedef struct {
    gint32   *memIndex;
    guchar   *memErrorName;
#define UCD_SNMP_MIB_MEMERRORNAMEMINLENGTH 0
#define UCD_SNMP_MIB_MEMERRORNAMEMAXLENGTH 255
    guint16  _memErrorNameLength;
    gint32   *memTotalSwap;
    gint32   *memAvailSwap;
    gint32   *memTotalReal;
    gint32   *memAvailReal;
    gint32   *memTotalSwapTXT;
    gint32   *memAvailSwapTXT;
    gint32   *memTotalRealTXT;
    gint32   *memAvailRealTXT;
    gint32   *memTotalFree;
    gint32   *memMinimumSwap;
    gint32   *memShared;
    gint32   *memBuffer;
    gint32   *memCached;
    gint32   *memSwapError;
    guchar   *memSwapErrorMsg;
#define UCD_SNMP_MIB_MEMSWAPERRORMSGMINLENGTH 0
#define UCD_SNMP_MIB_MEMSWAPERRORMSGMAXLENGTH 255
    guint16  _memSwapErrorMsgLength;
} ucd_snmp_mib_memory_t;

extern ucd_snmp_mib_memory_t *
ucd_snmp_mib_new_memory(void);

extern void
ucd_snmp_mib_get_memory(GSnmpSession *s, ucd_snmp_mib_memory_t **memory, gint mask);

extern void
ucd_snmp_mib_free_memory(ucd_snmp_mib_memory_t *memory);

/*
 * C type definitions for UCD-SNMP-MIB::extEntry.
 */

#define UCD_SNMP_MIB_EXTINDEX     (1 << 0) 
#define UCD_SNMP_MIB_EXTNAMES     (1 << 1) 
#define UCD_SNMP_MIB_EXTCOMMAND   (1 << 2) 
#define UCD_SNMP_MIB_EXTRESULT    (1 << 3) 
#define UCD_SNMP_MIB_EXTOUTPUT    (1 << 4) 
#define UCD_SNMP_MIB_EXTERRFIX    (1 << 5) 
#define UCD_SNMP_MIB_EXTERRFIXCMD (1 << 6) 

typedef struct {
    gint32   extIndex;
    guchar   *extNames;
#define UCD_SNMP_MIB_EXTNAMESMINLENGTH 0
#define UCD_SNMP_MIB_EXTNAMESMAXLENGTH 255
    guint16  _extNamesLength;
    guchar   *extCommand;
#define UCD_SNMP_MIB_EXTCOMMANDMINLENGTH 0
#define UCD_SNMP_MIB_EXTCOMMANDMAXLENGTH 255
    guint16  _extCommandLength;
    gint32   *extResult;
    guchar   *extOutput;
#define UCD_SNMP_MIB_EXTOUTPUTMINLENGTH 0
#define UCD_SNMP_MIB_EXTOUTPUTMAXLENGTH 255
    guint16  _extOutputLength;
    gint32   *extErrFix;
    guchar   *extErrFixCmd;
#define UCD_SNMP_MIB_EXTERRFIXCMDMINLENGTH 0
#define UCD_SNMP_MIB_EXTERRFIXCMDMAXLENGTH 255
    guint16  _extErrFixCmdLength;
} ucd_snmp_mib_extEntry_t;

extern void
ucd_snmp_mib_get_extTable(GSnmpSession *s, ucd_snmp_mib_extEntry_t ***extEntry, gint mask);

extern void
ucd_snmp_mib_free_extTable(ucd_snmp_mib_extEntry_t **extEntry);

extern ucd_snmp_mib_extEntry_t *
ucd_snmp_mib_new_extEntry(void);

extern void
ucd_snmp_mib_get_extEntry(GSnmpSession *s, ucd_snmp_mib_extEntry_t **extEntry, gint32 extIndex, gint mask);

extern void
ucd_snmp_mib_set_extEntry(GSnmpSession *s, ucd_snmp_mib_extEntry_t *extEntry, gint mask);

extern void
ucd_snmp_mib_free_extEntry(ucd_snmp_mib_extEntry_t *extEntry);

/*
 * C type definitions for UCD-SNMP-MIB::dskEntry.
 */

#define UCD_SNMP_MIB_DSKINDEX       (1 << 0) 
#define UCD_SNMP_MIB_DSKPATH        (1 << 1) 
#define UCD_SNMP_MIB_DSKDEVICE      (1 << 2) 
#define UCD_SNMP_MIB_DSKMINIMUM     (1 << 3) 
#define UCD_SNMP_MIB_DSKMINPERCENT  (1 << 4) 
#define UCD_SNMP_MIB_DSKTOTAL       (1 << 5) 
#define UCD_SNMP_MIB_DSKAVAIL       (1 << 6) 
#define UCD_SNMP_MIB_DSKUSED        (1 << 7) 
#define UCD_SNMP_MIB_DSKPERCENT     (1 << 8) 
#define UCD_SNMP_MIB_DSKPERCENTNODE (1 << 9) 
#define UCD_SNMP_MIB_DSKERRORFLAG   (1 << 10) 
#define UCD_SNMP_MIB_DSKERRORMSG    (1 << 11) 

typedef struct {
    gint32   dskIndex;
    guchar   *dskPath;
#define UCD_SNMP_MIB_DSKPATHMINLENGTH 0
#define UCD_SNMP_MIB_DSKPATHMAXLENGTH 255
    guint16  _dskPathLength;
    guchar   *dskDevice;
#define UCD_SNMP_MIB_DSKDEVICEMINLENGTH 0
#define UCD_SNMP_MIB_DSKDEVICEMAXLENGTH 255
    guint16  _dskDeviceLength;
    gint32   *dskMinimum;
    gint32   *dskMinPercent;
    gint32   *dskTotal;
    gint32   *dskAvail;
    gint32   *dskUsed;
    gint32   *dskPercent;
    gint32   *dskPercentNode;
    gint32   *dskErrorFlag;
    guchar   *dskErrorMsg;
#define UCD_SNMP_MIB_DSKERRORMSGMINLENGTH 0
#define UCD_SNMP_MIB_DSKERRORMSGMAXLENGTH 255
    guint16  _dskErrorMsgLength;
} ucd_snmp_mib_dskEntry_t;

extern void
ucd_snmp_mib_get_dskTable(GSnmpSession *s, ucd_snmp_mib_dskEntry_t ***dskEntry, gint mask);

extern void
ucd_snmp_mib_free_dskTable(ucd_snmp_mib_dskEntry_t **dskEntry);

extern ucd_snmp_mib_dskEntry_t *
ucd_snmp_mib_new_dskEntry(void);

extern void
ucd_snmp_mib_get_dskEntry(GSnmpSession *s, ucd_snmp_mib_dskEntry_t **dskEntry, gint32 dskIndex, gint mask);

extern void
ucd_snmp_mib_free_dskEntry(ucd_snmp_mib_dskEntry_t *dskEntry);

/*
 * C type definitions for UCD-SNMP-MIB::laEntry.
 */

#define UCD_SNMP_MIB_LAINDEX      (1 << 0) 
#define UCD_SNMP_MIB_LANAMES      (1 << 1) 
#define UCD_SNMP_MIB_LALOAD       (1 << 2) 
#define UCD_SNMP_MIB_LACONFIG     (1 << 3) 
#define UCD_SNMP_MIB_LALOADINT    (1 << 4) 
#define UCD_SNMP_MIB_LALOADFLOAT  (1 << 5) 
#define UCD_SNMP_MIB_LAERRORFLAG  (1 << 6) 
#define UCD_SNMP_MIB_LAERRMESSAGE (1 << 7) 

typedef struct {
    gint32   laIndex;
    guchar   *laNames;
#define UCD_SNMP_MIB_LANAMESMINLENGTH 0
#define UCD_SNMP_MIB_LANAMESMAXLENGTH 255
    guint16  _laNamesLength;
    guchar   *laLoad;
#define UCD_SNMP_MIB_LALOADMINLENGTH 0
#define UCD_SNMP_MIB_LALOADMAXLENGTH 255
    guint16  _laLoadLength;
    guchar   *laConfig;
#define UCD_SNMP_MIB_LACONFIGMINLENGTH 0
#define UCD_SNMP_MIB_LACONFIGMAXLENGTH 255
    guint16  _laConfigLength;
    gint32   *laLoadInt;
    guchar   *laLoadFloat;
#define UCD_SNMP_MIB_LALOADFLOATLENGTH 7
    gint32   *laErrorFlag;
    guchar   *laErrMessage;
#define UCD_SNMP_MIB_LAERRMESSAGEMINLENGTH 0
#define UCD_SNMP_MIB_LAERRMESSAGEMAXLENGTH 255
    guint16  _laErrMessageLength;
} ucd_snmp_mib_laEntry_t;

extern void
ucd_snmp_mib_get_laTable(GSnmpSession *s, ucd_snmp_mib_laEntry_t ***laEntry, gint mask);

extern void
ucd_snmp_mib_free_laTable(ucd_snmp_mib_laEntry_t **laEntry);

extern ucd_snmp_mib_laEntry_t *
ucd_snmp_mib_new_laEntry(void);

extern void
ucd_snmp_mib_get_laEntry(GSnmpSession *s, ucd_snmp_mib_laEntry_t **laEntry, gint32 laIndex, gint mask);

extern void
ucd_snmp_mib_free_laEntry(ucd_snmp_mib_laEntry_t *laEntry);

/*
 * C type definitions for UCD-SNMP-MIB::systemStats.
 */

#define UCD_SNMP_MIB_SSINDEX           (1 << 0) 
#define UCD_SNMP_MIB_SSERRORNAME       (1 << 1) 
#define UCD_SNMP_MIB_SSSWAPIN          (1 << 2) 
#define UCD_SNMP_MIB_SSSWAPOUT         (1 << 3) 
#define UCD_SNMP_MIB_SSIOSENT          (1 << 4) 
#define UCD_SNMP_MIB_SSIORECEIVE       (1 << 5) 
#define UCD_SNMP_MIB_SSSYSINTERRUPTS   (1 << 6) 
#define UCD_SNMP_MIB_SSSYSCONTEXT      (1 << 7) 
#define UCD_SNMP_MIB_SSCPUUSER         (1 << 8) 
#define UCD_SNMP_MIB_SSCPUSYSTEM       (1 << 9) 
#define UCD_SNMP_MIB_SSCPUIDLE         (1 << 10) 
#define UCD_SNMP_MIB_SSCPURAWUSER      (1 << 11) 
#define UCD_SNMP_MIB_SSCPURAWNICE      (1 << 12) 
#define UCD_SNMP_MIB_SSCPURAWSYSTEM    (1 << 13) 
#define UCD_SNMP_MIB_SSCPURAWIDLE      (1 << 14) 
#define UCD_SNMP_MIB_SSCPURAWWAIT      (1 << 15) 
#define UCD_SNMP_MIB_SSCPURAWKERNEL    (1 << 16) 
#define UCD_SNMP_MIB_SSCPURAWINTERRUPT (1 << 17) 
#define UCD_SNMP_MIB_SSIORAWSENT       (1 << 18) 
#define UCD_SNMP_MIB_SSIORAWRECEIVED   (1 << 19) 
#define UCD_SNMP_MIB_SSRAWINTERRUPTS   (1 << 20) 
#define UCD_SNMP_MIB_SSRAWCONTEXTS     (1 << 21) 

typedef struct {
    gint32   *ssIndex;
    guchar   *ssErrorName;
#define UCD_SNMP_MIB_SSERRORNAMEMINLENGTH 0
#define UCD_SNMP_MIB_SSERRORNAMEMAXLENGTH 255
    guint16  _ssErrorNameLength;
    gint32   *ssSwapIn;
    gint32   *ssSwapOut;
    gint32   *ssIOSent;
    gint32   *ssIOReceive;
    gint32   *ssSysInterrupts;
    gint32   *ssSysContext;
    gint32   *ssCpuUser;
    gint32   *ssCpuSystem;
    gint32   *ssCpuIdle;
    guint32  *ssCpuRawUser;
    guint32  *ssCpuRawNice;
    guint32  *ssCpuRawSystem;
    guint32  *ssCpuRawIdle;
    guint32  *ssCpuRawWait;
    guint32  *ssCpuRawKernel;
    guint32  *ssCpuRawInterrupt;
    guint32  *ssIORawSent;
    guint32  *ssIORawReceived;
    guint32  *ssRawInterrupts;
    guint32  *ssRawContexts;
} ucd_snmp_mib_systemStats_t;

extern ucd_snmp_mib_systemStats_t *
ucd_snmp_mib_new_systemStats(void);

extern void
ucd_snmp_mib_get_systemStats(GSnmpSession *s, ucd_snmp_mib_systemStats_t **systemStats, gint mask);

extern void
ucd_snmp_mib_free_systemStats(ucd_snmp_mib_systemStats_t *systemStats);

/*
 * C type definitions for UCD-SNMP-MIB::fileEntry.
 */

#define UCD_SNMP_MIB_FILEINDEX     (1 << 0) 
#define UCD_SNMP_MIB_FILENAME      (1 << 1) 
#define UCD_SNMP_MIB_FILESIZE      (1 << 2) 
#define UCD_SNMP_MIB_FILEMAX       (1 << 3) 
#define UCD_SNMP_MIB_FILEERRORFLAG (1 << 4) 
#define UCD_SNMP_MIB_FILEERRORMSG  (1 << 5) 

typedef struct {
    gint32   fileIndex;
    guchar   *fileName;
#define UCD_SNMP_MIB_FILENAMEMINLENGTH 0
#define UCD_SNMP_MIB_FILENAMEMAXLENGTH 255
    guint16  _fileNameLength;
    gint32   *fileSize;
    gint32   *fileMax;
    gint32   *fileErrorFlag;
    guchar   *fileErrorMsg;
#define UCD_SNMP_MIB_FILEERRORMSGMINLENGTH 0
#define UCD_SNMP_MIB_FILEERRORMSGMAXLENGTH 255
    guint16  _fileErrorMsgLength;
} ucd_snmp_mib_fileEntry_t;

extern void
ucd_snmp_mib_get_fileTable(GSnmpSession *s, ucd_snmp_mib_fileEntry_t ***fileEntry, gint mask);

extern void
ucd_snmp_mib_free_fileTable(ucd_snmp_mib_fileEntry_t **fileEntry);

extern ucd_snmp_mib_fileEntry_t *
ucd_snmp_mib_new_fileEntry(void);

extern void
ucd_snmp_mib_get_fileEntry(GSnmpSession *s, ucd_snmp_mib_fileEntry_t **fileEntry, gint32 fileIndex, gint mask);

extern void
ucd_snmp_mib_free_fileEntry(ucd_snmp_mib_fileEntry_t *fileEntry);

/*
 * C type definitions for UCD-SNMP-MIB::version.
 */

#define UCD_SNMP_MIB_VERSIONINDEX            (1 << 0) 
#define UCD_SNMP_MIB_VERSIONTAG              (1 << 1) 
#define UCD_SNMP_MIB_VERSIONDATE             (1 << 2) 
#define UCD_SNMP_MIB_VERSIONCDATE            (1 << 3) 
#define UCD_SNMP_MIB_VERSIONIDENT            (1 << 4) 
#define UCD_SNMP_MIB_VERSIONCONFIGUREOPTIONS (1 << 5) 
#define UCD_SNMP_MIB_VERSIONCLEARCACHE       (1 << 6) 
#define UCD_SNMP_MIB_VERSIONUPDATECONFIG     (1 << 7) 
#define UCD_SNMP_MIB_VERSIONRESTARTAGENT     (1 << 8) 
#define UCD_SNMP_MIB_VERSIONDODEBUGGING      (1 << 9) 

typedef struct {
    gint32   *versionIndex;
    guchar   *versionTag;
#define UCD_SNMP_MIB_VERSIONTAGMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONTAGMAXLENGTH 255
    guint16  _versionTagLength;
    guchar   *versionDate;
#define UCD_SNMP_MIB_VERSIONDATEMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONDATEMAXLENGTH 255
    guint16  _versionDateLength;
    guchar   *versionCDate;
#define UCD_SNMP_MIB_VERSIONCDATEMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONCDATEMAXLENGTH 255
    guint16  _versionCDateLength;
    guchar   *versionIdent;
#define UCD_SNMP_MIB_VERSIONIDENTMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONIDENTMAXLENGTH 255
    guint16  _versionIdentLength;
    guchar   *versionConfigureOptions;
#define UCD_SNMP_MIB_VERSIONCONFIGUREOPTIONSMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONCONFIGUREOPTIONSMAXLENGTH 1023
    guint16  _versionConfigureOptionsLength;
    gint32   *versionClearCache;
    gint32   *versionUpdateConfig;
    gint32   *versionRestartAgent;
    gint32   *versionDoDebugging;
} ucd_snmp_mib_version_t;

extern ucd_snmp_mib_version_t *
ucd_snmp_mib_new_version(void);

extern void
ucd_snmp_mib_get_version(GSnmpSession *s, ucd_snmp_mib_version_t **version, gint mask);

extern void
ucd_snmp_mib_set_version(GSnmpSession *s, ucd_snmp_mib_version_t *version, gint mask);

extern void
ucd_snmp_mib_free_version(ucd_snmp_mib_version_t *version);

/*
 * C type definitions for UCD-SNMP-MIB::snmperrs.
 */

#define UCD_SNMP_MIB_SNMPERRINDEX      (1 << 0) 
#define UCD_SNMP_MIB_SNMPERRNAMES      (1 << 1) 
#define UCD_SNMP_MIB_SNMPERRERRORFLAG  (1 << 2) 
#define UCD_SNMP_MIB_SNMPERRERRMESSAGE (1 << 3) 

typedef struct {
    gint32   *snmperrIndex;
    guchar   *snmperrNames;
#define UCD_SNMP_MIB_SNMPERRNAMESMINLENGTH 0
#define UCD_SNMP_MIB_SNMPERRNAMESMAXLENGTH 255
    guint16  _snmperrNamesLength;
    gint32   *snmperrErrorFlag;
    guchar   *snmperrErrMessage;
#define UCD_SNMP_MIB_SNMPERRERRMESSAGEMINLENGTH 0
#define UCD_SNMP_MIB_SNMPERRERRMESSAGEMAXLENGTH 255
    guint16  _snmperrErrMessageLength;
} ucd_snmp_mib_snmperrs_t;

extern ucd_snmp_mib_snmperrs_t *
ucd_snmp_mib_new_snmperrs(void);

extern void
ucd_snmp_mib_get_snmperrs(GSnmpSession *s, ucd_snmp_mib_snmperrs_t **snmperrs, gint mask);

extern void
ucd_snmp_mib_free_snmperrs(ucd_snmp_mib_snmperrs_t *snmperrs);

/*
 * C type definitions for UCD-SNMP-MIB::mrEntry.
 */

#define UCD_SNMP_MIB_MRINDEX      (1 << 0) 
#define UCD_SNMP_MIB_MRMODULENAME (1 << 1) 

typedef struct {
    guint32  mrIndex[118];
#define UCD_SNMP_MIB_MRINDEXMINLENGTH 0
#define UCD_SNMP_MIB_MRINDEXMAXLENGTH 118
    guint16  _mrIndexLength;
    guchar   *mrModuleName;
#define UCD_SNMP_MIB_MRMODULENAMEMINLENGTH 0
#define UCD_SNMP_MIB_MRMODULENAMEMAXLENGTH 255
    guint16  _mrModuleNameLength;
} ucd_snmp_mib_mrEntry_t;

extern void
ucd_snmp_mib_get_mrTable(GSnmpSession *s, ucd_snmp_mib_mrEntry_t ***mrEntry, gint mask);

extern void
ucd_snmp_mib_free_mrTable(ucd_snmp_mib_mrEntry_t **mrEntry);

extern ucd_snmp_mib_mrEntry_t *
ucd_snmp_mib_new_mrEntry(void);

extern void
ucd_snmp_mib_get_mrEntry(GSnmpSession *s, ucd_snmp_mib_mrEntry_t **mrEntry, guint32 *mrIndex, guint16 _mrIndexLength, gint mask);

extern void
ucd_snmp_mib_free_mrEntry(ucd_snmp_mib_mrEntry_t *mrEntry);


#endif /* _UCD_SNMP_MIB_H_ */
