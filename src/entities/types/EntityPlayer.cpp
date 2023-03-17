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
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

EntityPlayer::EntityPlayer(uuids::uuid uuid, std::string& name, std::shared_ptr<TCPConnection> conn)
    : Entity(uuid), conn(std::move(conn)), inventory(std::make_unique<PlayerInventory>(*this)) {
    auto loggerName = "Player/" + name;
    logger = spdlog::get(loggerName);
    if(!logger) logger = spdlog::stdout_color_mt(loggerName);

    this->name = name;
    this->data = PlayerData::load(uuid);
    pullData();
    syncAbilities();
}

void EntityPlayer::tick() {
    conn->getListener().tick();

    Entity::tick();

    if(loadedChunks.empty()) chunkChanged();

    int effectiveViewDistance = spawned ? std::min(getRenderDistance(), Config::get().viewDistance) : 1;
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
                logger->warn("No data for " + chunk.toString());
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
    int effectiveViewDistance = spawned ? std::min(getRenderDistance(), Config::get().viewDistance) : 1;
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
    this->abilities.flySpeed = speed;
    sendAbilities();
}

void EntityPlayer::setGamemode(GameMode::GameMode gamemode) {
    this->gamemode = gamemode;
    syncAbilities();

    getConnection().sendPacket(PacketGameEvent(PacketGameEvent::Event::ChangeGamemode, static_cast<float>(gamemode)));
    sendAbilities();
}

void EntityPlayer::pullData() {
    setLocation(data->getLocation(Location(Server::get().getWorld().getSpawnPosition())));
    gamemode = data->getGameMode(Config::get().gamemode);
    abilities = data->getAbilities();
    inventory = std::make_unique<PlayerInventory>(data->getInventory(*this));
}

void EntityPlayer::pushData() {
    data->setLocation(getLocation());
    data->setGameMode(gamemode);
    data->setAbilities(abilities);
    data->setInventory(*inventory);
}

void EntityPlayer::syncAbilities() {
    switch(getGamemode()) {
        case GameMode::GameMode::Survival:
        case GameMode::GameMode::Adventure:
            abilities.invulnerable = false;
            abilities.flying = false;
            abilities.allowFlying = false;
            abilities.creative = false;
            break;
        case GameMode::GameMode::Creative:
            abilities.invulnerable = true;
            abilities.allowFlying = true;
            abilities.creative = true;
            break;
        case GameMode::GameMode::Spectator:
            abilities.invulnerable = true;
            abilities.flying = true;
            abilities.allowFlying = true;
            abilities.creative = false;
            break;
    }
}

void EntityPlayer::sendAbilities() const {
    getConnection().sendPacket(PacketPlayerAbilities(abilities));
}

void EntityPlayer::setFlying(bool flying, bool fromClient) {
    this->abilities.flying = flying;

    if(!fromClient) {
        sendAbilities();
    }
}
