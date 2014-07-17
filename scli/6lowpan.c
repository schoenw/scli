/* 
 * 6lowpan.c -- scli 6lowpan mode implementation
 *
 * Copyright (C) 2013 Juergen Schoenwaelder
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
#include "jacobs-lowpan-mib.h"

#define JACOBS_LOWPAN_MIB_IN_NOMESH_STATS \
    ( JACOBS_LOWPAN_MIB_LOWPANREASMTIMEOUT || \
      JACOBS_LOWPAN_MIB_LOWPANINRECEIVES || \
      JACOBS_LOWPAN_MIB_LOWPANINHDRERRORS || \
      JACOBS_LOWPAN_MIB_LOWPANINREASMREQDS || \
      JACOBS_LOWPAN_MIB_LOWPANINREASMFAILS || \
      JACOBS_LOWPAN_MIB_LOWPANINREASMOKS || \
      JACOBS_LOWPAN_MIB_LOWPANINCOMPREQDS || \
      JACOBS_LOWPAN_MIB_LOWPANINCOMPFAILS || \
      JACOBS_LOWPAN_MIB_LOWPANINCOMPOKS || \
      JACOBS_LOWPAN_MIB_LOWPANINDISCARDS || \
      JACOBS_LOWPAN_MIB_LOWPANINDELIVERS )

#define JACOBS_LOWPAN_MIB_IN_MESH_STATS \
    ( JACOBS_LOWPAN_MIB_LOWPANINMESHRECEIVES || \
      JACOBS_LOWPAN_MIB_LOWPANINMESHFORWDS || \
      JACOBS_LOWPAN_MIB_LOWPANINMESHDELIVERS )

#define JACOBS_LOWPAN_MIB_IN_STATS \
    ( JACOBS_LOWPAN_MIB_IN_NOMESH_STATS || JACOBS_LOWPAN_MIB_IN_MESH_STATS)

#define JACOBS_LOWPAN_MIB_OUT_NOMESH_STATS \
    ( JACOBS_LOWPAN_MIB_LOWPANOUTREQUESTS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTCOMPREQDS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTCOMPFAILS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTCOMPOKS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGREQDS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGFAILS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGOKS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTFRAGCREATES || \
      JACOBS_LOWPAN_MIB_LOWPANOUTDISCARDS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTTRANSMITS )

#define JACOBS_LOWPAN_MIB_OUT_MESH_STATS \
    ( JACOBS_LOWPAN_MIB_LOWPANOUTMESHHOPLIMITEXCEEDS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHNOROUTES || \
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHREQUESTS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHFORWDS || \
      JACOBS_LOWPAN_MIB_LOWPANOUTMESHTRANSMITS )

#define JACOBS_LOWPAN_MIB_OUT_STATS \
    ( JACOBS_LOWPAN_MIB_OUT_NOMESH_STATS || JACOBS_LOWPAN_MIB_OUT_MESH_STATS )

#define JACOBS_LOWPAN_MIB_NOMESH_STATS \
    ( JACOBS_LOWPAN_MIB_OUT_NOMESH_STATS || JACOBS_LOWPAN_MIB_IN_NOMESH_STATS )

static void
fmt_6lowpan_stats(GString *s,
		  jacobs_lowpan_mib_lowpanStats_t *lowpanObjects)
{
    if (lowpanObjects) {
	/* fmt_counter_dt */
    }
}


static int
show_6lowpan_stats(scli_interp_t *interp, int argc, char **argv)
{
    int i;
    jacobs_lowpan_mib_lowpanStats_t *lowpanObjects = NULL;
    GError *error = NULL;
    
    g_return_val_if_fail(interp, SCLI_ERROR);
    
    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }
    
    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    jacobs_lowpan_mib_get_lowpanStats(interp->peer, &lowpanObjects,
				      JACOBS_LOWPAN_MIB_LOWPANINRECEIVES, NULL);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    jacobs_lowpan_mib_get_lowpanStats(interp->peer, &lowpanObjects,
				      JACOBS_LOWPAN_MIB_NOMESH_STATS, NULL);
    if (scli_interp_set_error_snmp(interp, &error)) {
	return SCLI_SNMP;
    }
    
    if (lowpanObjects) {
	fmt_6lowpan_stats(interp->result, lowpanObjects);
    }

    if (lowpanObjects) jacobs_lowpan_mib_free_lowpanStats(lowpanObjects);
    
    return SCLI_OK;
}



void
scli_init_6lowpan_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show 6lowpan stats", NULL,
	  "The `show 6lowpan stats' command displays statistics\n"
	  "of the 6LoWPAN layer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_6lowpan_stats },
	
	{ "monitor 6lowpan stats", NULL,
	  "The `monitor 6lowpan stats' command shows the same\n"
	  "information as the show 6lowpan stats command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_6lowpan_stats },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
	
    static scli_mode_t lowpan_mode = {
	"6lowpan",
	"The scli 6lowpan mode is used to display 6lowpan parameters\n"
	"and statistics.",
	cmds
    };
    
    scli_register_mode(interp, &lowpan_mode);
}
