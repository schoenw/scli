/*							-- DO NOT EDIT --
 * Generated by smidump version 0.4.3:
 *   smidump -f scli INET-ADDRESS-MIB
 *
 * Derived from INET-ADDRESS-MIB:
 *   This MIB module defines textual conventions for
 *   representing Internet addresses.  An Internet
 *   address can be an IPv4 address, an IPv6 address,
 *   or a DNS domain name.  This module also defines
 *   textual conventions for Internet port numbers,
 *   autonomous system numbers, and the length of an
 *   Internet address prefix.
 *   
 *   Copyright (C) The Internet Society (2005).  This version
 *   of this MIB module is part of RFC 4001, see the RFC
 *   itself for full legal notices.
 *
 * Revision 2005-02-04 00:00:
 *   Third version, published as RFC 4001.  This revision
 *   introduces the InetZoneIndex, InetScopeType, and
 *   InetVersion textual conventions.
 *
 * Revision 2002-05-09 00:00:
 *   Second version, published as RFC 3291.  This
 *   revision contains several clarifications and
 *   introduces several new textual conventions:
 *   InetAddressPrefixLength, InetPortNumber,
 *   InetAutonomousSystemNumber, InetAddressIPv4z,
 *   and InetAddressIPv6z.
 *
 * Revision 2000-06-08 00:00:
 *   Initial version, published as RFC 2851.
 *
 * $Id$
 */

#include "inet-address-mib.h"

GNetSnmpEnum const inet_address_mib_enums_InetAddressType[] = {
    { INET_ADDRESS_MIB_INETADDRESSTYPE_UNKNOWN, "unknown" },
    { INET_ADDRESS_MIB_INETADDRESSTYPE_IPV4,    "ipv4" },
    { INET_ADDRESS_MIB_INETADDRESSTYPE_IPV6,    "ipv6" },
    { INET_ADDRESS_MIB_INETADDRESSTYPE_IPV4Z,   "ipv4z" },
    { INET_ADDRESS_MIB_INETADDRESSTYPE_IPV6Z,   "ipv6z" },
    { INET_ADDRESS_MIB_INETADDRESSTYPE_DNS,     "dns" },
    { 0, NULL }
};

GNetSnmpEnum const inet_address_mib_enums_InetScopeType[] = {
    { INET_ADDRESS_MIB_INETSCOPETYPE_INTERFACELOCAL,    "interfaceLocal" },
    { INET_ADDRESS_MIB_INETSCOPETYPE_LINKLOCAL,         "linkLocal" },
    { INET_ADDRESS_MIB_INETSCOPETYPE_SUBNETLOCAL,       "subnetLocal" },
    { INET_ADDRESS_MIB_INETSCOPETYPE_ADMINLOCAL,        "adminLocal" },
    { INET_ADDRESS_MIB_INETSCOPETYPE_SITELOCAL,         "siteLocal" },
    { INET_ADDRESS_MIB_INETSCOPETYPE_ORGANIZATIONLOCAL, "organizationLocal" },
    { INET_ADDRESS_MIB_INETSCOPETYPE_GLOBAL,            "global" },
    { 0, NULL }
};

GNetSnmpEnum const inet_address_mib_enums_InetVersion[] = {
    { INET_ADDRESS_MIB_INETVERSION_UNKNOWN, "unknown" },
    { INET_ADDRESS_MIB_INETVERSION_IPV4,    "ipv4" },
    { INET_ADDRESS_MIB_INETVERSION_IPV6,    "ipv6" },
    { 0, NULL }
};

