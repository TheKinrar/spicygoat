//
// Created by thekinrar on 06/01/23.
//

#pragma once

#include "Item.h"

#include <utility>

/**
 * An item that represents a placeable block.
 */
class BlockItem : public Item {
    const std::shared_ptr<BlockState> block;

   public:
    BlockItem(const std::string& name, const std::shared_ptr<BlockState>& block) : Item(name), block(block) {}

    [[nodiscard]] const std::shared_ptr<BlockState>& getBlock() const {
        return block;
    }

    void onUseOn(EntityPlayer& player, const PacketUseItemOn& packet) const override;
};
