//
// Created by loona on 15/01/23.
//

#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


const json glob = json::parse(std::ifstream("globvars.json"));

const auto RENDER_DIST = glob["RENDER_DIST"];


