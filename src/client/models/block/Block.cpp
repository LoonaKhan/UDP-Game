//
// Created by loona on 05/01/23.
//

#include "Block.h"

namespace block {

    Block::Block(char *coords, char colour, char height) // default constructor
    : coords{coords[0], coords[1]},
    colour(colour),
    height(height)
    {
        // if colour || height == 0: set em
    }

    Block::Block() {}

    char *Block::getCoords() {
        return this->coords;
    }

    char Block::getColour() const {
        return this->colour;
    }

    char Block::getHeight() const {
        return this->height;
    }
} // block