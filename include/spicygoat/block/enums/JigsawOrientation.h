//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class JigsawOrientation : public Enum {
    explicit JigsawOrientation(const std::string& name) : Enum(name) {}

   public:
    static const JigsawOrientation down_east, down_north, down_south, down_west, up_east, up_north, up_south, up_west,
        west_up, east_up, north_up, south_up;

    static const std::vector<JigsawOrientation> values;
};

inline const JigsawOrientation JigsawOrientation::down_east = JigsawOrientation("down_east");
inline const JigsawOrientation JigsawOrientation::down_north = JigsawOrientation("down_north");
inline const JigsawOrientation JigsawOrientation::down_south = JigsawOrientation("down_south");
inline const JigsawOrientation JigsawOrientation::down_west = JigsawOrientation("down_west");
inline const JigsawOrientation JigsawOrientation::up_east = JigsawOrientation("up_east");
inline const JigsawOrientation JigsawOrientation::up_north = JigsawOrientation("up_north");
inline const JigsawOrientation JigsawOrientation::up_south = JigsawOrientation("up_south");
inline const JigsawOrientation JigsawOrientation::up_west = JigsawOrientation("up_west");
inline const JigsawOrientation JigsawOrientation::west_up = JigsawOrientation("west_up");
inline const JigsawOrientation JigsawOrientation::east_up = JigsawOrientation("east_up");
inline const JigsawOrientation JigsawOrientation::north_up = JigsawOrientation("north_up");
inline const JigsawOrientation JigsawOrientation::south_up = JigsawOrientation("south_up");

inline const std::vector<JigsawOrientation> JigsawOrientation::values = {down_east, down_north, down_south, down_west,
                                                                         up_east,   up_north,   up_south,   up_west,
                                                                         west_up,   east_up,    north_up,   south_up};
