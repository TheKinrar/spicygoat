//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class Axis : public Enum {
    explicit Axis(const std::string& name) : Enum(name) {}

   public:
    static const Axis x, y, z;

    static const std::vector<Axis> values;
};

const inline Axis Axis::x = Axis("x");
const inline Axis Axis::y = Axis("y");
const inline Axis Axis::z = Axis("z");

const inline std::vector<Axis> Axis::values = {x, y, z};
