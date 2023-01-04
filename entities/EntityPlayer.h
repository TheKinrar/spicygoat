//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITYPLAYER_H
#define SPICYGOAT_ENTITYPLAYER_H

class TCPConnection;

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "Entity.h"
#include "../world/geo/Location.h"
#include "../world/chunks/ChunkColumn.h"
#include "../TCPConnection.h"
#include "../world/geo/Position2D.h"
#include "../inventory/PlayerInventory.h"

class EntityPlayer : public Entity {
public:
    EntityPlayer(stud::uuid uuid, std::string& name, TCPConnection &conn);

    void tick() override;

    stud::uuid getUuid() const;

    const std::string &getName() const;

    TCPConnection &getConnection() const;

    std::unique_ptr<ClientBoundPacket> createPacket() override;

    std::unique_ptr<ClientBoundPacket> removePacket() override;

    std::string toString() override;

    PlayerInventory inventory;

protected:
    void chunkChanged() override;

private:
    stud::uuid uuid;
    std::string name;

    TCPConnection &conn;

    std::unordered_map<Position2D, std::reference_wrapper<ChunkColumn>> loadedChunks;
    std::queue<std::reference_wrapper<ChunkColumn>> chunkSendQueue;

    std::set<Entity*> nearbyEntities;
};


#endif //SPICYGOAT_ENTITYPLAYER_H
