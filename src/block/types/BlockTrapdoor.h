//
// Created by thekinrar on 24/01/23.
//

#pragma once

#include "../Block.h"
#include "../traits.h"

class BlockTrapdoor : public Block {
   public:
    BlockTrapdoor(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Traits::halfable},
                {Properties::horizontal_facing, Properties::block_half, Properties::open, Properties::powered, Properties::waterlogged},
                defaultValues) {}

    std::shared_ptr<BlockState> getStateToPlace(const BlockPlaceContext& ctx) const override {
        auto& blockDir = Direction::fromFace(ctx.packet.face);
        auto state = Block::getStateToPlace(ctx);

        if(blockDir.isHorizontal()) {
            state = Traits::wallMountable.transformStateToPlace(ctx, state);
        } else {
            state = Traits::orientableOpposite.transformStateToPlace(ctx, state);
        }

        return state;
    }
};
