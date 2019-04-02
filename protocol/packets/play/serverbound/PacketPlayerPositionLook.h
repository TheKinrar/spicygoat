//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERLOCATIONSB_H
#define SPICYGOAT_PACKETPLAYERLOCATIONSB_H


#include "../../ServerBoundPacket.h"
#include "../../../../world/Location.h"

class PacketPlayerPositionLook : public ServerBoundPacket {
public:
    explicit PacketPlayerPositionLook(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    double x, y, z;
    float yaw, pitch;
    bool onGround;
};


#endif //SPICYGOAT_PACKETPLAYERLOCATIONSB_H
