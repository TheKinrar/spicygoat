//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class DoubleBlockHalf : public Enum {
    explicit DoubleBlockHalf(const std::string& name) : Enum(name) {}

   public:
    static const DoubleBlockHalf upper, lower;

    static const std::vector<DoubleBlockHalf> values;
};

inline const DoubleBlockHalf DoubleBlockHalf::upper = DoubleBlockHalf("upper");
inline const DoubleBlockHalf DoubleBlockHalf::lower = DoubleBlockHalf("lower");

inline const std::vector<DoubleBlockHalf> DoubleBlockHalf::values = {upper, lower};
