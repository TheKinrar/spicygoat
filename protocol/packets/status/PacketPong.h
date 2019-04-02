//
// Created by thekinrar on 31/03/19.
//

#ifndef SPICYGOAT_PACKETPONG_H
#define SPICYGOAT_PACKETPONG_H


#include "../ClientBoundPacket.h"

class PacketPong : public ClientBoundPacket {
public:
    explicit PacketPong(int64_t payload);

    std::vector<std::byte> bytes() override;

    std::string toString() const override;

private:
    int64_t payload;
};


#endif //SPICYGOAT_PACKETPONG_H
