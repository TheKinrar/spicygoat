//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_SERVER_H
#define SPICYGOAT_SERVER_H

#include "entities/EntityPlayer.h"
#include "world/World.h"
#include "util/Registry.h"
#include <vector>
#include <string>
#include <libstud/uuid.hxx>

class Server {
public:
    inline static const int VIEW_DISTANCE = 10;
    inline static const int ENTITY_VIEW_DISTANCE = 50;
    inline static const int ENTITY_VIEW_DISTANCE_SQ = ENTITY_VIEW_DISTANCE * ENTITY_VIEW_DISTANCE;

    Server();
    static Server* get();

    void run();

    EntityPlayer* createPlayer(stud::uuid uuid, std::string name, TCPConnection &conn);
    void removePlayer(EntityPlayer&);
    [[nodiscard]] const std::forward_list<Entity*>& getEntities() const;
    [[nodiscard]] const std::forward_list<EntityPlayer*>& getPlayers() const;
    int32_t nextEID();
    static std::unique_ptr<EntityTracker> createTracker(Entity&);
    unsigned long getPlayerCount() const;

    void tick();

    World& getWorld();

    [[nodiscard]] std::shared_ptr<ChunkPalette> getPalette() const;
    [[nodiscard]] const Registry &getItemRegistry() const { return itemRegistry; }

    void broadcastPacket(Packet*);

private:
    void loadRegistries();
    static void loadRegistry(Registry& registry, nlohmann::json root);

    std::shared_ptr<ChunkPalette> palette;
    Registry itemRegistry = Registry("minecraft:item");

    std::forward_list<EntityPlayer*> players;
    int playerCount = 0;

    int32_t next_eid = 0;
    std::forward_list<Entity*> entities;

    World world;
};


#endif //SPICYGOAT_SERVER_H
