INCLUDES	= -I$(top_srcdir)/stub -I$(top_srcdir)/proc $(GSNMP_CFLAGS) $(GNET_CFLAGS) $(GTK_CFLAGS) $(XML_CFLAGS) $(XML_CPPFLAGS)

EXTRA_DIST	= oui.c

bin_PROGRAMS	= scli # gscli

scli_SOURCES	= scli.c scli.h scli.1 vendors.c \
		  basic.c monitor.c cmds.c \
		  fmt.c xml.c netconf.c \
		  system.c entity.c interface.c disman.c snmp.c \
		  ip.c udp.c tcp.c \
		  bridge.c atm.c ether.c \
		  ospf.c printer.c \
		  isdn.c rs232.c sonet.c \
		  cisco.c nortel.c netsnmp.c 3com.c hp.c sflow.c

scli_LDADD	= $(top_builddir)/proc/libproc.a \
		  $(top_builddir)/stub/libstub.a \
		  $(GSNMP_LIBS) $(GNET_LIBS) $(GLIB_LIBS) $(XML_LIBS)

#gscli_SOURCES	= gscli.c scli.h scli.1 vendors.c \
#		  getopt.h getopt.c getopt1.c basic.c monitor.c cmds.c \
#		  fmt.c xml.c \
#		  system.c entity.c interface.c disman.c snmp.c \
#		  ip.c udp.c tcp.c \
#		  bridge.c atm.c ether.c \
#		  ospf.c printer.c \
#		  isdn.c rs232.c sonet.c \
#		  cisco.c nortel.c netsnmp.c 3com.c
#
#gscli_LDADD	= $(top_builddir)/proc/libproc.a \
#		  $(top_builddir)/stub/libstub.a \
#		  $(top_builddir)/snmp/libgsnmp.a \
#		  $(GTK_LIBS) $(GNET_LIBS) $(XML_LIBS)

man_MANS	= scli.1

scli.1:
	$(top_builddir)/scli/scli -n -c "show scli modes" | \
	awk '/^$$/		{ printf(".PP\n"); next } \
	     /^[A-Z,0-9][A-Z,0-9,  ]*$$/	{ printf(".SH %s\n", $$0); next } \
	     /^    /		{ printf(".TP\n.B %s\n", $$0); next } \
	     /^ $$/		{ next } \
	     //			{ printf("%s\n", $$0) }' | \
	sed -e "s/\`/\\\\fI/" -e "s/'/\\\\fP/" > scli.1.modes
	m4 -P scli.1.in > scli.1

oui.c:
	echo "/*" > oui.c
	echo "/* The following list has been created on `date`" >> oui.c
	echo " * from http://standards.ieee.org/regauth/oui/oui.txt" >> oui.c
	echo " */" >> oui.c
	echo "static scli_vendor_t ieee802_vendor_table[] = {" >> oui.c
	wget -O - http://standards.ieee.org/regauth/oui/oui.txt | grep '(base 16)' | sed 's/"/\\"/g' | cut -c 1-6,23- | sed -e 's/\(......\)\(.*\)$$/    { 0x\1, \"\2\" },/' >> oui.c
	echo "    { 0, NULL }" >> oui.c
	echo "};" >> oui.c

