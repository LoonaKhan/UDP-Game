//
// Created by loona on 07/01/23.
//
#include <arpa/inet.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "block.h"
#include "chrono"
#include "thread"

#define PORT 4000
#define HOST "127.0.0.1"

using namespace std::chrono;
using namespace std::this_thread; // sleep_for, sleep_until

int main() {
    char bufferReq[] = "{\"method\":\"post_player\"}|{\"name\": \"mon\"}";
    char coords[] = {20,20},
            chunk_coords[] = {40,30},
            colour = 2,
            height=1;
    block b = block(coords, chunk_coords, colour, height);
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
    for (;;){
        ssize_t reqBytes = sendto(sock,
                                  &b,
                                  sizeof(b), // we subtract 1 to remove the terminating character
                                  0,
                                  (struct sockaddr *) &server,
                                  sizeof(server));
        std::cout << reqBytes << " bytes sent" << std::endl;
        sleep_for(seconds(1));
    }

    //ssize_t resByte = recv(sock, bufferRes, sizeof(bufferRes), 0);
    //std::cout << resByte << " bytes recieved: " << bufferRes << std::endl;

    //close(sock);
    return 0;


}