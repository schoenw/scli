/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.13 for the stools package.
 *
 * Derived from DISMAN-SCRIPT-MIB revision 1999-02-22 18:00.
 *
 * $Id$
 */

#include "disman-script-mib.h"

stls_table_t disman_script_mib_enums_smScriptAdminStatus[] = {
    { 1, "enabled" },
    { 2, "disabled" },
    { 3, "editing" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smScriptOperStatus[] = {
    { 1, "enabled" },
    { 2, "disabled" },
    { 3, "editing" },
    { 4, "retrieving" },
    { 5, "compiling" },
    { 6, "noSuchScript" },
    { 7, "accessDenied" },
    { 8, "wrongLanguage" },
    { 9, "wrongVersion" },
    { 10, "compilationFailed" },
    { 11, "noResourcesLeft" },
    { 12, "unknownProtocol" },
    { 13, "protocolFailure" },
    { 14, "genericError" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smScriptStorageType[] = {
    { 1, "other" },
    { 2, "volatile" },
    { 3, "nonVolatile" },
    { 4, "permanent" },
    { 5, "readOnly" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smScriptRowStatus[] = {
    { 1, "active" },
    { 2, "notInService" },
    { 3, "notReady" },
    { 4, "createAndGo" },
    { 5, "createAndWait" },
    { 6, "destroy" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smCodeRowStatus[] = {
    { 1, "active" },
    { 2, "notInService" },
    { 3, "notReady" },
    { 4, "createAndGo" },
    { 5, "createAndWait" },
    { 6, "destroy" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smLaunchControl[] = {
    { 1, "abort" },
    { 2, "suspend" },
    { 3, "resume" },
    { 4, "nop" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smLaunchAdminStatus[] = {
    { 1, "enabled" },
    { 2, "disabled" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smLaunchOperStatus[] = {
    { 1, "enabled" },
    { 2, "disabled" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smLaunchStorageType[] = {
    { 1, "other" },
    { 2, "volatile" },
    { 3, "nonVolatile" },
    { 4, "permanent" },
    { 5, "readOnly" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smLaunchRowStatus[] = {
    { 1, "active" },
    { 2, "notInService" },
    { 3, "notReady" },
    { 4, "createAndGo" },
    { 5, "createAndWait" },
    { 6, "destroy" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smRunExitCode[] = {
    { 1, "noError" },
    { 2, "halted" },
    { 3, "lifeTimeExceeded" },
    { 4, "noResourcesLeft" },
    { 5, "languageError" },
    { 6, "runtimeError" },
    { 7, "invalidArgument" },
    { 8, "securityViolation" },
    { 9, "genericError" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smRunControl[] = {
    { 1, "abort" },
    { 2, "suspend" },
    { 3, "resume" },
    { 4, "nop" },
    { 0, NULL }
};

stls_table_t disman_script_mib_enums_smRunState[] = {
    { 1, "initializing" },
    { 2, "executing" },
    { 3, "suspending" },
    { 4, "suspended" },
    { 5, "resuming" },
    { 6, "aborting" },
    { 7, "terminated" },
    { 0, NULL }
};


static smLangEntry_t *
assign_smLangEntry(GSList *vbl)
{
    GSList *elem;
    smLangEntry_t *smLangEntry;
    char *p;

    smLangEntry = (smLangEntry_t *) g_malloc0(sizeof(smLangEntry_t) + sizeof(GSList *));
    if (! smLangEntry) {
        return NULL;
    }

    p = (char *) smLangEntry + sizeof(smLangEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 12) return NULL;
        smLangEntry->smLangIndex = (gint32 *) &(vb->id[11]);
        if (vb->id_len > 12) return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 2) {
            smLangEntry->_smLangLanguageLength = vb->syntax_len / sizeof(guint32);
            smLangEntry->smLangLanguage = vb->syntax.ui32;
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            smLangEntry->_smLangVersionLength = vb->syntax_len;
            smLangEntry->smLangVersion = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            smLangEntry->_smLangVendorLength = vb->syntax_len / sizeof(guint32);
            smLangEntry->smLangVendor = vb->syntax.ui32;
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            smLangEntry->_smLangRevisionLength = vb->syntax_len;
            smLangEntry->smLangRevision = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            smLangEntry->_smLangDescrLength = vb->syntax_len;
            smLangEntry->smLangDescr = vb->syntax.uc;
        }
    }

    return smLangEntry;
}

int
disman_script_mib_get_smLangEntry(host_snmp *s, smLangEntry_t ***smLangEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 var[] = {1, 3, 6, 1, 2, 1, 64, 1, 1, 1, 0};

    *smLangEntry = NULL;

    var[10] = 2; stls_vbl_add_null(&in, var, 11);
    var[10] = 3; stls_vbl_add_null(&in, var, 11);
    var[10] = 4; stls_vbl_add_null(&in, var, 11);
    var[10] = 5; stls_vbl_add_null(&in, var, 11);
    var[10] = 6; stls_vbl_add_null(&in, var, 11);

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
disman_script_mib_free_smLangEntry(smLangEntry_t **smLangEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (smLangEntry) {
        for (i = 0; smLangEntry[i]; i++) {
            p = (char *) smLangEntry[i] + sizeof(smLangEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(smLangEntry[i]);
        }
        g_free(smLangEntry);
    }
}

static smExtsnEntry_t *
assign_smExtsnEntry(GSList *vbl)
{
    GSList *elem;
    smExtsnEntry_t *smExtsnEntry;
    char *p;

    smExtsnEntry = (smExtsnEntry_t *) g_malloc0(sizeof(smExtsnEntry_t) + sizeof(GSList *));
    if (! smExtsnEntry) {
        return NULL;
    }

    p = (char *) smExtsnEntry + sizeof(smExtsnEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 12) return NULL;
        smExtsnEntry->smLangIndex = (gint32 *) &(vb->id[11]);
        smExtsnEntry->smExtsnIndex = (gint32 *) &(vb->id[12]);
        if (vb->id_len > 13) return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (vb->id_len > 11 && vb->id[10] == 2) {
            smExtsnEntry->_smExtsnExtensionLength = vb->syntax_len / sizeof(guint32);
            smExtsnEntry->smExtsnExtension = vb->syntax.ui32;
        }
        if (vb->id_len > 11 && vb->id[10] == 3) {
            smExtsnEntry->_smExtsnVersionLength = vb->syntax_len;
            smExtsnEntry->smExtsnVersion = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 4) {
            smExtsnEntry->_smExtsnVendorLength = vb->syntax_len / sizeof(guint32);
            smExtsnEntry->smExtsnVendor = vb->syntax.ui32;
        }
        if (vb->id_len > 11 && vb->id[10] == 5) {
            smExtsnEntry->_smExtsnRevisionLength = vb->syntax_len;
            smExtsnEntry->smExtsnRevision = vb->syntax.uc;
        }
        if (vb->id_len > 11 && vb->id[10] == 6) {
            smExtsnEntry->_smExtsnDescrLength = vb->syntax_len;
            smExtsnEntry->smExtsnDescr = vb->syntax.uc;
        }
    }

    return smExtsnEntry;
}

int
disman_script_mib_get_smExtsnEntry(host_snmp *s, smExtsnEntry_t ***smExtsnEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 var[] = {1, 3, 6, 1, 2, 1, 64, 1, 2, 1, 0};

    *smExtsnEntry = NULL;

    var[10] = 2; stls_vbl_add_null(&in, var, 11);
    var[10] = 3; stls_vbl_add_null(&in, var, 11);
    var[10] = 4; stls_vbl_add_null(&in, var, 11);
    var[10] = 5; stls_vbl_add_null(&in, var, 11);
    var[10] = 6; stls_vbl_add_null(&in, var, 11);

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
disman_script_mib_free_smExtsnEntry(smExtsnEntry_t **smExtsnEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (smExtsnEntry) {
        for (i = 0; smExtsnEntry[i]; i++) {
            p = (char *) smExtsnEntry[i] + sizeof(smExtsnEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(smExtsnEntry[i]);
        }
        g_free(smExtsnEntry);
    }
}

static smScriptEntry_t *
assign_smScriptEntry(GSList *vbl)
{
    GSList *elem;
    smScriptEntry_t *smScriptEntry;
    char *p;

    smScriptEntry = (smScriptEntry_t *) g_malloc0(sizeof(smScriptEntry_t) + sizeof(GSList *));
    if (! smScriptEntry) {
        return NULL;
    }

    p = (char *) smScriptEntry + sizeof(smScriptEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        /* XXX fix this smScriptEntry->smScriptOwner = ?; */
        /* XXX fix this smScriptEntry->smScriptName = ?; */
        if (vb->id_len > 12) return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            smScriptEntry->_smScriptDescrLength = vb->syntax_len;
            smScriptEntry->smScriptDescr = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            smScriptEntry->smScriptLanguage = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            smScriptEntry->_smScriptSourceLength = vb->syntax_len;
            smScriptEntry->smScriptSource = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            smScriptEntry->smScriptAdminStatus = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            smScriptEntry->smScriptOperStatus = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            smScriptEntry->smScriptStorageType = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 9) {
            smScriptEntry->smScriptRowStatus = &(vb->syntax.i32[0]);
        }
    }

    return smScriptEntry;
}

int
disman_script_mib_get_smScriptEntry(host_snmp *s, smScriptEntry_t ***smScriptEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 var[] = {1, 3, 6, 1, 2, 1, 64, 1, 3, 1, 1, 0};

    *smScriptEntry = NULL;

    var[11] = 3; stls_vbl_add_null(&in, var, 12);
    var[11] = 4; stls_vbl_add_null(&in, var, 12);
    var[11] = 5; stls_vbl_add_null(&in, var, 12);
    var[11] = 6; stls_vbl_add_null(&in, var, 12);
    var[11] = 7; stls_vbl_add_null(&in, var, 12);
    var[11] = 8; stls_vbl_add_null(&in, var, 12);
    var[11] = 9; stls_vbl_add_null(&in, var, 12);

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
disman_script_mib_free_smScriptEntry(smScriptEntry_t **smScriptEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (smScriptEntry) {
        for (i = 0; smScriptEntry[i]; i++) {
            p = (char *) smScriptEntry[i] + sizeof(smScriptEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(smScriptEntry[i]);
        }
        g_free(smScriptEntry);
    }
}

static smCodeEntry_t *
assign_smCodeEntry(GSList *vbl)
{
    GSList *elem;
    smCodeEntry_t *smCodeEntry;
    char *p;

    smCodeEntry = (smCodeEntry_t *) g_malloc0(sizeof(smCodeEntry_t) + sizeof(GSList *));
    if (! smCodeEntry) {
        return NULL;
    }

    p = (char *) smCodeEntry + sizeof(smCodeEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        /* XXX fix this smCodeEntry->smScriptOwner = ?; */
        /* XXX fix this smCodeEntry->smScriptName = ?; */
        smCodeEntry->smCodeIndex = &(vb->id[12]);
        if (vb->id_len > 13) return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (vb->id_len > 12 && vb->id[11] == 2) {
            smCodeEntry->_smCodeTextLength = vb->syntax_len;
            smCodeEntry->smCodeText = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            smCodeEntry->smCodeRowStatus = &(vb->syntax.i32[0]);
        }
    }

    return smCodeEntry;
}

int
disman_script_mib_get_smCodeEntry(host_snmp *s, smCodeEntry_t ***smCodeEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 var[] = {1, 3, 6, 1, 2, 1, 64, 1, 3, 2, 1, 0};

    *smCodeEntry = NULL;

    var[11] = 2; stls_vbl_add_null(&in, var, 12);
    var[11] = 3; stls_vbl_add_null(&in, var, 12);

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
disman_script_mib_free_smCodeEntry(smCodeEntry_t **smCodeEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (smCodeEntry) {
        for (i = 0; smCodeEntry[i]; i++) {
            p = (char *) smCodeEntry[i] + sizeof(smCodeEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(smCodeEntry[i]);
        }
        g_free(smCodeEntry);
    }
}

static smLaunchEntry_t *
assign_smLaunchEntry(GSList *vbl)
{
    GSList *elem;
    smLaunchEntry_t *smLaunchEntry;
    char *p;

    smLaunchEntry = (smLaunchEntry_t *) g_malloc0(sizeof(smLaunchEntry_t) + sizeof(GSList *));
    if (! smLaunchEntry) {
        return NULL;
    }

    p = (char *) smLaunchEntry + sizeof(smLaunchEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        /* XXX fix this smLaunchEntry->smLaunchOwner = ?; */
        /* XXX fix this smLaunchEntry->smLaunchName = ?; */
        if (vb->id_len > 12) return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            smLaunchEntry->_smLaunchScriptOwnerLength = vb->syntax_len;
            smLaunchEntry->smLaunchScriptOwner = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            smLaunchEntry->_smLaunchScriptNameLength = vb->syntax_len;
            smLaunchEntry->smLaunchScriptName = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            smLaunchEntry->_smLaunchArgumentLength = vb->syntax_len;
            smLaunchEntry->smLaunchArgument = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            smLaunchEntry->smLaunchMaxRunning = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            smLaunchEntry->smLaunchMaxCompleted = &(vb->syntax.ui32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            smLaunchEntry->smLaunchLifeTime = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 9) {
            smLaunchEntry->smLaunchExpireTime = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 10) {
            smLaunchEntry->smLaunchStart = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 11) {
            smLaunchEntry->smLaunchControl = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 12) {
            smLaunchEntry->smLaunchAdminStatus = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 13) {
            smLaunchEntry->smLaunchOperStatus = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 14) {
            smLaunchEntry->smLaunchRunIndexNext = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 15) {
            smLaunchEntry->smLaunchStorageType = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 16) {
            smLaunchEntry->smLaunchRowStatus = &(vb->syntax.i32[0]);
        }
    }

    return smLaunchEntry;
}

int
disman_script_mib_get_smLaunchEntry(host_snmp *s, smLaunchEntry_t ***smLaunchEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 var[] = {1, 3, 6, 1, 2, 1, 64, 1, 4, 1, 1, 0};

    *smLaunchEntry = NULL;

    var[11] = 3; stls_vbl_add_null(&in, var, 12);
    var[11] = 4; stls_vbl_add_null(&in, var, 12);
    var[11] = 5; stls_vbl_add_null(&in, var, 12);
    var[11] = 6; stls_vbl_add_null(&in, var, 12);
    var[11] = 7; stls_vbl_add_null(&in, var, 12);
    var[11] = 8; stls_vbl_add_null(&in, var, 12);
    var[11] = 9; stls_vbl_add_null(&in, var, 12);
    var[11] = 10; stls_vbl_add_null(&in, var, 12);
    var[11] = 11; stls_vbl_add_null(&in, var, 12);
    var[11] = 12; stls_vbl_add_null(&in, var, 12);
    var[11] = 13; stls_vbl_add_null(&in, var, 12);
    var[11] = 14; stls_vbl_add_null(&in, var, 12);
    var[11] = 15; stls_vbl_add_null(&in, var, 12);
    var[11] = 16; stls_vbl_add_null(&in, var, 12);

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
disman_script_mib_free_smLaunchEntry(smLaunchEntry_t **smLaunchEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (smLaunchEntry) {
        for (i = 0; smLaunchEntry[i]; i++) {
            p = (char *) smLaunchEntry[i] + sizeof(smLaunchEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(smLaunchEntry[i]);
        }
        g_free(smLaunchEntry);
    }
}

static smRunEntry_t *
assign_smRunEntry(GSList *vbl)
{
    GSList *elem;
    smRunEntry_t *smRunEntry;
    char *p;

    smRunEntry = (smRunEntry_t *) g_malloc0(sizeof(smRunEntry_t) + sizeof(GSList *));
    if (! smRunEntry) {
        return NULL;
    }

    p = (char *) smRunEntry + sizeof(smRunEntry_t);
    * (GSList **) p = vbl;

    {
        GSnmpVarBind *vb = (GSnmpVarBind *) vbl->data;
        if (vb->id_len < 13) return NULL;
        /* XXX fix this smRunEntry->smLaunchOwner = ?; */
        /* XXX fix this smRunEntry->smLaunchName = ?; */
        smRunEntry->smRunIndex = (gint32 *) &(vb->id[12]);
        if (vb->id_len > 13) return NULL;
    }

    for (elem = vbl; elem; elem = g_slist_next(elem)) {
        GSnmpVarBind *vb = (GSnmpVarBind *) elem->data;
        if (vb->type == G_SNMP_ENDOFMIBVIEW
            || (vb->type == G_SNMP_NOSUCHOBJECT)
            || (vb->type == G_SNMP_NOSUCHINSTANCE)) {
            continue;
        }
        if (vb->id_len > 12 && vb->id[11] == 2) {
            smRunEntry->_smRunArgumentLength = vb->syntax_len;
            smRunEntry->smRunArgument = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 3) {
            smRunEntry->_smRunStartTimeLength = vb->syntax_len;
            smRunEntry->smRunStartTime = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 4) {
            smRunEntry->_smRunEndTimeLength = vb->syntax_len;
            smRunEntry->smRunEndTime = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 5) {
            smRunEntry->smRunLifeTime = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 6) {
            smRunEntry->smRunExpireTime = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 7) {
            smRunEntry->smRunExitCode = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 8) {
            smRunEntry->_smRunResultLength = vb->syntax_len;
            smRunEntry->smRunResult = vb->syntax.uc;
        }
        if (vb->id_len > 12 && vb->id[11] == 9) {
            smRunEntry->smRunControl = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 10) {
            smRunEntry->smRunState = &(vb->syntax.i32[0]);
        }
        if (vb->id_len > 12 && vb->id[11] == 11) {
            smRunEntry->_smRunErrorLength = vb->syntax_len;
            smRunEntry->smRunError = vb->syntax.uc;
        }
    }

    return smRunEntry;
}

int
disman_script_mib_get_smRunEntry(host_snmp *s, smRunEntry_t ***smRunEntry)
{
    GSList *in = NULL, *out = NULL;
    GSList *row;
    int i;
    static guint32 var[] = {1, 3, 6, 1, 2, 1, 64, 1, 4, 2, 1, 0};

    *smRunEntry = NULL;

    var[11] = 2; stls_vbl_add_null(&in, var, 12);
    var[11] = 3; stls_vbl_add_null(&in, var, 12);
    var[11] = 4; stls_vbl_add_null(&in, var, 12);
    var[11] = 5; stls_vbl_add_null(&in, var, 12);
    var[11] = 6; stls_vbl_add_null(&in, var, 12);
    var[11] = 7; stls_vbl_add_null(&in, var, 12);
    var[11] = 8; stls_vbl_add_null(&in, var, 12);
    var[11] = 9; stls_vbl_add_null(&in, var, 12);
    var[11] = 10; stls_vbl_add_null(&in, var, 12);
    var[11] = 11; stls_vbl_add_null(&in, var, 12);

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
disman_script_mib_free_smRunEntry(smRunEntry_t **smRunEntry)
{
    GSList *vbl;
    char *p;
    int i;

    if (smRunEntry) {
        for (i = 0; smRunEntry[i]; i++) {
            p = (char *) smRunEntry[i] + sizeof(smRunEntry_t);
            vbl = * (GSList **) p;
            stls_vbl_free(vbl);
            g_free(smRunEntry[i]);
        }
        g_free(smRunEntry);
    }
}

