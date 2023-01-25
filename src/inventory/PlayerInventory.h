//
// Created by thekinrar on 04/01/23.
//

#pragma once

#include <utility>

#include "../entities/types/EntityPlayer.h"
#include "../item/ItemStack.h"
#include "../protocol/packets/play/serverbound/PacketClickWindow.h"

#define PLAYER_INVENTORY_SIZE 46

class PlayerInventory {
    EntityPlayer& player;

    std::vector<ItemStack> slots{PLAYER_INVENTORY_SIZE};
    ItemStack inHand;
    int selectedSlot = 36;

    int trackedVersion = 0;
    std::vector<ItemStack> trackedSlots{PLAYER_INVENTORY_SIZE};
    ItemStack trackedInHand;

    bool enableSync = true;

   public:
    explicit PlayerInventory(EntityPlayer& player) : player(player) {}

    [[nodiscard]]
    const std::vector<ItemStack>& getSlots() const {
        return slots;
    }

    [[nodiscard]]
    const ItemStack& getSlot(int slot) const {
        if(slot < 0 || slot >= PLAYER_INVENTORY_SIZE)
            throw std::runtime_error("Invalid inventory slot");

        return slots[slot];
    }

    [[nodiscard]]
    const ItemStack& getSelected() const {
        return getSlot(selectedSlot);
    }

    [[nodiscard]] int getSelectedSlot() const {
        return selectedSlot;
    }

    void setSelectedSlot(int selectedSlot) {
        if(selectedSlot < 36 || selectedSlot > 45)
            throw std::runtime_error("Invalid inventory selected slot");

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
            setSlot(slot, invStack);
        }

        if(remaining.present && (slot = findEmptySlot()) != -1) {
            setSlot(slot, remaining);
            remaining.setCount(0);
        }

        return remaining;
    }

    void setSlot(int slot, const ItemStack& stack);
    void setInHand(const ItemStack& stack);

    void setTrackedSlot(int slot, const ItemStack& stack);
    void setTrackedInHand(const ItemStack& stack);

    void setSyncEnabled(bool v) {
        enableSync = v;
    }
    void sync();
    void forceSync();

    void onClick(const PacketClickWindow &packet);
};
