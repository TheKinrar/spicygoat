//
// Created by thekinrar on 01/04/19.
//

#include "Entity.h"

#include <iostream>

#include "../Server.h"
#include "../protocol/packets/play/clientbound/PacketEntityHeadRotation.h"
#include "../protocol/packets/play/clientbound/PacketEntityLook.h"
#include "../protocol/packets/play/clientbound/PacketEntityMove.h"
#include "../protocol/packets/play/clientbound/PacketEntityTeleport.h"
#include "../util/uuid.h"

Entity::Entity() : eid(Server::get().nextEID()), uuid(uuids::generate()) {
    tracker = Server::createTracker(*this);
}

Entity::Entity(const uuids::uuid& uuid) : eid(Server::get().nextEID()), uuid(uuid) {
    tracker = Server::createTracker(*this);
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
    tracker->tick();

    if(location != nextLocation) {
        bool newChunk =
            location.getChunkX() != nextLocation.getChunkX() || location.getChunkZ() != nextLocation.getChunkZ();

        m_nextLocation.lock();

        bool moved = (location.getX() != nextLocation.getX()) || (location.getY() != nextLocation.getY()) ||
                     (location.getZ() != nextLocation.getZ());

        bool looked = (location.getYaw() != nextLocation.getYaw()) || (location.getPitch() != nextLocation.getPitch());

        if(moved) {
            double dx = std::round(4096 * nextLocation.getX()) - std::round(4096 * location.getX());
            double dy = std::round(4096 * nextLocation.getY()) - std::round(4096 * location.getY());
            double dz = std::round(4096 * nextLocation.getZ()) - std::round(4096 * location.getZ());

            if(dx < -32768 || dx > 32767 || dy < -32768 || dy > 32767 || dz < -32768 || dz > 32767) {
                PacketEntityTeleport p(eid, nextLocation, nextOnGround);
                tracker->broadcast(p);
            } else if(looked) {
                PacketEntityMoveLook p(eid, dx, dy, dz, nextLocation.getYaw(), nextLocation.getPitch(), nextOnGround);
                tracker->broadcast(p);
            } else {
                PacketEntityMove p(eid, dx, dy, dz, nextOnGround);
                tracker->broadcast(p);
            }
        } else {
            PacketEntityLook p(eid, location, nextLocation, nextOnGround);
            tracker->broadcast(p);
        }

        if(looked) {
            // We could support different head and body yaws, but why
            PacketEntityHeadRotation p(eid, nextLocation.getYaw());
            tracker->broadcast(p);
        }

        location = nextLocation;

        m_nextLocation.unlock();

        if(newChunk) {
            chunkChanged();
        }
    }

    onGround = nextOnGround;
}

void Entity::chunkChanged() {}

std::string Entity::toString() {
    return std::string("Entity{eid=") + std::to_string(eid) + "}";
}

const Location Entity::getLocation() const {
    return location;
}

bool Entity::isOnGround() const {
    return onGround;
}

int Entity::getProtocolType() {
    return Server::get().getEntityRegistry().getId(getType());
}
