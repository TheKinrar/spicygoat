//
// Created by thekinrar on 17/09/2020.
//

#include <iostream>
#include "PlayerConnection.h"
#include "../../protocol/packets/play/clientbound/PacketChatMessageCB.h"
#include "../../Server.h"
#include "../../config/Config.h"

PlayerConnection::PlayerConnection(TCPConnection &connection, EntityPlayer &player) : connection(connection),
                                                                                      player(player) {}

void PlayerConnection::onTeleportConfirm(const PacketTeleportConfirm &packet) {
    // TODO confirm TP
}

void PlayerConnection::onClientStatus(const PacketClientStatus &packet) {
    // TODO perform respawn (?) and handle stats request
}

void PlayerConnection::onClientSettings(const PacketClientSettings &packet) {
    // TODO
}

void PlayerConnection::onPluginMessage(const PacketPluginMessageSB &packet) {
    // TODO
}

void PlayerConnection::onKeepAlive(const PacketKeepAliveSB &packet) {
    connection.confirmKeepAlive(packet.id);
}

void PlayerConnection::onPlayerPosition(const PacketPlayerPosition &packet) {
    player.setNextPosition(packet.x, packet.y, packet.z);
    player.setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerPositionLook(const PacketPlayerPositionLook &packet) {
    player.setNextPosition(packet.x, packet.y, packet.z);
    player.setNextLook(packet.yaw, packet.pitch);
    player.setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerLook(const PacketPlayerLook &packet) {
    player.setNextLook(packet.yaw, packet.pitch);
    player.setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerAbilities(const PacketPlayerAbilitiesSB &packet) {
    // TODO
}

void PlayerConnection::onPlayerDigging(const PacketPlayerDigging &packet) {
    if(packet.status == PacketPlayerDigging::Status::STARTED_DIGGING) {
        if(Config::get().gamemode == 1) {
            Server::get().getWorld().setBlockState(packet.position, BlockState("minecraft:air"));
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

void PlayerConnection::onSetCreativeSlot(const PacketSetCreativeSlot &packet) {
    connection.getPlayer()->inventory.setSlot(packet.slot, packet.stack);
}

void PlayerConnection::onUseItemOn(const PacketUseItemOn &packet) {
    if(Config::get().gamemode == 1) {
        ItemStack stack = connection.getPlayer()->inventory.getSelected();
        if(stack.present) {
            auto key = Server::get().getItemRegistry().entriesR.at(stack.id);
            BlockState bs(key);
            auto blockId = Server::get().getPalette()->getBlockStateId(bs);
            if(blockId != -1) {
                Server::get().getWorld().setBlockState(packet.position.relative(packet.face), bs);
            }
        }
    }
}
