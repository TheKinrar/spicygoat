//
// Created by thekinrar on 03/04/19.
//

#include <spicygoat/world/geo/Position2D.h>

Position2D::Position2D(int32_t x, int32_t z) : x(x), z(z) {}

std::ostream &operator<<(std::ostream &os, const Position2D &d) {
    os << "Pos2D{x=" << d.x << ",z=" << d.z << "}";
    return os;
}
