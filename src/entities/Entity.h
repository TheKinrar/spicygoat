//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITY_H
#define SPICYGOAT_ENTITY_H

#include <cstdint>
#include <mutex>
#include <set>
#include <string>

class EntityTracker;
#include "../protocol/packets/ClientBoundPacket.h"
#include "../tracking/EntityTracker.h"
#include "../world/geo/Location.h"

class Entity {
   public:
    explicit Entity();
    virtual ~Entity() = default;

    int32_t getEID();

    const Location getLocation() const;

    bool isOnGround() const;

    void setLocation(Location loc) {
        this->location = loc;
        this->nextLocation = loc;
    }

    void setNextLocation(Location loc);
    void setNextPosition(double x, double y, double z);
    void setNextLook(float yaw, float pitch);
    void setNextOnGround(bool onGround);

    virtual std::unique_ptr<ClientBoundPacket> createPacket() = 0;
    virtual std::unique_ptr<ClientBoundPacket> removePacket() = 0;

    virtual void tick();

    virtual std::string toString();

    bool operator==(const Entity &rhs) const {
        return eid == rhs.eid;
    }

    bool operator!=(const Entity &rhs) const {
        return !(rhs == *this);
    }

   protected:
    virtual void chunkChanged();

   private:
    int32_t eid;

    Location location;
    bool onGround = false;

    Location nextLocation;
    bool nextOnGround = false;

    std::mutex m_nextLocation;

    std::unique_ptr<EntityTracker> tracker;
};

#endif  // SPICYGOAT_ENTITY_H
