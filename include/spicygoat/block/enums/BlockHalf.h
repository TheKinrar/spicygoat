//
// Created by thekinrar on 19/01/23.
//

#pragma once

#include <spicygoat/util/Enum.h>

class BlockHalf : public Enum {
    explicit BlockHalf(const std::string& name) : Enum(name) {}

   public:
    static const BlockHalf top, bottom;

    static const std::vector<BlockHalf> values;
};

inline const BlockHalf BlockHalf::top = BlockHalf("top");
inline const BlockHalf BlockHalf::bottom = BlockHalf("bottom");

inline const std::vector<BlockHalf> BlockHalf::values = {top, bottom};
