//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_CHUNK_H
#define SPICYGOAT_CHUNK_H

#include "ChunkPalette.h"
#include <stdint-gcc.h>
#include <tag_compound.h>

class Chunk {
public:
    Chunk(int32_t x, int32_t y, int32_t z);

    int32_t getX() const;

    int32_t getY() const;

    int32_t getZ() const;

    ChunkPalette *getPalette() const;

    bool hasData();

    void loadNBT(nbt::tag_compound &);

    void writeToByteArray(std::vector<std::byte> &array);

private:
    int32_t x, y, z;

    ChunkPalette *palette = nullptr;
    std::vector<int64_t> blockStates;

    std::vector<int8_t> blockLight;
    std::vector<int8_t> skyLight;
};


#endif//SPICYGOAT_CHUNK_H
