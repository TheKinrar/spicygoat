//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include <spicygoat/entities/Entity.h>
#include <spicygoat/events/Event.h>

template <class E>
class EntityEvent : public Event<E> {
    std::shared_ptr<Entity> entity;

   public:
    explicit EntityEvent(const std::shared_ptr<Entity>& entity) : entity(entity) {}

    [[nodiscard]]
    const std::shared_ptr<Entity>& getEntity() const {
        return entity;
    }
};
