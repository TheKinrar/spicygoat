//
// Created by thekinrar on 01/04/19.
//

#include <iostream>
#include "EntityPlayer.h"
#include "../Server.h"
#include "../protocol/packets/play/clientbound/PacketUnloadChunk.h"
#include "../protocol/packets/play/clientbound/PacketChunkData.h"
#include "../protocol/packets/play/clientbound/PacketDestroyEntities.h"
#include "../protocol/packets/play/clientbound/PacketSpawnPlayer.h"

EntityPlayer::EntityPlayer(uuid_t &uuid, std::string& name, TCPConnection &conn) : uuid(uuid), conn(conn) {
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
            conn.sendPacket(new PacketChunkData(chunk));
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

    int32_t min_x = getLocation().getChunkX() - Server::VIEW_DISTANCE;
    int32_t max_x = getLocation().getChunkX() + Server::VIEW_DISTANCE;
    int32_t min_z = getLocation().getChunkZ() - Server::VIEW_DISTANCE;
    int32_t max_z = getLocation().getChunkZ() + Server::VIEW_DISTANCE;

    for(auto it : std::unordered_map(loadedChunks)) {
        auto& chunk = it.second.get();

        if(chunk.getX() < min_x || chunk.getX() > max_x || chunk.getZ() < min_z || chunk.getZ() > max_z) {
            conn.sendPacket(new PacketUnloadChunk(chunk));
            loadedChunks.erase(it.first);
        }
    }

    for(int32_t x = min_x; x <= max_x; ++x) {
        for(int32_t z = min_z; z <= max_z; ++z) {
            Position2D pos(x, z);

            if(loadedChunks.find(pos) == loadedChunks.end()) {
                ChunkColumn& column = Server::get()->getWorld().getChunk(x, z);
                chunkSendQueue.emplace(column);
                loadedChunks.emplace(pos, column);
            }
        }
    }

    nearbyEntities.clear();
    for(auto* e : Server::get()->getEntities()) {
        if(e != this) {
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

uuid_t& EntityPlayer::getUuid() const {
    return uuid;
}

const std::string &EntityPlayer::getName() const {
    return name;
}

TCPConnection &EntityPlayer::getConnection() const {
    return conn;
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
