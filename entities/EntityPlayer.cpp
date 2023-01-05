//
// Created by thekinrar on 01/04/19.
//

#include <iostream>
#include <utility>
#include "EntityPlayer.h"
#include "../Server.h"
#include "../protocol/packets/play/clientbound/PacketUnloadChunk.h"
#include "../protocol/packets/play/clientbound/PacketChunkData.h"
#include "../protocol/packets/play/clientbound/PacketDestroyEntities.h"
#include "../protocol/packets/play/clientbound/PacketSpawnPlayer.h"
#include "../protocol/packets/play/clientbound/PacketRenderCenter.h"

EntityPlayer::EntityPlayer(stud::uuid uuid, std::string& name, std::shared_ptr<TCPConnection> conn) : conn(std::move(conn)) {
    this->uuid = uuid;
    this->name = name;
}

void EntityPlayer::tick() {
    Entity::tick();

    if(loadedChunks.empty())
        chunkChanged();

    int n = 0;
    while(!chunkSendQueue.empty()) {
        auto& chunk = chunkSendQueue.front().get();

        if(chunk.hasData()) {
            conn->sendPacket(PacketChunkData(chunk));
        } else {
            std::cerr << "no data for column " << chunk.toString() << std::endl;
        }

        chunkSendQueue.pop();

        ++n;
        if(++n == 5)
            break;
    }
}

void EntityPlayer::chunkChanged() {
    Entity::chunkChanged();

    conn->sendPacket(PacketRenderCenter(getLocation().getChunkX(), getLocation().getChunkZ()));

    int32_t min_x = getLocation().getChunkX() - Server::VIEW_DISTANCE;
    int32_t max_x = getLocation().getChunkX() + Server::VIEW_DISTANCE;
    int32_t min_z = getLocation().getChunkZ() - Server::VIEW_DISTANCE;
    int32_t max_z = getLocation().getChunkZ() + Server::VIEW_DISTANCE;

    for(auto it : std::unordered_map(loadedChunks)) {
        auto& chunk = it.second.get();

        if(chunk.getX() < min_x || chunk.getX() > max_x || chunk.getZ() < min_z || chunk.getZ() > max_z) {
            conn->sendPacket(PacketUnloadChunk(chunk));
            loadedChunks.erase(it.first);
        }
    }

    for(int32_t x = min_x; x <= max_x; ++x) {
        for(int32_t z = min_z; z <= max_z; ++z) {
            Position2D pos(x, z);

            if(loadedChunks.find(pos) == loadedChunks.end()) {
                ChunkColumn& column = Server::get().getWorld().getChunk(x, z);
                chunkSendQueue.emplace(column);
                loadedChunks.emplace(pos, column);
            }
        }
    }

    nearbyEntities.clear();
    for(auto &e : Server::get().getEntities()) {
        if(e.get() != this) {
            double d = e->getLocation().distanceSquared(getLocation());

            if(d <= Server::ENTITY_VIEW_DISTANCE_SQ) {
                nearbyEntities.insert(e);
            }
        }
    }
}

std::string EntityPlayer::toString() {
    return std::string("EntityPlayer{name=") + name + "}";
}

stud::uuid EntityPlayer::getUuid() const {
    return uuid;
}

const std::string &EntityPlayer::getName() const {
    return name;
}

TCPConnection &EntityPlayer::getConnection() const {
    return *conn;
}

std::unique_ptr<ClientBoundPacket> EntityPlayer::createPacket() {
    return std::make_unique<PacketSpawnPlayer>(
            getEID(), uuid,
            getLocation().getX(), getLocation().getY(), getLocation().getZ(),
            getLocation().getYaw(), getLocation().getPitch()
    );
}

std::unique_ptr<ClientBoundPacket> EntityPlayer::removePacket() {
    return std::make_unique<PacketDestroyEntities>(getEID());
}
