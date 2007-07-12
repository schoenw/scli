/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.5:
 *   smidump -f scli SNMP-USER-BASED-SM-MIB
 *
 * Derived from SNMP-USER-BASED-SM-MIB:
 *   The management information definitions for the
 *   SNMP User-based Security Model.
 *   
 *   Copyright (C) The Internet Society (2002). This
 *   version of this MIB module is part of RFC 3414;
 *   see the RFC itself for full legal notices.
 *
 * Revision 2002-10-16 00:00:
 *   Changes in this revision:
 *   - Updated references and contact info.
 *   - Clarification to usmUserCloneFrom DESCRIPTION
 *     clause
 *   - Fixed 'command responder' into 'command generator'
 *     in last para of DESCRIPTION clause of
 *     usmUserTable.
 *   This revision published as RFC3414.
 *
 * Revision 1999-01-20 00:00:
 *   Clarifications, published as RFC2574
 *
 * Revision 1997-11-20 00:00:
 *   Initial version, published as RFC2274
 *
 * $Id$
 */

#ifndef _SNMP_USER_BASED_SM_MIB_H_
#define _SNMP_USER_BASED_SM_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map identities to strings and vice versa.
 */

#define SNMP_USER_BASED_SM_MIB_USMNOAUTHPROTOCOL	1,3,6,1,6,3,10,1,1,1
#define SNMP_USER_BASED_SM_MIB_USMHMACMD5AUTHPROTOCOL	1,3,6,1,6,3,10,1,1,2
#define SNMP_USER_BASED_SM_MIB_USMHMACSHAAUTHPROTOCOL	1,3,6,1,6,3,10,1,1,3
#define SNMP_USER_BASED_SM_MIB_USMNOPRIVPROTOCOL	1,3,6,1,6,3,10,1,2,1
#define SNMP_USER_BASED_SM_MIB_USMDESPRIVPROTOCOL	1,3,6,1,6,3,10,1,2,2

extern GNetSnmpIdentity const snmp_user_based_sm_mib_identities[];

/*
 * C type definitions for SNMP-USER-BASED-SM-MIB::usmStats.
 */

#define SNMP_USER_BASED_SM_MIB_USMSTATSUNSUPPORTEDSECLEVELS (1 << 0) 
#define SNMP_USER_BASED_SM_MIB_USMSTATSNOTINTIMEWINDOWS     (1 << 1) 
#define SNMP_USER_BASED_SM_MIB_USMSTATSUNKNOWNUSERNAMES     (1 << 2) 
#define SNMP_USER_BASED_SM_MIB_USMSTATSUNKNOWNENGINEIDS     (1 << 3) 
#define SNMP_USER_BASED_SM_MIB_USMSTATSWRONGDIGESTS         (1 << 4) 
#define SNMP_USER_BASED_SM_MIB_USMSTATSDECRYPTIONERRORS     (1 << 5) 

typedef struct {
    guint32  *usmStatsUnsupportedSecLevels;     /* ro SNMPv2-SMI::Counter32 */
    guint32  *usmStatsNotInTimeWindows;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *usmStatsUnknownUserNames;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *usmStatsUnknownEngineIDs;         /* ro SNMPv2-SMI::Counter32 */
    guint32  *usmStatsWrongDigests;             /* ro SNMPv2-SMI::Counter32 */
    guint32  *usmStatsDecryptionErrors;         /* ro SNMPv2-SMI::Counter32 */
} snmp_user_based_sm_mib_usmStats_t;

extern snmp_user_based_sm_mib_usmStats_t *
snmp_user_based_sm_mib_new_usmStats(void);

extern void
snmp_user_based_sm_mib_get_usmStats(GNetSnmp *s, snmp_user_based_sm_mib_usmStats_t **usmStats, gint64 mask);

extern void
snmp_user_based_sm_mib_free_usmStats(snmp_user_based_sm_mib_usmStats_t *usmStats);

/*
 * C type definitions for SNMP-USER-BASED-SM-MIB::usmUser.
 */

#define SNMP_USER_BASED_SM_MIB_USMUSERSPINLOCK (1 << 0) 

typedef struct {
    gint32   *usmUserSpinLock;     /* rw SNMPv2-TC::TestAndIncr */
} snmp_user_based_sm_mib_usmUser_t;

extern snmp_user_based_sm_mib_usmUser_t *
snmp_user_based_sm_mib_new_usmUser(void);

extern void
snmp_user_based_sm_mib_get_usmUser(GNetSnmp *s, snmp_user_based_sm_mib_usmUser_t **usmUser, gint64 mask);

extern void
snmp_user_based_sm_mib_set_usmUser(GNetSnmp *s, snmp_user_based_sm_mib_usmUser_t *usmUser, gint64 mask);

extern void
snmp_user_based_sm_mib_free_usmUser(snmp_user_based_sm_mib_usmUser_t *usmUser);

/*
 * C type definitions for SNMP-USER-BASED-SM-MIB::usmUserEntry.
 */

#define SNMP_USER_BASED_SM_MIB_USMUSERSECURITYNAME     (1 << 0) 
#define SNMP_USER_BASED_SM_MIB_USMUSERCLONEFROM        (1 << 1) 
#define SNMP_USER_BASED_SM_MIB_USMUSERAUTHPROTOCOL     (1 << 2) 
#define SNMP_USER_BASED_SM_MIB_USMUSERAUTHKEYCHANGE    (1 << 3) 
#define SNMP_USER_BASED_SM_MIB_USMUSEROWNAUTHKEYCHANGE (1 << 4) 
#define SNMP_USER_BASED_SM_MIB_USMUSERPRIVPROTOCOL     (1 << 5) 
#define SNMP_USER_BASED_SM_MIB_USMUSERPRIVKEYCHANGE    (1 << 6) 
#define SNMP_USER_BASED_SM_MIB_USMUSEROWNPRIVKEYCHANGE (1 << 7) 
#define SNMP_USER_BASED_SM_MIB_USMUSERPUBLIC           (1 << 8) 
#define SNMP_USER_BASED_SM_MIB_USMUSERSTORAGETYPE      (1 << 9) 
#define SNMP_USER_BASED_SM_MIB_USMUSERSTATUS           (1 << 10) 

typedef struct {
    guchar   usmUserEngineID[32];          /* na SNMP-FRAMEWORK-MIB::SnmpEngineID */
#define SNMP_USER_BASED_SM_MIB_USMUSERENGINEIDMINLENGTH 5
#define SNMP_USER_BASED_SM_MIB_USMUSERENGINEIDMAXLENGTH 32
    guint16  _usmUserEngineIDLength;
    guchar   usmUserName[32];              /* na */
#define SNMP_USER_BASED_SM_MIB_USMUSERNAMEMINLENGTH 1
#define SNMP_USER_BASED_SM_MIB_USMUSERNAMEMAXLENGTH 32
    guint16  _usmUserNameLength;
    guchar   *usmUserSecurityName;         /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define SNMP_USER_BASED_SM_MIB_USMUSERSECURITYNAMEMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSERSECURITYNAMEMAXLENGTH 255
    guint16  _usmUserSecurityNameLength;
    guint32  *usmUserCloneFrom;            /* rw SNMPv2-TC::RowPointer */
#define SNMP_USER_BASED_SM_MIB_USMUSERCLONEFROMMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSERCLONEFROMMAXLENGTH 128
    guint16  _usmUserCloneFromLength;
    guint32  *usmUserAuthProtocol;         /* rw SNMPv2-TC::AutonomousType */
#define SNMP_USER_BASED_SM_MIB_USMUSERAUTHPROTOCOLMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSERAUTHPROTOCOLMAXLENGTH 128
    guint16  _usmUserAuthProtocolLength;
    guchar   *usmUserAuthKeyChange;        /* rw SNMP-USER-BASED-SM-MIB::KeyChange */
#define SNMP_USER_BASED_SM_MIB_USMUSERAUTHKEYCHANGEMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSERAUTHKEYCHANGEMAXLENGTH 65535
    guint16  _usmUserAuthKeyChangeLength;
    guchar   *usmUserOwnAuthKeyChange;     /* rw SNMP-USER-BASED-SM-MIB::KeyChange */
#define SNMP_USER_BASED_SM_MIB_USMUSEROWNAUTHKEYCHANGEMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSEROWNAUTHKEYCHANGEMAXLENGTH 65535
    guint16  _usmUserOwnAuthKeyChangeLength;
    guint32  *usmUserPrivProtocol;         /* rw SNMPv2-TC::AutonomousType */
#define SNMP_USER_BASED_SM_MIB_USMUSERPRIVPROTOCOLMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSERPRIVPROTOCOLMAXLENGTH 128
    guint16  _usmUserPrivProtocolLength;
    guchar   *usmUserPrivKeyChange;        /* rw SNMP-USER-BASED-SM-MIB::KeyChange */
#define SNMP_USER_BASED_SM_MIB_USMUSERPRIVKEYCHANGEMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSERPRIVKEYCHANGEMAXLENGTH 65535
    guint16  _usmUserPrivKeyChangeLength;
    guchar   *usmUserOwnPrivKeyChange;     /* rw SNMP-USER-BASED-SM-MIB::KeyChange */
#define SNMP_USER_BASED_SM_MIB_USMUSEROWNPRIVKEYCHANGEMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSEROWNPRIVKEYCHANGEMAXLENGTH 65535
    guint16  _usmUserOwnPrivKeyChangeLength;
    guchar   *usmUserPublic;               /* rw */
#define SNMP_USER_BASED_SM_MIB_USMUSERPUBLICMINLENGTH 0
#define SNMP_USER_BASED_SM_MIB_USMUSERPUBLICMAXLENGTH 32
    guint16  _usmUserPublicLength;
    gint32   *usmUserStorageType;          /* rw SNMPv2-TC::StorageType */
    gint32   *usmUserStatus;               /* rw SNMPv2-TC::RowStatus */
} snmp_user_based_sm_mib_usmUserEntry_t;

extern void
snmp_user_based_sm_mib_get_usmUserTable(GNetSnmp *s, snmp_user_based_sm_mib_usmUserEntry_t ***usmUserEntry, gint64 mask);

extern void
snmp_user_based_sm_mib_free_usmUserTable(snmp_user_based_sm_mib_usmUserEntry_t **usmUserEntry);

extern snmp_user_based_sm_mib_usmUserEntry_t *
snmp_user_based_sm_mib_new_usmUserEntry(void);

extern void
snmp_user_based_sm_mib_get_usmUserEntry(GNetSnmp *s, snmp_user_based_sm_mib_usmUserEntry_t **usmUserEntry, guchar *usmUserEngineID, guint16 _usmUserEngineIDLength, guchar *usmUserName, guint16 _usmUserNameLength, gint64 mask);

extern void
snmp_user_based_sm_mib_set_usmUserEntry(GNetSnmp *s, snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry, gint64 mask);

extern void
snmp_user_based_sm_mib_free_usmUserEntry(snmp_user_based_sm_mib_usmUserEntry_t *usmUserEntry);


G_END_DECLS

#endif /* _SNMP_USER_BASED_SM_MIB_H_ */
