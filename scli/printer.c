/* 
 * printer.c -- scli printer mode implementation
 *
 * Copyright (C) 2001-2002 Oliver Wellnitz, Juergen Schoenwaelder
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

#include "host-resources-mib.h"
#include "host-resources-types.h"
#include "printer-mib.h"


static GSnmpEnum const prtAlertGroup[] = {
    { PRINTER_MIB_PRTALERTGROUP_OTHER,	"other" },
    { PRINTER_MIB_PRTALERTGROUP_HOSTRESOURCESMIBSTORAGETABLE,	"storage" },
    { PRINTER_MIB_PRTALERTGROUP_HOSTRESOURCESMIBDEVICETABLE,	"device" },
    { PRINTER_MIB_PRTALERTGROUP_GENERALPRINTER,	"general" },
    { PRINTER_MIB_PRTALERTGROUP_COVER,	"cover" },
    { PRINTER_MIB_PRTALERTGROUP_LOCALIZATION,	"localization" },
    { PRINTER_MIB_PRTALERTGROUP_INPUT,	"input" },
    { PRINTER_MIB_PRTALERTGROUP_OUTPUT,	"output" },
    { PRINTER_MIB_PRTALERTGROUP_MARKER,	"marker" },
    { PRINTER_MIB_PRTALERTGROUP_MARKERSUPPLIES,	"marker supply" },
    { PRINTER_MIB_PRTALERTGROUP_MARKERCOLORANT,	"marker colorant" },
    { PRINTER_MIB_PRTALERTGROUP_MEDIAPATH,	"media path" },
    { PRINTER_MIB_PRTALERTGROUP_CHANNEL,	"channel" },
    { PRINTER_MIB_PRTALERTGROUP_INTERPRETER,	"interpreter" },
    { PRINTER_MIB_PRTALERTGROUP_CONSOLEDISPLAYBUFFER,	"console display buffer" },
    { PRINTER_MIB_PRTALERTGROUP_CONSOLELIGHTS,	"console light" },
    { PRINTER_MIB_PRTALERTGROUP_ALERT,	"alert" },
    { PRINTER_MIB_PRTALERTGROUP_FINDEVICE,	"finishing device" },
    { PRINTER_MIB_PRTALERTGROUP_FINSUPPLY,	"finishing supply" },
    { PRINTER_MIB_PRTALERTGROUP_FINSUPPLYMEDIAINPUT,	"finishing supply media input" },
    { PRINTER_MIB_PRTALERTGROUP_FINATTRIBUTETABLE,	"finishing attribute table" },
    { 0, NULL }
};



static const char *error_states[] = {
    "low paper", "no paper", "low toner", "no toner", "door open",
    "jammed", "offline", "service requested", "input tray missing",
    "output tray missing", "marker supply missing", "output near full",
    "output full", "input tray empty", "overdue prevent maint", NULL
};



typedef struct {
    const int x;
    const int y;
    const char *unit;
    const char *name;
} media_names_t;

static media_names_t media_names[] = {
    {  841, 1189, "mm", "iso-a0" },
    {  594,  841, "mm", "iso-a1" },
    {  420,  594, "mm", "iso-a2" },
    {  297,  420, "mm", "iso-a3" },
    {  210,  297, "mm", "iso-a4" },
    {  148,  210, "mm", "iso-a5" },
    {  105,  148, "mm", "iso-a6" },
    {   74,  105, "mm", "iso-a7" },
    {   52,   74, "mm", "iso-a8" },
    {   37,   52, "mm", "iso-a9" },
    {   26,   37, "mm", "iso-a10" },

    { 1000, 1414, "mm", "iso-b0" },
    {  707, 1000, "mm", "iso-b1" },
    {  500,  707, "mm", "iso-b2" },
    {  353,  500, "mm", "iso-b3" },
    {  250,  353, "mm", "iso-b4" },
    {  176,  250, "mm", "iso-b5" },
    {  125,  176, "mm", "iso-b6" },
    {   88,  125, "mm", "iso-b7" },
    {   62,   88, "mm", "iso-b8" },
    {   44,   62, "mm", "iso-b9" },
    {   31,   44, "mm", "iso-b10" },
    {  917, 1297, "mm", "iso-c0" },
    {  648,  917, "mm", "iso-c1" },
    {  458,  648, "mm", "iso-c2" },
    {  324,  458, "mm", "iso-c3" },
    {  229,  324, "mm", "iso-c4" },
    {  162,  229, "mm", "iso-c5" },
    {  114,  162, "mm", "iso-c6" },
    {   81,  114, "mm", "iso-c7" },
    {   57,   81, "mm", "iso-c8" },
    {  110,  220, "mm", "iso-designated" },
    
    { 1030, 1456, "mm", "jis-b0" },
    {  728, 1030, "mm", "jis-b1" },
    {  515,  728, "mm", "jis-b2" },
    {  364,  515, "mm", "jis-b3" },
    {  257,  364, "mm", "jis-b4" },
    {  182,  257, "mm", "jis-b5" },
    {  128,  182, "mm", "jis-b6" },
    {   91,  128, "mm", "jis-b7" },
    {   64,   91, "mm", "jis-b8" },
    {   45,   64, "mm", "jis-b9" },
    {   32,   45, "mm", "jis-b10" },

    { 0, 0, NULL, NULL }
};


/*
 * Lookup a human friendly paper name.
 */

static const char *
lookup_media_name(gint32 dir, gint32 xdir, gint32 unit)
{
    gint32 x, y;
    char *s = NULL;
    int i;
  
#define TENTHOUSANDTHSOFINCHES 3
#define MICROMETERS 4

    x = (dir < xdir) ?  dir : xdir;
    y = (dir < xdir) ? xdir : dir;
    
    switch (unit) {
    case TENTHOUSANDTHSOFINCHES:
	s = "in";
	x /= 10000;
	y /= 10000;
	break;
    case MICROMETERS:
	s = "mm";
	x /= 1000;
	y /= 1000;
	break;
    }

    if (s) {
	for (i = 0; media_names[i].name; i++) {
	    if (x == media_names[i].x
		&& y == media_names[i].y
		&& strcmp(s, media_names[i].unit) == 0) {
		break;
	    }
	}
	if (media_names[i].name) {
	    return media_names[i].name;
	}
    }

    return NULL;
}



static char const *
fmt_bits(const char **labels, guchar *bits, gsize bits_len)
{
    int i, bit;
    int cnt = 0;
    
    if (! bits) {
	return NULL;
    }
    
    for (i = 0; labels[i]; i++) {
	bit = (i/8 < bits_len) ? bits[i/8] & 1 <<(7-(i%8)) : 0;
	if (bit) cnt++;
    }
    if (cnt == i) {
	return NULL;
    }

    return labels[i];
}
    


static const char *
fmt_subunit_availability(gint32 *status)
{
    static const char *labels[] = {
	"available and idle", "unavailable on request",
	"available and standby", "unavailable and broken",
	"available and active", "unknown", "available and busy"
    };

    const char *a = "-";
    
    if (! status) {
	return NULL;
    }

    if ((*status & 0x0f) < sizeof(labels)/sizeof(char *)) {
	a = labels[*status & 0x0f];
    }
    return a;
}



static const char *
fmt_subunit_alerts(gint32 *status)
{
    char *a;
    
    if (! status) {
	return NULL;
    }

    if ((*status & 8) && (*status & 16)) {
	a = "critical and non-critical";
    } else if (*status & 16) {
	a = "critical";
    } else if (*status & 8) {
	a = "non-critical";
    } else {
	a = "none";
    }
    return a;
}



static const char *
fmt_subunit_status(gint32 *status)
{
    static const char *labels[] = {
	"online", "offline",
	"online and transitioning", "offline and transitioning",
    };

    const char *a = "-";
    
    if (! status) {
	return NULL;
    }

    if (((*status >> 5) & 0x03) < sizeof(labels)/sizeof(char *)) {
	a = labels[(*status >> 5) & 0x03];
    }
    return a;
}



static void
fmt_subunit(GString *s, int indent, gint32 *status)
{
    if (! status) {
	return;
    }

    g_string_sprintfa(s, "%-*s %s\n", indent, "Availability:",
		      fmt_subunit_availability(status));
    g_string_sprintfa(s, "%-*s %s\n", indent, "Alerts:",
		      fmt_subunit_alerts(status));
    g_string_sprintfa(s, "%-*s %s\n", indent, "Status:",
		      fmt_subunit_status(status));
}



static void
xml_subunit(xmlNodePtr tree, gint32 *status)
{
    if (! status) {
	return;
    }

    xml_new_child(tree, NULL, "availability", "%s",
		  fmt_subunit_availability(status));
    xml_new_child(tree, NULL, "alerts", "%s",
		  fmt_subunit_alerts(status));
    xml_new_child(tree, NULL, "status", "%s",
		  fmt_subunit_status(status));
}



static const char *
fmt_dimensions(gint32 *dim)
{
    static char s[256];

    if (! dim) {
	return NULL;
    }

    if (*dim == -1) {
	return "other";
    } else if (*dim == -2) {
	return "unknown";
    } else if (*dim < 0) {
	return "-";
    }

    g_snprintf(s, sizeof(s), "%d", *dim);
    return s;
}



static void
fmt_media_dimensions(GString *s, gint indent, gchar *label,
		     gint32 *dir, gint32 *xdir,
		     gint32 *unit, const GSnmpEnum *enums)
{
    const char *e;
    const char *name;
    
    if (! dir || ! xdir || ! unit) {
	return;
    }

    name = lookup_media_name(*dir, *xdir, *unit);
    if (name) {
	g_string_sprintfa(s, "%-*s %s\n", indent, label, name);
    } else {
	e = fmt_enum(enums, unit);
	
	g_string_sprintfa(s, "%-*s %s", indent, label,
			  fmt_dimensions(dir));
	g_string_sprintfa(s, " x %s ",
			  fmt_dimensions(xdir));
	g_string_sprintfa(s, "%s\n", e ? e : "");
    }
}



static void
xml_media_dimensions(xmlNodePtr tree, gchar *label,
		     gint32 *dir, gint32 *xdir,
		     gint32 *unit, const GSnmpEnum *enums)
{
    const char *e;
    xmlNodePtr node;
    
    if (! dir || ! xdir || ! unit) {
	return;
    }

    node = xmlNewChild(tree, NULL, label,
		       lookup_media_name(*dir, *xdir, *unit));
    xml_set_prop(node, "direction", "%d", *dir);
    xml_set_prop(node, "cross-direction", "%d", *xdir);
    e = fmt_enum(enums, unit);
    if (e) xml_set_prop(node, "unit", "%s", e);
}



static xmlNodePtr
get_printer_node(xmlNodePtr tree, gint32 printer, const char *xpath)
{
    xmlNodePtr node;
    char buffer[20];

    g_snprintf(buffer, sizeof(buffer), "%d", printer);

    for (node = tree->children; node; node = node->next) {
	if (xmlStrcmp(node->name, (const xmlChar *) "printer") == 0) {
	    xmlChar *prop = xmlGetProp(node, (const xmlChar *) "device");
	    if (xmlStrcmp(prop, (const xmlChar *) buffer) == 0) {
		break;
	    }
	}
    }
    if (! node) {
	node = xmlNewChild(tree, NULL, "printer", NULL);
	xml_set_prop(node, "device", "%s", buffer);
    }

    /*
     * XXX We should treat this really like a path...
     */
    
    if (xpath) {
	xmlNodePtr child;
	for (child = node->children; child; child = child->next) {
            if (xmlStrcmp(child->name, (const xmlChar *) xpath) == 0) {
		break;
	    }
	}
	if (! child) {
	    child = xmlNewChild(node, NULL, xpath, NULL);
	}
	node = child;
    }
    
    return node;
}



static host_resources_mib_hrDeviceEntry_t*
get_device_entry(host_resources_mib_hrPrinterEntry_t *hrPrinterEntry,
		 host_resources_mib_hrDeviceEntry_t **hrDeviceTable)
{
    int i;

    if (hrDeviceTable) {
	for (i = 0; hrDeviceTable[i]; i++) {
	    if (hrDeviceTable[i]->hrDeviceIndex
		== hrPrinterEntry->hrDeviceIndex) {
		return hrDeviceTable[i];
	    }
	}
    }

    return NULL;
}



static printer_mib_prtGeneralEntry_t*
get_general_entry(host_resources_mib_hrPrinterEntry_t *hrPrinterEntry,
		  printer_mib_prtGeneralEntry_t **prtGeneralTable)
{
    int i;

    if (prtGeneralTable) {
	for (i = 0; prtGeneralTable[i]; i++) {
	    if (prtGeneralTable[i]->hrDeviceIndex
		== hrPrinterEntry->hrDeviceIndex) {
		return prtGeneralTable[i];
	    }
	}
    }

    return NULL;
}



static printer_mib_prtLocalizationEntry_t *
get_console_local_entry(printer_mib_prtGeneralEntry_t *prtGeneralEntry,
			printer_mib_prtLocalizationEntry_t **prtLocalTable)
{
    int i;
    
    if (prtGeneralEntry->prtConsoleLocalization && prtLocalTable) {
	for (i = 0; prtLocalTable[i]; i++) {
	    if ((prtLocalTable[i]->hrDeviceIndex
		 == prtGeneralEntry->hrDeviceIndex)
		&& (prtLocalTable[i]->prtLocalizationIndex
		    == *prtGeneralEntry->prtConsoleLocalization)) {
		return prtLocalTable[i];
	    }
	}
    }
    
    return NULL;
}



static void
fmt_printer_info(GString *s,
		 host_resources_mib_hrPrinterEntry_t *hrPrinterEntry,
		 host_resources_mib_hrDeviceEntry_t *hrDeviceEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Device:",
		      hrPrinterEntry->hrDeviceIndex);

    if (hrDeviceEntry && hrDeviceEntry->hrDeviceDescr) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Description:", 
			  (int) hrDeviceEntry->_hrDeviceDescrLength,
			  hrDeviceEntry->hrDeviceDescr);
    }

    if (hrDeviceEntry) {
	e = fmt_identity(host_resources_types_identities,
			 hrDeviceEntry->hrDeviceType,
			 hrDeviceEntry->_hrDeviceDescrLength);
	if (e) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Type:", e);
	}
    }
	
    if (hrDeviceEntry) {
	e = fmt_enum(host_resources_mib_enums_hrDeviceStatus,
		     hrDeviceEntry->hrDeviceStatus);
	if (e) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Device Status:", e);
	}
    }

    e = fmt_enum(host_resources_mib_enums_hrPrinterStatus,
		 hrPrinterEntry->hrPrinterStatus);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Printer Status:", e);
    }

    if (hrPrinterEntry->hrPrinterDetectedErrorState) {
	/* XXX fmt_bits() just does non-sense here */
	e = fmt_bits(error_states,
		     hrPrinterEntry->hrPrinterDetectedErrorState,
		     hrPrinterEntry->_hrPrinterDetectedErrorStateLength);
	if (e) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Error State:", e);
	}
    }
}



static void
xml_printer_info(xmlNodePtr root,
		 host_resources_mib_hrPrinterEntry_t *hrPrinterEntry,
		 host_resources_mib_hrDeviceEntry_t *hrDeviceEntry)
{
    xmlNodePtr tree;
    const char *e;

    tree = xmlNewChild(root, NULL, "cover", NULL);

    if (hrDeviceEntry) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			  (int) hrDeviceEntry->_hrDeviceDescrLength,
			  hrDeviceEntry->hrDeviceDescr);
    }

    if (hrDeviceEntry) {
	e = fmt_identity(host_resources_types_identities,
			 hrDeviceEntry->hrDeviceType,
			 hrDeviceEntry->_hrDeviceDescrLength);
	if (e) {
	    (void) xml_new_child(tree, NULL, "type", "%s", e);
	}
    }
	
    if (hrDeviceEntry) {
	e = fmt_enum(host_resources_mib_enums_hrDeviceStatus,
		     hrDeviceEntry->hrDeviceStatus);
	if (e) {
	    (void) xml_new_child(tree, NULL, "device-status", "%s", e);
	}
    }

    e = fmt_enum(host_resources_mib_enums_hrPrinterStatus,
		 hrPrinterEntry->hrPrinterStatus);
    if (e) {
	(void) xml_new_child(tree, NULL, "printer-status", "%s", e);
    }

    /* XXX fmt_bits() just does non-sense here */
    e = fmt_bits(error_states,
		 hrPrinterEntry->hrPrinterDetectedErrorState,
		 hrPrinterEntry->_hrPrinterDetectedErrorStateLength);
    if (e) {
	(void) xml_new_child(tree, NULL, "error-states", "%s", e);
    }
}



static void
fmt_printer_general(GString *s,
		     printer_mib_prtGeneralEntry_t *prtGeneralEntry,
		     printer_mib_prtLocalizationEntry_t **prtLocalTable)
{
    int const indent = 18;
    const char *e;

    /* MISSING: prtGeneralCurrentLocalization */
    /* MISSING: prtAuxiliarySheetStartupPage */
    /* MISSING: prtAuxiliarySheetBannerPage */
    /* MISSING: prtGeneralReset */
    
    if (prtGeneralEntry->prtGeneralPrinterName) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent,
			  "Printer Name:",
		    (int) prtGeneralEntry->_prtGeneralPrinterNameLength,
			  prtGeneralEntry->prtGeneralPrinterName);
    }

    if (prtGeneralEntry->prtGeneralSerialNumber) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent,
			  "Serial Number:",
		    (int) prtGeneralEntry->_prtGeneralSerialNumberLength,
			  prtGeneralEntry->prtGeneralSerialNumber);
    }
    
    if (prtGeneralEntry->prtGeneralCurrentOperator) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent,
			  "Current Operator:",
		    (int) prtGeneralEntry->_prtGeneralCurrentOperatorLength,
			  prtGeneralEntry->prtGeneralCurrentOperator);
    }
    
    if (prtGeneralEntry->prtGeneralServicePerson) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent,
			  "Service Person",
		    (int) prtGeneralEntry->_prtGeneralServicePersonLength,
			  prtGeneralEntry->prtGeneralServicePerson);
    }
    
    if (prtGeneralEntry->prtConsoleNumberOfDisplayLines &&
	prtGeneralEntry->prtConsoleNumberOfDisplayChars) {
	g_string_sprintfa(s, "%-*s %u line(s) a %u chars\n", indent,
			  "Console Display:",
			  *prtGeneralEntry->prtConsoleNumberOfDisplayLines,
			  *prtGeneralEntry->prtConsoleNumberOfDisplayChars);
    }

    if (prtGeneralEntry->prtConsoleLocalization && prtLocalTable) {
	printer_mib_prtLocalizationEntry_t *prtLocalEntry;
	prtLocalEntry = get_console_local_entry(prtGeneralEntry,
						prtLocalTable);
	if (prtLocalEntry) {
	    g_string_sprintfa(s, "%-*s %.*s/%.*s\n", indent,
			      "Console Language:",
		        (int) prtLocalEntry->_prtLocalizationLanguageLength,
			      prtLocalEntry->prtLocalizationLanguage,
		        (int) prtLocalEntry->_prtLocalizationCountryLength,
			      prtLocalEntry->prtLocalizationCountry);
	}
    }
    
    e = fmt_enum(printer_mib_enums_prtConsoleDisable,
		 prtGeneralEntry->prtConsoleDisable);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Console Access:", e);
    }
    
    if (prtGeneralEntry->prtInputDefaultIndex
	&& *prtGeneralEntry->prtInputDefaultIndex > 0) {
	g_string_sprintfa(s, "%-*s input #%d\n", indent, "Default Input:",
			  *prtGeneralEntry->prtInputDefaultIndex);
    }

    if (prtGeneralEntry->prtOutputDefaultIndex
	&& *prtGeneralEntry->prtOutputDefaultIndex > 0) {
	g_string_sprintfa(s, "%-*s output #%d\n", indent, "Default Output:",
			  *prtGeneralEntry->prtOutputDefaultIndex);
    }
    
    if (prtGeneralEntry->prtMarkerDefaultIndex) {
	g_string_sprintfa(s, "%-*s marker #%u\n", indent, "Default Marker:",
			  *prtGeneralEntry->prtMarkerDefaultIndex);
    }
    
    if (prtGeneralEntry->prtMediaPathDefaultIndex) {
	g_string_sprintfa(s, "%-*s media path #%u\n", indent, "Default Path:",
			  *prtGeneralEntry->prtMediaPathDefaultIndex);
    }
    
    if (prtGeneralEntry->prtAlertAllEvents) {
	g_string_sprintfa(s, "%-*s %u\n", indent, "Total Alerts:",
			  *prtGeneralEntry->prtAlertAllEvents);
    }
    
    if (prtGeneralEntry->prtAlertCriticalEvents) {
	g_string_sprintfa(s, "%-*s %u\n", indent, "Critical Alerts:",
			  *prtGeneralEntry->prtAlertCriticalEvents);
    }
    
    if (prtGeneralEntry->prtGeneralConfigChanges) {
	g_string_sprintfa(s, "%-*s %u\n", indent, "Config Changes:",
			  *prtGeneralEntry->prtGeneralConfigChanges);
    }
}



static int
show_printer_info(scli_interp_t *interp, int argc, char **argv)
{
    host_resources_mib_hrPrinterEntry_t **hrPrinterTable = NULL;
    host_resources_mib_hrDeviceEntry_t **hrDeviceTable = NULL;
    printer_mib_prtGeneralEntry_t **prtGeneralTable = NULL;
    printer_mib_prtLocalizationEntry_t **prtLocalTable = NULL;
    gint32 last = 0;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    host_resources_mib_get_hrPrinterTable(interp->peer, &hrPrinterTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (hrPrinterTable) {
	host_resources_mib_get_hrDeviceTable(interp->peer, &hrDeviceTable, 0);
	printer_mib_get_prtGeneralTable(interp->peer, &prtGeneralTable, 0);
	printer_mib_get_prtLocalizationTable(interp->peer, &prtLocalTable, 0);
	for (i = 0; hrPrinterTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					   hrPrinterTable[i]->hrDeviceIndex,
						   "info");
		xml_printer_info(node, hrPrinterTable[i],
				 get_device_entry(hrPrinterTable[i],
						  hrDeviceTable));
	    } else {
		if (hrPrinterTable[i]->hrDeviceIndex != last) {
		    if (i > 0) {
			g_string_append(interp->result, "\n");
		    }
		}
		fmt_printer_info(interp->result, hrPrinterTable[i],
				 get_device_entry(hrPrinterTable[i],
						  hrDeviceTable));
		if (prtGeneralTable) {
		    fmt_printer_general(interp->result,
					get_general_entry(hrPrinterTable[i],
							  prtGeneralTable),
				    prtLocalTable);
		}
		last = hrPrinterTable[i]->hrDeviceIndex;
	    }
	}
    }

    if (hrPrinterTable)
	host_resources_mib_free_hrPrinterTable(hrPrinterTable);
    if (hrDeviceTable)
	host_resources_mib_free_hrDeviceTable(hrDeviceTable);
    if (prtGeneralTable)
	printer_mib_free_prtGeneralTable(prtGeneralTable);
    if (prtLocalTable)
	printer_mib_free_prtLocalizationTable(prtLocalTable);

    return SCLI_OK;
}



static void
fmt_printer_cover(GString *s, printer_mib_prtCoverEntry_t *prtCoverEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtCoverEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %u\n", indent, "Cover:",
		      prtCoverEntry->prtCoverIndex);

    if (prtCoverEntry->prtCoverDescription &&
	prtCoverEntry->_prtCoverDescriptionLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Description:",
			  (int) prtCoverEntry->_prtCoverDescriptionLength,
			  prtCoverEntry->prtCoverDescription);
    }

    e = fmt_enum(printer_mib_enums_prtCoverStatus,
		 prtCoverEntry->prtCoverStatus);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Status:", e);
    }
}



static void
xml_printer_cover(xmlNodePtr root,
		  printer_mib_prtCoverEntry_t *prtCoverEntry)
{
    xmlNodePtr tree;
    const char *e;
    
    tree = xmlNewChild(root, NULL, "cover", NULL);
    xml_set_prop(tree, "number", "%d",
		 prtCoverEntry->prtCoverIndex);

    if (prtCoverEntry->prtCoverDescription) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			  (int) prtCoverEntry->_prtCoverDescriptionLength,
			  prtCoverEntry->prtCoverDescription);
    }

    e = fmt_enum(printer_mib_enums_prtCoverStatus,
		 prtCoverEntry->prtCoverStatus);
    if (e) {
	(void) xml_new_child(tree, NULL, "status", "%s", e);
    }
}



static int
show_printer_covers(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtCoverEntry_t **prtCoverTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtCoverTable(interp->peer, &prtCoverTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtCoverTable) {
	for (i = 0; prtCoverTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					   prtCoverTable[i]->hrDeviceIndex,
						   "covers");
		xml_printer_cover(node, prtCoverTable[i]);
	    } else {
		fmt_printer_cover(interp->result, prtCoverTable[i]);
	    }
	}
    }

    if (prtCoverTable)
	printer_mib_free_prtCoverTable(prtCoverTable);

    return SCLI_OK;
}



static void
fmt_printer_path(GString *s, printer_mib_prtMediaPathEntry_t *prtPathEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtPathEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %u\n", indent, "Path:",
		      prtPathEntry->prtMediaPathIndex);

    if (prtPathEntry->prtMediaPathDescription &&
	prtPathEntry->_prtMediaPathDescriptionLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Description:",
			  (int) prtPathEntry->_prtMediaPathDescriptionLength,
			  prtPathEntry->prtMediaPathDescription);
    }

    e = fmt_enum(printer_mib_enums_prtMediaPathType,
		 prtPathEntry->prtMediaPathType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Type:", e);
    }

    fmt_subunit(s, indent, prtPathEntry->prtMediaPathStatus);

    e = fmt_enum(printer_mib_enums_prtMediaPathMaxSpeedPrintUnit,
		 prtPathEntry->prtMediaPathMaxSpeedPrintUnit);
    if (e && prtPathEntry->prtMediaPathMaxSpeed) {
	g_string_sprintfa(s, "%-*s %d %s\n", indent, "Max. Speed:",
			  *prtPathEntry->prtMediaPathMaxSpeed, e);
    }

    fmt_media_dimensions(s, indent, "Min. Dimension:",
			 prtPathEntry->prtMediaPathMinMediaFeedDir,
			 prtPathEntry->prtMediaPathMinMediaXFeedDir,
			 prtPathEntry->prtMediaPathMediaSizeUnit,
			 printer_mib_enums_prtMediaPathMediaSizeUnit);

    fmt_media_dimensions(s, indent, "Max. Dimension:",
			 prtPathEntry->prtMediaPathMaxMediaFeedDir,
			 prtPathEntry->prtMediaPathMaxMediaXFeedDir,
			 prtPathEntry->prtMediaPathMediaSizeUnit,
			 printer_mib_enums_prtMediaPathMediaSizeUnit);
}



static void
xml_printer_path(xmlNodePtr root,
		 printer_mib_prtMediaPathEntry_t *prtPathEntry)
{
    xmlNodePtr tree, node;
    const char *e;
    
    tree = xmlNewChild(root, NULL, "path", NULL);
    xml_set_prop(tree, "number", "%d",
		 prtPathEntry->prtMediaPathIndex);

    if (prtPathEntry->prtMediaPathDescription) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			  (int) prtPathEntry->_prtMediaPathDescriptionLength,
			  prtPathEntry->prtMediaPathDescription);
    }

    e = fmt_enum(printer_mib_enums_prtMediaPathType,
		 prtPathEntry->prtMediaPathType);
    if (e) {
	(void) xml_new_child(tree, NULL, "type", "%s", e);
    }

    xml_subunit(tree, prtPathEntry->prtMediaPathStatus);

    if (prtPathEntry->prtMediaPathMaxSpeed) {
	node = xml_new_child(tree, NULL, "max-speed", "%d",
			     *prtPathEntry->prtMediaPathMaxSpeed);
	e = fmt_enum(printer_mib_enums_prtMediaPathMaxSpeedPrintUnit,
		     prtPathEntry->prtMediaPathMaxSpeedPrintUnit);
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    xml_media_dimensions(tree, "min-dimension",
			 prtPathEntry->prtMediaPathMinMediaFeedDir,
			 prtPathEntry->prtMediaPathMinMediaXFeedDir,
			 prtPathEntry->prtMediaPathMediaSizeUnit,
			 printer_mib_enums_prtMediaPathMediaSizeUnit);

    xml_media_dimensions(tree, "max-dimensions",
			 prtPathEntry->prtMediaPathMaxMediaFeedDir,
			 prtPathEntry->prtMediaPathMaxMediaXFeedDir,
			 prtPathEntry->prtMediaPathMediaSizeUnit,
			 printer_mib_enums_prtMediaPathMediaSizeUnit);
}



static int
show_printer_paths(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtMediaPathEntry_t **prtPathTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtMediaPathTable(interp->peer, &prtPathTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtPathTable) {
	for (i = 0; prtPathTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					   prtPathTable[i]->hrDeviceIndex,
						   "paths");
		xml_printer_path(node, prtPathTable[i]);
	    } else {
		fmt_printer_path(interp->result, prtPathTable[i]);
	    }
	}
    }

    if (prtPathTable)
	printer_mib_free_prtMediaPathTable(prtPathTable);

    return SCLI_OK;
}



static void
fmt_printer_inputs(GString *s, printer_mib_prtInputEntry_t *prtInputEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtInputEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %u\n", indent, "Input:",
		      prtInputEntry->prtInputIndex);
    
    if (prtInputEntry->prtInputName &&
	prtInputEntry->_prtInputNameLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Name:",
			  (int) prtInputEntry->_prtInputNameLength,
			  prtInputEntry->prtInputName);
    }

    if (prtInputEntry->prtInputDescription &&
	prtInputEntry->_prtInputDescriptionLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Description:",
			  (int) prtInputEntry->_prtInputDescriptionLength,
			  prtInputEntry->prtInputDescription);
    }

    if (prtInputEntry->prtInputVendorName &&
	prtInputEntry->_prtInputVendorNameLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Vendor",
			  (int) prtInputEntry->_prtInputVendorNameLength,
			  prtInputEntry->prtInputVendorName);
    }
    
    e = fmt_enum(printer_mib_enums_prtInputType, prtInputEntry->prtInputType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Type:", e);
    }
    
    if (prtInputEntry->prtInputModel &&
	prtInputEntry->_prtInputModelLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Model:",
			  (int) prtInputEntry->_prtInputModelLength,
			  prtInputEntry->prtInputModel);
    }

    e = fmt_enum(printer_mib_enums_prtInputCapacityUnit,
		 prtInputEntry->prtInputCapacityUnit);
    if (prtInputEntry->prtInputMaxCapacity) {
	g_string_sprintfa(s, "%-*s ", indent, "Capacity:");
	switch (*prtInputEntry->prtInputMaxCapacity) {
	case -1:
	    g_string_append(s, "unlimited");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	default:
	    g_string_sprintfa(s, "%d",
			      *prtInputEntry->prtInputMaxCapacity);
	}
	g_string_sprintfa(s, " %s\n", e ? e : "");
    }

    if (prtInputEntry->prtInputCurrentLevel) {
	g_string_sprintfa(s, "%-*s ", indent, "Level:");
	switch (*prtInputEntry->prtInputCurrentLevel) {
	case -1:
	    g_string_append(s, "unlimited");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	case -3:
	    g_string_append(s, ">0");
	    break;
	default:
	    g_string_sprintfa(s, "%d", *prtInputEntry->prtInputCurrentLevel);
	}
	g_string_sprintfa(s, " %s\n", e ? e : "");
    }

    if (prtInputEntry->prtInputNextIndex) {
	g_string_append(s, "Next Input: ");
	switch (*prtInputEntry->prtInputNextIndex) {
	case 0:
	    g_string_append(s, "none");
	    break;
	case -1:
	    g_string_append(s, "other");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	case -3:
	    g_string_append(s, "no input switching");
	    break;
	default:
	    g_string_sprintfa(s, "input #%u",
			      *prtInputEntry->prtInputNextIndex);
	}
	g_string_append(s, "\n");
    }

    fmt_subunit(s, indent, prtInputEntry->prtInputStatus);
    
    if (prtInputEntry->prtInputSerialNumber &&
	prtInputEntry->_prtInputSerialNumberLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Serial Number:",
			  (int) prtInputEntry->_prtInputSerialNumberLength,
			  prtInputEntry->prtInputSerialNumber);
    }
    
    if (prtInputEntry->prtInputVersion &&
	prtInputEntry->_prtInputVersionLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Input Version:",
			  (int) prtInputEntry->_prtInputVersionLength,
			  prtInputEntry->prtInputVersion);
    }

    e = fmt_enum(printer_mib_enums_prtInputSecurity,
		 prtInputEntry->prtInputSecurity);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Security:", e);
    }

    if (prtInputEntry->prtInputMediaName &&
	prtInputEntry->_prtInputMediaNameLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Media Name:",
			  (int) prtInputEntry->_prtInputMediaNameLength,
			  prtInputEntry->prtInputMediaName);
    }
    
    if (prtInputEntry->prtInputMediaType &&
	prtInputEntry->_prtInputMediaTypeLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Media Type:",
			  (int) prtInputEntry->_prtInputMediaTypeLength,
			  prtInputEntry->prtInputMediaType);
    }
    
    if (prtInputEntry->prtInputMediaWeight) {
	g_string_sprintfa(s, "%-*s ", indent, "Media Weight:");
	switch (*prtInputEntry->prtInputMaxCapacity) {
	case -2:
	    g_string_append(s, "unknown");
	    break;
	default:
	    g_string_sprintfa(s,
			      "%u g/m^2",
			      *prtInputEntry->prtInputMediaWeight);
	}
	g_string_append(s, "\n");
    }
    
    if (prtInputEntry->prtInputMediaColor &&
	prtInputEntry->_prtInputMediaColorLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Media Color:",
			  (int) prtInputEntry->_prtInputMediaColorLength,
			  prtInputEntry->prtInputMediaColor);
    }
    
    if (prtInputEntry->prtInputMediaFormParts) {
	g_string_sprintfa(s, "%-*s ", indent, "Media Parts:");
	switch (*prtInputEntry->prtInputMediaFormParts) {
	case -1:
	    g_string_append(s, "other");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	default:
	    g_string_sprintfa(s, "%u",
			      *prtInputEntry->prtInputMediaFormParts);
	}
	g_string_append(s, "\n");
    }

    fmt_media_dimensions(s, indent, "Media Dimensions:",
			 prtInputEntry->prtInputMediaDimFeedDirDeclared,
			 prtInputEntry->prtInputMediaDimXFeedDirDeclared,
			 prtInputEntry->prtInputDimUnit,
			 printer_mib_enums_prtInputDimUnit);

    fmt_media_dimensions(s, indent, "Chosen Dimensions:",
			 prtInputEntry->prtInputMediaDimFeedDirChosen,
			 prtInputEntry->prtInputMediaDimXFeedDirChosen,
			 prtInputEntry->prtInputDimUnit,
			 printer_mib_enums_prtInputDimUnit);
    
    if (prtInputEntry->prtInputMediaLoadTimeout) {
	g_string_sprintfa(s, "%-*s ", indent, "Media Load Timeout:");
	switch (*prtInputEntry->prtInputMediaLoadTimeout) {
	case -1:
	    g_string_append(s, "wait forever");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	default:
	    g_string_sprintfa(s,
			      "%u secs",
			      *prtInputEntry->prtInputMediaLoadTimeout);
	}
	g_string_append(s, "\n");
    }
}



static void
xml_printer_inputs(xmlNodePtr root,
		   printer_mib_prtInputEntry_t *prtInputEntry)
{
    xmlNodePtr tree, node;
    const char *e;

    tree = xmlNewChild(root, NULL, "input", NULL);
    xml_set_prop(tree, "number", "%d",
		 prtInputEntry->prtInputIndex);

    if (prtInputEntry->prtInputName) {
	(void) xml_new_child(tree, NULL, "name", "%.*s",
			     (int) prtInputEntry->_prtInputNameLength,
			     prtInputEntry->prtInputName);
    }

    if (prtInputEntry->prtInputDescription) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			     (int) prtInputEntry->_prtInputDescriptionLength,
			     prtInputEntry->prtInputDescription);
    }

    if (prtInputEntry->prtInputVendorName) {
	(void) xml_new_child(tree, NULL, "vendor", "%.*s",
			     (int) prtInputEntry->_prtInputVendorNameLength,
			     prtInputEntry->prtInputVendorName);
    }
    
    e = fmt_enum(printer_mib_enums_prtInputType, prtInputEntry->prtInputType);
    if (e) {
	(void) xml_new_child(tree, NULL, "type", "%s", e);
    }

    if (prtInputEntry->prtInputModel) {
	(void) xml_new_child(tree, NULL, "model", "%.*s",
			     (int) prtInputEntry->_prtInputModelLength,
			     prtInputEntry->prtInputModel);
    }

    e = fmt_enum(printer_mib_enums_prtInputCapacityUnit,
		 prtInputEntry->prtInputCapacityUnit);
    if (prtInputEntry->prtInputMaxCapacity) {
	switch (*prtInputEntry->prtInputMaxCapacity) {
	case -1:
	    node = xml_new_child(tree, NULL, "capacity", "unlimited");
	    break;
	case -2:
	    node = xml_new_child(tree, NULL, "capacity", "unknown");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "capacity", "%d",
				 *prtInputEntry->prtInputMaxCapacity);
	}
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    if (prtInputEntry->prtInputCurrentLevel) {
	switch (*prtInputEntry->prtInputCurrentLevel) {
	case -1:
	    node = xml_new_child(tree, NULL, "level", "unlimited");
	    break;
	case -2:
	    node = xml_new_child(tree, NULL, "level", "unknown");
	    break;
	case -3:
	    node = xml_new_child(tree, NULL, "level", ">0");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "level", "%d",
				 *prtInputEntry->prtInputCurrentLevel);
	}
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    xml_subunit(tree, prtInputEntry->prtInputStatus);

    if (prtInputEntry->prtInputSerialNumber) {
	(void) xml_new_child(tree, NULL, "serial", "%.*s",
			     (int) prtInputEntry->_prtInputSerialNumberLength,
			     prtInputEntry->prtInputSerialNumber);
    }
    
    if (prtInputEntry->prtInputVersion) {
	(void) xml_new_child(tree, NULL, "version", "%.*s",
			     (int) prtInputEntry->_prtInputVersionLength,
			     prtInputEntry->prtInputVersion);
    }

    e = fmt_enum(printer_mib_enums_prtInputSecurity,
		 prtInputEntry->prtInputSecurity);
    if (e) {
	(void) xml_new_child(tree, NULL, "security", "%s", e);
    }

    /* ...media specific stuff begins here... */

    tree = xmlNewChild(tree, NULL, "media", NULL);
    
    if (prtInputEntry->prtInputMediaName) {
	(void) xml_new_child(tree, NULL, "name", "%.*s",
			     (int) prtInputEntry->_prtInputMediaNameLength,
			     prtInputEntry->prtInputMediaName);
    }
    
    if (prtInputEntry->prtInputMediaType) {
	(void) xml_new_child(tree, NULL, "type", "%.*s",
			     (int) prtInputEntry->_prtInputMediaTypeLength,
			     prtInputEntry->prtInputMediaType);
    }

    if (prtInputEntry->prtInputMediaWeight) {
	switch (*prtInputEntry->prtInputMaxCapacity) {
	case -2:
	    (void) xml_new_child(tree, NULL, "weight", "%s", "unknown");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "weight",
				 "%u", *prtInputEntry->prtInputMediaWeight);
	    xml_set_prop(node, "unit", "%s", "g/m^2");
	}
    }

    if (prtInputEntry->prtInputMediaColor) {
	(void) xml_new_child(tree, NULL, "color", "%.*s",
			     (int) prtInputEntry->_prtInputMediaColorLength,
			     prtInputEntry->prtInputMediaColor);
    }

    if (prtInputEntry->prtInputMediaFormParts) {
	switch (*prtInputEntry->prtInputMediaFormParts) {
	case -1:
	    (void) xml_new_child(tree, NULL, "parts", "%s", "other");
	    break;
	case -2:
	    (void) xml_new_child(tree, NULL, "parts", "%s", "unknown");
	    break;
	default:
	    (void) xml_new_child(tree, NULL, "parts",
				 "%u", *prtInputEntry->prtInputMediaFormParts);
	}
     }

    e = fmt_enum(printer_mib_enums_prtInputDimUnit,
		 prtInputEntry->prtInputDimUnit);

    xml_media_dimensions(tree, "dimensions",
			 prtInputEntry->prtInputMediaDimFeedDirDeclared,
			 prtInputEntry->prtInputMediaDimXFeedDirDeclared,
			 prtInputEntry->prtInputDimUnit,
			 printer_mib_enums_prtInputDimUnit);

    xml_media_dimensions(tree, "chosen",
			 prtInputEntry->prtInputMediaDimFeedDirChosen,
			 prtInputEntry->prtInputMediaDimXFeedDirChosen,
			 prtInputEntry->prtInputDimUnit,
			 printer_mib_enums_prtInputDimUnit);
    
    if (prtInputEntry->prtInputMediaLoadTimeout) {
	switch (*prtInputEntry->prtInputMediaLoadTimeout) {
	case -1:
	    (void) xml_new_child(tree, NULL, "load-timeout",
				 "%s", "wait forever");
	    break;
	case -2:
	    (void) xml_new_child(tree, NULL, "load-timeout",
				 "%s", "unknown");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "load-timeout",
			 "%u", *prtInputEntry->prtInputMediaLoadTimeout);
	    xml_set_prop(node, "unit", "%s", "seconds");
	}
    }
}



static int
show_printer_inputs(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtInputEntry_t **prtInputTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtInputTable(interp->peer, &prtInputTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtInputTable) {
	for (i = 0; prtInputTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					 prtInputTable[i]->hrDeviceIndex,
						   "inputs");
		xml_printer_inputs(node, prtInputTable[i]);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_inputs(interp->result, prtInputTable[i]);
	    }
	}
    }

    if (prtInputTable) printer_mib_free_prtInputTable(prtInputTable);
	
    return SCLI_OK;
}



static void
fmt_printer_outputs(GString *s, printer_mib_prtOutputEntry_t *prtOutputEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtOutputEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %u\n", indent, "Output:",
		      prtOutputEntry->prtOutputIndex);
    
    if (prtOutputEntry->prtOutputName &&
	prtOutputEntry->_prtOutputNameLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Name:",
			  (int) prtOutputEntry->_prtOutputNameLength,
			  prtOutputEntry->prtOutputName);
    }

    if (prtOutputEntry->prtOutputDescription &&
	prtOutputEntry->_prtOutputDescriptionLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Description:",
			  (int) prtOutputEntry->_prtOutputDescriptionLength,
			  prtOutputEntry->prtOutputDescription);
    }

    if (prtOutputEntry->prtOutputVendorName &&
	prtOutputEntry->_prtOutputVendorNameLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Vendor",
			  (int) prtOutputEntry->_prtOutputVendorNameLength,
			  prtOutputEntry->prtOutputVendorName);
    }
    
    e = fmt_enum(printer_mib_enums_prtOutputType,
		 prtOutputEntry->prtOutputType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Type:", e);
    }
    
    if (prtOutputEntry->prtOutputModel &&
	prtOutputEntry->_prtOutputModelLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Model:",
			  (int) prtOutputEntry->_prtOutputModelLength,
			  prtOutputEntry->prtOutputModel);
    }

    e = fmt_enum(printer_mib_enums_prtOutputCapacityUnit,
		 prtOutputEntry->prtOutputCapacityUnit);
    
    if (prtOutputEntry->prtOutputMaxCapacity) {
	g_string_sprintfa(s, "%-*s ", indent, "Capacity:");
	switch (*prtOutputEntry->prtOutputMaxCapacity) {
	case -1:
	    g_string_append(s, "unlimited");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	default:
	    g_string_sprintfa(s, "%d",
			      *prtOutputEntry->prtOutputMaxCapacity);
	}
	g_string_sprintfa(s, " %s\n", e ? e : "");
    }

    if (prtOutputEntry->prtOutputRemainingCapacity) {
	g_string_sprintfa(s, "%-*s ", indent, "Remaining:");
	switch (*prtOutputEntry->prtOutputRemainingCapacity) {
	case -1:
	    g_string_append(s, "unlimited");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	case -3:
	    g_string_append(s, ">0");
	    break;
	default:
	    g_string_sprintfa(s, "%d", *prtOutputEntry->prtOutputRemainingCapacity);
	}
	g_string_sprintfa(s, " %s\n", e ? e : "");
    }

    fmt_subunit(s, indent, prtOutputEntry->prtOutputStatus);
    
    if (prtOutputEntry->prtOutputSerialNumber &&
	prtOutputEntry->_prtOutputSerialNumberLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Serial Number:",
			  (int) prtOutputEntry->_prtOutputSerialNumberLength,
			  prtOutputEntry->prtOutputSerialNumber);
    }
    
    if (prtOutputEntry->prtOutputVersion &&
	prtOutputEntry->_prtOutputVersionLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Output Version:",
			  (int) prtOutputEntry->_prtOutputVersionLength,
			  prtOutputEntry->prtOutputVersion);
    }

    e = fmt_enum(printer_mib_enums_prtOutputSecurity,
		 prtOutputEntry->prtOutputSecurity);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Security:", e);
    }

    fmt_media_dimensions(s, indent, "Min. Dimensions:",
			 prtOutputEntry->prtOutputMinDimFeedDir,
			 prtOutputEntry->prtOutputMinDimXFeedDir,
			 prtOutputEntry->prtOutputDimUnit,
			 printer_mib_enums_prtOutputDimUnit);

    fmt_media_dimensions(s, indent, "Max. Dimensions:",
			 prtOutputEntry->prtOutputMaxDimFeedDir,
			 prtOutputEntry->prtOutputMaxDimXFeedDir,
			 prtOutputEntry->prtOutputDimUnit,
			 printer_mib_enums_prtOutputDimUnit);

    e = fmt_enum(printer_mib_enums_prtOutputStackingOrder,
		 prtOutputEntry->prtOutputStackingOrder);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Stacking Order:", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputPageDeliveryOrientation,
		 prtOutputEntry->prtOutputPageDeliveryOrientation);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Orientation:", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputBursting,
		 prtOutputEntry->prtOutputBursting);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Bursting:", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputDecollating,
		 prtOutputEntry->prtOutputDecollating);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Decollating:", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputPageCollated,
		 prtOutputEntry->prtOutputPageCollated);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Collation:", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputOffsetStacking,
		 prtOutputEntry->prtOutputOffsetStacking);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Offset Stacking:", e);
    }
}



static void
xml_printer_outputs(xmlNodePtr root,
		    printer_mib_prtOutputEntry_t *prtOutputEntry)
{
    xmlNodePtr tree, node;
    const char *e;

    tree = xmlNewChild(root, NULL, "output", NULL);
    xml_set_prop(tree, "number", "%d",
		 prtOutputEntry->prtOutputIndex);

    if (prtOutputEntry->prtOutputName) {
        (void) xml_new_child(tree, NULL, "name", "%.*s",
			     (int) prtOutputEntry->_prtOutputNameLength,
			     prtOutputEntry->prtOutputName);
    }

    if (prtOutputEntry->prtOutputDescription) {
        (void) xml_new_child(tree, NULL, "description", "%.*s",
			     (int) prtOutputEntry->_prtOutputDescriptionLength,
			     prtOutputEntry->prtOutputDescription);
    }

    if (prtOutputEntry->prtOutputVendorName) {
        (void) xml_new_child(tree, NULL, "vendor", "%.*s",
			     (int) prtOutputEntry->_prtOutputVendorNameLength,
			     prtOutputEntry->prtOutputVendorName);
    }

    e = fmt_enum(printer_mib_enums_prtOutputType,
		 prtOutputEntry->prtOutputType);
    if (e) {
	(void) xml_new_child(tree, NULL, "type", "%s", e);
    }
    
    if (prtOutputEntry->prtOutputModel) {
        (void) xml_new_child(tree, NULL, "model", "%.*s",
			     (int) prtOutputEntry->_prtOutputModelLength,
			     prtOutputEntry->prtOutputModel);
    }

    e = fmt_enum(printer_mib_enums_prtOutputCapacityUnit,
		 prtOutputEntry->prtOutputCapacityUnit);

    if (prtOutputEntry->prtOutputMaxCapacity) {
	switch (*prtOutputEntry->prtOutputMaxCapacity) {
	case -1:
	    node = xml_new_child(tree, NULL, "capacity", "unlimited");
	    break;
	case -2:
	    node = xml_new_child(tree, NULL, "capacity", "unknown");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "capacity", "%d",
				 *prtOutputEntry->prtOutputMaxCapacity);
	}
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    if (prtOutputEntry->prtOutputRemainingCapacity) {
	switch (*prtOutputEntry->prtOutputRemainingCapacity) {
	case -1:
	    node = xml_new_child(tree, NULL, "level", "unlimited");
	    break;
	case -2:
	    node = xml_new_child(tree, NULL, "level", "unknown");
	    break;
	case -3:
	    node = xml_new_child(tree, NULL, "level", ">0");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "level", "%d",
				 *prtOutputEntry->prtOutputRemainingCapacity);
	}
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    xml_subunit(tree, prtOutputEntry->prtOutputStatus);

    if (prtOutputEntry->prtOutputSerialNumber) {
	(void) xml_new_child(tree, NULL, "serial", "%.*s",
			     (int) prtOutputEntry->_prtOutputSerialNumberLength,
			     prtOutputEntry->prtOutputSerialNumber);
    }
    
    if (prtOutputEntry->prtOutputVersion) {
	(void) xml_new_child(tree, NULL, "version", "%.*s",
			     (int) prtOutputEntry->_prtOutputVersionLength,
			     prtOutputEntry->prtOutputVersion);
    }

    e = fmt_enum(printer_mib_enums_prtOutputSecurity,
		 prtOutputEntry->prtOutputSecurity);
    if (e) {
	(void) xml_new_child(tree, NULL, "security", "%s", e);
    }

    /* ...media specific stuff begins here... */

    xml_media_dimensions(tree, "min-dimensions:",
			 prtOutputEntry->prtOutputMinDimFeedDir,
			 prtOutputEntry->prtOutputMinDimXFeedDir,
			 prtOutputEntry->prtOutputDimUnit,
			 printer_mib_enums_prtOutputDimUnit);

    xml_media_dimensions(tree, "max-dimensions:",
			 prtOutputEntry->prtOutputMaxDimFeedDir,
			 prtOutputEntry->prtOutputMaxDimXFeedDir,
			 prtOutputEntry->prtOutputDimUnit,
			 printer_mib_enums_prtOutputDimUnit);

    e = fmt_enum(printer_mib_enums_prtOutputStackingOrder,
		 prtOutputEntry->prtOutputStackingOrder);
    if (e) {
	(void) xml_new_child(tree, NULL, "stacking-order", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputPageDeliveryOrientation,
		 prtOutputEntry->prtOutputPageDeliveryOrientation);
    if (e) {
	(void) xml_new_child(tree, NULL, "orientation", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputBursting,
		 prtOutputEntry->prtOutputBursting);
    if (e) {
	(void) xml_new_child(tree, NULL, "bursting", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputDecollating,
		 prtOutputEntry->prtOutputDecollating);
    if (e) {
	(void) xml_new_child(tree, NULL, "decollating", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputPageCollated,
		 prtOutputEntry->prtOutputPageCollated);
    if (e) {
	(void) xml_new_child(tree, NULL, "collation", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtOutputOffsetStacking,
		 prtOutputEntry->prtOutputOffsetStacking);
    if (e) {
	(void) xml_new_child(tree, NULL, "offset-stacking", "%s", e);
    }
}



static int
show_printer_outputs(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtOutputEntry_t **prtOutputTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtOutputTable(interp->peer, &prtOutputTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtOutputTable) {
	for (i = 0; prtOutputTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					   prtOutputTable[i]->hrDeviceIndex,
						   "outputs");
		xml_printer_outputs(node, prtOutputTable[i]);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_outputs(interp->result, prtOutputTable[i]);
	    }
	}
    }

    if (prtOutputTable) printer_mib_free_prtOutputTable(prtOutputTable);
	
    return SCLI_OK;
}



static void
fmt_printer_marker(GString *s, printer_mib_prtMarkerEntry_t *prtMarkerEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtMarkerEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %u\n", indent, "Marker:",
		      prtMarkerEntry->prtMarkerIndex);

    e = fmt_enum(printer_mib_enums_prtMarkerCounterUnit,
		 prtMarkerEntry->prtMarkerCounterUnit);

    if (prtMarkerEntry->prtMarkerLifeCount) {
	g_string_sprintfa(s, "%-*s %u %s\n", indent, "Life Count:",
			  *prtMarkerEntry->prtMarkerLifeCount,
			  e ? e : "");
    }

    if (prtMarkerEntry->prtMarkerPowerOnCount) {
	g_string_sprintfa(s, "%-*s %u %s\n", indent, "Power On Count:",
			  *prtMarkerEntry->prtMarkerPowerOnCount,
			  e ? e : "");
    }

    e = fmt_enum(printer_mib_enums_prtMarkerMarkTech,
		 prtMarkerEntry->prtMarkerMarkTech);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Technology:", e);
    }

    fmt_subunit(s, indent, prtMarkerEntry->prtMarkerStatus);
}


    
static void
xml_printer_marker(xmlNodePtr root,
		   printer_mib_prtMarkerEntry_t *prtMarkerEntry)
{
    xmlNodePtr tree, node;
    const char *e;

    tree = xmlNewChild(root, NULL, "marker", NULL);
    xml_set_prop(tree, "number", "%d",
		      prtMarkerEntry->prtMarkerIndex);
    e = fmt_enum(printer_mib_enums_prtMarkerCounterUnit,
		 prtMarkerEntry->prtMarkerCounterUnit);

    if (prtMarkerEntry->prtMarkerLifeCount) {
	node = xml_new_child(tree, NULL, "life-count", "%u",
			     *prtMarkerEntry->prtMarkerLifeCount);
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    if (prtMarkerEntry->prtMarkerPowerOnCount) {
	node = xml_new_child(tree, NULL, "power-on-count", "%u",
			     *prtMarkerEntry->prtMarkerPowerOnCount);
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerMarkTech,
		 prtMarkerEntry->prtMarkerMarkTech);
    if (e) {
	(void) xml_new_child(tree, NULL, "technology", "%s", e);
    }

    xml_subunit(tree, prtMarkerEntry->prtMarkerStatus);
}


    
static int
show_printer_markers(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtMarkerEntry_t **prtMarkerTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtMarkerTable(interp->peer, &prtMarkerTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtMarkerTable) {
	for (i = 0; prtMarkerTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					   prtMarkerTable[i]->hrDeviceIndex,
						   "markers");
		xml_printer_marker(node, prtMarkerTable[i]);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_marker(interp->result, prtMarkerTable[i]);
	    }
	}
    }

    if (prtMarkerTable) printer_mib_free_prtMarkerTable(prtMarkerTable);
	
    return SCLI_OK;
}



static void
fmt_printer_colorant(GString *s,
		     printer_mib_prtMarkerColorantEntry_t *prtColorantEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtColorantEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %u\n", indent, "Colorant:",
		      prtColorantEntry->prtMarkerColorantIndex);

    if (prtColorantEntry->prtMarkerColorantMarkerIndex) {
	g_string_sprintfa(s, "%-*s %d\n", indent, "Marker:",
			  *prtColorantEntry->prtMarkerColorantMarkerIndex);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerColorantRole,
		 prtColorantEntry->prtMarkerColorantRole);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Role:", e);
    }

    if (prtColorantEntry->prtMarkerColorantValue
	&& prtColorantEntry->_prtMarkerColorantValueLength) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Color:",
		  (int) prtColorantEntry->_prtMarkerColorantValueLength,
		  prtColorantEntry->prtMarkerColorantValue);
    }

    if (prtColorantEntry->prtMarkerColorantTonality) {
	g_string_sprintfa(s, "%-*s %d\n", indent, "Tonality:",
			  *prtColorantEntry->prtMarkerColorantTonality);
    }
}


    
static void
xml_printer_colorant(xmlNodePtr root,
		     printer_mib_prtMarkerColorantEntry_t *prtColorantEntry)
{
    xmlNodePtr tree;
    const char *e;

    tree = xmlNewChild(root, NULL, "colorant", NULL);
    xml_set_prop(tree, "number", "%d",
		 prtColorantEntry->prtMarkerColorantIndex);

    if (prtColorantEntry->prtMarkerColorantMarkerIndex) {
	(void) xml_new_child(tree, NULL, "marker", "%d",
			     *prtColorantEntry->prtMarkerColorantMarkerIndex);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerColorantRole,
		 prtColorantEntry->prtMarkerColorantRole);
    if (e) {
	(void) xml_new_child(tree, NULL, "role", "%s", e);
    }

    if (prtColorantEntry->prtMarkerColorantValue) {
	(void) xml_new_child(tree, NULL, "color", "%.*s",
		  (int) prtColorantEntry->_prtMarkerColorantValueLength,
		  prtColorantEntry->prtMarkerColorantValue);
    }

    if (prtColorantEntry->prtMarkerColorantTonality) {
	(void) xml_new_child(tree, NULL, "tonality", "%d",
			     *prtColorantEntry->prtMarkerColorantTonality);
    }
}


    
static int
show_printer_colorants(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtMarkerColorantEntry_t **prtColorantTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtMarkerColorantTable(interp->peer, &prtColorantTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtColorantTable) {
	for (i = 0; prtColorantTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					   prtColorantTable[i]->hrDeviceIndex,
						   "colorants");
		xml_printer_colorant(node, prtColorantTable[i]);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_colorant(interp->result, prtColorantTable[i]);
	    }
	}
    }

    if (prtColorantTable)
	printer_mib_free_prtMarkerColorantTable(prtColorantTable);
	
    return SCLI_OK;
}



static void
fmt_printer_supplies(GString *s, printer_mib_prtMarkerSuppliesEntry_t *prtSuppliesEntry)
{
    int const indent = 18;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtSuppliesEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %u\n", indent, "Supply:",
		      prtSuppliesEntry->prtMarkerSuppliesIndex);

    if (prtSuppliesEntry->prtMarkerSuppliesMarkerIndex
	&& *prtSuppliesEntry->prtMarkerSuppliesMarkerIndex) {
	g_string_sprintfa(s, "%-*s marker #%u\n", indent, "Marker:",
			  *prtSuppliesEntry->prtMarkerSuppliesMarkerIndex);
    }

    if (prtSuppliesEntry->prtMarkerSuppliesColorantIndex
	&& *prtSuppliesEntry->prtMarkerSuppliesColorantIndex) {
	g_string_sprintfa(s, "%-*s colorant #%u\n", indent, "Colorant:",
			  *prtSuppliesEntry->prtMarkerSuppliesColorantIndex);
    }

    if (prtSuppliesEntry->prtMarkerSuppliesDescription &&
	prtSuppliesEntry->_prtMarkerSuppliesDescriptionLength > 0) {
	g_string_sprintfa(s, "%-*s %.*s\n", indent, "Description:",
			  (int) prtSuppliesEntry->_prtMarkerSuppliesDescriptionLength,
			  prtSuppliesEntry->prtMarkerSuppliesDescription);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerSuppliesType,
		 prtSuppliesEntry->prtMarkerSuppliesType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Type:", e);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerSuppliesClass,
		 prtSuppliesEntry->prtMarkerSuppliesClass);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Class:", e);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerSuppliesSupplyUnit,
		 prtSuppliesEntry->prtMarkerSuppliesSupplyUnit);

    if (prtSuppliesEntry->prtMarkerSuppliesMaxCapacity) {
	g_string_sprintfa(s, "%-*s ", indent, "Capacity:");
	switch (*prtSuppliesEntry->prtMarkerSuppliesMaxCapacity) {
	case -1:
	    g_string_append(s, "unlimited");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	default:
	    g_string_sprintfa(s, "%d", *prtSuppliesEntry->prtMarkerSuppliesMaxCapacity);
	}
	g_string_sprintfa(s, " %s\n", e ? e : "");
    }

    if (prtSuppliesEntry->prtMarkerSuppliesLevel) {
	g_string_sprintfa(s, "%-*s ", indent, "Level:");
	switch (*prtSuppliesEntry->prtMarkerSuppliesLevel) {
	case -1:
	    g_string_append(s, "unlimited");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	case -3:
	    g_string_append(s, ">0");
	    break;
	default:
	    g_string_sprintfa(s, "%d", *prtSuppliesEntry->prtMarkerSuppliesLevel);
	}
	g_string_sprintfa(s, " %s\n", e ? e : "");
    }
}


    
static void
xml_printer_supplies(xmlNodePtr root,
		     printer_mib_prtMarkerSuppliesEntry_t *prtSuppliesEntry)
{
    xmlNodePtr tree, node;
    const char *e;

    tree = xmlNewChild(root, NULL, "supply", NULL);
    xml_set_prop(tree, "number", "%d",
		 prtSuppliesEntry->prtMarkerSuppliesIndex);

    if (prtSuppliesEntry->prtMarkerSuppliesMarkerIndex
	&& *prtSuppliesEntry->prtMarkerSuppliesMarkerIndex) {
	(void) xml_new_child(tree, NULL, "description", "%d",
			  *prtSuppliesEntry->prtMarkerSuppliesMarkerIndex);
    }

    if (prtSuppliesEntry->prtMarkerSuppliesColorantIndex
	&& *prtSuppliesEntry->prtMarkerSuppliesColorantIndex) {
	(void) xml_new_child(tree, NULL, "colorant", "%d",
			  *prtSuppliesEntry->prtMarkerSuppliesColorantIndex);
    }

    if (prtSuppliesEntry->prtMarkerSuppliesDescription) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
			     (int) prtSuppliesEntry->_prtMarkerSuppliesDescriptionLength,
			     prtSuppliesEntry->prtMarkerSuppliesDescription);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerSuppliesType,
		 prtSuppliesEntry->prtMarkerSuppliesType);
    if (e) {
	(void) xml_new_child(tree, NULL, "type", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerSuppliesClass,
		 prtSuppliesEntry->prtMarkerSuppliesClass);
    if (e) {
	(void) xml_new_child(tree, NULL, "class", "%s", e);
    }

    e = fmt_enum(printer_mib_enums_prtMarkerSuppliesSupplyUnit,
		 prtSuppliesEntry->prtMarkerSuppliesSupplyUnit);

    if (prtSuppliesEntry->prtMarkerSuppliesMaxCapacity) {
	switch (*prtSuppliesEntry->prtMarkerSuppliesMaxCapacity) {
	case -1:
	    node = xml_new_child(tree, NULL, "capacity", "unlimited");
	    break;
	case -2:
	    node = xml_new_child(tree, NULL, "capacity", "unknown");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "capacity", "%d",
			 *prtSuppliesEntry->prtMarkerSuppliesMaxCapacity);
	}
	if (e) xml_set_prop(node, "unit", "%s", e);
    }

    if (prtSuppliesEntry->prtMarkerSuppliesLevel) {
	switch (*prtSuppliesEntry->prtMarkerSuppliesLevel) {
	case -1:
	    node = xml_new_child(tree, NULL, "level", "unlimited");
	    break;
	case -2:
	    node = xml_new_child(tree, NULL, "level", "unknown");
	    break;
	case -3:
	    node = xml_new_child(tree, NULL, "level", ">0");
	    break;
	default:
	    node = xml_new_child(tree, NULL, "level", "%d",
				 *prtSuppliesEntry->prtMarkerSuppliesLevel);
	}
	if (e) xml_set_prop(node, "unit", "%s", e);
    }
}


    
static int
show_printer_supplies(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtMarkerSuppliesEntry_t **prtMarkerSuppliesTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtMarkerSuppliesTable(interp->peer, &prtMarkerSuppliesTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtMarkerSuppliesTable) {
	for (i = 0; prtMarkerSuppliesTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
				   prtMarkerSuppliesTable[i]->hrDeviceIndex,
						   "supplies");
		xml_printer_supplies(node, prtMarkerSuppliesTable[i]);
	    } else {		
	        if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_supplies(interp->result,
				     prtMarkerSuppliesTable[i]);
	    }
	}
    }

    if (prtMarkerSuppliesTable)
	printer_mib_free_prtMarkerSuppliesTable(prtMarkerSuppliesTable);
	
    return SCLI_OK;
}



static void
fmt_printer_interpreter(GString *s,
			printer_mib_prtInterpreterEntry_t *interpEntry)
{
    int const indent = 14;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      interpEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %d\n", indent, "Interpreter:",
		      interpEntry->prtInterpreterIndex);

    e = fmt_enum(printer_mib_enums_prtInterpreterLangFamily,
		 interpEntry->prtInterpreterLangFamily);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Language:", e);
    }

    fmt_display_string(s, indent+1, "Description:",
		       (int) interpEntry->_prtInterpreterDescriptionLength,
		       interpEntry->prtInterpreterDescription);

    fmt_display_string(s, indent+1, "Version:",
		       (int) interpEntry->_prtInterpreterVersionLength,
		       interpEntry->prtInterpreterVersion);
}



static void
xml_printer_interpreter(xmlNodePtr root,
			printer_mib_prtInterpreterEntry_t *interpEntry)
{
    xmlNodePtr tree;
    const char *e;

    tree = xmlNewChild(root, NULL, "interpreter", NULL);
    xml_set_prop(tree, "number", "%d",
		 interpEntry->prtInterpreterIndex);

    e = fmt_enum(printer_mib_enums_prtInterpreterLangFamily,
		 interpEntry->prtInterpreterLangFamily);
    if (e) {
	(void) xml_new_child(tree, NULL, "language", "%s", e);
    }

    if (interpEntry->prtInterpreterDescription) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
		     (int) interpEntry->_prtInterpreterDescriptionLength,
		     interpEntry->prtInterpreterDescription);
    }

    if (interpEntry->prtInterpreterVersion) {
	(void) xml_new_child(tree, NULL, "version", "%.*s",
			     (int) interpEntry->_prtInterpreterVersionLength,
			     interpEntry->prtInterpreterVersion);
    }
}



static int
show_printer_interpreters(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtInterpreterEntry_t **interpTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtInterpreterTable(interp->peer, &interpTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (interpTable) {
	for (i = 0; interpTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					   interpTable[i]->hrDeviceIndex,
						   "interpreters");
		xml_printer_interpreter(node, interpTable[i]);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_interpreter(interp->result, interpTable[i]);
	    }
	}
    }

    if (interpTable)
	printer_mib_free_prtInterpreterTable(interpTable);
	
    return SCLI_OK;
}



static printer_mib_prtInterpreterEntry_t*
find_interp(printer_mib_prtInterpreterEntry_t **interpTable,
	    gint32 hrDeviceIndex, gint32 interpIndex)
{
    int i;
    
    if (! interpTable) {
	return NULL;
    }

    for (i = 0; interpTable[i]; i++) {
	if (interpTable[i]->hrDeviceIndex == hrDeviceIndex
	    && interpTable[i]->prtInterpreterIndex == interpIndex) {
	    break;
	}
    }
    return interpTable[i];
}



static void
fmt_printer_channel(GString *s,
		    printer_mib_prtChannelEntry_t *channelEntry,
		    printer_mib_prtInterpreterEntry_t **interpTable)
{
    printer_mib_prtInterpreterEntry_t *interpEntry;
    int const indent = 14;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      channelEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %d\n", indent, "Channel:",
		      channelEntry->prtChannelIndex);

    e = fmt_enum(printer_mib_enums_prtChannelType,
		 channelEntry->prtChannelType);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Type:", e);
    }

    fmt_display_string(s, indent+1, "Version:",
		       (int) channelEntry->_prtChannelProtocolVersionLength,
		       channelEntry->prtChannelProtocolVersion);

    e = fmt_enum(printer_mib_enums_prtChannelState,
		 channelEntry->prtChannelState);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "State:", e);
    }

    if (channelEntry->prtChannelIndex) {
	g_string_sprintfa(s, "%-*s %d\n", indent, "Interface:",
			  *channelEntry->prtChannelIfIndex);
    }
    
    if (channelEntry->prtChannelCurrentJobCntlLangIndex) {
	interpEntry = find_interp(interpTable, channelEntry->hrDeviceIndex,
			  *channelEntry->prtChannelCurrentJobCntlLangIndex);
	e = (interpEntry) ?
	    fmt_enum(printer_mib_enums_prtInterpreterLangFamily,
		     interpEntry->prtInterpreterLangFamily) : NULL;
	if (e) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Ctrl Language:", e);
	} else {
	    g_string_sprintfa(s, "%-*s %d\n", indent, "Ctrl Language:",
			      *channelEntry->prtChannelCurrentJobCntlLangIndex);
	}
    }
			      
    if (channelEntry->prtChannelDefaultPageDescLangIndex) {
	interpEntry = find_interp(interpTable, channelEntry->hrDeviceIndex,
			  *channelEntry->prtChannelDefaultPageDescLangIndex);
	e = (interpEntry) ?
	    fmt_enum(printer_mib_enums_prtInterpreterLangFamily,
		     interpEntry->prtInterpreterLangFamily) : NULL;
	if (e) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Page Language:", e);
	} else {
	    g_string_sprintfa(s, "%-*s %d\n", indent, "Page Language:",
			      *channelEntry->prtChannelDefaultPageDescLangIndex);
	}
    }
    
    fmt_subunit(s, indent, channelEntry->prtChannelStatus);

    fmt_display_string(s, indent+1, "Information:",
		       (int) channelEntry->_prtChannelInformationLength,
		       channelEntry->prtChannelInformation);
}



static void
xml_printer_channel(xmlNodePtr root,
		    printer_mib_prtChannelEntry_t *channelEntry,
		    printer_mib_prtInterpreterEntry_t **interpTable)
{
    printer_mib_prtInterpreterEntry_t *interpEntry;
    xmlNodePtr tree;
    const char *e;

    tree = xmlNewChild(root, NULL, "channel", NULL);
    xml_set_prop(tree, "number", "%d",
		 channelEntry->prtChannelIndex);

    e = fmt_enum(printer_mib_enums_prtChannelType,
		 channelEntry->prtChannelType);
    if (e) {
	(void) xml_new_child(tree, NULL, "type", "%s", e);
    }

    if (channelEntry->prtChannelProtocolVersion) {
	(void) xml_new_child(tree, NULL, "version", "%.*s",
		     (int) channelEntry->_prtChannelProtocolVersionLength,
		     channelEntry->prtChannelProtocolVersion);
    }

    e = fmt_enum(printer_mib_enums_prtChannelState,
		 channelEntry->prtChannelState);
    if (e) {
	(void) xml_new_child(tree, NULL, "state", "%s", e);
    }

    if (channelEntry->prtChannelIndex) {
	(void) xml_new_child(tree, NULL, "interface", "%d",
			     *channelEntry->prtChannelIfIndex);
    }

    if (channelEntry->prtChannelCurrentJobCntlLangIndex) {
	interpEntry = find_interp(interpTable, channelEntry->hrDeviceIndex,
			  *channelEntry->prtChannelCurrentJobCntlLangIndex);
	e = (interpEntry) ?
	    fmt_enum(printer_mib_enums_prtInterpreterLangFamily,
		     interpEntry->prtInterpreterLangFamily) : NULL;
	if (e) {
	    (void) xml_new_child(tree, NULL, "crtl-language", "%s", e);
	} else {
	    (void) xml_new_child(tree, NULL, "crtl-language", "%d",
			 *channelEntry->prtChannelCurrentJobCntlLangIndex);
	}
    }

    if (channelEntry->prtChannelDefaultPageDescLangIndex) {
	interpEntry = find_interp(interpTable, channelEntry->hrDeviceIndex,
			  *channelEntry->prtChannelDefaultPageDescLangIndex);
	e = (interpEntry) ?
	    fmt_enum(printer_mib_enums_prtInterpreterLangFamily,
		     interpEntry->prtInterpreterLangFamily) : NULL;
	if (e) {
	    (void) xml_new_child(tree, NULL, "page-language", "%s", e);
	} else {
	    (void) xml_new_child(tree, NULL, "page-language", "%d",
			 *channelEntry->prtChannelDefaultPageDescLangIndex);
	}
    }

    xml_subunit(tree, channelEntry->prtChannelStatus);

    if (channelEntry->prtChannelInformation) {
	(void) xml_new_child(tree, NULL, "information", "%.*s",
			     (int) channelEntry->_prtChannelInformationLength,
			     channelEntry->prtChannelInformation);
    }
}



static int
show_printer_channels(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtChannelEntry_t **channelTable = NULL;
    printer_mib_prtInterpreterEntry_t **interpTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtChannelTable(interp->peer, &channelTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }
    printer_mib_get_prtInterpreterTable(interp->peer, &interpTable, 0);

    if (channelTable) {
	for (i = 0; channelTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					 channelTable[i]->hrDeviceIndex,
						   "channels");
		xml_printer_channel(node, channelTable[i], interpTable);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_channel(interp->result, channelTable[i],
				    interpTable);
	    }
	}
    }

    if (channelTable)
	printer_mib_free_prtChannelTable(channelTable);
    if (interpTable)
	printer_mib_free_prtInterpreterTable(interpTable);
	
    return SCLI_OK;
}



static void
fmt_printer_display(GString *s,
		    printer_mib_prtConsoleDisplayBufferEntry_t *displayEntry)
{
    g_string_sprintfa(s, "%6d  ", displayEntry->hrDeviceIndex);
		      
    g_string_sprintfa(s, "%4d   ", displayEntry->prtConsoleDisplayBufferIndex);
	
    if (displayEntry->prtConsoleDisplayBufferText) {
	g_string_sprintfa(s, "%.*s\n",
		    (int) displayEntry->_prtConsoleDisplayBufferTextLength,
		          displayEntry->prtConsoleDisplayBufferText);
    }
}



static void
xml_printer_display(xmlNodePtr root,
		    printer_mib_prtConsoleDisplayBufferEntry_t *displayEntry)
{
    xmlNodePtr tree;

    if (displayEntry->prtConsoleDisplayBufferText) {
	tree = xmlNewChild(root, NULL, "line", NULL);
	xml_set_prop(tree, "number", "%d",
		     displayEntry->prtConsoleDisplayBufferIndex);
	xml_set_content(tree, "%.*s", 
		  (int) displayEntry->_prtConsoleDisplayBufferTextLength,
			displayEntry->prtConsoleDisplayBufferText);
    }
}



static int
show_printer_display(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtConsoleDisplayBufferEntry_t **displayTable;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtConsoleDisplayBufferTable(interp->peer,
						 &displayTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (displayTable) {
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "PRINTER LINE   TEXT");
	}
	for (i = 0; displayTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					 displayTable[i]->hrDeviceIndex,
						   "display");
		xml_printer_display(node, displayTable[i]);
	    } else {
		fmt_printer_display(interp->result, displayTable[i]);
	    }
	}
    }

    if (displayTable)
	printer_mib_free_prtConsoleDisplayBufferTable(displayTable);

    return SCLI_OK;
}



static void
fmt_printer_light(GString *s,
		  printer_mib_prtConsoleLightEntry_t *prtConsoleLightEntry,
		  int light_width)
{
    const char *state = "off";
    const char *e;
    
    g_string_sprintfa(s, "%6d  ", prtConsoleLightEntry->hrDeviceIndex);
    g_string_sprintfa(s, "%4d  ", prtConsoleLightEntry->prtConsoleLightIndex);

    if (prtConsoleLightEntry->prtConsoleDescription) {
	g_string_sprintfa(s, "%-*.*s ", light_width,
			  (int) prtConsoleLightEntry->_prtConsoleDescriptionLength,
			  prtConsoleLightEntry->prtConsoleDescription);
    } else {
	g_string_sprintfa(s, "%*s", light_width, "");
    }

    if (*prtConsoleLightEntry->prtConsoleOnTime
	&& !*prtConsoleLightEntry->prtConsoleOffTime) {
	state = "on";
    } else if (!*prtConsoleLightEntry->prtConsoleOnTime
	       && *prtConsoleLightEntry->prtConsoleOffTime) {
	state = "off";
    } else if (*prtConsoleLightEntry->prtConsoleOnTime
	       && *prtConsoleLightEntry->prtConsoleOffTime) {
	state = "blink";
    }
    g_string_sprintfa(s, " %-*s ", 5, state);

    e = fmt_enum(printer_mib_enums_prtConsoleColor,
		 prtConsoleLightEntry->prtConsoleColor);
    g_string_sprintfa(s, "%s\n", e ? e : "");
}



static void
xml_printer_light(xmlNodePtr root,
		  printer_mib_prtConsoleLightEntry_t *lightEntry)
{
    xmlNodePtr tree;
    const char *state = "off";
    const char *e;
    
    tree = xmlNewChild(root, NULL, "light", NULL);
    xml_set_prop(tree, "number", "%d", lightEntry->prtConsoleLightIndex);

    if (lightEntry->prtConsoleDescription) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
		       (int) lightEntry->_prtConsoleDescriptionLength,
			     lightEntry->prtConsoleDescription);
    }

    e = fmt_enum(printer_mib_enums_prtConsoleColor,
		 lightEntry->prtConsoleColor);
    if (e) {
	xml_new_child(tree, NULL, "color", e);
    }

    if (*lightEntry->prtConsoleOnTime
	&& !*lightEntry->prtConsoleOffTime) {
	state = "on";
    } else if (!*lightEntry->prtConsoleOnTime
	       && *lightEntry->prtConsoleOffTime) {
	state = "off";
    } else if (*lightEntry->prtConsoleOnTime
	       && *lightEntry->prtConsoleOffTime) {
	state = "blink";
    }
    xml_new_child(tree, NULL, "status", state);
}



static int
show_printer_lights(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtConsoleLightEntry_t **lightTable;
    int i;
    int light_width = 12;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtConsoleLightTable(interp->peer,
					 &lightTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (lightTable) {
	for (i = 0; lightTable[i]; i++) {
	    if (lightTable[i]->_prtConsoleDescriptionLength > light_width) {
		light_width = lightTable[i]->_prtConsoleDescriptionLength;
	    }
	}
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header,
			      "PRINTER LIGHT %-*s STATUS COLOR",
			      light_width, "DESCRIPTION");
	}
	for (i = 0; lightTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					 lightTable[i]->hrDeviceIndex,
						   "lights");
		xml_printer_light(node, lightTable[i]);
	    } else {
		fmt_printer_light(interp->result, lightTable[i], light_width);
	    }
	}
    }

    if (lightTable)
	printer_mib_free_prtConsoleLightTable(lightTable);
	
    return SCLI_OK;
}



static void
fmt_printer_alert(GString *s, printer_mib_prtAlertEntry_t *alertEntry)
{
    int const indent = 14;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      alertEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %d\n", indent, "Alert:",
		      alertEntry->prtAlertIndex);

    if (alertEntry->prtAlertTime) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Date:",
			  fmt_timeticks(*alertEntry->prtAlertTime));
    }

    e = fmt_enum(printer_mib_enums_prtAlertCode,
		 alertEntry->prtAlertCode);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Code:", e);
    }

    e = fmt_enum(printer_mib_enums_prtAlertSeverityLevel,
		 alertEntry->prtAlertSeverityLevel);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Severity:", e);
    }

    fmt_display_string(s, indent+1, "Description:",
		       (int) alertEntry->_prtAlertDescriptionLength,
		       alertEntry->prtAlertDescription);

    e = fmt_enum(prtAlertGroup, alertEntry->prtAlertGroup);
    if (e) {
	g_string_sprintfa(s, "%-*s %s", indent, "Location:", e);
	if (alertEntry->prtAlertGroupIndex
	    && *alertEntry->prtAlertGroupIndex > 0) {
	    g_string_sprintfa(s, " #%u", *alertEntry->prtAlertGroupIndex);
	}
	if (alertEntry->prtAlertLocation
	    && *alertEntry->prtAlertLocation > 0) {
	    g_string_sprintfa(s, " (at location %u)", *alertEntry->prtAlertLocation);
	}
	g_string_append(s, "\n");
    }

    e = fmt_enum(printer_mib_enums_prtAlertTrainingLevel,
		 alertEntry->prtAlertTrainingLevel);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Personnel:", e);
    }
}



static void
xml_printer_alert(xmlNodePtr root, printer_mib_prtAlertEntry_t *alertEntry)
{
    xmlNodePtr tree;
    const char *e;

    tree = xmlNewChild(root, NULL, "alert", NULL);
    xml_set_prop(tree, "number", "%d", alertEntry->prtAlertIndex);

    if (alertEntry->prtAlertTime) {
	xml_new_child(tree, NULL, "date",
		      fmt_timeticks(*alertEntry->prtAlertTime));
    }

    e = fmt_enum(printer_mib_enums_prtAlertCode,
		 alertEntry->prtAlertCode);
    if (e) {
	xml_new_child(tree, NULL, "code", e);
    }

    e = fmt_enum(printer_mib_enums_prtAlertSeverityLevel,
		 alertEntry->prtAlertSeverityLevel);
    if (e) {
	xml_new_child(tree, NULL, "severity", e);
    }

    if (alertEntry->prtAlertDescription) {
	xml_new_child(tree, NULL, "description", "%.*s",
		(int) alertEntry->_prtAlertDescriptionLength,
		      alertEntry->prtAlertDescription);
    }

    e = fmt_enum(prtAlertGroup, alertEntry->prtAlertGroup);
    if (e) {
	GString *s = g_string_new(e);
	if (alertEntry->prtAlertGroupIndex
	    && *alertEntry->prtAlertGroupIndex > 0) {
	    g_string_sprintfa(s, " #%u", *alertEntry->prtAlertGroupIndex);
	}
	if (alertEntry->prtAlertLocation
	    && *alertEntry->prtAlertLocation > 0) {
	    g_string_sprintfa(s, " (at location %u)", *alertEntry->prtAlertLocation);
	}
	xml_new_child(tree, NULL, "location", s->str);
	g_string_free(s, 1);
    }

    e = fmt_enum(printer_mib_enums_prtAlertTrainingLevel,
		 alertEntry->prtAlertTrainingLevel);
    if (e) {
	xml_new_child(tree, NULL, "personnel", "%s", e);
    }
}



static int
show_printer_alert(scli_interp_t *interp, int argc, char **argv)
{
    printer_mib_prtAlertEntry_t **alertTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc > 1) {
	return SCLI_SYNTAX_NUMARGS;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_get_prtAlertTable(interp->peer, &alertTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (alertTable) {
	for (i = 0; alertTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xmlNodePtr node = get_printer_node(interp->xml_node,
					 alertTable[i]->hrDeviceIndex,
						   "alerts");
		xml_printer_alert(node, alertTable[i]);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_alert(interp->result, alertTable[i]);
	    }
	}
    }

    if (alertTable) printer_mib_free_prtAlertTable(alertTable);
    
    return SCLI_OK;
}



static int
set_printer_operator(scli_interp_t *interp, int argc, char **argv)
{
    gchar *operator;
    gsize operator_len;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (argc != 2) {
	return SCLI_SYNTAX_NUMARGS;
    }

    operator = argv[1];
    operator_len = strlen(operator);
    if (operator_len < PRINTER_MIB_PRTGENERALCURRENTOPERATORMINLENGTH
	|| operator_len > PRINTER_MIB_PRTGENERALCURRENTOPERATORMAXLENGTH) {
	g_string_assign(interp->result, operator);
	return SCLI_SYNTAX_VALUE;
    }

    if (scli_interp_dry(interp)) {
	return SCLI_OK;
    }

    printer_mib_set_prtGeneralCurrentOperator(interp->peer, 42, /* xxx */
					      operator, operator_len);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    return SCLI_OK;
}



void
scli_init_printer_mode(scli_interp_t *interp)
{
    static scli_cmd_t cmds[] = {

	{ "set printer operator", "<string>",
	  "The `set printer operator' command configures the name of the\n"
	  "person responsible for operating a printer. As a convention,\n"
	  "the phone number, fax number or email address should be\n"
	  "indicated by the tel:, fax: and mailto: URL schemes.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY | SCLI_CMD_FLAG_NORECURSE,
	  NULL, NULL,
	  set_printer_operator },

	{ "show printer info", NULL,
	  "The `show printer info' command shows general information about\n"
	  "the printer including global status information.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_info },

	{ "show printer paths", NULL,
	  "The `show printer paths' command shows information about the\n"
	  "media paths of a printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_paths },

	{ "show printer inputs", NULL,
	  "The `show printer inputs' command shows information about the\n"
	  "input sub-units of a printer which provide media for input to\n"
	  "the printing process.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices",
	  NULL,
	  show_printer_inputs },

	{ "show printer outputs", NULL,
	  "The `show printer output' command shows information about the\n"
	  "output sub-units of a printer capable of receiving media\n"
	  "delivered from the printing process.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_outputs },

	{ "show printer markers", NULL,
	  "The `show printer markers' command shows information about the\n"
	  "marker sub-units of a printer which produce marks on the print\n"
	  "media.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_markers },

	{ "show printer colorants", NULL,
	  "The `show printer colorants' command shows information about the\n"
	  "colorant sub-units of a printer which produce marks on the print\n"
	  "media.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_colorants },

	{ "show printer supplies", NULL,
	  "The `show printer supplies' command shows information about the\n"
	  "supplies which are consumed and the waste produced by the\n"
	  "markers of a printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_supplies },

	{ "show printer interpreters", NULL,
	  "The `show printer interpreters' command shows information about\n"
	  "the page description language and control language interpreters\n"
	  "supported by the printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_interpreters },

	{ "show printer channels", NULL,
	  "The `show printer channels' command shows information about\n"
	  "the channels which can be used to submit data to the printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_channels },
	
	{ "show printer covers", NULL,
	  "The `show printer covers' command shows information about the\n"
	  "covers of a printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices", NULL,
	  show_printer_covers },

	{ "show printer display", NULL,
	  "The `show printer display' command shows the current\n"
	  "contents of the display attached to the printer. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  PRINTER logical printer number\n"
	  "  LINE    display line number\n"
	  "  TEXT    contents of the display line",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices",
	  NULL,
	  show_printer_display },

	{ "show printer lights", NULL,
	  "The `show printer lights' command shows the current\n"
	  "status of the lights attached to the printer. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  PRINTER     logical printer number\n"
	  "  LIGHT       number identifying the light/led\n"
	  "  DESCRIPTION description of the light/led\n"
	  "  STATUS      current status (on, off, blink)\n"
	  "  COLOR       current color of the light",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices",
	  "<xsd:simpleType name=\"PrinterLightColor\">\n"
	  "  <xsd:restriction base=\"xsd:string\">\n"
	  "    <xsd:enumeration value=\"other\"/>\n"
	  "    <xsd:enumeration value=\"unknown\"/>\n"
	  "    <xsd:enumeration value=\"white\"/>\n"
	  "    <xsd:enumeration value=\"red\"/>\n"
	  "    <xsd:enumeration value=\"green\"/>\n"
	  "    <xsd:enumeration value=\"blue\"/>\n"
	  "    <xsd:enumeration value=\"cyan\"/>\n"
	  "    <xsd:enumeration value=\"magenta\"/>\n"
	  "    <xsd:enumeration value=\"yellow\"/>\n"
	  "    <xsd:enumeration value=\"orange\"/>\n"
	  "  </xsd:restriction>\n"
	  "</xsd:simpleType>\n"
	  "\n"
	  "<xsd:simpleType name=\"PrinterLightStatus\">\n"
	  "  <xsd:restriction base=\"xsd:string\">\n"
	  "    <xsd:enumeration value=\"on\"/>\n"
	  "    <xsd:enumeration value=\"off\"/>\n"
	  "    <xsd:enumeration value=\"blink\"/>\n"
	  "  </xsd:restriction>\n"
	  "</xsd:simpleType>\n"
	  "\n"
	  "<xsd:complexType name=\"light\">\n"
	  "  <xsd:sequence>\n"
	  "    <xsd:element name=\"description\" type=\"xsd:string\" minOccurs=\"0\"/>\n"
	  "    <xsd:element name=\"color\" type=\"xsd:PrinterLightColor\" minOccurs=\"0\"/>\n"
	  "    <xsd:element name=\"status\" type=\"xsd:PrinterLightStatus\" minOccurs=\"0\"/>\n"
	  "  </xsd:sequence>\n"
	  "  <xsd:attribute name=\"printer\" type=\"xsd:int\"/>\n"
	  "  <xsd:attribute name=\"number\" type=\"xsd:int\"/>\n"
	  "</xsd:complexType>",
	  show_printer_lights },

	{ "show printer alerts", NULL,
	  "The `show printer alerts' command displays the list of active\n"
	  "printer alerts including the alert code, the alert severity,\n"
	  "the alert description, the alert time, the alert location and\n"
	  "the personel required to handle the alert.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "devices",
	  "<xsd:simpleType name=\"PrinterAlertSeverity\">\n"
	  "  <xsd:restriction base=\"xsd:string\">\n"
	  "    <xsd:enumeration value=\"other\"/>\n"
	  "    <xsd:enumeration value=\"critical\"/>\n"
	  "    <xsd:enumeration value=\"warning\"/>\n"
	  "    <xsd:enumeration value=\"warningBinaryChangeEvent\"/>\n"
	  "  </xsd:restriction>\n"
	  "</xsd:simpleType>\n"
	  "\n"
	  "<xsd:simpleType name=\"PrinterAlertPersonnel\">\n"
	  "  <xsd:restriction base=\"xsd:string\">\n"
	  "    <xsd:enumeration value=\"other\"/>\n"
	  "    <xsd:enumeration value=\"unknown\"/>\n"
	  "    <xsd:enumeration value=\"untrained\"/>\n"
	  "    <xsd:enumeration value=\"trained\"/>\n"
	  "    <xsd:enumeration value=\"fieldService\"/>\n"
	  "    <xsd:enumeration value=\"management\"/>\n"
	  "    <xsd:enumeration value=\"noInterventionRequired\"/>\n"
	  "  </xsd:restriction>\n"
	  "</xsd:simpleType>\n"
	  "\n"
	  "<xsd:complexType name=\"alert\">\n"
	  "  <xsd:sequence>\n"
	  "    <xsd:element name=\"date\" type=\"xsd:string\" minOccurs=\"0\"/>\n"
	  "    <xsd:element name=\"code\" type=\"xsd:string\" minOccurs=\"0\"/>\n"
	  "    <xsd:element name=\"severity\" type=\"xsd:PrinterAlertSeverity\" minOccurs=\"0\"/>\n"
	  "    <xsd:element name=\"description\" type=\"xsd:string\" minOccurs=\"0\"/>\n"
	  "    <xsd:element name=\"location\" type=\"xsd:string\" minOccurs=\"0\"/>\n"
	  "    <xsd:element name=\"personnel\" type=\"xsd:PrinterAlertPersonnel\" minOccurs=\"0\"/>\n"
	  "  </xsd:sequence>\n"
	  "  <xsd:attribute name=\"printer\" type=\"xsd:int\"/>\n"
	  "  <xsd:attribute name=\"number\" type=\"xsd:int\"/>\n"
	  "</xsd:complexType>",
	  show_printer_alert },

	{ "monitor printer display", NULL,
	  "The `monitor printer display' command shows the same\n"
          "information as the show printer display command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_display },

	{ "monitor printer lights", NULL,
	  "The `monitor printer lights' command shows the same\n"
	  "information as the show printer lights command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_lights },

	{ "monitor printer alerts", NULL,
	  "The `monitor printer alerts' command shows the same information\n"
	  "as the show printer alerts command. The information is updated\n"
	  "periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_alert },

	{ NULL, NULL, NULL, 0, NULL, NULL, NULL }
    };

    static scli_mode_t printer_mode = {
	"printer",
	"The scli printer mode is based on the Printer-MIB as published\n"
	"in RFC 1759 and some updates currently being worked on in the\n"
	"IETF Printer MIB working group.",
	cmds
    };

    scli_register_mode(interp, &printer_mode);
}
