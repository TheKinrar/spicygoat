//
// Created by thekinrar on 01/04/19.
//

#include <fstream>
#include <iostream>
#include "Server.h"

Server::Server() {
    std::ifstream ifs("/home/thekinrar/temparia/generated/reports/blocks.json");
    nlohmann::json j;
    ifs >> j;
    palette = ChunkPalette::fromJson(j);
    ifs.close();
}

Server* Server::get() {
    static auto instance = new Server();
    return instance;
}

EntityPlayer* Server::createPlayer(uuid_t &uuid, std::string name, TCPConnection &conn) {
    auto *player = new EntityPlayer(uuid, name, conn);
    players.push_back(player);
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

