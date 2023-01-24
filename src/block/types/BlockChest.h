//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include "../Block.h"
#include "../property/properties.h"
#include "../traits.h"

class BlockChest : public Block {
   public:
    BlockChest(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Traits::orientable},
                {Properties::chest_type, Properties::horizontal_facing, Properties::waterlogged},
                defaultValues) {}
};
