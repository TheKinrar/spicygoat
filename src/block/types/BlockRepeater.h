//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include "../Block.h"
#include "../property/properties.h"
#include "../traits.h"

class BlockRepeater : public Block {
   public:
    BlockRepeater(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Traits::orientable},
                {Properties::delay, Properties::horizontal_facing, Properties::locked, Properties::powered},
                defaultValues) {}
};
