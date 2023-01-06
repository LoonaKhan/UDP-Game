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
    bool logged_in;
    auto c = net::UDPConn(HOST, PORT); // connect

    // start listening
    std::thread listener(net::readRes, std::ref(c), std::ref(cred), std::ref(logged_in));

    // send requests
    auto bytesSent = c.send(post_player);
    fmt::print("{} Bytes sent\n", bytesSent);

    bytesSent = c.send(login);
    fmt::print("{} Bytes sent\n", bytesSent);

    /* wait a while for the other thread to recieve the login request.
    todo: have a login bool var. if true, continue with the rest of the game
        wait until we are logged in to start rendering
     */

    // for loop for the game
    for (;;) {
        if (logged_in){
            std::string method;
            fmt::print("enter which method you would like to call\n");
            std::cin >> method;

            if (method == "update_pos") {
                int coords[] = {10, 10};
                bytesSent = c.send(net::update_pos(cred, coords));
                fmt::print("{} Bytes sent\n", bytesSent);
            }
            else if (method == "get_chunks") {
                int chunk_coords[] = {0,0};
                bytesSent = c.send(net::get_chunks(cred, chunk_coords));
                fmt::print("{} Bytes sent\n", bytesSent);
            }
        }
    }
}