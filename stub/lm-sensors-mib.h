/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli LM-SENSORS-MIB
 *
 * Derived from LM-SENSORS-MIB:
 *   This MIB module defines objects for lm_sensor derived data.
 *
 * Revision 2000-11-05 00:00:
 *   Derived from DISKIO-MIB ex UCD.
 *
 * $Id$
 */

#ifndef _LM_SENSORS_MIB_H_
#define _LM_SENSORS_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * C type definitions for LM-SENSORS-MIB::lmTempSensorsEntry.
 */

#define LM_SENSORS_MIB_LMTEMPSENSORSINDEX  (1 << 0) 
#define LM_SENSORS_MIB_LMTEMPSENSORSDEVICE (1 << 1) 
#define LM_SENSORS_MIB_LMTEMPSENSORSVALUE  (1 << 2) 

typedef struct {
    gint32   lmTempSensorsIndex;       /* ro */
    guchar   *lmTempSensorsDevice;     /* ro SNMPv2-TC::DisplayString */
#define LM_SENSORS_MIB_LMTEMPSENSORSDEVICEMINLENGTH 0
#define LM_SENSORS_MIB_LMTEMPSENSORSDEVICEMAXLENGTH 255
    guint16  _lmTempSensorsDeviceLength;
    guint32  *lmTempSensorsValue;      /* ro SNMPv2-SMI::Gauge32 */
} lm_sensors_mib_lmTempSensorsEntry_t;

extern void
lm_sensors_mib_get_lmTempSensorsTable(GNetSnmp *s, lm_sensors_mib_lmTempSensorsEntry_t ***lmTempSensorsEntry, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmTempSensorsTable(lm_sensors_mib_lmTempSensorsEntry_t **lmTempSensorsEntry);

extern lm_sensors_mib_lmTempSensorsEntry_t *
lm_sensors_mib_new_lmTempSensorsEntry(void);

extern void
lm_sensors_mib_get_lmTempSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmTempSensorsEntry_t **lmTempSensorsEntry, gint32 lmTempSensorsIndex, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmTempSensorsEntry(lm_sensors_mib_lmTempSensorsEntry_t *lmTempSensorsEntry);

/*
 * C type definitions for LM-SENSORS-MIB::lmFanSensorsEntry.
 */

#define LM_SENSORS_MIB_LMFANSENSORSINDEX  (1 << 0) 
#define LM_SENSORS_MIB_LMFANSENSORSDEVICE (1 << 1) 
#define LM_SENSORS_MIB_LMFANSENSORSVALUE  (1 << 2) 

typedef struct {
    gint32   lmFanSensorsIndex;       /* ro */
    guchar   *lmFanSensorsDevice;     /* ro SNMPv2-TC::DisplayString */
#define LM_SENSORS_MIB_LMFANSENSORSDEVICEMINLENGTH 0
#define LM_SENSORS_MIB_LMFANSENSORSDEVICEMAXLENGTH 255
    guint16  _lmFanSensorsDeviceLength;
    guint32  *lmFanSensorsValue;      /* ro SNMPv2-SMI::Gauge32 */
} lm_sensors_mib_lmFanSensorsEntry_t;

extern void
lm_sensors_mib_get_lmFanSensorsTable(GNetSnmp *s, lm_sensors_mib_lmFanSensorsEntry_t ***lmFanSensorsEntry, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmFanSensorsTable(lm_sensors_mib_lmFanSensorsEntry_t **lmFanSensorsEntry);

extern lm_sensors_mib_lmFanSensorsEntry_t *
lm_sensors_mib_new_lmFanSensorsEntry(void);

extern void
lm_sensors_mib_get_lmFanSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmFanSensorsEntry_t **lmFanSensorsEntry, gint32 lmFanSensorsIndex, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmFanSensorsEntry(lm_sensors_mib_lmFanSensorsEntry_t *lmFanSensorsEntry);

/*
 * C type definitions for LM-SENSORS-MIB::lmVoltSensorsEntry.
 */

#define LM_SENSORS_MIB_LMVOLTSENSORSINDEX  (1 << 0) 
#define LM_SENSORS_MIB_LMVOLTSENSORSDEVICE (1 << 1) 
#define LM_SENSORS_MIB_LMVOLTSENSORSVALUE  (1 << 2) 

typedef struct {
    gint32   lmVoltSensorsIndex;       /* ro */
    guchar   *lmVoltSensorsDevice;     /* ro SNMPv2-TC::DisplayString */
#define LM_SENSORS_MIB_LMVOLTSENSORSDEVICEMINLENGTH 0
#define LM_SENSORS_MIB_LMVOLTSENSORSDEVICEMAXLENGTH 255
    guint16  _lmVoltSensorsDeviceLength;
    guint32  *lmVoltSensorsValue;      /* ro SNMPv2-SMI::Gauge32 */
} lm_sensors_mib_lmVoltSensorsEntry_t;

extern void
lm_sensors_mib_get_lmVoltSensorsTable(GNetSnmp *s, lm_sensors_mib_lmVoltSensorsEntry_t ***lmVoltSensorsEntry, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmVoltSensorsTable(lm_sensors_mib_lmVoltSensorsEntry_t **lmVoltSensorsEntry);

extern lm_sensors_mib_lmVoltSensorsEntry_t *
lm_sensors_mib_new_lmVoltSensorsEntry(void);

extern void
lm_sensors_mib_get_lmVoltSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmVoltSensorsEntry_t **lmVoltSensorsEntry, gint32 lmVoltSensorsIndex, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmVoltSensorsEntry(lm_sensors_mib_lmVoltSensorsEntry_t *lmVoltSensorsEntry);

/*
 * C type definitions for LM-SENSORS-MIB::lmMiscSensorsEntry.
 */

#define LM_SENSORS_MIB_LMMISCSENSORSINDEX  (1 << 0) 
#define LM_SENSORS_MIB_LMMISCSENSORSDEVICE (1 << 1) 
#define LM_SENSORS_MIB_LMMISCSENSORSVALUE  (1 << 2) 

typedef struct {
    gint32   lmMiscSensorsIndex;       /* ro */
    guchar   *lmMiscSensorsDevice;     /* ro SNMPv2-TC::DisplayString */
#define LM_SENSORS_MIB_LMMISCSENSORSDEVICEMINLENGTH 0
#define LM_SENSORS_MIB_LMMISCSENSORSDEVICEMAXLENGTH 255
    guint16  _lmMiscSensorsDeviceLength;
    guint32  *lmMiscSensorsValue;      /* ro SNMPv2-SMI::Gauge32 */
} lm_sensors_mib_lmMiscSensorsEntry_t;

extern void
lm_sensors_mib_get_lmMiscSensorsTable(GNetSnmp *s, lm_sensors_mib_lmMiscSensorsEntry_t ***lmMiscSensorsEntry, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmMiscSensorsTable(lm_sensors_mib_lmMiscSensorsEntry_t **lmMiscSensorsEntry);

extern lm_sensors_mib_lmMiscSensorsEntry_t *
lm_sensors_mib_new_lmMiscSensorsEntry(void);

extern void
lm_sensors_mib_get_lmMiscSensorsEntry(GNetSnmp *s, lm_sensors_mib_lmMiscSensorsEntry_t **lmMiscSensorsEntry, gint32 lmMiscSensorsIndex, gint64 mask, GError **error);

extern void
lm_sensors_mib_free_lmMiscSensorsEntry(lm_sensors_mib_lmMiscSensorsEntry_t *lmMiscSensorsEntry);


G_END_DECLS

#endif /* _LM_SENSORS_MIB_H_ */
