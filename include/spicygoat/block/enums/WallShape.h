//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class WallShape : public Enum {
    explicit WallShape(const std::string& name) : Enum(name) {}

   public:
    static const WallShape none, low, tall;

    static const std::vector<WallShape> values;
};

inline const WallShape WallShape::none = WallShape("none");
inline const WallShape WallShape::low = WallShape("low");
inline const WallShape WallShape::tall = WallShape("tall");

inline const std::vector<WallShape> WallShape::values = {none, low, tall};
