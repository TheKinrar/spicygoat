//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <utility>

#include "../../util/Enum.h"
#include "Axis.h"

class Direction : public Enum {
    Axis axis;

    Direction(const std::string& name, Axis axis) : Enum(name), axis(std::move(axis)) {}

   public:
    static const Direction down, up, north, south, west, east;
    static const std::vector<Direction> values;
};

inline const Direction Direction::down = Direction("down", Axis::y);
inline const Direction Direction::up = Direction("up", Axis::y);
inline const Direction Direction::north = Direction("north", Axis::z);
inline const Direction Direction::south = Direction("south", Axis::z);
inline const Direction Direction::west = Direction("west", Axis::x);
inline const Direction Direction::east = Direction("east", Axis::x);

inline const std::vector<Direction> Direction::values = {down, up, north, south, west, east};
