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

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using json = nlohmann::json;

namespace net {
    void verifyOnline(net::UDPConn &c, int id);

    void readRes(net::UDPConn &c, int &cred);

    void updateCred(int id, int &cred);

}