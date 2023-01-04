//
// Created by loona on 01/01/23.
//


#include <core.h>
#include <fmt/core.h>
#include <thread>

#include "../net/macros/macros.h"

using namespace std::chrono;
using namespace std::this_thread; // sleep_for, sleep_until

int main() {

    // our requests
    char post_player[] = "{\"method\":\"post_player\"}|{\"name\": \"mon\"}";
    char login[] = "{\"method\":\"login\"}|{\"name\": \"mon\"}";

    // setup connection
    char HOST[] = "127.0.0.1";
    int PORT  = 4000;
    int cred;
    auto c = net::UDPConn(HOST, PORT); // connect

    // start listening
    std::thread listener(net::readRes, std::ref(c), std::ref(cred));

    // send requests
    auto bytesSent = c.send(post_player, sizeof(post_player)-1);
    fmt::print("{} Bytes sent\n", bytesSent);

    bytesSent = c.send(login, sizeof(login)-1);
    fmt::print("{} Bytes sent\n", bytesSent);

    // for loop for the game
    for (;;) {
        continue;
    }
}