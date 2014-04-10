AM_CPPFLAGS		= $(GSNMP_CFLAGS) $(GNET_CFLAGS)

MIBS			= IF-MIB \
			  IANAifType-MIB \
			  IP-MIB \
			  IP-FORWARD-MIB \
			  UDP-MIB \
			  TCP-MIB \
			  SNMPv2-TC \
			  SNMPv2-MIB \
			  SNMPv2-TM \
			  HOST-RESOURCES-MIB \
			  HOST-RESOURCES-TYPES \
			  ENTITY-MIB \
			  ENTITY-SENSOR-MIB \
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
			  IANA-MAU-MIB \
			  MAU-MIB \
			  RFC1213-MIB \
			  OSPF-MIB \
			  IANA-CHARSET-MIB \
			  IANA-PRINTER-MIB \
			  Printer-MIB \
			  ISDN-MIB \
			  RS-232-MIB \
			  SONET-MIB \
			  RMON-MIB \
			  Q-BRIDGE-MIB \
			  INET-ADDRESS-MIB \
			  OLD-CISCO-IP-MIB \
			  RAPID-CITY \
			  UCD-SNMP-MIB \
			  PRODUCTMIB \
			  CISCO-DOT11-ASSOCIATION-MIB \
			  SFLOW5-MIB \
			  JACOBS-RPL-MIB \
			  IANA-RTPROTO-MIB

STUBS			= if-mib.h if-mib.c \
			  ianaiftype-mib.h ianaiftype-mib.c \
                          ip-mib.h ip-mib.c \
                          ip-forward-mib.h ip-forward-mib.c \
                          udp-mib.h udp-mib.c \
                          tcp-mib.h tcp-mib.c \
			  snmpv2-tc.h snmpv2-tc.c \
                          snmpv2-mib.h snmpv2-mib.c \
                          snmpv2-tm.h snmpv2-tm.c \
                          host-resources-mib.h host-resources-mib.c \
                          host-resources-types.h host-resources-types.c \
                          entity-mib.h entity-mib.c \
			  entity-sensor-mib.h entity-sensor-mib.c \
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
			  iana-mau-mib.h iana-mau-mib.c \
                          mau-mib.h mau-mib.c \
                          rfc1213-mib.h rfc1213-mib.c \
                          ospf-mib.h ospf-mib.c \
                          printer-mib.h printer-mib.c \
                          isdn-mib.h isdn-mib.c \
                          rs-232-mib.h rs-232-mib.c \
                          sonet-mib.h sonet-mib.c \
			  rmon-mib.h rmon-mib.c \
			  q-bridge-mib.h q-bridge-mib.c \
			  inet-address-mib.h inet-address-mib.c \
			  old-cisco-ip-mib.h old-cisco-ip-mib.c \
			  rapid-city.h rapid-city.c \
			  ucd-snmp-mib.h ucd-snmp-mib.c \
			  productmib.h productmib.c \
			  printer-mib.h printer-mib.c \
			  iana-charset-mib.h iana-charset-mib.c \
			  iana-printer-mib.h iana-printer-mib.c \
			  cisco-process-mib.h cisco-process-mib.c \
			  cisco-dot11-association-mib.h cisco-dot11-association-mib.c \
			  hp-icf-fault-finder-mib.h hp-icf-fault-finder-mib.c \
			  sflow5-mib.h sflow5-mib.c \
			  jacobs-rpl-mib.h jacobs-rpl-mib.c \
			  iana-rtproto-mib.c \
			  lm-sensors-mib.h lm-sensors-mib.c

MAINTAINERCLEANFILES	= $(STUBS)

noinst_LIBRARIES	= libstub.a
libstub_a_SOURCES	= $(STUBS)

SMIDUMP			= $(bindir)/smidump
#SMIDUMP			= ../../libsmi/tools/smidump
SMIPATH			= $(HOME)/mibs/cisco:$(HOME)/mibs/3com:$(HOME)/mibs/nortel:$(HOME)/mibs:/usr/local/share/mibs/site:/usr/local/share/mibs/ietf:/usr/local/share/mibs/iana:/usr/share/snmp/mibs

export SMIPATH

if-mib.h if-mib.c:
	$(SMIDUMP) -f scli --scli-set --scli-create --scli-delete --scli-exclude='ifTestEntry' IF-MIB

ianaiftype-mib.h ianaiftype-mib.c:
	$(SMIDUMP) -f scli IANAifType-MIB

ip-mib.h ip-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='icmp' IP-MIB

ip-forward-mib.h ip-forward-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='ipForwardEntry' IP-FORWARD-MIB

udp-mib.h udp-mib.c:
	$(SMIDUMP) -f scli UDP-MIB

tcp-mib.h tcp-mib.c:
	$(SMIDUMP) -f scli TCP-MIB

snmpv2-tc.h snmpv2-tc.c:
	$(SMIDUMP) -f scli SNMPv2-TC

snmpv2-mib.h snmpv2-mib.c:
	$(SMIDUMP) -f scli --scli-set SNMPv2-MIB

snmpv2-tm.h snmpv2-tm.c:
	$(SMIDUMP) -f scli SNMPv2-TM

host-resources-mib.h host-resources-mib.c:
	$(SMIDUMP) -f scli HOST-RESOURCES-MIB

host-resources-types.h host-resources-types.c:
	$(SMIDUMP) -f scli HOST-RESOURCES-TYPES

entity-mib.h entity-mib.c:
	$(SMIDUMP) -f scli ENTITY-MIB

entity-sensor-mib.h entity-sensor-mib.c:
	$(SMIDUMP) -f scli ENTITY-SENSOR-MIB

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

iana-mau-mib.h iana-mau-mib.c:
	$(SMIDUMP) -f scli IANA-MAU-MIB

mau-mib.h mau-mib.c:
	$(SMIDUMP) -f scli --scli-exclude='broadMauBasic' MAU-MIB

rfc1213-mib.h rfc1213-mib.c:
	$(SMIDUMP) -f scli -k --scli-include='ipRouteEntry' RFC1213-MIB

ospf-mib.h ospf-mib.c:
	$(SMIDUMP) -f scli -k --scli-include='ospfGeneralGroup|ospfAreaEntry|ospfIfEntry|ospfLsdbEntry' OSPF-MIB

iana-charset-mib.h iana-charset-mib.c:
	$(SMIDUMP) -f scli IANA-CHARSET-MIB

iana-printer-mib.h iana-printer-mib.c:
	$(SMIDUMP) -f scli IANA-PRINTER-MIB

printer-mib.h printer-mib.c:
	$(SMIDUMP) -f scli --scli-set Printer-MIB

isdn-mib.h isdn-mib.c:
	$(SMIDUMP) -f scli --scli-include='isdnBasicRateEntry|isdnBearerEntry|isdnEndpointEntry' ISDN-MIB

rs-232-mib.h rs-232-mib.c:
	$(SMIDUMP) -f scli RS-232-MIB

sonet-mib.h sonet-mib.c:
	$(SMIDUMP) -f scli --scli-include='sonetMediumEntry|sonetSection' SONET-MIB

rmon-mib.h rmon-mib.c:
	$(SMIDUMP) -f scli --scli-include='historyControlEntry' RMON-MIB

q-bridge-mib.h q-bridge-mib.c:
	$(SMIDUMP) -f scli --scli-include='dot1qBase|dot1qVlanStaticEntry|dot1qTpFdbEntry' Q-BRIDGE-MIB

inet-address-mib.h inet-address-mib.c:
	$(SMIDUMP) -f scli INET-ADDRESS-MIB

old-cisco-ip-mib.h old-cisco-ip-mib.c:
	$(SMIDUMP) -f scli OLD-CISCO-IP-MIB

cisco-process-mib.h cisco-process-mib.c:
	$(SMIDUMP) -f scli CISCO-PROCESS-MIB

rapid-city.h rapid-city.c:
	$(SMIDUMP) -f scli -k --scli-include='rcVlanEntry|rcVlanPortEntry' RAPID-CITY

ucd-snmp-mib.h ucd-snmp-mib.c:
	$(SMIDUMP) -f scli --scli-set UCD-SNMP-MIB

productmib.h productmib.c:
	$(SMIDUMP) -f scli --scli-include='a3ComVlanIfEntry|a3ComVirtualGroup' PRODUCTMIB

cisco-dot11-association-mib.h cisco-dot11-association-mib.c:
	$(SMIDUMP) -f scli -k CISCO-DOT11-ASSOCIATION-MIB

hp-icf-fault-finder-mib.h hp-icf-fault-finder-mib.c:
	$(SMIDUMP) -f scli HP-ICF-FAULT-FINDER-MIB

sflow5-mib.h sflow5-mib.c:
	$(SMIDUMP) -f scli SFLOW5-MIB

jacobs-rpl-mib.h jacobs-rpl-mib.c:
	$(SMIDUMP) -f scli JACOBS-RPL-MIB

iana-rtproto-mib.h iana-rtproto-mib.c:
	$(SMIDUMP) -f scli IANA-RTPROTO-MIB

lm-sensors-mib.h lm-sensors-mib.c:
	$(SMIDUMP) -f scli LM-SENSORS-MIB
