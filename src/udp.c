#include "../include/handler.h"
#include <stdio.h>

void handle_udp(const packet_ctx_t *ctx) {
    if (ctx == NULL) {
        return;
    }

    printf("UDP handler invoked. Payload length: %zu bytes\n", ctx->length);
}
