//
// Created by thekinrar on 23/01/23.
//

#pragma once

#include <spicygoat/block/BlockState.h>
#include <spicygoat/block/properties/Property.h>
#include <spicygoat/util/BlockPlaceContext.h>

#include <memory>

class BlockTrait {
   public:
    [[nodiscard]]
    virtual std::shared_ptr<BlockState> transformStateToPlace(const BlockPlaceContext& ctx,
                                                              const std::shared_ptr<BlockState>& base) const {
        return base;
    };
};
