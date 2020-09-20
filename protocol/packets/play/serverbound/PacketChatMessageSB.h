//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETCHATMESSAGESB_H
#define SPICYGOAT_PACKETCHATMESSAGESB_H


#include "../../ServerBoundPacket.h"

class PacketChatMessageSB : public ServerBoundPacket {
public:
    explicit PacketChatMessageSB(PacketData *data);

    std::string toString() const override;

    std::string message;
};


#endif//SPICYGOAT_PACKETCHATMESSAGESB_H
