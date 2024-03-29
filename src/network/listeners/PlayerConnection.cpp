//
// Created by thekinrar on 17/09/2020.
//

#include "PlayerConnection.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spicygoat/Server.h>
#include <spicygoat/config/Config.h>
#include <spicygoat/data/blocks.h>
#include <spicygoat/entities/types/EntityFireball.h>
#include <spicygoat/entities/types/EntityItem.h>
#include <spicygoat/events/Event.h>
#include <spicygoat/events/PlayerChatMessageEvent.h>
#include <spicygoat/events/PlayerUseItemEvent.h>
#include <spicygoat/events/PluginMessageEvent.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketAckAction.h>
#include <spicygoat/protocol/packets/play/clientbound/PacketChatMessageCB.h>
#include <spicygoat/util/except.h>

#include <iostream>

PlayerConnection::PlayerConnection(TCPConnection &connection, const std::shared_ptr<EntityPlayer> &player)
    : connection(connection), player(player) {}

void PlayerConnection::tick() {
    if(sequence != -1) {
        connection.sendPacket(PacketAckAction(sequence));
        sequence = -1;
    }
}

void PlayerConnection::updateSequence(int sequence) {
    if(sequence > this->sequence) {
        this->sequence = sequence;
    }
}

void PlayerConnection::onTeleportConfirm(const PacketTeleportConfirm &packet) {
    // TODO confirm TP
}

void PlayerConnection::onClientStatus(const PacketClientStatus &packet) {
    // TODO perform respawn (?) and handle stats request
}

void PlayerConnection::onClientSettings(const PacketClientSettings &packet) {
    player->setRenderDistance(packet.renderDistance);
}

void PlayerConnection::onPluginMessage(const PacketPluginMessageSB &packet) {
    PluginMessageEvent(player, packet.channel, packet.data).call();
}

void PlayerConnection::onKeepAlive(const PacketKeepAliveSB &packet) {
    connection.confirmKeepAlive(packet.id);
}

void PlayerConnection::onPlayerPosition(const PacketPlayerPosition &packet) {
    if(!player->isSpawned()) return;

    player->setNextPosition(packet.x, packet.y, packet.z);
    player->setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerPositionLook(const PacketPlayerPositionLook &packet) {
    if(!player->isSpawned()) return;

    player->setNextPosition(packet.x, packet.y, packet.z);
    player->setNextLook(packet.yaw, packet.pitch);
    player->setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerLook(const PacketPlayerLook &packet) {
    if(!player->isSpawned()) return;

    player->setNextLook(packet.yaw, packet.pitch);
    player->setNextOnGround(packet.onGround);
}

void PlayerConnection::onPlayerAbilities(const PacketPlayerAbilitiesSB &packet) {
    player->setFlying(packet.flying, true);
}

void PlayerConnection::onPlayerDigging(const PacketPlayerDigging &packet) {
    updateSequence(packet.sequence);

    if(packet.status == PacketPlayerDigging::Status::STARTED_DIGGING) {
        if(player->getGamemode() == GameMode::GameMode::Creative) {
            Server::get().getWorld().setBlockState(packet.position, Blocks::air.getDefaultState());

            Server::get().broadcastPacket(PacketBlockUpdate(
                packet.position, Server::get().getPalette()->getBlockStateId(Blocks::air.getDefaultState())));
        }
    } else if(packet.status == PacketPlayerDigging::Status::FINISHED_DIGGING) {
        if(player->getGamemode() == GameMode::GameMode::Survival) {
            auto loot =
                Server::get().getItemRegistry().getLoot(Server::get().getWorld().getBlockState(packet.position));

            Server::get().getWorld().setBlockState(packet.position, Blocks::air.getDefaultState());
            Server::get().broadcastPacket(PacketBlockUpdate(
                packet.position, Server::get().getPalette()->getBlockStateId(Blocks::air.getDefaultState())));

            if(loot.present) {
                auto e = std::make_unique<EntityItem>(loot);
                e->setLocation(Location::center(packet.position));
                Server::get().spawnEntity(std::move(e));
            }
        }
    }
}

void PlayerConnection::onEntityAction(const PacketEntityAction &packet) {}

void PlayerConnection::onChatMessage(const PacketChatMessageSB &packet) {
    PlayerChatMessageEvent event(player, packet.message);
    event.call();
    Server::get().broadcastMessage(player->getName() + ": " + event.getMessage());
}

void PlayerConnection::onChatCommand(const PacketChatCommand &packet) {
    player->getLogger().info("Launching: {}", packet.getMessage());

    Server::get().getCommandEngine().runCommand(packet.getMessage(), *player);
}

void PlayerConnection::onSetCreativeSlot(const PacketSetCreativeSlot &packet) {
    player->getInventory().setSlot(packet.slot, packet.stack);
}

void PlayerConnection::onUseItemOn(const PacketUseItemOn &packet) {
    updateSequence(packet.sequence);

    ItemStack stack = player->getInventory().getSelected();
    if(stack.present) {
        Server::get().getItemRegistry().get(stack.id).onUseOn(*player, packet);
    }
}

void PlayerConnection::onSetHeldItem(const PacketSetHeldItem &packet) {
    player->getInventory().setSelectedSlot(36 + packet.getSlot());
}

void PlayerConnection::onClickWindow(const PacketClickWindow &packet) {
    if(packet.windowId == 0) {
        player->getInventory().onClick(packet);
    } else {
        throw protocol_error("Unknown window ID");
    }
}

void PlayerConnection::onUseItem(const PacketUseItem &packet) {
    PlayerUseItemEvent(player).call();
}
