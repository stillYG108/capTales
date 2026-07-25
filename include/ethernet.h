#ifndef ETHERNET_H
#define ETHERNET_H

#include <sys/types.h>

void parsing_the_ethernet_frame(unsigned char *packet, ssize_t packet_len, int ifindex);

#endif // ETHERNET_H