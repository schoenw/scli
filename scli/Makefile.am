INCLUDES	= -I$(top_srcdir)/stub -I$(top_srcdir)/proc -I$(top_srcdir)/snmp $(GLIB_CFLAGS) $(GTK_CFLAGS) $(XML_CFLAGS)

bin_PROGRAMS	= scli # gscli

scli_SOURCES	= scli.c scli.h scli.1 vendors.c \
		  getopt.h getopt.c getopt1.c basic.c monitor.c cmds.c \
		  fmt.c xml.c \
		  system.c entity.c interface.c disman.c snmp.c \
		  ip.c udp.c tcp.c \
		  bridge.c atm.c ether.c \
		  ospf.c printer.c \
		  cisco.c nortel.c netsnmp.c
scli_LDADD	= -L../proc -lproc -L../stub -lstub -L../snmp -lgsnmp $(GLIB_LIBS) $(XML_LIBS)
#gscli_SOURCES	= gscli.c scli.h scli.1 vendors.c \
#		  getopt.h getopt.c getopt1.c basic.c monitor.c cmds.c fmt.c \
#		  system.c entity.c interface.c disman.c snmp.c \
#		  ip.c udp.c tcp.c \
#		  bridge.c atm.c ether.c \
#		  ospf.c printer.c \
#		  cisco.c nortel.c
#gscli_LDADD	= -L../stub -lstub -L../snmp -lgsnmp $(GTK_LIBS) $(GLIB_LIBS) $(XML_LIBS)
man_MANS	= scli.1

scli.1:
	./scli -n -c "show scli modes" | \
	awk '/^$$/		{ printf(".PP\n"); next } \
	     /^[A-Z][A-Z  ]*$$/	{ printf(".SH %s\n", $$0); next } \
	     /^    /		{ printf(".TP\n.B %s\n", $$0); next } \
	     /^ $$/		{ next } \
	     //			{ printf("%s\n", $$0) }' > scli.1.modes
	m4 -P scli.1.in > scli.1
