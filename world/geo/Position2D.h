//
// Created by thekinrar on 03/04/19.
//

#ifndef SPICYGOAT_POSITION2D_H
#define SPICYGOAT_POSITION2D_H


#include <stdint-gcc.h>
#include <ostream>

class Position2D {
public:
    Position2D(int32_t x, int32_t z);

    bool operator==(const Position2D &rhs) const {
        return x == rhs.x &&
               z == rhs.z;
    }

    bool operator!=(const Position2D &rhs) const {
        return !(rhs == *this);
    }

    friend std::ostream &operator<<(std::ostream &os, const Position2D &d);

    const int32_t x, z;
};

template<>
struct std::hash<Position2D> {
    std::size_t operator()(Position2D const& pos) const noexcept {
        return pos.x ^(pos.z << 1);
    }
};

#endif //SPICYGOAT_POSITION2D_H
