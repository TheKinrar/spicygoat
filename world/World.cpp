//
// Created by thekinrar on 03/04/19.
//

#include <cmath>
#include <io/stream_reader.h>
#include <io/izlibstream.h>
#include <fstream>
#include <iostream>
#include <tag_primitive.h>
#include "World.h"

World::World() {
    std::ifstream ifs("world/level.dat", std::ios::binary);
    zlib::izlibstream buf(ifs);

    auto level = nbt::io::read_compound(buf).second->at("Data").as<nbt::tag_compound>();

    spawnPosition = Position(level.at("SpawnX").as<nbt::tag_int>(), level.at("SpawnY").as<nbt::tag_int>(), level.at("SpawnZ").as<nbt::tag_int>());
}

Region * World::getRegion(int32_t x, int32_t z) {
    m_chunkLoading.lock();

    auto it = regions.find(Position2D(x, z));

    if(it == regions.end()) {
        auto region = new Region(x, z);
        regions[Position2D(x, z)] = region;

        m_chunkLoading.unlock();
        return region;
    }

    m_chunkLoading.unlock();
    return it->second;
}

ChunkColumn * World::getChunk(int32_t x, int32_t z) {
    return getRegion(floor((double) x / 32), floor((double) z / 32))->getColumn(x % 32 + (x < 0 ? 32 : 0), z % 32 + (z < 0 ? 32 : 0));
}

const Position &World::getSpawnPosition() const {
    return spawnPosition;
}
