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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "scli.h"

#include "printer-mib.h"


static void
misc_printer_printInputDimension(GString *s, gint32 * dim)
{
    if (dim) {
	fmt_enum(s, 22, printer_mib_enums_prtInputDimUnit, dim);
    }
}


static int
cmd_printer_info(scli_interp_t * interp, int argc, char **argv)
{
    printer_mib_prtGeneralEntry_t **prtGeneralTable = NULL;
    printer_mib_prtLocalizationEntry_t **prtLocalTable = NULL;
    int i, j;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (printer_mib_get_prtGeneralTable(interp->peer, &prtGeneralTable)) {
	return SCLI_ERROR;
    }

    printer_mib_get_prtLocalizationTable(interp->peer, &prtLocalTable);

    if (prtGeneralTable) {
	for (i = 0; prtGeneralTable[i]; i++) {

	    /* MISSING: prtGeneralCurrentLocalization */
	    /* MISSING: prtAuxiliarySheetStartupPage */
	    /* MISSING: prtAuxiliarySheetBannerPage */
	    /* Write-only-variable: prtGeneralReset */

	    if (prtGeneralTable[i]->prtGeneralPrinterName) {
		g_string_sprintfa(interp->result, "Printer name:     %.*s\n",
				  (int) prtGeneralTable [i]->
				  _prtGeneralPrinterNameLength,
				  prtGeneralTable[i]->prtGeneralPrinterName);
	    }

	    if (prtGeneralTable[i]->prtGeneralSerialNumber) {
		g_string_sprintfa(interp->result, "Serial number:    %.*s\n",
				  (int) prtGeneralTable [i]->
				  _prtGeneralSerialNumberLength,
				  prtGeneralTable[i]->prtGeneralSerialNumber);
	    }

	    if (prtGeneralTable[i]->prtGeneralCurrentOperator) {
		g_string_sprintfa(interp->result, "Current Operator: %.*s\n",
				  (int) prtGeneralTable [i]->
				  _prtGeneralCurrentOperatorLength,
				  prtGeneralTable[i]
				  ->prtGeneralCurrentOperator);
	    }

	    if (prtGeneralTable[i]->prtGeneralServicePerson) {
		g_string_sprintfa(interp->result, "Service Person:   %.*s\n",
				  (int) prtGeneralTable [i]->
				  _prtGeneralServicePersonLength,
				  prtGeneralTable[i]->
				  prtGeneralServicePerson);
	    }

	    if (prtGeneralTable[i]->prtConsoleNumberOfDisplayLines &&
		prtGeneralTable[i]->prtConsoleNumberOfDisplayChars) {
		g_string_sprintfa(interp->result,
				  "Display:          %u line(s) a %u chars\n",
				  *prtGeneralTable[i]->
				  prtConsoleNumberOfDisplayLines,
				  *prtGeneralTable[i]->
				  prtConsoleNumberOfDisplayChars);
	    }

	    if (prtGeneralTable[i]->prtConsoleLocalization &&
		prtLocalTable &&
		prtLocalTable[*prtGeneralTable[i]->prtConsoleLocalization]) {
		j = *prtGeneralTable[i]->prtConsoleLocalization - 1;
		g_string_sprintfa(interp->result,
				  "Console Language: %.*s/%.*s\n",
		  (int) prtLocalTable[j]->_prtLocalizationLanguageLength,
				  prtLocalTable[j]->prtLocalizationLanguage,
		  (int) prtLocalTable[j]->_prtLocalizationCountryLength,
				  prtLocalTable[j]->prtLocalizationCountry);
	    }

	    if (prtGeneralTable[i]->prtConsoleDisable) {
		g_string_append(interp->result, "Console access:   ");
		fmt_enum(interp->result, 8,
			 printer_mib_enums_prtConsoleDisable,
			 prtGeneralTable[i]->prtConsoleDisable);
		g_string_append(interp->result, "\n");
	    }

	    g_string_append(interp->result, "Defaults:         ");
	    if (prtGeneralTable[i]->prtInputDefaultIndex) {
		switch (*prtGeneralTable[i]->prtInputDefaultIndex) {
		case -1:
		    g_string_append(interp->result, "No default input\n");
		    break;
		default:
		    g_string_sprintfa(interp->result,
				      "input #%u\n",
				      *prtGeneralTable[i]->
				      prtInputDefaultIndex);
		}
	    } 

	    if (prtGeneralTable[i]->prtOutputDefaultIndex) {
	        g_string_append(interp->result, "                  ");
		switch (*prtGeneralTable[i]->prtOutputDefaultIndex) {
		case -1:
		    g_string_append(interp->result, "no default output\n");
		    break;
		default:
		    g_string_sprintfa(interp->result,
				      "output #%u\n",
				      *prtGeneralTable[i]->
				      prtOutputDefaultIndex);
		}
	    }

	    if (prtGeneralTable[i]->prtMarkerDefaultIndex) {
		g_string_sprintfa(interp->result, 
				  "                  marker #%u\n",
				  *prtGeneralTable[i]->prtMarkerDefaultIndex);
	    }

	    if (prtGeneralTable[i]->prtMediaPathDefaultIndex) {
		g_string_sprintfa(interp->result, 
				  "                  media path #%u",
				  *prtGeneralTable[i]->
				  prtMediaPathDefaultIndex);
	    }
	    g_string_append(interp->result, "\n");

	    if (prtGeneralTable[i]->prtAlertAllEvents) {
		g_string_sprintfa(interp->result,
				  "Alerts total:          %u\n",
				  *prtGeneralTable[i]->prtAlertAllEvents);
	    }

	    if (prtGeneralTable[i]->prtAlertCriticalEvents) {
		g_string_sprintfa(interp->result,
				  "Critical alerts:       %u\n",
				  *prtGeneralTable[i]->
				  prtAlertCriticalEvents);
	    }

	    if (prtGeneralTable[i]->prtGeneralConfigChanges) {
		g_string_sprintfa(interp->result,
				  "Configuration changes: %u\n",
				  *prtGeneralTable [i]->
				  prtGeneralConfigChanges);
	    }

	}
	printer_mib_free_prtGeneralTable(prtGeneralTable);
    }

    if (prtLocalTable)
	printer_mib_free_prtLocalizationTable(prtLocalTable);

    return SCLI_OK;
}


static void
show_printer_alert(GString *s, printer_mib_prtAlertEntry_t *prtAlertEntry)
{
    if (prtAlertEntry->prtAlertTime) {
	g_string_append(s, "Date:        ");
	g_string_append(s, stls_fmt_timeticks(*prtAlertEntry->prtAlertTime));
	g_string_append(s, "\n");
    }

    if (prtAlertEntry->prtAlertSeverityLevel) {
	g_string_append(s, "Severity:    ");
	fmt_enum(s, 24,
		 printer_mib_enums_prtAlertSeverityLevel,
		 prtAlertEntry->prtAlertSeverityLevel);
	g_string_append(s, "\n");
    }

    if (prtAlertEntry->prtAlertDescription) {
	g_string_sprintfa(s, "Description: %.*s\n",
			  (int) prtAlertEntry->_prtAlertDescriptionLength,
			  prtAlertEntry->prtAlertDescription);
    }

    g_string_append(s, "Alert Code:  ");
    if (prtAlertEntry->prtAlertGroup) {
	fmt_enum(s, 1, printer_mib_enums_prtAlertGroup,
		 prtAlertEntry->prtAlertGroup);
    } else {
	g_string_append(s, "?");
    }

    if (prtAlertEntry->prtAlertGroupIndex) {
	if (*prtAlertEntry->prtAlertGroupIndex != -1)
	    g_string_sprintfa(s, " #%u",
			      *prtAlertEntry->prtAlertGroupIndex);
    }
    g_string_append(s, " / ");
    if (prtAlertEntry->prtAlertCode) {
	fmt_enum(s, 1, printer_mib_enums_prtAlertCode,
		 prtAlertEntry->prtAlertCode);
    } else {
	g_string_append(s, "?");
    }
    g_string_append(s, "\n");

    if (prtAlertEntry->prtAlertLocation) {
	g_string_sprintfa(s, "Location:    %u\n",
			  *prtAlertEntry->prtAlertLocation);
    }
    
    if (prtAlertEntry->prtAlertTrainingLevel) {
	g_string_append(s, "Personnel:   ");
	fmt_enum(s, 22,
		 printer_mib_enums_prtAlertTrainingLevel,
		 prtAlertEntry->prtAlertTrainingLevel);
	g_string_append(s, "\n");
    }
}


static int
cmd_printer_alert(scli_interp_t * interp, int argc, char **argv)
{
    printer_mib_prtAlertEntry_t **prtAlertTable = NULL;
    int i;

    g_return_val_if_fail(interp, SCLI_ERROR);

    if (printer_mib_get_prtAlertTable(interp->peer, &prtAlertTable)) {
	return SCLI_ERROR;
    }

    if (prtAlertTable) {
	for (i = 0; prtAlertTable[i]; i++) {
	    if (i > 0) {
		g_string_append(interp->result, "\n");
	    }
	    show_printer_alert(interp->result, prtAlertTable[i]);
	}
    }

    if (prtAlertTable) printer_mib_free_prtAlertTable(prtAlertTable);
    
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
	fmt_enum(s, 30, printer_mib_enums_prtInputType,
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
	fmt_enum(s, 1,
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
	fmt_enum(s, 10,
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

    if (printer_mib_get_prtInputTable(interp->peer, &prtInputTable)) {
	return SCLI_ERROR;
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


void
scli_init_printer_mode(scli_interp_t * interp)
{
    static scli_cmd_t cmds[] = {
	{ "show printer info",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "general printer information",
	  cmd_printer_info },
	{ "show printer alerts",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "printer alert information",
	  cmd_printer_alert },
	{ "show printer inputs",
	  SCLI_CMD_FLAG_NEED_PEER,
	  "printer input information",
	  cmd_printer_inputs },
	{ NULL, 0, NULL, NULL }
    };

    static scli_mode_t printer_mode = {
	"pinter",
	"scli mode to display and configure printers",
	cmds
    };

    scli_register_mode(interp, &printer_mode);
}
