//
// Created by loona on 04/01/23.
//

#include "calls.h"

#include "cstring"
#include "iostream"

std::string net::post_player(std::string &name) {
    json header, body;
    header["method"] = "post_player";
    body["name"] = name;
    return header.dump() + "|" + body.dump();
}


std::string net::login(std::string &name) {
    json header, body;
    header["method"] = "login";
    body["name"] = name;
    return header.dump() + "|" + body.dump();
}

std::string net::update_pos(int &cred, int *coords) {
    json header, body;
    header["method"] = "update_pos";
    header["cred"] = cred;
    body["coords"] = {coords[0], coords[1]};
    return header.dump()+"|"+body.dump();
}

std::string net::get_chunks(int &cred, int *chunk_coords) {
    json header, body;
    header["method"] = "get_chunks";
    header["cred"] = cred;
    body["coords"] = {chunk_coords[0], chunk_coords[1]};
    return header.dump()+"|"+body.dump();
}
