//
// Created by thekinrar on 01/04/19.
//

#include "EntityPlayer.h"

#include <iostream>
#include <utility>

#include "../../Server.h"
#include "../../protocol/packets/play/clientbound/PacketChunkData.h"
#include "../../protocol/packets/play/clientbound/PacketDestroyEntities.h"
#include "../../protocol/packets/play/clientbound/PacketGameEvent.h"
#include "../../protocol/packets/play/clientbound/PacketRenderCenter.h"
#include "../../protocol/packets/play/clientbound/PacketSpawnPlayer.h"
#include "../../protocol/packets/play/clientbound/PacketUnloadChunk.h"

EntityPlayer::EntityPlayer(uuids::uuid uuid, std::string& name, std::shared_ptr<TCPConnection> conn)
    : Entity(uuid), conn(std::move(conn)), inventory(std::make_unique<PlayerInventory>(*this)) {
    this->name = name;
    this->data = PlayerData::load(uuid);
    pullData();
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
                loadedChunks.emplace(pos, chunk);
                ++n;
            } else {
                std::cerr << "no data for column " << chunk.toString() << std::endl;
            }
        }

        chunkSendQueue.pop();
        queuedChunks.erase(pos);

        if(n == 5) break;
    }

    if(!spawned && chunkSendQueue.empty()) {
        conn->sendPacket(PacketPlayerLocationCB(getLocation()));
        spawned = true;
        checkChunks();
    }
}

void EntityPlayer::chunkChanged() {
    Entity::chunkChanged();

    conn->sendPacket(PacketRenderCenter(getLocation().getChunkX(), getLocation().getChunkZ()));

    checkChunks();
}

void EntityPlayer::checkChunks() {
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
}

void EntityPlayer::loadChunk(int32_t x, int32_t z) {
    ChunkPosition pos(x, 0, z);

    if(loadedChunks.find(pos) == loadedChunks.end()
       && queuedChunks.find(pos) == queuedChunks.end()) {
        chunkSendQueue.emplace(pos);
        queuedChunks.emplace(pos);
    }
}

std::string EntityPlayer::toString() {
    return std::string("EntityPlayer{name=") + name + "}";
}

const std::string& EntityPlayer::getName() const {
    return name;
}

TCPConnection& EntityPlayer::getConnection() const {
    return *conn;
}

std::unique_ptr<ClientBoundPacket> EntityPlayer::createPacket() {
    return std::make_unique<PacketSpawnPlayer>(getEID(), getUuid(), getLocation().getX(), getLocation().getY(),
                                               getLocation().getZ(), getLocation().getYaw(), getLocation().getPitch());
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

void EntityPlayer::setGamemode(int gamemode) {
    getConnection().sendPacket(PacketGameEvent(PacketGameEvent::Event::ChangeGamemode, gamemode));

    this->gamemode = gamemode;
}

void EntityPlayer::pullData() {
    setLocation(data->getLocation(Location(Server::get().getWorld().getSpawnPosition())));
    inventory = std::make_unique<PlayerInventory>(data->getInventory(*this));
}

void EntityPlayer::pushData() {
    data->setLocation(getLocation());
    data->setInventory(*inventory);
}