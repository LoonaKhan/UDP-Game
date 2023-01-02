//
// Created by loona on 02/01/23.
//

#include "../parser.h"
#include "iostream"

int main() {
    char buf[] = "01";
    std::cout << net::seperate(buf, '|')<< std::endl;
}