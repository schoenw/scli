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
    
    if (! dir || ! xdir || ! unit) {
	return;
    }

    e = fmt_enum(enums, unit);
	
    g_string_sprintfa(s, "%-*s %s", indent, label,
		      fmt_dimensions(dir));
    g_string_sprintfa(s, " x %s ",
		      fmt_dimensions(xdir));
    g_string_sprintfa(s, "%s\n", e ? e : "");
}



static void
xml_media_dimensions(xmlNodePtr tree, gchar *label,
		     gint32 *dir, gint32 *xdir,
		     gint32 *unit, const GSnmpEnum *enums)
{
    const char *e;
    gchar *s;
    xmlNodePtr node;
    
    if (! dir || ! xdir || ! unit) {
	return;
    }

    s = g_strdup(fmt_dimensions(dir));
    node = xml_new_child(tree, NULL, label, "%sx%s", s, 
			 fmt_dimensions(xdir));
    g_free(s);

    e = fmt_enum(enums, unit);
    if (e) {
	xml_set_prop(node, "unit", e);
    }
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

    if (hrDeviceEntry && hrDeviceEntry->hrDeviceType) {
	char const *type;
	type = gsnmp_identity_get_label(host_resources_types_identities,
					hrDeviceEntry->hrDeviceType,
					hrDeviceEntry->_hrDeviceDescrLength);
	if (type) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Type:", type);
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
	char const *state;
	state = fmt_bits(error_states,
			 hrPrinterEntry->hrPrinterDetectedErrorState,
			 hrPrinterEntry->_hrPrinterDetectedErrorStateLength);
	if (state) {
	    g_string_sprintfa(s, "%-*s %s\n", indent, "Error State:", state);
	}
    }
}



static void
fmt_printer_general(GString *s,
		     printer_mib_prtGeneralEntry_t *prtGeneralEntry,
		     printer_mib_prtLocalizationEntry_t **prtLocalTable)
{
    int const indent = 18;

    /* MISSING: prtGeneralCurrentLocalization */
    /* MISSING: prtAuxiliarySheetStartupPage */
    /* MISSING: prtAuxiliarySheetBannerPage */
    /* Write-only-variable: prtGeneralReset */
    
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
    
    if (prtGeneralEntry->prtConsoleDisable) {
	g_string_sprintfa(s, "%-*s ", indent, "Console Access:");
	xxx_enum(s, 8, printer_mib_enums_prtConsoleDisable,
		 prtGeneralEntry->prtConsoleDisable);
	g_string_append(s, "\n");
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
show_printer_info(scli_interp_t * interp, int argc, char **argv)
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



static int
show_printer_covers(scli_interp_t * interp, int argc, char **argv)
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
	    fmt_printer_cover(interp->result, prtCoverTable[i]);
	}
    }

    if (prtCoverTable)
	printer_mib_free_prtCoverTable(prtCoverTable);

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
    xml_set_prop(tree, "printer", "%d",
		 prtInputEntry->hrDeviceIndex);
    xml_set_prop(tree, " number", "%d",
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
	xml_set_prop(node, "unit", "%s", e);
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
	xml_set_prop(node, "unit", "%s", e);
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
		xml_printer_inputs(interp->xml_node, prtInputTable[i]);
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
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_printer_outputs(interp->result, prtOutputTable[i]);
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
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_printer_marker(interp->result, prtMarkerTable[i]);
	}
    }

    if (prtMarkerTable) printer_mib_free_prtMarkerTable(prtMarkerTable);
	
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
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_printer_supplies(interp->result, prtMarkerSuppliesTable[i]);
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



static int
show_printer_interpreter(scli_interp_t * interp, int argc, char **argv)
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
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_printer_interpreter(interp->result, interpTable[i]);
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

    /*
      prtChannelState
      prtChannelIfIndex
    */

    
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



static int
show_printer_channels(scli_interp_t * interp, int argc, char **argv)
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
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_printer_channel(interp->result, channelTable[i], interpTable);
	}
    }

    if (channelTable)
	printer_mib_free_prtChannelTable(channelTable);
    if (interpTable)
	printer_mib_free_prtInterpreterTable(interpTable);
	
    return SCLI_OK;
}



static void
fmt_printer_console_display(GString *s,
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
xml_printer_console_display(xmlNodePtr root,
		    printer_mib_prtConsoleDisplayBufferEntry_t *displayEntry)
{
    xmlNodePtr tree;

    if (displayEntry->prtConsoleDisplayBufferText) {
	tree = xmlNewChild(root, NULL, "line", NULL);
	xml_set_prop(tree, "printer", "%d",
		     displayEntry->hrDeviceIndex);
	xml_set_prop(tree, " number", "%d",
		     displayEntry->prtConsoleDisplayBufferIndex);
	xml_set_content(tree, "%.*s", 
		  (int) displayEntry->_prtConsoleDisplayBufferTextLength,
			displayEntry->prtConsoleDisplayBufferText);
    }
}



static int
show_printer_console_display(scli_interp_t * interp, int argc, char **argv)
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
		xml_printer_console_display(interp->xml_node,
					    displayTable[i]);
	    } else {
		fmt_printer_console_display(interp->result,
					    displayTable[i]);
	    }
	}
    }

    if (displayTable)
	printer_mib_free_prtConsoleDisplayBufferTable(displayTable);

    return SCLI_OK;
}



static void
fmt_printer_console_light(GString *s,
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
xml_printer_console_light(xmlNodePtr root,
		  printer_mib_prtConsoleLightEntry_t *lightEntry)
{
    xmlNodePtr tree;
    const char *state = "off";
    const char *e;
    
    tree = xmlNewChild(root, NULL, "light", NULL);
    xml_set_prop(tree, "printer", "%d", lightEntry->hrDeviceIndex);
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
show_printer_console_lights(scli_interp_t *interp, int argc, char **argv)
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
		xml_printer_console_light(interp->xml_node, lightTable[i]);
	    } else {
		fmt_printer_console_light(interp->result, lightTable[i],
					  light_width);
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
    xml_set_prop(tree, "printer", "%d", alertEntry->hrDeviceIndex);
    xml_set_prop(tree, " number", "%d", alertEntry->prtAlertIndex);

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
show_printer_alert(scli_interp_t * interp, int argc, char **argv)
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
		xml_printer_alert(interp->xml_node, alertTable[i]);
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
scli_init_printer_mode(scli_interp_t * interp)
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
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_info },

	{ "show printer covers", NULL,
	  "The `show printer covers' command shows information about the\n"
	  "covers of a printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_covers },

	{ "show printer inputs", NULL,
	  "The `show printer inputs' command shows information about the\n"
	  "input sub-units of a printer which provide media for input to\n"
	  "the printing process.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "printer inputs",
	  NULL,
	  show_printer_inputs },

	{ "show printer outputs", NULL,
	  "The `show printer output' command shows information about the\n"
	  "output sub-units of a printer capable of receiving media\n"
	  "delivered from the printing process.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_outputs },

	{ "show printer markers", NULL,
	  "The `show printer markers' command shows information about the\n"
	  "marker sub-units of a printer which produce marks on the print\n"
	  "media.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_markers },

	{ "show printer supplies", NULL,
	  "The `show printer supplies' command shows information about the\n"
	  "supplies which are consumed and the waste produced by the\n"
	  "markers of a printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_supplies },

	{ "show printer interpreter", NULL,
	  "The `show printer interpreter' command shows information about\n"
	  "the page description language and control language interpreters\n"
	  "supported by the printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_interpreter },

	{ "show printer channels", NULL,
	  "The `show printer channels' command shows information about\n"
	  "the channels which can be used to submit data to the printer.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_channels },
	
	{ "show printer console display", NULL,
	  "The `show printer console display' command shows the current\n"
	  "contents of the display attached to the printer. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  PRINTER logical printer number\n"
	  "  LINE    display line number\n"
	  "  TEXT    contents of the display line",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "printer console display",
	  NULL,
	  show_printer_console_display },

	{ "show printer console lights", NULL,
	  "The `show printer console lights' command shows the current\n"
	  "status of the lights attached to the printer. The command\n"
	  "generates a table with the following columns:\n"
	  "\n"
	  "  PRINTER     logical printer number\n"
	  "  LIGHT       number identifying the light/led\n"
	  "  DESCRIPTION description of the light/led\n"
	  "  STATUS      current status (on, off, blink)\n"
	  "  COLOR       current color of the light",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "printer console lights",
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
	  show_printer_console_lights },

	{ "show printer alerts", NULL,
	  "The `show printer alerts' command displays the list of active\n"
	  "printer alerts including the alert code, the alert severity,\n"
	  "the alert description, the alert time, the alert location and\n"
	  "the personel required to handle the alert.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML | SCLI_CMD_FLAG_DRY,
	  "printer",
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

	{ "monitor printer console display", NULL,
	  "The `monitor printer console display' command shows the same\n"
          "information as the show printer console display command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_console_display },

	{ "monitor printer console lights", NULL,
	  "The `monitor printer console lights' command shows the same\n"
	  "information as the show printer console lights command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR | SCLI_CMD_FLAG_DRY,
	  NULL, NULL,
	  show_printer_console_lights },

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
