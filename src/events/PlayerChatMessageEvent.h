//
// Created by thekinrar on 15/03/23.
//

#pragma once

#include "Event.h"

#include <utility>

class PlayerChatMessageEvent : public Event<PlayerChatMessageEvent> {
    std::string message;

   public:
    explicit PlayerChatMessageEvent(std::string  message) : message(std::move(message)) {}

    [[nodiscard]]
    const std::string& getMessage() const {
        return message;
    }

    void setMessage(const std::string& message) {
        PlayerChatMessageEvent::message = message;
    }
};
