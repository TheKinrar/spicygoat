//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_SERVER_H
#define SPICYGOAT_SERVER_H

#include <uuid.h>

#include <string>
#include <vector>

#include "../data/out/registries.h"
#include "commands/CommandEngine.h"
#include "entities/types/EntityPlayer.h"
#include "item/ItemRegistry.h"
#include "util/Registry.h"
#include "world/World.h"

class Server {
   public:
    inline static const int VIEW_DISTANCE = 64;
    inline static const int ENTITY_VIEW_DISTANCE = 50;

    static Server& get();
    Server(const Server&) = delete;

    void load();
    void run();

    std::shared_ptr<EntityPlayer> createPlayer(uuids::uuid uuid, std::string name, std::shared_ptr<TCPConnection> conn);
    void spawnEntity(const std::shared_ptr<Entity>& entity);
    void removePlayer(EntityPlayer&);
    void removeEntity(Entity& entity);
    int32_t nextEID();
    static std::unique_ptr<EntityTracker> createTracker(Entity&);
    unsigned long getPlayerCount() const;

    [[nodiscard]] std::vector<std::shared_ptr<Entity>> getEntities() const {
        std::vector<std::shared_ptr<Entity>> vec;
        for(auto& item : entities) vec.push_back(item.second);
        return vec;
    }

    [[nodiscard]] std::vector<std::shared_ptr<EntityPlayer>> getPlayers() const {
        std::vector<std::shared_ptr<EntityPlayer>> vec;
        for(auto& item : players) vec.push_back(item.second);
        return vec;
    }

    [[nodiscard]] std::optional<std::shared_ptr<EntityPlayer>> getPlayer(const std::string& name) const {
        auto it = std::find_if(players.begin(), players.end(),
                               [name](auto& e) { return e.second->getName() == name; });
        if(it == players.end())
            return {};
        else
            return it->second;
    }

    void tick();

    World& getWorld();

    CommandEngine& getCommandEngine() {
        return commandEngine;
    }

    [[nodiscard]] std::shared_ptr<ChunkPalette> getPalette() const;
    [[nodiscard]] BlockRegistry& getBlockRegistry() {
        return blockRegistry;
    }
    [[nodiscard]] ItemRegistry& getItemRegistry() {
        return itemRegistry;
    }
    [[nodiscard]] Registry& getEntityRegistry() {
        return entityRegistry;
    }

    void broadcastMessage(const std::string& message);
    void broadcastPacket(const Packet&);

   private:
    Server();

    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<spdlog::logger> chatLogger;

    CommandEngine commandEngine;

    std::shared_ptr<ChunkPalette> palette;
    BlockRegistry blockRegistry = BlockRegistry();
    ItemRegistry itemRegistry = ItemRegistry();
    Registry entityRegistry = Registry("minecraft:entity_type");

    std::map<uuids::uuid, std::shared_ptr<EntityPlayer>> players;
    int playerCount = 0;

    int32_t next_eid = 0;
    std::map<int32_t, std::shared_ptr<Entity>> entities;

    World world;

    long startupTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
};

#endif  // SPICYGOAT_SERVER_H
