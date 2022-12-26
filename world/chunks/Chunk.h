//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_CHUNK_H
#define SPICYGOAT_CHUNK_H

#include <tag_compound.h>
#include <stdint-gcc.h>
#include <iostream>
#include <bitset>
#include "ChunkPalette.h"

class Chunk {
public:
    Chunk(int32_t x, int32_t y, int32_t z);

    int32_t getX() const;

    int32_t getY() const;

    int32_t getZ() const;

    ChunkPalette *getPalette() const;

    bool hasData();

    void loadNBT(nbt::tag_compound&);

    void writeToByteArray(std::vector<std::byte> &array);

    void setBlockState(int x, int y, int z, BlockState state) {
        if(!hasData())
            throw std::runtime_error("Can't set block in unloaded chunk");

        uint64_t id = palette->getBlockStateId(state);
        if(id != -1) {
            if(palette->getBitsPerBlock() != 0) {
                int i = (((16 * y) + z) * 16) + x; // Block number
                int iLong = i / palette->getBlocksPerLong(); // Index of the long containing the block
                int offset = i % palette->getBlocksPerLong(); // Offset of the block in the long
                int beforeBits = offset * palette->getBitsPerBlock(); // Count of prefix bits in the long
                int afterBits = 64 - beforeBits - palette->getBitsPerBlock(); // Count of suffix bits in the long

                uint64_t beforeMask = ((uint64_t) 1 << beforeBits) - 1; // Prefix mask
                uint64_t afterMask = (((uint64_t) 1 << afterBits) - 1) << (64 - afterBits); // Suffix mask

                uint64_t current = blockStates[iLong];
                uint64_t updated = (current & beforeMask) | (id << beforeBits) | (current & afterMask);
                blockStates[iLong] = (int64_t) updated;
            }
        } else {
            std::cerr << "sorry but no" << std::endl;
        }
    }

private:
    int32_t x, y, z;

    ChunkPalette *palette = nullptr;
    std::vector<int64_t> blockStates;

    std::vector<int8_t> blockLight;
    std::vector<int8_t> skyLight;
};


#endif //SPICYGOAT_CHUNK_H
