//
// Created by thekinrar on 07/04/23.
//

#pragma once

#include <spicygoat/events/PlayerEvent.h>

class PlayerUseItemEvent : public PlayerEvent<PlayerUseItemEvent> {
   public:
    explicit PlayerUseItemEvent(const std::shared_ptr<EntityPlayer>& player) : PlayerEvent(player) {}
};
