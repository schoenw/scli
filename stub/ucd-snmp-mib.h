/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli --scli-set UCD-SNMP-MIB
 *
 * Derived from UCD-SNMP-MIB:
 *   Added ssCpuRawSoftIRQ for Linux (2.6) and forgotten raw swap counters.
 *
 * Revision 2004-04-07 00:00:
 *   Deprecate the non-raw objects.
 *
 * Revision 2002-09-05 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 2002-09-05 00:00:
 *   This file defines the private UCD SNMP MIB extensions.
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

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map notifications to strings and vice versa.
 */

#define UCD_SNMP_MIB_UCDSTART	1,3,6,1,4,1,2021,251,1
#define UCD_SNMP_MIB_UCDSHUTDOWN	1,3,6,1,4,1,2021,251,2

extern GNetSnmpIdentity const ucd_snmp_mib_notifications[];

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
    gint32   prIndex;           /* ro */
    guchar   *prNames;          /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_PRNAMESMINLENGTH 0
#define UCD_SNMP_MIB_PRNAMESMAXLENGTH 255
    guint16  _prNamesLength;
    gint32   *prMin;            /* ro Integer32 */
    gint32   *prMax;            /* ro Integer32 */
    gint32   *prCount;          /* ro Integer32 */
    gint32   *prErrorFlag;      /* ro Integer32 */
    guchar   *prErrMessage;     /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_PRERRMESSAGEMINLENGTH 0
#define UCD_SNMP_MIB_PRERRMESSAGEMAXLENGTH 255
    guint16  _prErrMessageLength;
    gint32   *prErrFix;         /* rw Integer32 */
    guchar   *prErrFixCmd;      /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_PRERRFIXCMDMINLENGTH 0
#define UCD_SNMP_MIB_PRERRFIXCMDMAXLENGTH 255
    guint16  _prErrFixCmdLength;
} ucd_snmp_mib_prEntry_t;

extern void
ucd_snmp_mib_get_prTable(GNetSnmp *s, ucd_snmp_mib_prEntry_t ***prEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_prTable(ucd_snmp_mib_prEntry_t **prEntry);

extern ucd_snmp_mib_prEntry_t *
ucd_snmp_mib_new_prEntry(void);

extern void
ucd_snmp_mib_get_prEntry(GNetSnmp *s, ucd_snmp_mib_prEntry_t **prEntry, gint32 prIndex, gint64 mask, GError **error);

extern void
ucd_snmp_mib_set_prEntry(GNetSnmp *s, ucd_snmp_mib_prEntry_t *prEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_prEntry(ucd_snmp_mib_prEntry_t *prEntry);

extern void
ucd_snmp_mib_set_prErrFix(GNetSnmp *s, gint32 prIndex, gint32 prErrFix, GError **error);

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
    gint32   *memIndex;            /* ro Integer32 */
    guchar   *memErrorName;        /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_MEMERRORNAMEMINLENGTH 0
#define UCD_SNMP_MIB_MEMERRORNAMEMAXLENGTH 255
    guint16  _memErrorNameLength;
    gint32   *memTotalSwap;        /* ro Integer32 */
    gint32   *memAvailSwap;        /* ro Integer32 */
    gint32   *memTotalReal;        /* ro Integer32 */
    gint32   *memAvailReal;        /* ro Integer32 */
    gint32   *memTotalSwapTXT;     /* ro Integer32 */
    gint32   *memAvailSwapTXT;     /* ro Integer32 */
    gint32   *memTotalRealTXT;     /* ro Integer32 */
    gint32   *memAvailRealTXT;     /* ro Integer32 */
    gint32   *memTotalFree;        /* ro Integer32 */
    gint32   *memMinimumSwap;      /* ro Integer32 */
    gint32   *memShared;           /* ro Integer32 */
    gint32   *memBuffer;           /* ro Integer32 */
    gint32   *memCached;           /* ro Integer32 */
    gint32   *memSwapError;        /* ro Integer32 */
    guchar   *memSwapErrorMsg;     /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_MEMSWAPERRORMSGMINLENGTH 0
#define UCD_SNMP_MIB_MEMSWAPERRORMSGMAXLENGTH 255
    guint16  _memSwapErrorMsgLength;
} ucd_snmp_mib_memory_t;

extern ucd_snmp_mib_memory_t *
ucd_snmp_mib_new_memory(void);

extern void
ucd_snmp_mib_get_memory(GNetSnmp *s, ucd_snmp_mib_memory_t **memory, gint64 mask, GError **error);

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
    gint32   extIndex;          /* ro */
    guchar   *extNames;         /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_EXTNAMESMINLENGTH 0
#define UCD_SNMP_MIB_EXTNAMESMAXLENGTH 255
    guint16  _extNamesLength;
    guchar   *extCommand;       /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_EXTCOMMANDMINLENGTH 0
#define UCD_SNMP_MIB_EXTCOMMANDMAXLENGTH 255
    guint16  _extCommandLength;
    gint32   *extResult;        /* ro Integer32 */
    guchar   *extOutput;        /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_EXTOUTPUTMINLENGTH 0
#define UCD_SNMP_MIB_EXTOUTPUTMAXLENGTH 255
    guint16  _extOutputLength;
    gint32   *extErrFix;        /* rw Integer32 */
    guchar   *extErrFixCmd;     /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_EXTERRFIXCMDMINLENGTH 0
#define UCD_SNMP_MIB_EXTERRFIXCMDMAXLENGTH 255
    guint16  _extErrFixCmdLength;
} ucd_snmp_mib_extEntry_t;

extern void
ucd_snmp_mib_get_extTable(GNetSnmp *s, ucd_snmp_mib_extEntry_t ***extEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_extTable(ucd_snmp_mib_extEntry_t **extEntry);

extern ucd_snmp_mib_extEntry_t *
ucd_snmp_mib_new_extEntry(void);

extern void
ucd_snmp_mib_get_extEntry(GNetSnmp *s, ucd_snmp_mib_extEntry_t **extEntry, gint32 extIndex, gint64 mask, GError **error);

extern void
ucd_snmp_mib_set_extEntry(GNetSnmp *s, ucd_snmp_mib_extEntry_t *extEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_extEntry(ucd_snmp_mib_extEntry_t *extEntry);

extern void
ucd_snmp_mib_set_extErrFix(GNetSnmp *s, gint32 extIndex, gint32 extErrFix, GError **error);

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
    gint32   dskIndex;            /* ro */
    guchar   *dskPath;            /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_DSKPATHMINLENGTH 0
#define UCD_SNMP_MIB_DSKPATHMAXLENGTH 255
    guint16  _dskPathLength;
    guchar   *dskDevice;          /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_DSKDEVICEMINLENGTH 0
#define UCD_SNMP_MIB_DSKDEVICEMAXLENGTH 255
    guint16  _dskDeviceLength;
    gint32   *dskMinimum;         /* ro Integer32 */
    gint32   *dskMinPercent;      /* ro Integer32 */
    gint32   *dskTotal;           /* ro Integer32 */
    gint32   *dskAvail;           /* ro Integer32 */
    gint32   *dskUsed;            /* ro Integer32 */
    gint32   *dskPercent;         /* ro Integer32 */
    gint32   *dskPercentNode;     /* ro Integer32 */
    gint32   *dskErrorFlag;       /* ro Integer32 */
    guchar   *dskErrorMsg;        /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_DSKERRORMSGMINLENGTH 0
#define UCD_SNMP_MIB_DSKERRORMSGMAXLENGTH 255
    guint16  _dskErrorMsgLength;
} ucd_snmp_mib_dskEntry_t;

extern void
ucd_snmp_mib_get_dskTable(GNetSnmp *s, ucd_snmp_mib_dskEntry_t ***dskEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_dskTable(ucd_snmp_mib_dskEntry_t **dskEntry);

extern ucd_snmp_mib_dskEntry_t *
ucd_snmp_mib_new_dskEntry(void);

extern void
ucd_snmp_mib_get_dskEntry(GNetSnmp *s, ucd_snmp_mib_dskEntry_t **dskEntry, gint32 dskIndex, gint64 mask, GError **error);

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
    gint32   laIndex;           /* ro */
    guchar   *laNames;          /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LANAMESMINLENGTH 0
#define UCD_SNMP_MIB_LANAMESMAXLENGTH 255
    guint16  _laNamesLength;
    guchar   *laLoad;           /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LALOADMINLENGTH 0
#define UCD_SNMP_MIB_LALOADMAXLENGTH 255
    guint16  _laLoadLength;
    guchar   *laConfig;         /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LACONFIGMINLENGTH 0
#define UCD_SNMP_MIB_LACONFIGMAXLENGTH 255
    guint16  _laConfigLength;
    gint32   *laLoadInt;        /* ro Integer32 */
    guchar   *laLoadFloat;      /* ro UCD-SNMP-MIB::Float */
#define UCD_SNMP_MIB_LALOADFLOATLENGTH 7
    gint32   *laErrorFlag;      /* ro Integer32 */
    guchar   *laErrMessage;     /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LAERRMESSAGEMINLENGTH 0
#define UCD_SNMP_MIB_LAERRMESSAGEMAXLENGTH 255
    guint16  _laErrMessageLength;
} ucd_snmp_mib_laEntry_t;

extern void
ucd_snmp_mib_get_laTable(GNetSnmp *s, ucd_snmp_mib_laEntry_t ***laEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_laTable(ucd_snmp_mib_laEntry_t **laEntry);

extern ucd_snmp_mib_laEntry_t *
ucd_snmp_mib_new_laEntry(void);

extern void
ucd_snmp_mib_get_laEntry(GNetSnmp *s, ucd_snmp_mib_laEntry_t **laEntry, gint32 laIndex, gint64 mask, GError **error);

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
#define UCD_SNMP_MIB_SSCPURAWSOFTIRQ   (1 << 22) 
#define UCD_SNMP_MIB_SSRAWSWAPIN       (1 << 23) 
#define UCD_SNMP_MIB_SSRAWSWAPOUT      (1 << 24) 

typedef struct {
    gint32   *ssIndex;               /* ro Integer32 */
    guchar   *ssErrorName;           /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_SSERRORNAMEMINLENGTH 0
#define UCD_SNMP_MIB_SSERRORNAMEMAXLENGTH 255
    guint16  _ssErrorNameLength;
    gint32   *ssSwapIn;              /* ro Integer32 */
    gint32   *ssSwapOut;             /* ro Integer32 */
    gint32   *ssIOSent;              /* ro Integer32 */
    gint32   *ssIOReceive;           /* ro Integer32 */
    gint32   *ssSysInterrupts;       /* ro Integer32 */
    gint32   *ssSysContext;          /* ro Integer32 */
    gint32   *ssCpuUser;             /* ro Integer32 */
    gint32   *ssCpuSystem;           /* ro Integer32 */
    gint32   *ssCpuIdle;             /* ro Integer32 */
    guint32  *ssCpuRawUser;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssCpuRawNice;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssCpuRawSystem;        /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssCpuRawIdle;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssCpuRawWait;          /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssCpuRawKernel;        /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssCpuRawInterrupt;     /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssIORawSent;           /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssIORawReceived;       /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssRawInterrupts;       /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssRawContexts;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssCpuRawSoftIRQ;       /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssRawSwapIn;           /* ro SNMPv2-SMI::Counter32 */
    guint32  *ssRawSwapOut;          /* ro SNMPv2-SMI::Counter32 */
} ucd_snmp_mib_systemStats_t;

extern ucd_snmp_mib_systemStats_t *
ucd_snmp_mib_new_systemStats(void);

extern void
ucd_snmp_mib_get_systemStats(GNetSnmp *s, ucd_snmp_mib_systemStats_t **systemStats, gint64 mask, GError **error);

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
    gint32   fileIndex;          /* ro */
    guchar   *fileName;          /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_FILENAMEMINLENGTH 0
#define UCD_SNMP_MIB_FILENAMEMAXLENGTH 255
    guint16  _fileNameLength;
    gint32   *fileSize;          /* ro Integer32 [kB] */
    gint32   *fileMax;           /* ro Integer32 [kB] */
    gint32   *fileErrorFlag;     /* ro SNMPv2-TC::TruthValue */
    guchar   *fileErrorMsg;      /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_FILEERRORMSGMINLENGTH 0
#define UCD_SNMP_MIB_FILEERRORMSGMAXLENGTH 255
    guint16  _fileErrorMsgLength;
} ucd_snmp_mib_fileEntry_t;

extern void
ucd_snmp_mib_get_fileTable(GNetSnmp *s, ucd_snmp_mib_fileEntry_t ***fileEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_fileTable(ucd_snmp_mib_fileEntry_t **fileEntry);

extern ucd_snmp_mib_fileEntry_t *
ucd_snmp_mib_new_fileEntry(void);

extern void
ucd_snmp_mib_get_fileEntry(GNetSnmp *s, ucd_snmp_mib_fileEntry_t **fileEntry, gint32 fileIndex, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_fileEntry(ucd_snmp_mib_fileEntry_t *fileEntry);

/*
 * C type definitions for UCD-SNMP-MIB::logMatch.
 */

#define UCD_SNMP_MIB_LOGMATCHMAXENTRIES (1 << 0) 

typedef struct {
    gint32   *logMatchMaxEntries;     /* ro Integer32 */
} ucd_snmp_mib_logMatch_t;

extern ucd_snmp_mib_logMatch_t *
ucd_snmp_mib_new_logMatch(void);

extern void
ucd_snmp_mib_get_logMatch(GNetSnmp *s, ucd_snmp_mib_logMatch_t **logMatch, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_logMatch(ucd_snmp_mib_logMatch_t *logMatch);

/*
 * C type definitions for UCD-SNMP-MIB::logMatchEntry.
 */

#define UCD_SNMP_MIB_LOGMATCHINDEX            (1 << 0) 
#define UCD_SNMP_MIB_LOGMATCHNAME             (1 << 1) 
#define UCD_SNMP_MIB_LOGMATCHFILENAME         (1 << 2) 
#define UCD_SNMP_MIB_LOGMATCHREGEX            (1 << 3) 
#define UCD_SNMP_MIB_LOGMATCHGLOBALCOUNTER    (1 << 4) 
#define UCD_SNMP_MIB_LOGMATCHGLOBALCOUNT      (1 << 5) 
#define UCD_SNMP_MIB_LOGMATCHCURRENTCOUNTER   (1 << 6) 
#define UCD_SNMP_MIB_LOGMATCHCURRENTCOUNT     (1 << 7) 
#define UCD_SNMP_MIB_LOGMATCHCOUNTER          (1 << 8) 
#define UCD_SNMP_MIB_LOGMATCHCOUNT            (1 << 9) 
#define UCD_SNMP_MIB_LOGMATCHCYCLE            (1 << 10) 
#define UCD_SNMP_MIB_LOGMATCHERRORFLAG        (1 << 11) 
#define UCD_SNMP_MIB_LOGMATCHREGEXCOMPILATION (1 << 12) 

typedef struct {
    gint32   logMatchIndex;                 /* ro */
    guchar   *logMatchName;                 /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LOGMATCHNAMEMINLENGTH 0
#define UCD_SNMP_MIB_LOGMATCHNAMEMAXLENGTH 255
    guint16  _logMatchNameLength;
    guchar   *logMatchFilename;             /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LOGMATCHFILENAMEMINLENGTH 0
#define UCD_SNMP_MIB_LOGMATCHFILENAMEMAXLENGTH 255
    guint16  _logMatchFilenameLength;
    guchar   *logMatchRegEx;                /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LOGMATCHREGEXMINLENGTH 0
#define UCD_SNMP_MIB_LOGMATCHREGEXMAXLENGTH 255
    guint16  _logMatchRegExLength;
    guint32  *logMatchGlobalCounter;        /* ro SNMPv2-SMI::Counter32 */
    gint32   *logMatchGlobalCount;          /* ro Integer32 */
    guint32  *logMatchCurrentCounter;       /* ro SNMPv2-SMI::Counter32 */
    gint32   *logMatchCurrentCount;         /* ro Integer32 */
    guint32  *logMatchCounter;              /* ro SNMPv2-SMI::Counter32 */
    gint32   *logMatchCount;                /* ro Integer32 */
    gint32   *logMatchCycle;                /* ro Integer32 */
    gint32   *logMatchErrorFlag;            /* ro SNMPv2-TC::TruthValue */
    guchar   *logMatchRegExCompilation;     /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_LOGMATCHREGEXCOMPILATIONMINLENGTH 0
#define UCD_SNMP_MIB_LOGMATCHREGEXCOMPILATIONMAXLENGTH 255
    guint16  _logMatchRegExCompilationLength;
} ucd_snmp_mib_logMatchEntry_t;

extern void
ucd_snmp_mib_get_logMatchTable(GNetSnmp *s, ucd_snmp_mib_logMatchEntry_t ***logMatchEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_logMatchTable(ucd_snmp_mib_logMatchEntry_t **logMatchEntry);

extern ucd_snmp_mib_logMatchEntry_t *
ucd_snmp_mib_new_logMatchEntry(void);

extern void
ucd_snmp_mib_get_logMatchEntry(GNetSnmp *s, ucd_snmp_mib_logMatchEntry_t **logMatchEntry, gint32 logMatchIndex, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_logMatchEntry(ucd_snmp_mib_logMatchEntry_t *logMatchEntry);

/*
 * C type definitions for UCD-SNMP-MIB::version.
 */

#define UCD_SNMP_MIB_VERSIONINDEX              (1 << 0) 
#define UCD_SNMP_MIB_VERSIONTAG                (1 << 1) 
#define UCD_SNMP_MIB_VERSIONDATE               (1 << 2) 
#define UCD_SNMP_MIB_VERSIONCDATE              (1 << 3) 
#define UCD_SNMP_MIB_VERSIONIDENT              (1 << 4) 
#define UCD_SNMP_MIB_VERSIONCONFIGUREOPTIONS   (1 << 5) 
#define UCD_SNMP_MIB_VERSIONCLEARCACHE         (1 << 6) 
#define UCD_SNMP_MIB_VERSIONUPDATECONFIG       (1 << 7) 
#define UCD_SNMP_MIB_VERSIONRESTARTAGENT       (1 << 8) 
#define UCD_SNMP_MIB_VERSIONSAVEPERSISTENTDATA (1 << 9) 
#define UCD_SNMP_MIB_VERSIONDODEBUGGING        (1 << 10) 

typedef struct {
    gint32   *versionIndex;                  /* ro Integer32 */
    guchar   *versionTag;                    /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_VERSIONTAGMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONTAGMAXLENGTH 255
    guint16  _versionTagLength;
    guchar   *versionDate;                   /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_VERSIONDATEMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONDATEMAXLENGTH 255
    guint16  _versionDateLength;
    guchar   *versionCDate;                  /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_VERSIONCDATEMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONCDATEMAXLENGTH 255
    guint16  _versionCDateLength;
    guchar   *versionIdent;                  /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_VERSIONIDENTMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONIDENTMAXLENGTH 255
    guint16  _versionIdentLength;
    guchar   *versionConfigureOptions;       /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_VERSIONCONFIGUREOPTIONSMINLENGTH 0
#define UCD_SNMP_MIB_VERSIONCONFIGUREOPTIONSMAXLENGTH 255
    guint16  _versionConfigureOptionsLength;
    gint32   *versionClearCache;             /* rw Integer32 */
    gint32   *versionUpdateConfig;           /* rw Integer32 */
    gint32   *versionRestartAgent;           /* rw Integer32 */
    gint32   *versionSavePersistentData;     /* rw Integer32 */
    gint32   *versionDoDebugging;            /* rw Integer32 */
} ucd_snmp_mib_version_t;

extern ucd_snmp_mib_version_t *
ucd_snmp_mib_new_version(void);

extern void
ucd_snmp_mib_get_version(GNetSnmp *s, ucd_snmp_mib_version_t **version, gint64 mask, GError **error);

extern void
ucd_snmp_mib_set_version(GNetSnmp *s, ucd_snmp_mib_version_t *version, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_version(ucd_snmp_mib_version_t *version);

extern void
ucd_snmp_mib_set_versionClearCache(GNetSnmp *s, gint32 versionClearCache, GError **error);

extern void
ucd_snmp_mib_set_versionUpdateConfig(GNetSnmp *s, gint32 versionUpdateConfig, GError **error);

extern void
ucd_snmp_mib_set_versionRestartAgent(GNetSnmp *s, gint32 versionRestartAgent, GError **error);

extern void
ucd_snmp_mib_set_versionSavePersistentData(GNetSnmp *s, gint32 versionSavePersistentData, GError **error);

extern void
ucd_snmp_mib_set_versionDoDebugging(GNetSnmp *s, gint32 versionDoDebugging, GError **error);

/*
 * C type definitions for UCD-SNMP-MIB::snmperrs.
 */

#define UCD_SNMP_MIB_SNMPERRINDEX      (1 << 0) 
#define UCD_SNMP_MIB_SNMPERRNAMES      (1 << 1) 
#define UCD_SNMP_MIB_SNMPERRERRORFLAG  (1 << 2) 
#define UCD_SNMP_MIB_SNMPERRERRMESSAGE (1 << 3) 

typedef struct {
    gint32   *snmperrIndex;          /* ro Integer32 */
    guchar   *snmperrNames;          /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_SNMPERRNAMESMINLENGTH 0
#define UCD_SNMP_MIB_SNMPERRNAMESMAXLENGTH 255
    guint16  _snmperrNamesLength;
    gint32   *snmperrErrorFlag;      /* ro Integer32 */
    guchar   *snmperrErrMessage;     /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_SNMPERRERRMESSAGEMINLENGTH 0
#define UCD_SNMP_MIB_SNMPERRERRMESSAGEMAXLENGTH 255
    guint16  _snmperrErrMessageLength;
} ucd_snmp_mib_snmperrs_t;

extern ucd_snmp_mib_snmperrs_t *
ucd_snmp_mib_new_snmperrs(void);

extern void
ucd_snmp_mib_get_snmperrs(GNetSnmp *s, ucd_snmp_mib_snmperrs_t **snmperrs, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_snmperrs(ucd_snmp_mib_snmperrs_t *snmperrs);

/*
 * C type definitions for UCD-SNMP-MIB::mrEntry.
 */

#define UCD_SNMP_MIB_MRINDEX      (1 << 0) 
#define UCD_SNMP_MIB_MRMODULENAME (1 << 1) 

typedef struct {
    guint32  mrIndex[118];       /* ro ObjectIdentifier */
#define UCD_SNMP_MIB_MRINDEXMINLENGTH 0
#define UCD_SNMP_MIB_MRINDEXMAXLENGTH 118
    guint16  _mrIndexLength;
    guchar   *mrModuleName;     /* ro SNMPv2-TC::DisplayString */
#define UCD_SNMP_MIB_MRMODULENAMEMINLENGTH 0
#define UCD_SNMP_MIB_MRMODULENAMEMAXLENGTH 255
    guint16  _mrModuleNameLength;
} ucd_snmp_mib_mrEntry_t;

extern void
ucd_snmp_mib_get_mrTable(GNetSnmp *s, ucd_snmp_mib_mrEntry_t ***mrEntry, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_mrTable(ucd_snmp_mib_mrEntry_t **mrEntry);

extern ucd_snmp_mib_mrEntry_t *
ucd_snmp_mib_new_mrEntry(void);

extern void
ucd_snmp_mib_get_mrEntry(GNetSnmp *s, ucd_snmp_mib_mrEntry_t **mrEntry, guint32 *mrIndex, guint16 _mrIndexLength, gint64 mask, GError **error);

extern void
ucd_snmp_mib_free_mrEntry(ucd_snmp_mib_mrEntry_t *mrEntry);


G_END_DECLS

#endif /* _UCD_SNMP_MIB_H_ */
