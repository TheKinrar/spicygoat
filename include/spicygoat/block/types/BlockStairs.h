//
// Created by thekinrar on 22/01/23.
//

#pragma once

#include <spicygoat/block/Block.h>
#include <spicygoat/block/properties/properties.h>
#include <spicygoat/block/traits.h>

class BlockStairs : public Block {
   public:
    BlockStairs(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(
              name, {Traits::halfable, Traits::orientable},
              {Properties::horizontal_facing, Properties::block_half, Properties::stair_shape, Properties::waterlogged},
              defaultValues) {}
};
