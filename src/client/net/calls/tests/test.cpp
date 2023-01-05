#include "../calls.h"
#include <iostream>
#include "string"


int main() {

    std::string name = "loona";
    char buffer[]={};
    net::post_player(buffer, name);
    std::cout << buffer << std::endl;
    fmt::print("size: {}\n",sizeof(buffer));


}
