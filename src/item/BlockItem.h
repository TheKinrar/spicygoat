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
    const Block& block;

   public:
    BlockItem(const std::string& name, const Block& block) : Item(name), block(block) {}

    [[nodiscard]] const Block& getBlock() const {
        return block;
    }

    void onUseOn(EntityPlayer& player, const PacketUseItemOn& packet) const override;
};
