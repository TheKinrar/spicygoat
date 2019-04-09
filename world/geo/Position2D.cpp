//
// Created by thekinrar on 03/04/19.
//

#include "Position2D.h"

Position2D::Position2D(int32_t x, int32_t z) : x(x), z(z) {}

bool Position2D::operator<(const Position2D &rhs) const {
    if (x < rhs.x)
        return true;
    if (rhs.x < x)
        return false;
    return z < rhs.z;
}

bool Position2D::operator>(const Position2D &rhs) const {
    return rhs < *this;
}

bool Position2D::operator<=(const Position2D &rhs) const {
    return !(rhs < *this);
}

bool Position2D::operator>=(const Position2D &rhs) const {
    return !(*this < rhs);
}
