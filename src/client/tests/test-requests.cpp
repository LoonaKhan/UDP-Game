//
// Created by loona on 01/01/23.
//


#include <core.h>
#include <fmt/core.h>
#include <thread>

#include "../net/macros/macros.h"
#include "../net/calls/calls.h"

using namespace std::chrono;
using namespace std::this_thread; // sleep_for, sleep_until

int main() {

    // our requests
    std::string name = "mon";
    auto post_player = net::post_player(name);
    auto login = net::login(name);

    // setup connection
    char HOST[] = "127.0.0.1";
    int PORT  = 4000;
    int cred;
    auto c = net::UDPConn(HOST, PORT); // connect

    // start listening
    std::thread listener(net::readRes, std::ref(c), std::ref(cred));

    // send requests
    auto bytesSent = c.send(post_player);
    fmt::print("{} Bytes sent\n", bytesSent);

    bytesSent = c.send(login);
    fmt::print("{} Bytes sent\n", bytesSent);

    int coords[] = {10,10};
    bytesSent = c.send(net::update_pos(cred, coords)); // todo: does not update cred
    fmt::print("{} Bytes sent\n", bytesSent);

    // for loop for the game
    for (;;) {
        continue;
    }
}