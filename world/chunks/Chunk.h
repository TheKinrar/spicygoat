//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_CHUNK_H
#define SPICYGOAT_CHUNK_H


#include <stdint-gcc.h>

class Chunk {
public:
    Chunk(int32_t x, int32_t y, int32_t z);

    int32_t getX() const;

    int32_t getY() const;

    int32_t getZ() const;

private:
    int32_t x, y, z;
};


#endif //SPICYGOAT_CHUNK_H
