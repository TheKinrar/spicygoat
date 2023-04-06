//
// Created by nicolas on 1/9/23.
//

#include <spicygoat/entities/types/EntityPlayer.h>
#include <spicygoat/inventory/PlayerInventory.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketSetInventoryContent.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketSetInventorySlot.h>
#include <spicygoat/util/except.h>

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
                                inHand.setCount(newCount - 64);
                                newCount = 64;
                            } else {
                                setInHand({});
                            }
                            currentStack.setCount(newCount);
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
                                        currentStack.setCount(currentStack.count + 1);
                                        setSlot(packet.slot, currentStack);
                                        inHand.setCount(inHand.count - 1);
                                    }
                                } else {
                                    setSlot(packet.slot, inHand);
                                    setInHand(currentStack);
                                }
                            } else {
                                currentStack = inHand;
                                currentStack.setCount(1);
                                setSlot(packet.slot, currentStack);
                                inHand.setCount(inHand.count - 1);
                            }
                        } else if(currentStack.present) {
                            int slotCount = currentStack.count / 2;
                            int handCount = (currentStack.count + 1) / 2;
                            currentStack.setCount(slotCount);
                            setSlot(packet.slot, currentStack);
                            currentStack.setCount(handCount);
                            setInHand(currentStack);
                        }
                        break;
                    }
                    default:
                        throw protocol_error("Invalid click button");
                }
                break;
            case PacketClickWindow::Mode::ShiftSwap: {
                auto currentStack = getSlot(packet.slot);
                if(packet.slot >= PLAYER_INV_MAIN_BEGIN && packet.slot < PLAYER_INV_HOTBAR_BEGIN) {
                    setSlot(packet.slot, add(currentStack, PLAYER_INV_HOTBAR_BEGIN, PLAYER_INV_MAIN_END));
                } else if(packet.slot >= PLAYER_INV_HOTBAR_BEGIN && packet.slot <= PLAYER_INV_MAIN_END) {
                    setSlot(packet.slot, add(currentStack, PLAYER_INV_MAIN_BEGIN, PLAYER_INV_HOTBAR_BEGIN - 1));
                } else {
                    setSlot(packet.slot, add(currentStack, PLAYER_INV_MAIN_BEGIN, PLAYER_INV_MAIN_END));
                }
                break;
            }
            case PacketClickWindow::Mode::KeySwap: {
                auto currentStack = getSlot(packet.slot);
                int target = packet.button == PacketClickWindow::OffhandKey ? PLAYER_INV_OFFHAND
                                                                            : packet.button + PLAYER_INV_HOTBAR_BEGIN;
                setSlot(packet.slot, getSlot(target));
                setSlot(target, currentStack);
                break;
            }
                //        case PacketClickWindow::Mode::Drag:
                //            break;
            case PacketClickWindow::Mode::Double:
                if(inHand.present) {
                    while(inHand.count < 64) {
                        int slot = findCompatibleSlot(inHand);
                        if(slot == -1) break;
                        auto other = getSlot(slot);
                        int n = std::min(64 - inHand.count, (int) other.count);
                        other.setCount(other.count - n);
                        setSlot(slot, other);
                        inHand.setCount(inHand.count + n);
                    }
                }
                break;
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
