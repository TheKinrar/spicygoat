//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETCLIENTSTATUS_H
#define SPICYGOAT_PACKETCLIENTSTATUS_H

#include <spicygoat/protocol/ServerBoundPacket.h>

class PacketClientStatus : public ServerBoundPacket {
   public:
    explicit PacketClientStatus(PacketData& data);

    std::string toString() const override;

    int action;
};

#endif  // SPICYGOAT_PACKETCLIENTSTATUS_H
