//
// Created by loona on 15/01/23.
//

#include "globvars.h"

namespace glob {

    std::ifstream f("src/client/globvars/globvars.json");
    const json g = json::parse(f);
    const int RENDER_DIST = g["RENDER_DISTANCE"];

    std::mutex Mposted_plr;
    std::mutex *Mposted_plr_ptr = &Mposted_plr;
    std::condition_variable cv_plr;
    bool player_exists = false;

    std::mutex Mlogged_in;
    std::mutex* Mlogged_in_ptr = &Mlogged_in;
    std::condition_variable cv_logged;
    bool logged_in = false;
    int cred;


}