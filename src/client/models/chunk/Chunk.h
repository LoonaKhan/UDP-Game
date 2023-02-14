//
// Created by loona on 05/01/23.
//

#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include <map>
#include <iostream>
#include "../block/Block.h"
#include <vector>

using json = nlohmann::json;

namespace chunk {

    struct ByteArr{
        char bytes[1032];
        int len = 1032;
    };

    class Chunk {

    private: // attributes
        int coords[2];
        block::Block blocks[256]; // todo: needs to be the same size of chunk_size^2

    public: // attributes

    public: // methods
        /*
         * default constructor.
         * used when clients create a chunk.
         * sets coords and creates all blocks
         * */
        Chunk(int coords[2]);

        /*
         * Used when we recieve chunks from the server
         * we recieve a array of buffer(char) from the server,
         * the first 2 buffer become the chunk coordinates
         * the rest are used to create the blocks
         */
        Chunk(char buffer[], int len);

        Chunk(); // needed a blank constructor so we can create chunk arrays

        // converts the chunk data to bytes so we can send it along with a header
        ByteArr toBytes();

        // getters

        int* getCoords();

        block::BlockArray getBlocks();

        int getBlocksLen();

        block::Block getBlock(char coords[]);

        // operator so we can use it as a map key
        bool operator<(const Chunk& other) const {
            if (this->coords[0] == other.coords[0]) { // if the x coords are the same, use the y coords
                return this->coords[1] < other.coords[1];
            }
            return this->coords[0] < other.coords[0];
        }

        // we return a map since we will need to search through the render distance chunks
        static std::map<std::vector<int>, int*> getRenderDistChunks(float *plrCoords);

        static std::vector<int> toChunkCoords(float* plrCoords);

        static std::pair<std::vector<int>, std::vector<int>> RenderDistCorners(float *plrCoords);

    private: // methods

    };

    extern std::map<std::vector<int>, Chunk> chunks; // stores chunks using an array of their coords as a key

} // chunk
