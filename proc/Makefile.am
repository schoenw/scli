INCLUDES		= $(GLIB_CFLAGS) -I$(top_srcdir)/snmp -I$(top_srcdir)/stub

PROCS			= if-mib-proc.h if-mib-proc.c \
			  rapid-city-proc.h rapid-city-proc.c \
			  productmib-proc.h productmib-proc.c \
			  disman-script-mib-proc.h disman-script-mib-proc.c \
			  snmp-view-based-acm-mib-proc.h snmp-view-based-acm-mib-proc.c \
			  snmp-user-based-sm-mib-proc.h snmp-user-based-sm-mib-proc.c \
			  udp-mib-proc.h udp-mib-proc.c

noinst_LIBRARIES	= libproc.a
libproc_a_SOURCES	= $(PROCS)

