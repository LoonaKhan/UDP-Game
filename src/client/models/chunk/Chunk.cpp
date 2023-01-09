//
// Created by loona on 05/01/23.
//

#include "Chunk.h"
#include "iostream"

namespace chunk {

    Chunk::Chunk(int *coords)
    : coords{coords[0], coords[1]} {
        int i = 0;
        for (char x = 0; x < 16; x++) {
            for (char y = 0; y < 16; y++, i++) {
                char p[2]{x, y};
                this->blocks[i] = block::Block(p);
            }
        }
    }

    Chunk::Chunk(char *buffer, int len)
    : coords{buffer[0] + (buffer[1]<<8) + (buffer[2] << 16) + (buffer[3] << 24),
             buffer[4] + (buffer[5]<<8) + (buffer[6] << 16) + (buffer[7] << 24)} {

        for (int b_idx=8, i=0; // b_idx is the index of the buffer, i is the index of this->blocks
                b_idx < len;
                b_idx+=4, i++) {
            char b_coords[] = {buffer[b_idx], buffer[b_idx+1]};
            this->blocks[i] = block::Block(b_coords, buffer[b_idx+2], buffer[b_idx+3]);
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

    int *Chunk::getCoords(){
        return this->coords;
    }

} // chunk