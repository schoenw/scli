INCLUDES	= -I$(top_srcdir)/stub -I$(top_srcdir)/snmp $(GLIB_CFLAGS)
bin_PROGRAMS	= stop
stop_SOURCES	= stop.c stop.h stop.1 \
                  getopt.h getopt.c getopt1.c fmt.c \
		  interface.c process.c disman.c # snmp.c
stop_LDADD	= -L../stub -lstub -L../snmp -lsnmp $(GLIB_LIBS)
man_MANS	= stop.1
