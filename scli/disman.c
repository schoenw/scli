/* 
 * disman.c -- scli disman mode implementation
 *
 * Copyright (C) 2001 Juergen Schoenwaelder
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * 
 * @(#) $Id$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "scli.h"

#include "iana-language-mib.h"
#include "disman-script-mib.h"
#include "disman-schedule-mib.h"

#include <time.h>



static guint32 const oid_javabc[] = { IANA_LANGUAGE_MIB_IANALANGJAVABYTECODE };
static guint32 const oid_tcl[]    = { IANA_LANGUAGE_MIB_IANALANGTCL };
static guint32 const oid_perl[]   = { IANA_LANGUAGE_MIB_IANALANGPERL };
static guint32 const oid_scheme[] = { IANA_LANGUAGE_MIB_IANALANGSCHEME };
static guint32 const oid_srsl[]   = { IANA_LANGUAGE_MIB_IANALANGSRSL };
static guint32 const oid_psl[]    = { IANA_LANGUAGE_MIB_IANALANGPSL };
static guint32 const oid_smsl[]   = { IANA_LANGUAGE_MIB_IANALANGSMSL };

static stls_identity_t const languages[] = {
    { oid_javabc,	sizeof(oid_javabc) / sizeof(guint32),	"Java" },
    { oid_tcl,		sizeof(oid_tcl) / sizeof(guint32),	"Tcl" },
    { oid_perl,		sizeof(oid_perl) / sizeof(guint32),	"Perl" },
    { oid_scheme,	sizeof(oid_scheme) / sizeof(guint32),	"Scheme" },
    { oid_srsl,		sizeof(oid_srsl) / sizeof(guint32),	"SRSL" },
    { oid_psl,		sizeof(oid_psl) / sizeof(guint32),	"PSL" },
    { oid_smsl,		sizeof(oid_smsl) / sizeof(guint32),	"SMSL" },
    { NULL, 0, NULL }
};



static const char *weekdays[] = {
    "sun", "mon", "tue", "wed", "thu", "fri", "sat", NULL
};

static const char *months[] = {
    "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec", NULL
};

static const char *days[] = {
    "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10",
    "d11", "d12", "d13", "d14", "d15", "d16", "d17", "d18", "d19", "d20",
    "d21", "d22", "d23", "d24", "d25", "d26", "d27", "d28", "d29", "d30",
    "d31",
    "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10",
    "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19", "r20",
    "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30",
    "r31", NULL
};

static const char *ddays[] = {
    "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10",
    "d11", "d12", "d13", "d14", "d15", "d16", "d17", "d18", "d19", "d20",
    "d21", "d22", "d23", "d24", "d25", "d26", "d27", "d28", "d29", "d30",
    "d31", NULL
};

static const char *rdays[] = {
    "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10",
    "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19", "r20",
    "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30",
    "r31", NULL
};

static const char *hours[] = {
    "h0", "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8", "h9", "h10",
    "h11", "h12", "h13", "h14", "h15", "h16", "h17", "h18", "h19", "h20",
    "h21", "h22", "h23", NULL
};

static const char *minutes[] = {
    "m0", "m1", "m2", "m3", "m4", "m5", "m6", "m7", "m8", "m9", "m10",
    "m11", "m12", "m13", "m14", "m15", "m16", "m17", "m18", "m19", "m20",
    "m21", "m22", "m23", "m24", "m25", "m26", "m27", "m28", "m29", "m30",
    "m31", "m32", "m33", "m34", "m35", "m36", "m37", "m38", "m39", "m40",
    "m41", "m42", "m43", "m44", "m45", "m46", "m47", "m48", "m49", "m50",
    "m51", "m52", "m53", "m54", "m55", "m56", "m57", "m58", "m59", NULL
};



static time_t
date_to_time(guchar *date, gsize len)
{
    struct tm tm;
    time_t t = 0;
    
    if (len == 8 || len == 11) {
	memset(&tm, 0, sizeof(struct tm));
	tm.tm_year = ((date[0] << 8) + date[1]) - 1900;
	tm.tm_mon  = date[2];
	tm.tm_mday = date[3];
	tm.tm_hour = date[4];
	tm.tm_min  = date[5];
	tm.tm_sec  = date[6];
	t = mktime(&tm);
    }

    return t;
}



static void
fmt_last_change(GString *s, guchar *date, gsize len)
{
    static char const *months[] = {
	"---",
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    int year;
    time_t now, lch;
    
    if (! date || (len != 8 && len != 11)) {
	g_string_sprintfa(s, "--- -- ----- ");
	return;
    }

    now = time(NULL);
    lch = date_to_time(date, len);

    year = (date[0] << 8) + date[1];

    if (now-lch > 3600 * 24 * 365) {
	g_string_sprintfa(s, "%3s %2u  %4u ",
			  months[date[2] < 13 ? date[2] : 0], date[3], year);
    } else {
	g_string_sprintfa(s, "%3s %2u %02u:%02u ",
			  months[date[2] < 13 ? date[2] : 0], date[3],
			  date[4], date[5]);
    }
}



static void
fmt_storage_type(GString *s, gint32 *storage)
{
    static stls_enum_t const storage_types[] = {
	{ 1, "o" },	/* other */
	{ 2, "v" },	/* volatile */
	{ 3, "n" },	/* nonVolatile */
	{ 4, "p" },	/* permanent */
	{ 5, "r" },	/* readOnly */
	{ 0, NULL }
    };

    fmt_enum(s, 1, storage_types, storage);
}



static void
fmt_row_status(GString *s, gint32 *status)
{
    static stls_enum_t const row_states[] = {
	{ 1, "a" },	/* active */
	{ 2, "s" },	/* notInService */
	{ 3, "r" },	/* notReady */
	{ 0, NULL }
    };

    fmt_enum(s, 1, row_states, status);
}



static void
fmt_script_admin_status(GString *s, gint32 *status)
{
    static stls_enum_t const script_admin_states[] = {
	{ DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_ENABLED,	"e" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_DISABLED,	"d" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTADMINSTATUS_EDITING,	"t" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, script_admin_states, status);
}



static void
fmt_script_oper_status(GString *s, gint32 *status)
{
    static stls_enum_t const script_oper_states[] = {
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_ENABLED,		"e" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_DISABLED,	"d" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_EDITING,		"t" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_RETRIEVING,	"r" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_COMPILING,	"c" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_NOSUCHSCRIPT,	"n" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_ACCESSDENIED,	"a" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_WRONGLANGUAGE,	"w" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_WRONGVERSION,	"v" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_COMPILATIONFAILED, "f" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_NORESOURCESLEFT,	"o" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_UNKNOWNPROTOCOL,	"u" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_PROTOCOLFAILURE,	"p" },
	{ DISMAN_SCRIPT_MIB_SMSCRIPTOPERSTATUS_GENERICERROR,	"g" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, script_oper_states, status);
}



static void
fmt_launch_admin_status(GString *s, gint32 *status)
{
    static stls_enum_t const launch_admin_states[] = {
	{ DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_ENABLED,	"e" },
	{ DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_DISABLED,	"d" },
	{ DISMAN_SCRIPT_MIB_SMLAUNCHADMINSTATUS_AUTOSTART,	"a" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, launch_admin_states, status);
}



static void
fmt_launch_oper_status(GString *s, gint32 *status)
{
    static stls_enum_t const launch_oper_states[] = {
	{ DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_ENABLED,		"e" },
	{ DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_DISABLED,	"d" },
	{ DISMAN_SCRIPT_MIB_SMLAUNCHOPERSTATUS_EXPIRED,		"x" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, launch_oper_states, status);
}



static void
fmt_run_state(GString *s, gint32 *state)
{
    char const *name;

    static stls_enum_t const run_states[] = {
	{ DISMAN_SCRIPT_MIB_SMRUNSTATE_INITIALIZING,	"I" },
	{ DISMAN_SCRIPT_MIB_SMRUNSTATE_EXECUTING,	"R" },
	{ DISMAN_SCRIPT_MIB_SMRUNSTATE_SUSPENDING,	"U" },
	{ DISMAN_SCRIPT_MIB_SMRUNSTATE_SUSPENDED,	"S" },
	{ DISMAN_SCRIPT_MIB_SMRUNSTATE_RESUMING,	"R" },
	{ DISMAN_SCRIPT_MIB_SMRUNSTATE_ABORTING,	"A" },
	{ DISMAN_SCRIPT_MIB_SMRUNSTATE_TERMINATED,	"T" },
	{ 0, NULL }
    };
    
    if (! state) {
	g_string_append(s, "-");
	return;
    }
    
    name = stls_enum_get_label(run_states, *state);
    if (name) {
	g_string_append(s, name);
    } else {
	g_string_append(s, "?");
    }
}


static void
fmt_exit_code(GString *s, gint32 *code)
{
    char const *name;

    static stls_enum_t const exit_codes[] = {
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_NOERROR,		"N" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_HALTED,		"H" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_LIFETIMEEXCEEDED,	"T" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_NORESOURCESLEFT,	"O" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_LANGUAGEERROR,	"L" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_RUNTIMEERROR,		"R" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_INVALIDARGUMENT,	"A" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_SECURITYVIOLATION,	"S" },
	{ DISMAN_SCRIPT_MIB_SMRUNEXITCODE_GENERICERROR,		"G" },
	{ 0, NULL }
    };
    
    if (! code) {
	g_string_append(s, "-");
	return;
    }
    
    name = stls_enum_get_label(exit_codes, *code);
    if (name) {
	g_string_append(s, name);
    } else {
	g_string_append(s, "?");
    }
}



static void
fmt_schedule_admin_status(GString *s, gint32 *status)
{
    static stls_enum_t const schedule_admin_states[] = {
	{ DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_ENABLED,		"e" },
	{ DISMAN_SCHEDULE_MIB_SCHEDADMINSTATUS_DISABLED,	"d" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, schedule_admin_states, status);
}



static void
fmt_schedule_oper_status(GString *s, gint32 *status)
{
    static stls_enum_t const schedule_oper_states[] = {
	{ DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_ENABLED,	"e" },
	{ DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_DISABLED,	"d" },
	{ DISMAN_SCHEDULE_MIB_SCHEDOPERSTATUS_FINISHED,	"f" },
	{ 0, NULL }
    };

    fmt_enum(s, 1, schedule_oper_states, status);
}



static int
fmt_item(GString *s, const char **labels, guchar *bits, gsize bits_len)
{
    int i, bit, start = -1;
    int cnt = 0;

    if (! bits) {
	return 0;
    }

    for (i = 0; labels[i]; i++) {
	bit = (i/8 < bits_len) ? bits[i/8] & 1 <<(7-(i%8)) : 0;
	if (bit) cnt++;
    }
    if (cnt == i) {
	return -1;
    }

    /* XXX should recognize / ranges (are they called ranges?) */
    
    for (i = 0; labels[i]; i++) {
	bit = (i/8 < bits_len) ? bits[i/8] & 1 <<(7-(i%8)) : 0;
	if (bit) {
	    if (start == -1) {
		g_string_sprintfa(s, "%s%s", s->len ? " " : "", labels[i]);
		start = i;
	    }
	} else {
	    if (start >= 0 && start != i-1) {
		g_string_sprintfa(s, "-%s", labels[i-1]);
	    }
	    start = -1;
	}
    }
    if (start >= 0 && start != i-1) {
	g_string_sprintfa(s, "-%s", labels[i-1]);
    }

    return cnt;
}



static char*
fmt_expression(disman_schedule_mib_schedEntry_t *schedEntry)
{
    static GString *s = NULL;
    int w = 0, o = 0, d = 0, h = 0, m = 0;

    if (!s) {
	s = g_string_new(NULL);
    } else {
	s = g_string_truncate(s, 0);
    }

    if (! schedEntry->schedType) {
	return "?";
    }

    switch (*schedEntry->schedType) {
    case DISMAN_SCHEDULE_MIB_SCHEDTYPE_PERIODIC:
	if (schedEntry->schedInterval) {
	    g_string_sprintfa(s, "%u", *schedEntry->schedInterval);
	} else {
	    g_string_append(s, "?");
	}
	break;
    case DISMAN_SCHEDULE_MIB_SCHEDTYPE_CALENDAR:
    case DISMAN_SCHEDULE_MIB_SCHEDTYPE_ONESHOT:
	w = fmt_item(s, weekdays,
		     schedEntry->schedWeekDay, schedEntry->_schedWeekDayLength);
	o = fmt_item(s, months,
		     schedEntry->schedMonth, schedEntry->_schedMonthLength);
	d = fmt_item(s, ddays,
		     schedEntry->schedDay, schedEntry->_schedDayLength);
	h = fmt_item(s, hours,
		     schedEntry->schedHour, schedEntry->_schedHourLength);
	m = fmt_item(s, minutes,
		     schedEntry->schedMinute, schedEntry->_schedMinuteLength);
	
	if (w == 0 || o == 0 || d == 0 || h == 0 || m == 0) {
	    g_string_truncate(s, 0);
	}
	
	if (w == -1 && o == -1 && d == -1 && h == -1 && m == -1) {
	    g_string_append(s, "*");
	}
	break;
    default:
	g_string_append(s, "?");
    }
    return s->str;
}



static char const *
get_script_lang_name(disman_script_mib_smScriptEntry_t *smScriptEntry,
		     disman_script_mib_smLangEntry_t **smLangTable)
{
    int i;

    if (! smScriptEntry->smScriptLanguage) {
	return NULL;
    }
    
    for (i = 0; smLangTable[i]; i++) {
	if (smLangTable[i]->smLangIndex == *smScriptEntry->smScriptLanguage) {
	    return stls_identity_get_label(languages,
				   smLangTable[i]->smLangLanguage,
				   smLangTable[i]->_smLangLanguageLength);
	}
    }
    return NULL;
}



static disman_script_mib_smLaunchEntry_t*
get_launch_entry(disman_script_mib_smRunEntry_t *smRunEntry,
		 disman_script_mib_smLaunchEntry_t **smLaunchTable)
{
    int l;

    if (! smLaunchTable) {
	return NULL;
    }
    
    for (l = 0; smLaunchTable[l]; l++) {
	if (smLaunchTable[l]->_smLaunchOwnerLength == smRunEntry->_smLaunchOwnerLength
	    && memcmp(smLaunchTable[l]->smLaunchOwner, smRunEntry->smLaunchOwner, smRunEntry->_smLaunchOwnerLength) == 0
	    && smLaunchTable[l]->_smLaunchNameLength == smRunEntry->_smLaunchNameLength
	    && memcmp(smLaunchTable[l]->smLaunchName, smRunEntry->smLaunchName, smRunEntry->_smLaunchNameLength) == 0
	    ) {
	    return smLaunchTable[l];
	}
    }

    return NULL;
}



static void
show_extension(GString *s,
	       disman_script_mib_smExtsnEntry_t *smExtsnEntry,
	       int c)
{
    int const indent = 12;
    
    if (smExtsnEntry->smExtsnDescr) {
	g_string_sprintfa(s, "%c%-*s ", c, indent, "- Extension:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smExtsnEntry->_smExtsnDescrLength,
			  smExtsnEntry->smExtsnDescr);
    }
    if (c == '`') c = ' ';
    if (smExtsnEntry->smExtsnVersion) {
	g_string_sprintfa(s, "%c%-*s ", c, indent, "  Version:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smExtsnEntry->_smExtsnVersionLength,
			  smExtsnEntry->smExtsnVersion);
    }
    if (c == '`') c = ' ';
    if (smExtsnEntry->smExtsnVendor) {
	scli_vendor_t *vendor;
	vendor = scli_get_iana_vendor(smExtsnEntry->smExtsnVendor,
				      smExtsnEntry->_smExtsnVendorLength);
	if (vendor && vendor->name) {
	    g_string_sprintfa(s, "%c%-*s  ", c, indent, "  Vendor:");
	    if (vendor->id) {
		g_string_append(s, vendor->name);
		if (vendor->url) {
		    g_string_sprintfa(s, " <%s>", vendor->url);
		}
	    } else {
		g_string_sprintfa(s, "unknown (%s)", vendor->name);
	    }
	    g_string_append(s, "\n");
	}
    }
    if (c == '`') c = ' ';
    if (smExtsnEntry->smExtsnRevision && smExtsnEntry->_smExtsnRevisionLength) {
	g_string_sprintfa(s, "%c%-*s ", c, indent, "  Revision:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smExtsnEntry->_smExtsnRevisionLength,
			  smExtsnEntry->smExtsnRevision);
    }
}



static void
show_language(GString *s,
	      disman_script_mib_smLangEntry_t *smLangEntry,
	      disman_script_mib_smExtsnEntry_t **smExtsnTable)
{
    int i, j;
    int const indent = 13;

    if (smLangEntry->smLangDescr) {
	g_string_sprintfa(s, "%-*s ", indent, "Descr:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smLangEntry->_smLangDescrLength,
			  smLangEntry->smLangDescr);
    }
    if (smLangEntry->smLangVersion) {
	g_string_sprintfa(s, "%-*s ", indent, "Version:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smLangEntry->_smLangVersionLength,
			  smLangEntry->smLangVersion);
    }
    if (smLangEntry->smLangVendor) {
	scli_vendor_t *vendor;
	vendor = scli_get_iana_vendor(smLangEntry->smLangVendor,
				      smLangEntry->_smLangVendorLength);
	if (vendor && vendor->name) {
	    g_string_sprintfa(s, "%-*s  ", indent, "Vendor:");
	    if (vendor->id) {
		g_string_append(s, vendor->name);
		if (vendor->url) {
		    g_string_sprintfa(s, " <%s>", vendor->url);
		}
	    } else {
		g_string_sprintfa(s, "unknown (%s)", vendor->name);
	    }
	    g_string_append(s, "\n");
	}
    }
    if (smLangEntry->smLangRevision && smLangEntry->_smLangRevisionLength) {
	g_string_sprintfa(s, "%-*s ", indent, "Revision:");
	g_string_sprintfa(s, " %.*s\n",
			  (int) smLangEntry->_smLangRevisionLength,
			  smLangEntry->smLangRevision);
    }

    if (smExtsnTable) {
	for (i = 0; smExtsnTable[i]; i++) {
	    if (smExtsnTable[i]->smLangIndex != smLangEntry->smLangIndex) {
		continue;
	    }
	    for (j = i+1; smExtsnTable[j]; j++) {
		if (smExtsnTable[j]->smLangIndex == smLangEntry->smLangIndex) {
		    break;
		}
	    }
	    show_extension(s, smExtsnTable[i], smExtsnTable[j] ? '|' : '`');
	}
    }
}



static int
cmd_languages(scli_interp_t *interp, int argc, char **argv)
{
    disman_script_mib_smLangEntry_t **smLangTable = NULL;
    disman_script_mib_smExtsnEntry_t **smExtsnTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_script_mib_get_smLangTable(interp->peer, &smLangTable)) {
	return SCLI_ERROR;
    }
    (void) disman_script_mib_get_smExtsnTable(interp->peer, &smExtsnTable);

    if (smLangTable) {
	for (i = 0; smLangTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_language(interp->result, smLangTable[i], smExtsnTable);
	}
    }

    if (smLangTable) disman_script_mib_free_smLangTable(smLangTable);
    if (smExtsnTable) disman_script_mib_free_smExtsnTable(smExtsnTable);
    
    return SCLI_OK;
}



static void
show_script_details(GString *s,
		    disman_script_mib_smScriptEntry_t *smScriptEntry,
		    char const *language)
{
    int const width = 20;
    
    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptAdminStatus,
	     smScriptEntry->smScriptAdminStatus);
    g_string_append(s, "Owner:    ");
    g_string_sprintfa(s, "%*s\n",
		      (int) smScriptEntry->_smScriptOwnerLength,
		      smScriptEntry->smScriptOwner);

    g_string_append(s, "OperStatus:  ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptOperStatus,
	     smScriptEntry->smScriptOperStatus);
    g_string_append(s, "Name:     ");
    g_string_sprintfa(s, "%*s\n",
		      (int) smScriptEntry->_smScriptNameLength,
		      smScriptEntry->smScriptName);
    
    g_string_append(s, "RowStatus:   ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptRowStatus,
	     smScriptEntry->smScriptRowStatus);
    g_string_append(s, "Language: ");
    if (smScriptEntry->smScriptLanguage) {
	if (language) {
	    g_string_sprintfa(s, "%s", language);
	} else {
	    g_string_sprintfa(s, "%d",
			      *(smScriptEntry->smScriptLanguage));
	}
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Storage:     ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptStorageType,
	     smScriptEntry->smScriptStorageType);
    g_string_append(s, "Change:   ");
    if (smScriptEntry->smScriptLastChange) {
	g_string_append(s, fmt_date_and_time(smScriptEntry->smScriptLastChange,
			     smScriptEntry->_smScriptLastChangeLength));
    }
    g_string_append(s, "\n");
    
    if (smScriptEntry->smScriptSource) {
	g_string_sprintfa(s, "Source:      %.*s\n",
			  (int) smScriptEntry->_smScriptSourceLength,
			  smScriptEntry->smScriptSource);
    }

    if (smScriptEntry->smScriptError && smScriptEntry->_smScriptErrorLength) {
	g_string_sprintfa(s, "Error:       %.*s\n",
			  (int) smScriptEntry->_smScriptErrorLength,
			  smScriptEntry->smScriptError);
    }

    if (smScriptEntry->smScriptDescr) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) smScriptEntry->_smScriptDescrLength,
			  smScriptEntry->smScriptDescr);
    }
}



static int
cmd_script_details(scli_interp_t *interp, int argc, char **argv)
{
    disman_script_mib_smLangEntry_t **smLangTable = NULL;
    disman_script_mib_smScriptEntry_t **smScriptTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_script_mib_get_smLangTable(interp->peer, &smLangTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable);

    if (smScriptTable) {
	for (i = 0; smScriptTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_script_details(interp->result, smScriptTable[i],
			get_script_lang_name(smScriptTable[i], smLangTable));
	}
    }

    if (smScriptTable) disman_script_mib_free_smScriptTable(smScriptTable);
    if (smLangTable) disman_script_mib_free_smLangTable(smLangTable);

    return SCLI_OK;
}



static void
show_script_info(GString *s,
		 disman_script_mib_smScriptEntry_t *smScriptEntry, 
		 char const *language, int launches,
		 int owner_width, int lang_width)
{
    fmt_script_admin_status(s, smScriptEntry->smScriptAdminStatus);
    fmt_script_oper_status(s, smScriptEntry->smScriptOperStatus);
    fmt_storage_type(s, smScriptEntry->smScriptStorageType);
    fmt_row_status(s, smScriptEntry->smScriptRowStatus);

    g_string_sprintfa(s, " %3u ", launches);
    
    g_string_sprintfa(s, "%-*.*s ", owner_width,
		      (int) smScriptEntry->_smScriptOwnerLength,
		      smScriptEntry->smScriptOwner);

    g_string_sprintfa(s, "%-*s ", lang_width, language ? language : "");

    fmt_last_change(s, smScriptEntry->smScriptLastChange,
		    smScriptEntry->_smScriptLastChangeLength);
    
    g_string_sprintfa(s, "%.*s",
		      (int) smScriptEntry->_smScriptNameLength,
		      smScriptEntry->smScriptName);
    g_string_append(s, "\n");
}



static int
count_launches(disman_script_mib_smScriptEntry_t *smScriptEntry,
	       disman_script_mib_smLaunchEntry_t **smLaunchTable)
{
    int i;
    int launches = 0;

    if (! smLaunchTable) {
	return 0;
    }

    for (i = 0; smLaunchTable[i]; i++) {
	if (smLaunchTable[i]->smLaunchScriptOwner
	    && smLaunchTable[i]->smLaunchScriptName
	    && (smLaunchTable[i]->_smLaunchScriptOwnerLength ==
		smScriptEntry->_smScriptOwnerLength)
	    && (smLaunchTable[i]->_smLaunchScriptNameLength ==
		smScriptEntry->_smScriptNameLength)
	    && memcmp(smLaunchTable[i]->smLaunchScriptOwner,
		      smScriptEntry->smScriptOwner,
		      smScriptEntry->_smScriptOwnerLength) == 0
	    && memcmp(smLaunchTable[i]->smLaunchScriptName,
		      smScriptEntry->smScriptName,
		      smScriptEntry->_smScriptNameLength) == 0)
	    {
	    launches++;
	}
    }
    
    return launches;
}



static int
cmd_script_info(scli_interp_t *interp, int argc, char **argv)
{
    disman_script_mib_smLangEntry_t **smLangTable = NULL;
    disman_script_mib_smScriptEntry_t **smScriptTable = NULL;
    disman_script_mib_smLaunchEntry_t **smLaunchTable = NULL;
    int i;
    int owner_width = 8, lang_width = 8;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_script_mib_get_smLangTable(interp->peer, &smLangTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable);
    (void) disman_script_mib_get_smLaunchTable(interp->peer, &smLaunchTable);

    if (smScriptTable) {
	for (i = 0; smScriptTable[i]; i++) {
	    if (smScriptTable[i]->_smScriptOwnerLength > owner_width) {
		owner_width = smScriptTable[i]->_smScriptOwnerLength;
	    }
	}
	g_string_sprintfa(interp->header,
			  "STATE  L %-*s %-*s LAST CHANGE  NAME",
			  owner_width, "OWNER", lang_width, "LANGUAGE");
	for (i = 0; smScriptTable[i]; i++) {
	    show_script_info(interp->result, smScriptTable[i],
		     get_script_lang_name(smScriptTable[i], smLangTable),
			     count_launches(smScriptTable[i], smLaunchTable),
			     owner_width, lang_width);
	}
    }

    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);
    if (smScriptTable) disman_script_mib_free_smScriptTable(smScriptTable);
    if (smLangTable) disman_script_mib_free_smLangTable(smLangTable);

    return SCLI_OK;
}



static int
count_runs(disman_script_mib_smLaunchEntry_t *smLaunchEntry,
	   disman_script_mib_smRunEntry_t **smRunTable)
{
    int i;
    int runs = 0;

    if (! smRunTable) {
	return 0;
    }

    for (i = 0; smRunTable[i]; i++) {
	if ((smRunTable[i]->_smLaunchOwnerLength ==
	     smLaunchEntry->_smLaunchOwnerLength)
	    && (smRunTable[i]->_smLaunchNameLength ==
		smLaunchEntry->_smLaunchNameLength)
	    && memcmp(smRunTable[i]->smLaunchOwner,
		      smLaunchEntry->smLaunchOwner,
		      smLaunchEntry->_smLaunchOwnerLength) == 0
	    && memcmp(smRunTable[i]->smLaunchName,
		      smLaunchEntry->smLaunchName,
		      smLaunchEntry->_smLaunchNameLength) == 0)
	    {
	    runs++;
	}
    }
    
    return runs;
}



static void
show_launch_info(GString *s,
		 disman_script_mib_smLaunchEntry_t *smLaunchEntry,
		 int runs, int owner_width)
{
    fmt_launch_admin_status(s, smLaunchEntry->smLaunchAdminStatus);
    fmt_launch_oper_status(s, smLaunchEntry->smLaunchOperStatus);
    fmt_storage_type(s, smLaunchEntry->smLaunchStorageType);
    fmt_row_status(s, smLaunchEntry->smLaunchRowStatus);

    g_string_sprintfa(s, " %3u ", runs);
    
    g_string_sprintfa(s, "%-*.*s ", owner_width,
		      (int) smLaunchEntry->_smLaunchOwnerLength,
		      smLaunchEntry->smLaunchOwner);

    fmt_last_change(s, smLaunchEntry->smLaunchLastChange,
		    smLaunchEntry->_smLaunchLastChangeLength);
    
    g_string_sprintfa(s, "%.*s",
		      (int) smLaunchEntry->_smLaunchNameLength,
		      smLaunchEntry->smLaunchName);
    if (smLaunchEntry->smLaunchScriptName) {
	g_string_sprintfa(s, " -> %.*s",
			  (int) smLaunchEntry->_smLaunchScriptNameLength,
			  smLaunchEntry->smLaunchScriptName);
    }
    if (smLaunchEntry->smLaunchScriptOwner) {
	if (smLaunchEntry->_smLaunchScriptOwnerLength
	    != smLaunchEntry->_smLaunchOwnerLength ||
	    memcmp(smLaunchEntry->smLaunchScriptOwner,
		   smLaunchEntry->smLaunchOwner,
		   smLaunchEntry->_smLaunchOwnerLength)) {
	    g_string_sprintfa(s, " (%.*s)",
			  (int) smLaunchEntry->_smLaunchScriptOwnerLength,
			  smLaunchEntry->smLaunchScriptOwner);
	}
    }
    g_string_append(s, "\n");
}



static int
cmd_launch_info(scli_interp_t *interp, int argc, char **argv)
{
    disman_script_mib_smScriptEntry_t **smScriptTable = NULL;
    disman_script_mib_smLaunchEntry_t **smLaunchTable = NULL;
    disman_script_mib_smRunEntry_t **smRunTable = NULL;
    int i;
    int owner_width = 8;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_script_mib_get_smLaunchTable(interp->peer, &smLaunchTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smScriptTable(interp->peer, &smScriptTable);
    (void) disman_script_mib_get_smRunTable(interp->peer, &smRunTable);

    if (smLaunchTable) {
	for (i = 0; smLaunchTable[i]; i++) {
	    if (smLaunchTable[i]->_smLaunchOwnerLength > owner_width) {
		owner_width = smLaunchTable[i]->_smLaunchOwnerLength;
	    }
	}
	g_string_sprintfa(interp->header,
			  "STATE  R %-*s LAST CHANGE  NAME",
			  owner_width, "OWNER");
	for (i = 0; smLaunchTable[i]; i++) {
	    show_launch_info(interp->result, smLaunchTable[i],
			     count_runs(smLaunchTable[i], smRunTable),
			     owner_width);
	}
    }

    if (smRunTable) disman_script_mib_free_smRunTable(smRunTable);
    if (smScriptTable) disman_script_mib_free_smScriptTable(smScriptTable);
    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);

    return SCLI_OK;
}



static void
show_launch_details(GString *s,
		    disman_script_mib_smLaunchEntry_t *smLaunchEntry)
{
    int const width = 20;

    g_string_append(s, "Life Time:   ");
    if (smLaunchEntry->smLaunchLifeTime) {
	if (*smLaunchEntry->smLaunchLifeTime == 2147483647) {
	    g_string_sprintfa(s, "unlimited           ");
	} else {
	    g_string_sprintfa(s, "%9s         ",
		      fmt_seconds(*smLaunchEntry->smLaunchLifeTime/100));
	}
    } else {
	g_string_sprintfa(s, "%9s         ", "");
    }
    g_string_append(s, "L-Owner:  ");
    if (smLaunchEntry->smLaunchOwner) {
	g_string_sprintfa(s, "%.*s",
			  (int) smLaunchEntry->_smLaunchOwnerLength,
			  smLaunchEntry->smLaunchOwner);
    }
    g_string_append(s, "\n");

    g_string_append(s, "Expire Time: ");
    if (smLaunchEntry->smLaunchExpireTime) {
	g_string_sprintfa(s, "%9s           ",
			  fmt_seconds(*smLaunchEntry->smLaunchExpireTime/100));
    } else {
	g_string_sprintfa(s, "%9s         ", "");
    }
    g_string_append(s, "L-Name:   ");
    if (smLaunchEntry->smLaunchName) {
	g_string_sprintfa(s, "%.*s",
			  (int) smLaunchEntry->_smLaunchNameLength,
			  smLaunchEntry->smLaunchName);
    }
    g_string_append(s, "\n");
        
    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, width, disman_script_mib_enums_smLaunchAdminStatus,
	     smLaunchEntry->smLaunchAdminStatus);
    g_string_append(s, "S-Owner:  ");
    if (smLaunchEntry->smLaunchScriptOwner) {
	g_string_sprintfa(s, "%.*s ",
			  (int) smLaunchEntry->_smLaunchScriptOwnerLength,
			  smLaunchEntry->smLaunchScriptOwner);
    }
    g_string_append(s, "\n");

    g_string_append(s, "OperStatus:  ");
    fmt_enum(s, width, disman_script_mib_enums_smScriptOperStatus,
	     smLaunchEntry->smLaunchOperStatus);
    g_string_append(s, "S-Name:   ");
    if (smLaunchEntry->smLaunchScriptName) {
	g_string_sprintfa(s, "%.*s",
			  (int) smLaunchEntry->_smLaunchScriptNameLength,
			  smLaunchEntry->smLaunchScriptName);
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "RowStatus:   ");
    fmt_enum(s, width, disman_script_mib_enums_smLaunchRowStatus,
	     smLaunchEntry->smLaunchRowStatus);
    g_string_append(s, "Expires:  ");
    if (smLaunchEntry->smLaunchRowExpireTime) {
	if (*smLaunchEntry->smLaunchRowExpireTime == 2147483647) {
	    g_string_sprintfa(s, "never");
	} else {
	    g_string_sprintfa(s, "%s",
		      fmt_seconds(*smLaunchEntry->smLaunchRowExpireTime/100));
	}
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Storage:     ");
    fmt_enum(s, width, disman_script_mib_enums_smLaunchStorageType,
	     smLaunchEntry->smLaunchStorageType);
    g_string_append(s, "Change:   ");
    if (smLaunchEntry->smLaunchLastChange) {
	g_string_append(s, fmt_date_and_time(smLaunchEntry->smLaunchLastChange,
			     smLaunchEntry->_smLaunchLastChangeLength));
    }
    g_string_append(s, "\n");

    g_string_append(s, "Max Running: ");
    if (smLaunchEntry->smLaunchMaxRunning) {
	g_string_sprintfa(s, "%-*u", width, *smLaunchEntry->smLaunchMaxRunning);
    } else {
	g_string_sprintfa(s, "%*s", width, "");
    }
    g_string_append(s, "Max Term: ");
    if (smLaunchEntry->smLaunchMaxCompleted) {
	g_string_sprintfa(s, "%u", *smLaunchEntry->smLaunchMaxCompleted);
    }
    g_string_append(s, "\n");

    if (smLaunchEntry->smLaunchArgument
	&& smLaunchEntry->_smLaunchArgumentLength) {
	g_string_sprintfa(s, "Argument:    %.*s\n",
			  (int) smLaunchEntry->_smLaunchArgumentLength,
			  smLaunchEntry->smLaunchArgument);
    }

    if (smLaunchEntry->smLaunchError && smLaunchEntry->_smLaunchErrorLength) {
	g_string_sprintfa(s, "Error:       %.*s\n",
			  (int) smLaunchEntry->_smLaunchErrorLength,
			  smLaunchEntry->smLaunchError);
    }
}



static int
cmd_launch_details(scli_interp_t *interp, int argc, char **argv)
{
    disman_script_mib_smLaunchEntry_t **smLaunchTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_script_mib_get_smLaunchTable(interp->peer, &smLaunchTable)) {
	return SCLI_ERROR;
    }

    if (smLaunchTable) {
	for (i = 0; smLaunchTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_launch_details(interp->result, smLaunchTable[i]);
	}
    }

    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);

    return SCLI_OK;
}



static void
show_run_info(GString *s,
	      disman_script_mib_smRunEntry_t *smRunEntry,
	      int l_owner_width, int l_name_width)
{
    g_string_sprintfa(s, "%-*.*s ", l_owner_width,
		      (int) smRunEntry->_smLaunchOwnerLength,
		      smRunEntry->smLaunchOwner);
    g_string_sprintfa(s, "%-*.*s ", l_name_width,
		      (int) smRunEntry->_smLaunchNameLength,
		      smRunEntry->smLaunchName);
    
    g_string_sprintfa(s, "%5u  ", smRunEntry->smRunIndex);
    
    fmt_run_state(s, smRunEntry->smRunState);
    fmt_exit_code(s, smRunEntry->smRunExitCode);

    g_string_append(s, " ");
    
    if (smRunEntry->smRunLifeTime) {
	if (*smRunEntry->smRunLifeTime == 2147483647) {
	    g_string_sprintfa(s, "         - ");
	} else {
	    g_string_sprintfa(s, "%10s ",
			      fmt_seconds(*smRunEntry->smRunLifeTime/100));
	}
    } else {
	g_string_sprintfa(s, "%10s ", "");
    }
    if (smRunEntry->smRunExpireTime) {
	g_string_sprintfa(s, "%10s ", 
			      fmt_seconds(*smRunEntry->smRunExpireTime/100));
    } else {
	g_string_sprintfa(s, "%10s ", "");
    }

    g_string_append(s, "\n");
}



static int
cmd_run_info(scli_interp_t *interp, int argc, char **argv)
{
    disman_script_mib_smRunEntry_t **smRunTable = NULL;
    int l_owner_width = 8;
    int l_name_width = 8;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_script_mib_get_smRunTable(interp->peer, &smRunTable)) {
	return SCLI_ERROR;
    }

    if (smRunTable) {
	for (i = 0; smRunTable[i]; i++) {
	    if (smRunTable[i]->_smLaunchOwnerLength > l_owner_width) {
		l_owner_width = smRunTable[i]->_smLaunchOwnerLength;
	    }
	    if (smRunTable[i]->_smLaunchNameLength > l_name_width) {
		l_name_width = smRunTable[i]->_smLaunchNameLength;
	    }
	}
	g_string_sprintfa(interp->header,
			  "%-*s %-*s RUNID STAT      LIFE     EXPIRE",
			  l_owner_width, "L-OWNER", l_name_width, "L-NAME");
	for (i = 0; smRunTable[i]; i++) {
	    show_run_info(interp->result, smRunTable[i],
			  l_owner_width, l_name_width);
	}
    }

    if (smRunTable) disman_script_mib_free_smRunTable(smRunTable);
	
    return SCLI_OK;
}



static void
show_run_details(GString *s,
		 disman_script_mib_smRunEntry_t *smRunEntry,
		 disman_script_mib_smLaunchEntry_t *smLaunchEntry)
{
    char buffer[80];
    int const width = 20;

    g_snprintf(buffer, sizeof(buffer), "%u", smRunEntry->smRunIndex);
    g_string_append(s, "Index:       ");
    g_string_sprintfa(s, "%-7s\n", buffer);

    g_string_append(s, "L-Owner:     ");
    g_string_sprintfa(s, "%-*.*s ", width-1,
		      (int) smRunEntry->_smLaunchOwnerLength,
		      smRunEntry->smLaunchOwner);
    g_string_append(s, "L-Name:   ");
    g_string_sprintfa(s, "%.*s\n",
		      (int) smRunEntry->_smLaunchNameLength,
		      smRunEntry->smLaunchName);

    if (smLaunchEntry) {
	g_string_append(s, "S-Owner:     ");
	g_string_sprintfa(s, "%-*.*s ", width-1,
			  (int) smLaunchEntry->_smLaunchScriptOwnerLength,
			  smLaunchEntry->smLaunchScriptOwner);
	g_string_append(s, "S-Name:   ");
	g_string_sprintfa(s, "%.*s\n",
			  (int) smLaunchEntry->_smLaunchScriptNameLength,
			  smLaunchEntry->smLaunchScriptName);
    }
    
    g_string_append(s, "Status:      ");
    fmt_enum(s, width, disman_script_mib_enums_smRunState,
	     smRunEntry->smRunState);
    g_string_append(s, "Start:    ");
    if (smRunEntry->smRunStartTime) {
	g_string_append(s, fmt_date_and_time( smRunEntry->smRunStartTime,
				      smRunEntry->_smRunStartTimeLength));
    }
    g_string_append(s, "\n");

    g_string_append(s, "Exit Code:   ");
    fmt_enum(s, width, disman_script_mib_enums_smRunExitCode,
	     smRunEntry->smRunExitCode);
    g_string_append(s, "Result:   ");
    if (smRunEntry->smRunResultTime) {
	g_string_append(s, fmt_date_and_time(smRunEntry->smRunResultTime,
				     smRunEntry->_smRunResultTimeLength));
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Life Time:   ");
    if (smRunEntry->smRunLifeTime) {
	if (*smRunEntry->smRunLifeTime == 2147483647) {
	    g_string_sprintfa(s, "unlimited         ");
	} else {
	    g_string_sprintfa(s, "%9s         ",
			      fmt_seconds(*smRunEntry->smRunLifeTime/100));
	}
    } else {
	g_string_sprintfa(s, "%9s         ", "");
    }
    g_string_append(s, "  Error:    ");
    if (smRunEntry->smRunErrorTime) {
	g_string_append(s, fmt_date_and_time(smRunEntry->smRunErrorTime,
				     smRunEntry->_smRunErrorTimeLength));
    }
    g_string_append(s, "\n");

    g_string_append(s, "Expire Time: ");
    if (smRunEntry->smRunExpireTime) {
	g_string_sprintfa(s, "%9s         ",
			  fmt_seconds(*smRunEntry->smRunExpireTime/100));
    } else {
	g_string_sprintfa(s, "%9s         ", "");
    }
    g_string_append(s, "  End:      ");
    if (smRunEntry->smRunEndTime) {
	g_string_append(s, fmt_date_and_time(smRunEntry->smRunEndTime,
				     smRunEntry->_smRunEndTimeLength));
    }
    g_string_append(s, "\n");

    if (smRunEntry->smRunArgument && smRunEntry->_smRunArgumentLength) {
	g_string_sprintfa(s, "Argument:    %.*s\n",
			  (int) smRunEntry->_smRunArgumentLength,
			  smRunEntry->smRunArgument);
    }

    if (smRunEntry->smRunResult && smRunEntry->_smRunResultLength) {
	g_string_sprintfa(s, "Result:      %.*s\n",
			  (int) smRunEntry->_smRunResultLength,
			  smRunEntry->smRunResult);
    }

    if (smRunEntry->smRunError && smRunEntry->_smRunErrorLength) {
	g_string_sprintfa(s, "Error:       %.*s\n",
			  (int) smRunEntry->_smRunErrorLength,
			  smRunEntry->smRunError);
    }
}



static int
cmd_run_details(scli_interp_t *interp, int argc, char **argv)
{
    disman_script_mib_smLaunchEntry_t **smLaunchTable = NULL;
    disman_script_mib_smRunEntry_t **smRunTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_script_mib_get_smRunTable(interp->peer, &smRunTable)) {
	return SCLI_ERROR;
    }

    (void) disman_script_mib_get_smLaunchTable(interp->peer, &smLaunchTable);

    if (smRunTable) {
	for (i = 0; smRunTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_run_details(interp->result, smRunTable[i],
			     get_launch_entry(smRunTable[i], smLaunchTable));
	}
    }

    if (smLaunchTable) disman_script_mib_free_smLaunchTable(smLaunchTable);
    if (smRunTable) disman_script_mib_free_smRunTable(smRunTable);
	
    return SCLI_OK;
}



static void
show_scheduler_info(GString *s,
		    disman_schedule_mib_schedEntry_t *schedEntry,
		    int name_width, int owner_width)
{
    fmt_schedule_admin_status(s, schedEntry->schedAdminStatus);
    fmt_schedule_oper_status(s, schedEntry->schedOperStatus);
    fmt_storage_type(s, schedEntry->schedStorageType);
    fmt_row_status(s, schedEntry->schedRowStatus);

    g_string_sprintfa(s, "  %-*.*s ", owner_width,
		      (int) schedEntry->_schedOwnerLength,
		      schedEntry->schedOwner);
    
    g_string_sprintfa(s, "%-*.*s ", name_width,
		      (int) schedEntry->_schedNameLength,
		      schedEntry->schedName);

    fmt_enum(s, 8, disman_schedule_mib_enums_schedType,
	     schedEntry->schedType);

    g_string_sprintfa(s, " %s\n", fmt_expression(schedEntry));
}



static int
cmd_scheduler_info(scli_interp_t *interp, int argc, char **argv)
{
    disman_schedule_mib_schedEntry_t **schedTable = NULL;
    int name_width = 5, owner_width = 5;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_schedule_mib_get_schedTable(interp->peer, &schedTable)) {
	return SCLI_ERROR;
    }

    if (schedTable) {
	for (i = 0; schedTable[i]; i++) {
	    if (schedTable[i]->_schedOwnerLength > owner_width) {
		owner_width = schedTable[i]->_schedOwnerLength;
	    }
	    if (schedTable[i]->_schedNameLength > name_width) {
		name_width = schedTable[i]->_schedNameLength;
	    }
	}
	g_string_sprintfa(interp->header,
			  "STATE %-*s %-*s TYPE     EXPRESSION",
			  owner_width, "OWNER", name_width, "NAME");
	for (i = 0; schedTable[i]; i++) {
	    show_scheduler_info(interp->result, schedTable[i],
				name_width, owner_width);
	}
    }

    if (schedTable) disman_schedule_mib_free_schedTable(schedTable);
	
    return SCLI_OK;
}



static void
show_scheduler_details(GString *s,
		       disman_schedule_mib_schedEntry_t *schedEntry)
{
    int const width = 20;
    int i;
    
    g_string_append(s, "AdminStatus: ");
    fmt_enum(s, width, disman_schedule_mib_enums_schedAdminStatus,
	     schedEntry->schedAdminStatus);
    g_string_append(s, "Owner:    ");
    g_string_sprintfa(s, "%.*s\n",
		      (int) schedEntry->_schedOwnerLength,
		      schedEntry->schedOwner);

    g_string_append(s, "OperStatus:  ");
    fmt_enum(s, width, disman_schedule_mib_enums_schedOperStatus,
	     schedEntry->schedOperStatus);
    g_string_append(s, "Name:     ");
    g_string_sprintfa(s, "%*s\n",
		      (int) schedEntry->_schedNameLength,
		      schedEntry->schedName);

    g_string_append(s, "RowStatus:   ");
    fmt_enum(s, width, disman_schedule_mib_enums_schedRowStatus,
	     schedEntry->schedRowStatus);
    g_string_append(s, "Type:     ");
    fmt_enum(s, 1, disman_schedule_mib_enums_schedType,
	     schedEntry->schedType);
    g_string_append(s, "\n");
    
    g_string_append(s, "Storage:     ");
    fmt_enum(s, width, disman_schedule_mib_enums_schedStorageType,
	     schedEntry->schedStorageType);
    g_string_append(s, "Value:    ");
    if (schedEntry->schedValue) {
	g_string_sprintfa(s, "%d", *schedEntry->schedValue);
    }
    g_string_append(s, "\n");
    
    g_string_append(s, "Last Error:  ");
    fmt_enum(s, width, disman_schedule_mib_enums_schedLastFailure,
	     schedEntry->schedLastFailure);
    g_string_append(s, "Error:    ");
    if (schedEntry->schedLastFailed) {
	g_string_append(s, fmt_date_and_time(schedEntry->schedLastFailed,
				     schedEntry->_schedLastFailedLength));
    }
    g_string_append(s, "\n");
    
    if (schedEntry->schedContextName && schedEntry->_schedContextNameLength) {
	g_string_sprintfa(s, "Context:     <%.*s>\n",
			  (int) schedEntry->_schedContextNameLength,
			  schedEntry->schedContextName);
    }
    
    if (schedEntry->schedVariable) {
	g_string_sprintfa(s, "Variable:    ");
	for (i = 0; i < schedEntry->_schedVariableLength; i++) {
	    g_string_sprintfa(s, "%s%u", i ? "." : "",
			      schedEntry->schedVariable[i]);
	}
	g_string_append(s, "\n");
    }
    
    g_string_sprintfa(s, "Expression:  %s\n",
		      fmt_expression(schedEntry));
        
    if (schedEntry->schedDescr) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) schedEntry->_schedDescrLength,
			  schedEntry->schedDescr);
    }
}


    
static int
cmd_scheduler_details(scli_interp_t *interp, int argc, char **argv)
{
    disman_schedule_mib_schedEntry_t **schedTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX;
    }

    if (disman_schedule_mib_get_schedTable(interp->peer, &schedTable)) {
	return SCLI_ERROR;
    }

    if (schedTable) {
	for (i = 0; schedTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    show_scheduler_details(interp->result, schedTable[i]);
	}
    }

    if (schedTable) disman_schedule_mib_free_schedTable(schedTable);
	
    return SCLI_OK;
}



void
scli_init_disman_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show disman languages", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "languages supported by the distributed manager",
	  cmd_languages },
	{ "show disman script info", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "script summary information",
	  cmd_script_info },
	{ "show disman script details", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "scripts installed at the distributed manager",
	  cmd_script_details },
	{ "show disman launch info", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "launch summary information",
	  cmd_launch_info },
	{ "show disman launch details", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "launch buttons installed on the distributed manager",
	  cmd_launch_details },
	{ "show disman run info", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "summary information about running scripts",
	  cmd_run_info },
	{ "show disman run details", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "running scripts on the distributed manager",
	  cmd_run_details },
	{ "show disman scheduler info", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "scheduler information",
	  cmd_scheduler_info },
	{ "show disman scheduler details", NULL,
	  SCLI_CMD_FLAG_NEED_PEER,
	  "schedules on the distributed manager",
	  cmd_scheduler_details },
	{ "monitor disman run", NULL,
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  "running scripts",
	  cmd_run_info },
	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t disman_mode = {
	"disman",
	"scli mode to display and configure distributed managers",
	cmds
    };
    
    scli_register_mode(interp, &disman_mode);
}
