//
// Created by loona on 31/12/22.
//

#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

namespace net {

    class UDPConn {
    private:
        int sock;
        sockaddr_in addr;
        socklen_t addr_len;
    public:
        UDPConn(char *host, uint port);

        ssize_t send(char buffer[], int buffer_len);

        ssize_t recieve(char buffer[], int buffer_len);

        void close();
    };
}
