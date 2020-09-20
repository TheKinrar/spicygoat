//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITYPLAYER_H
#define SPICYGOAT_ENTITYPLAYER_H

class TCPConnection;

#include "../TCPConnection.h"
#include "../world/chunks/ChunkColumn.h"
#include "../world/geo/Location.h"
#include "../world/geo/Position2D.h"
#include "Entity.h"
#include <boost/uuid/uuid.hpp>
#include <map>
#include <string>
#include <vector>

class EntityPlayer : public Entity {
public:
    EntityPlayer(boost::uuids::uuid& uuid, std::string& name, TCPConnection& conn);

    void tick() override;

    boost::uuids::uuid& getUuid() const;

    const std::string& getName() const;

    TCPConnection& getConnection() const;

    std::unique_ptr<ClientBoundPacket> createPacket() override;

    std::unique_ptr<ClientBoundPacket> removePacket() override;

    std::string toString() override;

protected:
    void chunkChanged() override;

private:
    boost::uuids::uuid& uuid;
    std::string name;

    TCPConnection& conn;

    std::map<Position2D, ChunkColumn*> loadedChunks;
    std::map<Position2D, ChunkColumn*> loadingChunks;

    std::set<Entity*> nearbyEntities;
};


#endif//SPICYGOAT_ENTITYPLAYER_H
