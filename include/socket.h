#ifndef SOCKET_H
#define SOCKET_H

int create_raw_socket();
void receive_packets(int sock_fd);

#endif // SOCKET_H