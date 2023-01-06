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
#include "../world/chunks/ChunkColumn.h"
#include "../world/geo/Location.h"
#include "../world/geo/Position2D.h"
#include "Entity.h"

class EntityPlayer : public Entity {
   public:
    EntityPlayer(uuids::uuid uuid, std::string &name, std::shared_ptr<TCPConnection> conn);

    void tick() override;

    uuids::uuid getUuid() const;

    const std::string &getName() const;

    TCPConnection &getConnection() const;

    std::unique_ptr<ClientBoundPacket> createPacket() override;

    std::unique_ptr<ClientBoundPacket> removePacket() override;

    std::string toString() override;

    PlayerInventory inventory;

   protected:
    void chunkChanged() override;

   private:
    uuids::uuid uuid;
    std::string name;

    std::shared_ptr<TCPConnection> conn;

    std::unordered_map<Position2D, std::reference_wrapper<ChunkColumn>> loadedChunks;
    std::queue<std::reference_wrapper<ChunkColumn>> chunkSendQueue;

    std::set<std::shared_ptr<Entity>> nearbyEntities;
};

#endif  // SPICYGOAT_ENTITYPLAYER_H
