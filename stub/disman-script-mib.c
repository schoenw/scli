/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from DISMAN-SCRIPT-MIB:
 *   This MIB module defines a set of objects that allow to
 *   delegate management scripts to distributed managers.
 *
 * Revision 2001-04-03 00:00:
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
 *   Clarifications have been added in several places to remove
 *   ambiguities or contradictions that were discovered and
 *   reported by implementors.
 *
 * Revision 1999-02-22 18:00:
 *   Initial version, published as RFC 2592.
 *
 * $Id$
 */

#include "disman-script-mib.h"

stls_enum_t const disman_script_mib_enums_smScriptAdminStatus[] = {
    { DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_ENABLED,	"enabled" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_DISABLED,	"disabled" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_EDITING,	"editing" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smScriptOperStatus[] = {
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_ENABLED,	"enabled" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_DISABLED,	"disabled" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_EDITING,	"editing" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_RETRIEVING,	"retrieving" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_COMPILING,	"compiling" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_NOSUCHSCRIPT,	"noSuchScript" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_ACCESSDENIED,	"accessDenied" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_WRONGLANGUAGE,	"wrongLanguage" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_WRONGVERSION,	"wrongVersion" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_COMPILATIONFAILED,	"compilationFailed" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_NORESOURCESLEFT,	"noResourcesLeft" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_UNKNOWNPROTOCOL,	"unknownProtocol" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_PROTOCOLFAILURE,	"protocolFailure" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_GENERICERROR,	"genericError" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smScriptStorageType[] = {
    { DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_OTHER,	"other" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_VOLATILE,	"volatile" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_NONVOLATILE,	"nonVolatile" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_PERMANENT,	"permanent" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTSTORAGETYPE_READONLY,	"readOnly" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smScriptRowStatus[] = {
    { DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_ACTIVE,	"active" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_NOTINSERVICE,	"notInService" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_NOTREADY,	"notReady" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_CREATEANDGO,	"createAndGo" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_CREATEANDWAIT,	"createAndWait" },
    { DISMAN_SCRIPT_MIB_SMSCRIPTROWSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smCodeRowStatus[] = {
    { DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_ACTIVE,	"active" },
    { DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_NOTINSERVICE,	"notInService" },
    { DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_NOTREADY,	"notReady" },
    { DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_CREATEANDGO,	"createAndGo" },
    { DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_CREATEANDWAIT,	"createAndWait" },
    { DISMAN_SCRIPT_MIB_SMCODEROWSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smLaunchControl[] = {
    { DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_ABORT,	"abort" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_SUSPEND,	"suspend" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_RESUME,	"resume" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHCONTROL_NOP,	"nop" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smLaunchAdminStatus[] = {
    { DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_ENABLED,	"enabled" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_DISABLED,	"disabled" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_AUTOSTART,	"autostart" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smLaunchOperStatus[] = {
    { DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_ENABLED,	"enabled" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_DISABLED,	"disabled" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_EXPIRED,	"expired" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smLaunchStorageType[] = {
    { DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_OTHER,	"other" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_VOLATILE,	"volatile" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_NONVOLATILE,	"nonVolatile" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_PERMANENT,	"permanent" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHSTORAGETYPE_READONLY,	"readOnly" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smLaunchRowStatus[] = {
    { DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_ACTIVE,	"active" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_NOTINSERVICE,	"notInService" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_NOTREADY,	"notReady" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_CREATEANDGO,	"createAndGo" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_CREATEANDWAIT,	"createAndWait" },
    { DISMAN_SCRIPT_MIB_SMLAUNCHROWSTATUS_DESTROY,	"destroy" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smRunExitCode[] = {
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_NOERROR,	"noError" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_HALTED,	"halted" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_LIFETIMEEXCEEDED,	"lifeTimeExceeded" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_NORESOURCESLEFT,	"noResourcesLeft" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_LANGUAGEERROR,	"languageError" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_RUNTIMEERROR,	"runtimeError" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_INVALIDARGUMENT,	"invalidArgument" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_SECURITYVIOLATION,	"securityViolation" },
    { DISMAN_SCRIPT_MIB_SMRUNEXITCODE_GENERICERROR,	"genericError" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smRunControl[] = {
    { DISMAN_SCRIPT_MIB_SMRUNCONTROL_ABORT,	"abort" },
    { DISMAN_SCRIPT_MIB_SMRUNCONTROL_SUSPEND,	"suspend" },
    { DISMAN_SCRIPT_MIB_SMRUNCONTROL_RESUME,	"resume" },
    { DISMAN_SCRIPT_MIB_SMRUNCONTROL_NOP,	"nop" },
    { 0, NULL }
};

stls_enum_t const disman_script_mib_enums_smRunState[] = {
    { DISMAN_SCRIPT_MIB_SMRUNSTATE_INITIALIZING,	"initializing" },
    { DISMAN_SCRIPT_MIB_SMRUNSTATE_EXECUTING,	"executing" },
    { DISMAN_SCRIPT_MIB_SMRUNSTATE_SUSPENDING,	"suspending" },
    { DISMAN_SCRIPT_MIB_SMRUNSTATE_SUSPENDED,	"suspended" },
    { DISMAN_SCRIPT_MIB_SMRUNSTATE_RESUMING,	"resuming" },
    { DISMAN_SCRIPT_MIB_SMRUNSTATE_ABORTING,	"aborting" },
    { DISMAN_SCRIPT_MIB_SMRUNSTATE_TERMINATED,	"terminated" },
    { 0, NULL }
};


static stls_stub_attr_t _smLangEntry[] = {
    { 2, G_SNMP_OBJECT_ID, "smLangLanguage" },
    { 3, G_SNMP_OCTET_STRING, "smLangVersion" },
    { 4, G_SNMP_OBJECT_ID, "smLangVendor" },
    { 5, G_SNMP_OCTET_STRING, "smLangRevision" },
    { 6, G_SNMP_OCTET_STRING, "smLangDescr" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _smExtsnEntry[] = {
    { 2, G_SNMP_OBJECT_ID, "smExtsnExtension" },
    { 3, G_SNMP_OCTET_STRING, "smExtsnVersion" },
    { 4, G_SNMP_OBJECT_ID, "smExtsnVendor" },
    { 5, G_SNMP_OCTET_STRING, "smExtsnRevision" },
    { 6, G_SNMP_OCTET_STRING, "smExtsnDescr" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _smScriptEntry[] = {
    { 3, G_SNMP_OCTET_STRING, "smScriptDescr" },
    { 4, G_SNMP_INTEGER32, "smScriptLanguage" },
    { 5, G_SNMP_OCTET_STRING, "smScriptSource" },
    { 6, G_SNMP_INTEGER32, "smScriptAdminStatus" },
    { 7, G_SNMP_INTEGER32, "smScriptOperStatus" },
    { 8, G_SNMP_INTEGER32, "smScriptStorageType" },
    { 9, G_SNMP_INTEGER32, "smScriptRowStatus" },
    { 10, G_SNMP_OCTET_STRING, "smScriptError" },
    { 11, G_SNMP_OCTET_STRING, "smScriptLastChange" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _smCodeEntry[] = {
    { 2, G_SNMP_OCTET_STRING, "smCodeText" },
    { 3, G_SNMP_INTEGER32, "smCodeRowStatus" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _smLaunchEntry[] = {
    { 3, G_SNMP_OCTET_STRING, "smLaunchScriptOwner" },
    { 4, G_SNMP_OCTET_STRING, "smLaunchScriptName" },
    { 5, G_SNMP_OCTET_STRING, "smLaunchArgument" },
    { 6, G_SNMP_UNSIGNED32, "smLaunchMaxRunning" },
    { 7, G_SNMP_UNSIGNED32, "smLaunchMaxCompleted" },
    { 8, G_SNMP_INTEGER32, "smLaunchLifeTime" },
    { 9, G_SNMP_INTEGER32, "smLaunchExpireTime" },
    { 10, G_SNMP_INTEGER32, "smLaunchStart" },
    { 11, G_SNMP_INTEGER32, "smLaunchControl" },
    { 12, G_SNMP_INTEGER32, "smLaunchAdminStatus" },
    { 13, G_SNMP_INTEGER32, "smLaunchOperStatus" },
    { 14, G_SNMP_INTEGER32, "smLaunchRunIndexNext" },
    { 15, G_SNMP_INTEGER32, "smLaunchStorageType" },
    { 16, G_SNMP_INTEGER32, "smLaunchRowStatus" },
    { 17, G_SNMP_OCTET_STRING, "smLaunchError" },
    { 18, G_SNMP_OCTET_STRING, "smLaunchLastChange" },
    { 19, G_SNMP_INTEGER32, "smLaunchRowExpireTime" },
    { 0, 0, NULL }
};

static stls_stub_attr_t _smRunEntry[] = {
    { 2, G_SNMP_OCTET_STRING, "smRunArgument" },
    { 3, G_SNMP_OCTET_STRING, "smRunStartTime" },
    { 4, G_SNMP_OCTET_STRING, "smRunEndTime" },
    { 5, G_SNMP_INTEGER32, "smRunLifeTime" },
    { 6, G_SNMP_INTEGER32, "smRunExpireTime" },
    { 7, G_SNMP_INTEGER32, "smRunExitCode" },
    { 8, G_SNMP_OCTET_STRING, "smRunResult" },
    { 9, G_SNMP_INTEGER32, "smRunControl" },
    { 10, G_SNMP_INTEGER32, "smRunState" },
    { 11, G_SNMP_OCTET_STRING, "smRunError" },
    { 12, G_SNMP_OCTET_STRING, "smRunResultTime" },
    { 13, G_SNMP_OCTET_STRING, "smRunErrorTime" },
    { 0, 0, NULL }
};


smLangEntry_t *
disman_script_mib_new_smLangEntry()
{
    smLangEntry_t *smLangEntry;

    smLangEntry = (smLangEntry_t *) g_malloc0(sizeof(smLangEntry_t) + sizeof(gpointer));
    return smLangEntry;
}

static int
unpack_smLangEntry(GSnmpVarBind *vb, smLangEntry_t *smLangEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    smLangEntry->smLangIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static smLangEntry_t *
assign_smLangEntry(GSList *vbl)
{
    GSList *elem;
    smLangEntry_t *smLangEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 64, 1, 1, 1};

    smLangEntry = disman_script_mib_new_smLangEntry();
    if (! smLangEntry) {
        return NULL;
    }

    p = (char *) smLangEntry + sizeof(smLangEntry_t);
    * (GSList **) p = vbl;

    if (unpack_smLangEntry((GSnmpVarBind *) vbl->data, smLangEntry) < 0) {
        g_warning("illegal smLangEntry instance identifier");
        g_free(smLangEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _smLangEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            smLangEntry->_smLangLanguageLength = vb->syntax_len / sizeof(guint32);
            smLangEntry->smLangLanguage = vb->syntax.ui32;
            break;
        case 3:
            smLangEntry->_smLangVersionLength = vb->syntax_len;
            smLangEntry->smLangVersion = vb->syntax.uc;
            break;
        case 4:
            smLangEntry->_smLangVendorLength = vb->syntax_len / sizeof(guint32);
            smLangEntry->smLangVendor = vb->syntax.ui32;
            break;
        case 5:
            smLangEntry->_smLangRevisionLength = vb->syntax_len;
            smLangEntry->smLangRevision = vb->syntax.uc;
            break;
        case 6:
            smLangEntry->_smLangDescrLength = vb->syntax_len;
            smLangEntry->smLangDescr = vb->syntax.uc;
            break;
        };
    }

    return smLangEntry;
}

int
disman_script_mib_get_smLangTable(host_snmp *s, smLangEntry_t ***smLangEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 64, 1, 1, 1, 0};

    *smLangEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _smLangEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *smLangEntry = (smLangEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(smLangEntry_t *));
    if (! *smLangEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*smLangEntry)[i] = assign_smLangEntry(row->data);
    }

    return 0;
}

void
disman_script_mib_free_smLangEntry(smLangEntry_t *smLangEntry)
{
    GSList *vbl;
    char *p;

    if (smLangEntry) {
        p = (char *) smLangEntry + sizeof(smLangEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(smLangEntry);
    }
}

void
disman_script_mib_free_smLangTable(smLangEntry_t **smLangEntry)
{
    int i;

    if (smLangEntry) {
        for (i = 0; smLangEntry[i]; i++) {
            disman_script_mib_free_smLangEntry(smLangEntry[i]);
        }
        g_free(smLangEntry);
    }
}

smExtsnEntry_t *
disman_script_mib_new_smExtsnEntry()
{
    smExtsnEntry_t *smExtsnEntry;

    smExtsnEntry = (smExtsnEntry_t *) g_malloc0(sizeof(smExtsnEntry_t) + sizeof(gpointer));
    return smExtsnEntry;
}

static int
unpack_smExtsnEntry(GSnmpVarBind *vb, smExtsnEntry_t *smExtsnEntry)
{
    int idx = 11;

    if (vb->id_len < idx) return -1;
    smExtsnEntry->smLangIndex = vb->id[idx++];
    if (vb->id_len < idx) return -1;
    smExtsnEntry->smExtsnIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static smExtsnEntry_t *
assign_smExtsnEntry(GSList *vbl)
{
    GSList *elem;
    smExtsnEntry_t *smExtsnEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 64, 1, 2, 1};

    smExtsnEntry = disman_script_mib_new_smExtsnEntry();
    if (! smExtsnEntry) {
        return NULL;
    }

    p = (char *) smExtsnEntry + sizeof(smExtsnEntry_t);
    * (GSList **) p = vbl;

    if (unpack_smExtsnEntry((GSnmpVarBind *) vbl->data, smExtsnEntry) < 0) {
        g_warning("illegal smExtsnEntry instance identifier");
        g_free(smExtsnEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _smExtsnEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            smExtsnEntry->_smExtsnExtensionLength = vb->syntax_len / sizeof(guint32);
            smExtsnEntry->smExtsnExtension = vb->syntax.ui32;
            break;
        case 3:
            smExtsnEntry->_smExtsnVersionLength = vb->syntax_len;
            smExtsnEntry->smExtsnVersion = vb->syntax.uc;
            break;
        case 4:
            smExtsnEntry->_smExtsnVendorLength = vb->syntax_len / sizeof(guint32);
            smExtsnEntry->smExtsnVendor = vb->syntax.ui32;
            break;
        case 5:
            smExtsnEntry->_smExtsnRevisionLength = vb->syntax_len;
            smExtsnEntry->smExtsnRevision = vb->syntax.uc;
            break;
        case 6:
            smExtsnEntry->_smExtsnDescrLength = vb->syntax_len;
            smExtsnEntry->smExtsnDescr = vb->syntax.uc;
            break;
        };
    }

    return smExtsnEntry;
}

int
disman_script_mib_get_smExtsnTable(host_snmp *s, smExtsnEntry_t ***smExtsnEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 64, 1, 2, 1, 0};

    *smExtsnEntry = NULL;

    stls_vbl_attributes(s, &in, base, 10, _smExtsnEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *smExtsnEntry = (smExtsnEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(smExtsnEntry_t *));
    if (! *smExtsnEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*smExtsnEntry)[i] = assign_smExtsnEntry(row->data);
    }

    return 0;
}

void
disman_script_mib_free_smExtsnEntry(smExtsnEntry_t *smExtsnEntry)
{
    GSList *vbl;
    char *p;

    if (smExtsnEntry) {
        p = (char *) smExtsnEntry + sizeof(smExtsnEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(smExtsnEntry);
    }
}

void
disman_script_mib_free_smExtsnTable(smExtsnEntry_t **smExtsnEntry)
{
    int i;

    if (smExtsnEntry) {
        for (i = 0; smExtsnEntry[i]; i++) {
            disman_script_mib_free_smExtsnEntry(smExtsnEntry[i]);
        }
        g_free(smExtsnEntry);
    }
}

smScriptEntry_t *
disman_script_mib_new_smScriptEntry()
{
    smScriptEntry_t *smScriptEntry;

    smScriptEntry = (smScriptEntry_t *) g_malloc0(sizeof(smScriptEntry_t) + sizeof(gpointer));
    return smScriptEntry;
}

static int
unpack_smScriptEntry(GSnmpVarBind *vb, smScriptEntry_t *smScriptEntry)
{
    int i, len, idx = 12;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smScriptEntry->smScriptOwner[i] = vb->id[idx++];
    }
    smScriptEntry->_smScriptOwnerLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smScriptEntry->smScriptName[i] = vb->id[idx++];
    }
    smScriptEntry->_smScriptNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static smScriptEntry_t *
assign_smScriptEntry(GSList *vbl)
{
    GSList *elem;
    smScriptEntry_t *smScriptEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 64, 1, 3, 1, 1};

    smScriptEntry = disman_script_mib_new_smScriptEntry();
    if (! smScriptEntry) {
        return NULL;
    }

    p = (char *) smScriptEntry + sizeof(smScriptEntry_t);
    * (GSList **) p = vbl;

    if (unpack_smScriptEntry((GSnmpVarBind *) vbl->data, smScriptEntry) < 0) {
        g_warning("illegal smScriptEntry instance identifier");
        g_free(smScriptEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _smScriptEntry, &idx) < 0) continue;

        switch (idx) {
        case 3:
            smScriptEntry->_smScriptDescrLength = vb->syntax_len;
            smScriptEntry->smScriptDescr = vb->syntax.uc;
            break;
        case 4:
            smScriptEntry->smScriptLanguage = &(vb->syntax.i32[0]);
            break;
        case 5:
            smScriptEntry->_smScriptSourceLength = vb->syntax_len;
            smScriptEntry->smScriptSource = vb->syntax.uc;
            break;
        case 6:
            smScriptEntry->smScriptAdminStatus = &(vb->syntax.i32[0]);
            break;
        case 7:
            smScriptEntry->smScriptOperStatus = &(vb->syntax.i32[0]);
            break;
        case 8:
            smScriptEntry->smScriptStorageType = &(vb->syntax.i32[0]);
            break;
        case 9:
            smScriptEntry->smScriptRowStatus = &(vb->syntax.i32[0]);
            break;
        case 10:
            smScriptEntry->_smScriptErrorLength = vb->syntax_len;
            smScriptEntry->smScriptError = vb->syntax.uc;
            break;
        case 11:
            smScriptEntry->_smScriptLastChangeLength = vb->syntax_len;
            smScriptEntry->smScriptLastChange = vb->syntax.uc;
            break;
        };
    }

    return smScriptEntry;
}

int
disman_script_mib_get_smScriptTable(host_snmp *s, smScriptEntry_t ***smScriptEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 64, 1, 3, 1, 1, 0};

    *smScriptEntry = NULL;

    stls_vbl_attributes(s, &in, base, 11, _smScriptEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *smScriptEntry = (smScriptEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(smScriptEntry_t *));
    if (! *smScriptEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*smScriptEntry)[i] = assign_smScriptEntry(row->data);
    }

    return 0;
}

void
disman_script_mib_free_smScriptEntry(smScriptEntry_t *smScriptEntry)
{
    GSList *vbl;
    char *p;

    if (smScriptEntry) {
        p = (char *) smScriptEntry + sizeof(smScriptEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(smScriptEntry);
    }
}

void
disman_script_mib_free_smScriptTable(smScriptEntry_t **smScriptEntry)
{
    int i;

    if (smScriptEntry) {
        for (i = 0; smScriptEntry[i]; i++) {
            disman_script_mib_free_smScriptEntry(smScriptEntry[i]);
        }
        g_free(smScriptEntry);
    }
}

smCodeEntry_t *
disman_script_mib_new_smCodeEntry()
{
    smCodeEntry_t *smCodeEntry;

    smCodeEntry = (smCodeEntry_t *) g_malloc0(sizeof(smCodeEntry_t) + sizeof(gpointer));
    return smCodeEntry;
}

static int
unpack_smCodeEntry(GSnmpVarBind *vb, smCodeEntry_t *smCodeEntry)
{
    int i, len, idx = 12;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smCodeEntry->smScriptOwner[i] = vb->id[idx++];
    }
    smCodeEntry->_smScriptOwnerLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smCodeEntry->smScriptName[i] = vb->id[idx++];
    }
    smCodeEntry->_smScriptNameLength = len;
    if (vb->id_len < idx) return -1;
    smCodeEntry->smCodeIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static smCodeEntry_t *
assign_smCodeEntry(GSList *vbl)
{
    GSList *elem;
    smCodeEntry_t *smCodeEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 64, 1, 3, 2, 1};

    smCodeEntry = disman_script_mib_new_smCodeEntry();
    if (! smCodeEntry) {
        return NULL;
    }

    p = (char *) smCodeEntry + sizeof(smCodeEntry_t);
    * (GSList **) p = vbl;

    if (unpack_smCodeEntry((GSnmpVarBind *) vbl->data, smCodeEntry) < 0) {
        g_warning("illegal smCodeEntry instance identifier");
        g_free(smCodeEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _smCodeEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            smCodeEntry->_smCodeTextLength = vb->syntax_len;
            smCodeEntry->smCodeText = vb->syntax.uc;
            break;
        case 3:
            smCodeEntry->smCodeRowStatus = &(vb->syntax.i32[0]);
            break;
        };
    }

    return smCodeEntry;
}

int
disman_script_mib_get_smCodeTable(host_snmp *s, smCodeEntry_t ***smCodeEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 64, 1, 3, 2, 1, 0};

    *smCodeEntry = NULL;

    stls_vbl_attributes(s, &in, base, 11, _smCodeEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *smCodeEntry = (smCodeEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(smCodeEntry_t *));
    if (! *smCodeEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*smCodeEntry)[i] = assign_smCodeEntry(row->data);
    }

    return 0;
}

void
disman_script_mib_free_smCodeEntry(smCodeEntry_t *smCodeEntry)
{
    GSList *vbl;
    char *p;

    if (smCodeEntry) {
        p = (char *) smCodeEntry + sizeof(smCodeEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(smCodeEntry);
    }
}

void
disman_script_mib_free_smCodeTable(smCodeEntry_t **smCodeEntry)
{
    int i;

    if (smCodeEntry) {
        for (i = 0; smCodeEntry[i]; i++) {
            disman_script_mib_free_smCodeEntry(smCodeEntry[i]);
        }
        g_free(smCodeEntry);
    }
}

smLaunchEntry_t *
disman_script_mib_new_smLaunchEntry()
{
    smLaunchEntry_t *smLaunchEntry;

    smLaunchEntry = (smLaunchEntry_t *) g_malloc0(sizeof(smLaunchEntry_t) + sizeof(gpointer));
    return smLaunchEntry;
}

static int
unpack_smLaunchEntry(GSnmpVarBind *vb, smLaunchEntry_t *smLaunchEntry)
{
    int i, len, idx = 12;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smLaunchEntry->smLaunchOwner[i] = vb->id[idx++];
    }
    smLaunchEntry->_smLaunchOwnerLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smLaunchEntry->smLaunchName[i] = vb->id[idx++];
    }
    smLaunchEntry->_smLaunchNameLength = len;
    if (vb->id_len > idx) return -1;
    return 0;
}

static smLaunchEntry_t *
assign_smLaunchEntry(GSList *vbl)
{
    GSList *elem;
    smLaunchEntry_t *smLaunchEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 64, 1, 4, 1, 1};

    smLaunchEntry = disman_script_mib_new_smLaunchEntry();
    if (! smLaunchEntry) {
        return NULL;
    }

    p = (char *) smLaunchEntry + sizeof(smLaunchEntry_t);
    * (GSList **) p = vbl;

    if (unpack_smLaunchEntry((GSnmpVarBind *) vbl->data, smLaunchEntry) < 0) {
        g_warning("illegal smLaunchEntry instance identifier");
        g_free(smLaunchEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _smLaunchEntry, &idx) < 0) continue;

        switch (idx) {
        case 3:
            smLaunchEntry->_smLaunchScriptOwnerLength = vb->syntax_len;
            smLaunchEntry->smLaunchScriptOwner = vb->syntax.uc;
            break;
        case 4:
            smLaunchEntry->_smLaunchScriptNameLength = vb->syntax_len;
            smLaunchEntry->smLaunchScriptName = vb->syntax.uc;
            break;
        case 5:
            smLaunchEntry->_smLaunchArgumentLength = vb->syntax_len;
            smLaunchEntry->smLaunchArgument = vb->syntax.uc;
            break;
        case 6:
            smLaunchEntry->smLaunchMaxRunning = &(vb->syntax.ui32[0]);
            break;
        case 7:
            smLaunchEntry->smLaunchMaxCompleted = &(vb->syntax.ui32[0]);
            break;
        case 8:
            smLaunchEntry->smLaunchLifeTime = &(vb->syntax.i32[0]);
            break;
        case 9:
            smLaunchEntry->smLaunchExpireTime = &(vb->syntax.i32[0]);
            break;
        case 10:
            smLaunchEntry->smLaunchStart = &(vb->syntax.i32[0]);
            break;
        case 11:
            smLaunchEntry->smLaunchControl = &(vb->syntax.i32[0]);
            break;
        case 12:
            smLaunchEntry->smLaunchAdminStatus = &(vb->syntax.i32[0]);
            break;
        case 13:
            smLaunchEntry->smLaunchOperStatus = &(vb->syntax.i32[0]);
            break;
        case 14:
            smLaunchEntry->smLaunchRunIndexNext = &(vb->syntax.i32[0]);
            break;
        case 15:
            smLaunchEntry->smLaunchStorageType = &(vb->syntax.i32[0]);
            break;
        case 16:
            smLaunchEntry->smLaunchRowStatus = &(vb->syntax.i32[0]);
            break;
        case 17:
            smLaunchEntry->_smLaunchErrorLength = vb->syntax_len;
            smLaunchEntry->smLaunchError = vb->syntax.uc;
            break;
        case 18:
            smLaunchEntry->_smLaunchLastChangeLength = vb->syntax_len;
            smLaunchEntry->smLaunchLastChange = vb->syntax.uc;
            break;
        case 19:
            smLaunchEntry->smLaunchRowExpireTime = &(vb->syntax.i32[0]);
            break;
        };
    }

    return smLaunchEntry;
}

int
disman_script_mib_get_smLaunchTable(host_snmp *s, smLaunchEntry_t ***smLaunchEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 64, 1, 4, 1, 1, 0};

    *smLaunchEntry = NULL;

    stls_vbl_attributes(s, &in, base, 11, _smLaunchEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *smLaunchEntry = (smLaunchEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(smLaunchEntry_t *));
    if (! *smLaunchEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*smLaunchEntry)[i] = assign_smLaunchEntry(row->data);
    }

    return 0;
}

void
disman_script_mib_free_smLaunchEntry(smLaunchEntry_t *smLaunchEntry)
{
    GSList *vbl;
    char *p;

    if (smLaunchEntry) {
        p = (char *) smLaunchEntry + sizeof(smLaunchEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(smLaunchEntry);
    }
}

void
disman_script_mib_free_smLaunchTable(smLaunchEntry_t **smLaunchEntry)
{
    int i;

    if (smLaunchEntry) {
        for (i = 0; smLaunchEntry[i]; i++) {
            disman_script_mib_free_smLaunchEntry(smLaunchEntry[i]);
        }
        g_free(smLaunchEntry);
    }
}

smRunEntry_t *
disman_script_mib_new_smRunEntry()
{
    smRunEntry_t *smRunEntry;

    smRunEntry = (smRunEntry_t *) g_malloc0(sizeof(smRunEntry_t) + sizeof(gpointer));
    return smRunEntry;
}

static int
unpack_smRunEntry(GSnmpVarBind *vb, smRunEntry_t *smRunEntry)
{
    int i, len, idx = 12;

    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smRunEntry->smLaunchOwner[i] = vb->id[idx++];
    }
    smRunEntry->_smLaunchOwnerLength = len;
    if (vb->id_len < idx) return -1;
    len = vb->id[idx++];
    if (vb->id_len < idx + len) return -1;
    for (i = 0; i < len; i++) {
        smRunEntry->smLaunchName[i] = vb->id[idx++];
    }
    smRunEntry->_smLaunchNameLength = len;
    if (vb->id_len < idx) return -1;
    smRunEntry->smRunIndex = vb->id[idx++];
    if (vb->id_len > idx) return -1;
    return 0;
}

static smRunEntry_t *
assign_smRunEntry(GSList *vbl)
{
    GSList *elem;
    smRunEntry_t *smRunEntry;
    guint32 idx;
    char *p;
    static guint32 const base[] = {1, 3, 6, 1, 2, 1, 64, 1, 4, 2, 1};

    smRunEntry = disman_script_mib_new_smRunEntry();
    if (! smRunEntry) {
        return NULL;
    }

    p = (char *) smRunEntry + sizeof(smRunEntry_t);
    * (GSList **) p = vbl;

    if (unpack_smRunEntry((GSnmpVarBind *) vbl->data, smRunEntry) < 0) {
        g_warning("illegal smRunEntry instance identifier");
        g_free(smRunEntry);
        return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;

        if (stls_vb_lookup(vb, base, sizeof(base)/sizeof(guint32),
                           _smRunEntry, &idx) < 0) continue;

        switch (idx) {
        case 2:
            smRunEntry->_smRunArgumentLength = vb->syntax_len;
            smRunEntry->smRunArgument = vb->syntax.uc;
            break;
        case 3:
            smRunEntry->_smRunStartTimeLength = vb->syntax_len;
            smRunEntry->smRunStartTime = vb->syntax.uc;
            break;
        case 4:
            smRunEntry->_smRunEndTimeLength = vb->syntax_len;
            smRunEntry->smRunEndTime = vb->syntax.uc;
            break;
        case 5:
            smRunEntry->smRunLifeTime = &(vb->syntax.i32[0]);
            break;
        case 6:
            smRunEntry->smRunExpireTime = &(vb->syntax.i32[0]);
            break;
        case 7:
            smRunEntry->smRunExitCode = &(vb->syntax.i32[0]);
            break;
        case 8:
            smRunEntry->_smRunResultLength = vb->syntax_len;
            smRunEntry->smRunResult = vb->syntax.uc;
            break;
        case 9:
            smRunEntry->smRunControl = &(vb->syntax.i32[0]);
            break;
        case 10:
            smRunEntry->smRunState = &(vb->syntax.i32[0]);
            break;
        case 11:
            smRunEntry->_smRunErrorLength = vb->syntax_len;
            smRunEntry->smRunError = vb->syntax.uc;
            break;
        case 12:
            smRunEntry->_smRunResultTimeLength = vb->syntax_len;
            smRunEntry->smRunResultTime = vb->syntax.uc;
            break;
        case 13:
            smRunEntry->_smRunErrorTimeLength = vb->syntax_len;
            smRunEntry->smRunErrorTime = vb->syntax.uc;
            break;
        };
    }

    return smRunEntry;
}

int
disman_script_mib_get_smRunTable(host_snmp *s, smRunEntry_t ***smRunEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 base[] = {1, 3, 6, 1, 2, 1, 64, 1, 4, 2, 1, 0};

    *smRunEntry = NULL;

    stls_vbl_attributes(s, &in, base, 11, _smRunEntry);

    out = stls_snmp_gettable(s, in);
    /* stls_vbl_free(in); */
    if (! out) {
        return -2;
    }

    *smRunEntry = (smRunEntry_t **) g_malloc0((g_slist_length(out) + 1) * sizeof(smRunEntry_t *));
    if (! *smRunEntry) {
        return -4;
    }

    for (row = out, i = 0; row; row = g_slist_next(row), i++) {
        (*smRunEntry)[i] = assign_smRunEntry(row->data);
    }

    return 0;
}

void
disman_script_mib_free_smRunEntry(smRunEntry_t *smRunEntry)
{
    GSList *vbl;
    char *p;

    if (smRunEntry) {
        p = (char *) smRunEntry + sizeof(smRunEntry_t);
        vbl = * (GSList **) p;
        stls_vbl_free(vbl);
        g_free(smRunEntry);
    }
}

void
disman_script_mib_free_smRunTable(smRunEntry_t **smRunEntry)
{
    int i;

    if (smRunEntry) {
        for (i = 0; smRunEntry[i]; i++) {
            disman_script_mib_free_smRunEntry(smRunEntry[i]);
        }
        g_free(smRunEntry);
    }
}


