/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli \
 *     --scli-include='dot1qBase' Q-BRIDGE-MIB
 *
 * Derived from Q-BRIDGE-MIB:
 *   The VLAN Bridge MIB module for managing Virtual Bridged
 *   Local Area Networks, as defined by IEEE 802.1Q-1998.
 *
 * Revision 1999-08-25 00:00:
 *   Initial version, published as RFC 2674.
 *
 * $Id$
 */

#ifndef _Q_BRIDGE_MIB_H_
#define _Q_BRIDGE_MIB_H_

#include "gsnmp.h"

G_BEGIN_DECLS

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define Q_BRIDGE_MIB_DOT1QVLANVERSIONNUMBER_VERSION1 1

extern GNetSnmpEnum const q_bridge_mib_enums_dot1qVlanVersionNumber[];


/*
 * C type definitions for Q-BRIDGE-MIB::dot1qBase.
 */

#define Q_BRIDGE_MIB_DOT1QVLANVERSIONNUMBER (1 << 0) 
#define Q_BRIDGE_MIB_DOT1QMAXVLANID         (1 << 1) 
#define Q_BRIDGE_MIB_DOT1QMAXSUPPORTEDVLANS (1 << 2) 
#define Q_BRIDGE_MIB_DOT1QNUMVLANS          (1 << 3) 
#define Q_BRIDGE_MIB_DOT1QGVRPSTATUS        (1 << 4) 

typedef struct {
    gint32   *dot1qVlanVersionNumber;     /* ro */
    gint32   *dot1qMaxVlanId;             /* ro Q-BRIDGE-MIB::VlanId */
    guint32  *dot1qMaxSupportedVlans;     /* ro Unsigned32 */
    guint32  *dot1qNumVlans;              /* ro Unsigned32 */
    gint32   *dot1qGvrpStatus;            /* rw P-BRIDGE-MIB::EnabledStatus */
} q_bridge_mib_dot1qBase_t;

extern q_bridge_mib_dot1qBase_t *
q_bridge_mib_new_dot1qBase(void);

extern void
q_bridge_mib_get_dot1qBase(GNetSnmp *s, q_bridge_mib_dot1qBase_t **dot1qBase, gint64 mask);

extern void
q_bridge_mib_set_dot1qBase(GNetSnmp *s, q_bridge_mib_dot1qBase_t *dot1qBase, gint64 mask);

extern void
q_bridge_mib_free_dot1qBase(q_bridge_mib_dot1qBase_t *dot1qBase);


G_END_DECLS

#endif /* _Q_BRIDGE_MIB_H_ */
