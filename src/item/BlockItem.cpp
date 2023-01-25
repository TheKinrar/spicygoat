//
// Created by thekinrar on 06/01/23.
//

#include "BlockItem.h"

#include "../util/BlockPlaceContext.h"
#include "../Server.h"

void BlockItem::onUseOn(EntityPlayer& player, const PacketUseItemOn& packet) const {
    bool place = false;

    if(player.getGamemode() == GameMode::GameMode::Creative) {
        place = true;
    } else if(player.getGamemode() == GameMode::GameMode::Survival) {
        auto& inv = player.inventory;
        auto stack = inv->getSelected();
        stack.setCount(stack.count - 1);
        inv->setSlot(inv->getSelectedSlot(), stack);

        place = true;
    }

    if(place) {
        auto& world = Server::get().getWorld();
        auto placedPos = packet.position.relative(packet.face);

        auto state = block.getStateToPlace(
            BlockPlaceContext(world, player.getLocation(), packet, world.getBlockState(placedPos)));

        world.setBlockState(placedPos, state);

        Server::get().broadcastPacket(PacketBlockUpdate(placedPos, Server::get().getPalette()->getBlockStateId(state)));
    }
}
