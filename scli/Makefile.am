INCLUDES	= -I$(top_srcdir)/stub -I$(top_srcdir)/snmp $(GLIB_CFLAGS)
bin_PROGRAMS	= scli
scli_SOURCES	= scli.c scli.h scli.1 vendors.c \
		  getopt.h getopt.c getopt1.c basic.c cmds.c fmt.c \
		  system.c entity.c interface.c disman.c snmp.c \
		  ip.c udp.c tcp.c \
		  bridge.c atm.c ether.c \
		  ospf.c printer.c
scli_LDADD	= -L../stub -lstub -L../snmp -lsnmp $(GLIB_LIBS)
man_MANS	= scli.1
