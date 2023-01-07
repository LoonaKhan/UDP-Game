//
// Created by loona on 06/01/23.
//

#include "../block/Block.h"
#include "../chunk/Chunk.h"
#include "../player/player.h"
#include <fmt/core.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

block::Block blockConstructorTest() {
    int coords[] = {0,0};
    int chunk_coords[] = {1,0};

    auto b = block::Block(coords, chunk_coords);

    fmt::print("Block:\n"
               "coords: [{}, {}]\n"
               "chunk_coords: [{}, {}]\n"
               "colour noise: {}\n"
               "height_noise: {}\n",
               b.getCoords()[0], b.getCoords()[1],
               b.getChunkCoords()[0], b.getChunkCoords()[1],
               b.getColour(), b.getHeight());

    return b;
}

block::Block blockJsonConstructorTest() {
    json data = {
            {"x", 0},
            {"y", 0},
            {"colour", 1},
            {"height", 1}
    };
    int chunk_coords[] = {0,0};

    auto b = block::Block(data, chunk_coords);
    fmt::print("Block:\n"
               "coords: [{}, {}]\n"
               "chunk_coords: [{}, {}]\n"
               "colour noise: {}\n"
               "height_noise: {}\n",
               b.getCoords()[0], b.getCoords()[1],
               b.getChunkCoords()[0], b.getChunkCoords()[1],
               b.getColour(), b.getHeight());

    return b;
}

void blockDecodetoJsonTest(block::Block b){
    json data = b.toJson();
    fmt::print("data: {}\n", data.dump());
}


chunk::Chunk chunkConstructorTest(){
    int coords[] = {0,0};
    return {coords};
}

chunk::Chunk chunkJsonConstrcutorTest() {
    /*
     * we use a string literal parsed as json to act as our data
     * needed to get it somehow, so i just used a string literal
     */
    json data = R"({
    "blocks": [
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 0,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 1,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 2,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 3,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 4,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 5,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 6,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 7,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 8,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 9,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 10,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 11,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 12,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 13,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 14,
            "y": 15
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 0
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 1
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 2
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 3
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 4
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 5
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 6
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 7
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 8
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 9
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 10
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 11
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 12
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 13
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 14
        },
        {
            "colour": 1.0,
            "height": 1.0,
            "x": 15,
            "y": 15
        }
    ],
    "x": 0,
    "y": 0
}
)"_json;
    return {data};
}

void chunkDecodeToJsonTest(chunk::Chunk c){
    json data = c.toJson();
    fmt::print("data: {}\n", data.dump(4));
}

void chunkGetBlockTest() {
    int coords[] = {0,1};
    auto c = chunk::Chunk(coords);

    int block[] = {10,10};
    auto b = c.getBlock(block);
    fmt::print("block: {}", b.toJson().dump(4));
}

int main() {
    //blockDecodetoJsonTest(blockConstructorTest());

    //chunkDecodeToJsonTest(chunkConstructorTest());
    //chunkDecodeToJsonTest(chunkJsonConstrcutorTest());

    //chunkGetBlockTest();
}
