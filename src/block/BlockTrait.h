//
// Created by thekinrar on 23/01/23.
//

#pragma once

#include <memory>

#include "../util/BlockPlaceContext.h"
#include "BlockState.h"
#include "property/Property.h"

class BlockTrait {
   public:
    [[nodiscard]]
    virtual std::shared_ptr<BlockState> transformStateToPlace(const BlockPlaceContext& ctx,
                                                              const std::shared_ptr<BlockState>& base) const {
        return base;
    };
};
