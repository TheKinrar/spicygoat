//
// Created by thekinrar on 18/09/2020.
//

#include "HandshakeListener.h"

#include <spicygoat/Server.h>

#include "LoginListener.h"
#include "StatusListener.h"

void HandshakeListener::onHandshake(const PacketHandshake &packet) {
    if(packet.getNextState() == ProtocolState::STATUS) {
        connection->setState(ProtocolState::STATUS);
        connection->setListener(std::make_unique<StatusListener>(*connection));
    } else if(packet.getNextState() == ProtocolState::LOGIN) {
        if(packet.getProtocolVersion() == Server::get().getProtocolVersionNumber()) {
            connection->setState(ProtocolState::LOGIN);
            connection->setListener(std::make_unique<LoginListener>(connection));
        } else {
            throw std::runtime_error("Protocol error: version mismatch");
        }
    } else {
        throw std::runtime_error("Protocol error: invalid state requested during handshake");
    }
}

HandshakeListener::HandshakeListener(std::shared_ptr<TCPConnection> connection) : connection(std::move(connection)) {}
