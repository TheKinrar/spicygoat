//
// Created by thekinrar on 03/04/19.
//

#ifndef SPICYGOAT_REGION_H
#define SPICYGOAT_REGION_H


#include <map>
#include "../geo/Position2D.h"
#include "ChunkColumn.h"

class Region {
public:
    Region(int32_t x, int32_t z);

    ChunkColumn *getColumn(int32_t x, int32_t z);

private:
    int32_t x, z;

    std::map<Position2D, ChunkColumn *> columns;
};


#endif //SPICYGOAT_REGION_H
