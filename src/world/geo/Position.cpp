//
// Created by thekinrar on 02/04/19.
//

#include <spicygoat/world/geo/Position.h>

Position::Position(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}

int32_t Position::getX() const {
    return x;
}

int32_t Position::getY() const {
    return y;
}

int32_t Position::getZ() const {
    return z;
}

std::string Position::toString() const {
    return std::string("Position{x=") + std::to_string(x) + ",y=" + std::to_string(y) + ",z=" + std::to_string(z) + "}";
}
