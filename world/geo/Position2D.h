//
// Created by thekinrar on 03/04/19.
//

#ifndef SPICYGOAT_POSITION2D_H
#define SPICYGOAT_POSITION2D_H


#include <ostream>
#include <stdint-gcc.h>

class Position2D {
public:
    Position2D(int32_t x, int32_t z);

    bool operator<(const Position2D &rhs) const;

    bool operator>(const Position2D &rhs) const;

    bool operator<=(const Position2D &rhs) const;

    bool operator>=(const Position2D &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Position2D &d);

private:
    int32_t x, z;
};


#endif//SPICYGOAT_POSITION2D_H
