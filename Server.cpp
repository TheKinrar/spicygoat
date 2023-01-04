//
// Created by thekinrar on 01/04/19.
//

#include <fstream>
#include <iostream>
#include "Server.h"
#include "protocol/packets/play/clientbound/PacketPlayerInfo.h"
#include "TCPServer.h"
#include "tracking/PlayerTracker.h"
#include "protocol/packets/play/clientbound/PacketPlayerInfoRemove.h"
#include "protocol/packets/play/clientbound/PacketDestroyEntities.h"

Server::Server() {
    std::ifstream ifs("blocks.json");
    nlohmann::json j;
    ifs >> j;
    palette = ChunkPalette::fromJson(j);
    ifs.close();

    std::ifstream ifsc("codec.dat", std::ios::binary);
    ifsc.unsetf(std::ios::skipws);
    ifsc.seekg(0, std::ios::end);
    size_t len = ifsc.tellg();
    ifsc.seekg(0, std::ios::beg);
    std::vector<unsigned char> vec;
    vec.reserve(len);
    vec.insert(vec.begin(),
                 std::istream_iterator<unsigned char>(ifsc), std::istream_iterator<unsigned char>());
    codec.reserve(len);
    for(unsigned char& c : vec) codec.push_back(static_cast<std::byte>(c));

    loadRegistries();
}

void Server::loadRegistries() {
    std::ifstream ifs("registries.json");
    nlohmann::json j;
    ifs >> j;
    ifs.close();

    loadRegistry(itemRegistry, j);
}

void Server::loadRegistry(Registry& registry, nlohmann::json root) {
    auto j = root[registry.id];

    auto entries = j["entries"];
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        registry.entries[it.key()] = it.value()["protocol_id"];
        registry.entriesR[it.value()["protocol_id"]] = it.key();
    }

    auto defaultIt = j.find("default");
    if(defaultIt != j.end()) {
        registry.defaultEntry = defaultIt.value();
    }
}

Server* Server::get() {
    static auto instance = new Server();
    return instance;
}

void Server::run() {
    std::thread tcpThread(&TCPServer::accept, &TCPServer::get());

    while(TCPServer::get().isRunning()) {
        auto tickStart = std::chrono::system_clock::now();
        tick();
        long tickTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - tickStart).count();

        if(tickTime < 50000) {
            std::this_thread::sleep_for(std::chrono::microseconds(50000 - tickTime));
        }
    }

    tcpThread.join();
}

EntityPlayer* Server::createPlayer(stud::uuid uuid, std::string name, TCPConnection &conn) {
    auto player = new EntityPlayer(uuid, name, conn);

    std::forward_list<EntityPlayer*> array;
    array.push_front(player);
    auto packetForAll = new PacketPlayerInfo(PacketPlayerInfo::Action::AddPlayer, array);
    broadcastPacket(packetForAll);
    delete(packetForAll);

    entities.push_front(player);
    players.push_front(player);
    playerCount++;

    auto packetForOne = new PacketPlayerInfo(PacketPlayerInfo::Action::AddPlayer, players);
    conn.sendPacket(packetForOne);
    delete(packetForOne);

    return player;
}

void Server::removePlayer(EntityPlayer &p) {
    entities.remove(&p);
    players.remove(&p);
    playerCount--;

    std::forward_list<stud::uuid> array;
    array.emplace_front(p.getUuid());
    auto packetForAll = new PacketPlayerInfoRemove(array);
    broadcastPacket(packetForAll);
    delete(packetForAll);

    // TODO this should be handled by the EntityTracker
    broadcastPacket(new PacketDestroyEntities(p.getEID()));
}

const std::forward_list<Entity *> &Server::getEntities() const {
    return entities;
}

const std::forward_list<EntityPlayer *> &Server::getPlayers() const {
    return players;
}

int32_t Server::nextEID() {
    return next_eid++;
}

void Server::tick() {
    for(auto p : players) {
        p->tick();
    }
}

World& Server::getWorld() {
    return world;
}

std::shared_ptr<ChunkPalette> Server::getPalette() const {
    return palette;
}

void Server::broadcastPacket(Packet *packet) {
    for(auto &player : players) {
        player->getConnection().sendPacket(packet);
    }
}

unsigned long Server::getPlayerCount() const {
    return playerCount;
}

const std::vector<std::byte> &Server::getCodec() const {
    return codec;
}

std::unique_ptr<EntityTracker> Server::createTracker(Entity& e) {
    return std::make_unique<PlayerTracker>(e);
}

