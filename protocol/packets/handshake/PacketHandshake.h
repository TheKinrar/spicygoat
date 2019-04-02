//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKETHANDSHAKE_H
#define SPICYGOAT_PACKETHANDSHAKE_H

#include "../../ConnectionState.h"
#include "../ServerBoundPacket.h"

#include <string>

class PacketHandshake : public ServerBoundPacket {
public:
    explicit PacketHandshake(PacketData* data, TCPConnection* conn);

    void handle() override;

    int getProtocolVersion() const;
    const std::string &getServerAddress() const;
    uint16_t getServerPort() const;
    int getNextState() const;

    std::string toString() const override;

private:
    TCPConnection* conn;

    int protocolVersion;
    std::string serverAddress;
    uint16_t serverPort;
    ConnectionState nextState;
};


#endif //SPICYGOAT_PACKETHANDSHAKE_H
