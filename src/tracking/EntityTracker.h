//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_ENTITYTRACKER_H
#define SPICYGOAT_ENTITYTRACKER_H

class Entity;
#include "../entities/Entity.h"
#include "../protocol/packets/ClientBoundPacket.h"

class EntityTracker {
   public:
    explicit EntityTracker(Entity& self);
    EntityTracker(EntityTracker&) = delete;
    virtual ~EntityTracker() = default;

    virtual void tick() = 0;

    virtual void broadcast(const ClientBoundPacket& packet) = 0;
    virtual void destroy() = 0;

   protected:
    Entity& self;
};

#endif  // SPICYGOAT_ENTITYTRACKER_H
