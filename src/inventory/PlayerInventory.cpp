//
// Created by nicolas on 1/9/23.
//

#include "PlayerInventory.h"

void PlayerInventory::set(int slot, const ItemStack& stack) {
    slots[slot] = stack;
    player.getConnection().sendPacket(PacketSetInventorySlot(0, slot, stack));
}
