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
			  ATM-MIB \
			  EtherLike-MIB \
			  MAU-MIB \
			  RFC1213-MIB \
			  OSPF-MIB \
			  Printer-MIB \
			  ISDN-MIB \
			  RS-232-MIB \
			  SONET-MIB \
			  OLD-CISCO-IP-MIB \
			  RAPID-CITY \
			  UCD-SNMP-MIB \
			  PRODUCTMIB

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
			  rs-232-mib.h rs-232-mib.c \
			  sonet-mib.h sonet-mib.c \
			  old-cisco-ip-mib.h old-cisco-ip-mib.c \
			  rapid-city.h rapid-city.c \
			  ucd-snmp-mib.h ucd-snmp-mib.c \
			  productmib.h productmib.c

noinst_LIBRARIES	= libstub.a
libstub_a_SOURCES	= $(STUBS)

SMIDUMP			= ../../libsmi/tools/smidump

rmstubs:
	rm -f $(STUBS)

if-mib.h if-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='ifTestEntry' IF-MIB

ip-mib.h ip-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='icmp' IP-MIB

ip-forward-mib.h ip-forward-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='ipForwardEntry' IF-FORWARD-MIB

udp-mib.h udp-mib.c:
	$(SMIDUMP) -f scli UDP-MIB

tcp-mib.h tcp-mib.c:
	$(SMIDUMP) -f scli TCP-MIB

snmpv2-mib.h snmpv2-mib.c:
	$(SMIDUMP) -f scli SNMPv2-MIB

snmpv2-tm.h snmpv2-tm.c:
	$(SMIDUMP) -f scli SNMPv2-TM

host-resources-mib.h host-resources-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='hrSWInstalled' HOST-RESOURCES-MIB

host-resources-types.h host-resources-types.c:
	$(SMIDUMP) -f scli HOST-RESOURCES-TYPES

entity-mib.h entity-mib.c:
	$(SMIDUMP) -f scli ENTITY-MIB

bridge-mib.h bridge-mib.c:
	$(SMIDUMP) -f scli BRIDGE-MIB

iana-language-mib.h iana-language-mib.c:
	$(SMIDUMP) -f scli IANA-LANGUAGE-MIB

disman-script-mib.h disman-script-mib.c:
	$(SMIDUMP) -f scli DISMAN-SCRIPT-MIB

disman-schedule-mib.h disman-schedule-mib.c:
	$(SMIDUMP) -f scli DISMAN-SCHEDULE-MIB

snmp-framework-mib.h snmp-framework-mib.c:
	$(SMIDUMP) -f scli SNMP-FRAMEWORK-MIB

snmp-mpd-mib.h snmp-mpd-mib.c:
	$(SMIDUMP) -f scli SNMP-MPD-MIB

snmp-user-based-sm-mib.h snmp-user-based-sm-mib.c:
	$(SMIDUMP) -f scli SNMP-USER-BASED-SM-MIB

snmp-community-mib.h snmp-community-mib.c:
	$(SMIDUMP) -f scli SNMP-COMMUNITY-MIB

snmp-view-based-acm-mib.h snmp-view-based-acm-mib.c:
	$(SMIDUMP) -f scli SNMP-VIEW-BASED-ACM-MIB

snmp-target-mib.h snmp-target-mib.c:
	$(SMIDUMP) -f scli SNMP-TARGET-MIB

snmp-notification-mib.h snmp-notification-mib.c:
	$(SMIDUMP) -f scli SNMP-NOTIFICATION-MIB

notification-log-mib.h notification-log-mib.c:
	$(SMIDUMP) -f scli NOTIFICATION-LOG-MIB

tunnel-mib.h tunnel-mib.c:
	$(SMIDUMP) -f scli TUNNEL-MIB

atm-mib.h atm-mib.c:
	$(SMIDUMP) -f scli --scli-include='atmInterfaceConfEntry' ATM-MIB

etherlike-mib.h etherlike-mib.c:
	$(SMIDUMP) -f scli --scli-include='dot3StatsEntry' EtherLike-MIB

mau-mib.h mau-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='broadMauBasic' MAU-MIB

rfc1213-mib.h rfc1213-mib.c:
	$(SMIDUMP) -f scli --scli-include='ipRouteEntry' RFC1213-MIB

ospf-mib.h ospf-mib.c:
	$(SMIDUMP) -f scli --scli-include='ospfGeneralGroup|ospfAreaEntry|ospfIfEntry' OSPF-MIB

printer-mib.h printer-mib.c:
	$(SMIDUMP) -f scli Printer-MIB

isdn-mib.h isdn-mib.c:
	$(SMIDUMP) -f scli --scli-include='isdnBasicRateEntry|isdnBearerEntry|isdnEndpointEntry' ISDN-MIB

rs-232-mib.h rs-232-mib.c:
	$(SMIDUMP) -f scli RS-232-MIB

sonet-mib.h sonet-mib.c:
	$(SMIDUMP) -f scli --scli-include='sonetMediumEntry|sonetSection' SONET-MIB

old-cisco-ip-mib.h old-cisco-ip-mib.c:
	$(SMIDUMP) -f scli OLD-CISCO-IP-MIB

rapid-city.h rapid-city.c:
	$(SMIDUMP) -f scli --scli-include='vlanEntry|vlanPortEntry' RAPID-CITY

ucd-snmp-mib.h ucd-snmp-mib.c:
	$(SMIDUMP) -f scli --scli-include='version|extEntry|prEntry|laEntry' UCD-SNMP-MIB

productmib.h productmib.c:
	$(SMIDUMP) -f scli --scli-include='a3ComVlanIfEntry|a3ComVirtualGroup' PRODUCTMIB
