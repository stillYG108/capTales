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
#include <linux/udp.h>
#include <stdio.h>

#include "../include/handler.h"

void parsing_the_udp_segment(const packet_ctx_t *ctx) {
    if (ctx == NULL || ctx->payload == NULL) {
        return;
    }

    if (ctx->length < sizeof(struct udphdr)) {
        printf("Truncated UDP datagram (length: %zu)\n", ctx->length);
        return;
    }

    struct udphdr *udp = (struct udphdr *)(ctx->payload);
    printf("Source Port: %d\n", ntohs(udp->source));
    printf("Dest Port: %d\n", ntohs(udp->dest));
    printf("Length: %d\n", ntohs(udp->len));
    printf("Checksum: %d\n", ntohs(udp->check));
}



void handle_udp(const packet_ctx_t *ctx) {
    if (ctx == NULL) {
        return;
    }

    printf("UDP handler invoked. Payload length: %zu bytes\n", ctx->length);
    parsing_the_udp_segment(ctx);
}
