//
// Created by thekinrar on 01/04/19.
//

#include "Server.h"

#include <fstream>
#include <iostream>

#include "TCPServer.h"
#include "protocol/packets/play/clientbound/PacketDestroyEntities.h"
#include "protocol/packets/play/clientbound/PacketPlayerInfo.h"
#include "protocol/packets/play/clientbound/PacketPlayerInfoRemove.h"
#include "resources_out/resources.h"
#include "tracking/PlayerTracker.h"

Server::Server() {
    nlohmann::json j = nlohmann::json::parse(Resources::blocks());
    palette = ChunkPalette::fromJson(j);
}

void Server::loadRegistries() {
    nlohmann::json j = nlohmann::json::parse(Resources::registries());

    loadRegistry(entityRegistry, j);
    loadRegistry(itemRegistry, j);
}

void Server::loadRegistry(Registry& registry, nlohmann::json root) {
    auto j = root[registry.id];

    auto entries = j["entries"];
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        registry.addMapping(it.key(), it.value()["protocol_id"]);
    }

    auto defaultIt = j.find("default");
    if(defaultIt != j.end()) {
        registry.defaultKey = defaultIt.value();
    }
}

Server& Server::get() {
    static Server instance;
    return instance;
}

void Server::run() {
    std::thread tcpThread(&TCPServer::accept, &TCPServer::get());

    while(TCPServer::get().isRunning()) {
        auto tickStart = std::chrono::system_clock::now();
        tick();
        long tickTime =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tickStart).count();

        if(tickTime < 50000) {
            std::this_thread::sleep_for(std::chrono::microseconds(50000 - tickTime));
        }
    }

    tcpThread.join();
}

std::shared_ptr<EntityPlayer> Server::createPlayer(uuids::uuid uuid, std::string name,
                                                   std::shared_ptr<TCPConnection> conn) {
    auto player = std::make_shared<EntityPlayer>(uuid, name, conn);

    std::vector<std::shared_ptr<EntityPlayer>> array;
    array.push_back(player);
    broadcastPacket(PacketPlayerInfo(PacketPlayerInfo::Action::AddPlayer, array));

    spawnEntity(player);
    players[uuid] = player;
    playerCount++;

    auto players = getPlayers();
    conn->sendPacket(PacketPlayerInfo(PacketPlayerInfo::Action::AddPlayer, players));

    return player;
}

void Server::spawnEntity(const std::shared_ptr<Entity>& entity) {
    entities[entity->getEID()] = entity;
}

void Server::removePlayer(EntityPlayer& p) {
    p.pushData();
    p.getData().save();

    removeEntity(p);
    players.erase(p.getUuid());
    playerCount--;

    std::forward_list<uuids::uuid> array;
    array.emplace_front(p.getUuid());
    broadcastPacket(PacketPlayerInfoRemove(array));
}

void Server::removeEntity(Entity& entity) {
    entities.erase(entity.getEID());

    // TODO this should be handled by the EntityTracker
    broadcastPacket(PacketDestroyEntities(entity.getEID()));
}

int32_t Server::nextEID() {
    return next_eid++;
}

void Server::tick() {
    for(auto& e : getEntities()) {
        e->tick();
    }
}

World& Server::getWorld() {
    return world;
}

std::shared_ptr<ChunkPalette> Server::getPalette() const {
    return palette;
}

void Server::broadcastPacket(const Packet& packet) {
    for(auto& player : players) {
        player.second->getConnection().sendPacket(packet);
    }
}

unsigned long Server::getPlayerCount() const {
    return playerCount;
}

std::unique_ptr<EntityTracker> Server::createTracker(Entity& e) {
    return std::make_unique<PlayerTracker>(e);
}
