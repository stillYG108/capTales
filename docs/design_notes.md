# Design Notes

## 1) Experiment Scope
This project is a Linux packet-sniffer experiment focused on:
- Raw packet capture using AF_PACKET sockets
- Layered protocol parsing (Ethernet -> IPv4/IPv6 -> TCP/UDP/ICMP)
- Protocol dispatch through a small handler router
- Safe parsing with packet-length checks before header access

It is intentionally a learning implementation, not a full production analyzer.

## 2) Socket Configuration
The capture socket is created in src/socket.c with:
- Address family: AF_PACKET
- Socket type: SOCK_RAW
- Protocol: htons(ETH_P_ALL)

Configuration details:
- bind() uses sockaddr_ll
- sll_family = AF_PACKET
- sll_protocol = htons(ETH_P_ALL)
- sll_ifindex = 0 (listen on all interfaces)

Runtime behavior:
- receive loop uses recvfrom() into a 65536-byte buffer
- interface index is read from sockaddr_ll and printed
- SIGINT (Ctrl+C) sets a stop flag for clean shutdown
- total packet count is tracked and printed on exit

## 3) Parsing Pipeline
Current flow is strictly layered:

1. socket.c receives raw frame bytes
2. ethernet.c parses struct ethhdr
3. EtherType check:
	- ETH_P_IP -> ipv4.c
	- ETH_P_IPV6 -> ipv6.c
4. IPv4/IPv6 parser builds packet_ctx_t
5. handler.c dispatches by IP protocol number
6. tcp.c / udp.c / icmp.c parse L4 payload

## 4) Router and Handler Design
handler.c uses a direct lookup table indexed by protocol number:
- 6  (TCP)   -> handle_tcp
- 17 (UDP)   -> handle_udp
- 1  (ICMP)  -> handle_icmp
- 58 (ICMPv6)-> handle_icmp

This keeps dispatch O(1) and easy to extend.

## 5) Shared Packet Context
packet_ctx_t (include/handler.h) carries parsed IP-layer context into handlers:
- payload pointer to L4 bytes
- payload length
- IPv4 src/dst fields
- IPv6 src/dst fields
- is_ipv6 flag

Important detail:
- IPv4 parser fills src_ip_v4/dst_ip_v4
- IPv6 parser fills src_ip_v6/dst_ip_v6
- ICMP handler prints addresses based on is_ipv6

## 6) Safety Checks Implemented
The parser currently validates:
- Ethernet minimum frame header size
- IPv4 minimum header size and IHL validity
- IPv4 total length bounds
- IPv6 minimum base header size
- ICMP minimum header size before reading fields

These checks prevent out-of-bounds reads for truncated packets.

## 7) Current Limitations
This phase intentionally stops before deep protocol decoding. Not included yet:
- IPv6 extension header chain parsing
- TCP options decoding
- UDP payload interpretation
- Full ICMP/ICMPv6 message taxonomy
- Stateful flow tracking and reassembly

## 8) Next-Step Ideas (Future Phase)
If resumed later, natural next steps are:
- Add IPv6 extension-header walker before L4 dispatch
- Enrich TCP flag and option parsing
- Add ICMPv6-specific field formatting
- Add filters by interface/protocol/port
- Export structured output (JSON/pcap-like logging)
