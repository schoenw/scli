INCLUDES	= -I$(top_srcdir)/stub -I$(top_srcdir)/snmp $(GLIB_CFLAGS)
bin_PROGRAMS	= scli
scli_SOURCES	= scli.c scli.h scli.1 vendors.c \
		  getopt.h getopt.c getopt1.c basic.c cmds.c \
		  system.c interface.c
scli_LDADD	= -L../stub -lstub -L../snmp -lsnmp $(GLIB_LIBS)
man_MANS	= scli.1
