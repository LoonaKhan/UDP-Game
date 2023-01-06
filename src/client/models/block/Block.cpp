//
// Created by loona on 05/01/23.
//

#include "Block.h"

namespace block {

    Block::Block(int *coords, int *chunk_coords, double colour_noise, double height_noise) // default constructor
    : coords{coords[0], coords[1]},
    chunk_coords{chunk_coords[0], chunk_coords[1]}
    {
        this->colour_noise = 1;
        this->height_noise = 1;
    }

    Block::Block() {}

    Block::Block(json d, int *chunk_coords)
    : coords{d["x"], d["y"]},
    chunk_coords{chunk_coords[0], chunk_coords[1]},
    colour_noise(d["colour"]),
    height_noise(d["height"])
    {}

    json Block::toJson() {
        json b;

        b["x"] = this->coords[0];
        b["y"] = this->coords[1];
        b["colour"] = this->colour_noise;
        b["height"] = this->height_noise;

        return b;
    }
} // block