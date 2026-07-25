#include "../include/handler.h"
#include <stdio.h>

void handle_tcp(const packet_ctx_t *ctx) {
    if (ctx == NULL) {
        return;
    }

    printf("TCP handler invoked. Payload length: %zu bytes\n", ctx->length);
}
