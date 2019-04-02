//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETPLAYERLOCATIONSB_H
#define SPICYGOAT_PACKETPLAYERLOCATIONSB_H


#include "../../ServerBoundPacket.h"
#include "../../../../world/Location.h"

class PacketPlayerLocationSB : public ServerBoundPacket {
public:
    explicit PacketPlayerLocationSB(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    Location location = Location(0, 0, 0, 0, 0);
    bool onGround;
};


#endif //SPICYGOAT_PACKETPLAYERLOCATIONSB_H
