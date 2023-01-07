//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITYPLAYER_H
#define SPICYGOAT_ENTITYPLAYER_H

class TCPConnection;

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../TCPConnection.h"
#include "../../config/Config.h"
#include "../../inventory/PlayerInventory.h"
#include "../../persist/PlayerData.h"
#include "../../protocol/packets/play/clientbound/PacketChatMessageCB.h"
#include "../../world/chunks/ChunkColumn.h"
#include "../../world/geo/ChunkPosition.h"
#include "../../world/geo/Location.h"
#include "../../world/geo/Position2D.h"
#include "../Entity.h"

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

    int getGamemode() const {
        return gamemode;
    }

    void setGamemode(int gamemode);

    void sendMessage(const std::string& message) const;

    void teleport(const Location& loc);

    void setFlyingSpeed(float speed);

    bool isSpawned() const {
        return spawned;
    }

    TCPConnection &getConnection() const;

    std::unique_ptr<ClientBoundPacket> createPacket() override;

    std::string toString() override;

    PlayerInventory inventory;

   protected:
    void chunkChanged() override;

   private:
    void checkChunks();
    void loadChunk(int32_t x, int32_t z);

    std::string name;
    int gamemode = Config::get().gamemode;

    std::unique_ptr<PlayerData> data;

    std::shared_ptr<TCPConnection> conn;

    std::unordered_map<ChunkPosition, std::reference_wrapper<ChunkColumn>> loadedChunks;
    std::queue<ChunkPosition> chunkSendQueue;
    std::set<ChunkPosition> queuedChunks;
    bool spawned = false;

    int renderDistance = 0;
};

#endif  // SPICYGOAT_ENTITYPLAYER_H
