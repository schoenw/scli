/* 
 * rpl.c -- scli rpl mode implementation
 *
 * Copyright (C) 2011 Juergen Schoenwaelder
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
 * @(#) $Id: rpl.c 3180 2009-07-29 22:36:13Z schoenw $
 */

#include "scli.h"

#include "snmpv2-tc.h"
#include "ip-mib.h"
#include "if-mib.h"
#include "jacobs-rpl-mib.h"


static void
fmt_rpl_info(GString *s, jacobs_rpl_mib_rplActive_t *rplActive)
{
    if (rplActive->rplActiveInstance) {
	g_string_sprintfa(s, "Active Instance: %u\n",
			  *rplActive->rplActiveInstance);
    }

    if (rplActive->rplActiveDodag) {
	g_string_sprintfa(s, "Active Dodag: %s\n",
			  fmt_ipv6_address(rplActive->rplActiveDodag,
					   SCLI_FMT_ADDR));
    }

    if (rplActive->rplActiveDodagTriggerSequence) {
	g_string_sprintfa(s, "Trigger Sequence: %u\n",
			  *rplActive->rplActiveDodagTriggerSequence);
    }
}


static int
show_rpl_info(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_rpl_mib_rplActive_t *rplActive = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplActive(interp->peer, &rplActive, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplActive) {
	fmt_rpl_info(interp->result, rplActive);
    }

    if (rplActive) jacobs_rpl_mib_free_rplActive(rplActive);
    
    return SCLI_OK;
}



static void
fmt_rpl_instance(GString *s, jacobs_rpl_mib_rplInstanceEntry_t *rplInstanceEntry)
{
    const char *label;

    g_string_sprintfa(s, "Instance: %d\n",
		      rplInstanceEntry->rplInstanceID);

    label = fmt_enum(jacobs_rpl_mib_enums_RplDISMode,
		     rplInstanceEntry->rplInstanceDISMode);
    g_string_sprintfa(s, "DIS Mode: %s\n", label);
    
    if (rplInstanceEntry->rplInstanceDISMessages) {
	g_string_sprintfa(s, "DIS Messages: %d\n",
			  *rplInstanceEntry->rplInstanceDISMessages);
    }
		  
    if (rplInstanceEntry->rplInstanceDISTimeout) {
	g_string_sprintfa(s, "DIS Timeout: %d seconds\n",
			  *rplInstanceEntry->rplInstanceDISTimeout);
    }

    label = fmt_enum(jacobs_rpl_mib_enums_RplModeOfOperation,
		     rplInstanceEntry->rplInstanceModeOfOperation);
    g_string_sprintfa(s, "Mode of Operation: %s\n", label);
    return;
}



static int
show_rpl_instances(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_rpl_mib_rplInstanceEntry_t **rplInstanceTable = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplInstanceTable(interp->peer, &rplInstanceTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplInstanceTable) {
	for (i = 0; rplInstanceTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_rpl_instance(interp->result, rplInstanceTable[i]);
	}
    }
    
    if (rplInstanceTable) jacobs_rpl_mib_free_rplInstanceTable(rplInstanceTable);
    
    return SCLI_OK;
}



static void
fmt_rpl_dodag(GString *s, jacobs_rpl_mib_rplDodagEntry_t *rplDodagEntry)
{
    const char *label;

    g_string_sprintfa(s, "Instance: %d\n",
		      rplDodagEntry->rplInstanceID);
    g_string_sprintfa(s, "Dodag: %d\n",
		      rplDodagEntry->rplDodagIndex);
    g_string_sprintfa(s, "DodagID: %s\n",
		      fmt_ipv6_address(rplDodagEntry->rplDodagID,
                                       SCLI_FMT_ADDR));
    if (rplDodagEntry->rplDodagVersion) {
	g_string_sprintfa(s, "Version: %u\n",
			  *rplDodagEntry->rplDodagVersion);
    }
    if (rplDodagEntry->rplDodagRank) {
	g_string_sprintfa(s, "Rank: %u\n",
			  *rplDodagEntry->rplDodagRank);
    }
    label = fmt_enum(jacobs_rpl_mib_enums_rplDodagState,
		     rplDodagEntry->rplDodagState);
    g_string_sprintfa(s, "State: %s\n", label);
    if (rplDodagEntry->rplDodagDAODelay) {
	g_string_sprintfa(s, "DAO Delay: %u milliseconds\n",
			  *rplDodagEntry->rplDodagDAODelay);
    }
    if (rplDodagEntry->rplDodagPreference) {
	g_string_sprintfa(s, "Preference: %u\n",
			  *rplDodagEntry->rplDodagPreference);
    }
    if (rplDodagEntry->rplDodagMinHopRankIncrease) {
	g_string_sprintfa(s, "MinHopIncrease: %u\n",
			  *rplDodagEntry->rplDodagMinHopRankIncrease);
    }
    if (rplDodagEntry->rplDodagPathControlSize) {
	g_string_sprintfa(s, "PathControlSize: %u\n",
			  *rplDodagEntry->rplDodagPathControlSize);
    }
    
    return;
}



static int
show_rpl_dodags(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_rpl_mib_rplDodagEntry_t **rplDodagTable = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplDodagTable(interp->peer, &rplDodagTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplDodagTable) {
	for (i = 0; rplDodagTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_rpl_dodag(interp->result, rplDodagTable[i]);
	}
    }
    
    if (rplDodagTable) jacobs_rpl_mib_free_rplDodagTable(rplDodagTable);
    
    return SCLI_OK;
}



static void
fmt_rpl_parent(GString *s, jacobs_rpl_mib_rplDodagParentEntry_t *rplParentEntry)
{
    g_string_sprintfa(s, "Instance: %d\n",
		      rplParentEntry->rplInstanceID);
    g_string_sprintfa(s, "Dodag: %d\n",
		      rplParentEntry->rplDodagIndex);
    g_string_sprintfa(s, "Parent: %s\n",
		      fmt_ipv6_address(rplParentEntry->rplDodagParentID,
                                       SCLI_FMT_ADDR));
    if (rplParentEntry->rplDodagParentIf) {
	g_string_sprintfa(s, "Interface: %d\n",
			  *rplParentEntry->rplDodagParentIf);
    }
}



static int
show_rpl_parents(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_rpl_mib_rplDodagParentEntry_t **rplParentTable = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplDodagParentTable(interp->peer, &rplParentTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplParentTable) {
	for (i = 0; rplParentTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_rpl_parent(interp->result, rplParentTable[i]);
	}
    }
    
    if (rplParentTable) jacobs_rpl_mib_free_rplDodagParentTable(rplParentTable);
    
    return SCLI_OK;
}



static void
fmt_rpl_child(GString *s, jacobs_rpl_mib_rplDodagChildEntry_t *rplChildEntry)
{
    g_string_sprintfa(s, "Instance: %d\n",
		      rplChildEntry->rplInstanceID);
    g_string_sprintfa(s, "Dodag: %d\n",
		      rplChildEntry->rplDodagIndex);
    g_string_sprintfa(s, "Child: %s\n",
		      fmt_ipv6_address(rplChildEntry->rplDodagChildID,
                                       SCLI_FMT_ADDR));
}



static int
show_rpl_childs(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_rpl_mib_rplDodagChildEntry_t **rplChildTable = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplDodagChildTable(interp->peer, &rplChildTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplChildTable) {
	for (i = 0; rplChildTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_rpl_child(interp->result, rplChildTable[i]);
	}
    }
    
    if (rplChildTable) jacobs_rpl_mib_free_rplDodagChildTable(rplChildTable);
    
    return SCLI_OK;
}



static void
fmt_rpl_stats(GString *s, jacobs_rpl_mib_rplStats_t *rplStats)
{
    const char *label;

    if (rplStats->rplMemOverflows) {
	g_string_sprintfa(s, "Memory Overflows: %u\n",
			  *rplStats->rplMemOverflows);
    }

    if (rplStats->rplParseErrors) {
	g_string_sprintfa(s, "Parse Errors: %u\n",
			  *rplStats->rplParseErrors);
    }

    if (rplStats->rplUnknownMsgTypes) {
	g_string_sprintfa(s, "Unknown Message Types: %u\n",
			  *rplStats->rplUnknownMsgTypes);
    }
}



static int
show_rpl_stats(scli_interp_t *interp, int argc, char **argv)
{
    jacobs_rpl_mib_rplStats_t *rplStats = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplStats(interp->peer, &rplStats, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplStats) {
	fmt_rpl_stats(interp->result, rplStats);
    }
    
    if (rplStats) jacobs_rpl_mib_free_rplStats(rplStats);
    
    return SCLI_OK;
}


static void
fmt_rpl_msg_stats(GString *s,
		  jacobs_rpl_mib_rplMsgStatsEntry_t *rplMsgStatsEntry)
{
    g_string_sprintfa(s, "Message type %3d:",
		      rplMsgStatsEntry->rplMsgStatsType);
    if (rplMsgStatsEntry->rplMsgStatsInMsgs) {
	g_string_sprintfa(s, "%8d", *rplMsgStatsEntry->rplMsgStatsInMsgs);
    } else {
	g_string_sprintfa(s, "  ----  ");
    }
    g_string_sprintfa(s, " in, ");
    if (rplMsgStatsEntry->rplMsgStatsOutMsgs) {
	g_string_sprintfa(s, "%8d", *rplMsgStatsEntry->rplMsgStatsOutMsgs);
    } else {
	g_string_sprintfa(s, "  ----  ");
    }
    g_string_sprintfa(s, " out\n");
}



static int
show_rpl_msg_stats(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_rpl_mib_rplMsgStatsEntry_t **rplMsgStatsTable = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_rpl_mib_get_rplMsgStatsTable(interp->peer, &rplMsgStatsTable, 0, &error);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (rplMsgStatsTable) {
	for (i = 0; rplMsgStatsTable[i]; i++) {
	    if (i) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_rpl_msg_stats(interp->result, rplMsgStatsTable[i]);
	}
    }
    
    if (rplMsgStatsTable) jacobs_rpl_mib_free_rplMsgStatsTable(rplMsgStatsTable);
    
    return SCLI_OK;
}



void
scli_init_rpl_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show rpl info", NULL,
	  "",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_info },

	{ "show rpl instances", NULL,
	  "The `show rpl instances' command displays information about\n"
	  "RPL instances known by the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_instances },

	{ "show rpl dodags", NULL,
	  "The `show rpl dodags' command displays information about\n"
	  "RPL dodags known by the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_dodags },

	{ "show rpl parents", NULL,
	  "The `show rpl parents' command displays information about\n"
	  "parents of RPL dodags known by the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_parents },
	
	{ "show rpl childs", NULL,
	  "The `show rpl childs' command displays information about\n"
	  "children of RPL dodags known by the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_childs },
	
	{ "show rpl stats", NULL,
	  "The `show rpl stats' command displays statistics about\n"
	  "the RPL implementation of the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_stats },
	
	{ "show rpl msg stats", NULL,
	  "The `show rpl msg stats' command displays statistics about\n"
	  "messages handled by the RPL implementation of the system.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_rpl_msg_stats },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
	
    static scli_mode_t rpl_mode = {
	"rpl",
	"The scli rpl mode is used to display and configure RPL\n"
	"parameters.",
	cmds
    };
    
    scli_register_mode(interp, &rpl_mode);
}
