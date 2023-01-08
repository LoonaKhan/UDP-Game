//
// Created by loona on 07/01/23.
//

#pragma once
#include "block.h"


class chunk {

private: // members
    char coords[2];
    block blocks[256];

public: // members

public: // methods
    chunk(char *coords)
    : coords{coords[0], coords[1]},
    blocks()
    {}

private: // methods

};
