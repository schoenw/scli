/*							-- DO NOT EDIT --
 * This file has been generated by smidump
 * version 0.2.17 for the scli package.
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

#include "g_snmp.h"

/*
 * Tables to map enumerations to strings and vice versa.
 */

#define TCP_MIB_TCPRTOALGORITHM_OTHER	1
#define TCP_MIB_TCPRTOALGORITHM_CONSTANT	2
#define TCP_MIB_TCPRTOALGORITHM_RSRE	3
#define TCP_MIB_TCPRTOALGORITHM_VANJ	4

extern GSnmpEnum const tcp_mib_enums_tcpRtoAlgorithm[];

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

extern GSnmpEnum const tcp_mib_enums_tcpConnState[];


/*
 * C type definitions for TCP-MIB::tcp.
 */

#define TCP_MIB_TCPRTOALGORITHM	0x1 
#define TCP_MIB_TCPRTOMIN	0x2 
#define TCP_MIB_TCPRTOMAX	0x4 
#define TCP_MIB_TCPMAXCONN	0x8 
#define TCP_MIB_TCPACTIVEOPENS	0x10 
#define TCP_MIB_TCPPASSIVEOPENS	0x20 
#define TCP_MIB_TCPATTEMPTFAILS	0x40 
#define TCP_MIB_TCPESTABRESETS	0x80 
#define TCP_MIB_TCPCURRESTAB	0x100 
#define TCP_MIB_TCPINSEGS	0x200 
#define TCP_MIB_TCPOUTSEGS	0x400 
#define TCP_MIB_TCPRETRANSSEGS	0x800 
#define TCP_MIB_TCPINERRS	0x1000 
#define TCP_MIB_TCPOUTRSTS	0x2000 

typedef struct {
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
} tcp_mib_tcp_t;

extern tcp_mib_tcp_t *
tcp_mib_new_tcp(void);

extern void
tcp_mib_get_tcp(GSnmpSession *s, tcp_mib_tcp_t **tcp, gint mask);

extern void
tcp_mib_free_tcp(tcp_mib_tcp_t *tcp);

/*
 * C type definitions for TCP-MIB::tcpConnEntry.
 */

#define TCP_MIB_TCPCONNSTATE	0x1 
#define TCP_MIB_TCPCONNLOCALADDRESS	0x2 
#define TCP_MIB_TCPCONNLOCALPORT	0x4 
#define TCP_MIB_TCPCONNREMADDRESS	0x8 
#define TCP_MIB_TCPCONNREMPORT	0x10 

typedef struct {
    guchar   tcpConnLocalAddress[4];
    gint32   tcpConnLocalPort;
    guchar   tcpConnRemAddress[4];
    gint32   tcpConnRemPort;
    gint32   *tcpConnState;
} tcp_mib_tcpConnEntry_t;

extern void
tcp_mib_get_tcpConnTable(GSnmpSession *s, tcp_mib_tcpConnEntry_t ***tcpConnEntry, gint mask);

extern void
tcp_mib_free_tcpConnTable(tcp_mib_tcpConnEntry_t **tcpConnEntry);

extern tcp_mib_tcpConnEntry_t *
tcp_mib_new_tcpConnEntry(void);

extern void
tcp_mib_get_tcpConnEntry(GSnmpSession *s, tcp_mib_tcpConnEntry_t **tcpConnEntry, guchar *tcpConnLocalAddress, gint32 tcpConnLocalPort, guchar *tcpConnRemAddress, gint32 tcpConnRemPort, gint mask);

extern void
tcp_mib_set_tcpConnEntry(GSnmpSession *s, tcp_mib_tcpConnEntry_t *tcpConnEntry, gint mask);

extern void
tcp_mib_free_tcpConnEntry(tcp_mib_tcpConnEntry_t *tcpConnEntry);


#endif /* _TCP_MIB_H_ */
