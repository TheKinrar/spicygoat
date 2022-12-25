//
// Created by thekinrar on 18/09/2020.
//

#include <uuid/uuid.h>
#include <iostream>

#include "LoginListener.h"
#include "../../Server.h"
#include "../../protocol/channels/minecraft/CMBrand.h"
#include "PlayerConnection.h"
#include "../../protocol/packets/login/PacketPluginRequest.h"

LoginListener::LoginListener(TCPConnection &connection) : connection(connection) {}

void LoginListener::onLoginStart(const PacketLoginStart &packet) {
    connection.username = packet.name;
    uuid_generate(connection.uuid); // TODO generate offline UUID like official server does

    // Velocity
    std::vector<std::byte> request;
    PacketData::writeByte(4, request); // Velocity protocol version (MODERN_LAZY_SESSION)
    connection.sendPacket(new PacketPluginRequest(42, "velocity:player_info", request));
}

void LoginListener::onPluginResponse(const PacketPluginResponse &response) {
    if(response.id != 42)
        throw std::runtime_error("Unexpected plugin response");

    if(response.successful) {
        std::cout << connection.getName() << " is a proxy" << std::endl;

        PacketData data(reinterpret_cast<char *>(const_cast<std::byte *>(response.data.data())), response.data.size()); // TODO oskour

        std::vector<std::byte> signature;
        data.readByteArray(signature, 32);
        // TODO verify signature

        int protocolVersion = data.readVarInt();
        if(protocolVersion != 4)
            throw std::runtime_error("Unsupported Velocity protocol version");

        std::string address = data.readString();
        std::cout << connection.getName() << " proxies " << address << std::endl;

        data.readUuid(connection.uuid);
        std::string proxiedUsername = data.readString();

        std::cout << connection.username << " vs " << proxiedUsername << std::endl;
        connection.username = proxiedUsername;

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

    connection.sendPacket(new PacketLoginSuccess(connection.uuid, connection.username));
    connection.setState(ProtocolState::PLAY);

    EntityPlayer *player = Server::get()->createPlayer(connection.uuid, connection.username, connection);
    connection.setPlayer(player);

    auto pos = Server::get()->getWorld().getSpawnPosition();
    connection.sendPacket(new PacketJoinGame(player));
    CMBrand(std::string("SpicyGoat")).send(connection);
    connection.sendPacket(new PacketServerDifficulty(0)); // TODO difficulty
    connection.sendPacket(new PacketSpawnPosition(pos));
    connection.sendPacket(new PacketPlayerAbilities(false, false, true, false, 0.05, 0.1)); // TODO player abilities
    connection.sendPacket(new PacketPlayerLocationCB(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0))); // TODO player location
    connection.getPlayer()->setNextLocation(Location(pos.getX(), pos.getY(), pos.getZ(), 0, 0));

    connection.setListener(std::make_unique<PlayerConnection>(connection, *player));
}
