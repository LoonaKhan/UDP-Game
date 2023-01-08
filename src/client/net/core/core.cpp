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

ssize_t net::UDPConn::send(std::string req) {
    char *buffer = new char[req.length()+1];
    strcpy(buffer, req.c_str());
    auto ret =  sendto(this->sock, buffer, strlen(buffer), 0, (struct sockaddr *)&this->addr, this->addr_len);
    delete[] buffer;
    return ret;
}

ssize_t net::UDPConn::recieve(char *buffer, int buffer_len) const {
    return recv(this->sock, buffer, buffer_len, 0);
}

template <typename T>
ssize_t net::UDPConn::send_bin(T data) {
    sendto(this->sock, data, sizeof(data), 0, (struct sockaddr *)&this->addr, this->addr_len);
}