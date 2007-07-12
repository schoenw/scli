/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli \
 *     --scli-include='a3ComVlanIfEntry|a3ComVirtualGroup' PRODUCTMIB
 *
 * Derived from PRODUCTMIB:
 *
 * $Id$
 */

#ifndef _PRODUCTMIB_H_
#define _PRODUCTMIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define PRODUCTMIB_ENTRYSTATUS_VALID         1
#define PRODUCTMIB_ENTRYSTATUS_CREATEREQUEST 2
#define PRODUCTMIB_ENTRYSTATUS_UNDERCREATION 3
#define PRODUCTMIB_ENTRYSTATUS_INVALID       4

extern GNetSnmpEnum const productmib_enums_EntryStatus[];

#define PRODUCTMIB_ROWSTATUS_ACTIVE        1
#define PRODUCTMIB_ROWSTATUS_NOTINSERVICE  2
#define PRODUCTMIB_ROWSTATUS_NOTREADY      3
#define PRODUCTMIB_ROWSTATUS_CREATEANDGO   4
#define PRODUCTMIB_ROWSTATUS_CREATEANDWAIT 5
#define PRODUCTMIB_ROWSTATUS_DESTROY       6

extern GNetSnmpEnum const productmib_enums_RowStatus[];

#define PRODUCTMIB_A3COMVLANTYPE_VLANLAYER2            1
#define PRODUCTMIB_A3COMVLANTYPE_VLANDEFAULTPROTOCOLS  2
#define PRODUCTMIB_A3COMVLANTYPE_VLANIPPROTOCOL        3
#define PRODUCTMIB_A3COMVLANTYPE_VLANIPXPROTOCOL       4
#define PRODUCTMIB_A3COMVLANTYPE_VLANAPPLETALKPROTOCOL 5
#define PRODUCTMIB_A3COMVLANTYPE_VLANXNSPROTOCOL       6
#define PRODUCTMIB_A3COMVLANTYPE_VLANISOPROTOCOL       7
#define PRODUCTMIB_A3COMVLANTYPE_VLANDECNETPROTOCOL    8
#define PRODUCTMIB_A3COMVLANTYPE_VLANNETBIOSPROTOCOL   9
#define PRODUCTMIB_A3COMVLANTYPE_VLANSNAPROTOCOL       10
#define PRODUCTMIB_A3COMVLANTYPE_VLANVINESPROTOCOL     11
#define PRODUCTMIB_A3COMVLANTYPE_VLANX25PROTOCOL       12
#define PRODUCTMIB_A3COMVLANTYPE_VLANIGMPPROTOCOL      13

extern GNetSnmpEnum const productmib_enums_A3ComVlanType[];

#define PRODUCTMIB_A3COMVLANENCAPSTYPE_VLANENCAPS3COMPROPRIETARYPDD 1
#define PRODUCTMIB_A3COMVLANENCAPSTYPE_VLANENCAPS8021Q              2
#define PRODUCTMIB_A3COMVLANENCAPSTYPE_VLANENCAPSPRE8021QONCORE     3

extern GNetSnmpEnum const productmib_enums_A3ComVlanEncapsType[];

#define PRODUCTMIB_TRUTHVALUE_TRUE  1
#define PRODUCTMIB_TRUTHVALUE_FALSE 2

extern GNetSnmpEnum const productmib_enums_TruthValue[];


/*
 * Tables to map notifications to strings and vice versa.
 */

#define PRODUCTMIB_COLDSTART	1,3,6,1,2,1,11,0,0
#define PRODUCTMIB_WARMSTART	1,3,6,1,2,1,11,0,1
#define PRODUCTMIB_LINKDOWN	1,3,6,1,2,1,11,0,2
#define PRODUCTMIB_LINKUP	1,3,6,1,2,1,11,0,3
#define PRODUCTMIB_AUTHENTICATIONFAILURE	1,3,6,1,2,1,11,0,4
#define PRODUCTMIB_RISINGALARM	1,3,6,1,2,1,16,0,1
#define PRODUCTMIB_FALLINGALARM	1,3,6,1,2,1,16,0,2
#define PRODUCTMIB_NEWROOT	1,3,6,1,2,1,17,0,1
#define PRODUCTMIB_TOPOLOGYCHANGE	1,3,6,1,2,1,17,0,2
#define PRODUCTMIB_RESRESILIENCESWITCH	1,3,6,1,4,1,43,0,43
#define PRODUCTMIB_RESSTATECHANGE	1,3,6,1,4,1,43,0,44
#define PRODUCTMIB_BRDATABASEFULL	1,3,6,1,4,1,43,0,65
#define PRODUCTMIB_SECUREADDRESSLEARNED	1,3,6,1,4,1,43,0,71
#define PRODUCTMIB_REMPOLLSUCCESSTRAP	1,3,6,1,4,1,43,0,74
#define PRODUCTMIB_REMPOLLFAILURETRAP	1,3,6,1,4,1,43,0,75
#define PRODUCTMIB_EVENTGENERICTRAP	1,3,6,1,4,1,43,0,82
#define PRODUCTMIB_BRDESKTOPMISCONFIGURATION	1,3,6,1,4,1,43,0,83
#define PRODUCTMIB_SECUREADDRESSLEARNED2	1,3,6,1,4,1,43,0,85
#define PRODUCTMIB_SECUREVIOLATION3	1,3,6,1,4,1,43,0,86

extern GNetSnmpIdentity const productmib_notifications[];

/*
 * C type definitions for PRODUCTMIB::a3ComVlanIfEntry.
 */

#define PRODUCTMIB_A3COMVLANIFDESCR            (1 << 0) 
#define PRODUCTMIB_A3COMVLANIFTYPE             (1 << 1) 
#define PRODUCTMIB_A3COMVLANIFGLOBALIDENTIFIER (1 << 2) 
#define PRODUCTMIB_A3COMVLANIFINFO             (1 << 3) 
#define PRODUCTMIB_A3COMVLANIFSTATUS           (1 << 4) 

typedef struct {
    gint32   a3ComVlanIfIndex;                 /* na Integer32 */
    guchar   *a3ComVlanIfDescr;                /* rw */
#define PRODUCTMIB_A3COMVLANIFDESCRMINLENGTH 0
#define PRODUCTMIB_A3COMVLANIFDESCRMAXLENGTH 80
    guint16  _a3ComVlanIfDescrLength;
    gint32   *a3ComVlanIfType;                 /* rw PRODUCTMIB::A3ComVlanType */
    gint32   *a3ComVlanIfGlobalIdentifier;     /* rw */
    guchar   *a3ComVlanIfInfo;                 /* ro OctetString */
#define PRODUCTMIB_A3COMVLANIFINFOMINLENGTH 0
#define PRODUCTMIB_A3COMVLANIFINFOMAXLENGTH 65535
    guint16  _a3ComVlanIfInfoLength;
    gint32   *a3ComVlanIfStatus;               /* rw PRODUCTMIB::RowStatus */
} productmib_a3ComVlanIfEntry_t;

extern void
productmib_get_a3ComVlanIfTable(GNetSnmp *s, productmib_a3ComVlanIfEntry_t ***a3ComVlanIfEntry, gint64 mask);

extern void
productmib_free_a3ComVlanIfTable(productmib_a3ComVlanIfEntry_t **a3ComVlanIfEntry);

extern productmib_a3ComVlanIfEntry_t *
productmib_new_a3ComVlanIfEntry(void);

extern void
productmib_get_a3ComVlanIfEntry(GNetSnmp *s, productmib_a3ComVlanIfEntry_t **a3ComVlanIfEntry, gint32 a3ComVlanIfIndex, gint64 mask);

extern void
productmib_set_a3ComVlanIfEntry(GNetSnmp *s, productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry, gint64 mask);

extern void
productmib_free_a3ComVlanIfEntry(productmib_a3ComVlanIfEntry_t *a3ComVlanIfEntry);

/*
 * C type definitions for PRODUCTMIB::a3ComVirtualGroup.
 */

#define PRODUCTMIB_A3COMNEXTAVAILABLEVIRTIFINDEX (1 << 0) 

typedef struct {
    gint32   *a3ComNextAvailableVirtIfIndex;     /* ro Integer32 */
} productmib_a3ComVirtualGroup_t;

extern productmib_a3ComVirtualGroup_t *
productmib_new_a3ComVirtualGroup(void);

extern void
productmib_get_a3ComVirtualGroup(GNetSnmp *s, productmib_a3ComVirtualGroup_t **a3ComVirtualGroup, gint64 mask);

extern void
productmib_free_a3ComVirtualGroup(productmib_a3ComVirtualGroup_t *a3ComVirtualGroup);


G_END_DECLS

#endif /* _PRODUCTMIB_H_ */
