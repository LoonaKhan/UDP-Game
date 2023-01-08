//
// Created by loona on 05/01/23.
//

#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace block {

    class Block {
    private: // priv attributes
        char coords[2]; // relative to their chunk
        char colour,
        height;

    public: // pub attributes
        // the SFML shape

    public: // pub methods
        /*
         * if we are creating a chunk, colour and height are empty as we generate those ourselves.
         * if we are recieving data from the server, colour and height will already be filled
         * */
        Block(char coords[2], char colour=0, char height=0);

        Block(); // this constructor only exists because member init lists wouldnt recognize the other constructors???

        // json constructor for when we recieve chunks and blocks from the server
        Block(json d, int chunk_coords[]);


         void render(); // renders the block to the screen

         // getters
         char* getCoords();

         int getColour();

         int getHeight();


    private: // priv methods

        void genNoise(char *chunk);

    };

    struct BlockArray { // since we need an array + it's length, this struct contains both
        block::Block blocks[256];
        int len = 256;
    };

} // block

