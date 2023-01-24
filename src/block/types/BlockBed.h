//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include "../Block.h"
#include "../property/properties.h"
#include "../traits.h"

class BlockBed : public Block {
   public:
    BlockBed(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Traits::orientable},
                {Properties::horizontal_facing, Properties::occupied, Properties::bed_part},
                defaultValues) {}
};
