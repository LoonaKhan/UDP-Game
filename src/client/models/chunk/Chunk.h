//
// Created by loona on 05/01/23.
//

#pragma once

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
        Chunk(char coords[2], block::Block blocks[256]= nullptr);

        // getters
        char* getCoords() {
            return this->coords;
        }

        block::Block* getBlocks() { // todo: get this working. needs to return all blocks
            return this->blocks;
        }

        int getBlocksLen() {
            return sizeof(this->blocks) / sizeof(this->blocks[0]);
        }

        block::Block getBlock(char coords[]) {
            for (auto& b : this->blocks) {
                if (b.getCoords()[0] == coords[0] && b.getCoords()[1] == coords[1])
                    return b;
            }
        }

    private: // methods

    };

} // chunk
