//
// Created by loona on 02/01/23.
//

#pragma once

#include <nlohmann/json.hpp>
#include <string>

using json =  nlohmann::json;


namespace net {
    int seperate(char buffer[], char substr);

    json toJson(char buffer[]); // instead use generics and to structs
}