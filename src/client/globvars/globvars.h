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
    extern const json g;
    extern const int RENDER_DIST;

    extern std::mutex Mposted_plr;
    extern std::mutex *Mposted_plr_ptr;
    extern std::condition_variable cv_plr;
    extern bool player_exists;

    extern std::mutex Mlogged_in;
    extern std::mutex *Mlogged_in_ptr;
    extern std::condition_variable cv_logged;
    extern bool logged_in;
    extern int cred;


}


