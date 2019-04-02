//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKETREQUEST_H
#define SPICYGOAT_PACKETREQUEST_H

#include "../Packet.h"
#include "../ServerBoundPacket.h"

class PacketRequest : public ServerBoundPacket {
public:
    explicit PacketRequest(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;
};


#endif //SPICYGOAT_PACKETREQUEST_H
