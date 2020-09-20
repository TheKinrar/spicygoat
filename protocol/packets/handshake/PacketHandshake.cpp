//
// Created by thekinrar on 30/03/19.
//

#include <stdexcept>
#include "PacketHandshake.h"
#include "../../../Server.h"

PacketHandshake::PacketHandshake(PacketData *data) : ServerBoundPacket(Packets::S_HANDSHAKE) {
    protocolVersion = data->readVarInt();
    serverAddress = data->readString();
    serverPort = data->readUnsignedShort();
    nextState = static_cast<ProtocolState>(data->readVarInt());
}

int PacketHandshake::getProtocolVersion() const {
    return protocolVersion;
}

const std::string &PacketHandshake::getServerAddress() const {
    return serverAddress;
}

uint16_t PacketHandshake::getServerPort() const {
    return serverPort;
}

int PacketHandshake::getNextState() const {
    return nextState;
}

std::string PacketHandshake::toString() const {
    return std::string("PacketHandshake{version=") + std::to_string(protocolVersion)
           + ",address=" + serverAddress
           + ",port=" + std::to_string(serverPort)
           + ",state=" + std::to_string(nextState) + "}";
}
