//
// Created by loona on 07/01/23.
//

#include "chunk.h"
#include "block.h"


chunk::chunk(int *coords)
        : coords{coords[0], coords[1]},
          blocks()
{
    int i=0;
    for (char x=0; x<16; x++){
        for (char y=0; y<16; y++, i++){
            char p[2]{x,y};
            this->blocks[i] = block(p);
        }

    }
}