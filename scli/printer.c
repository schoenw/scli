/* 
 * printer.c -- scli printer mode implementation
 *
 * Copyright (C) 2001 Oliver Wellnitz, Juergen Schoenwaelder
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
	return 0;
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

    

static void
misc_printer_printInputDimension(GString *s, gint32 * dim)
{
    if (dim) {
	xxx_enum(s, 22, printer_mib_enums_prtInputDimUnit, dim);
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
	
    if (hrDeviceEntry && hrDeviceEntry->hrDeviceStatus) {
	g_string_sprintfa(s, "%-*s ", indent, "Device Status:");
	xxx_enum(s, 0, host_resources_mib_enums_hrDeviceStatus,
		 hrDeviceEntry->hrDeviceStatus);
	g_string_append(s, "\n");
    }
    
    if (hrPrinterEntry->hrPrinterStatus) {
	g_string_sprintfa(s, "%-*s ", indent, "Printer Status:");
	xxx_enum(s, 0, host_resources_mib_enums_hrPrinterStatus,
		 hrPrinterEntry->hrPrinterStatus);
	g_string_append(s, "\n");
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
    
    g_string_sprintfa(s, "%-*s ", indent, "Defaults:");
    if (prtGeneralEntry->prtInputDefaultIndex) {
	switch (*prtGeneralEntry->prtInputDefaultIndex) {
	case -1:
	    g_string_append(s, "No default input\n");
	    break;
	default:
	    g_string_sprintfa(s, "input #%u\n",
			      *prtGeneralEntry->prtInputDefaultIndex);
	}
    } 
    
    if (prtGeneralEntry->prtOutputDefaultIndex) {
	g_string_sprintfa(s, "%-*s ", indent, "");
	switch (*prtGeneralEntry->prtOutputDefaultIndex) {
	case -1:
	    g_string_append(s, "no default output\n");
	    break;
	default:
	    g_string_sprintfa(s, "output #%u\n",
			      *prtGeneralEntry->prtOutputDefaultIndex);
	}
    }
    
    if (prtGeneralEntry->prtMarkerDefaultIndex) {
	g_string_sprintfa(s, "%-*s marker #%u\n", indent, "",
			  *prtGeneralEntry->prtMarkerDefaultIndex);
    }
    
    if (prtGeneralEntry->prtMediaPathDefaultIndex) {
	g_string_sprintfa(s, "%-*s media path #%u", indent, "",
			  *prtGeneralEntry->prtMediaPathDefaultIndex);
    }
    g_string_append(s, "\n");
    
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
show_printer_inputs(GString *s, printer_mib_prtInputEntry_t *prtInputEntry)
{
    if (prtInputEntry->prtInputIndex) {
	g_string_sprintfa(s, "Input #%u\n", prtInputEntry->prtInputIndex);
    }
    
    if (prtInputEntry->prtInputName &&
	prtInputEntry->_prtInputNameLength > 0) {
	g_string_sprintfa(s, "Name:        %.*s\n",
			  (int) prtInputEntry->_prtInputNameLength,
			  prtInputEntry->prtInputName);
    }

    if (prtInputEntry->prtInputDescription &&
	prtInputEntry->_prtInputDescriptionLength > 0) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) prtInputEntry->_prtInputDescriptionLength,
			  prtInputEntry->prtInputDescription);
    }

    if (prtInputEntry->prtInputVendorName &&
	prtInputEntry->_prtInputVendorNameLength > 0) {
	g_string_sprintfa(s, "Vendor:      %.*s\n",
			  (int) prtInputEntry->_prtInputVendorNameLength,
			  prtInputEntry->prtInputVendorName);
    }
    
    if (prtInputEntry->prtInputType) {
	g_string_append(s, "Type:        ");
	xxx_enum(s, 30, printer_mib_enums_prtInputType,
		 prtInputEntry->prtInputType);
	g_string_append(s, "\n");
    }
    
    if (prtInputEntry->prtInputModel &&
	prtInputEntry->_prtInputModelLength > 0) {
	g_string_sprintfa(s, "Model:       %.*s\n",
			  (int) prtInputEntry->_prtInputModelLength,
			  prtInputEntry->prtInputModel);
    }

    g_string_append(s, "Capacity:    ");
    if (prtInputEntry->prtInputCurrentLevel) {
	switch (*prtInputEntry->prtInputCurrentLevel) {
	case -1:
	    g_string_append(s, "other ");
	    break;
	case -2:
	    g_string_append(s, "unknown ");
	    break;
	case -3:
	    g_string_append(s, ">0 ");
	    break;
	default:
	    g_string_sprintfa(s, "%u ", *prtInputEntry->prtInputCurrentLevel);
	}
    } else {
	g_string_append(s, "?");
    }

    if (prtInputEntry->prtInputCapacityUnit) {
	xxx_enum(s, 1,
		 printer_mib_enums_prtInputCapacityUnit,
		 prtInputEntry->prtInputCapacityUnit);
    } else {
	g_string_append(s, "?");
    }

    if (prtInputEntry->prtInputMaxCapacity) {
	g_string_append(s, " (max ");
	switch ((long int) *prtInputEntry->prtInputMaxCapacity) {
	case -1:
	    g_string_append(s, "other)");
	    break;
	case -2:
	    g_string_append(s, "unknown)");
	    break;
	default:
	    g_string_sprintfa(s, "%u)",
			      *prtInputEntry->prtInputMaxCapacity);
	}
    }
    g_string_append(s, "\n");

    if (prtInputEntry->prtInputNextIndex) {
	g_string_append(s, "Next Input: ");
	switch (*prtInputEntry->prtInputNextIndex) {
	case 0:
	    g_string_append(s, "No next unit");
	    break;
	case -1:
	    g_string_append(s, "other");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	case -3:
	    g_string_append(s, "No input switching");
	    break;
	default:
	    g_string_sprintfa(s, "input #%u",
			      *prtInputEntry->prtInputNextIndex);
	}
	g_string_append(s, "\n");
    }

    if (prtInputEntry->prtInputStatus) {
	g_string_append(s, "Status:      ");
	switch (*prtInputEntry->prtInputStatus & 7) {
	case 0:
	    g_string_append(s, "Available and Idle");
	    break;
	case 1:
	    g_string_append(s,
			    "Unavailable and OnRequest");
	    break;
	case 2:
	    g_string_append(s, "Available and Standby");
	    break;
	case 3:
	    g_string_append(s,
			    "Unavailable because Broken");
	    break;
	case 4:
	    g_string_append(s, "Available and Active");
	    break;
	case 5:
	    g_string_append(s, "Unknown");
	    break;
	case 6:
	    g_string_append(s, "Available and Busy");
	    break;
	default:
	    g_string_append(s, "?");
	    break;
	}
	if (*prtInputEntry->prtInputStatus & 8) {
	    g_string_append(s, ", Non-Critical Alerts");
	}
	if (*prtInputEntry->prtInputStatus & 16) {
	    g_string_append(s, ", Critical Alerts");
	}
	if (*prtInputEntry->prtInputStatus & 32) {
	    g_string_append(s, ", Offline");
	}
	if (*prtInputEntry->prtInputStatus & 64) {
	    g_string_append(s, ", Transitioning");
	}
	g_string_append(s, "\n");
    }
    
    if (prtInputEntry->prtInputSerialNumber &&
	prtInputEntry->_prtInputSerialNumberLength > 0) {
	g_string_sprintfa(s, "Serial number: %.*s\n",
			  (int) prtInputEntry->_prtInputSerialNumberLength,
			  prtInputEntry->prtInputSerialNumber);
    }
    
    if (prtInputEntry->prtInputVersion &&
	prtInputEntry->_prtInputVersionLength > 0) {
	g_string_sprintfa(s, "Input version: %.*s\n",
			  (int) prtInputEntry->_prtInputVersionLength,
			  prtInputEntry->prtInputVersion);
    }
    
    g_string_append(s, "Security:    ");
    if (prtInputEntry->prtInputSecurity) {
	xxx_enum(s, 10,
		 printer_mib_enums_prtOutputSecurity,
		 prtInputEntry->prtInputSecurity);
    }
    else {
	g_string_append(s, "?");
    }
    g_string_append(s, "\n");

    if (prtInputEntry->prtInputMediaName &&
	prtInputEntry->_prtInputMediaNameLength > 0) {
	g_string_sprintfa(s, "Media name:  %.*s\n",
			  (int) prtInputEntry->_prtInputMediaNameLength,
			  prtInputEntry->prtInputMediaName);
    }
    
    if (prtInputEntry->prtInputMediaType &&
	prtInputEntry->_prtInputMediaTypeLength > 0) {
	g_string_sprintfa(s, "Media type:   %.*s\n",
			  (int) prtInputEntry->_prtInputMediaTypeLength,
			  prtInputEntry->prtInputMediaType);
    }
    
    if (prtInputEntry->prtInputMediaWeight) {
	g_string_append(s, "Media weight: ");
	switch ((long int) *prtInputEntry->prtInputMaxCapacity) {
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
	g_string_sprintfa(s, "Media color:  %.*s\n",
			  (int) prtInputEntry->_prtInputMediaColorLength,
			  prtInputEntry->prtInputMediaColor);
    }
    
    if (prtInputEntry->prtInputMediaFormParts) {
	g_string_append(s, "Media parts: ");
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

    if (prtInputEntry->prtInputMediaDimFeedDirDeclared ||
	prtInputEntry->prtInputMediaDimXFeedDirDeclared) {
	g_string_append(s, "Declared media dimensions: ");
	if (prtInputEntry->prtInputMediaDimFeedDirDeclared) {
	    switch (*prtInputEntry->prtInputMediaDimFeedDirDeclared) {
	    case -1:
		g_string_append(s, "other");
		break;
	    default:
		g_string_sprintfa(s, "%u ",
			  *prtInputEntry->prtInputMediaDimFeedDirDeclared);
	    }
	}
	else {
	    g_string_append(s, "?");
	}
	
	if (prtInputEntry->prtInputMediaDimXFeedDirDeclared) {
	    g_string_append(s, "x ");
	    switch (*prtInputEntry->prtInputMediaDimXFeedDirDeclared) {
	    case -1:
		g_string_append(s, "other");
		break;
	    case -2:
		g_string_append(s, "unknown");
		break;
	    default:
		g_string_sprintfa(s, "%u ",
			  *prtInputEntry->prtInputMediaDimXFeedDirDeclared);
	    }
	} else {
	    g_string_append(s, "?");
	}
	misc_printer_printInputDimension(s, prtInputEntry->prtInputDimUnit);
	g_string_append(s, "\n");
    }
    
    if (prtInputEntry->prtInputMediaDimFeedDirChosen ||
	prtInputEntry->prtInputMediaDimXFeedDirChosen) {
	g_string_append(s,
			"Chosen media dimensions:   ");
	if (prtInputEntry->prtInputMediaDimFeedDirChosen) {
	    switch (*prtInputEntry->prtInputMediaDimFeedDirChosen) {
	    case -1:
		g_string_append(s, "other");
		break;
	    case -2:
		g_string_append(s, "unknown");
		break;
	    default:
		g_string_sprintfa(s, "%u ",
			  *prtInputEntry->prtInputMediaDimFeedDirChosen);
	    }
	}
	else {
	    g_string_append(s, "?");
	}
	
	if (prtInputEntry->prtInputMediaDimXFeedDirChosen) {
	    g_string_append(s, "x ");
	    switch (*prtInputEntry->prtInputMediaDimXFeedDirChosen) {
	    case -1:
		g_string_append(s, "other");
		break;
	    case -2:
		g_string_append(s, "unknown");
		break;
	    default:
		g_string_sprintfa(s, "%u ",
			  *prtInputEntry->prtInputMediaDimXFeedDirChosen);
	    }
	} else {
	    g_string_append(s, "?");
	}
	misc_printer_printInputDimension(s, prtInputEntry->prtInputDimUnit);
	g_string_append(s, "\n");
    }
    
    if (prtInputEntry->prtInputMediaLoadTimeout) {
	g_string_append(s, "Media load timeout: ");
	switch (*prtInputEntry->prtInputMediaLoadTimeout) {
	case -1:
	    g_string_append(s, "wait forever");
	    break;
	case -2:
	    g_string_append(s, "unknown");
	    break;
	default:
	    g_string_sprintfa(s,
			      "prtInputMediaLoadTimeout: %u",
			      *prtInputEntry->prtInputMediaLoadTimeout);
	}
	g_string_append(s, "\n");
    }
}



static int
cmd_printer_inputs(scli_interp_t * interp, int argc, char **argv)
{
    printer_mib_prtInputEntry_t **prtInputTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    printer_mib_get_prtInputTable(interp->peer, &prtInputTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtInputTable) {
	for (i = 0; prtInputTable[i]; i++) {
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    show_printer_inputs(interp->result, prtInputTable[i]);
	}
    }

    if (prtInputTable) printer_mib_free_prtInputTable(prtInputTable);
	
    return SCLI_OK;
}



static void
fmt_printer_interpreter(GString *s,
			printer_mib_prtInterpreterEntry_t *prtInterpEntry)
{
    int const indent = 14;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtInterpEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %d\n", indent, "Interpreter:",
		      prtInterpEntry->prtInterpreterIndex);

    e = fmt_enum(printer_mib_enums_prtInterpreterLangFamily,
		 prtInterpEntry->prtInterpreterLangFamily);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Language:", e);
    }

    fmt_display_string(s, indent+1, "Description:",
		       (int) prtInterpEntry->_prtInterpreterDescriptionLength,
		       prtInterpEntry->prtInterpreterDescription);

    fmt_display_string(s, indent+1, "Version:",
		       (int) prtInterpEntry->_prtInterpreterVersionLength,
		       prtInterpEntry->prtInterpreterVersion);
}



static int
show_printer_interpreter(scli_interp_t * interp, int argc, char **argv)
{
    printer_mib_prtInterpreterEntry_t **prtInterpreterTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    printer_mib_get_prtInterpreterTable(interp->peer, &prtInterpreterTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtInterpreterTable) {
	for (i = 0; prtInterpreterTable[i]; i++) {
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    fmt_printer_interpreter(interp->result, prtInterpreterTable[i]);
	}
    }

    if (prtInterpreterTable)
	printer_mib_free_prtInterpreterTable(prtInterpreterTable);
	
    return SCLI_OK;
}



static void
fmt_printer_console_display(GString *s,
	    printer_mib_prtConsoleDisplayBufferEntry_t *prtConsoleDisplayEntry)
{
    g_string_sprintfa(s, "%6d  ", prtConsoleDisplayEntry->hrDeviceIndex);
		      
    g_string_sprintfa(s, "%4d   ",
		      prtConsoleDisplayEntry->prtConsoleDisplayBufferIndex);
	
    if (prtConsoleDisplayEntry->prtConsoleDisplayBufferText) {
	g_string_sprintfa(s, "%.*s\n",
	    (int) prtConsoleDisplayEntry->_prtConsoleDisplayBufferTextLength,
		  prtConsoleDisplayEntry->prtConsoleDisplayBufferText);
    }
}



static void
xml_printer_console_display(xmlNodePtr root,
		    printer_mib_prtConsoleDisplayBufferEntry_t *prtConsoleDisplayEntry)
{
    xmlNodePtr tree;

    if (prtConsoleDisplayEntry->prtConsoleDisplayBufferText) {
	tree = xmlNewChild(root, NULL, "line", NULL);
	xml_set_prop(tree, "printer", "%d",
		     prtConsoleDisplayEntry->hrDeviceIndex);
	xml_set_prop(tree, " number", "%d",
		     prtConsoleDisplayEntry->prtConsoleDisplayBufferIndex);
	xml_set_content(tree, "%.*s", 
		  (int) prtConsoleDisplayEntry->_prtConsoleDisplayBufferTextLength,
			prtConsoleDisplayEntry->prtConsoleDisplayBufferText);
    }
}



static int
show_printer_console_display(scli_interp_t * interp, int argc, char **argv)
{
    printer_mib_prtConsoleDisplayBufferEntry_t **prtConsoleDisplayTable;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    printer_mib_get_prtConsoleDisplayBufferTable(interp->peer,
						 &prtConsoleDisplayTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtConsoleDisplayTable) {
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "PRINTER LINE   TEXT");
	}
	for (i = 0; prtConsoleDisplayTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_printer_console_display(interp->xml_node,
					    prtConsoleDisplayTable[i]);
	    } else {
		fmt_printer_console_display(interp->result,
					    prtConsoleDisplayTable[i]);
	    }
	}
    }

    if (prtConsoleDisplayTable)
	printer_mib_free_prtConsoleDisplayBufferTable(prtConsoleDisplayTable);

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
		  printer_mib_prtConsoleLightEntry_t *prtConsoleLightEntry)
{
    xmlNodePtr tree;
    const char *state = "off";
    const char *e;
    
    tree = xmlNewChild(root, NULL, "light", NULL);
    xml_set_prop(tree, "printer", "%d", prtConsoleLightEntry->hrDeviceIndex);
    xml_set_prop(tree, "number", "%d", prtConsoleLightEntry->prtConsoleLightIndex);

    if (prtConsoleLightEntry->prtConsoleDescription) {
	(void) xml_new_child(tree, NULL, "description", "%.*s",
		       (int) prtConsoleLightEntry->_prtConsoleDescriptionLength,
			     prtConsoleLightEntry->prtConsoleDescription);
    }

    e = fmt_enum(printer_mib_enums_prtConsoleColor,
		 prtConsoleLightEntry->prtConsoleColor);
    if (e) {
	xml_new_child(tree, NULL, "color", e);
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
    xml_new_child(tree, NULL, "status", state);
}



static int
show_printer_console_lights(scli_interp_t * interp, int argc, char **argv)
{
    printer_mib_prtConsoleLightEntry_t **prtConsoleLightTable;
    int i;
    int light_width = 12;

    g_return_val_if_fail(interp, SCLI_ERROR);

    printer_mib_get_prtConsoleLightTable(interp->peer,
					 &prtConsoleLightTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtConsoleLightTable) {
	for (i = 0; prtConsoleLightTable[i]; i++) {
	    if (prtConsoleLightTable[i]->_prtConsoleDescriptionLength > light_width) {
		light_width = prtConsoleLightTable[i]->_prtConsoleDescriptionLength;
	    }
	}
	if (! scli_interp_xml(interp)) {
	    g_string_sprintfa(interp->header, "PRINTER LIGHT %-*s STATUS COLOR",
			      light_width, "DESCRIPTION");
	}
	for (i = 0; prtConsoleLightTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_printer_console_light(interp->xml_node, prtConsoleLightTable[i]);
	    } else {
		fmt_printer_console_light(interp->result, prtConsoleLightTable[i],
					  light_width);
	    }
	}
    }

    if (prtConsoleLightTable)
	printer_mib_free_prtConsoleLightTable(prtConsoleLightTable);
	
    return SCLI_OK;
}



static void
fmt_printer_alert(GString *s, printer_mib_prtAlertEntry_t *prtAlertEntry)
{
    int const indent = 14;
    const char *e;

    g_string_sprintfa(s, "%-*s %d\n", indent, "Printer:",
		      prtAlertEntry->hrDeviceIndex);

    g_string_sprintfa(s, "%-*s %d\n", indent, "Alert:",
		      prtAlertEntry->prtAlertIndex);

    if (prtAlertEntry->prtAlertTime) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Date:",
			  fmt_timeticks(*prtAlertEntry->prtAlertTime));
    }

    e = fmt_enum(printer_mib_enums_prtAlertCode,
		 prtAlertEntry->prtAlertCode);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Code:", e);
    }

    e = fmt_enum(printer_mib_enums_prtAlertSeverityLevel,
		 prtAlertEntry->prtAlertSeverityLevel);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Severity:", e);
    }

    fmt_display_string(s, indent+1, "Description:",
		       (int) prtAlertEntry->_prtAlertDescriptionLength,
		       prtAlertEntry->prtAlertDescription);

    e = fmt_enum(prtAlertGroup, prtAlertEntry->prtAlertGroup);
    if (e) {
	g_string_sprintfa(s, "%-*s %s", indent, "Location:", e);
	if (prtAlertEntry->prtAlertGroupIndex
	    && *prtAlertEntry->prtAlertGroupIndex > 0) {
	    g_string_sprintfa(s, " #%u", *prtAlertEntry->prtAlertGroupIndex);
	}
	if (prtAlertEntry->prtAlertLocation
	    && *prtAlertEntry->prtAlertLocation > 0) {
	    g_string_sprintfa(s, " (at location %u)", *prtAlertEntry->prtAlertLocation);
	}
	g_string_append(s, "\n");
    }

    e = fmt_enum(printer_mib_enums_prtAlertTrainingLevel,
		 prtAlertEntry->prtAlertTrainingLevel);
    if (e) {
	g_string_sprintfa(s, "%-*s %s\n", indent, "Personnel:", e);
    }
}



static void
xml_printer_alert(xmlNodePtr root, printer_mib_prtAlertEntry_t *prtAlertEntry)
{
    xmlNodePtr tree;
    const char *e;

    tree = xmlNewChild(root, NULL, "alert", NULL);
    xml_set_prop(tree, "printer", "%d", prtAlertEntry->hrDeviceIndex);
    xml_set_prop(tree, " number", "%d", prtAlertEntry->prtAlertIndex);

    if (prtAlertEntry->prtAlertTime) {
	xml_new_child(tree, NULL, "date",
		      fmt_timeticks(*prtAlertEntry->prtAlertTime));
    }

    e = fmt_enum(printer_mib_enums_prtAlertCode,
		 prtAlertEntry->prtAlertCode);
    if (e) {
	xml_new_child(tree, NULL, "code", e);
    }

    e = fmt_enum(printer_mib_enums_prtAlertSeverityLevel,
		 prtAlertEntry->prtAlertSeverityLevel);
    if (e) {
	xml_new_child(tree, NULL, "severity", e);
    }

    if (prtAlertEntry->prtAlertDescription) {
	xml_new_child(tree, NULL, "description", "%.*s",
		(int) prtAlertEntry->_prtAlertDescriptionLength,
		      prtAlertEntry->prtAlertDescription);
    }

    e = fmt_enum(prtAlertGroup, prtAlertEntry->prtAlertGroup);
    if (e) {
	GString *s = g_string_new(e);
	if (prtAlertEntry->prtAlertGroupIndex
	    && *prtAlertEntry->prtAlertGroupIndex > 0) {
	    g_string_sprintfa(s, " #%u", *prtAlertEntry->prtAlertGroupIndex);
	}
	if (prtAlertEntry->prtAlertLocation
	    && *prtAlertEntry->prtAlertLocation > 0) {
	    g_string_sprintfa(s, " (at location %u)", *prtAlertEntry->prtAlertLocation);
	}
	xml_new_child(tree, NULL, "location", s->str);
	g_string_free(s, 1);
    }

    e = fmt_enum(printer_mib_enums_prtAlertTrainingLevel,
		 prtAlertEntry->prtAlertTrainingLevel);
    if (e) {
	xml_new_child(tree, NULL, "personnel", "%s", e);
    }
}



static int
show_printer_alert(scli_interp_t * interp, int argc, char **argv)
{
    printer_mib_prtAlertEntry_t **prtAlertTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    printer_mib_get_prtAlertTable(interp->peer, &prtAlertTable, 0);
    if (interp->peer->error_status) {
	return SCLI_SNMP;
    }

    if (prtAlertTable) {
	for (i = 0; prtAlertTable[i]; i++) {
	    if (scli_interp_xml(interp)) {
		xml_printer_alert(interp->xml_node, prtAlertTable[i]);
	    } else {
		if (i > 0) {
		    g_string_append(interp->result, "\n");
		}
		fmt_printer_alert(interp->result, prtAlertTable[i]);
	    }
	}
    }

    if (prtAlertTable) printer_mib_free_prtAlertTable(prtAlertTable);
    
    return SCLI_OK;
}



void
scli_init_printer_mode(scli_interp_t * interp)
{
    static scli_cmd_t cmds[] = {

	{ "show printer info", NULL,
	  "general printer information",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_printer_info },

	{ "show printer inputs", NULL,
	  "printer input information",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  cmd_printer_inputs },

	{ "show printer interpreter", NULL,
	  "The show printer interpreter command shows information about\n"
	  "the page description language and control language interpreters\n"
	  "supported by the printer.",
	  SCLI_CMD_FLAG_NEED_PEER,
	  NULL, NULL,
	  show_printer_interpreter },

	{ "show printer console display", NULL,
	  "The show printer console display command shows the current\n"
	  "contents of the printer's display. The command generates a\n"
	  "table with the following columns:\n"
	  "\n"
	  "  PRINTER logical printer number\n"
	  "  LINE    display line number\n"
	  "  TEXT    contents of the display line",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "printer console",
	  NULL,
	  show_printer_console_display },

	{ "show printer console lights", NULL,
	  "The show printer console lights command shows the current\n"
	  "status of the printers lights. The command generates a table\n"
	  "with the following columns:\n"
	  "\n"
	  "  PRINTER     logical printer number\n"
	  "  LIGHT       number identifying the light/led\n"
	  "  DESCRIPTION description of the light/led\n"
	  "  STATUS      current status (on, off, blink)\n"
	  "  COLOR       current color of the light",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
	  "printer console",
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
	  "The show printer alerts command displays the list of active\n"
	  "printer alerts including the alert code, the alert severity,\n"
	  "the alert description, the alert time, the alert location and\n"
	  "the personel required to handle the alert.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_XML,
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
	  "The monitor printer console display command shows the same\n"
          "information as the show printer console display command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  show_printer_console_display },

	{ "monitor printer console lights", NULL,
	  "The monitor printer console lights command shows the same\n"
	  "information as the show printer console lights command. The\n"
	  "information is updated periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
	  NULL, NULL,
	  show_printer_console_lights },

	{ "monitor printer alerts", NULL,
	  "The monitor printer alerts command shows the same information\n"
	  "as the show printer alerts command. The information is updated\n"
	  "periodically.",
	  SCLI_CMD_FLAG_NEED_PEER | SCLI_CMD_FLAG_MONITOR,
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
