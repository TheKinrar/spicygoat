//
// Created by thekinrar on 03/04/19.
//

#ifndef SPICYGOAT_WORLD_H
#define SPICYGOAT_WORLD_H

#include <map>
#include <mutex>

#include "chunks/Region.h"
#include "geo/ChunkPosition.h"
#include "geo/Position.h"
#include "geo/Position2D.h"

class World {
   public:
    World();

    Region& getRegion(int32_t x, int32_t z);
    ChunkColumn& getChunk(int32_t x, int32_t z);
    ChunkColumn& getChunk(ChunkPosition pos) {
        return getChunk(pos.getX(), pos.getZ());
    }

    const Position& getSpawnPosition() const;

    BlockState getBlockState(Position pos) {
        auto& chunk = getChunk(pos.getChunkX(), pos.getChunkZ());
        auto& section = chunk.getChunk(pos.getChunkY());
        return section.getBlockState(pos.getInChunkX(), pos.getInChunkY(), pos.getInChunkZ());
    }

    void setBlockState(Position pos, BlockState state) {
        auto& chunk = getChunk(pos.getChunkX(), pos.getChunkZ());
        auto& section = chunk.getChunk(pos.getChunkY());
        section.setBlockState(pos.getInChunkX(), pos.getInChunkY(), pos.getInChunkZ(), state);
    }

   private:
    std::mutex m_chunkLoading;

    std::unordered_map<Position2D, std::unique_ptr<Region>> regions;

    Position spawnPosition = Position(0, 0, 0);
};

#endif  // SPICYGOAT_WORLD_H
