//
// Created by thekinrar on 01/04/19.
//

#include <iostream>
#include "Entity.h"
#include "../Server.h"

Entity::Entity() {
    eid = Server::get()->nextEID();
}

int32_t Entity::getEID() {
    return eid;
}

void Entity::setNextLocation(Location loc) {
    setNextPosition(loc.getX(), loc.getY(), loc.getZ());
    setNextLook(loc.getYaw(), loc.getPitch());
}

void Entity::setNextPosition(double x, double y, double z) {
    nextLocation.setX(x);
    nextLocation.setY(y);
    nextLocation.setZ(z);
}

void Entity::setNextLook(float yaw, float pitch) {
    nextLocation.setYaw(yaw);
    nextLocation.setPitch(pitch);
}

void Entity::setNextOnGround(bool onGround) {
    nextOnGround = onGround;
}

void Entity::tick() {
    if(location != nextLocation) {
        bool newChunk = location.getChunkX() != nextLocation.getChunkX() || location.getChunkZ() != nextLocation.getChunkZ();

        m_nextLocation.lock();

        bool moved = (location.getX() != nextLocation.getX())
                || (location.getY() != nextLocation.getY())
                || (location.getZ() != nextLocation.getZ());

        bool looked = (location.getYaw() != nextLocation.getYaw())
                || (location.getPitch() != nextLocation.getPitch());

        if(moved) {
            // TODO check dist > 8 => tp

            if(looked) {
                // TODO Entity Look And Relative Move
            } else {
                // TODO Entity Relative Move
            }
        } else {
            // TODO Entity Look
        }

        location = nextLocation;

        m_nextLocation.unlock();

        if(newChunk) {
            chunkChanged();
        }
    }
}

void Entity::chunkChanged() {
}

std::string Entity::toString() {
    return std::string("Entity{eid=") + std::to_string(eid) + "}";
}

const Location Entity::getLocation() const {
    return location;
}

bool Entity::isOnGround() const {
    return onGround;
}
