//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_SERVER_H
#define SPICYGOAT_SERVER_H

#include "entities/EntityPlayer.h"
#include "world/World.h"
#include <vector>
#include <uuid/uuid.h>
#include <string>

class Server {
public:
    Server();

    static Server* get();

    EntityPlayer* createPlayer(uuid_t &uuid, std::string name, TCPConnection &conn);

    int32_t nextEID();

    void tick();

    World& getWorld();

    ChunkPalette *getPalette() const;

private:
    ChunkPalette *palette;

    std::vector<EntityPlayer*> players;

    int32_t next_eid = 0;
    std::vector<Entity*> entities;

    World world;
};


#endif //SPICYGOAT_SERVER_H
