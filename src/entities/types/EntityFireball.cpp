//
// Created by thekinrar on 12/03/23.
//

#include <spicygoat/entities/types/EntityFireball.h>
#include <spicygoat/Server.h>

void EntityFireball::tick() {
    Entity::tick();

    RayCast cast = move(getVelocity());
    if(cast.collided()) {
        Server::get().removeEntity(*this);
    }
}
