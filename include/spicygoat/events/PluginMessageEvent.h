//
// Created by thekinrar on 16/03/23.
//

#pragma once

#include <spicygoat/events/PlayerEvent.h>

#include <utility>

class PluginMessageEvent : public PlayerEvent<PluginMessageEvent> {
    std::string channel;
    std::vector<std::byte> data;

   public:
    PluginMessageEvent(const std::shared_ptr<EntityPlayer>& player, std::string channel,
                       const std::vector<std::byte>& data)
        : PlayerEvent(player), channel(std::move(channel)), data(data) {}

    [[nodiscard]]
    const std::string& getChannel() const {
        return channel;
    }

    [[nodiscard]]
    const std::vector<std::byte>& getData() const {
        return data;
    }
};
