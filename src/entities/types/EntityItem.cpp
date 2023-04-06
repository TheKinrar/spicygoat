//
// Created by thekinrar on 07/01/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/entities/types/EntityItem.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketPickupItem.h>
#include <spicygoat/tracking/PlayerTracker.h>

void EntityItem::tick() {
    Entity::tick();

    if(pickupDelay == 0) {
        const auto& players = dynamic_cast<PlayerTracker&>(getTracker()).getPlayers();
        for(const auto& player : players) {
            if(player->getLocation().distanceSquared(getLocation()) < 1 ||
               player->getLocation().add(0, 1, 0).distanceSquared(getLocation()) < 1) {
                auto remaining = player->inventory->add(stack);

                if(remaining.count != stack.count) {
                    getTracker().broadcast(PacketPickupItem(getEID(), player->getEID(), stack.count - remaining.count));
                    if(!remaining.present) {
                        Server::get().removeEntity(*this);
                        return;
                    } else {
                        stack = remaining;
                    }
                }
            }
        }
    } else if(pickupDelay > 0) {
        pickupDelay--;
    }

    auto vel = getVelocity();

    // Gravity
    vel = vel.add(0, -0.04, 0);

    // TODO push out of blocks if we're clipping

    if(!isOnGround() || vel.horizontalLengthSquared() > 1.0/8000) {
        RayCast cast = move(vel, true);
        if(cast.collidedX()) vel.setX(0);
        if(cast.collidedZ()) vel.setZ(0);
        if(cast.collidedY()) {
            if(vel.getY() < 0)
                setNextOnGround(true);

            vel.setY(0);
        }

        vel = vel.multiply(0.98, 0.98, 0.98);
    }

    setVelocity(vel);
}
