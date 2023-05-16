//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class RailShape : public Enum {
    explicit RailShape(const std::string& name) : Enum(name) {}

   public:
    static const RailShape north_south, east_west, ascending_east, ascending_west, ascending_north, ascending_south,
        south_east, south_west, north_west, north_east;

    static const std::vector<RailShape> values;
};

inline const RailShape RailShape::north_south = RailShape("north_south");
inline const RailShape RailShape::east_west = RailShape("east_west");
inline const RailShape RailShape::ascending_east = RailShape("ascending_east");
inline const RailShape RailShape::ascending_west = RailShape("ascending_west");
inline const RailShape RailShape::ascending_north = RailShape("ascending_north");
inline const RailShape RailShape::ascending_south = RailShape("ascending_south");
inline const RailShape RailShape::south_east = RailShape("south_east");
inline const RailShape RailShape::south_west = RailShape("south_west");
inline const RailShape RailShape::north_west = RailShape("north_west");
inline const RailShape RailShape::north_east = RailShape("north_east");

inline const std::vector<RailShape> RailShape::values = {
    north_south,     east_west,  ascending_east, ascending_west, ascending_north,
    ascending_south, south_east, south_west,     north_west,     north_east};
