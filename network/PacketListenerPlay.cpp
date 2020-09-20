//
// Created by thekinrar on 17/09/2020.
//

#include "PacketListenerPlay.h"

void PacketListenerPlay::handle(const ServerBoundPacket& packet) {
    switch (packet.getId()) {
        case Packets::S_CHAT_MESSAGE:
            onChatMessage(static_cast<const PacketChatMessageSB&>(packet));
            break;
        case Packets::S_TELEPORT_CONFIRM:
            onTeleportConfirm(static_cast<const PacketTeleportConfirm&>(packet));
            break;
        case Packets::S_CLIENT_STATUS:
            onClientStatus(static_cast<const PacketClientStatus&>(packet));
            break;
        case Packets::S_CLIENT_SETTINGS:
            onClientSettings(static_cast<const PacketClientSettings&>(packet));
            break;
        case Packets::S_PLUGIN_MESSAGE:
            onPluginMessage(static_cast<const PacketPluginMessageSB&>(packet));
            break;
        case Packets::S_KEEP_ALIVE:
            onKeepAlive(static_cast<const PacketKeepAliveSB&>(packet));
            break;
        case Packets::S_PLAYER_POSITION:
            onPlayerPosition(static_cast<const PacketPlayerPosition&>(packet));
            break;
        case Packets::S_PLAYER_POSITION_LOOK:
            onPlayerPositionLook(static_cast<const PacketPlayerPositionLook&>(packet));
            break;
        case Packets::S_PLAYER_LOOK:
            onPlayerLook(static_cast<const PacketPlayerLook&>(packet));
            break;
        case Packets::S_PLAYER_ABILITIES:
            onPlayerAbilities(static_cast<const PacketPlayerAbilitiesSB&>(packet));
            break;
        case Packets::S_PLAYER_DIGGING:
            onPlayerDigging(static_cast<const PacketPlayerDigging&>(packet));
            break;
        case Packets::S_ENTITY_ACTION:
            onEntityAction(static_cast<const PacketEntityAction&>(packet));
            break;
    }
}
