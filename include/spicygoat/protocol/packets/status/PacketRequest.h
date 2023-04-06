//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKETREQUEST_H
#define SPICYGOAT_PACKETREQUEST_H

#include <spicygoat/protocol/ServerBoundPacket.h>

class PacketRequest : public ServerBoundPacket {
   public:
    explicit PacketRequest(PacketData&);

    std::string toString() const override;
};

#endif  // SPICYGOAT_PACKETREQUEST_H
