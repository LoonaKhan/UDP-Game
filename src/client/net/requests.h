//
// Created by loona on 31/12/22.
//

#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
// h

namespace net {

    int UDPSock(); // creates a socket

    sockaddr_in setUDPAddr(char host[], uint port); // sets the address of the socket

    ssize_t send(int &sock, std::string buffer, int buffer_len, sockaddr *addr, socklen_t addr_len); // sends data from a buffer

    ssize_t recieve(int &sock, char buffer[]); // recieves data and puts it into a buffer
}
