//
// Created by thekinrar on 18/09/2020.
//

#include <spicygoat/protocol/packets.h>

#include <sstream>
#include <stdexcept>

std::unique_ptr<Packet> Packets::parse(PacketData& data, ProtocolState state) {
    int id = data.readVarInt();

    if(state == ProtocolState::HANDSHAKE) {
        if(id == S_HANDSHAKE) {
            return std::make_unique<PacketHandshake>(data);
        }
    } else if(state == ProtocolState::STATUS) {
        switch(id) {
            case S_REQUEST:
                return std::make_unique<PacketRequest>(data);
            case S_PING:
                return std::make_unique<PacketPing>(data);
        }
    } else if(state == ProtocolState::LOGIN) {
        switch(id) {
            case S_LOGIN_START:
                return std::make_unique<PacketLoginStart>(data);
            case S_PLUGIN_RESPONSE:
                return std::make_unique<PacketPluginResponse>(data);
        }
    } else if(state == ProtocolState::PLAY) {
        switch(id) {
            case S_TELEPORT_CONFIRM:
                return std::make_unique<PacketTeleportConfirm>(data);
            case S_CHAT_COMMAND:
                return std::make_unique<PacketChatCommand>(data);
            case S_CHAT_MESSAGE:
                return std::make_unique<PacketChatMessageSB>(data);
            case S_CLIENT_STATUS:
                return std::make_unique<PacketClientStatus>(data);
            case S_CLIENT_SETTINGS:
                return std::make_unique<PacketClientSettings>(data);
            case S_PLUGIN_MESSAGE:
                return std::make_unique<PacketPluginMessageSB>(data);
            case S_KEEP_ALIVE:
                return std::make_unique<PacketKeepAliveSB>(data);
            case S_PLAYER_POSITION:
                return std::make_unique<PacketPlayerPosition>(data);
            case S_PLAYER_POSITION_LOOK:
                return std::make_unique<PacketPlayerPositionLook>(data);
            case S_PLAYER_LOOK:
                return std::make_unique<PacketPlayerLook>(data);
            case 0x16:
                return nullptr;  // TODO Player
            case S_PLAYER_ABILITIES:
                return std::make_unique<PacketPlayerAbilitiesSB>(data);
            case S_PLAYER_DIGGING:
                return std::make_unique<PacketPlayerDigging>(data);
            case S_ENTITY_ACTION:
                return std::make_unique<PacketEntityAction>(data);
            case 0x2F:
                return nullptr;  // TODO Animation
            case S_CLOSE_WINDOW:
                return nullptr;
            case S_SET_CREATIVE_SLOT:
                return std::make_unique<PacketSetCreativeSlot>(data);
            case S_USE_ITEM_ON:
                return std::make_unique<PacketUseItemOn>(data);
            case S_SET_HELD_ITEM:
                return std::make_unique<PacketSetHeldItem>(data);
            case S_USE_ITEM:
                return nullptr;
            case S_CLICK_WINDOW:
                return std::make_unique<PacketClickWindow>(data);
        }
    }

    std::stringstream ss;
    ss << "Protocol error: invalid packet ID 0x" << std::hex << id;
    throw std::runtime_error(ss.str());
}
