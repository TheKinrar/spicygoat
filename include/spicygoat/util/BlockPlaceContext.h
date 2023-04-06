//
// Created by thekinrar on 23/01/23.
//

#pragma once

#include <spicygoat/protocol/packets/play/serverbound/PacketUseItemOn.h>
#include <spicygoat/world/geo/Location.h>

#include <memory>

class BlockState;
class World;

struct BlockPlaceContext {
    const World& world;
    const Location playerLocation;
    const PacketUseItemOn& packet;
    const std::shared_ptr<BlockState> currentState;

    BlockPlaceContext(const World& world, const Location& playerLocation, const PacketUseItemOn& packet,
                      const std::shared_ptr<BlockState>& currentState)
        : world(world), playerLocation(playerLocation), packet(packet), currentState(currentState) {}
};
