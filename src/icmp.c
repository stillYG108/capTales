#include "../include/handler.h"
#include <stdio.h>

void handle_icmp(const packet_ctx_t *ctx) {
	if (ctx == NULL) {
		return;
	}

	printf("ICMP handler invoked. Payload length: %zu bytes\n", ctx->length);
}
