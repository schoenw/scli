INCLUDES		= $(GLIB_CFLAGS) -I$(top_srcdir)/snmp

MIBS			= IF-MIB \
			  IP-MIB \
			  IP-FORWARD-MIB \
			  UDP-MIB \
			  TCP-MIB \
			  SNMPv2-MIB \
			  SNMPv2-TM \
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
			  SNMP-NOTIFICATION-MIB \
			  NOTIFICATION-LOG-MIB \
			  TUNNEL-MIB \
			  EtherLike-MIB \
			  MAU-MIB \
			  OSPF-MIB \
			  Printer-MIB \
			  ISDN-MIB \
			  OLD-CISCO-IP-MIB \
			  RAPID-CITY \
			  UCD-SNMP-MIB

STUBS			= if-mib.h if-mib.c \
			  ip-mib.h ip-mib.c \
			  ip-forward-mib.h ip-forward-mib.c \
			  udp-mib.h udp-mib.c \
			  tcp-mib.h tcp-mib.c \
			  snmpv2-mib.h snmpv2-mib.c \
			  snmpv2-tm.h snmpv2-tm.c \
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
			  snmp-notification-mib.h snmp-notification-mib.c \
			  notification-log-mib.h notification-log-mib.c \
			  tunnel-mib.h tunnel-mib.c \
			  atm-mib.h atm-mib.c \
			  etherlike-mib.h etherlike-mib.c \
			  mau-mib.h mau-mib.c \
			  rfc1213-mib.h rfc1213-mib.c \
			  ospf-mib.h ospf-mib.c \
			  printer-mib.h printer-mib.c \
			  isdn-mib.h isdn-mib.c \
			  old-cisco-ip-mib.h old-cisco-ip-mib.c \
			  rapid-city.h rapid-city.c \
			  ucd-snmp-mib.h ucd-snmp-mib.c

noinst_LIBRARIES	= libstub.a
libstub_a_SOURCES	= $(STUBS)

SMIDUMP			= ../../libsmi/tools/smidump

rmstubs:
	rm -f $(STUBS)

stubs:
	$(SMIDUMP) -f scli --scli-match="VlanEntry|VlanPortEntry" RAPID-CITY
	$(SMIDUMP) -f scli --scli-match="ipRouteEntry" RFC1213-MIB
	$(SMIDUMP) -f scli --scli-match="atmInterfaceConfEntry" ATM-MIB
	@for f in $(MIBS) ; do \
	    echo "$(SMIDUMP) -f scli $$f" ; \
	    $(SMIDUMP) -f scli $$f ; \
	done
