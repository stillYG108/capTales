#ifndef ICMP_H
#define ICMP_H   

#include "../include/handler.h"

void handle_icmp(const packet_ctx_t *ctx);
void parsing_the_icmp_packet(const packet_ctx_t *ctx);

#endif /* ICMP_H */