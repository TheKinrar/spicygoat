//
// Created by thekinrar on 31/03/19.
//

#ifndef SPICYGOAT_PACKETRESPONSE_H
#define SPICYGOAT_PACKETRESPONSE_H

#include <spicygoat/protocol/ClientBoundPacket.h>

#include <vector>

class PacketResponse : public ClientBoundPacket {
   public:
    explicit PacketResponse();
    std::vector<std::byte> bytes() const override;

    std::string toString() const override;
};

#endif  // SPICYGOAT_PACKETRESPONSE_H
