//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include <spicygoat/block/Block.h>
#include <spicygoat/block/properties/properties.h>
#include <spicygoat/block/traits.h>

class BlockFenceGate : public Block {
   public:
    BlockFenceGate(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Traits::orientable},
                {Properties::horizontal_facing, Properties::in_wall, Properties::open, Properties::powered},
                defaultValues) {}
};
