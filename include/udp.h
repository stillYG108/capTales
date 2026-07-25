#ifndef UDP_H
#define UDP_H  

#include "../include/handler.h"
void handle_udp(const packet_ctx_t *ctx);
void parsing_the_udp_segment(const packet_ctx_t *ctx);

#endif /* UDP_H */