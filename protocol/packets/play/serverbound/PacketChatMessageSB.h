//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETCHATMESSAGESB_H
#define SPICYGOAT_PACKETCHATMESSAGESB_H

#include "../../ServerBoundPacket.h"

class PacketChatMessageSB : public ServerBoundPacket {
   public:
    explicit PacketChatMessageSB(PacketData& data);

    std::string toString() const override;

    std::string message;
    long timestamp;
    long salt;
    bool hasSignature;
    std::vector<std::byte> signature;
    int count;
    int ackOffset;
    std::bitset<20> ack;
};

#endif  // SPICYGOAT_PACKETCHATMESSAGESB_H
