//
// Created by thekinrar on 18/09/2020.
//

#include <libstud/uuid.hxx>
#include <iostream>
#include <utility>

#include "LoginListener.h"
#include "../../Server.h"
#include "../../protocol/channels/minecraft/CMBrand.h"
#include "PlayerConnection.h"
#include "../../protocol/packets/login/PacketPluginRequest.h"

LoginListener::LoginListener(std::shared_ptr<TCPConnection> connection) : connection(std::move(connection)) {}

void LoginListener::onLoginStart(const PacketLoginStart &packet) {
    connection->username = packet.name;
    connection->uuid = stud::uuid::generate(false); // TODO generate offline UUID like official server does

    // Velocity
    std::vector<std::byte> request;
    PacketData::writeByte(4, request); // Velocity protocol version (MODERN_LAZY_SESSION)
    connection->sendPacket(PacketPluginRequest(42, "velocity:player_info", request));
}

void LoginListener::onPluginResponse(const PacketPluginResponse &response) {
    if(response.id != 42)
        throw std::runtime_error("Unexpected plugin response");

    if(response.successful) {
        std::cout << connection->getName() << " is a proxy" << std::endl;

        PacketData data = response.data;

        std::vector<std::byte> signature;
        data.readByteArray(signature, 32);
        // TODO verify signature

        int protocolVersion = data.readVarInt();
        if(protocolVersion != 4)
            throw std::runtime_error("Unsupported Velocity protocol version");

        std::string address = data.readString();
        std::cout << connection->getName() << " proxies " << address << std::endl;

        connection->uuid = data.readUuid();
        std::string proxiedUsername = data.readString();

        std::cout << connection->username << " vs " << proxiedUsername << std::endl;
        connection->username = proxiedUsername;

        // Properties!
        int propertyCount = data.readVarInt();
        for(int i = 0; i < propertyCount; ++i) {
            std::string key = data.readString();
            std::string value = data.readString();
            bool hasSignature = data.readBoolean();
            if(hasSignature) {
                std::string signature = data.readString();
            }
        }

        std::cout << "remaining: " << data.remaining() << std::endl;
    }

    connection->sendPacket(PacketLoginSuccess(connection->uuid, connection->username));
    connection->setState(ProtocolState::PLAY);

    auto player = Server::get().createPlayer(connection->uuid, connection->username, connection);
    connection->setPlayer(player);

    auto pos = Server::get().getWorld().getSpawnPosition();
    connection->sendPacket(PacketJoinGame(player));
    CMBrand(std::string("SpicyGoat")).send(*connection);
    connection->sendPacket(PacketServerDifficulty(0)); // TODO difficulty
    connection->sendPacket(PacketSpawnPosition(pos));
    connection->sendPacket(PacketPlayerAbilities(false, false, true, false, 0.05, 0.1)); // TODO player abilities
    connection->sendPacket(PacketPlayerLocationCB(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0))); // TODO player location
    connection->getPlayer()->setNextLocation(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0));

    connection->setListener(std::make_unique<PlayerConnection>(*connection, *player));
}
