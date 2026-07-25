#ifndef HANDLER_H
#define HANDLER_H

#include <stdint.h>
#include <stddef.h>

/* Well-known IP Protocol Numbers */
#define IP_PROTO_ICMP   1
#define IP_PROTO_TCP    6
#define IP_PROTO_UDP    17
#define IP_PROTO_ICMPV6 58

/* Context structure to pass IP layer data into sub-protocols */
typedef struct {
    const uint8_t *payload;   /* Pointer to layer 4 start (TCP/UDP header) */
    size_t length;            /* Remaining length of the packet */
    uint32_t src_ip_v4;       /* IPv4 source address (if applicable) */
    uint32_t dst_ip_v4;       /* IPv4 dest address (if applicable) */
    uint8_t src_ip_v6[16];    /* IPv6 source address (if applicable) */
    uint8_t dst_ip_v6[16];    /* IPv6 dest address (if applicable) */
    uint8_t is_ipv6;          /* Flag: 0 for IPv4, 1 for IPv6 */
} packet_ctx_t;

/* Function pointer type for protocol handlers */
typedef void (*proto_handler_fn)(const packet_ctx_t *ctx);

/* Core routing function to be called after parsing IP headers */
void route_ip_packet(uint8_t protocol_num, const packet_ctx_t *ctx);

#endif /* HANDLER_H */
