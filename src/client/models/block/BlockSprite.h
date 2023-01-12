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

    public: // methods
        BlockSprite(Block block);

        void render(sf::RenderWindow *window);
    private: // methods
    };

} // block

