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

#include "../TCPConnection.h"
#include "../inventory/PlayerInventory.h"
#include "../protocol/packets/play/clientbound/PacketChatMessageCB.h"
#include "../world/chunks/ChunkColumn.h"
#include "../world/geo/ChunkPosition.h"
#include "../world/geo/Location.h"
#include "../world/geo/Position2D.h"
#include "Entity.h"

class EntityPlayer : public Entity {
   public:
    EntityPlayer(uuids::uuid uuid, std::string &name, std::shared_ptr<TCPConnection> conn);

    void tick() override;

    uuids::uuid getUuid() const;

    const std::string &getName() const;

    int getRenderDistance() const {
        return renderDistance;
    }

    void setRenderDistance(int renderDistance) {
        this->renderDistance = renderDistance;
    }

    void sendMessage(const std::string& message) const;

    void teleport(const Location& loc);

    TCPConnection &getConnection() const;

    std::unique_ptr<ClientBoundPacket> createPacket() override;

    std::unique_ptr<ClientBoundPacket> removePacket() override;

    std::string toString() override;

    PlayerInventory inventory;

   protected:
    void chunkChanged() override;

   private:
    void loadChunk(int32_t x, int32_t z);

    uuids::uuid uuid;
    std::string name;

    std::shared_ptr<TCPConnection> conn;

    std::unordered_map<ChunkPosition, std::reference_wrapper<ChunkColumn>> loadedChunks;
    std::queue<ChunkPosition> chunkSendQueue;
    bool spawned = false;

    std::set<std::shared_ptr<Entity>> nearbyEntities;

    int renderDistance = 0;
};

#endif  // SPICYGOAT_ENTITYPLAYER_H
