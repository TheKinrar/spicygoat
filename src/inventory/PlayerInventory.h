//
// Created by thekinrar on 04/01/23.
//

#pragma once

#include <utility>

#include "../entities/types/EntityPlayer.h"
#include "../item/ItemStack.h"
#include "../protocol/packets/play/clientbound/PacketSetInventorySlot.h"

#define PLAYER_INVENTORY_SIZE 46

class PlayerInventory {
    EntityPlayer& player;
    ItemStack slots[PLAYER_INVENTORY_SIZE];
    int selectedSlot = 36;

   public:
    explicit PlayerInventory(EntityPlayer& player) : player(player) {}

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

    int findCompatibleSlot(const ItemStack& stack) {
        for(int i = 36; i <= 44; i++) {
            auto& item = slots[i];
            if(item.compatibleWith(stack) && item.count < 64)
                return i;
        }
        for(int i = 9; i <= 35; i++) {
            auto& item = slots[i];
            if(item.compatibleWith(stack) && item.count < 64)
                return i;
        }
        return -1;
    }

    int findEmptySlot() {
        for(int i = 36; i <= 44; i++) {
            auto& item = slots[i];
            if(!item.present)
                return i;
        }
        for(int i = 9; i <= 35; i++) {
            auto& item = slots[i];
            if(!item.present)
                return i;
        }
        return -1;
    }

    bool hasSpace(const ItemStack& stack) {
        return unfittableItems(stack) == 0;
    }

    int unfittableItems(const ItemStack& stack) {
        int n = stack.count;

        for(int i = 9; i <= 44 && n > 0; i++) {
            auto& item = slots[i];
            if(!item.present) {
                n -= 64;
            } else if(item.compatibleWith(stack)) {
                n -= (64 - item.count);
            }
        }

        return n > 0 ? n : 0;
    }

    ItemStack add(const ItemStack& stack) {
        int slot;
        ItemStack remaining(stack);

        while(remaining.present && (slot = findCompatibleSlot(stack)) != -1) {
            int n = std::min((int) 64 - slots[slot].count, (int) remaining.count);

            auto invStack = stack;
            invStack.setCount(slots[slot].count + n);
            remaining.setCount(remaining.count - n);
            set(slot, invStack);
        }

        if(remaining.present && (slot = findEmptySlot()) != -1) {
            set(slot, remaining);
            remaining.setCount(0);
        }

        return remaining;
    }

    void set(int slot, const ItemStack& stack, bool sendPacket = true);
};
