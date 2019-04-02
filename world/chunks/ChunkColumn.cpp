//
// Created by thekinrar on 02/04/19.
//

#include "ChunkColumn.h"

ChunkColumn::ChunkColumn(int32_t x, int32_t z) : x(x), z(z) {}

int32_t ChunkColumn::getX() const {
    return x;
}

int32_t ChunkColumn::getZ() const {
    return z;
}

Chunk *ChunkColumn::getChunk(int8_t y) {
    return chunks[y];
}
