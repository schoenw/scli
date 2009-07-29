/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.8:
 *   smidump -f scli ENTITY-SENSOR-MIB
 *
 * Derived from ENTITY-SENSOR-MIB:
 *   This module defines Entity MIB extensions for physical
 *   sensors.
 *   
 *   Copyright (C) The Internet Society (2002). This version
 *   of this MIB module is part of RFC 3433; see the RFC
 *   itself for full legal notices.
 *
 * Revision 2002-12-16 00:00:
 *   Initial version of the Entity Sensor MIB module, published
 *   as RFC 3433.
 *
 * $Id$
 */

#ifndef _ENTITY_SENSOR_MIB_H_
#define _ENTITY_SENSOR_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_OTHER      1
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_UNKNOWN    2
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_VOLTSAC    3
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_VOLTSDC    4
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_AMPERES    5
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_WATTS      6
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_HERTZ      7
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_CELSIUS    8
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_PERCENTRH  9
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_RPM        10
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_CMM        11
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATATYPE_TRUTHVALUE 12

extern GNetSnmpEnum const entity_sensor_mib_enums_EntitySensorDataType[];

#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_YOCTO 1
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_ZEPTO 2
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_ATTO  3
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_FEMTO 4
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_PICO  5
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_NANO  6
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_MICRO 7
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_MILLI 8
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_UNITS 9
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_KILO  10
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_MEGA  11
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_GIGA  12
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_TERA  13
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_EXA   14
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_PETA  15
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_ZETTA 16
#define ENTITY_SENSOR_MIB_ENTITYSENSORDATASCALE_YOTTA 17

extern GNetSnmpEnum const entity_sensor_mib_enums_EntitySensorDataScale[];

#define ENTITY_SENSOR_MIB_ENTITYSENSORSTATUS_OK             1
#define ENTITY_SENSOR_MIB_ENTITYSENSORSTATUS_UNAVAILABLE    2
#define ENTITY_SENSOR_MIB_ENTITYSENSORSTATUS_NONOPERATIONAL 3

extern GNetSnmpEnum const entity_sensor_mib_enums_EntitySensorStatus[];


/*
 * C type definitions for ENTITY-SENSOR-MIB::entPhySensorEntry.
 */

#define ENTITY_SENSOR_MIB_ENTPHYSENSORTYPE            (1 << 0) 
#define ENTITY_SENSOR_MIB_ENTPHYSENSORSCALE           (1 << 1) 
#define ENTITY_SENSOR_MIB_ENTPHYSENSORPRECISION       (1 << 2) 
#define ENTITY_SENSOR_MIB_ENTPHYSENSORVALUE           (1 << 3) 
#define ENTITY_SENSOR_MIB_ENTPHYSENSOROPERSTATUS      (1 << 4) 
#define ENTITY_SENSOR_MIB_ENTPHYSENSORUNITSDISPLAY    (1 << 5) 
#define ENTITY_SENSOR_MIB_ENTPHYSENSORVALUETIMESTAMP  (1 << 6) 
#define ENTITY_SENSOR_MIB_ENTPHYSENSORVALUEUPDATERATE (1 << 7) 

typedef struct {
    gint32   entPhysicalIndex;                 /* na ENTITY-MIB::PhysicalIndex */
    gint32   *entPhySensorType;                /* ro ENTITY-SENSOR-MIB::EntitySensorDataType */
    gint32   *entPhySensorScale;               /* ro ENTITY-SENSOR-MIB::EntitySensorDataScale */
    gint32   *entPhySensorPrecision;           /* ro ENTITY-SENSOR-MIB::EntitySensorPrecision */
    gint32   *entPhySensorValue;               /* ro ENTITY-SENSOR-MIB::EntitySensorValue */
    gint32   *entPhySensorOperStatus;          /* ro ENTITY-SENSOR-MIB::EntitySensorStatus */
    guchar   *entPhySensorUnitsDisplay;        /* ro SNMP-FRAMEWORK-MIB::SnmpAdminString */
#define ENTITY_SENSOR_MIB_ENTPHYSENSORUNITSDISPLAYMINLENGTH 0
#define ENTITY_SENSOR_MIB_ENTPHYSENSORUNITSDISPLAYMAXLENGTH 255
    guint16  _entPhySensorUnitsDisplayLength;
    guint32  *entPhySensorValueTimeStamp;      /* ro SNMPv2-TC::TimeStamp */
    guint32  *entPhySensorValueUpdateRate;     /* ro Unsigned32 [milliseconds] */
} entity_sensor_mib_entPhySensorEntry_t;

extern void
entity_sensor_mib_get_entPhySensorTable(GNetSnmp *s, entity_sensor_mib_entPhySensorEntry_t ***entPhySensorEntry, gint64 mask, GError **error);

extern void
entity_sensor_mib_free_entPhySensorTable(entity_sensor_mib_entPhySensorEntry_t **entPhySensorEntry);

extern entity_sensor_mib_entPhySensorEntry_t *
entity_sensor_mib_new_entPhySensorEntry(void);

extern void
entity_sensor_mib_get_entPhySensorEntry(GNetSnmp *s, entity_sensor_mib_entPhySensorEntry_t **entPhySensorEntry, gint32 entPhysicalIndex, gint64 mask, GError **error);

extern void
entity_sensor_mib_free_entPhySensorEntry(entity_sensor_mib_entPhySensorEntry_t *entPhySensorEntry);


G_END_DECLS

#endif /* _ENTITY_SENSOR_MIB_H_ */
