//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "../world/blocks/BlockState.h"
#include "Item.h"

#include <utility>

/**
 * An item that represents a placeable block.
 */
class BlockItem : public Item {
    BlockState block;

   public:
    BlockItem(const std::string& name, BlockState  block) : Item(name), block(std::move(block)) {}

    [[nodiscard]] const BlockState& getBlock() const {
        return block;
    }

    void onUseOn(EntityPlayer& player, const PacketUseItemOn& packet) const override;
};
