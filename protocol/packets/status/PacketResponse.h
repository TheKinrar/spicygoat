//
// Created by thekinrar on 31/03/19.
//

#ifndef SPICYGOAT_PACKETRESPONSE_H
#define SPICYGOAT_PACKETRESPONSE_H

#include "../Packet.h"
#include "../ClientBoundPacket.h"

#include <vector>

class PacketResponse : public ClientBoundPacket {
public:
    std::vector<std::byte> bytes() override;

    std::string toString() const override;
};


#endif //SPICYGOAT_PACKETRESPONSE_H
