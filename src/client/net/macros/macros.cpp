//
// Created by loona on 02/01/23.
//

#include "macros.h"
#include "iostream"

using namespace glob;

void net::verifyOnline(net::UDPConn &c) { // continuously pings the server to prevent timeouts
    for (;;){
        sleep_for(seconds(4)); // set this to the globvars
        auto req = "{"+fmt::format("\"method\":\"syn\", \"cred\":{}", cred)+"}|{}";
        c.send(req);
    }
}


void net::updateCred(int id) { // updates credentials.
    cred = id;
    logged_in = true;
}

void net::readRes(net::UDPConn &c) { // reads and handle the responses from the server in its own thread
    for (;;) { // runs indefinitely
        char buffer[8192];
        auto n = c.recieve(buffer, sizeof(buffer)); // recieve data
        buffer[n] = '\0';

        // locks
        std::unique_lock lock_logged(*Mlogged_in_ptr);
        std::unique_lock lock_posted(*Mposted_plr_ptr);

        // parse header
        int idx = net::seperate(buffer, '|');
        std::string head = ((std::string)buffer).substr(0, idx);
        auto header = json::parse(head);

        // logic
        if (header["method"] == "login") {
            // if we login, parse the body, update user credentials and start another thread to verify we are online
            try {
                json body = json::parse(((std::string) buffer).substr(idx + 1));
                if (body.contains("id")){
                    // if we logged in, lock, set logged_in to true and then unlock
                    // start the verify online thread


                    fmt::print("in login\n");

                    updateCred(body["id"]);
                    fmt::print("logged in\n");
                    lock_logged.unlock();
                    cv_logged.notify_one();

                    static std::thread vOnline(
                            net::verifyOnline,
                            std::ref(c)); // static otherwise the thread would terminate after the scope ends
                }
                else throw ("Not logged in");
            }
            catch (std::string errmsg){
                fmt::print("err: {}", errmsg);
            }
        }
        else if (header["method"] == "get_chunk") { // recieves a chunk and appends it

            char *body = buffer + idx+1;
            auto new_c = chunk::Chunk(body, n-(idx+1));
            chunk::chunks.insert({std::vector<int>{new_c.getCoords()[0], new_c.getCoords()[1]}, new_c});
            fmt::print("Chunk: [{},{}] | [{}] | {}\n",
                       new_c.getCoords()[0], new_c.getCoords()[1],
                       (int)new_c.getBlock(new char[]{0,0}).getColour(),
                       chunk::chunks.size()
                       );
        }
        else if (header["method"] == "post_player") {
            // we dont care about the response
            // either the player already exists, or we create them
            fmt::print("player has been posted\n");
            player_exists = true;
            cv_plr.notify_one();
            lock_posted.unlock();
        }
        if (header["method"] != "players") {
            //fmt::print("response: {}\n", (std::string) buffer);
        }
    }
}