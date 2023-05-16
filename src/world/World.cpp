//
// Created by thekinrar on 03/04/19.
//

#include <io/izlibstream.h>
#include <io/stream_reader.h>
#include <spicygoat/world/World.h>
#include <spicygoat/world/geo/ChunkPosition.h>
#include <tag_primitive.h>

#include <cmath>
#include <fstream>
#include <iostream>

World::World() {
    std::ifstream ifs("world/level.dat", std::ios::binary);
    zlib::izlibstream buf(ifs);

    auto level = nbt::io::read_compound(buf).second->at("Data").as<nbt::tag_compound>();

    spawnPosition = Position(level.at("SpawnX").as<nbt::tag_int>(), level.at("SpawnY").as<nbt::tag_int>(),
                             level.at("SpawnZ").as<nbt::tag_int>());
}

Region& World::getRegion(int32_t x, int32_t z) {
    m_chunkLoading.lock();

    auto it = regions.find(Position2D(x, z));

    if(it == regions.end()) {
        regions[Position2D(x, z)] = Region::load(x, z);

        m_chunkLoading.unlock();
        return *regions[Position2D(x, z)];
    }

    m_chunkLoading.unlock();
    return *it->second;
}

ChunkColumn& World::getChunk(int32_t x, int32_t z) {
    ChunkPosition pos(x, 0, z);
    return getRegion(pos.getRegionX(), pos.getRegionZ()).getColumn(pos.getInRegionX(), pos.getInRegionZ());
}

const Position& World::getSpawnPosition() const {
    return spawnPosition;
}
