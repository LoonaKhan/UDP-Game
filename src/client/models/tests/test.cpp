//
// Created by loona on 06/01/23.
//

#include "../block/Block.h"
#include "../chunk/Chunk.h"
#include "../player/player.h"
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include "iostream"

using json = nlohmann::json;

block::Block blockConstructorTest() {
    char coords[] = {1,0};

    auto b = block::Block(coords);

    fmt::print("Block:\n"
               "coords: [{}, {}]\n"
               "colour noise: {}\n"
               "height_noise: {}\n",
               (int)b.getCoords()[0], (int)b.getCoords()[1],
               b.getColour(), b.getHeight());

    return b;
}

// chunk constructor
void chunkConstructorTest() {
    char coords[] = {0,0};

    auto c = chunk::Chunk(coords);

    fmt::print("size: {}\n", c.getBlocksLen());

    // can access all blocks from here
    for (auto&b : c.getBlocks().blocks) {
        fmt::print("block: [{},{}]\n", (int)b.getCoords()[0], (int)b.getCoords()[1]);
    }
}

void chunkGetBlockTest() {
    char coords[] = {0,1};
    auto c = chunk::Chunk(coords);

    char block[] = {10,10};
    auto b = c.getBlock(block);
    fmt::print("Block:\n"
               "coords: [{}, {}]\n"
               "colour noise: {}\n"
               "height_noise: {}\n",
               (int)b.getCoords()[0], (int)b.getCoords()[1],
               b.getColour(), b.getHeight());
}

int main() {
    //blockConstructorTest();
    //chunkGetBlockTest();
    //chunkConstructorTest();
}
