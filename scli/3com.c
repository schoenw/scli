/* 
 * 3com.c -- scli 3com mode implementation
 *
 * Copyright (C) 2002 Juergen Schoenwaelder
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

#include "scli.h"

#include "productmib.h"
#include "if-mib.h"


static void
fmt_vlanStatus(GString *s, productmib_a3ComVlanIfEntry_t *vlanEntry)
{
    static GSnmpEnum const a3ComVlanIfStatus[] = {
	{ PRODUCTMIB_A3COMVLANIFSTATUS_ACTIVE,		"A" },
	{ PRODUCTMIB_A3COMVLANIFSTATUS_NOTINSERVICE,	"S" },
	{ PRODUCTMIB_A3COMVLANIFSTATUS_NOTREADY,	"R" },
	{ 0, NULL }
    };
    
    const char *e;
    
    e = fmt_enum(a3ComVlanIfStatus, vlanEntry->a3ComVlanIfStatus);
    g_string_sprintfa(s, "%s   ", e ? e : "-");
}



static int
match_vlan(regex_t *regex_vlan,
	   productmib_a3ComVlanIfEntry_t *vlanEntry)
{
    int status;
    
    if (! regex_vlan) {
	return 1;
    }

    if (vlanEntry->a3ComVlanIfDescr) {
	char *string = g_malloc0(vlanEntry->_a3ComVlanIfDescrLength + 1);
	memcpy(string, vlanEntry->a3ComVlanIfDescr, vlanEntry->_a3ComVlanIfDescrLength);
	status = regexec(regex_vlan, string, (size_t) 0, NULL, 0);
	g_free(string);
	if (status == 0) {
	    return 1;
	}
    }

    return 0;
}



static int
get_vlan_name_width(productmib_a3ComVlanIfEntry_t **vlanTable)
{
    int i, name_width = 6;
    
    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (vlanTable[i]->_a3ComVlanIfDescrLength > name_width) {
		name_width = vlanTable[i]->_a3ComVlanIfDescrLength;
	    }
	}
    }
    return name_width;
}



static void
fmt_3com_bridge_vlan_info(GString *s,
			  productmib_a3ComVlanIfEntry_t *vlanEntry,
			  guchar *bits, gsize bits_len,
			  int name_width)
{
    g_string_sprintfa(s, "%4d  ",
		      vlanEntry->a3ComVlanIfGlobalIdentifier
		      ? *vlanEntry->a3ComVlanIfGlobalIdentifier : 0);

    fmt_vlanStatus(s, vlanEntry);
    
    if (vlanEntry->a3ComVlanIfDescr && vlanEntry->_a3ComVlanIfDescrLength) {
	g_string_sprintfa(s, "  %-*.*s ", name_width,
			  (int) vlanEntry->_a3ComVlanIfDescrLength,
			  vlanEntry->a3ComVlanIfDescr);
    } else {
	g_string_sprintfa(s, "  %*s ", name_width, "");
    }

    fmt_port_set(s, bits, bits_len);

    g_string_append(s, "\n");
}



static void
create_port_list(guchar *bits, gsize bits_len, int ifIndex,
		 if_mib_ifStackEntry_t **ifStackTable,
		 if_mib_ifEntry_t **ifTable)
{
    int i;

    for (i = 0; ifStackTable[i]; i++) {
	if (ifStackTable[i]->ifStackHigherLayer == ifIndex) {
	    int l = ifStackTable[i]->ifStackLowerLayer;

	    // ignore everything which is not a real physical interface
	    
	    if (l < bits_len * 8) {
		bits[l/8] |= (1 <<(7-(l%8)));
	    }
	}
    }
}



static int
show_3com_bridge_vlan_info(scli_interp_t *interp, int argc, char **argv)
{
    productmib_a3ComVlanIfEntry_t **vlanTable = NULL;
    if_mib_ifStackEntry_t **ifStackTable = NULL;
    if_mib_ifEntry_t **ifTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i, name_width;
    guchar ports[256];
    const int mask = (PRODUCTMIB_A3COMVLANIFDESCR
		      | PRODUCTMIB_A3COMVLANIFTYPE
		      | PRODUCTMIB_A3COMVLANIFGLOBALIDENTIFIER
		      | PRODUCTMIB_A3COMVLANIFSTATUS);

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (argc == 2) {
	regex_vlan = &_regex_vlan;
	if (regcomp(regex_vlan, argv[1], interp->regex_flags) != 0) {
	    return SCLI_SYNTAX_REGEXP;
	}
    }

    if (scli_interp_dry(interp)) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_OK;
    }

    productmib_get_a3ComVlanIfTable(interp->peer, &vlanTable, mask);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if_mib_get_ifStackTable(interp->peer, &ifStackTable, 0);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if_mib_get_ifTable(interp->peer, &ifTable, IF_MIB_IFTYPE);
    if (interp->peer->error_status) {
	if (regex_vlan) regfree(regex_vlan);
	return SCLI_SNMP;
    }

    name_width = get_vlan_name_width(vlanTable);

    memset(ports, 0, sizeof(ports));

    if (vlanTable) {
	g_string_sprintfa(interp->header,
			  "VLAN STATUS %-*s PORTS", name_width, "NAME");
	for (i = 0; vlanTable[i]; i++) {
	    if (! match_vlan(regex_vlan, vlanTable[i])) continue;
	    create_port_list(ports, sizeof(ports),
			     vlanTable[i]->a3ComVlanIfIndex,
			     ifStackTable, ifTable);
	    fmt_3com_bridge_vlan_info(interp->result, vlanTable[i],
				      ports, sizeof(ports), name_width);
	}
    }

    if (vlanTable) productmib_free_a3ComVlanIfTable(vlanTable);
    if (regex_vlan) regfree(regex_vlan);
    
    return SCLI_OK;
}



void
scli_init_3com_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "show 3com bridge vlan info", "[<regexp>]",
	  "",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_3com_bridge_vlan_info },
	 
	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };
    
    static scli_mode_t _3com_mode = {
	"3com",
	"The 3com scli mode allows to manipulate virtual lans (vlans)\n"
	"on 3com bridges. It is based on the PRODUCTMIB which is\n"
	"implemented at least on 3Com SuperStack II switches.",
	cmds
    };

    scli_register_mode(interp, &_3com_mode);
}
