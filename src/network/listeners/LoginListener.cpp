//
// Created by thekinrar on 18/09/2020.
//

#include "LoginListener.h"

#include <uuid.h>

#include <iostream>
#include <utility>

#include <spicygoat/Server.h>
#include <spicygoat/data/tags.h>
#include <spicygoat/protocol/packets/login/PacketPluginRequest.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketRenderCenter.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketSetInventoryContent.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketUpdateTags.h>
#include <spicygoat/tags/Tag.h>
#include <spicygoat/util/md5.h>

#include "../../protocol/channels/minecraft/CMBrand.h"
#include "PlayerConnection.h"

LoginListener::LoginListener(std::shared_ptr<TCPConnection> connection) : connection(std::move(connection)) {}

void LoginListener::onLoginStart(const PacketLoginStart &packet) {
    std::string uuidName = "OfflinePlayer:" + packet.name;
    MD5 hasher;
    hasher.add(uuidName.data(), uuidName.size());
    std::array<uuids::uuid::value_type, 16> bin{};
    hasher.getHash(bin.data());

    bin[6]  &= 0x0f;  /* clear version        */
    bin[6]  |= 0x30;  /* set to version 3     */
    bin[8]  &= 0x3f;  /* clear variant        */
    bin[8]  |= 0x80;  /* set to IETF variant  */

    connection->username = packet.name;
    connection->uuid = {bin};

    // Velocity
    std::vector<std::byte> request;
    PacketData::writeByte(4, request);  // Velocity protocol version (MODERN_LAZY_SESSION)
    connection->sendPacket(PacketPluginRequest(42, "velocity:player_info", request));
}

void LoginListener::onPluginResponse(const PacketPluginResponse &response) {
    if(response.id != 42) throw std::runtime_error("Unexpected plugin response");

    if(response.successful) {
        connection->getLogger().info("Proxy detected");

        PacketData data = response.data;

        std::vector<std::byte> signature;
        data.readByteArray(signature, 32);
        // TODO verify signature

        int protocolVersion = data.readVarInt();
        if(protocolVersion != 4) throw std::runtime_error("Unsupported Velocity protocol version");

        std::string address = data.readString();
        connection->getLogger().info("Forwarded address: " + address);

        connection->uuid = data.readUuid();
        connection->username = data.readString();

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
    }

    connection->getLogger().info("Logged in as {}", connection->username);

    connection->sendPacket(PacketLoginSuccess(connection->uuid, connection->username));
    connection->setState(ProtocolState::PLAY);

    auto player = Server::get().createPlayer(connection->uuid, connection->username, connection);
    connection->setPlayer(player);

    auto spawnPos = Server::get().getWorld().getSpawnPosition();
    auto loc = player->getLocation();

    connection->sendPacket(PacketJoinGame(player));
    CMBrand(std::string("SpicyGoat")).send(*connection);
    connection->sendPacket(PacketServerDifficulty(0));  // TODO difficulty
    connection->sendPacket(PacketSpawnPosition(spawnPos));
    player->sendAbilities();
    connection->sendPacket(PacketRenderCenter(loc.getChunkX(), loc.getChunkZ()));

    player->getInventory().forceSync();

    std::map<std::string, std::vector<std::reference_wrapper<Tag>>> tags;
    tags.emplace("minecraft:block", Tags::blocks::All);
    tags.emplace("minecraft:entity_type", Tags::entity_types::All);
    tags.emplace("minecraft:fluid", Tags::fluids::All);
    tags.emplace("minecraft:game_event", Tags::game_events::All);
    tags.emplace("minecraft:item", Tags::items::All);
    connection->sendPacket(PacketUpdateTags(tags));

    connection->setListener(std::make_unique<PlayerConnection>(*connection, player));
}
