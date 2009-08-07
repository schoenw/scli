INCLUDES		= $(GSNMP_CFLAGS) $(GNET_CFLAGS) -I$(top_srcdir)/stub

PROCS			= if-mib-proc.h if-mib-proc.c \
			  rapid-city-proc.h rapid-city-proc.c \
			  productmib-proc.h productmib-proc.c \
			  disman-script-mib-proc.h disman-script-mib-proc.c \
			  snmp-view-based-acm-mib-proc.h snmp-view-based-acm-mib-proc.c \
			  snmp-user-based-sm-mib-proc.h snmp-user-based-sm-mib-proc.c \
			  udp-mib-proc.h udp-mib-proc.c \
			  ianaiftype-mib-proc.h ianaiftype-mib-proc.c \
			  sflow5-mib-proc.h sflow5-mib-proc.c \
			  q-bridge-mib-proc.h q-bridge-mib-proc.c

noinst_LIBRARIES	= libproc.a
libproc_a_SOURCES	= $(PROCS)

