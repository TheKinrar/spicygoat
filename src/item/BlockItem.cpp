//
// Created by thekinrar on 06/01/23.
//

#include "BlockItem.h"

#include "../Server.h"

void BlockItem::onUseOn(EntityPlayer& player, const PacketUseItemOn& packet) const {
    if(player.getGamemode() == GameMode::GameMode::Creative) {
        Server::get().getWorld().setBlockState(packet.position.relative(packet.face), block);

        Server::get().broadcastPacket(PacketBlockUpdate(packet.position.relative(packet.face),
                                                        Server::get().getPalette()->getBlockStateId(block)));
    }
}
