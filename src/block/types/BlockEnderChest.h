//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include "../Block.h"
#include "../property/properties.h"
#include "../traits.h"

class BlockEnderChest : public Block {
   public:
    BlockEnderChest(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Traits::orientable},
                {Properties::horizontal_facing, Properties::waterlogged},
                defaultValues) {}
};
