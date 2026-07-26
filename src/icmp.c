#include "../include/handler.h"
#include <stdio.h>
#include <arpa/inet.h>

void parsing_the_icmp_packet(const packet_ctx_t *ctx) {
	if (ctx == NULL || ctx->payload == NULL) {
		return;
	}

	printf("ICMP Packet Details:\n");
	printf("Payload Length: %zu bytes\n", ctx->length);

	if (ctx->is_ipv6) {
		char src_str[INET6_ADDRSTRLEN];
		char dst_str[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, ctx->src_ip_v6, src_str, sizeof(src_str));
		inet_ntop(AF_INET6, ctx->dst_ip_v6, dst_str, sizeof(dst_str));
		printf("Source IP: %s\n", src_str);
		printf("Destination IP: %s\n", dst_str);
	} else {
		struct in_addr src_addr;
		struct in_addr dst_addr;
		src_addr.s_addr = ctx->src_ip_v4;
		dst_addr.s_addr = ctx->dst_ip_v4;
		printf("Source IP: %s\n", inet_ntoa(src_addr));
		printf("Destination IP: %s\n", inet_ntoa(dst_addr));
	}
	
	// Ensure payload has at least the minimum ICMP header size (8 bytes)
	if (ctx->length < 8) {
		printf("Error: Payload too short for ICMP header\n");
		return;
	}

	// Extract standard ICMP core fields from payload
	uint8_t type = ctx->payload[0];
	uint8_t code = ctx->payload[1];
	uint16_t checksum = (ctx->payload[2] << 8) | ctx->payload[3];

	printf("ICMP Type: %u\n", type);
	printf("ICMP Code: %u\n", code);
	printf("Checksum: 0x%04X\n", checksum);

	// Parse type-specific fields
	if (type == 8 || type == 0) {
		// Echo Request (8) or Echo Reply (0)
		uint16_t id = (ctx->payload[4] << 8) | ctx->payload[5];
		uint16_t sequence = (ctx->payload[6] << 8) | ctx->payload[7];

		printf("Echo Message: %s\n", (type == 8) ? "Request" : "Reply");
		printf("Identifier: %u\n", id);
		printf("Sequence Number: %u\n", sequence);
	} 
	else if (type == 3) {
		// Destination Unreachable
		printf("Message: Destination Unreachable\n");
		if (code == 4 && ctx->length >= 8) {
			// Fragmentation Needed code contains Next-Hop MTU in bytes 6-7
			uint16_t mtu = (ctx->payload[6] << 8) | ctx->payload[7];
			printf("Next-Hop MTU: %u\n", mtu);
		}
	} 
	else if (type == 5) {
		// Redirect Message
		uint32_t gateway = ((uint32_t)ctx->payload[4] << 24) |
		                   ((uint32_t)ctx->payload[5] << 16) |
		                   ((uint32_t)ctx->payload[6] << 8)  |
		                   ctx->payload[7];
		printf("Message: Redirect\n");
		printf("Gateway Internet Address: %u\n", gateway);
	} 
	else if (type == 11) {
		// Time Exceeded
		printf("Message: Time Exceeded\n");
	} 
	else {
		// Other unhandled ICMP types
		uint32_t rest_of_header = ((uint32_t)ctx->payload[4] << 24) |
		                          ((uint32_t)ctx->payload[5] << 16) |
		                          ((uint32_t)ctx->payload[6] << 8)  |
		                          ctx->payload[7];
		printf("Rest of Header: 0x%08X\n", rest_of_header);
	}
}


void handle_icmp(const packet_ctx_t *ctx) {
	if (ctx == NULL) {
		return;
	}

	printf("ICMP handler invoked. Payload length: %zu bytes\n", ctx->length);
	parsing_the_icmp_packet(ctx);
}
