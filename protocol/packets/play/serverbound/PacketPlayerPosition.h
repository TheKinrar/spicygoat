//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERPOSITION_H
#define SPICYGOAT_PACKETPLAYERPOSITION_H


#include "../../ServerBoundPacket.h"

class PacketPlayerPosition : public ServerBoundPacket {
public:
    explicit PacketPlayerPosition(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    double x, y, z;
    bool onGround;
};


#endif //SPICYGOAT_PACKETPLAYERPOSITION_H
