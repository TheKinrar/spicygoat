#pragma once

#include <spicygoat/util/Enum.h>

class DoorHinge : public Enum {
    explicit DoorHinge(const std::string& name) : Enum(name) {}

   public:
    static const DoorHinge left, right;

    static const std::vector<DoorHinge> values;
};

inline const DoorHinge DoorHinge::left = DoorHinge("left");
inline const DoorHinge DoorHinge::right = DoorHinge("right");

inline const std::vector<DoorHinge> DoorHinge::values = {left, right};
