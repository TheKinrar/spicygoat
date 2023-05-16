//
// Created by thekinrar on 12/03/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/entities/types/EntityFireball.h>
#include <spicygoat/events/EntityCollisionEvent.h>

void EntityFireball::tick() {
    Entity::tick();

    RayCast cast = move(getVelocity());
    if(cast.collided()) {
        EntityCollisionEvent event(ptr());
        event.call();

        Server::get().removeEntity(*this);
    }
}
