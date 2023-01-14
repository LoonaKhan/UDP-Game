//
// Created by loona on 12/01/23.
//

#include "BlockSprite.h"

namespace block {

    BlockSprite::BlockSprite(block::Block block)
    : block(block) {
        auto pos = this->block.getCoords();
        auto c = colours[this->block.getColour()];

        this->setPosition((float)pos[0], (float)pos[1]);
        this->setColor(sf::Color(c[0], c[1], c[2]));
    }

    void BlockSprite::render(sf::RenderWindow *window) {
        window->draw(*this);
    }

} // block