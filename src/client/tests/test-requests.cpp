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
    int sock;

    if ((sock = net::UDPSock()) < 0) {
        std::cout << "cant creat socket\n";
        exit(-1);
    }
    auto server = net::setUDPAddr(HOST, PORT);

    //auto bytesSent = sendto(sock, bufferReq, sizeof(bufferReq)-1, 0, (struct sockaddr *)&server, sizeof(server));
    auto bytesSent = net::send(sock, bufferReq, sizeof(bufferReq)-1,(struct sockaddr *)&server, sizeof(server));
    std::cout << bytesSent << " bytes sent\n";

    auto bytesRecv = net::recieve(sock, bufferRes);
    std::cout << bytesRecv << " bytes recieved\n";

}