/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.3.1 for the scli package.
 *
 * Derived from RS-232-MIB:
 *   The MIB module for RS-232-like hardware devices.
 *
 * Revision 1994-05-26 17:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#ifndef _RS_232_MIB_H_
#define _RS_232_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define RS_232_MIB_RS232PORTTYPE_OTHER 1
#define RS_232_MIB_RS232PORTTYPE_RS232 2
#define RS_232_MIB_RS232PORTTYPE_RS422 3
#define RS_232_MIB_RS232PORTTYPE_RS423 4
#define RS_232_MIB_RS232PORTTYPE_V35   5
#define RS_232_MIB_RS232PORTTYPE_X21   6

extern GSnmpEnum const rs_232_mib_enums_rs232PortType[];

#define RS_232_MIB_RS232PORTINFLOWTYPE_NONE   1
#define RS_232_MIB_RS232PORTINFLOWTYPE_CTSRTS 2
#define RS_232_MIB_RS232PORTINFLOWTYPE_DSRDTR 3

extern GSnmpEnum const rs_232_mib_enums_rs232PortInFlowType[];

#define RS_232_MIB_RS232PORTOUTFLOWTYPE_NONE   1
#define RS_232_MIB_RS232PORTOUTFLOWTYPE_CTSRTS 2
#define RS_232_MIB_RS232PORTOUTFLOWTYPE_DSRDTR 3

extern GSnmpEnum const rs_232_mib_enums_rs232PortOutFlowType[];

#define RS_232_MIB_RS232ASYNCPORTSTOPBITS_ONE        1
#define RS_232_MIB_RS232ASYNCPORTSTOPBITS_TWO        2
#define RS_232_MIB_RS232ASYNCPORTSTOPBITS_ONEANDHALF 3
#define RS_232_MIB_RS232ASYNCPORTSTOPBITS_DYNAMIC    4

extern GSnmpEnum const rs_232_mib_enums_rs232AsyncPortStopBits[];

#define RS_232_MIB_RS232ASYNCPORTPARITY_NONE  1
#define RS_232_MIB_RS232ASYNCPORTPARITY_ODD   2
#define RS_232_MIB_RS232ASYNCPORTPARITY_EVEN  3
#define RS_232_MIB_RS232ASYNCPORTPARITY_MARK  4
#define RS_232_MIB_RS232ASYNCPORTPARITY_SPACE 5

extern GSnmpEnum const rs_232_mib_enums_rs232AsyncPortParity[];

#define RS_232_MIB_RS232ASYNCPORTAUTOBAUD_ENABLED  1
#define RS_232_MIB_RS232ASYNCPORTAUTOBAUD_DISABLED 2

extern GSnmpEnum const rs_232_mib_enums_rs232AsyncPortAutobaud[];

#define RS_232_MIB_RS232SYNCPORTCLOCKSOURCE_INTERNAL 1
#define RS_232_MIB_RS232SYNCPORTCLOCKSOURCE_EXTERNAL 2
#define RS_232_MIB_RS232SYNCPORTCLOCKSOURCE_SPLIT    3

extern GSnmpEnum const rs_232_mib_enums_rs232SyncPortClockSource[];

#define RS_232_MIB_RS232SYNCPORTROLE_DTE 1
#define RS_232_MIB_RS232SYNCPORTROLE_DCE 2

extern GSnmpEnum const rs_232_mib_enums_rs232SyncPortRole[];

#define RS_232_MIB_RS232SYNCPORTENCODING_NRZ  1
#define RS_232_MIB_RS232SYNCPORTENCODING_NRZI 2

extern GSnmpEnum const rs_232_mib_enums_rs232SyncPortEncoding[];

#define RS_232_MIB_RS232SYNCPORTRTSCONTROL_CONTROLLED 1
#define RS_232_MIB_RS232SYNCPORTRTSCONTROL_CONSTANT   2

extern GSnmpEnum const rs_232_mib_enums_rs232SyncPortRTSControl[];

#define RS_232_MIB_RS232SYNCPORTMODE_FDX             1
#define RS_232_MIB_RS232SYNCPORTMODE_HDX             2
#define RS_232_MIB_RS232SYNCPORTMODE_SIMPLEX_RECEIVE 3
#define RS_232_MIB_RS232SYNCPORTMODE_SIMPLEX_SEND    4

extern GSnmpEnum const rs_232_mib_enums_rs232SyncPortMode[];

#define RS_232_MIB_RS232SYNCPORTIDLEPATTERN_MARK  1
#define RS_232_MIB_RS232SYNCPORTIDLEPATTERN_SPACE 2

extern GSnmpEnum const rs_232_mib_enums_rs232SyncPortIdlePattern[];

#define RS_232_MIB_RS232INSIGNAME_RTS  1
#define RS_232_MIB_RS232INSIGNAME_CTS  2
#define RS_232_MIB_RS232INSIGNAME_DSR  3
#define RS_232_MIB_RS232INSIGNAME_DTR  4
#define RS_232_MIB_RS232INSIGNAME_RI   5
#define RS_232_MIB_RS232INSIGNAME_DCD  6
#define RS_232_MIB_RS232INSIGNAME_SQ   7
#define RS_232_MIB_RS232INSIGNAME_SRS  8
#define RS_232_MIB_RS232INSIGNAME_SRTS 9
#define RS_232_MIB_RS232INSIGNAME_SCTS 10
#define RS_232_MIB_RS232INSIGNAME_SDCD 11

extern GSnmpEnum const rs_232_mib_enums_rs232InSigName[];

#define RS_232_MIB_RS232INSIGSTATE_NONE 1
#define RS_232_MIB_RS232INSIGSTATE_ON   2
#define RS_232_MIB_RS232INSIGSTATE_OFF  3

extern GSnmpEnum const rs_232_mib_enums_rs232InSigState[];

#define RS_232_MIB_RS232OUTSIGNAME_RTS  1
#define RS_232_MIB_RS232OUTSIGNAME_CTS  2
#define RS_232_MIB_RS232OUTSIGNAME_DSR  3
#define RS_232_MIB_RS232OUTSIGNAME_DTR  4
#define RS_232_MIB_RS232OUTSIGNAME_RI   5
#define RS_232_MIB_RS232OUTSIGNAME_DCD  6
#define RS_232_MIB_RS232OUTSIGNAME_SQ   7
#define RS_232_MIB_RS232OUTSIGNAME_SRS  8
#define RS_232_MIB_RS232OUTSIGNAME_SRTS 9
#define RS_232_MIB_RS232OUTSIGNAME_SCTS 10
#define RS_232_MIB_RS232OUTSIGNAME_SDCD 11

extern GSnmpEnum const rs_232_mib_enums_rs232OutSigName[];

#define RS_232_MIB_RS232OUTSIGSTATE_NONE 1
#define RS_232_MIB_RS232OUTSIGSTATE_ON   2
#define RS_232_MIB_RS232OUTSIGSTATE_OFF  3

extern GSnmpEnum const rs_232_mib_enums_rs232OutSigState[];


/*
 * C type definitions for RS-232-MIB::rs232.
 */

#define RS_232_MIB_RS232NUMBER (1 << 0) 
typedef struct {
    gint32   *rs232Number;
} rs_232_mib_rs232_t;

extern rs_232_mib_rs232_t *
rs_232_mib_new_rs232(void);

extern void
rs_232_mib_get_rs232(GSnmpSession *s, rs_232_mib_rs232_t **rs232, gint mask);

extern void
rs_232_mib_free_rs232(rs_232_mib_rs232_t *rs232);

/*
 * C type definitions for RS-232-MIB::rs232PortEntry.
 */

#define RS_232_MIB_RS232PORTINDEX        (1 << 0) 
#define RS_232_MIB_RS232PORTTYPE         (1 << 1) 
#define RS_232_MIB_RS232PORTINSIGNUMBER  (1 << 2) 
#define RS_232_MIB_RS232PORTOUTSIGNUMBER (1 << 3) 
#define RS_232_MIB_RS232PORTINSPEED      (1 << 4) 
#define RS_232_MIB_RS232PORTOUTSPEED     (1 << 5) 
#define RS_232_MIB_RS232PORTINFLOWTYPE   (1 << 6) 
#define RS_232_MIB_RS232PORTOUTFLOWTYPE  (1 << 7) 

typedef struct {
    gint32   rs232PortIndex;
    gint32   *rs232PortType;
    gint32   *rs232PortInSigNumber;
    gint32   *rs232PortOutSigNumber;
    gint32   *rs232PortInSpeed;
    gint32   *rs232PortOutSpeed;
    gint32   *rs232PortInFlowType;
    gint32   *rs232PortOutFlowType;
} rs_232_mib_rs232PortEntry_t;

extern void
rs_232_mib_get_rs232PortTable(GSnmpSession *s, rs_232_mib_rs232PortEntry_t ***rs232PortEntry, gint mask);

extern void
rs_232_mib_free_rs232PortTable(rs_232_mib_rs232PortEntry_t **rs232PortEntry);

extern rs_232_mib_rs232PortEntry_t *
rs_232_mib_new_rs232PortEntry(void);

extern void
rs_232_mib_get_rs232PortEntry(GSnmpSession *s, rs_232_mib_rs232PortEntry_t **rs232PortEntry, gint32 rs232PortIndex, gint mask);

extern void
rs_232_mib_set_rs232PortEntry(GSnmpSession *s, rs_232_mib_rs232PortEntry_t *rs232PortEntry, gint mask);

extern void
rs_232_mib_free_rs232PortEntry(rs_232_mib_rs232PortEntry_t *rs232PortEntry);

/*
 * C type definitions for RS-232-MIB::rs232AsyncPortEntry.
 */

#define RS_232_MIB_RS232ASYNCPORTINDEX       (1 << 0) 
#define RS_232_MIB_RS232ASYNCPORTBITS        (1 << 1) 
#define RS_232_MIB_RS232ASYNCPORTSTOPBITS    (1 << 2) 
#define RS_232_MIB_RS232ASYNCPORTPARITY      (1 << 3) 
#define RS_232_MIB_RS232ASYNCPORTAUTOBAUD    (1 << 4) 
#define RS_232_MIB_RS232ASYNCPORTPARITYERRS  (1 << 5) 
#define RS_232_MIB_RS232ASYNCPORTFRAMINGERRS (1 << 6) 
#define RS_232_MIB_RS232ASYNCPORTOVERRUNERRS (1 << 7) 

typedef struct {
    gint32   rs232AsyncPortIndex;
    gint32   *rs232AsyncPortBits;
    gint32   *rs232AsyncPortStopBits;
    gint32   *rs232AsyncPortParity;
    gint32   *rs232AsyncPortAutobaud;
    guint32  *rs232AsyncPortParityErrs;
    guint32  *rs232AsyncPortFramingErrs;
    guint32  *rs232AsyncPortOverrunErrs;
} rs_232_mib_rs232AsyncPortEntry_t;

extern void
rs_232_mib_get_rs232AsyncPortTable(GSnmpSession *s, rs_232_mib_rs232AsyncPortEntry_t ***rs232AsyncPortEntry, gint mask);

extern void
rs_232_mib_free_rs232AsyncPortTable(rs_232_mib_rs232AsyncPortEntry_t **rs232AsyncPortEntry);

extern rs_232_mib_rs232AsyncPortEntry_t *
rs_232_mib_new_rs232AsyncPortEntry(void);

extern void
rs_232_mib_get_rs232AsyncPortEntry(GSnmpSession *s, rs_232_mib_rs232AsyncPortEntry_t **rs232AsyncPortEntry, gint32 rs232AsyncPortIndex, gint mask);

extern void
rs_232_mib_set_rs232AsyncPortEntry(GSnmpSession *s, rs_232_mib_rs232AsyncPortEntry_t *rs232AsyncPortEntry, gint mask);

extern void
rs_232_mib_free_rs232AsyncPortEntry(rs_232_mib_rs232AsyncPortEntry_t *rs232AsyncPortEntry);

/*
 * C type definitions for RS-232-MIB::rs232SyncPortEntry.
 */

#define RS_232_MIB_RS232SYNCPORTINDEX                (1 << 0) 
#define RS_232_MIB_RS232SYNCPORTCLOCKSOURCE          (1 << 1) 
#define RS_232_MIB_RS232SYNCPORTFRAMECHECKERRS       (1 << 2) 
#define RS_232_MIB_RS232SYNCPORTTRANSMITUNDERRUNERRS (1 << 3) 
#define RS_232_MIB_RS232SYNCPORTRECEIVEOVERRUNERRS   (1 << 4) 
#define RS_232_MIB_RS232SYNCPORTINTERRUPTEDFRAMES    (1 << 5) 
#define RS_232_MIB_RS232SYNCPORTABORTEDFRAMES        (1 << 6) 
#define RS_232_MIB_RS232SYNCPORTROLE                 (1 << 7) 
#define RS_232_MIB_RS232SYNCPORTENCODING             (1 << 8) 
#define RS_232_MIB_RS232SYNCPORTRTSCONTROL           (1 << 9) 
#define RS_232_MIB_RS232SYNCPORTRTSCTSDELAY          (1 << 10) 
#define RS_232_MIB_RS232SYNCPORTMODE                 (1 << 11) 
#define RS_232_MIB_RS232SYNCPORTIDLEPATTERN          (1 << 12) 
#define RS_232_MIB_RS232SYNCPORTMINFLAGS             (1 << 13) 

typedef struct {
    gint32   rs232SyncPortIndex;
    gint32   *rs232SyncPortClockSource;
    guint32  *rs232SyncPortFrameCheckErrs;
    guint32  *rs232SyncPortTransmitUnderrunErrs;
    guint32  *rs232SyncPortReceiveOverrunErrs;
    guint32  *rs232SyncPortInterruptedFrames;
    guint32  *rs232SyncPortAbortedFrames;
    gint32   *rs232SyncPortRole;
    gint32   *rs232SyncPortEncoding;
    gint32   *rs232SyncPortRTSControl;
    gint32   *rs232SyncPortRTSCTSDelay;
    gint32   *rs232SyncPortMode;
    gint32   *rs232SyncPortIdlePattern;
    gint32   *rs232SyncPortMinFlags;
} rs_232_mib_rs232SyncPortEntry_t;

extern void
rs_232_mib_get_rs232SyncPortTable(GSnmpSession *s, rs_232_mib_rs232SyncPortEntry_t ***rs232SyncPortEntry, gint mask);

extern void
rs_232_mib_free_rs232SyncPortTable(rs_232_mib_rs232SyncPortEntry_t **rs232SyncPortEntry);

extern rs_232_mib_rs232SyncPortEntry_t *
rs_232_mib_new_rs232SyncPortEntry(void);

extern void
rs_232_mib_get_rs232SyncPortEntry(GSnmpSession *s, rs_232_mib_rs232SyncPortEntry_t **rs232SyncPortEntry, gint32 rs232SyncPortIndex, gint mask);

extern void
rs_232_mib_set_rs232SyncPortEntry(GSnmpSession *s, rs_232_mib_rs232SyncPortEntry_t *rs232SyncPortEntry, gint mask);

extern void
rs_232_mib_free_rs232SyncPortEntry(rs_232_mib_rs232SyncPortEntry_t *rs232SyncPortEntry);

/*
 * C type definitions for RS-232-MIB::rs232InSigEntry.
 */

#define RS_232_MIB_RS232INSIGPORTINDEX (1 << 0) 
#define RS_232_MIB_RS232INSIGNAME      (1 << 1) 
#define RS_232_MIB_RS232INSIGSTATE     (1 << 2) 
#define RS_232_MIB_RS232INSIGCHANGES   (1 << 3) 

typedef struct {
    gint32   rs232InSigPortIndex;
    gint32   rs232InSigName;
    gint32   *rs232InSigState;
    guint32  *rs232InSigChanges;
} rs_232_mib_rs232InSigEntry_t;

extern void
rs_232_mib_get_rs232InSigTable(GSnmpSession *s, rs_232_mib_rs232InSigEntry_t ***rs232InSigEntry, gint mask);

extern void
rs_232_mib_free_rs232InSigTable(rs_232_mib_rs232InSigEntry_t **rs232InSigEntry);

extern rs_232_mib_rs232InSigEntry_t *
rs_232_mib_new_rs232InSigEntry(void);

extern void
rs_232_mib_get_rs232InSigEntry(GSnmpSession *s, rs_232_mib_rs232InSigEntry_t **rs232InSigEntry, gint32 rs232InSigPortIndex, gint32 rs232InSigName, gint mask);

extern void
rs_232_mib_free_rs232InSigEntry(rs_232_mib_rs232InSigEntry_t *rs232InSigEntry);

/*
 * C type definitions for RS-232-MIB::rs232OutSigEntry.
 */

#define RS_232_MIB_RS232OUTSIGPORTINDEX (1 << 0) 
#define RS_232_MIB_RS232OUTSIGNAME      (1 << 1) 
#define RS_232_MIB_RS232OUTSIGSTATE     (1 << 2) 
#define RS_232_MIB_RS232OUTSIGCHANGES   (1 << 3) 

typedef struct {
    gint32   rs232OutSigPortIndex;
    gint32   rs232OutSigName;
    gint32   *rs232OutSigState;
    guint32  *rs232OutSigChanges;
} rs_232_mib_rs232OutSigEntry_t;

extern void
rs_232_mib_get_rs232OutSigTable(GSnmpSession *s, rs_232_mib_rs232OutSigEntry_t ***rs232OutSigEntry, gint mask);

extern void
rs_232_mib_free_rs232OutSigTable(rs_232_mib_rs232OutSigEntry_t **rs232OutSigEntry);

extern rs_232_mib_rs232OutSigEntry_t *
rs_232_mib_new_rs232OutSigEntry(void);

extern void
rs_232_mib_get_rs232OutSigEntry(GSnmpSession *s, rs_232_mib_rs232OutSigEntry_t **rs232OutSigEntry, gint32 rs232OutSigPortIndex, gint32 rs232OutSigName, gint mask);

extern void
rs_232_mib_free_rs232OutSigEntry(rs_232_mib_rs232OutSigEntry_t *rs232OutSigEntry);


#endif /* _RS_232_MIB_H_ */