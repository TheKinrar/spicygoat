//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITY_H
#define SPICYGOAT_ENTITY_H

#include <mutex>
#include <cstdint>
#include <string>
#include "../world/Location.h"

class Entity {
public:
    Entity();

    int32_t getEID();

    void setNextPosition(double x, double y, double z);
    void setNextLook(float yaw, float pitch);
    void setNextOnGround(bool onGround);

    virtual void tick();

    virtual std::string toString();

private:
    int32_t eid;

    Location location;
    bool onGround = false;

    Location nextLocation;
    bool nextOnGround = false;

    std::mutex m_nextLocation;
};


#endif //SPICYGOAT_ENTITY_H
