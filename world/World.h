//
// Created by thekinrar on 03/04/19.
//

#ifndef SPICYGOAT_WORLD_H
#define SPICYGOAT_WORLD_H

#include <map>
#include <mutex>
#include "geo/Position2D.h"
#include "chunks/Region.h"
#include "geo/Position.h"

class World {
public:
    World();

    Region * getRegion(int32_t x, int32_t z);
    ChunkColumn * getChunk(int32_t x, int32_t z);

    const Position &getSpawnPosition() const;

private:
    std::mutex m_chunkLoading;

    std::map<Position2D, Region*> regions;

    Position spawnPosition = Position(0, 0, 0);
};


#endif //SPICYGOAT_WORLD_H
