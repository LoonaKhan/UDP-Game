//
// Created by loona on 02/01/23.
//

#include "macros.h"
#include "iostream"

void net::verifyOnline(net::UDPConn &c, int id) { // continuously pings the server to prevent timeouts
    for (;;){
        sleep_for(seconds(4)); // set this to the globvars
        auto req = "{"+fmt::format("\"method\":\"syn\", \"cred\":{}", id)+"}|{}";
        c.send(req);
    }
}


void net::updateCred(int id, int &cred, bool &logged_in) { // updates credentials.
    cred = id;
    logged_in = true;
}

void net::readRes(net::UDPConn &c, int &cred, bool &logged_in) { // reads and handle the responses from the server in its own thread
    for (;;) { // runs indefinitely
        char buffer[8192];
        auto n = c.recieve(buffer, sizeof(buffer)); // recieve data
        buffer[n] = '\0';

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
                    updateCred(body["id"], cred, logged_in);
                    static std::thread vOnline(
                            net::verifyOnline, std::ref(c),
                            cred); // static otherwise the thread would terminate after the scope ends
                } else throw ("Not logged in");
            } catch (std::string errmsg){
                fmt::print("err: {}", errmsg);
            }
        }
        if (header["method"] != "players")
            fmt::print("response: {}\n", (std::string)buffer);
    }
}