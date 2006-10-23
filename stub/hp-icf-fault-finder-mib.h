/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli HP-ICF-FAULT-FINDER-MIB
 *
 * Derived from HP-ICF-FAULT-FINDER-MIB:
 *   This MIB module contains object definitions for
 *   managing the Fault Finder feature in web-capable
 *   HP devices.
 *
 * Revision 2005-03-22 07:07:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 2003-07-28 07:07:
 *   Add duplexMismatch type. Update division name.
 *
 * Revision 2003-07-28 07:07:
 *   Added Transceiver related fault messages and
 *   jumbos/flow control fault.
 *
 * Revision 2000-11-03 07:07:
 *   Add lossOfStackMember and hotSwapReboot fault
 *   types.  Update division name.
 *
 * Revision 1998-11-20 23:50:
 *   Added several fault types, and the ability to
 *   reduce a port's speed as one of the actions to
 *   take on a fault.
 *
 * Revision 1997-10-21 02:49:
 *   Initial version of this MIB module.
 *
 * $Id$
 */

#ifndef _HP_ICF_FAULT_FINDER_MIB_H_
#define _HP_ICF_FAULT_FINDER_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSEVERITY_INFORMATIONAL 1
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSEVERITY_MEDIUM        2
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSEVERITY_CRITICAL      3

extern GNetSnmpEnum const hp_icf_fault_finder_mib_enums_hpicfFfLogSeverity[];

#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSTATUS_NEW    1
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSTATUS_ACTIVE 2
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSTATUS_OLD    3

extern GNetSnmpEnum const hp_icf_fault_finder_mib_enums_hpicfFfLogStatus[];

#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_BADDRIVER             1
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_BADXCVR               2
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_BADCABLE              3
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_TOOLONGCABLE          4
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_OVERBANDWIDTH         5
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_BCASTSTORM            6
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_PARTITION             7
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_MISCONFIGUREDSQE      8
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_POLARITYREVERSAL      9
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_NETWORKLOOP           10
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_LOSSOFLINK            11
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_PORTSECURITYVIOLATION 12
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_BACKUPLINKTRANSITION  13
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_MESHINGFAULT          14
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_FANFAULT              15
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_RPSFAULT              16
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_STUCK10MBFAULT        17
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_LOSSOFSTACKMEMBER     18
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_HOTSWAPREBOOT         19
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_DUPLEXMISMATCHHDX     20
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_DUPLEXMISMATCHFDX     21
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_FLOWCNTLJUMBOSFAULT   22
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_PORTSELFTESTFAILURE   23
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_XCVRUNIDENTIFIED      24
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTTYPE_XCVRUNSUPPORTED       25

extern GNetSnmpEnum const hp_icf_fault_finder_mib_enums_HpicfFaultType[];

#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTACTION_NONE                         1
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTACTION_WARN                         2
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTACTION_WARNANDDISABLE               3
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTACTION_WARNANDSPEEDREDUCE           4
#define HP_ICF_FAULT_FINDER_MIB_HPICFFAULTACTION_WARNANDSPEEDREDUCEANDDISABLE 5

extern GNetSnmpEnum const hp_icf_fault_finder_mib_enums_HpicfFaultAction[];


/*
 * C type definitions for HP-ICF-FAULT-FINDER-MIB::hpicfFfControlEntry.
 */

#define HP_ICF_FAULT_FINDER_MIB_HPICFFFACTION               (1 << 0) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFWARNTOLERANCE        (1 << 1) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFDISABLEPORTTOLERANCE (1 << 2) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFSPEEDREDUCETOLERANCE (1 << 3) 

typedef struct {
    gint32   hpicfFfControlIndex;              /* na HP-ICF-FAULT-FINDER-MIB::HpicfFaultType */
    gint32   *hpicfFfAction;                   /* rw HP-ICF-FAULT-FINDER-MIB::HpicfFaultAction */
    gint32   *hpicfFfWarnTolerance;            /* rw HP-ICF-FAULT-FINDER-MIB::HpicfFaultTolerance */
    gint32   *hpicfFfDisablePortTolerance;     /* rw HP-ICF-FAULT-FINDER-MIB::HpicfFaultTolerance */
    gint32   *hpicfFfSpeedReduceTolerance;     /* rw HP-ICF-FAULT-FINDER-MIB::HpicfFaultTolerance */
} hp_icf_fault_finder_mib_hpicfFfControlEntry_t;

extern void
hp_icf_fault_finder_mib_get_hpicfFfControlTable(GNetSnmp *s, hp_icf_fault_finder_mib_hpicfFfControlEntry_t ***hpicfFfControlEntry, gint64 mask);

extern void
hp_icf_fault_finder_mib_free_hpicfFfControlTable(hp_icf_fault_finder_mib_hpicfFfControlEntry_t **hpicfFfControlEntry);

extern hp_icf_fault_finder_mib_hpicfFfControlEntry_t *
hp_icf_fault_finder_mib_new_hpicfFfControlEntry(void);

extern void
hp_icf_fault_finder_mib_get_hpicfFfControlEntry(GNetSnmp *s, hp_icf_fault_finder_mib_hpicfFfControlEntry_t **hpicfFfControlEntry, gint32 hpicfFfControlIndex, gint64 mask);

extern void
hp_icf_fault_finder_mib_set_hpicfFfControlEntry(GNetSnmp *s, hp_icf_fault_finder_mib_hpicfFfControlEntry_t *hpicfFfControlEntry, gint64 mask);

extern void
hp_icf_fault_finder_mib_free_hpicfFfControlEntry(hp_icf_fault_finder_mib_hpicfFfControlEntry_t *hpicfFfControlEntry);

/*
 * C type definitions for HP-ICF-FAULT-FINDER-MIB::hpicfFfLogEntry.
 */

#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGCREATETIME (1 << 0) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGPHYSENTITY (1 << 1) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGFAULTTYPE  (1 << 2) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGACTION     (1 << 3) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSEVERITY   (1 << 4) 
#define HP_ICF_FAULT_FINDER_MIB_HPICFFFLOGSTATUS     (1 << 5) 

typedef struct {
    gint32   hpicfFfLogIndex;           /* na */
    guint32  *hpicfFfLogCreateTime;     /* ro SNMPv2-TC::TimeStamp */
    gint32   *hpicfFfLogPhysEntity;     /* ro ENTITY-MIB::PhysicalIndex */
    gint32   *hpicfFfLogFaultType;      /* ro HP-ICF-FAULT-FINDER-MIB::HpicfFaultType */
    gint32   *hpicfFfLogAction;         /* ro HP-ICF-FAULT-FINDER-MIB::HpicfFaultAction */
    gint32   *hpicfFfLogSeverity;       /* ro */
    gint32   *hpicfFfLogStatus;         /* rw */
} hp_icf_fault_finder_mib_hpicfFfLogEntry_t;

extern void
hp_icf_fault_finder_mib_get_hpicfFfLogTable(GNetSnmp *s, hp_icf_fault_finder_mib_hpicfFfLogEntry_t ***hpicfFfLogEntry, gint64 mask);

extern void
hp_icf_fault_finder_mib_free_hpicfFfLogTable(hp_icf_fault_finder_mib_hpicfFfLogEntry_t **hpicfFfLogEntry);

extern hp_icf_fault_finder_mib_hpicfFfLogEntry_t *
hp_icf_fault_finder_mib_new_hpicfFfLogEntry(void);

extern void
hp_icf_fault_finder_mib_get_hpicfFfLogEntry(GNetSnmp *s, hp_icf_fault_finder_mib_hpicfFfLogEntry_t **hpicfFfLogEntry, gint32 hpicfFfLogIndex, gint64 mask);

extern void
hp_icf_fault_finder_mib_set_hpicfFfLogEntry(GNetSnmp *s, hp_icf_fault_finder_mib_hpicfFfLogEntry_t *hpicfFfLogEntry, gint64 mask);

extern void
hp_icf_fault_finder_mib_free_hpicfFfLogEntry(hp_icf_fault_finder_mib_hpicfFfLogEntry_t *hpicfFfLogEntry);


G_END_DECLS

#endif /* _HP_ICF_FAULT_FINDER_MIB_H_ */
