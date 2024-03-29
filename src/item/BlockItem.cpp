//
// Created by thekinrar on 06/01/23.
//

#include <spicygoat/Server.h>
#include <spicygoat/item/BlockItem.h>
#include <spicygoat/util/BlockPlaceContext.h>

BlockItem::BlockItem(const std::string& name, const Block& block) : Item(name), block(block) {
    Server::get().getItemRegistry().addBlockItem(*this);
}

void BlockItem::onUseOn(EntityPlayer& player, const PacketUseItemOn& packet) const {
    bool place = false;

    if(player.getGamemode() == GameMode::GameMode::Creative) {
        place = true;
    } else if(player.getGamemode() == GameMode::GameMode::Survival) {
        auto& inv = player.getInventory();
        auto stack = inv.getSelected();
        stack.setCount(stack.count - 1);
        inv.setSlot(inv.getSelectedSlot(), stack);

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
