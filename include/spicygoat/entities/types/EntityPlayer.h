//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITYPLAYER_H
#define SPICYGOAT_ENTITYPLAYER_H

class PlayerData;
class TCPConnection;

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include <spdlog/spdlog.h>
#include <spicygoat/config/Config.h>
#include <spicygoat/entities/Entity.h>
#include <spicygoat/inventory/PlayerInventory.h>
#include <spicygoat/persist/PlayerData.h>
#include <spicygoat/TCPConnection.h>
#include <spicygoat/util/PlayerAbilities.h>
#include <spicygoat/world/chunks/ChunkColumn.h>
#include <spicygoat/world/geo/ChunkPosition.h>
#include <spicygoat/world/geo/Location.h>
#include <spicygoat/world/geo/Position2D.h>

class EntityPlayer : public Entity {
   public:
    EntityPlayer(uuids::uuid uuid, std::string &name, std::shared_ptr<TCPConnection> conn);

    std::string getType() override {
        return "minecraft:player";
    }

    void tick() override;

    const std::string &getName() const;

    PlayerData &getData() const {
        return *data;
    }

    void pullData();
    void pushData();

    int getRenderDistance() const {
        return renderDistance;
    }

    void setRenderDistance(int renderDistance) {
        this->renderDistance = renderDistance;

        checkChunks();
    }

    GameMode::GameMode getGamemode() const {
        return gamemode;
    }

    void setGamemode(GameMode::GameMode gamemode);

    void syncAbilities();

    void sendAbilities() const;

    void sendMessage(const std::string& message) const;

    void teleport(const Location& loc);

    void setFlying(bool flying, bool fromClient = false);

    void setFlyingSpeed(float speed);

    bool isSpawned() const {
        return spawned;
    }

    spdlog::logger& getLogger() const {
        return *logger;
    }

    TCPConnection &getConnection() const;

    std::unique_ptr<ClientBoundPacket> createPacket() override;

    std::string toString() override;

    std::unique_ptr<PlayerInventory> inventory;

   protected:
    void chunkChanged() override;

   private:
    void checkChunks();
    void loadChunk(int32_t x, int32_t z);

    std::shared_ptr<spdlog::logger> logger;

    std::string name;
    GameMode::GameMode gamemode = Config::get().gamemode;

    PlayerAbilities abilities{};

    std::unique_ptr<PlayerData> data;

    std::shared_ptr<TCPConnection> conn;

    std::unordered_map<ChunkPosition, std::reference_wrapper<ChunkColumn>> loadedChunks;
    std::queue<ChunkPosition> chunkSendQueue;
    std::set<ChunkPosition> queuedChunks;
    bool spawned = false;

    int renderDistance = 0;
};

#endif  // SPICYGOAT_ENTITYPLAYER_H
