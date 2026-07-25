#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <string.h>
#include <netinet/ip.h>
#include <arpa/inet.h> 
#include "../include/ipv4.h"


void parsing_the_ipv4_packet(unsigned char *packet, ssize_t packet_len){
    
   struct iphdr *ip = (struct iphdr *)packet;
    
   if (packet_len < (ssize_t)sizeof(struct iphdr)) {
      printf("Truncated IPv4 packet (length: %zd)\n", packet_len);
      return;
   }

   struct in_addr src_addr, dest_addr;
   src_addr.s_addr = ip->saddr;
   dest_addr.s_addr = ip->daddr;

   printf("IPv4 Header\n");
   printf("   |-Version        : %d\n", (unsigned int)ip->version);
   printf("   |-Header Length  : %d DWORDS or %d Bytes\n", (unsigned int)ip->ihl, ((unsigned int)(ip->ihl))*4);
   printf("   |-Type Of Service: %d\n", (unsigned int)ip->tos);
   printf("   |-Total Length   : %d Bytes\n", ntohs(ip->tot_len));
   printf("   |-Identification : %d\n", ntohs(ip->id));
   printf("   |-TTL            : %d\n", (unsigned int)ip->ttl);
   printf("   |-Protocol       : %d\n", (unsigned int)ip->protocol);
   printf("   |-Checksum       : %d\n", ntohs(ip->check));
   printf("   |-Source IP      : %s\n", inet_ntoa(src_addr));
   printf("   |-Destination IP : %s\n", inet_ntoa(dest_addr));
}