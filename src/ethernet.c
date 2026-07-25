#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <string.h>
#include <arpa/inet.h>

#include "../include/ethernet.h"
#include "../include/ipv4.h"
#include "../include/ipv6.h"

void parsing_the_ethernet_frame(unsigned char *packet, ssize_t packet_len, int ifindex){
   if (packet_len < (ssize_t)sizeof(struct ethhdr)) {
      printf("Truncated Ethernet frame on interface %d (length: %zd)\n", ifindex, packet_len);
      return;
   }

   struct ethhdr *eth = (struct ethhdr *)packet;

   printf("Ethernet Header\n");
   printf("   |-Destination Address : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X \n", 
         eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], 
         eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
   printf("   |-Source Address      : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X \n", 
         eth->h_source[0], eth->h_source[1], eth->h_source[2], 
         eth->h_source[3], eth->h_source[4], eth->h_source[5]);

   printf("   |-Protocol            : %u \n", ntohs(eth->h_proto));
   printf("   |-Interface Index     : %d\n", ifindex);
   printf("Protocol Type: 0x%04x\n", ntohs(eth->h_proto));

   if (ntohs(eth->h_proto) == ETH_P_IP) {
      printf("This is an IPv4 packet!\n");
      parsing_the_ipv4_packet(packet + sizeof(struct ethhdr),
                        packet_len - (ssize_t)sizeof(struct ethhdr));
   } else if (ntohs(eth->h_proto) == ETH_P_IPV6) {
      printf("This is an IPv6 packet!\n");
      parsing_the_ipv6_packet(packet + sizeof(struct ethhdr),
                        packet_len - (ssize_t)sizeof(struct ethhdr));
   }
}