//
// Created by thekinrar on 19/09/2020.
//

#include <spicygoat/Server.h>
#include <spicygoat/tracking/PlayerTracker.h>

#include <iostream>

PlayerTracker::PlayerTracker(Entity &self) : EntityTracker(self) {}

PlayerTracker::~PlayerTracker() {
    destroy();
}

void PlayerTracker::tick() {
    if(destroyed) return;

    for(auto &player : Server::get().getPlayers()) {
        if(*player == self) continue;

        Location a = player->getLocation();
        Location b = self.getLocation();

        int n = Config::get().entityViewDistance;
        double dx = a.getX() - b.getX();
        double dy = a.getY() - b.getY();
        double dz = a.getZ() - b.getZ();

        if(dx <= n && dx >= -n && dy <= n && dy >= -n && dz <= n && dz >= -n) {
            if(players.insert(player).second) {
                player->getConnection().sendPacket(*self.createPacket());
                auto metaPacket = self.metadataPacket();
                if(metaPacket.has_value()) player->getConnection().sendPacket(**metaPacket);
            }
        } else {
            if(players.erase(player)) {
                player->getConnection().sendPacket(*self.removePacket());
            }
        }
    }
}

void PlayerTracker::broadcast(const ClientBoundPacket &packet) {
    for(auto &player : players) {
        player->getConnection().sendPacket(packet);
    }
}

void PlayerTracker::destroy() {
    if(destroyed) return;

    destroyed = true;

    broadcast(*self.removePacket());
}
