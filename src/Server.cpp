//
// Created by thekinrar on 01/04/19.
//

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spicygoat/Server.h>
#include <spicygoat/TCPServer.h>
#include <spicygoat/commands/builtin/CommandGm.h>
#include <spicygoat/commands/builtin/CommandSpeed.h>
#include <spicygoat/commands/builtin/CommandTp.h>
#include <spicygoat/data/blocks.h>
#include <spicygoat/events/PlayerJoinEvent.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketChatMessageCB.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketPlayerInfo.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketPlayerInfoRemove.h>
#include <spicygoat/tracking/PlayerTracker.h>

#include <iostream>

Server& Server::get() {
    static Server instance;
    return instance;
}

Server::Server() {
    spdlog::info(std::string("SpicyGoat dev build - MC ") + Protocol::PROTOCOL_VERSION_NAME + " (protocol " +
                 getProtocolVersionString() + ")");

    logger = spdlog::stdout_color_mt("Server");
    chatLogger = spdlog::stdout_color_mt("Chat");
}

void Server::load() {
    for(Block& block : blockRegistry.getBlocks()) block.load();

    palette = std::make_unique<ChunkPalette>();
    palette->loadGlobal();
    palette->finalize();

    Registries::load(blockRegistry, entityRegistry, itemRegistry);

    getCommandEngine().registerCommand(std::make_unique<CommandGm>());
    getCommandEngine().registerCommand(std::make_unique<CommandSpeed>());
    getCommandEngine().registerCommand(std::make_unique<CommandTp>());

    pluginManager.loadPlugins();
}

void Server::run() {
    logger->info("Starting");

    load();

    std::thread tcpThread(&TCPServer::accept, &TCPServer::get());

    long elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
            .count() -
        startupTime;
    logger->info("Ready! Started in {} s", (double)elapsed / 1000);

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

    auto event = PlayerJoinEvent(player, "§6" + player->getName() + " joined");
    event.call();

    if(!event.getJoinMessage().empty()) {
        broadcastMessage(event.getJoinMessage());
    }

    return player;
}

void Server::spawnEntity(const std::shared_ptr<Entity>& entity) {
    entity->setSelfPtr(entity);

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

    broadcastMessage("§6" + p.getName() + " left");
}

void Server::removeEntity(Entity& entity) {
    entity.getTracker().destroy();
    entities.erase(entity.getEID());
}

int32_t Server::nextEID() {
    return next_eid++;
}

void Server::tick() {
    scheduler.tick();

    for(auto& e : getEntities()) {
        if(world.getChunkAt(e->getLocation()).hasData()) {
            e->tick();
        }
    }
}

World& Server::getWorld() {
    return world;
}

std::shared_ptr<ChunkPalette> Server::getPalette() const {
    return palette;
}

void Server::broadcastMessage(const std::string& message) {
    chatLogger->info(message);
    broadcastPacket(PacketChatMessageCB(message));
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

int Server::getProtocolVersionNumber() const {
    if(Protocol::PROTOCOL_SNAPSHOT) {
        return 0x40000000 + Protocol::PROTOCOL_VERSION_NUMBER;
    } else {
        return Protocol::PROTOCOL_VERSION_NUMBER;
    }
}

std::string Server::getProtocolVersionString() const {
    if(Protocol::PROTOCOL_SNAPSHOT) {
        return "Snapshot " + std::to_string(Protocol::PROTOCOL_VERSION_NUMBER);
    } else {
        return std::to_string(Protocol::PROTOCOL_VERSION_NUMBER);
    }
}
