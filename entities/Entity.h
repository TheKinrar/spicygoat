//
// Created by thekinrar on 01/04/19.
//

#ifndef SPICYGOAT_ENTITY_H
#define SPICYGOAT_ENTITY_H

#include <cstdint>
#include <string>

class Entity {
public:
    Entity();

    int32_t getEID();

    virtual std::string toString();

private:
    int32_t eid;
};


#endif //SPICYGOAT_ENTITY_H
