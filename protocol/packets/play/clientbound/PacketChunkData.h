//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETCHUNKDATA_H
#define SPICYGOAT_PACKETCHUNKDATA_H


#include "../../ClientBoundPacket.h"

class PacketChunkData : public ClientBoundPacket {
    PacketLoginSuccess(uuid_t uuid, std::string &username);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;
};


#endif //SPICYGOAT_PACKETCHUNKDATA_H
