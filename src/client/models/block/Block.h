//
// Created by loona on 05/01/23.
//

#pragma once

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "fmt/core.h"
#include "../../globvars/globvars.h"

using json = nlohmann::json;
using namespace glob;

namespace block {

    class Block : public sf::RectangleShape{
    private: // priv attributes
        char coords[2]; // relative to their chunk
        char colour, height;

    public: // pub methods
        /*
         * if we are recieving data from the server, colour and height will already be filled
         * */
        Block(char coords[2], char colour=128, char height=0);

        Block(); // blank constructor so we can make block arrays

        void render(sf::RenderWindow *window, int chunk[2], float plrCoords[2]); // renders the block to the screen

        // getters
        char* getCoords();

        [[nodiscard]] char getColour() const;

        [[nodiscard]] char getHeight() const;


    private: // priv methods

        void genNoise(char *chunk);

    };

    struct BlockArray { // since we need an array + it's length, this struct contains both
        block::Block blocks[256];
        int len = 256;
    };

    extern unsigned char colours[5][3];

} // block

