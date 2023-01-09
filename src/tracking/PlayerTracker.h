//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_PLAYERTRACKER_H
#define SPICYGOAT_PLAYERTRACKER_H

#include <set>

#include "../entities/types/EntityPlayer.h"
#include "EntityTracker.h"

class PlayerTracker : public EntityTracker {
   public:
    explicit PlayerTracker(Entity &self);
    ~PlayerTracker() override;

    void tick() override;

    [[nodiscard]]
    const std::set<std::shared_ptr<EntityPlayer>>& getPlayers() const {
        return players;
    }
    void broadcast(const ClientBoundPacket &packet) override;
    void destroy() override;

   private:
    std::set<std::shared_ptr<EntityPlayer>> players;
    bool destroyed = false;
};

#endif  // SPICYGOAT_PLAYERTRACKER_H
