//
// Created by thekinrar on 03/01/23.
//

#ifndef SPICYGOAT_PACKETSETCREATIVESLOT_H
#define SPICYGOAT_PACKETSETCREATIVESLOT_H

#include "../../../../item/ItemStack.h"
#include "../../ServerBoundPacket.h"

class PacketSetCreativeSlot : public ServerBoundPacket {
   public:
    int16_t slot;
    ItemStack stack;

    explicit PacketSetCreativeSlot(PacketData& data)
        : ServerBoundPacket(Packets::S_SET_CREATIVE_SLOT), slot(data.readShort()), stack(data.readItemStack()) {}

    [[nodiscard]] std::string toString() const override {
        return std::string("PacketSetCreativeSlot{slot=") + std::to_string(slot) + "}";
    }
};

#endif  // SPICYGOAT_PACKETSETCREATIVESLOT_H
