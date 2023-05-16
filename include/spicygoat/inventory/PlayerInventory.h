//
// Created by thekinrar on 04/01/23.
//

#pragma once

#include <utility>

class EntityPlayer;

#include <spicygoat/item/ItemStack.h>
#include <spicygoat/protocol/packets/play/serverbound/PacketClickWindow.h>

#define PLAYER_INV_SIZE 46
#define PLAYER_INV_CRAFT_OUT 0
#define PLAYER_INV_CRAFT_BEGIN 1
#define PLAYER_INV_CRAFT_END 4
#define PLAYER_INV_HELMET 5
#define PLAYER_INV_CHESTPLATE 6
#define PLAYER_INV_LEGGINGS 7
#define PLAYER_INV_BOOTS 8
#define PLAYER_INV_MAIN_BEGIN 9
#define PLAYER_INV_HOTBAR_BEGIN 36
#define PLAYER_INV_MAIN_END 44
#define PLAYER_INV_OFFHAND 45

class PlayerInventory {
    EntityPlayer& player;

    std::vector<ItemStack> slots{PLAYER_INV_SIZE};
    ItemStack inHand;
    int selectedSlot = 36;

    int trackedVersion = 0;
    std::vector<ItemStack> trackedSlots{PLAYER_INV_SIZE};
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
        if(slot < 0 || slot >= PLAYER_INV_SIZE) throw std::runtime_error("Invalid inventory slot");

        return slots[slot];
    }

    [[nodiscard]]
    const ItemStack& getSelected() const {
        return getSlot(selectedSlot);
    }

    [[nodiscard]]
    int getSelectedSlot() const {
        return selectedSlot;
    }

    void setSelectedSlot(int selectedSlot) {
        if(selectedSlot < 36 || selectedSlot > 45) throw std::runtime_error("Invalid inventory selected slot");

        this->selectedSlot = selectedSlot;
    }

    /**
     * Looks for a compatible slot in this inventory.
     * @param stack the stack to check compatibility with
     * @param begin Lower bound, inclusive
     * @param end Upper bound, inclusive
     * @return slot number if found, else -1
     */
    int findCompatibleSlot(const ItemStack& stack, int begin = PLAYER_INV_MAIN_BEGIN, int end = PLAYER_INV_MAIN_END) {
        for(int i = begin; i <= end; i++) {
            auto& item = slots[i];
            if(item.compatibleWith(stack) && item.count < 64) return i;
        }
        return -1;
    }

    /**
     * Looks for a compatible slot in the main section of this inventory, with a priority on the hotbar.
     * @param stack the stack to check compatibility with
     * @return slot number if found, else -1
     */
    int findCompatibleMainSlot(const ItemStack& stack) {
        int r = findCompatibleSlot(stack, PLAYER_INV_HOTBAR_BEGIN);
        if(r != -1)
            return r;
        else
            return findCompatibleSlot(stack, PLAYER_INV_MAIN_BEGIN, PLAYER_INV_HOTBAR_BEGIN - 1);
    }

    /**
     * Looks for an empty slot in this inventory.
     * @param begin Lower bound, inclusive
     * @param end Upper bound, inclusive
     * @return slot number if found, else -1
     */
    int findEmptySlot(int begin = PLAYER_INV_MAIN_BEGIN, int end = PLAYER_INV_MAIN_END) {
        for(int i = begin; i <= end; i++) {
            auto& item = slots[i];
            if(!item.present) return i;
        }
        return -1;
    }

    /**
     * Looks for an empty slot in the main section of this inventory, with a priority on the hotbar.
     * @return slot number if found, else -1
     */
    int findEmptyMainSlot() {
        int r = findEmptySlot(PLAYER_INV_HOTBAR_BEGIN);
        if(r != -1)
            return r;
        else
            return findEmptySlot(PLAYER_INV_MAIN_BEGIN, PLAYER_INV_HOTBAR_BEGIN - 1);
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
        auto remaining = stack;

        while(remaining.present && (slot = findCompatibleMainSlot(stack)) != -1) {
            int n = std::min((int)64 - slots[slot].count, (int)remaining.count);

            auto invStack = stack;
            invStack.setCount(slots[slot].count + n);
            remaining.setCount(remaining.count - n);
            setSlot(slot, invStack);
        }

        if(remaining.present && (slot = findEmptyMainSlot()) != -1) {
            setSlot(slot, remaining);
            remaining.setCount(0);
        }

        return remaining;
    }

    ItemStack add(const ItemStack& stack, int begin, int end) {
        int slot;
        auto remaining = stack;

        while(remaining.present && (slot = findCompatibleSlot(stack, begin, end)) != -1) {
            int n = std::min((int)64 - slots[slot].count, (int)remaining.count);

            auto invStack = stack;
            invStack.setCount(slots[slot].count + n);
            remaining.setCount(remaining.count - n);
            setSlot(slot, invStack);
        }

        if(remaining.present && (slot = findEmptySlot(begin, end)) != -1) {
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

    void onClick(const PacketClickWindow& packet);
};
