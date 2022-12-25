//
// Created by thekinrar on 25/12/22.
//

#ifndef SPICYGOAT_PACKETENTITYHEADROTATION_H
#define SPICYGOAT_PACKETENTITYHEADROTATION_H


#include "../../ClientBoundPacket.h"

class PacketEntityHeadRotation : public ClientBoundPacket {
public:
    PacketEntityHeadRotation(int eid, float headYaw) : eid(eid), headYaw(headYaw) {}

    [[nodiscard]]
    std::vector<std::byte> bytes() override {
        std::vector<std::byte> array;
        PacketData::writeVarInt(0x3E, array);
        PacketData::writeVarInt(eid, array);
        PacketData::writeAngle(headYaw, array);
        return array;
    }

    [[nodiscard]]
    std::string toString() const override {
        return std::string("PacketEntityHeadRotation{eid=") + std::to_string(eid)
                + ",headYaw=" + std::to_string(headYaw) + "}";
    }

    int eid;
    float headYaw;
};


#endif //SPICYGOAT_PACKETENTITYHEADROTATION_H
