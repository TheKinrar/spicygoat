//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_SERVER_H
#define SPICYGOAT_SERVER_H

#include "entities/EntityPlayer.h"
#include "world/World.h"
#include <string>
#include <uuid/uuid.h>
#include <vector>

class Server {
public:
    inline static const int VIEW_DISTANCE = 10;
    inline static const int ENTITY_VIEW_DISTANCE = 50;
    inline static const int ENTITY_VIEW_DISTANCE_SQ = ENTITY_VIEW_DISTANCE * ENTITY_VIEW_DISTANCE;

    Server();

    static Server* get();

    void run();

    EntityPlayer* createPlayer(uuid_t& uuid, std::string name, TCPConnection& conn);

    void removePlayer(EntityPlayer&);

    [[nodiscard]] const std::forward_list<Entity*>& getEntities() const;

    [[nodiscard]] const std::forward_list<EntityPlayer*>& getPlayers() const;

    int32_t nextEID();

    static std::unique_ptr<EntityTracker> createTracker(Entity&);

    unsigned long getPlayerCount() const;

    void tick();

    World& getWorld();

    [[nodiscard]] ChunkPalette* getPalette() const;

    [[nodiscard]] const std::vector<std::byte>& getCodec() const;

    void broadcastPacket(Packet*);

private:
    ChunkPalette* palette;
    std::vector<std::byte> codec;

    std::forward_list<EntityPlayer*> players;
    int playerCount = 0;

    int32_t next_eid = 0;
    std::forward_list<Entity*> entities;

    World world;
};


#endif//SPICYGOAT_SERVER_H
