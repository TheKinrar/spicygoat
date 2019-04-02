//
// Created by thekinrar on 01/04/19.
//

#include "Entity.h"
#include "../Server.h"

Entity::Entity() {
    eid = Server::get()->nextEID();
}

int32_t Entity::getEID() {
    return eid;
}

std::string Entity::toString() {
    return std::string("Entity{eid=") + std::to_string(eid) + "}";
}
