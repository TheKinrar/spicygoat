//
// Created by thekinrar on 01/04/19.
//

#include "EntityPlayer.h"

#include <iostream>
#include <utility>

#include "../Server.h"
#include "../protocol/packets/play/clientbound/PacketChunkData.h"
#include "../protocol/packets/play/clientbound/PacketDestroyEntities.h"
#include "../protocol/packets/play/clientbound/PacketRenderCenter.h"
#include "../protocol/packets/play/clientbound/PacketSpawnPlayer.h"
#include "../protocol/packets/play/clientbound/PacketUnloadChunk.h"

EntityPlayer::EntityPlayer(uuids::uuid uuid, std::string& name, std::shared_ptr<TCPConnection> conn)
    : conn(std::move(conn)) {
    this->uuid = uuid;
    this->name = name;
}

void EntityPlayer::tick() {
    Entity::tick();

    if(loadedChunks.empty()) chunkChanged();

    int effectiveViewDistance = spawned ? std::min(getRenderDistance(), Server::VIEW_DISTANCE) : 1;
    int32_t cx = getLocation().getChunkX();
    int32_t cz = getLocation().getChunkZ();
    int32_t min_x = cx - effectiveViewDistance;
    int32_t max_x = cx + effectiveViewDistance;
    int32_t min_z = cz - effectiveViewDistance;
    int32_t max_z = cz + effectiveViewDistance;

    int n = 0;
    while(!chunkSendQueue.empty()) {
        auto pos = chunkSendQueue.front();
        if(pos.getX() >= min_x && pos.getX() <= max_x && pos.getZ() >= min_z && pos.getZ() <= max_z) {
            auto& chunk = Server::get().getWorld().getChunk(pos);

            if(chunk.hasData()) {
                conn->sendPacket(PacketChunkData(chunk));
                ++n;
            } else {
                std::cerr << "no data for column " << chunk.toString() << std::endl;
            }
        }

        chunkSendQueue.pop();

        if(++n == 5) break;
    }

    if(!spawned && chunkSendQueue.empty()) {
        conn->sendPacket(PacketPlayerLocationCB(getLocation()));
        spawned = true;
        chunkChanged(); // Trigger loading of more chunks
    }
}

void EntityPlayer::chunkChanged() {
    Entity::chunkChanged();

    conn->sendPacket(PacketRenderCenter(getLocation().getChunkX(), getLocation().getChunkZ()));

    int effectiveViewDistance = spawned ? std::min(getRenderDistance(), Server::VIEW_DISTANCE) : 1;
    int32_t cx = getLocation().getChunkX();
    int32_t cz = getLocation().getChunkZ();
    int32_t min_x = cx - effectiveViewDistance;
    int32_t max_x = cx + effectiveViewDistance;
    int32_t min_z = cz - effectiveViewDistance;
    int32_t max_z = cz + effectiveViewDistance;

    for(auto it : std::unordered_map(loadedChunks)) {
        auto& chunk = it.second.get();

        if(chunk.getX() < min_x || chunk.getX() > max_x || chunk.getZ() < min_z || chunk.getZ() > max_z) {
            conn->sendPacket(PacketUnloadChunk(chunk));
            loadedChunks.erase(it.first);
        }
    }

    loadChunk(cx, cz);
    for(int i = 1; i <= effectiveViewDistance; ++i) {
        for(int32_t x = cx - i; x <= cx + i; ++x) {
            loadChunk(x, cz - i);
            loadChunk(x, cz + i);
        }

        for(int32_t z = cz - i + 1; z <= cz + i - 1; ++z) {
            loadChunk(cx - i, z);
            loadChunk(cx + i, z);
        }
    }

    nearbyEntities.clear();
    for(auto& e : Server::get().getEntities()) {
        if(e.get() != this) {
            double d = e->getLocation().distanceSquared(getLocation());

            if(d <= Server::ENTITY_VIEW_DISTANCE_SQ) {
                nearbyEntities.insert(e);
            }
        }
    }
}

void EntityPlayer::loadChunk(int32_t x, int32_t z) {
    ChunkPosition pos(x, 0, z);

    if(loadedChunks.find(pos) == loadedChunks.end()) {
        chunkSendQueue.emplace(pos);
    }
}

std::string EntityPlayer::toString() {
    return std::string("EntityPlayer{name=") + name + "}";
}

uuids::uuid EntityPlayer::getUuid() const {
    return uuid;
}

const std::string& EntityPlayer::getName() const {
    return name;
}

TCPConnection& EntityPlayer::getConnection() const {
    return *conn;
}

std::unique_ptr<ClientBoundPacket> EntityPlayer::createPacket() {
    return std::make_unique<PacketSpawnPlayer>(getEID(), uuid, getLocation().getX(), getLocation().getY(),
                                               getLocation().getZ(), getLocation().getYaw(), getLocation().getPitch());
}

std::unique_ptr<ClientBoundPacket> EntityPlayer::removePacket() {
    return std::make_unique<PacketDestroyEntities>(getEID());
}

void EntityPlayer::sendMessage(const std::string& message) const {
    getConnection().sendPacket(PacketChatMessageCB(message));
}

void EntityPlayer::teleport(const Location& loc) {
    this->getConnection().sendPacket(PacketPlayerLocationCB(loc));
    this->setNextLocation(loc);
}

void EntityPlayer::setFlyingSpeed(float speed) {
    this->getConnection().sendPacket(PacketPlayerAbilities(false, true, true, false, speed, 0.1));
}
