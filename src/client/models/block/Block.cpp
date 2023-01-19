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
        this->setPosition((float)this->coords[0], (float)this->coords[1]);

        auto c = colours[this->colour];
        this->setColor(sf::Color(c[0], c[1], c[2]));

        this->setScale(5, 5); //todo: get size
    }

    Block::Block() {}

    void Block::render(sf::RenderWindow *window, int *chunk) {
        this->setPosition((float)chunk[0] + this->coords[0], (float)chunk[1] + this->coords[1]);
        window->draw(*this);
    }

    char *Block::getCoords() {
        return this->coords;
    }

    char Block::getColour() const {
        return this->colour;
    }

    char Block::getHeight() const {
        return this->height;
    }

    unsigned char colours[5][3]{
            {28, 43, 140},
            {247, 250, 155},
            {32, 110, 33},
            {8, 87, 9},
            {93, 97, 93}
    };
} // block