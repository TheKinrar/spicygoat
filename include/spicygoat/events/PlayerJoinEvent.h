//
// Created by thekinrar on 16/03/23.
//

#pragma once

#include <spicygoat/events/PlayerEvent.h>

#include <utility>

class PlayerJoinEvent : public PlayerEvent<PlayerJoinEvent> {
    std::string joinMessage;

   public:
    PlayerJoinEvent(const std::shared_ptr<EntityPlayer>& player, std::string joinMessage)
        : PlayerEvent(player), joinMessage(std::move(joinMessage)) {}

    [[nodiscard]]
    const std::string& getJoinMessage() const {
        return joinMessage;
    }

    void setJoinMessage(const std::string& joinMessage) {
        PlayerJoinEvent::joinMessage = joinMessage;
    }
};
