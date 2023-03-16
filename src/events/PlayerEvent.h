//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include "Event.h"
#include <spicygoat/entities/types/EntityPlayer.h>

template <class E>
class PlayerEvent : public Event<E> {
    std::shared_ptr<EntityPlayer> player;

   public:
    explicit PlayerEvent(const std::shared_ptr<EntityPlayer>& player) : player(player) {}

    [[nodiscard]]
    const std::shared_ptr<EntityPlayer>& getPlayer() const {
        return player;
    }
};
