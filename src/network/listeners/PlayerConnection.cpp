//
// Created by thekinrar on 17/09/2020.
//

#include "PlayerConnection.h"

#include <iostream>

#include "../../Server.h"
#include "../../config/Config.h"
#include "../../entities/types/EntityItem.h"
#include "../../protocol/packets/play/clientbound/PacketChatMessageCB.h"

PlayerConnection::PlayerConnection(TCPConnection &connection, EntityPlayer &player)
    : connection(connection), player(player) {}

void PlayerConnection::onTeleportConfirm(const PacketTeleportConfirm &packet) {
    // TODO confirm TP
}

void PlayerConnection::onClientStatus(const PacketClientStatus &packet) {
    // TODO perform respawn (?) and handle stats request
}

void PlayerConnection::onClientSettings(const PacketClientSettings &packet) {
    player.setRenderDistance(packet.renderDistance);
}

void PlayerConnection::onPluginMessage(const PacketPluginMessageSB &packet) {
    // TODO
}

void PlayerConnection::onKeepAlive(const PacketKeepAliveSB &packet) {
    connection.confirmKeepAlive(packet.id);
}

void PlayerConnection::onPlayerPosition(const PacketPlayerPosition &packet) {
    if(!player.isSpawned()) return;

    player.setNextPosition(packet.x, packet.y, packet.z);
    player.setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerPositionLook(const PacketPlayerPositionLook &packet) {
    if(!player.isSpawned()) return;

    player.setNextPosition(packet.x, packet.y, packet.z);
    player.setNextLook(packet.yaw, packet.pitch);
    player.setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerLook(const PacketPlayerLook &packet) {
    if(!player.isSpawned()) return;

    player.setNextLook(packet.yaw, packet.pitch);
    player.setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerAbilities(const PacketPlayerAbilitiesSB &packet) {
    // TODO
}

void PlayerConnection::onPlayerDigging(const PacketPlayerDigging &packet) {
    if(packet.status == PacketPlayerDigging::Status::STARTED_DIGGING) {
        if(player.getGamemode() == 1) {
            Server::get().getWorld().setBlockState(packet.position, BlockState("minecraft:air"));

            Server::get().broadcastPacket(PacketBlockUpdate(
                packet.position, Server::get().getPalette()->getBlockStateId(BlockState("minecraft:air"))));
        }
    } else if(packet.status == PacketPlayerDigging::Status::FINISHED_DIGGING) {
        if(player.getGamemode() == 0) {
            auto loot = Server::get().getItemRegistry().getLoot(
                Server::get().getWorld().getBlockState(packet.position));

            Server::get().getWorld().setBlockState(packet.position, BlockState("minecraft:air"));
            Server::get().broadcastPacket(PacketBlockUpdate(
                packet.position, Server::get().getPalette()->getBlockStateId(BlockState("minecraft:air"))));

            if(loot.present) {
                auto e = std::make_unique<EntityItem>(loot);
                e->setLocation(Location::center(packet.position));
                Server::get().spawnEntity(std::move(e));
            }
        }
    }
}

void PlayerConnection::onEntityAction(const PacketEntityAction &packet) {
    // TODO
}

void PlayerConnection::onChatMessage(const PacketChatMessageSB &packet) {
    std::cout << "[CHAT] " << player.getName() << ": " << packet.message << std::endl;

    Server::get().broadcastPacket(PacketChatMessageCB(player.getName() + ": " + packet.message));
}

void PlayerConnection::onChatCommand(const PacketChatCommand &packet) {
    std::cout << "[CMD] " << player.getName() << ": " << packet.getMessage() << std::endl;

    Server::get().getCommandEngine().runCommand(packet.getMessage(), player);
}

void PlayerConnection::onSetCreativeSlot(const PacketSetCreativeSlot &packet) {
    connection.getPlayer()->inventory->setSlot(packet.slot, packet.stack);
}

void PlayerConnection::onUseItemOn(const PacketUseItemOn &packet) {
    ItemStack stack = connection.getPlayer()->inventory->getSelected();
    if(stack.present) {
        Server::get().getItemRegistry().get(stack.id).onUseOn(player, packet);
    }
}

void PlayerConnection::onSetHeldItem(const PacketSetHeldItem &packet) {
    player.inventory->setSelectedSlot(36 + packet.getSlot());
}
