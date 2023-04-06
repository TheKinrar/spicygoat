//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class WallMountLocation : public Enum {
    explicit WallMountLocation(const std::string& name) : Enum(name) {}

   public:
    static const WallMountLocation floor, wall, ceiling;

    static const std::vector<WallMountLocation> values;
};

inline const WallMountLocation WallMountLocation::floor = WallMountLocation("floor");
inline const WallMountLocation WallMountLocation::wall = WallMountLocation("wall");
inline const WallMountLocation WallMountLocation::ceiling = WallMountLocation("ceiling");

inline const std::vector<WallMountLocation> WallMountLocation::values = {floor, wall, ceiling};
