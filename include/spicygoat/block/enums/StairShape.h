#pragma once

#include <spicygoat/util/Enum.h>

class StairShape : public Enum {
    explicit StairShape(const std::string& name) : Enum(name) {}

   public:
    static const StairShape straight, inner_left, inner_right, outer_left, outer_right;

    static const std::vector<StairShape> values;
};

inline const StairShape StairShape::straight = StairShape("straight");
inline const StairShape StairShape::inner_left = StairShape("inner_left");
inline const StairShape StairShape::inner_right = StairShape("inner_right");
inline const StairShape StairShape::outer_left = StairShape("outer_left");
inline const StairShape StairShape::outer_right = StairShape("outer_right");

inline const std::vector<StairShape> StairShape::values = {straight, inner_left, inner_right, outer_left, outer_right};
