//
// Created by loona on 14/02/23.
//
/*
 * Objective:
 *  draw player on midpoint
 *      movements increase a player position variable
 *  chunks are drawn relative to certain limits
 *      player coords allow chunk limits to be calculated (corners)
 *  draw blocks relative to
 *      (((chunk - LeftCorner) * ChunkSize) + block - (plrCoords mod ChunkSize)) * BlockSize
 *
 *  draw a player on a screen
 *  render checker for chunks
 *  gens left n right corners
 *  redo block formula
 *
 *  dont consider chunks when rendering
 *  keep block limits?
 */

#include <thread>
#include <core.h>
#include "fmt/core.h"
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "../net/macros/macros.h"
#include "../net/calls/calls.h"
#include "../models/chunk/Chunk.h"
#include "../models/block/Block.h"
#include "../globvars/globvars.h"

using namespace glob;
using namespace std::chrono;
using namespace std::this_thread;

int main() {

    // player stuff
    float plrCoords[] = {0,0};
    sf::RectangleShape plrShape;
    plrShape.setPosition(SCREEN_CENTRE[0], SCREEN_CENTRE[1]);
    plrShape.setFillColor(sf::Color::Red);
    plrShape.setSize(sf::Vector2f(10,10));
    plrShape.setOrigin(5,5);

    // chunk corners
    auto curChunk = chunk::Chunk::toChunkCoords(plrCoords);
    std::pair<std::vector<int>, std::vector<int>> chunkCorners = {
            {curChunk[0] - RENDER_DIST, curChunk[1] - RENDER_DIST},
            {curChunk[0] + RENDER_DIST, curChunk[1] + RENDER_DIST}
    };

    // SFML setup
    sf::RenderWindow window(sf::VideoMode(1920,1080),
                     "CLIENT",
                     sf::Style::Close | sf::Style::Resize);
    sf::Clock clock;

    // add chunks to chunks
    int chunks[][2] = {
            {0,0},
            {1,0},
            {6,0},
            {-6, 0}
    };
    for (int i =0; i< sizeof(chunks) / sizeof(chunks[0]); i++){
        chunk::chunks.insert({ {chunks[i][0], chunks[i][1]}, chunk::Chunk( chunks[i])});
    }

    while (window.isOpen()) {
        sf::Event evnt{};
        while(window.pollEvent(evnt)) {
            if (evnt.type == evnt.Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                window.close();
            }
        }

        float walk_speed = 0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            plrCoords[1]-=walk_speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            plrCoords[1]+=walk_speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            plrCoords[0]-=walk_speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            plrCoords[0]+=walk_speed;

        curChunk = chunk::Chunk::toChunkCoords(plrCoords);
        chunkCorners  = {
                {curChunk[0] - RENDER_DIST, curChunk[1] - RENDER_DIST},
                {curChunk[0] + RENDER_DIST, curChunk[1] + RENDER_DIST}
        };

        // draws the chunks. based on formula
        for (auto& [coords, chunk] : chunk::chunks)
            for (auto& b : chunk.getBlocks().blocks) {
                //b.render(&window, chunk.getCoords(), plrCoords);
                // (((chunk - LeftCorner) * ChunkSize) + block - (plrCoords mod ChunkSize)) * BlockSize
                b.setPosition(
                        ((((chunk.getCoords()[0] ) * CHUNK_SIZE) + b.getCoords()[0]) - ((int)plrCoords[0] % 16)) * BLOCK_SIZE,
                        ((((chunk.getCoords()[1] ) * CHUNK_SIZE) + b.getCoords()[1]) - ((int)plrCoords[1] % 16)) * BLOCK_SIZE
                        );
                window.draw(b);
            }

        // remove chunks from the map
        /*std::vector<std::vector<int>> badChunks;
        for (auto& [coords, chunk] : chunk::chunks){
            if (!(coords[0] > chunkCorners.first[0] and coords[0] < chunkCorners.second[0]
                and coords[1] > chunkCorners.first[1] and coords[1] < chunkCorners.second[1]))
                badChunks.push_back(coords);
        }
        for (auto it = badChunks.begin(); it != badChunks.end();) {
            chunk::chunks.erase(it);
        }*/

        window.draw(plrShape);
        window.display();
        window.clear();
        window.setFramerateLimit(60);

    }
}