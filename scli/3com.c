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
#include "productmib-proc.h"
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



static int
create_3com_bridge_vlan(scli_interp_t *interp, int argc, char **argv)
{
    gint32 vlanId;
    char *end;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 3) {
	return SCLI_SYNTAX_NUMARGS;
    }

    vlanId = strtol(argv[1], &end, 0);
    if (*end) {
	return SCLI_SYNTAX_NUMBER;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    productmib_proc_create_vlan(interp->peer, vlanId, argv[2],
				PRODUCTMIB_A3COMVLANIFTYPE_VLANLAYER2);
    if (interp->peer->error_status) {
	return SCLI_ERROR;
    }

    return SCLI_OK;
}



static int
delete_3com_bridge_vlan(scli_interp_t *interp, int argc, char **argv)
{
    productmib_a3ComVlanIfEntry_t **vlanTable = NULL;
    regex_t _regex_vlan, *regex_vlan = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    regex_vlan = &_regex_vlan;
    if (regcomp(regex_vlan, argv[1], interp->regex_flags) != 0) {
	return SCLI_SYNTAX_REGEXP;
    }

    if (scli_interp_dry(interp)) {
	regfree(regex_vlan);
	return SCLI_OK;
    }

    productmib_get_a3ComVlanIfTable(interp->peer, &vlanTable,
				    PRODUCTMIB_A3COMVLANIFDESCR);
    if (interp->peer->error_status) {
	regfree(regex_vlan);
	return SCLI_SNMP;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (match_vlan(regex_vlan, vlanTable[i])) {
#if 0
		rapid_city_proc_delete_vlan(interp->peer,
					    vlanTable[i]->a3ComVlanIfIndex);
		if (interp->peer->error_status) {
		    vlan_snmp_error(interp, vlanTable[i]);
		}
#endif
	    }
	}
    }

    if (vlanTable) productmib_free_a3ComVlanIfTable(vlanTable);
    regfree(regex_vlan);
    
    return SCLI_OK;
}



static int
dump_3com_bridge_vlan(scli_interp_t *interp, int argc, char **argv)
{
#if 0
    rapid_city_rcVlanEntry_t **vlanTable = NULL;
    int i;
    const int mask = (RAPID_CITY_RCVLANNAME
		      | RAPID_CITY_RCVLANTYPE
		      | RAPID_CITY_RCVLANPORTMEMBERS);
    
    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    rapid_city_get_rcVlanTable(interp->peer, &vlanTable, mask);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (vlanTable) {
	for (i = 0; vlanTable[i]; i++) {
	    if (! vlanTable[i]->rcVlanName) {
		continue;
	    }
	    g_string_sprintfa(interp->result,
			      "create 3com bridge vlan \"%u\" \"%.*s\"\n",
			      vlanTable[i]->rcVlanId,
			      (int) vlanTable[i]->_rcVlanNameLength,
			      vlanTable[i]->rcVlanName);
	}
	g_string_append(interp->result, "\n");
	for (i = 0; vlanTable[i]; i++) {
	    if (! vlanTable[i]->rcVlanName) {
		continue;
	    }
	    if (vlanTable[i]->rcVlanPortMembers) {
		g_string_sprintfa(interp->result,
				  "set 3com bridge vlan ports \"%.*s\" \"",
				  (int) vlanTable[i]->_rcVlanNameLength,
				  vlanTable[i]->rcVlanName);
		fmt_port_set(interp->result, vlanTable[i]->rcVlanPortMembers, 32);
		g_string_sprintfa(interp->result, "\"\n");
	    }
	}
    }

    if (vlanTable) rapid_city_free_rcVlanTable(vlanTable);
#endif
    return SCLI_OK;
}



void
scli_init_3com_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "create 3com bridge vlan", "<vlanid> <name>",
	  "The `create 3com bridge vlan' command is used to create a\n"
	  "new virtual LAN with the given <vlanid> and <name>.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  create_3com_bridge_vlan },
	 
	{ "delete 3com bridge vlan", "<regexp>",
	  "The `delete 3com bridge vlan' command deletes all selected\n"
	  "virtual LANs. The regular expression <regexp> is matched\n"
	  "against the virtual LAN names to select the vlans that should\n"
	  "be deleted.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  delete_3com_bridge_vlan },

	{ "show 3com bridge vlan info", "[<regexp>]",
	  "The `show 3com bridge vlan info' command shows summary\n"
	  "information about all selected virtual LANs. The optional\n"
	  "regular expression <regexp> is matched against the virtual\n"
	  "LAN names to select the virtual LANs of interest. The\n"
	  "command generates a table with the following columns:\n"
	  "\n"
	  "  VLAN   virtual LAN number\n"
	  "  STATUS status of the virutal LAN (see below)\n"
	  "  NAME   name of the virutal LAN\n"
	  "  PORTS  ports assigned to the virtual LAN\n"
	  "\n"
	  "The status is encoded in two characters. The first character\n"
	  "indicates the status of the row (A=active, S=not in service,\n"
	  "R=not ready). The second character indicates virutal LAN type\n"
	  "(P=port, I=IP-subnet, O=protocol, S=src address, D=dst address)."
	  "",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_3com_bridge_vlan_info },
	 
	{ "dump 3com bridge vlan", NULL,
	  "The `dump 3com bridge vlan' command generates a sequence of scli\n"
	  "commands which can be used to restore the virtual LAN configuration.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  dump_3com_bridge_vlan },
	
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
