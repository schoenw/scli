/*
 * $Id$
 * GXSNMP -- An snmp management application
 * Copyright (C) 1998 Gregory McLean & Jochen Friedrich
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.,  59 Temple Place - Suite 330, Cambridge, MA 02139, USA.
 *
 * Snmp transport modules
 */

#ifndef lint
static char const copyright[] =
"@(#) Copyright (c) 1998 Gregory McLean & Jochen Friedrich";
#endif
static char const rcsid[] =
"$Id$";
#include "config.h"
#include <g_snmp.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

extern int     errno;

#ifdef HAVE_INET

#include <netinet/in.h>
#include <netdb.h>

#ifdef SNMP_DEBUG
/* Subroutine to dump packet contents to the screen - jms */
static void packet_dump (gpointer data, guint len)
{
  guint i;
  for (i = 0; i < len; i++)
    {
      if (i % 16 == 0)
        g_print ("%8.8x:", i);
      if (i % 4 == 0)
        g_print (" ");
        g_print ("%2.2x", ((guchar *)data)[i]);
      if (i % 16 == 15)
        g_print ("\n");
    }
  if (i % 16 != 15)
    g_print ("\n");
}
#endif

static gint ipv4_socket = 0;      /* file handle for SNMP traffic */

static gboolean
ipv4_init(gboolean dobind)
{
  struct sockaddr_in adr;

  if ((ipv4_socket = socket(AF_INET, SOCK_DGRAM, 0)) != -1)
    {
      if (dobind)
        {
          adr.sin_family  = AF_INET;
          adr.sin_port    = htons(161);
          adr.sin_addr.s_addr = INADDR_ANY;
          if (bind(ipv4_socket, (struct sockaddr *) &adr, sizeof(struct sockaddr_in)) == -1)
            {
              close(ipv4_socket);
              g_warning("Can't bind IPv4 socket: %s", g_strerror(errno));
            }
        }
      return TRUE;
    }
  g_warning("Open socket for transport AF_INET failed: %s", g_strerror(errno));
  return FALSE;
}

static gboolean
ipv4_resolve_address (guchar *hostname, struct sockaddr **address)
{
  struct servent *port;
  struct hostent *hp;
  struct sockaddr_in *adr;

  *address = NULL;
  adr = (struct sockaddr_in *) g_malloc(sizeof(struct sockaddr_in)); 
  adr->sin_family = AF_INET;
  hp = gethostbyname((char *) hostname);
  if (!hp)
    {
      g_free(adr);
      return FALSE;
    }
  g_memmove((char *)&adr->sin_addr, (char *)hp->h_addr, hp->h_length);
  port = getservbyname("snmp","udp");
  if (!port)
    {
      g_free(adr);
      return FALSE;
    }
  adr->sin_port = port->s_port;
  *address = (struct sockaddr *)adr;
  return TRUE;
}

static gboolean
ipv4_send_message(struct sockaddr *transportAddress, gpointer outgoingMessage, 
                  guint outgoingMessageLength)
{
#ifdef SNMP_DEBUG
  printf("Sending packet on IPv4, %d bytes\n", outgoingMessageLength);
  packet_dump (outgoingMessage, outgoingMessageLength);
#endif
  if (sendto(ipv4_socket, outgoingMessage, outgoingMessageLength, 0,
             transportAddress, sizeof(struct sockaddr_in)))
    return TRUE;
#ifdef SNMP_DEBUG
  printf("Sending packet on IPv4 FAILED with RC=%d\n", errno);
#endif
  return FALSE;
}

static void
ipv4_receive_message()
{
  guchar              buffer[MAX_DGRAM_SIZE];
  struct sockaddr_in  address;
  int                 adrsize, len;

  adrsize = sizeof (address);

  len = recvfrom(ipv4_socket, (char *) buffer, sizeof(buffer), 0, 
                 (struct sockaddr *) &address, &adrsize);
#ifdef SNMP_DEBUG
  printf("Received packet on IPv4, %d bytes\n", len);
  packet_dump (buffer, len);
#endif
  if (len>0)
    g_receive_message(AF_INET, (struct sockaddr *)&address, buffer, len);

}

static guint
ipv4_get_socket()
{
  return ipv4_socket;
}

#endif

#ifdef HAVE_IPX

/* Transport mapping as defined in RFC1906 Chapter 6 */

#include <netipx/ipx.h>

static gint ipx_socket  = 0;      /* file handle for SNMP traffic */

static gboolean
ipx_resolve_address (guchar *hostname, struct sockaddr **address)
{
  struct sockaddr_ipx *adr;
  char *net, *hwaddr;
  int a1, a2, a3, a4, a5, a6;

  adr = (struct sockaddr_ipx *) g_malloc(sizeof(struct sockaddr_ipx)); 
  adr->sipx_family  = AF_IPX;
  adr->sipx_port    = htons(0x900f);
  adr->sipx_type    = 4; /* Packet Exchange Protocol */

  net    = strtok(hostname, ".");
  hwaddr = strtok(NULL, ".");

  if (!hwaddr)
    {
      hwaddr = net;
      adr->sipx_network = 0;
    }
  else
    {
      adr->sipx_network = htonl(atoi(net));
    }
  sscanf(hwaddr, "%x:%x:%x:%x:%x:%x", &a1, &a2, &a3, &a4, &a5, &a6);
  adr->sipx_node[0] = a1;
  adr->sipx_node[1] = a2;
  adr->sipx_node[2] = a3;
  adr->sipx_node[3] = a4;
  adr->sipx_node[4] = a5;
  adr->sipx_node[5] = a6;
  
  *address = (struct sockaddr *) adr;

  return TRUE;
}

static gboolean
ipx_init(gboolean dobind)
{
  struct sockaddr_ipx adr;

  if ((ipx_socket = socket(AF_IPX, SOCK_DGRAM, 0)) != -1) 
    {
      adr.sipx_family  = AF_IPX;
      adr.sipx_network = 0;
      adr.sipx_node[0] = 0;
      adr.sipx_node[1] = 0;
      adr.sipx_node[2] = 0;
      adr.sipx_node[3] = 0;
      adr.sipx_node[4] = 0;
      adr.sipx_node[5] = 0;
      adr.sipx_type    = 4; /* Packet Exchange Protocol */
      if (dobind)
        adr.sipx_port  = htons(36879); /* SNMP IPX port as of RFC1903 */
      else
        adr.sipx_port  = 0;
      if (bind(ipx_socket, &adr, sizeof(struct sockaddr_ipx)) == -1)
        {
          close(ipx_socket);
          g_warning("Can't bind IPX socket: %s", g_strerror(errno));
        }
      return TRUE;
    }
  g_warning("Open socket for transport AF_IPX failed: %s", g_strerror(errno));
  return FALSE;
}
  
static gboolean
ipx_send_message(struct sockaddr *transportAddress, gpointer outgoingMessage, 
                 guint outgoingMessageLength)
{
#ifdef SNMP_DEBUG
  printf("Sending packet on IPX\n");
#endif
  if (sendto(ipx_socket, outgoingMessage, outgoingMessageLength, 0,
             transportAddress, sizeof(struct sockaddr_ipx)))
    return TRUE;
  else
    return FALSE;
}

static void
ipx_receive_message()
{
  guchar              buffer[MAX_DGRAM_SIZE];
  struct sockaddr_ipx address;
  int                 adrsize, len;

  adrsize = sizeof (address);
  len = recvfrom(ipx_socket, buffer, sizeof(buffer), 0, 
                 &address, &adrsize);
  if (len>0)
    g_receive_message(AF_IPX, (struct sockaddr *)&address, buffer, len);
}

static guint
ipx_get_socket()
{
  return ipx_socket;
}

#endif

#ifdef HAVE_INET6

#include <arpa/inet.h>

static gint ipv6_socket  = 0;      /* file handle for SNMP traffic */

static gboolean
ipv6_resolve_address (guchar *hostname, struct sockaddr **address)
{
  struct sockaddr_in6 *adr;
  struct servent *port;

  *address = NULL;
  adr = (struct sockaddr_in6 *) g_malloc(sizeof(struct sockaddr_in6)); 
  adr->sin6_family  = AF_INET6;
  inet_pton(AF_INET6, hostname, &adr->sin6_addr);

  port = getservbyname("snmp","udp");
  if (!port)
    {
      g_free(adr);
      return FALSE;
    }
  adr->sin6_port = port->s_port;
  *address = (struct sockaddr *) adr;

  return TRUE;
}

static gboolean
ipv6_init(gboolean dobind)
{
  if ((ipv6_socket = socket(AF_INET6, SOCK_DGRAM, 0)) != -1)
    return TRUE;
  g_warning("Open socket for transport AF_INET6 failed: %s", g_strerror(errno));
  return FALSE;
}
  
static gboolean
ipv6_send_message(struct sockaddr *transportAddress, gpointer outgoingMessage, 
                 guint outgoingMessageLength)
{
#ifdef SNMP_DEBUG
  printf("Sending packet on IPv6\n");
#endif
  if (sendto(ipv6_socket, outgoingMessage, outgoingMessageLength, 0,
             transportAddress, sizeof(struct sockaddr_in6)))
    return TRUE;
  else
    return FALSE;
}

static void
ipv6_receive_message()
{
  guchar              buffer[MAX_DGRAM_SIZE];
  struct sockaddr_in6 address;
  int                 adrsize, len;

  adrsize = sizeof (address);
  len = recvfrom(ipv6_socket, buffer, sizeof(buffer), 0, 
                 &address, &adrsize);
  if (len>0)
    g_receive_message(AF_INET6, (struct sockaddr *)&address, buffer, len);
}

static guint
ipv6_get_socket()
{
  return ipv6_socket;
}

#endif

gboolean
g_transport_init(gboolean dobind)
{
  struct g_transport *my_transport;
  int success = 0;

#ifdef HAVE_INET
  if (ipv4_init(dobind))
    {
      my_transport = g_malloc(sizeof(struct g_transport));

      my_transport->model		   = AF_INET;
      my_transport->name		   = "IP";
      my_transport->sendMessage            = ipv4_send_message;
      my_transport->receiveMessage         = ipv4_receive_message;
      my_transport->resolveAddress         = ipv4_resolve_address;
      my_transport->getSocket              = ipv4_get_socket;

      g_register_transport (my_transport);
      success = 1;
    }
#endif

#ifdef HAVE_IPX
  if (ipx_init(dobind))
    {
      my_transport = g_malloc(sizeof(struct g_transport));

      my_transport->model		   = AF_IPX;
      my_transport->name		   = "IPX";
      my_transport->sendMessage            = ipx_send_message;
      my_transport->receiveMessage         = ipx_receive_message;
      my_transport->resolveAddress         = ipx_resolve_address;
      my_transport->getSocket              = ipx_get_socket;

      g_register_transport (my_transport);
      success = 1;
    }
#endif

#ifdef HAVE_INET6
  if (ipv6_init(dobind))
    {
      my_transport = g_malloc(sizeof(struct g_transport));

      my_transport->model 		   = AF_INET6;
      my_transport->name		   = "IPv6";
      my_transport->sendMessage            = ipv6_send_message;
      my_transport->receiveMessage         = ipv6_receive_message;
      my_transport->resolveAddress         = ipv6_resolve_address;
      my_transport->getSocket              = ipv6_get_socket;

      g_register_transport (my_transport);
      success = 1;
    }
#endif
  if (success)
    return TRUE;
  return FALSE;
}

/* EOF */
