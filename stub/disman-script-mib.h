/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.16 for the scli package.
 *
 * Derived from DISMAN-SCRIPT-MIB:
 *   This MIB module defines a set of objects that allow to
 *   delegate management scripts to distributed managers.
 *
 * Revision 2001-06-08 00:00:
 *   Revised version, published as RFC XXXX.
 *   
 *   This revision introduces several new objects: smScriptError,
 *   smScriptLastChange, smLaunchError, smLaunchLastChange,
 *   smLaunchRowExpireTime, smRunResultTime, and smRunErrorTime.
 *   
 *   The following existing objects were updated: the maximum
 *   value of smRunLifeTime now disables the timer, an
 *   autostart value was added to the smLaunchAdminStatus
 *   object, and a new expired state was added to the
 *   smLaunchOperStatus object.
 *   
 *   A new smScriptException notification has been added to
 *   support runtime error notifications.
 *   
 *   Created new conformance and compliance statements that
 *   take care of the new objects and notifications.
 *   
 *   Clarifications have been added in several places to remove
 *   ambiguities or contradictions that were discovered and
 *   reported by implementors.
 *
 * Revision 1999-02-22 18:00:
 *   Initial version, published as RFC 2592.
 *
 * $Id$
 */

#ifndef _DISMAN_SCRIPT_MIB_H_
#define _DISMAN_SCRIPT_MIB_H_

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_ENABLED	1
#define DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_DISABLED	2
#define DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_EDITING	3

extern GSnmpEnum const disman_script_mib_enums_smScriptAdminStatus[];

#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_ENABLED	1
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_DISABLED	2
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_EDITING	3
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_RETRIEVING	4
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_COMPILING	5
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_NOSUCHSCRIPT	6
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_ACCESSDENIED	7
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_WRONGLANGUAGE	8
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_WRONGVERSION	9
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_COMPILATIONFAILED	10
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_NORESOURCESLEFT	11
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_UNKNOWNPROTOCOL	12
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_PROTOCOLFAILURE	13
#define DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_GENERICERROR	14

extern GSnmpEnum const disman_script_mib_enums_smScriptOperStatus[];

#define DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_OTHER	1
#define DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_VOLATILE	2
#define DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_NONVOLATILE	3
#define DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_PERMANENT	4
#define DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_READONLY	5

extern GSnmpEnum const disman_script_mib_enums_smScriptStorageType[];

#define DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_ACTIVE	1
#define DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_NOTINSERVICE	2
#define DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_NOTREADY	3
#define DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_CREATEANDGO	4
#define DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_CREATEANDWAIT	5
#define DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_DESTROY	6

extern GSnmpEnum const disman_script_mib_enums_smScriptRowStatus[];

#define DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_ACTIVE	1
#define DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_NOTINSERVICE	2
#define DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_NOTREADY	3
#define DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_CREATEANDGO	4
#define DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_CREATEANDWAIT	5
#define DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_DESTROY	6

extern GSnmpEnum const disman_script_mib_enums_smCodeRowStatus[];

#define DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_ABORT	1
#define DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_SUSPEND	2
#define DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_RESUME	3
#define DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_NOP	4

extern GSnmpEnum const disman_script_mib_enums_smLaunchControl[];

#define DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_ENABLED	1
#define DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_DISABLED	2
#define DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_AUTOSTART	3

extern GSnmpEnum const disman_script_mib_enums_smLaunchAdminStatus[];

#define DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_ENABLED	1
#define DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_DISABLED	2
#define DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_EXPIRED	3

extern GSnmpEnum const disman_script_mib_enums_smLaunchOperStatus[];

#define DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_OTHER	1
#define DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_VOLATILE	2
#define DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_NONVOLATILE	3
#define DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_PERMANENT	4
#define DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_READONLY	5

extern GSnmpEnum const disman_script_mib_enums_smLaunchStorageType[];

#define DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_ACTIVE	1
#define DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_NOTINSERVICE	2
#define DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_NOTREADY	3
#define DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_CREATEANDGO	4
#define DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_CREATEANDWAIT	5
#define DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_DESTROY	6

extern GSnmpEnum const disman_script_mib_enums_smLaunchRowStatus[];

#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_NOERROR	1
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_HALTED	2
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_LIFETIMEEXCEEDED	3
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_NORESOURCESLEFT	4
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_LANGUAGEERROR	5
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_RUNTIMEERROR	6
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_INVALIDARGUMENT	7
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_SECURITYVIOLATION	8
#define DISMAN_SCRIPT_MIB_SMRUNEXITCODE_GENERICERROR	9

extern GSnmpEnum const disman_script_mib_enums_smRunExitCode[];

#define DISMAN_SCRIPT_MIB_SMRUNCONTROL_ABORT	1
#define DISMAN_SCRIPT_MIB_SMRUNCONTROL_SUSPEND	2
#define DISMAN_SCRIPT_MIB_SMRUNCONTROL_RESUME	3
#define DISMAN_SCRIPT_MIB_SMRUNCONTROL_NOP	4

extern GSnmpEnum const disman_script_mib_enums_smRunControl[];

#define DISMAN_SCRIPT_MIB_SMRUNSTATE_INITIALIZING	1
#define DISMAN_SCRIPT_MIB_SMRUNSTATE_EXECUTING	2
#define DISMAN_SCRIPT_MIB_SMRUNSTATE_SUSPENDING	3
#define DISMAN_SCRIPT_MIB_SMRUNSTATE_SUSPENDED	4
#define DISMAN_SCRIPT_MIB_SMRUNSTATE_RESUMING	5
#define DISMAN_SCRIPT_MIB_SMRUNSTATE_ABORTING	6
#define DISMAN_SCRIPT_MIB_SMRUNSTATE_TERMINATED	7

extern GSnmpEnum const disman_script_mib_enums_smRunState[];


/*
 * C type definitions for DISMAN-SCRIPT-MIB::smLangEntry.
 */

typedef struct {
    gint32   smLangIndex;
    guint32  *smLangLanguage;
    gsize    _smLangLanguageLength;
    guchar   *smLangVersion;
    gsize    _smLangVersionLength;
    guint32  *smLangVendor;
    gsize    _smLangVendorLength;
    guchar   *smLangRevision;
    gsize    _smLangRevisionLength;
    guchar   *smLangDescr;
    gsize    _smLangDescrLength;
} disman_script_mib_smLangEntry_t;

extern int
disman_script_mib_get_smLangTable(GSnmpSession *s, disman_script_mib_smLangEntry_t ***smLangEntry);

extern void
disman_script_mib_free_smLangTable(disman_script_mib_smLangEntry_t **smLangEntry);

extern disman_script_mib_smLangEntry_t *
disman_script_mib_new_smLangEntry();

extern int
disman_script_mib_get_smLangEntry(GSnmpSession *s, disman_script_mib_smLangEntry_t **smLangEntry);

extern void
disman_script_mib_free_smLangEntry(disman_script_mib_smLangEntry_t *smLangEntry);

/*
 * C type definitions for DISMAN-SCRIPT-MIB::smExtsnEntry.
 */

typedef struct {
    gint32   smLangIndex;
    gint32   smExtsnIndex;
    guint32  *smExtsnExtension;
    gsize    _smExtsnExtensionLength;
    guchar   *smExtsnVersion;
    gsize    _smExtsnVersionLength;
    guint32  *smExtsnVendor;
    gsize    _smExtsnVendorLength;
    guchar   *smExtsnRevision;
    gsize    _smExtsnRevisionLength;
    guchar   *smExtsnDescr;
    gsize    _smExtsnDescrLength;
} disman_script_mib_smExtsnEntry_t;

extern int
disman_script_mib_get_smExtsnTable(GSnmpSession *s, disman_script_mib_smExtsnEntry_t ***smExtsnEntry);

extern void
disman_script_mib_free_smExtsnTable(disman_script_mib_smExtsnEntry_t **smExtsnEntry);

extern disman_script_mib_smExtsnEntry_t *
disman_script_mib_new_smExtsnEntry();

extern int
disman_script_mib_get_smExtsnEntry(GSnmpSession *s, disman_script_mib_smExtsnEntry_t **smExtsnEntry);

extern void
disman_script_mib_free_smExtsnEntry(disman_script_mib_smExtsnEntry_t *smExtsnEntry);

/*
 * C type definitions for DISMAN-SCRIPT-MIB::smScriptEntry.
 */

typedef struct {
    guchar   smScriptOwner[32];
    gsize    _smScriptOwnerLength;
    guchar   smScriptName[32];
    gsize    _smScriptNameLength;
    guchar   *smScriptDescr;
    gsize    _smScriptDescrLength;
    gint32   *smScriptLanguage;
    guchar   *smScriptSource;
    gsize    _smScriptSourceLength;
    gint32   *smScriptAdminStatus;
    gint32   *smScriptOperStatus;
    gint32   *smScriptStorageType;
    gint32   *smScriptRowStatus;
    guchar   *smScriptError;
    gsize    _smScriptErrorLength;
    guchar   *smScriptLastChange;
    gsize    _smScriptLastChangeLength;
} disman_script_mib_smScriptEntry_t;

extern int
disman_script_mib_get_smScriptTable(GSnmpSession *s, disman_script_mib_smScriptEntry_t ***smScriptEntry);

extern void
disman_script_mib_free_smScriptTable(disman_script_mib_smScriptEntry_t **smScriptEntry);

extern disman_script_mib_smScriptEntry_t *
disman_script_mib_new_smScriptEntry();

extern int
disman_script_mib_get_smScriptEntry(GSnmpSession *s, disman_script_mib_smScriptEntry_t **smScriptEntry);

extern int
disman_script_mib_set_smScriptEntry(GSnmpSession *s, disman_script_mib_smScriptEntry_t *smScriptEntry);

extern void
disman_script_mib_free_smScriptEntry(disman_script_mib_smScriptEntry_t *smScriptEntry);

/*
 * C type definitions for DISMAN-SCRIPT-MIB::smCodeEntry.
 */

typedef struct {
    guchar   smScriptOwner[32];
    gsize    _smScriptOwnerLength;
    guchar   smScriptName[32];
    gsize    _smScriptNameLength;
    guint32  smCodeIndex;
    guchar   *smCodeText;
    gsize    _smCodeTextLength;
    gint32   *smCodeRowStatus;
} disman_script_mib_smCodeEntry_t;

extern int
disman_script_mib_get_smCodeTable(GSnmpSession *s, disman_script_mib_smCodeEntry_t ***smCodeEntry);

extern void
disman_script_mib_free_smCodeTable(disman_script_mib_smCodeEntry_t **smCodeEntry);

extern disman_script_mib_smCodeEntry_t *
disman_script_mib_new_smCodeEntry();

extern int
disman_script_mib_get_smCodeEntry(GSnmpSession *s, disman_script_mib_smCodeEntry_t **smCodeEntry);

extern int
disman_script_mib_set_smCodeEntry(GSnmpSession *s, disman_script_mib_smCodeEntry_t *smCodeEntry);

extern void
disman_script_mib_free_smCodeEntry(disman_script_mib_smCodeEntry_t *smCodeEntry);

/*
 * C type definitions for DISMAN-SCRIPT-MIB::smLaunchEntry.
 */

typedef struct {
    guchar   smLaunchOwner[32];
    gsize    _smLaunchOwnerLength;
    guchar   smLaunchName[32];
    gsize    _smLaunchNameLength;
    guchar   *smLaunchScriptOwner;
    gsize    _smLaunchScriptOwnerLength;
    guchar   *smLaunchScriptName;
    gsize    _smLaunchScriptNameLength;
    guchar   *smLaunchArgument;
    gsize    _smLaunchArgumentLength;
    guint32  *smLaunchMaxRunning;
    guint32  *smLaunchMaxCompleted;
    gint32   *smLaunchLifeTime;
    gint32   *smLaunchExpireTime;
    gint32   *smLaunchStart;
    gint32   *smLaunchControl;
    gint32   *smLaunchAdminStatus;
    gint32   *smLaunchOperStatus;
    gint32   *smLaunchRunIndexNext;
    gint32   *smLaunchStorageType;
    gint32   *smLaunchRowStatus;
    guchar   *smLaunchError;
    gsize    _smLaunchErrorLength;
    guchar   *smLaunchLastChange;
    gsize    _smLaunchLastChangeLength;
    gint32   *smLaunchRowExpireTime;
} disman_script_mib_smLaunchEntry_t;

extern int
disman_script_mib_get_smLaunchTable(GSnmpSession *s, disman_script_mib_smLaunchEntry_t ***smLaunchEntry);

extern void
disman_script_mib_free_smLaunchTable(disman_script_mib_smLaunchEntry_t **smLaunchEntry);

extern disman_script_mib_smLaunchEntry_t *
disman_script_mib_new_smLaunchEntry();

extern int
disman_script_mib_get_smLaunchEntry(GSnmpSession *s, disman_script_mib_smLaunchEntry_t **smLaunchEntry);

extern int
disman_script_mib_set_smLaunchEntry(GSnmpSession *s, disman_script_mib_smLaunchEntry_t *smLaunchEntry);

extern void
disman_script_mib_free_smLaunchEntry(disman_script_mib_smLaunchEntry_t *smLaunchEntry);

/*
 * C type definitions for DISMAN-SCRIPT-MIB::smRunEntry.
 */

typedef struct {
    guchar   smLaunchOwner[32];
    gsize    _smLaunchOwnerLength;
    guchar   smLaunchName[32];
    gsize    _smLaunchNameLength;
    gint32   smRunIndex;
    guchar   *smRunArgument;
    gsize    _smRunArgumentLength;
    guchar   *smRunStartTime;
    gsize    _smRunStartTimeLength;
    guchar   *smRunEndTime;
    gsize    _smRunEndTimeLength;
    gint32   *smRunLifeTime;
    gint32   *smRunExpireTime;
    gint32   *smRunExitCode;
    guchar   *smRunResult;
    gsize    _smRunResultLength;
    gint32   *smRunControl;
    gint32   *smRunState;
    guchar   *smRunError;
    gsize    _smRunErrorLength;
    guchar   *smRunResultTime;
    gsize    _smRunResultTimeLength;
    guchar   *smRunErrorTime;
    gsize    _smRunErrorTimeLength;
} disman_script_mib_smRunEntry_t;

extern int
disman_script_mib_get_smRunTable(GSnmpSession *s, disman_script_mib_smRunEntry_t ***smRunEntry);

extern void
disman_script_mib_free_smRunTable(disman_script_mib_smRunEntry_t **smRunEntry);

extern disman_script_mib_smRunEntry_t *
disman_script_mib_new_smRunEntry();

extern int
disman_script_mib_get_smRunEntry(GSnmpSession *s, disman_script_mib_smRunEntry_t **smRunEntry);

extern int
disman_script_mib_set_smRunEntry(GSnmpSession *s, disman_script_mib_smRunEntry_t *smRunEntry);

extern void
disman_script_mib_free_smRunEntry(disman_script_mib_smRunEntry_t *smRunEntry);


#endif /* _DISMAN_SCRIPT_MIB_H_ */
