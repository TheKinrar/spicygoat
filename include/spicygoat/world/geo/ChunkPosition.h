//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include <cstdint>

class ChunkPosition {
    int32_t x, y, z;

   public:
    ChunkPosition(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}

    [[nodiscard]]
    int32_t getX() const {
        return x;
    }

    [[nodiscard]]
    int32_t getY() const {
        return y;
    }

    [[nodiscard]]
    int32_t getZ() const {
        return z;
    }

    [[nodiscard]]
    int32_t getRegionX() const {
        return x >> 5;
    }

    [[nodiscard]]
    int32_t getRegionZ() const {
        return z >> 5;
    }

    [[nodiscard]]
    int32_t getInRegionX() const {
        return x < 0 ? (32 - (-x % 32)) % 32 : x % 32;
    }

    [[nodiscard]]
    int32_t getInRegionZ() const {
        return z < 0 ? (32 - (-z % 32)) % 32 : z % 32;
    }

    bool operator==(const ChunkPosition &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!=(const ChunkPosition &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const ChunkPosition &rhs) const {
        return std::tie(x, y, z) < std::tie(rhs.x, rhs.y, rhs.z);
    }
    bool operator>(const ChunkPosition &rhs) const {
        return rhs < *this;
    }
    bool operator<=(const ChunkPosition &rhs) const {
        return !(rhs < *this);
    }
    bool operator>=(const ChunkPosition &rhs) const {
        return !(*this < rhs);
    }
};

template <>
struct std::hash<ChunkPosition> {
    std::size_t operator()(ChunkPosition const &pos) const noexcept {
        return pos.getX() ^ (pos.getY() << 1) ^ (pos.getZ() << 1);
    }
};
