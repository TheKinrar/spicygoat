//
// Created by thekinrar on 30/03/19.
//

#ifndef SPICYGOAT_PACKETHANDSHAKE_H
#define SPICYGOAT_PACKETHANDSHAKE_H

#include <spicygoat/protocol/ProtocolState.h>
#include <spicygoat/protocol/ServerBoundPacket.h>

#include <string>

class PacketHandshake : public ServerBoundPacket {
   public:
    explicit PacketHandshake(PacketData& data);

    int getProtocolVersion() const;
    const std::string& getServerAddress() const;
    uint16_t getServerPort() const;
    int getNextState() const;

    std::string toString() const override;

   private:
    int protocolVersion;
    std::string serverAddress;
    uint16_t serverPort;
    ProtocolState nextState;
};

#endif  // SPICYGOAT_PACKETHANDSHAKE_H
