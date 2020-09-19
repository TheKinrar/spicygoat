//
// Created by thekinrar on 19/09/2020.
//

#include <iostream>
#include "PlayerTracker.h"
#include "../Server.h"

PlayerTracker::PlayerTracker(Entity &self) : EntityTracker(self) {}

void PlayerTracker::tick() {
    for(auto player : Server::get()->getPlayers()) {
        if(player == &self) continue;

        Location a = player->getLocation();
        Location b = self.getLocation();

        int n = Server::ENTITY_VIEW_DISTANCE;
        double dx = a.getX() - b.getX();
        double dy = a.getY() - b.getY();
        double dz = a.getZ() - b.getZ();

        if(dx <= n && dx >= -n && dy <= n && dy >= -n && dz <= n && dz >= -n) {
            if(players.insert(player).second) {
                std::cout << "+track " << player->getName() << std::endl;
                player->getConnection().sendPacket(self.createPacket().get());
            }
        } else {
            if(players.erase(player)) {
                std::cout << "-track " << player->getName() << std::endl;
                player->getConnection().sendPacket(self.removePacket().get());
            }
        }
    }
}

void PlayerTracker::broadcast(ClientBoundPacket &packet) {
    for(auto player : players) {
        player->getConnection().sendPacket(&packet);
    }
}
