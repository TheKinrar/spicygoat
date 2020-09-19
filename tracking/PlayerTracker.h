//
// Created by thekinrar on 19/09/2020.
//

#ifndef SPICYGOAT_PLAYERTRACKER_H
#define SPICYGOAT_PLAYERTRACKER_H


#include <set>

#include "EntityTracker.h"
#include "../entities/EntityPlayer.h"

class PlayerTracker : public EntityTracker {
public:
    explicit PlayerTracker(Entity &self);

    void tick() override;

    void broadcast(ClientBoundPacket &packet) override;

private:
    std::set<EntityPlayer*> players;
};


#endif //SPICYGOAT_PLAYERTRACKER_H
