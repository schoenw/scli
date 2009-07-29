/* 
 * hp.c -- scli hp mode implementation
 *
 * Copyright (C) 2006 Juergen Schoenwaelder
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
 * @(#) $Id: cisco.c 1632 2005-06-28 09:45:21Z strauss $
 */

#include "scli.h"

#include "snmpv2-mib.h"

#include "snmpv2-mib.h"
#include "hp-icf-fault-finder-mib.h"

static void
fmt_hp_fault_finder_log_entry(GString *s,
			      snmpv2_mib_system_t *system,
			      hp_icf_fault_finder_mib_hpicfFfLogEntry_t *logEntry)
{
    char const *e;
    
    g_string_sprintfa(s, "%d", logEntry->hpicfFfLogIndex);

    if (logEntry->hpicfFfLogCreateTime && system && system->sysUpTime) {
	guint32 dsecs = *(system->sysUpTime)
	    - *(logEntry->hpicfFfLogCreateTime);
	g_string_sprintfa(s, " %s", fmt_timeticks(dsecs));
    } else {
	g_string_sprintfa(s, " %5s", "-");
    }

    if (logEntry->hpicfFfLogPhysEntity) {
	g_string_sprintfa(s, " %5d", *logEntry->hpicfFfLogPhysEntity);
    } else {
	g_string_sprintfa(s, " %5s", "-");
    }

    e = fmt_enum(hp_icf_fault_finder_mib_enums_HpicfFaultType,
		 logEntry->hpicfFfLogFaultType);
    g_string_sprintfa(s, " %s", e ? e : "");
    
    e = fmt_enum(hp_icf_fault_finder_mib_enums_HpicfFaultAction,
		 logEntry->hpicfFfLogAction);
    g_string_sprintfa(s, " %s", e ? e : "");
    
    e = fmt_enum(hp_icf_fault_finder_mib_enums_hpicfFfLogSeverity,
		 logEntry->hpicfFfLogSeverity);
    g_string_sprintfa(s, " %s", e ? e : "");
    
    e = fmt_enum(hp_icf_fault_finder_mib_enums_hpicfFfLogStatus,
		 logEntry->hpicfFfLogStatus);
    g_string_sprintfa(s, " %s", e ? e : "");
    
    g_string_append(s, "\n");
}



static int
show_hp_fault_finder_log(scli_interp_t *interp, int argc, char **argv)
{
    snmpv2_mib_system_t *system = NULL;
    hp_icf_fault_finder_mib_hpicfFfLogEntry_t **logTable = NULL;
    int i, j, n;
    GError *error = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    hp_icf_fault_finder_mib_get_hpicfFfLogTable(interp->peer,
						&logTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }

    if (logTable) {
	snmpv2_mib_get_system(interp->peer, &system, SNMPV2_MIB_SYSUPTIME, NULL);
#if 0
	g_string_sprintfa(interp->header,
			  "SOURCE           DESTINATION       "
			  " PKTS > BYTS   PKTS < BYTS   TPKTS  TBYTS");
#endif
	for (i = 0; logTable[i]; i++) {
	    fmt_hp_fault_finder_log_entry(interp->result, system, logTable[i]);
	}
    }

    if (logTable)
	hp_icf_fault_finder_mib_free_hpicfFfLogTable(logTable);

    return SCLI_OK;
}



void
scli_init_hp_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	
	{ "show hp fault log", NULL,
	  "XXX",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_hp_fault_finder_log },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t hp_mode = {
	"hp",
	"The hp scli mode is used to display and configure hp\n"
	"parameters.",
	cmds
    };

    scli_register_mode(interp, &hp_mode);
}
