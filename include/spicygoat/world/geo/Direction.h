//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>
#include <spicygoat/world/geo/Axis.h>
#include <spicygoat/world/geo/Face.h>

#include <cmath>
#include <stdexcept>
#include <utility>

class Direction : public Enum {
    Axis axis;

    Direction(const std::string& name, Axis axis) : Enum(name), axis(std::move(axis)) {}

   public:
    static const Direction north, east, south, west, up, down;
    static const std::vector<Direction> values;

    [[nodiscard]]
    bool isVertical() const {
        return name() == "down" || name() == "up";
    }

    [[nodiscard]]
    bool isHorizontal() const {
        return !isVertical();
    }

    [[nodiscard]]
    const Direction& opposite() const {
        if(name() == "down") return up;
        if(name() == "up") return down;
        if(name() == "north") return south;
        if(name() == "south") return north;
        if(name() == "west") return east;
        if(name() == "east") return west;
        throw std::runtime_error("Invalid Direction enum value");
    }

    static const Direction& fromYaw(float yaw) {
        auto v = std::remainder(yaw, 360.0f);
        if(v < -135) return north;
        if(v < -45) return east;
        if(v < 45) return south;
        if(v < 135) return west;
        return north;
    }

    static const Direction& fromFace(Face face) {
        switch(face) {
            case Face::Bottom:
                return down;
            case Face::Top:
                return up;
            case Face::North:
                return north;
            case Face::South:
                return south;
            case Face::West:
                return west;
            case Face::East:
                return east;
        }
        throw std::runtime_error("Invalid Face enum value");
    }
};

inline const Direction Direction::north = Direction("north", Axis::z);
inline const Direction Direction::east = Direction("east", Axis::x);
inline const Direction Direction::south = Direction("south", Axis::z);
inline const Direction Direction::west = Direction("west", Axis::x);
inline const Direction Direction::up = Direction("up", Axis::y);
inline const Direction Direction::down = Direction("down", Axis::y);

inline const std::vector<Direction> Direction::values = {north, east, south, west, up, down};
