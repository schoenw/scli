INCLUDES		= $(GLIB_CFLAGS) -I$(top_srcdir)/snmp

MIBS			= IF-MIB \
			  IP-MIB \
			  IP-FORWARD-MIB \
			  UDP-MIB \
			  TCP-MIB \
			  SNMPv2-MIB \
			  HOST-RESOURCES-MIB \
			  HOST-RESOURCES-TYPES \
			  ENTITY-MIB \
			  BRIDGE-MIB \
			  IANA-LANGUAGE-MIB \
			  DISMAN-SCRIPT-MIB \
			  DISMAN-SCHEDULE-MIB \
			  SNMP-FRAMEWORK-MIB \
			  SNMP-MPD-MIB \
			  SNMP-USER-BASED-SM-MIB \
			  SNMP-COMMUNITY-MIB \
			  SNMP-VIEW-BASED-ACM-MIB \
			  SNMP-TARGET-MIB \
			  TUNNEL-MIB \
			  ATM-MIB \
			  EtherLike-MIB \
			  MAU-MIB \
			  RFC1213-MIB \
			  OSPF-MIB \
			  Printer-MIB \
			  OLD-CISCO-IP-MIB \
			  RAPIDCITY-VLAN-MIB

STUBS			= if-mib.h if-mib.c \
			  ip-mib.h ip-mib.c \
			  ip-forward-mib.h ip-forward-mib.c \
			  udp-mib.h udp-mib.c \
			  tcp-mib.h tcp-mib.c \
			  snmpv2-mib.h snmpv2-mib.c \
			  host-resources-mib.h host-resources-mib.c \
			  host-resources-types.h host-resources-types.c \
			  entity-mib.h entity-mib.c \
			  bridge-mib.h bridge-mib.c \
			  iana-language-mib.h iana-language-mib.c \
			  disman-script-mib.h disman-script-mib.c \
			  disman-schedule-mib.h disman-schedule-mib.c \
			  snmp-framework-mib.h snmp-framework-mib.c \
			  snmp-mpd-mib.h snmp-mpd-mib.c \
			  snmp-user-based-sm-mib.h snmp-user-based-sm-mib.c \
			  snmp-community-mib.h snmp-community-mib.c \
			  snmp-view-based-acm-mib.h snmp-view-based-acm-mib.c \
			  snmp-target-mib.h snmp-target-mib.c \
			  tunnel-mib.h tunnel-mib.c \
			  atm-mib.h atm-mib.c \
			  etherlike-mib.h etherlike-mib.c \
			  mau-mib.h mau-mib.c \
			  rfc1213-mib.h rfc1213-mib.c \
			  ospf-mib.h ospf-mib.c \
			  printer-mib.h printer-mib.c \
			  old-cisco-ip-mib.h old-cisco-ip-mib.c \
			  rapidcity-vlan-mib.h rapidcity-vlan-mib.c

noinst_LIBRARIES	= libstub.a
libstub_a_SOURCES	= $(STUBS)

SMIDUMP			= ../../libsmi/tools/smidump

rmstubs:
	rm -f $(STUBS)

stubs:
	@for f in $(MIBS) ; do \
	    echo "$(SMIDUMP) -f scli $$f" ; \
	    $(SMIDUMP) -f scli $$f ; \
	done
