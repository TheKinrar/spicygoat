//
// Created by thekinrar on 17/09/2020.
//

#include "PlayerConnection.h"

#include <iostream>

#include "../../../data/out/blocks.h"
#include "../../Server.h"
#include "../../config/Config.h"
#include "../../entities/types/EntityItem.h"
#include "../../protocol/packets/play/clientbound/PacketAckAction.h"
#include "../../protocol/packets/play/clientbound/PacketChatMessageCB.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

static std::shared_ptr<spdlog::logger> chatLogger = spdlog::stdout_color_mt("Chat");

PlayerConnection::PlayerConnection(TCPConnection &connection, EntityPlayer &player)
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
    player.setFlying(packet.flying, true);
}

void PlayerConnection::onPlayerDigging(const PacketPlayerDigging &packet) {
    updateSequence(packet.sequence);

    if(packet.status == PacketPlayerDigging::Status::STARTED_DIGGING) {
        if(player.getGamemode() == GameMode::GameMode::Creative) {
            Server::get().getWorld().setBlockState(packet.position, Blocks::air.getDefaultState());

            Server::get().broadcastPacket(PacketBlockUpdate(
                packet.position, Server::get().getPalette()->getBlockStateId(Blocks::air.getDefaultState())));
        }
    } else if(packet.status == PacketPlayerDigging::Status::FINISHED_DIGGING) {
        if(player.getGamemode() == GameMode::GameMode::Survival) {
            auto loot = Server::get().getItemRegistry().getLoot(
                Server::get().getWorld().getBlockState(packet.position));

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

void PlayerConnection::onEntityAction(const PacketEntityAction &packet) {
    // TODO
}

void PlayerConnection::onChatMessage(const PacketChatMessageSB &packet) {
    chatLogger->info("{}: {}", player.getName(), packet.message);

    Server::get().broadcastPacket(PacketChatMessageCB(player.getName() + ": " + packet.message));
}

void PlayerConnection::onChatCommand(const PacketChatCommand &packet) {
    player.getLogger().info("Launching: {}", packet.getMessage());

    Server::get().getCommandEngine().runCommand(packet.getMessage(), player);
}

void PlayerConnection::onSetCreativeSlot(const PacketSetCreativeSlot &packet) {
    player.inventory->set(packet.slot, packet.stack);
}

void PlayerConnection::onUseItemOn(const PacketUseItemOn &packet) {
    updateSequence(packet.sequence);

    ItemStack stack = player.inventory->getSelected();
    if(stack.present) {
        Server::get().getItemRegistry().get(stack.id).onUseOn(player, packet);
    }
}

void PlayerConnection::onSetHeldItem(const PacketSetHeldItem &packet) {
    player.inventory->setSelectedSlot(36 + packet.getSlot());
}
