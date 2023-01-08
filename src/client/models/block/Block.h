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
         int* getIntCoords() { //! returns a static variable. DONT FORGET TO DELETE AFTER
             static int int_coords[2] = {this->coords[0], this->coords[1]};
             return int_coords;
         }

         char* getCoords(){
             return this->coords;
         }

         int getColour() {
             return this->colour;
         }
         int getHeight() {
             return this->height;
         }


    private: // priv methods

        void genNoise(char *chunk);

    };

} // block

