//
// Created by thekinrar on 06/01/23.
//

#include "BlockItem.h"

#include "../Server.h"

void BlockItem::onUseOn(EntityPlayer& player, const PacketUseItemOn& packet) const {
    bool place = false;

    if(player.getGamemode() == GameMode::GameMode::Creative) {
        place = true;
    } else if(player.getGamemode() == GameMode::GameMode::Survival) {
        auto& inv = player.inventory;
        auto stack = inv->getSelected();
        stack.setCount(stack.count - 1);
        inv->set(inv->getSelectedSlot(), stack);

        place = true;
    }

    if(place) {
        auto state = block.getStateToPlace(player.getLocation(), packet);

        Server::get().getWorld().setBlockState(packet.position.relative(packet.face), state);

        Server::get().broadcastPacket(PacketBlockUpdate(packet.position.relative(packet.face),
                                                        Server::get().getPalette()->getBlockStateId(state)));
    }
}
