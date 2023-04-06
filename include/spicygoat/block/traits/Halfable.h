//
// Created by thekinrar on 23/01/23.
//

#pragma once

#include <spicygoat/block/BlockTrait.h>
#include <spicygoat/block/properties/properties.h>

class Halfable : public BlockTrait {
   public:
    [[nodiscard]]
    std::shared_ptr<BlockState> transformStateToPlace(const BlockPlaceContext& ctx,
                                                      const std::shared_ptr<BlockState>& base) const override {
        auto top = ctx.packet.face == Face::Bottom || (ctx.packet.face != Face::Top && ctx.packet.cursorY > 0.5);
        return base->with(Properties::block_half, top ? "top" : "bottom");
    }
};
