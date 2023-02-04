//
// Created by loona on 05/01/23.
//

#include "Chunk.h"

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
    : coords{buffer[0] | (buffer[1]<<8) | (buffer[2] << 16) | (buffer[3] << 24),
             buffer[4] | (buffer[5]<<8) | (buffer[6] << 16) | (buffer[7] << 24)} {

        for (int b_idx=8, i=0; // b_idx is the index of the buffer, i is the index of this->blocks
                b_idx < len;
                b_idx+=4, i++) {
            char b_coords[] = {buffer[b_idx], buffer[b_idx+1]};
            this->blocks[i] = block::Block(b_coords, buffer[b_idx+2], buffer[b_idx+3]);
        }
    }

    ByteArr Chunk::toBytes() {
         ByteArr buffer;

        // append the chunks
        buffer.bytes[0] = this->coords[0] & 0xFF;
        buffer.bytes[1] = (this->coords[0] >> 8) & 0xFF;
        buffer.bytes[2] = (this->coords[0] >> 16) & 0xFF;
        buffer.bytes[3] = (this->coords[0] >> 24) & 0xFF;
        buffer.bytes[4] = this->coords[1] & 0xFF;
        buffer.bytes[5] = (this->coords[1] >> 8) & 0xFF;
        buffer.bytes[6] = (this->coords[1] >> 16) & 0xFF;
        buffer.bytes[7] = (this->coords[1] >> 24) & 0xFF;


        // add the blocks
        int b_idx=8;
        for (auto& b : this->blocks) {
            buffer.bytes[b_idx] = b.getCoords()[0];
            buffer.bytes[b_idx+1] = b.getCoords()[1];
            buffer.bytes[b_idx+2] = b.getColour();
            buffer.bytes[b_idx+3] = b.getHeight();
            b_idx +=4;
        }

        return buffer;
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
            b_arr.blocks[i] = this->blocks[i]; // todo: crashes
        }
        return b_arr;
    }

    int *Chunk::getCoords() {
        return this->coords;
    }

    std::map<std::vector<int>, Chunk> chunks; // stores chunks using an array of their coords as a key

    Chunk::Chunk() {}

    // todo: needs to be based on the player's render dist
    std::map<std::vector<int>, int*> Chunk::getRenderDistChunks(float *plrCoords) {
        std::map<std::vector<int>, int*> ret;
        auto curChunk = toChunkCoords(plrCoords);
        /*std::cout << "x0: " <<  curChunk[0] - RENDER_DIST
            << " x1: " << curChunk[0] + RENDER_DIST <<
            " y0: " << curChunk[1] - RENDER_DIST <<
            " y1: " << curChunk[1] + RENDER_DIST<< "\n";*/

        /*
         * take the render distance and subtract it from plrCoords[0,1] and iterate until we reach plrCoords+render dist
         * append each entry
         */
        for (int x=curChunk[0]- RENDER_DIST; x < curChunk[0] + RENDER_DIST; x++)
            for (int y=curChunk[1] - RENDER_DIST; y < curChunk[1] + RENDER_DIST; y++)
                ret.insert({std::vector<int>{x, y}, nullptr});
        return ret;
    }

    std::vector<int> Chunk::toChunkCoords(float* plrCoords) {
        /*
         * Determines what chunk the player is in.
         *
         * divide player coords  by RENDER_DISTANCE. if negative, subtract 1
         */
        std::vector<int> curChunk;
        for (int i=0; i < 2; i++) {
            curChunk.push_back(int(plrCoords[i] / RENDER_DIST));
            if (curChunk[i] < 0)
                curChunk[i]--;
        }
        return curChunk;
    }

} // chunk