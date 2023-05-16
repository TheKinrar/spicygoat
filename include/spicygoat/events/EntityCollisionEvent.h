//
// Created by thekinrar on 07/04/23.
//

#pragma once

#include <spicygoat/events/EntityEvent.h>

class EntityCollisionEvent : public EntityEvent<EntityCollisionEvent> {
   public:
    explicit EntityCollisionEvent(const std::shared_ptr<Entity>& entity) : EntityEvent(entity) {}
};
