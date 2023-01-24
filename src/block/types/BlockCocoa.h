//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include "../Block.h"
#include "../property/properties.h"
#include "../traits.h"

class BlockCocoa : public Block {
   public:
    BlockCocoa(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Traits::orientable}, {Properties::age_2, Properties::horizontal_facing}, defaultValues) {}
};
