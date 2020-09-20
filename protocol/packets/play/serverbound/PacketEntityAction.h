//
// Created by thekinrar on 04/04/19.
//

#ifndef SPICYGOAT_PACKETENTITYACTION_H
#define SPICYGOAT_PACKETENTITYACTION_H


#include "../../ServerBoundPacket.h"

class PacketEntityAction : public ServerBoundPacket {
public:
    explicit PacketEntityAction(PacketData *data);

    std::string toString() const override;

    int32_t eid;
    int8_t action;
    int8_t jumpBoost;
};


#endif//SPICYGOAT_PACKETENTITYACTION_H
