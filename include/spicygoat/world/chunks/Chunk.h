//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_CHUNK_H
#define SPICYGOAT_CHUNK_H

#include <spicygoat/world/chunks/ChunkPalette.h>
#include <tag_compound.h>

#include <bitset>
#include <cstdint>
#include <iostream>

class Chunk {
   private:
    int32_t x, y, z;

    std::shared_ptr<ChunkPalette> palette;
    std::vector<int64_t> blockStates;

    std::vector<std::byte> blockLight;
    std::vector<std::byte> skyLight;

   public:
    Chunk(int32_t x, int32_t y, int32_t z);
    Chunk(const Chunk&) = delete;

    int32_t getX() const;

    int32_t getY() const;

    int32_t getZ() const;

    [[nodiscard]]
    const ChunkPalette& getPalette() const;

    bool hasData();

    bool hasBlockLightData() {
        return !blockLight.empty();
    }

    bool hasSkyLightData() {
        return !skyLight.empty();
    }

    [[nodiscard]]
    const std::vector<std::byte>& getBlockLightData() const {
        return blockLight;
    }

    [[nodiscard]]
    const std::vector<std::byte>& getSkyLightData() const {
        return skyLight;
    }

    void loadNBT(nbt::tag_compound&);

    void writeDataToByteArray(std::vector<std::byte>& array);

    void setBlockState(int x, int y, int z, const std::shared_ptr<BlockState>& state) {
        if(!hasData()) throw std::runtime_error("Can't set block in unloaded chunk");

        int16_t id = palette->getBlockStateId(state);
        if(id == -1) {
            auto grown = palette->grow(state);
            rewriteData(*palette, *grown);
            palette = grown;

            id = palette->getBlockStateId(state);
        }

        writeBlockState(blockStates, *palette, x, y, z, id);
    }

    const std::shared_ptr<BlockState>& getBlockState(int x, int y, int z) {
        if(!hasData()) throw std::runtime_error("Can't get block in unloaded chunk");

        return palette->getBlockState(readBlockState(blockStates, *palette, x, y, z));
    }

    int16_t countAirBlocks() {
        if(palette->isSingle()) {
            return palette->getSingleBlockState()->getBlock().isAir() ? 4096 : 0;
        } else {
            int16_t n = 0;
            for(int x = 0; x < 16; ++x) {
                for(int y = 0; y < 16; ++y) {
                    for(int z = 0; z < 16; ++z) {
                        if(getBlockState(x, y, z)->getBlock().isAir()) {
                            n++;
                        }
                    }
                }
            }
            return n;
        }
    }

   private:
    void rewriteData(const ChunkPalette& from, const ChunkPalette& to) {
        if(to.isSingle()) return;

        std::vector<int64_t> newStates(std::ceil((double)4096 / to.getBlocksPerLong()));
        for(int x = 0; x < 16; ++x) {
            for(int y = 0; y < 16; ++y) {
                for(int z = 0; z < 16; ++z) {
                    writeBlockState(newStates, to, x, y, z, readBlockState(blockStates, from, x, y, z));
                }
            }
        }
        blockStates = newStates;
    }

    [[nodiscard]]
    static int64_t readBlockState(const std::vector<int64_t>& data, const ChunkPalette& palette, int x, int y, int z) {
        if(palette.isSingle()) return 0;

        int i = (((16 * y) + z) * 16) + x;                    // Block number
        int iLong = i / palette.getBlocksPerLong();           // Index of the long containing the block
        int offset = i % palette.getBlocksPerLong();          // Offset of the block in the long
        int beforeBits = offset * palette.getBitsPerBlock();  // Count of prefix bits in the long

        uint64_t mask = (((uint64_t)1 << palette.getBitsPerBlock()) - 1);

        return (int64_t)((data[iLong] >> beforeBits) & mask);
    }

    static void writeBlockState(std::vector<int64_t>& data, const ChunkPalette& palette, int x, int y, int z,
                                int64_t id) {
        if(palette.getBitsPerBlock() != 0) {
            int i = (((16 * y) + z) * 16) + x;                            // Block number
            int iLong = i / palette.getBlocksPerLong();                   // Index of the long containing the block
            int offset = i % palette.getBlocksPerLong();                  // Offset of the block in the long
            int beforeBits = offset * palette.getBitsPerBlock();          // Count of prefix bits in the long
            int afterBits = 64 - beforeBits - palette.getBitsPerBlock();  // Count of suffix bits in the long

            uint64_t beforeMask = ((uint64_t)1 << beforeBits) - 1;                      // Prefix mask
            uint64_t afterMask = (((uint64_t)1 << afterBits) - 1) << (64 - afterBits);  // Suffix mask

            uint64_t current = data[iLong];
            uint64_t updated = (current & beforeMask) | (id << beforeBits) | (current & afterMask);
            data[iLong] = (int64_t)updated;
        }
    }
};

#endif  // SPICYGOAT_CHUNK_H
