//
// Created by loona on 31/12/22.
//

#include "requests.h"
#include "iostream"

int net::UDPSock() {
    return socket(AF_INET, SOCK_DGRAM, 0);
}

sockaddr_in net::setUDPAddr(char *host, uint port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host);
    addr.sin_port = htons(port);

    return addr;
}

ssize_t net::send(int &sock, std::string buffer, int buffer_len, sockaddr *addr, socklen_t addr_len) {
    std::cout << "request: \nsock: " << sock << "\nbuffer: " << buffer
    << "\nbuffer len: " << buffer_len << std::endl;
    return sendto(
            sock,
            buffer.c_str(),buffer_len,
            0,
            addr, addr_len
                    );
}

ssize_t net::recieve(int &sock, char *buffer) {
    return recv(sock, buffer, sizeof(buffer), 0);
}