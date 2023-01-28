//
// Created by loona on 15/01/23.
//

#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <condition_variable>
#include <mutex>
//#include <unique_lock>
using json = nlohmann::json;


namespace glob{
    // our json config
    extern const json g;
    extern const int RENDER_DIST;

    // player mutexes. makes sure the player exists before we login
    extern std::mutex Mposted_plr;
    extern std::mutex *Mposted_plr_ptr;
    extern std::condition_variable cv_plr;
    extern bool player_exists;

    // login mutexes. player must be logged in before we can play
    extern std::mutex Mlogged_in;
    extern std::mutex *Mlogged_in_ptr;
    extern std::condition_variable cv_logged;
    extern bool logged_in;
    extern int cred;

    // chunks mutexes. ensures
    extern std::mutex MChunks;
    extern std::mutex *MChunks_ptr;
    extern std::condition_variable cv_chunks;
    extern bool cswitch_turns;


    // graphical
    extern const int BLOCK_SIZE;
    extern const int CHUNK_SIZE;
}


