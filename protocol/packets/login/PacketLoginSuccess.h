//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_PACKETLOGINSUCCESS_H
#define SPICYGOAT_PACKETLOGINSUCCESS_H

#include "../ClientBoundPacket.h"

#include <boost/uuid/uuid.hpp>

class PacketLoginSuccess : public ClientBoundPacket {
public:
    PacketLoginSuccess(boost::uuids::uuid uuid, const std::string& username);

    std::vector<std::byte> bytes() override;

    [[nodiscard]] std::string toString() const override;

private:
    boost::uuids::uuid uuid{};
    std::string username;
};


#endif//SPICYGOAT_PACKETLOGINSUCCESS_H
