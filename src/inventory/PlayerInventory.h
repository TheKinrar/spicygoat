//
// Created by thekinrar on 04/01/23.
//

#ifndef SPICYGOAT_PLAYERINVENTORY_H
#define SPICYGOAT_PLAYERINVENTORY_H

#include <utility>

#include "../item/ItemStack.h"

#define PLAYER_INVENTORY_SIZE 46

class PlayerInventory {
    ItemStack slots[PLAYER_INVENTORY_SIZE];
    int selectedSlot = 36;

   public:
    void setSlot(int slot, ItemStack stack) {
        if(slot < 5) throw std::runtime_error("Can't set crafting slots");

        slots[slot] = std::move(stack);
    }

    [[nodiscard]]
    std::vector<ItemStack> getSlots() const {
        return {std::begin(slots), std::end(slots)};
    }

    [[nodiscard]]
    ItemStack getSlot(int slot) const {
        return slots[slot];
    }

    [[nodiscard]]
    ItemStack getSelected() const {
        return getSlot(selectedSlot);
    }

    [[nodiscard]] int getSelectedSlot() const {
        return selectedSlot;
    }

    void setSelectedSlot(int selectedSlot) {
        this->selectedSlot = selectedSlot;
    }
};

#endif  // SPICYGOAT_PLAYERINVENTORY_H
