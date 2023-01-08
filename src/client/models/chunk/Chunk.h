//
// Created by loona on 05/01/23.
//

#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include "../block/Block.h"

using json = nlohmann::json;

namespace chunk {

    class Chunk {

    private: // attributes
        char coords[2];
        block::Block blocks[256]; // todo: needs to be the same size of chunk_size^2

    public: // attributes

    public: // methods
        /*
         * default constructor.
         * used when clients create a chunk.
         * sets coords and creates all blocks
         * */
        Chunk(char coords[2]);

        /*
         * Used when we recieve chunks from the server
         * we recieve a array of buffer(char) from the server,
         * the first 2 buffer become the chunk coordinates
         * the rest are used to create the blocks
         */
        Chunk(char buffer[], int len);

        // getters
        char* getCoords();

        block::BlockArray getBlocks();

        int getBlocksLen();

        block::Block getBlock(char coords[]);

    private: // methods

    };

} // chunk
