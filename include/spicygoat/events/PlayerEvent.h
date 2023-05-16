//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include <spicygoat/entities/types/EntityPlayer.h>
#include <spicygoat/events/EntityEvent.h>

template <class E>
class PlayerEvent : public EntityEvent<E> {
    std::shared_ptr<EntityPlayer> player;

   public:
    explicit PlayerEvent(const std::shared_ptr<EntityPlayer>& player) : EntityEvent<E>(player), player(player) {}

    [[nodiscard]]
    const std::shared_ptr<EntityPlayer>& getPlayer() const {
        return player;
    }
};
