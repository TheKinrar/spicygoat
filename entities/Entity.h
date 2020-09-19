//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITY_H
#define SPICYGOAT_ENTITY_H

#include <mutex>
#include <cstdint>
#include <string>
#include <set>

class EntityTracker;
#include "../world/geo/Location.h"
#include "../tracking/EntityTracker.h"
#include "../protocol/packets/ClientBoundPacket.h"

class Entity {
public:
    explicit Entity();

    int32_t getEID();

    const Location getLocation() const;

    bool isOnGround() const;

    void setNextLocation(Location loc);
    void setNextPosition(double x, double y, double z);
    void setNextLook(float yaw, float pitch);
    void setNextOnGround(bool onGround);

    virtual std::unique_ptr<ClientBoundPacket> createPacket() = 0;
    virtual std::unique_ptr<ClientBoundPacket> removePacket() = 0;

    virtual void tick();

    virtual std::string toString();

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


#endif //SPICYGOAT_ENTITY_H
