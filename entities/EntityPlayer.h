//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITYPLAYER_H
#define SPICYGOAT_ENTITYPLAYER_H

class TCPConnection;

#include <uuid/uuid.h>
#include <string>
#include <vector>
#include <map>
#include "Entity.h"
#include "../world/geo/Location.h"
#include "../world/chunks/ChunkColumn.h"
#include "../TCPConnection.h"
#include "../world/geo/Position2D.h"

class EntityPlayer : public Entity {
public:
    EntityPlayer(uuid_t &uuid, std::string& name, TCPConnection &conn);

    void tick() override;

    std::string toString() override;

protected:
    void chunkChanged() override;

private:
    uuid_t *uuid;
    std::string name;

    TCPConnection &conn;

    std::map<Position2D, ChunkColumn*> loadedChunks;
    std::map<Position2D, ChunkColumn*> loadingChunks;
};


#endif //SPICYGOAT_ENTITYPLAYER_H
