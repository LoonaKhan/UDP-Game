//
// Created by loona on 05/01/23.
//

#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace block {

    class Block {
    private: // priv attributes
        int coords[2]; // relative to their chunk
        int chunk_coords[2]; // coords of the chunk they belong to
        double colour_noise; // the colour noise value. based on coordinates
        double height_noise; // their height. based off coordinates and colour

    public: // pub attributes
        // the SFML shape

    public: // pub methods
        /*
         * default constructor.
         * used when the client creates a block
         * sets coords and determines the noise values
         * */
        Block(int coords[2], int chunk_coords[2], double colour_noise=0, double height_noise=0);

        Block();

        Block(json d, int chunk_coords[]);


         void render(); // renders the block to the screen

         json toJson(); // for when we want to package it

    private: // priv methods

    };

} // block

