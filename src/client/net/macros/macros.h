//
// Created by loona on 02/01/23.
//

#pragma once

#include <core.h>
#include <fmt/core.h>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>
#include "../parser/parser.h"
#include "../../models/chunk/Chunk.h"
#include "../../globvars/globvars.h"
#include "../calls/calls.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using json = nlohmann::json;

namespace net {
    void verifyOnline(net::UDPConn &c);

    void readRes(net::UDPConn &c);

    void updateCred(int id);

    void reqChunks(net::UDPConn &c, float *plrCoords);

    void delChunks(net::UDPConn &c, float *plrCoords);

}