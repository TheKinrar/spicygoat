#pragma once

#include <spicygoat/util/Enum.h>

class Thickness : public Enum {
    explicit Thickness(const std::string& name) : Enum(name) {}

   public:
    static const Thickness tip_merge, tip, frustum, middle, base;

    static const std::vector<Thickness> values;
};

inline const Thickness Thickness::tip_merge = Thickness("tip_merge");
inline const Thickness Thickness::tip = Thickness("tip");
inline const Thickness Thickness::frustum = Thickness("frustum");
inline const Thickness Thickness::middle = Thickness("middle");
inline const Thickness Thickness::base = Thickness("base");

inline const std::vector<Thickness> Thickness::values = {tip_merge, tip, frustum, middle, base};
