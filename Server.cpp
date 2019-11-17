//
// Created by thekinrar on 01/04/19.
//

#include <fstream>
#include <iostream>
#include "Server.h"
#include "protocol/packets/play/clientbound/PacketPlayerInfo.h"

Server::Server() {
    std::ifstream ifs("/home/thekinrar/temparia/generated/1.14/reports/blocks.json");
    nlohmann::json j;
    ifs >> j;
    palette = ChunkPalette::fromJson(j);
    ifs.close();


    //std::cout << palette->toString(true) << std::endl; TODO
}

Server* Server::get() {
    static auto instance = new Server();
    return instance;
}

EntityPlayer* Server::createPlayer(uuid_t &uuid, std::string name, TCPConnection &conn) {
    auto player = new EntityPlayer(uuid, name, conn);

    std::vector<EntityPlayer*> array;
    array.push_back(player);
    auto packetForAll = new PacketPlayerInfo(PacketPlayerInfo::Action::AddPlayer, array);
    broadcastPacket(packetForAll);
    delete(packetForAll);

    players.push_back(player);

    auto packetForOne = new PacketPlayerInfo(PacketPlayerInfo::Action::AddPlayer, players);
    conn.sendPacket(packetForOne);
    delete(packetForOne);

    return player;
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

ChunkPalette *Server::getPalette() const {
    return palette;
}

void Server::broadcastPacket(Packet *packet) {
    for(auto &player : players) {
        player->getConnection().sendPacket(packet);
    }
}

unsigned long Server::getPlayerCount() {
    return players.size();
}

