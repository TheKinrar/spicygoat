//
// Created by thekinrar on 22/01/23.
//

#pragma once

#include "../Block.h"
#include "../property/properties.h"

class BlockStairs : public Block {
   public:
    BlockStairs(const Identifier& name, const std::vector<std::string>& defaultValues)
        : Block(name, {Properties::horizontal_facing, Properties::block_half, Properties::stair_shape, Properties::waterlogged}, defaultValues) {}

    std::shared_ptr<BlockState> getStateToPlace(const Location& loc, const PacketUseItemOn& packet) const override {
        auto top = packet.face == Face::Bottom || (packet.face != Face::Top && packet.cursorY > 0.5);

        return getDefaultState()
            ->with(Properties::horizontal_facing, Direction::fromYaw(loc.getYaw()).name())
            ->with(Properties::block_half, top ? "top" : "bottom");
    }
};
