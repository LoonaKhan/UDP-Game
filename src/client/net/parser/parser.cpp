//
// Created by loona on 02/01/23.
//

#include "parser.h"


int net::seperate(char *buffer, char substr) {
    auto str = (std::string)buffer;
    return str.find(substr);
}