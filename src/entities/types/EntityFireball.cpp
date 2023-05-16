//
// Created by thekinrar on 12/03/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/entities/types/EntityFireball.h>

void EntityFireball::tick() {
    Entity::tick();

    RayCast cast = move(getVelocity());
    if(cast.collided()) {
        Server::get().removeEntity(*this);
    }
}
