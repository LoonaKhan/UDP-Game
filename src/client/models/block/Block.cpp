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
        this->setFillColor(sf::Color(c[0], c[1], c[2]));

        this->setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE)); //todo: get size
        this->setOrigin(BLOCK_SIZE/2,BLOCK_SIZE/2);
    }

    Block::Block() {}

    void Block::render(sf::RenderWindow *window, int *chunk, float *plrCoords) {
        this->setPosition(
                (((float)chunk[0] * CHUNK_SIZE) + this->coords[0] - plrCoords[0]) * BLOCK_SIZE+ SCREEN_CENTRE[0],
                (((float)chunk[1] * CHUNK_SIZE) + this->coords[1] - plrCoords[1]) * BLOCK_SIZE+ SCREEN_CENTRE[1]
                );
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
            {28, 43, 140},      //      0: water
            {247, 250, 155},    //      1: beach
            {32, 110, 33},      //      2: plains
            {8, 87, 9},         //      3: forest
            {93, 97, 93}        //      4: mountain
    };
} // block