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
        std::cout << "nextloc" << std::endl;

        m_nextLocation.unlock();
    }
}

std::string Entity::toString() {
    return std::string("Entity{eid=") + std::to_string(eid) + "}";
}
