//
// Created by loona on 05/01/23.
//

#include "Chunk.h"

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

} // chunk