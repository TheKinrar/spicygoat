//
// Created by thekinrar on 31/03/19.
//

#ifndef SPICYGOAT_PACKETLOGINSTART_H
#define SPICYGOAT_PACKETLOGINSTART_H


#include "../ServerBoundPacket.h"

class PacketLoginStart : public ServerBoundPacket {
public:
    explicit PacketLoginStart(PacketData* data, TCPConnection* conn);

    void handle() override;

    std::string toString() const override;

private:
    TCPConnection* conn;

    std::string name;
};


#endif //SPICYGOAT_PACKETLOGINSTART_H
