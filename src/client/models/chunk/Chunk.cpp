//
// Created by loona on 05/01/23.
//

#include "Chunk.h"

namespace chunk {

    Chunk::Chunk(int *coords)
    : coords{coords[0], coords[1]},
    blocks() {
        int i=0;
        for (int x=0; x<16; x++){
            for (int y=0; y<16; y++, i++){
                int p[2]{x,y};
                this->blocks[i] = block::Block(p, coords);
            }

        }
    }

    Chunk::Chunk(json d)
    : coords{d["x"], d["y"]}
    {
        for (int i=0; i<256; i++){
            this->blocks[i] = block::Block(d["blocks"][i], this->coords);
        }
    }

} // chunk