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
    inline static constexpr const char* const PROTOCOL_VERSION_NAME = "1.15.2";
    inline static const int PROTOCOL_VERSION_NUMBER = 578;

    Server();

    static Server* get();

    EntityPlayer* createPlayer(uuid_t &uuid, std::string name, TCPConnection &conn);
    void removePlayer(EntityPlayer&);

    int32_t nextEID();

    void tick();

    unsigned long getPlayerCount();

    World& getWorld();

    ChunkPalette *getPalette() const;

    void broadcastPacket(Packet*);

private:
    ChunkPalette *palette;

    std::forward_list<EntityPlayer*> players;
    int playerCount = 0;

    int32_t next_eid = 0;
    std::vector<Entity*> entities;

    World world;
};


#endif //SPICYGOAT_SERVER_H
