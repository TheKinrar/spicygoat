//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLUGINMESSAGESB_H
#define SPICYGOAT_PACKETPLUGINMESSAGESB_H


#include "../../ServerBoundPacket.h"

class PacketPluginMessageSB : public ServerBoundPacket {
public:
    explicit PacketPluginMessageSB(PacketData& data);

    std::string toString() const override;

    std::string channel;
    std::vector<std::byte> data;
};


#endif //SPICYGOAT_PACKETPLUGINMESSAGESB_H
