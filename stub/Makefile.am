INCLUDES		= $(GLIB_CFLAGS) -I$(top_srcdir)/snmp

MIBS			= IF-MIB \
			  IP-MIB \
			  UDP-MIB \
			  TCP-MIB \
			  SNMPv2-MIB \
			  HOST-RESOURCES-MIB \
			  ENTITY-MIB \
			  BRIDGE-MIB \
			  DISMAN-SCRIPT-MIB \
			  DISMAN-SCHEDULE-MIB \
			  SNMP-FRAMEWORK-MIB \
			  SNMP-MPD-MIB \
			  SNMP-USER-BASED-SM-MIB \
			  SNMP-COMMUNITY-MIB \
			  SNMP-VIEW-BASED-ACM-MIB \
			  SNMP-TARGET-MIB

STUBS			= if-mib.h if-mib.c \
			  ip-mib.h ip-mib.c \
			  udp-mib.h udp-mib.c \
			  tcp-mib.h tcp-mib.c \
			  snmpv2-mib.h snmpv2-mib.c \
			  host-resources-mib.h host-resources-mib.c \
			  entity-mib.h entity-mib.c \
			  bridge-mib.h bridge-mib.c \
			  disman-script-mib.h disman-script-mib.c \
			  disman-schedule-mib.h disman-schedule-mib.c \
			  snmp-framework-mib.h snmp-framework-mib.c \
			  snmp-mpd-mib.h snmp-mpd-mib.c \
			  snmp-user-based-sm-mib.h snmp-user-based-sm-mib.c \
			  snmp-community-mib.h snmp-community-mib.c \
			  snmp-view-based-acm-mib.h snmp-view-based-acm-mib.c \
			  snmp-target-mib.h snmp-target-mib.c

noinst_LIBRARIES	= libstub.a
libstub_a_SOURCES	= stools.h stools.c $(STUBS)

SMIDUMP			= ../../libsmi/tools/smidump

stubs:
	rm -f $(STUBS)
	@for f in $(MIBS) ; do \
	    echo "$(SMIDUMP) -f stools $$f" ; \
	    $(SMIDUMP) -f stools $$f ; \
	done
