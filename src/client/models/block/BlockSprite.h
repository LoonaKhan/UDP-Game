//
// Created by loona on 12/01/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"

namespace block {

    class BlockSprite : sf::Sprite {
        // block sprites are used to draw blocks onto the screen.
        // they utilize the Block class for data and rendeer them using sf::Sprite
        // we use the colour and height from block. maybe just an attribute?
        // sprite from sprite

    private: // attributes
        Block block;
        sf::RectangleShape shape;

    public: // methods
        BlockSprite(Block block);

        void render(sf::RenderWindow *window);
    private: // methods
    };

    // the colour codes of each biome
    unsigned char colours[5][3]{
            {28, 43, 140},
            {247, 250, 155},
            {32, 110, 33},
            {8, 87, 9},
            {93, 97, 93}
    };

} // block

