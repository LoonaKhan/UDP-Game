//
// Created by loona on 31/12/22.
//
#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define PORT 4000
#define HOST "127.0.0.1"

int main() {
    char bufferReq[] = "{\"method\":\"post_player\"}|{\"name\": \"mon\"}";
    char bufferRes[1024] = {0};
    int sock;

    // create socket
    if ((sock = socket(
                    AF_INET, // ipv4
                    SOCK_DGRAM, // udp
                    0        // protocol
                    )) <0) {
        std::cout << "cannot create socket" << std::endl;
        exit(-1);

    }

    //identify socket names - give socket info of the server and client
    struct sockaddr_in server, client;
    socklen_t  client_len = sizeof(client);
    socklen_t server_len = sizeof(server);

    server.sin_family = AF_INET; // ipv4
    server.sin_port = htons(PORT); // port      htons = (host to network socket)
    server.sin_addr.s_addr = inet_addr(HOST); // the host

    // send message
    ssize_t reqBytes = sendto(sock,
                         bufferReq,
                         sizeof(bufferReq)-1, // we subtract 1 to remove the terminating character
                         0,
                         (struct sockaddr *)&server,
                              sizeof(server));
    std::cout << reqBytes << " bytes sent" << std::endl;

    ssize_t resByte = recv(sock, bufferRes, sizeof(bufferRes), 0);
    std::cout << resByte << " bytes recieved: " << bufferRes << std::endl;

    close(sock);
    return 0;


}