#include <stdio.h>
#include <linux/tcp.h>
#include <linux/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <string.h>
#include <arpa/inet.h> 
#include <signal.h>
#include "../include/ethernet.h"
#include "../include/handler.h"



void parcing_the_tcp_segment(const packet_ctx_t *ctx) {
    if (ctx == NULL || ctx->payload == NULL) {
        return;
    }
        
    struct tcphdr *tcp = (struct tcphdr *)(ctx->payload);
    printf("Source Port: %d\n", ntohs(tcp->source));
    printf("Dest Port: %d\n", ntohs(tcp->dest));
    printf("Sequence Number: %u\n", ntohl(tcp->seq));
    
    
    if (tcp->syn && tcp->ack) {
        printf("Packet status: SYN-ACK (Connection accepted)\n");
     } else if (tcp->syn) {
        printf("Packet status: SYN (Connection request)\n");
    } else if (tcp->fin) {
        printf("Packet status: FIN (Connection closing)\n");
    }
    
}

void handle_tcp(const packet_ctx_t *ctx) {
    if (ctx == NULL) {
        return;
    }

    printf("TCP handler invoked. Payload length: %zu bytes\n", ctx->length);
    parcing_the_tcp_segment(ctx);
}
