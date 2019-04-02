//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_PACKETLOGINSUCCESS_H
#define SPICYGOAT_PACKETLOGINSUCCESS_H

#include "../ClientBoundPacket.h"

#include <uuid/uuid.h>

class PacketLoginSuccess : public ClientBoundPacket {
public:
    PacketLoginSuccess(uuid_t uuid, std::string &username);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    char uuid[37];
    std::string username;
};


#endif //SPICYGOAT_PACKETLOGINSUCCESS_H
