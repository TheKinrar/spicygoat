//
// Created by thekinrar on 18/09/2020.
//

#include <stdexcept>
#include <sstream>

#include "packets.h"

Packet* Packets::parse(PacketData* data, ProtocolState state) {
    int id = data->readVarInt();

    if(state == ProtocolState::HANDSHAKE) {
        if(id == S_HANDSHAKE) {
            return new PacketHandshake(data);
        }
    } else if(state == ProtocolState::STATUS) {
        switch(id) {
            case S_REQUEST:
                return new PacketRequest(data);
            case S_PING:
                return new PacketPing(data);
        }
    } else if(state == ProtocolState::LOGIN) {
        switch(id) {
            case S_LOGIN_START:
                return new PacketLoginStart(data);
        }
    } else if(state == ProtocolState::PLAY) {
        switch(id) {
            case S_TELEPORT_CONFIRM:
                return new PacketTeleportConfirm(data);
            case S_CHAT_MESSAGE:
                return new PacketChatMessageSB(data);
            case S_CLIENT_STATUS:
                return new PacketClientStatus(data);
            case S_CLIENT_SETTINGS:
                return new PacketClientSettings(data);
            case S_PLUGIN_MESSAGE:
                return new PacketPluginMessageSB(data);
            case S_KEEP_ALIVE:
                return new PacketKeepAliveSB(data);
            case S_PLAYER_POSITION:
                return new PacketPlayerPosition(data);
            case S_PLAYER_POSITION_LOOK:
                return new PacketPlayerPositionLook(data);
            case S_PLAYER_LOOK:
                return new PacketPlayerLook(data);
            case 0x16:
                return nullptr; // TODO Player
            case S_PLAYER_ABILITIES:
                return new PacketPlayerAbilitiesSB(data);
            case S_PLAYER_DIGGING:
                return new PacketPlayerDigging(data);
            case S_ENTITY_ACTION:
                return new PacketEntityAction(data);
            case 0x2F:
                return nullptr; // TODO Animation
        }
    }

    std::stringstream ss;
    ss << "Protocol error: invalid packet ID 0x" << std::hex << id;
    throw std::runtime_error(ss.str());
}
