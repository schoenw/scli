/* 
 * bridge.c -- scli bridge mode implementation
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

#include "bridge-mib.h"
#include "if-mib.h"


static void
show_bridge_info(GString *s, dot1dBase_t *dot1dBase, dot1dTp_t *dot1dTp,
		 dot1dStp_t *dot1dStp)
{
    int const indent = 18;

    if (dot1dBase->dot1dBaseNumPorts) {
	g_string_sprintfa(s, "%-*s %d\n", indent, "Ports:",
			  *(dot1dBase->dot1dBaseNumPorts));
	if (dot1dBase->dot1dBaseType) {
	    g_string_sprintfa(s, "%-*s ", indent, "Type:");
	    fmt_enum(s, 1, bridge_mib_enums_dot1dBaseType,
		     dot1dBase->dot1dBaseType);
	    g_string_append(s, "\n");
	    if (dot1dBase->dot1dBaseType
		&& (*dot1dBase->dot1dBaseType == 2
		    || *dot1dBase->dot1dBaseType == 4)
		&& dot1dTp
		&& dot1dTp->dot1dTpAgingTime) {
		g_string_sprintfa(s, "%-*s %d sec\n", indent, "Aging Time:",
				  *dot1dTp->dot1dTpAgingTime);
	    }
	    if (dot1dStp && dot1dStp->dot1dStpMaxAge) {
		g_string_sprintfa(s, "%-*s %d sec\n", indent, "Aging Time:",
				  *dot1dStp->dot1dStpMaxAge);
	    }
	}
    }
}



static int
cmd_bridge_info(scli_interp_t *interp, int argc, char **argv)
{
    dot1dBase_t *dot1dBase = NULL;
    dot1dTp_t *dot1dTp = NULL;
    dot1dStp_t *dot1dStp = NULL;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (bridge_mib_get_dot1dBase(interp->peer, &dot1dBase)) {
	return SCLI_ERROR;
    }
    (void) bridge_mib_get_dot1dTp(interp->peer, &dot1dTp);
    (void) bridge_mib_get_dot1dStp(interp->peer, &dot1dStp);
    
    if (dot1dBase
	&& dot1dBase->dot1dBaseNumPorts
	&& *dot1dBase->dot1dBaseNumPorts) {
	show_bridge_info(interp->result, dot1dBase, dot1dTp, dot1dStp);
    }

    if (dot1dBase)
	bridge_mib_free_dot1dBase(dot1dBase);
    if (dot1dTp)
	bridge_mib_free_dot1dTp(dot1dTp);
    if (dot1dStp)
	bridge_mib_free_dot1dStp(dot1dStp);
    
    return SCLI_OK;
}



static void
show_bridge_port(GString *s, dot1dBasePortEntry_t *dot1dBasePortEntry,
	  ifEntry_t *ifEntry, ifXEntry_t *ifXEntry)
{
    g_string_sprintfa(s, "%5u ", dot1dBasePortEntry->dot1dBasePort);
    if (dot1dBasePortEntry->dot1dBasePortIfIndex) {
	g_string_sprintfa(s, "%7u   ",
			  *dot1dBasePortEntry->dot1dBasePortIfIndex);
    } else {
	g_string_sprintfa(s, "%7s   ", "");
    }
    if (ifEntry) {
	fmt_enum(s, 20, if_mib_enums_ifType, ifEntry->ifType);
    }
    g_string_append(s, "\n");
}



static int
cmd_bridge_ports(scli_interp_t *interp, int argc, char **argv)
{
    dot1dBasePortEntry_t **dot1dBasePortTable = NULL;
    ifEntry_t **ifTable = NULL;
    ifXEntry_t **ifXTable = NULL;
    int i, j = -1;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (bridge_mib_get_dot1dBasePortTable(interp->peer, &dot1dBasePortTable)) {
	return SCLI_ERROR;
    }

    (void) if_mib_get_ifTable(interp->peer, &ifTable);
    (void) if_mib_get_ifXTable(interp->peer, &ifXTable);
    
    if (dot1dBasePortTable) {
	g_string_append(interp->result, " Port Interface Type\n");
	for (i = 0; dot1dBasePortTable[i]; i++) {
	    if (ifTable && dot1dBasePortTable[i]->dot1dBasePortIfIndex) {
		for (j = 0; ifTable[j]; j++) {
		    if (ifTable[j]->ifIndex ==
			*dot1dBasePortTable[i]->dot1dBasePortIfIndex) {
			break;
		    }
		}
	    }
	    show_bridge_port(interp->result, dot1dBasePortTable[i],
			     (ifTable && ifTable[j]) ? ifTable[j] : NULL,
			     (ifXTable && ifXTable[j]) ? ifXTable[j] : NULL);
	}
    }

    if (dot1dBasePortTable)
	bridge_mib_free_dot1dBasePortTable(dot1dBasePortTable);
    if (ifTable) if_mib_free_ifTable(ifTable);
    if (ifXTable) if_mib_free_ifXTable(ifXTable);

    return SCLI_OK;
}



static void
show_bridge_forwarding(GString *s, dot1dTpFdbEntry_t *dot1dTpFdbEntry)
{
    scli_vendor_t *vendor;
    guint32 prefix;
    int i;

    if (dot1dTpFdbEntry->dot1dTpFdbPort) {
	g_string_sprintfa(s, "%5u ", *dot1dTpFdbEntry->dot1dTpFdbPort);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }
    fmt_enum(s, 8, bridge_mib_enums_dot1dTpFdbStatus,
	     dot1dTpFdbEntry->dot1dTpFdbStatus);
    g_string_append(s, " ");
    if (dot1dTpFdbEntry->dot1dTpFdbAddress) {
	prefix = dot1dTpFdbEntry->dot1dTpFdbAddress[0] * 65536
	    + dot1dTpFdbEntry->dot1dTpFdbAddress[1] * 256
	    + dot1dTpFdbEntry->dot1dTpFdbAddress[2];
	for (i = 0; i < 6; i++) {
	    g_string_sprintfa(s, "%s%02x", i ? ":" : "",
			      dot1dTpFdbEntry->dot1dTpFdbAddress[i]);
	}
	vendor = scli_get_ieee_vendor(prefix);
	if (vendor && vendor->name) {
	    g_string_sprintfa(s, " %s", vendor->name);
	}
    }
    g_string_append(s, "\n");
}



static int
cmd_bridge_forwarding(scli_interp_t *interp, int argc, char **argv)
{
    dot1dTpFdbEntry_t **dot1dTpFdbTable = NULL;
    int i, p, max = 0;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (bridge_mib_get_dot1dTpFdbTable(interp->peer, &dot1dTpFdbTable)) {
	return SCLI_ERROR;
    }

    if (dot1dTpFdbTable) {
	for (i = 0; dot1dTpFdbTable[i]; i++) {
	    if (dot1dTpFdbTable[i]->dot1dTpFdbPort
		&& *dot1dTpFdbTable[i]->dot1dTpFdbPort > max) {
		max = *dot1dTpFdbTable[i]->dot1dTpFdbPort;
	    }
	};
	g_string_append(interp->result,
			" Port Status   Address           Vendor\n");
	for (p = 0; p < max+1; p++) {
	    for (i = 0; dot1dTpFdbTable[i]; i++) {
		if (dot1dTpFdbTable[i]->dot1dTpFdbPort
		    && *dot1dTpFdbTable[i]->dot1dTpFdbPort == p) {
		    show_bridge_forwarding(interp->result, dot1dTpFdbTable[i]);
		}
	    }
	}
    }

    if (dot1dTpFdbTable) bridge_mib_free_dot1dTpFdbTable(dot1dTpFdbTable);

    return SCLI_OK;
}



static void
show_bridge_filter(GString *s, dot1dStaticEntry_t *dot1dStaticEntry)
{
    int i;
    
    if (dot1dStaticEntry->dot1dStaticReceivePort) {
	g_string_sprintfa(s, "%5d ",
			  dot1dStaticEntry->dot1dStaticReceivePort);
    } else {
	g_string_sprintfa(s, "%5s ", "");
    }

    if (dot1dStaticEntry->dot1dStaticAddress) {
	for (i = 0; i < 6; i++) {
	    g_string_sprintfa(s, "%s%02x", i ? ":" : "",
			      dot1dStaticEntry->dot1dStaticAddress[i]);
	}
    } else {
	g_string_sprintfa(s, "--:--:--:--:--:--");
    }

    if (dot1dStaticEntry->dot1dStaticAllowedToGoTo) {
	/* xxx */
    }

    g_string_append(s, " ");
    fmt_enum(s, 15, bridge_mib_enums_dot1dStaticStatus,
	     dot1dStaticEntry->dot1dStaticStatus);
 
    g_string_append(s, "\n");
}



static int
cmd_bridge_filter(scli_interp_t *interp, int argc, char **argv)
{
    dot1dStaticEntry_t **dot1dStaticTable = NULL;
    int i;
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (bridge_mib_get_dot1dStaticTable(interp->peer, &dot1dStaticTable)) {
	return SCLI_ERROR;
    }

    if (dot1dStaticTable) {
	for (i = 0; dot1dStaticTable[i]; i++) {
	    show_bridge_filter(interp->result, dot1dStaticTable[i]);
	}
    }

    if (dot1dStaticTable)
	bridge_mib_free_dot1dStaticTable(dot1dStaticTable);

    return SCLI_OK;
}



void
scli_init_bridge_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {
	{ "show", "bridge", 0, NULL, NULL },
	{ "show bridge", "info", SCLI_CMD_FLAG_NEED_PEER,
	  "show bridge information",
	  cmd_bridge_info },
	{ "show bridge", "ports", SCLI_CMD_FLAG_NEED_PEER,
	  "show bridge ports",
	  cmd_bridge_ports },
	{ "show bridge", "forwarding", SCLI_CMD_FLAG_NEED_PEER,
	  "show bridge forwarding data base",
	  cmd_bridge_forwarding },
	{ "show bridge", "filter", SCLI_CMD_FLAG_NEED_PEER,
	  "show bridge filtering data base",
	  cmd_bridge_filter },
	{ NULL, NULL, 0, NULL, NULL }
    };
    
    static scli_mode_t bridge_mode = {
	"bridge",
	"scli mode to display and configure bridge parameters",
	cmds,
	NULL,
	NULL
    };
    
    scli_register_mode(interp, &bridge_mode);
}
