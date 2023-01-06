//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_POSITION_H
#define SPICYGOAT_POSITION_H

#include <cstdint>
#include <stdexcept>
#include <string>

#include "Face.h"

class Position {
   public:
    Position(int32_t x, int32_t y, int32_t z);

    [[nodiscard]] int32_t getX() const;

    [[nodiscard]] int32_t getY() const;

    [[nodiscard]] int32_t getZ() const;

    [[nodiscard]] int32_t getChunkX() const {
        return x >> 4;
    }

    [[nodiscard]] int32_t getChunkY() const {
        return y >> 4;
    }

    [[nodiscard]] int32_t getChunkZ() const {
        return z >> 4;
    }

    [[nodiscard]] int32_t getRegionX() const {
        return x >> 9;
    }

    [[nodiscard]] int32_t getRegionZ() const {
        return z >> 9;
    }

    [[nodiscard]] int32_t getInChunkX() const {
        return x < 0 ? (16 - (-x % 16)) % 16 : x % 16;
    }

    [[nodiscard]] int32_t getInChunkY() const {
        return y < 0 ? (16 - (-y % 16)) % 16 : y % 16;
    }

    [[nodiscard]] int32_t getInChunkZ() const {
        return z < 0 ? (16 - (-z % 16)) % 16 : z % 16;
    }

    [[nodiscard]] Position relative(Face face) const {
        switch(face) {
            case Face::Bottom:
                return relative(0, -1, 0);
            case Face::Top:
                return relative(0, 1, 0);
            case Face::North:
                return relative(0, 0, -1);
            case Face::South:
                return relative(0, 0, 1);
            case Face::West:
                return relative(-1, 0, 0);
            case Face::East:
                return relative(1, 0, 0);
        }

        throw std::runtime_error("Bad enum value");
    }

    [[nodiscard]] Position relative(int32_t x, int16_t y, int32_t z) const {
        return {this->x + x, this->y + y, this->z + z};
    }

    [[nodiscard]] std::string toString() const;

   private:
    int32_t x;
    int32_t y;
    int32_t z;
};

#endif  // SPICYGOAT_POSITION_H
