//
// Created by thekinrar on 02/04/19.
//

#include "Chunk.h"

Chunk::Chunk(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}

int32_t Chunk::getX() const {
    return x;
}

int32_t Chunk::getY() const {
    return y;
}

int32_t Chunk::getZ() const {
    return z;
}
