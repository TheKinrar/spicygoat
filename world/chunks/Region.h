//
// Created by thekinrar on 03/04/19.
//

#ifndef SPICYGOAT_REGION_H
#define SPICYGOAT_REGION_H


#include <unordered_map>
#include "../geo/Position2D.h"
#include "ChunkColumn.h"
#include "../../protocol/PacketData.h"

class Region {
public:
    static std::unique_ptr<Region> load(int32_t x, int32_t z);

    Region(int32_t x, int32_t z, std::shared_ptr<char[]> data) : x(x), z(z), data(std::move(data)) {}

    ChunkColumn& getColumn(int32_t x, int32_t z);

private:
    const int32_t x, z;

    std::shared_ptr<char[]> data;

    std::unordered_map<Position2D, std::unique_ptr<ChunkColumn>> columns;
};


#endif //SPICYGOAT_REGION_H
