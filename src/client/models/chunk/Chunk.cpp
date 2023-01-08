//
// Created by loona on 05/01/23.
//

#include "Chunk.h"
#include "iostream"

namespace chunk {

    Chunk::Chunk(char *coords, block::Block* blocks)
    : coords{coords[0], coords[1]},
    blocks() {
        int i=0;
        for (char x=0; x<16; x++){
            for (char y=0; y<16; y++, i++){

                if (blocks == nullptr) { // if no blocks are given. IE: we are creating these blocks
                    char p[2]{x,y};
                    this->blocks[i] = block::Block(p);
                }
                else { // if we are recieving data from the server
                    this->blocks[i] = blocks[i];
                }

            }

        }
    }

    block::Block Chunk::getBlock(char *coords)  {
        for (auto& b : this->blocks) {
            if (b.getCoords()[0] == coords[0] && b.getCoords()[1] == coords[1])
                return b;
        }
    }

    int Chunk::getBlocksLen() {
        return sizeof(this->blocks) / sizeof(this->blocks[0]);
    }

    block::BlockArray Chunk::getBlocks() { //
        block::BlockArray b_arr;
        for (int i=0; i<b_arr.len ; i++) {
            b_arr.blocks[i] = this->blocks[i];
        }
        return b_arr;
    }

    char *Chunk::getCoords(){
        return this->coords;
    }

} // chunk