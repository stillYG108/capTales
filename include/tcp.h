#ifndef TCP_H
#define TCP_H   

#include "../include/handler.h"

void handle_tcp(const packet_ctx_t *ctx);
void parcing_the_tcp_segment(const packet_ctx_t *ctx);

#endif /* TCP_H */