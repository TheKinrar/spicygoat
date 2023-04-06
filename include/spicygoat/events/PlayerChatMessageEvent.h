//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include <utility>

#include <spicygoat/events/PlayerEvent.h>

class PlayerChatMessageEvent : public PlayerEvent<PlayerChatMessageEvent> {
    std::string message;

   public:
    explicit PlayerChatMessageEvent(const std::shared_ptr<EntityPlayer>& player, std::string message)
        : PlayerEvent(player), message(std::move(message)) {}

    [[nodiscard]]
    const std::string& getMessage() const {
        return message;
    }

    void setMessage(const std::string& message) {
        PlayerChatMessageEvent::message = message;
    }
};
