#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <string.h>
#include <arpa/inet.h> 
#include <signal.h>
#include "../include/ethernet.h"
static volatile sig_atomic_t keep_running = 1;

static void handle_sigint(int signo) {
    (void)signo;
    keep_running = 0;
}


int create_raw_socket(){
    int sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if(sock_fd < 0){
        perror("Socket creation failed. Did you run as root with sudo?");
        exit(EXIT_FAILURE);
    }

    printf("socket successfully opened with fd: %d\n", sock_fd);

    struct sockaddr_ll la;
    memset(&la,0,sizeof(la));
    la.sll_family = AF_PACKET; 
    la.sll_protocol = htons(ETH_P_ALL);
    la.sll_ifindex = 0;

    if(bind(sock_fd,(struct sockaddr *)&la , sizeof(la)) < 0){
        perror("Bind failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Socket successfully bound to all interfaces.\n");
    return sock_fd;
}

void receive_packets(int sock_fd){
    unsigned char buffer[65536];
    struct sockaddr_ll addr;
    unsigned long packet_count = 0;

    // Register signal handler
    signal(SIGINT, handle_sigint);

    printf("Listening for packets... Press Ctrl+C to stop.\n");

    while(keep_running){
        socklen_t addr_len = sizeof(addr);
        ssize_t packet_size = recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_len);
        
        if(packet_size < 0){
            // Check if the read was broken by our Ctrl+C signal
            if (!keep_running) { 
                break; // Exit loop cleanly
            }
            
            perror("recvfrom failed");
            close(sock_fd);
            exit(EXIT_FAILURE);
        }
        parsing_the_ethernet_frame(buffer, packet_size, addr.sll_ifindex);

        packet_count++;
        printf("[%lu] Received packet of size: %zd bytes (Interface Index: %d)\n", 
               packet_count, packet_size, addr.sll_ifindex);
    }

    // This will now execute perfectly on Ctrl+C!
    printf("\nStopping capture. Total packets handled: %lu\n", packet_count);
    close(sock_fd);

   
}


