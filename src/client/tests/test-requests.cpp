//
// Created by loona on 01/01/23.
//


#include <requests.h>
#include <iostream>

int main() {
    char HOST[] = "127.0.0.1";
    int PORT  = 4000;

    char bufferReq[] = "{\"method\":\"post_player\"}|{\"name\": \"mon\"}";
    char bufferRes[1024] = {0};

    auto c = net::UDPConn(HOST, PORT);

    auto bytesSent = c.send(bufferReq, sizeof(bufferReq)-1);
    std::cout << "bytes sent: " << bytesSent << std::endl;

    auto bytesRecv = c.recieve(bufferRes, sizeof(bufferRes));
    std::cout << bytesRecv << " bytes recieved\n" << "buffer: " << bufferRes;
}