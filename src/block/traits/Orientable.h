//
// Created by thekinrar on 23/01/23.
//

#pragma once

#include "../BlockTrait.h"
#include "../property/properties.h"

class Orientable : public BlockTrait {
   public:
    [[nodiscard]]
    std::shared_ptr<BlockState> transformStateToPlace(const BlockPlaceContext& ctx,
                          const std::shared_ptr<BlockState>& base) const override {
        return base->with(Properties::horizontal_facing, Direction::fromYaw(ctx.playerLocation.getYaw()).name());
    }
};
