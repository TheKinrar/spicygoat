//
// Created by nicolas on 1/9/23.
//

#include "PlayerInventory.h"

#include "../protocol/packets/play/clientbound/PacketSetInventoryContent.h"
#include "../protocol/packets/play/clientbound/PacketSetInventorySlot.h"
#include "../util/except.h"

void PlayerInventory::setSlot(int slot, const ItemStack& stack) {
    if(slot < 0 || slot >= PLAYER_INV_SIZE)
        throw std::runtime_error("Invalid inventory slot");

    slots[slot] = stack;
    if(enableSync) sync();
}

void PlayerInventory::setInHand(const ItemStack& stack) {
    inHand = stack;
    if(enableSync) sync();
}

void PlayerInventory::setTrackedSlot(int slot, const ItemStack& stack) {
    if(slot < 0 || slot >= PLAYER_INV_SIZE)
        throw std::runtime_error("Invalid inventory slot");

    trackedSlots[slot] = stack;
}

void PlayerInventory::setTrackedInHand(const ItemStack& stack) {
    trackedInHand = stack;
}

void PlayerInventory::onClick(const PacketClickWindow& packet) {
    enableSync = false;

    if(packet.slot > PLAYER_INV_CRAFT_END) {
        switch(packet.mode) {
            case PacketClickWindow::Mode::Normal:
                switch(packet.button) {
                    case PacketClickWindow::LeftClick: {
                        auto currentStack = getSlot(packet.slot);
                        if(currentStack.compatibleWith(inHand)) {
                            int newCount = currentStack.count + inHand.count;
                            if(newCount > 64) {
                                inHand.count = newCount - 64;
                                newCount = 64;
                            } else {
                                setInHand({});
                            }
                            currentStack.count = newCount;
                            setSlot(packet.slot, currentStack);
                        } else {
                            setSlot(packet.slot, inHand);
                            setInHand(currentStack);
                        }
                        break;
                    }
                    case PacketClickWindow::RightClick: {
                        auto currentStack = getSlot(packet.slot);
                        if(inHand.present) {
                            if(currentStack.present) {
                                if(currentStack.compatibleWith(inHand)) {
                                    if(currentStack.count < 64) {
                                        currentStack.count++;
                                        setSlot(packet.slot, currentStack);
                                        inHand.count--;
                                    }
                                } else {
                                    setSlot(packet.slot, inHand);
                                    setInHand(currentStack);
                                }
                            } else {
                                currentStack = inHand;
                                currentStack.count = 1;
                                setSlot(packet.slot, currentStack);
                                inHand.count--;
                            }
                        } else if(currentStack.present) {
                            int slotCount = currentStack.count / 2;
                            int handCount = (currentStack.count + 1) / 2;
                            currentStack.count = slotCount;
                            setSlot(packet.slot, currentStack);
                            currentStack.count = handCount;
                            setInHand(currentStack);
                        }
                        break;
                    }
                    default:
                        throw protocol_error("Invalid click button");
                }
                break;
                //        case PacketClickWindow::Mode::ShiftSwap:
                //            break;
                //        case PacketClickWindow::Mode::KeySwap:
                //            break;
                //        case PacketClickWindow::Mode::Middle:
                //            break;
                //        case PacketClickWindow::Mode::Drop:
                //            break;
                //        case PacketClickWindow::Mode::Drag:
                //            break;
                //        case PacketClickWindow::Mode::Double:
                //            break;
            default:
                throw protocol_error("Invalid click mode");
        }
    }

    enableSync = true;

    if(packet.stateId == trackedVersion) {
        for(const auto& item : packet.stacks) {
            setTrackedSlot(item.first, item.second);
        }
        setTrackedInHand(packet.inHand);

        sync();
    } else {
        forceSync();
    }
}

void PlayerInventory::sync() {
    for(int i = 0; i < PLAYER_INV_SIZE; ++i) {
        if(trackedSlots[i] != slots[i]) {
            trackedSlots[i] = slots[i];
            player.getConnection().sendPacket(PacketSetInventorySlot(0, ++trackedVersion, i, slots[i]));
        }
    }

    if(trackedInHand != inHand) {
        trackedInHand = inHand;
        player.getConnection().sendPacket(PacketSetInventorySlot(-1, ++trackedVersion, -1, inHand));
    }
}

void PlayerInventory::forceSync() {
    trackedSlots = slots;
    trackedInHand = inHand;
    player.getConnection().sendPacket(PacketSetInventoryContent(0, ++trackedVersion, slots, inHand));
}
