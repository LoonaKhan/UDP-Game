//
// Created by loona on 04/01/23.
//

#pragma once

#include <string>
#include <fmt/core.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace net {
    /*
     * Each of these methods correspond to a route on the server.
     *
     * These functions format and return the json string data to be sent to the server.
     * The benefit of this is being able to handle arguments rather than static strings.
     */

    std::string post_player(std::string &name);

    std::string login(std::string &name);

    std::string update_pos(int &cred, int coords[]);

    std::string get_chunk(int &cred, int chunk_coords[]);

    // post chunk updates
}