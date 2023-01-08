//
// Created by loona on 07/01/23.
//

#pragma once


class block {

private: // members
    char coords[2];
    char colour;
    char height;

public: // members

public: // methods
    block(char *coords, char *chunk_coords, char colour= 0, char height= 0) // default to 0 if blank. cn also check if numbers are within bounds
    :coords{coords[0], coords[1]},
    colour(colour),
    height(height)
    {}

    block(){}

private: // methods

};
