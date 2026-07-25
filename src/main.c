#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <string.h>
#include <arpa/inet.h> 
#include "../include/socket.h"
#include "../include/ethernet.h"
#include "../include/ipv4.h"
#include "../include/ipv6.h"



int main() {
    int sock_fd = create_raw_socket();
    receive_packets(sock_fd);

    return 0;
}