//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_PACKETLOGINSUCCESS_H
#define SPICYGOAT_PACKETLOGINSUCCESS_H

#include <spicygoat/protocol/ClientBoundPacket.h>

class PacketLoginSuccess : public ClientBoundPacket {
   public:
    PacketLoginSuccess(uuids::uuid uuid, const std::string &username);

    std::vector<std::byte> bytes() const override;

    [[nodiscard]]
    std::string toString() const override;

   private:
    uuids::uuid uuid;
    std::string username;
};

#endif  // SPICYGOAT_PACKETLOGINSUCCESS_H
