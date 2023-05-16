//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_CHUNKCOLUMN_H
#define SPICYGOAT_CHUNKCOLUMN_H

#include <spicygoat/world/chunks/Chunk.h>
#include <spicygoat/world/chunks/ChunkPalette.h>
#include <spicygoat/world/geo/Position2D.h>
#include <stdint.h>
#include <tag_compound.h>

class ChunkColumn {
   public:
    ChunkColumn(int32_t x, int32_t z);
    ChunkColumn(const ChunkColumn&) = delete;

    Position2D getPosition2D();

    int32_t getX() const;

    int32_t getZ() const;

    Chunk& getChunk(int32_t y);

    bool hasData();

    void setNbt(std::unique_ptr<nbt::tag_compound>& nbt);

    void writeDataToByteArray(std::vector<std::byte>&);
    void writeLightToByteArray(std::vector<std::byte>&);
    void writeHeightMapsToByteArray(std::vector<std::byte>&);

    std::string toString();

   private:
    int32_t x, z;
    std::unique_ptr<Chunk> chunks[26];

    std::unique_ptr<nbt::tag_compound> nbt = nullptr;
};

#endif  // SPICYGOAT_CHUNKCOLUMN_H
