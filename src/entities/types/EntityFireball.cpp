//
// Created by thekinrar on 12/03/23.
//

#include "EntityFireball.h"

#include "../../Server.h"

void EntityFireball::tick() {
    Entity::tick();

    RayCast cast = move(getVelocity());
    if(cast.collided()) {
        Server::get().removeEntity(*this);
    }
}
