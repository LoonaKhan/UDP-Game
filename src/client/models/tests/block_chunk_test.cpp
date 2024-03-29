//
// Created by loona on 06/01/23.
//

#include "../block/Block.h"
#include "../chunk/Chunk.h"
#include "../player/player.h"
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
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
    int coords[] = {0,0};

    auto c = chunk::Chunk(coords);

    fmt::print("size: {}\n", c.getBlocksLen());

    // can access all blocks from here
    for (auto&b : c.getBlocks().blocks) {
        fmt::print("block: [{},{}]\n", (int)b.getCoords()[0], (int)b.getCoords()[1]);
    }
}

void chunkResConstructorTest() { // tests the response costructor

    // response from the server
    char buffer[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 126, 0, 1, 127, 126, 0, 2, 127, 126, 0, 3, 127, 126, 0, 4, 127, 126, 0, 5, 127, 126, 0, 6, 127, 126, 0, 7, 127, 126, 0, 8, 127, 126, 0, 9, 127, 126, 0, 10, 127, 126, 0, 11, 127, 126, 0, 12, 127, 126, 0, 13, 127, 126, 0, 14, 127, 126, 0, 15, 127, 126, 1, 0, 127, 126, 1, 1, 127, 126, 1, 2, 127, 126, 1, 3, 127, 126, 1, 4, 127, 126, 1, 5, 127, 126, 1, 6, 127, 126, 1, 7, 127, 126, 1, 8, 127, 126, 1, 9, 127, 126, 1, 10, 127, 126, 1, 11, 127, 126, 1, 12, 127, 126, 1, 13, 127, 126, 1, 14, 127, 126, 1, 15, 127, 126, 2, 0, 127, 126, 2, 1, 127, 126, 2, 2, 127, 126, 2, 3, 127, 126, 2, 4, 127, 126, 2, 5, 127, 126, 2, 6, 127, 126, 2, 7, 127, 126, 2, 8, 127, 126, 2, 9, 127, 126, 2, 10, 127, 126, 2, 11, 127, 126, 2, 12, 127, 126, 2, 13, 127, 126, 2, 14, 127, 126, 2, 15, 127, 126, 3, 0, 127, 126, 3, 1, 127, 126, 3, 2, 127, 126, 3, 3, 127, 126, 3, 4, 127, 126, 3, 5, 127, 126, 3, 6, 127, 126, 3, 7, 127, 126, 3, 8, 127, 126, 3, 9, 127, 126, 3, 10, 127, 126, 3, 11, 127, 126, 3, 12, 127, 126, 3, 13, 127, 126, 3, 14, 127, 126, 3, 15, 127, 126, 4, 0, 127, 126, 4, 1, 127, 126, 4, 2, 127, 126, 4, 3, 127, 126, 4, 4, 127, 126, 4, 5, 127, 126, 4, 6, 127, 126, 4, 7, 127, 126, 4, 8, 127, 126, 4, 9, 127, 126, 4, 10, 127, 126, 4, 11, 127, 126, 4, 12, 127, 126, 4, 13, 127, 126, 4, 14, 127, 126, 4, 15, 127, 126, 5, 0, 127, 126, 5, 1, 127, 126, 5, 2, 127, 126, 5, 3, 127, 126, 5, 4, 127, 126, 5, 5, 127, 126, 5, 6, 127, 126, 5, 7, 127, 126, 5, 8, 127, 126, 5, 9, 127, 126, 5, 10, 127, 126, 5, 11, 127, 126, 5, 12, 127, 126, 5, 13, 127, 126, 5, 14, 127, 126, 5, 15, 127, 126, 6, 0, 127, 126, 6, 1, 127, 126, 6, 2, 127, 126, 6, 3, 127, 126, 6, 4, 127, 126, 6, 5, 127, 126, 6, 6, 127, 126, 6, 7, 127, 126, 6, 8, 127, 126, 6, 9, 127, 126, 6, 10, 127, 126, 6, 11, 127, 126, 6, 12, 127, 126, 6, 13, 127, 126, 6, 14, 127, 126, 6, 15, 127, 126, 7, 0, 127, 126, 7, 1, 127, 126, 7, 2, 127, 126, 7, 3, 127, 126, 7, 4, 127, 126, 7, 5, 127, 126, 7, 6, 127, 126, 7, 7, 127, 126, 7, 8, 127, 126, 7, 9, 127, 126, 7, 10, 127, 126, 7, 11, 127, 126, 7, 12, 127, 126, 7, 13, 127, 126, 7, 14, 127, 126, 7, 15, 127, 126, 8, 0, 127, 126, 8, 1, 127, 126, 8, 2, 127, 126, 8, 3, 127, 126, 8, 4, 127, 126, 8, 5, 127, 126, 8, 6, 127, 126, 8, 7, 127, 126, 8, 8, 127, 126, 8, 9, 127, 126, 8, 10, 127, 126, 8, 11, 127, 126, 8, 12, 127, 126, 8, 13, 127, 126, 8, 14, 127, 126, 8, 15, 127, 126, 9, 0, 127, 126, 9, 1, 127, 126, 9, 2, 127, 126, 9, 3, 127, 126, 9, 4, 127, 126, 9, 5, 127, 126, 9, 6, 127, 126, 9, 7, 127, 126, 9, 8, 127, 126, 9, 9, 127, 126, 9, 10, 127, 126, 9, 11, 127, 126, 9, 12, 127, 126, 9, 13, 127, 126, 9, 14, 127, 126, 9, 15, 127, 126, 10, 0, 127, 126, 10, 1, 127, 126, 10, 2, 127, 126, 10, 3, 127, 126, 10, 4, 127, 126, 10, 5, 127, 126, 10, 6, 127, 126, 10, 7, 127, 126, 10, 8, 127, 126, 10, 9, 127, 126, 10, 10, 127, 126, 10, 11, 127, 126, 10, 12, 127, 126, 10, 13, 127, 126, 10, 14, 127, 126, 10, 15, 127, 126, 11, 0, 127, 126, 11, 1, 127, 126, 11, 2, 127, 126, 11, 3, 127, 126, 11, 4, 127, 126, 11, 5, 127, 126, 11, 6, 127, 126, 11, 7, 127, 126, 11, 8, 127, 126, 11, 9, 127, 126, 11, 10, 127, 126, 11, 11, 127, 126, 11, 12, 127, 126, 11, 13, 127, 126, 11, 14, 127, 126, 11, 15, 127, 126, 12, 0, 127, 126, 12, 1, 127, 126, 12, 2, 127, 126, 12, 3, 127, 126, 12, 4, 127, 126, 12, 5, 127, 126, 12, 6, 127, 126, 12, 7, 127, 126, 12, 8, 127, 126, 12, 9, 127, 126, 12, 10, 127, 126, 12, 11, 127, 126, 12, 12, 127, 126, 12, 13, 127, 126, 12, 14, 127, 126, 12, 15, 127, 126, 13, 0, 127, 126, 13, 1, 127, 126, 13, 2, 127, 126, 13, 3, 127, 126, 13, 4, 127, 126, 13, 5, 127, 126, 13, 6, 127, 126, 13, 7, 127, 126, 13, 8, 127, 126, 13, 9, 127, 126, 13, 10, 127, 126, 13, 11, 127, 126, 13, 12, 127, 126, 13, 13, 127, 126, 13, 14, 127, 126, 13, 15, 127, 126, 14, 0, 127, 126, 14, 1, 127, 126, 14, 2, 127, 126, 14, 3, 127, 126, 14, 4, 127, 126, 14, 5, 127, 126, 14, 6, 127, 126, 14, 7, 127, 126, 14, 8, 127, 126, 14, 9, 127, 126, 14, 10, 127, 126, 14, 11, 127, 126, 14, 12, 127, 126, 14, 13, 127, 126, 14, 14, 127, 126, 14, 15, 127, 126, 15, 0, 127, 126, 15, 1, 127, 126, 15, 2, 127, 126, 15, 3, 127, 126, 15, 4, 127, 126, 15, 5, 127, 126, 15, 6, 127, 126, 15, 7, 127, 126, 15, 8, 127, 126, 15, 9, 127, 126, 15, 10, 127, 126, 15, 11, 127, 126, 15, 12, 127, 126, 15, 13, 127, 126, 15, 14, 127, 126, 15, 15, 127, 126};

    auto c = chunk::Chunk(buffer, sizeof(buffer));

    fmt::print("size: {}\n", c.getBlocksLen());

    fmt::print("coords: [{},{}]\n", c.getCoords()[0], c.getCoords()[1]);

    // can access all blocks from here
    for (auto&b : c.getBlocks().blocks) {
        fmt::print("block: [{},{}]\n", (int)b.getCoords()[0], (int)b.getCoords()[1]);
    }
}

void chunkGetBlockTest() {
    int coords[] = {0,1};
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

void chunkToBytesTest() {
    int coords[] = {0,0};
    auto c = chunk::Chunk(coords);

    auto buffer = c.toBytes();

    fmt::print("len({}) [", buffer.len);
    for (int i=0; i< buffer.len; i++) {
        fmt::print("{}, ", (int)buffer.bytes[i]);
    }
    fmt::print("]\n");
}

void chunkCoordsTest(){
    int coords[] = {1,0};
    auto c = chunk::Chunk(coords);

    //std::cout << c.getCoords()[0] <<" " << c.getCoords()[1] <<"\n";
    fmt::print("[{}, {}]\n", (int)c.getCoords()[0], c.getCoords()[1]);
}

void chunkDrawTest(){
    int coords[] = {0,0};
    auto c = chunk::Chunk(coords);
    sf::RenderWindow window(sf::VideoMode(1920,1080),
                            "CLIENT",
                            sf::Style::Close | sf::Style::Resize);

    while (window.isOpen()){
        sf::Event evnt{};

        while(window.pollEvent(evnt)) {
            if (evnt.type == evnt.Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                window.close();
            }
        }

        /*for (auto &b: c.getBlocks().blocks) {
            b.render(&window, c.getCoords());
        }*/
    }

    window.clear();
    window.display();
    //window.clear();
}

int main() {
    //blockConstructorTest();
    //chunkGetBlockTest();
    //chunkConstructorTest();
    //chunkResConstructorTest();
    //chunkToBytesTest();
    //chunkCoordsTest();
    chunkDrawTest();
}
