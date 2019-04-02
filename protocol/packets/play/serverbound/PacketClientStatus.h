//
// Created by thekinrar on 02/04/19.
//

#ifndef SPICYGOAT_PACKETCLIENTSTATUS_H
#define SPICYGOAT_PACKETCLIENTSTATUS_H


#include "../../ServerBoundPacket.h"

class PacketClientStatus : public ServerBoundPacket {
public:
    explicit PacketClientStatus(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    int action;
};


#endif //SPICYGOAT_PACKETCLIENTSTATUS_H
