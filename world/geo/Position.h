//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_POSITION_H
#define SPICYGOAT_POSITION_H

#include <cstdint>
#include <string>

class Position {
public:
    Position(int32_t x, int16_t y, int32_t z);

    int32_t getX() const;

    int16_t getY() const;

    int32_t getZ() const;

    std::string toString() const;

private:
    int32_t x;
    int16_t y;
    int32_t z;
};


#endif//SPICYGOAT_POSITION_H
