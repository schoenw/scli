/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.14 for the stools package.
 *
 * Derived from TCP-MIB:
 *   The MIB module for managing TCP implementations.
 *
 * Revision 1994-11-01 00:00:
 *   [Revision added by libsmi due to a LAST-UPDATED clause.]
 *
 * Revision 1991-03-31 00:00:
 *   The initial revision of this MIB module was part of MIB-
 *   II.
 *
 * $Id$
 */

#ifndef _TCP_MIB_H_
#define _TCP_MIB_H_

#include "stools.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define TCP_MIB_TCPRTOALGORITHM_OTHER	1
#define TCP_MIB_TCPRTOALGORITHM_CONSTANT	2
#define TCP_MIB_TCPRTOALGORITHM_RSRE	3
#define TCP_MIB_TCPRTOALGORITHM_VANJ	4

extern stls_table_t const tcp_mib_enums_tcpRtoAlgorithm[];

#define TCP_MIB_TCPCONNSTATE_CLOSED	1
#define TCP_MIB_TCPCONNSTATE_LISTEN	2
#define TCP_MIB_TCPCONNSTATE_SYNSENT	3
#define TCP_MIB_TCPCONNSTATE_SYNRECEIVED	4
#define TCP_MIB_TCPCONNSTATE_ESTABLISHED	5
#define TCP_MIB_TCPCONNSTATE_FINWAIT1	6
#define TCP_MIB_TCPCONNSTATE_FINWAIT2	7
#define TCP_MIB_TCPCONNSTATE_CLOSEWAIT	8
#define TCP_MIB_TCPCONNSTATE_LASTACK	9
#define TCP_MIB_TCPCONNSTATE_CLOSING	10
#define TCP_MIB_TCPCONNSTATE_TIMEWAIT	11
#define TCP_MIB_TCPCONNSTATE_DELETETCB	12

extern stls_table_t const tcp_mib_enums_tcpConnState[];


/*
 * C type definitions for TCP-MIB::tcp.
 */

typedef struct tcp {
    gint32   *tcpRtoAlgorithm;
    gint32   *tcpRtoMin;
    gint32   *tcpRtoMax;
    gint32   *tcpMaxConn;
    guint32  *tcpActiveOpens;
    guint32  *tcpPassiveOpens;
    guint32  *tcpAttemptFails;
    guint32  *tcpEstabResets;
    guint32  *tcpCurrEstab;
    guint32  *tcpInSegs;
    guint32  *tcpOutSegs;
    guint32  *tcpRetransSegs;
    guint32  *tcpInErrs;
    guint32  *tcpOutRsts;
} tcp_t;

extern tcp_t *
tcp_mib_new_tcp();

extern int
tcp_mib_get_tcp(host_snmp *s, tcp_t **tcp);

extern void
tcp_mib_free_tcp(tcp_t *tcp);

/*
 * C type definitions for TCP-MIB::tcpConnEntry.
 */

typedef struct tcpConnEntry {
    guchar   tcpConnLocalAddress[4];
    gint32   tcpConnLocalPort;
    guchar   tcpConnRemAddress[4];
    gint32   tcpConnRemPort;
    gint32   *tcpConnState;
} tcpConnEntry_t;

extern int
tcp_mib_get_tcpConnTable(host_snmp *s, tcpConnEntry_t ***tcpConnEntry);

extern void
tcp_mib_free_tcpConnTable(tcpConnEntry_t **tcpConnEntry);

extern tcpConnEntry_t *
tcp_mib_new_tcpConnEntry();

extern int
tcp_mib_get_tcpConnEntry(host_snmp *s, tcpConnEntry_t **tcpConnEntry);

extern int
tcp_mib_set_tcpConnEntry(host_snmp *s, tcpConnEntry_t *tcpConnEntry);

extern void
tcp_mib_free_tcpConnEntry(tcpConnEntry_t *tcpConnEntry);


#endif /* _TCP_MIB_H_ */
