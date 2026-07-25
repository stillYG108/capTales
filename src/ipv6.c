#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <string.h>
#include <netinet/ip6.h>
#include <arpa/inet.h> 
#include "../include/ipv6.h"


void parsing_the_ipv6_packet(unsigned char *packet, ssize_t packet_len){
    
   struct ip6_hdr *ip6 = (struct ip6_hdr *)packet;
    
   if (packet_len < (ssize_t)sizeof(struct ip6_hdr)) {
      printf("Truncated IPv6 packet (length: %zd)\n", packet_len);
      return;
   }

   char src_addr[INET6_ADDRSTRLEN];
   char dest_addr[INET6_ADDRSTRLEN];

   inet_ntop(AF_INET6, &(ip6->ip6_src), src_addr, INET6_ADDRSTRLEN);
   inet_ntop(AF_INET6, &(ip6->ip6_dst), dest_addr, INET6_ADDRSTRLEN);

   printf("IPv6 Header\n");
   printf("   |-Version        : %d\n", (unsigned int)((ntohl(ip6->ip6_flow) >> 28) & 0x0F));
   printf("   |-Traffic Class  : %d\n", (unsigned int)((ntohl(ip6->ip6_flow) >> 20) & 0xFF));
   printf("   |-Flow Label     : %d\n", (unsigned int)(ntohl(ip6->ip6_flow) & 0xFFFFF));
   printf("   |-Payload Length : %d Bytes\n", ntohs(ip6->ip6_plen));
   printf("   |-Next Header    : %d\n", (unsigned int)ip6->ip6_nxt);
   printf("   |-Hop Limit      : %d\n", (unsigned int)ip6->ip6_hlim);
   printf("   |-Source IP      : %s\n", src_addr);
   printf("   |-Destination IP : %s\n", dest_addr);
}