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

#include "../../net/macros/macros.h"
#include "../../net/calls/calls.h"
#include "../../models/chunk/Chunk.h"
#include "../../models/block/Block.h"
#include "../../globvars/globvars.h"

void getChunks(net::UDPConn &c, int &cred, bool &logged_in) {
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
        else if (chunk::chunks.size() == 256) return;
    }
} //todo: test

int main() {
    /*
     * posts player and logs in.
     * sets up a listener thread.
     * for loop waiting for the player to be logged in
     * if so, render all chunks, from an array
     */

    // login vars
    int cred;
    bool logged_in = false;
    std::string uname = "loona";

    // connection
    char HOST[] = "127.0.0.1";
    int PORT = 4000;
    auto c = net::UDPConn(HOST, PORT);

    std::thread listener(net::readRes, std::ref(c), std::ref(cred), std::ref(logged_in)); // recieves bytes

    // post_player and login
    // todo: can throw an error if packages are sent incorrectly and player didnt get created
    // todo: wait for player to be created first. we need waitgroup equivalents
    auto bytesSent = c.send(net::post_player(uname));
    fmt::print("{} Bytes sent\n", bytesSent);
    bytesSent = c.send(net::login(uname));
    fmt::print("{} Bytes sent\n", bytesSent);

    /* chunk sending loop
     * continuously runs until the user is logged in,
     * then, it starts a thread to request all chunks
     * todo: how to make a thread wait until a condition. wait groups cpp
     */
    for (;;) {
        if (logged_in) {
            static std::thread ReqChunks(getChunks,
                                         std::ref(c), std::ref(cred), std::ref(logged_in));
            break;
        }
    }

    // draws the chunks
    for (;;) {

    }

}