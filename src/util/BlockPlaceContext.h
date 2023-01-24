//
// Created by thekinrar on 23/01/23.
//

#pragma once

#include <memory>

class BlockState;
class PacketUseItemOn;
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
