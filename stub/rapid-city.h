/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.4.2-pre1 for the scli package.
 *
 * Options:
 *   --scli-include='rcVlanEntry|rcVlanPortEntry'
 *
 * Derived from RAPID-CITY:
 *   Enterprise MIB for the Accelar product family.
 *
 * Revision 1997-01-01 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * $Id$
 */

#ifndef _RAPID_CITY_H_
#define _RAPID_CITY_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define RAPID_CITY_RCVLANACTION_NONE             1
#define RAPID_CITY_RCVLANACTION_FLUSHMACFDB      2
#define RAPID_CITY_RCVLANACTION_FLUSHARP         3
#define RAPID_CITY_RCVLANACTION_FLUSHIP          4
#define RAPID_CITY_RCVLANACTION_FLUSHDYNMEMB     5
#define RAPID_CITY_RCVLANACTION_ALL              6
#define RAPID_CITY_RCVLANACTION_FLUSHSNOOPMEMB   7
#define RAPID_CITY_RCVLANACTION_TRIGGERRIPUPDATE 8
#define RAPID_CITY_RCVLANACTION_FLUSHSNOOPMRTR   9

extern GSnmpEnum const rapid_city_enums_rcVlanAction[];

#define RAPID_CITY_RCVLANRESULT_NONE       1
#define RAPID_CITY_RCVLANRESULT_INPROGRESS 2
#define RAPID_CITY_RCVLANRESULT_SUCCESS    3
#define RAPID_CITY_RCVLANRESULT_FAIL       4

extern GSnmpEnum const rapid_city_enums_rcVlanResult[];

#define RAPID_CITY_RCVLANTYPE_BYPORT       1
#define RAPID_CITY_RCVLANTYPE_BYIPSUBNET   2
#define RAPID_CITY_RCVLANTYPE_BYPROTOCOLID 3
#define RAPID_CITY_RCVLANTYPE_BYSRCMAC     4
#define RAPID_CITY_RCVLANTYPE_BYDSTMCAST   5

extern GSnmpEnum const rapid_city_enums_rcVlanType[];

#define RAPID_CITY_RCVLANPROTOCOLID_NONE         0
#define RAPID_CITY_RCVLANPROTOCOLID_IP           1
#define RAPID_CITY_RCVLANPROTOCOLID_IPX802DOT3   2
#define RAPID_CITY_RCVLANPROTOCOLID_IPX802DOT2   3
#define RAPID_CITY_RCVLANPROTOCOLID_IPXSNAP      4
#define RAPID_CITY_RCVLANPROTOCOLID_IPXETHERNET2 5
#define RAPID_CITY_RCVLANPROTOCOLID_APPLETALK    6
#define RAPID_CITY_RCVLANPROTOCOLID_DECLAT       7
#define RAPID_CITY_RCVLANPROTOCOLID_DECOTHER     8
#define RAPID_CITY_RCVLANPROTOCOLID_SNA802DOT2   9
#define RAPID_CITY_RCVLANPROTOCOLID_SNAETHERNET2 10
#define RAPID_CITY_RCVLANPROTOCOLID_NETBIOS      11
#define RAPID_CITY_RCVLANPROTOCOLID_XNS          12
#define RAPID_CITY_RCVLANPROTOCOLID_VINES        13
#define RAPID_CITY_RCVLANPROTOCOLID_IPV6         14
#define RAPID_CITY_RCVLANPROTOCOLID_USRDEFINED   15
#define RAPID_CITY_RCVLANPROTOCOLID_RARP         16

extern GSnmpEnum const rapid_city_enums_rcVlanProtocolId[];

#define RAPID_CITY_RCVLANPORTTYPE_ACCESS 1
#define RAPID_CITY_RCVLANPORTTYPE_TRUNK  2

extern GSnmpEnum const rapid_city_enums_rcVlanPortType[];


/*
 * C type definitions for RAPID-CITY::rcVlanEntry.
 */

#define RAPID_CITY_RCVLANID                          (1 << 0) 
#define RAPID_CITY_RCVLANNAME                        (1 << 1) 
#define RAPID_CITY_RCVLANCOLOR                       (1 << 2) 
#define RAPID_CITY_RCVLANHIGHPRIORITY                (1 << 3) 
#define RAPID_CITY_RCVLANROUTINGENABLE               (1 << 4) 
#define RAPID_CITY_RCVLANIFINDEX                     (1 << 5) 
#define RAPID_CITY_RCVLANACTION                      (1 << 6) 
#define RAPID_CITY_RCVLANRESULT                      (1 << 7) 
#define RAPID_CITY_RCVLANSTGID                       (1 << 8) 
#define RAPID_CITY_RCVLANTYPE                        (1 << 9) 
#define RAPID_CITY_RCVLANPORTMEMBERS                 (1 << 10) 
#define RAPID_CITY_RCVLANACTIVEMEMBERS               (1 << 11) 
#define RAPID_CITY_RCVLANSTATICMEMBERS               (1 << 12) 
#define RAPID_CITY_RCVLANNOTALLOWTOJOIN              (1 << 13) 
#define RAPID_CITY_RCVLANPROTOCOLID                  (1 << 14) 
#define RAPID_CITY_RCVLANSUBNETADDR                  (1 << 15) 
#define RAPID_CITY_RCVLANSUBNETMASK                  (1 << 16) 
#define RAPID_CITY_RCVLANAGINGTIME                   (1 << 17) 
#define RAPID_CITY_RCVLANMACADDRESS                  (1 << 18) 
#define RAPID_CITY_RCVLANROWSTATUS                   (1 << 19) 
#define RAPID_CITY_RCVLANIGMPSNOOPENABLE             (1 << 20) 
#define RAPID_CITY_RCVLANIGMPSNOOPREPORTPROXYENABLE  (1 << 21) 
#define RAPID_CITY_RCVLANIGMPSNOOPROBUSTNESS         (1 << 22) 
#define RAPID_CITY_RCVLANIGMPSNOOPQUERYINTERVAL      (1 << 23) 
#define RAPID_CITY_RCVLANIGMPSNOOPMROUTERPORTS       (1 << 24) 
#define RAPID_CITY_RCVLANUSERDEFINEDPID              (1 << 25) 
#define RAPID_CITY_RCVLANIGMPSNOOPACTIVEMROUTERPORTS (1 << 26) 
#define RAPID_CITY_RCVLANPROTOCOLIDS                 (1 << 27) 
#define RAPID_CITY_RCVLANIGMPSNOOPACTIVEQUERIER      (1 << 28) 
#define RAPID_CITY_RCVLANIGMPSNOOPMROUTEREXPIRATION  (1 << 29) 
#define RAPID_CITY_RCVLANIGMPSNOOPQUERIERPORT        (1 << 30) 

typedef struct {
    gint32   rcVlanId;                               /* ro */
    guchar   *rcVlanName;                            /* rw */
#define RAPID_CITY_RCVLANNAMEMINLENGTH 0
#define RAPID_CITY_RCVLANNAMEMAXLENGTH 20
    guint16  _rcVlanNameLength;
    gint32   *rcVlanColor;                           /* rw */
    gint32   *rcVlanHighPriority;                    /* rw SNMPv2-TC::TruthValue */
    gint32   *rcVlanRoutingEnable;                   /* rw SNMPv2-TC::TruthValue */
    gint32   *rcVlanIfIndex;                         /* ro RAPID-CITY::InterfaceIndex */
    gint32   *rcVlanAction;                          /* rw */
    gint32   *rcVlanResult;                          /* ro */
    gint32   *rcVlanStgId;                           /* rw */
    gint32   *rcVlanType;                            /* rw */
    guchar   *rcVlanPortMembers;                     /* rw RAPID-CITY::PortSet */
#define RAPID_CITY_RCVLANPORTMEMBERSLENGTH 32
    guchar   *rcVlanActiveMembers;                   /* ro RAPID-CITY::PortSet */
#define RAPID_CITY_RCVLANACTIVEMEMBERSLENGTH 32
    guchar   *rcVlanStaticMembers;                   /* rw RAPID-CITY::PortSet */
#define RAPID_CITY_RCVLANSTATICMEMBERSLENGTH 32
    guchar   *rcVlanNotAllowToJoin;                  /* rw RAPID-CITY::PortSet */
#define RAPID_CITY_RCVLANNOTALLOWTOJOINLENGTH 32
    gint32   *rcVlanProtocolId;                      /* rw */
    guchar   *rcVlanSubnetAddr;                      /* rw SNMPv2-SMI::IpAddress */
#define RAPID_CITY_RCVLANSUBNETADDRLENGTH 4
    guchar   *rcVlanSubnetMask;                      /* rw SNMPv2-SMI::IpAddress */
#define RAPID_CITY_RCVLANSUBNETMASKLENGTH 4
    gint32   *rcVlanAgingTime;                       /* rw */
    guchar   *rcVlanMacAddress;                      /* ro SNMPv2-TC::MacAddress */
#define RAPID_CITY_RCVLANMACADDRESSLENGTH 6
    gint32   *rcVlanRowStatus;                       /* rw SNMPv2-TC::RowStatus */
    gint32   *rcVlanIgmpSnoopEnable;                 /* rw SNMPv2-TC::TruthValue */
    gint32   *rcVlanIgmpSnoopReportProxyEnable;      /* rw SNMPv2-TC::TruthValue */
    gint32   *rcVlanIgmpSnoopRobustness;             /* rw */
    gint32   *rcVlanIgmpSnoopQueryInterval;          /* rw */
    guchar   *rcVlanIgmpSnoopMRouterPorts;           /* rw RAPID-CITY::PortSet */
#define RAPID_CITY_RCVLANIGMPSNOOPMROUTERPORTSLENGTH 32
    gint32   *rcVlanUserDefinedPid;                  /* rw Integer32 */
    guchar   *rcVlanIgmpSnoopActiveMRouterPorts;     /* ro RAPID-CITY::PortSet */
#define RAPID_CITY_RCVLANIGMPSNOOPACTIVEMROUTERPORTSLENGTH 32
    gint32   *rcVlanProtocolIds;                     /* rw Integer32 */
    guchar   *rcVlanIgmpSnoopActiveQuerier;          /* ro SNMPv2-SMI::IpAddress */
#define RAPID_CITY_RCVLANIGMPSNOOPACTIVEQUERIERLENGTH 4
    gint32   *rcVlanIgmpSnoopMRouterExpiration;      /* ro Integer32 */
    gint32   *rcVlanIgmpSnoopQuerierPort;            /* ro RAPID-CITY::InterfaceIndex */
} rapid_city_rcVlanEntry_t;

extern void
rapid_city_get_rcVlanTable(GSnmpSession *s, rapid_city_rcVlanEntry_t ***rcVlanEntry, gint64 mask);

extern void
rapid_city_free_rcVlanTable(rapid_city_rcVlanEntry_t **rcVlanEntry);

extern rapid_city_rcVlanEntry_t *
rapid_city_new_rcVlanEntry(void);

extern void
rapid_city_get_rcVlanEntry(GSnmpSession *s, rapid_city_rcVlanEntry_t **rcVlanEntry, gint32 rcVlanId, gint64 mask);

extern void
rapid_city_set_rcVlanEntry(GSnmpSession *s, rapid_city_rcVlanEntry_t *rcVlanEntry, gint64 mask);

extern void
rapid_city_free_rcVlanEntry(rapid_city_rcVlanEntry_t *rcVlanEntry);

/*
 * C type definitions for RAPID-CITY::rcVlanPortEntry.
 */

#define RAPID_CITY_RCVLANPORTINDEX                 (1 << 0) 
#define RAPID_CITY_RCVLANPORTNUMVLANIDS            (1 << 1) 
#define RAPID_CITY_RCVLANPORTVLANIDS               (1 << 2) 
#define RAPID_CITY_RCVLANPORTTYPE                  (1 << 3) 
#define RAPID_CITY_RCVLANPORTDISCARDTAGGEDFRAMES   (1 << 4) 
#define RAPID_CITY_RCVLANPORTDISCARDUNTAGGEDFRAMES (1 << 5) 
#define RAPID_CITY_RCVLANPORTDEFAULTVLANID         (1 << 6) 
#define RAPID_CITY_RCVLANPORTPERFORMTAGGING        (1 << 7) 

typedef struct {
    gint32   rcVlanPortIndex;                      /* ro Integer32 */
    gint32   *rcVlanPortNumVlanIds;                /* ro Integer32 */
    guchar   *rcVlanPortVlanIds;                   /* rw */
#define RAPID_CITY_RCVLANPORTVLANIDSLENGTH 250
    gint32   *rcVlanPortType;                      /* rw */
    gint32   *rcVlanPortDiscardTaggedFrames;       /* rw SNMPv2-TC::TruthValue */
    gint32   *rcVlanPortDiscardUntaggedFrames;     /* rw SNMPv2-TC::TruthValue */
    gint32   *rcVlanPortDefaultVlanId;             /* rw */
    gint32   *rcVlanPortPerformTagging;            /* rw SNMPv2-TC::TruthValue */
} rapid_city_rcVlanPortEntry_t;

extern void
rapid_city_get_rcVlanPortTable(GSnmpSession *s, rapid_city_rcVlanPortEntry_t ***rcVlanPortEntry, gint64 mask);

extern void
rapid_city_free_rcVlanPortTable(rapid_city_rcVlanPortEntry_t **rcVlanPortEntry);

extern rapid_city_rcVlanPortEntry_t *
rapid_city_new_rcVlanPortEntry(void);

extern void
rapid_city_get_rcVlanPortEntry(GSnmpSession *s, rapid_city_rcVlanPortEntry_t **rcVlanPortEntry, gint32 rcVlanPortIndex, gint64 mask);

extern void
rapid_city_set_rcVlanPortEntry(GSnmpSession *s, rapid_city_rcVlanPortEntry_t *rcVlanPortEntry, gint64 mask);

extern void
rapid_city_free_rcVlanPortEntry(rapid_city_rcVlanPortEntry_t *rcVlanPortEntry);


G_END_DECLS

#endif /* _RAPID_CITY_H_ */
