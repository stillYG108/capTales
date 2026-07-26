# Header Layouts Used In This Project

## 1) Project Header Files (include/)

### socket.h
- create_raw_socket()
- receive_packets(int sock_fd)

Purpose: raw socket setup and packet receive loop.

### ethernet.h
- parsing_the_ethernet_frame(unsigned char *packet, ssize_t packet_len, int ifindex)

Purpose: Layer-2 parsing and EtherType-based forwarding.

### ipv4.h
- parsing_the_ipv4_packet(unsigned char *packet, ssize_t packet_len)

Purpose: IPv4 header parsing and protocol handoff.

### ipv6.h
- parsing_the_ipv6_packet(unsigned char *packet, ssize_t packet_len)

Purpose: IPv6 base-header parsing and next-header handoff.

### handler.h
- Protocol constants (ICMP, TCP, UDP, ICMPv6)
- packet_ctx_t shared context
- route_ip_packet(uint8_t protocol_num, const packet_ctx_t *ctx)

Purpose: protocol dispatch interface and shared parser context.

### tcp.h
- handle_tcp(const packet_ctx_t *ctx)
- parsing_the_tcp_segment(const packet_ctx_t *ctx)

### udp.h
- handle_udp(const packet_ctx_t *ctx)
- parsing_the_udp_segment(const packet_ctx_t *ctx)

### icmp.h
- handle_icmp(const packet_ctx_t *ctx)
- parsing_the_icmp_packet(const packet_ctx_t *ctx)

Purpose for tcp.h/udp.h/icmp.h: L4 handler entry points and parsing functions.

## 2) On-Wire Protocol Header Layouts

### Ethernet II Header (14 bytes)
- Destination MAC: 6 bytes (offset 0)
- Source MAC: 6 bytes (offset 6)
- EtherType: 2 bytes (offset 12)

Used struct: struct ethhdr

### IPv4 Header (minimum 20 bytes)
- Version + IHL: 1 byte
- TOS: 1 byte
- Total Length: 2 bytes
- Identification: 2 bytes
- Flags + Fragment Offset: 2 bytes
- TTL: 1 byte
- Protocol: 1 byte
- Header Checksum: 2 bytes
- Source Address: 4 bytes
- Destination Address: 4 bytes
- Options: variable (if IHL > 5)

Used struct: struct iphdr

### IPv6 Base Header (40 bytes)
- Version + Traffic Class + Flow Label: 4 bytes
- Payload Length: 2 bytes
- Next Header: 1 byte
- Hop Limit: 1 byte
- Source Address: 16 bytes
- Destination Address: 16 bytes

Used struct: struct ip6_hdr

### TCP Header (minimum 20 bytes)
- Source Port: 2 bytes
- Destination Port: 2 bytes
- Sequence Number: 4 bytes
- Acknowledgment Number: 4 bytes
- Data Offset + Reserved + Flags: 2 bytes
- Window Size: 2 bytes
- Checksum: 2 bytes
- Urgent Pointer: 2 bytes
- Options: variable

Used in tcp.c for basic field extraction.

### UDP Header (8 bytes)
- Source Port: 2 bytes
- Destination Port: 2 bytes
- Length: 2 bytes
- Checksum: 2 bytes

Used in udp.c for basic field extraction.

### ICMP / ICMPv6 Common 8-byte Start
- Type: 1 byte
- Code: 1 byte
- Checksum: 2 bytes
- Rest-of-header / type-specific: 4 bytes

Used in icmp.c with minimum-length validation before read.

## 3) Parsing Order in This Codebase
Ethernet header -> IPv4 or IPv6 header -> route by protocol number -> TCP/UDP/ICMP parser.
