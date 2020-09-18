//
// Created by thekinrar on 17/09/2020.
//

#include <iostream>
#include "PlayerConnection.h"
#include "../../protocol/packets/play/clientbound/PacketChatMessageCB.h"
#include "../../Server.h"

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
    if(packet.status == PacketPlayerDigging::Status::FINISHED_DIGGING) {
        // TODO
    }
}

void PlayerConnection::onEntityAction(const PacketEntityAction &packet) {
    // TODO
}

void PlayerConnection::onChatMessage(const PacketChatMessageSB &packet) {
    std::cout << "[CHAT] " << player.getName() << ": " << packet.message << std::endl;

    Server::get()->broadcastPacket(new PacketChatMessageCB(player.getName() + ": " + packet.message));
}
