//
// Created by thekinrar on 18/09/2020.
//

#ifndef SPICYGOAT_PACKETCHATMESSAGECB_H
#define SPICYGOAT_PACKETCHATMESSAGECB_H

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketChatMessageCB : public ClientBoundPacket {
   public:
    explicit PacketChatMessageCB(const std::string &message);

    std::vector<std::byte> bytes() const override;

    std::string toString() const override;

   private:
    const std::string message;
};

#endif  // SPICYGOAT_PACKETCHATMESSAGECB_H
