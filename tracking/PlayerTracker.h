//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_PLAYERTRACKER_H
#define SPICYGOAT_PLAYERTRACKER_H

#include <set>

#include "../entities/EntityPlayer.h"
#include "EntityTracker.h"

class PlayerTracker : public EntityTracker {
   public:
    explicit PlayerTracker(Entity &self);

    void tick() override;

    void broadcast(const ClientBoundPacket &packet) override;

   private:
    std::set<std::shared_ptr<EntityPlayer>> players;
};

#endif  // SPICYGOAT_PLAYERTRACKER_H
