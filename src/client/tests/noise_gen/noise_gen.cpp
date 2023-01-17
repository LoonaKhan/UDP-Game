//
// Created by loona on 15/01/23.
//

/*
 * tests out perlin noise generation
 *
 * does this by requesting chunks from the server and rendering them
 */

#include <thread>
#include <core.h>
#include <fmt/core.h>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "../../net/macros/macros.h"
#include "../../net/calls/calls.h"
#include "../../models/chunk/Chunk.h"
#include "../../models/block/Block.h"
#include "../../globvars/globvars.h"

using namespace glob;

void getChunks(net::UDPConn &c) {
    // continuously requests chunks until they are all recieved.
    // todo: if not all chunks have been recieved, this will unnecessarily call more. optimize
    for (;;) {
        if (logged_in && chunk::chunks.size() < 256) {
            for (int x=0; x<glob::RENDER_DIST; x++)
                for (int y=0; y < glob::RENDER_DIST; y++) {
                    int coords[] = {x,y};
                    c.send(net::get_chunk(cred, coords));
                }
        }
        else if (chunk::chunks.size() == 256) {
            fmt::print("size of chunks: {}\n", chunk::chunks.size());
            return;
        };
    }
}

int main() {
    /*
     * posts player and logs in.
     * sets up a listener thread.
     * for loop waiting for the player to be logged in
     * if so, render all chunks, from an array
     */

    // login vars
    std::string uname = "loona";

    // connection
    char HOST[] = "127.0.0.1";
    int PORT = 4000;
    auto c = net::UDPConn(HOST, PORT);

    std::thread listener(net::readRes, std::ref(c)); // recieves bytes

    // post_player and login
    auto bytesSent = c.send(net::post_player(uname));
    fmt::print("{} Bytes sent\n", bytesSent);


    { // todo: wait without a cond var?
        std::unique_lock l_posted(*Mposted_plr_ptr);
        fmt::print("waiting on player thread to login\n");
        cv_plr.wait(l_posted, []{return player_exists;});
        bytesSent = c.send(net::login(uname));
        fmt::print("{} Bytes sent\n", bytesSent);
    }

    // requests chunks when the player logs in
    {
        std::unique_lock l_logged_in(*Mlogged_in_ptr);
        fmt::print("waiting on log in thread to start req'ing chunks\n");
        cv_logged.wait(l_logged_in, []{return logged_in;});
        static std::thread ReqChunks(getChunks, std::ref(c));
    }

    // draws the chunks
    for (;;) {

    }

}