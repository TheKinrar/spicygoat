//
// Created by thekinrar on 02/04/19.
//

#include <string>
#include "ChunkColumn.h"

ChunkColumn::ChunkColumn(int32_t x, int32_t z) : x(x), z(z) {
    for(int i = 0; i < 16; ++i)
        chunks[i] = i == 4 ? new Chunk(x, i, z) : nullptr;
}

int32_t ChunkColumn::getX() const {
    return x;
}

int32_t ChunkColumn::getZ() const {
    return z;
}

Chunk *ChunkColumn::getChunk(int8_t y) {
    return chunks[y];
}

std::string ChunkColumn::toString() {
    return std::string("ChunkColumn{x=") + std::to_string(x) + ",z=" + std::to_string(z) + "}";
}

Position2D ChunkColumn::getPosition2D() {
    return Position2D(x, z);
}
