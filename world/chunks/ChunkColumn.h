//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_CHUNKCOLUMN_H
#define SPICYGOAT_CHUNKCOLUMN_H


#include <stdint-gcc.h>
#include "Chunk.h"

class ChunkColumn {
public:
    ChunkColumn(int32_t x, int32_t z);

    int32_t getX() const;

    int32_t getZ() const;

    Chunk* getChunk(int8_t y);

private:
    int32_t x, z;
    Chunk* chunks[16];
};


#endif //SPICYGOAT_CHUNKCOLUMN_H
