//
// Created by thekinrar on 30/03/19.
//

#include <stdexcept>
#include "PacketHandshake.h"

PacketHandshake::PacketHandshake(PacketData *data, TCPConnection* conn) {
    this->conn = conn;

    protocolVersion = data->readVarInt();
    serverAddress = data->readString();
    serverPort = data->readUnsignedShort();
    nextState = static_cast<ConnectionState>(data->readVarInt());
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

void PacketHandshake::handle() {
    if(nextState == ConnectionState::STATUS) {
        conn->setState(nextState);
    } else if(nextState == ConnectionState::LOGIN) {
        if(protocolVersion == 404) {
            conn->setState(nextState);
        } else {
            throw std::runtime_error("Protocol error: version mismatch");
        }
    } else {
        throw std::runtime_error("Protocol error: invalid state requested during handshake");
    }
}
