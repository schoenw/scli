/* 
 * fmt.c -- stop formatting utilities used by many stop modes
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

#include "stop.h"



char const *
fmt_seconds(guint32 number)
{
    static char buffer[80];
    guint32 sec, min, hour;

    sec  = (number) % 60;
    min  = (number / 60) % 60;
    hour = (number / 60 / 60);

    g_snprintf(buffer, sizeof(buffer), "%2d:%02d:%02d", hour, min, sec);

#if 0
    if (number > 99900) {
      g_snprintf(buffer, sizeof(buffer), "%3dh", number / 3600 / 100);
    } else if (number > 5900) {
      g_snprintf(buffer, sizeof(buffer), "%3dm", number / 60 / 100);
    } else if (number < 100) {
      g_snprintf(buffer, sizeof(buffer), ".%02ds", number);
    } else if (number < 1000) {
      g_snprintf(buffer, sizeof(buffer), "%3.1fs", number / 100.0);
    } else {
      g_snprintf(buffer, sizeof(buffer), "%3ds", number / 100);
    }
#endif
    return buffer;
}
