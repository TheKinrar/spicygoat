//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_PACKETPLUGINMESSAGECB_H
#define SPICYGOAT_PACKETPLUGINMESSAGECB_H


#include "../../ClientBoundPacket.h"

class PacketPluginMessageCB : public ClientBoundPacket {
public:
    PacketPluginMessageCB(std::string channel, std::vector<std::byte> data);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    std::string channel;
    std::vector<std::byte> data;
};


#endif//SPICYGOAT_PACKETPLUGINMESSAGECB_H
