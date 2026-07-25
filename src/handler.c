#include "../include/handler.h"
#include <stdio.h>

/* Forward declarations of functions implemented in tcp.c, udp.c, etc. */
extern void handle_tcp(const packet_ctx_t *ctx);
extern void handle_udp(const packet_ctx_t *ctx);
extern void handle_icmp(const packet_ctx_t *ctx);

/* 
 * Direct-mapped lookup table for all 256 possible protocol numbers.
 * Elements not explicitly initialized will default to NULL.
 */
static const proto_handler_fn protocol_lookup_table[256] = {
    [IP_PROTO_TCP]  = handle_tcp,
    [IP_PROTO_UDP]  = handle_udp,
    [IP_PROTO_ICMP] = handle_icmp
};

/* Executes the constant-time O(1) lookup and routes the packet */
void route_ip_packet(uint8_t protocol_num, const packet_ctx_t *ctx) {
    if (ctx == NULL || ctx->payload == NULL) {
        return;
    }

    /* Look up the function pointer from the table */
    proto_handler_fn handler = protocol_lookup_table[protocol_num];

    if (handler != NULL) {
        /* Call the matched handler (jumps execution to tcp.c, udp.c, etc.) */
        handler(ctx);
    } else {
        /* Fallback for unhandled protocols */
        printf("Dropping packet: Unsupported protocol number %d\n", protocol_num);
    }
}
