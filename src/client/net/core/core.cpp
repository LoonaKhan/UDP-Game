//
// Created by loona on 31/12/22.
//

#include "core.h"
#include "iostream"

net::UDPConn::UDPConn(char *host, uint port) {
    if ((this->sock = socket(AF_INET, SOCK_DGRAM, 0)) <0) {
        std::cout << "Cant create socket" << std::endl;
        exit(-1);
    }

    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = inet_addr(host);
    this->addr.sin_port = htons(port);

    this->addr_len = sizeof(addr);
}

net::UDPConn::~UDPConn() {
    close(this->sock);
}

ssize_t net::UDPConn::send(const char *buffer, int buffer_len) {
    return sendto(this->sock, buffer, buffer_len, 0, (struct sockaddr *)&this->addr, this->addr_len);
}

ssize_t net::UDPConn::recieve(char *buffer, int buffer_len) {
    return recv(this->sock, buffer, buffer_len, 0);
}